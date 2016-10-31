
#include "MemoryTree.h"
#include "SMBuffer.h"
#include "FileInformation.h"
#include "All_Defines.h"
#include "CPU.h"
#include "avltree.h"

#ifdef ALLOC_PRAGMA
#pragma alloc_text(PAGE, SMGetMemBuffer)
#pragma alloc_text(PAGE, SMSetMemBuffer)
#endif

//////////////////////////////////////////////////////////////////////////
/////////////  Fill The middle buffer from memory or file ////////////////
//////////////////////////////////////////////////////////////////////////
BOOLEAN SMGetMemBuffer(VirtualMachine *posVm, UINT32 nOffset, UINT32 nSize)
{	
	UINT32	nAlignedAddress;
	MemoryCreated	*posMemoryCreated0, *posMemoryCreated1;
	UINT64 PhisycalAddr = nOffset;
	UINT32	nSub;
	PVOID vTmp ;

	PAGED_CODE();
	//	Create Align address from offset
	nAlignedAddress = nOffset & (~(DefaultSize - 1));

	nSub = nOffset - nAlignedAddress;

	//	Check if the requested buffer is between 2 aligned offset
	//	It means that data may be in 2 memory tree node
	if (nSub + nSize > DefaultSize)
	{
		posMemoryCreated0 = GetTreeNode(posVm, nAlignedAddress);
		posMemoryCreated1 = GetTreeNode(posVm, nAlignedAddress + DefaultSize);

		//	If memory tree doesn't contain the data, read data from file
		if (posMemoryCreated0 == NULL && posMemoryCreated1 == NULL)
		{
			PhisycalAddr = SMRvaToOffset(posVm->Context.posInfoOFFile, nOffset);

		if (PhisycalAddr == (UINT32)-2)
			{
				ZeroMemory(posVm->pnMiddleBuffer, nSize);
			}
			else if (PhisycalAddr == (UINT32)-1)
			{
				return FALSE;
			}
			else
			{
				vTmp = SMGetBufferOffsetForMemTree(posVm->Context.posBuffer, PhisycalAddr, nSize);
				if (vTmp == NULL)
				{
					return FALSE;
				}
				memmove(posVm->pnMiddleBuffer, vTmp, nSize);
			}
		}

		//	If data part one is exist on memory tree , read this part from file
		else if (posMemoryCreated0 == NULL)
		{
			PhisycalAddr = SMRvaToOffset(posVm->Context.posInfoOFFile, nOffset);
			if (PhisycalAddr == (UINT32)-2)
			{
				ZeroMemory(posVm->pnMiddleBuffer, nSub);
			}
			else if (PhisycalAddr == (UINT32)-1)
			{
				return FALSE;
			}
			else
			{
			nSub = DefaultSize - nSub;
			vTmp = SMGetBufferOffsetForMemTree(posVm->Context.posBuffer, PhisycalAddr, nSub);
			if (vTmp == NULL)
			{
				return FALSE;
			}
			memmove(posVm->pnMiddleBuffer, vTmp, nSub);
}
			memmove(posVm->pnMiddleBuffer + nSub, posMemoryCreated1->nData, nSize - nSub);
		}
		
		//	If part two is exist on memory tree , read this part from file
		else if (posMemoryCreated1 == NULL)
		{	
			memmove(posVm->pnMiddleBuffer , posMemoryCreated0->nData +  nSub, DefaultSize - nSub);
			nSub = DefaultSize - nSub;
			PhisycalAddr = SMRvaToOffset(posVm->Context.posInfoOFFile, nOffset + nSub);
			if (PhisycalAddr == (UINT32)-2)
			{
				ZeroMemory(posVm->pnMiddleBuffer, nSize - nSub);
			}
			else if (PhisycalAddr == (UINT32)-1)
			{
				return FALSE;
			}
			else
			{
			vTmp = SMGetBufferOffsetForMemTree(posVm->Context.posBuffer, PhisycalAddr, nSize - nSub);
			if (vTmp == NULL)
			{
				return FALSE;
			}
			memmove(posVm->pnMiddleBuffer + nSub, vTmp, nSize - nSub);
}
		}
		
		//	Read data from memory tree
		else
		{
			memmove(posVm->pnMiddleBuffer, posMemoryCreated0->nData +  nSub, DefaultSize - nSub);
			memmove(posVm->pnMiddleBuffer + (DefaultSize - nSub), posMemoryCreated1->nData , nSize - (DefaultSize - nSub));
		}
		return TRUE;
	}
	
	//	Data can be in a memory tree node
	else
	{
		posMemoryCreated0 = GetTreeNode(posVm, nAlignedAddress);
		
		//	If memory tree doesn't contain the data, read this part from file
		if (posMemoryCreated0 == NULL)
		{
			PhisycalAddr = SMRvaToOffset(posVm->Context.posInfoOFFile, nOffset);
			if (PhisycalAddr == (UINT32)-2)
			{
				ZeroMemory(posVm->pnMiddleBuffer, nSize);
			}
			else if (PhisycalAddr == (UINT32)-1)
			{
				return FALSE;
			}
			else
			{
			vTmp = SMGetBufferOffsetForMemTree(posVm->Context.posBuffer, PhisycalAddr, nSize);
			if (vTmp == NULL)
			{
				return FALSE;
			}
			memmove(posVm->pnMiddleBuffer, vTmp, nSize);
}			
		}

		//	Read data from memory tree
		else
		{
			memmove(posVm->pnMiddleBuffer, posMemoryCreated0->nData + nSub, nSize);
		}
		return TRUE;
	}
}

//////////////////////////////////////////////////////////////////////////
///////////// Set The memory tree from middle buffer /////////////////////
//////////////////////////////////////////////////////////////////////////
BOOLEAN SMSetMemBuffer(VirtualMachine *posVm, UINT32 nOffset, UINT32 nSize)
{
	UINT32	nAlignedAddress;
	MemoryCreated	*posMemoryCreated0, *posMemoryCreated1;
	INT64 PhisycalAddr = nOffset;
	UINT32	nSub;
	UINT32	IsNodeCreated0 = FALSE, IsNodeCreated1 = FALSE;
	PVOID vTmp;
	PAGED_CODE();

	//	Create Align address from offset
	nAlignedAddress = nOffset & (~(DefaultSize - 1));
	nSub = nOffset - nAlignedAddress;

	//	Check if the requested buffer is between 2 aligned offset
	//	It means that data may be in 2 memory tree node
	if (nSub + nSize > DefaultSize)
	{
		posMemoryCreated0 = SetTreeNode(posVm, nAlignedAddress);
		IsNodeCreated0 = posVm->IsNodeCreated;
		
		posMemoryCreated1 = SetTreeNode(posVm, nAlignedAddress + DefaultSize);
		IsNodeCreated1 = posVm->IsNodeCreated;
		

		//	If first node is just created, it should fill remaining raw data from file
		if (IsNodeCreated0 == TRUE)
		{
			posMemoryCreated0->nOffset = nAlignedAddress;
 			PhisycalAddr = SMRvaToOffset(posVm->Context.posInfoOFFile, posMemoryCreated0->nOffset);
			if (PhisycalAddr == (UINT32)-2)
			{
				ZeroMemory(posMemoryCreated0->nData, nSub);
			}
			else if (PhisycalAddr == (UINT32)-1)
			{
				return FALSE;
			}
			else
			{
 			vTmp = SMGetBufferOffsetForMemTree(posVm->Context.posBuffer, PhisycalAddr, nSub);
			if (vTmp == NULL)
			{
				return FALSE;
			}
			memmove(posMemoryCreated0->nData, vTmp, nSub);
}
		}
		//	copy data from middle buffer to first node of memory tree
		memmove(posMemoryCreated0->nData + nSub, posVm->pnMiddleBuffer, DefaultSize - nSub);

		//	If second node is just created, it should fill remaining raw data from file
		nSub = nSize - (DefaultSize - nSub);
		if (IsNodeCreated1 == TRUE)
		{
			posMemoryCreated1->nOffset = nAlignedAddress + DefaultSize;
			
			PhisycalAddr = SMRvaToOffset(posVm->Context.posInfoOFFile, posMemoryCreated1->nOffset + nSub);
			if (PhisycalAddr == (UINT32)-2)
			{
				ZeroMemory(posMemoryCreated1->nData, DefaultSize - nSub);
			}
			else if (PhisycalAddr == (UINT32)-1)
			{
				return FALSE;
			}
			else
			{
			vTmp = SMGetBufferOffsetForMemTree(posVm->Context.posBuffer, PhisycalAddr, DefaultSize - nSub);
			if (vTmp == NULL)
			{
				return FALSE;
			}
			memmove(posMemoryCreated1->nData + nSub, vTmp, DefaultSize - nSub);		
}
		}
		//	copy data from middle buffer to second node of memory tree
		memmove(posMemoryCreated1->nData, posVm->pnMiddleBuffer + (nSize - nSub), nSub /*nSize - (DefaultSize - nSub)*/);
		//memmove(posMemoryCreated1->nData , DefaultSize , posVm->pnMiddleBuffer + (DefaultSize - nSub), nSub /*nSize - (DefaultSize - nSub)*/);
		
	}

	else
	{
		posMemoryCreated0 = SetTreeNode(posVm, nAlignedAddress);

		//	If memory tree node is just created, it should fill remaining raw data from file
		if (posVm->IsNodeCreated == TRUE)
		{
			posMemoryCreated0->nOffset = nAlignedAddress;
			PhisycalAddr = SMRvaToOffset(posVm->Context.posInfoOFFile, posMemoryCreated0->nOffset);
			if (PhisycalAddr == (UINT32)-2)
			{	
				ZeroMemory((posMemoryCreated0->nData + nSub), nSize);
			}
			else if (PhisycalAddr == (UINT32)-1)
			{
				return FALSE;
			}
			else
			{
			vTmp = SMGetBufferOffsetForMemTree(posVm->Context.posBuffer, PhisycalAddr, DefaultSize);
			if (vTmp == NULL)
			{
				return FALSE;
			}
			memmove(posMemoryCreated0->nData, vTmp, DefaultSize);
}
		}
		//	copy data from middle buffer to memory tree node
		memmove(posMemoryCreated0->nData + nSub, posVm->pnMiddleBuffer , nSize);		
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
/////////////  Search Memory tree with the input offset //////////////////
/////////// Return the node if finds , otherwise return NULL /////////////
//////////////////////////////////////////////////////////////////////////
__inline MemoryCreated* GetTreeNode (VirtualMachine *posVm, UINT32 nOffset)
{
	if(posVm->posLastUsedMemoryTree != NULL)
	{
		if (posVm->posLastUsedMemoryTree->nOffset == nOffset)
		{
			return posVm->posLastUsedMemoryTree;
		}
	}
	posVm->posLastUsedMemoryTree = (MemoryCreated *)avl_find(posVm->posMainMemoryTree, (MemoryCreated *)&nOffset);
	return posVm->posLastUsedMemoryTree;
}

//////////////////////////////////////////////////////////////////////////
/////////////  Search Memory tree with the input offset //////////////////
///// Return the node if finds , otherwise create new and return it //////
//////////////////////////////////////////////////////////////////////////
__inline MemoryCreated* SetTreeNode (VirtualMachine *posVm, UINT32 nOffset)
{
	MemoryCreated *posMemoryCreated = GetTreeNode(posVm, nOffset);
	if (posMemoryCreated != NULL)
	{
		posVm->IsNodeCreated = FALSE;
	}
	else
	{
		posMemoryCreated = (MemoryCreated *)SMAlloc(sizeof(MemoryCreated));
		posMemoryCreated->nOffset = nOffset;
		posVm->IsNodeCreated = TRUE;
		avl_insert(posVm->posMainMemoryTree, posMemoryCreated);
	}
	return posMemoryCreated;
}
//////////////////////////////////////////////////////////////////////////