#ifndef UNRARH
#define UNRARH
#include "IUnCompersser.h"
#include "JCompressfile.h"
#include <list>
#include <map>

#define UNRAR_MAIN_HEADER_TAG_LEN 13 

#pragma pack(push , 1)


typedef struct __UrarCommentHeader__
{
	UINT16  Crc  ; 
	UINT8   Type ;
	UINT16  Flags ;
	UINT16  Size  ;
	UINT16  UnpackSize ;  
	UINT8   UnpackVer ;
	UINT8   Method;
	UINT16  CommentCrc ;
} UrarCommentHeader , *PUrarCommentHeader;


typedef struct __UnrarMainHeader__
{
	UINT16 Crc ;
	UINT8  Type;
	UINT16 Flags ;
	UINT16 Size ;
	UINT16 HighPosav ;
	UINT32 Posav ;
} UnrarMainHeader , *PUnrarMainHeader;

typedef struct __UnrarFileHeader__
{
	UINT16   crc ;
	UINT8    Type;
	UINT16   Flags ;
	UINT16   HeadSize ;
	UINT32   PackSize ;
	UINT32   UnpackSize ; 
	UINT8    HostOs;
	UINT32   FileCrc ;
	UINT32   FileTime ;
	UINT8    UnpackVer;
	UINT8    Method;
	UINT16   NameSize ;
	UINT32   FileAttrib ;
	UINT32   HighPackSize ;   
	UINT32   HighUnpackSize ; 
	char Filename[MAX_PATH] ;
	UINT32 start_offset ;
	UINT32 next_offset ;
} UnrarFileHeader , *P__UnrarFileHeader__;

typedef struct __UnrarMetadata__
{
	UINT64 PackSize;
	UINT64 UnpackSize;
	char *FileName;
	struct  __UnrarMetadata__ *Next;
	UINT32 Crc;
	unsigned int Encrypted;
	UINT8 Method;
} UnrarMetadata , *PUnrarMetadata;


static unsigned int dec_l1[]={0x8000,0xa000,0xc000,0xd000,0xe000,0xea00,
0xee00,0xf000,0xf200,0xf200,0xffff};
static unsigned int pos_l1[]={0,0,0,2,3,5,7,11,16,20,24,32,32};

static unsigned int dec_l2[]={0xa000,0xc000,0xd000,0xe000,0xea00,0xee00,
0xf000,0xf200,0xf240,0xffff};
static unsigned int pos_l2[]={0,0,0,0,5,7,9,13,18,22,26,34,36};

static unsigned int dec_hf0[]={0x8000,0xc000,0xe000,0xf200,0xf200,0xf200,
0xf200,0xf200,0xffff};
static unsigned int pos_hf0[]={0,0,0,0,0,8,16,24,33,33,33,33,33};


static unsigned int dec_hf1[]={0x2000,0xc000,0xe000,0xf000,0xf200,0xf200,
0xf7e0,0xffff};
static unsigned int pos_hf1[]={0,0,0,0,0,0,4,44,60,76,80,80,127};


static unsigned int dec_hf2[]={0x1000,0x2400,0x8000,0xc000,0xfa00,0xffff,
0xffff,0xffff};
static unsigned int pos_hf2[]={0,0,0,0,0,0,2,7,53,117,233,0,0};


static unsigned int dec_hf3[]={0x800,0x2400,0xee00,0xfe80,0xffff,0xffff,
0xffff};
static unsigned int pos_hf3[]={0,0,0,0,0,0,0,2,16,218,251,0,0};


static unsigned int dec_hf4[]={0xff00,0xffff,0xffff,0xffff,0xffff,0xffff};
static unsigned int pos_hf4[]={0,0,0,0,0,0,0,0,0,255,0,0,0};

static UINT8	pu8EndOfArchive [] = {0xC4, 0x3D, 0x7B, 0x00, 0x40, 0x07, 0x00};

#pragma pack(pop)

class Unrar : public IUnCompersser
{

public :
	Unrar(UINT32 MaxSizeFile)	;
	Unrar() ;
	BOOLEAN HasNextFile();
	BOOLEAN GetFile () ;
	BOOLEAN SetHandle( JFile *i_pclsFile) ;

	JFile * GetCurrentFile() ;
	UINT32  GetCurrentFileIndex () ;
	BOOLEAN CloseCompessFile();
	static IUnCompersser * IsArchive(JFile * i_pclsFile);
	void    SetMessageQueue(queue <JString> *) ; 

//Kia Develop
	BOOLEAN ExtractCurrentFile (TCHAR * PathToSaveExtractedFile) ;	
	int Count();
	struct RarDirectory
	{
		INT64 m_i64FileHeaderOffset;
		UINT32 m_u32HeadAndBodySize, m_u32Index;
		
		//RarDirectory * NextNode;
		//RarVirList * PreviousNode;
		RarDirectory()
		{
			//NextNode = NULL ;
			m_u32HeadAndBodySize = 0 ;
			m_u32Index = -1;
			m_i64FileHeaderOffset = -1 ;
		}
	};
	BOOLEAN RemoveEntries(RarDirectory * List/*, INT64 ListCount*/);
	UINT32 CleanRarFile();
	void SetDeleteIndex(UINT32 u32Index) ;
	void SetReplaceIndex(JString ocFileNameinZip, JString ocFileName);
	
	UINT32 GetFilesCount()
	{
		return u32FilesCount;
	}
	JString GetCompressFileName()
	{
		return ocRarFileName;
	}

	UINT32  GetStatus()
	{
		return u32FileChange;
	}
	TCHAR * GetCurrentFileNameinZip()
	{
		return NamePointer;
	}
	~Unrar();

private :
	list <UINT32>			ocDeleteIndexList;
	map <JString, JString>	ocReplacedItemIndex;
	typedef pair <JString, JString> Pair;

	list <RarDirectory>		ocMainDirectory;

	UINT32					u32SubHeadNumber;
	UINT32					u32ItemIndex;
	UINT32					u32FileChange;
	INT64 FileCount;
	INT64 m_i64WritePointer;

	void SeekToFirstBlock();
	BOOLEAN CopyDataBlock(INT64 WriteStartOffset, INT64 ReadStartOffset, INT64 ReadSize);
//End Kia Develop

	static const UINT32 CopyBlock = 8192;	
	
	BOOLEAN ReadMainHeader();
	BOOLEAN ReadFileHeader ();
	BOOLEAN ReadCommentHeader();
	BOOLEAN ReadBlock() ;
	BOOLEAN CopyDataFromFile(UINT32 Size);
	queue <JString> *MessageQueue ;
	static const UINT16 m_u16FileNameSize = 1024;
	TCHAR m_strCurrentFileName[m_u16FileNameSize];
	TCHAR *NamePointer;
	BOOLEAN SoldCorrupt ;
	void close();
	JString ocRarFileName;

	//-------------------------------------------------------
	static const UINT32 RAR_MAX_ALLOCATION  = 184549376;
	static const UINT8 SIZEOF_MARKHEAD =  7 ;
	static const UINT8 SIZEOF_NEWLHD =  32 ;
	static const UINT8 SIZEOF_SHORTBLOCKHEAD  = 7 ;
	static const UINT8 SIZEOF_LONGBLOCKHEAD =  11 ;
	static const UINT8 SIZEOF_SUBBLOCKHEAD  = 14 ; 
	static const UINT8 SIZEOF_COMMHEAD =  13 ;
	static const UINT8 SIZEOF_PROTECTHEAD  = 26 ;
	static const UINT8 SIZEOF_AVHEAD  = 14 ;
	static const UINT8 SIZEOF_SIGNHEAD  = 15 ;
	static const UINT8 SIZEOF_UOHEAD  = 18 ;
	static const UINT8 SIZEOF_MACHEAD = 22;
	static const UINT8 SIZEOF_EAHEAD  = 24 ;
	static const UINT8 SIZEOF_BEEAHEAD = 24;
	static const UINT8 SIZEOF_STREAMHEAD  = 26 ;
	static const UINT8 MAX_O  = 64 ;

	static const UINT16 MHD_VOLUME		= 0x0001 ;
	static const UINT16 MHD_COMMENT	    = 0x0002 ;
	static const UINT16 MHD_LOCK	    = 0x0004 ;
	static const UINT16 MHD_SOLID		= 0x0008 ;
	static const UINT16 MHD_PACK_COMMENT= 0x0010 ;
	static const UINT16 MHD_NEWNUMBERING= 0x0010 ;
	static const UINT16 MHD_AV			= 0x0020 ;
	static const UINT16 MHD_PROTECT		= 0x0040 ;
	static const UINT16 MHD_PASSWORD	= 0x0080 ;
	static const UINT16 MHD_FIRSTVOLUME	= 0x0100 ;
	static const UINT16 MHD_ENCRYPTVER	= 0x0200 ;

	static const UINT16 LHD_SPLIT_BEFORE= 0x0001 ;
	static const UINT16 LHD_SPLIT_AFTER	= 0x0002 ;
	static const UINT16 LHD_PASSWORD    = 0x0004 ;
	static const UINT16 LHD_COMMENT	    = 0x0008 ;
	static const UINT16 LHD_SOLID	    = 0x0010 ;
	static const UINT16 LHD_ISDIR       = 0x00E0 ;

	static const UINT16 LONG_BLOCK      = 0x8000 ;

	static const UINT8 BC20  = 19 ;
	static const UINT8 DC20  = 48 ;
	static const UINT8 RC20  = 28 ;
	static const UINT16 MC20 =  257 ;
	static const UINT16 NC20 =  298 ;

	static const UINT16 NC              = 299;
	static const UINT16 DC              = 60 ;
	static const UINT16 RC		        = 28;
	static const UINT16 LDC		        = 17;
	static const UINT16 BC		        = 20;
	static const UINT16 HUFF_TABLE_SIZE = NC+DC+RC+LDC;

	static const UINT16 MAX_BUF_SIZE    = 32768;
	static const UINT32 MAXWINSIZE      = 0x400000;
	static const UINT32 MAXWINMASK      = MAXWINSIZE-1;
	static const UINT8 LOW_DIST_REP_COUNT  =16;
	static const UINT8 N1  = 4 ;
	static const UINT8 N2  = 4 ;
	static const UINT8 N3  = 4 ;
	static const UINT8 N4  = 26 ;
	static const UINT8 N_INDEXES = 38;

	static const UINT32 RARVM_MEMSIZE =	0x40000 ;
	static const UINT32 RARVM_MEMMASK =(RARVM_MEMSIZE-1) ;

	static const UINT32 VM_GLOBALMEMADDR     =       0x3C000 ;
	static const UINT16 VM_GLOBALMEMSIZE     =       0x2000 ;
	static const UINT8  VM_FIXEDGLOBALSIZE   =       64 ;

	static const UINT8 STARTL1  = 2 ; 
	static const UINT8 STARTL2  = 3 ; 
	static const UINT8 STARTHF0 = 4 ; 
	static const UINT8 STARTHF1 = 5 ; 
	static const UINT8 STARTHF2 = 5 ; 
	static const UINT8 STARTHF3 = 6 ;
	static const UINT8 STARTHF4 = 8 ; 

	static const UINT8 READBUFBOUND= 30 ;

	static const UINT32 MAXMEMORYAAVLIBALE = 138412020 ;

	static const unsigned int FIXED_UNIT_SIZE=12;
	static const int INT_BITS=7, PERIOD_BITS=7, TOT_BITS=14;
	static const int INTERVAL=1 << 7, BIN_SCALE=1 << 14, MAX_FREQ=124;
	static const unsigned int TOP=1 << 24, BOT=1 << 15;


	struct Decode;
	//Unrar() ;
	UnrarFileHeader *file_header;
	//UnrarMetadata *metadata;
	//UnrarMetadata *metadata_tail;
	UnrarMainHeader *main_hdr;
	UrarCommentHeader *comment_hdr;
	unsigned long file_count;
	UINT64 maxfilesize;
	JFile * m_pclsRarFile ;
	JCompressFile * m_pclsUnrarFile;
	INT64 NextHeaderFile ;
	UINT32 u32FilesCount ;
#pragma pack(push , 1)
	//--------------------------------------------------------------------------
	///------------------------Data20-------------------------------------------
	void InitUpack20 (BOOLEAN solid);
	//--------------------------------------------------------------------------
	//----------------------------------------------------------------------------
	//---------------------------Filters------------------------------------------
	struct rar_filter_array_t ;
	struct UnpackFilter;
	void InitFilter() ;
	void FilterArrayReset() ;
	void FilterDelete(int i) ;
	void PragStackDelete(int i) ;
	__inline BOOLEAN rar_filter_array_add(rar_filter_array_t *filter_a, int num);
	UnpackFilter *rar_filter_new(void) ;
	//----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------
	//---------------------------Upacker-------------------------------------------
	BOOLEAN Unpack (int Version ,BOOLEAN solid ) ;
	BOOLEAN Upack15 (BOOLEAN solid ) ;
	BOOLEAN Upack20 (BOOLEAN solid ) ;
	BOOLEAN Upack29 (BOOLEAN solid ) ;
	BOOLEAN InitDataUpack15 (BOOLEAN solid); 
	BOOLEAN UpackReadBuffer ();
	BOOLEAN UnpackInitData(BOOLEAN solid); 
	void unp_write_buf_old() ; 
	BOOLEAN get_char(unsigned int &Arg) ;
	void unp_write_data(UINT8 *data, int size) ;

	//-----------------------------------------------------------------------------
	//-----------------------------------------------------------------------------
	//--------------------------Unpck20--------------------------------------------
	struct range_coder_t ;
	BOOLEAN read_tables20();
	void make_decode_tables(unsigned char *len_tab, Unrar::Decode *decode, int size);
	int decode_number(Unrar::Decode *decode) ;
	unsigned char decode_audio(int delta);
	void copy_string20(unsigned int length, unsigned int distance) ;
	void read_last_tables();
	void range_coder_init_decoder(range_coder_t *coder);

	//--------------------------------------------------------------------------------
	//----------------------------upack29---------------------------------------------
	struct ppm_data_t ;
	struct state_tag; 
	struct ppm_context;
	struct see2_context_tag;
	enum rarvm_standard_filters_t;
	struct rarvm_prepared_operand ;
	BOOLEAN read_tables();
	void sub_allocator_stop_sub_allocator() ;
	BOOLEAN sub_allocator_start_sub_allocator(int sa_size) ;
	BOOLEAN start_model_rare(int max_order);
	BOOLEAN restart_model_rare();
	void sub_allocator_init_sub_allocator();
	void *sub_allocator_alloc_context();
	void *sub_allocator_remove_node(int index) ;
	void sub_allocator_insert_node(void *p, int index) ;
	void *sub_allocator_alloc_units_rare(int index) ;
	void sub_allocator_glue_free_blocks();
	void *sub_allocator_shrink_units (void *old_ptr, int old_nu, int new_nu) ;
	void sub_allocator_split_block(void *pv, int old_indx, int new_indx) ;
	void *sub_allocator_expand_units( void *old_ptr, int old_nu);
	void *sub_allocator_alloc_units(int nu);
	void update1(Unrar::state_tag *p) ;
	void unp_write_buf();
	void unp_write_area(unsigned int start_ptr, unsigned int end_ptr);
	__inline int coder_get_current_count() ;
	see2_context_tag * make_esc_freq(int diff);
	__inline unsigned int get_mean(struct see2_context_tag *see2_cont);
	__inline void update(struct see2_context_tag *see2_cont);
	__inline void update2(struct state_tag *p);
	__inline void clear_mask() ;
	BOOLEAN update_model() ;
	ppm_context *create_successors(int skip,state_tag *p1) ;
	ppm_context *create_child( Unrar::ppm_context *context,	struct state_tag *pstats, struct state_tag *first_state) ;
	BOOLEAN add_vm_code( unsigned int first_byte,unsigned char *vmcode,UINT32 code_size) ;
	__inline rarvm_standard_filters_t is_standard_filter(unsigned char *code, int code_size) ;
	void vm_decode_arg(rarvm_prepared_operand *op, int byte_mode) ;

	void filter_delete(int i);
	//---------------------------------------------------------------------------------
	//--------------------------ppm----------------------------------------------------
	typedef struct rar_mem_blk_tag
	{
		struct rar_mem_blk_tag *next, *prev;
		UINT16 stamp, nu;
	} rar_mem_blk_t;

	struct rar_node
	{
		struct rar_node *next;
	};

	typedef struct sub_allocator_tag
	{
		UINT8 *ptext, *units_start, *heap_end, *fake_units_start;
		UINT8 *heap_start, *lo_unit, *hi_unit;
		long sub_allocator_size;
		struct rar_node free_list[N_INDEXES];
		UINT16 indx2units[N_INDEXES], units2indx[128], glue_count;
	} sub_allocator_t;

	struct range_coder_t
	{
		unsigned int low, code, range;
		unsigned int low_count, high_count, scale;
	};

	struct see2_context_tag
	{
		UINT16 summ;
		UINT8 shift, count;
	};

	struct freq_data_tag
	{
		struct state_tag *stats;
		UINT16 summ_freq;
	} ;

	struct ppm_data_t
	{
		struct state_tag *found_state;
		struct Unrar::ppm_context *min_context, *max_context;
		struct see2_context_tag see2cont[25][16], dummy_sse2cont;
		int num_masked;
		sub_allocator_t sub_alloc;
		range_coder_t coder;
		int init_esc, order_fall, max_order, run_length, init_rl;
		UINT8 char_mask[256], ns2indx[256], ns2bsindx[256], hb2flag[256];
		UINT16 bin_summ[128][64];
		UINT8 esc_count, prev_success, hi_bits_flag;

	};

	struct __Unpackdata__ ;

	void ppm_cleanup();
	BOOLEAN ppm_decode_init();
	int ppm_decode_char(ppm_data_t *ppm_data, int fd, struct __Unpackdata__ *unpack_data);
	void ppm_constructor() ;
	void ppm_destructor(ppm_data_t *ppm_data);

	//------------------------------------------------------------------------------
	//------------------------------Memory-----------------------------------------
	void *UrarMalloc(size_t size);
	void *UrarRealloc2(void *ptr, size_t size);

	//---------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------
	//-----------------------------CMD---------------------------------------
	struct rarvm_prepared_command;
	typedef struct rar_cmd_array_tag
	{
		struct rarvm_prepared_command *array;
		size_t num_items;
	} rar_cmd_array_t;

	void rar_cmd_array_init(rar_cmd_array_t *cmd_a);
	BOOLEAN rar_cmd_array_add(rar_cmd_array_t *cmd_a, int num);
	//----------------------------------------------------------------------------------
	//---------------------------HuffManDecoder-----------------------------------------
	void HuffInit () ; //init_huff
	void corr_huff(unsigned int *char_set, unsigned int *num_to_place) ;
	void get_flag_buf () ;
	void huff_decode() ;
	void copy_string15(unsigned int distance, unsigned int length) ;
	void long_lz();
	void short_lz();
	//----------------------------------------------------------------------------------
	//----------------------------------------------------------------------------------
	unsigned int getbits() ;
	void addbits(int bits) ; // rar_addbits 
	unsigned int decode_num (UINT32 i_u32Num, UINT32  i_u32Start_pos,UINT32 * i_pu32Dec_tab,UINT32 * i_pu32Pos_tab);



	//-----------------------------------------------------------------------------------
	//----------------------------VirtualMachine-----------------------------------------
	typedef enum rarvm_commands
	{
		VM_MOV,  VM_CMP,  VM_ADD,  VM_SUB,  VM_JZ,   VM_JNZ,  VM_INC,  VM_DEC,
		VM_JMP,  VM_XOR,  VM_AND,  VM_OR,   VM_TEST, VM_JS,   VM_JNS,  VM_JB,
		VM_JBE,  VM_JA,   VM_JAE,  VM_PUSH, VM_POP,  VM_CALL, VM_RET,  VM_NOT,
		VM_SHL,  VM_SHR,  VM_SAR,  VM_NEG,  VM_PUSHA,VM_POPA, VM_PUSHF,VM_POPF,
		VM_MOVZX,VM_MOVSX,VM_XCHG, VM_MUL,  VM_DIV,  VM_ADC,  VM_SBB,  VM_PRINT,
		VM_MOVB, VM_MOVD, VM_CMPB, VM_CMPD, VM_ADDB, VM_ADDD, VM_SUBB, VM_SUBD,
		VM_INCB, VM_INCD, VM_DECB, VM_DECD, VM_NEGB, VM_NEGD, VM_STANDARD
	} rarvm_commands_t;

	enum rarvm_standard_filters_t {
		VMSF_NONE, VMSF_E8, VMSF_E8E9, VMSF_ITANIUM, VMSF_RGB, VMSF_AUDIO,
		VMSF_DELTA, VMSF_UPCASE
	} ;

	enum VM_Flags {
		VM_FC=1,
		VM_FZ=2,
		VM_FS=0x80000000
	};

	enum rarvm_op_type {
		VM_OPREG,
		VM_OPINT,
		VM_OPREGMEM,
		VM_OPNONE
	};

	struct rarvm_prepared_operand {
		unsigned int *addr;
		enum rarvm_op_type type;
		unsigned int data;
		unsigned int base;
	};

	struct rarvm_prepared_command {
		rarvm_commands_t op_code;
		int byte_mode;
		struct rarvm_prepared_operand op1, op2;
	};

	struct rarvm_prepared_program {
		rar_cmd_array_t cmd;
		struct rarvm_prepared_command *alt_cmd;
		unsigned char *global_data;
		unsigned char *static_data;
		UINT8 *filtered_data;
		UINT32 global_size, static_size;
		UINT32 cmd_count;
		UINT32 init_r[7];
		UINT32 filtered_data_size;
	};

	typedef struct rarvm_input_tag {
		unsigned char *in_buf;
		int buf_size;
		int in_addr;
		int in_bit;
	} rarvm_input_t;

	typedef struct rarvm_data_tag {
		UINT8 *mem;
		unsigned int R[8];
		unsigned int Flags;
	} rarvm_data_t;

	__inline void vm_optimize(struct rarvm_prepared_program *prg);
	unsigned int vm_getbits();
	void vm_addbits( int bits);
	int rarvm_init();
	void vm_free();
	BOOLEAN vm_prepare(unsigned char *code,int code_size, struct rarvm_prepared_program *prg);
	void vm_set_memory(unsigned int pos, UINT8 *data, unsigned int data_size);
	int vm_execute(struct rarvm_prepared_program *prg);
	__inline void vm_set_value(int byte_mode, unsigned int *addr, unsigned int value);
	unsigned int vm_read_data();
	BOOLEAN vm_execute_code(struct rarvm_prepared_command *prepared_code, UINT32 code_size) ;
	unsigned int * rarvm_get_operand(struct rarvm_prepared_operand *cmd_op);
	void execute_standard_filter(rarvm_standard_filters_t filter_type);
	__inline unsigned int filter_itanium_getbits(unsigned char *data, int bit_pos, int bit_count);
	__inline void filter_itanium_setbits(unsigned char *data, unsigned int bit_field, int bit_pos, int bit_count);
	__inline void *rar_realloc2(void *ptr, size_t size);
	void execute_code(struct rarvm_prepared_program *prg);
	int ppm_decode_char();
	BOOLEAN ppm_decode_symbol1();
	void rescale() ;
	__inline void ppmd_swap(struct state_tag *p0, struct state_tag *p1);
	void ppm_decode_bin_symbol();
	__inline unsigned int  coder_get_current_shift_count(range_coder_t *coder, unsigned int shift) ;
	__inline void coder_decode();
	BOOLEAN ppm_decode_symbol2() ;
	BOOLEAN read_vm_code_PPM();
	int read_vm_code();
	//UINT32 crc(UINT32 start_crc, void *addr, UINT32 size);
	void copy_string( unsigned int length, unsigned int distance) ; 
	__inline void insert_old_dist(unsigned int distance) ;
	__inline void insert_last_match(unsigned int length, unsigned int distance) ;
	int read_end_of_block() ;

	//--------------------------------------------------------------------------------

	typedef struct mark_header_tag
	{
		unsigned char mark[SIZEOF_MARKHEAD];
	} mark_header_t;
	struct Decode
	{
		unsigned int MaxNum;
		unsigned int DecodeLen[16];
		unsigned int DecodePos[16];
		unsigned int DecodeNum[2];
	};

	struct LitDecode
	{
		unsigned int MaxNum;
		unsigned int DecodeLen[16];
		unsigned int DecodePos[16];
		unsigned int DecodeNum[NC];
	};
	struct DistDecode
	{
		unsigned int MaxNum;
		unsigned int DecodeLen[16];
		unsigned int DecodePos[16];
		unsigned int DecodeNum[DC];
	};

	struct LowDistDecode
	{
		unsigned int MaxNum;
		unsigned int DecodeLen[16];
		unsigned int DecodePos[16];
		unsigned int DecodeNum[LDC];
	};

	struct RepDecode
	{
		unsigned int MaxNum;
		unsigned int DecodeLen[16];
		unsigned int DecodePos[16];
		unsigned int DecodeNum[RC];
	};

	struct BitDecode
	{
		unsigned int MaxNum;
		unsigned int DecodeLen[16];
		unsigned int DecodePos[16];
		unsigned int DecodeNum[BC];
	};
	struct UnpackFilter
	{
		unsigned int block_start;
		unsigned int block_length;
		unsigned int exec_count;
		int next_window;
		struct rarvm_prepared_program prg;
	};

	struct MultDecode
	{
		unsigned int MaxNum;
		unsigned int DecodeLen[16];
		unsigned int DecodePos[16];
		unsigned int DecodeNum[MC20];
	};

	struct AudioVariables
	{
		int K1,K2,K3,K4,K5;
		int D1,D2,D3,D4;
		int last_delta;
		unsigned int dif[11];
		unsigned int byte_count;
		int last_char;
	};

	struct rar_filter_array_t
	{
		struct UnpackFilter **array;
		size_t num_items;
	} ;
	struct state_tag
	{
		ppm_context *successor;
		UINT8 symbol;
		UINT8 freq;
	};


	struct ppm_context {
		struct ppm_context *suffix;
		union {
			freq_data_tag u;
			state_tag one_state;
		} con_ut;
		UINT16 num_stats;
	} ;

	typedef struct __Unpackdata__
	{
		unsigned char in_buf[MAX_BUF_SIZE];
		UINT8 window[MAXWINSIZE];
		int in_addr;
		int in_bit;
		unsigned int unp_ptr;
		unsigned int wr_ptr;
		int tables_read;
		int read_top;
		int read_border;
		int unp_block_type;
		int prev_low_dist;
		int low_dist_rep_count;
		unsigned char unp_old_table[HUFF_TABLE_SIZE];
		struct LitDecode LD;
		struct DistDecode DD;
		struct LowDistDecode LDD;
		struct RepDecode RD;
		struct BitDecode BD;
		unsigned int old_dist[4];
		unsigned int old_dist_ptr;
		unsigned int last_dist;
		unsigned int last_length;
		ppm_data_t ppm_data;
		int ppm_esc_char;
		rar_filter_array_t Filters;
		rar_filter_array_t PrgStack;
		int *old_filter_lengths;
		int last_filter, old_filter_lengths_size;
		INT64 written_size;
		INT64 true_size;
		INT64 max_size;
		INT64 dest_unp_size;
		rarvm_data_t rarvm_data;
		unsigned int unp_crc;
		UINT32 pack_size;

		/* RAR2 variables */
		int unp_cur_channel, unp_channel_delta, unp_audio_block, unp_channels;
		unsigned char unp_old_table20[MC20 * 4];
		struct MultDecode MD[4];
		struct AudioVariables audv[4];

		/* RAR1 variables */
		unsigned int  flag_buf, avr_plc, avr_plcb, avr_ln1, avr_ln2, avr_ln3;
		int buf60, num_huf, st_mode, lcount, flags_cnt;
		unsigned int nhfb, nlzb, max_dist3;
		unsigned int chset[256], chseta[256], chsetb[256], chsetc[256];
		unsigned int place[256], placea[256], placeb[256], placec[256];
		unsigned int ntopl[256], ntoplb[256], ntoplc[256];
	} Unpackdata;
	Unpackdata *unpack_data;

	typedef enum
	{
		ALL_HEAD=0,
		MARK_HEAD=0x72,
		MAIN_HEAD=0x73,
		FILE_HEAD=0x74,
		COMM_HEAD=0x75,
		AV_HEAD=0x76,
		SUB_HEAD=0x77,
		PROTECT_HEAD=0x78,
		SIGN_HEAD=0x79,
		NEWSUB_HEAD=0x7a,
		ENDARC_HEAD=0x7b
	} header_type;

	enum BLOCK_TYPES
	{
		BLOCK_LZ,
		BLOCK_PPM
	};
	rarvm_input_t rarvm_input;


	static const unsigned int UNIT_SIZE=MAX(sizeof(Unrar::ppm_context), sizeof(Unrar::rar_mem_blk_tag));
#pragma pack(pop)

};


#endif

