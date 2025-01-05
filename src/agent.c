#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "agent.h"

// 创建新的代理实例
Agent* create_agent(const char* player, EnvConfig* env_cfg) {
    Agent* agent = (Agent*)malloc(sizeof(Agent));
    
    // 设置玩家信息
    agent->player = strdup(player);
    agent->team_id = strcmp(player, "player_0") == 0 ? 0 : 1;
    agent->opp_player = strdup(agent->team_id == 0 ? "player_1" : "player_0");
    agent->opp_team_id = 1 - agent->team_id;
    
    // 复制环境配置
    agent->env_cfg = env_cfg;
    
    // 初始化遗迹节点存储
    agent->relic_node_count = 0;
    agent->relic_node_positions = NULL;
    agent->discovered_relic_nodes_ids = (bool*)calloc(100, sizeof(bool)); // 假设最多100个遗迹
    
    // 初始化单位探索位置
    agent->unit_explore_locations = (int**)malloc(env_cfg->max_units * sizeof(int*));
    for (int i = 0; i < env_cfg->max_units; i++) {
        agent->unit_explore_locations[i] = (int*)malloc(2 * sizeof(int));
        agent->unit_explore_locations[i][0] = -1;
        agent->unit_explore_locations[i][1] = -1;
    }
    
    return agent;
}

// 获取安全的移动方向
static int get_safe_move(Agent* agent, const int* unit_pos, const int* target_pos) {
    int dir = direction_to(unit_pos, target_pos);
    int next_pos[2] = {unit_pos[0], unit_pos[1]};
    
    // 计算下一个位置
    switch(dir) {
        case 1: next_pos[1]--; break; // 上
        case 2: next_pos[0]++; break; // 右
        case 3: next_pos[1]++; break; // 下
        case 4: next_pos[0]--; break; // 左
    }
    
    // 检查边界
    if (next_pos[0] < 0 || next_pos[0] >= agent->env_cfg->map_width ||
        next_pos[1] < 0 || next_pos[1] >= agent->env_cfg->map_height) {
        return 0;
    }
    
    return dir;
}

// 代理行动函数
Actions* act(Agent* agent, int step, Observation* obs, int remainingOverageTime) {
    Actions* actions = (Actions*)malloc(sizeof(Actions));
    actions->actions = (int**)malloc(agent->env_cfg->max_units * sizeof(int*));
    
    // 处理每个单位
    for (int unit_id = 0; unit_id < agent->env_cfg->max_units; unit_id++) {
        actions->actions[unit_id] = (int*)malloc(3 * sizeof(int));
        
        // 检查单位是否存在
        if (!obs->units_mask[agent->team_id][unit_id]) {
            actions->actions[unit_id][0] = 0;
            actions->actions[unit_id][1] = 0;
            actions->actions[unit_id][2] = 0;
            continue;
        }
        
        // 获取单位位置和能量
        int* unit_pos = obs->units_position[agent->team_id][unit_id];
        int unit_energy = obs->units_energy[agent->team_id][unit_id];
        
        // 如果能量不足,优先充能
        if (unit_energy < agent->env_cfg->unit_move_cost * 2) {
            actions->actions[unit_id][0] = 0;
            actions->actions[unit_id][1] = 0;
            actions->actions[unit_id][2] = 0;
            continue;
        }
        
        // 如果没有探索目标或需要更新目标
        if (agent->unit_explore_locations[unit_id][0] == -1 || step % 20 == 0) {
            agent->unit_explore_locations[unit_id][0] = rand() % agent->env_cfg->map_width;
            agent->unit_explore_locations[unit_id][1] = rand() % agent->env_cfg->map_height;
        }
        
        // 计算移动方向
        int dir = get_safe_move(agent, unit_pos, agent->unit_explore_locations[unit_id]);
        
        actions->actions[unit_id][0] = dir;
        actions->actions[unit_id][1] = 0;
        actions->actions[unit_id][2] = 0;
    }
    
    return actions;
}

// 清理代理资源
void destroy_agent(Agent* agent) {
    if (agent) {
        free(agent->player);
        free(agent->opp_player);
        free(agent->discovered_relic_nodes_ids);
        
        if (agent->relic_node_positions) {
            for (int i = 0; i < agent->relic_node_count; i++) {
                free(agent->relic_node_positions[i]);
            }
            free(agent->relic_node_positions);
        }
        
        for (int i = 0; i < agent->env_cfg->max_units; i++) {
            free(agent->unit_explore_locations[i]);
        }
        free(agent->unit_explore_locations);
        
        free(agent);
    }
}
