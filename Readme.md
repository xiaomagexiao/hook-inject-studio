## 部分内容记录

#### 注入debug模式下的apk，一直提示类找不到，分析后确实没有那个类文件。
- 配置好签名，用release版本的运行。




#### 步骤
- 加载so ok
- 注册广播 ok
- 通过广播控制流程 ok
- 控制监控的模块


#### 测试命令

```
adb shell am broadcast -a inject.cmd  --es cmd  "sdfdsfdsfd"


 
cd /Users/mama/GitHub/hook-inject-studio/read_memory/.externalNativeBuild/cmake/debug/armeabi-v7a
/Users/mama/Library/Android/SDK/cmake/3.6.3155560/bin/ninja

# release里面的才是对的上的，可以找到问题
arm-linux-androideabi-addr2line -C -f -e /Users/mama/GitHub/hook-inject-studio/read_memory/build/intermediates/cmake/release/obj/armeabi-v7a/libsearch.so 0xce02 

# 查看cout的输出
tail -f /data/local/tmp/loglog.txt

```


#### 原来依赖的module里一直只生成release的lib，把主的module改成支持c++项目后就可以生成debug的了。