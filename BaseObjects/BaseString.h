#ifndef BASESTRING_H
#define BASESTRING_H
#ifdef UNICODE
    #include <wchar.h>
    #define TCHAR wchar_t
    #define _tcscpy wcscpy
    #define _tcscat wcscat
	#define _tcsstr wcsstr
	#define	_tcsrchr wcsrchr 
	#define _tcsncpy wcsncpy 
	#define _tcsncat wcsncat 	
	#define _tcslen  wcslen
	#define _tcsupr _wcsupr
	#define _istalpha iswalpha
	#define _tcsncicmp _wcsnicmp
	#define _stprintf  swprintf
	#define _itoat     _itow
    #define _T(x)       L ## x
    #define _TEXT(x)   _T(x)
#else
    #include<string.h>
    #define _T(x)       x
    #define _TEXT(x)    x
    #define TCHAR char
	#define _tcsstr strstr
    #define _tcscpy strcpy
    #define _tcscat strcat
	#define	_tcsrchr strrchr 	
	#define _tcsncpy strncpy 
	#define _tcsncat strncat 	
	#define _tcslen  strlen
	#define _tcsupr _strupr
	#define _istalpha isalpha
	#define _tcsncicmp _strnicmp
	#define _stprintf sprintf
	#define _itoat     _itoa
#endif



#endif // BASESTRING_H
