![Thanks Downloads](https://img.shields.io/github/downloads/neville-studio/nettimesynctool/total?style=flat-square&logo=GitHub)
![Thanks Stars](https://img.shields.io/github/stars/neville-studio/nettimesynctool?style=flat-square&logo=GitHub)
![Thanks Forks](https://img.shields.io/github/forks/neville-studio/nettimesynctool?style=flat-square&logo=GitHub)


If you Like this Reposity, give a star. Thanks for your support.

如果你喜欢这个项目，请给个Star，谢谢您的支持！

# About This Reposity
This is a mini tools, which can sync your time. and view online SNTP Server Time, manage your online NTP Servers.

You can set Online time to Microsoft Windows.

To run This tool, your computer must have installed latest Microsoft Visual C++ v14 Redistributable. 

This reposity is built by Microsoft Visual Studio 2022.

# OS Requirements
   Windows Server 2025、Windows 11、Windows 10、Windows Server 2022、Windows Server 2019、Windows Server 2016、Windows Server 2012 R2\*\*、Windows Server 2012\*\*、Windows Server 2008 R2 SP1\*\*、Windows Server 2008 SP2*、Windows 7 SP1\*\*、Windows 8.1\*\*、Windows 8\*\*、Windows Vista SP2*.

\* Although the tool: Microsoft Visual C++ v14 Redistributable, is not supported on Windows Vista SP2 and Windows Server 2008, the tool still can running on them, just install Microsoft Visual C++ 2015-2019 Redistributable. You can download it from [here](https://my.visualstudio.com).

\*\* Although the tool: Microsoft Visual C++ v14 Redistributable, is not supported on Windows Server 2008 R2, Windows Server 2012, Windows Server 2012 R2, Windows 7, Windows 8.1 and Windows 8. the tool still can running on them, just install Microsoft Visual C++ 2015-2022 Redistributable. You can download it from [here](https://my.visualstudio.com) or [this x86 link](https://aka.ms/vs/17/release/vc_redist.x86.exe),  [this x64 link](https://aka.ms/vs/17/release/vc_redist.x64.exe) and [this arm64 link](https://aka.ms/vs/17/release/vc_redist.arm64.exe).

# Usage
This is window application, you can run it on Windows.

1. To run main application, you can dual click or run it in command line.
  ```Powershell
    ./NetTimeSyncTool.exe
  ```

2. Automatic sync the time. After sync, there is a Message Box to show that whether you have successfully sync the time.
  ```Powershell
    ./NetTimeSyncTool.exe autosync
  ```

3. Sync Time, but not show the Message Box.
  ```Powershell
    ./NetTimeSyncTool.exe autosync /nowarn
  ``` 

# Support Plan
- **Windows Vista, Windows Server 2008 Supportion**: at least until Jan. 14, 2026, when Windows Server 2008 Premium Assurance ends of its life.
- **Windows 7, Windows 8, Windows 8.1, Windows Server 2012, Windows Server 2012 R2 Supportion**: at least until Oct. 14, 2026, when Windows Server 2012 R2 ESU end of its life.
- **Feature Update**: at least until Jan. 12, 2027, when Windows Server 2016 ends of its life.
- **Security Update && Bug Fix**: at least until 2036, when first epoch of NTP ends

# Copyright
**The Software is protected by Chinese and international copyright laws.**

**Copyright (C) 2019-2025 Neville Studio.**

We use MIT License to allow you to using this code. see [license](./LICENSE)


  


# 关于此项目
这是一个小工具，用于同步网络上的NTP服务器上的时钟，并管理你在本地的时钟源

可以在Windows上重新同步您的网络时钟

您的电脑必须安装Microsoft Visual C++ 2022 Redistributable.

此软件基于Microsoft Visual Studio 2022构建

# 操作系统要求
Windows Server 2025、Windows 11、Windows 10、Windows Server 2022、Windows Server 2019、Windows Server 2016、Windows Server 2012 R2\*\*、Windows Server 2012\*\*、Windows Server 2008 R2 SP1\*\*、Windows Server 2008 SP2*、Windows 7 SP1\*\*、Windows 8.1\*\*、Windows 8\*\*、Windows Vista SP2*.

\* 即使Microsoft Visual Studio v14 Redistributable不再支持Windows Vista SP2和Windows Server 2008，但该工具仍可以在Windows Vista SP2上运行。您只需要安装Microsoft Visual C++ 2015-2019 Redistributable才能运行。您可以从[这里](https://my.visualstudio.com)下载。

\*\* 即使 Microsoft Visual C++ v14 Redistributable, 不再支持 Windows Server 2008 R2, Windows Server 2012, Windows Server 2012 R2, Windows 7, Windows 8.1 and Windows 8，但是该工具仍然可以在这些系统上运行，只需要在这些操作系统上安装 Microsoft Visual C++ 2015-2022 Redistributable . 您可以在[此处](https://my.visualstudio.com)搜索下载或使用[该x86链接](https://aka.ms/vs/17/release/vc_redist.x86.exe),  [该x64链接](https://aka.ms/vs/17/release/vc_redist.x64.exe) 和 [该arm64链接](https://aka.ms/vs/17/release/vc_redist.arm64.exe).

# 用法
1. 要运行主应用程序，您可以双击或在命令行中运行它。
  ```Powershell
    ./NetTimeSyncTool.exe
  ```

2. 自动同步时间。同步后，会弹出一个消息框，显示您是否成功同步了时间。
  ```Powershell
    ./NetTimeSyncTool.exe autosync
  ```

3. 同步时间，但不显示消息框。
  ```Powershell
    ./NetTimeSyncTool.exe autosync /nowarn
  ```
# 项目支持计划
- **Windows Vista和Windows Server 2008支持**：至少到2026年1月14日，也就是Windows Server 2008高级保障计划结束支持的时间
- **Windows 7, Windows Server 2008 R2, Windows 8.1, Windows Server 2012 R2支持**：至少到2026年10月14日，也就是Windows Server 2012 R2的ESU结束支持时间
- **功能性更新**：至少到2027年1月12日，也就是Windows Server 2016结束支持的时间
- **安全更新和Bug修复**：至少到2036年，第一轮NTP时钟结束时。

# 版权信息
**本软件受到中国和国际版权法保护**

（For China） 中国软件著作权证号：2024SR0209367

**版权所有 2019-2025 Neville Studio**

我们使用MIT License许可您使用此软件代码。详情请查看[这里](./LICENSE)
