//
// Created by MaMa on 2017/4/15.
//

#ifndef READMEMORY_STACKCALLBACK_H
#define READMEMORY_STACKCALLBACK_H

#include "Common.h"

class StackCallBack {
public:
    static void backtraceToLogcat();

private:
    static void dumpBacktrace(std::ostream &os, void **buffer, size_t count);

    static size_t captureBacktrace(void **buffer, size_t max);
};


#endif //READMEMORY_STACKCALLBACK_H
