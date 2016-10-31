// align to 512

#ifndef MemoryTree_ADDED
#define MemoryTree_ADDED
#include "All_Defines.h"
#include "avltree.h"

#define		DefaultSize		4096

//	Structure base on link list data structure used for memory tree emulation 
typedef struct _MemoryCreated
{
	UINT32	nOffset;
	UINT8 	nData[DefaultSize];
// 	MemoryCreated*	posLeft;
// 	MemoryCreated*	posRight;
} MemoryCreated;

//	Structure base on link list data structure used for free memory tree 
// typedef struct _MemoryDel
// {
// 	MemoryCreated * Current;
// 	MemoryDel * Next;
// }MemoryDel;

//	Function Prototypes
BOOLEAN SMGetMemBuffer(VirtualMachine *posVm, UINT32 nOffset, UINT32 nSize);
BOOLEAN SMSetMemBuffer(VirtualMachine *posVm, UINT32 nOffset, UINT32 nSize);

__inline MemoryCreated* GetTreeNode (VirtualMachine *posVm, UINT32 nOffset);
__inline MemoryCreated* SetTreeNode (VirtualMachine *posVm, UINT32 nOffset);

//////////////////////////////////////////////////////////////////////////
FORCEINLINE INT32 CompareMemory(const void *pa, const void *pb, void *param)
{
	if (((MemoryCreated *)pa)->nOffset == ((MemoryCreated *)pb)->nOffset)
	{
		return 0;
	}
	else if (((MemoryCreated *)pa)->nOffset > ((MemoryCreated *)pb)->nOffset)
	{
		return 1;
	}
	else 
	{
		return -1;
	}
}
//////////////////////////////////////////////////////////////////////////
__inline void InitMemoryTree(VirtualMachine *posVm)
{
	posVm->posMainMemoryTree = avl_create(NULL , NULL);
}
//////////////////////////////////////////////////////////////////////////
__inline void DestroyMemoryTree(VirtualMachine *posVm)
{
	avl_destroy(posVm->posMainMemoryTree); 
}
#endif