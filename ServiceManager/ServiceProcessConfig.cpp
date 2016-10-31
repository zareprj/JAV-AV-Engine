#include "ServiceProcessConfig.h"
#include "BaseObject.h"

ServiceProcessConfig::ServiceProcessConfig(
	__in_opt    TCHAR *      _strMachineName,
	__in_opt    TCHAR *      _strDatabaseName,
	__in        DWORD       _dwDesiredAccessSCM,
	__in        TCHAR *      _strServiceName,
	__in_opt    TCHAR *      _strDisplayName,
	__in        DWORD       _dwDesiredAccessService,
	__in        DWORD       _dwServiceType,
	__in        DWORD       _dwStartType,
	__in        DWORD       _dwErrorControl,
	__in_opt    TCHAR *     _strBinaryPathName,
	__in_opt    TCHAR *     _strLoadOrderGroup,
	__in_opt    TCHAR *     _strDependencies,
	__in_opt    TCHAR *     _strServiceStartName,
	__in_opt    TCHAR *     _strPassword)
{
	strMachineName = _strMachineName;
	strDatabaseName =_strDatabaseName;
	dwDesiredAccessSCM=_dwDesiredAccessSCM;
	strServiceName = _strServiceName;
	strDisplayName = _strDisplayName;
	dwDesiredAccessService =_dwDesiredAccessService;
	dwServiceType=_dwServiceType;
	dwStartType=_dwStartType;
	dwErrorControl=_dwErrorControl;
	strBinaryPathName=_strBinaryPathName;
	strLoadOrderGroup=_strLoadOrderGroup;
	strDependencies=_strDependencies;
	strServiceStartName=_strServiceStartName;
	strPassword=_strPassword;	
}
ServiceProcessConfig::~ServiceProcessConfig()
{
	if ( strPassword != NULL )
		delete strPassword;
	if ( strServiceStartName != NULL ) 
		delete strServiceStartName; 
	if ( strDependencies != NULL )
		delete strDependencies ;
	if ( strLoadOrderGroup != NULL)
		delete strLoadOrderGroup ;
	if ( strBinaryPathName != NULL )
		delete strBinaryPathName ;
	if ( strDisplayName != NULL)
		delete strDisplayName ;
	if ( strServiceName != NULL)
		delete strServiceName ;
	if ( strDatabaseName !=  NULL)
		delete strDatabaseName ;
	if ( strMachineName != NULL)
		delete strMachineName ;
}



string ServiceProcessConfig::LpwstrToString(LPWSTR lpwstr)
{
	char str[256];
	wcstombs(str,lpwstr,256);
	char*       p_char=(char*)(lpwstr);
	string       resultStr=(string)(str);
	
	return resultStr;	
}
void ServiceProcessConfig::StringToLpwstr(string str, LPWSTR &dest)
{
	mbstowcs(dest,str.c_str(),str.size());
	dest[str.size()] = L'\0';
	if(*dest==0)
		dest=NULL;
	//dest=NULL;
	return;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

const TCHAR * ServiceProcessConfig::getMachineName()
{
	return strMachineName;
}

void ServiceProcessConfig::SetMachineName(const TCHAR * strArg)
{
	if (strArg == NULL)
	{
		if (strMachineName == NULL)
			return ;
		else
		{
			delete strMachineName ;
			strMachineName = NULL ;
		}
	}else
	{
		if ( strMachineName != NULL )
		{
			delete strMachineName ;
		}
		UINT uSize = lstrlen(strArg) +1 ;
		strMachineName = new TCHAR [uSize];
		memcpy (strMachineName ,strArg ,uSize *sizeof(TCHAR));
	}
}

const TCHAR *  ServiceProcessConfig::getDatabaseName()
{
		return strDatabaseName;
}
void  ServiceProcessConfig::SetDatabaseName(const TCHAR *strArg)
{
	if (strArg == NULL)
	{
		if (strDatabaseName == NULL)
			return ;
		else
		{
			delete strDatabaseName ;
			strDatabaseName = NULL ;
		}
	}else
	{
		if ( strDatabaseName != NULL )
		{
			delete strDatabaseName ;
		}
		UINT uSize = lstrlen(strArg) +1 ;
		strDatabaseName = new TCHAR [uSize];
		memcpy (strDatabaseName ,strArg ,uSize *sizeof(TCHAR));
	}
}

DWORD ServiceProcessConfig::getDesiredAccessSCM()
{
	return dwDesiredAccessSCM ;
}
void ServiceProcessConfig::SetDesiredAccessSCM(DWORD dwArg)
{
	dwDesiredAccessSCM = dwArg ;
}



const TCHAR *  ServiceProcessConfig::getServiceName()
{
	return strServiceName; 
}
void   ServiceProcessConfig::SetServiceName(const TCHAR *strArg)
{
	if (strArg == NULL)
	{
		if (strServiceName == NULL)
			return ;
		else
		{
			delete strServiceName ;
			strServiceName = NULL ;
		}
	}else
	{
		if ( strServiceName != NULL )
		{
			delete strServiceName ;
		}
		UINT uSize = lstrlen(strArg) +1 ;
		strServiceName = new TCHAR [uSize];
		memcpy (strServiceName ,strArg ,uSize *sizeof(TCHAR));
	}
}

const TCHAR * ServiceProcessConfig::getDisplayName()
{
	return strDisplayName;
}
void    ServiceProcessConfig::SetDisplayName(const TCHAR * strArg)
{
	if (strArg == NULL)
	{
		if (strDisplayName == NULL)
			return ;
		else
		{
			delete strDisplayName ;
			strDisplayName = NULL ;
		}
	}else
	{
		if ( strDisplayName != NULL )
		{
			delete strDisplayName ;
		}
		UINT uSize = lstrlen(strArg) +1 ;
		strDisplayName = new TCHAR [uSize];
		memcpy (strDisplayName ,strArg ,uSize *sizeof(TCHAR));
	}
}

DWORD ServiceProcessConfig::getDesiredAccessService()
{
	return dwDesiredAccessService ;
}
void  ServiceProcessConfig::SetDesiredAccessService(DWORD dwArg)
{
	dwDesiredAccessService = dwArg ;
}

DWORD ServiceProcessConfig::getServiceType()
{
	return dwServiceType ;
}
void  ServiceProcessConfig::SetServiceType(DWORD dwArg)
{
	dwServiceType = dwArg ;
}

DWORD ServiceProcessConfig::getStartType()
{
	
	return dwStartType ;
}
void  ServiceProcessConfig::SetStartType(DWORD dwArg)
{
	dwStartType = dwArg ;
}

DWORD ServiceProcessConfig::getErrorControl()
{
	return dwErrorControl ;
}
void  ServiceProcessConfig::SetErrorControl(DWORD dwArg)
{
	dwErrorControl = dwArg ;
}

const TCHAR *  ServiceProcessConfig::getBinaryPathName()
{
	return  strBinaryPathName;
}

void    ServiceProcessConfig::SetBinaryPathName(const TCHAR * strArg)
{
	if (strArg == NULL)
	{
		if (strBinaryPathName == NULL)
			return ;
		else
		{
			delete strBinaryPathName ;
			strBinaryPathName = NULL ;
		}
	}else
	{
		if ( strBinaryPathName != NULL )
		{
			delete strBinaryPathName ;
		}
		UINT uSize = lstrlen(strArg) +1 ;
		strBinaryPathName = new TCHAR [uSize];
		memcpy (strBinaryPathName ,strArg ,uSize *sizeof(TCHAR));
	}
}

const TCHAR * ServiceProcessConfig::getLoadOrderGroup()
{
	return strLoadOrderGroup ;
}

void     ServiceProcessConfig::SetLoadOrderGroup(const TCHAR *strArg)
{
	if (strArg == NULL)
	{
		if (strLoadOrderGroup == NULL)
			return ;
		else
		{
			delete strLoadOrderGroup ;
			strLoadOrderGroup = NULL ;
		}
	}else
	{
		if ( strLoadOrderGroup != NULL )
		{
			delete strLoadOrderGroup ;
		}
		UINT uSize = lstrlen(strArg) +1 ;
		strLoadOrderGroup = new TCHAR [uSize];
		memcpy (strLoadOrderGroup ,strArg ,uSize *sizeof(TCHAR));
	}
}

void ServiceProcessConfig::SetTagId(DWORD i_dwTagId)
{
	dwTagId = i_dwTagId ;
}
DWORD   ServiceProcessConfig::getTagId()
{
	return dwTagId ;
}



const TCHAR * ServiceProcessConfig::getDependencies()
{
	return strDependencies;
}
void    ServiceProcessConfig::SetDependencies(const TCHAR * strArg)
{
	if (strArg == NULL)
	{
		if (strLoadOrderGroup == NULL)
			return ;
		else
		{
			delete strLoadOrderGroup ;
			strLoadOrderGroup = NULL ;
		}
	}else
	{
		if ( strLoadOrderGroup != NULL )
		{
			delete strLoadOrderGroup ;
		}
		UINT uSize = 0;
		if ( sizeof (TCHAR) == 2 )
		{
			int index = 0;
			unsigned char * byteTmp =(unsigned char *) strArg ;
			while ((*(unsigned int *)(byteTmp+index)) != 0)
			{
				uSize ++ ;
				index += sizeof (TCHAR);
			}
			uSize += 2*sizeof (TCHAR) ;
		}else if (sizeof (TCHAR) == 1)
		{
			int index = 0;
			unsigned char * byteTmp =(unsigned char *) strArg ;
			while ((*(unsigned short int *)(byteTmp+index)) != 0)
			{
				uSize ++ ;
				index ++ ;
			}
			uSize +=2 ;
		}

		strLoadOrderGroup = new TCHAR  [uSize];
		memcpy (strLoadOrderGroup ,strArg ,uSize * sizeof(TCHAR));
	}
}
const TCHAR * ServiceProcessConfig::getServiceStartName()
{
	return strServiceStartName;
}
void    ServiceProcessConfig::SetServiceStartName(const TCHAR * strArg)
{
    if (strArg == NULL)
	{
		if (strServiceStartName == NULL)
			return ;
		else
		{
			delete strServiceStartName ;
			strServiceStartName = NULL ;
		}
	}else
	{
		if ( strServiceStartName != NULL )
		{
			delete strServiceStartName ;
		}
		UINT uSize = lstrlen(strArg) +1 ;
		strServiceStartName = new TCHAR [uSize];
		memcpy (strServiceStartName ,strArg ,uSize *sizeof(TCHAR));
	}
}
const TCHAR * ServiceProcessConfig::getPassword()
{
	return strPassword;
}
void       ServiceProcessConfig::SetPassword(const TCHAR * strArg)
{
	if (strArg == NULL)
	{
		if (strPassword == NULL)
			return ;
		else
		{
			delete strPassword ;
			strPassword = NULL ;
		}
	}else
	{
		if ( strPassword != NULL )
		{
			delete strPassword ;
		}
		UINT uSize = lstrlen(strArg) +1 ;
		strPassword = new TCHAR [uSize];
		memcpy (strPassword ,strArg ,uSize *sizeof(TCHAR));
	}
}