# FTC

## 批量文件格式转换工具

一个基于 C/C++ 语言和 FFmpeg 的多功能文件格式转换工具，支持批量处理和交互式操作。

## 项目简介

该项目由本人学习 C 语言和 FFmpeg 过程中所编写.

第一次上传那么完整的github项目, 虽然只是很简单的调用程序, 但是在处理输入和输出方面花了很多心思, 虽然网络上肯定有类似的开源项目, 但是本项目为本人独自完成, 没有参考和借鉴, 受益匪浅, 希望得到大家的支持和鼓励.

改项目的扩展性极强, 可以随意添加其他各种功能, 并且现有的每种功能都单独封装了程序.
release文件夹有经过测试的版本可以直接使用.


## 功能特性

- 🎯 **批量文件格式转换** - 支持多种图片/视频格式转换
- 📁 **智能路径处理** - 自动解析文件路径和扩展名
- 🔄 **交互式操作** - 提供友好的命令行界面
- 🎨 **编码支持** - 完善的 UTF-8 编码处理
- ⚡ **高效处理** - 支持多文件并行处理


## 📁 功能1支持的格式分类

### 1. **图片格式** ✅
```bash
# 常见图片格式
.png, .jpg, .jpeg, .bmp, .gif, .tiff, .tif
.webp, .ico, .svg, .psd, .raw, .cr2, .nef

# 专业图片格式
.pgm, .ppm, .pbm, .pnm, .dpx, .exr, .hdr
```

### 2. **视频格式** ✅
```bash
# 常见视频格式
.mp4, .avi, .mkv, .mov, .wmv, .flv, .webm
.m4v, .3gp, .ogv, .ts, .mts, .m2ts

# 专业视频格式
.mxf, .vob, .asf, .rm, .rmvb, .divx
```

### 3. **音频格式** ✅
```bash
# 常见音频格式
.mp3, .wav, .aac, .flac, .ogg, .m4a, .wma
.opus, .ac3, .aiff, .ape, .tta
```

### 4. **特殊格式** ⚠️
```bash
# 需要额外编解码器
.heic, .heif, .avif    # 现代图片格式
.vp9, .av1, .h265      # 现代视频编码
```

## 使用方法

**提示**: 使用前请确保 FFmpeg 已正确安装并配置到系统 PATH 环境变量中.
**FFmpeg 安装说明**: 具体的 FFmpeg 安装步骤请善用ai和搜索.

### 1. [推荐] 选中并拖入单个或多个文件到release中的程序图标运行 (将自动导入文件路径)
演示动画:
<video controls src="Docs\Picture\272da77e210c3bddba46b9c1212e28e6.gif" title="Title"></video>
### 2. 双击release中的 .exe 文件运行, 目前功能 [2. 输入文件路径](#输入文件路径) 只支持输出导入的文件路径,不能合并到处理队列, 所有暂时无法使用.

### 3. 直接参数传递
```bash
main.exe "file1.png" "file2.jpg" "file3.gif"
```


## 开发计划
<span id="输入文件路径"></span>
- [ ] 完善功能 2. 输入文件路径 ,使路径合并到处理队列
- [ ] 清除现有路径, 避免重新打开程序
- [ ] 封装包含ffmpeg静态库的版本, 供电脑没有ffmpeg的用户使用
- [ ] 开发可视化界面
- [ ] 配置文件支持
- [ ] 日志记录系统
- [ ] CHANGELOG 和 CONTRIBUTION 文档都还是空壳子,后面再补充

## 项目结构

```
project/
├── source/           # 源代码目录
│   ├── main.cpp         # 主程序入口
│   ├── main.h           # 主头文件
│   ├── function1.cpp    # 文件格式转换功能
│   ├── function1.h      # 功能1头文件
│   ├── function2.cpp    # 交互式路径输入功能
│   ├── function2.h      # 功能2头文件
│   ├── file_path_processing.cpp  # 文件路径处理
│   ├── file_path_processing.h    # 路径处理头文件
│   ├── ffmpeg_using.cpp # FFmpeg 封装
│   ├── ffmpeg_using.h   # FFmpeg 头文件
│   ├── animation.cpp    # 控制台动画效果
│   └── animation.h      # 动画头文件
├── output/              # 编译输出目录
│   ├── debug/          # 调试版本
│   └── release/        # 发布版本
└── .vscode/            # VSCode 配置
    ├── launch.json     # 调试配置
    └── tasks.json      # 构建任务
```
## 配置说明

### VSCode 调试配置
项目包含完整的 VSCode 调试配置：
- **调试配置**: `.vscode/launch.json`
- **构建任务**: `.vscode/tasks.json`
- **支持调试和发布两种模式**

需要安装好 VSCode 插件:
- **C/C++**

### 路径配置
[需要手动填写] 请确保以下路径配置正确：
1. **FFmpeg 路径**: 系统 PATH 中需包含 ffmpeg.exe
2. **GDB 路径**: `launch.json` 中的 `miDebuggerPath`
3. **测试文件路径**: `launch.json` 中的示例文件路径
<span id="JSON文件配置"></span>
4. **JSON文件配置**: 
`tasks.json` 中的gcc路径需要替换为你自己的gcc路径，如:"command": "C:/msys64/ucrt64/bin/gcc.exe", 
检查 `launch.json` 中的 `miDebuggerPath` 是否正确,如:"miDebuggerPath": "C:/msys64/ucrt64/bin/gdb.exe",


## 编译说明

### 推荐使用VSCode编译此项目
- **安装VSCode**: 下载并安装 VSCode 最新版本
- **安装插件**: 安装 C/C++ 插件
- **配置项目**: 打开项目文件夹，在VSCode中打开项目，选择菜单栏中的「调试」->「开始调试」，即可编译运行项目![alt text](Docs/Picture/配置项目.png)
如果运行错误，请检查 [JSON文件配置](#JSON文件配置) 是否正确。

### 依赖要求
- **编译器**: GCC (MinGW-w64 或 MSYS2)
- **FFmpeg**: 需要安装 FFmpeg 并添加到系统 PATH
- **系统**: Windows 7+

### 编译命令

- **注意cmd运行路径**: 需要跳转到保存本项目的根目录下, 请在cmd使用cd命令,具体请询问ai

**调试版本:**
```bash
gcc -g -o ./output/debug/main.exe ./source/file_path_processing.cpp ./source/ffmpeg_using.cpp ./source/function1.cpp ./source/main.cpp ./source/animation.cpp ./source/function2.cpp
```

**发布版本:**
```bash
gcc -O2 -s -o ./release/main.exe ./source/file_path_processing.cpp ./source/ffmpeg_using.cpp ./source/function1.cpp ./source/main.cpp ./source/animation.cpp ./source/function2.cpp
```

## API 文档

### 核心函数

#### 文件路径处理
```c
void get_multiple_file_info(int argc, char *argv[], FileInfo *file_info);
void combine_paths_count(FileInfo *file_info, char **output_path_ptr, const char *user_ext, int file_count);
char *LocalToUTF8(const char *local_str);
int split_path_from_user();              // 路径分割处理
```

#### 格式转换
```c
int ffmpeg_convert(const char *input, const char *output);
int file_type_change(int argc, char *argv[], char *newtype);
```

#### 用户交互
```c
void function1(int argc, char *argv[]);  // 格式转换功能
void function2();                        // 交互式路径输入
```

## 数据结构

### FileInfo 结构体
```c
typedef struct {
    char *file_path;            // 完整文件路径
    char *parent_path;          // 父目录路径
    char *filename_without_ext; // 无扩展名文件名
    char *ext;                  // 文件扩展名
} FileInfo;
```

## 注意事项

1. **内存管理**: 所有动态分配的内存都已妥善处理
2. **编码支持**: 自动处理本地编码到 UTF-8 的转换
3. **错误处理**: 包含完善的错误检查和用户提示
4. **缓冲区安全**: 使用安全的字符串函数防止溢出

## 许可证

本项目采用 [许可证名称] - 详见 [LICENSE](LICENSE) 文件

## 联系方式

nywerya - nywerya@gmail.com - https://github.com/Mamekokwai

---



