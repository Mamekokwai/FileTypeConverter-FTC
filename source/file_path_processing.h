#ifndef FILE_PATH_PROCESSING_H
#define FILE_PATH_PROCESSING_H

#include <stdio.h>
#include <windows.h>
#include <string.h>
// 定义结构体来存储文件信息
typedef struct
{
    char *file_path;
    char *parent_path;
    char *filename_without_ext;
    char *ext;
} FileInfo;

/**
 * @brief 获取文件路径的父级路径
 * @param  file_path        输入的文件路径
 * @param  parent_path      输出的父级路径
 * @date 2025-10-21
 */
void get_parent_path(const char *file_path, char *parent_path);

/**
 * @brief 获取文件名（不含扩展名）
 * @param  file_path        输入的文件路径
 * @param  filename         输出的文件名（不含扩展名）
 * @date 2025-10-21
 */
void get_filename_without_ext(const char *file_path, char *filename);

/**
 * @brief 获取文件扩展名
 * @param  file_path         输入的文件路径
 * @param  ext_output          输出的文件扩展名
 * @date 2025-10-21
 */
void get_ext(const char *file_path, char *ext_output);

//=========================================================================//
/**
 * @brief 获取多个文件的信息（父路径和文件名无扩展名）
 * @note 使用方法:调用一次将全部信息保存在结构体中
 * @param  argc              文件数量
 * @param  argv              文件路径数组
 * @param  file_info         保存文件信息的结构体数组
 * @date 2025-10-21
 */
void get_multiple_file_info(int argc, char *argv[], FileInfo *file_info);

/**
 * @brief   合并文件路径和用户指定的扩展名
 * @param  file_info        FileInfo结构体数组
 * @param  output_path_ptr  保存输出路径的数组
 * @param  user_ext         用户指定的扩展名
 * @param  file_count       文件数量
 * @date 2025-10-21
 */
void combine_paths_count(FileInfo *file_info, char **output_path_ptr, const char *user_ext, int file_count);

/**
 * @brief 将传参编码转换为 UTF-8 编码
 * @param  local_str        传入的本地编码字符串
 * @return char*
 * @date 2025-10-22
 */
char *LocalToUTF8(const char *local_str);

int split_paths(const char *input, char ***paths);
void free_paths(char **paths, int count);
int clear_input_buffer();

#endif //  FILE_PATH_PROCESSING_H