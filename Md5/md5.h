#ifndef MD5H
#define MD5H
#include "BaseObject.h"
class Md5 : public BaseObject
{
private :
	UINT32 hash[4];
	UINT32 bits[2];
	UINT32 data[16];
	static void md5_transform( UINT32 hash[ 4 ], const UINT32 data[ 16 ] ) ;
public :
	Md5();
	void Reset() ;
	void md5_update( const UINT8 *buf, UINT32 buflen ) ;
	void md5_final( UINT8 digest[ 16 ] );
};


#endif 