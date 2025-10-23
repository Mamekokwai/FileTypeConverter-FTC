#include "main.h"

/**
 * @file main.cpp
 * @brief  主程序入口
 * @author Nywerya (nywerya@gmail.com)
 * @version 1.0
 * @date 2025-10-22
 * @license MIT license
 *
 * @copyright Copyright (c) 2025  nywerya
 *
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author  <th>Description
 * <tr><td>2025-10-22 <td>1.0     <td>Nywerya     <td>内容
 * </table>
 */
int main(int argc, char **argv)
{

    char input[10];
    int choice;

    // 设置控制台为 UTF-8 编码
    system("chcp 65001 > nul");
    SetConsoleOutputCP(65001);
    // 在程序中添加检查
    char cwd[1024];
    _getcwd(cwd, sizeof(cwd));
    printf("当前工作目录: %s\n", cwd);
    // 检查 PATH 环境变量
    // printf("PATH: %s\n", getenv("PATH"));
    loading_animation1();

    while (1)
    {
        printf("\n1. 文件格式转换\n");
        printf("2. 输入文件路径\n");
        printf("3. 待完善\n");
        printf("0. 退出\n");
        printf("▶ ");

        // 使用 fgets 读取整行输入
        if (fgets(input, sizeof(input), stdin) != NULL)
        {
            // 尝试转换为数字
            if (sscanf(input, "%d", &choice) == 1)
            {

                switch (choice)
                {
                case 1:
                    function1(argc, argv);
                    break;
                case 2:
                    function2();
                    break;
                case 3:
                    function3();
                    break;
                case 0:
                    printf("再见!\n");
                    return 0;
                default:
                    printf("❌ 无效选择! 请输入 0-3 之间的数字\n");
                }
            }
            else
            {
                printf("❌ 输入错误，请输入数字！\n");
                continue;
            }
        }
    }
}

void function3() { printf("待完善\n"); }

int test()
{ // 设置控制台编码为 UTF-8
    return 0;
}