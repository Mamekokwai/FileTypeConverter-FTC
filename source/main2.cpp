#include "main2.h"

// int main(int argc, char *argv[])
// {
//     // 设置控制台编码为 UTF-8（更完整的方法）
//     SetConsoleOutputCP(65001);
//     SetConsoleCP(65001);
//     system("chcp 65001 > nul");

//     // 分配结构体数组
//     FileInfo *file_info = (FileInfo *)malloc((argc) * sizeof(FileInfo));

//     // 分配内存给输出路径
//     char **output_path_ptr = (char **)malloc(argc * sizeof(char *));

//     // 获取多个文件信息
//     get_multiple_file_info(argc, argv, file_info);

//     // 合并路径
//     combine_paths_count(file_info, output_path_ptr, ".ico", argc);

//     if (argc > 1)
//     {
//         for (int i = 1; i < argc; i++)
//         {
//             printf("文件路径: %s\n", argv[i]);
//             printf("父目录: %s\n", file_info[i].parent_path);
//             printf("文件名: %s\n", file_info[i].filename_without_ext);
//             printf("扩展名: %s\n", file_info[i].ext);
//             printf("输出路径: %s\n", output_path_ptr[i]);
//             printf("---\n");
//         }
//     }

//     getchar();

//     // 释放内存
//     for (int i = 0; i < argc; i++)
//     {
//         free(output_path_ptr[i]);
//         free(file_info[i].parent_path);
//         free(file_info[i].filename_without_ext);
//         free(file_info[i].ext);
//     }
//     free(output_path_ptr);
//     free(file_info);

//     return 0;
// }
