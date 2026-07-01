#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "json_value.h"

using namespace std;

void JsonObject::set(const string& key, JsonValue* val)
{
	auto it = values.find(key);
	if (it != values.end()) 
	{
		delete it->second;  // 删除旧值
		it->second = val;
	}
	else 
	{
		values.emplace(key, val);
	}
}

JsonValue* JsonObject::get(const string& key) const
{
	auto it = values.find(key);
	if (it != values.end())
		return it->second;
	return nullptr;
}

bool JsonObject::hasKey(const string& key) const
{
	for (const auto& pair : values)
	{
		if (pair.first == key)
			return true;
	}
	return false;
}

void JsonArray::add(JsonValue* val)
{
	values.push_back(val);
}

JsonValue* JsonArray::get(int index) const
{
	if (index >= 0 && index < values.size())
		return values[index];
	return nullptr;
}

int JsonArray::size() const
{
	return values.size();
}

JsonObject::~JsonObject()
{
	for (auto& pair : values)
		delete pair.second;
	values.clear();
}

JsonArray::~JsonArray()
{
	for (auto& val : values)
		delete val;
}