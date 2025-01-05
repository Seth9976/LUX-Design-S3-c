#ifndef AGENT_H
#define AGENT_H

#include "lux/kit.h"

typedef struct {
    char* player;
    char* opp_player;
    int team_id;
    int opp_team_id;
    EnvConfig* env_cfg;
    
    // 存储已发现的遗迹节点
    int** relic_node_positions;
    int relic_node_count;
    bool* discovered_relic_nodes_ids;
    
    // 单位探索位置
    int** unit_explore_locations;
} Agent;

// 创建新的代理实例
Agent* create_agent(const char* player, EnvConfig* env_cfg);

// 代理行动函数
Actions* act(Agent* agent, int step, Observation* obs, int remainingOverageTime);

// 清理代理资源
void destroy_agent(Agent* agent);

#endif
