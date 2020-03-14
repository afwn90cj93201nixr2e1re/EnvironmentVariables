gcc -DMODULE_VERSION_A=\"$1\" -DRelease -O3 -g3 -m32 -shared -msse3 -std=c++14 -mtune=generic \
	-Wno-pointer-arith -Wno-conversion-null -Wno-write-strings -Wno-attributes \
	-fPIC -fomit-frame-pointer -fno-builtin -fno-rtti -fno-exceptions \
	-fomit-frame-pointer -fvisibility=hidden -fvisibility-inlines-hidden -flto \
	-I. -Isdk/metamod  \
	main.cpp amxxmodule.cpp \
	-Wl,--version-script=version_script.lds -Wl,--gc-sections \
	-o environmentvariables_amxx_i386.so
