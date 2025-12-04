#include <stdio.h>
#include <windows.h>

#include "file_path_processing.h"

/**
 * @brief 编码命令(GBK or UTF-8),使用system()执行cmd命令
 * @param  input            输入的文件路径
 * @param  output           输出的文件路径
 * @return int
 * @date 2025-12-04
 */
int ffmpeg_convert(const char *input, const char *output);
/**
 * @brief 获取程序所在目录的辅助函数
 * @return char*
 * @date 2025-12-04
 */
char *get_ffmpeg_path();
char *get_program_directory();
bool check_ffmpeg_available();