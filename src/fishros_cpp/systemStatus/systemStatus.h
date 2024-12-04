//
// Created by lining on 12/4/24.
//

#ifndef SYSTEMSTATUS_H
#define SYSTEMSTATUS_H

#include <string>
#include <vector>

using namespace std;

string getuname();

//网卡情况
typedef struct {
    string interfaceName;//网卡名称
    uint64_t receiveBytes;
    uint64_t receivePackets;
    uint64_t receiveErrors;
    uint64_t receiveDrops;
    uint64_t receiveFifo;
    uint64_t receiveFrame;
    uint64_t receiveCompressed;
    uint64_t receiveMulticast;
    uint64_t transmitBytes;
    uint64_t transmitPackets;
    uint64_t transmitErrors;
    uint64_t transmitDrops;
    uint64_t transmitFifo;
    uint64_t transmitColls;
    uint64_t transmitCarrier;
    uint64_t transmitCompressed;
}NetInfo;

void getNetInfos(vector<NetInfo> &netInfos);

int runCmd(const std::string &command, std::string *output = nullptr,
           bool redirect_stderr = false);

void Trim(string &str, char trim);

bool startsWith(const std::string str, const std::string prefix);

bool endsWith(const std::string str, const std::string suffix);

double cpuUtilizationRatio();

double cpuTemperature();

int memoryInfo(float &total, float &free);

int dirInfo(const string& dir, int &total, int &free);



#endif //SYSTEMSTATUS_H
