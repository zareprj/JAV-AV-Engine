#ifndef __JBUFFER__
#define __JBUFFER__
#include "iomonitor.h" 
#include "log.h"

typedef struct _ModuleDescriptor
{
	unsigned __int64 Start  , Limit ;
	BOOLEAN Used ;
	UCHAR *Pointer ;
	PMDL   mdl;
} SMModuleDescriptor;

typedef struct _SMBuffer 
{
	__int64        Current ;
	PFileHandle    File ;
	UINT32		   Config ;	
	PIRP           Irp ; 
	UCHAR		   *Buffer ;
	ULONG          CountChunk ;
	ULONG          CurrentBlock , ModuleSize  ;
	PKEVENT        phEvent;
//	LARGE_INTEGER FileSize ;
	unsigned __int64 FileSize ;
	SMModuleDescriptor *ModuleDescriptor ;
} SMBuffer , *PSMBuffer;

NTSTATUS SMBufferInit (IN PSMBuffer *ImpBuffer , ULONG CountModule , ULONG SizeOfModule );
NTSTATUS SMSetBufferFile (IN SMBuffer *ImpBuffer ) ;
//NTSTATUS SetBufferFile4App( IN JBuffer *ImpBuffer  , PFileHandle FH);
BOOLEAN SMSetBufferPointer (SMBuffer *ImpBuffer ,unsigned __int64 Index)  ;
BOOLEAN SMSetRelativePointer (IN SMBuffer *ImpBuffer , int Index)  ;
PVOID  SMGetBuffer(IN SMBuffer *ImpBuffer, ULONG SizeofBuffer ) ;
PVOID SMGetBufferOffset(IN SMBuffer *ImpBuffer,unsigned __int64 Offset , ULONG SizeofBuffer ) ;
PVOID SMGetBufferOffsetForMemTree( IN SMBuffer *ImpBuffer,unsigned __int64 Offset , ULONG SizeofBuffer ) ;

void SMBufferUninitialize(SMBuffer **ImpBuffer); 
__inline PSbScaner SMGetBufferFromPool( IN PFileHandle FH )
{
	NTSTATUS   status ;
	ULONG CurrentBufferPointer ;
	WCHAR log[100] ;  
	PAGED_CODE();
	status = KeWaitForSingleObject ( &GV.BufferSemaphore , Executive, KernelMode, FALSE, NULL);
	if ( !NT_SUCCESS(status) ) 
	{
		PutLog(L"can not wait for single object" , status)	;
		return NULL ;
	}
	ExAcquireFastMutex (&GV.BufferPointerLock)  ;
	{
		do 
		{
			if (GV.StartBufferAccsess == COUNTFILEJBUFFER - 1 ) 
			{
				GV.StartBufferAccsess = 0 ;
			}
			else
			{
				GV.StartBufferAccsess ++ ;
			}
		} while(GV.BufferPool[GV.StartBufferAccsess]->File != NULL) ;
		GV.BufferPool[GV.StartBufferAccsess]->File = FH ;
		CurrentBufferPointer = GV.StartBufferAccsess ;
	}
	ExReleaseFastMutex  (&GV.BufferPointerLock)  ;

	return GV.SbScanerPool[CurrentBufferPointer] ;
}


#endif 