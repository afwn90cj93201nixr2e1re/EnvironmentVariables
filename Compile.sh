g++ -DMODULE_VERSION_A=\"$1\" -DRelease -O3 -g0 -m32 -s -shared -msse3 -std=c++14 -mtune=generic -static-libstdc++ \
	-Wno-pointer-arith -Wno-conversion-null -Wno-write-strings -Wno-attributes \
	-fPIC -fomit-frame-pointer -fno-builtin -fno-rtti -fno-exceptions \
	-fomit-frame-pointer -fvisibility=hidden -fvisibility-inlines-hidden -flto \
	-I. -Isdk/hlsdk/common -Isdk/hlsdk/dlls -Isdk/hlsdk/engine -Isdk/hlsdk/pm_shared -Isdk/hlsdk/public -Isdk/metamod  \
	main.cpp amxxmodule.cpp \
	-Wl,--version-script=version_script.lds -Wl,--gc-sections -lrt -ldl -lm \
	-o enviromentvariables_amxx_i386.so
