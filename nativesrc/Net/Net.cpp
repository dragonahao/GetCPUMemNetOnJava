#include "Net.h"
#include <winsock2.h>
#include <iphlpapi.h>

//Link Iphlpapi.lib

DWORD i;
PMIB_IFTABLE ifTable = NULL;
MIB_IFROW MibIfRow;
DWORD dwSize = 0;
DWORD dwRetVal = 0;

int StrLength(BYTE *b){
	int n = 0;
	while(*b++ != NULL){
		n++;
	}
	return n;
}


void ConvSJistoUtf8( BYTE* pSource, BYTE* pDist, int* pSize ){
	*pSize = 0;

	const int nSize = ::MultiByteToWideChar( CP_ACP, 0, (LPCSTR)
	pSource, -1, NULL, 0 );

	BYTE* buffUtf16 = new BYTE[ nSize * 2 + 2 ];
	::MultiByteToWideChar( CP_ACP, 0, (LPCSTR)pSource, -1, (LPWSTR)
	buffUtf16, nSize );

	const int nSizeUtf8 = ::WideCharToMultiByte( CP_UTF8, 0, (LPCWSTR)
	buffUtf16, -1, NULL, 0, NULL, NULL );
	if( !pDist ){
		*pSize = nSizeUtf8;
		delete buffUtf16;
		return;
	}

	BYTE* buffUtf8 = new BYTE[ nSizeUtf8 * 2 ];
	ZeroMemory( buffUtf8, nSizeUtf8 * 2 );
	::WideCharToMultiByte( CP_UTF8, 0, (LPCWSTR)buffUtf16, -1, (LPSTR)
	buffUtf8, nSizeUtf8, NULL, NULL );

	*pSize = lstrlen((WCHAR *)buffUtf8) * 2;
	memcpy( pDist, buffUtf8, *pSize );

	delete buffUtf16;
	delete buffUtf8;
}

JNIEXPORT void JNICALL Java_net_caffeineswitch_lib_getcmn_Net_initNetIntf
	(JNIEnv *env, jobject thisj){
	if (GetIfTable(NULL, &dwSize, 0) == ERROR_INSUFFICIENT_BUFFER) {
		ifTable = (MIB_IFTABLE *) malloc (dwSize);
	}
}


JNIEXPORT jint JNICALL Java_net_caffeineswitch_lib_getcmn_Net_getNetIntfNum
	(JNIEnv *env, jobject thisj){
		if (ifTable != NULL && (dwRetVal = GetIfTable(ifTable, &dwSize, 0)) == NO_ERROR) {
			return (int)ifTable->dwNumEntries;
		}else{
			return -1;
		}
}

JNIEXPORT jstring JNICALL Java_net_caffeineswitch_lib_getcmn_Net_getNetIntfDesc
	(JNIEnv *env, jobject thisj, jint i){
		if (ifTable != NULL && (dwRetVal = GetIfTable(ifTable, &dwSize, 0)) == NO_ERROR && i > 0 && i <= (int)ifTable->dwNumEntries) {
			MibIfRow.dwIndex = i;
			if ((dwRetVal = GetIfEntry(&MibIfRow)) == NO_ERROR) {
				int i;
				ConvSJistoUtf8(MibIfRow.bDescr,NULL,&i);
				BYTE* d = new BYTE[i*2+1];
				ZeroMemory(d,i*2+1);
				ConvSJistoUtf8(MibIfRow.bDescr,d,&i);
				return env->NewStringUTF((const char*)(d));
			}else{
				return env->NewStringUTF("");
			}
		}else{
			return env->NewStringUTF("");
		}
}

JNIEXPORT jlong JNICALL Java_net_caffeineswitch_lib_getcmn_Net_getNetIntfInOctet
	(JNIEnv *env, jobject thisj, jint i){
		if (ifTable != NULL && (dwRetVal = GetIfTable(ifTable, &dwSize, 0)) == NO_ERROR && i > 0 && i <= (int)ifTable->dwNumEntries) {
			MibIfRow.dwIndex = i;
			if ((dwRetVal = GetIfEntry(&MibIfRow)) == NO_ERROR) {
				return (signed long long)MibIfRow.dwInOctets;
			}else{
				return -1;
			}
		}else{
			return -1;
		}
}

JNIEXPORT jlong JNICALL Java_net_caffeineswitch_lib_getcmn_Net_getNetIntfOutOctet
	(JNIEnv *env, jobject thisj, jint i){
		if (ifTable != NULL && (dwRetVal = GetIfTable(ifTable, &dwSize, 0)) == NO_ERROR && i > 0 && i <= (int)ifTable->dwNumEntries) {
			MibIfRow.dwIndex = i;
			if ((dwRetVal = GetIfEntry(&MibIfRow)) == NO_ERROR) {
				return (signed long long)MibIfRow.dwOutOctets;
			}else{
				return -1;
			}
		}else{
			return -1;
		}
}
