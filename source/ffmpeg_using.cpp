#include "ffmpeg_using.h"

int ffmpeg_convert(const char *input, const char *output)
{
    char command[512];

    // 构建UTF-8命令
    snprintf(command, sizeof(command), "ffmpeg -i \"%s\" \"%s\" -y -hide_banner -loglevel error", input, output);
    // printf("🔧 UTF-8命令: %s\n", command);

    // 将UTF-8命令转换为本地编码（GBK）
    char *local_command = UTF8ToLocal(command);
    if (local_command)
    {
        // printf("🔧 本地编码命令: %s\n", local_command);
        int result = system(local_command);
        free(local_command);
        return result;
    }
    else
    {
        // 转换失败，使用原始命令
        printf("⚠️ 编码转换失败，使用原始命令\n");
        return system(command);
    }
}

// 获取程序所在目录的辅助函数
char *get_program_directory()
{
    // 创建静态缓冲区以存储路径，路径最大默认260个字符
    static char path[MAX_PATH] = {0};
    // 检查缓冲区是否为空（只包含空字符）
    if (path[0] == '\0')
    {
        // 使用 GetModuleFileNameA 函数获取当前模块（程序）的完整路径
        // NULL 表示获取当前模块的路径，path 是存储路径的缓冲区，MAX_PATH 是缓冲区的最大长度
        GetModuleFileNameA(NULL, path, MAX_PATH);
        // 使用 strrchr 函数找到路径中最后一个反斜杠的位置
        char *last_slash = strrchr(path, '\\');
        // 如果找到了反斜杠
        if (last_slash)
        {
            // 将反斜杠位置的字符设置为空字符，从而截断路径，只保留目录部分
            *last_slash = '\0';
        }
    }
    // 返回程序所在目录的路径
    return path;
}

// 获取 ffmpeg 完整路径
char *get_ffmpeg_path()
{
    // 声明一个静态字符数组来存储 ffmpeg 可执行文件的路径
    // 静态变量确保数组的内存只分配一次，并且在函数调用之间持久存在
    static char ffmpeg_path[MAX_PATH] = {0}; // MAX_PATH 通常定义为 260，这是 Windows 系统中路径的最大长度

    // 检查 ffmpeg_path 数组是否为空（只包含空字符）
    if (ffmpeg_path[0] == '\0')
    {
        // 如果为空，则使用 snprintf 构造 ffmpeg.exe 的完整路径
        // snprintf 用于安全地格式化并存储路径到分配的缓冲区中
        // 它使用格式字符串 "%s\\tools\\ffmpeg\\ffmpeg.exe"，并将 %s 替换为 get_program_directory() 的结果
        snprintf(ffmpeg_path, sizeof(ffmpeg_path),
                 "%s\\tools\\ffmpeg\\ffmpeg.exe", get_program_directory());
        // sizeof(ffmpeg_path) 确保 snprintf 不会向缓冲区中写入超过其容量的字符
    }
    // 返回构造的路径给调用者
    return ffmpeg_path;
}

// 调用 Windows API 函数 PathFileExistsA 检查 ffmpeg 可执行文件的可用性
bool check_ffmpeg_available()
{
    // 通过调用 get_ffmpeg_path() 获取 ffmpeg 可执行文件的路径
    char *ffmpeg_path = get_ffmpeg_path();

    // 使用 Windows API 函数 PathFileExistsA 检查指定路径的文件是否存在
    if (PathFileExistsA(ffmpeg_path))
    {
        // 如果文件存在，打印成功消息到控制台
        printf("✅ FFmpeg 可用: %s\n", ffmpeg_path);
        // 返回 true 表示 ffmpeg 可用
        return true;
    }
    else
    {
        // 如果文件不存在，打印错误消息到控制台
        printf("❌ FFmpeg 未找到: %s\n", ffmpeg_path);
        // 提示用户确保 tools/ffmpeg/ffmpeg.exe 文件存在
        printf("请确保 tools/ffmpeg/ffmpeg.exe 存在\n");
        // 返回 false 表示 ffmpeg 未找到
        return false;
    }
}
