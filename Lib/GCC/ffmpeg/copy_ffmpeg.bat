@echo off
echo 复制 FFmpeg 库文件到项目...

REM 获取 bat 文件所在目录
set "BAT_DIR=%~dp0"
echo BAT 文件目录: %BAT_DIR%

@REM REM 启动 MSYS2 UCRT64 并执行复制命令
@REM C:\msys64\ucrt64.exe -c "
@REM PROJECT_PATH='/d/PersonalFile/Art/paint/2025/10-21shell_ico_make/FileTypeConverter-FTC'

@REM echo '复制 FFmpeg 库文件到项目...'
@REM echo '目标路径: '\\\"\\\$PROJECT_PATH\\\"'

@REM mkdir -p \\\"\\\$PROJECT_PATH/lib/ffmpeg/include\\\"
@REM mkdir -p \\\"\\\$PROJECT_PATH/lib/ffmpeg/lib\\\"

@REM echo '复制头文件...'
@REM cp -r /ucrt64/include/libav* \\\"\\\$PROJECT_PATH/lib/ffmpeg/include/\\\"
@REM cp -r /ucrt64/include/libsw* \\\"\\\$PROJECT_PATH/lib/ffmpeg/include/\\\"

@REM echo '复制静态库...'
@REM cp /ucrt64/lib/libavcodec.a \\\"\\\$PROJECT_PATH/lib/ffmpeg/lib/\\\"
@REM cp /ucrt64/lib/libavformat.a \\\"\\\$PROJECT_PATH/lib/ffmpeg/lib/\\\"
@REM cp /ucrt64/lib/libavutil.a \\\"\\\$PROJECT_PATH/lib/ffmpeg/lib/\\\"
@REM cp /ucrt64/lib/libswscale.a \\\"\\\$PROJECT_PATH/lib/ffmpeg/lib/\\\"
@REM cp /ucrt64/lib/libavfilter.a \\\"\\\$PROJECT_PATH/lib/ffmpeg/lib/\\\"
@REM cp /ucrt64/lib/libswresample.a \\\"\\\$PROJECT_PATH/lib/ffmpeg/lib/\\\"

@REM echo '✅ 复制完成！'
@REM echo '📁 头文件位置: '\\\"\\\$PROJECT_PATH/lib/ffmpeg/include/\\\"'
@REM echo '📁 库文件位置: '\\\"\\\$PROJECT_PATH/lib/ffmpeg/lib/\\\"'

@REM echo '验证复制结果:'
@REM ls \\\"\\\$PROJECT_PATH/lib/ffmpeg/include/\\\" | head -5
@REM ls \\\"\\\$PROJECT_PATH/lib/ffmpeg/lib/\\\" | head -5
@REM "

@REM echo.
@REM echo 按任意键退出...
@REM pause > nul