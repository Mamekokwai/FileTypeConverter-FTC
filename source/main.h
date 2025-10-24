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

void function3();

// 使用统一的全局变量名称
extern char **g_global_paths;
extern int g_global_path_count;

// 编译代码:
// gcc -o .\output\main.exe .\sourcecode\file_path_processing.cpp .\sourcecode\ffmpeg_using.cpp .\sourcecode\function1.cpp .\sourcecode\main.cpp .\sourcecode\animation.cpp