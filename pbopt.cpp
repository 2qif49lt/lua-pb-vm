#include "pbopt.h"

google::protobuf::Message* ProtoBufOption::CreateMessage(const std::string& type_name)
{
	google::protobuf::Message* message = NULL;

	const google::protobuf::Descriptor* descriptor =
		google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(type_name);
	if (descriptor)
	{
		const google::protobuf::Message* proto_type =
			google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
		if (proto_type)
			message = proto_type->New();
	}
	else
	{
		printf("CreateMessage %s error\n", type_name.c_str());
	}

	return message;
}

bool ProtoBufOption::DestroyMessage(const void* message_obj)
{
	const google::protobuf::Message* message = (const google::protobuf::Message*)message_obj;
	if (message)
	{
		delete message;
		return true;
	}
	else
	{
		return false;
	}
}

bool ProtoBufOption::HasFieldKey(const void* message_obj, const std::string& field_name)
{
	const google::protobuf::Message& message = *(const google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
			return reflection->HasField(message, field);
	}
	return false;
}

bool ProtoBufOption::HasField(const void* message_obj, const std::string& field_name)
{
	const google::protobuf::Message& message = *(const google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
			return reflection->HasField(message, field);
	}
	return false;
}

bool ProtoBufOption::FieldSize(const void* message_obj, const std::string& field_name, int* ret_val)
{
	const google::protobuf::Message& message = *(const google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			*ret_val = reflection->FieldSize(message, field);
			return true;
		}
	}
	return false;
}

bool ProtoBufOption::ClearField(const void* message_obj, const std::string& field_name)
{
	const google::protobuf::Message& message = *(const google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			reflection->ClearField((google::protobuf::Message*)message_obj, field);
			return true;
		}
	}
	return false;
}

bool ProtoBufOption::RemoveLast(const void* message_obj, const std::string& field_name)
{
	const google::protobuf::Message& message = *(const google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			reflection->RemoveLast((google::protobuf::Message*)message_obj, field);
			return true;
		}
	}
	return false;
}

bool ProtoBufOption::Swap(void* message1, void* message2)
{
	google::protobuf::Message* msg1 = (google::protobuf::Message*)message1;
	google::protobuf::Message* msg2 = (google::protobuf::Message*)message2;
	const google::protobuf::Reflection *reflection = msg1->GetReflection();
	if (reflection)
	{
		reflection->Swap(msg1, msg2);
		return true;
	}

	return false;
}

bool ProtoBufOption::SwapElements(const void* message_obj, const std::string& field_name, int index1, int index2)
{
	const google::protobuf::Message& message = *(const google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			reflection->SwapElements((google::protobuf::Message*)message_obj, field, index1, index2);
			return true;
		}
	}
	return false;
}


bool ProtoBufOption::GetBool(const void* message_obj, const std::string& field_name, bool* ret_val)
{
	const google::protobuf::Message& message = *(const google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			*ret_val = reflection->GetBool(message, field);
			return true;
		}
	}
	return false;
}

bool ProtoBufOption::GetEnumValue(const void* message_obj, const std::string& field_name, int* ret_val)
{
	const google::protobuf::Message& message = *(const google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	const google::protobuf::EnumValueDescriptor *value = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			value = reflection->GetEnum(message, field);
			if (value)
			{
				*ret_val = value->number();
				return true;
			}
		}
	}
	return false;
}

bool ProtoBufOption::GetEnumName(const void* message_obj, const std::string& field_name, std::string& ret_val)
{
	const google::protobuf::Message& message = *(const google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	const google::protobuf::EnumValueDescriptor *value = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			value = reflection->GetEnum(message, field);
			if (value)
			{
				ret_val = value->name();
				return true;
			}
		}
	}
	return false;
}

bool ProtoBufOption::GetInt32(const void* message_obj, const std::string& field_name, google::protobuf::int32* ret_val)
{
	const google::protobuf::Message& message = *(const google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			*ret_val = reflection->GetInt32(message, field);
			return true;
		}
	}
	return false;
}

bool ProtoBufOption::GetInt64(const void* message_obj, const std::string& field_name, google::protobuf::int64* ret_val)
{
	const google::protobuf::Message& message = *(const google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			*ret_val = reflection->GetInt64(message, field);
			return true;
		}
	}
	return false;
}

bool ProtoBufOption::GetFloat(const void* message_obj, const std::string& field_name, float* ret_val)
{
	const google::protobuf::Message& message = *(const google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			*ret_val = reflection->GetFloat(message, field);
			return true;
		}
	}
	return false;
}

bool ProtoBufOption::GetString(const void* message_obj, const std::string& field_name, std::string& ret_val)
{
	const google::protobuf::Message& message = *(const google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			ret_val = reflection->GetString(message, field);
			return true;
		}
	}
	return false;
}
bool ProtoBufOption::DebugMessageStr(const void* message_obj,std::string& ret_val)
{
	if(message_obj == NULL) return false;
	const google::protobuf::Message& message = *(const google::protobuf::Message*)message_obj;
	ret_val = message.Utf8DebugString();
	return true;
}
bool ProtoBufOption::GetMessage(const void* message_obj, const std::string& field_name, void** ret_val)
{
	const google::protobuf::Message& message = *(const google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			*((google::protobuf::Message**)ret_val) = (google::protobuf::Message*)(&(reflection->GetMessage(message, field)));
			return true;
		}
	}
	return false;
}

bool ProtoBufOption::MutableMessage(const void* message_obj, const std::string& field_name, void** ret_val)
{
	google::protobuf::Message* message = (google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message->GetReflection();
	const google::protobuf::Descriptor* descriptor = message->GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			*((google::protobuf::Message**)ret_val) = reflection->MutableMessage(message, field);
			return true;
		}
	}
	return false;
}

bool ProtoBufOption::SetBool(const void* message_obj, const std::string& field_name, bool value)
{
	google::protobuf::Message& message = *(google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			reflection->SetBool(&message, field, value);
			return true;
		}
	}
	return false;
}

bool ProtoBufOption::SetEnumByValue(const void* message_obj, const std::string& field_name, const std::string& enum_name, google::protobuf::int32 enum_number)
{
	google::protobuf::Message& message = *(google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::EnumDescriptor *enumdsp = NULL;
	const google::protobuf::FieldDescriptor *field = NULL;
	const google::protobuf::EnumValueDescriptor *value = NULL;
	if (reflection && descriptor)
	{
		enumdsp = google::protobuf::DescriptorPool::generated_pool()->FindEnumTypeByName(enum_name);
		if (enumdsp)
		{
			value = enumdsp->FindValueByNumber(enum_number);
			field = descriptor->FindFieldByName(field_name);
			if (field && value)
			{
				reflection->SetEnum(&message, field, value);
			}
			return true;
		}
	}
	return false;
}

bool ProtoBufOption::SetEnumByName(const void* message_obj, const std::string& field_name, const std::string& enum_name, const std::string& enum_number_name)
{
	google::protobuf::Message& message = *(google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::EnumDescriptor *enumdsp = NULL;
	const google::protobuf::FieldDescriptor *field = NULL;
	const google::protobuf::EnumValueDescriptor *value = NULL;
	if (reflection && descriptor)
	{
		enumdsp = google::protobuf::DescriptorPool::generated_pool()->FindEnumTypeByName(enum_name);
		if (enumdsp)
		{
			value = enumdsp->FindValueByName(enum_number_name);
			field = descriptor->FindFieldByName(field_name);
			if (field && value)
			{
				reflection->SetEnum(&message, field, value);
			}
			return true;
		}
	}
	return false;
}

bool ProtoBufOption::SetInt32(const void* message_obj, const std::string& field_name, google::protobuf::int32 value)
{
	google::protobuf::Message& message = *(google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			reflection->SetInt32(&message, field, value);
			return true;
		}
	}
	return false;
}

bool ProtoBufOption::SetInt64(const void* message_obj, const std::string& field_name, google::protobuf::int64 value)
{
	google::protobuf::Message& message = *(google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			reflection->SetInt64(&message, field, value);
			return true;
		}
	}
	return false;
}

bool ProtoBufOption::SetFloat(const void* message_obj, const std::string& field_name, float value)
{
	google::protobuf::Message& message = *(google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			reflection->SetFloat(&message, field, value);
			return true;
		}
	}
	return false;
}

bool ProtoBufOption::SetString(const void* message_obj, const std::string& field_name, const std::string& value)
{
	google::protobuf::Message& message = *(google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			reflection->SetString(&message, field, value);
			return true;
		}
	}
	return false;
}

bool ProtoBufOption::SetMessage(const void* message_obj, const std::string& field_name, void* value)
{
	return false;
}


bool ProtoBufOption::GetRepeatedInt32(const void* message_obj, const std::string& field_name, int index, google::protobuf::int32* ret_val)
{
	const google::protobuf::Message& message = *(const google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			*ret_val = reflection->GetRepeatedInt32(message, field, index);
			return true;
		}
	}
	return false;
}

bool ProtoBufOption::GetRepeatedInt64(const void* message_obj, const std::string& field_name, int index, google::protobuf::int64* ret_val)
{
	const google::protobuf::Message& message = *(const google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			*ret_val = reflection->GetRepeatedInt64(message, field, index);
			return true;
		}
	}
	return false;
}

bool ProtoBufOption::GetRepeatedFloat(const void* message_obj, const std::string& field_name, int index, float* ret_val)
{
	const google::protobuf::Message& message = *(const google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			*ret_val = reflection->GetRepeatedFloat(message, field, index);
			return true;
		}
	}
	return false;
}

bool ProtoBufOption::GetRepeatedString(const void* message_obj, const std::string& field_name, int index, std::string& ret_val)
{
	const google::protobuf::Message& message = *(const google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			ret_val = reflection->GetRepeatedString(message, field, index);
			return true;
		}
	}
	return false;
}

bool ProtoBufOption::GetRepeatedMessage(const void* message_obj, const std::string& field_name, int index, void** ret_val)
{
	const google::protobuf::Message& message = *(const google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			*((google::protobuf::Message**)ret_val) = (google::protobuf::Message*)(&(reflection->GetRepeatedMessage(message, field, index)));
			return true;
		}
	}
	return false;
}


bool ProtoBufOption::SetRepeatedInt32(const void* message_obj, const std::string& field_name, int index, google::protobuf::int32 value)
{
	google::protobuf::Message& message = *(google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			reflection->SetRepeatedInt32(&message, field, index, value);
			return true;
		}
	}
	return false;
}

bool ProtoBufOption::SetRepeatedInt64(const void* message_obj, const std::string& field_name, int index, google::protobuf::int64 value)
{
	google::protobuf::Message& message = *(google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			reflection->SetRepeatedInt64(&message, field, index, value);
			return true;
		}
	}
	return false;
}

bool ProtoBufOption::SetRepeatedFloat(const void* message_obj, const std::string& field_name, int index, float value)
{
	google::protobuf::Message& message = *(google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			reflection->SetRepeatedFloat(&message, field, index, value);
			return true;
		}
	}
	return false;
}

bool ProtoBufOption::SetRepeatedString(const void* message_obj, const std::string& field_name, int index, const std::string& value)
{
	google::protobuf::Message& message = *(google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			reflection->SetRepeatedString(&message, field, index, value);
			return true;
		}
	}
	return false;
}


bool ProtoBufOption::AddInt32(const void* message_obj, const std::string& field_name, google::protobuf::int32 value)
{
	google::protobuf::Message& message = *(google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			reflection->AddInt32(&message, field, value);
			return true;
		}
	}
	return false;
}

bool ProtoBufOption::AddInt64(const void* message_obj, const std::string& field_name, google::protobuf::int64 value)
{
	google::protobuf::Message& message = *(google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			reflection->AddInt64(&message, field, value);
			return true;
		}
	}
	return false;
}

bool ProtoBufOption::AddFloat(const void* message_obj, const std::string& field_name, float value)
{
	google::protobuf::Message& message = *(google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			reflection->AddFloat(&message, field, value);
			return true;
		}
	}
	return false;
}

bool ProtoBufOption::AddString(const void* message_obj, const std::string& field_name, const std::string& value)
{
	google::protobuf::Message& message = *(google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			reflection->AddString(&message, field, value);
			return true;
		}
	}
	return false;
}

bool ProtoBufOption::AddMessage(const void* message_obj, const std::string& field_name, void** ret_val)
{
	const google::protobuf::Message& message = *(const google::protobuf::Message*)message_obj;
	const google::protobuf::Reflection *reflection = message.GetReflection();
	const google::protobuf::Descriptor* descriptor = message.GetDescriptor();
	const google::protobuf::FieldDescriptor *field = NULL;
	if (reflection && descriptor)
	{
		field = descriptor->FindFieldByName(field_name);
		if (field)
		{
			*((google::protobuf::Message**)ret_val) = reflection->AddMessage((google::protobuf::Message*)(&message), field);
			return true;
		}
	}
	return false;
}