#ifndef _ServiceProcessConfig_
#define _ServiceProcessConfig_

#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <strsafe.h>
#include "conio.h"
#include "BaseObject.h"

using namespace std;


class ServiceProcessConfig
{
public:
	ServiceProcessConfig()
	{
		strPassword = NULL ;
		strServiceStartName = NULL;
		strDependencies = NULL;
		strLoadOrderGroup = NULL;
		strBinaryPathName = NULL ;
		strDisplayName = NULL;
		strServiceName = NULL;
		strDatabaseName =  NULL;
		strMachineName = NULL;
	};
	ServiceProcessConfig(
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
	__in_opt    TCHAR *     _strPassword) ;
	~ServiceProcessConfig();


	static string LpwstrToString(LPWSTR lpwstr);
	static void ServiceProcessConfig::StringToLpwstr(string str, LPWSTR& dest);

	const TCHAR * getMachineName();
	void          SetMachineName(const TCHAR *);

	const TCHAR * getDatabaseName();
	void          SetDatabaseName(const TCHAR *);

	DWORD getDesiredAccessSCM();
	void SetDesiredAccessSCM(DWORD );

	const TCHAR * getServiceName();
	void          SetServiceName(const TCHAR *);

	const TCHAR * getDisplayName();
	void          SetDisplayName(const TCHAR * );

	DWORD getDesiredAccessService();
	void  SetDesiredAccessService(DWORD );

	DWORD getServiceType();
	void  SetServiceType(DWORD);

	DWORD getStartType();
	void  SetStartType(DWORD);

	DWORD getErrorControl();
	void  SetErrorControl(DWORD );

	const TCHAR * getBinaryPathName();
	void          SetBinaryPathName(const TCHAR * );

	const TCHAR * getLoadOrderGroup();
	void          SetLoadOrderGroup(const TCHAR *);

	void    SetTagId(DWORD i_dwTagId);
	DWORD   getTagId();
	
	const TCHAR * getDependencies();
	void          SetDependencies(const TCHAR * );

	const TCHAR * getServiceStartName();
	void          SetServiceStartName(const TCHAR * );

	const TCHAR * getPassword();
	void          SetPassword(const TCHAR * );

protected:

private:
	TCHAR * strPassword;
	TCHAR * strServiceStartName;
	TCHAR * strDependencies;
	DWORD   dwTagId;
	TCHAR * strLoadOrderGroup;
	TCHAR * strBinaryPathName;
	DWORD dwErrorControl;
	DWORD dwStartType;
	DWORD dwServiceType;
	DWORD dwDesiredAccessService;
	TCHAR * strDisplayName;
	TCHAR * strServiceName;
	DWORD dwDesiredAccessSCM;
	TCHAR * strDatabaseName;
	TCHAR * strMachineName;
	
};
#endif