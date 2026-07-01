#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

#include "json_value.h"

string JsonNull::serialize() const
{
	return "null";
}

string JsonBool::serialize() const
{
	return value ? "true" : "false";
}

string JsonNumber::serialize() const
{
	stringstream ss;
	if (value == static_cast<long long>(value)) {
		ss << static_cast<long long>(value);
	}
	else {
		ss << value;
	}
	return ss.str();
}

string JsonString::serialize() const
{
	string result = "\"";
	for (char c : value) {
		if (c == '"') result += "\\\"";
		else if (c == '\\') result += "\\\\";
		else if (c == '\n') result += "\\n";
		else if (c == '\r') result += "\\r";
		else if (c == '\t') result += "\\t";
		else result += c;
	}
	result += "\"";
	return result;
}

string JsonArray::serialize() const
{
	string result = "[";
	for (int i = 0; i < values.size(); i++)
	{
		if (i > 0)
			result += ",";
		result += values[i]->serialize();
	}
	result += "]";
	return result;
}

string JsonObject::serialize() const
{
	string result = "{";
	bool first = true;
	for (const auto& pair : values) 
	{
		if (!first) result += ",";                    // 键值对之间加逗号
		result += "\"" + pair.first + "\":";          // 键加引号，加冒号
		result += pair.second->serialize();           // 值自己负责自己的格式
		first = false;
	}
	result += "}";
	return result;
}