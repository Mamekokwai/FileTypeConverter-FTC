#include <stdio.h>
#include <windows.h>

#include "file_path_processing.h"

int ffmpeg_convert(const char *input, const char *output);

char *get_ffmpeg_path();
char *get_program_directory();
bool check_ffmpeg_available();