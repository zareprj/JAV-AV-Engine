
#include "Unrar.h"
#include "crc.h"

#define SET_VALUE(byte_mode,addr,value) (void)(((byte_mode) ? (*(unsigned char *)(addr)=(value)):(*(UINT32 *)(addr)=((UINT32)(value)))))
#define GET_VALUE(byte_mode,addr) ((byte_mode) ? (*(unsigned char *)(addr)) : UINT32((*(unsigned int *)(addr))))
#define SET_IP(IP)                      \
	if ((IP)>=code_size)                   \
	return TRUE;                       \
	if (--max_ops<=0)                  \
	return FALSE;                      \
	cmd=prepared_code+(IP);

#define int64to32(x) ((unsigned int)(x))

static const UINT8 ExpEscape[16]={ 25,14, 9, 7, 5, 5, 4, 4, 4, 3, 3, 3, 2, 2, 2, 2 };
#define GET_MEAN(SUMM,SHIFT,ROUND) ((SUMM+(1 << (SHIFT-ROUND))) >> (SHIFT))
#define ARI_DEC_NORMALISE(code, low, range)					\
{												\
	while ((low^(low+range)) < TOP || (range < BOT && ((range=-low&(BOT-1)),1))) {		\
	unsigned int Tempchar ;                    \
	get_char(Tempchar) ;						\
	code = (code << 8) | Tempchar;				\
	range <<= 8;									\
	low <<= 8;									\
	}											\
}


#define VMCF_OP0             0
#define VMCF_OP1             1
#define VMCF_OP2             2
#define VMCF_OPMASK          3
#define VMCF_BYTEMODE        4
#define VMCF_JUMP            8
#define VMCF_PROC           16
#define VMCF_USEFLAGS       32
#define VMCF_CHFLAGS        64

static UINT8 vm_cmdflags[]=
{
	/* VM_MOV   */ VMCF_OP2 | VMCF_BYTEMODE                                ,
	/* VM_CMP   */ VMCF_OP2 | VMCF_BYTEMODE | VMCF_CHFLAGS                 ,
	/* VM_ADD   */ VMCF_OP2 | VMCF_BYTEMODE | VMCF_CHFLAGS                 ,
	/* VM_SUB   */ VMCF_OP2 | VMCF_BYTEMODE | VMCF_CHFLAGS                 ,
	/* VM_JZ    */ VMCF_OP1 | VMCF_JUMP | VMCF_USEFLAGS                    ,
	/* VM_JNZ   */ VMCF_OP1 | VMCF_JUMP | VMCF_USEFLAGS                    ,
	/* VM_INC   */ VMCF_OP1 | VMCF_BYTEMODE | VMCF_CHFLAGS                 ,
	/* VM_DEC   */ VMCF_OP1 | VMCF_BYTEMODE | VMCF_CHFLAGS                 ,
	/* VM_JMP   */ VMCF_OP1 | VMCF_JUMP                                    ,
	/* VM_XOR   */ VMCF_OP2 | VMCF_BYTEMODE | VMCF_CHFLAGS                 ,
	/* VM_AND   */ VMCF_OP2 | VMCF_BYTEMODE | VMCF_CHFLAGS                 ,
	/* VM_OR    */ VMCF_OP2 | VMCF_BYTEMODE | VMCF_CHFLAGS                 ,
	/* VM_TEST  */ VMCF_OP2 | VMCF_BYTEMODE | VMCF_CHFLAGS                 ,
	/* VM_JS    */ VMCF_OP1 | VMCF_JUMP | VMCF_USEFLAGS                    ,
	/* VM_JNS   */ VMCF_OP1 | VMCF_JUMP | VMCF_USEFLAGS                    ,
	/* VM_JB    */ VMCF_OP1 | VMCF_JUMP | VMCF_USEFLAGS                    ,
	/* VM_JBE   */ VMCF_OP1 | VMCF_JUMP | VMCF_USEFLAGS                    ,
	/* VM_JA    */ VMCF_OP1 | VMCF_JUMP | VMCF_USEFLAGS                    ,
	/* VM_JAE   */ VMCF_OP1 | VMCF_JUMP | VMCF_USEFLAGS                    ,
	/* VM_PUSH  */ VMCF_OP1                                                ,
	/* VM_POP   */ VMCF_OP1                                                ,
	/* VM_CALL  */ VMCF_OP1 | VMCF_PROC                                    ,
	/* VM_RET   */ VMCF_OP0 | VMCF_PROC                                    ,
	/* VM_NOT   */ VMCF_OP1 | VMCF_BYTEMODE                                ,
	/* VM_SHL   */ VMCF_OP2 | VMCF_BYTEMODE | VMCF_CHFLAGS                 ,
	/* VM_SHR   */ VMCF_OP2 | VMCF_BYTEMODE | VMCF_CHFLAGS                 ,
	/* VM_SAR   */ VMCF_OP2 | VMCF_BYTEMODE | VMCF_CHFLAGS                 ,
	/* VM_NEG   */ VMCF_OP1 | VMCF_BYTEMODE | VMCF_CHFLAGS                 ,
	/* VM_PUSHA */ VMCF_OP0                                                ,
	/* VM_POPA  */ VMCF_OP0                                                ,
	/* VM_PUSHF */ VMCF_OP0 | VMCF_USEFLAGS                                ,
	/* VM_POPF  */ VMCF_OP0 | VMCF_CHFLAGS                                 ,
	/* VM_MOVZX */ VMCF_OP2                                                ,
	/* VM_MOVSX */ VMCF_OP2                                                ,
	/* VM_XCHG  */ VMCF_OP2 | VMCF_BYTEMODE                                ,
	/* VM_MUL   */ VMCF_OP2 | VMCF_BYTEMODE                                ,
	/* VM_DIV   */ VMCF_OP2 | VMCF_BYTEMODE                                ,
	/* VM_ADC   */ VMCF_OP2 | VMCF_BYTEMODE | VMCF_USEFLAGS | VMCF_CHFLAGS ,
	/* VM_SBB   */ VMCF_OP2 | VMCF_BYTEMODE | VMCF_USEFLAGS | VMCF_CHFLAGS ,
	/* VM_PRINT */ VMCF_OP0
};

//----------------------------------
BOOLEAN Unrar::SetHandle( JFile *i_pclsFile )
{
	BOOLEAN Rez = FALSE ;
	UINT64 CurrentOffset ;
	m_pclsUnrarFile = NULL ;
	m_pclsRarFile = i_pclsFile ;
	Rez = ReadMainHeader () ;
	m_pclsRarFile->GetFilePosition(CurrentOffset);

	if( main_hdr == NULL || Rez == FALSE )
	{
		if (main_hdr!=NULL)
		{
			PutLog (RAR_CAN_NOT_READ_MAIN_HEADER) ;
			SMHeapFree(main_hdr) ;
		}
		
		JString Message ;
		Message = i_pclsFile->GetDisplayName();
		Message += JString(MSC(FILE_COMMPERS_FORMAT_ERROR));
		MessageQueue->push(Message);
		return FALSE ;
	}
	if(main_hdr->Flags & MHD_PASSWORD)
	{
		JString Message ;
		Message = i_pclsFile->GetDisplayName();
		Message += JString(MSC(FILE_COMPERSS_PROTECT));
		MessageQueue->push(Message);
		SMHeapFree(main_hdr);
		return FALSE ;
	}
	
	unpack_data =(Unpackdata*) SMHeapAlloc(sizeof(Unpackdata)) ;
	if ( unpack_data==NULL )
	{
		SMHeapFree(main_hdr);
		PutLog (NON_ENOUGH_MEMORY) ;
		return FALSE ;
	}
	unpack_data->rarvm_data.mem = NULL;
	unpack_data->old_filter_lengths = NULL;
	unpack_data->PrgStack.array = unpack_data->Filters.array = NULL;
	unpack_data->PrgStack.num_items = unpack_data->Filters.num_items = 0;
	unpack_data->unp_crc = 0xffffffff;
	unpack_data->max_size = 0;

	ppm_constructor() ;

	file_header = NULL ;

	
	m_pclsRarFile->GetFilePosition(CurrentOffset);
	NextHeaderFile = CurrentOffset ;
	_tcsncpy ( m_strCurrentFileName , m_pclsRarFile->GetDisplayName().c_str(), m_u16FileNameSize) ;
	_tcsncat ( m_strCurrentFileName , TEXT("->") , m_u16FileNameSize) ;
	m_strCurrentFileName[m_u16FileNameSize-1] = NULL ;
	
	NamePointer = m_strCurrentFileName + lstrlen(m_strCurrentFileName);
	SoldCorrupt = FALSE ; // ÒãÇäí ÓÊ ãíÔæÏ ˜å ÝÇíá åÇí ÓæáÏ ÏÇÑí í˜ ÝÇíá ˜ÑÇÊ ÔÏå ÈÇÔÏ
	u32ItemIndex = 0;
	u32SubHeadNumber = 0;
	return TRUE ;
}
//----------------------------------
IUnCompersser * Unrar::IsArchive( JFile * i_pclsFile )
{
	mark_header_t mark;
	size_t Size  = SIZEOF_MARKHEAD;
	BOOLEAN Rez ;
	const mark_header_t rar_hdr[2] = {{{0x52, 0x61, 0x72, 0x21, 0x1a, 0x07, 0x00}}, {{'U', 'n', 'i', 'q', 'u', 'E', '!'}}};
	UINT32 u32SeekValue = 0;
	if ( i_pclsFile->Seek(u32SeekValue , JFile::FBEGIN )== FALSE || u32SeekValue !=0 )
	{
		return NULL ;
	}
	Rez = i_pclsFile->Read(&mark , Size);
	if (Rez == FALSE || Size!=SIZEOF_MARKHEAD)
	{
		return NULL ;
	}
	if(memcmp(&mark, &rar_hdr[0], SIZEOF_MARKHEAD) == 0 || memcmp(&mark, &rar_hdr[1], SIZEOF_MARKHEAD) == 0)
	{
		Unrar *pocRar = new Unrar();
		if (pocRar == NULL)
		{
			return NULL ;
		}
		return pocRar ;
	}

	return NULL ;

}
//----------------------------------
BOOLEAN Unrar::ReadMainHeader()
{
	BOOLEAN Rez ; 
	size_t CountRead ;
	main_hdr = (UnrarMainHeader *) SMHeapAlloc(sizeof(UnrarMainHeader));
	if  (main_hdr == NULL)
	{
		return FALSE ;
	}
	CountRead = sizeof(UnrarMainHeader) ;
	Rez = m_pclsRarFile->Read(main_hdr ,CountRead) ;
	if (Rez == FALSE || CountRead != sizeof(UnrarMainHeader)  || main_hdr->Size < sizeof(UnrarMainHeader)) 
	{
		SMHeapFree(main_hdr) ;
		return FALSE ; 
	}
	return TRUE ;
};

void Unrar::ppm_constructor()
{
	unpack_data->ppm_data.sub_alloc.sub_allocator_size = 0 ;
	unpack_data->ppm_data.min_context = NULL ;
	unpack_data->ppm_data.max_context = NULL ;
}

BOOLEAN Unrar::ReadCommentHeader()
{
	BOOLEAN Rez ; 
	size_t CountRead ;
	comment_hdr = (UrarCommentHeader *) SMHeapAlloc(sizeof(UrarCommentHeader));
	if  (comment_hdr == NULL)
	{
		return FALSE ;
	}
	CountRead = SIZEOF_COMMHEAD ;
	Rez = m_pclsRarFile->Read(comment_hdr ,CountRead) ;
	if (Rez == FALSE || CountRead != SIZEOF_COMMHEAD  || comment_hdr->Size < SIZEOF_COMMHEAD) 
	{
		SMHeapFree(comment_hdr) ;
		return FALSE ; 
	}
	return TRUE ;
}

BOOLEAN Unrar::CopyDataFromFile(UINT32 Size)
{
	unsigned char data[CopyBlock];
	BOOLEAN Rez ;
	size_t stTempCount, StCount, Strem;
	
	Strem = Size;
	while(Strem > 0)
	{
		stTempCount = MIN(CopyBlock, Strem);
		StCount = stTempCount ;
		Rez = m_pclsRarFile->Read(data , StCount) ;
		if (StCount != stTempCount || Rez == FALSE )
		{
			return FALSE ;
		}
		Rez = m_pclsUnrarFile->Write(data , StCount) ;
		if (StCount != stTempCount||Rez == FALSE )
		{
			return FALSE ;
		}
		Strem -= StCount ;
	}
	return TRUE ;
}

BOOLEAN Unrar::Unpack (int Version ,BOOLEAN solid ) 
{

	BOOLEAN Rez = FALSE ;
	switch (Version)
	{
	case 15:
		Rez = Upack15(solid);
	break;
	case 20:
	case 26 :
		Rez = Upack20(solid);
		break ;
	case 29 :
		Rez = Upack29(solid) ;

		break;
	default :
		Rez = Upack29(solid) ;
		if (Rez == FALSE)
		{
			vm_free();
			Rez = Upack20(solid);
			if (Rez == FALSE)
			{
				Rez = Upack15(solid) ;
			}
		}
		break ;

	}
	return Rez ;
}
void Unrar::vm_free()
{
	if (unpack_data->rarvm_data.mem)
	{
		SMHeapFree (unpack_data->rarvm_data.mem) ; 
		unpack_data->rarvm_data.mem = NULL ;
	}
}


BOOLEAN Unrar::Upack15 (BOOLEAN solid ) 
{
	UnpackInitData(solid);
	InitDataUpack15(solid);
	if (UpackReadBuffer() == FALSE)
	{
		return FALSE ;
	}
	if (!solid)
	{
		HuffInit();
		unpack_data->unp_ptr = 0;
	}else 
	{
		unpack_data->unp_ptr = unpack_data->wr_ptr;
	}
	--unpack_data->dest_unp_size;

	if (unpack_data->dest_unp_size >= 0) {
		get_flag_buf();
		unpack_data->flags_cnt = 8;
	}
	while (unpack_data->dest_unp_size >= 0)
	{
		unpack_data->unp_ptr &= MAXWINMASK;
		
		if (unpack_data->in_addr > unpack_data->read_top-READBUFBOUND && 
			!UpackReadBuffer())
		{
			break ;
		}
		if (((unpack_data->wr_ptr - unpack_data->unp_ptr) & MAXWINMASK) < 270 &&
			(unpack_data->wr_ptr != unpack_data->unp_ptr)) {
				unp_write_buf_old();
		}
		if (unpack_data->st_mode)
		{
			huff_decode();
			continue;
		}
		if (--unpack_data->flags_cnt < 0) {
			get_flag_buf();
			unpack_data->flags_cnt = 7;
		}
		if (unpack_data->flag_buf & 0x80) {
			unpack_data->flag_buf <<= 1;
			if (unpack_data->nlzb > unpack_data->nhfb) {
				long_lz();
			} else {
				huff_decode();
			}
		} else {
			unpack_data->flag_buf <<= 1;
			if (--unpack_data->flags_cnt < 0) {
				get_flag_buf();
				unpack_data->flags_cnt = 7;
			}
			if (unpack_data->flag_buf & 0x80) {
				unpack_data->flag_buf <<= 1;
				if (unpack_data->nlzb > unpack_data->nhfb) {
					huff_decode();
				} else {
					long_lz();
				}
			} else {
				unpack_data->flag_buf <<= 1;
				short_lz();
			}
		}
	}
	unp_write_buf_old();
	return TRUE;

	
	return TRUE ;
}

BOOLEAN Unrar::UnpackInitData(BOOLEAN solid) 
{
	if (!solid)
	{
		unpack_data->tables_read = FALSE ;
		memset(unpack_data->old_dist , 0 , sizeof(unpack_data->old_dist));
		unpack_data->old_dist_ptr = 0 ;
		memset(unpack_data->unp_old_table, 0, sizeof(unpack_data->unp_old_table));
		memset(&unpack_data->LD, 0, sizeof(unpack_data->LD));
		memset(&unpack_data->DD, 0, sizeof(unpack_data->DD));
		memset(&unpack_data->LDD, 0, sizeof(unpack_data->LDD));
		memset(&unpack_data->RD, 0, sizeof(unpack_data->RD));
		memset(&unpack_data->BD, 0, sizeof(unpack_data->BD));
		unpack_data->last_dist= 0;
		unpack_data->last_length=0;
		unpack_data->ppm_esc_char = 2;
		unpack_data->unp_ptr = 0;
		unpack_data->wr_ptr = 0;
		unpack_data->unp_block_type = BLOCK_LZ;
		InitFilter () ;
	}
	unpack_data->in_bit = 0;
	unpack_data->in_addr = 0;
	unpack_data->read_top = 0;
	unpack_data->read_border = 0;
	unpack_data->written_size = 0;
	unpack_data->true_size = 0;
	unpack_data->unp_crc = 0xffffffff;
	rarvm_init();
	InitUpack20(solid);
	return TRUE ;
}

VOID Unrar::InitFilter() 
{
	if (unpack_data->old_filter_lengths) {
		SMHeapFree(unpack_data->old_filter_lengths);
		unpack_data->old_filter_lengths = NULL;
	}
	unpack_data->old_filter_lengths_size = 0;
	unpack_data->last_filter = 0;
	FilterArrayReset();

}

__inline void Unrar::FilterArrayReset() 
{
	UINT32 i;
	for (i = 0 ; i < unpack_data->Filters.num_items ; i++)
	{
		FilterDelete(i);
		PragStackDelete(i);
	}
	if(unpack_data->Filters.array)
	{
		SMHeapFree(unpack_data->Filters.array);
	}
	if(unpack_data->PrgStack.array)
	{
		SMHeapFree(unpack_data->PrgStack.array);
	}
	unpack_data->Filters.array = NULL ;
	unpack_data->Filters.num_items = 0 ;
	unpack_data->PrgStack.array = NULL ;
	unpack_data->PrgStack.num_items = 0 ;
}
//---------------------------------------------------------------
void Unrar::FilterDelete(int i) 
{
	void * Temp = unpack_data->Filters.array[i]->prg.global_data ;
	
	if (Temp) {
		SMHeapFree(Temp);
	}
	Temp = unpack_data->Filters.array[i]->prg.static_data ;
	if (Temp) {
		SMHeapFree(Temp);
	}
	Temp = unpack_data->Filters.array[i]->prg.cmd.array ;
	if (Temp) {
		SMHeapFree(Temp);
		Temp = NULL ;
		unpack_data->Filters.array[i]->prg.cmd.num_items = 0 ;
	} 

	SMHeapFree(unpack_data->Filters.array[i]);
}
//---------------------------------------------------------------
void Unrar::PragStackDelete(int i) 
{

	if (!unpack_data->PrgStack.array[i])
	{
		return ;
	}

	void * Temp = unpack_data->PrgStack.array[i]->prg.global_data ;

	if (Temp) {
		SMHeapFree(Temp);
	}
	Temp = unpack_data->PrgStack.array[i]->prg.static_data ;
	if (Temp) {
		SMHeapFree(Temp);
	}
	Temp = unpack_data->PrgStack.array[i]->prg.cmd.array ;
	if (Temp) {
		SMHeapFree(Temp);
		Temp = NULL ;
		unpack_data->PrgStack.array[i]->prg.cmd.num_items = 0 ;
	} 

	SMHeapFree(unpack_data->PrgStack.array[i]);
}
//---------------------------------------------------------------
int Unrar::rarvm_init()
{
	unpack_data->rarvm_data.mem = (UINT8 *) UrarMalloc(RARVM_MEMSIZE+4);

	if (!unpack_data->rarvm_data.mem)
	{
		return FALSE ;
	}
	return TRUE ;
}
//---------------------------------------------------------------
void * Unrar::UrarMalloc(size_t size)
{
	void *alloc;
	if(!size || size > RAR_MAX_ALLOCATION)
	{
		PutLog(RAR_ALLOC_TOO_BUFFER);
		return NULL ;
	}
	alloc = SMHeapAlloc(size);
	if(!alloc) {
		PutLog(NON_ENOUGH_MEMORY);
		return NULL ;
	}else 
	{
		return alloc ;
	}
}
//---------------------------------------------------------------
void * Unrar::UrarRealloc2(void *ptr, size_t size)
{
	return NULL ;
}
//---------------------------------------------------------------
void Unrar::InitUpack20 (BOOLEAN solid)
{
	if (!solid) {
		unpack_data->unp_channel_delta = 0;
		unpack_data->unp_cur_channel = 0;
		unpack_data->unp_audio_block = 0;
		unpack_data->unp_channels = 1;
		memset(unpack_data->audv, 0, sizeof(unpack_data->audv));
		memset(unpack_data->unp_old_table20, 0, sizeof(unpack_data->unp_old_table20));
		memset(unpack_data->MD, 0, sizeof(unpack_data->MD));
	}
}
//---------------------------------------------------------------
BOOLEAN Unrar::InitDataUpack15 (BOOLEAN solid)
{
	if ( solid == FALSE )
	{
		unpack_data->avr_plcb = unpack_data->avr_ln1 = unpack_data->avr_ln2 =
		unpack_data->avr_ln3 = unpack_data->num_huf =
		unpack_data->buf60 = 0;
		unpack_data->avr_plc = 0x3500;
		unpack_data->max_dist3 = 0x2001;
		unpack_data->nhfb = unpack_data->nlzb = 0x80;
	}

	unpack_data->flags_cnt = 0;
	unpack_data->flag_buf = 0;
	unpack_data->st_mode = 0;
	unpack_data->lcount = 0;
	unpack_data->read_top = 0;
	return TRUE ;
}
//---------------------------------------------------------------
BOOLEAN Unrar::UpackReadBuffer ()
{
	UINT32 u32DataSize;
	size_t stRetval ;
	UINT32 u32ReadSize;
	BOOLEAN bRez ;
	
	u32DataSize = unpack_data->read_top - unpack_data->in_addr;

	if (u32DataSize < 0) {
		return FALSE;
	}

	if (unpack_data->in_addr > MAX_BUF_SIZE / 2) {
		if (u32DataSize > 0) {
			memmove(unpack_data->in_buf, unpack_data->in_buf+unpack_data->in_addr,
				u32DataSize);
		}
		unpack_data->in_addr = 0;
		unpack_data->read_top = u32DataSize;
	} else {
		u32DataSize = unpack_data->read_top;
	}

	if (unpack_data->pack_size < ((MAX_BUF_SIZE-u32DataSize)&~0xf))
	{
		u32ReadSize = unpack_data->pack_size;
	} else
	{
		u32ReadSize = (MAX_BUF_SIZE-u32DataSize)&~0xf;
	}

	stRetval = u32ReadSize ;

	bRez = m_pclsRarFile->Read( unpack_data->in_buf + u32DataSize , stRetval ) ; 
	if ( bRez == FALSE )
	{
		return FALSE ;
	}
	if ( stRetval > 0 )
	{
		unpack_data->read_top += stRetval;
		unpack_data->pack_size -= stRetval;
	}

	unpack_data->read_border = unpack_data->read_top - READBUFBOUND ;
	
	if(unpack_data->read_border < unpack_data->in_addr) {
		int fill = ((unpack_data->read_top + READBUFBOUND) < MAX_BUF_SIZE) ? READBUFBOUND : (MAX_BUF_SIZE - unpack_data->read_top);
		if(fill)
			memset(unpack_data->in_buf + unpack_data->read_top, 0, fill);
	}
	return  bRez ;
}
//---------------------------------------------------------------
void Unrar::HuffInit ()
{
	UINT32 u32Index; 
	for (u32Index=0 ; u32Index<256 ; u32Index++)
	{
		unpack_data->place[u32Index] = unpack_data->placea[u32Index] = unpack_data->placeb[u32Index] = u32Index;
		unpack_data->placec[u32Index] = (~u32Index+1) & 0xff;
		unpack_data->chset[u32Index] = unpack_data->chsetb[u32Index] = u32Index << 8;
		unpack_data->chseta[u32Index] = u32Index;
		unpack_data->chsetc[u32Index] = ((~u32Index+1) & 0xff) << 8;
	}
	memset(unpack_data->ntopl, 0, sizeof(unpack_data->ntopl));
	memset(unpack_data->ntoplb, 0, sizeof(unpack_data->ntoplb));
	memset(unpack_data->ntoplc, 0, sizeof(unpack_data->ntoplc));
	corr_huff(unpack_data->chsetb, unpack_data->ntoplb);
}
//---------------------------------------------------------------
void Unrar::corr_huff(unsigned int *char_set, unsigned int *num_to_place) 
{
	UINT32 u32Index1, u32Index2;

	for (u32Index1=7 ; u32Index1 >= 0 ; u32Index1--) {
		for (u32Index2=0 ; u32Index2 < 32 ; u32Index2++, char_set++) {
			*char_set = (*char_set & ~0xff) | u32Index1;
		}
	}
	memset(num_to_place, 0, sizeof(unpack_data->ntopl));
	for (u32Index1=6 ; u32Index1 >= 0 ; u32Index1--) {
		num_to_place[u32Index1] = (7-u32Index1) * 32;
	}

}
//---------------------------------------------------------------
void Unrar::get_flag_buf ()
{
	unsigned int flags, new_flags_place, flags_place;
	flags_place = decode_num( getbits(), STARTHF2,dec_hf2, pos_hf2);
	for (;;) {
		flags = unpack_data->chsetc[flags_place & 0xff];
		unpack_data->flag_buf = flags >> 8;
		new_flags_place = unpack_data->ntoplc[flags++ & 0xff]++;
		if ((flags & 0xff) != 0) {
			break;
		}
		corr_huff(unpack_data->chsetc, unpack_data->ntoplc);
	}
	unpack_data->chsetc[flags_place & 0xff] = unpack_data->chsetc[new_flags_place & 0xff];
	unpack_data->chsetc[new_flags_place & 0xff] = flags;
}
//---------------------------------------------------------------
unsigned int Unrar::getbits() 
{
	unsigned int bit_field;

	bit_field = (unsigned int) unpack_data->in_buf[unpack_data->in_addr] << 16;
	bit_field |= (unsigned int) unpack_data->in_buf[unpack_data->in_addr+1] << 8;
	bit_field |= (unsigned int) unpack_data->in_buf[unpack_data->in_addr+2];
	bit_field >>= (8-unpack_data->in_bit);

	return(bit_field & 0xffff);
}
//---------------------------------------------------------------
unsigned int Unrar::decode_num( UINT32 i_u32Num, UINT32 i_u32Start_pos,UINT32 * i_pu32Dec_tab,UINT32 * i_pu32Pos_tab )
{
	UINT i;

	for (i_u32Num&=0xfff0, i=0 ; i_pu32Dec_tab[i] <= i_u32Num ; i++) {
		i_u32Start_pos++;
	}
	addbits(i_u32Start_pos);
	return (((i_u32Num-(i ? i_pu32Dec_tab[i-1]:0)) >> (16-i_u32Start_pos)) + i_pu32Pos_tab[i_u32Start_pos]);
}
//---------------------------------------------------------------
void Unrar::addbits(int bits) 
{
	bits += unpack_data->in_bit;
	unpack_data->in_addr += bits >> 3;
	unpack_data->in_bit = bits & 7;
}
//---------------------------------------------------------------
void Unrar::unp_write_buf_old() 
{
	if (unpack_data->unp_ptr < unpack_data->wr_ptr)
	{
		unp_write_data(&unpack_data->window[unpack_data->wr_ptr],
			-(int)unpack_data->wr_ptr & MAXWINMASK);
		unp_write_data(unpack_data->window, unpack_data->unp_ptr);
	}
	else
	{
		unp_write_data( &unpack_data->window[unpack_data->wr_ptr],
			unpack_data->unp_ptr - unpack_data->wr_ptr);
	}
	unpack_data->wr_ptr = unpack_data->unp_ptr;
}
//---------------------------------------------------------------
void Unrar::unp_write_data(UINT8 *data, int size) 
{
	size_t WriteSize ;
	BOOLEAN Rez ; 
	WriteSize = size ;
	unpack_data->true_size += size;
	unpack_data->unp_crc = crc::crc32Rar(unpack_data->unp_crc, data, size);
	if(unpack_data->max_size) {
		if(unpack_data->written_size >= unpack_data->max_size)
			return;

		if(unpack_data->written_size + size > unpack_data->max_size)
			WriteSize = unpack_data->max_size - unpack_data->written_size;
	}
	Rez = m_pclsUnrarFile->Write(data, WriteSize) ;
	if(Rez == TRUE  && WriteSize > 0 )
		unpack_data->written_size += WriteSize;
}

//---------------------------------------------------------------
void Unrar::huff_decode() 
{
	unsigned int cur_byte, new_byte_place, length, distance, bit_field;
	int byte_place;

	bit_field = getbits();

	if (unpack_data->avr_plc > 0x75ff) {
		byte_place = decode_num(bit_field,
			STARTHF4, dec_hf4, pos_hf4);
	} else if (unpack_data->avr_plc > 0x5dff) {
		byte_place = decode_num(bit_field,
			STARTHF3, dec_hf3, pos_hf3);
	} else if (unpack_data->avr_plc > 0x35ff) {
		byte_place = decode_num( bit_field,
			STARTHF2, dec_hf2, pos_hf2);
	} else if (unpack_data->avr_plc > 0x0dff) {
		byte_place = decode_num(bit_field,
			STARTHF1, dec_hf1, pos_hf1);
	} else {
		byte_place = decode_num( bit_field,
			STARTHF0, dec_hf0, pos_hf0);
	} 
	byte_place &= 0xff;
	if (unpack_data->st_mode) {
		if (byte_place == 0 && bit_field > 0xfff) {
			byte_place = 0x100;
		}
		if (--byte_place == -1) {
			bit_field = getbits();
			addbits(1);
			if (bit_field & 0x8000) {
				unpack_data->num_huf = unpack_data->st_mode = 0;
				return;
			} else {
				length = (bit_field & 0x4000) ? 4 : 3;
				addbits(1);
				distance = decode_num(getbits(),
					STARTHF2, dec_hf2, pos_hf2);
				distance = (distance << 5) | (getbits() >> 11);
				addbits(5);
				copy_string15(distance, length);
				return;
			}
		}
	} else if (unpack_data->num_huf++ >= 16 && unpack_data->flags_cnt == 0) {
		unpack_data->st_mode = 1;
	}
	unpack_data->avr_plc += byte_place;
	unpack_data->avr_plc -= unpack_data->avr_plc >> 8;
	unpack_data->nhfb += 16;
	if (unpack_data->nhfb > 0xff) {
		unpack_data->nhfb = 0x90;
		unpack_data->nlzb >>= 1;
	}

	unpack_data->window[unpack_data->unp_ptr++] = 
		(unsigned char) (unpack_data->chset[byte_place & 0xff] >>8);
	--unpack_data->dest_unp_size;

	while (1) {
		cur_byte = unpack_data->chset[byte_place & 0xff];
		new_byte_place = unpack_data->ntopl[cur_byte++ & 0xff]++;
		if ((cur_byte & 0xff) > 0xa1) {
			corr_huff(unpack_data->chset, unpack_data->ntopl);
		} else {
			break;
		}
	}

	unpack_data->chset[byte_place & 0xff] = unpack_data->chset[new_byte_place & 0xff];
	unpack_data->chset[new_byte_place & 0xff] = cur_byte;
}
//---------------------------------------------------------------
void Unrar::copy_string15(unsigned int distance, unsigned int length) 
{
	unpack_data->dest_unp_size -= length;
	while (length--)
	{
		unpack_data->window[unpack_data->unp_ptr] =
			unpack_data->window[(unpack_data->unp_ptr - distance) & MAXWINMASK];
		unpack_data->unp_ptr = (unpack_data->unp_ptr + 1) & MAXWINMASK;
	}
}
//---------------------------------------------------------------
void Unrar::long_lz()
{
	unsigned int length, distance, distance_place, new_distance_place;
	unsigned int old_avr2, old_avr3, bit_field;

	unpack_data->num_huf = 0;
	unpack_data->nlzb += 16;

	if (unpack_data->nlzb > 0xff) {
		unpack_data->nlzb = 0x90;
		unpack_data->nhfb >>= 1;
	}
	old_avr2 = unpack_data->avr_ln2;

	bit_field = getbits();
	if (unpack_data->avr_ln2 >= 122) {
		length = decode_num( bit_field, STARTL2, dec_l2, pos_l2);
	} else if (unpack_data->avr_ln2 >= 64) {
		length = decode_num( bit_field, STARTL1, dec_l1, pos_l1);
	} else if (bit_field < 0x100) {
		length = bit_field;
		addbits(16);
	} else {
		for (length=0 ; ((bit_field << length) & 0x8000)==0 ; length++) {
			/* Empty loop */
		}
		addbits(length+1);
	}

	unpack_data->avr_ln2 += length;
	unpack_data->avr_ln2 -= unpack_data->avr_ln2 >> 5;

	bit_field = getbits();
	if (unpack_data->avr_plcb > 0x28ff) {
		distance_place = decode_num(bit_field, STARTHF2,
			dec_hf2, pos_hf2);
	} else if (unpack_data->avr_plcb > 0x6ff) {
		distance_place = decode_num( bit_field, STARTHF1,
			dec_hf1, pos_hf1);
	} else {
		distance_place = decode_num(bit_field, STARTHF0,
			dec_hf0, pos_hf0);
	}

	unpack_data->avr_plcb += distance_place;
	unpack_data->avr_plcb -= unpack_data->avr_plcb >> 8;
	for (;;) {
		distance = unpack_data->chsetb[distance_place & 0xff];
		new_distance_place = unpack_data->ntoplb[distance++ & 0xff]++;
		if (!(distance & 0xff)) {
			corr_huff(unpack_data->chsetb, unpack_data->ntoplb);
		} else {
			break;
		}
	}

	unpack_data->chsetb[distance_place & 0xff] = unpack_data->chsetb[new_distance_place & 0xff];
	unpack_data->chsetb[new_distance_place & 0xff] = distance;

	distance = ((distance & 0xff00) | (getbits() >> 8)) >> 1;
	addbits(7);

	old_avr3 = unpack_data->avr_ln3;
	if (length != 1 && length != 4) {
		if (length==0 && distance <= unpack_data->max_dist3) {
			unpack_data->avr_ln3++;
			unpack_data->avr_ln3 -= unpack_data->avr_ln3 >> 8;
		} else if (unpack_data->avr_ln3 > 0) {
			unpack_data->avr_ln3--;
		}
	}

	length += 3;

	if (distance >= unpack_data->max_dist3) {
		length++;
	}
	if (distance <= 256) {
		length += 8;
	}
	if (old_avr3 > 0xb0 || (unpack_data->avr_plc >= 0x2a00 && old_avr2 < 0x40)) {
		unpack_data->max_dist3 = 0x7f00;
	} else {
		unpack_data->max_dist3 = 0x2001;
	}
	unpack_data->old_dist[unpack_data->old_dist_ptr++] = distance;
	unpack_data->old_dist_ptr = unpack_data->old_dist_ptr & 3;
	unpack_data->last_length = length;
	unpack_data->last_dist = distance;
	copy_string15(distance, length);
}
//---------------------------------------------------------------
void  Unrar::short_lz()
{
	static unsigned int short_len1[]={1,3,4,4,5,6,7,8,8,4,4,5,6,6,4,0};
	static unsigned int short_xor1[]={0,0xa0,0xd0,0xe0,0xf0,0xf8,0xfc,0xfe,
		0xff,0xc0,0x80,0x90,0x98,0x9c,0xb0};
	static unsigned int short_len2[]={2,3,3,3,4,4,5,6,6,4,4,5,6,6,4,0};
	static unsigned int short_xor2[]={0,0x40,0x60,0xa0,0xd0,0xe0,0xf0,0xf8,
		0xfc,0xc0,0x80,0x90,0x98,0x9c,0xb0};

	unsigned int length, save_length, last_distance, distance, bit_field;
	int distance_place;

	unpack_data->num_huf = 0;
	bit_field = getbits();
	if (unpack_data->lcount == 2)
	{
		addbits(1);
		if (bit_field >= 0x8000) {
			copy_string15((unsigned int)unpack_data->last_dist,
				unpack_data->last_length);
			return;
		}
		bit_field <<= 1;
		unpack_data->lcount = 0;
	}

	bit_field >>= 8;
	short_len1[1] = short_len2[3] = unpack_data->buf60+3;
	if (unpack_data->avr_ln1 < 37) {
		for (length=0 ;; length++) {
			if (((bit_field^short_xor1[length]) &
				(~(0xff>>short_len1[length]))) == 0) {
					break;
			}
		}
		addbits(short_len1[length]);
	} else {
		for (length=0; ;length++) {
			if (((bit_field^short_xor2[length]) &
				(~(0xff>>short_len2[length]))) == 0) {
					break;
			}
		}
		addbits(short_len2[length]);
	}

	if (length >= 9) {
		if (length == 9) {
			unpack_data->lcount++;
			copy_string15((unsigned int) unpack_data->last_dist,
				unpack_data->last_length);
			return;
		}
		if (length == 14) {
			unpack_data->lcount = 0;
			length = decode_num(getbits(),
				STARTL2, dec_l2, pos_l2) + 5;
			distance = (getbits() >> 1) | 0x8000;
			addbits(15);
			unpack_data->last_length = length;
			unpack_data->last_dist = distance;
			copy_string15(distance, length);
			return;
		}

		unpack_data->lcount = 0;
		save_length = length;
		distance = unpack_data->old_dist[(unpack_data->old_dist_ptr-(length-9)) & 3];
		length = decode_num(			getbits(), STARTL1, dec_l1, pos_l1) + 2;
		if (length == 0x101 && save_length == 10) {
			unpack_data->buf60 ^= 1;
			return;
		}
		if (distance > 256) {
			length++;
		}
		if (distance >= unpack_data->max_dist3) {
			length++;
		}

		unpack_data->old_dist[unpack_data->old_dist_ptr++] = distance;
		unpack_data->old_dist_ptr = unpack_data->old_dist_ptr & 3;
		unpack_data->last_length = length;
		unpack_data->last_dist = distance;
		copy_string15(distance, length);
		return;
	}

	unpack_data->lcount = 0;
	unpack_data->avr_ln1 += length;
	unpack_data->avr_ln1 -= unpack_data->avr_ln1 >> 4;

	distance_place = decode_num(getbits(),
		STARTHF2, dec_hf2, pos_hf2) & 0xff;
	distance = unpack_data->chseta[distance_place & 0xff];
	if (--distance_place != -1) {
		unpack_data->placea[distance & 0xff]--;
		last_distance = unpack_data->chseta[distance_place & 0xff];
		unpack_data->placea[last_distance & 0xff]++;
		unpack_data->chseta[(distance_place+1) & 0xff] = last_distance;
		unpack_data->chseta[distance_place & 0xff] = distance;
	}
	length += 2;
	unpack_data->old_dist[unpack_data->old_dist_ptr++] = ++distance;
	unpack_data->old_dist_ptr = unpack_data->old_dist_ptr & 3;
	unpack_data->last_length = length;
	unpack_data->last_dist = distance;
	copy_string15(distance, length);

}
//---------------------------------------------------------------
BOOLEAN Unrar::Upack20 (BOOLEAN solid ) 
{
	unsigned char ldecode[]={0,1,2,3,4,5,6,7,8,10,12,14,16,20,24,28,
		32,40,48,56,64,80,96,112,128,160,192,224};
	unsigned char lbits[]={0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5};
	int ddecode[]={0,1,2,3,4,6,8,12,16,24,32,48,64,96,128,192,256,384,512,
		768,1024,1536,2048,3072,4096,6144,8192,12288,16384,24576,
		32768U,49152U,65536,98304,131072,196608,262144,327680,393216,
		458752,524288,589824,655360,720896,786432,851968,917504,983040};
	unsigned char dbits[]={0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,
		12,12,13,13,14,14,15,15,16,16,16,16,16,16,16,16,16,16,16,16,16,16};
	unsigned char sddecode[]={0,4,8,16,32,64,128,192};
	unsigned char sdbits[]={2,2,3,4,5,6,6,6};
	unsigned int bits, distance;
	int retval=TRUE, audio_number, number, length, dist_number, length_number;
	UnpackInitData(solid);
	if (UpackReadBuffer() == FALSE)
	{
		return FALSE ;
	}

	if (!solid) {
		if (!read_tables20()) {
			return FALSE;
		}
	}
	--unpack_data->dest_unp_size;
	while (unpack_data->dest_unp_size >= 0) 
	{
		unpack_data->unp_ptr &= MAXWINMASK;
		if (unpack_data->in_addr > unpack_data->read_top-READBUFBOUND && 
			!UpackReadBuffer())
		{
			break ;
		}
		if (((unpack_data->wr_ptr - unpack_data->unp_ptr) & MAXWINMASK) < 270 &&
			(unpack_data->wr_ptr != unpack_data->unp_ptr)) {
				unp_write_buf_old();
		}
		if (unpack_data->unp_audio_block) 
		{
			audio_number = decode_number((struct Decode *)&unpack_data->MD[unpack_data->unp_cur_channel]);
			if (audio_number == 256)
			{
				if (!read_tables20()) 
				{
					retval = FALSE;
					break;
				}
				continue;
			}
			unpack_data->window[unpack_data->unp_ptr++] = decode_audio(audio_number);
			if (++unpack_data->unp_cur_channel == unpack_data->unp_channels) 
			{
				unpack_data->unp_cur_channel = 0;
			}
			--unpack_data->dest_unp_size;
			continue;
		}
		number = decode_number((struct Decode *)&unpack_data->LD);
		if (number < 256)
		{
			unpack_data->window[unpack_data->unp_ptr++] = (unsigned char) number;
			--unpack_data->dest_unp_size;
			continue;
		}
		if (number > 269)
		{
			length = ldecode[number-=270]+3;
			if ((bits = lbits[number]) > 0) 
			{
				length += getbits() >> (16-bits);
				addbits(bits);
			}

			dist_number = decode_number( (struct Decode *)&unpack_data->DD);
			distance = ddecode[dist_number] + 1;
			if ((bits = dbits[dist_number]) > 0) 
			{
				distance += getbits()>>(16-bits);
				addbits(bits);
			}

			if (distance >= 0x2000) 
			{
				length++;
				if (distance >= 0x40000L) 
				{
					length++;
				}
			}

			copy_string20(length, distance);
			continue;
		}
		if (number == 269)
		{
			if (!read_tables20())
			{
				retval = FALSE;
				break;
			}
			continue;
		}
		if (number == 256)
		{
			copy_string20(unpack_data->last_length, unpack_data->last_dist);
			continue;
		}
		if (number < 261)
		{
			distance = unpack_data->old_dist[(unpack_data->old_dist_ptr-(number-256)) & 3];
			length_number = decode_number((struct Decode *)&unpack_data->RD);
			length = ldecode[length_number]+2;
			if ((bits = lbits[length_number]) > 0) 
			{
				length += getbits() >> (16-bits);
				addbits( bits);
			}
			if (distance >= 0x101)
			{
				length++;
				if (distance >= 0x2000)
				{
					length++;
					if (distance >= 0x40000) 
					{
						length++;
					}
				}
			}
			copy_string20(length, distance);
			continue;
		}
		if (number < 270)
		{
			distance = sddecode[number-=261]+1;
			if ((bits=sdbits[number]) > 0)
			{
				distance += getbits() >> (16-bits);
				addbits(bits);
			}
			copy_string20(2, distance);
			continue;
		}
	}
	if (retval) {
		read_last_tables();
		unp_write_buf_old();
	}
	return retval;


}
//---------------------------------------------------------------
BOOLEAN Unrar::read_tables20()
{
	unsigned char bit_length[BC20];
	unsigned char table[MC20 * 4];
	int table_size, n, i, number;
	unsigned int bit_field;

	if (unpack_data->in_addr > unpack_data->read_top-25) {
		if (!UpackReadBuffer()) {
			return FALSE;
		}
	}
	bit_field = getbits();
	unpack_data->unp_audio_block = (bit_field & 0x8000);

	if (!(bit_field & 0x4000)) {
		memset(unpack_data->unp_old_table20, 0, sizeof(unpack_data->unp_old_table20));
	}
	addbits(2);

	if (unpack_data->unp_audio_block) {
		unpack_data->unp_channels = ((bit_field>>12) & 3) + 1;
		if (unpack_data->unp_cur_channel >= unpack_data->unp_channels) {
			unpack_data->unp_cur_channel = 0;
		}
		addbits(2);
		table_size = MC20 * unpack_data->unp_channels;
	} else {
		table_size = NC20+DC20+RC20;
	}

	for (i=0 ; i < BC20 ; i++) {
		bit_length[i] = (unsigned char) (getbits()>> 12);
		addbits(4);
	}
	make_decode_tables(bit_length, (Unrar::Decode *)&unpack_data->BD, BC20);
	i=0;
	for (i=0;i<table_size;) 
	{
		if (unpack_data->in_addr > unpack_data->read_top-5) 
		{
			if (!UpackReadBuffer()) 
			{
				return FALSE;
			}
		}
		number = decode_number((struct Decode *)&unpack_data->BD);
		if (number < 16) 
		{
			table[i] = (number+unpack_data->unp_old_table[i]) & 0xf;
			i++;
		} else if (number == 16)
			{
				n = (getbits() >> 14) + 3;
					addbits(2);	
			while ((n-- > 0 )&& (i < table_size)) 
			{
				table[i] = table[i-1];
				i++;
			}
		} else
		{
			if (number == 17) 
			{
				n = (getbits() >> 13) + 3;
					addbits(3);
			} else
			{
				n = (getbits() >> 9) + 11;
					addbits( 7);
			}
			while (n-- > 0 && i < table_size) 
			{
				table[i++] = 0;
			}
		}
	}
	if (unpack_data->in_addr > unpack_data->read_top) 
	{
		return TRUE;
	}
	if (unpack_data->unp_audio_block)
	{
		for (i=0 ; i < unpack_data->unp_channels ; i++) 
		{
			make_decode_tables(&table[i*MC20], (struct Decode *)&unpack_data->MD[i], MC20);
		}
	}else
	{
		make_decode_tables(&table[0], (struct Decode *)&unpack_data->LD, NC20);
		make_decode_tables(&table[NC20], (struct Decode *)&unpack_data->DD, DC20);
		make_decode_tables(&table[NC20+DC20], (struct Decode *)&unpack_data->RD, RC20);
	}

	memcpy(unpack_data->unp_old_table20, table, sizeof(unpack_data->unp_old_table20));

	return TRUE;

}
//---------------------------------------------------------------
void Unrar::make_decode_tables(unsigned char *len_tab, Unrar::Decode *decode, int size)
{
	int len_count[16], tmp_pos[16], i;
	long m,n;

	memset(len_count, 0, sizeof(len_count));
	memset(decode->DecodeNum,0,size*sizeof(*decode->DecodeNum));
	for (i=0 ; i < size ; i++) {
		len_count[len_tab[i] & 0x0f]++;
	}
	len_count[0]=0;
	for (tmp_pos[0]=decode->DecodePos[0]=decode->DecodeLen[0]=0,n=0,i=1;i<16;i++) {
		n=2*(n+len_count[i]);
		m=n<<(15-i);
		if (m>0xFFFF) {
			m=0xFFFF;
		}
		decode->DecodeLen[i]=(unsigned int)m;
		tmp_pos[i]=decode->DecodePos[i]=decode->DecodePos[i-1]+len_count[i-1];
	}

	for (i=0;i<size;i++) {
		if (len_tab[i]!=0) {
			decode->DecodeNum[tmp_pos[len_tab[i] & 0x0f]++]=i;
		}
	}
	decode->MaxNum=size;
}
//--------------------------------------------------------------------------
int Unrar::decode_number(Unrar::Decode *decode)
{
	unsigned int bits, bit_field, n;

	bit_field = getbits() & 0xfffe;
	
	if (bit_field < decode->DecodeLen[8])
		if (bit_field < decode->DecodeLen[4])
			if (bit_field < decode->DecodeLen[2])
				if (bit_field < decode->DecodeLen[1])
					bits=1;
				else
					bits=2;
			else
				if (bit_field < decode->DecodeLen[3])
					bits=3;
				else
					bits=4;
		else
			if (bit_field < decode->DecodeLen[6])
				if (bit_field < decode->DecodeLen[5])
					bits=5;
				else
					bits=6;
			else
				if (bit_field < decode->DecodeLen[7])
					bits=7;
				else
					bits=8;
	else
		if (bit_field < decode->DecodeLen[12])
			if (bit_field < decode->DecodeLen[10])
				if (bit_field < decode->DecodeLen[9])
					bits=9;
				else
					bits=10;
			else
				if (bit_field < decode->DecodeLen[11])
					bits=11;
				else
					bits=12;
		else
			if (bit_field < decode->DecodeLen[14])
				if (bit_field < decode->DecodeLen[13])
					bits=13;
				else
					bits=14;
			else
				bits=15;

	addbits(bits);
	n=decode->DecodePos[bits]+((bit_field-decode->DecodeLen[bits-1])>>(16-bits));
	if (n >= decode->MaxNum) {
		n=0;
	}
	return(decode->DecodeNum[n]);
}
//----------------------------------------------------------------
unsigned char Unrar::decode_audio(int delta)
{
	struct AudioVariables *v;
	int pch, d, i;
	unsigned int ch, mindif, num_min_dif;

	v = &unpack_data->audv[unpack_data->unp_cur_channel];
	v->byte_count++;
	v->D4 = v->D3;
	v->D3 = v->D2;
	v->D2 = v->last_delta - v->D1;
	v->D1 = v->last_delta;

	pch = 8 * v->last_char + v->K1 * v->D1 + v->K2 * v->D2 + v->K3 *
		v->D3 + v->K4 * v->D4 + v->K5 * unpack_data->unp_channel_delta;
	pch = (pch >> 3) & 0xff;

	ch = pch - delta;

	d = ((signed char) delta) << 3;

	v->dif[0] += abs(d);
	v->dif[1] += abs(d - v->D1);
	v->dif[2] += abs(d + v->D1);
	v->dif[3] += abs(d - v->D2);
	v->dif[4] += abs(d + v->D2);
	v->dif[5] += abs(d - v->D3);
	v->dif[6] += abs(d + v->D3);
	v->dif[7] += abs(d - v->D4);
	v->dif[8] += abs(d + v->D4);
	v->dif[9] += abs(d - unpack_data->unp_channel_delta);
	v->dif[10] += abs(d + unpack_data->unp_channel_delta);

	unpack_data->unp_channel_delta = v->last_delta = (signed char) (ch - v->last_char);
	v->last_char = ch;

	if ((v->byte_count & 0x1f) == 0) {
		mindif = v->dif[0];
		num_min_dif = 0;
		v->dif[0] = 0;
		for (i = 1 ; i < 11 ; i++) {
			if (v->dif[i] < mindif) {
				mindif = v->dif[i];
				num_min_dif = i;
			}
			v->dif[i]=0; /* ?????? looks wrong to me */
		}
		switch(num_min_dif) {
			case 1:
				if (v->K1 >= -16) {
					v->K1--;
				}
				break;
			case 2:
				if (v->K1 < 16) {
					v->K1++;
				}
				break;
			case 3:
				if (v->K2 >= -16) {
					v->K2--;
				}
				break;
			case 4:
				if (v->K2 < 16) {
					v->K2++;
				}
				break;
			case 5:
				if (v->K3 >= -16) {
					v->K3--;
				}
				break;
			case 6:
				if (v->K3 < 16) {
					v->K3++;
				}
				break;
			case 7:
				if (v->K4 >= -16) {
					v->K4--;
				}
				break;
			case 8:
				if (v->K4 < 16) {
					v->K4++;
				}
				break;
			case 9:
				if (v->K5 >= -16) {
					v->K5--;
				}
				break;
			case 10:
				if (v->K5 < 16) {
					v->K5++;
				}
				break;
		}
	}
	return ((unsigned char) ch);
}
//---------------------------------------------------------------
void  Unrar::copy_string20(unsigned int length, unsigned int distance) 
{
	unsigned int dest_ptr;

	unpack_data->last_dist = unpack_data->old_dist[unpack_data->old_dist_ptr++ & 3] = distance;
	unpack_data->last_length = length;
	unpack_data->dest_unp_size -= length;

	dest_ptr = unpack_data->unp_ptr - distance;
	if (dest_ptr < MAXWINSIZE-300 && unpack_data->unp_ptr < MAXWINSIZE-300) {
		unpack_data->window[unpack_data->unp_ptr++] = unpack_data->window[dest_ptr++];
		unpack_data->window[unpack_data->unp_ptr++] = unpack_data->window[dest_ptr++];
		while (length > 2) {
			length--;
			unpack_data->window[unpack_data->unp_ptr++] = unpack_data->window[dest_ptr++];
		}
	} else while (length--) {
		unpack_data->window[unpack_data->unp_ptr] = unpack_data->window[dest_ptr++ & MAXWINMASK];
		unpack_data->unp_ptr = (unpack_data->unp_ptr+1) & MAXWINMASK;
	}
}
//---------------------------------------------------------------
void Unrar::read_last_tables()
{

	if (unpack_data->read_top >= unpack_data->in_addr+5)
	{
		if (unpack_data->unp_audio_block)
		{
			if (decode_number((struct Decode *)&unpack_data->MD[unpack_data->unp_cur_channel]) == 256)
			{
					read_tables20();
			}
		} else if (decode_number((struct Decode *)&unpack_data->LD) == 269) 
		{
			read_tables20();
		}
	}
}
//-----------------------------------------------------------------
Unrar::~Unrar() 
{
		//close();
}
//-----------------------------------------------------------------
BOOLEAN Unrar::HasNextFile()
{
	BOOLEAN Rez  ;
	INT64 SeekParameter ;
	if ( SoldCorrupt == TRUE  )
	{
		return FALSE ;
	}
	SeekParameter  = NextHeaderFile ;
	Rez =m_pclsRarFile->Seek(NextHeaderFile , JFile::FBEGIN) ;
	if (Rez == FALSE || SeekParameter != NextHeaderFile  )
	{

		if (file_header != NULL)
		{
			SMHeapFree(file_header) ;
			file_header = NULL ;
		}
		PutLog (FILE_SEEK_ERROR) ;
		return FALSE ;
	}	
	Rez = ReadBlock();
	if (Rez == FALSE || file_header == NULL)
	{
		return FALSE ;
	}

	NextHeaderFile =  file_header->next_offset ;		
	
	return TRUE ;
}
//-----------------------------------------------------------------
BOOLEAN Unrar::ReadBlock()
{
	UINT64 CurrentOffset ;
	INT64 SeekParameter ; 
	BOOLEAN Rez ;
	RarDirectory	ocRarDirectory;
	
	while(1)
	{
		m_pclsRarFile->GetFilePosition(CurrentOffset);	
		Rez = ReadFileHeader();
		if (Rez == FALSE || file_header == NULL)
		{
			return FALSE ;
		}
		

		file_header->start_offset = CurrentOffset ;
		file_header->next_offset = CurrentOffset + file_header->HeadSize ;
		if(file_header->Flags & LONG_BLOCK)
			file_header->next_offset += file_header->PackSize;

		if(file_header->next_offset <= CurrentOffset)
		{
			SMHeapFree(file_header);
			file_header = NULL;
			return FALSE;
		}

		ocRarDirectory.m_u32Index = ocMainDirectory.size();
		ocRarDirectory.m_i64FileHeaderOffset = file_header->start_offset;
		ocRarDirectory.m_u32HeadAndBodySize = file_header->HeadSize + file_header->PackSize;
		ocMainDirectory.push_back(ocRarDirectory);
		u32ItemIndex++;

		if(file_header->Type == FILE_HEAD && ((file_header->Flags & LHD_ISDIR ) != LHD_ISDIR )  &&
		   file_header->UnpackSize != 0 &&  !(file_header->Flags &  (LHD_SPLIT_BEFORE | LHD_SPLIT_AFTER)))
		{

			UINT32 NameSize = min ( sizeof (file_header->Filename) - 1 , file_header->NameSize) ;
			size_t TempSize = NameSize ;
			Rez = m_pclsRarFile->Read( file_header->Filename , TempSize);
			if (Rez == FALSE || TempSize != NameSize )
			{
				SMHeapFree(file_header);
				file_header = NULL ;
				return FALSE ;
			}

			file_header->Filename[NameSize] = '\0' ;
			UINT32 SeekParam = file_header->NameSize - NameSize ;
			if (SeekParam != 0)
			{
				if ( m_pclsRarFile->Seek(SeekParam , JFile::FCURRENT) == FALSE ) 
				{
					PutLog(FILE_SEEK_ERROR);
					return FALSE ;
				}
			}
#ifdef UNICODE
			*NamePointer = L'\0' ;
			mbstowcs ( NamePointer , file_header->Filename  ,NameSize) ;
			NamePointer [NameSize]  = L'\0' ;
#else 
			strncpy (file_header->Filename , NamePointer , m_u16FileNameSize - (NamePointer - m_strCurrentFileName));
			NamePointer [(m_u16FileNameSize - (NamePointer - m_strCurrentFileName) -1 )]  = '\0' ;
#endif
			
			if ( (file_header->Flags & LHD_PASSWORD) )
			{
				JString Message = JString(m_strCurrentFileName);
				Message += JString(MSC(FILE_COMPERSS_PROTECT));
				MessageQueue->push(Message); 
			}
			else
			{
				break ;

			}
			
		}
		else
		{
			u32SubHeadNumber++;
		}
		SeekParameter = file_header->next_offset ;
		Rez = m_pclsRarFile->Seek(SeekParameter , JFile::FBEGIN) ;
		if (Rez == FALSE || SeekParameter != file_header->next_offset )
		{
			SMHeapFree(file_header) ;
			file_header = NULL ;
			return FALSE ;
		}
		
		SMHeapFree(file_header) ;
		file_header = NULL ;
	}

	return TRUE ;

}
//----------------------------------------------------------------
BOOLEAN Unrar::ReadFileHeader()
{
	size_t CountRead ;
	BOOLEAN Rez ; 
	file_header = (UnrarFileHeader *) SMHeapAlloc(sizeof(UnrarFileHeader)) ;
	if (file_header == NULL)
		return FALSE ;
	memset (file_header,0,sizeof(UnrarFileHeader));
	CountRead = SIZEOF_NEWLHD ;
	Rez = m_pclsRarFile->Read(file_header ,CountRead) ;
	if (Rez == FALSE || CountRead != SIZEOF_NEWLHD ) 
	{
		SMHeapFree(file_header) ;
		file_header = NULL ;
		return FALSE ; 
	}
	return TRUE ;
	
}

//Kia Develop 
//////////////////////////////////////////////////////////////////////////
void Unrar::SeekToFirstBlock()
{
	INT64 MainSeek = sizeof(mark_header_t) + sizeof(UnrarMainHeader);
	m_pclsRarFile->Seek(MainSeek, JFile::FBEGIN);
}
//////////////////////////////////////////////////////////////////////////
int Unrar::Count()
{	
// 	FileCount = 0;
// 	SeekToFirstBlock();
// 	while(HasNextFile() != FALSE)
// 	{
// 		INT64 SeekParameter = file_header->PackSize + (INT64)file_header->start_offset + (INT64)file_header->HeadSize;
// 		m_pclsRarFile->Seek(SeekParameter, JFile::FBEGIN);
// 		FileCount++;
// 	}
	return ocMainDirectory.size();
	//return FileCount;
}
//////////////////////////////////////////////////////////////////////////
BOOLEAN Unrar::CopyDataBlock(INT64 WriteStartOffset, INT64 ReadStartOffset, INT64 ReadSize)
{
	UINT8 *Buffer = (UINT8 *)SMHeapAlloc(4096);
	INT64 TmpWritePointer = WriteStartOffset;
	size_t TmpReadSize = 0;
	//m_i64WritePointer += ReadSize;
	while (ReadSize != 0)
	{
		INT64 SeekParameter = ReadStartOffset;
		//TmpReadSize += ReadStartOffset;
		m_pclsRarFile->Seek(SeekParameter, JFile::FBEGIN);		
		TmpReadSize = (ReadSize > 4096? 4096 : ReadSize);
		ReadStartOffset += TmpReadSize;
		if(m_pclsRarFile->Read(Buffer, TmpReadSize) == FALSE)
		{
			SMHeapFree(Buffer);
			return FALSE;
		}
		
		SeekParameter = TmpWritePointer;
		m_pclsRarFile->Seek(SeekParameter, JFile::FBEGIN);
		if(m_pclsRarFile->Write(Buffer, TmpReadSize) == FALSE)
		{
			SMHeapFree(Buffer);
			return FALSE;
		}
		TmpWritePointer += TmpReadSize ;
		ReadSize -= TmpReadSize;
	}
	SMHeapFree(Buffer);
	return TRUE;
}
//////////////////////////////////////////////////////////////////////////
BOOLEAN Unrar::RemoveEntries(RarDirectory *List = NULL/*, INT64 ListCount = 0*/)
{
// 	this->Count();
// 	if (FileCount == 0)
// 	{
// 		return FALSE;
// 	}

// 	if (ListCount != 0 && List->Index == 0)
// 	{
// 		SeekToFirstBlock();
// 		HasNextFile();
//  		if (FileCount == 1)
//  		{
// 			if (SetEndOfFile(m_pclsRarFile->GetHandle()) == 0)
// 			{
// 			 	LastErrorCode = GetLastError();
// 			}
//  		}
// 	}
	RarDirectory *TempList;
	INT64 FileSize = 0;
	m_pclsRarFile->Seek(FileSize, JFile::FEND);
	SeekToFirstBlock();
	m_i64WritePointer = List->m_i64FileHeaderOffset;
	TempList = List;
	/*
	while (TRUE)
	{
		// Remove Entry Here		
		if (TempList->NextNode == NULL)
		{
			if ((TempList->FileHeaderOffset + TempList->HeadAndBodySize) == FileSize || FileSize - TempList->FileHeaderOffset + TempList->HeadAndBodySize <= sizeof(UnrarFileHeader))
			{
				break;
			}
			else
			{
				CopyDataBlock(TempList->FileHeaderOffset,  TempList->FileHeaderOffset + TempList->HeadAndBodySize, FileSize - (TempList->FileHeaderOffset + TempList->HeadAndBodySize));
				break;
			}
		}
		else
		{
			CopyDataBlock(TempList->FileHeaderOffset,  TempList->FileHeaderOffset + TempList->HeadAndBodySize, (TempList->NextNode->FileHeaderOffset) - (TempList->FileHeaderOffset + TempList->HeadAndBodySize));
			List  = List->NextNode;
			delete TempList;
			TempList = List;
		}
	}*/
	m_pclsRarFile->Seek(m_i64WritePointer, JFile::FBEGIN);
	if (SetEndOfFile(m_pclsRarFile->GetHandle()) == 0)
	{
		LastErrorCode = GetLastError();
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}
//////////////////////////////////////////////////////////////////////////
BOOLEAN Unrar::ExtractCurrentFile (TCHAR * PathToSaveExtractedFile) 
{
// 	BOOLEAN Result = ExtractCurrentFile();
// 	if (!Result)
// 	{
// 		return Result;
// 	}
		
// 	JString FileName = TempFile->GetName();
// 	TempFile->Close();
// 	
// 	if(CopyFile(FileName.data(), PathToSaveExtractedFile, false) == 0)
// 	{		
// 		LastErrorCode = GetLastError();
// 		return FALSE;jn
// 	}
	return TRUE;
}
//End Kia Develop 

//--------------------------------------------------------
BOOLEAN Unrar::GetFile () 
{
	INT64  SeekParameter ;
	BOOLEAN Rez ;
	


	SeekParameter = file_header->start_offset + file_header->HeadSize ;
	Rez = m_pclsRarFile->Seek (SeekParameter , JFile::FBEGIN) ;
	if (Rez == FALSE || SeekParameter != file_header->start_offset + file_header->HeadSize)
	{
		PutLog (FILE_SEEK_ERROR) ;
		SMHeapFree(file_header) ;
		file_header = NULL ;
		JString Message = JString(m_strCurrentFileName);
		Message += JString(MSC(UNCOMMPESS_CROUPTED));
		MessageQueue->push(Message); 
		return FALSE ;
	}

	Rez = JFile::GetTempFile<JCompressFile>(m_pclsUnrarFile , _TEXT("Jav")) ;
	if ( Rez == FALSE || m_pclsUnrarFile == NULL)
	{
		SMHeapFree(file_header) ;
		file_header = NULL ;
		PutLog (RAR_CAN_NOT_CREATE_TEMP_FILE) ;
		JString Message = JString(m_strCurrentFileName);
		Message += JString(MSC(FILE_CREATE_TEMP_FILE));
		MessageQueue->push(Message); 
		return FALSE ;
	}
	m_pclsUnrarFile->SetCompressor(this);
	unpack_data->max_size = maxfilesize ;
	if (file_header->Method == 0x30 )
	{
		Rez = CopyDataFromFile(file_header->PackSize) ; 
		if ( Rez == FALSE )
		{
			PutLog(RAR_CAN_NOT_COPY_FILE_UPACK) ;
			JString Message = JString(m_strCurrentFileName);
			Message += JString(MSC(UNCOMMPESS_CROUPTED));
			MessageQueue->push(Message); 
		}
	}else
	{
		unpack_data->dest_unp_size = file_header->UnpackSize;
		unpack_data->pack_size = file_header->PackSize;
		if( file_header->UnpackVer <= 15)
		{
			Rez = Unpack(15, (file_count>1) && ((main_hdr->Flags & MHD_SOLID)!=0));
		} else
		{
			if ((file_count == 1)  && (file_header->Flags & LHD_SOLID) )
			{
				file_header->Flags -= LHD_SOLID ;
			}
			Rez = Unpack(file_header->UnpackVer, file_header->Flags & LHD_SOLID);
		}
		if(Rez == TRUE && unpack_data->unp_crc != 0xffffffff)
		{
			if(file_header->FileCrc != (unpack_data->unp_crc^0xffffffff))
			{
				PutLog(RAR_CRC_ERROR);
				JString Message = JString(m_strCurrentFileName);
				Message += JString(MSC(CRC_ERROR));
				MessageQueue->push(Message); 
				Rez = FALSE ;
			}
		}
		if (Rez == FALSE )
		{
			PutLog(RAR_CORRUPT_FILE_DETECTED);
			if (file_header->Flags & LHD_SOLID) // æä ÏÑ ÝÇíá ÓæáÏ ÇÑ í˜í ÇÒ ÝÇíáåÇ ÎÑÇÈ ÈÇÔÏ ÏÑ äíÊíÌå ÏíÑÇä åã ÎÑÇÈ ÎæÇåäÏ ÈæÏ
			{
				JString Message = JString(m_strCurrentFileName);
				Message += JString(MSC(UNCOMMPESS_CROUPTED));
				MessageQueue->push(Message); 
				SoldCorrupt = TRUE ;
			}
		}
		vm_free();
	}
	if (Rez== FALSE)
	{
		delete m_pclsUnrarFile;
		m_pclsUnrarFile = NULL ;
	}
	else
	{
		m_pclsUnrarFile->SetDisplayName(JString(m_strCurrentFileName));
	}
	SMHeapFree(file_header) ;
	file_header = NULL ;
	file_count++ ;
	return Rez  ;
}
//----------------------------------------------------------------
BOOLEAN Unrar::Upack29 (BOOLEAN solid) 
{
	unsigned char ldecode[]={0,1,2,3,4,5,6,7,8,10,12,14,16,20,24,28,
		32,40,48,56,64,80,96,112,128,160,192,224};
	unsigned char lbits[]=  {0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5};
	int ddecode[DC]={0,1,2,3,4,6,8,12,16,24,32,48,64,96,128,192,256,384,512,768,1024,
		1536,2048,3072,4096,6144,8192,12288,16384,24576,32768,49152,65536,
		98304,131072,196608,262144,327680,393216,458752,524288,589824,655360,
		720896,786432,851968,917504,983040,1048576,1310720,1572864,
		1835008,2097152,2359296,2621440,2883584,3145728,3407872,3670016,3932160};
	UINT8 dbits[DC]= {0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,
		11,11,12,12,13,13,14,14,15,15,16,16,16,16,16,16,16,16,16,
		16,16,16,16,16,18,18,18,18,18,18,18,18,18,18,18,18};
	unsigned char sddecode[]={0,4,8,16,32,64,128,192};
	unsigned char sdbits[]=  {2,2,3, 4, 5, 6,  6,  6};
	unsigned int bits, distance;
	int retval=TRUE, i, number, length, dist_number, low_dist, ch, next_ch;
	int length_number, failed;
	UnpackInitData(solid);
	if (UpackReadBuffer() == FALSE)
	{
		return FALSE ;
	}
	if (!solid || !unpack_data->tables_read)
	{
		if(read_tables() == FALSE)
		{
			return FALSE ;
		}

	}
	while (1)
	{
		unpack_data->unp_ptr &= MAXWINMASK;
		if (unpack_data->in_addr > unpack_data->read_border) 
		{
			if (UpackReadBuffer() == FALSE)
			{
				retval = FALSE;
				break;
			}
		}
		if (((unpack_data->wr_ptr - unpack_data->unp_ptr) & MAXWINMASK) < 260 &&
			unpack_data->wr_ptr != unpack_data->unp_ptr) 
		{
				unp_write_buf();
		}
		if (unpack_data->unp_block_type == BLOCK_PPM) {
			ch = ppm_decode_char();
			if (ch == -1)
			{
				ppm_cleanup();
				unpack_data->unp_block_type = BLOCK_LZ;
				retval = FALSE;
				break;
			}
			if (ch == unpack_data->ppm_esc_char)
			{
				next_ch = ppm_decode_char();
				if (next_ch == -1) {
					retval = FALSE;
					break;
				}
				if (next_ch == 0)
				{
					if (read_tables() == FALSE) {
						retval = FALSE;
						break;
					}
					continue;
				}
				if (next_ch == 2 || next_ch == -1)
				{
					break;
				}
				if (next_ch == 3)
				{
					if (!read_vm_code_PPM())
					{
						retval = FALSE;
						break;
					}
					continue;
				}
				if (next_ch == 4)
				{
					unsigned int length = 0;
					distance = 0;
					failed = FALSE;
					for (i=0 ; i < 4 && !failed; i++) {
						ch = ppm_decode_char();
						if (ch == -1) {
							failed = TRUE;
						} else {
							if (i==3) {
								length = (UINT8)ch;
							} else {
								distance = (distance << 8) +
									(UINT8)ch;
							}
						}
					}
					if (failed) {
						retval = FALSE;
						break;
					}
					copy_string(length+32, distance+2);
					continue;
				}
				if (next_ch == 5) {
					int length = ppm_decode_char();
					if (length == -1) {
						retval = FALSE;
						break;
					}
					copy_string(length+4, 1);
					continue;
				}
			}
			unpack_data->window[unpack_data->unp_ptr++] = ch;
			continue;
		} else {

			number = decode_number( (struct Decode *)&unpack_data->LD);
			if (number < 256) {
				unpack_data->window[unpack_data->unp_ptr++] = (UINT8) number;
				continue;
			}
			if (number >= 271) {
				length = ldecode[number-=271]+3;
				if ((bits=lbits[number]) > 0) {
					length += getbits() >> (16-bits);
					addbits( bits);
				}
				dist_number = decode_number((struct Decode *)&unpack_data->DD);
				distance = ddecode[dist_number] + 1;
				if ((bits = dbits[dist_number]) > 0) {
					if (dist_number > 9) {
						if (bits > 4) {
							distance += ((getbits() >>
								(20-bits)) << 4);
							addbits(bits-4);
						}
						if (unpack_data->low_dist_rep_count > 0) {
							unpack_data->low_dist_rep_count--;
							distance += unpack_data->prev_low_dist;
						} else {
							low_dist = decode_number((struct Decode *) &unpack_data->LDD);
							if (low_dist == 16) {
								unpack_data->low_dist_rep_count =
									LOW_DIST_REP_COUNT-1;
								distance += unpack_data->prev_low_dist;
							} else {
								distance += low_dist;
								unpack_data->prev_low_dist = low_dist;
							}
						}
					} else {
						distance += getbits() >> (16-bits);
						addbits(bits);
					}
				}

				if (distance >= 0x2000) {
					length++;
					if (distance >= 0x40000L) {
						length++;
					}
				}

				insert_old_dist(distance);
				insert_last_match(length, distance);
				copy_string(length, distance);
				continue;
			}
			if (number == 256) {
				if (!read_end_of_block()) {
					break;
				}
				continue;
			}
			if (number == 257) {
				if (!read_vm_code()) {
					retval = FALSE;
					break;
				}
				continue;
			}
			if (number == 258) {
				if (unpack_data->last_length != 0) {
					copy_string(unpack_data->last_length,
						unpack_data->last_dist);
				}
				continue;
			}
			if (number < 263) {
				dist_number = number-259;
				distance = unpack_data->old_dist[dist_number];
				for (i=dist_number ; i > 0 ; i--) {
					unpack_data->old_dist[i] = unpack_data->old_dist[i-1];
				}
				unpack_data->old_dist[0] = distance;

				length_number = decode_number((struct Decode *)&unpack_data->RD);
				length = ldecode[length_number]+2;
				if ((bits = lbits[length_number]) > 0) {
					length += getbits() >> (16-bits);
					addbits(bits);
				}
				insert_last_match(length, distance);
				copy_string(length, distance);
				continue;
			}
			if (number < 272) {
				distance = sddecode[number-=263]+1;
				if ((bits = sdbits[number]) > 0) {
					distance += getbits() >> (16-bits);
					addbits(bits);
				}
				insert_old_dist(distance);
				insert_last_match(2, distance);
				copy_string(2, distance);
				continue;
			}

		}
	}
	if (retval) {
		unp_write_buf();
	}
	return retval;
}
//----------------------------------------------------------------
BOOLEAN Unrar::read_tables()
{
	UINT8 bit_length[BC];
	unsigned char table[HUFF_TABLE_SIZE];
	unsigned int bit_field;
	int i, length, zero_count, number, n;
	const int table_size=HUFF_TABLE_SIZE;
	if (unpack_data->in_addr > unpack_data->read_top-25) 
	{
		if (!UpackReadBuffer()) {
			return FALSE;
		}
	}
	addbits((8-unpack_data->in_bit) & 7);
	bit_field = getbits() ;
	if (bit_field & 0x8000)
	{
		unpack_data->unp_block_type = BLOCK_PPM;
		if(!ppm_decode_init())
		{
			return FALSE;
		}
		return TRUE;
	}
	unpack_data->unp_block_type = BLOCK_LZ;
	unpack_data->prev_low_dist = 0;
	unpack_data->low_dist_rep_count = 0;
	if (!(bit_field & 0x4000)) 
	{
		memset(unpack_data->unp_old_table, 0, sizeof(unpack_data->unp_old_table));
	}
	addbits(2);
	

	for (i=0 ; i < BC ; i++) 
	{
		length = (UINT8)(getbits() >> 12);
		addbits(4);
		if (length == 15) {
			zero_count = (UINT8)(getbits() >> 12);
			addbits(4);
			if (zero_count == 0) {
				bit_length[i] = 15;
			} else {
				zero_count += 2;
				while (zero_count-- > 0 &&
					i<sizeof(bit_length)/sizeof(bit_length[0])) {
						bit_length[i++]=0;
				}
				i--;
			}
		} else {
			bit_length[i] = length;
		}
	}

	make_decode_tables(bit_length,(struct Decode *)&unpack_data->BD,BC);

	for (i=0;i<table_size;) {
			if (unpack_data->in_addr > unpack_data->read_top-5) 
			{
				if (!UpackReadBuffer())
				{
					return FALSE;
				}
			}
			number = decode_number((struct Decode *)&unpack_data->BD);
			if (number < 16) 
			{
				table[i] = (number+unpack_data->unp_old_table[i]) & 0xf;
				i++;
			} else if (number < 18) 
			{
				if (number == 16) 
				{
					n = (getbits() >> 13) + 3;
					addbits(3);
				} else 
				{
					n = (getbits() >> 9) + 11;
					addbits(7);
				}
				while (n-- > 0 && i < table_size) 
				{
					table[i] = table[i-1];
					i++;
				}
			} else
			{
				if (number == 18) 
				{
					n = (getbits() >> 13) + 3;
					addbits(3);
				} else {
					n = (getbits() >> 9) + 11;
					addbits(7);
				}
				while (n-- > 0 && i < table_size) 
				{
					table[i++] = 0;
				}
			}
		}
	unpack_data->tables_read = TRUE;
	if (unpack_data->in_addr > unpack_data->read_top) {
		return FALSE;
	}
	make_decode_tables(&table[0], (struct Decode *)&unpack_data->LD,NC);
	make_decode_tables(&table[NC], (struct Decode *)&unpack_data->DD,DC);
	make_decode_tables(&table[NC+DC], (struct Decode *)&unpack_data->LDD,LDC);
	make_decode_tables(&table[NC+DC+LDC], (struct Decode *)&unpack_data->RD,RC);
	memcpy(unpack_data->unp_old_table,table,sizeof(unpack_data->unp_old_table));

	return TRUE;
	
}
//----------------------------------------------------------------
BOOLEAN Unrar::get_char(unsigned int &Arg) 
{
	if (unpack_data->in_addr > MAX_BUF_SIZE-30) 
	{
		if (!UpackReadBuffer()) 
		{
			return FALSE;
		}
	}
	Arg = unpack_data->in_buf[unpack_data->in_addr++] ;
	return TRUE ;
}
//----------------------------------------------------------------
BOOLEAN Unrar::ppm_decode_init()
{
	int  Reset ;
	unsigned int max_order ,MaxMB , Temp;
	BOOLEAN Rez ;
	Rez = get_char(max_order); 
	if (Rez == FALSE)
	{
		PutLog (RAR_ERROR_IN_GET_CHAR) ;
	}
	Reset = (max_order & 0x20) ? 1 : 0;
	if (Reset)
	{
		Rez = get_char(MaxMB); 
		if (Rez == FALSE)
		{
			PutLog (RAR_ERROR_IN_GET_CHAR) ;
		}
	}else
	{
		if (unpack_data->ppm_data.sub_alloc.sub_allocator_size == 0 )
		{
			return FALSE ;
		}
	}
	if (max_order & 0x40)
	{
		
		Rez = get_char(Temp) ;
		unpack_data->ppm_esc_char  = Temp; 
	}
	range_coder_init_decoder(&unpack_data->ppm_data.coder);
	if (Reset)
	{
		max_order = (max_order & 0x1f) + 1;
		if (max_order > 16)
		{
			max_order = 16 + (max_order - 16) * 3;
		}
		if (max_order == 1)
		{
			sub_allocator_stop_sub_allocator() ;
			return FALSE ;
		}
		if(sub_allocator_start_sub_allocator(MaxMB+1) == FALSE)
		{
			sub_allocator_stop_sub_allocator() ;
			return FALSE;
		}
		if (!start_model_rare(max_order)) {
			sub_allocator_stop_sub_allocator();
			return FALSE;
		}
	}
	return ((unpack_data->ppm_data.min_context != NULL) ? TRUE : FALSE );

}
//----------------------------------------------------------------
void Unrar::range_coder_init_decoder(range_coder_t *coder)
{
	int i;
	unsigned int TempChar ;	
	coder->low = coder->code = 0;
	coder->range = (unsigned int) -1;
	for (i=0; i < 4 ; i++)
	{
		get_char(TempChar);
		coder->code = (coder->code << 8) | TempChar ;
	}
}
//----------------------------------------------------------------
void Unrar::sub_allocator_stop_sub_allocator() 
{
	if (unpack_data->ppm_data.sub_alloc.sub_allocator_size )
	{	
		unpack_data->ppm_data.sub_alloc.sub_allocator_size  =  0 ;
		SMHeapFree(unpack_data->ppm_data.sub_alloc.heap_start) ;
	}
}
//----------------------------------------------------------------
BOOLEAN Unrar::sub_allocator_start_sub_allocator(int sa_size) 
{
	unsigned int t, alloc_size;
	t = sa_size << 20;
	if (unpack_data->ppm_data.sub_alloc.sub_allocator_size == t)
	{
		return TRUE;
	}
	sub_allocator_stop_sub_allocator() ;
	if (t > MAXMEMORYAAVLIBALE)
	{
		return FALSE ;
	}
	alloc_size = t/FIXED_UNIT_SIZE*UNIT_SIZE+UNIT_SIZE;
	unpack_data->ppm_data.sub_alloc.heap_start =(UINT8 *)SMHeapAlloc(alloc_size) ;
	if (unpack_data->ppm_data.sub_alloc.heap_start==NULL)
	{
		PutLog (RAR_ALLOC_TOO_BUFFER);
		return FALSE ;
	}
	unpack_data->ppm_data.sub_alloc.heap_end = unpack_data->ppm_data.sub_alloc.heap_start + alloc_size - UNIT_SIZE;
	unpack_data->ppm_data.sub_alloc.sub_allocator_size = t;
	return TRUE ;
}
//----------------------------------------------------------------
BOOLEAN Unrar::start_model_rare(int max_order)
{
	int i, k, m, step;
	unpack_data->ppm_data.esc_count = 1 ;
	unpack_data->ppm_data.max_order = max_order;
	if (restart_model_rare() == FALSE)
	{
		return FALSE;
	}
	unpack_data->ppm_data.ns2bsindx[0] = 2*0;
	unpack_data->ppm_data.ns2bsindx[1] = 2*1;

	memset(unpack_data->ppm_data.ns2bsindx+2, 2*2, 9);
	memset(unpack_data->ppm_data.ns2bsindx+11, 2*3, 256-11);

	for (i=0 ; i < 3; i++) {
		unpack_data->ppm_data.ns2indx[i] = i;
	}
	for (m=i, k=step=1; i < 256; i++) {
		unpack_data->ppm_data.ns2indx[i]=m;
		if (!--k) {
			k = ++step;
			m++;
		}
	}
	memset(unpack_data->ppm_data.hb2flag, 0, 0x40);
	memset(unpack_data->ppm_data.hb2flag+0x40, 0x08, 0x100-0x40);
	unpack_data->ppm_data.dummy_sse2cont.shift = PERIOD_BITS;
	return TRUE;
}
//----------------------------------------------------------------
BOOLEAN  Unrar::restart_model_rare()
{
	int i, k, m ,init_val;
	static const UINT16 init_bin_esc[] = {
		0x3cdd, 0x1f3f, 0x59bf, 0x48f3, 0x64a1, 0x5abc, 0x6632, 0x6051
	};
	memset(unpack_data->ppm_data.char_mask, 0, sizeof(unpack_data->ppm_data.char_mask));
	sub_allocator_init_sub_allocator() ;

	unpack_data->ppm_data.init_rl=-(unpack_data->ppm_data.max_order < 12 ? unpack_data->ppm_data.max_order:12)-1;
	unpack_data->ppm_data.min_context = unpack_data->ppm_data.max_context =
		(struct ppm_context *) sub_allocator_alloc_context();
	if(!unpack_data->ppm_data.min_context) {
		return FALSE;
	}
	unpack_data->ppm_data.min_context->suffix = NULL;
	unpack_data->ppm_data.order_fall = unpack_data->ppm_data.max_order;
	unpack_data->ppm_data.min_context->con_ut.u.summ_freq = (unpack_data->ppm_data.min_context->num_stats=256)+1;
	unpack_data->ppm_data.found_state = unpack_data->ppm_data.min_context->con_ut.u.stats=
		(struct state_tag *)sub_allocator_alloc_units(256/2);
	if(!unpack_data->ppm_data.found_state) {
		return FALSE;
	}
	for (unpack_data->ppm_data.run_length = unpack_data->ppm_data.init_rl, unpack_data->ppm_data.prev_success=i=0; i < 256 ; i++)
	{
		unpack_data->ppm_data.min_context->con_ut.u.stats[i].symbol = i;
		unpack_data->ppm_data.min_context->con_ut.u.stats[i].freq = 1;
		unpack_data->ppm_data.min_context->con_ut.u.stats[i].successor = NULL;
	}
	for (i=0 ; i < 128 ; i++) {
		for (k=0 ; k < 8 ; k++) {
			for (m=0 ; m < 64 ; m+=8) {
				unpack_data->ppm_data.bin_summ[i][k+m]=BIN_SCALE-init_bin_esc[k]/(i+2);
			}
		}
	}
	for (i=0; i < 25; i++) {
		for (k=0 ; k < 16 ; k++) {
			init_val = 5*i+10 ;  
			unpack_data->ppm_data.see2cont[i][k].summ = init_val << (unpack_data->ppm_data.see2cont[i][k].shift=PERIOD_BITS-4);
			unpack_data->ppm_data.see2cont[i][k].count = 4;
		}
	}
	return TRUE;
}
//----------------------------------------------------------------
void Unrar::sub_allocator_init_sub_allocator()
{
	int i, k;
	unsigned int size1, real_size1, size2, real_size2;
	memset(unpack_data->ppm_data.sub_alloc.free_list, 0, sizeof(unpack_data->ppm_data.sub_alloc.free_list));
	unpack_data->ppm_data.sub_alloc.ptext = unpack_data->ppm_data.sub_alloc.heap_start;

	size2 = FIXED_UNIT_SIZE*(unpack_data->ppm_data.sub_alloc.sub_allocator_size/8/FIXED_UNIT_SIZE*7);
	real_size2 = size2/FIXED_UNIT_SIZE*UNIT_SIZE;
	size1 = unpack_data->ppm_data.sub_alloc.sub_allocator_size - size2;
	real_size1 = size1/FIXED_UNIT_SIZE*UNIT_SIZE+size1%FIXED_UNIT_SIZE;
	unpack_data->ppm_data.sub_alloc.hi_unit = unpack_data->ppm_data.sub_alloc.heap_start + unpack_data->ppm_data.sub_alloc.sub_allocator_size;
	unpack_data->ppm_data.sub_alloc.lo_unit = unpack_data->ppm_data.sub_alloc.units_start = unpack_data->ppm_data.sub_alloc.heap_start + real_size1;
	unpack_data->ppm_data.sub_alloc.fake_units_start = unpack_data->ppm_data.sub_alloc.heap_start + size1;
	unpack_data->ppm_data.sub_alloc.hi_unit = unpack_data->ppm_data.sub_alloc.lo_unit + real_size2;

	for (i=0,k=1; i < N1 ; i++, k+=1) {
		unpack_data->ppm_data.sub_alloc.indx2units[i] = k;
	}
	for (k++; i < N1+N2 ; i++, k+=2) {
		unpack_data->ppm_data.sub_alloc.indx2units[i] = k;
	}
	for (k++; i < N1+N2+N3 ; i++, k+=3) {
		unpack_data->ppm_data.sub_alloc.indx2units[i] = k;
	}
	for (k++; i < N1+N2+N3+N4 ; i++, k+=4) {
		unpack_data->ppm_data.sub_alloc.indx2units[i] = k;
	}

	for (unpack_data->ppm_data.sub_alloc.glue_count=k=i=0; k < 128; k++) {
		i += (unpack_data->ppm_data.sub_alloc.indx2units[i] < k+1);
		unpack_data->ppm_data.sub_alloc.units2indx[k] = i;
	}
}
//----------------------------------------------------------------
void *Unrar::sub_allocator_alloc_context()
{
	if (unpack_data->ppm_data.sub_alloc.hi_unit != unpack_data->ppm_data.sub_alloc.lo_unit) {
		return (unpack_data->ppm_data.sub_alloc.hi_unit -= UNIT_SIZE);
	}
	if (unpack_data->ppm_data.sub_alloc.free_list->next) {
		return sub_allocator_remove_node(0);
	}
	return sub_allocator_alloc_units_rare(0);
}
//----------------------------------------------------------------
void * Unrar::sub_allocator_remove_node(int index) 
{
	struct rar_node *ret_val;
	ret_val = unpack_data->ppm_data.sub_alloc.free_list[index].next;
	unpack_data->ppm_data.sub_alloc.free_list[index].next = ret_val->next;
	return ret_val;
}
//----------------------------------------------------------------
void * Unrar::sub_allocator_alloc_units_rare(int index) 
{
	int i, j;
	void *ret_val;
	if (!unpack_data->ppm_data.sub_alloc.glue_count)
	{
			unpack_data->ppm_data.sub_alloc.glue_count = 255;
			sub_allocator_glue_free_blocks();
			if (unpack_data->ppm_data.sub_alloc.free_list[index].next)
			{
				return sub_allocator_remove_node(index);
			}
	}
	i=index;
	do {
		if (++i == N_INDEXES) {
			unpack_data->ppm_data.sub_alloc.glue_count--;
			i = UNIT_SIZE * unpack_data->ppm_data.sub_alloc.indx2units[index];
			j = 12 * unpack_data->ppm_data.sub_alloc.indx2units[index];
			if (unpack_data->ppm_data.sub_alloc.fake_units_start - unpack_data->ppm_data.sub_alloc.ptext > j) {
				unpack_data->ppm_data.sub_alloc.fake_units_start -= j;
				unpack_data->ppm_data.sub_alloc.units_start -= i;
				return unpack_data->ppm_data.sub_alloc.units_start;
			}
			return NULL;
		}
	} while ( !unpack_data->ppm_data.sub_alloc.free_list[i].next);
	ret_val = sub_allocator_remove_node(i);
	sub_allocator_split_block(ret_val, i, index);
	return ret_val;
}
//----------------------------------------------------------------
void Unrar::sub_allocator_glue_free_blocks()
{
	rar_mem_blk_t s0, *p;
	UINT32 u32Index;
	if (unpack_data->ppm_data.sub_alloc.lo_unit != unpack_data->ppm_data.sub_alloc.hi_unit) 
	{
		*unpack_data->ppm_data.sub_alloc.lo_unit = 0;
	}
	for (u32Index=0, s0.next=s0.prev=&s0; u32Index < N_INDEXES; u32Index++) {
		while (unpack_data->ppm_data.sub_alloc.free_list[u32Index].next) {
			p = (rar_mem_blk_t *) sub_allocator_remove_node(u32Index);
			p->next = (p->prev=p)->next;
			s0.next = p->next->prev = p;
			p->stamp = 0xFFFF;
			p->nu = unpack_data->ppm_data.sub_alloc.indx2units[u32Index];
		}
	}
}

void Unrar::sub_allocator_split_block(void *pv, int old_indx, int new_indx) 
{
	int i, udiff;
	UINT8 *p;

	udiff = unpack_data->ppm_data.sub_alloc.indx2units[old_indx] - unpack_data->ppm_data.sub_alloc.indx2units[new_indx];
	p = ((UINT8 *) pv) + UNIT_SIZE*(unpack_data->ppm_data.sub_alloc.indx2units[new_indx]);
	if (unpack_data->ppm_data.sub_alloc.indx2units[i=unpack_data->ppm_data.sub_alloc.units2indx[udiff-1]] != udiff)
	{
		sub_allocator_insert_node(p, --i);
		p += UNIT_SIZE*(i=unpack_data->ppm_data.sub_alloc.indx2units[i]);
		udiff -= i;
	}
	sub_allocator_insert_node(p, unpack_data->ppm_data.sub_alloc.units2indx[udiff-1]);
}
//----------------------------------------------------------------
void Unrar::unp_write_buf()
{
	unsigned int written_border, part_length, filtered_size;
	unsigned int write_size, block_start, block_length, block_end;
	struct UnpackFilter *flt, *next_filter;
	struct rarvm_prepared_program *prg, *next_prg;
	UINT8 *filtered_data;
	UINT32 u32Index1, u32Index2;

	written_border = unpack_data->wr_ptr;
	write_size = (unpack_data->unp_ptr - written_border) & MAXWINMASK;
	for (u32Index1=0 ; u32Index1 < unpack_data->PrgStack.num_items ; u32Index1++) {
		flt = unpack_data->PrgStack.array[u32Index1];
		if (flt == NULL) {
			continue;
		}
		if (flt->next_window) {
			flt->next_window = FALSE;
			continue;
		}
		block_start = flt->block_start;
		block_length = flt->block_length;
		if (((block_start-written_border)&MAXWINMASK) < write_size)
		{
			if (written_border != block_start) 
			{
				unp_write_area(written_border, block_start);
				written_border = block_start;
				write_size = (unpack_data->unp_ptr - written_border) & MAXWINMASK;
			}
			if (block_length <= write_size) 
			{
				block_end = (block_start + block_length) & MAXWINMASK;
				if (block_start < block_end || block_end==0) 
				{
					vm_set_memory(0,
					unpack_data->window+block_start, block_length);
				} else 
				{
					part_length = MAXWINMASK - block_start;
					vm_set_memory(0,
						unpack_data->window+block_start, part_length);
					vm_set_memory(part_length,
						unpack_data->window, block_end);
				}
				prg = &flt->prg;
				execute_code(prg);

				filtered_data = prg->filtered_data;
				filtered_size = prg->filtered_data_size;

				filter_delete(u32Index1);
				unpack_data->PrgStack.array[u32Index1] = NULL;				
				while (u32Index1+1 < unpack_data->PrgStack.num_items) {
					next_filter = unpack_data->PrgStack.array[u32Index1+1];
					if (next_filter==NULL ||
						next_filter->block_start!=block_start ||
						next_filter->block_length!=filtered_size ||
						next_filter->next_window) {
							break;
					}
					vm_set_memory(0,
						filtered_data, filtered_size);
					next_prg = &unpack_data->PrgStack.array[u32Index1+1]->prg;
					execute_code( next_prg);
					filtered_data = next_prg->filtered_data;
					filtered_size = next_prg->filtered_data_size;
					u32Index1++;
					filter_delete(u32Index1);
					unpack_data->PrgStack.array[u32Index1] = NULL;
				}
				unp_write_data( filtered_data, filtered_size);
				written_border = block_end;
				write_size = (unpack_data->unp_ptr - written_border) & MAXWINMASK;
			} else {
				for (u32Index2=u32Index1 ; u32Index2 < unpack_data->PrgStack.num_items ; u32Index2++) {
					flt = unpack_data->PrgStack.array[u32Index2];
					if (flt != NULL && flt->next_window) {
						flt->next_window = FALSE;
					}
				}
				unpack_data->wr_ptr = written_border;
				return;

			}
		}
	}
	unp_write_area(written_border, unpack_data->unp_ptr);
	unpack_data->wr_ptr = unpack_data->unp_ptr;

}
//----------------------------------------------------------------
void Unrar::unp_write_area(unsigned int start_ptr, unsigned int end_ptr)
{
	if (end_ptr < start_ptr) {
		unp_write_data(&unpack_data->window[start_ptr], -start_ptr & MAXWINMASK);
		unp_write_data(unpack_data->window, end_ptr);
	} else {
		unp_write_data(&unpack_data->window[start_ptr], end_ptr-start_ptr);
	}
}
//----------------------------------------------------------------
void  Unrar::vm_set_memory(unsigned int pos, UINT8 *data, unsigned int data_size)
{
	if (pos<RARVM_MEMSIZE && data!=unpack_data->rarvm_data.mem+pos) 
	{
		memmove(unpack_data->rarvm_data.mem+pos, data, MIN(data_size, RARVM_MEMSIZE-pos));
	}
}
//----------------------------------------------------------------
int Unrar::vm_execute(struct rarvm_prepared_program *prg)
{
	unsigned int global_size, static_size, new_pos, new_size, data_size;
	struct rarvm_prepared_command *prepared_code;
	memcpy(unpack_data->rarvm_data.R, prg->init_r, sizeof(prg->init_r));
	global_size = MIN(prg->global_size, VM_GLOBALMEMSIZE);
	if (global_size) 
	{
		memcpy(unpack_data->rarvm_data.mem+VM_GLOBALMEMADDR, &prg->global_data[0], global_size);
	}
	static_size = MIN(prg->static_size, VM_GLOBALMEMSIZE-global_size);
	if (static_size) 
	{
		memcpy(unpack_data->rarvm_data.mem+VM_GLOBALMEMADDR+global_size,
			&prg->static_data[0], static_size);
	}

	unpack_data->rarvm_data.R[7] = RARVM_MEMSIZE;
	unpack_data->rarvm_data.Flags = 0;

	prepared_code=prg->alt_cmd ? prg->alt_cmd : &prg->cmd.array[0];
	if(!prepared_code) 
	{
		return FALSE;
	}
	if (vm_execute_code(prepared_code, prg->cmd_count) == FALSE) 
	{
		prepared_code[0].op_code = VM_RET;
	}
	new_pos = GET_VALUE(FALSE, &unpack_data->rarvm_data.mem[VM_GLOBALMEMADDR+0x20])&RARVM_MEMMASK;
	new_size = GET_VALUE(FALSE, &unpack_data->rarvm_data.mem[VM_GLOBALMEMADDR+0x1c])&RARVM_MEMMASK;
	if (new_pos+new_size >= RARVM_MEMSIZE) 
	{
		new_pos = new_size = 0;
	}
	prg->filtered_data = unpack_data->rarvm_data.mem + new_pos;
	prg->filtered_data_size = new_size;

	if (prg->global_data) 
	{
		SMHeapFree(prg->global_data);
		prg->global_data = NULL;
		prg->global_size = 0;
	}
	data_size = MIN(GET_VALUE(FALSE,
		(unsigned int *)&unpack_data->rarvm_data.mem[VM_GLOBALMEMADDR+0x30]),VM_GLOBALMEMSIZE);
	if (data_size != 0) 
	{
		prg->global_size += data_size+VM_FIXEDGLOBALSIZE;
		prg->global_data =(unsigned char *) rar_realloc2(prg->global_data, prg->global_size);
		if(!prg->global_data)
		{
			return FALSE;
		}
		memcpy(prg->global_data, &unpack_data->rarvm_data.mem[VM_GLOBALMEMADDR],
			data_size+VM_FIXEDGLOBALSIZE);
	}

	return TRUE;
}
BOOLEAN Unrar::vm_execute_code(struct rarvm_prepared_command *prepared_code, UINT32 code_size) 
{
	int max_ops=25000000, i, SP;
	struct rarvm_prepared_command *cmd;
	unsigned int value1, value2, result, divider, FC, *op1, *op2;
	const int reg_count=sizeof(unpack_data->rarvm_data.R)/sizeof(unpack_data->rarvm_data.R[0]);

	cmd = prepared_code;
	while (1) {
		if (cmd > (prepared_code + code_size))
		{
			return FALSE;
		}
		if (cmd < prepared_code) 
		{
			return FALSE;
		}
		op1 = rarvm_get_operand(&cmd->op1);
		op2 = rarvm_get_operand(&cmd->op2);
		switch(cmd->op_code) {
		case VM_MOV:
			SET_VALUE(cmd->byte_mode, op1, GET_VALUE(cmd->byte_mode, op2));
			break;
		case VM_MOVB:
			SET_VALUE(TRUE, op1, GET_VALUE(TRUE, op2));
			break;
		case VM_MOVD:
			SET_VALUE(FALSE, op1, GET_VALUE(FALSE, op2));
			break;
		case VM_CMP:
			value1 = GET_VALUE(cmd->byte_mode, op1);
			result = UINT32(value1 - GET_VALUE(cmd->byte_mode, op2));
			unpack_data->rarvm_data.Flags = result==0 ? VM_FZ : (result>value1)|(result&VM_FS);
			break;
		case VM_CMPB:
			value1 = GET_VALUE(TRUE, op1);
			result = UINT32(value1 - GET_VALUE(TRUE, op2));
			unpack_data->rarvm_data.Flags = result==0 ? VM_FZ : (result>value1)|(result&VM_FS);
			break;
		case VM_CMPD:
			value1 = GET_VALUE(FALSE, op1);
			result = UINT32(value1 - GET_VALUE(FALSE, op2));
			unpack_data->rarvm_data.Flags = result==0 ? VM_FZ : (result>value1)|(result&VM_FS);
			break;
		case VM_ADD:
			value1 = GET_VALUE(cmd->byte_mode, op1);
			result = UINT32(value1 + GET_VALUE(cmd->byte_mode, op2));
			unpack_data->rarvm_data.Flags = result==0 ? VM_FZ : (result<value1)|(result&VM_FS);
			SET_VALUE(cmd->byte_mode, op1, result);
			break;
		case VM_ADDB:
			SET_VALUE(TRUE, op1, GET_VALUE(TRUE, op1)+GET_VALUE(TRUE, op2));
			break;
		case VM_ADDD:
			SET_VALUE(FALSE, op1, GET_VALUE(FALSE, op1)+GET_VALUE(FALSE, op2));
			break;
		case VM_SUB:
			value1 = GET_VALUE(cmd->byte_mode, op1);
			result = UINT32(value1 - GET_VALUE(cmd->byte_mode, op2));
			unpack_data->rarvm_data.Flags = result==0 ? VM_FZ : (result>value1)|(result&VM_FS);
			SET_VALUE(cmd->byte_mode, op1, result);
			break;
		case VM_SUBB:
			SET_VALUE(TRUE, op1, GET_VALUE(TRUE, op1)-GET_VALUE(TRUE, op2));
			break;
		case VM_SUBD:
			SET_VALUE(FALSE, op1, GET_VALUE(FALSE, op1)-GET_VALUE(FALSE, op2));
			break;
		case VM_JZ:
			if ((unpack_data->rarvm_data.Flags & VM_FZ) != 0) {
				SET_IP(GET_VALUE(FALSE, op1));
				continue;
			}
			break;
		case VM_JNZ:
			if ((unpack_data->rarvm_data.Flags & VM_FZ) == 0) {
				SET_IP(GET_VALUE(FALSE, op1));
				continue;
			}
			break;
		case VM_INC:
			result = UINT32(GET_VALUE(cmd->byte_mode, op1)+1);
			SET_VALUE(cmd->byte_mode, op1, result);
			unpack_data->rarvm_data.Flags = result==0 ? VM_FZ : result&VM_FS;
			break;
		case VM_INCB:
			SET_VALUE(TRUE, op1, GET_VALUE(TRUE, op1)+1);
			break;
		case VM_INCD:
			SET_VALUE(FALSE, op1, GET_VALUE(FALSE, op1)+1);
			break;
		case VM_DEC:
			result = UINT32(GET_VALUE(cmd->byte_mode, op1)-1);
			SET_VALUE(cmd->byte_mode, op1, result);
			unpack_data->rarvm_data.Flags = result==0 ? VM_FZ : result&VM_FS;
			break;
		case VM_DECB:
			SET_VALUE(TRUE, op1, GET_VALUE(TRUE, op1)-1);
			break;
		case VM_DECD:
			SET_VALUE(FALSE, op1, GET_VALUE(FALSE, op1)-1);
			break;
		case VM_JMP:
			SET_IP(GET_VALUE(FALSE, op1));
			continue;
		case VM_XOR:
			result = UINT32(GET_VALUE(cmd->byte_mode, op1)^GET_VALUE(cmd->byte_mode, op2));
			unpack_data->rarvm_data.Flags = result==0 ? VM_FZ : result&VM_FS;
			SET_VALUE(cmd->byte_mode, op1, result);
			break;
		case VM_AND:
			result = UINT32(GET_VALUE(cmd->byte_mode, op1)&GET_VALUE(cmd->byte_mode, op2));
			unpack_data->rarvm_data.Flags = result==0 ? VM_FZ : result&VM_FS;
			SET_VALUE(cmd->byte_mode, op1, result);
			break;
		case VM_OR:
			result = UINT32(GET_VALUE(cmd->byte_mode, op1)|GET_VALUE(cmd->byte_mode, op2));
			unpack_data->rarvm_data.Flags = result==0 ? VM_FZ : result&VM_FS;
			SET_VALUE(cmd->byte_mode, op1, result);
			break;
		case VM_TEST:
			result = UINT32(GET_VALUE(cmd->byte_mode, op1)&GET_VALUE(cmd->byte_mode, op2));
			unpack_data->rarvm_data.Flags = result==0 ? VM_FZ : result&VM_FS;
			break;
		case VM_JS:
			if ((unpack_data->rarvm_data.Flags & VM_FS) != 0) {
				SET_IP(GET_VALUE(FALSE, op1));
				continue;
			}
			break;
		case VM_JNS:
			if ((unpack_data->rarvm_data.Flags & VM_FS) == 0) {
				SET_IP(GET_VALUE(FALSE, op1));
				continue;
			}
			break;
		case VM_JB:
			if ((unpack_data->rarvm_data.Flags & VM_FC) != 0) {
				SET_IP(GET_VALUE(FALSE, op1));
				continue;
			}
			break;
		case VM_JBE:
			if ((unpack_data->rarvm_data.Flags & (VM_FC|VM_FZ)) != 0) {
				SET_IP(GET_VALUE(FALSE, op1));
				continue;
			}
			break;
		case VM_JA:
			if ((unpack_data->rarvm_data.Flags & (VM_FC|VM_FZ)) == 0) {
				SET_IP(GET_VALUE(FALSE, op1));
				continue;
			}
			break;
		case VM_JAE:
			if ((unpack_data->rarvm_data.Flags & VM_FC) == 0) {
				SET_IP(GET_VALUE(FALSE, op1));
				continue;
			}
			break;
		case VM_PUSH:
			unpack_data->rarvm_data.R[7] -= 4;
			SET_VALUE(FALSE, (unsigned int *)&unpack_data->rarvm_data.mem[unpack_data->rarvm_data.R[7] &
				RARVM_MEMMASK],	GET_VALUE(FALSE, op1));
			break;
		case VM_POP:
			SET_VALUE(FALSE, op1, GET_VALUE(FALSE,
				(unsigned int *)&unpack_data->rarvm_data.mem[unpack_data->rarvm_data.R[7] & RARVM_MEMMASK]));
			unpack_data->rarvm_data.R[7] += 4;
			break;
		case VM_CALL:
			unpack_data->rarvm_data.R[7] -= 4;
			SET_VALUE(FALSE, (unsigned int *)&unpack_data->rarvm_data.mem[unpack_data->rarvm_data.R[7] &
				RARVM_MEMMASK], cmd-prepared_code+1);
			SET_IP(GET_VALUE(FALSE, op1));
			continue;
		case VM_NOT:
			SET_VALUE(cmd->byte_mode, op1, ~GET_VALUE(cmd->byte_mode, op1));
			break;
		case VM_SHL:
			value1 = GET_VALUE(cmd->byte_mode, op1);
			value2 = GET_VALUE(cmd->byte_mode, op1);
			result = UINT32(value1 << value2);
			unpack_data->rarvm_data.Flags = (result==0 ? VM_FZ : (result&VM_FS))|
				((value1 << (value2-1))&0x80000000 ? VM_FC:0);
			SET_VALUE(cmd->byte_mode, op1, result);
			break;
		case VM_SHR:
			value1 = GET_VALUE(cmd->byte_mode, op1);
			value2 = GET_VALUE(cmd->byte_mode, op1);
			result = UINT32(value1 >> value2);
			unpack_data->rarvm_data.Flags = (result==0 ? VM_FZ : (result&VM_FS))|
				((value1 >> (value2-1)) & VM_FC);
			SET_VALUE(cmd->byte_mode, op1, result);
			break;
		case VM_SAR:
			value1 = GET_VALUE(cmd->byte_mode, op1);
			value2 = GET_VALUE(cmd->byte_mode, op1);
			result = UINT32(((int)value1) >> value2);
			unpack_data->rarvm_data.Flags = (result==0 ? VM_FZ : (result&VM_FS))|
				((value1 >> (value2-1)) & VM_FC);
			SET_VALUE(cmd->byte_mode, op1, result);
			break;
		case VM_NEG:
			result = UINT32(-GET_VALUE(cmd->byte_mode, op1));
			unpack_data->rarvm_data.Flags = result==0 ? VM_FZ:VM_FC|(result&VM_FS);
			SET_VALUE(cmd->byte_mode, op1, result);
			break;
		case VM_NEGB:
			SET_VALUE(TRUE, op1, -GET_VALUE(TRUE, op1));
			break;
		case VM_NEGD:
			SET_VALUE(FALSE, op1, -GET_VALUE(FALSE, op1));
			break;
		case VM_PUSHA:
			for (i=0, SP=unpack_data->rarvm_data.R[7]-4 ; i<reg_count ; i++, SP-=4) {
				SET_VALUE(FALSE,
					(unsigned int *)&unpack_data->rarvm_data.mem[SP & RARVM_MEMMASK],
					unpack_data->rarvm_data.R[i]);
			}
			unpack_data->rarvm_data.R[7] -= reg_count*4;
			break;
		case VM_POPA:
			for (i=0,SP=unpack_data->rarvm_data.R[7] ; i<reg_count ; i++, SP+=4) {
				unpack_data->rarvm_data.R[7-i] = GET_VALUE(FALSE,
					(unsigned int *)&unpack_data->rarvm_data.mem[SP & RARVM_MEMMASK]);
			}
			break;
		case VM_PUSHF:
			unpack_data->rarvm_data.R[7] -= 4;
			SET_VALUE(FALSE,
				(unsigned int *)&unpack_data->rarvm_data.mem[unpack_data->rarvm_data.R[7] & RARVM_MEMMASK],
				unpack_data->rarvm_data.Flags);
			break;
		case VM_POPF:
			unpack_data->rarvm_data.Flags = GET_VALUE(FALSE,
				(unsigned int *)&unpack_data->rarvm_data.mem[unpack_data->rarvm_data.R[7] & RARVM_MEMMASK]);
			unpack_data->rarvm_data.R[7] += 4;
			break;
		case VM_MOVZX:
			SET_VALUE(FALSE, op1, GET_VALUE(TRUE, op2));
			break;
		case VM_MOVSX:
			SET_VALUE(FALSE, op1, (signed char)GET_VALUE(TRUE, op2));
			break;
		case VM_XCHG:
			value1 = GET_VALUE(cmd->byte_mode, op1);
			SET_VALUE(cmd->byte_mode, op1, GET_VALUE(cmd->byte_mode, op2));
			SET_VALUE(cmd->byte_mode, op2, value1);
			break;
		case VM_MUL:
			result = GET_VALUE(cmd->byte_mode, op1) * GET_VALUE(cmd->byte_mode, op2);
			SET_VALUE(cmd->byte_mode, op1, result);
			break;
		case VM_DIV:
			divider = GET_VALUE(cmd->byte_mode, op2);
			if (divider != 0) {
				result = GET_VALUE(cmd->byte_mode, op1) / divider;
				SET_VALUE(cmd->byte_mode, op1, result);
			}
			break;
		case VM_ADC:
			value1 = GET_VALUE(cmd->byte_mode, op1);
			FC = (unpack_data->rarvm_data.Flags & VM_FC);
			result = UINT32(value1+GET_VALUE(cmd->byte_mode, op2)+FC);
			unpack_data->rarvm_data.Flags = result==0 ? VM_FZ:(result<value1 ||
				(result==value1 && FC))|(result&VM_FS);
			SET_VALUE(cmd->byte_mode, op1, result);
			break;
		case VM_SBB:
			value1 = GET_VALUE(cmd->byte_mode, op1);
			FC = (unpack_data->rarvm_data.Flags & VM_FC);
			result = UINT32(value1-GET_VALUE(cmd->byte_mode, op2)-FC);
			unpack_data->rarvm_data.Flags = result==0 ? VM_FZ:(result>value1 ||
				(result==value1 && FC))|(result&VM_FS);
			SET_VALUE(cmd->byte_mode, op1, result);
			break;
		case VM_RET:
			if (unpack_data->rarvm_data.R[7] >= RARVM_MEMSIZE) {
				return TRUE;
			}
			SET_IP(GET_VALUE(FALSE, (unsigned int *)&unpack_data->rarvm_data.mem[unpack_data->rarvm_data.R[7] &
				RARVM_MEMMASK]));
			unpack_data->rarvm_data.R[7] += 4;
			continue;
		case VM_STANDARD:
			execute_standard_filter((rarvm_standard_filters_t)cmd->op1.data);
			break;
		case VM_PRINT:
			break;
		}
		cmd++;
		--max_ops;
	}

}
unsigned int * Unrar::rarvm_get_operand(struct rarvm_prepared_operand *cmd_op)
{
	if (cmd_op->type == VM_OPREGMEM) {
		return ((unsigned int *)&unpack_data->rarvm_data.mem[(*cmd_op->addr+cmd_op->base) & RARVM_MEMMASK]);
	} else {
		return cmd_op->addr;
	}
}
void Unrar::execute_standard_filter(rarvm_standard_filters_t filter_type)
{
	unsigned char *data, cmp_byte2, cur_byte, *src_data, *dest_data;
	int i, j, data_size, channels, src_pos, dest_pos, border, width, PosR;
	int op_type, cur_channel, byte_count, start_pos, pa, pb, pc;
	unsigned int file_offset, cur_pos, predicted;
	__int32 offset, addr;
	const int file_size=0x1000000;

	switch(filter_type) {
	case VMSF_E8:
	case VMSF_E8E9:
		data=unpack_data->rarvm_data.mem;
		data_size = unpack_data->rarvm_data.R[4];
		file_offset = unpack_data->rarvm_data.R[6];

		if (((unsigned int)data_size >= VM_GLOBALMEMADDR) || (data_size < 4)) {
			break;
		}

		cmp_byte2 = filter_type==VMSF_E8E9 ? 0xe9:0xe8;
		for (cur_pos = 0 ; cur_pos < data_size-4 ; ) {
			cur_byte = *(data++);
			cur_pos++;
			if (cur_byte==0xe8 || cur_byte==cmp_byte2) {
				offset = cur_pos+file_offset;
				addr = GET_VALUE(FALSE, data);
				if (addr < 0) {
					if (addr+offset >=0 ) {
						SET_VALUE(FALSE, data, addr+file_size);
					}
				} else {
					if (addr<file_size) {
						SET_VALUE(FALSE, data, addr-offset);
					}
				}
				data += 4;
				cur_pos += 4;
			}
		}
		break;
	case VMSF_ITANIUM:
		data=unpack_data->rarvm_data.mem;
		data_size = unpack_data->rarvm_data.R[4];
		file_offset = unpack_data->rarvm_data.R[6];

		if (((unsigned int)data_size >= VM_GLOBALMEMADDR) || (data_size < 21)) {
			break;
		}

		cur_pos = 0;

		file_offset>>=4;

		while (cur_pos < data_size-21) {
			int Byte = (data[0] & 0x1f) - 0x10;
			if (Byte >= 0) {
				static unsigned char masks[16]={4,4,6,6,0,0,7,7,4,4,0,0,4,4,0,0};
				unsigned char cmd_mask = masks[Byte];

				if (cmd_mask != 0) {
					for (i=0 ; i <= 2 ; i++) {
						if (cmd_mask & (1<<i)) {
							start_pos = i*41+5;
							op_type = filter_itanium_getbits(data,
								start_pos+37, 4);
							if (op_type == 5) {
								offset = filter_itanium_getbits(data,
									start_pos+13, 20);
								filter_itanium_setbits(data,
									(offset-file_offset)
									&0xfffff,start_pos+13,20);
							}
						}
					}
				}
			}
			data += 16;
			cur_pos += 16;
			file_offset++;
		}
		break;
	case VMSF_DELTA:
		data_size = unpack_data->rarvm_data.R[4];
		channels = unpack_data->rarvm_data.R[0];
		src_pos = 0;
		border = data_size*2;

		SET_VALUE(FALSE, &unpack_data->rarvm_data.mem[VM_GLOBALMEMADDR+0x20], data_size);
		if ((unsigned int)data_size >= VM_GLOBALMEMADDR/2) {
			break;
		}
		for (cur_channel=0 ; cur_channel < channels ; cur_channel++) {
			unsigned char prev_byte = 0;
			for (dest_pos=data_size+cur_channel ; dest_pos<border ; dest_pos+=channels) {
				unpack_data->rarvm_data.mem[dest_pos] = (prev_byte -= unpack_data->rarvm_data.mem[src_pos++]);
			}
		}
		break;
	case VMSF_RGB: {
		const int channels=3;
		data_size = unpack_data->rarvm_data.R[4];
		width = unpack_data->rarvm_data.R[0] - 3;
		PosR = unpack_data->rarvm_data.R[1];
		src_data = unpack_data->rarvm_data.mem;
		dest_data = src_data + data_size;

		SET_VALUE(FALSE, &unpack_data->rarvm_data.mem[VM_GLOBALMEMADDR+0x20], data_size);
		if ((unsigned int)data_size >= VM_GLOBALMEMADDR/2) {
			break;
		}
		for (cur_channel=0 ; cur_channel < channels; cur_channel++) {
			unsigned int prev_byte = 0;
			for (i=cur_channel ; i<data_size ; i+=channels) {
				int upper_pos=i-width;
				if (upper_pos >= 3) {
					unsigned char *upper_data = dest_data+upper_pos;
					unsigned int upper_byte = *upper_data;
					unsigned int upper_left_byte = *(upper_data-3);
					predicted = prev_byte+upper_byte-upper_left_byte;
					pa = abs((int)(predicted-prev_byte));
					pb = abs((int)(predicted-upper_byte));
					pc = abs((int)(predicted-upper_left_byte));
					if (pa <= pb && pa <= pc) {
						predicted = prev_byte;
					} else {
						if (pb <= pc) {
							predicted = upper_byte;
						} else {
							predicted = upper_left_byte;
						}
					}
				} else {
					predicted = prev_byte;
				}
				dest_data[i] = prev_byte = (unsigned char)(predicted-*(src_data++));
			}
		}
		for (i=PosR,border=data_size-2 ; i < border ; i+=3) {
			unsigned char g=dest_data[i+1];
			dest_data[i] += g;
			dest_data[i+2] += g;
		}
		break;
				   }
	case VMSF_AUDIO: {
		int channels=unpack_data->rarvm_data.R[0];
		data_size = unpack_data->rarvm_data.R[4];
		src_data = unpack_data->rarvm_data.mem;
		dest_data = src_data + data_size;

		SET_VALUE(FALSE, &unpack_data->rarvm_data.mem[VM_GLOBALMEMADDR+0x20], data_size);
		if ((unsigned int)data_size >= VM_GLOBALMEMADDR/2) {
			break;
		}
		for (cur_channel=0 ; cur_channel < channels ; cur_channel++) {
			unsigned int prev_byte = 0, prev_delta=0, Dif[7];
			int D, D1=0, D2=0, D3=0, K1=0, K2=0, K3=0;

			memset(Dif, 0, sizeof(Dif));

			for (i=cur_channel, byte_count=0 ; i<data_size ; i+=channels, byte_count++) {
				D3=D2;
				D2 = prev_delta-D1;
				D1 = prev_delta;

				predicted = 8*prev_byte+K1*D1+K2*D2+K3*D3;
				predicted = (predicted>>3) & 0xff;

				cur_byte = *(src_data++);

				predicted -= cur_byte;
				dest_data[i] = predicted;
				prev_delta = (signed char)(predicted-prev_byte);
				prev_byte = predicted;

				D=((signed char)cur_byte) << 3;

				Dif[0] += abs(D);
				Dif[1] += abs(D-D1);
				Dif[2] += abs(D+D1);
				Dif[3] += abs(D-D2);
				Dif[4] += abs(D+D2);
				Dif[5] += abs(D-D3);
				Dif[6] += abs(D+D3);

				if ((byte_count & 0x1f) == 0) {
					unsigned int min_dif=Dif[0], num_min_dif=0;
					Dif[0]=0;
					for (j=1 ; j<sizeof(Dif)/sizeof(Dif[0]) ; j++) {
						if (Dif[j] < min_dif) {
							min_dif = Dif[j];
							num_min_dif = j;
						}
						Dif[j]=0;
					}
					switch(num_min_dif) {
	case 1: if (K1>=-16) K1--; break;
	case 2: if (K1 < 16) K1++; break;
	case 3: if (K2>=-16) K2--; break;
	case 4: if (K2 < 16) K2++; break;
	case 5: if (K3>=-16) K3--; break;
	case 6: if (K3 < 16) K3++; break;
					}
				}
			}
		}
		break;
					 }
	case VMSF_UPCASE:
		data_size = unpack_data->rarvm_data.R[4];
		src_pos = 0;
		dest_pos = data_size;
		if ((unsigned int)data_size >= VM_GLOBALMEMADDR/2) {
			break;
		}
		while (src_pos < data_size) {
			cur_byte = unpack_data->rarvm_data.mem[src_pos++];
			if (cur_byte==2 && (cur_byte=unpack_data->rarvm_data.mem[src_pos++]) != 2) {
				cur_byte -= 32;
			}
			unpack_data->rarvm_data.mem[dest_pos++]=cur_byte;
		}
		SET_VALUE(FALSE, &unpack_data->rarvm_data.mem[VM_GLOBALMEMADDR+0x1c], dest_pos-data_size);
		SET_VALUE(FALSE, &unpack_data->rarvm_data.mem[VM_GLOBALMEMADDR+0x20], data_size);
		break;
	default: 
		break;
	}
	
}
unsigned int Unrar::filter_itanium_getbits(unsigned char *data, int bit_pos, int bit_count)
{
	int in_addr=bit_pos/8;
	int in_bit=bit_pos&7;
	unsigned int bit_field=(unsigned int)data[in_addr++];
	bit_field|=(unsigned int)data[in_addr++] << 8;
	bit_field|=(unsigned int)data[in_addr++] << 16;
	bit_field|=(unsigned int)data[in_addr] << 24;
	bit_field >>= in_bit;
	return(bit_field & (0xffffffff>>(32-bit_count)));
}
void Unrar::filter_itanium_setbits(unsigned char *data, unsigned int bit_field, int bit_pos, int bit_count)
{
	int i, in_addr=bit_pos/8;
	int in_bit=bit_pos&7;
	unsigned int and_mask=0xffffffff>>(32-bit_count);
	and_mask=~(and_mask<<in_bit);

	bit_field<<=in_bit;

	for (i=0 ; i<4 ; i++) {
		data[in_addr+i]&=and_mask;
		data[in_addr+i]|=bit_field;
		and_mask=(and_mask>>8)|0xff000000;
		bit_field>>=8;
	}
}
void *Unrar::rar_realloc2(void *ptr, size_t size)

{
	void *alloc;
	if(!size || size > RAR_MAX_ALLOCATION)
	{
		return NULL;
	}

	return SMRealloc(alloc, size, ptr);
}
void Unrar::execute_code(struct rarvm_prepared_program *prg)
{
	if (prg->global_size > 0) {
		prg->init_r[6] = int64to32(unpack_data->written_size);
		vm_set_value(FALSE, (unsigned int *)&prg->global_data[0x24],
			int64to32(unpack_data->written_size));
		vm_set_value(FALSE, (unsigned int *)&prg->global_data[0x28],
			int64to32(unpack_data->written_size>>32));
		vm_execute(prg);
	}
}
void Unrar::vm_set_value(int byte_mode, unsigned int *addr, unsigned int value)
{
	if (byte_mode) {
		*(unsigned char *)addr=value;
	} else {
		*(UINT32 *)addr = value;
	}
}
void Unrar::filter_delete(int i)
{
	if (unpack_data->PrgStack.array[i]->prg.global_data) {
		SMHeapFree(unpack_data->PrgStack.array[i]->prg.global_data);
	}
	if (unpack_data->PrgStack.array[i]->prg.static_data) {
		SMHeapFree(unpack_data->PrgStack.array[i]->prg.static_data);
	}
	if (unpack_data->PrgStack.array[i]->prg.cmd.array) {
		SMHeapFree(unpack_data->PrgStack.array[i]->prg.cmd.array);
	}
	unpack_data->PrgStack.array[i]->prg.cmd.array = NULL;
	unpack_data->PrgStack.array[i]->prg.cmd.num_items = 0;
	SMHeapFree(unpack_data->PrgStack.array[i]);
}
int Unrar::ppm_decode_char()
{
	int symbol;

	if ((UINT8 *) unpack_data->ppm_data.min_context <= unpack_data->ppm_data.sub_alloc.ptext ||
		(UINT8 *)unpack_data->ppm_data.min_context > unpack_data->ppm_data.sub_alloc.heap_end) 
	{
			return -1;
	}
	if (unpack_data->ppm_data.min_context->num_stats != 1) 
	{
		if ((UINT8 *) unpack_data->ppm_data.min_context->con_ut.u.stats <= unpack_data->ppm_data.sub_alloc.ptext ||
			(UINT8 *) unpack_data->ppm_data.min_context->con_ut.u.stats > unpack_data->ppm_data.sub_alloc.heap_end) {
				return -1;
		}
		if (ppm_decode_symbol1() == FALSE) {
			return -1;
		}
	} else {
		ppm_decode_bin_symbol();
	}
	coder_decode();
	while (!unpack_data->ppm_data.found_state)
	{
		ARI_DEC_NORMALISE(unpack_data->ppm_data.coder.code,	unpack_data->ppm_data.coder.low, unpack_data->ppm_data.coder.range);
		do {
			unpack_data->ppm_data.order_fall++;
			unpack_data->ppm_data.min_context = unpack_data->ppm_data.min_context->suffix;
			if ((UINT8 *)unpack_data->ppm_data.min_context <= unpack_data->ppm_data.sub_alloc.ptext ||
				(UINT8 *)unpack_data->ppm_data.min_context >
				unpack_data->ppm_data.sub_alloc.heap_end)
			{
					return -1;
			}
		} while (unpack_data->ppm_data.min_context->num_stats == unpack_data->ppm_data.num_masked);
		if (!ppm_decode_symbol2()) {
			return -1;
		}
		coder_decode();
	}

	symbol = unpack_data->ppm_data.found_state->symbol;
	if (!unpack_data->ppm_data.order_fall && (UINT8*) unpack_data->ppm_data.found_state->successor > unpack_data->ppm_data.sub_alloc.ptext) {
		unpack_data->ppm_data.min_context = unpack_data->ppm_data.max_context = unpack_data->ppm_data.found_state->successor;
	} else {
		if(!update_model()) {
			return -1;
		}

		if (unpack_data->ppm_data.esc_count == 0) {
			clear_mask();
		}
	}
	ARI_DEC_NORMALISE(unpack_data->ppm_data.coder.code,	unpack_data->ppm_data.coder.low, unpack_data->ppm_data.coder.range);
	return symbol;
}
BOOLEAN Unrar::ppm_decode_symbol1()
{
	struct state_tag *p;
	int i, hi_cnt, count;

	unpack_data->ppm_data.coder.scale = unpack_data->ppm_data.min_context->con_ut.u.summ_freq;
	p = unpack_data->ppm_data.min_context->con_ut.u.stats;
	count = coder_get_current_count();
	if (count >= (signed)unpack_data->ppm_data.coder.scale)
	{
		return FALSE;
	}
	if (count < (hi_cnt = p->freq)) {
		unpack_data->ppm_data.prev_success = (2 * (unpack_data->ppm_data.coder.high_count=hi_cnt) >
			unpack_data->ppm_data.coder.scale);
		unpack_data->ppm_data.run_length += unpack_data->ppm_data.prev_success;
		(unpack_data->ppm_data.found_state=p)->freq=(hi_cnt += 4);
		unpack_data->ppm_data.min_context->con_ut.u.summ_freq += 4;
		if (hi_cnt > MAX_FREQ)
		{
			rescale();
		}
		unpack_data->ppm_data.coder.low_count = 0;
		return TRUE;
	} else if (unpack_data->ppm_data.found_state == NULL) {
		return FALSE;
	}
	unpack_data->ppm_data.prev_success = 0;
	i = unpack_data->ppm_data.min_context->num_stats-1;
	while ((hi_cnt += (++p)->freq) <= count) {
		if (--i == 0) {
			unpack_data->ppm_data.hi_bits_flag = unpack_data->ppm_data.hb2flag[unpack_data->ppm_data.found_state->symbol];
			unpack_data->ppm_data.coder.low_count = hi_cnt;
			unpack_data->ppm_data.char_mask[p->symbol] = unpack_data->ppm_data.esc_count;
			i = (unpack_data->ppm_data.num_masked=unpack_data->ppm_data.min_context->num_stats) - 1;
			unpack_data->ppm_data.found_state = NULL;
			do {
				unpack_data->ppm_data.char_mask[(--p)->symbol] = unpack_data->ppm_data.esc_count;
			} while (--i);
			unpack_data->ppm_data.coder.high_count = unpack_data->ppm_data.coder.scale;
			return TRUE;
		}
	}
	unpack_data->ppm_data.coder.low_count = (unpack_data->ppm_data.coder.high_count = hi_cnt) - p->freq;
	update1(p);
	return TRUE;
}
void Unrar::rescale() 
{
	int old_ns, i, adder, esc_freq, n0, n1;
	struct state_tag *p1, *p;

	old_ns = unpack_data->ppm_data.min_context->num_stats;
	i = unpack_data->ppm_data.min_context->num_stats-1;
	for (p=unpack_data->ppm_data.found_state ; p != unpack_data->ppm_data.min_context->con_ut.u.stats ; p--) 
	{
		ppmd_swap(&p[0], &p[-1]);
	}
	unpack_data->ppm_data.min_context->con_ut.u.stats->freq += 4;
	unpack_data->ppm_data.min_context->con_ut.u.summ_freq += 4;
	esc_freq = unpack_data->ppm_data.min_context->con_ut.u.summ_freq - p->freq;
	adder = (unpack_data->ppm_data.order_fall != 0);
	unpack_data->ppm_data.min_context->con_ut.u.summ_freq = (p->freq = (p->freq+adder) >> 1);
	do {
		esc_freq -= (++p)->freq;
		unpack_data->ppm_data.min_context->con_ut.u.summ_freq += (p->freq = (p->freq + adder) >> 1);
		if (p[0].freq > p[-1].freq) {
			struct state_tag tmp = *(p1=p);
			do {
				p1[0] = p1[-1];
			} while (--p1 != unpack_data->ppm_data.min_context->con_ut.u.stats && tmp.freq > p1[-1].freq);
			*p1 = tmp;
		}
	} while (--i);

	if (p->freq == 0) {
		do {
			i++;
		} while ((--p)->freq == 0);
		esc_freq += i;
		if ((unpack_data->ppm_data.min_context->num_stats -= i) == 1) {
			struct state_tag tmp = *unpack_data->ppm_data.min_context->con_ut.u.stats;
			do {
				tmp.freq -= (tmp.freq >> 1);
				esc_freq >>= 1;
			} while (esc_freq > 1);
			sub_allocator_insert_node(unpack_data->ppm_data.min_context->con_ut.u.stats, unpack_data->ppm_data.sub_alloc.units2indx[((old_ns+1)>>1)-1]);
			*(unpack_data->ppm_data.found_state=&unpack_data->ppm_data.min_context->con_ut.one_state)=tmp;
			return;
		}
	}
	unpack_data->ppm_data.min_context->con_ut.u.summ_freq += (esc_freq -= (esc_freq >> 1));
	n0 = (old_ns+1) >> 1;
	n1 = (unpack_data->ppm_data.min_context->num_stats+1) >> 1;
	if (n0 != n1) {
		unpack_data->ppm_data.min_context->con_ut.u.stats = (struct state_tag *) sub_allocator_shrink_units(unpack_data->ppm_data.min_context->con_ut.u.stats, n0, n1);
	}
	unpack_data->ppm_data.found_state = unpack_data->ppm_data.min_context->con_ut.u.stats;

}
void Unrar::ppmd_swap(struct state_tag *p0, struct state_tag *p1)
{
	struct state_tag tmp;

	tmp = *p0;
	*p0 = *p1;
	*p1 = tmp;
}
void Unrar::sub_allocator_insert_node(void *p, int index)
{
	((struct rar_node *) p)->next = unpack_data->ppm_data.sub_alloc.free_list[index].next;
	unpack_data->ppm_data.sub_alloc.free_list[index].next = (struct rar_node *) p;
}
void *Unrar::sub_allocator_shrink_units (void *old_ptr, int old_nu, int new_nu) 
{

	int i0, i1;
	void *ptr;

	i0 = unpack_data->ppm_data.sub_alloc.units2indx[old_nu-1];
	i1 = unpack_data->ppm_data.sub_alloc.units2indx[new_nu-1];
	if (i0 == i1) {
		return old_ptr;
	}
	if (unpack_data->ppm_data.sub_alloc.free_list[i1].next) {
		ptr = sub_allocator_remove_node(i1);
		memcpy(ptr, old_ptr, UNIT_SIZE*(new_nu));
		sub_allocator_insert_node(old_ptr, i0);
		return ptr;
	} else {
		sub_allocator_split_block(old_ptr, i0, i1);
		return old_ptr;
	}

}
void Unrar::update1(Unrar::state_tag *p) 
{
	(unpack_data->ppm_data.found_state=p)->freq += 4;
	unpack_data->ppm_data.min_context->con_ut.u.summ_freq += 4;
	if (p[0].freq > p[-1].freq) {
		ppmd_swap(&p[0], &p[-1]);
		unpack_data->ppm_data.found_state = --p;
		if (p->freq > MAX_FREQ) {
			rescale();
		}
	}
}
void Unrar::ppm_decode_bin_symbol()
{
	struct state_tag *rs;
	UINT16 *bs;

	rs = &unpack_data->ppm_data.min_context->con_ut.one_state;

	unpack_data->ppm_data.hi_bits_flag = unpack_data->ppm_data.hb2flag[unpack_data->ppm_data.found_state->symbol];
	bs = &unpack_data->ppm_data.bin_summ[rs->freq-1][unpack_data->ppm_data.prev_success +
		unpack_data->ppm_data.ns2bsindx[unpack_data->ppm_data.min_context->suffix->num_stats-1] +
		unpack_data->ppm_data.hi_bits_flag+2*unpack_data->ppm_data.hb2flag[rs->symbol] +
		((unpack_data->ppm_data.run_length >> 26) & 0x20)];
	if (coder_get_current_shift_count(&unpack_data->ppm_data.coder, TOT_BITS) < *bs) {
		unpack_data->ppm_data.found_state = rs;
		rs->freq += (rs->freq < 128);
		unpack_data->ppm_data.coder.low_count = 0;
		unpack_data->ppm_data.coder.high_count = *bs;
		*bs = (UINT16) (*bs + INTERVAL - GET_MEAN(*bs, PERIOD_BITS, 2));
		unpack_data->ppm_data.prev_success = 1;
		unpack_data->ppm_data.run_length++;
	} else {
		unpack_data->ppm_data.coder.low_count = *bs;
		*bs = (UINT16) (*bs - GET_MEAN(*bs, PERIOD_BITS, 2));
		unpack_data->ppm_data.coder.high_count = BIN_SCALE;
		unpack_data->ppm_data.init_esc = ExpEscape[*bs >> 10];
		unpack_data->ppm_data.num_masked = 1;
		unpack_data->ppm_data.char_mask[rs->symbol] = unpack_data->ppm_data.esc_count;
		unpack_data->ppm_data.prev_success = 0;
		unpack_data->ppm_data.found_state = NULL;
	}
}
unsigned int  Unrar::coder_get_current_shift_count(range_coder_t *coder, unsigned int shift) 
{
	return (coder->code - coder->low) / (coder->range >>= shift);
}
void Unrar::coder_decode()
{
	unpack_data->ppm_data.coder.low += unpack_data->ppm_data.coder.range * unpack_data->ppm_data.coder.low_count;
	unpack_data->ppm_data.coder.range *= unpack_data->ppm_data.coder.high_count - unpack_data->ppm_data.coder.low_count;
}
BOOLEAN Unrar::ppm_decode_symbol2() 
{
	int count, hi_cnt, i;
	see2_context_tag *psee2c;
	state_tag *ps[256], **pps, *p;

	
	i = unpack_data->ppm_data.min_context->num_stats - unpack_data->ppm_data.num_masked;
	psee2c = make_esc_freq(i);
	pps = ps;
	p = unpack_data->ppm_data.min_context->con_ut.u.stats - 1;
	hi_cnt = 0;

	do {
		do {
			p++;
		} while (unpack_data->ppm_data.char_mask[p->symbol] == unpack_data->ppm_data.esc_count);
		hi_cnt += p->freq;
		*pps++ = p;
	} while (--i);
	unpack_data->ppm_data.coder.scale += hi_cnt;
	count = coder_get_current_count();
	if (count >= unpack_data->ppm_data.coder.scale) {
		return FALSE;
	}
	p=*(pps=ps);
	if (count < hi_cnt) {
		hi_cnt = 0;
		while ((hi_cnt += p->freq) <= count) {
			p=*++pps;
		}
		unpack_data->ppm_data.coder.low_count = (unpack_data->ppm_data.coder.high_count=hi_cnt) - p->freq;
		update(psee2c);
		update2(p);
	} else {
		unpack_data->ppm_data.coder.low_count = hi_cnt;
		unpack_data->ppm_data.coder.high_count = unpack_data->ppm_data.coder.scale;
		i = unpack_data->ppm_data.min_context->num_stats - unpack_data->ppm_data.num_masked;
		pps--;
		do {
			unpack_data->ppm_data.char_mask[(*++pps)->symbol] = unpack_data->ppm_data.esc_count;
		} while (--i);
		psee2c->summ += unpack_data->ppm_data.coder.scale;
		unpack_data->ppm_data.num_masked = unpack_data->ppm_data.min_context->num_stats;
	}
	return TRUE;
}
int Unrar::coder_get_current_count() 
{
	return (unpack_data->ppm_data.coder.code - unpack_data->ppm_data.coder.low) / (unpack_data->ppm_data.coder.range /= unpack_data->ppm_data.coder.scale);
}
Unrar::see2_context_tag * Unrar::make_esc_freq(int diff)
{
	struct see2_context_tag *psee2c;

	if (unpack_data->ppm_data.min_context->num_stats != 256) {
		psee2c = unpack_data->ppm_data.see2cont[unpack_data->ppm_data.ns2indx[diff-1]] +
			(diff < unpack_data->ppm_data.min_context->suffix->num_stats-unpack_data->ppm_data.min_context->num_stats) +
			2 * (unpack_data->ppm_data.min_context->con_ut.u.summ_freq < 11*unpack_data->ppm_data.min_context->num_stats)+4*
			(unpack_data->ppm_data.num_masked > diff) +	unpack_data->ppm_data.hi_bits_flag;
		unpack_data->ppm_data.coder.scale = get_mean(psee2c);
	} else {
		psee2c = &unpack_data->ppm_data.dummy_sse2cont;
		unpack_data->ppm_data.coder.scale = 1;
	}
	return psee2c;
}
unsigned int Unrar::get_mean(struct see2_context_tag *see2_cont)
{
	unsigned int ret_val;

	ret_val = see2_cont->summ >> see2_cont->shift;
	see2_cont->summ -= ret_val;
	return ret_val + (ret_val == 0);
}
void Unrar::update(struct see2_context_tag *see2_cont)
{
	if (see2_cont->shift < PERIOD_BITS && --see2_cont->count == 0)
	{
		see2_cont->summ += see2_cont->summ;
		see2_cont->count = 3 << see2_cont->shift++;
	}

}
void Unrar::update2(struct state_tag *p)
{
	(unpack_data->ppm_data.found_state = p)->freq += 4;
	unpack_data->ppm_data.min_context->con_ut.u.summ_freq += 4;
	if (p->freq > MAX_FREQ) {
		rescale();
	}
	unpack_data->ppm_data.esc_count++;
	unpack_data->ppm_data.run_length = unpack_data->ppm_data.init_rl;
}
void Unrar::clear_mask()
{
	unpack_data->ppm_data.esc_count = 1;
	memset(unpack_data->ppm_data.char_mask, 0, sizeof(unpack_data->ppm_data.char_mask));
}
BOOLEAN Unrar::update_model()
{
	struct state_tag fs, *p;
	struct ppm_context *pc, *successor;
	unsigned int ns1, ns, cf, sf, s0;
	fs = *unpack_data->ppm_data.found_state;
	p = NULL;

	if (fs.freq < MAX_FREQ/4 && (pc=unpack_data->ppm_data.min_context->suffix) != NULL) {
		if (pc->num_stats != 1) {
			if ((p=pc->con_ut.u.stats)->symbol != fs.symbol) {
				do {
					p++;
				} while (p->symbol != fs.symbol);
				if (p[0].freq >= p[-1].freq) {
					ppmd_swap(&p[0], &p[-1]);
					p--;
				}
			}
			if (p->freq < MAX_FREQ-9) {
				p->freq += 2;
				pc->con_ut.u.summ_freq += 2;
			}
		} else {
			p = &(pc->con_ut.one_state);
			p->freq += (p->freq < 32);
		}
	}
	if (!unpack_data->ppm_data.order_fall) {
		unpack_data->ppm_data.min_context = unpack_data->ppm_data.max_context =
			unpack_data->ppm_data.found_state->successor = create_successors(TRUE, p);
		if (!unpack_data->ppm_data.min_context) {
			goto RESTART_MODEL;
		}
		return TRUE;
	}
	*unpack_data->ppm_data.sub_alloc.ptext++ = fs.symbol;
	successor = (struct ppm_context *) unpack_data->ppm_data.sub_alloc.ptext;
	if (unpack_data->ppm_data.sub_alloc.ptext >= unpack_data->ppm_data.sub_alloc.fake_units_start) {
		goto RESTART_MODEL;
	}
	if (fs.successor) {
		if ((UINT8 *)fs.successor <= unpack_data->ppm_data.sub_alloc.ptext &&
			(fs.successor = create_successors( FALSE, p)) == NULL) {
				goto RESTART_MODEL;
		}
		if (!--unpack_data->ppm_data.order_fall) {
			successor = fs.successor;
			unpack_data->ppm_data.sub_alloc.ptext -= (unpack_data->ppm_data.max_context != unpack_data->ppm_data.min_context);
		}
	} else {
		unpack_data->ppm_data.found_state->successor = successor;
		fs.successor = unpack_data->ppm_data.min_context;
	}
	s0 = unpack_data->ppm_data.min_context->con_ut.u.summ_freq-(ns=unpack_data->ppm_data.min_context->num_stats)-(fs.freq-1);
	for (pc=unpack_data->ppm_data.max_context; pc != unpack_data->ppm_data.min_context ; pc=pc->suffix) {
		if ((ns1=pc->num_stats) != 1) {
			if ((ns1 & 1) == 0) {
				pc->con_ut.u.stats = (struct state_tag *)
					sub_allocator_expand_units(pc->con_ut.u.stats, ns1>>1);
				if (!pc->con_ut.u.stats) {
					goto RESTART_MODEL;
				}
			}
			pc->con_ut.u.summ_freq += (2*ns1 < ns)+2*((4*ns1 <= ns) & (pc->con_ut.u.summ_freq <= 8*ns1));
		} else {
			p = (struct state_tag *) sub_allocator_alloc_units(1);
			if (!p) {
				goto RESTART_MODEL;
			}
			*p = pc->con_ut.one_state;
			pc->con_ut.u.stats = p;
			if (p->freq < MAX_FREQ/4-1) {
				p->freq += p->freq;
			} else {
				p->freq = MAX_FREQ - 4;
			}
			pc->con_ut.u.summ_freq = p->freq + unpack_data->ppm_data.init_esc + (ns > 3);
		}
		cf = 2*fs.freq*(pc->con_ut.u.summ_freq+6);
		sf = s0 + pc->con_ut.u.summ_freq;
		if (cf < 6*sf) {
			cf = 1 + (cf > sf) + (cf >= 4*sf);
			pc->con_ut.u.summ_freq += 3;
		} else {
			cf = 4 + (cf >= 9*sf) + (cf >= 12*sf) + (cf >= 15*sf);
			pc->con_ut.u.summ_freq += cf;
		}
		p = pc->con_ut.u.stats + ns1;
		p->successor = successor;
		p->symbol = fs.symbol;
		p->freq = cf;
		pc->num_stats = ++ns1;
	}
	unpack_data->ppm_data.max_context = unpack_data->ppm_data.min_context = fs.successor;
	return TRUE;

RESTART_MODEL:
	if (!restart_model_rare())
	{
		return FALSE;
	}
	unpack_data->ppm_data.esc_count = 0;
	return TRUE;
}
Unrar::ppm_context *Unrar::create_successors(int skip, struct state_tag *p1)
{
	struct state_tag up_state;
	struct ppm_context *pc, *up_branch;
	struct state_tag *p, *ps[MAX_O], **pps;
	unsigned int cf, s0;

	pc = unpack_data->ppm_data.min_context;
	up_branch = unpack_data->ppm_data.found_state->successor;
	pps = ps;

	if (!skip) {
		*pps++ = unpack_data->ppm_data.found_state;
		if (!pc->suffix) {
			goto NO_LOOP;
		}
	}
	if (p1) {
		p = p1;
		pc = pc->suffix;
		goto LOOP_ENTRY;
	}
	do {
		pc = pc->suffix;
		if (pc->num_stats != 1) {
			if ((p=pc->con_ut.u.stats)->symbol != unpack_data->ppm_data.found_state->symbol) {
				do {
					p++;
				} while (p->symbol != unpack_data->ppm_data.found_state->symbol);
			}
		} else {
			p = &(pc->con_ut.one_state);
		}
LOOP_ENTRY:
		if (p->successor != up_branch) {
			pc = p->successor;
			break;
		}
		*pps++ = p;
	} while (pc->suffix);
NO_LOOP:
	if (pps == ps) {
		return pc;
	}
	up_state.symbol= *(UINT8 *) up_branch;
	up_state.successor = (struct ppm_context *) (((UINT8 *) up_branch)+1);
	if (pc->num_stats != 1) {
		if ((UINT8 *) pc <= unpack_data->ppm_data.sub_alloc.ptext) {
			return NULL;
		}
		if ((p=pc->con_ut.u.stats)->symbol != up_state.symbol) {
			do {
				p++;
				if ((void *)p > (void *) unpack_data->ppm_data.sub_alloc.heap_end) {
					return NULL;
				}
			} while (p->symbol != up_state.symbol);
		}
		cf = p->freq - 1;
		s0 = pc->con_ut.u.summ_freq - pc->num_stats - cf;
		up_state.freq = 1 + ((2*cf <= s0)?(5*cf > s0):((2*cf+3*s0-1)/(2*s0)));
	} else {
		up_state.freq = pc->con_ut.one_state.freq;
	}
	do {
		pc = create_child(pc, *--pps, &up_state);
		if (!pc) {
			return NULL;
		}
	} while (pps != ps);
	return pc;
}
Unrar::ppm_context * Unrar::create_child( struct ppm_context *context,	struct state_tag *pstats, struct state_tag *first_state) 
{
	struct ppm_context *pc;
	pc = (struct ppm_context *) sub_allocator_alloc_context();
	if (pc) {
		pc->num_stats = 1;
		pc->con_ut.one_state = *first_state;
		pc->suffix = context;
		pstats->successor = pc;
	}
	return pc;
}
BOOLEAN Unrar::read_vm_code_PPM()
{
	unsigned int first_byte , length;
	int  i, ch, retval, b1, b2;
	unsigned char *vmcode;

	first_byte = ppm_decode_char();
	if ((int)first_byte == -1) {
		return FALSE;
	}
	length = (first_byte & 7) + 1;
	if (length == 7) {
		b1 = ppm_decode_char();
		if (b1 == -1) {
			return FALSE;
		}
		length = b1 + 7;
	} else if (length == 8) {
		b1 = ppm_decode_char();
		if (b1 == -1) {
			return FALSE;
		}
		b2 = ppm_decode_char();
		if (b2 == -1) {
			return FALSE;
		}
		length = b1*256 + b2;
	}
	vmcode = (unsigned char *) UrarMalloc(length + 2);

	if (!vmcode) 
	{
		return FALSE;
	}
	for (i=0 ; i < length ; i++)
	{
		ch = ppm_decode_char();
		if (ch == -1) {
			SMHeapFree(vmcode);
			return FALSE;
		}
		vmcode[i] = ch;
	}
	retval = add_vm_code(first_byte, vmcode, length);
	SMHeapFree(vmcode);
	return retval;
}
BOOLEAN Unrar::add_vm_code( unsigned int first_byte,unsigned char *vmcode,UINT32 code_size )
{
	
	unsigned int filter_pos, new_filter, block_start, init_mask, cur_size;
	struct UnpackFilter *filter, *stack_filter;
	int i, empty_count, stack_pos, vm_codesize, static_size, data_size;
	unsigned char *vm_code, *global_data;
	rarvm_input.in_buf = vmcode;
	rarvm_input.buf_size = code_size;
	rarvm_input.in_addr = 0;
	rarvm_input.in_bit = 0;
	if (first_byte & 0x80) 
	{
		filter_pos = vm_read_data();
		if (filter_pos == 0) {
			InitFilter();
		} else {
			filter_pos--;
		}
	} else {
		filter_pos = unpack_data->last_filter;
	}
	if (filter_pos > unpack_data->Filters.num_items ||
		filter_pos > unpack_data->old_filter_lengths_size) 
	{
			return FALSE;
	}
	unpack_data->last_filter = filter_pos;
	new_filter = (filter_pos == unpack_data->Filters.num_items);
	if (new_filter) {
		if (!rar_filter_array_add(&unpack_data->Filters, 1)) {
			return FALSE;
		}
		unpack_data->Filters.array[unpack_data->Filters.num_items-1] =
			filter = rar_filter_new();
		if (!unpack_data->Filters.array[unpack_data->Filters.num_items-1]) {
			
			return FALSE;
		}	
		unpack_data->old_filter_lengths_size++;
		unpack_data->old_filter_lengths = (int *) rar_realloc2(unpack_data->old_filter_lengths,
			sizeof(int) * unpack_data->old_filter_lengths_size);
		if(!unpack_data->old_filter_lengths) {
			return FALSE;
		}
		unpack_data->old_filter_lengths[unpack_data->old_filter_lengths_size-1] = 0;
		filter->exec_count = 0;
	} else {
		filter = unpack_data->Filters.array[filter_pos];
		filter->exec_count++;
	}

	stack_filter = rar_filter_new();

	empty_count = 0;
	for (i=0 ; i < unpack_data->PrgStack.num_items; i++) {
		unpack_data->PrgStack.array[i-empty_count] = unpack_data->PrgStack.array[i];
		if (unpack_data->PrgStack.array[i] == NULL) {
			empty_count++;
		}
		if (empty_count > 0) {
			unpack_data->PrgStack.array[i] = NULL;
		}
	}

	if (empty_count == 0) {
		rar_filter_array_add(&unpack_data->PrgStack, 1);
		empty_count = 1;
	}
	stack_pos = unpack_data->PrgStack.num_items - empty_count;
	unpack_data->PrgStack.array[stack_pos] = stack_filter;
	stack_filter->exec_count = filter->exec_count;

	block_start = vm_read_data();
	if (first_byte & 0x40) {
		block_start += 258;
	}
	stack_filter->block_start = (block_start + unpack_data->unp_ptr) & MAXWINMASK;
	if (first_byte & 0x20) {
		stack_filter->block_length = vm_read_data();
	} else {
		stack_filter->block_length = filter_pos < unpack_data->old_filter_lengths_size ?
			unpack_data->old_filter_lengths[filter_pos] : 0;
	}
	stack_filter->next_window = unpack_data->wr_ptr != unpack_data->unp_ptr &&
		((unpack_data->wr_ptr - unpack_data->unp_ptr) & MAXWINMASK) <= block_start;

	unpack_data->old_filter_lengths[filter_pos] = stack_filter->block_length;

	memset(stack_filter->prg.init_r, 0, sizeof(stack_filter->prg.init_r));
	stack_filter->prg.init_r[3] = VM_GLOBALMEMADDR;
	stack_filter->prg.init_r[4] = stack_filter->block_length;
	stack_filter->prg.init_r[5] = stack_filter->exec_count;
	if (first_byte & 0x10) {
		init_mask = vm_getbits() >> 9;
		vm_addbits(7);
		for (i=0 ; i<7 ; i++) {
			if (init_mask & (1<<i)) {
				stack_filter->prg.init_r[i] =
					vm_read_data();
			}
		}
	}
	if (new_filter) {
		vm_codesize = vm_read_data();
		if (vm_codesize >= 0x1000 || vm_codesize == 0 || (vm_codesize > rarvm_input.buf_size) || vm_codesize < 0) {
			return FALSE;
		}
		vm_code = (unsigned char *) UrarMalloc(vm_codesize);
		if(!vm_code) {

			return FALSE;
		}
		for (i=0 ; i < vm_codesize ; i++) {
			vm_code[i] = vm_getbits() >> 8;
			vm_addbits( 8);
		}
		if(!vm_prepare(&vm_code[0], vm_codesize, &filter->prg)) {
			SMHeapFree(vm_code);
			return FALSE;
		}
		SMHeapFree(vm_code);
	}
	stack_filter->prg.alt_cmd = &filter->prg.cmd.array[0];
	stack_filter->prg.cmd_count = filter->prg.cmd_count;

	static_size = filter->prg.static_size;
	if (static_size > 0 && static_size < VM_GLOBALMEMSIZE) {
		stack_filter->prg.static_data =(unsigned char *) UrarMalloc(static_size);
		if(!stack_filter->prg.static_data) {
			return FALSE;
		}
		memcpy(stack_filter->prg.static_data, filter->prg.static_data, static_size);
	}

	if (stack_filter->prg.global_size < VM_FIXEDGLOBALSIZE) {
		SMHeapFree(stack_filter->prg.global_data);
		stack_filter->prg.global_data =(unsigned char *) UrarMalloc(VM_FIXEDGLOBALSIZE);
		if(!stack_filter->prg.global_data) {
			
			return FALSE;
		}
		memset(stack_filter->prg.global_data, 0, VM_FIXEDGLOBALSIZE);
		stack_filter->prg.global_size = VM_FIXEDGLOBALSIZE;
	}
	global_data = &stack_filter->prg.global_data[0];
	for (i=0 ; i<7 ; i++)
	{
		vm_set_value(FALSE, (unsigned int *)&global_data[i*4],
			stack_filter->prg.init_r[i]);
	}
	vm_set_value(FALSE, (unsigned int *)&global_data[0x1c], stack_filter->block_length);
	vm_set_value(FALSE, (unsigned int *)&global_data[0x20], 0);
	vm_set_value(FALSE, (unsigned int *)&global_data[0x2c], stack_filter->exec_count);
	memset(&global_data[0x30], 0, 16);
	
	if (first_byte & 8) {
		data_size = vm_read_data();
		if (data_size >= 0x10000) {
			return FALSE;
		}
		cur_size = stack_filter->prg.global_size;
		if (cur_size < data_size+VM_FIXEDGLOBALSIZE) {
			stack_filter->prg.global_size += data_size+VM_FIXEDGLOBALSIZE-cur_size;
			stack_filter->prg.global_data =(unsigned char *) rar_realloc2(stack_filter->prg.global_data,
				stack_filter->prg.global_size);
			if(!stack_filter->prg.global_data) {
				return FALSE;
			}
		}
		global_data = &stack_filter->prg.global_data[VM_FIXEDGLOBALSIZE];
		for (i=0 ; i< data_size ; i++) {
			if ((rarvm_input.in_addr+2) > rarvm_input.buf_size) {
			
				return FALSE;
			}
			global_data[i] = vm_getbits() >> 8;
			vm_addbits(8);
		}
	}
	return TRUE;


}
unsigned int Unrar::vm_read_data()
{
	unsigned int data;

	data = vm_getbits();
	switch (data & 0xc000) {
	case 0:
		vm_addbits(6);
		return ((data>>10)&0x0f);
	case 0x4000:
		if ((data & 0x3c00) == 0) {
			data = 0xffffff00 | ((data>>2) & 0xff);
			vm_addbits(14);
		} else {
			data = (data >> 6) &0xff;
			vm_addbits(10);
		}
		return data;
	case 0x8000:
		vm_addbits(2);
		data = vm_getbits();
		vm_addbits(16);
		return data;
	default:
		vm_addbits(2);
		data = (vm_getbits() << 16);
		vm_addbits(16);
		data |= vm_getbits();
		vm_addbits(16);
		return data;
	}
}
unsigned int Unrar::vm_getbits()
{
	unsigned int bit_field;

	bit_field = (unsigned int) rarvm_input.in_buf[rarvm_input.in_addr] << 16;
	bit_field |= (unsigned int) rarvm_input.in_buf[rarvm_input.in_addr+1] << 8;
	bit_field |= (unsigned int) rarvm_input.in_buf[rarvm_input.in_addr+2];
	bit_field >>= (8-rarvm_input.in_bit);

	return(bit_field & 0xffff);
}
void Unrar::vm_addbits(int bits)
{
	bits += rarvm_input.in_bit;
	rarvm_input.in_addr += bits >> 3;
	rarvm_input.in_bit = bits & 7;
}
BOOLEAN Unrar::rar_filter_array_add(rar_filter_array_t *filter_a, int num)
{
	filter_a->num_items += num;
	filter_a->array = (struct UnpackFilter **) rar_realloc2(filter_a->array,
		filter_a->num_items * sizeof(struct UnpackFilter **));
	if (filter_a->array == NULL) {
		filter_a->num_items=0;
		return FALSE;
	}
	filter_a->array[filter_a->num_items-1] = NULL;
	return TRUE;
}
Unrar::UnpackFilter *Unrar::rar_filter_new(void) 
{
	struct UnpackFilter *filter;

	filter = (struct UnpackFilter *) UrarMalloc(sizeof(struct UnpackFilter));
	if (!filter) {
		return NULL;
	}
	filter->block_start = 0;
	filter->block_length = 0;
	filter->exec_count = 0;
	filter->next_window = 0;

	filter->prg.cmd.array =NULL;
	filter->prg.cmd.num_items = 0 ;
	filter->prg.global_data = NULL;
	filter->prg.static_data = NULL;
	filter->prg.global_size = filter->prg.static_size = 0;
	filter->prg.filtered_data = NULL;
	filter->prg.filtered_data_size = 0;
	return filter;
}
BOOLEAN Unrar::vm_prepare(unsigned char *code,int code_size, struct rarvm_prepared_program *prg)
{
	unsigned char xor_sum;
	int  op_num, distance;
	rarvm_standard_filters_t filter_type;
	struct rarvm_prepared_command *cur_cmd;
	UINT32 data_flag, data , u32Index;
	struct rarvm_prepared_command *cmd;

	rarvm_input.in_addr = rarvm_input.in_bit = 0;
	memcpy(rarvm_input.in_buf, code, MIN(code_size, 0x8000));
	xor_sum = 0;
	for (u32Index=1 ; u32Index<code_size; u32Index++) 
	{
		xor_sum ^= code[u32Index];
	}
	vm_addbits(8);

	prg->cmd_count = 0;
	if (xor_sum == code[0]) {
		filter_type = is_standard_filter(code, code_size);
		if (filter_type != VMSF_NONE) {
			rar_cmd_array_add(&prg->cmd, 1);
			cur_cmd = &prg->cmd.array[prg->cmd_count++];
			cur_cmd->op_code = VM_STANDARD;
			cur_cmd->op1.data = filter_type;
			cur_cmd->op1.addr = &cur_cmd->op1.data;
			cur_cmd->op2.addr = &cur_cmd->op2.data;
			cur_cmd->op1.type = cur_cmd->op2.type = VM_OPNONE;
			code_size = 0;
		}

		data_flag = vm_getbits();
		vm_addbits(1);
		if (data_flag & 0x8000) {
			int data_size = vm_read_data()+1;
			prg->static_data =(unsigned char *) UrarMalloc(data_size);
			if(!prg->static_data) 
			{
				return FALSE;
			}
			for (u32Index=0 ; rarvm_input.in_addr < code_size && u32Index < data_size ; u32Index++) {
				prg->static_size++;
				prg->static_data =(unsigned char *) rar_realloc2(prg->static_data, prg->static_size);
				if(!prg->static_data) {
					return FALSE;
				}
				prg->static_data[u32Index] = vm_getbits() >> 8;
				vm_addbits(8);
			}
		}
		while (rarvm_input.in_addr < code_size) {
			rar_cmd_array_add(&prg->cmd, 1);
			cur_cmd = &prg->cmd.array[prg->cmd_count];
			data = vm_getbits();
			if ((data & 0x8000) == 0) {
				cur_cmd->op_code = (rarvm_commands_t) (data>>12);
				vm_addbits( 4);
			} else {
				cur_cmd->op_code = (rarvm_commands_t) ((data>>10)-24);
				vm_addbits(6);
			}
			if (vm_cmdflags[cur_cmd->op_code] & VMCF_BYTEMODE) {
				cur_cmd->byte_mode = vm_getbits() >> 15;
				vm_addbits(1);
			} else {
				cur_cmd->byte_mode = 0;
			}
			cur_cmd->op1.type = cur_cmd->op2.type = VM_OPNONE;
			op_num = (vm_cmdflags[cur_cmd->op_code] & VMCF_OPMASK);
			cur_cmd->op1.addr = cur_cmd->op2.addr = NULL;
			if (op_num > 0) {
				vm_decode_arg(&cur_cmd->op1, cur_cmd->byte_mode);
				if (op_num == 2) {
					vm_decode_arg(&cur_cmd->op2, cur_cmd->byte_mode);
				} else {
					if (cur_cmd->op1.type == VM_OPINT &&
						(vm_cmdflags[cur_cmd->op_code] &
						(VMCF_JUMP|VMCF_PROC))) {
							distance = cur_cmd->op1.data;
							if (distance >= 256) {
								distance -= 256;
							} else {
								if (distance >=136) {
									distance -= 264;
								} else {
									if (distance >= 16) {
										distance -= 8;
									} else if (distance >= 8) {
										distance -= 16;
									}
								}
								distance += prg->cmd_count;
							}
							cur_cmd->op1.data = distance;
					}
				}
			}
			prg->cmd_count++;
		}
	}
	
	rar_cmd_array_add(&prg->cmd,1);
	cur_cmd = &prg->cmd.array[prg->cmd_count++];
	cur_cmd->op_code = VM_RET;
	cur_cmd->op1.addr = &cur_cmd->op1.data;
	cur_cmd->op2.addr = &cur_cmd->op2.data;
	cur_cmd->op1.type = cur_cmd->op2.type = VM_OPNONE;
	
	for (u32Index=0 ; u32Index < prg->cmd_count ; u32Index++) {
		cmd = &prg->cmd.array[u32Index];
		if (cmd->op1.addr == NULL) {
			cmd->op1.addr = &cmd->op1.data;
		}
		if (cmd->op2.addr == NULL) {
			cmd->op2.addr = &cmd->op2.data;
		}
	}

	if (code_size!=0) {
		vm_optimize(prg);
	}
	
	return TRUE;
}
Unrar::rarvm_standard_filters_t Unrar::is_standard_filter(unsigned char *code, int code_size)
{
	UINT32 code_crc;
	int i;

	struct standard_filter_signature
	{
		int length;
		UINT32 crc;
		rarvm_standard_filters_t type;
	} std_filt_list[] = {
		{53,  0xad576887, VMSF_E8},
		{57,  0x3cd7e57e, VMSF_E8E9},
		{120, 0x3769893f, VMSF_ITANIUM},
		{29,  0x0e06077d, VMSF_DELTA},
		{149, 0x1c2c5dc8, VMSF_RGB},
		{216, 0xbc85e701, VMSF_AUDIO},
		{40,  0x46b9c560, VMSF_UPCASE}
	};

	code_crc = crc::crc32Rar(0xffffffff, code, code_size)^0xffffffff;
	for (i=0 ; i<sizeof(std_filt_list)/sizeof(std_filt_list[0]) ; i++) {
		if (std_filt_list[i].crc == code_crc && std_filt_list[i].length == code_size) {
			return std_filt_list[i].type;
		}
	}
	return VMSF_NONE;
}
void Unrar::vm_decode_arg(struct rarvm_prepared_operand *op, int byte_mode) 
{
	UINT16 data;

	data = vm_getbits();
	if (data & 0x8000) {
		op->type = VM_OPREG;
		op->data = (data >> 12) & 7;
		op->addr = &unpack_data->rarvm_data.R[op->data];
		vm_addbits(4);
	} else if ((data & 0xc000) == 0) {
		op->type = VM_OPINT;
		if (byte_mode) {
			op->data = (data>>6) & 0xff;
			vm_addbits(10);
		} else {
			vm_addbits(2);
			op->data = vm_read_data();
		}
	} else {
		op->type = VM_OPREGMEM;
		if ((data & 0x2000) == 0) {
			op->data = (data >> 10) & 7;
			op->addr = &unpack_data->rarvm_data.R[op->data];
			op->base = 0;
			vm_addbits(6);
		} else {
			if ((data & 0x1000) == 0) {
				op->data = (data >> 9) & 7;
				op->addr = &unpack_data->rarvm_data.R[op->data];
				vm_addbits(7);
			} else {
				op->data = 0;
				vm_addbits(4);
			}
			op->base = vm_read_data();
		}
	}
}
void Unrar::vm_optimize(struct rarvm_prepared_program *prg)
{
	struct rarvm_prepared_command *code, *cmd;
	int code_size, i, flags_required, j, flags;

	code = prg->cmd.array;
	code_size = prg->cmd_count;

	for (i=0 ; i < code_size ; i++) {
		cmd = &code[i];
		switch(cmd->op_code) {
			case VM_MOV:
				cmd->op_code = cmd->byte_mode ? VM_MOVB:VM_MOVD;
				continue;
			case VM_CMP:
				cmd->op_code = cmd->byte_mode ? VM_CMPB:VM_CMPD;
				continue;
			default: 
				break;
		}
		if ((vm_cmdflags[cmd->op_code] & VMCF_CHFLAGS) == 0) {
			continue;
		}
		flags_required = FALSE;
		for (j=i+1 ; j < code_size ; j++) {
			flags = vm_cmdflags[code[j].op_code];
			if (flags & (VMCF_JUMP|VMCF_PROC|VMCF_USEFLAGS)) {
				flags_required=TRUE;
				break;
			}
			if (flags & VMCF_CHFLAGS) {
				break;
			}
		}
		if (flags_required) {
			continue;
		}
		switch(cmd->op_code) {
			case VM_ADD:
				cmd->op_code = cmd->byte_mode ? VM_ADDB:VM_ADDD;
				continue;
			case VM_SUB:
				cmd->op_code = cmd->byte_mode ? VM_SUBB:VM_SUBD;
				continue;
			case VM_INC:
				cmd->op_code = cmd->byte_mode ? VM_INCB:VM_INCD;
				continue;
			case VM_DEC:
				cmd->op_code = cmd->byte_mode ? VM_DECB:VM_DECD;
				continue;
			case VM_NEG:
				cmd->op_code = cmd->byte_mode ? VM_NEGB:VM_NEGD;
				continue;
			default:
				break;
		}
	}
}
//-------------------------------------------------

void Unrar::copy_string( unsigned int length, unsigned int distance) 
{
	unsigned int dest_ptr;

	dest_ptr = unpack_data->unp_ptr - distance;
	if (dest_ptr < MAXWINSIZE-260 && unpack_data->unp_ptr < MAXWINSIZE - 260) {
		unpack_data->window[unpack_data->unp_ptr++] = unpack_data->window[dest_ptr++];
		while (--length > 0) {
			unpack_data->window[unpack_data->unp_ptr++] = unpack_data->window[dest_ptr++];
		}
	} else {
		while (length--) {
			unpack_data->window[unpack_data->unp_ptr] =
				unpack_data->window[dest_ptr++ & MAXWINMASK];
			unpack_data->unp_ptr = (unpack_data->unp_ptr + 1) & MAXWINMASK;
		}
	}
}
//-----------------------------------------------------------------
void Unrar::insert_old_dist(unsigned int distance)
{
	unpack_data->old_dist[3] = unpack_data->old_dist[2];
	unpack_data->old_dist[2] = unpack_data->old_dist[1];
	unpack_data->old_dist[1] = unpack_data->old_dist[0];
	unpack_data->old_dist[0] = distance;
}
//-----------------------------------------------------------------
void Unrar::insert_last_match(unsigned int length, unsigned int distance)
{
	unpack_data->last_dist = distance;
	unpack_data->last_length = length;
}
//-----------------------------------------------------------------
int Unrar::read_vm_code()
{
	unsigned int first_byte;
	int length, i, retval;
	unsigned char *vmcode;

	first_byte = getbits()>>8;
	addbits(8);
	length = (first_byte & 7) + 1;
	if (length == 7) {
		length = (getbits() >> 8) + 7;
		addbits(8);
	} else if (length == 8) {
		length = getbits();
		addbits(16);
	}
	vmcode = (unsigned char *) UrarMalloc(length + 2);
	if (!vmcode) {
		return FALSE;
	}
	for (i=0 ; i < length ; i++) {
		if (unpack_data->in_addr >= unpack_data->read_top-1 &&
			!UpackReadBuffer() && i<length-1) {
				return FALSE;
		}
		vmcode[i] = getbits() >> 8;
		addbits(8);
	}
	retval = add_vm_code(first_byte, vmcode, length);
	SMHeapFree(vmcode);
	return retval;
}
int Unrar::read_end_of_block() 
{
	unsigned int bit_field;
	int new_table, new_file=FALSE;

	bit_field = getbits();
	if (bit_field & 0x8000) {
		new_table = TRUE;
		addbits(1);
	} else {
		new_file = TRUE;
		new_table = (bit_field & 0x4000);
		addbits(2);
	}
	unpack_data->tables_read = !new_table;

	return !(new_file || (new_table && !read_tables()));
}
void * Unrar::sub_allocator_expand_units(void *old_ptr, int old_nu)
{
	int i0, i1;
	void *ptr;

	i0 = unpack_data->ppm_data.sub_alloc.units2indx[old_nu-1];
	i1 = unpack_data->ppm_data.sub_alloc.units2indx[old_nu];
	if (i0 == i1) {
		return old_ptr;
	}
	ptr = sub_allocator_alloc_units(old_nu+1);
	if (ptr) {
		memcpy(ptr, old_ptr, UNIT_SIZE*(old_nu));
		sub_allocator_insert_node(old_ptr, i0);
	}
	return ptr;
}
void * Unrar::sub_allocator_alloc_units(int nu)
{
	int indx;
	void *ret_val;

	indx = unpack_data->ppm_data.sub_alloc.units2indx[nu-1];
	if (unpack_data->ppm_data.sub_alloc.free_list[indx].next) {
		return sub_allocator_remove_node(indx);
	}
	ret_val = unpack_data->ppm_data.sub_alloc.lo_unit;
	unpack_data->ppm_data.sub_alloc.lo_unit += UNIT_SIZE*(unpack_data->ppm_data.sub_alloc.indx2units[indx]);
	if (unpack_data->ppm_data.sub_alloc.lo_unit <= unpack_data->ppm_data.sub_alloc.hi_unit) {
		return ret_val;
	}
	unpack_data->ppm_data.sub_alloc.lo_unit -= UNIT_SIZE*(unpack_data->ppm_data.sub_alloc.indx2units[indx]);
	return sub_allocator_alloc_units_rare(indx);
}
void Unrar::ppm_cleanup()
{
	sub_allocator_stop_sub_allocator();
	sub_allocator_start_sub_allocator(1);
	start_model_rare(2);
}
BOOLEAN Unrar::rar_cmd_array_add(rar_cmd_array_t *cmd_a, int num)
{
	cmd_a->num_items += num;
	cmd_a->array = (struct rarvm_prepared_command *) rar_realloc2(cmd_a->array,
		cmd_a->num_items * sizeof(struct rarvm_prepared_command));
	if (cmd_a->array == NULL) {
		return FALSE;
	}
	//JFree(unpack_data->Filters.array[0]->prg.cmd.array );
	memset(&cmd_a->array[cmd_a->num_items-1], 0, sizeof(struct rarvm_prepared_command));
	return TRUE;
}

void Unrar::close()
{
	sub_allocator_stop_sub_allocator();
	if (main_hdr)
	{
		SMHeapFree(main_hdr);
	}
	
	InitFilter();
	vm_free();
	if (unpack_data)
	{
		SMHeapFree(unpack_data);
	}
	if (comment_hdr)
	{
		SMHeapFree(comment_hdr);
	}	
}
Unrar::Unrar(UINT32 MaxSizeFile  )
{
	maxfilesize = MaxSizeFile ;
	comment_hdr = NULL;
}

Unrar::Unrar()
{
	maxfilesize = 0xffffff;
	comment_hdr = NULL;
}

UINT32  Unrar::GetCurrentFileIndex ()
{
	return (u32ItemIndex -1);
}

void Unrar::SetDeleteIndex(UINT32 u32Index) 
{
	ocDeleteIndexList.push_back(u32Index);
}

void Unrar::SetReplaceIndex(JString ocFileNameinZip, JString ocFileName)
{
	ocReplacedItemIndex.insert(Pair(ocFileNameinZip, ocFileName));
}

JFile * Unrar::GetCurrentFile()
{
	return m_pclsUnrarFile ;
}

BOOLEAN Unrar::CloseCompessFile()
{	
	if (ocDeleteIndexList.size() > 0)
	{
		ocRarFileName = m_pclsRarFile->GetName();
		CleanRarFile();
	}
	else
	{
		m_pclsRarFile->Close();
	}
	close();
	return TRUE;
}
void Unrar::SetMessageQueue(queue <JString> * i_MessageQueue)
{
	MessageQueue = i_MessageQueue ;
}

UINT32 Unrar::CleanRarFile()
{
	list <RarDirectory> ocDirectoryList;
	list <RarDirectory> :: iterator pocDirectoryListIterator;
	list <UINT32> :: iterator iListIterator;
	JFile ocRarCleanFile;
	m_pclsUnrarFile;
	UINT32 u32Size, u32CentralDirectorySize = 0, u32Counter = 0, u32SeekParam = 0, u32DeletedCounter = 0, u32Magic = 0x02014b50;
 	if(!ocRarCleanFile.Open(m_pclsRarFile->GetName(), FALSE, TRUE))
 	{
 		// Could Not Open Archive For Write
 		// CloseHandle(m_pclsZipFile->GetHandle());
 		m_pclsRarFile->CloseHandle();
 		if(!ocRarCleanFile.Open(m_pclsRarFile->GetName(), FALSE, TRUE))
 		{
 			return -1;
 		}
 	}
	BOOLEAN bCheck;
	m_pclsRarFile = &ocRarCleanFile;


	BOOLEAN IsDir ;
	UINT8 Host ;
	u32FileChange = CompressFileChanged;

	// Enumerate all item in main directory
	for (pocDirectoryListIterator = ocMainDirectory.begin(); pocDirectoryListIterator != ocMainDirectory.end(); ++pocDirectoryListIterator)
	{
		ocDeleteIndexList.size();
		// choose ones who are not deleted
		for (iListIterator = ocDeleteIndexList.begin(), bCheck = FALSE; iListIterator != ocDeleteIndexList.end() && !bCheck; ++iListIterator)
		{
			if (pocDirectoryListIterator->m_u32Index == *iListIterator)
			{
				u32Counter++;
				u32DeletedCounter++;
				bCheck = TRUE;
			}
		}
		if(bCheck)
		{
			continue;
		}

		ocDirectoryList.push_back( *pocDirectoryListIterator );
	}
	u32SeekParam = main_hdr->Size + SIZEOF_MARKHEAD;

	if (!(ocDirectoryList.empty() || (ocDirectoryList.size() == u32SubHeadNumber)))
	{
		pocDirectoryListIterator = ocDirectoryList.begin();
		//m_i64WritePointer = pocDirectoryListIterator->m_i64FileHeaderOffset;
		//UINT32 u32FileSize = ocRarCleanFile.GetFileLength();		
		ocRarCleanFile.Seek(u32SeekParam, JFile::FBEGIN);
		for (;;)
		{
			RarDirectory osRarDirectory = *pocDirectoryListIterator;
			++pocDirectoryListIterator;
			if (u32SeekParam != osRarDirectory.m_i64FileHeaderOffset)
			{						
				CopyDataBlock(u32SeekParam, osRarDirectory.m_i64FileHeaderOffset, osRarDirectory.m_u32HeadAndBodySize);
			}
			u32SeekParam += osRarDirectory.m_u32HeadAndBodySize;

			if ( pocDirectoryListIterator == ocDirectoryList.end() )
			{
				break;
			}

		}
	}
	else
	{
		if (ocReplacedItemIndex.size() == 0 /*|| (ocDirectoryList.size() == u32SubHeadNumber)*/)
		{
			u32FileChange = CompressFileDeleted;
			ocRarCleanFile.Close();
			ocRarCleanFile.Delete(m_pclsRarFile->GetName());
			return FALSE;
		}
	}
	ocRarCleanFile.Seek(u32SeekParam, JFile::FBEGIN);

	map <JString, JString>::iterator iReplaceIterator;
	//UINT8 *pu8Buffer = (UINT8 *)SMHeapAlloc(4096);
	for(iReplaceIterator = ocReplacedItemIndex.begin(); iReplaceIterator != ocReplacedItemIndex.end(); iReplaceIterator++)
	{		
		UnrarFileHeader  osFileHeader;
		JFile osTempFile;
		ZeroMemory(&osFileHeader, sizeof(UnrarFileHeader));

		
		osTempFile.Open(iReplaceIterator->second, TRUE, FALSE);
		UINT64 u64TempFileLength = osTempFile.GetFileLength();
		UINT32 u32TempCrc = -1, u32Size, u32CurrentFilePosition = u32SeekParam;
		
		//osFileHeader.
		FILETIME osCreateFileTime;
		LARGE_INTEGER u64FileSize;
		UINT8 pu8Buffer[0x10000];
		ZeroMemory(pu8Buffer, 0x10000);
		u64FileSize.QuadPart = osTempFile.GetFileLength();
		/*
		char* _string = "Enumator\\1\\All_Defines.h";
		osFileHeader.Type = 0x74 ;
		osFileHeader.Flags = 0x9080;
		osFileHeader.HeadSize = 0x3d;
		osFileHeader.PackSize = 0x10b3;
		osFileHeader.UnpackSize = 0x3d99;
		osFileHeader.HostOs = 2; // 2 Means Window OS
		osFileHeader.FileCrc  = 0x03c6d588;
		osFileHeader.FileTime = 0x40216021;
		osFileHeader.UnpackVer = 0x1d;
		osFileHeader.Method = 0x33;
		osFileHeader.NameSize = 0x18;
		osFileHeader.FileAttrib = 0x20;
		osFileHeader.HighPackSize  = 0;
		osFileHeader.HighUnpackSize  = 0;
		
		UINT8 Buffer[1000];
		UINT32 address = ((UINT32)(&osFileHeader.HighPackSize) - (UINT32)(&osFileHeader.Type)), temp = 0x0eba42b0;
		memcpy(Buffer, (UINT8*)&(osFileHeader.Type), address);
		memcpy(Buffer + address, _string, osFileHeader.NameSize + 1);
		memcpy(Buffer + address + osFileHeader.NameSize + 1, &temp, 4);
		
		osFileHeader.crc = ~crc::crc32Rar(-1, Buffer, address + osFileHeader.NameSize + 5);
		*/

		osFileHeader.Type = FILE_HEAD ;
		osFileHeader.Flags = /*0x8000 |*/ (u64FileSize.HighPart? 0x100 : 0);
// 		osFileHeader.HeadSize ; It is on the below
 		osFileHeader.PackSize  = u64FileSize.LowPart;
		osFileHeader.UnpackSize = u64FileSize.LowPart;
		osFileHeader.HostOs = 2; // 2 Means Window OS
		osFileHeader.FileTime = GetFileTime(osTempFile.GetHandle(), &osCreateFileTime, NULL, NULL);
		osFileHeader.UnpackVer = 0x14;
		osFileHeader.Method = 0x30;
		osFileHeader.NameSize = iReplaceIterator->first.length();
		osFileHeader.HeadSize = osFileHeader.NameSize + (u64FileSize.HighPart? 0x28 : 0x20);
		osFileHeader.FileAttrib = FILE_ATTRIBUTE_NORMAL;
		osFileHeader.HighPackSize  = u64FileSize.HighPart;
		osFileHeader.HighUnpackSize  = u64FileSize.HighPart;

		
		//osFileHeader.
		u32Size = (u64FileSize.HighPart? 0x28 : 0x20);
		ocRarCleanFile.Write(&osFileHeader, u32Size);
		if (u32Size != 0x20)
		{
			return FALSE;
		}
		u32SeekParam += u32Size;

		CPINFO osCPINFO;
		GetCPInfo(CP_ACP, &osCPINFO);
		WideCharToMultiByte(CP_ACP, 0, iReplaceIterator->first.c_str(), -1, osFileHeader.Filename, MAX_PATH, (LPCSTR)&osCPINFO.DefaultChar, 0);

		u32Size = osFileHeader.NameSize;		
		ocRarCleanFile.Write(&osFileHeader.Filename, u32Size);
		if (u32Size != osFileHeader.NameSize)
		{
			return FALSE;
		}

		u32SeekParam += u32Size;
		ocRarCleanFile.Seek(u32SeekParam, JFile::FBEGIN);
		//u32SeekParam += u64TempFileLength + 
		//for (UINT64 u64Index = (u64TempFileLength < 4096? u64TempFileLength : 4096); u64Index < u64TempFileLength; u64Index += 4096 )
		u32Size = 0x10000;
		while(u64TempFileLength != 0)
		{
			osTempFile.Read(pu8Buffer, u32Size);
			u32TempCrc = crc::crc32Rar(u32TempCrc, pu8Buffer, u32Size);
			
			ocRarCleanFile.Write(pu8Buffer, u32Size);
			
			u32SeekParam += u32Size;
			u64TempFileLength -= u32Size;
		}
		osFileHeader.FileCrc = u32TempCrc ^ 0xffffffff;
		
		u32Size = ((UINT32)(&osFileHeader.HighPackSize) - (UINT32)(&osFileHeader.Type)) + (u64FileSize.HighPart? 0x8 : 0x0);
		memcpy(pu8Buffer, (UINT8*)&(osFileHeader.Type), u32Size );
		memcpy(pu8Buffer + u32Size, osFileHeader.Filename, osFileHeader.NameSize );
		osFileHeader.crc = ~crc::crc32Rar(-1, pu8Buffer, u32Size + osFileHeader.NameSize );


		ocRarCleanFile.Seek(u32CurrentFilePosition, JFile::FBEGIN);
		u32Size = (u64FileSize.HighPart? 0x28 : 0x20);
		ocRarCleanFile.Write(&osFileHeader, u32Size);
		ocRarCleanFile.Seek(u32SeekParam, JFile::FBEGIN);
		//iReplaceIterator->
	}

	u32Size = sizeof(pu8EndOfArchive);
	ocRarCleanFile.Write(pu8EndOfArchive, u32Size);
	ocRarCleanFile.Truncate();
	ocRarCleanFile.Close();
	m_pclsRarFile = 0;
// 	list <UINT32> :: iterator iListIterator;
// 	map <JString, JString>::iterator iReplaceIterator;
	return TRUE;
}