//
// Created by MaMa on 2017/4/15.
//

#ifndef READMEMORY_MODULEMEMORYINFO_H
#define READMEMORY_MODULEMEMORYINFO_H

#include "Common.h"

class ModuleMemoryInfo {
public:
    ModuleMemoryInfo() : startAddress(0), endAddress(0) {}

    unsigned long startAddress;
    unsigned long endAddress;
    string attr;
    string name;
};


#endif //READMEMORY_MODULEMEMORYINFO_H
