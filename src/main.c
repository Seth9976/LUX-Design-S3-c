#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "agent.h"
#include "lux/kit.h"

#define MAX_INPUT_SIZE 1024*1024

int main() {
    char input[MAX_INPUT_SIZE];
    Agent* agent = NULL;
    
    while (fgets(input, MAX_INPUT_SIZE, stdin)) {
        // 解析输入JSON
        Observation* obs = parse_observation(input);
        
        // 首次运行时创建代理
        if (!agent) {
            EnvConfig* env_cfg = get_env_config(input);
            agent = create_agent("player_0", env_cfg);
        }
        
        // 执行代理动作
        Actions* actions = act(agent, obs->step, obs, 60);
        
        // 序列化并输出动作
        char* output = serialize_actions(actions);
        printf("%s\n", output);
        fflush(stdout);
        
        // 清理本轮资源
        free(output);
        free_observation(obs);
    }
    
    // 清理代理资源
    if (agent) {
        destroy_agent(agent);
    }
    
    return 0;
}
