#include "Msg.h"
TCHAR MessageString[1024] ;
TCHAR *MSC(UINT32 MessageId)
{
	if ( FormatMessage(FORMAT_MESSAGE_FROM_HMODULE , NULL , MessageId , MAKELANGID(LANG_FARSI ,SUBLANG_DEFAULT) ,
						MessageString ,sizeof (MessageString) , NULL ) == 0 ) 
	{
		PutLog(FORMATMESSAGE_ERROR);
		MessageString[0] = NULL ;
	}
	return MessageString ;
}

TCHAR *MSC(UINT32 MessageId , ...)
{
	va_list args = NULL;
	va_start(args, MessageId);
	if ( FormatMessage(FORMAT_MESSAGE_FROM_HMODULE , NULL , MessageId , MAKELANGID(LANG_FARSI ,SUBLANG_DEFAULT) ,
						MessageString ,sizeof (MessageString) , &args ) == 0 ) 
	{
		PutLog(FORMATMESSAGE_ERROR);
		MessageString[0] = NULL ;
	}
	va_end(args);
	return MessageString ;
}

/*TCHAR *MSC(UINT32 MessageId , TCHAR * i_strArg0 , TCHAR * i_strArg1)
{
	if ( FormatMessage(FORMAT_MESSAGE_FROM_HMODULE , NULL , MessageId , MAKELANGID(LANG_FARSI ,SUBLANG_DEFAULT) ,
						MessageString ,sizeof (MessageString) , i_strArg0 , i_strArg1 ) == 0 ) 
	{
		PutLog(FORMATMESSAGE_ERROR);
		MessageString[0] = NULL ;
	}
	return MessageString ;
}*/

