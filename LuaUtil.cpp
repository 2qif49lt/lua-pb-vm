
#include "LuaUtil.h"

 
void LuaGetStackInfo(lua_State *lua_state, std::string& stack_info)
{
	int cur_level = 0;
	lua_Debug luaDebuger;
	const int cnInfoSize = 512;
	char szInfo[cnInfoSize + 1] ={};
 
	while (lua_getstack(lua_state, cur_level++, &luaDebuger) == 1)
	{
		lua_getinfo(lua_state, "Sln", &luaDebuger);  /* retrieves function */
		stack_info += luaDebuger.short_src;
		snprintf(szInfo, cnInfoSize, "[%d %d]", luaDebuger.linedefined, luaDebuger.currentline);
		stack_info += szInfo;
		stack_info += "(";
		stack_info += luaDebuger.what;
		stack_info += ")";
		if (luaDebuger.name)
			stack_info += luaDebuger.name;

		stack_info += ": ";
		const char *name;
		int i = 1;
		while ((name = lua_getlocal(lua_state, &luaDebuger, i++)) != NULL)
		{
			int nValPos = - 1;
			if (lua_isnumber(lua_state, nValPos))
			{
				stack_info += name;
				snprintf(szInfo, cnInfoSize, "=%f ", lua_tonumber(lua_state, nValPos));
				stack_info += szInfo;
			}
			else if (lua_islightuserdata(lua_state, nValPos))
			{
				stack_info += name;
				snprintf(szInfo, cnInfoSize, "=%u ", (int)((char*)lua_touserdata(lua_state, nValPos) - (char*)0));
				stack_info += szInfo;
			}
			else if (lua_isstring(lua_state, nValPos))
			{
				stack_info += name;
				stack_info += "=";
				char *pStr = (char *)lua_tostring(lua_state, nValPos);
				size_t nLen = strlen(pStr);
				for(size_t i = 0; i < nLen; i++)
				{
					if (pStr[i] == '%')
					{
						pStr[i] = '#';
					}
				}
				stack_info += pStr;
			}
			lua_pop(lua_state, 1);  /* remove variable value */
		}

		stack_info += "\n"; 
	}
}

void LuaGetParamInfo(lua_State *lua_state, const char* func_name, std::string& param_info)
{
	const int cnLineSize = 128;
	char szLine[cnLineSize + 1] = {};
 
	snprintf(szLine, cnLineSize, "函数[%s]参数列表:\n", func_name);
	param_info+=szLine;
	int top = lua_gettop(lua_state);
	for (int i = 1; i <= top; i++) 
	{ 
		int t = lua_type(lua_state, i);
		switch (t) 
		{
		case LUA_TSTRING: /* strings */
			snprintf(szLine, cnLineSize, "字符串:\t [%s]\n", (char*)(lua_tostring(lua_state, i)));
			param_info+=szLine;
			break;
		case LUA_TBOOLEAN: /* booleans */
			snprintf(szLine, cnLineSize, lua_toboolean(lua_state, i) ? "true" : "false");
			param_info+=szLine;
			break;
		case LUA_TNUMBER: /* numbers */
			snprintf(szLine, cnLineSize, "数字:\t %g \n", lua_tonumber(lua_state, i));
			param_info+=szLine;
			break;
		default: /* other values */
			snprintf(szLine, cnLineSize, "值:\t %s \n", lua_typename(lua_state, t));
			param_info+=szLine;
			break;
		}
	}
	param_info+="________参数列表结束_________\n\n";
}

void LuaParamError(lua_State *lua_state, const char* func_name)
{
	char str_fix[1024];
	sprintf(str_fix, "lua扩展函数[%s]参数个数或者类型错误!\n", func_name);
	std::string stack_info;
	stack_info += str_fix;
	LuaGetParamInfo(lua_state, func_name, stack_info);
	sprintf(str_fix, "堆栈信息：\n");
	stack_info += str_fix;
	LuaGetStackInfo(lua_state, stack_info);
	call_log(lua_state,3,stack_info.c_str());
}


