#include "function3.h"
#include "main.h"

int choice_compression = 0;

int function3(int argc, char *argv[])
{
    while (1)
    {
        printf("当前压缩率:%d", compression_ratio);
        printf("\n1. 开始压缩\n2. 修改压缩率\n0. 返回主菜单\n▶ ");
        // 读取用户输入
        if (scanf("%d", &choice_compression) != 1)
        {
            printf("输入无效，请输入一个整数。\n");
            // 清除输入缓冲区
            clear_input_buffer();
            continue; // 继续循环
        }
        switch (choice_compression)
        {
        case 1:
            compressing(argc, argv);
            return 0;
        case 2:
            change_compression_ratio();
            break;
        case 0:
            return 0;
        default:
            break;
        }
    }
};

int compressing(int argc, char *argv[])
{
    printf("压缩成功！\n");
    return 0;
}
int change_compression_ratio()
{
    printf("输入压缩百分比(1-100):");
    int new_ratio;
    if (scanf("%d", &new_ratio) != 1 || new_ratio < 1 || new_ratio > 100)
    {
        printf("输入无效，请输入一个整数。\n");
        // 清除输入缓冲区
        clear_input_buffer();
        return -1;
    }
    compression_ratio = new_ratio;
    printf("压缩率已更新为: %d%%\n", compression_ratio);
    return 0;
}