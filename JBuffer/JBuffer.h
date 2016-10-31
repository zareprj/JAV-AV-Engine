#ifndef __JBUFFER__
#define __JBUFFER__
#include "BaseObject.h"
#include "JFile.h"
struct _ModuleDescriptor
{
	UINT Start  , Limit ;
	BOOLEAN Used ;
	BYTE *Pointer ;
};

class JBuffer : public BaseObject
{
public :
	JBuffer (JFile *Arg , UINT Reserve = 512) ; 
	JBuffer (JFile *Arg , UINT CountModule , UINT SizeOfModule );
	BYTE operator[](INT ) ;
	BYTE   GETBYTE();
	WORD   GETWORD();
	UINT32  GETUINT32();
	BYTE * GETValidFF(UINT32 Offset) ;
	BYTE * GetValidBlock (UINT32 Offset ) ;
	JFile *file ;
	template <class T>
	T* GetBuffer2(UINT32 Offset) 
	{
		UINT Counter  = 0, StartOffset ;
		do{
			StartOffset = Offset - (ModuleDescriptor+ Counter)->Start ;
			if ( StartOffset >= 0 && 
				(ModuleDescriptor + Counter)->Limit > Offset + sizeof(T)  )
			{
				(ModuleDescriptor + Counter)->Used = TRUE ;

				return (T*)((ModuleDescriptor + Counter)->Pointer +  StartOffset) ;
			}
			Counter++ ;
		}while (Counter != CountChunk ) ; 
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
				if (Offset < 0 )
				{
					return NULL ;
				}
				StartOffset = MAX ( Offset - ( ModuleSize >> 8 ) , 0 )  ; 
				(ModuleDescriptor + CurrentBlock)->Start = StartOffset ;
				(ModuleDescriptor + CurrentBlock)->Limit = MIN (((ModuleDescriptor + CurrentBlock)->Start + ModuleSize) ,file->GetFileLength() );

				if ( (ModuleDescriptor + Counter)->Limit < Offset + sizeof(T) ) 
				{
					return NULL ; 
				}

				if ( file->Seek(StartOffset , JFile::FBEGIN) == FALSE )
				{
					return NULL;
				}

				if  ( file->Read((ModuleDescriptor + CurrentBlock)->Pointer , (ModuleDescriptor + CurrentBlock)->Limit - StartOffset )== FALSE)
				{
					return NULL;
				}
				StartOffset = Offset - (ModuleDescriptor + CurrentBlock)->Start ;
				(ModuleDescriptor + CurrentBlock)->Used = TRUE ;
				return (T*)((ModuleDescriptor + CurrentBlock)->Pointer +  StartOffset) ;
			}
		}while ( CurrentBlock ++ != Counter );
		return NULL ;
	}
	
	
	template <class T>
	T* GetBuffer()
	{
		UINT Counter  = 0 , StartOffset;
		UINT32 Temp ;
		
		
		do{
			StartOffset = Current - (ModuleDescriptor+ Counter)->Start ;
			if ( (INT)StartOffset >= 0 && 
				(ModuleDescriptor + Counter)->Limit > Current + sizeof(T)  )
			{
				(ModuleDescriptor + Counter)->Used = TRUE ;
				Current += sizeof(T) ;
			//Must be check
				OffsetFromFristBlock += sizeof(T) ;
				if (ModuleDescriptor->Start > Current  )
				{
					LastAddress = 0 ;
				}
			//must be check 
				return (T*)((ModuleDescriptor + Counter)->Pointer +  StartOffset) ;
			}
			Counter++ ;
		}while (Counter != CountChunk );
		Counter = CurrentBlock  ;
		do
		{
			if (CurrentBlock >= CountChunk)
			{
				CurrentBlock = 0 ;
			}
			if ((ModuleDescriptor + CurrentBlock)->Used == TRUE  )
			{
				(ModuleDescriptor + CurrentBlock)->Used = FALSE ;
			}
			else
			{
				if (Current < 0 )
				{
					throw BUFFER_ERROR ;
					return NULL ;
				}
				StartOffset = MAX ( (INT)Current - ( ModuleSize >> 3 ) , 0 )  ; 
				(ModuleDescriptor + CurrentBlock)->Start = StartOffset ;
				(ModuleDescriptor + CurrentBlock)->Limit = MIN (((ModuleDescriptor + CurrentBlock)->Start + ModuleSize) ,file->GetFileLength() );

				if ( (ModuleDescriptor + Counter)->Limit < Current + sizeof(T) ) 
				{
					throw BUFFER_ERROR ;
					return NULL ; 
				}

				if ( file->Seek(StartOffset , JFile::FBEGIN) == FALSE )
				{
					throw FILE_SEEK_ERROR ;
					return NULL;
				}
				Temp = (ModuleDescriptor + CurrentBlock)->Limit - StartOffset ;
				if  ( file->Read((ModuleDescriptor + CurrentBlock)->Pointer , Temp)== FALSE)
				{
					throw FILE_READ_ERROR ;
					return NULL;
				}
				StartOffset = Current - (ModuleDescriptor + CurrentBlock)->Start ;
				(ModuleDescriptor + CurrentBlock)->Used = TRUE ;
				Current += sizeof(T);
				return (T*)((ModuleDescriptor + CurrentBlock)->Pointer +  StartOffset) ;
			}
			CurrentBlock ++ ;
		}while ( CurrentBlock != Counter );
		return NULL ;
	}
	BOOLEAN SetBufferPointer (UINT32 Index) ;
	BOOLEAN SetRelativePointer (INT Index) ;
	void SetNULL() ;
	//FORCEINLINE BYTE *  GetRapidByte();
	FORCEINLINE BYTE *  JBuffer::GetRapidByte()
	{
		UINT32 Temp ;
		if ( LastAddress >= OffsetFromFristBlock )
		{
			return OffsetFromFristBlock ++;
		}
		else
		{
			ModuleDescriptor->Start = (OffsetFromFristBlock - ModuleDescriptor->Pointer) + ModuleDescriptor->Start  ; 	
			ModuleDescriptor->Limit = MIN ((ModuleDescriptor->Start + ModuleSize) ,file->GetFileLength() );
			if ( ModuleDescriptor->Limit < ModuleDescriptor->Start )
			{
				throw BUFFER_ERROR ;
				return NULL ;
			}
			if ( file->Seek(*(UINT * )&ModuleDescriptor->Start , JFile::FBEGIN) == FALSE )
			{
				throw FILE_SEEK_ERROR ;
				return NULL;
			}
			Temp = ModuleDescriptor->Limit - ModuleDescriptor->Start ; 
			if  ( file->Read( ModuleDescriptor->Pointer , Temp )== FALSE)
			{
				throw FILE_READ_ERROR ;
				return NULL;
			}
			OffsetFromFristBlock = 	ModuleDescriptor->Pointer ;
			LastAddress = ModuleDescriptor->Pointer + (ModuleDescriptor->Limit - ModuleDescriptor->Start ) ;
			return OffsetFromFristBlock ++;
		}
		throw BUFFER_ERROR ;
		return NULL ;
	}
	~JBuffer(); 
private :
	UINT32 Current ;
	
	BYTE  *Buffer  , *OffsetFromFristBlock , *LastAddress;
	UINT  BufferSize , CountChunk ;
	UINT CurrentBlock , ModuleSize   ;
	_ModuleDescriptor *ModuleDescriptor ;
};
#endif 