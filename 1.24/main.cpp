// main.cpp
#include "JsonUtils.h"
#include <iostream>

int main() {
    try {
        // 1. 创建 JSON 对象
        auto obj = Json::object();
        obj->set("name", Json::string("张三"));
        obj->set("age", Json::number(25));
        obj->set("isStudent", Json::boolean(false));

        // 2. 创建数组
        auto arr = Json::array();
        arr->add(Json::string("apple"));
        arr->add(Json::string("banana"));
        arr->add(Json::string("orange"));
        obj->set("hobbies", arr);

        // 3. 嵌套对象
        auto address = Json::object();
        address->set("city", Json::string("北京"));
        address->set("street", Json::string("长安街"));
        obj->set("address", address);

        // 4. 序列化
        std::cout << "=== 序列化（紧凑格式）===" << std::endl;
        std::string json = JsonSerializer::serialize(*obj);
        std::cout << json << std::endl;

        std::cout << "\n=== 序列化（美化格式）===" << std::endl;
        std::string prettyJson = JsonSerializer::serialize(*obj, true);
        std::cout << prettyJson << std::endl;

        // 5. 反序列化
        std::cout << "\n=== 反序列化 ===" << std::endl;
        auto parsed = JsonDeserializer::deserialize(json);
        std::cout << "解析后的 JSON: " << JsonSerializer::serialize(*parsed, true) << std::endl;

        // 6. 验证相等性
        std::cout << "\n=== 验证 ===" << std::endl;
        std::cout << "原始对象和解析后对象相等: " << (obj->equals(*parsed) ? "是" : "否") << std::endl;

        // 7. 克隆
        auto cloned = obj->clone();
        std::cout << "克隆对象相等: " << (obj->equals(*cloned) ? "是" : "否") << std::endl;

        // 8. 访问元素
        std::cout << "\n=== 访问元素 ===" << std::endl;
        std::cout << "姓名: " << obj->asObject()["name"]->asString().get() << std::endl;
        std::cout << "年龄: " << obj->asObject()["age"]->asNumber().get() << std::endl;

        // 9. 遍历数组
        std::cout << "爱好: ";
        auto& hobbies = obj->asObject()["hobbies"]->asArray();
        for (size_t i = 0; i < hobbies.size(); ++i) {
            if (i > 0) std::cout << ", ";
            std::cout << hobbies[i]->asString().get();
        }
        std::cout << std::endl;

        // 10. 错误处理示例
        std::cout << "\n=== 错误处理 ===" << std::endl;
        try {
            auto invalid = JsonDeserializer::deserialize("{invalid json}");
        }
        catch (const JsonParseException& e) {
            std::cout << "捕获到解析错误: " << e.what() << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "错误: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}