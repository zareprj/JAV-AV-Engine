#include "BaseObject.h"
#include "JFile.h"
#ifdef _LOGEE

#if LogLevel == 1
static void ReportMessage (TCHAR *Message) ;
void Logger (DWORD MessageId , TCHAR *File , int Line )
{
	TCHAR strOwnMessage [200] ,strSystemMessage [200] , LogTemp[1024] ;
	DWORD dwLastError = GetLastError() ;
	if ( FormatMessage (FORMAT_MESSAGE_FROM_HMODULE , NULL , MessageId , 
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT) ,strOwnMessage , sizeof (strOwnMessage) , NULL ) == 0 ) 
	{
		DWORD dwLastError = GetLastError() ;
		return;
	}

	if ( FormatMessage (FORMAT_MESSAGE_FROM_SYSTEM , NULL , dwLastError , 
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT) ,strSystemMessage , sizeof (strSystemMessage) , NULL ) == 0 ) 
	{
		DWORD dwLastError = GetLastError() ;
		return;
	}
	wsprintf ( LogTemp , _T("%wsLast Error : %wsFile : %ws \r\n Line : %d \r\n")  , strOwnMessage ,strSystemMessage , File , Line );
	ReportMessage(LogTemp) ;
}
void ReportMessage (TCHAR *Message) 
{
#ifdef LogToFile
	JFile ocReportFile ;	
	INT64 n64SeekParameter ;
	size_t stMessageLen ;
	if ( ocReportFile.CreateFile(JString(LogFile),TRUE ,TRUE , FALSE )==TRUE) 
	{
		if ( ocReportFile.GetFileLength() < 1) 
		{
			UINT8 u8Unicode [] = {0xFF,0xFE} ;
			stMessageLen = sizeof (u8Unicode) ;
			ocReportFile.Write(u8Unicode ,stMessageLen);
		}
		else
		{
			n64SeekParameter = 0;
			ocReportFile.Seek( n64SeekParameter, JFile::FEND);
		}
		size_t stMessageLen = lstrlen(Message) * sizeof (TCHAR) ;
		ocReportFile.Write(Message , stMessageLen);
		ocReportFile.Flush();
	}
#elif  LogToConsol
	printf ("%ws" , Message);
#endif
}
#endif
#if LogLevel == 0
void Logger (DWORD MessageId )
{

	TCHAR Temp [1024] ;
	FormatMessage (FORMAT_MESSAGE_FROM_HMODULE , NULL , MessageId , 
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT) ,Temp , 0 , NULL ) ;
	OutputDebugStringA(Temp) ;
};

#endif

#endif