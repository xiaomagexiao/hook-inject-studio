
temp_dir="/data/local/tmp"

fun_push_file()
{
    adb push $1 ${temp_dir}/$2
    echo "adb push $1 ${temp_dir}/$2"
    adb shell chmod 777 ${temp_dir}/$2
    echo "adb shell chmod 777 ${temp_dir}/$2"
}

fun_push_file "inject_dex/build/intermediates/cmake/release/obj/armeabi-v7a/libinject-dex.so" "libinject-dex.so"
rm -rf "inject_dex_target/build/outputs/apk/unzip"
# unzip "inject_dex_target/build/outputs/apk/inject_dex_target-release.apk" -d "inject_dex_target/build/outputs/apk/unzip"
fun_push_file "inject_dex_target/build/outputs/apk/inject_dex_target-release.apk" "inject.dex"
# fun_push_file "/Users/mama/GitHub/hook-inject/android_dex_injection-master/jni/dex-target-model.apk" "inject_dex_target-debug.apk"

# fun_push_file "inject_dex_target/build/outputs/apk/unzip/classes.dex" "inject.dex"

adb shell ${temp_dir}/android_zygote_injection-master
