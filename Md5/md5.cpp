

#include <stdio.h> 
#include <string.h> 
#include <errno.h>

#include "md5.h"

/* Basic MD5 functions */

/*inline static void byteSwap(UINT32 *buf, UINT32 words)
{
	const UINT32 byteOrderTest = 0x1;
	if (((char *)&byteOrderTest)[0] == 0)
	{
		UINT8 *p = (UINT8 *)buf;

		do {
			*buf++ = (UINT32)((UINT32)p[3] << 8 | p[2]) << 16 |
				((UINT32)p[1] << 8 | p[0]);
			p += 4;
		} while (--words);
	}
}*/

#define F1(x, y, z) (z ^ (x & (y ^ z)))
#define F2(x, y, z) (y ^ (z & (x ^ y))) 
#define F3(x, y, z) (x ^ y ^ z) 
#define F4(x, y, z) (y ^ (x | ~z))

/* This is the central step in the MD5 algorithm. */ 
#define TRANSFORM(f, w, x, y, z, data, s) \
	( w += f(x, y, z) + data,  w = w<<s | w>>(32-s),  w += x )


void Md5::md5_transform( UINT32 hash[ 4 ], const UINT32 data[ 16 ] ) 
{
	UINT32 a = hash[0], b = hash[1], c = hash[2], d = hash[3];

/* Round 1 */ 
TRANSFORM( F1, a, b, c, d, data[ 0] + 0xd76aa478, 7); 
TRANSFORM( F1, d, a, b, c, data[ 1] + 0xe8c7b756, 12);
TRANSFORM( F1, c, d, a, b, data[ 2] + 0x242070db, 17); 
TRANSFORM( F1, b, c, d, a, data[ 3] + 0xc1bdceee, 22); 
TRANSFORM( F1, a, b, c, d, data[ 4] + 0xf57c0faf, 7); 
TRANSFORM( F1, d, a, b, c, data[ 5] + 0x4787c62a, 12); 
TRANSFORM( F1, c, d, a, b, data[ 6] + 0xa8304613, 17); 
TRANSFORM( F1, b, c, d, a, data[ 7] + 0xfd469501, 22); 
TRANSFORM( F1, a, b, c, d, data[ 8] + 0x698098d8, 7); 
TRANSFORM( F1, d, a, b, c, data[ 9] + 0x8b44f7af, 12); 
TRANSFORM( F1, c, d, a, b, data[10] + 0xffff5bb1, 17); 
TRANSFORM( F1, b, c, d, a, data[11] + 0x895cd7be, 22); 
TRANSFORM( F1, a, b, c, d, data[12] + 0x6b901122, 7); 
TRANSFORM( F1, d, a, b, c, data[13] + 0xfd987193, 12); 
TRANSFORM( F1, c, d, a, b, data[14] + 0xa679438e, 17); 
TRANSFORM( F1, b, c, d, a, data[15] + 0x49b40821, 22);


/* Round 2 */ 
TRANSFORM( F2, a, b, c, d, data[ 1] + 0xf61e2562, 5); 
TRANSFORM( F2, d, a, b, c, data[ 6] + 0xc040b340, 9); 
TRANSFORM( F2, c, d, a, b, data[11] + 0x265e5a51, 14); 
TRANSFORM( F2, b, c, d, a, data[ 0] + 0xe9b6c7aa, 20); 
TRANSFORM( F2, a, b, c, d, data[ 5] + 0xd62f105d, 5); 
TRANSFORM( F2, d, a, b, c, data[10] + 0x02441453, 9); 
TRANSFORM( F2, c, d, a, b, data[15] + 0xd8a1e681, 14); 
TRANSFORM( F2, b, c, d, a, data[ 4] + 0xe7d3fbc8, 20); 
TRANSFORM( F2, a, b, c, d, data[ 9] + 0x21e1cde6, 5); 
TRANSFORM( F2, d, a, b, c, data[14] + 0xc33707d6, 9); 
TRANSFORM( F2, c, d, a, b, data[ 3] + 0xf4d50d87, 14);
TRANSFORM( F2, b, c, d, a, data[ 8] + 0x455a14ed, 20); 
TRANSFORM( F2, a, b, c, d, data[13] + 0xa9e3e905, 5);
TRANSFORM( F2, d, a, b, c, data[ 2] + 0xfcefa3f8, 9); 
TRANSFORM( F2, c, d, a, b, data[ 7] + 0x676f02d9, 14); 
TRANSFORM( F2, b, c, d, a, data[12] + 0x8d2a4c8a, 20);

/* Round 3 */
TRANSFORM( F3, a, b, c, d, data[ 5] + 0xfffa3942, 4); 
TRANSFORM( F3, d, a, b, c, data[ 8] + 0x8771f681, 11); 
TRANSFORM( F3, c, d, a, b, data[11] + 0x6d9d6122, 16); 
TRANSFORM( F3, b, c, d, a, data[14] + 0xfde5380c, 23); 
TRANSFORM( F3, a, b, c, d, data[ 1] + 0xa4beea44, 4); 
TRANSFORM( F3, d, a, b, c, data[ 4] + 0x4bdecfa9, 11); 
TRANSFORM( F3, c, d, a, b, data[ 7] + 0xf6bb4b60, 16); 
TRANSFORM( F3, b, c, d, a, data[10] + 0xbebfbc70, 23); 
TRANSFORM( F3, a, b, c, d, data[13] + 0x289b7ec6, 4); 
TRANSFORM( F3, d, a, b, c, data[ 0] + 0xeaa127fa, 11); 
TRANSFORM( F3, c, d, a, b, data[ 3] + 0xd4ef3085, 16); 
TRANSFORM( F3, b, c, d, a, data[ 6] + 0x04881d05, 23); 
TRANSFORM( F3, a, b, c, d, data[ 9] + 0xd9d4d039, 4); 
TRANSFORM( F3, d, a, b, c, data[12] + 0xe6db99e5, 11);
TRANSFORM( F3, c, d, a, b, data[15] + 0x1fa27cf8, 16); 
TRANSFORM( F3, b, c, d, a, data[ 2] + 0xc4ac5665, 23);

/* Round 4 */
TRANSFORM( F4, a, b, c, d, data[ 0] + 0xf4292244, 6);
TRANSFORM( F4, d, a, b, c, data[ 7] + 0x432aff97, 10);
TRANSFORM( F4, c, d, a, b, data[14] + 0xab9423a7, 15);
TRANSFORM( F4, b, c, d, a, data[ 5] + 0xfc93a039, 21); 
TRANSFORM( F4, a, b, c, d, data[12] + 0x655b59c3, 6); 
TRANSFORM( F4, d, a, b, c, data[ 3] + 0x8f0ccc92, 10);
TRANSFORM( F4, c, d, a, b, data[10] + 0xffeff47d, 15);
TRANSFORM( F4, b, c, d, a, data[ 1] + 0x85845dd1, 21); 
TRANSFORM( F4, a, b, c, d, data[ 8] + 0x6fa87e4f, 6); 
TRANSFORM( F4, d, a, b, c, data[15] + 0xfe2ce6e0, 10);
TRANSFORM( F4, c, d, a, b, data[ 6] + 0xa3014314, 15);
TRANSFORM( F4, b, c, d, a, data[13] + 0x4e0811a1, 21);
TRANSFORM( F4, a, b, c, d, data[ 4] + 0xf7537e82, 6);
TRANSFORM( F4, d, a, b, c, data[11] + 0xbd3af235, 10);
TRANSFORM( F4, c, d, a, b, data[ 2] + 0x2ad7d2bb, 15);
TRANSFORM( F4, b, c, d, a, data[ 9] + 0xeb86d391, 21);

	hash[ 0 ] += a; hash[ 1 ] += b; hash[ 2 ] += c; hash[ 3 ] += d; 
}

/* ** md5_init ** ** Initialise md5 context structure ** */ 
Md5::Md5()
{ 
	Reset();	
}
void Md5::Reset()
{
	hash[ 0 ] = 0x67452301; 
	hash[ 1 ] = 0xefcdab89;
	hash[ 2 ] = 0x98badcfe; 
	hash[ 3 ] = 0x10325476;

	bits[ 0 ] = 0;
	bits[ 1 ] = 0; 
}

/* ** md5_update ** ** Update context with the next buffer from the stream of data. ** Call with each block of data to update the md5 hash. ** */ 
void Md5::md5_update( const UINT8 *buf, UINT32 buflen ) 
{ 
	int idx;

/* Update bitcount */

idx = bits[ 0 ]; 
if ((bits[0] = idx + buflen) < idx)
	bits[1]++;	/* Carry from low to high */

idx = 64 -(idx & 0x3f);
if (idx > buflen)
{
	memcpy((UINT8 *) data + 64 - idx, buf, buflen);
	return;
}

memcpy((UINT8 *) data + 64 - idx, buf, idx);
//byteSwap(data, 16);
md5_transform( hash, (UINT32 *) data );
buf += idx ;
buflen -=idx ;
while( buflen >= 64 )
{
	memcpy( data, buf, 64 );
	md5_transform( hash, (UINT32 *) data ); 
	buf += 64; buflen -= 64;
}
memcpy( data, buf, (size_t) buflen );

}

/* ** md5_final ** ** Finalize creation of md5 hash and copy to digest buffer. ** */ 
void Md5::md5_final( UINT8 digest[ 16 ] )
{
	int count;
	UINT8 *pad;

	count = (bits[ 0 ] >> 3) & 0x3F;
	pad = (UINT8 *)data + count;
	*pad++ = 0x80;

/* Bytes of padding needed to make 64 bytes */
	count = 56 - 1 - count;

/* Pad out to 56 mod 64 */
	if( count < 0 )
	{ /* Two lots of padding: Pad the first block to 64 bytes */ 
		memset( pad, 0, (size_t) count + 8 ); 
		md5_transform( hash, (UINT32 *) data );
		pad =(UINT8 *) data ;
/* Now fill the next block with 56 bytes */
		count = 56 ;
		
	}
	memset( pad, 0, count ); 

/* Append length in bits and transform */
	((UINT32 *) data)[ 14 ] = bits[ 0 ] << 3;
	((UINT32 *) data)[ 15 ] = bits[ 1 ] << 3 | bits[ 0 ] >> 29 ;

	md5_transform( hash, (UINT32 *) data ); 
	memcpy( digest, hash, 16 );
} 