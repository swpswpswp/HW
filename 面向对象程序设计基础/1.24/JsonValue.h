// JsonValue.h
#pragma once
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <variant>
#include <stdexcept>

class JsonValue;
using JsonPtr = std::shared_ptr<JsonValue>;

// 前向声明
class JsonNull;
class JsonBoolean;
class JsonNumber;
class JsonString;
class JsonArray;
class JsonObject;

// 访问者模式接口
class JsonVisitor {
public:
    virtual ~JsonVisitor() = default;
    virtual void visit(JsonNull& value) = 0;
    virtual void visit(JsonBoolean& value) = 0;
    virtual void visit(JsonNumber& value) = 0;
    virtual void visit(JsonString& value) = 0;
    virtual void visit(JsonArray& value) = 0;
    virtual void visit(JsonObject& value) = 0;
};

class JsonConstVisitor {
public:
    virtual ~JsonConstVisitor() = default;
    virtual void visit(const JsonNull& value) = 0;
    virtual void visit(const JsonBoolean& value) = 0;
    virtual void visit(const JsonNumber& value) = 0;
    virtual void visit(const JsonString& value) = 0;
    virtual void visit(const JsonArray& value) = 0;
    virtual void visit(const JsonObject& value) = 0;
};

// 抽象基类
class JsonValue {
public:
    virtual ~JsonValue() = default;

    // 类型判断
    virtual bool isNull() const { return false; }
    virtual bool isBoolean() const { return false; }
    virtual bool isNumber() const { return false; }
    virtual bool isString() const { return false; }
    virtual bool isArray() const { return false; }
    virtual bool isObject() const { return false; }

    // 类型转换（安全）
    virtual JsonNull& asNull() { throw std::bad_cast(); }
    virtual const JsonNull& asNull() const { throw std::bad_cast(); }
    virtual JsonBoolean& asBoolean() { throw std::bad_cast(); }
    virtual const JsonBoolean& asBoolean() const { throw std::bad_cast(); }
    virtual JsonNumber& asNumber() { throw std::bad_cast(); }
    virtual const JsonNumber& asNumber() const { throw std::bad_cast(); }
    virtual JsonString& asString() { throw std::bad_cast(); }
    virtual const JsonString& asString() const { throw std::bad_cast(); }
    virtual JsonArray& asArray() { throw std::bad_cast(); }
    virtual const JsonArray& asArray() const { throw std::bad_cast(); }
    virtual JsonObject& asObject() { throw std::bad_cast(); }
    virtual const JsonObject& asObject() const { throw std::bad_cast(); }

    // 访问者模式
    virtual void accept(JsonVisitor& visitor) = 0;
    virtual void accept(JsonConstVisitor& visitor) const = 0;

    // 序列化
    virtual std::string serialize() const = 0;

    // 克隆
    virtual JsonPtr clone() const = 0;

    // 比较
    virtual bool equals(const JsonValue& other) const = 0;
    bool operator==(const JsonValue& other) const { return equals(other); }
    bool operator!=(const JsonValue& other) const { return !equals(other); }
};

// 具体类：Null
class JsonNull : public JsonValue {
public:
    bool isNull() const override { return true; }
    JsonNull& asNull() override { return *this; }
    const JsonNull& asNull() const override { return *this; }

    void accept(JsonVisitor& visitor) override { visitor.visit(*this); }
    void accept(JsonConstVisitor& visitor) const override { visitor.visit(*this); }

    std::string serialize() const override { return "null"; }

    JsonPtr clone() const override { return std::make_shared<JsonNull>(); }

    bool equals(const JsonValue& other) const override {
        return other.isNull();
    }
};

// 具体类：Boolean
class JsonBoolean : public JsonValue {
private:
    bool value_;

public:
    explicit JsonBoolean(bool value) : value_(value) {}

    bool isBoolean() const override { return true; }
    JsonBoolean& asBoolean() override { return *this; }
    const JsonBoolean& asBoolean() const override { return *this; }

    bool get() const { return value_; }
    void set(bool value) { value_ = value; }

    void accept(JsonVisitor& visitor) override { visitor.visit(*this); }
    void accept(JsonConstVisitor& visitor) const override { visitor.visit(*this); }

    std::string serialize() const override {
        return value_ ? "true" : "false";
    }

    JsonPtr clone() const override { return std::make_shared<JsonBoolean>(value_); }

    bool equals(const JsonValue& other) const override {
        if (!other.isBoolean()) return false;
        return value_ == dynamic_cast<const JsonBoolean&>(other).value_;
    }
};

// 具体类：Number
class JsonNumber : public JsonValue {
private:
    double value_;

public:
    explicit JsonNumber(double value) : value_(value) {}

    bool isNumber() const override { return true; }
    JsonNumber& asNumber() override { return *this; }
    const JsonNumber& asNumber() const override { return *this; }

    double get() const { return value_; }
    void set(double value) { value_ = value; }

    int getInt() const { return static_cast<int>(value_); }
    long getLong() const { return static_cast<long>(value_); }

    void accept(JsonVisitor& visitor) override { visitor.visit(*this); }
    void accept(JsonConstVisitor& visitor) const override { visitor.visit(*this); }

    std::string serialize() const override {
        if (value_ == static_cast<long long>(value_)) {
            return std::to_string(static_cast<long long>(value_));
        }
        std::string str = std::to_string(value_);
        // 移除末尾多余的零
        str.erase(str.find_last_not_of('0') + 1, std::string::npos);
        if (str.back() == '.') str.pop_back();
        return str;
    }

    JsonPtr clone() const override { return std::make_shared<JsonNumber>(value_); }

    bool equals(const JsonValue& other) const override {
        if (!other.isNumber()) return false;
        return value_ == dynamic_cast<const JsonNumber&>(other).value_;
    }
};

// 具体类：String
class JsonString : public JsonValue {
private:
    std::string value_;

    static std::string escape(const std::string& str) {
        std::string result;
        for (char c : str) {
            switch (c) {
            case '"': result += "\\\""; break;
            case '\\': result += "\\\\"; break;
            case '\b': result += "\\b"; break;
            case '\f': result += "\\f"; break;
            case '\n': result += "\\n"; break;
            case '\r': result += "\\r"; break;
            case '\t': result += "\\t"; break;
            default: result += c; break;
            }
        }
        return result;
    }

public:
    explicit JsonString(const std::string& value) : value_(value) {}

    bool isString() const override { return true; }
    JsonString& asString() override { return *this; }
    const JsonString& asString() const override { return *this; }

    const std::string& get() const { return value_; }
    void set(const std::string& value) { value_ = value; }

    void accept(JsonVisitor& visitor) override { visitor.visit(*this); }
    void accept(JsonConstVisitor& visitor) const override { visitor.visit(*this); }

    std::string serialize() const override {
        return "\"" + escape(value_) + "\"";
    }

    JsonPtr clone() const override { return std::make_shared<JsonString>(value_); }

    bool equals(const JsonValue& other) const override {
        if (!other.isString()) return false;
        return value_ == dynamic_cast<const JsonString&>(other).value_;
    }
};

// 具体类：Array
class JsonArray : public JsonValue {
private:
    std::vector<JsonPtr> elements_;

public:
    JsonArray() = default;

    bool isArray() const override { return true; }
    JsonArray& asArray() override { return *this; }
    const JsonArray& asArray() const override { return *this; }

    size_t size() const { return elements_.size(); }
    bool empty() const { return elements_.empty(); }

    JsonPtr& operator[](size_t index) { return elements_[index]; }
    const JsonPtr& operator[](size_t index) const { return elements_[index]; }

    void add(JsonPtr element) { elements_.push_back(element); }
    void insert(size_t index, JsonPtr element) {
        elements_.insert(elements_.begin() + index, element);
    }
    void remove(size_t index) {
        elements_.erase(elements_.begin() + index);
    }
    void clear() { elements_.clear(); }

    auto begin() { return elements_.begin(); }
    auto end() { return elements_.end(); }
    auto begin() const { return elements_.begin(); }
    auto end() const { return elements_.end(); }

    void accept(JsonVisitor& visitor) override { visitor.visit(*this); }
    void accept(JsonConstVisitor& visitor) const override { visitor.visit(*this); }

    std::string serialize() const override {
        std::string result = "[";
        for (size_t i = 0; i < elements_.size(); ++i) {
            if (i > 0) result += ",";
            result += elements_[i]->serialize();
        }
        result += "]";
        return result;
    }

    JsonPtr clone() const override {
        auto arr = std::make_shared<JsonArray>();
        for (const auto& elem : elements_) {
            arr->add(elem->clone());
        }
        return arr;
    }

    bool equals(const JsonValue& other) const override {
        if (!other.isArray()) return false;
        const auto& otherArr = dynamic_cast<const JsonArray&>(other);
        if (elements_.size() != otherArr.elements_.size()) return false;
        for (size_t i = 0; i < elements_.size(); ++i) {
            if (!elements_[i]->equals(*otherArr.elements_[i])) return false;
        }
        return true;
    }
};

// 具体类：Object
class JsonObject : public JsonValue {
private:
    std::unordered_map<std::string, JsonPtr> members_;

public:
    JsonObject() = default;

    bool isObject() const override { return true; }
    JsonObject& asObject() override { return *this; }
    const JsonObject& asObject() const override { return *this; }

    size_t size() const { return members_.size(); }
    bool empty() const { return members_.empty(); }

    bool has(const std::string& key) const {
        return members_.find(key) != members_.end();
    }

    JsonPtr& operator[](const std::string& key) { return members_[key]; }
    const JsonPtr& operator[](const std::string& key) const {
        auto it = members_.find(key);
        if (it == members_.end()) throw std::out_of_range("Key not found: " + key);
        return it->second;
    }

    void set(const std::string& key, JsonPtr value) {
        members_[key] = value;
    }

    void remove(const std::string& key) {
        members_.erase(key);
    }

    void clear() { members_.clear(); }

    auto begin() { return members_.begin(); }
    auto end() { return members_.end(); }
    auto begin() const { return members_.begin(); }
    auto end() const { return members_.end(); }

    void accept(JsonVisitor& visitor) override { visitor.visit(*this); }
    void accept(JsonConstVisitor& visitor) const override { visitor.visit(*this); }

    std::string serialize() const override {
        std::string result = "{";
        bool first = true;
        for (const auto& [key, value] : members_) {
            if (!first) result += ",";
            first = false;
            result += "\"" + key + "\":" + value->serialize();
        }
        result += "}";
        return result;
    }

    JsonPtr clone() const override {
        auto obj = std::make_shared<JsonObject>();
        for (const auto& [key, value] : members_) {
            obj->set(key, value->clone());
        }
        return obj;
    }

    bool equals(const JsonValue& other) const override {
        if (!other.isObject()) return false;
        const auto& otherObj = dynamic_cast<const JsonObject&>(other);
        if (members_.size() != otherObj.members_.size()) return false;
        for (const auto& [key, value] : members_) {
            auto it = otherObj.members_.find(key);
            if (it == otherObj.members_.end()) return false;
            if (!value->equals(*it->second)) return false;
        }
        return true;
    }
};