#ifndef _SafavaServiceProcessManager_
#define _SafavaServiceProcessManager_

#include <map>
#include <iostream>
#include "conio.h"
#include "Service.h"
#include "AVEngine.h"
using namespace std;

//typedef std::pair </*TCHAR**/wstring,Service*> ID_ServicePair;
//typedef std::map </*TCHAR**/wstring,Service*> serviceMap;
//typedef serviceMap::iterator serviceMap_pIter;
#define numberOfEntryPoint  1

typedef struct ServiceEntry
{
	TCHAR* serviceID;
	Service* pService; 
};


static ServiceEntry serviceEntry[numberOfEntryPoint];

//static serviceMap serviceRepository;// <ID,threadPointer>

class SafavaServiceProcessManager
{
public:

	SafavaServiceProcessManager();
	~SafavaServiceProcessManager();

	// New Data Type
	enum mapOperationsResult 
	{
		successfully,
		failing,
		failing_alreadyExist,
		failing_doesNotExist,
		failing_threadCannotbeStop
	};

	// Business Methods
	static mapOperationsResult installNewThread(TCHAR* threadID,Service* servicethreadPointer, int index);
	static Service* getThreadHandler(TCHAR* threadID); // if threadID does not exist it return NULL.
	static int SafavaServiceProcessManager::getIndexOfThreadHandler( TCHAR* threadID );

	static mapOperationsResult unistallThread(TCHAR* threadID);
	static int unistallAllThread(); // return number of failed un-installing thread(for thread can't be stop). Remark: if an unexpected exception occur it return -1.
	static bool isEmpty();
protected:

private:
	
	static ServiceEntry* getServiceRepository();
	
	static int SafavaServiceProcessManager::getLengthOfServiceRepository();
	static void initializer();

};
#endif