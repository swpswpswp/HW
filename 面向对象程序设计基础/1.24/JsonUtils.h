// JsonUtils.h
#pragma once
#include "JsonValue.h"
#include <iostream>
#include <fstream>

// 美化输出访问者
class PrettyPrintVisitor : public JsonConstVisitor {
private:
    std::string& output;
    int indentLevel;
    bool pretty;

    void addIndent() {
        if (!pretty) return;
        for (int i = 0; i < indentLevel; ++i) {
            output += "  ";
        }
    }

public:
    PrettyPrintVisitor(std::string& out, bool prettyMode = true)
        : output(out), indentLevel(0), pretty(prettyMode) {
    }

    void visit(const JsonNull& value) override {
        output += "null";
    }

    void visit(const JsonBoolean& value) override {
        output += value.get() ? "true" : "false";
    }

    void visit(const JsonNumber& value) override {
        output += value.serialize();
    }

    void visit(const JsonString& value) override {
        output += "\"" + value.get() + "\"";
    }

    void visit(const JsonArray& value) override {
        output += "[";
        if (pretty && !value.empty()) {
            output += "\n";
            indentLevel++;
            for (auto it = value.begin(); it != value.end(); ++it) {
                addIndent();
                (*it)->accept(*this);
                if (std::next(it) != value.end()) output += ",";
                output += "\n";
            }
            indentLevel--;
            addIndent();
        }
        else {
            for (size_t i = 0; i < value.size(); ++i) {
                if (i > 0) output += ",";
                value[i]->accept(*this);
            }
        }
        output += "]";
    }

    void visit(const JsonObject& value) override {
        output += "{";
        if (pretty && !value.empty()) {
            output += "\n";
            indentLevel++;
            for (auto it = value.begin(); it != value.end(); ++it) {
                addIndent();
                output += "\"" + it->first + "\":";
                if (pretty) output += " ";
                it->second->accept(*this);
                if (std::next(it) != value.end()) output += ",";
                output += "\n";
            }
            indentLevel--;
            addIndent();
        }
        else {
            for (auto it = value.begin(); it != value.end(); ++it) {
                if (it != value.begin()) output += ",";
                output += "\"" + it->first + "\":";
                it->second->accept(*this);
            }
        }
        output += "}";
    }
};

// JSON 序列化器
class JsonSerializer {
public:
    static std::string serialize(const JsonValue& value, bool pretty = false) {
        std::string result;
        PrettyPrintVisitor visitor(result, pretty);
        value.accept(visitor);
        return result;
    }
};

// JSON 反序列化器
class JsonDeserializer {
public:
    static JsonPtr deserialize(const std::string& json) {
        JsonParser parser;
        return parser.parse(json);
    }
};

// 便捷的工厂函数
namespace Json {
    inline JsonPtr null() { return std::make_shared<JsonNull>(); }
    inline JsonPtr boolean(bool value) { return std::make_shared<JsonBoolean>(value); }
    inline JsonPtr number(double value) { return std::make_shared<JsonNumber>(value); }
    inline JsonPtr string(const std::string& value) { return std::make_shared<JsonString>(value); }
    inline JsonPtr array() { return std::make_shared<JsonArray>(); }
    inline JsonPtr object() { return std::make_shared<JsonObject>(); }
}