import json
import sys
import subprocess

def main():
    # 启动C程序
    process = subprocess.Popen(['./luxbot'], 
                             stdin=subprocess.PIPE,
                             stdout=subprocess.PIPE,
                             stderr=subprocess.PIPE)
    
    try:
        while True:
            # 从标准输入读取
            observation = input()
            
            # 发送到C程序
            process.stdin.write(f"{observation}\n".encode())
            process.stdin.flush()
            
            # 读取C程序输出
            response = process.stdout.readline().decode().strip()
            
            # 输出动作
            print(response, flush=True)
            
    except EOFError:
        process.terminate()
        
if __name__ == "__main__":
    main()
