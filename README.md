# Blueerrs
It's a just parody project just for education or fun.  It makes your PC blue and blue:)
Chinese 中文
⚠️ 这是一个严格用于教育和研究目的的概念验证项目。请谨慎使用。⚠️

重要警告与免责声明
本项目旨在为安全研究人员、软件开发人员和计算机科学学生演示 Windows 操作系统内部的一些底层机制，包括：

进程调试权限 (SeDebugPrivilege) 的启用

文件持久化技术

系统关键进程的管理

请勿将此代码用于任何恶意或非法活动。滥用此代码可能导致：

您的 Windows 系统立即崩溃和数据丢失。

对他人系统造成破坏，这可能构成违法行为。

违反您所在地区的计算机安全法规。

作者不对任何滥用此代码的行为负责。在非隔离的测试环境（如虚拟机）之外运行此代码是极其危险和不负责任的。

项目目的
此代码库是一个教学工具，用于展示和理解以下 Windows API 和安全概念：

权限提升：如何通过 AdjustTokenPrivileges 为进程启用调试权限，这是与系统进程交互的关键步骤。

持久化技术：演示了一种常见的程序持久化方法（将自身复制到启动目录）。

系统进程的脆弱性：展示了终止关键系统进程 (wininit.exe) 所带来的灾难性后果，从而强调系统防护的重要性。

此项目适用于蓝队（防御方）研究攻击者策略，以及开发者深入理解 Windows 系统安全机制。

技术细节
代码功能分解
enableDebugPrivilege(): 获取当前进程的令牌并启用 SE_DEBUG_NAME 权限。此权限允许该进程调试其他用户上下文中的进程，是操作系统级别的强大权限。

copy(): 一个简单的文件复制函数，使用 C++ 文件流将源文件二进制内容写入目标路径。

getPath(): 使用 GetFullPathNameA 获取当前可执行文件的绝对路径。

main() 函数:

调用 enableDebugPrivilege()。

定义系统启动目录的路径。

获取当前可执行文件的路径并将其复制到启动目录（实现持久化）。

使用 system() 命令调用 taskkill 强制终止 wininit.exe 进程。

终止 wininit.exe 的后果
wininit.exe 是 Windows 启动初始化进程。它是用户模式的核心组件，负责启动其他关键服务，如 lsass.exe（本地安全认证子系统服务）和 services.exe（服务控制管理器）。强制终止此进程会导致系统瞬间失去关键功能，从而触发蓝屏错误 (CRITICAL_PROCESS_DIED) 并立即重启。

如何安全地运行和研究（在虚拟环境中）
强烈建议仅在完全隔离的环境中进行测试。

准备虚拟机：使用 VMware、VirtualBox 或 Hyper-V 安装一个 Windows 10/11 虚拟机。确保虚拟机网络设置为“主机模式”或“断开连接”，以免造成任何外部影响。

安装开发环境：在虚拟机中安装 Visual Studio 或 MinGW 等编译环境。

运行与研究：运行编译好的程序，观察系统行为。完成后，恢复到之前的快照。

许可证
本项目采用 MIT 许可证。

Copyright (c) 2023 [聪明的mnb先生]
