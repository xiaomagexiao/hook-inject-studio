
temp_dir="/data/local/tmp"
so_name="libsearch.so"
package=""
pwd=`pwd`
#package="com.example.crash_test"

fun_push_file()
{
    adb push $1 ${temp_dir}/$2
    echo "adb push $1 ${temp_dir}/$2"
    adb shell chmod 777 ${temp_dir}/$2
    echo "adb shell chmod 777 ${temp_dir}/$2"
}

fun_push_file "inject_dex/build/intermediates/cmake/release/obj/armeabi-v7a/libinject-dex.so" "libinject-dex.so"
fun_push_file "inject_dex_target/build/outputs/apk/inject_dex_target-release.apk" "inject.apk"



# copy so
unzip -o "inject_dex_target/build/outputs/apk/inject_dex_target-release.apk" lib/armeabi-v7a/${so_name} -d .
echo "adb push lib/armeabi-v7a/${so_name} /data/data/${package}/lib/${so_name}"
adb shell mount  -o  remount,rw  /system
adb push lib/armeabi-v7a/${so_name} /system/lib/${so_name}
adb shell mount  -o  remount,ro  /system

# execute injector

exe_bin="injector"
cd inject_zygote/.externalNativeBuild/cmake/release/armeabi-v7a

/Users/mama/Library/Android/SDK/cmake/3.6.3155560/bin/ninja
echo `pwd`
adb push ${exe_bin} ${temp_dir}/${exe_bin}
adb shell ${temp_dir}/${exe_bin} "${package}" "/data/local/tmp/libinject-dex.so"

#cd ${pwd}
