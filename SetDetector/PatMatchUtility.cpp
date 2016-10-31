#include "PatMatchUtility.h"

BOOLEAN PatMatchUtility::RetrieveFilePackerType(UINT8 * i_pu8Sb , UINT16 i_u16Size ,UINT32 i_u32Offset ,UINT32 i_u32Type , JBuffer *i_pocBuffer , FileInfo  *i_pocFileInfo ) 
{
	enum 
	{
		DirectAccess  = 0 ,
		ReadOffset = 1 , 
		ReadReletiveOffset = 2 ,
	};
	PVOID ptemp ;
	try

	{
		if ( i_pocBuffer->SetBufferPointer(i_pocFileInfo->EntryPointOffset)== FALSE ) 
		{
			return FALSE; ;
		} 
		switch ( i_u32Type )
		{
		case DirectAccess: 

			if ( i_pocBuffer->SetRelativePointer(i_u32Offset) == FALSE ) 
			{
				return FALSE ;
			}
			break;
		case ReadOffset :
			if ( i_pocBuffer->SetRelativePointer(i_u32Offset) == FALSE ) 
			{
				return FALSE ;
			}
			ptemp = (i_pocBuffer->GetBuffer<DWORD>());
			if (ptemp == NULL )  
			{
				return false ;
			}

			i_u32Offset = *(DWORD *)ptemp ;	
			i_u32Offset -= i_pocFileInfo->ImageBase ; 
			i_u32Offset = i_pocFileInfo->RvaToOffset(i_u32Offset) ;

			if ( i_pocBuffer->SetBufferPointer(i_u32Offset) == FALSE ) 
			{
				return FALSE ;
			}

			break ;
		case ReadReletiveOffset :
			{
				UINT32 u32TmpOffset ;
				if ( i_pocBuffer->SetRelativePointer(i_u32Offset) == FALSE ) 
				{
					return FALSE ;
				}

				u32TmpOffset = i_pocFileInfo->EntryPointRva + i_u32Offset ;   

				ptemp = (i_pocBuffer->GetBuffer<DWORD>());
				if (ptemp == NULL )  
				{
					return false ;
				}

				i_u32Offset = *(DWORD *)ptemp ;	

				u32TmpOffset += i_u32Offset+4;

				u32TmpOffset = i_pocFileInfo->RvaToOffset(u32TmpOffset);
				if (u32TmpOffset == (DWORD) -1)
				{
					return FALSE;
				}

				if ( i_pocBuffer->SetBufferPointer(u32TmpOffset) == FALSE ) 
				{
					return FALSE ;
				}
			}
			break;
		}
		if (CheckPattern ( i_pu8Sb  , i_u16Size , i_pocBuffer) == TRUE)
		{
			return TRUE;
		}

	}
	catch (...)
	{
		;
	}
	return FALSE ;

}
//-------------------------------------------------------------------------
BOOLEAN PatMatchUtility::GetPatternType(UINT8 * i_pu8Sb , UINT16 i_u16Size ,UINT32 i_u32Offset ,UINT32 i_u32Type , JBuffer *i_pocBuffer , FileInfo  *i_pocFileInfo ) 
{
	enum 
	{
		DirectAccess  = 0 ,
		ReadOffset = 1 , 
		ReadReletiveOffset = 2 ,
	};
	try
	{
		if ( i_pocBuffer->SetBufferPointer(i_pocFileInfo->EntryPointOffset)== FALSE ) 
		{
			return FALSE; ;
		} 
		switch ( i_u32Type )
		{
		case DirectAccess: 

			if ( i_pocBuffer->SetRelativePointer(i_u32Offset) == FALSE ) 
			{
				return FALSE ;
			}
			break;
		case ReadOffset :
			if ( i_pocBuffer->SetRelativePointer(i_u32Offset) == FALSE ) 
			{
				return FALSE ;
			}

			i_u32Offset = *(i_pocBuffer->GetBuffer<DWORD>());
			i_u32Offset -= i_pocFileInfo->ImageBase ; 
			i_u32Offset = i_pocFileInfo->RvaToOffset(i_u32Offset) ;

			if ( i_pocBuffer->SetBufferPointer(i_u32Offset) == FALSE ) 
			{
				return FALSE ;
			}

			break ;
		case ReadReletiveOffset :
			{
				UINT32 u32TmpOffset ;
				if ( i_pocBuffer->SetRelativePointer(i_u32Offset) == FALSE ) 
				{
					return FALSE ;
				}

				u32TmpOffset = i_pocFileInfo->EntryPointRva + i_u32Offset ;   

				i_u32Offset = *(i_pocBuffer->GetBuffer<DWORD>());

				u32TmpOffset += i_u32Offset+4;
				
				u32TmpOffset = i_pocFileInfo->RvaToOffset(u32TmpOffset);
				
				if ( i_pocBuffer->SetBufferPointer(u32TmpOffset) == FALSE ) 
				{
					return FALSE ;
				}
			}
			break ;
		}
		UINT8 u8Count = 0 ;
		while (u8Count < i_u16Size)
		{
			UINT8 u8tmp = *i_pocBuffer->GetRapidByte() ; 
			i_pu8Sb[u8Count]= u8tmp;
			u8Count++;
		}
	}
	catch (...)
	{
		return FALSE ;
	}
	return TRUE ;

}

//-------------------------------------------------------------------------
BOOLEAN PatMatchUtility::CheckPattern ( UINT8  i_u8Sb[] , UINT16 i_u16Size , JBuffer *i_pocBuffer )
{
	UINT8 u8Count = 0 ;
	try
	{
		while (u8Count < i_u16Size)
		{
			if (i_u8Sb[u8Count] == 0xff)
			{	
				u8Count ++ ;
				if (i_u8Sb[u8Count] != 0xff)
				{
					i_pocBuffer->SetRelativePointer(i_u8Sb[u8Count]);
					u8Count ++ ;
					continue ;
				}
			}
			UINT8 u8tmp = *i_pocBuffer->GetRapidByte() ;
			if (i_u8Sb[u8Count] != u8tmp)
			{
				return FALSE ;
			}
			u8Count++ ;
		}
	}
	catch(...)
	{
		;
	}
	return TRUE ;
}
//-------------------------------------------------------------------------
UINT64 PatMatchUtility::MakeCRC(INT32 i_i32Start , UINT32 i_u32Size , FileInfo  *i_pocFileInfo , JFile *i_pocFile)
{
	INT32  i32Dummy ;
	INT64  i64SeekParameter  ;
	size_t  stReadSize ; 

	i64SeekParameter = i_pocFileInfo->EntryPointOffset + i_i32Start  ;

	if ( i_pocFile->Seek(i64SeekParameter , JFile::FBEGIN)	== FALSE ) 
	{
		return 0 ;
	}

	stReadSize = sizeof(INT32) ; 
	if ( i_pocFile->Read (&i32Dummy,stReadSize) == FALSE ) 
	{
		return 0 ;
	}

	i32Dummy -= i_pocFileInfo->ImageBase ; 
	i32Dummy = i_pocFileInfo->RvaToOffset(i32Dummy) ;
	if ( i32Dummy == -1 )
	{
		return 0 ;
	}

	i64SeekParameter = i32Dummy ;
	if ( i_pocFile->Seek(i64SeekParameter , JFile::FBEGIN)	== FALSE ) 
	{
		return 0 ;
	}
	if ( i32Dummy > i_pocFileInfo->EntryPointOffset)
	{
		return 0 ;
	}
	if ( i32Dummy +  i_u32Size > i_pocFileInfo->EntryPointOffset )
	{
		i_u32Size = i_pocFileInfo->EntryPointOffset - i32Dummy   ;
	}

	return TakeCrc(i_u32Size, i_pocFile) ;
}
//-----------------------------------------------------------------------------------------------
UINT64 PatMatchUtility::MakeCRC1(INT32 i_i32Start , UINT32 i_u32Size , FileInfo  *i_pocFileInfo , JFile *i_pocFile)
{
	INT32  i32Dummy ;
	INT64  i64SeekParameter ; 

	i64SeekParameter = i_pocFileInfo->EntryPointOffset + i_i32Start ;
	if ( i_pocFile->Seek(i64SeekParameter , JFile::FBEGIN)	== FALSE ) 
	{
		return 0 ;
	}
	i32Dummy = i_pocFileInfo->MaxSizeSection( i_pocFileInfo->EntryPointOffset ) ;
	if ( i32Dummy == -1 )
	{
		return 0  ;
	}
	if (  i32Dummy <= i64SeekParameter  )
	{
		return 0 ;
	}
	if ( i32Dummy < i64SeekParameter +  i_u32Size )
	{
		i_u32Size = i32Dummy - i64SeekParameter ;
	}

	return TakeCrc(i_u32Size , i_pocFile) ;
}
//-----------------------------------------------------------------------------------------------
UINT64 PatMatchUtility::MakeCRC2(UINT32 i_u32Size , FileInfo  *i_pocFileInfo , JFile *i_pocFile) 
{
	INT32  i32Dummy ;
	INT64  i64SeekParameter ; 
	i32Dummy = i_pocFileInfo->MinFirstSection() ;
	if ( i32Dummy == -1 )
	{
		return 0  ;
	}
	i64SeekParameter = i32Dummy ;
	if ( i_pocFile->Seek(i64SeekParameter , JFile::FBEGIN)	== FALSE ) 
	{
		return 0 ;
	}

	if ( i32Dummy +  i_u32Size > i_pocFileInfo->MaxFirstSection() )
	{
		i_u32Size = i_pocFileInfo->MaxFirstSection() - i32Dummy   ;
	}
	return TakeCrc(i_u32Size , i_pocFile) ;
}
//-----------------------------------------------------------------------------------------------
UINT64 PatMatchUtility::MakeCRC3( INT32 i_i32Start , INT32 i_i32ExtendedOffset ,UINT32 i_u32Size , FileInfo  *i_pocFileInfo , JFile *i_pocFile )
{
	INT32   i32Dummy  ;
	INT64   i64SeekParameter ;
	size_t  stReadSize ; 

	i64SeekParameter = i_pocFileInfo->EntryPointOffset + i_i32Start ;

	if ( i_pocFile->Seek(i64SeekParameter , JFile::FBEGIN)	== FALSE ) 
	{
		return 0 ;
	}

	stReadSize = sizeof(INT32) ; 
	if ( i_pocFile->Read ( &i32Dummy,stReadSize) == FALSE ) 
	{
		return 0 ;
	}
	i32Dummy -= i_pocFileInfo->ImageBase ; 
	i32Dummy  = i_pocFileInfo->RvaToOffset(i32Dummy) ;
	if ( i32Dummy == -1 )
	{
		return 0 ;
	}

	i64SeekParameter = i32Dummy + i_i32ExtendedOffset ;
	
	if ( i_pocFile->Seek(i64SeekParameter , JFile::FBEGIN)	== FALSE ) 
	{
		return 0 ;
	}

	i64SeekParameter = sizeof(INT32) ; 
	if ( i_pocFile->Read ( &i32Dummy,*(UINT32*)& i64SeekParameter) == FALSE ) 
	{
		return 0 ;
	}
	i32Dummy -= i_pocFileInfo->ImageBase ; 
	i32Dummy = i_pocFileInfo->RvaToOffset(i32Dummy) ;
	if ( i32Dummy == -1 )
	{
		return 0 ;
	}
	i64SeekParameter = i32Dummy  ;
	if ( i_pocFile->Seek(i64SeekParameter , JFile::FBEGIN)	== FALSE ) 
	{
		return 0 ;
	}
	return TakeCrc(i_u32Size , i_pocFile); 
}
//-----------------------------------------------------------------------------------------------
UINT64 PatMatchUtility::MakeCRC4(INT32 i_i32Start , INT32 i_i32ExtendedOffset ,UINT32 i_u32Size , FileInfo  *i_pocFileInfo , JFile *i_pocFile )
{
	UINT32 u32StartOfSeconedPart ;
	INT32  i32Dummy , i32StartComplierCoed ;
	INT64  i64SeekParameter ;
	size_t  stReadSize ; 

	i64SeekParameter = i_pocFileInfo->EntryPointOffset + i_i32Start ;

	if ( i_pocFile->Seek(i64SeekParameter , JFile::FBEGIN)	== FALSE ) 
	{
		return 0 ;
	}

	stReadSize = sizeof(INT32) ; 
	if ( i_pocFile->Read ( &i32Dummy,stReadSize) == FALSE  || stReadSize != sizeof(INT32) ) 
	{
		return 0 ;
	}
	u32StartOfSeconedPart = i32Dummy + i_pocFileInfo->EntryPointOffset + i_i32Start + 4 ;
	i32Dummy = i_pocFileInfo->MinFirstSection() ;
	if ( i32Dummy == -1 )
	{
		return 0  ;
	}
	i64SeekParameter = i32Dummy ;
	if ( i_pocFile->Seek(i64SeekParameter , JFile::FBEGIN)	== FALSE ) 
	{
		return 0 ;
	}

	if ( i32Dummy +  i_u32Size > u32StartOfSeconedPart )
	{
		i_u32Size = u32StartOfSeconedPart - i32Dummy  ;
	}
	return TakeCrc(i_u32Size , i_pocFile); 
}
//-----------------------------------------------------------------------------------------------
UINT64 PatMatchUtility::MakeCRC5(INT32 i_i32Start ,UINT32 i_u32Size , FileInfo  *i_pocFileInfo , JFile *i_pocFile )
{
	INT32  i32Dummy  ;
	INT64  i64SeekParameter ;

	i32Dummy = i_pocFileInfo->MinFirstSection() ;
	if ( i32Dummy == -1 )
	{
		return 0  ;
	}
	i64SeekParameter = i32Dummy ;
	if ( i_pocFile->Seek(i64SeekParameter , JFile::FBEGIN)	== FALSE ) 
	{
		return 0 ;
	}

	if ( i32Dummy +  i_u32Size > i_pocFileInfo->EntryPointOffset )
	{
		i_u32Size = i_pocFileInfo->EntryPointOffset - i32Dummy   ;
	}
	return TakeCrc(i_u32Size , i_pocFile); 
}
//-----------------------------------------------------------------------------------------------
UINT64 PatMatchUtility::TakeCrc(UINT32 u_i32Size , JFile *i_pocFile)
{
	UINT8  u8Buffer [4096] ;
	UINT64 u64CRCCheck =  0 ;
	size_t   stReadSize; 
	for (UINT32 iIndex = 0 ;  iIndex < u_i32Size ; iIndex += sizeof(u8Buffer))
	{
		stReadSize = min ( ( u_i32Size - iIndex ) , sizeof(u8Buffer) ) ;
		if ( i_pocFile->Read (u8Buffer ,stReadSize) == FALSE ) 
		{
			return 0 ;
		}
		u64CRCCheck  = crc::crc64(u64CRCCheck ,  u8Buffer , stReadSize ) ;
	}
	return u64CRCCheck ; 
}
//-----------------------------------------------------------------------------------------------