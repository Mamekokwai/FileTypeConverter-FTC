#include "function1.h"

int function1(int path_count, char *path_str[])
{
    char newtype[_MAX_EXT];

    printf("▲▼▲FUNCTION1 START▲▼▲\n");
    newtype[0] = '.';
    printf("▲▼▲请输入文件类型(例如: png jpg gif ico):▼▲▼ \n");
    printf("▶ ");
    scanf("%254s", newtype + 1);
    clear_input_buffer();

    int result = file_type_change(path_count, path_str, newtype);
    if (result)
    {
        printf("❌ FUNCTION file_type_change() error!\n");
        return -1;
    }
    printf("▲▼▲FUNCTION1 SUCCESS▲▼▲\n");
    // 等待用户输入回车
    wait_for_enter();

    return result;
    return 0;
}

int file_type_change(int path_count, char *path_str[], char *newtype)
{
    int result = 0;
    FileInfo *file_info = NULL;
    char **output_path_ptr = NULL;

    // 🚨 检查参数
    if (path_count <= 0)
    {
        printf("❌ 没有文件\nSOLUION: 请使用功能2\n");
        return -1;
    }

    // 分配内存
    file_info = (FileInfo *)malloc((path_count) * sizeof(FileInfo));
    output_path_ptr = (char **)malloc(path_count * sizeof(char *));

    // 🚨 问题：没有检查内存分配是否成功
    if (file_info == NULL || output_path_ptr == NULL)
    {
        printf("❌ Memory -output_path_ptr- allocation error!\n");
        result = -1;
        goto cleanup;
    }

    // 初始化指针
    for (int i = 0; i < path_count; i++)
    {
        file_info[i].parent_path = NULL;
        file_info[i].filename_without_ext = NULL;
        file_info[i].ext = NULL;
        output_path_ptr[i] = NULL;
    }

    get_multiple_file_info(path_count, path_str, file_info);
    combine_paths_count(file_info, output_path_ptr, newtype, path_count);

    if (path_count > 0)
    {
        printf("正在转换 %d 个文件...\n", path_count);

        for (int i = 0; i < path_count; i++)
        {
            printf("[%d/%d] 转换: %s%s -> %s%s\n",
                   i + 1, path_count, file_info[i].filename_without_ext, file_info[i].ext,
                   file_info[i].filename_without_ext, newtype);
            // printf("文件路径: %s\n", path_str[i]);
            // printf("父目录: %s\n", file_info[i].parent_path);
            // printf("文件名: %s\n", file_info[i].filename_without_ext);
            // printf("扩展名: %s\n", file_info[i].ext);
            // printf("输出路径: %s\n", output_path_ptr[i]);
            // printf("---\n");

            // 执行转换
            printf("使用GCK编码指令...");
            int result1 = ffmpeg_convert(path_str[i], output_path_ptr[i]);
            // printf("%s\n", path_str[i]);

            if (result1 == 0)
            {
                printf("✅ SUCCESS\n");
            }
            else
            {
                printf("❌ FAILURE\n");
            }

            // 添加短暂延时，避免同时启动太多进程
            Sleep(10);
        }
    }
cleanup:
    // 安全释放内存
    if (output_path_ptr)
    {
        for (int i = 0; i < path_count; i++)
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
        for (int i = 0; i < path_count; i++)
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
    return result;
}