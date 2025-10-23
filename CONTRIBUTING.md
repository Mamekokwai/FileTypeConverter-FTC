# 📝 贡献指南

感谢你考虑为这个项目做出贡献！以下是参与贡献的指南。

## 🛠️ 开发环境设置

1. **克隆仓库**
   ```bash
   git clone https://github.com/你的用户名/你的项目名.git
   cd 你的项目名
   ```

2. **设置开发环境**
   - 安装 MSYS2
   - 安装 FFmpeg: `pacman -S mingw-w64-ucrt-x86_64-ffmpeg`
   - 安装编译工具: `pacman -S mingw-w64-ucrt-x86_64-toolchain`

3. **编译测试**
   ```bash
   gcc -g -o output/debug/main.exe sourcecode/*.cpp
   ```

## 📋 贡献流程

### 报告问题
- 使用 [Issues](../../issues) 页面报告 bug 或提出功能建议
- 提供详细的重现步骤和环境信息

### 提交代码
1. Fork 本仓库
2. 创建功能分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 开启 Pull Request

## 📝 代码规范

### C/C++ 代码风格
```c
// 使用有意义的变量名
int file_count = 0;  // ✅ 好的
int fc = 0;          // ❌ 避免

// 函数注释使用文档格式
/**
 * @brief 文件格式转换函数
 * @param input 输入文件路径
 * @param output 输出文件路径
 * @return 转换结果 (0=成功)
 */
int convert_file(const char* input, const char* output);
```

### 提交信息规范
- feat: 新功能
- fix: 修复 bug
- docs: 文档更新
- style: 代码格式调整
- refactor: 代码重构
- test: 测试相关

## 🧪 测试要求

提交代码前请确保：
- [ ] 代码可以正常编译
- [ ] 通过基本功能测试
- [ ] 不影响现有功能
- [ ] 更新相关文档

## ❓ 需要帮助？

如果你在贡献过程中遇到问题：
1. 查看 [Issues](../../issues) 是否有类似问题
2. 查看项目文档
3. 联系维护者


## 🏗️ 项目架构

### 核心模块
- `file_path_processing` - 文件路径处理
- `ffmpeg_using` - FFmpeg 功能封装  
- `function1` - 格式转换功能
- `function2` - 交互式输入功能

### 添加新功能指南
1. 在 `sourcecode/` 目录创建新的 `.cpp` 和 `.h` 文件
2. 在 `main.h` 中声明函数
3. 在 `main.cpp` 的菜单中添加选项
4. 更新编译脚本

## 🔧 调试技巧

### VSCode 调试
项目已配置完整的 VSCode 调试环境：
- F5: 启动调试
- Ctrl+Shift+B: 编译项目

### 常见问题
```bash
# 如果遇到链接错误，检查所有源文件是否都加入编译
gcc -o main.exe sourcecode/*.cpp

# 如果 FFmpeg 找不到，检查环境变量
echo $PATH
```

---

