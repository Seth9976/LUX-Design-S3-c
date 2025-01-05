#include <math.h>
#include <json-c/json.h>
#include "utils.h"

// 计算从源位置到目标位置的方向
int direction_to(const int* src, const int* target) {
    int dx = target[0] - src[0];
    int dy = target[1] - src[1];
    
    // 优先选择距离更大的方向
    if (abs(dx) > abs(dy)) {
        if (dx > 0) return 2; // 右
        if (dx < 0) return 4; // 左
    } else {
        if (dy < 0) return 1; // 上
        if (dy > 0) return 3; // 下
    }
    return 0; // 原地不动
}

// JSON序列化函数
char* serialize_actions(Actions* actions) {
    struct json_object* root = json_object_new_object();
    
    // TODO: 实现动作序列化为JSON
    
    const char* json_str = json_object_to_json_string(root);
    char* result = strdup(json_str);
    
    json_object_put(root);
    return result;
}

// JSON解析函数
Observation* parse_observation(const char* json) {
    struct json_object* root = json_tokener_parse(json);
    
    // TODO: 实现JSON解析为观察对象
    
    json_object_put(root);
    return NULL;
}
