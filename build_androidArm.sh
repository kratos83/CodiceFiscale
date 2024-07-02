#!/bin/sh

export JAVA_HOME=/usr/lib64/jvm/java-8-openjdk
export ANDROID_HOME=/software/Android/Sdk
export ANDROID_SDK=/software/Android/Sdk/
export ANDROID_NDK=/software/android-ndk-r13b
export ANDROID_NDK_TOOLCHAIN_ROOT=/software/android-ndk-r13b/toolchains
export Qt5_host=/usr
export Qt5_android=/opt/Qt5.8.0/5.8/android_armv7

export PATH="/software/Android/Sdk/tools:$PATH"
export PATH="/opt/Qt5.8.0/5.8/android_armv7/bin:$PATH"

DIRECTORY="build"

if [ ! -d "$DIRECTORY" ]; then
    mkdir "$DIRECTORY"
    cd "$DIRECTORY"
else
    cd "$DIRECTORY"
fi

cmake .. -DCMAKE_TOOLCHAIN_FILE=../platforms/android.cmake -Wno-dev
make -j5
make apk_release
