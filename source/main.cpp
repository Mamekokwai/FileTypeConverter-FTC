/**
 * @file main.cpp
 * @brief 主程序
 * @author nywerya (nywerya@gmail.com)
 * @version 1.0
 * @date 2026-03-26
 */
#include "main.h"

// 全局变量定义
char **g_global_paths = NULL;
int g_global_path_count = 0;
int compression_ratio = 80;

menu_choice menu_choices[] = {
    {FILE_TYPE_CHANGING, "格式转换"},
    {DELETE_FILE_PATH, "删除所有文件路径"},
    {ADDING_FILE_PATH, "添加文件"},
    {COMPRESSION_TO_JPG, "图片压缩为jpg"},
    {TEST, "测试"},
    {SHOW_PATH_LIST, "显示路径列表"},
    {EXIT, "退出"},
    {COPY_AND_RENAME_BY_PARENT_PATH, "根据父路径复制并重命名"},
};

int main(int argc, char *argv[])
{

    setup_console_encoding();
    // 初始化全局变量（如果有命令行参数）

    // 检查 FFmpeg
    if (!check_ffmpeg_available())
    {
        wait_for_enter();
        return -1;
    }

    if (argc > 1)
    {
        // 可以将命令行参数也合并到全局变量中
        char **cmd_paths = &argv[1];
        int cmd_count = argc - 1;
        paths_merge_to_global(cmd_paths, cmd_count);
    }

    char input[10];
    int choice;
    char path1[MAX_PATH] = {0};
    // const char *path = "E:\\Personalfile\\Art\\paint\\2025\\10-21shell_ico_make\\FileTypeConverter-FTC\\resources\\和服花妈.jpg";
    char *test_path;

    while (1)
    {
        // printf("\n1. 格 式 转 换 (当前有 %d 个文件)\n", g_global_path_count);
        // printf("2. 添 加 文 件\n");
        // printf("3. 显示路径列表\n");
        // printf("4. 测 试\n");
        // printf("5. 图片压缩为jpg\n");
        // printf("0. 退 出\n");
        // 对结构体数组按 choice 字段进行排序
        int menu_count = sizeof(menu_choices) / sizeof(menu_choice);
        for (int i = 0; i < menu_count - 1; i++)
        {
            for (int j = 0; j < menu_count - i - 1; j++)
            {
                if (menu_choices[j].choice > menu_choices[j + 1].choice)
                {
                    menu_choice temp = menu_choices[j];
                    menu_choices[j] = menu_choices[j + 1];
                    menu_choices[j + 1] = temp;
                }
            }
        }
        printf("▶ ");

        // 按大小排序输出菜单
        printf("\n");
        for (int i = 0; i < menu_count; i++)
        {
            printf("%d. %s\n", menu_choices[i].choice, menu_choices[i].description);
        }

        if (fgets(input, sizeof(input), stdin) != NULL)
        {

            // 先移除换行符
            input[strcspn(input, "\n")] = 0;

            // 清除缓存区
            // clear_input_buffer();

            if (!is_pure_digits(input))
                goto end;

            choice = atoi(input);
            /***************************************************************************************/
            switch (choice)
            {
            case COPY_AND_RENAME_BY_PARENT_PATH:
                function6();
                break;
            case FILE_TYPE_CHANGING:
                // 使用全局变量调用 function1
                function1(g_global_path_count, g_global_paths);
                // 需要稍微修改 function1 来使用全局变量
                break;

            case ADDING_FILE_PATH:
                if (function2()) // 现在不需要参数
                {
                    printf("❌ FUNCTION2 ERROR\n");
                }
                break;

            case DELETE_FILE_PATH:
                // 释放全局路径内存
                if (g_global_paths)
                {
                    free_paths(g_global_paths, g_global_path_count);
                    g_global_paths = NULL;
                    g_global_path_count = 0;
                    printf("✅ 已删除所有文件路径\n");
                }
                else
                {
                    printf("⚠️ 没有文件路径可删除\n");
                }
                break;
            case COMPRESSION_TO_JPG:
                function3(g_global_path_count, g_global_paths);
                // 清空输入缓冲区
                clear_input_buffer();
                break;

            case TEST:
                GetModuleFileNameA(NULL, path1, MAX_PATH);
                printf("当前程序路径: %s\n", path1);
                printf(".\\tools\\ffmpeg\\ffmpeg.exe -i \"%s\" \"%s\" -y -hide_banner -loglevel error\n", "A", "B");
                printf("✅ 路径存在: %s\n", get_ffmpeg_path());
                break;

            case SHOW_PATH_LIST:
                // 显示当前全局路径
                printf("\n▲ 当前路径列表 (%d):\n", g_global_path_count);
                for (int i = 0; i < g_global_path_count; i++)
                {
                    printf("  %d: %s\n", i, g_global_paths[i]);
                    Sleep(60);
                }
                break;

            case EXIT:
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
                break;
            }
        }
    }
}
