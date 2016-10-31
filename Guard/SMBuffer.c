#include "SMBuffer.h"
#include "FileApiBYIRP.h"
#include "log.h"

#ifdef ALLOC_PRAGMA
	#pragma alloc_text( PAGE ,SMBufferInit )
	#pragma alloc_text( PAGE ,SMSetBufferPointer )
	#pragma alloc_text( PAGE ,SMSetRelativePointer )
	#pragma alloc_text( PAGE ,SMGetBufferOffset )
	#pragma alloc_text( PAGE ,SMGetBufferOffsetForMemTree )
	#pragma alloc_text( PAGE ,SMGetBuffer )
	#pragma alloc_text( PAGE ,SMSetBufferFile)
	#pragma alloc_text( PAGE ,SMBufferUninitialize )
#endif
#define AlignValue ~511

NTSTATUS SMBufferInit (IN PSMBuffer *ImpBuffer , ULONG CountModule , ULONG SizeOfModule )
{
	NTSTATUS status = STATUS_SUCCESS ;
	ULONG i ;
	PAGED_CODE();
	
	if ( ImpBuffer == NULL ) //|| Arg == NULL )
	{
		PutLog(L"Invalid Parameter" , STATUS_INVALID_PARAMETER) ;
		return STATUS_INVALID_PARAMETER;
	} 

	*ImpBuffer = (SMBuffer *) ExAllocatePoolWithTag( NonPagedPool ,sizeof(SMBuffer) , DRIVERTAG ) ;
	if (*ImpBuffer == NULL )
	{
		*ImpBuffer = NULL ;
		PutLog (L"Can Not Alloc Memory" ,STATUS_NO_MEMORY )	 ;
		return STATUS_NO_MEMORY;
	}

	memset(*ImpBuffer , 0 , sizeof(SMBuffer));
	
	(*ImpBuffer)->Config = 0 ;
	(*ImpBuffer)->CountChunk = CountModule ;  
	(*ImpBuffer)->ModuleSize = SizeOfModule; 

    (*ImpBuffer)->Buffer = (UCHAR*)ExAllocatePoolWithTag( NonPagedPool , (CountModule * SizeOfModule) , DRIVERTAG ) ;
	
	if ((*ImpBuffer)->Buffer == NULL)
	{
		ExFreePool(*ImpBuffer) ;
		*ImpBuffer = NULL ;
		PutLog (L"Can Not Alloc Memory" ,STATUS_NO_MEMORY )	 ;
		return STATUS_NO_MEMORY;
	}

	(*ImpBuffer)->ModuleDescriptor = (SMModuleDescriptor *)ExAllocatePoolWithTag( NonPagedPool , (*ImpBuffer)->CountChunk * sizeof(SMModuleDescriptor)  , DRIVERTAG ) ;
	if ((*ImpBuffer)->ModuleDescriptor == NULL)
	{
		ExFreePool((*ImpBuffer)->Buffer) ;
		ExFreePool(*ImpBuffer) ;
		*ImpBuffer = NULL ;
		PutLog (L"Can Not Alloc Memory" ,STATUS_NO_MEMORY )	 ;
		return STATUS_NO_MEMORY;
	}

	for ( i = 0; i <  (*ImpBuffer)->CountChunk ; i ++ )
	{
		((*ImpBuffer)->ModuleDescriptor + i)->Pointer = (*ImpBuffer)->Buffer + i * (*ImpBuffer)->ModuleSize ; 
		((*ImpBuffer)->ModuleDescriptor + i)->mdl = IoAllocateMdl(((*ImpBuffer)->ModuleDescriptor + i)->Pointer, (*ImpBuffer)->ModuleSize, FALSE, TRUE, 0);
		if (((*ImpBuffer)->ModuleDescriptor + i)->mdl == NULL )
		{
			while ( i != 0 )
			{
				i--;
				IoFreeMdl(((*ImpBuffer)->ModuleDescriptor + i)->mdl);
			}
			ExFreePool((*ImpBuffer)->Buffer) ;
			ExFreePool(*ImpBuffer) ;
			*ImpBuffer = NULL ;
			PutLog (L"Can Not Alloc Memory" ,STATUS_NO_MEMORY )	 ;
			return STATUS_NO_MEMORY;
		}
		MmBuildMdlForNonPagedPool(((*ImpBuffer)->ModuleDescriptor + i)->mdl);
	}
	(*ImpBuffer)->phEvent =(PKEVENT) ExAllocatePoolWithTag( NonPagedPool ,sizeof(KEVENT) , DRIVERTAG ) ;
	return status ;

}
//-----------------------------------------------------------------------
NTSTATUS SMSetBufferFile( IN SMBuffer *ImpBuffer )
{
	ULONG i ;
	NTSTATUS status ;
	PAGED_CODE();
	ImpBuffer->Irp  = IoAllocateIrp(ImpBuffer->File->FileSysDevice->StackSize, FALSE);
	if (!(ImpBuffer->Irp))
	{
		return STATUS_INSUFFICIENT_RESOURCES;
	}
	
	for ( i = 0; i <  ImpBuffer->CountChunk ; i ++ )
	{
		(ImpBuffer->ModuleDescriptor + i)->Used = 0 ;
		(ImpBuffer->ModuleDescriptor + i)->Limit = 0;
		(ImpBuffer->ModuleDescriptor + i)->Start = 0;
	}

	status = IRPGetFileSize ( ImpBuffer,  (LARGE_INTEGER *)&(ImpBuffer->FileSize) ) ;
	if ( !NT_SUCCESS(status)  )
	{
		PutLog (L"Can Get File Size" ,status ) ;
		return STATUS_OBJECT_NO_LONGER_EXISTS ;
	}

	if ( SMSetBufferPointer( ImpBuffer , 0) == FALSE ) 
	{
		PutLog (L"Can Not Alloc Memory" ,STATUS_OBJECT_NO_LONGER_EXISTS )	 ;
		return STATUS_OBJECT_NO_LONGER_EXISTS ;
	}

	return STATUS_SUCCESS ;
}
//-----------------------------------------------------------------------
/*NTSTATUS SetBufferFile4App( IN JBuffer *ImpBuffer  , PFileHandle FH)
{
	ULONG i ;
	NTSTATUS status ;

	ImpBuffer->Irp  = IoAllocateIrp(FH->FileSysDevice->StackSize, FALSE);
	if (!(ImpBuffer->Irp))
	{
		return STATUS_INSUFFICIENT_RESOURCES;
	}

	for ( i = 0; i <  ImpBuffer->CountChunk ; i ++ )
	{
		(ImpBuffer->ModuleDescriptor + i)->Used = (ImpBuffer->ModuleDescriptor + i)->Limit = (ImpBuffer->ModuleDescriptor + i)->Start = 0;
	}

	status = IRPGetFileSize ( ImpBuffer,  (LARGE_INTEGER *)&(ImpBuffer->FileSize) ) ;
	if ( !NT_SUCCESS(status)  )
	{
		PutLog (L"Can Get File Size" ,status ) ;
		return STATUS_OBJECT_NO_LONGER_EXISTS ;
	}

	if ( SetBufferPointer( ImpBuffer , 0) == FALSE ) 
	{
		PutLog (L"Can Not Alloc Memory" ,STATUS_OBJECT_NO_LONGER_EXISTS )	 ;
		return STATUS_OBJECT_NO_LONGER_EXISTS ;
	}

	return STATUS_SUCCESS ;
}*/
//-----------------------------------------------------------------------
BOOLEAN SMSetBufferPointer( SMBuffer *ImpBuffer ,unsigned __int64 Index )
{
	NTSTATUS status ;
	PAGED_CODE();

	ASSERT(ImpBuffer!=NULL); 

	if ( Index > ImpBuffer->FileSize )
	{
		return FALSE ;
	}
	ImpBuffer->Current = Index ;
	return TRUE ;
}
//------------------------------------------------------
BOOLEAN SMSetRelativePointer (IN SMBuffer *ImpBuffer , int Offset)  
{
	NTSTATUS status ;
	PAGED_CODE();

	ASSERT(ImpBuffer!=NULL); 

	if ((UINT64)(ImpBuffer->Current + Offset) > ImpBuffer->FileSize || ImpBuffer->Current + Offset < 0)
	{
		return FALSE ;
	}
	ImpBuffer->Current += Offset ;
	return TRUE ;
}
//-----------------------------------------------------------------------
PVOID SMGetBufferOffset( IN SMBuffer *ImpBuffer,unsigned __int64 Offset , ULONG SizeofBuffer )
{
	NTSTATUS status;
	ULONG Counter  = 0  , SizeBuffer;
	__int64  StartOffset ;
	PAGED_CODE();

	do{
		StartOffset = Offset - (ImpBuffer->ModuleDescriptor+ Counter)->Start ;
		if ( StartOffset >= 0 && 
			(ImpBuffer->ModuleDescriptor + Counter)->Limit > Offset + SizeofBuffer  )
		{
			(ImpBuffer->ModuleDescriptor + Counter)->Used = TRUE ;

			return ((ImpBuffer->ModuleDescriptor + Counter)->Pointer +  StartOffset) ;
		}
		Counter++ ;
	}while (Counter < ImpBuffer->CountChunk) ; 
	ImpBuffer->CurrentBlock = 0 ;
	do
	{
		if (ImpBuffer->CurrentBlock >= ImpBuffer->CountChunk)
		{
			ImpBuffer->CurrentBlock = 0 ;
		}
		if ((ImpBuffer->ModuleDescriptor + ImpBuffer->CurrentBlock)->Used == TRUE  )
		{
			(ImpBuffer->ModuleDescriptor + ImpBuffer->CurrentBlock)->Used = FALSE ;
		}
		else
		{
			UINT64 u64TempLimit;
			StartOffset = Offset & AlignValue   ; 
			u64TempLimit = (UINT64) MIN ( (UINT64)(StartOffset + ImpBuffer->ModuleSize) , ImpBuffer->FileSize );	
			
			if ( u64TempLimit < Offset + SizeofBuffer ) 
			{
				PutLog(L"Offset over boundary" , STATUS_UNSUCCESSFUL );
				return NULL ; 
			}

			(ImpBuffer->ModuleDescriptor + ImpBuffer->CurrentBlock)->Start = StartOffset ;
			(ImpBuffer->ModuleDescriptor + ImpBuffer->CurrentBlock)->Limit = u64TempLimit;	


			SizeBuffer =(ULONG) ((ImpBuffer->ModuleDescriptor + ImpBuffer->CurrentBlock)->Limit - StartOffset) ;
			ASSERT(SizeBuffer <= ImpBuffer->ModuleSize);
			Counter = SizeBuffer ;
			status = ReadByIRPFromFileObject (ImpBuffer, (ImpBuffer->ModuleDescriptor + ImpBuffer->CurrentBlock) , &SizeBuffer , StartOffset  ) ;
			if (!NT_SUCCESS(status) || SizeBuffer != Counter)
			{
				PutLog(L"Can not read File With Irp" , status );
				return NULL ; 
			}

			StartOffset = Offset - (ImpBuffer->ModuleDescriptor + ImpBuffer->CurrentBlock)->Start ;
			(ImpBuffer->ModuleDescriptor + ImpBuffer->CurrentBlock)->Used = TRUE ;
			return ((ImpBuffer->ModuleDescriptor + ImpBuffer->CurrentBlock)->Pointer +  StartOffset) ;
		}
		ImpBuffer->CurrentBlock ++ ;
	}while ( TRUE );
	PutLog(L"Buffer Error" , STATUS_UNSUCCESSFUL );
	return NULL ;
}
//-----------------------------------------------------------------------
PVOID SMGetBufferOffsetForMemTree( IN SMBuffer *ImpBuffer,unsigned __int64 Offset , ULONG SizeofBuffer )
{
	NTSTATUS status;
	ULONG Counter  = 0  , SizeBuffer;
	__int64  StartOffset ;
	PAGED_CODE();

	do{
		StartOffset = Offset - (ImpBuffer->ModuleDescriptor+ Counter)->Start ;
		if ( StartOffset >= 0 && 
			(ImpBuffer->ModuleDescriptor + Counter)->Limit > Offset + SizeofBuffer  )
		{
			(ImpBuffer->ModuleDescriptor + Counter)->Used = TRUE ;

			return ((ImpBuffer->ModuleDescriptor + Counter)->Pointer +  StartOffset) ;
		}
		Counter++ ;
	}while (Counter < ImpBuffer->CountChunk) ; 
	ImpBuffer->CurrentBlock = 0 ;
	do
	{
		if (ImpBuffer->CurrentBlock >= ImpBuffer->CountChunk)
		{
			ImpBuffer->CurrentBlock = 0 ;
		}
		if ((ImpBuffer->ModuleDescriptor + ImpBuffer->CurrentBlock)->Used == TRUE  )
		{
			(ImpBuffer->ModuleDescriptor + ImpBuffer->CurrentBlock)->Used = FALSE ;
		}
		else
		{
			StartOffset = Offset & AlignValue   ; 
			(ImpBuffer->ModuleDescriptor + ImpBuffer->CurrentBlock)->Start = StartOffset ;
			(ImpBuffer->ModuleDescriptor + ImpBuffer->CurrentBlock)->Limit = (UINT64) MIN ( (UINT64)(StartOffset + ImpBuffer->ModuleSize) , ImpBuffer->FileSize );	

			SizeBuffer =(ULONG) ((ImpBuffer->ModuleDescriptor + ImpBuffer->CurrentBlock)->Limit - StartOffset) ;
			ASSERT(SizeBuffer <= ImpBuffer->ModuleSize);
			Counter = SizeBuffer ;
			status = ReadByIRPFromFileObject (ImpBuffer, (ImpBuffer->ModuleDescriptor + ImpBuffer->CurrentBlock) , &SizeBuffer , StartOffset  ) ;
			if (!NT_SUCCESS(status) || SizeBuffer != Counter)
			{
				PutLog(L"Can not read File With Irp" , status );
				return NULL ; 
			}

			StartOffset = Offset - (ImpBuffer->ModuleDescriptor + ImpBuffer->CurrentBlock)->Start ;
			(ImpBuffer->ModuleDescriptor + ImpBuffer->CurrentBlock)->Used = TRUE ;
			return ((ImpBuffer->ModuleDescriptor + ImpBuffer->CurrentBlock)->Pointer +  StartOffset) ;
		}
		ImpBuffer->CurrentBlock ++ ;
	}while ( TRUE );
	PutLog(L"Buffer Error" , STATUS_UNSUCCESSFUL );
	return NULL ;
}//-----------------------------------------------------------------------
PVOID SMGetBuffer(IN SMBuffer *ImpBuffer, ULONG SizeofBuffer ) 
{
	NTSTATUS status;
	ULONG Counter  = 0 , SizeBuffer;
	__int64  StartOffset ;
	PAGED_CODE();

	do{
		StartOffset = ImpBuffer->Current - (ImpBuffer->ModuleDescriptor+ Counter)->Start ;
		if ( StartOffset >= 0 && 
			(ImpBuffer->ModuleDescriptor + Counter)->Limit > (UINT64)(ImpBuffer->Current + SizeofBuffer)  )
		{
			(ImpBuffer->ModuleDescriptor + Counter)->Used = TRUE ;
			ImpBuffer->Current += SizeofBuffer ;

			return ((ImpBuffer->ModuleDescriptor + Counter)->Pointer +  StartOffset) ;
		}
		Counter++ ;
	}while (Counter < ImpBuffer->CountChunk ) ; 
	ImpBuffer->CurrentBlock = 0 ;
	do
	{
		if (ImpBuffer->CurrentBlock >= ImpBuffer->CountChunk)
		{
			ImpBuffer->CurrentBlock = 0 ;
		}
		if ((ImpBuffer->ModuleDescriptor + ImpBuffer->CurrentBlock)->Used == TRUE  )
		{
			(ImpBuffer->ModuleDescriptor + ImpBuffer->CurrentBlock)->Used = FALSE ;
		}
		else
		{
			UINT64 u64TempLimit;
			if (ImpBuffer->Current < 0 )
			{
				PutLog(L"Offset is negative" , STATUS_UNSUCCESSFUL );
				return NULL ;
			}
			StartOffset = ImpBuffer->Current & AlignValue  ; 
			u64TempLimit = MIN ((UINT64)(StartOffset + ImpBuffer->ModuleSize) ,ImpBuffer->FileSize );
			
			

			if ( u64TempLimit < (UINT64)(ImpBuffer->Current + SizeofBuffer) ) 
			{
				PutLog(L"Offset over boundary" , STATUS_UNSUCCESSFUL );
				return NULL ; 
			}
			
			(ImpBuffer->ModuleDescriptor + ImpBuffer->CurrentBlock)->Start = StartOffset ;
			(ImpBuffer->ModuleDescriptor + ImpBuffer->CurrentBlock)->Limit = u64TempLimit ;

			SizeBuffer = (ULONG)((ImpBuffer->ModuleDescriptor + ImpBuffer->CurrentBlock)->Limit - StartOffset) ;
			Counter = SizeBuffer ;
			status = ReadByIRPFromFileObject (ImpBuffer , (ImpBuffer->ModuleDescriptor + ImpBuffer->CurrentBlock) , &SizeBuffer , StartOffset  ) ;
			if (!NT_SUCCESS(status) || SizeBuffer != Counter)
			{
				PutLog(L"Can not read File With Irp" , status );
				return NULL ; 
			}

			StartOffset = ImpBuffer->Current - (ImpBuffer->ModuleDescriptor + ImpBuffer->CurrentBlock)->Start ;
			(ImpBuffer->ModuleDescriptor + ImpBuffer->CurrentBlock)->Used = TRUE ;
			ImpBuffer->Current += SizeofBuffer ;
			return ((ImpBuffer->ModuleDescriptor + ImpBuffer->CurrentBlock)->Pointer +  StartOffset) ;
		}
		ImpBuffer->CurrentBlock ++ ;
	}while ( TRUE );
	PutLog(L"Buffer Error" , STATUS_UNSUCCESSFUL );
	return NULL ;
}
//------------------------------------------------------------------------------------
void SMBufferUninitialize(SMBuffer **ImpBuffer)
{
	ULONG i = 0 ;
	PAGED_CODE();

	for ( i = 0; i <  (*ImpBuffer)->CountChunk ; i ++ )
	{
		IoFreeMdl(((*ImpBuffer)->ModuleDescriptor + i)->mdl);
	}
	ExFreePool((*ImpBuffer)->ModuleDescriptor) ;
	ExFreePool((*ImpBuffer)->Buffer) ;
	ExFreePool((*ImpBuffer)->phEvent);
	ExFreePool(*ImpBuffer) ;
	*ImpBuffer = NULL ;
}