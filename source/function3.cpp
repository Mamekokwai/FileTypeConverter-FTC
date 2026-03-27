/**
 * @file function3.cpp
 * @brief 功能3：图片压缩
 * @author nywerya (nywerya@gmail.com)
 * @version 1.0
 * @date 2026-03-26
 */
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 假设这是你在其他地方定义的全局变量
extern int compression_ratio; // 压缩率 1-100

int compressing(int argc, char *argv[])
{

    int success_count = 0;
    int fail_count = 0;

    printf("开始压缩 %d 张图片，压缩率: %d%%\n", argc - 1, compression_ratio);
    printf("====================================\n");

    // 从 argv[1] 开始遍历图片
    for (int i = 0; i < argc; i++)
    {
        printf("[%d/%d] 正在压缩: %s\n", i, argc - 1, argv[i]);

        // 构建输出文件名（在原文件名后加 _compressed）
        char output_file[512];
        char *dot = strrchr(argv[i], '.');
        if (dot)
        {
            // 有扩展名，在扩展名前插入 _compressed和压缩率
            int pos = dot - argv[i];
            strncpy(output_file, argv[i], pos);
            output_file[pos] = '\0';
            strcat(output_file, "_compressed");
            strcat(output_file, "_");
            char ratio_str[10];
            sprintf(ratio_str, "%d%", compression_ratio);
            strcat(output_file, ratio_str);
            strcat(output_file, dot);
        }
        else
        {
            // 没有扩展名，直接加后缀
            sprintf(output_file, "%s_compressed_%drate.jpg", argv[i], compression_ratio);
        }

        // 构建 ffmpeg 命令
        char command[2048];
        // // 创建GBK命令
        // char GBK_command[2048];

        // 根据压缩率设置 ffmpeg 的 q:v 参数
        // 压缩率 1-100 映射到 ffmpeg 的 q:v 2-31
        // 压缩率越高（数值大），q:v 值越小（质量越高）
        int qv = 2 + (100 - compression_ratio) * 29 / 99; // 映射公式

        // Windows 系统用反斜杠路径需要处理，但 system() 能处理正斜杠
        // 将路径中的反斜杠替换为正斜杠（ffmpeg 支持）
        char input_path[512];
        char output_path[512];
        strcpy(input_path, argv[i]);
        strcpy(output_path, output_file);

        // 替换反斜杠为正斜杠（可选，ffmpeg 支持两种）
        for (int j = 0; input_path[j]; j++)
        {
            if (input_path[j] == '\\')
                input_path[j] = '/';
        }
        for (int j = 0; output_path[j]; j++)
        {
            if (output_path[j] == '\\')
                output_path[j] = '/';
        }

        // 构建命令
        sprintf(command,
                ".\\tools\\ffmpeg\\ffmpeg.exe -y -i \"%s\" -q:v %d \"%s\" 2> nul",
                input_path, qv, output_path);

        // // 修改为（显示错误）
        // sprintf(command,
        //         ".\\tools\\ffmpeg\\ffmpeg.exe -y -i \"%s\" -q:v %d \"%s\"",
        //         input_path, qv, output_path);

        // 将UTF-8转换为GBK
        char *GBK_command = UTF8ToLocal(command);

        // if (convert_encoding("UTF-8", "GBK", command, GBK_command, sizeof(GBK_command)) == 0)
        // {
        //     // printf("转换后的GBK字节: ");
        //     // for (int i = 0; i < strlen(GBK_command); i++)
        //     // {
        //     //     printf("%02X ", (unsigned char)GBK_command[i]);
        //     // }
        //     // printf("\n");

        //     // 注意：在GBK控制台下打印UTF-8字符串可能会乱码，这是正常的
        //     // 你可以将结果写入文件或通过网络发送
        // }
        // else
        // {
        //     printf("转换失败\n");
        // }

        // // 输出utf8命令调试信息
        // printf("utf8命令显示: %s\n", command);
        // 输出GBK命令调试信息
        // printf("GBK命令显示: %s\n", GBK_command);

        // // 执行命令
        // int result = system(command);

        // if (result == 0)
        // {
        //     printf("  ✓ 压缩成功: %s\n", output_file);
        //     success_count++;
        // }
        // else
        // {
        //     printf("  ✗ 压缩失败: %s (错误码: %d)\n", argv[i], result);
        //     fail_count++;
        // }

        // 执行GBK命令
        int result_gbk = system(GBK_command);
        if (result_gbk == 0)
        {
            printf("  ✓ GBK命令压缩成功: %s\n", output_file);
        }
        else
        {
            printf("  ✗ GBK命令压缩失败: %s (错误码: %d)\n", argv[i], result_gbk);
        }
    }

    printf("====================================\n");
    printf("压缩完成！成功: %d, 失败: %d\n", success_count, fail_count);

    return fail_count; // 返回失败数量，0 表示全部成功
}
// int compressing(int argc, char *argv[])
// {
//     printf("压缩成功！\n");
//     return 0;
// }
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