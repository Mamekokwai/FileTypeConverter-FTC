#include "function2.h"

void function2()
{
    int result = split_path_from_user();
    if (result != 0)
    {
        // 处理错误情况
        printf("❌ FUNCTION1 ERROR\n");
    }
    printf("✅ FUNCTION2 DONE\n");
}

// 使用示例
int split_path_from_user()
{
    char input[2048];
    char **paths = NULL;
    int count = 0;

    printf("\n▲▼▲FUNCTION2 START▲▼▲");
    printf("\n▲▼▲请拖入文件,支持多个▲▼▲\n▶ ");

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

        count = split_paths(input, &paths);

        if (count == -1)
        {
            printf("\n❌ 请拖入文件,输入0返回\n▶ ");
            continue;
        }

        break;
    }

    printf("\n▲Found %d paths:\n", count);
    for (int i = 0; i < count; i++)
    {
        printf("%s\n", paths[i]);
    }

    free_paths(paths, count);
    printf("按回车键继续...");
    getchar();
    return 0;
}