#include "log.h" 
#include <stdio.h>

#ifdef ALLOC_PRAGMA
	#pragma alloc_text(PAGE, _BufferLog_)
	#pragma alloc_text(PAGE, _PutLog_)
#ifdef LOGTOFILE
	#pragma alloc_text(PAGE, CloseLogFile)
#endif
#endif

#ifdef LOGTOFILE
	SMFile g_ocFile ;

NTSTATUS InitLogFile ()
{
	return  SMCreateFileForWrite(&g_ocFile , L"\\??\\C:\\IoMonitorlog.log");
}

#endif
#ifdef IOHOOKMONITOR
	SMFile g_ocIoMonitorFile ;
	NTSTATUS InitMonitorLogFile ()
	{
		return  SMCreateFileForWrite(&g_ocIoMonitorFile , L"\\??\\C:\\IoMonitor.log");
	}
	void LogHookMonitor (char * StrMessage )
	{
		ULONG ulbufferlen ;
		ulbufferlen = strlen(StrMessage) ;
		SMWriteFile( &g_ocIoMonitorFile , StrMessage , &ulbufferlen ) ; 
		SMFlushBuffer( &g_ocIoMonitorFile );
	}
#endif 

//----------------------------------------------------------------
#ifdef LOGTOFILE
void _PutLog_ ( WCHAR * StrMessage , NTSTATUS STATUS  , ULONG line , char * Source) 
{
	char MsgBuffer[1024];
	ULONG ulbufferlen ;
	sprintf(MsgBuffer ,"Jav message : %ws \r\n CodeMessage : %d  \r\n Source : %s \r\n Line : line %d\n\r Process Id : %d \r\n"  , StrMessage , STATUS , Source, line , PsGetCurrentProcessId() ) ;
	ulbufferlen = strlen(MsgBuffer) ;
	SMWriteFile( &g_ocFile , MsgBuffer , &ulbufferlen ) ; 
	SMFlushBuffer( &g_ocFile );
}
#else
//----------------------------------------------------------------
void _PutLog_ ( WCHAR * StrMessage , NTSTATUS STATUS  , ULONG line , char * Source) 
{	
	DbgPrint ( "Jav message : %ws \r\n CodeMessage : %d  \r\n Source : %s \r\n Line : line %d\r\n Process Id : %d \r\n"  , StrMessage , STATUS , Source, line , PsGetCurrentProcessId() ) ;	
}
#endif
//----------------------------------------------------------------
#ifdef LOGTOFILE
void _BufferLog_ (char * StrMessage , WCHAR * Buffer , ULONG line , char * Source)
{
	char MsgBuffer[1024];
	ULONG ulbufferlen ;
	sprintf(MsgBuffer , "Jav message : %s \r\n Buffer : %ws  \r\n Source : %s \r\n Line : line %d \r\n Process Id : %d \r\n"  , StrMessage , Buffer , Source, line , PsGetCurrentProcessId() ) ;
	ulbufferlen = strlen(MsgBuffer) ;
	SMWriteFile( &g_ocFile , MsgBuffer , &ulbufferlen ) ; 
	SMFlushBuffer( &g_ocFile );
}
#else
//----------------------------------------------------------------
void _BufferLog_ (char * StrMessage , WCHAR * Buffer , ULONG line , char * Source)
{
	char MsgBuffer[1024];
	DbgPrint ( "Jav message : %s \r\n Buffer : %ws  \r\n Source : %s \r\n Line : line %d \r\n Process Id : %d \r\n"  , StrMessage , Buffer , Source, line , PsGetCurrentProcessId() ) ;
}
#endif
//----------------------------------------------------------------
#ifdef LOGTOFILE
void CloseLogFile()
{
	ZwClose(g_ocFile.HFile);
}
#endif