@echo off
echo ���� FFmpeg ���ļ�����Ŀ...

set "BAT_DIR=%~dp0"
echo BAT �ļ�Ŀ¼: %BAT_DIR%

REM ����Ŀ¼
mkdir "%BAT_DIR%include" 2>nul
mkdir "%BAT_DIR%lib" 2>nul

echo.
echo ����1: ����ͷ�ļ�...

REM ������� FFmpeg ���ͷ�ļ�Ŀ¼
xcopy "C:\msys64\ucrt64\include\libavcodec" "%BAT_DIR%include\libavcodec\" /E /I /Y
xcopy "C:\msys64\ucrt64\include\libavformat" "%BAT_DIR%include\libavformat\" /E /I /Y
xcopy "C:\msys64\ucrt64\include\libavutil" "%BAT_DIR%include\libavutil\" /E /I /Y
xcopy "C:\msys64\ucrt64\include\libavfilter" "%BAT_DIR%include\libavfilter\" /E /I /Y
xcopy "C:\msys64\ucrt64\include\libavdevice" "%BAT_DIR%include\libavdevice\" /E /I /Y
xcopy "C:\msys64\ucrt64\include\libswscale" "%BAT_DIR%include\libswscale\" /E /I /Y
xcopy "C:\msys64\ucrt64\include\libswresample" "%BAT_DIR%include\libswresample\" /E /I /Y

echo.
echo ����2: ���ƾ�̬��...
xcopy "C:\msys64\ucrt64\lib\libav*.a" "%BAT_DIR%lib\" /Y
xcopy "C:\msys64\ucrt64\lib\libsw*.a" "%BAT_DIR%lib\" /Y

echo.
echo �� ������ɣ�
echo �� ͷ�ļ�λ��: %BAT_DIR%include\
echo �� ���ļ�λ��: %BAT_DIR%lib\

echo.
echo ��֤���ƽ��:
dir "%BAT_DIR%include\libavcodec\*.h" /B 2>nul >nul && (
    echo �� ͷ�ļ����Ƴɹ�
) || (
    echo �� ͷ�ļ�����ʧ��
)

dir "%BAT_DIR%lib\*.a" /B 2>nul >nul && (
    echo �� ���ļ����Ƴɹ�
) || (
    echo �� ���ļ�����ʧ��
)

echo.
echo ��������˳�...
pause > nul