@echo off
REM echo 当前脚本路径：%~dp0
REM echo %~dp0..

for %%I in ("%~dp0..") do set "parent_path=%%~fI"
REM echo 父级目录：%parent_path%
set source_path=%~dp0Tools\ffmpeg
set target_path=%parent_path%\Build\Test\tools\ffmpeg
echo 源目录：%source_path%
echo 目标目录：%target_path%
xcopy /s /e /i /y %source_path% %target_path%