#ifndef CRCH
#define CRCH
#include "BaseObject.h"

class crc
{
	public :
		static UINT32 crc32Rar(UINT32 start_crc,const UINT8 *addr, UINT32 size) ;
		static UINT32 crc32Zip(UINT32 start_crc,const UINT8 *addr, UINT32 size);
		static UINT64 crc64( UINT64 start_crc , const UINT8 *addr ,UINT32 size);
	private :
		static UINT32 crc_table[256] ;
		static UINT64 crc64_table[4][256];
};

#endif 