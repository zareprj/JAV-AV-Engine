#ifndef __JDECRYPTEDFILE__
#define __JDECRYPTEDFILE__
#include "SMTypeDefine.h"
#include "SMFile.h"
#pragma section ("JJJ",read , write)

#define xtime(x)   ((x<<1) ^ (((x>>7) & 1) * 0x1b))

// Multiplty is a macro used to multiply numbers in the field GF(2^8)
#define Multiply(x,y) (((y & 1) * x) ^ ((y>>1 & 1) * xtime(x)) ^ ((y>>2 & 1) * xtime(xtime(x))) ^ ((y>>3 & 1) * xtime(xtime(xtime(x)))) ^ ((y>>4 & 1) * xtime(xtime(xtime(xtime(x))))))

#pragma pack(8)
typedef struct _CryptFile
{
	UINT8	 Nb;
	UINT8    state[4][4], RoundKey[240], BUFFER [16] , WriteBuffer [16] , AlignByte, IndexBuffer, *inBuffer, *OutBuffer;
	UINT8    Nr , Nk ;	
	NTSTATUS LastErrorCode;
	UINT64   FilePosition , BufferPosition , RealFilePosition , WriteBufferPosition , FileSize ; 
	SMFile   hFile;
}CryptFile;
	
	UINT64	GetCryptFileLength(CryptFile *osCryptFile);
 	void	CryptKeyExpansion(CryptFile *osCryptFile) ;
 	UINT8   GetSBoxValue(UINT8 num);
 	void	AddRoundKey(CryptFile *osCryptFile, UINT8 round) ;
 	void	SubBytes(CryptFile *osCryptFile);
 	void	MixColumns(CryptFile *osCryptFile);
 	void	Cipher(CryptFile *osCryptFile);
 	void	ShiftRows(CryptFile *osCryptFile) ;

	FORCEINLINE void	InvCipher(CryptFile *osCryptFile);
	FORCEINLINE void	InvShiftRows(CryptFile *osCryptFile);
	FORCEINLINE void	InvSubBytes(CryptFile *osCryptFile) ;
	FORCEINLINE void	InvMixColumns(CryptFile *osCryptFile) ;
	FORCEINLINE	UINT8   GetSBoxInvert(UINT8 num);
 	
	BOOLEAN GetCryptedFilePosition (CryptFile *osCryptFile, UINT64 *Offset);
 	void	CryptedFileInit(CryptFile *osCryptFile);

	BOOLEAN CryptOpen(CryptFile *osCryptFile,  WCHAR* szName);
	BOOLEAN CryptCreateFile(CryptFile *osCryptFile, WCHAR* szName);
	BOOLEAN CryptRead(CryptFile *osCryptFile, void *Data ,UINT32 *Size);
	BOOLEAN CryptWrite(CryptFile *osCryptFile, void *Data ,UINT32 *Size) ;
	BOOLEAN CryptSeek(CryptFile *osCryptFile, INT64 *Offset) ;
	BOOLEAN CryptClose(CryptFile *osCryptFile); 
	BOOLEAN CryptSeekCurrent(CryptFile *osCryptFile, INT64 *Offset);
#endif 