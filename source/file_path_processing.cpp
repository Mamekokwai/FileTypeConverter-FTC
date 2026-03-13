#include "file_path_processing.h"
#include <ctype.h>
#include <stdlib.h>

// // 全局变量定义
// char **g_global_paths = NULL;
// int g_global_path_count = 0;

void get_parent_path(const char *file_path, char *parent_path)
{
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];

    // 分割路径
    _splitpath_s(file_path, drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);

    // 组合驱动器和目录（就是父级路径）
    _makepath_s(parent_path, _MAX_PATH, drive, dir, "", "");

    // 移除末尾的反斜杠（如果有）
    size_t len = strlen(parent_path);
    if (len > 0 && (parent_path[len - 1] == '\\' || parent_path[len - 1] == '/'))
    {
        parent_path[len - 1] = '\0';
    }
}

void get_filename_without_ext(const char *file_path, char *filename)
{
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];

    _splitpath_s(file_path, NULL, 0, NULL, 0, fname, _MAX_FNAME, ext, _MAX_EXT);
    strcpy(filename, fname);
}

void get_ext(const char *file_path, char *ext_output)
{
    char ext[_MAX_EXT];

    _splitpath_s(file_path, NULL, 0, NULL, 0, NULL, 0, ext, _MAX_EXT);
    strcpy(ext_output, ext);
}

//=========================================================================//
void get_multiple_file_info(int argc, char *argv[], FileInfo *file_info)
{
    for (int i = 0; i < argc; i++)
    {
        // 直接使用 UTF-8 路径，不再重复转换
        file_info[i].file_path = _strdup(argv[i]);

        file_info[i].parent_path = (char *)malloc(_MAX_PATH * sizeof(char));
        get_parent_path(argv[i], file_info[i].parent_path);

        file_info[i].filename_without_ext = (char *)malloc(_MAX_FNAME * sizeof(char));
        get_filename_without_ext(argv[i], file_info[i].filename_without_ext);

        file_info[i].ext = (char *)malloc(_MAX_EXT * sizeof(char));
        get_ext(argv[i], file_info[i].ext);
    }
}

void combine_paths_count(FileInfo *file_info, char **output_path_ptr, const char *user_ext, int file_count)
{
    for (int i = 0; i < file_count; i++)
    {
        size_t len = strlen(file_info[i].parent_path) + strlen(file_info[i].filename_without_ext) + strlen(user_ext) + 3;
        output_path_ptr[i] = (char *)malloc(len * sizeof(char));

        snprintf(output_path_ptr[i], len, "%s\\%s%s",
                 file_info[i].parent_path,
                 file_info[i].filename_without_ext,
                 user_ext);
    }
}

// 将本地编码转换为 UTF-8,修复路径乱码问题
char *LocalToUTF8(const char *local_str)
{
    if (!local_str)
        return NULL;

    // 先转到宽字符，再转到 UTF-8
    int wlen = MultiByteToWideChar(CP_ACP, 0, local_str, -1, NULL, 0);
    if (wlen <= 0)
        return NULL;

    wchar_t *wstr = (wchar_t *)malloc(wlen * sizeof(wchar_t));
    if (!wstr)
        return NULL;

    MultiByteToWideChar(CP_ACP, 0, local_str, -1, wstr, wlen);

    int utflen = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
    if (utflen <= 0)
    {
        free(wstr);
        return NULL;
    }

    char *utf8str = (char *)malloc(utflen);
    if (utf8str)
    {
        WideCharToMultiByte(CP_UTF8, 0, wstr, -1, utf8str, utflen, NULL, NULL);
    }

    free(wstr);
    return utf8str;
}

// UTF-8 转本地编码（用于调试输出）
char *UTF8ToLocal(const char *utf8_str)
{
    if (!utf8_str)
        return NULL;

    // 先转到宽字符
    int wlen = MultiByteToWideChar(CP_UTF8, 0, utf8_str, -1, NULL, 0);
    if (wlen <= 0)
        return NULL;

    wchar_t *wstr = (wchar_t *)malloc(wlen * sizeof(wchar_t));
    if (!wstr)
        return NULL;

    MultiByteToWideChar(CP_UTF8, 0, utf8_str, -1, wstr, wlen);

    // 再转到本地编码
    int locallen = WideCharToMultiByte(CP_ACP, 0, wstr, -1, NULL, 0, NULL, NULL);
    if (locallen <= 0)
    {
        free(wstr);
        return NULL;
    }

    char *localstr = (char *)malloc(locallen);
    if (localstr)
    {
        WideCharToMultiByte(CP_ACP, 0, wstr, -1, localstr, locallen, NULL, NULL);
    }

    free(wstr);
    return localstr;
}

// 改进的智能分割函数 - 只接受实际存在的文件
int split_paths_smart(const char *input, char ***paths)
{
    if (!input || strlen(input) == 0)
        return 0;

    // printf("🔍 原始输入: [%s]\n", input);

    int capacity = 10;
    int count = 0;
    *paths = (char **)malloc(capacity * sizeof(char *));
    if (!*paths)
        return 0;

    // 初始化指针
    for (int i = 0; i < capacity; i++)
    {
        (*paths)[i] = NULL;
    }

    const char *start = input;
    const char *end = input;
    int in_quotes = 0;

    while (*end)
    {
        // 处理引号
        if (*end == '"')
        {
            in_quotes = !in_quotes;
            if (!in_quotes)
            {
                // 找到完整的引号路径
                const char *path_start = start;
                const char *path_end = end;

                // 跳过开始引号
                if (*path_start == '"')
                    path_start++;

                int path_len = path_end - path_start;
                if (path_len > 0)
                {
                    char temp_path[MAX_PATH];
                    strncpy(temp_path, path_start, path_len);
                    temp_path[path_len] = '\0';

                    // 🎯 检查文件是否存在
                    if (path_exists_ex((temp_path), 1)) // 1 表示仅检查文件
                    {
                        // 扩展数组如果需要
                        if (count >= capacity)
                        {
                            capacity *= 2;
                            *paths = (char **)realloc(*paths, capacity * sizeof(char *));
                        }

                        (*paths)[count] = _strdup(temp_path);
                        // printf("📁 解析引号路径: [%s]\n", (*paths)[count]);
                        count++;
                    }
                    // else
                    // {
                    //     printf("❌ 忽略无效文件: [%s]\n", temp_path);
                    // }
                }

                start = end + 1;
            }
        }
        // 处理空格分隔（不在引号内时）
        else if (*end == ' ' && !in_quotes)
        {
            int path_len = end - start;
            if (path_len > 0 && !is_whitespace_only_range(start, end))
            {
                char temp_path[MAX_PATH];
                strncpy(temp_path, start, path_len);
                temp_path[path_len] = '\0';

                // 🎯 检查文件是否存在
                if (path_exists_ex((temp_path), 1)) // 1 表示仅检查文件
                {
                    // 扩展数组如果需要
                    if (count >= capacity)
                    {
                        capacity *= 2;
                        *paths = (char **)realloc(*paths, capacity * sizeof(char *));
                    }

                    (*paths)[count] = _strdup(temp_path);
                    // printf("📁 解析空格路径: [%s]\n", (*paths)[count]);
                    count++;
                }
                // else
                // {
                //     printf("❌ 忽略无效文件: [%s]\n", temp_path);
                // }
            }
            start = end + 1;
        }

        end++;
    }

    // 处理最后一个路径（如果没有以空格或引号结束）
    if (start < end && !is_whitespace_only(start))
    {
        int path_len = end - start;
        if (path_len > 0)
        {
            char temp_path[MAX_PATH];
            strncpy(temp_path, start, path_len);
            temp_path[path_len] = '\0';

            // 🎯 检查文件是否存在
            if (path_exists_ex((temp_path), 1)) // 1 表示仅检查文件
            {
                // 扩展数组如果需要
                if (count >= capacity)
                {
                    capacity *= 2;
                    *paths = (char **)realloc(*paths, capacity * sizeof(char *));
                }

                (*paths)[count] = _strdup(temp_path);
                // printf("📁 解析末尾路径: [%s]\n", (*paths)[count]);
                count++;
            }
            // else
            // {
            //     printf("❌ 忽略无效文件: [%s]\n", temp_path);
            // }
        }
    }

    printf("✅ 已解析出 %d 个路径\n", count);
    return count;
}

// 辅助函数：检查字符串范围是否只包含空白字符
int is_whitespace_only_range(const char *start, const char *end)
{
    const char *ptr = start;
    while (ptr < end)
    {
        if (!isspace((unsigned char)*ptr))
            return 0;
        ptr++;
    }
    return 1;
}

// 辅助函数：检查是否只包含空白字符
int is_whitespace_only(const char *str)
{
    while (*str)
    {
        if (!isspace((unsigned char)*str))
            return 0;
        str++;
    }
    return 1;
}

// int split_paths(const char *input, char ***paths)
// {
//     // 简化版本，直接调用智能分割
//     return split_paths_smart(input, paths);
// }

void free_paths(char **paths, int count)
{
    if (!paths)
        return;
    for (int i = 0; i < count; i++)
    {
        if (paths[i])
        {
            free(paths[i]);
        }
    }
    free(paths);
}



//=========================================================================//

int paths_merge_to_global(char **new_paths, int new_count)
{
    if (!new_paths || new_count <= 0)
    {
        printf("❌ paths_merge_to_global() 参数错误\n");
        printf("new_paths=%p, new_count=%d\n", (void *)new_paths, new_count);
        return -1;
    }

    // 显示当前编码模式
    PRINT_ENCODING_INFO();

    printf("▲ 合并路径到全局变量:\n");
    // printf("  当前全局路径数: %d\n", g_global_path_count);
    // printf("  新导入路径数: %d\n", new_count);

    // 计算新的总数量
    int total_count = g_global_path_count + new_count;

    // 分配新的内存空间
    char **merged_paths = (char **)malloc(total_count * sizeof(char *));
    if (!merged_paths)
    {
        printf("❌ 内存分配失败\n");
        return -1;
    }

    // 初始化新数组的所有指针为 NULL
    for (int i = 0; i < total_count; i++)
    {
        merged_paths[i] = NULL;
    }

    // 复制原有的全局路径
    for (int i = 0; i < g_global_path_count; i++)
    {
        if (g_global_paths && g_global_paths[i])
        {
            merged_paths[i] = _strdup(g_global_paths[i]);
        }
    }

    // 🎯 使用宏控制的编码处理方式
    // 复制新导入的路径
    for (int i = 0; i < new_count; i++)
    {
        if (new_paths[i])
        {
            // 使用统一的编码处理函数
            char *processed_path = process_path_encoding(new_paths[i]);
            if (processed_path)
            {
                merged_paths[g_global_path_count + i] = processed_path;
                // printf("  ✅ 添加路径: %s\n", processed_path);
            }
            else
            {
                merged_paths[g_global_path_count + i] = _strdup(new_paths[i]);
                printf("  ⚠️  添加路径(原始): %s\n", new_paths[i]);
            }
        }
    }

    // 释放旧的全局路径内存
    if (g_global_paths)
    {
        free_paths(g_global_paths, g_global_path_count);
    }

    // 更新全局变量
    g_global_paths = merged_paths;
    g_global_path_count = total_count;

    // 显示合并结果
    printf("✅ 合并成功，总路径数: %d\n", g_global_path_count);

    // 显示所有路径
    printf("▲ 所有路径列表:\n");
    for (int i = 0; i < g_global_path_count; i++)
    {
        if (g_global_paths[i])
        {
            // 根据编码模式决定如何显示
#if CURRENT_PATH_ENCODING == PATH_ENCODING_UTF8
            // UTF-8模式：可能需要转换回本地编码显示
            char *local_display = UTF8ToLocal(g_global_paths[i]);
            if (local_display)
            {
                printf("  %d: %s\n", i, local_display);
                free(local_display);
            }
            else
            {
                printf("  %d: %s\n", i, g_global_paths[i]);
            }
#else
            // 其他模式：直接显示
            printf("  %d: %s\n", i, g_global_paths[i]);
#endif
        }
        else
        {
            printf("  %d: [NULL]\n", i);
        }
    }

    return 0;
}

static char *process_path_encoding(const char *input_path)
{
    if (!input_path)
        return NULL;

#if CURRENT_PATH_ENCODING == PATH_ENCODING_UTF8
    // UTF-8 模式：强制转换为UTF-8
    // printf("  🔄 [UTF-8 MOD] TRANSLATING ENCODING\n");
    return LocalToUTF8(input_path);

#elif CURRENT_PATH_ENCODING == PATH_ENCODING_LOCAL
    // 本地编码模式：直接复制
    // printf("  📝 [LOCAL MOD] LOCAL ENCODING\n");
    return _strdup(input_path);

#elif CURRENT_PATH_ENCODING == PATH_ENCODING_AUTO
    // 自动模式：尝试检测并智能处理
    // printf("  🔍 [AUTO MOD] DETECTING ENCODING\n");

    // 简单的自动检测逻辑：
    // 如果路径包含中文字符且看起来是乱码，尝试转换
    int has_chinese = 0;
    int likely_mojibake = 0;
    const char *p = input_path;

    while (*p)
    {
        // 检测可能的中文乱码模式（GBK编码特征）
        if ((unsigned char)*p >= 0x80)
        {
            has_chinese = 1;
            // 简单的乱码检测：连续的高位字节
            if ((unsigned char)*p >= 0xA1 && (unsigned char)*p <= 0xFE)
            {
                likely_mojibake = 1;
                break;
            }
        }
        p++;
    }

    if (has_chinese && likely_mojibake)
    {
        printf("  🔄 [AUTO] POSIBITLY MOJIBAKE, TRANSLATING ENCODING TO UTF-8\n");
        return LocalToUTF8(input_path);
    }
    else
    {
        printf("  📝 [AUTO] USING LOCAL ENCODING\n");
        return _strdup(input_path);
    }

#else
    // 默认情况
    return _strdup(input_path);
#endif
}

int is_pure_digits(const char *str)
{
    if (!str || *str == '\0')
    {
        return 0; // 空指针或空字符串
    }

    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)str[i]))
        {
            return 0; // 包含非数字字符
        }
    }

    return 1; // 纯数字
}

void wait_for_enter()
{
    printf("按回车键继续...");
    fflush(stdout);

    // 保存原来的标准输入句柄
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

    // 禁用所有输入模式
    DWORD mode;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT | ENABLE_PROCESSED_INPUT));

    // 读取直到回车
    DWORD read;
    INPUT_RECORD input;
    do
    {
        ReadConsoleInput(hStdin, &input, 1, &read);
    } while (!(input.EventType == KEY_EVENT &&
               input.Event.KeyEvent.wVirtualKeyCode == VK_RETURN &&
               input.Event.KeyEvent.bKeyDown));

    // 恢复模式
    SetConsoleMode(hStdin, mode);
    printf("\n");
}

int path_exists_ex(const char *path, int check_type)
{
    if (!path || *path == '\0')
    {
        printf("❌ 路径为空\n");
        return 0;
    }

    // 首先检查路径是否存在
    if (!PathFileExistsA(UTF8ToLocal(path)))
    {
        printf("❌ 路径不存在: %s\n", path);
        return 0;
    }

    // 根据检查类型进一步验证
    switch (check_type)
    {
    case 0: // 文件或目录都可以
        printf("✅ 路径存在: %s\n", path);
        return 1;

    case 1: // 仅文件
        if (PathIsDirectoryA(LocalToUTF8(path)))
        {
            printf("❌ 这是目录，不是文件: %s\n", path);
            return 0;
        }
        printf("✅ 文件存在: %s\n", path);
        return 1;

    case 2: // 仅目录
        if (!PathIsDirectoryA(LocalToUTF8(path)))
        {
            printf("❌ 这是文件，不是目录: %s\n", path);
            return 0;
        }
        printf("✅ 目录存在: %s\n", path);
        return 1;

    default:
        printf("❌ 无效的检查类型: %d\n", check_type);
        return 0;
    }
}