#ifndef JZipEnumeratorH
#define JZipEnumeratorH
#include "IUnCompersser.h"
#include "JCompressfile.h"
#include <queue>
#include <map>
#include <list>

typedef void* (*alloc_func) (void * opaque, UINT32 items, UINT32 size) ;
typedef void   (*free_func)  (void * opaque, void* address) ;
typedef UINT32  (*check_func) (UINT32 check, const UINT8 *buf, UINT32 len) ;
DWORD WINAPI CleanThread( LPVOID lpParam );


class JZipEnumerator : public  IUnCompersser
{
public :
	JZipEnumerator();
	BOOLEAN   GetFile();
	BOOLEAN   HasNextFile();
	JFile*    GetCurrentFile();
	UINT32	  GetCurrentFileIndex();
	BOOLEAN	  CloseCompessFile();
	void      SetMessageQueue(queue <JString> * ) ; 
	BOOLEAN   SetHandle (JFile * ) ; 
	void	  SetDeleteIndex(UINT32 u32Index);
	void	  SetReplaceIndex(JString ocFileNameinZip, JString ocFileName);
	static    IUnCompersser * IsArchive(JFile *);
	UINT32    GetFilesCount();
 	
	
	UINT32	  GetStatus()
	{
		return u32FileChange;
	}

	JString GetCompressFileName()
	{
		return ocZipFileName;
	}

	TCHAR*	  GetCurrentFileNameinZip()
	{
		return NamePointer;
	}

#pragma pack(push , 1)
	struct internal_state;
	typedef struct z_stream_s
	{
		UINT8    *next_in ;             // next input byte
		UINT32     avail_in ;            // number of bytes available at next_in
		UINT32    total_in ;            // total nb of input bytes read so far
		UINT8    *next_out ;            // next output byte should be put there
		UINT32     avail_out ;           // remaining free space at next_out
		UINT32    total_out ;           // total nb of bytes output so far
		UINT8     *msg ;                // last error message, NULL if no error
		struct internal_state *state ; // not visible by applications
		alloc_func zalloc ;            // used to allocate the internal state
		free_func  zfree ;             // used to free the internal state
		void *     opaque ;            // private data object passed to zalloc and zfree
		UINT32     data_type ;            // best guess about the data type: ascii or binary
		UINT32   adler ;                // adler32 value of the uncompressed data
		UINT32   reserved ;             // reserved for future use
	} z_stream, *z_streamp ;


	typedef struct _CentralHeader
	{
		UINT32 uL ;	
		UINT16 number_disk ;
		UINT16 number_disk_with_CD;
		UINT16 number_entry;
		UINT16 number_entry_CD;
		UINT size_central_dir;
		UINT offset_central_dir;
		UINT16 size_comment;
	}CentralHeader;

	typedef struct unz_file_info_s // unz_file_info contain information about a file in the zipfile
	{
		UINT16 version ;              // version made by                 2 bytes
		UINT16 version_needed ;       // version needed to extract       2 bytes
		UINT16 flag ;                 // general purpose bit flag        2 bytes
		UINT16 compression_method ;   // compression method              2 bytes
		UINT32 dosDate ;              // last mod file date in Dos fmt   4 bytes
		UINT32 crc ;                  // crc-32                          4 bytes
		UINT32 compressed_size ;      // compressed size                 4 bytes
		UINT32 uncompressed_size ;    // uncompressed size               4 bytes
		UINT16 size_filename ;        // filename length                 2 bytes
		UINT16 size_file_extra ;      // extra field length              2 bytes
		UINT16 size_file_comment ;    // file comment length             2 bytes
		UINT16 disk_num_start ;       // disk number start               2 bytes
		UINT16 internal_fa ;          // internal file attributes        2 bytes
		UINT32 external_fa ;
		UINT32 Offset_curfile ;
		UINT8 *TempBlock ;
	} unz_file_info ;

	typedef struct unz_file_Header_s // File Header
	{
		UINT32 Magic;				  // Local file header signature = 0x04034b50
		UINT16 version_needed ;       // version needed to extract       2 bytes
		UINT16 flag ;                 // general purpose bit flag        2 bytes
		UINT16 compression_method ;   // compression method              2 bytes
		UINT32 dosDate ;              // last mod file date in Dos fmt   4 bytes
		UINT32 crc ;                  // crc-32                          4 bytes
		UINT32 compressed_size ;      // compressed size                 4 bytes
		UINT32 uncompressed_size ;    // uncompressed size               4 bytes
		UINT16 size_filename ;        // filename length                 2 bytes
		UINT16 size_file_extra ;      // extra field length              2 bytes
	} unz_file_Header ;

	typedef struct
	{
		UINT8  *read_buffer ;            // internal buffer for compressed data
		z_stream stream ;               // zLib stream structure for inflate
		UINT32 pos_in_zipfile ;          // position in byte on the zipfile, for fseek
		UINT32 stream_initialised ;      // flag set if stream structure is initialised
		UINT32 offset_local_extrafield ; // offset of the local extra field
		UINT32  size_local_extrafield ;   // size of the local extra field
		UINT32 pos_local_extrafield ;    // position in the local extra field in read
		UINT32 crc32 ;                   // crc32 of all data uncompressed
		UINT32 crc32_wait ;              // crc32 we must obtain after decompress all
		UINT32 rest_read_compressed ;    // number of byte to be decompressed
		UINT32 rest_read_uncompressed ;  //number of byte to be obtained after decomp
		UINT32 compression_method ;      // compression method (0==store)
		UINT32 byte_before_the_zipfile ; // byte before the zipfile, (>0 for sfx)
		BOOLEAN encrypted ;                // is it encrypted?
		UINT32 keys[3] ;         // decryption keys, initialized by unzOpenCurrentFile
		int encheadleft ;               // the first call(s) to unzReadCurrentFile will read this many encryption-header bytes first
		UINT8 crcenctest ;               // if encrypted, we'll check the encryption buffer against this
	} file_in_zip_read_info_s ;

	typedef enum
	{
		IM_METHOD,   // waiting for method byte
		IM_FLAG,     // waiting for flag byte
		IM_DICT4,    // four dictionary check bytes to go
		IM_DICT3,    // three dictionary check bytes to go
		IM_DICT2,    // two dictionary check bytes to go
		IM_DICT1,    // one dictionary check byte to go
		IM_DICT0,    // waiting for inflateSetDictionary
		IM_BLOCKS,   // decompressing blocks
		IM_CHECK4,   // four check bytes to go
		IM_CHECK3,   // three check bytes to go
		IM_CHECK2,   // two check bytes to go
		IM_CHECK1,   // one check byte to go
		IM_DONE,     // finished check, done
		IM_BAD       // got an error--stay here
	} inflate_mode ;

	typedef enum
	{
		IBM_TYPE,     // get type bits (3, including end bit)
		IBM_LENS,     // get lengths for stored
		IBM_STORED,   // processing stored block
		IBM_TABLE,    // get table lengths
		IBM_BTREE,    // get bit lengths tree for a dynamic block
		IBM_DTREE,    // get length, distance trees for a dynamic block
		IBM_CODES,    // processing fixed or dynamic block
		IBM_DRY,      // output remaining window bytes
		IBM_DONE,     // finished last block, done
		IBM_BAD       // got a data error--stuck here
	} inflate_block_mode ;

	struct inflate_huft
	{
		union
		{
			struct
			{
				UINT8 Exop ; // number of extra bits or operation
				UINT8 Bits ; // number of bits in this code or subcode
			} what ;
			UINT32 pad ;      // pad structure to a power of 2 (4 bytes for
		} word ;            //  16-bit, 8 bytes for 32-bit int's)
		UINT32 base ;         // literal, length base, distance base, or table offset
	} ;

	typedef enum  // waiting for "i:"=input, "o:"=output, "x:"=nothing
	{
		START,    // x: set up for LEN
		LEN,      // i: get length/literal/eob next
		LENEXT,   // i: getting length extra (have base)
		DIST,     // i: get distance next
		DISTEXT,  // i: getting distance extra
		COPY,     // o: copying bytes in window, waiting for space
		LIT,      // o: got literal, waiting for output space
		WASH,     // o: got eob, possibly still output waiting
		END,      // x: got eob and all data flshed
		BADCODE   // x: got error
	}
	inflate_codes_mode ;

	// inflate codes private state
	struct inflate_codes_state
	{
		// mode
		inflate_codes_mode mode ;          // current inflate_codes mode

		// mode dependent information
		UINT32 len ;
		union
		{
			struct
			{
				const inflate_huft *tree ; // pointer into tree
				UINT32 need ;                // bits needed
			} code ;                       // if LEN or DIST, where in tree
			UINT32 lit ;                     // if LIT, literal
			struct
			{
				UINT32 get ;                 // bits to get for extra
				UINT32 dist ;                // distance back to copy from
			} copy ;                       // if EXT or COPY, where and how mUINT8
		} sub ;                            // submode

		// mode independent information
		BYTE lbits ;                       // ltree bits decoded per branch
		BYTE dbits ;                       // dtree bits decoder per branch
		const inflate_huft *ltree ;        // literal/length/eob tree
		const inflate_huft *dtree ;        // distance tree
	} ;
	struct inflate_blocks_state
	{
		// mode
		inflate_block_mode  mode ; // current inflate_block mode

		// mode dependent information
		union
		{
			UINT32 left ;            // if STORED, bytes left to copy
			struct
			{
				UINT32  table ;      // table lengths (14 bits)
				UINT32  index ;      // index into blens (or border)
				UINT32 *blens ;      // bit lengths of codes
				UINT32  bb ;         // bit length tree depth
				inflate_huft *tb ; // bit length decoding tree
			} trees ;              // if DTREE, decoding info for trees
			struct
			{
				inflate_codes_state *codes ;
			} decode ;             // if CODES, current state
		} sub ;                    // submode
		UINT32 last ;                // true if this block is the last block

		// mode independent information
		UINT32  bitk ;               // bits in bit buffer
		UINT32 bitb ;               // bit buffer
		inflate_huft *hufts ;      // single malloc for tree space
		UINT8 *window ;             // sliding window
		UINT8 *end ;                // one byte after sliding window
		UINT8 *read ;               // window read pointer
		UINT8 *write ;              // window write pointer
		check_func checkfn ;       // check function
		UINT32 check ;              // check on output
	} ;
	struct internal_state
	{
		// mode
		inflate_mode  mode ;            // current inflate mode

		// mode dependent information
		union
		{
			UINT32 method ;               // if IM_FLAGS, method byte
			struct
			{
				UINT32 was ;             // computed check value
				UINT32 need ;            // stream check value
			} check ;                   // if CHECK, check values to compare
			UINT32 marker ;               // if IM_BAD, inflateSync's marker bytes count
		} sub ;                         // submode

		// mode independent information
		UINT32  nowrap ;                   // flag for no wrapper
		UINT32 wbits ;                    // log2(window size)  (8..15, defaults to 15)
		inflate_blocks_state *blocks ; // current inflate_blocks state
	} ;
#pragma pack(pop)
private :
	UINT32					u32FileChange;
	list <UINT32>			ocDeleteIndexList;
	map <JString, JString>	ocReplacedItemIndex;
	typedef pair <JString, JString> Pair;

	UINT32 CleanZipFile();
	file_in_zip_read_info_s  pfile_in_zip_read_info ;
	UINT32  byte_before_the_zipfile ;                 // byte before the zipfile, (>0 for sfx)
	UINT32  num_file ;                                // number of the current file in the zipfile
	UINT32 pos_in_central_dir ;                       // pos of the current file in the central dir
	BOOLEAN current_file_ok ;                          // flag about the usability of the current file
	UINT32 central_pos ;                              // position of the beginning of the central dir
// 	UINT32 size_central_dir ;                         // size of the central directory
// 	UINT32 offset_central_dir ;                       // offset of start of central directory 
// 	UINT16 number_entry ;     // total number of entries in the central dir on this disk
	JString ocZipFileName;
	UINT16 size_comment ;     // size of the global comment of the zipfile
	unz_file_info cur_file_info ;
	UINT32 offset_curfile ; 
	UINT32 u32FilesCount ;

	CentralHeader osCentralHeader;
	static const UINT8 SIZECENTRALDIRITEM = 0x2e ;
	static const UINT8 SIZEZIPLOCALHEADER = 0x1e ;
	static const UINT16 UNZ_BUFSIZE = 16384 ;
	static const UINT8 Z_DEFLATED = 8 ;
	static const UINT16 MANY = 1440 ;
	static const UINT8 PRESET_DICT = 0x20 ;
	static const UINT8 fixed_bl = 9 ;
	static const UINT8 fixed_bd = 5 ;
	static const UINT8 BMAX = 15 ;
	static const UINT16  BUFREADCOMMENT = 0x400 ;
	JFile *m_pclsZipFile ;
	JCompressFile *m_pclsUnzipFile ;
	static const UINT16 m_u16FileNameSize = 1024;
	TCHAR  m_strCurrentFileName[m_u16FileNameSize] ;
	UINT8 extraField[1];// “„«‰Ì òÂ „ÌŒÊ«ÂÌ„ «ò” —« ›Ì·œ —« »ŒÊ«‰Ì„ «‰œ«“Â ¬—«ÌÂ —« 1024 „‰ ”» „Ìò‰Ì„
	UINT8 CommentField[1]; // “„«‰Ì òÂ „ÌŒòÊ«ÂÌ„ ò«„‰  Â« —« ‰Ì“ »ŒÊ«‰Ì„ „ﬁœ«— 1024 —« „‰ ”» „Ìò‰Ì„
	typedef enum __enUnZipRetVal
	{
		 Z_OK ,
		 UNZ_ERRNO ,
		 UNZ_BADZIPFILE ,
		 UNZ_END_OF_LIST_OF_FILE ,
		 UNZ_EOF,
		 Z_STREAM_ERROR , 
		 Z_DATA_ERROR  , 
		 Z_MEM_ERROR , 
		 Z_BUF_ERROR ,
         Z_VERSION_ERROR ,
		 UNZ_PASSWORD , 
		 Z_STREAM_END ,
		 Z_SYNC_FLUSH ,
		 Z_NO_FLUSH ,
		 Z_FINISH ,
		 Z_NEED_DICT
	}_enUnZipRetVal;

	TCHAR *NamePointer ;
	char m_szCurrentFileName[MAX_PATH] ;
	queue <JString> *MessageQueue ;
	UINT32 m_u32CentralPos ;
	void inflate_blocks_new(inflate_blocks_state *s , UINT32 *c);
	_enUnZipRetVal GetFileInfoInternal();
	_enUnZipRetVal GetFileInfoInternalForClean();
	_enUnZipRetVal getLong(UINT32 *o_u32X);
	_enUnZipRetVal getByte(UINT8 *o_u8X);
	_enUnZipRetVal getShort(UINT16 *o_u16X);
	void ImproveFileName(TCHAR TempFileName[]);
	//_enZipRetVal OpenCurrentFile();
	_enUnZipRetVal inflateInit2();
	_enUnZipRetVal inflateReset ();
	inflate_blocks_state * inflate_blocks_new ()   ;
	void inflate_blocks_reset(inflate_blocks_state *s , UINT32 *c);
	_enUnZipRetVal inflate_blocks (inflate_blocks_state *s,  JZipEnumerator::_enUnZipRetVal r);
	_enUnZipRetVal JZipEnumerator::inflate_trees_bits (UINT32 *c,	UINT32 *bb,	inflate_huft **tb, inflate_huft *hp) ;

	_enUnZipRetVal inflateEnd ();
	_enUnZipRetVal inflate (JZipEnumerator::_enUnZipRetVal f);
	_enUnZipRetVal unzReadCurrentFile(UINT8 unzbuf[] , BOOLEAN *reached_eof) ;
	_enUnZipRetVal CheckCurrentFileCoherencyHeader(UINT32 &SizeVar,UINT32 &offset_local_extrafield ,UINT32 &size_local_extrafield) ;
	void inflate_blocks_reset(z_stream *s , UINT32 *c);
	
	inline static void   inflate_trees_fixed (UINT32 *bl, UINT32 *bd, const inflate_huft ** tl, const inflate_huft **td) ;
	_enUnZipRetVal huft_build (UINT32 *b, UINT32 n,UINT32 s,const UINT16 *d,const UINT8 *e,inflate_huft * *t,UINT32 *m,inflate_huft *hp,UINT32 *hn,UINT32 *v) ;
	_enUnZipRetVal inflate_trees_dynamic (UINT32 nl, 	UINT32 nd,UINT32 *c,UINT32 *bl,UINT32 *bd,inflate_huft **tl,inflate_huft **td,inflate_huft *hp) ;
	inflate_codes_state * inflate_codes_new (UINT32 bl, UINT32 bd, const inflate_huft *tl,	const inflate_huft *td );
	_enUnZipRetVal inflate_codes (inflate_blocks_state *s, _enUnZipRetVal r);
	_enUnZipRetVal inflate_fast (UINT32 bl, UINT32 bd, const inflate_huft *tl,const inflate_huft *td,inflate_blocks_state *s);
	_enUnZipRetVal inflate_flush (inflate_blocks_state *s, _enUnZipRetVal r);
	static UINT32 unzlocal_SearchCentralDir (JFile *);
	void unzCloseCurrentFile ();
	inline void  NeedBits(UINT32 &j , UINT32  &k , UINT32 &b , UINT32  &n , UINT8 *&p) ;
	
	size_t WriteSize ;
	static inflate_huft fixed_tl[];
	static inflate_huft fixed_td[];
	static UINT8 border[];
	static UINT16 inflate_mask[] ;
	static UINT16 cplens[] ;
	static UINT8 cplext[] ;
	static UINT16 cpdist[];
	static UINT8 cpdext[] ;	
};

/*class IZipEnum : public CompFile 
{
	friend JZipEnumerator;
private :
	IZipEnum() ;
	JZipEnumerator *ZipEnum ;
public :
	LPTSTR    virtual GetFile() ;
	BOOLEAN   virtual SetHandle (JFile *File ) ;
};*/
#endif 
