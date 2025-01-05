#ifndef LUX_KIT_H
#define LUX_KIT_H

#include <stdbool.h>

// 环境配置结构体
typedef struct {
    int max_units;
    int match_count_per_episode;
    int max_steps_in_match;
    int map_height;
    int map_width;
    int num_teams;
    int unit_move_cost;
    int unit_sap_cost;
    int unit_sap_range;
    int unit_sensor_range;
} EnvConfig;

// 观察结构体
typedef struct {
    int** units_position[2];  // [team][unit_id][2]
    int** units_energy[2];    // [team][unit_id]
    bool** units_mask[2];     // [team][unit_id]
    int** relic_nodes;        // [node_id][2]
    bool* relic_nodes_mask;   // [node_id]
    int* team_points;         // [team_id]
} Observation;

// 动作结构体
typedef struct {
    int** actions;  // [unit_id][3] - [direction, sap_x, sap_y]
} Actions;

#endif
