#include "SafavaServiceProcessManager.h"
#include "AVEngine.h"
//---------------------------------------------------------------------------------------
SafavaServiceProcessManager::SafavaServiceProcessManager()
{
	AVEngine*avEngine=new AVEngine(); // new -> free ; malloce->delete
	installNewThread(L"Hafez-RPC-AVEngine",(Service*)avEngine,0);	
}
//---------------------------------------------------------------------------------------
SafavaServiceProcessManager::~SafavaServiceProcessManager()
{
	//delete avEngine ;
//	MessageBox(NULL,TEXT("~SafavaServiceProcessManager"), TEXT("Error"), MB_OK);
//	SafavaServiceProcessManager
}
//---------------------------------------------------------------------------------------
void SafavaServiceProcessManager::initializer()
{
	for (int i=0;i<getLengthOfServiceRepository();i++)
	{
		getServiceRepository()[i].pService=NULL;
		getServiceRepository()[i].serviceID=NULL;
	}
	return;
}
//---------------------------------------------------------------------------------------
SafavaServiceProcessManager::mapOperationsResult SafavaServiceProcessManager::installNewThread( TCHAR* threadID,Service* servicethreadPointer, int index )
{	
	try
	{
		if (getThreadHandler(threadID)==NULL)
		{
			getServiceRepository()[index].serviceID=threadID;
			getServiceRepository()[index].pService=servicethreadPointer;
			return mapOperationsResult::successfully;
		} 
		else
		{
			return mapOperationsResult::failing_alreadyExist;
		}
	}catch (char * errorStr )
	{
		cout << "Exception raised: " << errorStr << '\n';
		return mapOperationsResult::failing;
	}	
}
//---------------------------------------------------------------------------------------
SafavaServiceProcessManager::mapOperationsResult SafavaServiceProcessManager::unistallThread( TCHAR* threadID )
{
	Service* serviceHandle;
	
	ServiceEntry serviceEntry=getServiceRepository()[getIndexOfThreadHandler(threadID)];
	try
	{
		serviceHandle=serviceEntry.pService;/*getThreadHandler(threadID);*/
		if (serviceHandle!=NULL)
			if (serviceHandle->Stop()==true)
			{
				free(serviceHandle);
				serviceEntry.serviceID=NULL;
				return mapOperationsResult::successfully;
			} 
			else
			{
				return mapOperationsResult::failing_threadCannotbeStop;
			} 
		else
			return mapOperationsResult::failing_doesNotExist;
		
	}catch (char * errorStr )
	{
		cout << "Exception raised: " << errorStr << '\n';
		return mapOperationsResult::failing;
	}
}
//---------------------------------------------------------------------------------------
int SafavaServiceProcessManager::unistallAllThread()
{
	int numFail=0;
	for (int i=0;i<getLengthOfServiceRepository();i++)
		if (unistallThread(getServiceRepository()[i].serviceID)!=mapOperationsResult::successfully)
			numFail=numFail+1;					
	return numFail;
}
//---------------------------------------------------------------------------------------
Service* SafavaServiceProcessManager::getThreadHandler( TCHAR* threadID )
{

	for (int i=0;i<getLengthOfServiceRepository();i++)
		if (getServiceRepository()[i].pService!=NULL)
			if (strcmp((char*)getServiceRepository()[i].serviceID,(char*)threadID)==0)
				return getServiceRepository()[i].pService;
	return NULL;

}
//---------------------------------------------------------------------------------------
int SafavaServiceProcessManager::getIndexOfThreadHandler( TCHAR* threadID )
{

	for (int i=0;i<getLengthOfServiceRepository();i++)
		if (strcmp((char*)getServiceRepository()[i].serviceID,(char*)threadID)==0)
			return i;
	return -1;
}
//---------------------------------------------------------------------------------------
bool SafavaServiceProcessManager::isEmpty()
{
	return getServiceRepository()==NULL;
}
//---------------------------------------------------------------------------------------
// getter and setter
ServiceEntry* SafavaServiceProcessManager::getServiceRepository()
{
	return serviceEntry;
}
//---------------------------------------------------------------------------------------
int SafavaServiceProcessManager::getLengthOfServiceRepository()
{
	return numberOfEntryPoint;
}
//---------------------------------------------------------------------------------------