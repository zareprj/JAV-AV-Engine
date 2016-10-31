
#include "JBuffer.h"
#include "JMessage.h"

//------------------------------------------------------------------
JBuffer::JBuffer (JFile *Arg , UINT Reserve)
{
	UINT64 FileOffset = 0LL ; 
	ModuleDescriptor = NULL ;
	CurrentBlock = 0 ;
	LastAddress = NULL ;
	if (Arg == NULL)
	{
		LastErrorCode = PARAMETER_INVALID ;
		return ;
	}
	CountChunk = 1 ;
	BufferSize = Reserve ; 
	Buffer =(BYTE *) SMHeapAlloc(Reserve) ;
	if (Buffer = NULL)
	{
		BufferSize = 0 ;
		LastErrorCode = NON_ENOUGH_MEMORY ;
		return  ;
	}
	file = Arg ; 
	if (file->GetFilePosition(FileOffset) == TRUE ) 	
	{
		SetBufferPointer(FileOffset) ;
	}	
}
//------------------------------------------------------------------
JBuffer::JBuffer (JFile *Arg , UINT CountModule , UINT SizeOfModule )
{
	Buffer = NULL ;
	UINT64 FileOffset = 0LL ;
	ModuleDescriptor = NULL ;
	CurrentBlock = 0 ;
	LastAddress = NULL ;
	OffsetFromFristBlock = NULL ;
	if ( Arg == NULL )
	{
		BufferSize = 0 ; 
		LastErrorCode = PARAMETER_INVALID ;
		return ;
	}
	CountChunk = CountModule ;  
	ModuleSize = SizeOfModule; 
	BufferSize  = CountModule * SizeOfModule ;
	Buffer =(BYTE *) SMHeapAlloc(BufferSize) ; 
	if (Buffer == NULL)
	{
		BufferSize = 0 ; 
		LastErrorCode = NON_ENOUGH_MEMORY ;
		return ;
	}
	file = Arg ; 
	ModuleDescriptor = (_ModuleDescriptor *)SMHeapAlloc( CountChunk * sizeof(_ModuleDescriptor) ) ;
	if (ModuleDescriptor == NULL)
	{
		BufferSize = 0 ; 
		SMHeapFree(Buffer) ;
		Buffer= NULL ;
		LastErrorCode = NON_ENOUGH_MEMORY ;
		return ;
	}
	memset(ModuleDescriptor , 0 ,  CountChunk * sizeof(_ModuleDescriptor) );
	for (int i = 0; i <  CountModule ; i ++ )
	{
		(ModuleDescriptor + i)->Pointer = Buffer + i * SizeOfModule ; 
	}

	if (file->GetFilePosition(FileOffset) == TRUE ) 	
	{
		if ( SetBufferPointer(FileOffset) == FALSE ) 
		{
			LastErrorCode = FILE_SEEK_ERROR ;
		}
	}	
	else 
	{
		LastErrorCode = FILE_SEEK_ERROR ;
	}

}
//------------------------------------------------------------------
BYTE JBuffer::operator[](INT Arg) 
{
	UINT Counter  = 0, StartOffset ;
	while (Counter != CountChunk  )
	{
		StartOffset = (ModuleDescriptor+ Counter)->Start - Arg;
		if ( StartOffset >= 0 && 
			 (ModuleDescriptor + Counter)->Limit > Arg )
		{
			(ModuleDescriptor + Counter)->Used = TRUE ;
			return *((ModuleDescriptor + Counter)->Pointer +  StartOffset) ;
		}
		Counter++ ;
	}
	Counter = CurrentBlock ;
	do
	{
		if (CurrentBlock > CountChunk)
		{
			CurrentBlock = 0 ;
		}
		if ((ModuleDescriptor + CurrentBlock)->Used == TRUE  )
		{
			(ModuleDescriptor + CurrentBlock)->Used = FALSE ;
		}
		else
		{
			StartOffset = MIN ( Arg - ( ModuleSize >> 3 ) , 0 )  ; 
			if ( file->Seek(StartOffset , JFile::FBEGIN) == FALSE )
			{
				return 0;
			}
			(ModuleDescriptor + CurrentBlock)->Limit = (ModuleDescriptor + CurrentBlock)->Start + ModuleSize ;
			if  ( file->Read((ModuleDescriptor + CurrentBlock)->Pointer ,ModuleSize)== FALSE)
			{
				return 0;
			}
			StartOffset = Current - (ModuleDescriptor + CurrentBlock)->Start ;
			(ModuleDescriptor + CurrentBlock)->Used = TRUE ;
			return *((ModuleDescriptor + CurrentBlock)->Pointer +  StartOffset) ;
			
		}
	}while (CurrentBlock++ != Counter );
	return 0 ; 
}
//------------------------------------------------------------------
BYTE * JBuffer::GETValidFF(UINT32 Offset)
{
	UINT Counter  = 0, StartOffset ;
	UINT32 Temp ;
	
	while (Counter != CountChunk  )
	{
		StartOffset = Offset - (ModuleDescriptor+ Counter)->Start ;
		if ( StartOffset >= 0 && 
			(ModuleDescriptor + Counter)->Limit > Offset + 0xff  )
		{
			(ModuleDescriptor + Counter)->Used = TRUE ;
			
			return ((ModuleDescriptor + Counter)->Pointer +  StartOffset) ;
		}
		Counter++ ;
	}
	Counter = CurrentBlock ;
	do
	{
		if (CurrentBlock > CountChunk)
		{
			CurrentBlock = 0 ;
		}
		if ((ModuleDescriptor + CurrentBlock)->Used == TRUE  )
		{
			(ModuleDescriptor + CurrentBlock)->Used = FALSE ;
		}
		else
		{
			StartOffset = MIN ( Offset - ( ModuleSize >> 3) , 0 )  ; 
			(ModuleDescriptor + CurrentBlock)->Start = StartOffset ;
			(ModuleDescriptor + CurrentBlock)->Limit = MIN (((ModuleDescriptor + CurrentBlock)->Start + ModuleSize) ,file->GetFileLength() );

			if ( (ModuleDescriptor + Counter)->Limit < Offset + 0xff ) 
			{
				return NULL ; 
			}

			if ( file->Seek(StartOffset , JFile::FBEGIN) == FALSE )
			{
				return NULL;
			}
			Temp = ((ModuleDescriptor + CurrentBlock)->Limit - StartOffset) ;
			if  ( file->Read((ModuleDescriptor + CurrentBlock)->Pointer , Temp )== FALSE)
			{
				return NULL;
			}
			StartOffset = Offset - (ModuleDescriptor + CurrentBlock)->Start ;
			(ModuleDescriptor + CurrentBlock)->Used = TRUE ;
			return ((ModuleDescriptor + CurrentBlock)->Pointer +  StartOffset) ;
		}
	}while ( CurrentBlock ++ != Counter );
	return NULL ;
}
//------------------------------------------------------------------
BOOLEAN JBuffer::SetBufferPointer (UINT32 Index) 
{
	if (Index > file->GetFileLength())
	{
		return FALSE ;
	}
	Current = Index ;
	OffsetFromFristBlock = ModuleDescriptor->Pointer + (Current - ModuleDescriptor->Start ) ;
	if ( ModuleDescriptor->Start > Current )
	{
		LastAddress = 0 ;
	}
	return TRUE ;
}
//---------------------------------------------------------------------
// this method just use first of block for buffering 
/*
FORCEINLINE BYTE *  JBuffer::GetRapidByte()
{
	UINT32 Temp ;
	if ( LastAddress >= OffsetFromFristBlock )
	{
		return OffsetFromFristBlock ++;
	}
	else
	{
		ModuleDescriptor->Start = (OffsetFromFristBlock - ModuleDescriptor->Pointer) + Current  ; 	
		Current = ModuleDescriptor->Start; 
		ModuleDescriptor->Limit = MIN ((ModuleDescriptor->Start + ModuleSize) ,file->FileLength() );
		if ( ModuleDescriptor->Limit < Current )
		{
			return NULL ;
		}
		if ( file->Seek(*(UINT * )&Current , JFile::FBEGIN) == FALSE )
		{
			return NULL;
		}
		Temp = ModuleDescriptor->Limit - ModuleDescriptor->Start ; 
		if  ( file->Read( ModuleDescriptor->Pointer , Temp )== FALSE)
		{
			return NULL;
		}
		OffsetFromFristBlock = 	ModuleDescriptor->Pointer ;
		LastAddress = ModuleDescriptor->Pointer + (ModuleDescriptor->Limit - ModuleDescriptor->Start ) ;
	}
	
	return NULL ;
}
*/
//---------------------------------------------------------------------
BOOLEAN JBuffer::SetRelativePointer (INT Index) 
{
	if (Current + Index > file->GetFileLength() || Current + Index < 0)
	{
		return FALSE ;
	}
	Current += Index ;
	OffsetFromFristBlock += Index ;
	if (ModuleDescriptor->Start > Current  )
	{
		LastAddress = 0 ;
	}
	return TRUE ;
}
//----------------------------------------------------------------
JBuffer::~JBuffer()
{
	SMHeapFree(ModuleDescriptor) ;
	ModuleDescriptor = NULL ;
	SMHeapFree(Buffer);
	Buffer = NULL ;
}
//----------------------------------------------------------------
void JBuffer::SetNULL()
{
	LastAddress = NULL ; 
	OffsetFromFristBlock = NULL ;
}
