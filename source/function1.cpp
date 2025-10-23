#include "function1.h"

void function1(int argc, char *argv[])
{
    char newtype[_MAX_EXT];

    newtype[0] = '.';
    printf("▲▼▲请输入文件类型(例如: png jpg gif ico):▼▲▼ \n");
    printf("▶ ");
    scanf("%254s", newtype + 1);
    clear_input_buffer();

    printf("▲▼▲FUNCTION1 START▲▼▲\n");
    int result = file_type_change(argc, argv, newtype);
    if (result)
    {
        printf("❌ FUNCTION1 ERROR\n");
    }
    else
    {
        printf("✅ FUNCTION1 SUCCESS\n");
    };
}

int file_type_change(int argc, char *argv[], char *newtype)
{
    int result = 0;
    FileInfo *file_info = NULL;
    char **output_path_ptr = NULL;

    // 🚨 检查参数
    if (argc <= 1)
    {
        printf("❌ 没有文件\nSOLUION: 请使用功能2\n");
        return -1;
    }

    // 分配内存
    file_info = (FileInfo *)malloc((argc) * sizeof(FileInfo));
    output_path_ptr = (char **)malloc(argc * sizeof(char *));

    // 🚨 问题：没有检查内存分配是否成功
    if (file_info == NULL || output_path_ptr == NULL)
    {
        printf("❌ 内存分配失败！\n");
        result = -1;
        goto cleanup;
    }

    // 初始化指针
    for (int i = 0; i < argc; i++)
    {
        file_info[i].parent_path = NULL;
        file_info[i].filename_without_ext = NULL;
        file_info[i].ext = NULL;
        output_path_ptr[i] = NULL;
    }

    get_multiple_file_info(argc, argv, file_info);
    combine_paths_count(file_info, output_path_ptr, newtype, argc);

    if (argc > 1)
    {
        printf("正在转换 %d 个文件...\n", argc - 1);

        for (int i = 1; i < argc; i++)
        {
            printf("[%d/%d] 转换: %s%s -> %s%s\n",
                   i, argc - 1, file_info[i].filename_without_ext, file_info[i].ext,
                   file_info[i].filename_without_ext, newtype);
            // printf("文件路径: %s\n", argv[i]);
            // printf("父目录: %s\n", file_info[i].parent_path);
            // printf("文件名: %s\n", file_info[i].filename_without_ext);
            // printf("扩展名: %s\n", file_info[i].ext);
            // printf("输出路径: %s\n", output_path_ptr[i]);
            // printf("---\n");

            // 执行转换
            int result1 = ffmpeg_convert(argv[i], output_path_ptr[i]);

            if (result1 == 0)
            {
                printf("   ✅ SUCCESS\n");
            }
            else
            {
                printf("   ❌ FAILURE\n");
            }

            // 添加短暂延时，避免同时启动太多进程
            Sleep(100);
        }
        printf("转换完成！\n");
    }
cleanup:
    // 安全释放内存
    if (output_path_ptr)
    {
        for (int i = 0; i < argc; i++)
        {
            if (output_path_ptr[i])
            {
                free(output_path_ptr[i]);
            }
        }
        free(output_path_ptr);
    }

    if (file_info)
    {
        for (int i = 0; i < argc; i++)
        {
            if (file_info[i].parent_path)
                free(file_info[i].parent_path);
            if (file_info[i].filename_without_ext)
                free(file_info[i].filename_without_ext);
            if (file_info[i].ext)
                free(file_info[i].ext);
        }
        free(file_info);
    }

    printf("按回车键继续...");
    getchar();
    return result;
}