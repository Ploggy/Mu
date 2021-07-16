#if !defined(_MSC_VER)
	#include <sys/time.h>
#else
	#include <windows.h>
	#include <sysinfoapi.h>
#endif

#include "pxa260/pxa260.h"
#include "pxa260/pxa260_RTC.h"

static UInt32 rtcCurTime(void){
#if !defined(_MSC_VER)
	struct timeval tv;

	gettimeofday(&tv, NULL);

	return tv.tv_sec;
#else
	FILETIME ftFiletime;
	uint64_t sTime;

	// https://docs.microsoft.com/en-us/windows/win32/api/minwinbase/ns-minwinbase-filetime
	GetSystemTimeAsFileTime(&ftFiletime);

	sTime = (((uint64_t)ftFiletime.dwHighDateTime) << UINT64_C(32)) |
			(((uint64_t)ftFiletime.dwLowDateTime) & UINT64_C(0xFFFFFFFF));

	// To microseconds -> NT Epoch to UNIX Epoch -> Seconds
	return (((sTime / UINT64_C(10)) - UINT64_C(11644473600000000))) /
		UINT64_C(1000000);
#endif
}

void pxa260rtcPrvUpdate(Pxa260rtc* rtc){
	
	UInt32 time = rtcCurTime();
	
	if(rtc->lastSeenTime != time){	//do not triger alarm more than once per second please
		
		if((rtc->RTSR & 0x4) && (time + rtc->RCNR_offset == rtc->RTAR)){	//check alarm
			rtc->RTSR |= 1;
		}
		if(rtc->RTSR & 0x8){							//send HZ interrupt
			rtc->RTSR |= 2;
		}
	}
	pxa260icInt(rtc->ic, PXA260_I_RTC_ALM, (rtc->RTSR & 1) != 0);
	pxa260icInt(rtc->ic, PXA260_I_RTC_HZ, (rtc->RTSR & 2) != 0);
}

static Boolean pxa260rtcPrvMemAccessF(void* userData, UInt32 pa, UInt8 size, Boolean write, void* buf){

	Pxa260rtc* rtc = userData;
	UInt32 val = 0;
	
	if(size != 4) {
		err_str(__FILE__ ": Unexpected ");
	//	err_str(write ? "write" : "read");
	//	err_str(" of ");
	//	err_dec(size);
	//	err_str(" bytes to 0x");
	//	err_hex(pa);
	//	err_str("\r\n");
		return true;		//we do not support non-word accesses
	}
	
	pa = (pa - PXA260_RTC_BASE) >> 2;

   debugLog("PXA260 RTC access:0x%04X, write:%d, PC:0x%08X\n", pa, write, pxa260GetPc());
	
	if(write){
		val = *(UInt32*)buf;
		
		switch(pa){
			case 0:
				rtc->RCNR_offset = rtcCurTime() - val;
				break;
			
			case 1:
				rtc->RTAR = val;
				pxa260rtcPrvUpdate(rtc);
				break;
			
			case 2:
				rtc->RTSR = (val &~ 3UL) | ((rtc->RTSR &~ val) & 3UL);
				pxa260rtcPrvUpdate(rtc);
				break;
			
			case 3:
				if(!(rtc->RTTR & 0x80000000UL)) rtc->RTTR = val;
				break;
		}
	}
	else{
		switch(pa){
			case 0:
				val = rtcCurTime() - rtc->RCNR_offset;
				break;
			
			case 1:
				val = rtc->RTAR;
				break;
			
			case 2:
				val = rtc->RTSR;
				break;
			
			case 3:
				val = rtc->RTTR;
				break;
		}
		*(UInt32*)buf = val;
	}
	
	return true;
}


void pxa260rtcInit(Pxa260rtc* rtc, Pxa260ic* ic){
	
	__mem_zero(rtc, sizeof(Pxa260rtc));
	rtc->ic = ic;
	rtc->RCNR_offset = 0;
	rtc->RTTR = 0x7FFF;	//nice default value
	rtc->lastSeenTime = rtcCurTime();
   //return memRegionAdd(physMem, PXA260_RTC_BASE, PXA260_RTC_SIZE, pxa260rtcPrvMemAccessF, rtc);
}

void pxa260rtcUpdate(Pxa260rtc* rtc){
	pxa260rtcPrvUpdate(rtc);
}
