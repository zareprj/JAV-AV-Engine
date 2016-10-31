#ifndef _zip_H
#define _zip_H
#include "BaseObject.h"
#include "JFile.h"
#include "JZipEnumerator.h"

// ZIP functions -- for creating zip files
// This file is a repackaged form of the Info-Zip source code available
// at www.info-zip.org. The original copyright notice may be found in
// zip.cpp. The repackaging was done by Lucian Wischik to simplify and
// extend its use in Windows/C++. Also to add encryption and unicode.


//DECLARE_HANDLE(HZIP);
// An HZIP identifies a zip file that is being created

typedef DWORD ZRESULT;
// return codes from any of the zip functions. Listed later.



// HZIP CreateZip(const TCHAR *fn, const UINT8 *password);
// HZIP CreateZip(void *buf,unsigned int len, const UINT8 *password);
// HZIP CreateZipHandle(HANDLE h, const UINT8 *password);
// 
// ZRESULT ZipAdd(HZIP hz,const TCHAR *dstzn, const TCHAR *fn);
// ZRESULT ZipAdd(HZIP hz,const TCHAR *dstzn, void *src,unsigned int len);
// ZRESULT ZipAddHandle(HZIP hz,const TCHAR *dstzn, HANDLE h);
// ZRESULT ZipAddHandle(HZIP hz,const TCHAR *dstzn, HANDLE h, unsigned int len);
// ZRESULT ZipAddFolder(HZIP hz,const TCHAR *dstzn);
// ZipAdd - call this for each file to be added to the zip.
// dstzn is the name that the file will be stored as in the zip file.
// The file to be added to the zip can come
// from a pipe:  ZipAddHandle(hz,"file.dat", hpipe_read);
// from a file:  ZipAddHandle(hz,"file.dat", hfile);
// from a filen: ZipAdd(hz,"file.dat", "c:\\docs\\origfile.dat");
// from memory:  ZipAdd(hz,"subdir\\file.dat", buf,len);

// Note: if adding an item from a pipe, and if also creating the zip file itself
// to a pipe, then you might wish to pass a non-zero length to the ZipAddHandle
// function. This will let the zipfile store the item's size ahead of the
// compressed item itself, which in turn makes it easier when unzipping the
// zipfile from a pipe.

//ZRESULT ZipGetMemory(HZIP hz, void **buf, unsigned long *len);
// ZipGetMemory - If the zip was created in memory, via ZipCreate(0,len),
// then this function will return information about that memory block.
// buf will receive a pointer to its start, and len its length.
// Note: you can't add any more after calling this.

//ZRESULT CloseZip(HZIP hz);
// CloseZip - the zip handle must be closed with this function.

//unsigned int FormatZipMessage(ZRESULT code, TCHAR *buf,unsigned int len);
// FormatZipMessage - given an error code, formats it as a string.
// It returns the length of the error message. If buf/len points
// to a real buffer, then it also writes as much as possible into there.



// These are the result codes:
#define ZR_OK         0x00000000     // nb. the pseudo-code zr-recent is never returned,
#define ZR_RECENT     0x00000001     // but can be passed to FormatZipMessage.
// The following come from general system stuff (e.g. files not openable)
#define ZR_GENMASK    0x0000FF00
#define ZR_NODUPH     0x00000100     // couldn't duplicate the handle
#define ZR_NOFILE     0x00000200     // couldn't create/open the file
#define ZR_NOALLOC    0x00000300     // failed to allocate some resource
#define ZR_WRITE      0x00000400     // a general error writing to the file
#define ZR_NOTFOUND   0x00000500     // couldn't find that file in the zip
#define ZR_MORE       0x00000600     // there's still more data to be unzipped
#define ZR_CORRUPT    0x00000700     // the zipfile is corrupt or not a zipfile
#define ZR_READ       0x00000800     // a general error reading the file
// The following come from mistakes on the part of the caller
#define ZR_CALLERMASK 0x00FF0000
#define ZR_ARGS       0x00010000     // general mistake with the arguments
#define ZR_NOTMMAP    0x00020000     // tried to ZipGetMemory, but that only works on mmap zipfiles, which yours wasn't
#define ZR_MEMSIZE    0x00030000     // the memory size is too small
#define ZR_FAILED     0x00040000     // the thing was already failed when you called this function
#define ZR_ENDED      0x00050000     // the zip creation has already been closed
#define ZR_MISSIZE    0x00060000     // the indicated input file size turned out mistaken
#define ZR_PARTIALUNZ 0x00070000     // the file had already been partially unzipped
#define ZR_ZMODE      0x00080000     // tried to mix creating/opening a zip 
// The following come from bugs within the zip library itself
#define ZR_BUGMASK    0xFF000000
#define ZR_NOTINITED  0x01000000     // initialisation didn't work
#define ZR_SEEK       0x02000000     // trying to seek in an unseekable file
#define ZR_NOCHANGE   0x04000000     // changed its mind on storage, but not allowed
#define ZR_FLATE      0x05000000     // an internal error in the de/inflation code






// e.g.
//
// (1) Traditional use, creating a zipfile from existing files
//     HZIP hz = CreateZip("c:\\simple1.zip",0);
//     ZipAdd(hz,"znsimple.bmp", "c:\\simple.bmp");
//     ZipAdd(hz,"znsimple.txt", "c:\\simple.txt");
//     CloseZip(hz);
//
// (2) Memory use, creating an auto-allocated mem-based zip file from various sources
//     HZIP hz = CreateZip(0,100000, 0);
//     // adding a conventional file...
//     ZipAdd(hz,"src1.txt",  "c:\\src1.txt");
//     // adding something from memory...
//     UINT8 buf[1000]; for (int i=0; i<1000; i++) buf[i]=(UINT8)(i&0x7F);
//     ZipAdd(hz,"file.dat",  buf,1000);
//     // adding something from a pipe...
//     HANDLE hread,hwrite; CreatePipe(&hread,&hwrite,NULL,0);
//     HANDLE hthread = CreateThread(0,0,ThreadFunc,(void*)hwrite,0,0);
//     ZipAdd(hz,"unz3.dat",  hread,1000);  // the '1000' is optional.
//     WaitForSingleObject(hthread,INFINITE);
//     CloseHandle(hthread); CloseHandle(hread);
//     ... meanwhile DWORD WINAPI ThreadFunc(void *dat)
//                   { HANDLE hwrite = (HANDLE)dat;
//                     UINT8 buf[1000]={17};
//                     DWORD writ; WriteFile(hwrite,buf,1000,&writ,NULL);
//                     CloseHandle(hwrite);
//                     return 0;
//                   }
//     // and now that the zip is created, let's do something with it:
//     void *zbuf; unsigned long zlen; ZipGetMemory(hz,&zbuf,&zlen);
//     HANDLE hfz = CreateFile("test2.zip",GENERIC_WRITE,0,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
//     DWORD writ; WriteFile(hfz,zbuf,zlen,&writ,NULL);
//     CloseHandle(hfz);
//     CloseZip(hz);
//
// (3) Handle use, for file handles and pipes
//     HANDLE hzread,hzwrite; CreatePipe(&hzread,&hzwrite,0,0);
//     HANDLE hthread = CreateThread(0,0,ZipReceiverThread,(void*)hzread,0,0);
//     HZIP hz = CreateZipHandle(hzwrite,0);
//     // ... add to it
//     CloseZip(hz);
//     CloseHandle(hzwrite);
//     WaitForSingleObject(hthread,INFINITE);
//     CloseHandle(hthread);
//     ... meanwhile DWORD WINAPI ZipReceiverThread(void *dat)
//                   { HANDLE hread = (HANDLE)dat;
//                     UINT8 buf[1000];
//                     while (true)
//                     { DWORD red; ReadFile(hread,buf,1000,&red,NULL);
//                       // ... and do something with this zip data we're receiving
//                       if (red==0) break;
//                     }
//                     CloseHandle(hread);
//                     return 0;
//                   }



// Now we indulge in a little skullduggery so that the code works whether
// the user has included just zip or both zip and unzip.
// Idea: if header files for both zip and unzip are present, then presumably
// the cpp files for zip and unzip are both present, so we will call
// one or the other of them based on a dynamic choice. If the header file
// for only one is present, then we will bind to that particular one.
// ZRESULT CloseZipZ(HZIP hz);
// unsigned int FormatZipMessageZ(ZRESULT code, UINT8 *buf,unsigned int len);
// bool IsZipHandleZ(HZIP hz);
// #ifdef _unzip_H
// #undef CloseZip
// CloseZipU(hz))
// #else
// #define CloseZip CloseZipZ
// #define FormatZipMessage FormatZipMessageZ
// #endif

//////////////////////////////////////////////////////////////////////////

#ifndef EOF
#define EOF (-1)
#endif


// Error return values.  The values 0..4 and 12..18 follow the conventions
// of PKZIP.   The values 4..10 are all assigned to "insufficient memory"
// by PKZIP, so the codes 5..10 are used here for other purposes.
#define ZE_MISS         -1      // used by procname(), zipbare()
#define ZE_OK           0       // success
#define ZE_EOF          2       // unexpected end of zip file
#define ZE_FORM         3       // zip file structure error
#define ZE_MEM          4       // out of memory
#define ZE_LOGIC        5       // internal logic error
#define ZE_BIG          6       // entry too large to split
#define ZE_NOTE         7       // invalid comment format
#define ZE_TEST         8       // zip test (-T) failed or out of memory
#define ZE_ABORT        9       // user interrupt or termination
#define ZE_TEMP         10      // error using a temp file
#define ZE_READ         11      // read or seek error
#define ZE_NONE         12      // nothing to do
#define ZE_NAME         13      // missing or empty zip file
#define ZE_WRITE        14      // error writing to a file
#define ZE_CREAT        15      // couldn't open to write
#define ZE_PARMS        16      // bad command line
#define ZE_OPEN         18      // could not open a specified file to read
#define ZE_MAXERR       18      // the highest error number


// internal file attribute
#define UNKNOWN (-1)
#define BINARY  0
#define ASCII   1

#define BEST -1                 // Use best method (deflation or store)
#define STORE 0                 // Store method
#define DEFLATE 8               // Deflation method

#define CRCVAL_INITIAL  0L

// MSDOS file or directory attributes
#define MSDOS_HIDDEN_ATTR 0x02
#define MSDOS_DIR_ATTR 0x10

// Lengths of headers after signatures in bytes
#define LOCHEAD 26
#define CENHEAD 42
#define ENDHEAD 18

// Definitions for extra field handling:
#define EB_HEADSIZE       4     /* length of a extra field block header */
#define EB_LEN            2     /* offset of data length field in header */
#define EB_UT_MINLEN      1     /* minimal UT field contains Flags byte */
#define EB_UT_FLAGS       0     /* byte offset of Flags field */
#define EB_UT_TIME1       1     /* byte offset of 1st time value */
#define EB_UT_FL_MTIME    (1 << 0)      /* mtime present */
#define EB_UT_FL_ATIME    (1 << 1)      /* atime present */
#define EB_UT_FL_CTIME    (1 << 2)      /* ctime present */
#define EB_UT_LEN(n)      (EB_UT_MINLEN + 4 * (n))
#define EB_L_UT_SIZE    (EB_HEADSIZE + EB_UT_LEN(3))
#define EB_C_UT_SIZE    (EB_HEADSIZE + EB_UT_LEN(1))


// Macros for writing machine integers to little-endian format
#define PUTSH(a,f) {UINT8 _putsh_c=(UINT8)((a)&0xff); wfunc(param,&_putsh_c,1); _putsh_c=(UINT8)((a)>>8); wfunc(param,&_putsh_c,1);}
#define PUTLG(a,f) {PUTSH((a) & 0xffff,(f)) PUTSH((a) >> 16,(f))}


// -- Structure of a ZIP file --
// Signatures for zip file information headers
#define LOCSIG     0x04034b50L
#define CENSIG     0x02014b50L
#define ENDSIG     0x06054b50L
#define EXTLOCSIG  0x08074b50L


#define MIN_MATCH  3
#define MAX_MATCH  258
// The minimum and maximum match lengths


#define WSIZE  (0x8000)
// Maximum window size = 32K. If you are really short of memory, compile
// with a smaller WSIZE but this reduces the compression ratio for files
// of size > WSIZE. WSIZE must be a power of two in the current implementation.
//

#define MIN_LOOKAHEAD (MAX_MATCH+MIN_MATCH+1)
// Minimum amount of lookahead, except at the end of the input file.
// See deflate.c for comments about the MIN_MATCH+1.
//

#define MAX_DIST  (WSIZE-MIN_LOOKAHEAD)
// In order to simplify the code, particularly on 16 bit machines, match
// distances are limited to MAX_DIST instead of WSIZE.
//


#define ZIP_HANDLE   1
#define ZIP_FILENAME 2
#define ZIP_MEMORY   3
#define ZIP_FOLDER   4



// ===========================================================================
// Constants
//

#define MAX_BITS 15
// All codes must not exceed MAX_BITS bits

#define MAX_BL_BITS 7
// Bit length codes must not exceed MAX_BL_BITS bits

#define LENGTH_CODES 29
// number of length codes, not counting the special END_BLOCK code

#define LITERALS  256
// number of literal bytes 0..255

#define END_BLOCK 256
// end of block literal code

#define L_CODES (LITERALS+1+LENGTH_CODES)
// number of Literal or Length codes, including the END_BLOCK code

#define D_CODES   30
// number of distance codes

#define BL_CODES  19
// number of codes used to transfer the bit lengths


#define STORED_BLOCK 0
#define STATIC_TREES 1
#define DYN_TREES    2
// The three kinds of block type

#define LIT_BUFSIZE  0x8000
#define DIST_BUFSIZE  LIT_BUFSIZE
// Sizes of match buffers for literals/lengths and distances.  There are
// 4 reasons for limiting LIT_BUFSIZE to 64K:
//   - frequencies can be kept in 16 bit counters
//   - if compression is not successful for the first block, all input data is
//     still in the window so we can still emit a stored block even when input
//     comes from standard input.  (This can also be done for all blocks if
//     LIT_BUFSIZE is not greater than 32K.)
//   - if compression is not successful for a file smaller than 64K, we can
//     even emit a stored file instead of a stored block (saving 5 bytes).
//   - creating new Huffman trees less frequently may not provide fast
//     adaptation to changes in the input data statistics. (Take for
//     example a binary file with poorly compressible code followed by
//     a highly compressible string table.) Smaller buffer sizes give
//     fast adaptation but have of course the overhead of transmitting trees
//     more frequently.
//   - I can't count above 4
// The current code is general and allows DIST_BUFSIZE < LIT_BUFSIZE (to save
// memory at the expense of compression). Some optimizations would be possible
// if we rely on DIST_BUFSIZE == LIT_BUFSIZE.
//

#define REP_3_6      16
// repeat previous bit length 3-6 times (2 bits of repeat count)

#define REPZ_3_10    17
// repeat a zero length 3-10 times  (3 bits of repeat count)

#define REPZ_11_138  18
// repeat a zero length 11-138 times  (7 bits of repeat count)

#define HEAP_SIZE (2*L_CODES+1)
// maximum heap size


// ===========================================================================
// Local data used by the "bit string" routines.
//

#define Buf_size (8 * 2*sizeof(UINT8))
// Number of bits used within bi_buf. (bi_buf may be implemented on
// more than 16 bits on some systems.)

// Output a 16 bit value to the bit stream, lower (oldest) byte first
#define PUTSHORT(state,w) \
{ if (state.bs.out_offset >= state.bs.out_size-1) \
	state.flush_outbuf(state.param,state.bs.out_buf, &state.bs.out_offset); \
	state.bs.out_buf[state.bs.out_offset++] = (UINT8) ((w) & 0xff); \
	state.bs.out_buf[state.bs.out_offset++] = (UINT8) ((UINT16)(w) >> 8); \
}

#define PUTBYTE(state,b) \
{ if (state.bs.out_offset >= state.bs.out_size) \
	state.flush_outbuf(state.param,state.bs.out_buf, &state.bs.out_offset); \
	state.bs.out_buf[state.bs.out_offset++] = (UINT8) (b); \
}

// DEFLATE.CPP HEADER

#define HASH_BITS  15
// For portability to 16 bit machines, do not use values above 15.

#define HASH_SIZE (unsigned)(1<<HASH_BITS)
#define HASH_MASK (HASH_SIZE-1)
#define WMASK     (WSIZE-1)
// HASH_SIZE and WSIZE must be powers of two

#define NIL 0
// Tail of hash chains

#define FAST 4
#define SLOW 2
// speed options for the general purpose bit flag

#define TOO_FAR 4096
// Matches of length 3 are discarded if their distance exceeds TOO_FAR



#define EQUAL 0
// result of memcmp for equal strings


// ===========================================================================
// Local data used by the "longest match" routines.

#define H_SHIFT  ((HASH_BITS+MIN_MATCH-1)/MIN_MATCH)
// Number of bits by which ins_h and del_h must be shifted at each
// input step. It must be such that after MIN_MATCH steps, the oldest
// byte no longer takes part in the hash key, that is:
//   H_SHIFT * MIN_MATCH >= HASH_BITS

#define max_insert_length  max_lazy_match
// Insert new strings in the hash table only if the match length
// is not greater than this length. This saves time but degrades compression.
// max_insert_length is used only for compression levels <= 3.



const int extra_lbits[LENGTH_CODES] // extra bits for each length code
= {0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0};

const int extra_dbits[D_CODES] // extra bits for each distance code
= {0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13};

const int extra_blbits[BL_CODES]// extra bits for each bit length code
= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,7};

const UINT8 bl_order[BL_CODES] = {16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15};
// The lengths of the bit length codes are sent in order of decreasing
// probability, to avoid transmitting the lengths for unused bit length codes.


typedef struct config {
	UINT16 good_length; // reduce lazy search above this match length
	UINT16 max_lazy;    // do not perform lazy search above this match length
	UINT16 nice_length; // quit search above this match length
	UINT16 max_chain;
} config;

// Values for max_lazy_match, good_match, nice_match and max_chain_length,
// depending on the desired pack level (0..9). The values given below have
// been tuned to exclude worst case performance for pathological files.
// Better values may be found for specific files.
//

const config configuration_table[10] = {
	//  good lazy nice chain
	{0,    0,  0,    0},  // 0 store only
	{4,    4,  8,    4},  // 1 maximum speed, no lazy matches
	{4,    5, 16,    8},  // 2
	{4,    6, 32,   32},  // 3
	{4,    4, 16,   16},  // 4 lazy matches */
	{8,   16, 32,   32},  // 5
	{8,   16, 128, 128},  // 6
	{8,   32, 128, 256},  // 7
	{32, 128, 258, 1024}, // 8
	{32, 258, 258, 4096}};// 9 maximum compression */

	// Note: the deflate() code requires max_lazy >= MIN_MATCH and max_chain >= 4
	// For deflate_fast() (levels <= 3) good is ignored and lazy has a different meaning.







// Data structure describing a single value and its code string.
typedef struct ct_data {
	union {
		UINT16  freq;       // frequency count
		UINT16  code;       // bit string
	} fc;
	union {
		UINT16  dad;        // father node in Huffman tree
		UINT16  len;        // length of bit string
	} dl;
} ct_data;

typedef struct tree_desc {
	ct_data *dyn_tree;      // the dynamic tree
	ct_data *static_tree;   // corresponding static tree or NULL
	const int *extra_bits;  // extra bits for each code or NULL
	int     extra_base;     // base index for extra_bits
	int     elems;          // max number of elements in the tree
	int     max_length;     // max bit length for the codes
	int     max_code;       // largest code with non zero frequency
} tree_desc;


class TTreeState
{ public:
TTreeState::TTreeState()
{ 
	tree_desc a = {dyn_ltree, static_ltree, extra_lbits, LITERALS+1, L_CODES, MAX_BITS, 0};  l_desc = a;
	tree_desc b = {dyn_dtree, static_dtree, extra_dbits, 0,          D_CODES, MAX_BITS, 0};  d_desc = b;
	tree_desc c = {bl_tree, NULL,       extra_blbits, 0,         BL_CODES, MAX_BL_BITS, 0};  bl_desc = c;
	last_lit=0;
	last_dist=0;
	last_flags=0;
}


ct_data dyn_ltree[HEAP_SIZE];    // literal and length tree
ct_data dyn_dtree[2*D_CODES+1];  // distance tree
ct_data static_ltree[L_CODES+2]; // the static literal tree...
// ... Since the bit lengths are imposed, there is no need for the L_CODES
// extra codes used during heap construction. However the codes 286 and 287
// are needed to build a canonical tree (see ct_init below).
ct_data static_dtree[D_CODES]; // the static distance tree...
// ... (Actually a trivial tree since all codes use 5 bits.)
ct_data bl_tree[2*BL_CODES+1];  // Huffman tree for the bit lengths

tree_desc l_desc;
tree_desc d_desc;
tree_desc bl_desc;

UINT16 bl_count[MAX_BITS+1];  // number of codes at each bit length for an optimal tree

int heap[2*L_CODES+1]; // heap used to build the Huffman trees
int heap_len;               // number of elements in the heap
int heap_max;               // element of largest frequency
// The sons of heap[n] are heap[2*n] and heap[2*n+1]. heap[0] is not used.
// The same heap array is used to build all trees.

UINT8 depth[2*L_CODES+1];
// Depth of each subtree used as tie breaker for trees of equal frequency

UINT8 length_code[MAX_MATCH-MIN_MATCH+1];
// length code for each normalized match length (0 == MIN_MATCH)

UINT8 dist_code[512];
// distance codes. The first 256 values correspond to the distances
// 3 .. 258, the last 256 values correspond to the top 8 bits of
// the 15 bit distances.

int base_length[LENGTH_CODES];
// First normalized length for each code (0 = MIN_MATCH)

int base_dist[D_CODES];
// First normalized distance for each code (0 = distance of 1)

UINT8 far l_buf[LIT_BUFSIZE];  // buffer for literals/lengths
UINT16 far d_buf[DIST_BUFSIZE]; // buffer for distances

UINT8 flag_buf[(LIT_BUFSIZE/8)];
// flag_buf is a bit array distinguishing literals from lengths in
// l_buf, and thus indicating the presence or absence of a distance.

unsigned last_lit;    // running index in l_buf
unsigned last_dist;   // running index in d_buf
unsigned last_flags;  // running index in flag_buf
UINT8 flags;            // current flags not yet saved in flag_buf
UINT8 flag_bit;         // current bit used in flags
// bits are filled in flags starting at bit 0 (least significant).
// Note: these flags are overkill in the current code since we don't
// take advantage of DIST_BUFSIZE == LIT_BUFSIZE.

UINT32 opt_len;          // bit length of current block with optimal trees
UINT32 static_len;       // bit length of current block with static trees

UINT32 cmpr_bytelen;     // total byte length of compressed file
UINT32 cmpr_len_bits;    // number of bits past 'cmpr_bytelen'

UINT32 input_len;        // total byte length of input file
// input_len is for debugging only since we can get it by other means.

UINT16 *file_type;       // pointer to UNKNOWN, BINARY or ASCII
//  int *file_method;     // pointer to DEFLATE or STORE
};


class TBitState
{ public:

int flush_flg;
//
unsigned bi_buf;
// Output buffer. bits are inserted starting at the bottom (least significant
// bits). The width of bi_buf must be at least 16 bits.
int bi_valid;
// Number of valid bits in bi_buf.  All bits above the last valid bit
// are always zero.
UINT8 *out_buf;
// Current output buffer.
unsigned out_offset;
// Current offset in output buffer.
// On 16 bit machines, the buffer is limited to 64K.
unsigned out_size;
// Size of current output buffer
UINT32 bits_sent;   // bit length of the compressed data  only needed for debugging???
};

class TDeflateState
{ public:
TDeflateState() {window_size=0;}

UINT8    window[2L*WSIZE];
// Sliding window. Input bytes are read into the second half of the window,
// and move to the first half later to keep a dictionary of at least WSIZE
// bytes. With this organization, matches are limited to a distance of
// WSIZE-MAX_MATCH bytes, but this ensures that IO is always
// performed with a length multiple of the block size. Also, it limits
// the window size to 64K, which is quite useful on MSDOS.
// To do: limit the window size to WSIZE+CBSZ if SMALL_MEM (the code would
// be less efficient since the data would have to be copied WSIZE/CBSZ times)
UINT32    prev[WSIZE];
// Link to older string with same hash index. To limit the size of this
// array to 64K, this link is maintained only for the last 32K strings.
// An index in this array is thus a window index modulo 32K.
UINT32    head[HASH_SIZE];
// Heads of the hash chains or NIL. If your compiler thinks that
// HASH_SIZE is a dynamic value, recompile with -DDYN_ALLOC.

UINT32 window_size;
// window size, 2*WSIZE except for MMAP or BIG_MEM, where it is the
// input file length plus MIN_LOOKAHEAD.

long block_start;
// window position at the beginning of the current output block. Gets
// negative when the window is moved backwards.

int sliding;
// Set to false when the input file is already in memory

unsigned ins_h;  // hash index of string to be inserted

unsigned int prev_length;
// Length of the best match at previous step. Matches not greater than this
// are discarded. This is used in the lazy match evaluation.

unsigned strstart;         // start of string to insert
unsigned match_start; // start of matching string
int      eofile;           // flag set at end of input file
unsigned lookahead;        // number of valid bytes ahead in window

unsigned max_chain_length;
// To speed up deflation, hash chains are never searched beyond this length.
// A higher limit improves compression ratio but degrades the speed.

unsigned int max_lazy_match;
// Attempt to find a better match only when the current match is strictly
// smaller than this value. This mechanism is used only for compression
// levels >= 4.

unsigned good_match;
// Use a faster search when the previous match is longer than this

int nice_match; // Stop searching when current match exceeds this
};

typedef __int64 lutime_t;       // define it ourselves since we don't include time.h

typedef struct iztimes {
	lutime_t atime,mtime,ctime;
} iztimes; // access, modify, create times

typedef struct zlist {
	UINT16 vem, ver, flg, how;       // See central header in zipfile.c for what vem..off are
	UINT32 tim, crc, siz, len;
	UINT32 nam, ext, cext, com;   // offset of ext must be >= LOCHEAD
	UINT16 dsk, att, lflg;           // offset of lflg must be >= LOCHEAD
	UINT32 atx, off;
	char name[MAX_PATH];          // File name in zip file
	UINT8 *extra;                  // Extra field (set only if ext != 0)
	UINT8 *cextra;                 // Extra in central (set only if cext != 0)
	UINT8 *comment;                // Comment (set only if com != 0)
	char iname[MAX_PATH];         // Internal file name after cleanup
	char zname[MAX_PATH];         // External version of internal name
	int mark;                     // Marker for files to operate on
	int trash;                    // Marker for files to delete
	int dosflag;                  // Set to force MSDOS file attributes
	struct zlist far *nxt;        // Pointer to next header in list
} TZipFileInfo;

struct TState;
typedef unsigned (*READFUNC)(TState &state, UINT8 *buf,unsigned size);
typedef unsigned (*FLUSHFUNC)(void *param, const UINT8 *buf, unsigned *size);
typedef unsigned (*WRITEFUNC)(void *param, const UINT8 *buf, unsigned size);

struct TState
{ 
	void *param;
	int level; bool seekable;
	READFUNC readfunc; FLUSHFUNC flush_outbuf;
	TTreeState ts; TBitState bs; TDeflateState ds;
	const UINT8 *err;
};

class SubZipEnumator
{
public:
	UINT8 * CreateZipFromFile (JString ocFileNameinZip, JString ocFileName)
	{		
		UINT64 u64Length;
		UINT32 u32Seek = 0;
		ocFile.Open(ocFileName);
		u64Length = ocFile.GetFileLength();
		ocFile.Seek(u32Seek, JFile::FCURRENT);
		if (u64Length > 0xFFFFFFFF)
		{
			// More than it not supported
			return NULL;
		}

		if(CreateMemory((UINT32)u64Length + /* Length of local file header*/ 0x2A + MAX_PATH) != ZE_OK)
		{
			return NULL;
		}

		ocanseek = ocFile.Seek(u32Seek, JFile::FCURRENT);
		if (ocanseek) ooffset=ocanseek; else ooffset=0;

		if(Add(ocFileNameinZip.c_str(), ocFile.GetHandle(), (UINT32)u64Length, DEFLATE))
		{
			return NULL;
		}
		ocFile.Close();
		return obuf;
	}
	SubZipEnumator() :hmapout(0),obuf(0),hfin(0),writ(0),oerr(false),ooffset(0), state(0) 
	{	
	}
	~SubZipEnumator() 
	{
		if (state!=0) 
			delete state; 
		state=0;
		Close();
	}
	UINT32 GetFileAndHeaderSize(){ return writ; }
	JZipEnumerator::unz_file_info osFileInfo;
	ZRESULT Close();
private:
	JFile ocFile;
	TZipFileInfo zfi;

	// These variables say about the file we're writing into
	// We can write to pipe, file-by-handle, file-by-name, memory-to-memmapfile
	HANDLE hmapout;           // otherwise, we'll write here (for memmap)
	unsigned ooffset;         // for hfout, this is where the pointer was initially
	ZRESULT oerr;             // did a write operation give rise to an error?
	unsigned writ;            // how far have we written. This is maintained by Add, not write(), to avoid confusion over seeks
	bool ocanseek;            // can we seek?
	UINT8 *obuf;               // this is where we've locked mmap to view.
	unsigned int opos;        // current pos in the mmap
	unsigned int mapsize;     // the size of the map we created
	
	//bool encwriting;          // if true, then we'll encrypt stuff using 'keys' before we write it to disk

	//TZipFileInfo *zfis;       // each file gets added onto this list, for writing the table at the end
	TState *state;            // we use just one state object per zip, because it's big (500k)

	ZRESULT CreateMemory(UINT32 u32Len);
	static unsigned sflush(void *param,const UINT8 *buf, unsigned *size);
	static unsigned swrite(void *param,const UINT8 *buf, unsigned size);
	unsigned int write(const UINT8 *buf,unsigned int size);
	bool oseek(unsigned int pos);
	ZRESULT GetMemory(void **pbuf, unsigned long *plen);
	

	// some variables to do with the file currently being read:
	// I haven't done it object-orientedly here, just put them all
	// together, since OO didn't seem to make the design any clearer.
	UINT32 attr; iztimes times; UINT32 timestamp;  // all open_* methods set these
	bool iseekable; long isize,ired;         // size is not set until close() on pips
	UINT32 crc;                                 // crc is not set until close(). iwrit is cumulative
	HANDLE hfin; bool selfclosehf;           // for input files and pipes
	const UINT8 *bufin; unsigned int lenin,posin; // for memory
	// and a variable for what we've done with the input: (i.e. compressed it!)
	UINT32 csize;                               // compressed size, set by the compression routines
	// and this is used by some of the compression routines
	UINT8 buf[16384];


//	ZRESULT open_file(const TCHAR *fn);
	ZRESULT open_handle(HANDLE hf,unsigned int len);
// 	ZRESULT open_mem(void *src,unsigned int len);
// 	ZRESULT open_dir();
	static unsigned sread(TState &s,UINT8 *buf,unsigned size);
	unsigned read(UINT8 *buf, unsigned size);
	ZRESULT iclose();

	ZRESULT ideflate(TZipFileInfo *zfi);
	ZRESULT istore();

	ZRESULT Add(const TCHAR *odstzn, void *hFileHandle,unsigned int len, UINT32 u32Method);
//	ZRESULT AddCentral();

	void ct_init(TState &state, UINT16 *attr);
	void init_block(TState &state);
	void pqdownheap(TState &state,ct_data *tree, int k);
	void gen_bitlen(TState &state,tree_desc *desc);
	void gen_codes (TState &state, ct_data *tree, int max_code);
	void build_tree(TState &state,tree_desc *desc);
	void scan_tree (TState &state,ct_data *tree, int max_code);
	void send_tree (TState &state, ct_data *tree, int max_code);
	void send_all_trees(TState &state,int lcodes, int dcodes, int blcodes);
	UINT32 flush_block(TState &state,UINT8 *buf, UINT32 stored_len, int eof);
	void compress_block(TState &state,ct_data *ltree, ct_data *dtree);
	void set_file_type(TState &state);
	void bi_init (TState &state,UINT8 *tgt_buf, unsigned tgt_size, int flsh_allowed);
	void send_bits(TState &state,int value, int length);
	unsigned bi_reverse(unsigned code, int len);
	void bi_windup(TState &state);
	void copy_block(TState &state, UINT8 *block, unsigned len, int header);
	void lm_init (TState &state, int pack_level, UINT16 *flags);
	void fill_window(TState &state);
	UINT32 deflate_fast(TState &state);
	UINT32 deflate(TState &state);
	int putlocal(struct zlist far *z, WRITEFUNC wfunc,void *param);
	int putcentral(struct zlist far *z, WRITEFUNC wfunc, void *param);
	UINT32 crc32(UINT32 crc, const UINT8 *buf, UINT32 len);
	lutime_t filetime2timet(const FILETIME ft);
	void filetime2dosdatetime(const FILETIME ft, WORD *dosdate,WORD *dostime);
	ZRESULT GetFileInfo(HANDLE hf, UINT32 *attr, long *size, iztimes *times, UINT32 *timestamp);
	int ct_tally (TState &state,int dist, int lc);
	int longest_match(TState &state,UINT32 cur_match);
	int build_bl_tree(TState &state);
};

#endif
