#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <direct.h>

#include "file_path_processing.h"
#include "ffmpeg_using.h"
#include "function1.h"
#include "animation.h"
#include "function2.h"
#include "init.h"
#include "function3.h"
#include "common.h"

// 使用统一的全局变量名称
extern char **g_global_paths;
extern int g_global_path_count;
extern int compression_ratio;

// 定义宏
#define FILE_TYPE_CHANGING 1             // 格式转换
#define ADDING_FILE_PATH 2               // 添加文件路径
#define COMPRESSION_TO_JPG 3             // 图片压缩为jpg
#define DELETE_FILE_PATH 4               // 删除文件路径
#define SHOW_PATH_LIST 5                 // 显示路径列表
#define COPY_AND_RENAME_BY_PARENT_PATH 6 // 根据父路径复制并重命名
#define TEST 10                          // 测试
#define EXIT 0                           // 退出

typedef struct
{
    int choice;
    const char *description;
} menu_choice;

// 编译代码:
// gcc -o .\output\main.exe .\sourcecode\file_path_processing.cpp .\sourcecode\ffmpeg_using.cpp .\sourcecode\function1.cpp .\sourcecode\main.cpp .\sourcecode\animation.cpp