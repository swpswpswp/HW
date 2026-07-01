#include <iostream>
#include <memory>
#include "json_value.h"

using namespace std;

void testSerialization() {
    cout << "========== 序列化测试 ==========" << endl;

    // 1. null
    JsonNull v1;
    cout << "1. null: " << v1.serialize() << " (期望: null)" << endl;

    // 2. bool true
    JsonBool v2(true);
    cout << "2. true: " << v2.serialize() << " (期望: true)" << endl;

    // 3. bool false
    JsonBool v3(false);
    cout << "3. false: " << v3.serialize() << " (期望: false)" << endl;

    // 4. 整数
    JsonNumber v4(42);
    cout << "4. 整数: " << v4.serialize() << " (期望: 42)" << endl;

    // 5. 负数
    JsonNumber v5(-10);
    cout << "5. 负数: " << v5.serialize() << " (期望: -10)" << endl;

    // 6. 小数
    JsonNumber v6(3.14159);
    cout << "6. 小数: " << v6.serialize() << " (期望: 3.14159)" << endl;

    // 7. 空字符串
    JsonString v7("");
    cout << "7. 空字符串: " << v7.serialize() << " (期望: \"\")" << endl;

    // 8. 普通字符串
    JsonString v8("hello");
    cout << "8. 普通字符串: " << v8.serialize() << " (期望: \"hello\")" << endl;

    // 9. 带引号的字符串
    JsonString v9("he said \"hi\"");
    cout << "9. 带引号: " << v9.serialize() << " (期望: \"he said \\\"hi\\\"\")" << endl;

    // 10. 空数组
    JsonArray v10;
    cout << "10. 空数组: " << v10.serialize() << " (期望: [])" << endl;

    // 11. 单元素数组
    JsonArray v11;
    v11.add(new JsonNumber(1));
    cout << "11. 单元素数组: " << v11.serialize() << " (期望: [1])" << endl;

    // 12. 多元素数组
    JsonArray v12;
    v12.add(new JsonNumber(1));
    v12.add(new JsonNumber(2));
    v12.add(new JsonNumber(3));
    cout << "12. 多元素数组: " << v12.serialize() << " (期望: [1,2,3])" << endl;

    // 13. 混合类型数组
    JsonArray v13;
    v13.add(new JsonNumber(1));
    v13.add(new JsonString("hello"));
    v13.add(new JsonBool(true));
    v13.add(new JsonNull());
    cout << "13. 混合数组: " << v13.serialize() << " (期望: [1,\"hello\",true,null])" << endl;

    // 14. 空对象
    JsonObject v14;
    cout << "14. 空对象: " << v14.serialize() << " (期望: {})" << endl;

    // 15. 单键值对
    JsonObject v15;
    v15.set("k", new JsonString("v"));
    cout << "15. 单键值对: " << v15.serialize() << " (期望: {\"k\":\"v\"})" << endl;

    // 16. 多键值对
    JsonObject v16;
    v16.set("a", new JsonNumber(1));
    v16.set("b", new JsonNumber(2));
    cout << "16. 多键值对: " << v16.serialize() << " (期望: {\"a\":1,\"b\":2})" << endl;

    // 17. 数组嵌套数组
    JsonArray v17;
    JsonArray* inner1 = new JsonArray();
    inner1->add(new JsonNumber(1));
    inner1->add(new JsonNumber(2));
    JsonArray* inner2 = new JsonArray();
    inner2->add(new JsonNumber(3));
    inner2->add(new JsonNumber(4));
    v17.add(inner1);
    v17.add(inner2);
    cout << "17. 嵌套数组: " << v17.serialize() << " (期望: [[1,2],[3,4]])" << endl;

    // 18. 数组嵌套对象
    JsonArray v18;
    JsonObject* user1 = new JsonObject();
    user1->set("name", new JsonString("张三"));
    JsonObject* user2 = new JsonObject();
    user2->set("name", new JsonString("李四"));
    v18.add(user1);
    v18.add(user2);
    cout << "18. 数组嵌套对象: " << v18.serialize() << " (期望: [{\"name\":\"张三\"},{\"name\":\"李四\"}])" << endl;

    // 19. 对象嵌套对象
    JsonObject v19;
    JsonObject* addr = new JsonObject();
    addr->set("city", new JsonString("北京"));
    addr->set("code", new JsonNumber(100000));
    v19.set("address", addr);
    cout << "19. 对象嵌套对象: " << v19.serialize() << " (期望: {\"address\":{\"city\":\"北京\",\"code\":100000}})" << endl;

    // 20. 对象嵌套数组
    JsonObject v20;
    JsonArray* scores = new JsonArray();
    scores->add(new JsonNumber(90));
    scores->add(new JsonNumber(95));
    scores->add(new JsonNumber(88));
    v20.set("scores", scores);
    v20.set("name", new JsonString("张三"));
    cout << "20. 对象嵌套数组: " << v20.serialize() << " (期望: {\"name\":\"张三\",\"scores\":[90,95,88]})" << endl;
}

// ========== 反序列化测试（解析 + round-trip + 负例）==========

// 辅助：断言解析成功且再次序列化后与期望 JSON 一致
static bool assertParseRoundTrip(const string& json, const string& label) {
    ParseError err;
    unique_ptr<JsonValue> parsed = parse(json, &err);
    if (!parsed) {
        cout << "[FAIL] " << label << " - 解析失败: pos=" << err.position
             << " msg: " << err.message << endl;
        return false;
    }
    string again = parsed->serialize();
    if (again != json) {
        cout << "[FAIL] " << label << endl;
        cout << "  输入:   " << json << endl;
        cout << "  再序列化: " << again << endl;
        return false;
    }
    cout << "[PASS] " << label << endl;
    return true;
}

// 辅助：断言解析应失败，并打印错误信息
static bool assertParseFails(const string& json, const string& label) {
    ParseError err;
    unique_ptr<JsonValue> parsed = parse(json, &err);
    if (parsed) {
        cout << "[FAIL] " << label << " - 期望解析失败，但成功了" << endl;
        return false;
    }
    cout << "[PASS] " << label << " - 正确拒绝, pos=" << err.position
         << " msg=" << err.message << endl;
    return true;
}

void testParsing() {
    cout << "\n========== 反序列化正向测试(对应序列化 20 用例)==========" << endl;

    int pass = 0;
    int total = 0;

    auto check = [&](const string& json, const string& label) {
        ++total;
        if (assertParseRoundTrip(json, label)) ++pass;
    };

    check("null", "1. null");
    check("true", "2. true");
    check("false", "3. false");
    check("42", "4. 整数");
    check("-10", "5. 负数");
    check("3.14159", "6. 小数");
    check("\"\"", "7. 空字符串");
    check("\"hello\"", "8. 普通字符串");
    check("\"he said \\\"hi\\\"\"", "9. 带转义引号");
    check("[]", "10. 空数组");
    check("[1]", "11. 单元素数组");
    check("[1,2,3]", "12. 多元素数组");
    check("[1,\"hello\",true,null]", "13. 混合数组");
    check("{}", "14. 空对象");
    check("{\"k\":\"v\"}", "15. 单键值对");
    check("{\"a\":1,\"b\":2}", "16. 多键值对");
    check("[[1,2],[3,4]]", "17. 嵌套数组");
    check("[{\"name\":\"张三\"},{\"name\":\"李四\"}]", "18. 数组嵌套对象");
    check("{\"address\":{\"city\":\"北京\",\"code\":100000}}", "19. 对象嵌套对象");
    check("{\"name\":\"张三\",\"scores\":[90,95,88]}", "20. 对象嵌套数组");

    cout << "正向测试: " << pass << "/" << total << " 通过" << endl;
}

void testRoundTripFromMemory() {
    cout << "\n========== Round-trip 测试(内存树 -> JSON -> 解析 -> JSON)==========" << endl;

    // 构造一个嵌套结构，序列化后解析，再序列化应一致
    JsonObject root;
    JsonArray* scores = new JsonArray();
    scores->add(new JsonNumber(90));
    scores->add(new JsonNumber(85));
    root.set("name", new JsonString("测试"));
    root.set("scores", scores);
    root.set("active", new JsonBool(true));

    string original = root.serialize();
    cout << "原始 JSON: " << original << endl;

    ParseError err;
    unique_ptr<JsonValue> parsed = parse(original, &err);
    if (!parsed) {
        cout << "[FAIL] round-trip 解析失败: " << err.message << endl;
        return;
    }

    string roundTripped = parsed->serialize();
    cout << "往返 JSON: " << roundTripped << endl;

    if (original == roundTripped) {
        cout << "[PASS] round-trip 一致" << endl;
    }
    else {
        cout << "[FAIL] round-trip 不一致" << endl;
    }
}

void testNegativeCases() {
    cout << "\n========== 负例测试（非法 JSON 应安全拒绝）==========" << endl;

    int pass = 0;
    int total = 0;

    auto check = [&](const string& json, const string& label) {
        ++total;
        if (assertParseFails(json, label)) ++pass;
    };

    check("", "空输入");
    check("{\"a\":1,}", "对象尾逗号");
    check("[1,]", "数组尾逗号");
    check("{\"a\":1 \"b\":2}", "对象缺逗号");
    check("[1 2]", "数组缺逗号");
    check("\"unclosed", "字符串未闭合");
    check("\"bad\\q\"", "非法转义 \\q");
    check("tru", "截断的 true");
    check("nul", "截断的 null");
    check("nullx", "根值后多余字符");
    check("{key:1}", "对象键未加引号");
    check("{\"a\":}", "缺少值");

    cout << "负例测试: " << pass << "/" << total << " 通过" << endl;
}

int main() {
    testSerialization();

    testParsing();
    testRoundTripFromMemory();
    testNegativeCases();

    return 0;
}