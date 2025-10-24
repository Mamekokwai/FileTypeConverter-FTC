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
// 全局变量定义
char **g_global_paths = NULL;
int g_global_path_count = 0;

int main(int argc, char *argv[])
{

    setup_console_encoding();
    // 初始化全局变量（如果有命令行参数）
    if (argc > 1)
    {
        // 可以将命令行参数也合并到全局变量中
        char **cmd_paths = &argv[1];
        int cmd_count = argc - 1;
        paths_merge_to_global(cmd_paths, cmd_count);
    }

    char input[10];
    int choice;

    while (1)
    {
        printf("\n1. 格 式 转 换 (当前有 %d 个文件)\n", g_global_path_count);
        printf("2. 添 加 文 件\n");
        printf("3. 显示路径列表\n");
        printf("0. 退 出\n");
        printf("▶ ");

        if (fgets(input, sizeof(input), stdin) != NULL)
        {

            // 先移除换行符
            input[strcspn(input, "\n")] = 0;

            // 清除缓存区
            // clear_input_buffer();

            if (!is_pure_digits(input))
                goto end;

            choice = atoi(input);

            switch (choice)
            {
            case 1:
                // 使用全局变量调用 function1
                function1(g_global_path_count, g_global_paths);
                // 需要稍微修改 function1 来使用全局变量
                break;
            case 2:
                if (function2()) // 现在不需要参数
                {
                    printf("❌ FUNCTION2 ERROR\n");
                }
                break;
            case 3:
                // 显示当前全局路径
                printf("\n▲ 当前路径列表 (%d):\n", g_global_path_count);
                for (int i = 0; i < g_global_path_count; i++)
                {
                    printf("  %d: %s\n", i, g_global_paths[i]);
                    Sleep(60);
                }
                break;
            case 0:
                printf("SEEYOU NEXT TIME\n");
                // 释放全局路径内存
                if (g_global_paths)
                {
                    free_paths(g_global_paths, g_global_path_count);
                }
                return 0;
            default:
            end:
                printf("❌ 无效选择! 请输入存在的数字选项\n");
            }
        }
    }
}