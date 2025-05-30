/*
 * @Author: Neville Studio <2840772674@qq.com>
 * @Date: 2024-11-29 22:29:42
 * @Function: Storage logics.
 */

#include "GlobalNTPResultData.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#include <ShlObj.h>
std::string getWritableFilename();
bool isMsixEnvironment();
#endif

// 获取可写的NTP服务器文件路径
std::string getWritableFilename() {
    std::string filename = "NTPServers.ini";
#ifdef _WIN32
    char path[MAX_PATH] = { 0 };
    if (SUCCEEDED(SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path))) {
        std::string dirPath = std::string(path) + "\\NevilleStudio\\NetTimesyncTool";
        std::filesystem::create_directories(dirPath);
        return dirPath + "\\" + filename;
    }
#endif // _WIN32
    return filename;
}

// 读取服务器列表
std::vector<std::string> readServersFromFile() {
    std::vector<std::string> servers;
    std::string filePath = getWritableFilename();
    std::ifstream file(filePath, std::ios::in);
    if (!file.is_open())
        return servers;
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty())
            servers.push_back(line);
    }
    file.close();
    return servers;
}

// 写入服务器列表
void writeServersToFile(const std::vector<std::string>& serverNames) {
    std::string filePath = getWritableFilename();
    std::ofstream file(filePath, std::ios::out | std::ios::trunc);
    if (!file.is_open())
        return;
    for (const auto& name : serverNames) {
        file << name << std::endl;
    }
    file.close();
}

GlobalData::GlobalData() {
    servers = readServersFromFile();
}

GlobalData::~GlobalData() {
    std::vector<std::string> serverNames;
    for (const auto& ntp : globalData) {
        // 只导出 serverName 字段
        char server[256] = {0};
        size_t tsize = 256;
        wcstombs_s(&tsize, server, ntp.serverName.c_str(), 256);
        serverNames.push_back(server);
    }
    writeServersToFile(serverNames);
}

#ifdef _WIN32
// 判断当前是否运行在 MSIX 环境下
bool isMsixEnvironment() {
    char* packageFamily = nullptr;
    size_t len = 0;
    if (_dupenv_s(&packageFamily, &len, "PACKAGE_FAMILY_NAME") == 0 && packageFamily != nullptr) {
        free(packageFamily);
        return true;
    }
    return false;
}

// 获取 MSIX 可写路径

#endif
