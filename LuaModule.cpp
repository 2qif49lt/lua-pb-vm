#include "LuaModule.h"
#include "pbopt.h"
#include "LuaUtil.h"

LuaVm::LuaVm()
{
	m_lustate = NULL;
}
LuaVm::~LuaVm()
{
	uninitvm();
}

/*
-- 应该使用safe模块来避免抛出异常
json_text = '[true, {"foo":"bar"}]'
local cjson_safe = require "cjson.safe"
local cs = cjson_safe.new()
local cstb = cs.decode(json_text)
print(cstb[1],cstb[2]["foo"])

-- bit32已经被官方废弃
bit32 = require"bit32"
bit32.bor(10,1) 

-- 应使用标准位操作
a=10
b=1
c = a&b
print(c)
print(a|b)
print(b<<10)
print(a&0x2)

*/
bool LuaVm::initvm(char* script_data, unsigned int script_data_size){
	m_lustate = luaL_newstate();
	luaL_openlibs(m_lustate);

	lua_pushlightuserdata(m_lustate,(void*)this);
	lua_setfield(m_lustate,LUA_REGISTRYINDEX,KEY_SPEC_FOR_VM);
	LuaRegisteCFunc(m_lustate);

	luaopen_cjson_safe(m_lustate);
//	luaopen_bit(m_lustate);


	int load_ret = luaL_loadbuffer(m_lustate, script_data, script_data_size, "");
	if (load_ret == 0)
		load_ret = lua_pcall(m_lustate, 0, LUA_MULTRET, 0);

	if (load_ret != 0)
	{
		g_lualog.log(LOG_LV_ERROR,"initvm error: %s",lua_tostring(m_lustate, -1));
		lua_close(m_lustate);
		m_lustate = NULL;
		return false;
	}

	
	return true;
}

void LuaVm::uninitvm()
{
	if (m_lustate != NULL)
	{
		lua_close(m_lustate);
		m_lustate = NULL;
	}
}


bool LuaVm::get_lua_version(string& str)
{
	char buff[1024] = {};
	bool bsucc = do_lua_func("version",">s",buff);
	str = buff;
	return bsucc;
}

bool LuaVm::testlua()
{
	char buff[10240] = {};
	int i = 0;
	string strver;
	bool bsucc = do_lua_func("Log","is",LOG_LV_INFO,"hello lua function!");
	printf("Log: %s\n",bsucc ? "succ" : "fail");

	bsucc = do_lua_func("error_func","s>s","testlua",buff);
	printf("testlua:%s. %s\n",bsucc ? "succ" : "fail",buff);
	
//	bsucc = do_lua_func("test",">i",&i);
//	printf("test:%s. %d\n",bsucc ? "succ" : "fail",i);

	bsucc = get_lua_version(strver);
	printf("get_lua_version:%s. %s\n",bsucc ? "succ" : "fail",strver.c_str());
	g_lualog.log(LOG_LV_ERROR,"get_lua_version:%s. %s",bsucc ? "succ" : "fail",strver.c_str());
	return bsucc;
}

bool LuaVm::do_lua_func(const char* func,const char* paras,...)
{
	va_list args;
	va_start(args,paras);
	bool bret = do_lua_func_inner(func,paras,args);
	va_end(args);
	return bret;
}
bool LuaVm::do_lua_func_inner(const char* func,const char* paras,va_list& args)
{
	if(m_lustate == NULL || func == NULL)
		return false;

	vm_clean_stack cl(m_lustate);

	lua_getglobal(m_lustate, "error_func"); // 脚本错误处理函数
	lua_getglobal(m_lustate, func);

	if(!lua_isfunction(m_lustate,-1))
	{
		g_lualog.log(LOG_LV_ERROR,"脚本中未定义函数: %s ",func);
		return false;
	}
	char* tmppara = const_cast<char*>(paras);
	if(tmppara == NULL)
		tmppara = "";

	int arg_num = 0;
	while(tmppara && *tmppara)
	{
		switch(*tmppara++)
		{
			case 'i':
			{
				lua_pushinteger(m_lustate, va_arg(args, int));
			}
			break;
			case 'I':
			{
				lua_pushinteger(m_lustate, va_arg(args, unsigned int));
			}
			break;
			case 'l':
			{
				lua_pushinteger(m_lustate, va_arg(args, t_int64));
			}
			break;
			case 'L':
			{
				lua_pushinteger(m_lustate, va_arg(args, t_uint64));
			}
			break;
			case 'p':  
			{
				void* val = va_arg(args, void*);
				if (val)
					lua_pushlightuserdata(m_lustate, val);
				else
					lua_pushnil(m_lustate);
			}
			break;
		case 's':  
			{
				char* val = va_arg(args, char*);
				if (val)
					lua_pushstring(m_lustate, val);
				else
					lua_pushnil(m_lustate);
			}
			break;
		case 'b':  
			{
				char* szByte = va_arg(args, char*);
				unsigned int unLen = va_arg(args, unsigned int);
				if (szByte)
					lua_pushlstring(m_lustate, szByte, unLen);
				else
					lua_pushnil(m_lustate);
			}
			break;
		case '>':
			goto ret_proc;
		default:
				g_lualog.log(LOG_LV_ERROR,"参数格式符不支持: %s(%c)",paras,paras[arg_num]);
				return false;
		}
		arg_num++;
	}

ret_proc:
	int ret_num = (int)strlen(tmppara);
	if (lua_pcall(m_lustate, arg_num, ret_num, -1 - arg_num - 1) != 0)
	{
		const char* err_info = lua_tostring(m_lustate,-1);

		g_lualog.log(LOG_LV_ERROR,"lua_pcall func: %s-%s:errinfo:%s",func,
			paras != NULL ? paras : "无参数",
			err_info != NULL ? err_info : "获取错误处理信息出错");
		return false;
	}

	ret_num = -ret_num;
	int ret_count = 0;

	while (tmppara && *tmppara)
	{
		ret_count++;
		switch (*tmppara++)
		{
		case 'i':
			{
				if (lua_type(m_lustate, ret_num) != LUA_TNUMBER)
				{
					g_lualog.log(LOG_LV_ERROR,"第%d个返回值不是整型",ret_count);
					return false;
				}
				*va_arg(args, int*) = (int)lua_tointeger(m_lustate, ret_num);
			}
			break;
		case 'I':
			{
				if (lua_type(m_lustate, ret_num) != LUA_TNUMBER)
				{
					g_lualog.log(LOG_LV_ERROR,"第%d个返回值不是整型",ret_count);
					return false;
				}
				*va_arg(args,unsigned int*) = (unsigned int)lua_tointeger(m_lustate, ret_num);
			}
			break;
		case 'l':
			{
				if (lua_type(m_lustate, ret_num) != LUA_TNUMBER)
				{
					g_lualog.log(LOG_LV_ERROR,"第%d个返回值不是整型",ret_count);
					return false;
				}
				*va_arg(args, t_int64*) = (t_int64)lua_tointeger(m_lustate, ret_num);
			}
			break;
		case 'L':
			{
				if (lua_type(m_lustate, ret_num) != LUA_TNUMBER)
				{
					g_lualog.log(LOG_LV_ERROR,"第%d个返回值不是整型",ret_count);
					return false;
				}
				*va_arg(args,t_uint64*) = (t_uint64)lua_tointeger(m_lustate, ret_num);
			}
			break;
		case 'p':
			{
				if (lua_type(m_lustate, ret_num) != LUA_TLIGHTUSERDATA)
				{
					g_lualog.log(LOG_LV_ERROR,"第%d个返回值不是指针",ret_count);
					return false;
				}
				*va_arg(args, void**) = lua_touserdata(m_lustate, ret_num);
			}
			break;
		case 's':
			{
				if (lua_type(m_lustate, ret_num) != LUA_TSTRING)
				{
					g_lualog.log(LOG_LV_ERROR,"第%d个返回值不是字符串",ret_count);
					return false;
				}
				strcpy(va_arg(args, char*), lua_tostring(m_lustate, ret_num));
			}
			break;
		default:
			{
				g_lualog.log(LOG_LV_ERROR,"输出参数格式符不支持: (%c)",*(tmppara-1));
				return false;
			}
		}
		ret_num++;
	}

	return true;
}