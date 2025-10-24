#include "ffmpeg_using.h"

int ffmpeg_convert(const char *input, const char *output)
{
    char command[512];
    // 使用 -hide_banner -loglevel error 隐藏不必要信息
    snprintf(command, sizeof(command), "ffmpeg -i \"%s\" \"%s\" -y -hide_banner -loglevel error", input, output);
    // printf("%s\n", input);
    printf("%s\n", command);

    return system(command);
}
