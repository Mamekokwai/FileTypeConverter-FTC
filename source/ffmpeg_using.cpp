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