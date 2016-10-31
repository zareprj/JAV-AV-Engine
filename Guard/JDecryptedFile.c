#include "JDecryptedFile.h"
#pragma pack(8)
UINT8  AESKey[32] = {0x0F  ,0xFF  ,0x00  ,0x07  ,0xC4  ,0x54  ,0x06  ,0x07  ,0x3A  ,0x72  ,0x80  ,0x4F  ,0xFb  ,0x10  ,0x54  ,0x38};

static BOOLEAN Write( CryptFile * osCryptFile, void * Data, size_t *TempSize );
static BOOLEAN Read( CryptFile * osCryptFile, void * Data, size_t *TempSize ) ;
static BOOLEAN Seek(CryptFile *osCryptFile,INT64 *Offset);
static BOOLEAN GetFilePosion(CryptFile * osCryptFile , UINT64 *Offset);

#ifdef ALLOC_PRAGMA

	#pragma alloc_text( PAGE , CryptedFileInit )
	#pragma alloc_text( PAGE , GetCryptFileLength )
	#pragma alloc_text( PAGE , CryptOpen )
	#pragma alloc_text( PAGE , CryptCreateFile )
	#pragma alloc_text( PAGE , Seek )
	#pragma alloc_text( PAGE , Read )
	#pragma alloc_text( PAGE , CryptRead )
	#pragma alloc_text( PAGE , Write )
	#pragma alloc_text( PAGE , CryptWrite )
	#pragma alloc_text( PAGE , CryptClose )
	#pragma alloc_text( PAGE , CryptSeek )
	#pragma alloc_text( PAGE , CryptSeekCurrent )
	#pragma alloc_text( PAGE , CryptKeyExpansion )
	#pragma alloc_text( PAGE , GetSBoxValue )
	#pragma alloc_text( PAGE , Cipher )
	#pragma alloc_text( PAGE , AddRoundKey )
	#pragma alloc_text( PAGE , SubBytes )
	#pragma alloc_text( PAGE , ShiftRows )
	#pragma alloc_text( PAGE , MixColumns )
	#pragma alloc_text( PAGE , InvCipher )
	#pragma alloc_text( PAGE , InvShiftRows )
	#pragma alloc_text( PAGE , InvSubBytes )
	#pragma alloc_text( PAGE , GetSBoxInvert )
	#pragma alloc_text( PAGE , InvMixColumns )
	#pragma alloc_text( PAGE , GetCryptedFilePosition )

#endif


UINT8 Rcon[256] =
{
	0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 
	0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 
	0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 
	0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 
	0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 
	0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 
	0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 
	0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 
	0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 
	0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 
	0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 
	0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 
	0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04, 
	0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 
	0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 
	0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb 
};
//----------------------------------------------------------------------------------------------------------
void CryptedFileInit(CryptFile *osCryptFile)
{
	UINT8 i = 0; 
	PAGED_CODE();
	for ( i ; i < (sizeof (AESKey) / 2)  ; i++)
	{
		AESKey[i] ^= AESKey[(sizeof (AESKey) / 2 ) + i]  ;
	}
	(*osCryptFile).RealFilePosition = (*osCryptFile).FilePosition   = 0LL ;
	(*osCryptFile).WriteBufferPosition = (*osCryptFile).BufferPosition = 0xffffffffffffffff ;
	(*osCryptFile).Nb = 4;
	(*osCryptFile).Nk = (256) / 32;
	(*osCryptFile).Nr = (*osCryptFile).Nk + 6;
	CryptKeyExpansion (osCryptFile);
}
//----------------------------------------------------------------------------------------------------------
UINT64 GetCryptFileLength(CryptFile *osCryptFile)
{
	UINT64 u64FileSize;
	NTSTATUS ntStatus ;
	PAGED_CODE();
	ntStatus = SMGetFileLength ( &osCryptFile->hFile, ((LARGE_INTEGER*)&u64FileSize) );
	if ( !NT_SUCCESS (ntStatus) )
	{
		(*osCryptFile).LastErrorCode = ntStatus;
		return 0 ;
	}
	return u64FileSize;
}
//-----------------------------------------------------------------------------
BOOLEAN CryptOpen(CryptFile *osCryptFile,  WCHAR* szName)
{
	BOOLEAN Iret = FALSE;
	size_t Size ;
	NTSTATUS ntStatus ;
	PAGED_CODE();
	CryptedFileInit(osCryptFile);
	(*osCryptFile).RealFilePosition = (*osCryptFile).FilePosition = 0LL ;
	(*osCryptFile).WriteBufferPosition = (*osCryptFile).BufferPosition = 0xffffffffffffffff ;

	ntStatus = SMCreateFileForRead (&osCryptFile->hFile , szName ) ;
	if ( !NT_SUCCESS (ntStatus) ) 
	{
		(*osCryptFile).LastErrorCode = ntStatus ;
		Iret = FALSE ;
	}
	else
	{
		(*osCryptFile).FileSize = GetCryptFileLength(osCryptFile) ;
		Size = sizeof(UINT8) ;
		Iret = Read(osCryptFile, &(osCryptFile->AlignByte), &Size);
		if (Iret == TRUE)
		{
			(*osCryptFile).FileSize -= sizeof((*osCryptFile).BUFFER) - (*osCryptFile).AlignByte ;
			(*osCryptFile).RealFilePosition = (*osCryptFile).FilePosition   = 1LL ;
		}
	}
	return Iret ;
}
//-----------------------------------------------------------------------------
BOOLEAN CryptCreateFile(CryptFile *osCryptFile, WCHAR* szName)
{
	BOOLEAN Iret = FALSE ;
	size_t Size ;
	NTSTATUS ntStatus ;
	PAGED_CODE();
	(*osCryptFile).RealFilePosition = (*osCryptFile).FilePosition   = 0LL ;
	(*osCryptFile).WriteBufferPosition = (*osCryptFile).BufferPosition = 0xffffffffffffffff ;	
	
	ntStatus = SMCreateFileForWrite  (&osCryptFile->hFile , szName ) ;

	if ( NT_SUCCESS (ntStatus)) 
	{
		(*osCryptFile).FileSize = GetCryptFileLength(osCryptFile) ;
		(*osCryptFile).AlignByte = sizeof((*osCryptFile).BUFFER) ;
		Size = sizeof(UINT8);
		Iret = Write(osCryptFile, &(osCryptFile->AlignByte), &Size);
		if (Iret == TRUE)
		{
			(*osCryptFile).RealFilePosition = (*osCryptFile).FilePosition   = 1LL ;
		}
	}
	
	return Iret ;
}
//-----------------------------------------------------------------------------
BOOLEAN Seek(CryptFile *osCryptFile,INT64 *Offset)
{
	NTSTATUS ntStatus ;
	PAGED_CODE();
	ntStatus = SMSeekFile ( &osCryptFile->hFile , ((LARGE_INTEGER*)Offset) );
	if (!NT_SUCCESS(ntStatus))
	{
		(*osCryptFile).LastErrorCode = ntStatus;
		return FALSE ;
	}
	return TRUE ;
}
//-----------------------------------------------------------------------------
BOOLEAN Read( CryptFile * osCryptFile, void * Data, size_t *TempSize ) 
{
	UINT32   u32NumToRead = *TempSize;
	NTSTATUS ntStatus ;
	PAGED_CODE();
	ntStatus = SMReadFile( &osCryptFile->hFile , Data , &u32NumToRead );
	if (!NT_SUCCESS(ntStatus) || u32NumToRead != *TempSize)
	{
		osCryptFile->LastErrorCode = ntStatus;
		return FALSE;
	}
	return TRUE;
}

//-----------------------------------------------------------------------------
BOOLEAN CryptRead(CryptFile *osCryptFile, void *Data,UINT32 *Size)
{
	UINT8 DiffPosition;
	UINT32 TempSize = 0,IniSize , Temp  ;
	PAGED_CODE();
	IniSize = *Size = (UINT32)min (((*osCryptFile).FilePosition + *Size) , (*osCryptFile).FileSize) - (UINT32)(*osCryptFile).FilePosition ;
	if ( (*osCryptFile).RealFilePosition != (*osCryptFile).FilePosition )
	{
		if ( (*osCryptFile).BufferPosition > (*osCryptFile).FilePosition || (*osCryptFile).BufferPosition + sizeof ((*osCryptFile).BUFFER) < (*osCryptFile).FilePosition )
		{
			Temp = sizeof ((*osCryptFile).BUFFER) ;
			if ( Read(osCryptFile, (*osCryptFile).BUFFER , &Temp) == FALSE ) 
			{
				return FALSE ;
			}
			if ( Temp !=  sizeof ((*osCryptFile).BUFFER) )
			{
				Seek(osCryptFile, (INT64 *) (&(*osCryptFile).RealFilePosition));
				(*osCryptFile).FilePosition +=Temp ; 
				return FALSE ;
			}
			(*osCryptFile).BufferPosition = (*osCryptFile).RealFilePosition ;
			//(*osCryptFile).RealFilePosition += sizeof ((*osCryptFile).BUFFER);
			(*osCryptFile).OutBuffer = (*osCryptFile).inBuffer = (*osCryptFile).BUFFER ;
			InvCipher(osCryptFile); 
		}
		
		DiffPosition = (UINT8)((((*osCryptFile).FilePosition)) - (*osCryptFile).BufferPosition) ;
		TempSize = min ( (sizeof((*osCryptFile).BUFFER) - DiffPosition) , *Size  );
		memcpy (Data , (*osCryptFile).BUFFER + DiffPosition , TempSize) ;
		
		if (DiffPosition + TempSize == sizeof((*osCryptFile).BUFFER))
		{
			(*osCryptFile).RealFilePosition = sizeof ((*osCryptFile).BUFFER) + (*osCryptFile).BufferPosition;
			Seek(osCryptFile, (INT64 *) (&(*osCryptFile).RealFilePosition));
		}

		if (TempSize == *Size)
		{	
			(*osCryptFile).FilePosition += *Size;
			return TRUE ;
		}
		Data = (UINT8 *)Data + TempSize ;
		IniSize -= TempSize ;
	}
	*Size = TempSize ;
	Temp = TempSize = IniSize &~ (sizeof ((*osCryptFile).BUFFER) - 1 ) ;
	
	if (TempSize != 0 )
	{
		if ( Read(osCryptFile, Data, &TempSize) == FALSE ) 
		{
			(*osCryptFile).FilePosition +=*Size ; 
			return FALSE ;
		}
		*Size += TempSize ;
		if ( Temp > TempSize  )
		{
			GetFilePointer(&osCryptFile->hFile,(PLARGE_INTEGER) &(*osCryptFile).RealFilePosition) ;
			(*osCryptFile).RealFilePosition = (*osCryptFile).RealFilePosition &~ (sizeof ((*osCryptFile).BUFFER) - 1 ) ;
			Seek(osCryptFile, (INT64 *) (&(*osCryptFile).RealFilePosition));
			(*osCryptFile).FilePosition +=*Size ; 
			return FALSE ;
		}

		(*osCryptFile).RealFilePosition += TempSize ;
		while ( TempSize > 0)
		{
			(*osCryptFile).OutBuffer = (*osCryptFile).inBuffer = (UINT8 *)Data  ; 
			InvCipher(osCryptFile); 
			Data  = (UINT8 *)Data + sizeof((*osCryptFile).BUFFER) ;
			TempSize -= sizeof ((*osCryptFile).BUFFER) ;
		}
	}

	TempSize = IniSize & (sizeof ((*osCryptFile).BUFFER) - 1 ) ; 

	if (TempSize != 0)
	{
		Temp =  sizeof ((*osCryptFile).BUFFER) ;
		if ( Read( osCryptFile, (*osCryptFile).BUFFER, &Temp) == FALSE ) 
		{
			(*osCryptFile).FilePosition += *Size ; 
			return FALSE ;
		}
		if ( Temp !=  sizeof ((*osCryptFile).BUFFER) )
		{
			Seek( osCryptFile, (INT64 *) (&((*osCryptFile).RealFilePosition)));
			(*osCryptFile).FilePosition +=Temp ; 
			return FALSE ;
		}
		(*osCryptFile).OutBuffer = (*osCryptFile).inBuffer = (UINT8 *) (*osCryptFile).BUFFER ;
		InvCipher(osCryptFile); 
		(*osCryptFile).BufferPosition = (*osCryptFile).RealFilePosition ;
		(*osCryptFile).RealFilePosition += sizeof ((*osCryptFile).BUFFER) ;
		memcpy (Data , (*osCryptFile).BUFFER , TempSize);
		*Size += TempSize ;
	}
	(*osCryptFile).FilePosition += *Size ;
	return TRUE ;
}
//-----------------------------------------------------------------------------
BOOLEAN Write( CryptFile * osCryptFile, void * Data, size_t *TempSize ) 
{
	UINT32  u32NumToRead = *TempSize;
	NTSTATUS ntStatus = SMWriteFile( &osCryptFile->hFile, (*osCryptFile).WriteBuffer , (PULONG) TempSize );
	PAGED_CODE();
	if (!NT_SUCCESS(ntStatus) || u32NumToRead != *TempSize)
	{
		osCryptFile->LastErrorCode = ntStatus;
		return FALSE;
	}
	return TRUE;
}
//-----------------------------------------------------------------------------
BOOLEAN CryptWrite(CryptFile *osCryptFile, void *Data,UINT32 *Size)
{
	UINT8 DiffPosition;
	size_t TempSize ,IniSize = *Size  , Temp;
	PAGED_CODE();
	
	if ( (*osCryptFile).RealFilePosition != (*osCryptFile).FilePosition )
	{
		if ( (*osCryptFile).WriteBufferPosition > (*osCryptFile).FilePosition || (*osCryptFile).WriteBufferPosition + sizeof ((*osCryptFile).BUFFER) < (*osCryptFile).FilePosition )
		{
			if ( (*osCryptFile).WriteBufferPosition != 0xffffffffffffffff )
			{
				if ( Seek( osCryptFile, (INT64 *) (&(*osCryptFile).WriteBufferPosition)) == FALSE ) 
				{
					return FALSE ;
				}
				(*osCryptFile).OutBuffer = (*osCryptFile).inBuffer = (UINT8 *)(*osCryptFile).WriteBuffer ;
				Cipher(osCryptFile);
				TempSize = sizeof ((*osCryptFile).WriteBuffer) ;
				if ( Write(osCryptFile, (*osCryptFile).WriteBuffer, &TempSize) == FALSE ) 
				{
					*Size = 0 ;
					return FALSE ;
				}
				if ( Seek( osCryptFile, (INT64 *) (&(*osCryptFile).RealFilePosition) ) == FALSE ) 
				{
					return FALSE ;
				}
			}
			TempSize = sizeof ((*osCryptFile).WriteBuffer) ;
			if ( Read(osCryptFile, (*osCryptFile).WriteBuffer, &TempSize) == FALSE ) 
			{
				*Size = 0 ;
				return FALSE ;
			}

			if ( TempSize == sizeof ((*osCryptFile).WriteBuffer) )
			{
				(*osCryptFile).OutBuffer = (*osCryptFile).inBuffer =(UINT8 *) (*osCryptFile).WriteBuffer ;
				InvCipher(osCryptFile);
			}
			else if (TempSize != 0 )
			{
				return FALSE ;
			}

			(*osCryptFile).WriteBufferPosition = (*osCryptFile).RealFilePosition ;
			if ( TempSize != sizeof ((*osCryptFile).WriteBuffer) )
			{
				memset((*osCryptFile).WriteBuffer , 0xff , sizeof((*osCryptFile).WriteBuffer) ) ;
				if ( Seek( osCryptFile, (INT64 *) (&(*osCryptFile).RealFilePosition)) == FALSE ) 
				{
					return FALSE ;
				}
			}
		    (*osCryptFile).RealFilePosition += sizeof ((*osCryptFile).WriteBuffer) ;
			(*osCryptFile).OutBuffer = (*osCryptFile).inBuffer = (UINT8 *)(*osCryptFile).WriteBuffer ;
			InvCipher(osCryptFile);
		}
		DiffPosition = (UINT8)((((*osCryptFile).FilePosition)) - (*osCryptFile).WriteBufferPosition );
		TempSize = min ( (sizeof((*osCryptFile).BUFFER) - DiffPosition) , *Size  );
		memcpy ( (*osCryptFile).WriteBuffer + DiffPosition , Data , TempSize) ;
		if (TempSize == *Size)
		{
			(*osCryptFile).FilePosition += *Size;
			if ( (*osCryptFile).FileSize < (*osCryptFile).FilePosition )
			{
				(*osCryptFile).FileSize = (*osCryptFile).FilePosition;
			}
			return TRUE ;
		}
		Data = (UINT8 *)Data + TempSize ;
		IniSize -= TempSize ;
	}

	Temp = TempSize = IniSize&~ (sizeof ((*osCryptFile).BUFFER) - 1 );

	if (TempSize != 0 )
	{
		while ( TempSize > 0 )
		{
			(*osCryptFile).OutBuffer = (*osCryptFile).inBuffer = (UINT8 *)Data  ; 
			Cipher(osCryptFile);
			Data  = (UINT8 *)Data + sizeof((*osCryptFile).BUFFER) ;
			TempSize -= sizeof ((*osCryptFile).BUFFER) ;
		}
		if ( Write( osCryptFile, (UINT8 *)Data - Temp , &Temp) == FALSE ) 
		{
			Size = 0 ;
			return FALSE ;
		}
		(*osCryptFile).RealFilePosition += Temp ;
	}

	TempSize = IniSize & (sizeof ((*osCryptFile).WriteBuffer) - 1 ) ; 

	if (TempSize != 0)
	{
		if ( (*osCryptFile).WriteBufferPosition != 0xffffffffffffffff )
		{
			if ( Seek( osCryptFile ,(INT64 *) (&(*osCryptFile).WriteBufferPosition)) == FALSE ) 
			{
				return FALSE ;
			}
			(*osCryptFile).OutBuffer = (*osCryptFile).inBuffer = (UINT8 *)(*osCryptFile).WriteBuffer ;
			Cipher(osCryptFile);
			Temp = sizeof ((*osCryptFile).WriteBuffer) ;
			if ( Write(osCryptFile, (*osCryptFile).WriteBuffer, &Temp) == FALSE ) 
			{
				Size = 0 ;
				return FALSE ;
			}
			if ( Seek( osCryptFile, (INT64 *) (&(*osCryptFile).RealFilePosition)) == FALSE ) 
			{
				return FALSE ;
			}
		}
		IniSize = sizeof ((*osCryptFile).WriteBuffer) ;
		if ( Read( osCryptFile, (*osCryptFile).WriteBuffer, &IniSize) == FALSE ) 
		{
			return FALSE ;
		}
		
		if ( IniSize == sizeof ((*osCryptFile).WriteBuffer) )
		{
			(*osCryptFile).OutBuffer = (*osCryptFile).inBuffer =(UINT8 *) (*osCryptFile).WriteBuffer ;
			InvCipher(osCryptFile); 	
		}
		else if (IniSize != 0 )
		{
			return FALSE ;
		}
		memcpy ((*osCryptFile).WriteBuffer , Data , TempSize) ;
		(*osCryptFile).WriteBufferPosition = (*osCryptFile).RealFilePosition ;
		(*osCryptFile).RealFilePosition += sizeof ((*osCryptFile).WriteBuffer) ;
	}
	
	(*osCryptFile).FilePosition += *Size;
	if ( (*osCryptFile).FileSize < (*osCryptFile).FilePosition )
	{
		(*osCryptFile).FileSize = (*osCryptFile).FilePosition;
	}
	return TRUE ;
}
//-----------------------------------------------------------------------------
BOOLEAN CryptClose(CryptFile *osCryptFile)
{
	size_t TempSize ;

	UINT8 OriginOffset ;	
	NTSTATUS ntStatus ;
	PAGED_CODE();
	if ( (*osCryptFile).WriteBufferPosition != 0xffffffffffffffff )
	{
		if ( Seek(osCryptFile,  (INT64 *) (&(*osCryptFile).WriteBufferPosition) ) == FALSE ) 
		{
			return FALSE ;
		}
		(*osCryptFile).OutBuffer = (*osCryptFile).inBuffer = (UINT8 *)(*osCryptFile).WriteBuffer ;
		Cipher(osCryptFile);
		TempSize = sizeof ((*osCryptFile).WriteBuffer) ;
		if ( Write(osCryptFile, (*osCryptFile).WriteBuffer , &TempSize) == FALSE ) 
		{
			return FALSE ;
		}
		OriginOffset = min ( (size_t) ((*osCryptFile).FileSize - (*osCryptFile).WriteBufferPosition) , sizeof ((*osCryptFile).WriteBuffer))  ;
		(*osCryptFile).WriteBufferPosition = 0 ;
		if ( Seek( osCryptFile, (INT64 *) (&(*osCryptFile).WriteBufferPosition) ) == FALSE ) 
		{
			return FALSE ;
		}
		(*osCryptFile).WriteBuffer[0] = OriginOffset ;
		TempSize = 1 ;
		if ( Write( osCryptFile, (*osCryptFile).WriteBuffer, &TempSize) == FALSE ) 
		{
			return FALSE ;
		}
	}
	ntStatus = SMCloseFile(&osCryptFile->hFile);
	if ( !NT_SUCCESS (ntStatus))
	{
		return FALSE ;
	}
	return TRUE ;
}
//-----------------------------------------------------------------------------
BOOLEAN  CryptSeek(CryptFile *osCryptFile, INT64 *Offset)
{
	INT64 TempOffset;
	PAGED_CODE();
	(*osCryptFile).FilePosition = *Offset + 1;
	TempOffset = ((*osCryptFile).FilePosition - 1) & ~15 ;
	TempOffset += 1 ;
	if ( Seek(osCryptFile, &TempOffset) == FALSE ) 
	{
		return FALSE ;
	}
	(*osCryptFile).RealFilePosition = TempOffset ;
	*Offset = (*osCryptFile).FilePosition -1 ;
	return TRUE;
}
//-----------------------------------------------------------------------------
BOOLEAN  CryptSeekCurrent(CryptFile *osCryptFile, INT64 *Offset)
{
	INT64 TempOffset;
	PAGED_CODE();
	(*osCryptFile).FilePosition += *Offset ;
	TempOffset = ((*osCryptFile).FilePosition - 1) & ~15 ;
	TempOffset += 1 ;
	if ( Seek(osCryptFile, &TempOffset) == FALSE ) 
	{
		return FALSE ;
	}
	(*osCryptFile).RealFilePosition = TempOffset ;
	*Offset = (*osCryptFile).FilePosition -1 ;
	return TRUE;
}
//-----------------------------------------------------------------------------
void CryptKeyExpansion(CryptFile *osCryptFile) 
{
	unsigned int i,j;
	unsigned char temp[4],k;
	PAGED_CODE();
	// The first round key is the key itself.
	for(i=0;i<(*osCryptFile).Nk;i++)
	{
		(*osCryptFile).RoundKey[i*4]=AESKey[i*4];
		(*osCryptFile).RoundKey[i*4+1]=AESKey[i*4+1];
		(*osCryptFile).RoundKey[i*4+2]=AESKey[i*4+2];
		(*osCryptFile).RoundKey[i*4+3]=AESKey[i*4+3];
	}

	// All other round keys are found from the previous round keys.
	while (i < (unsigned int)((*osCryptFile).Nb * ((*osCryptFile).Nr+1)))
	{
		for(j=0;j<4;j++)
		{
			temp[j]=(*osCryptFile).RoundKey[(i-1) * 4 + j];
		}
		if (i % (*osCryptFile).Nk == 0)
		{
			// This function rotates the 4 bytes in a word to the left once.
			// [a0,a1,a2,a3] becomes [a1,a2,a3,a0]

			// Function RotWord()
			{
				k = temp[0];
				temp[0] = temp[1];
				temp[1] = temp[2];
				temp[2] = temp[3];
				temp[3] = k;
			}

			// SubWord() is a function that takes a four-byte input word and 
			// applies the S-box to each of the four bytes to produce an output word.

			// Function Subword()
			{
				temp[0]=GetSBoxValue(temp[0]);
				temp[1]=GetSBoxValue(temp[1]);
				temp[2]=GetSBoxValue(temp[2]);
				temp[3]=GetSBoxValue(temp[3]);
			}

			temp[0] =  temp[0] ^ Rcon[i/(*osCryptFile).Nk];
		}
		else if ((*osCryptFile).Nk > 6 && i % (*osCryptFile).Nk == 4)
		{
			// Function Subword()
			{
				temp[0]=GetSBoxValue(temp[0]);
				temp[1]=GetSBoxValue(temp[1]);
				temp[2]=GetSBoxValue(temp[2]);
				temp[3]=GetSBoxValue(temp[3]);
			}
		}
		(*osCryptFile).RoundKey[i*4+0] = (*osCryptFile).RoundKey[(i-(*osCryptFile).Nk)*4+0] ^ temp[0];
		(*osCryptFile).RoundKey[i*4+1] = (*osCryptFile).RoundKey[(i-(*osCryptFile).Nk)*4+1] ^ temp[1];
		(*osCryptFile).RoundKey[i*4+2] = (*osCryptFile).RoundKey[(i-(*osCryptFile).Nk)*4+2] ^ temp[2];
		(*osCryptFile).RoundKey[i*4+3] = (*osCryptFile).RoundKey[(i-(*osCryptFile).Nk)*4+3] ^ temp[3];
		i++;
	}
}
//---------------------------------------------------------------------------------------
FORCEINLINE UINT8 GetSBoxValue(UINT8 num) 
{
	static UINT8 sbox[256] =   {
		//0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
		0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, //0
		0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, //1
		0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, //2
		0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, //3
		0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, //4
		0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, //5
		0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, //6
		0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, //7
		0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, //8
		0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, //9
		0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, //A
		0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, //B
		0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, //C
		0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, //D
		0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, //E
		0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 }; //F

		return sbox[num];
}
//-------------------------------------------------------------------------------------------
void Cipher(CryptFile *osCryptFile)
{
	unsigned int i,j;
	UINT8 round=0 ;
	PAGED_CODE();

	//Copy the input PlainText to state array.
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			(*osCryptFile).state[j][i] = (*osCryptFile).inBuffer[i*4 + j];
		}
	}

	// Add the First round key to the state before starting the rounds.
	AddRoundKey(osCryptFile, 0); 

	// There will be Nr rounds.
	// The first Nr-1 rounds are identical.
	// These Nr-1 rounds are executed in the loop below.
	for(round=1;round<osCryptFile->Nr;round++)
	{
		SubBytes(osCryptFile);
		ShiftRows(osCryptFile);
		MixColumns(osCryptFile);
		AddRoundKey(osCryptFile, round);
	}

	// The last round is given below.
	// The MixColumns function is not here in the last round.
	SubBytes(osCryptFile);
	ShiftRows(osCryptFile);
	AddRoundKey(osCryptFile, osCryptFile->Nr);

	// The encryption process is over.
	// Copy the state array to output array.
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			(*osCryptFile).OutBuffer[i*4+j]=(*osCryptFile).state[j][i];
		}
	}
}
//-------------------------------------------------------------------------------------------
void AddRoundKey(CryptFile *osCryptFile, UINT8 round) 
{
	UINT8 i,j;
	PAGED_CODE();
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			(*osCryptFile).state[j][i] ^= (*osCryptFile).RoundKey[round * osCryptFile->Nb * 4 + i * osCryptFile->Nb + j];
		}
	}
}
//-------------------------------------------------------------------------------------------
void SubBytes(CryptFile *osCryptFile)
{
	UINT8 i,j;
	PAGED_CODE();
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			(*osCryptFile).state[i][j] = GetSBoxValue((*osCryptFile).state[i][j]);
		}
	}
}
//-------------------------------------------------------------------------------------------
void ShiftRows(CryptFile *osCryptFile)
{
	unsigned char temp;
	PAGED_CODE();
	// Rotate first row 1 columns to left	
	temp=(*osCryptFile).state[1][0];
	(*osCryptFile).state[1][0]=(*osCryptFile).state[1][1];
	(*osCryptFile).state[1][1]=(*osCryptFile).state[1][2];
	(*osCryptFile).state[1][2]=(*osCryptFile).state[1][3];
	(*osCryptFile).state[1][3]=temp;

	// Rotate second row 2 columns to left	
	temp=(*osCryptFile).state[2][0];
	(*osCryptFile).state[2][0]=(*osCryptFile).state[2][2];
	(*osCryptFile).state[2][2]=temp;

	temp=(*osCryptFile).state[2][1];
	(*osCryptFile).state[2][1]=(*osCryptFile).state[2][3];
	(*osCryptFile).state[2][3]=temp;

	// Rotate third row 3 columns to left
	temp=(*osCryptFile).state[3][0];
	(*osCryptFile).state[3][0]=(*osCryptFile).state[3][3];
	(*osCryptFile).state[3][3]=(*osCryptFile).state[3][2];
	(*osCryptFile).state[3][2]=(*osCryptFile).state[3][1];
	(*osCryptFile).state[3][1]=temp;
}
//-------------------------------------------------------------------------------------------
void MixColumns(CryptFile *osCryptFile)
{
	int i;
	unsigned char Tmp,Tm,t;
	PAGED_CODE();
	for(i=0;i<4;i++)
	{	
		t=(*osCryptFile).state[0][i];
		Tmp = (*osCryptFile).state[0][i] ^ (*osCryptFile).state[1][i] ^ (*osCryptFile).state[2][i] ^ (*osCryptFile).state[3][i] ;
		Tm = (*osCryptFile).state[0][i] ^ (*osCryptFile).state[1][i] ; Tm = xtime(Tm); (*osCryptFile).state[0][i] ^= Tm ^ Tmp ;
		Tm = (*osCryptFile).state[1][i] ^ (*osCryptFile).state[2][i] ; Tm = xtime(Tm); (*osCryptFile).state[1][i] ^= Tm ^ Tmp ;
		Tm = (*osCryptFile).state[2][i] ^ (*osCryptFile).state[3][i] ; Tm = xtime(Tm); (*osCryptFile).state[2][i] ^= Tm ^ Tmp ;
		Tm = (*osCryptFile).state[3][i] ^ t ; Tm = xtime(Tm); (*osCryptFile).state[3][i] ^= Tm ^ Tmp ;
	}
}
//-------------------------------------------------------------------------------------------
// InvCipher is the main function that decrypts the CipherText.
void InvCipher(CryptFile *osCryptFile)
{
	UINT8 i,j,round=0;
	PAGED_CODE();
	/*memcpy((*osCryptFile).OutBuffer ,osCryptFile->inBuffer , 16);
	return ;*/
	//Copy the input CipherText to state array.
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			osCryptFile->state[j][i] = osCryptFile->inBuffer[i*4 + j];
		}
	}

	// Add the First round key to the state before starting the rounds.
	AddRoundKey(osCryptFile, osCryptFile->Nr); 

	// There will be Nr rounds.
	// The first Nr-1 rounds are identical.
	// These Nr-1 rounds are executed in the loop below.
	for(round=osCryptFile->Nr-1;round>0;round--)
	{
		InvShiftRows(osCryptFile);
		InvSubBytes(osCryptFile);
		AddRoundKey(osCryptFile, round);
		InvMixColumns(osCryptFile);
	}

	// The last round is given below.
	// The MixColumns function is not here in the last round.
	InvShiftRows(osCryptFile);
	InvSubBytes(osCryptFile);
	AddRoundKey(osCryptFile, 0);

	// The decryption process is over.
	// Copy the state array to output array.
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			(*osCryptFile).OutBuffer[i*4+j]=(*osCryptFile).state[j][i];
		}
	}
}
//---------------------------------------------------------------------
// The ShiftRows() function shifts the rows in the state to the left.
// Each row is shifted with different offset.
// Offset = Row number. So the first row is not shifted.
//---------------------------------------------------------------------
void InvShiftRows(CryptFile *osCryptFile)
{
	unsigned char temp;
	PAGED_CODE();

	// Rotate first row 1 columns to right	
	temp=(*osCryptFile).state[1][3];
	(*osCryptFile).state[1][3]=(*osCryptFile).state[1][2];
	(*osCryptFile).state[1][2]=(*osCryptFile).state[1][1];
	(*osCryptFile).state[1][1]=(*osCryptFile).state[1][0];
	(*osCryptFile).state[1][0]=temp;

	// Rotate second row 2 columns to right	
	temp=(*osCryptFile).state[2][0];
	(*osCryptFile).state[2][0]=(*osCryptFile).state[2][2];
	(*osCryptFile).state[2][2]=temp;

	temp=(*osCryptFile).state[2][1];
	(*osCryptFile).state[2][1]=(*osCryptFile).state[2][3];
	(*osCryptFile).state[2][3]=temp;

	// Rotate third row 3 columns to right
	temp=(*osCryptFile).state[3][0];
	(*osCryptFile).state[3][0]=(*osCryptFile).state[3][1];
	(*osCryptFile).state[3][1]=(*osCryptFile).state[3][2];
	(*osCryptFile).state[3][2]=(*osCryptFile).state[3][3];
	(*osCryptFile).state[3][3]=temp;
}
// The SubBytes Function Substitutes the values in the
// state matrix with values in an S-box.
//---------------------------------------------------------------------
void InvSubBytes(CryptFile *osCryptFile)
{
	int i,j;
	PAGED_CODE();
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			(*osCryptFile).state[i][j] = GetSBoxInvert((*osCryptFile).state[i][j]);
		}
	}
}
//---------------------------------------------------------------------
UINT8 GetSBoxInvert(UINT8 num)
{
	static UINT8 rsbox[256] =
	{ 0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb
	, 0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb
	, 0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e
	, 0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25
	, 0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92
	, 0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84
	, 0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06
	, 0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b
	, 0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73
	, 0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e
	, 0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b
	, 0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4
	, 0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f
	, 0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef
	, 0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61
	, 0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };
	return rsbox[num];
}
// The SubBytes Function Substitutes the values in the
// state matrix with values in an S-box.
//---------------------------------------------------------------------
void InvMixColumns(CryptFile *osCryptFile)
{
	int i;
	unsigned char a,b,c,d;
	PAGED_CODE();
	for(i=0;i<4;i++)
	{
		a = (*osCryptFile).state[0][i];
		b = (*osCryptFile).state[1][i];
		c = (*osCryptFile).state[2][i];
		d = (*osCryptFile).state[3][i];

		(*osCryptFile).state[0][i] = Multiply(a, 0x0e) ^ Multiply(b, 0x0b) ^ Multiply(c, 0x0d) ^ Multiply(d, 0x09);
		(*osCryptFile).state[1][i] = Multiply(a, 0x09) ^ Multiply(b, 0x0e) ^ Multiply(c, 0x0b) ^ Multiply(d, 0x0d);
		(*osCryptFile).state[2][i] = Multiply(a, 0x0d) ^ Multiply(b, 0x09) ^ Multiply(c, 0x0e) ^ Multiply(d, 0x0b);
		(*osCryptFile).state[3][i] = Multiply(a, 0x0b) ^ Multiply(b, 0x0d) ^ Multiply(c, 0x09) ^ Multiply(d, 0x0e);
	}
}
//---------------------------------------------------------------------
BOOLEAN GetCryptedFilePosition (CryptFile *osCryptFile, UINT64 *Offset) 
{
	*Offset = (*osCryptFile).FilePosition - 1;
	return TRUE ;
}
//---------------------------------------------------------------------
