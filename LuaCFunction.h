#ifndef _LUACFUNCTION_H_
#define _LUACFUNCTION_H_

#include "LuaUtil.h"
#include "../pbopt/pbopt.h"
#include "../std_type.h"


LUA_C_API(IfRand)
{
	lua_pushinteger(L,rand());
	return 1;
}

//proto buff相关界面

//=============================================================================
// 功能：	创建proto message
// 参数：	GameServer：指针，
//			proto：messge名字字符串，
// 返回值：	proto：messge指针
//=============================================================================

LUA_C_API(PBCreateMessage)
{
	bool param_valid = (lua_gettop(L) >= 1 && lua_isstring(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	 
	char* msg_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);

	void* message = NULL;
	message = ProtoBufOption::CreateMessage(msg_name);
	lua_pushlightuserdata(L, message);
	call_checkin_memory(L,message);

	return 1;
}

//=============================================================================
// 功能：删除proto message
// 参数：GameServer指针，
//	   proto messge指针，
// 返回值：1，删除成功；0，删除失败（未找到该对象）
//=============================================================================
LUA_C_API(PBDeleteMessage)
{
	bool param_valid = (lua_gettop(L) >= 1 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
 
	void* msg_obj = lua_touserdata(L, 1);
	lua_remove(L, 1);

	ProtoBufOption::DestroyMessage(msg_obj);
	lua_pushnumber(L, 1);
	call_checkout_memory(L,msg_obj);

	return 1;
}

//=============================================================================
// 功能：判断proto message的字段是否存在
// 参数：message指针，
//	   字段名字字符串，
// 返回值：1，存在；0，不存在
//=============================================================================
LUA_C_API(PBHasFieldKey)
{
	bool param_valid = (lua_gettop(L) >= 2 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);

	bool has_field = ProtoBufOption::HasFieldKey(msg_obj, field_name);
	lua_pushboolean(L, has_field);

	return 1;
}

//=============================================================================
// 功能：判断proto message的non-repeated字段的值是否被设置
// 参数：message指针，
//	   字段名字字符串，
// 返回值：1，被设置；0，没被设置
//=============================================================================
LUA_C_API(PBHasFieldValue)
{
	bool param_valid = (lua_gettop(L) >= 2 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);

	bool has_field = ProtoBufOption::HasField(msg_obj, field_name);
	lua_pushboolean(L, has_field);

	return 1;
}

//=============================================================================
// 功能：取proto message的数组字段的元素个数
// 参数：message指针，
//	   字段名字字符串，
// 返回值：字段值
//		 1，成功；0，失败
//=============================================================================
LUA_C_API(PBFieldSize)
{
	bool param_valid = (lua_gettop(L) >= 2 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);

	int value;
	bool suc = ProtoBufOption::FieldSize(msg_obj, field_name, &value);
	lua_pushnumber(L, value);
	lua_pushboolean(L, suc);

	return 2;
}

//=============================================================================
// 功能：清除字段值，之后HasField返回false，FieldSize返回0
// 参数：message指针，
//	   字段名字字符串，
// 返回值：1，成功；0，失败
//=============================================================================
LUA_C_API(PBClearField)
{
	bool param_valid = (lua_gettop(L) >= 2 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);

	bool suc = ProtoBufOption::ClearField(msg_obj, field_name);
	lua_pushboolean(L, suc);

	return 1;
}

//=============================================================================
// 功能：移除repeated字段的最后一个元素
// 参数：message指针，
//	   字段名字字符串，
// 返回值：1，成功；0，失败
//=============================================================================
LUA_C_API(PBRemoveLast)
{
	bool param_valid = (lua_gettop(L) >= 2 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);

	bool suc = ProtoBufOption::RemoveLast(msg_obj, field_name);
	lua_pushboolean(L, suc);

	return 1;
}

//=============================================================================
// 功能：交换两个message的完整内容
// 参数：message指针，
//	   message指针，
// 返回值：1，成功；0，失败
//=============================================================================
LUA_C_API(PBSwap)
{
	bool param_valid = (lua_gettop(L) >= 2 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj1 = lua_touserdata(L, 1);
	if (!msg_obj1)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	void* msg_obj2 = lua_touserdata(L, 1);
	if (!msg_obj2)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);

	bool suc = ProtoBufOption::Swap(msg_obj1, msg_obj2);
	lua_pushboolean(L, suc);

	return 1;
}

//=============================================================================
// 功能：交换repeated字段的两个元素
// 参数：message指针，
//	   字段名字字符串，
//	   元素索引1
//	   元素索引2
// 返回值：1，成功；0，失败
//=============================================================================
LUA_C_API(PBSwapElements)
{
	bool param_valid = (lua_gettop(L) >= 4 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);
	int index1 = (int)lua_tonumber(L, 1);
	lua_remove(L, 1);
	int index2 = (int)lua_tonumber(L, 1);
	lua_remove(L, 1);

	bool suc = ProtoBufOption::SwapElements(msg_obj, field_name, index1, index2);
	lua_pushboolean(L, suc);

	return 1;
}

LUA_C_API(PBGetBool)
{
	bool param_valid = (lua_gettop(L) >= 2 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);

	bool value;
	bool suc = ProtoBufOption::GetBool(msg_obj, field_name, &value);
	lua_pushboolean(L, value);
	lua_pushboolean(L, suc);

	return 2;
}

LUA_C_API(PBSetBool)
{
	bool param_valid = (lua_gettop(L) >= 3 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);
	bool field_val = lua_toboolean(L, 1);
	lua_remove(L, 1);

	bool suc = ProtoBufOption::SetBool(msg_obj, field_name, field_val);
	lua_pushboolean(L, 1);

	return 1;
}

LUA_C_API(PBGetPtr32)
{
	bool param_valid = (lua_gettop(L) >= 2 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);

	int value;
	bool suc = ProtoBufOption::GetInt32(msg_obj, field_name, &value);

	__int64 value1 = value;
	lua_pushlightuserdata(L, (void *)value1);
	lua_pushboolean(L, suc);

	return 2;
}

LUA_C_API(PBGetPtr)
{
	bool param_valid = (lua_gettop(L) >= 2 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);

	__int64 value;
	bool suc = ProtoBufOption::GetInt64(msg_obj, field_name, (google::protobuf::int64*)&value);
	lua_pushlightuserdata(L, (void *)value);
	lua_pushboolean(L, suc);

	return 2;
}

LUA_C_API(PBSetPtr32)
{
	bool param_valid = (lua_gettop(L) >= 3 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);
	int field_val = (int)((long)lua_touserdata(L, 1));
	lua_remove(L, 1);

	bool suc = ProtoBufOption::SetInt32(msg_obj, field_name, field_val);
	lua_pushboolean(L, 1);

	return 1;
}

LUA_C_API(PBSetPtr)
{
	bool param_valid = (lua_gettop(L) >= 3 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);
	__int64 field_val = (__int64)lua_touserdata(L, 1);
	lua_remove(L, 1);

	bool suc = ProtoBufOption::SetInt64(msg_obj, field_name, field_val);
	lua_pushboolean(L, 1);

	return 1;
}

LUA_C_API(PBAddPtr)
{
	bool param_valid = (lua_gettop(L) >= 3 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);
	__int64 field_val = (__int64)lua_touserdata(L, 1);
	lua_remove(L, 1);

	bool suc = ProtoBufOption::AddInt64(msg_obj, field_name, field_val);
	lua_pushboolean(L, 1);

	return 1;
}

LUA_C_API(PBGetEnum)
{
	bool param_valid = (lua_gettop(L) >= 2 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);

	std::string value;
	bool suc = ProtoBufOption::GetEnumName(msg_obj, field_name, value);
	lua_pushstring(L, value.c_str());
	lua_pushboolean(L, suc);

	return 2;
}

LUA_C_API(PBSetEnum)
{
	bool param_valid = (lua_gettop(L) >= 3 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);
	char* enum_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);
	char* enum_number_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);

	bool suc = ProtoBufOption::SetEnumByName(msg_obj, field_name, enum_name, enum_number_name);
	lua_pushboolean(L, 1);

	return 1;
}

//=============================================================================
// 功能：取proto message的字段的32位整形值
// 参数：message指针，
//	   字段名字字符串，
// 返回值：字段值，
//		 1，成功；0，失败
//=============================================================================
LUA_C_API(PBGetInt32)
{
	bool param_valid = (lua_gettop(L) >= 2 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);

	int value;
	bool suc = ProtoBufOption::GetInt32(msg_obj, field_name, &value);
	lua_pushinteger(L, value);
	lua_pushboolean(L, suc);

	return 2;
}

//=============================================================================
// 功能：设置proto message的字段的32位整形值
// 参数：message指针，
//	   字段名字字符串，
//	   字段值
// 返回值：1，设置成功；0，失败
//=============================================================================
LUA_C_API(PBSetInt32)
{
	bool param_valid = (lua_gettop(L) >= 3 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);
	int field_val = lua_tointeger(L, 1);
	lua_remove(L, 1);

	bool suc = ProtoBufOption::SetInt32(msg_obj, field_name, field_val);
	lua_pushboolean(L, 1);

	return 1;
}

//=============================================================================
// 功能：取proto message的数组字段的32位整形值
// 参数：message指针，
//	   字段名字字符串，
//	   数组索引
// 返回值：字段值，
//		 1，成功；0，失败
//=============================================================================
LUA_C_API(PBGetRepeatedInt32)
{
	bool param_valid = (lua_gettop(L) >= 3 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);
	int index = lua_tointeger(L, 1);
	lua_remove(L, 1);

	int value;
	bool suc = ProtoBufOption::GetRepeatedInt32(msg_obj, field_name, index, &value);
	lua_pushinteger(L, value);
	lua_pushboolean(L, suc);

	return 2;
}

//=============================================================================
// 功能：设置proto message的数组字段的32位整形值
// 参数：message指针，
//	   字段名字字符串，
//	   数组索引
//	   字段值
// 返回值：1，设置成功；0，失败
//=============================================================================
LUA_C_API(PBSetRepeatedInt32)
{
	bool param_valid = (lua_gettop(L) >= 3 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);
	int index = lua_tointeger(L, 1);
	lua_remove(L, 1);
	int field_val = lua_tointeger(L, 1);
	lua_remove(L, 1);

	bool suc = ProtoBufOption::SetRepeatedInt32(msg_obj, field_name, index, field_val);
	lua_pushboolean(L, 1);

	return 1;
}

//=============================================================================
// 功能：增加proto message的字段的32位整形值
// 参数：message指针，
//	   字段名字字符串，
//	   字段值
// 返回值：1，设置成功；0，失败
//=============================================================================
LUA_C_API(PBAddInt32)
{
	bool param_valid = (lua_gettop(L) >= 3 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);
	int field_val = (int)lua_tointeger(L, 1);
	lua_remove(L, 1);

	bool suc = ProtoBufOption::AddInt32(msg_obj, field_name, field_val);
	lua_pushboolean(L, 1);

	return 1;
}

//=============================================================================
// 功能：取proto message的字段的64位整形值
// 参数：message指针，
//	   字段名字字符串，
// 返回值：字段值，
//		 1，成功；0，失败
//=============================================================================
LUA_C_API(PBGetInt64)
{
//#ifdef _WIN64
	bool param_valid = (lua_gettop(L) >= 2 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);

	__int64 value;
	bool suc = ProtoBufOption::GetInt64(msg_obj, field_name, (google::protobuf::int64*)&value);
	lua_pushinteger(L, value);
	lua_pushboolean(L, suc);

	return 2;
//#else
//	return 0;
//#endif
}

//=============================================================================
// 功能：设置proto message的字段的64位整形值
// 参数：message指针，
//	   字段名字字符串，
//	   字段值
// 返回值：1，设置成功；0，失败
//=============================================================================
LUA_C_API(PBSetInt64)
{
	bool param_valid = (lua_gettop(L) >= 3 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);
	__int64 field_val = lua_tointeger(L, 1);
	lua_remove(L, 1);

	bool suc = ProtoBufOption::SetInt64(msg_obj, field_name, field_val);
	lua_pushboolean(L, 1);

	return 1;
}

//=============================================================================
// 功能：取proto message的数组字段的64位整形值
// 参数：message指针，
//	   字段名字字符串，
//	   数组索引
// 返回值：字段值，
//		 1，成功；0，失败
//=============================================================================
LUA_C_API(PBGetRepeatedInt64)
{
//#ifdef _WIN64
	bool param_valid = (lua_gettop(L) >= 3 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);
	int index = lua_tointeger(L, 1);
	lua_remove(L, 1);

	__int64 value;
	bool suc = ProtoBufOption::GetRepeatedInt64(msg_obj, field_name, index, (google::protobuf::int64*)&value);
	lua_pushinteger(L, value);
	lua_pushboolean(L, suc);

	return 2;
//#else
//	return 0;
//#endif
}

//=============================================================================
// 功能：设置proto message的数组字段的64位整形值
// 参数：message指针，
//	   字段名字字符串，
//	   数组索引
//	   字段值
// 返回值：1，设置成功；0，失败
//=============================================================================
LUA_C_API(PBSetRepeatedInt64)
{
	bool param_valid = (lua_gettop(L) >= 3 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);
	int index = lua_tointeger(L, 1);
	lua_remove(L, 1);
	__int64 field_val = lua_tointeger(L, 1);
	lua_remove(L, 1);

	bool suc = ProtoBufOption::SetRepeatedInt64(msg_obj, field_name, index, field_val);
	lua_pushboolean(L, 1);

	return 1;
}

//=============================================================================
// 功能：增加proto message的字段的64位整形值
// 参数：message指针，
//	   字段名字字符串，
//	   字段值
// 返回值：1，设置成功；0，失败
//=============================================================================
LUA_C_API(PBAddInt64)
{
	bool param_valid = (lua_gettop(L) >= 3 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);
	__int64 field_val = lua_tointeger(L, 1);
	lua_remove(L, 1);

	bool suc = ProtoBufOption::AddInt64(msg_obj, field_name, field_val);
	lua_pushboolean(L, 1);

	return 1;
}

//=============================================================================
// 功能：取proto message的字段的浮点值
// 参数：message指针，
//	   字段名字字符串，
// 返回值：字段值，
//		 1，成功；0，失败
//=============================================================================
LUA_C_API(PBGetFloat)
{
	bool param_valid = (lua_gettop(L) >= 2 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);

	float value;
	bool suc = ProtoBufOption::GetFloat(msg_obj, field_name, &value);
	lua_pushnumber(L, value);
	lua_pushboolean(L, suc);

	return 2;
}

//=============================================================================
// 功能：设置proto message的字段的浮点值
// 参数：message指针，
//	   字段名字字符串，
//	   字段值
// 返回值：1，设置成功；0，失败
//=============================================================================
LUA_C_API(PBSetFloat)
{
	bool param_valid = (lua_gettop(L) >= 3 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);
	float field_val = (float)lua_tonumber(L, 1);
	lua_remove(L, 1);

	bool suc = ProtoBufOption::SetFloat(msg_obj, field_name, field_val);
	lua_pushboolean(L, 1);

	return 1;
}

//=============================================================================
// 功能：取proto message的数组字段的浮点值
// 参数：message指针，
//	   字段名字字符串，
//	   数组索引
// 返回值：字段值，
//		 1，成功；0，失败
//=============================================================================
LUA_C_API(PBGetRepeatedFloat)
{
	bool param_valid = (lua_gettop(L) >= 3 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);
	int index = lua_tointeger(L, 1);
	lua_remove(L, 1);

	float value;
	bool suc = ProtoBufOption::GetRepeatedFloat(msg_obj, field_name, index, &value);
	lua_pushnumber(L, value);
	lua_pushboolean(L, suc);

	return 2;
}

//=============================================================================
// 功能：设置proto message的数组字段的浮点值
// 参数：message指针，
//	   字段名字字符串，
//	   数组索引
//	   字段值
// 返回值：1，设置成功；0，失败
//=============================================================================
LUA_C_API(PBSetRepeatedFloat)
{
	bool param_valid = (lua_gettop(L) >= 3 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);
	int index = lua_tointeger(L, 1);
	lua_remove(L, 1);
	float field_val = (float)lua_tonumber(L, 1);
	lua_remove(L, 1);

	bool suc = ProtoBufOption::SetRepeatedFloat(msg_obj, field_name, index, field_val);
	lua_pushboolean(L, 1);

	return 1;
}

//=============================================================================
// 功能：增加proto message的字段的浮点值
// 参数：message指针，
//	   字段名字字符串，
//	   字段值
// 返回值：1，设置成功；0，失败
//=============================================================================
LUA_C_API(PBAddFloat)
{
	bool param_valid = (lua_gettop(L) >= 3 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);
	float field_val = (float)lua_tonumber(L, 1);
	lua_remove(L, 1);

	bool suc = ProtoBufOption::AddFloat(msg_obj, field_name, field_val);
	lua_pushboolean(L, 1);

	return 1;
}

//=============================================================================
// 功能：取proto message的字段的字符串值
// 参数：message指针，
//	   字段名字字符串，
// 返回值：字段值
//		 1，成功；0，失败
//=============================================================================
LUA_C_API(PBGetString)
{
	bool param_valid = (lua_gettop(L) >= 2 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);

	std::string value;
	bool suc = ProtoBufOption::GetString(msg_obj, field_name, value);
	lua_pushstring(L, value.c_str());
	lua_pushboolean(L, suc);

	return 2;
}
LUA_C_API(PBDebugMessageStr)
{
	bool param_valid = (lua_gettop(L) >= 1 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);

	std::string value;
	bool suc = ProtoBufOption::DebugMessageStr(msg_obj, value);
	lua_pushstring(L, value.c_str());
	lua_pushboolean(L, suc);

	return 2;
}
//=============================================================================
// 功能：设置proto message的字段的字符串值
// 参数：message指针，
//	   字段名字字符串，
//	   字段值
// 返回值：1，设置成功；0，失败
//=============================================================================
LUA_C_API(PBSetString)
{
	bool param_valid = (lua_gettop(L) >= 3 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);
	const char* field_val = lua_tostring(L, 1);
	lua_remove(L, 1);

	bool suc = ProtoBufOption::SetString(msg_obj, field_name, field_val);
	lua_pushboolean(L, suc);

	return 1;
}

//=============================================================================
// 功能：取proto message的数组字段的字符串值
// 参数：message指针，
//	   字段名字字符串，
//	   索引
// 返回值：字段值
//		 1，成功；0，失败
//=============================================================================
LUA_C_API(PBGetRepeatedString)
{
	bool param_valid = (lua_gettop(L) >= 3 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);
	int index = lua_tointeger(L, 1);
	lua_remove(L, 1);

	std::string value;
	bool suc = ProtoBufOption::GetRepeatedString(msg_obj, field_name, index, value);
	lua_pushstring(L, value.c_str());
	lua_pushboolean(L, suc);

	return 2;
}

//=============================================================================
// 功能：设置proto message的数组字段的字符串值
// 参数：message指针，
//	   字段名字字符串，
//	   索引
//	   字段值
// 返回值：1，设置成功；0，失败
//=============================================================================
LUA_C_API(PBSetRepeatedString)
{
	bool param_valid = (lua_gettop(L) >= 4 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);
	int index = lua_tointeger(L, 1);
	lua_remove(L, 1);
	const char* field_val = lua_tostring(L, 1);
	lua_remove(L, 1);

	bool suc = ProtoBufOption::SetRepeatedString(msg_obj, field_name, index, field_val);
	lua_pushboolean(L, suc);

	return 1;
}

//=============================================================================
// 功能：增加proto message的字段的字符串值
// 参数：message指针，
//	   字段名字字符串，
//	   字段值
// 返回值：1，设置成功；0，失败
//=============================================================================
LUA_C_API(PBAddString)
{
	bool param_valid = (lua_gettop(L) >= 3 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);
	const char* field_val = lua_tostring(L, 1);
	lua_remove(L, 1);

	bool suc = ProtoBufOption::AddString(msg_obj, field_name, field_val);
	lua_pushboolean(L, suc);

	return 1;
}

//=============================================================================
// 功能：取proto message的字段的Message值
// 参数：message指针，
//	   字段名字字符串，
// 返回值：字段值
//		 1，成功；0，失败
//=============================================================================
LUA_C_API(PBGetMessage)
{
	bool param_valid = (lua_gettop(L) >= 2 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);

	void* value;
	bool suc = ProtoBufOption::GetMessage(msg_obj, field_name, &value);
	lua_pushlightuserdata(L, value);
	lua_pushboolean(L, suc);

	return 2;
}

LUA_C_API(PBMutableMessage)
{
	bool param_valid = (lua_gettop(L) >= 2 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);

	void* value;
	bool suc = ProtoBufOption::MutableMessage(msg_obj, field_name, &value);
	lua_pushlightuserdata(L, value);
	lua_pushboolean(L, suc);

	return 2;
}

//=============================================================================
// 功能：增加proto message的字段的Message值
// 参数：message指针，
//	   字段名字字符串，
//	   字段值
// 返回值：1，设置成功；0，失败
//=============================================================================
LUA_C_API(PBAddMessage)
{
	bool param_valid = (lua_gettop(L) >= 2 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);

	void* value;
	bool suc = ProtoBufOption::AddMessage(msg_obj, field_name, &value);
	lua_pushlightuserdata(L, value);
	lua_pushboolean(L, suc);

	return 2;
}


LUA_C_API(PBGetRepeatedMessage)
{
	bool param_valid = (lua_gettop(L) >= 3 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	void* msg_obj = lua_touserdata(L, 1);
	if (!msg_obj)
	{
		PARAM_ERROR(L);
		return 0;
	}
	lua_remove(L, 1);
	char* field_name = (char*)lua_tostring(L, 1);
	lua_remove(L, 1);
	int index = lua_tointeger(L, 1);
	lua_remove(L, 1);

	void* value;
	bool suc = ProtoBufOption::GetRepeatedMessage(msg_obj, field_name, index, &value);
	lua_pushlightuserdata(L, value);
	lua_pushboolean(L, suc);

	return 2;
}

LUA_C_API(PtrToString)
{
	bool param_valid = (lua_gettop(L) == 1 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}

	void *value_ptr = lua_touserdata(L, 1);
	lua_remove(L, 1);

	__int64 value = (__int64)value_ptr;
	char value_str[50] = {0};
	sprintf(value_str,"%lld",value);
	lua_pushstring(L, value_str);
	return 1;
}

LUA_C_API(CmpPtrZero)
{
	bool param_valid = (lua_gettop(L) == 1 && lua_islightuserdata(L, 1));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}

	void *value_ptr1 = lua_touserdata(L, 1);
	lua_remove(L, 1);
	__int64 value1 = (__int64)value_ptr1;

	bool res = false;
	if (0 == value1)
	{
		res = true;
	}
	lua_pushboolean(L, res);

	return 1;
}

LUA_C_API(CmpPtr)
{
	bool param_valid = (lua_gettop(L) == 2 && lua_islightuserdata(L, 1) && lua_islightuserdata(L, 2));
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}

	void *value_ptr1 = lua_touserdata(L, 1);
	lua_remove(L, 1);
	void *value_ptr2 = lua_touserdata(L, 1);
	lua_remove(L, 1);
	__int64 value1 = (__int64)value_ptr1;
	__int64 value2 = (__int64)value_ptr2;

	int res = 0;
	if (value1 > value2)
	{
		res = 1;
	}
	else if (value1 == value2)
	{
		res = 0;
	}
	else
	{
		res = -1;
	}
	lua_pushinteger(L, res);

	return 1;
}


//=============================================================================
// 功能：输出信息到处理线程的日志 ,写入宿主程序启动时建立的日志文件
// 返回值：无
//=============================================================================
LUA_C_API(Log)
{
	bool param_valid = (lua_gettop(L) >= 2);
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	int level = (int)lua_tointeger(L, 1);
	lua_remove(L, 1);
	const char* log_info = lua_tostring(L, 1);
	lua_remove(L, 1);

	call_log(L,level, log_info);
	return 0;
}
//=============================================================================
// 功能：脚本可以创建私有的日志文件.和Log一样的功能 
// 返回值：无
//=============================================================================
LUA_C_API(LogPriv)
{
	bool param_valid = (lua_gettop(L) >= 3);
	if(!param_valid)
	{
		PARAM_ERROR(L);
		return 0;
	}
	const char* file_name = lua_tostring(L, 1);
	lua_remove(L, 1);
	int level = (int)lua_tointeger(L, 1);
	lua_remove(L, 1);
	const char* log_info = lua_tostring(L, 1);
	lua_remove(L, 1);

	call_log_priv(L,file_name,level, log_info);
	return 0;
}
//=============================================================================
// 功能：取堆栈信息
// 参数：无
// 返回值：堆栈信息字符串
//=============================================================================
LUA_C_API(LuaStackInfo)
{
	std::string stack_info;
	LuaGetStackInfo(L, stack_info);
	lua_pushstring(L, stack_info.c_str());

	return 1;
}

 
//注册lua函数
extern void LuaRegisteCFunc(void* script_object);


#endif //_LUACFUNCTION_H_