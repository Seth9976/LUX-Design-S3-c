#include <stdlib.h>
#include "kit.h"

// 创建新的观察对象
Observation* create_observation(EnvConfig* cfg) {
    Observation* obs = (Observation*)malloc(sizeof(Observation));
    
    // 初始化单位数据
    for (int team = 0; team < 2; team++) {
        obs->units_position[team] = (int**)malloc(cfg->max_units * sizeof(int*));
        obs->units_energy[team] = (int**)malloc(cfg->max_units * sizeof(int*));
        obs->units_mask[team] = (bool**)malloc(cfg->max_units * sizeof(bool*));
        
        for (int i = 0; i < cfg->max_units; i++) {
            obs->units_position[team][i] = (int*)malloc(2 * sizeof(int));
            obs->units_energy[team][i] = (int*)malloc(sizeof(int));
            obs->units_mask[team][i] = (bool*)malloc(sizeof(bool));
        }
    }
    
    // 初始化遗迹节点数据
    obs->relic_nodes = (int**)malloc(100 * sizeof(int*)); // 假设最多100个遗迹
    obs->relic_nodes_mask = (bool*)malloc(100 * sizeof(bool));
    
    // 初始化队伍得分
    obs->team_points = (int*)malloc(2 * sizeof(int));
    
    return obs;
}

// 清理观察对象
void free_observation(Observation* obs) {
    if (obs) {
        for (int team = 0; team < 2; team++) {
            for (int i = 0; i < 100; i++) {
                free(obs->units_position[team][i]);
                free(obs->units_energy[team][i]);
                free(obs->units_mask[team][i]);
            }
            free(obs->units_position[team]);
            free(obs->units_energy[team]);
            free(obs->units_mask[team]);
        }
        
        for (int i = 0; i < 100; i++) {
            if (obs->relic_nodes[i]) {
                free(obs->relic_nodes[i]);
            }
        }
        free(obs->relic_nodes);
        free(obs->relic_nodes_mask);
        free(obs->team_points);
        free(obs);
    }
}
