
temp_dir="/data/local/tmp"

fun_push_file()
{
    adb push $1 ${temp_dir}/$2
    echo "adb push $1 ${temp_dir}/$2"
    adb shell chmod 777 ${temp_dir}/$2
    echo "adb shell chmod 777 ${temp_dir}/$2"
}

fun_push_file "inject_dex/build/intermediates/cmake/release/obj/armeabi-v7a/libinject-dex.so" "libinject-dex.so"
fun_push_file "inject_dex_target/build/outputs/apk/inject_dex_target-debug.apk" "inject_dex_target-debug.apk"
adb shell ${temp_dir}/android_zygote_injection-master
