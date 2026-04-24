// JsonParser.h
#pragma once
#include "JsonValue.h"
#include <string>
#include <cctype>
#include <memory>
#include <stdexcept>

class JsonParseException : public std::runtime_error {
public:
    explicit JsonParseException(const std::string& msg) : std::runtime_error(msg) {}
};

class JsonParser {
private:
    std::string input;
    size_t pos;

    char peek() const {
        if (pos >= input.length()) return '\0';
        return input[pos];
    }

    char get() {
        if (pos >= input.length()) throw JsonParseException("Unexpected end of input");
        return input[pos++];
    }

    void skipWhitespace() {
        while (pos < input.length() && std::isspace(static_cast<unsigned char>(input[pos]))) {
            ++pos;
        }
    }

    JsonPtr parseNull() {
        if (input.substr(pos, 4) != "null") {
            throw JsonParseException("Expected 'null'");
        }
        pos += 4;
        return std::make_shared<JsonNull>();
    }

    JsonPtr parseBoolean() {
        if (input.substr(pos, 4) == "true") {
            pos += 4;
            return std::make_shared<JsonBoolean>(true);
        }
        else if (input.substr(pos, 5) == "false") {
            pos += 5;
            return std::make_shared<JsonBoolean>(false);
        }
        throw JsonParseException("Expected 'true' or 'false'");
    }

    JsonPtr parseNumber() {
        size_t start = pos;

        // 处理负号
        if (peek() == '-') get();

        // 整数部分
        if (!std::isdigit(peek())) {
            throw JsonParseException("Expected digit");
        }

        // 处理整数部分，不允许前导零
        if (peek() == '0') {
            get();
            if (std::isdigit(peek())) {
                throw JsonParseException("Invalid number: leading zero");
            }
        }
        else {
            while (std::isdigit(peek())) get();
        }

        // 小数部分
        if (peek() == '.') {
            get();
            if (!std::isdigit(peek())) {
                throw JsonParseException("Expected digit after decimal point");
            }
            while (std::isdigit(peek())) get();
        }

        // 指数部分
        if (peek() == 'e' || peek() == 'E') {
            get();
            if (peek() == '+' || peek() == '-') get();
            if (!std::isdigit(peek())) {
                throw JsonParseException("Expected digit in exponent");
            }
            while (std::isdigit(peek())) get();
        }

        std::string numStr = input.substr(start, pos - start);
        double value = std::stod(numStr);
        return std::make_shared<JsonNumber>(value);
    }

    std::string parseString() {
        if (get() != '"') {
            throw JsonParseException("Expected '\"'");
        }

        std::string result;
        while (true) {
            char c = get();
            if (c == '"') break;

            if (c == '\\') {
                char esc = get();
                switch (esc) {
                case '"': result += '"'; break;
                case '\\': result += '\\'; break;
                case '/': result += '/'; break;
                case 'b': result += '\b'; break;
                case 'f': result += '\f'; break;
                case 'n': result += '\n'; break;
                case 'r': result += '\r'; break;
                case 't': result += '\t'; break;
                default: throw JsonParseException("Invalid escape sequence");
                }
            }
            else {
                result += c;
            }
        }
        return result;
    }

    JsonPtr parseArray() {
        if (get() != '[') {
            throw JsonParseException("Expected '['");
        }

        auto arr = std::make_shared<JsonArray>();
        skipWhitespace();

        if (peek() == ']') {
            get();
            return arr;
        }

        while (true) {
            arr->add(parseValue());
            skipWhitespace();

            if (peek() == ']') {
                get();
                break;
            }

            if (peek() != ',') {
                throw JsonParseException("Expected ',' or ']'");
            }
            get();
            skipWhitespace();
        }

        return arr;
    }

    JsonPtr parseObject() {
        if (get() != '{') {
            throw JsonParseException("Expected '{'");
        }

        auto obj = std::make_shared<JsonObject>();
        skipWhitespace();

        if (peek() == '}') {
            get();
            return obj;
        }

        while (true) {
            skipWhitespace();
            std::string key = parseString();
            skipWhitespace();

            if (get() != ':') {
                throw JsonParseException("Expected ':'");
            }
            skipWhitespace();

            JsonPtr value = parseValue();
            obj->set(key, value);

            skipWhitespace();
            if (peek() == '}') {
                get();
                break;
            }

            if (peek() != ',') {
                throw JsonParseException("Expected ',' or '}'");
            }
            get();
        }

        return obj;
    }

public:
    JsonParser() : pos(0) {}

    JsonPtr parse(const std::string& json) {
        input = json;
        pos = 0;
        skipWhitespace();
        JsonPtr result = parseValue();
        skipWhitespace();

        if (pos < input.length()) {
            throw JsonParseException("Unexpected trailing characters");
        }

        return result;
    }

    JsonPtr parseValue() {
        skipWhitespace();
        char c = peek();

        if (c == 'n') return parseNull();
        if (c == 't' || c == 'f') return parseBoolean();
        if (c == '"') return std::make_shared<JsonString>(parseString());
        if (c == '[') return parseArray();
        if (c == '{') return parseObject();
        if (c == '-' || std::isdigit(c)) return parseNumber();

        throw JsonParseException("Unexpected character: " + std::string(1, c));
    }
};