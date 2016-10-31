#ifndef __JDECRYPTEDFILE__
#define __JDECRYPTEDFILE__
#include "BaseObject.h"
#include "WinError.h"
#include "JFile.h"
#pragma section ("JJJ",read , write)

#define xtime(x)   ((x<<1) ^ (((x>>7) & 1) * 0x1b))

// Multiplty is a macro used to multiply numbers in the field GF(2^8)
#define Multiply(x,y) (((y & 1) * x) ^ ((y>>1 & 1) * xtime(x)) ^ ((y>>2 & 1) * xtime(xtime(x))) ^ ((y>>3 & 1) * xtime(xtime(xtime(x)))) ^ ((y>>4 & 1) * xtime(xtime(xtime(xtime(x))))))



class JDecryptedFile : public JFile 
{

private :
	static const UINT8	Nb = 4 ;
	UINT8 Nr , Nk ;
	UINT8 state[4][4];
	unsigned char RoundKey[240];

	BYTE BUFFER [16] , WriteBuffer [16] , AlignByte;

	UINT8 IndexBuffer ;
	unsigned char *inBuffer  , *OutBuffer;
	
	void KeyExpansion() ;
	FORCEINLINE UINT8 getSBoxValue(UINT8 num) ;
	void AddRoundKey(UINT8 round) ;
	void SubBytes();
	void MixColumns();
	void InvCipher();
	void Cipher();
	void ShiftRows() ;
	void InvShiftRows();
	void InvSubBytes() ;
	void InvMixColumns() ;
	UINT8 getSBoxInvert(UINT8 num);
	UINT64 FilePosiotn , BufferPosiotn , RealFilePosotion , WriteBuffrePostion , FileSize ; 
 
public :
	
	JDecryptedFile();
	~JDecryptedFile();
	BOOLEAN Open(JString &Name,BOOLEAN OpenShared=FALSE,BOOLEAN Update=FALSE) ;
	BOOLEAN CreateFile(JString &Name,BOOLEAN OpenShared,BOOLEAN Update);
	BOOLEAN Read(void *Data,size_t &Size);
	BOOLEAN Write(const void *Data,size_t &Size) ;
	BOOLEAN Seek(INT64 &Offset,MoveMethod Method) ;
	BOOLEAN GetFilePosition (UINT64 &Offset) ;
	BOOLEAN Close(); 
	UINT64 GetFileLength();
};
#endif 