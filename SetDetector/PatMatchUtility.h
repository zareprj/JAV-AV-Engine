#ifndef PATMATCHUTILITY
#define PATMATCHUTILITY
#include "BaseObject.h"
#include "JBuffer.h"
#include "JFile.h"
#include "FileInf.h"
#include "crc.h"

class PatMatchUtility 
{	
public :

	static BOOLEAN RetrieveFilePackerType(UINT8 * i_u8Sb , UINT16 i_u16Size ,UINT32 i_u32Offset ,UINT32 i_u32Type , JBuffer *i_pocBuffer , FileInfo  *i_pocFileInfo )  ; 
	static BOOLEAN CheckPattern (UINT8  i_u8Sb[] , UINT16 i_u16Size , JBuffer *i_pocBuffer );
	static UINT64  MakeCRC(INT32 i_i32Start , UINT32 i_u32Size , FileInfo  *i_pocFileInfo , JFile *i_pocFile);
	static UINT64  MakeCRC1(INT32 i_i32Start , UINT32 i_u32Size , FileInfo  *i_pocFileInfo , JFile *i_pocFile);
	static UINT64  MakeCRC2(UINT32 i_u32Size , FileInfo  *i_pocFileInfo , JFile *i_pocFile) ;
	static UINT64  MakeCRC3(INT32 i_i32Start , INT32 i_i32ExtendedOffset ,UINT32 i_u32Size , FileInfo  *i_pocFileInfo , JFile *i_pocFile );
	static UINT64  MakeCRC4(INT32 i_i32Start , INT32 i_i32ExtendedOffset ,UINT32 i_u32Size , FileInfo  *i_pocFileInfo , JFile *i_pocFile );
	static UINT64  MakeCRC5(INT32 i_i32Start ,UINT32 i_u32Size , FileInfo  *i_pocFileInfo , JFile *i_pocFile );
	static UINT64  TakeCrc(UINT32 u_i32Size , JFile *i_pocFile);
	static BOOLEAN GetPatternType(UINT8 * i_pu8Sb , UINT16 i_u16Size ,UINT32 i_u32Offset ,UINT32 i_u32Type , JBuffer *i_pocBuffer , FileInfo *i_pocFileInfo );
};
#endif 