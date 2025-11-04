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
    static char path[MAX_PATH] = {0};
    if (path[0] == '\0')
    {
        GetModuleFileNameA(NULL, path, MAX_PATH);
        char *last_slash = strrchr(path, '\\');
        if (last_slash)
            *last_slash = '\0';
    }
    return path;
}

// 获取 ffmpeg 完整路径
char *get_ffmpeg_path()
{
    static char ffmpeg_path[MAX_PATH] = {0};
    if (ffmpeg_path[0] == '\0')
    {
        snprintf(ffmpeg_path, sizeof(ffmpeg_path),
                 "%s\\tools\\ffmpeg\\ffmpeg.exe", get_program_directory());
    }
    return ffmpeg_path;
}

// 检查 ffmpeg 可用性
bool check_ffmpeg_available()
{
    char *ffmpeg_path = get_ffmpeg_path();

    if (PathFileExistsA(ffmpeg_path))
    {
        printf("✅ FFmpeg 可用: %s\n", ffmpeg_path);
        return true;
    }
    else
    {
        printf("❌ FFmpeg 未找到: %s\n", ffmpeg_path);
        printf("请确保 tools/ffmpeg/ffmpeg.exe 存在\n");
        return false;
    }
}