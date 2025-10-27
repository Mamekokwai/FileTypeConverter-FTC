@echo off
echo 复制 FFmpeg 库文件到项目...

set "BAT_DIR=%~dp0"
echo BAT 文件目录: %BAT_DIR%

REM 创建目录
mkdir "%BAT_DIR%include" 2>nul
mkdir "%BAT_DIR%lib" 2>nul

echo.
echo 步骤1: 复制头文件...

REM 逐个复制 FFmpeg 库的头文件目录
xcopy "C:\msys64\ucrt64\include\libavcodec" "%BAT_DIR%include\libavcodec\" /E /I /Y
xcopy "C:\msys64\ucrt64\include\libavformat" "%BAT_DIR%include\libavformat\" /E /I /Y
xcopy "C:\msys64\ucrt64\include\libavutil" "%BAT_DIR%include\libavutil\" /E /I /Y
xcopy "C:\msys64\ucrt64\include\libavfilter" "%BAT_DIR%include\libavfilter\" /E /I /Y
xcopy "C:\msys64\ucrt64\include\libavdevice" "%BAT_DIR%include\libavdevice\" /E /I /Y
xcopy "C:\msys64\ucrt64\include\libswscale" "%BAT_DIR%include\libswscale\" /E /I /Y
xcopy "C:\msys64\ucrt64\include\libswresample" "%BAT_DIR%include\libswresample\" /E /I /Y

echo.
echo 步骤2: 复制静态库...
xcopy "C:\msys64\ucrt64\lib\libav*.a" "%BAT_DIR%lib\" /Y
xcopy "C:\msys64\ucrt64\lib\libsw*.a" "%BAT_DIR%lib\" /Y

echo.
echo ▲ 复制完成！
echo ▲ 头文件位置: %BAT_DIR%include\
echo ▲ 库文件位置: %BAT_DIR%lib\

echo.
echo 验证复制结果:
dir "%BAT_DIR%include\libavcodec\*.h" /B 2>nul >nul && (
    echo ▲ 头文件复制成功
) || (
    echo ▼ 头文件复制失败
)

dir "%BAT_DIR%lib\*.a" /B 2>nul >nul && (
    echo ▲ 库文件复制成功
) || (
    echo ▼ 库文件复制失败
)

echo.
echo 按任意键退出...
pause > nul