#include "file_path_processing.h"

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
        // 先进行编码转换
        char *utf8_path = LocalToUTF8(argv[i]);

        file_info[i].file_path = (char *)malloc(strlen(utf8_path));
        strcpy(file_info[i].file_path, utf8_path);

        file_info[i].parent_path = (char *)malloc(_MAX_PATH * sizeof(char));
        get_parent_path(utf8_path, file_info[i].parent_path);

        file_info[i].filename_without_ext = (char *)malloc(_MAX_FNAME * sizeof(char));
        get_filename_without_ext(utf8_path, file_info[i].filename_without_ext);

        file_info[i].ext = (char *)malloc(_MAX_EXT * sizeof(char));
        get_ext(utf8_path, file_info[i].ext);

        free(utf8_path);
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
    // 先转到宽字符，再转到 UTF-8
    int wlen = MultiByteToWideChar(CP_ACP, 0, local_str, -1, NULL, 0);
    wchar_t *wstr = (wchar_t *)malloc(wlen * sizeof(wchar_t));
    MultiByteToWideChar(CP_ACP, 0, local_str, -1, wstr, wlen);

    int utflen = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
    char *utf8str = (char *)malloc(utflen);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, utf8str, utflen, NULL, NULL);

    free(wstr);
    return utf8str;
}

int split_paths(const char *input, char ***paths)
{
    if (!input || !paths)
        return -1;

    // 统计路径数量（通过引号数量）
    int count = 0;
    const char *ptr = input;
    while (*ptr)
    {
        if (*ptr == '"')
            count++;
        ptr++;
    }
    // 错误检查
    if (count % 2 != 0 || count == 0)
        return -1; // 引号不匹配或没有路径
    count /= 2;    // 每对引号包含一个路径

    // 分配内存
    *paths = (char **)malloc(count * sizeof(char *));
    if (!*paths)
        return -1;

    // 初始化指针为 NULL
    for (int i = 0; i < count; i++)
    {
        (*paths)[i] = NULL;
    }

    // 提取路径
    int index = 0;
    ptr = input;
    while (*ptr && index < count)
    {
        // 找到开始引号
        while (*ptr && *ptr != '"')
            ptr++;
        if (!*ptr)
            break;

        const char *start = ++ptr; // 跳过开始引号

        // 找到结束引号
        while (*ptr && *ptr != '"')
            ptr++;
        if (!*ptr)
            break;

        // 复制路径 - 添加显式类型转换
        int len = ptr - start;
        (*paths)[index] = (char *)malloc(len + 1);
        if (!(*paths)[index])
        {
            // 内存分配失败，清理已分配的内存
            for (int i = 0; i < index; i++)
                free((*paths)[i]);
            free(*paths);
            *paths = NULL;
            return 0;
        }
        strncpy((*paths)[index], start, len);
        (*paths)[index][len] = '\0';

        index++;
        ptr++; // 跳过结束引号
    }

    return count;
}

void free_paths(char **paths, int count)
{
    if (!paths)
        return;
    for (int i = 0; i < count; i++)
    {
        free(paths[i]);
    }
    free(paths);
}

int clear_input_buffer()
{
    int c;
    int count = 0;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        count++;
    }
    return count; // 返回清理的字符数，可用于调试
}