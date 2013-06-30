#include "CPU.h"
#include <pdh.h>

//Link "Pdh.lib"

PDH_HQUERY              hQuery = NULL;
PDH_HCOUNTER            hCounter = NULL;
PDH_FMT_COUNTERVALUE    fntValue;

bool loadPdh(){
	if ( PdhOpenQuery(NULL,0,&hQuery) == ERROR_SUCCESS ){
		PdhAddCounter( hQuery, TEXT("\\Processor(_Total)\\% Processor Time"), 0, &hCounter );
		PdhCollectQueryData( hQuery );
		return true;
	}
	return false;
}

void unloadPdh(){
	hQuery = NULL;
	hCounter = NULL;
}

JNIEXPORT jdouble JNICALL Java_net_caffeineswitch_lib_getcmn_CPU_getCPUUsage
  (JNIEnv *env, jobject thisj){
		if(hQuery == NULL){
			if(!loadPdh()){
				unloadPdh();
				return -1;
			}
		}
		PdhCollectQueryData( hQuery );
		PdhGetFormattedCounterValue( hCounter, PDH_FMT_DOUBLE, NULL, &fntValue );
		return fntValue.doubleValue;
}
