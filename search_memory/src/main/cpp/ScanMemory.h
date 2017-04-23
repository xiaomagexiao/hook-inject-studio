//
// Created by MaMa on 2017/4/15.
//

#ifndef READMEMORY_SCANMEMORY_H
#define READMEMORY_SCANMEMORY_H

#include "Common.h"
#include "ModuleMemoryInfo.h"

class ScanMemory {

public:
    ScanMemory() : lastSearchValue(0) {}

    ~ScanMemory() {}

    void initWithVlaue(unsigned long value);

    void newValue(unsigned value);

    void bigger();

    void equal();

    void smaller();

    void clear();

    void printResult() const;

private:
    unsigned long lastSearchValue;
    vector<unsigned long> resultVec;

    vector<ModuleMemoryInfo> moduleVec;

    void printModuleInfo() const;
};


#endif //READMEMORY_SCANMEMORY_H
