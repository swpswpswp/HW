#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

class JsonValue 
{
public:
	virtual string serialize() const = 0;
	virtual ~JsonValue() {}
};

class JsonObject :public JsonValue
{
private:
	map<string, JsonValue*> values; 
public:
	void set(const string& key, JsonValue* val);
	JsonValue* get(const string& key) const;
	bool hasKey(const string& key) const;
	string serialize() const override;
	~JsonObject();  // 需要释放所有值
};

class JsonArray :public JsonValue
{
private:
	vector<JsonValue*> values;
public:
	void add(JsonValue* val);
	JsonValue* get(int index) const;
	int size() const;
	string serialize() const override;
	~JsonArray();  // 需要释放所有元素
};

class JsonString :public JsonValue
{
private:
	string value;
public:
	JsonString(const string& val) :value(val) {};
	string serialize() const override;
};

class JsonNumber :public JsonValue
{
private:
	double value;
public:
	JsonNumber(double val) :value(val) {};
	string serialize() const override;
};

class JsonBool :public JsonValue
{
private:
	bool value;
public:
	JsonBool(bool val) :value(val) {};
	string serialize() const override;
};

class JsonNull :public JsonValue
{
public:
	string serialize() const override;
};

// ========== 反序列化 API（解析 JSON 字符串 → JsonValue 内存树）==========

#include <memory>

// 解析失败时携带的错误信息：position 为出错字符在输入串中的下标（从 0 开始）
struct ParseError {
	size_t position = 0;
	string message;
};

// 将 JSON 文本解析为 JsonValue 树。
// 成功：返回非空 unique_ptr；失败：返回 nullptr，若 err 非空则写入错误详情。
unique_ptr<JsonValue> parse(const string& json, ParseError* err = nullptr);