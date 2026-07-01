// json_parse.cpp — JSON 反序列化（解析）实现
//
// 设计思路：递归下降解析器（Recursive Descent Parser）
//   1. 词法层：跳过空白，按当前字符识别 token 起点
//   2. 语法层：parseValue 根据首字符分发到各类型子解析函数
//   3. 与队友 serialize() 输出格式互逆（紧凑 JSON、相同转义规则）
//
// 内存管理：与 json_value 体系一致，用 new 创建节点，通过 set/add 移交所有权

#include "json_value.h"

#include <cctype>
#include <memory>

using namespace std;

// ---------------------------------------------------------------------------
// 内部解析器类（不暴露在头文件中，仅供本文件使用）
// ---------------------------------------------------------------------------
class Parser {
public:
	Parser(const string& input, ParseError* err)
		: input_(input), pos_(0), err_(err) {}

	// 解析入口：读取一个完整的 JSON 值（可以是任意类型）
	JsonValue* parseValue() {
		skipWhitespace();
		if (pos_ >= input_.size()) {
			return fail("unexpected end of input");
		}

		char ch = peek();
		if (ch == '{') return parseObject();
		if (ch == '[') return parseArray();
		if (ch == '"') return parseStringValue();
		if (ch == 'n') return parseNull();
		if (ch == 't' || ch == 'f') return parseBool();
		if (ch == '-' || isdigit(static_cast<unsigned char>(ch))) return parseNumber();

		return fail(string("unexpected character '") + ch + "'");
	}

	// 解析完成后检查是否有多余字符（如 "nullxxx"）
	bool hasTrailingInput() {
		skipWhitespace();
		return pos_ < input_.size();
	}

	size_t position() const { return pos_; }

private:
	const string& input_;   // 待解析的 JSON 文本（不拷贝，只读引用）
	size_t pos_;            // 当前读指针（下标）
	ParseError* err_;       // 可选的错误出参，失败时写入

	// ---------- 基础读写工具 ----------

	// 查看当前字符，不移动读指针；若已到末尾则返回 '\0'
	char peek() const {
		if (pos_ >= input_.size()) return '\0';
		return input_[pos_];
	}

	// 消费当前字符并前进读指针
	bool consume(char expected) {
		if (pos_ >= input_.size() || input_[pos_] != expected) {
			return false;
		}
		++pos_;
		return true;
	}

	// 跳过 JSON 空白字符（比序列化更宽松，允许输入中含空格/换行）
	void skipWhitespace() {
		while (pos_ < input_.size()) {
			char ch = input_[pos_];
			if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
				++pos_;
			}
			else {
				break;
			}
		}
	}

	// 记录错误并返回 nullptr；所有子解析函数在失败时统一调用此方法
	JsonValue* fail(const string& message) {
		if (err_ != nullptr) {
			err_->position = pos_;
			err_->message = message;
		}
		return nullptr;
	}

	// 仅记录错误、不返回值（用于返回 string 的解析函数）
	void setError(const string& message) {
		if (err_ != nullptr) {
			err_->position = pos_;
			err_->message = message;
		}
	}

	// 尝试匹配一段固定字面量（如 "null"、"true"）；成功则前进 pos_ 并返回 true
	bool matchLiteral(const string& literal) {
		if (pos_ + literal.size() > input_.size()) {
			return false;
		}
		if (input_.compare(pos_, literal.size(), literal) != 0) {
			return false;
		}
		pos_ += literal.size();
		return true;
	}

	// ---------- 字符串解析（核心逻辑） ----------

	// 解析一个 JSON 字符串的字面量内容（含引号与反转义）。
	// 成功：out 为解码结果（可为空串 ""），返回 true。
	// 失败：通过 err_ 写入错误，返回 false。
	// 对象键与字符串值共用此函数，避免依赖 JsonString 的私有成员。
	bool parseStringContent(string& out) {
		out.clear();

		if (!consume('"')) {
			setError("expected '\"' to start string");
			return false;
		}

		while (pos_ < input_.size()) {
			char ch = input_[pos_];

			if (ch == '"') {
				++pos_;
				return true;
			}

			if (ch == '\\') {
				++pos_;
				if (pos_ >= input_.size()) {
					setError("unterminated escape sequence");
					return false;
				}
				char esc = input_[pos_++];
				switch (esc) {
				case '"':  out += '"';  break;
				case '\\': out += '\\';  break;
				case 'n':  out += '\n'; break;
				case 'r':  out += '\r'; break;
				case 't':  out += '\t'; break;
				default:
					setError(string("invalid escape sequence '\\") + esc + "'");
					return false;
				}
				continue;
			}

			out += ch;
			++pos_;
		}

		setError("unterminated string");
		return false;
	}

	// 解析 JSON 字符串值 → JsonString 节点
	JsonValue* parseStringValue() {
		string content;
		if (!parseStringContent(content)) {
			return nullptr;
		}
		return new JsonString(content);
	}

	// ---------- 各类型解析 ----------

	// null 字面量
	JsonValue* parseNull() {
		if (!matchLiteral("null")) {
			return fail("expected 'null'");
		}
		return new JsonNull();
	}

	// true / false 布尔字面量
	JsonValue* parseBool() {
		if (matchLiteral("true")) {
			return new JsonBool(true);
		}
		if (matchLiteral("false")) {
			return new JsonBool(false);
		}
		return fail("expected 'true' or 'false'");
	}

	// 数字：可选负号 + 整数部分 + 可选小数部分
	JsonValue* parseNumber() {
		size_t start = pos_;

		if (peek() == '-') {
			++pos_;
		}

		if (pos_ >= input_.size() || !isdigit(static_cast<unsigned char>(peek()))) {
			pos_ = start;
			return fail("invalid number");
		}

		while (pos_ < input_.size() && isdigit(static_cast<unsigned char>(peek()))) {
			++pos_;
		}

		if (peek() == '.') {
			++pos_;
			if (pos_ >= input_.size() || !isdigit(static_cast<unsigned char>(peek()))) {
				pos_ = start;
				return fail("invalid number: decimal part expected");
			}
			while (pos_ < input_.size() && isdigit(static_cast<unsigned char>(peek()))) {
				++pos_;
			}
		}

		if (pos_ < input_.size() && isalpha(static_cast<unsigned char>(peek()))) {
			pos_ = start;
			return fail("invalid number");
		}

		string numStr = input_.substr(start, pos_ - start);
		try {
			double value = stod(numStr);
			return new JsonNumber(value);
		}
		catch (...) {
			pos_ = start;
			return fail("invalid number format");
		}
	}

	// 数组：[ value (, value)* ]，不允许尾逗号
	JsonValue* parseArray() {
		if (!consume('[')) {
			return fail("expected '['");
		}

		JsonArray* arr = new JsonArray();
		skipWhitespace();

		if (consume(']')) {
			return arr;
		}

		while (true) {
			JsonValue* elem = parseValue();
			if (elem == nullptr) {
				delete arr;
				return nullptr;
			}
			arr->add(elem);

			skipWhitespace();

			if (consume(']')) {
				return arr;
			}

			if (!consume(',')) {
				delete arr;
				return fail("expected ',' or ']' in array");
			}

			skipWhitespace();

			if (peek() == ']') {
				delete arr;
				return fail("trailing comma in array");
			}
		}
	}

	// 对象：{ "key" : value (, "key" : value)* }，不允许尾逗号
	JsonValue* parseObject() {
		if (!consume('{')) {
			return fail("expected '{'");
		}

		JsonObject* obj = new JsonObject();
		skipWhitespace();

		if (consume('}')) {
			return obj;
		}

		while (true) {
			// 键：必须是带引号的字符串
			string key;
			if (!parseStringContent(key)) {
				delete obj;
				return nullptr;
			}

			skipWhitespace();

			if (!consume(':')) {
				delete obj;
				return fail("expected ':' after object key");
			}

			JsonValue* val = parseValue();
			if (val == nullptr) {
				delete obj;
				return nullptr;
			}

			obj->set(key, val);

			skipWhitespace();

			if (consume('}')) {
				return obj;
			}

			if (!consume(',')) {
				delete obj;
				return fail("expected ',' or '}' in object");
			}

			skipWhitespace();

			if (peek() == '}') {
				delete obj;
				return fail("trailing comma in object");
			}
		}
	}
};

// ---------------------------------------------------------------------------
// 对外接口：parse()
// ---------------------------------------------------------------------------

unique_ptr<JsonValue> parse(const string& json, ParseError* err) {
	// 空输入直接失败
	if (json.empty()) {
		if (err != nullptr) {
			err->position = 0;
			err->message = "empty input";
		}
		return nullptr;
	}

	Parser parser(json, err);
	JsonValue* root = parser.parseValue();

	if (root == nullptr) {
		return nullptr;
	}

	// 根值解析成功后，检查是否还有多余字符
	if (parser.hasTrailingInput()) {
		if (err != nullptr) {
			err->position = parser.position();
			err->message = "trailing characters after JSON value";
		}
		delete root;
		return nullptr;
	}

	return unique_ptr<JsonValue>(root);
}
