#include "function2.h"
#include "main.h"

int function2()
{
    printf("▲▼▲FUNCTION2 START▲▼▲\n");

    char **new_paths = NULL;
    int new_count = 0;

    // 获取用户输入的路径
    if ((new_count = split_path_from_user(&new_paths)) <= 0)
    {
        printf("❌ FUNCTION split_path_from_user() error!\n");
        return -1;
    }

    // 使用新的合并函数，直接操作全局变量
    if (paths_merge_to_global(new_paths, new_count))
    {
        printf("❌ FUNCTION paths_merge_to_global() error!\n");
        free_paths(new_paths, new_count);
        return -1;
    }

    // 释放临时路径（内容已经复制到全局变量）
    free_paths(new_paths, new_count);

    printf("▲▼▲FUNCTION2 DONE▲▼▲\n");

    // 等待用户输入回车
    wait_for_enter();
    return 0;
}

int split_path_from_user(char ***paths)
{
    char input[2048];

    printf("▲▼▲请拖入文件,支持多个▲▼▲\n▶ ");

    while (1)
    {
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("\n❌ 读取输入失败\n");
            return -1;
        }

        // 移除换行符
        input[strcspn(input, "\n")] = 0;

        if (strcmp(input, "0") == 0)
            return 0;

        // int count = split_paths(input, paths);
        int count = split_paths_smart(input, paths);

        if (count <= 0)
        {
            printf("\n❓ 请拖入文件或输入0返回\n▶ ");
            continue;
        }

        // printf("\n▲Found %d paths:\n", count);
        // for (int i = 0; i < count; i++)
        // {
        //     printf("  %d: %s\n", i, (*paths)[i]);
        // }

        return count;
    }
}
