//
// Created by MaMa on 2017/4/15.
//

#include "Test.h"

#include "Common.h"
#include "HackEngine.h"
#include "Util.h"

void Test::testCreateFolder() {
    Util::createFolder(string("/data/data/com.example.mama.readmemory/ssss"));
}

void Test::testGetMaps() {
    int pid = getpid();
    cout << "pid = " << pid << endl;
    vector<string> mapVec;
    HackEngine::getInstance()->getProcMaps(pid, mapVec);
    for (string str:mapVec) {
        cout << str << endl;
    }
}

void Test::testGetMapsWithFilter() {
    int pid = getpid();
    vector<string> mapVecFilter;
    vector<string> mapVecFilterTag;
    mapVecFilterTag.push_back("libc_malloc");
    mapVecFilterTag.push_back("libnative-lib.so");
    HackEngine::getInstance()->getProcMapsWithFilter(pid, mapVecFilter, mapVecFilterTag);
    for (string str:mapVecFilter) {
        cout << str << endl;
    }
}

void Test::testGetMapsInfoWithFilter() {
    int pid = getpid();
    vector<string> mapVecFilterTag;
    mapVecFilterTag.push_back("libc_malloc");
    mapVecFilterTag.push_back("libnative-lib.so");
    vector<ModuleMemoryInfo> moduleVec;

    HackEngine::getInstance()->getProcMapsModuleWithFilter(pid, moduleVec, mapVecFilterTag);

    for (ModuleMemoryInfo module:moduleVec) {
        cout << "start: " << hex << module.startAddress
             << ", end: " << hex << module.endAddress
             << ", attr: " << module.attr
             << ", name: " << module.name << endl;
    }
}

void Test::testScanMemory() {
    char *p = (char *) Util::pe_malloc(88);
    memset(p, 'c', 88);
    int *temp = (int *) p;
    printf("pointer: %p\n", p);
    int value = 80;
    vector<unsigned int> vec;
    // 速度还是很快的，需要获取模块地址，不然可能有些地址不能操作
    for (unsigned int i = 0; i < 0x8000 / 4; i++) {
        // cout << "value: " << hex << * (temp + i) << endl;
        if (*(temp + i) == value) {
            vec.push_back(i);
//            if(vec.size()>500){
//                break;
//            }
        }
    }
}
