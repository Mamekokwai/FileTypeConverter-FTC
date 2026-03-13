#include "common.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * 清空标准输入缓冲区
 * 读取并丢弃所有字符直到遇到换行符或文件结尾
 */
void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        // 空循环，只读取不处理
    }
}

void clear_screen()
{
#ifdef _WIN32
    system("cls"); // Windows系统
#else
    system("clear"); // Linux/Unix/Mac系统
#endif
}