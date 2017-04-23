//
// Created by MaMa on 2017/4/15.
//

#include "HackEngine.h"
#include <mutex>
#include "Util.h"

HackEngine *HackEngine::instance = NULL;

int HackEngine::getProcMaps(int pid, vector<string> &vec) {
    char buf[50] = {0};
    sprintf(buf, "cat /proc/%d/maps", pid);
    Util::executeCmdWithResult(string(buf), vec);
    return 0;
}

HackEngine::HackEngine() {

}

HackEngine::~HackEngine() {

}

HackEngine *HackEngine::getInstance() {
    if (!instance) {
        std::mutex mt;
        mt.lock();
        if (!instance) {
            instance = new HackEngine();
        }
        mt.unlock();
    }
    return instance;
}

void HackEngine::getProcMapsWithFilter(int pid, vector<string> &resultVec,
                                       const vector<string> &filterTagVec) {
    vector<string> tempVec;
    getProcMaps(pid, tempVec);
    for (string str:tempVec) {
        bool find = false;
        for (string inner:filterTagVec) {
            if (str.find(inner) != string::npos) {
                find = true;
                break;
            }
        }
        if (find) {
            resultVec.push_back(str);
        }
    }
}


void HackEngine::getProcMapsModuleWithFilter(int pid, vector<ModuleMemoryInfo> &resultVec,
                                             const vector<string> &filterTagVec) {
    vector<string> tempVec;
    getProcMapsWithFilter(pid, tempVec, filterTagVec);
    for (string str:tempVec) {
        vector<string> splitVec = Util::string_split(str, " ");
        ModuleMemoryInfo module;
        //address是第一位
        string address = splitVec[0];
        vector<string> addressVec = Util::string_split(address, "-");
        module.startAddress = strtoul(addressVec[0].c_str(), NULL, 16);
        module.endAddress = strtoul(addressVec[1].c_str(), NULL, 16);
        //name是最后一位
        module.name = splitVec[splitVec.size() - 1];
        module.attr = splitVec[1];
        resultVec.push_back(module);
    }
}
