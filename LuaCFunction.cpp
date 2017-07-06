#include "LuaCFunction.h"

//注册lua函数
void LuaRegisteCFunc(void* script_object)
{
	lua_State* lua_state = (lua_State*)script_object;

//proto buff相关
	LUA_REGFN(lua_state, PBHasFieldKey);
	LUA_REGFN(lua_state, PBHasFieldValue);
	LUA_REGFN(lua_state, PBFieldSize);
	LUA_REGFN(lua_state, PBClearField);

	LUA_REGFN(lua_state, PBSwap);
	LUA_REGFN(lua_state, PBSwapElements);

	LUA_REGFN(lua_state, PBSetBool);
	LUA_REGFN(lua_state, PBGetBool);

	LUA_REGFN(lua_state, PBSetEnum);
	LUA_REGFN(lua_state, PBGetEnum);

	LUA_REGFN(lua_state, PBSetInt32);
	LUA_REGFN(lua_state, PBGetInt32);
	LUA_REGFN(lua_state, PBSetRepeatedInt32);
	LUA_REGFN(lua_state, PBGetRepeatedInt32);
	LUA_REGFN(lua_state, PBAddInt32);

	LUA_REGFN(lua_state, PBSetInt64);
	LUA_REGFN(lua_state, PBGetInt64);
	LUA_REGFN(lua_state, PBSetRepeatedInt64);
	LUA_REGFN(lua_state, PBGetRepeatedInt64);
	LUA_REGFN(lua_state, PBAddInt64);

	LUA_REGFN(lua_state, PBSetPtr);
	LUA_REGFN(lua_state, PBSetPtr32);
	LUA_REGFN(lua_state, PBGetPtr);
	LUA_REGFN(lua_state, PBGetPtr32);
	LUA_REGFN(lua_state, PBAddPtr);

	LUA_REGFN(lua_state, PBSetFloat);
	LUA_REGFN(lua_state, PBGetFloat);
	LUA_REGFN(lua_state, PBSetRepeatedFloat);
	LUA_REGFN(lua_state, PBGetRepeatedFloat);
	LUA_REGFN(lua_state, PBAddFloat);

	LUA_REGFN(lua_state, PBDebugMessageStr);

	LUA_REGFN(lua_state, PBSetString);
	LUA_REGFN(lua_state, PBGetString);
	LUA_REGFN(lua_state, PBSetRepeatedString);
	LUA_REGFN(lua_state, PBGetRepeatedString);
	LUA_REGFN(lua_state, PBAddString);

	LUA_REGFN(lua_state, PBCreateMessage);
	LUA_REGFN(lua_state, PBDeleteMessage);
	LUA_REGFN(lua_state, PBGetMessage);
	LUA_REGFN(lua_state, PBMutableMessage);
	LUA_REGFN(lua_state, PBGetRepeatedMessage);
	LUA_REGFN(lua_state, PBAddMessage);

	LUA_REGFN(lua_state, PtrToString);
	LUA_REGFN(lua_state, CmpPtr);
	LUA_REGFN(lua_state, CmpPtrZero);


//辅助
	LUA_REGFN(lua_state, IfRand);

	luaL_dostring(lua_state, "function error_func(info) return info..\"\\n\"..LuaStackInfo() end");
}

 