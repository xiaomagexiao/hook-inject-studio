//
// Created by MaMa on 2017/4/15.
//

#ifndef READMEMORY_SCANMEMORY_H
#define READMEMORY_SCANMEMORY_H

#include "Common.h"
#include "ModuleMemoryInfo.h"
class ScanMemory {

public:
    ScanMemory() : lastSearchValue(0) {
        moduleName="libsearch.so";

    }

    ~ScanMemory() {}

    void initWithVlaue(unsigned long value);

    void newValue(unsigned value);

    void bigger();

    void equal();

    void smaller();

    void clear();

private:
    unsigned long lastSearchValue;
    string moduleName;
    vector<unsigned long> resultVec;
    vector<ModuleMemoryInfo> moduleVec;

    void printModuleInfo() const;

    void printResult() const;
};


#endif //READMEMORY_SCANMEMORY_H
