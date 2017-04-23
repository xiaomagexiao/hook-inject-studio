//
// Created by MaMa on 2017/4/15.
//

#ifndef READMEMORY_HACKENGINE_H
#define READMEMORY_HACKENGINE_H

#include "Common.h"
#include "ModuleMemoryInfo.h"
class HackEngine {

public:
    HackEngine();

    ~ HackEngine();

    static HackEngine *getInstance();

private:
    static HackEngine *instance;

public:
    int getProcMaps(int pid, vector<string> &vec);

    void getProcMapsWithFilter(int pid, vector<string> &resultVec,
                               const vector<string> &filterTagVec);

    void
    getProcMapsModuleWithFilter(int pid, vector<ModuleMemoryInfo> &resultVec,
                                const vector<string> &filterTagVec);
};


#endif //READMEMORY_HACKENGINE_H
