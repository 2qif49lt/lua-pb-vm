#ifndef _LUAINTERFACE2_H_
#define _LUAINTERFACE2_H_

#include <lua.hpp>
#include <string>

extern void LuaGetStackInfo(lua_State *lua_state, std::string& stack_info);

extern void LuaGetParamInfo(lua_State *lua_state, const char* func_name, std::string& param_info);

extern void LuaParamError(lua_State *lua_state, const char* func_name);

#define PARAM_ERROR(state) LuaParamError(state, __FUNCTION__);


#define LUA_REGFN(L, fn) lua_register(L, ("" #fn ""), (luac_##fn))
#define LUA_C_API(api) \
	extern int lua_##api(lua_State *L); \
	inline int luac_##api(lua_State *L) \
	{\
		int n = lua_##api(L); \
		return n; \
	}\
	inline int lua_##api(lua_State *L)



#endif //_LUAINTERFACE2_H_
