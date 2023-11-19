#include "GlobalNTPResultData.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

GlobalData::GlobalData() {
    string filePath = "NTPServers.ini";
    ifstream file;
    file.open(filePath, ios::in);

    if (!file.is_open())
        return;


    std::string strLine;
    while (getline(file, strLine))
    {

        if (strLine.empty())
            continue;

        servers.push_back(strLine);
    }
}
GlobalData::~GlobalData() {
    string filePath = "NTPServers.ini";
    ofstream file;
    file.open(filePath, ios::trunc);

    if (!file.is_open())
        return;


    for (int i = 0; i < globalData.size(); i++)
    {
        char server[256];
        size_t tsize = 256;
        wcstombs_s(&tsize, server, globalData[i].serverName.c_str(), 256);
        file << server << endl;
    }
}