#ifndef _LUA_MODULE_H_
#define _LUA_MODULE_H_

#include "LuaCFunction.h"
#include <stdarg.h>
#include <list>
#include <string>
using namespace std;

class LuaVm
{
	class vm_clean_stack
	{
	public:
		vm_clean_stack(lua_State* st):toclean(st){}
		~vm_clean_stack()
		{
			lua_settop(toclean,0);
		}

	private:
		vm_clean_stack();
		lua_State* toclean;
	};
public:
	LuaVm();
	virtual ~LuaVm();

	bool initvm(char* script_data, unsigned int script_data_size);
	void uninitvm();

	bool get_lua_version(string& str);

	// 参数格式:
	/*
		i 32位有符号整型, I 32位无符号整型 int / int*
		l 64位有符号整型, L 64位无符号整型(无符号64位其实不支持,实际存储的类型还是有符号,所以不能溢出) int64 /int64*
		p 指针  输入输出只能为:void* / void**
		s 以null结尾的字符串 char* / char*, 输出时作为足够长的buff地址
		b 字符数组,该标识代表2个参数. 除字符数组指针外,还有个长度参数(不能作为输出参数)
		> 分割标志,后续格式符表示输出
	*/
	bool do_lua_func(const char* func,const char* paras,...);
	bool do_lua_func_inner(const char* func,const char* paras,va_list& args);
	bool testlua();
private:

	lua_State* m_lustate;
};


#endif //_LUA_MODULE_H_
