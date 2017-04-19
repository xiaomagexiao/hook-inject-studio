## 部分内容记录

#### cout输出到logcat

```
# 方式一、设置属性
adb shell
su
stop
setprop log.redirect-stdio true
start

# 方式二、代码入口重定向到文件
freopen("/sdcard/tmp/loglog.txt", "w", stdout);
```

### 适合不同平台的log
```
	
I use a logger header to print crossplatform logs.

In c++ code just write LOGD("msg"); or LOGE("msg"); and print messages checking the platform.

Try creating a crossplatform log header like:

Logs.h

#       ifdef ANDROID
            // LOGS ANDROID
#           include <android/log.h>
#           define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG,__VA_ARGS__)
#           define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG  , LOG_TAG,__VA_ARGS__)
#           define LOGI(...) __android_log_print(ANDROID_LOG_INFO   , LOG_TAG,__VA_ARGS__)
#           define LOGW(...) __android_log_print(ANDROID_LOG_WARN   , LOG_TAG,__VA_ARGS__)
#           define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , LOG_TAG,__VA_ARGS__)
#           define LOGSIMPLE(...)
#       else
            // LOGS NO ANDROID
#           include <stdio.h>
#           define LOGV(...) printf("  ");printf(__VA_ARGS__); printf("\t -  <%s> \n", LOG_TAG);
#           define LOGD(...) printf("  ");printf(__VA_ARGS__); printf("\t -  <%s> \n", LOG_TAG);
#           define LOGI(...) printf("  ");printf(__VA_ARGS__); printf("\t -  <%s> \n", LOG_TAG);
#           define LOGW(...) printf("  * Warning: "); printf(__VA_ARGS__); printf("\t -  <%s> \n", LOG_TAG);
#           define LOGE(...) printf("  *** Error:  ");printf(__VA_ARGS__); printf("\t -  <%s> \n", LOG_TAG);
#           define LOGSIMPLE(...) printf(" ");printf(__VA_ARGS__);
#       endif // ANDROID
```

### 内存地址记录
```
af0df000-af135000 r-xp 00000000 b3:1c 188348     /data/app/com.example.mama.readmemory-2/lib/arm/libnative-lib.so
af136000-af139000 r--p 00056000 b3:1c 188348     /data/app/com.example.mama.readmemory-2/lib/arm/libnative-lib.so
af139000-af13a000 rw-p 00059000 b3:1c 188348     /data/app/com.example.mama.readmemory-2/lib/arm/libnative-lib.so

pointer: 0xb4b30e80
pointer: 0xb4b38280
pointer: 0xb4b384c0
pointer: 0xb4b38340
pointer: 0xb4b38b20
pointer: 0xb4b38580
pointer: 0xb4b38be0

b4800000-b5000000 rw-p 00000000 00:00 0          [anon:libc_malloc]
# 内存落在libc_malloc区域，堆上
```

### 内容

```
1/ 解析程序的/proc/pid/maps，指定模块及malloc的相关区域内存 ok
2/ 等值、变大、变小扫描 ok
3/ 可以用Android studio的lldb命令窗口对内存地址进行读写断点及打印堆栈了 ok
4/ 不用studio，通过lldb直接附加及调试程序，获取关心内存的读写堆栈。(可以试试用studio附加其他进程)。studio里的项目包名修改成跟要附加的一样的
5/ so文件如何注入到其他进程中来搜索其他进程的内存。
```

### 解决问题花费时间久的地方
- 字符串转整形一直是0，用下面方法解决了。

```
module.startAddress = strtoul(addressVec[0].c_str(), NULL, 16);
module.endAddress = strtoul(addressVec[1].c_str(), NULL, 16);
```

- studio附加其他进程，[参考](https://github.com/dodola/BinderDebug)

### lldb如何用命令行附加

```
04/17 20:53:14: Launching app3
No apk changes detected since last installation, skipping installation of D:\workspace\my-git\DebugTest2\app3\build\outputs\apk\app3-debug.apk
$ adb shell am force-stop com.example.com.app3
$ adb shell am start -n "com.example.com.app3/com.example.com.app3.MainActivity" -a android.intent.action.MAIN -c android.intent.category.LAUNCHER -D
Connecting to com.example.com.app3
Now Launching Native Debug Session
Starting LLDB server: /data/data/com.example.com.app3/lldb/bin/start_lldb_server.sh /data/data/com.example.com.app3/lldb unix-abstract /data/data/com.example.com.app3/lldb/tmp platform-1492433596210.sock "lldb process:gdb-remote packets"
$ adb shell cat /data/local/tmp/lldb-server | run-as com.example.com.app3 sh -c 'cat > /data/data/com.example.com.app3/lldb/bin/lldb-server && chmod 700 /data/data/com.example.com.app3/lldb/bin/lldb-server'
$ adb shell cat /data/local/tmp/start_lldb_server.sh | run-as com.example.com.app3 sh -c 'cat > /data/data/com.example.com.app3/lldb/bin/start_lldb_server.sh && chmod 700 /data/data/com.example.com.app3/lldb/bin/start_lldb_server.sh'
Debugger attached to process 3601
```

### lldb相关命令
