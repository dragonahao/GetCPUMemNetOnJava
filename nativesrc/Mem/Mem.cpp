#include <windows.h>
#include "Mem.h"

JNIEXPORT jlong JNICALL Java_net_caffeineswitch_lib_getcmn_Mem_getTotalMem
	(JNIEnv *env, jobject thisj){
		MEMORYSTATUSEX ms = {sizeof(MEMORYSTATUSEX)};
		GlobalMemoryStatusEx(&ms);

		return ms.ullTotalPhys;
}

JNIEXPORT jlong JNICALL Java_net_caffeineswitch_lib_getcmn_Mem_getFreeMem
	(JNIEnv *, jobject thisj){
		MEMORYSTATUSEX ms = {sizeof(MEMORYSTATUSEX)};
		GlobalMemoryStatusEx(&ms);
		
		return ms.ullAvailPhys;
}

JNIEXPORT jlong JNICALL Java_net_caffeineswitch_lib_getcmn_Mem_getUsedMem
	(JNIEnv *, jobject thisj){
		
		MEMORYSTATUSEX ms = {sizeof(MEMORYSTATUSEX)};
		GlobalMemoryStatusEx(&ms);

		return ms.ullTotalPhys - ms.ullAvailPhys;
}
