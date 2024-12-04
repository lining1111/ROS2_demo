//
// Created by lining on 12/4/24.
//

#include "systemStatus.h"
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <dirent.h>
#include <sys/stat.h>
#include <cerrno>
#include <iostream>
#include <sys/statfs.h>
#include <sys/utsname.h>

string getuname() {
    string uname_;
    utsname uts;
    if (uname(&uts) == 0) {
        uname_ = string(uts.sysname);
    }

    return uname_;
}


void getNetInfos(vector<NetInfo> &netInfos) {
    std::ifstream infile("/proc/net/dev");
    std::string line;
    std::getline(infile, line); // 忽略第一行（标题行）
    std::getline(infile,line);
    while (std::getline(infile, line)) {
        NetInfo item;

        std::istringstream iss(line);
        std::string interface_name;
        std::vector<std::string> data;
        std::getline(iss, interface_name, ':'); // 接口名称
        interface_name = interface_name.substr(0, interface_name.size() - 1); // 去除尾部空格
        std::string stats;
        while (std::getline(iss, stats, ' ')) { // 读取其余数据
            if (!stats.empty()) {
                data.push_back(stats);
            }
        }
        // 输出接口名称和统计数据
//        std::cout << "Interface: " << interface_name << std::endl;
        item.interfaceName = interface_name;
        char *endptr;
//        std::cout << "Receive bytes: " << data[0] << std::endl;
        item.receiveBytes = strtoll(data[0].c_str(), &endptr, 10);
//        std::cout << "Receive packets: " << data[1] << std::endl;
        item.receivePackets = strtoll(data[1].c_str(), &endptr, 10);
//        std::cout << "Receive errors: " << data[2] << std::endl;
        item.receiveErrors = strtoll(data[2].c_str(), &endptr, 10);
//        std::cout << "Receive drops: " << data[3] << std::endl;
        item.receiveDrops = strtoll(data[3].c_str(), &endptr, 10);
//        std::cout << "Receive fifo: " << data[4] << std::endl;
        item.receiveFifo = strtoll(data[4].c_str(), &endptr, 10);
//        std::cout << "Receive frame: " << data[5] << std::endl;
        item.receiveFrame = strtoll(data[5].c_str(), &endptr, 10);
//        std::cout << "Receive compressed: " << data[6] << std::endl;
        item.receiveCompressed = strtoll(data[6].c_str(), &endptr, 10);
//        std::cout << "Receive multicast: " << data[7] << std::endl;
        item.receiveMulticast = strtoll(data[7].c_str(), &endptr, 10);
//        std::cout << "Transmit bytes: " << data[8] << std::endl;
        item.transmitBytes = strtoll(data[8].c_str(), &endptr, 10);
//        std::cout << "Transmit packets: " << data[9] << std::endl;
        item.transmitPackets = strtoll(data[9].c_str(), &endptr, 10);
//        std::cout << "Transmit errors: " << data[10] << std::endl;
        item.transmitErrors = strtoll(data[10].c_str(), &endptr, 10);
//        std::cout << "Transmit drops: " << data[11] << std::endl;
        item.transmitDrops = strtoll(data[11].c_str(), &endptr, 10);
//        std::cout << "Transmit fifo: " << data[12] << std::endl;
        item.transmitFifo = strtoll(data[12].c_str(), &endptr, 10);
//        std::cout << "Transmit colls: " << data[13] << std::endl;
        item.transmitColls = strtoll(data[13].c_str(), &endptr, 10);
//        std::cout << "Transmit carrier: " << data[14] << std::endl;
        item.transmitCarrier = strtoll(data[14].c_str(), &endptr, 10);
//        std::cout << "Transmit compressed: " << data[15] << std::endl;
        item.transmitCompressed = strtoll(data[15].c_str(), &endptr, 10);
    }
}


int runCmd(const std::string &command, std::string *output, bool redirect_stderr) {
    const auto &cmd = redirect_stderr ? command + " 2>&1" : command;
    auto pipe = popen(cmd.c_str(), "r");
    if (!pipe) {
        //记录日志
        return errno == 0 ? -1 : errno;
    }
    {
        char buffer[1024] = {0};
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            if (output) {
                output->append(buffer);
            }
//            printf("%s",buffer);
        }
    }
    return pclose(pipe);
}

void Trim(string &str, char trim) {
    std::string::iterator end_pos = std::remove(str.begin(), str.end(), trim);
    str.erase(end_pos, str.end());
}

bool startsWith(const std::string str, const std::string prefix) {
    return (str.rfind(prefix, 0) == 0);
}

bool endsWith(const std::string str, const std::string suffix) {
    if (suffix.length() > str.length()) {
        return false;
    }

    return (str.rfind(suffix) == (str.length() - suffix.length()));
}


double cpuUtilizationRatio() {
    int ret = 0;
    string cmd = R"(top -bn1 |sed -n '3p' | awk -F 'ni,' '{print $2}' |cut -d. -f1 | sed 's/ //g')";
    std::string strRes;
    if (runCmd(cmd, &strRes) == 0) {
        Trim(strRes, ' ');
        ret = 100.0 - atof(strRes.c_str());
    }
    return ret;
}

double cpuTemperature() {
    FILE *fp = nullptr;
    int temp = 0;
    fp = fopen("/sys/devices/virtual/thermal/thermal_zone0/temp", "r");
    if (fp == nullptr) {
        std::cerr << "CpuTemperature fail" << std::endl;
        return 0;
    }

    fscanf(fp, "%d", &temp);
    fclose(fp);
    return (double) temp / 1000;
}

int memoryInfo(float &total, float &free) {
    int mem_free = -1;//空闲的内存，=总内存-使用了的内存
    int mem_total = -1; //当前系统可用总内存
    int mem_buffers = -1;//缓存区的内存大小
    int mem_cached = -1;//缓存区的内存大小
    char name[20];

    FILE *fp;
    char buf1[128], buf2[128], buf3[128], buf4[128], buf5[128];
    int buff_len = 128;
    fp = fopen("/proc/meminfo", "r");
    if (fp == nullptr) {
        std::cerr << "GetSysMemInfo() error! file not exist" << std::endl;
        return -1;
    }
    if (nullptr == fgets(buf1, buff_len, fp) ||
        nullptr == fgets(buf2, buff_len, fp) ||
        nullptr == fgets(buf3, buff_len, fp) ||
        nullptr == fgets(buf4, buff_len, fp) ||
        nullptr == fgets(buf5, buff_len, fp)) {
        std::cerr << "GetSysMemInfo() error! fail to read!" << std::endl;
        fclose(fp);
        return -1;
    }
    fclose(fp);
    sscanf(buf1, "%s%d", name, &mem_total);
    sscanf(buf2, "%s%d", name, &mem_free);
    sscanf(buf4, "%s%d", name, &mem_buffers);
    sscanf(buf5, "%s%d", name, &mem_cached);

    total = (double) mem_total / 1024.0;
    free = (double) mem_free / 1024.0;

    return 0;
}

int dirInfo(const string &dir, int &total, int &free) {
    struct statfs diskInfo;
    // 设备挂载的节点
    if (statfs(dir.c_str(), &diskInfo) == 0) {
        uint64_t blocksize = diskInfo.f_bsize;                   // 每一个block里包含的字节数
        uint64_t totalsize = blocksize * diskInfo.f_blocks;      // 总的字节数，f_blocks为block的数目
        uint64_t freeDisk = diskInfo.f_bfree * blocksize;       // 剩余空间的大小
        uint64_t availableDisk = diskInfo.f_bavail * blocksize; // 可用空间大小
        total = (double) totalsize / (1024.0 * 1024.0);
        free = (double) freeDisk / (1024.0 * 1024.0);
        return 0;
    } else {
        total = 0;
        free = 0;
        return -1;
    }
}

