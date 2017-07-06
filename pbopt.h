#ifndef _PROTOBUFLUA_H_
#define _PROTOBUFLUA_H_

#include <stdio.h>

#include <google/protobuf/descriptor.h>
#include <google/protobuf/reflection_ops.h>

class ProtoBufOption
{
public:
	static google::protobuf::Message* CreateMessage(const std::string& type_name);

	static bool DestroyMessage(const void* message_obj);

	//判断字段是否存在
	static bool HasFieldKey(const void* message_obj, const std::string& field_name);

	//判断non-repeated字段的值是否被设置
	static bool HasField(const void* message_obj, const std::string& field_name);

	static bool FieldSize(const void* message_obj, const std::string& field_name, int* ret_val);

	static bool ClearField(const void* message_obj, const std::string& field_name);

	static bool RemoveLast(const void* message_obj, const std::string& field_name);

	static bool Swap(void* message1, void* message2);

	static bool SwapElements(const void* message_obj, const std::string& field_name, int index1, int index2);


	static bool GetBool(const void* message_obj, const std::string& field_name, bool* ret_val);

	static bool GetEnumValue(const void* message_obj, const std::string& field_name, int* ret_val);

	static bool GetEnumName(const void* message_obj, const std::string& field_name, std::string& ret_val);

	static bool GetInt32(const void* message_obj, const std::string& field_name, google::protobuf::int32* ret_val);

	static bool GetInt64(const void* message_obj, const std::string& field_name, google::protobuf::int64* ret_val);

	static bool GetFloat(const void* message_obj, const std::string& field_name, float* ret_val);

	static bool GetString(const void* message_obj, const std::string& field_name, std::string& ret_val);

	static bool GetMessage(const void* message_obj, const std::string& field_name, void** ret_val);
	static bool MutableMessage(const void* message_obj, const std::string& field_name, void** ret_val);


	static bool SetBool(const void* message_obj, const std::string& field_name, bool value);

	static bool SetEnumByValue(const void* message_obj, const std::string& field_name, const std::string& enum_name, google::protobuf::int32 enum_number);

	static bool SetEnumByName(const void* message_obj, const std::string& field_name, const std::string& enum_name, const std::string& enum_number_name);

	static bool SetInt32(const void* message_obj, const std::string& field_name, google::protobuf::int32 value);

	static bool SetInt64(const void* message_obj, const std::string& field_name, google::protobuf::int64 value);

	static bool SetFloat(const void* message_obj, const std::string& field_name, float value);

	static bool SetString(const void* message_obj, const std::string& field_name, const std::string& value);

	static bool SetMessage(const void* message_obj, const std::string& field_name, void* value);
	


	static bool GetRepeatedInt32(const void* message_obj, const std::string& field_name, int index, google::protobuf::int32* ret_val);

	static bool GetRepeatedInt64(const void* message_obj, const std::string& field_name, int index, google::protobuf::int64* ret_val);

	static bool GetRepeatedFloat(const void* message_obj, const std::string& field_name, int index, float* ret_val);

	static bool GetRepeatedString(const void* message_obj, const std::string& field_name, int index, std::string& ret_val);

	static bool GetRepeatedMessage(const void* message_obj, const std::string& field_name, int index, void** ret_val);



	static bool SetRepeatedInt32(const void* message_obj, const std::string& field_name, int index, google::protobuf::int32 value);

	static bool SetRepeatedInt64(const void* message_obj, const std::string& field_name, int index, google::protobuf::int64 value);

	static bool SetRepeatedFloat(const void* message_obj, const std::string& field_name, int index, float value);

	static bool SetRepeatedString(const void* message_obj, const std::string& field_name, int index, const std::string& value);



	static bool AddInt32(const void* message_obj, const std::string& field_name, google::protobuf::int32 value);

	static bool AddInt64(const void* message_obj, const std::string& field_name, google::protobuf::int64 value);

	static bool AddFloat(const void* message_obj, const std::string& field_name, float value);

	static bool AddString(const void* message_obj, const std::string& field_name, const std::string& value);

	static bool AddMessage(const void* message_obj, const std::string& field_name, void** ret_val);

	static bool DebugMessageStr(const void* message_obj,std::string& ret_val);

};

#endif //_PROTOBUFLUA_H_
