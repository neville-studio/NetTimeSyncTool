![Thanks Downloads](https://img.shields.io/github/downloads/neville-studio/nettimesynctool/total?style=flat-square&logo=GitHub)
![Thanks Stars](https://img.shields.io/github/stars/neville-studio/nettimesynctool?style=flat-square&logo=GitHub)
![Thanks Forks](https://img.shields.io/github/forks/neville-studio/nettimesynctool?style=flat-square&logo=GitHub)


If you Like this Reposity, give a star. Thanks for your support.

如果你喜欢这个项目，请给个Star，谢谢您的支持！

# About This Reposity
This is a mini tools, which can sync your time. and view online SNTP Server Time, manage your online NTP Servers.

You can set Online time to Microsoft Windows.

To run This tool, your computer must have installed latest Microsoft Visual C++ 2022 Redistributable.

This reposity is built by Microsoft Visual Studio 2022.

# OS Requirements
   Windows Server 2025、Windows 11、Windows 10、Windows Server 2022、Windows Server 2019、Windows Server 2016、Windows Server 2012 R2、Windows Server 2012、Windows Server 2008 R2 SP1、Windows Server 2008 SP2*、Windows 7 SP1、Windows 8.1、Windows 8、Windows Vista SP2*.

\* Because of the tool: Microsoft Visual C++ 2015-2022 Redistributable, is not supported on Windows Vista SP2 and Windows Server 2008, but the tool can run on Windows Vista SP2. So you can use this tool on Windows Vista SP2. But you need to install Microsoft Visual C++ 2015-2019 Redistributable to run. You can download it from [here](https://my.visualstudio.com).

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
- **Windows Vista Supportion**: at least until Jan. 14, 2026, when Windows Server 2008 Premium Assurance ends of its life.
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
Windows Server 2025、Windows 11、Windows 10、Windows Server 2022、Windows Server 2019、Windows Server 2016、Windows Server 2012 R2、Windows Server 2012、Windows Server 2008 R2 SP1、Windows Server 2008 SP2*、Windows 7 SP1、Windows 8.1、Windows 8、Windows Vista SP2*

\* 由于Microsoft Visual Studio 2015-2022 Redistributable不再支持Windows Vista SP2和Windows Server 2008，但该工具可以在Windows Vista SP2上运行。因此，您可以在Windows Vista SP2上使用此工具。但是，您需要安装Microsoft Visual C++ 2015-2019 Redistributable才能运行。您可以从[这里](https://my.visualstudio.com)下载。
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
- **Windows Vista支持**：至少到2026年1月14日，也就是Windows Server 2008高级保障计划结束支持的时间
- **功能性更新**：至少到2027年1月12日，也就是Windows Server 2016结束支持的时间
- **安全更新和Bug修复**：至少到2036年，第一轮NTP时钟结束时。

# 版权信息
**本软件受到中国和国际版权法保护**

（For China） 中国软件著作权证号：2024SR0209367

**版权所有 2019-2025 Neville Studio**

我们使用MIT License许可您使用此软件代码。详情请查看[这里](./LICENSE)
