#ifndef FILE_PATH_PROCESSING_H
#define FILE_PATH_PROCESSING_H

#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

// 编码配置宏
// ============================================================
// 选择编码处理方式：
//   PATH_ENCODING_UTF8     - 所有路径转换为UTF-8存储
//   PATH_ENCODING_LOCAL    - 使用系统本地编码
//   PATH_ENCODING_AUTO     - 自动检测并转换（推荐）
// ============================================================

#define PATH_ENCODING_UTF8 1
#define PATH_ENCODING_LOCAL 2
#define PATH_ENCODING_AUTO 3

// 🎯 在这里设置您想要的编码方式（修改这个值即可）
#define CURRENT_PATH_ENCODING PATH_ENCODING_LOCAL

// 编码方式描述
#if CURRENT_PATH_ENCODING == PATH_ENCODING_UTF8
#define ENCODING_MODE_DESC "UTF-8编码模式"
#elif CURRENT_PATH_ENCODING == PATH_ENCODING_LOCAL
#define ENCODING_MODE_DESC "本地编码模式"
#elif CURRENT_PATH_ENCODING == PATH_ENCODING_AUTO
#define ENCODING_MODE_DESC "自动编码模式"
#else
#define CURRENT_PATH_ENCODING PATH_ENCODING_AUTO
#define ENCODING_MODE_DESC "自动编码模式(默认)"
#endif

// 调试宏
#define PRINT_ENCODING_INFO() printf("🔧 当前编码模式: %s\n", ENCODING_MODE_DESC)

// 定义全局路径数组和计数器
extern char **g_global_paths;
extern int g_global_path_count;

// 通用交换宏
#define SWAP(a, b)           \
    do                       \
    {                        \
        typeof(a) _temp = a; \
        a = b;               \
        b = _temp;           \
    } while (0)

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

/**
 * @brief 将 UTF-8 编码转换为本地编码（用于调试输出）
 * @param  utf8_str          UTF-8编码字符串
 * @return char*
 * @date 2025-10-24
 */
char *UTF8ToLocal(const char *utf8_str);

// /**
//  * @brief 分割输入的路径字符串为多个路径字符串
//  * @param  input              输入的路径字符串
//  * @param  paths              输出的路径数组
//  * @note 在function2.cpp的split_path_from_user()调用
//  * @return int
//  * @date 2025-10-24
//  */
// int split_paths(const char *input, char ***paths);

/**
 * @brief 更智能的分割路径字符串为多个路径字符串
 * @param  input            输入的路径字符串
 * @param  paths            输出的路径数组
 * @note 在function2.cpp的split_path_from_user()调用
 * @return int
 * @date 2025-10-24
 */
int split_paths_smart(const char *input, char ***paths);

/**
 * @brief 释放路径数组的内存
 * @param  paths             路径数组
 * @param  count              路径数量
 * @date 2025-10-24
 */
void free_paths(char **paths, int count);

/**
 * @brief 清空输入缓冲区
 * @return int
 * @date 2025-10-24
 */
int clear_input_buffer();

/**
 * @brief 合并路径数组到全局变量
 * @param  new_paths        新导入的路径数组
 * @param  new_count        新导入的路径数量
 * @return int
 * @date 2025-10-24
 */
int paths_merge_to_global(char **new_paths, int new_count);

/**
 * @brief 检查字符串是否只包含空白字符
 * @param str 要检查的字符串
 * @return int 1=只有空白字符, 0=包含非空白字符
 */
int is_whitespace_only(const char *str);

int is_whitespace_only_range(const char *start, const char *end);

static char *process_path_encoding(const char *input_path);

/**
 * @brief 检查字符串是否只包含数字字符（纯数字）
 * @param str 要检查的字符串
 * @return int 1=纯数字, 0=包含非数字字符
 */
int is_pure_digits(const char *str);

/**
 * @brief 等待用户输入回车键并忽略其他任何输入
 * @date 2025-10-24
 */
void wait_for_enter();

/**
 * @brief 增强的路径存在性检查
 * @param path 要检查的路径
 * @param check_type 检查类型: 0=文件或目录, 1=仅文件, 2=仅目录
 * @return int 1=存在且符合类型, 0=不存在或类型不匹配
 */
int path_exists_ex(const char *path, int check_type);

#endif //  FILE_PATH_PROCESSING_H