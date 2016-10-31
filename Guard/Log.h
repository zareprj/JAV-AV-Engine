#ifndef __LOGHEADER__
#define __LOGHEADER__

#include "ntddk.h"
#include "SMFile.h"

#ifdef LOGTOFILE
	extern SMFile g_ocFile ;
	NTSTATUS InitLogFile ();
	void CloseLogFile();
#endif 

void _PutLog_ ( WCHAR * StrMessage , NTSTATUS STATUS  , ULONG line , char * Source) ;
void _BufferLog_ (char * StrMessage , WCHAR * Buffer , ULONG line , char * Source);
#ifdef IOHOOKMONITOR
NTSTATUS InitMonitorLogFile ();
void LogHookMonitor (char * StrMessage );
#endif 
//void CloseLogFile();
#ifdef LOGEE
#define PutLog( _hookExt, _call )                                                      \
	_PutLog_ ( _hookExt , _call  ,__LINE__, __FILE__ ) 
#else 
#define PutLog( _hookExt, _call )
#endif
	
#ifdef LOGEE
#define SourceLogger( _MESS )                                                      \
	PutLog(L##_MESS , STATUS_SUCCESS) 
#else
#define SourceLogger( _MESS )
#endif 

#ifdef LOGEE
#define BufferLogger( _MESS, _call )                                                      \
	_BufferLog_(_MESS , _call,__LINE__, __FILE__ ) 
#else
#define BufferLogger( _MESS, _call )
#endif
#endif 