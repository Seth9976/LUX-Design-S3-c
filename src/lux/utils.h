#ifndef LUX_UTILS_H
#define LUX_UTILS_H

// 方向计算函数(0=中心,1=上,2=右,3=下,4=左)
int direction_to(const int* src, const int* target);

// JSON解析和序列化函数声明
char* serialize_actions(Actions* actions);
Observation* parse_observation(const char* json);

#endif
