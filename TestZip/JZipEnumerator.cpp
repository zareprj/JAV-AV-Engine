#include "JZipEnumerator.h"
#include "SMSubZipEnumator.h"
#include "crc.h"
#define BufferSize 16384 

#define IM_NEEDBYTE {if(pfile_in_zip_read_info.stream.avail_in==0)return Z_OK;r=f;}
#define IM_NEXTBYTE (pfile_in_zip_read_info.stream.avail_in--,pfile_in_zip_read_info.stream.total_in++,*pfile_in_zip_read_info.stream.next_in++)

#define UPDBITS {s->bitb=b;s->bitk=k;}
#define UPDIN {pfile_in_zip_read_info.stream.avail_in=n;pfile_in_zip_read_info.stream.total_in+=(UINT32)(p-pfile_in_zip_read_info.stream.next_in);pfile_in_zip_read_info.stream.next_in=p;}
#define UPDOUT {s->write=q;}
#define UPDATE {UPDBITS UPDIN UPDOUT}
#define LEAVE {UPDATE return inflate_flush(s,r);}
//   get bytes and bits
#define LOADIN {p=pfile_in_zip_read_info.stream.next_in;n=pfile_in_zip_read_info.stream.avail_in;b=s->bitb;k=s->bitk;}
#define NEEDBYTE {if(n)r=Z_OK;else LEAVE}
#define NEXTBYTE (n--,*p++)
#define NEEDBITS(j) {while(k<(j)){NEEDBYTE;b|=((UINT32)NEXTBYTE)<<k;k+=8;}}
#define DUMPBITS(j) {b>>=(j);k-=(j);}
//   output bytes
#define WAVAIL (UINT32)(q<s->read?s->read-q-1:s->end-q)
#define LOADOUT {q=s->write;m=(UINT32)WAVAIL;m;}
#define WRAP {if(q==s->end&&s->read!=s->window){q=s->window;m=(UINT32)WAVAIL;}}
#define FLUSH {UPDOUT r=inflate_flush(s,r); LOADOUT}
#define NEEDOUT {if(m==0){WRAP if(m==0){FLUSH WRAP if(m==0) LEAVE}}r=Z_OK;}
#define OUTBYTE(a) {*q++=(BYTE)(a);m--;}
//   load local pointers
#define LOAD {LOADIN LOADOUT}
#define GRABBITS(j) {while(k<(j)){b|=((UINT32)NEXTBYTE)<<k;k+=8;}}
#define UNGRAB {c=pfile_in_zip_read_info.stream.avail_in-n;c=(k>>3)<c?k>>3:c;n+=c;p-=c;k-=c<<3;}
UINT8 JZipEnumerator::cplext[] = // Extra bits for literal codes 257..285
{
	0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2,   2,   2, 2,
	3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0, 112, 112 // 112==invalid
} ;
UINT16 JZipEnumerator::cpdist[] = // Copy offsets for distance codes 0..29
{
	1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193, 257, 385, 513,
	769, 1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577
} ;
UINT8 JZipEnumerator::cpdext[] = // Extra bits for distance codes
{
	0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6,
	7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13
} ;
UINT16 JZipEnumerator::cplens[] = // Copy lengths for literal codes 257..285
{
	3,   4,  5,  6,  7,  8,  9,  10,  11,  13,  15,  17,  19, 23, 27, 31,
	35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258,  0,  0
} ;
UINT16 JZipEnumerator::inflate_mask[]=
{
	0x0000, 0x0001, 0x0003, 0x0007, 0x000f, 0x001f, 0x003f, 0x007f, 0x00ff,
	0x01ff, 0x03ff, 0x07ff, 0x0fff, 0x1fff, 0x3fff, 0x7fff, 0xffff
} ;
UINT8 JZipEnumerator::border[] = {16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15} ;


//---------------------------------------------------------------------------------
JZipEnumerator::inflate_huft JZipEnumerator::fixed_tl[]=
{
	{{{96,7}},256}, {{{0,8}},80},  {{{0,8}},16}, {{{84,8}},115},
	{{{82,7}},31},  {{{0,8}},112}, {{{0,8}},48}, {{{0,9}},192},
	{{{80,7}},10},  {{{0,8}},96},  {{{0,8}},32}, {{{0,9}},160},
	{{{0,8}},0},    {{{0,8}},128}, {{{0,8}},64}, {{{0,9}},224},
	{{{80,7}},6},   {{{0,8}},88},  {{{0,8}},24}, {{{0,9}},144},
	{{{83,7}},59},  {{{0,8}},120}, {{{0,8}},56}, {{{0,9}},208},
	{{{81,7}},17},  {{{0,8}},104}, {{{0,8}},40}, {{{0,9}},176},
	{{{0,8}},8},    {{{0,8}},136}, {{{0,8}},72}, {{{0,9}},240},
	{{{80,7}},4},   {{{0,8}},84},  {{{0,8}},20}, {{{85,8}},227},
	{{{83,7}},43},  {{{0,8}},116}, {{{0,8}},52}, {{{0,9}},200},
	{{{81,7}},13},  {{{0,8}},100}, {{{0,8}},36}, {{{0,9}},168},
	{{{0,8}},4},    {{{0,8}},132}, {{{0,8}},68}, {{{0,9}},232},
	{{{80,7}},8},   {{{0,8}},92},  {{{0,8}},28}, {{{0,9}},152},
	{{{84,7}},83},  {{{0,8}},124}, {{{0,8}},60}, {{{0,9}},216},
	{{{82,7}},23},  {{{0,8}},108}, {{{0,8}},44}, {{{0,9}},184},
	{{{0,8}},12},   {{{0,8}},140}, {{{0,8}},76}, {{{0,9}},248},
	{{{80,7}},3},   {{{0,8}},82},  {{{0,8}},18}, {{{85,8}},163},
	{{{83,7}},35},  {{{0,8}},114}, {{{0,8}},50}, {{{0,9}},196},
	{{{81,7}},11},  {{{0,8}},98},  {{{0,8}},34}, {{{0,9}},164},
	{{{0,8}},2},    {{{0,8}},130}, {{{0,8}},66}, {{{0,9}},228},
	{{{80,7}},7},   {{{0,8}},90},  {{{0,8}},26}, {{{0,9}},148},
	{{{84,7}},67},  {{{0,8}},122}, {{{0,8}},58}, {{{0,9}},212},
	{{{82,7}},19},  {{{0,8}},106}, {{{0,8}},42}, {{{0,9}},180},
	{{{0,8}},10},   {{{0,8}},138}, {{{0,8}},74}, {{{0,9}},244},
	{{{80,7}},5},   {{{0,8}},86},  {{{0,8}},22}, {{{192,8}},0},
	{{{83,7}},51},  {{{0,8}},118}, {{{0,8}},54}, {{{0,9}},204},
	{{{81,7}},15},  {{{0,8}},102}, {{{0,8}},38}, {{{0,9}},172},
	{{{0,8}},6},    {{{0,8}},134}, {{{0,8}},70}, {{{0,9}},236},
	{{{80,7}},9},   {{{0,8}},94},  {{{0,8}},30}, {{{0,9}},156},
	{{{84,7}},99},  {{{0,8}},126}, {{{0,8}},62}, {{{0,9}},220},
	{{{82,7}},27},  {{{0,8}},110}, {{{0,8}},46}, {{{0,9}},188},
	{{{0,8}},14},   {{{0,8}},142}, {{{0,8}},78}, {{{0,9}},252},
	{{{96,7}},256}, {{{0,8}},81},  {{{0,8}},17}, {{{85,8}},131},
	{{{82,7}},31},  {{{0,8}},113}, {{{0,8}},49}, {{{0,9}},194},
	{{{80,7}},10},  {{{0,8}},97},  {{{0,8}},33}, {{{0,9}},162},
	{{{0,8}},1},    {{{0,8}},129}, {{{0,8}},65}, {{{0,9}},226},
	{{{80,7}},6},   {{{0,8}},89},  {{{0,8}},25}, {{{0,9}},146},
	{{{83,7}},59},  {{{0,8}},121}, {{{0,8}},57}, {{{0,9}},210},
	{{{81,7}},17},  {{{0,8}},105}, {{{0,8}},41}, {{{0,9}},178},
	{{{0,8}},9},    {{{0,8}},137}, {{{0,8}},73}, {{{0,9}},242},
	{{{80,7}},4},   {{{0,8}},85},  {{{0,8}},21}, {{{80,8}},258},
	{{{83,7}},43},  {{{0,8}},117}, {{{0,8}},53}, {{{0,9}},202},
	{{{81,7}},13},  {{{0,8}},101}, {{{0,8}},37}, {{{0,9}},170},
	{{{0,8}},5},    {{{0,8}},133}, {{{0,8}},69}, {{{0,9}},234},
	{{{80,7}},8},   {{{0,8}},93},  {{{0,8}},29}, {{{0,9}},154},
	{{{84,7}},83},  {{{0,8}},125}, {{{0,8}},61}, {{{0,9}},218},
	{{{82,7}},23},  {{{0,8}},109}, {{{0,8}},45}, {{{0,9}},186},
	{{{0,8}},13},   {{{0,8}},141}, {{{0,8}},77}, {{{0,9}},250},
	{{{80,7}},3},   {{{0,8}},83},  {{{0,8}},19}, {{{85,8}},195},
	{{{83,7}},35},  {{{0,8}},115}, {{{0,8}},51}, {{{0,9}},198},
	{{{81,7}},11},  {{{0,8}},99},  {{{0,8}},35}, {{{0,9}},166},
	{{{0,8}},3},    {{{0,8}},131}, {{{0,8}},67}, {{{0,9}},230},
	{{{80,7}},7},   {{{0,8}},91},  {{{0,8}},27}, {{{0,9}},150},
	{{{84,7}},67},  {{{0,8}},123}, {{{0,8}},59}, {{{0,9}},214},
	{{{82,7}},19},  {{{0,8}},107}, {{{0,8}},43}, {{{0,9}},182},
	{{{0,8}},11},   {{{0,8}},139}, {{{0,8}},75}, {{{0,9}},246},
	{{{80,7}},5},   {{{0,8}},87},  {{{0,8}},23}, {{{192,8}},0},
	{{{83,7}},51},  {{{0,8}},119}, {{{0,8}},55}, {{{0,9}},206},
	{{{81,7}},15},  {{{0,8}},103}, {{{0,8}},39}, {{{0,9}},174},
	{{{0,8}},7},    {{{0,8}},135}, {{{0,8}},71}, {{{0,9}},238},
	{{{80,7}},9},   {{{0,8}},95},  {{{0,8}},31}, {{{0,9}},158},
	{{{84,7}},99},  {{{0,8}},127}, {{{0,8}},63}, {{{0,9}},222},
	{{{82,7}},27},  {{{0,8}},111}, {{{0,8}},47}, {{{0,9}},190},
	{{{0,8}},15},   {{{0,8}},143}, {{{0,8}},79}, {{{0,9}},254},
	{{{96,7}},256}, {{{0,8}},80},  {{{0,8}},16}, {{{84,8}},115},
	{{{82,7}},31},  {{{0,8}},112}, {{{0,8}},48}, {{{0,9}},193},
	{{{80,7}},10},  {{{0,8}},96},  {{{0,8}},32}, {{{0,9}},161},
	{{{0,8}},0},    {{{0,8}},128}, {{{0,8}},64}, {{{0,9}},225},
	{{{80,7}},6},   {{{0,8}},88},  {{{0,8}},24}, {{{0,9}},145},
	{{{83,7}},59},  {{{0,8}},120}, {{{0,8}},56}, {{{0,9}},209},
	{{{81,7}},17},  {{{0,8}},104}, {{{0,8}},40}, {{{0,9}},177},
	{{{0,8}},8},    {{{0,8}},136}, {{{0,8}},72}, {{{0,9}},241},
	{{{80,7}},4},   {{{0,8}},84},  {{{0,8}},20}, {{{85,8}},227},
	{{{83,7}},43},  {{{0,8}},116}, {{{0,8}},52}, {{{0,9}},201},
	{{{81,7}},13},  {{{0,8}},100}, {{{0,8}},36}, {{{0,9}},169},
	{{{0,8}},4},    {{{0,8}},132}, {{{0,8}},68}, {{{0,9}},233},
	{{{80,7}},8},   {{{0,8}},92},  {{{0,8}},28}, {{{0,9}},153},
	{{{84,7}},83},  {{{0,8}},124}, {{{0,8}},60}, {{{0,9}},217},
	{{{82,7}},23},  {{{0,8}},108}, {{{0,8}},44}, {{{0,9}},185},
	{{{0,8}},12},   {{{0,8}},140}, {{{0,8}},76}, {{{0,9}},249},
	{{{80,7}},3},   {{{0,8}},82},  {{{0,8}},18}, {{{85,8}},163},
	{{{83,7}},35},  {{{0,8}},114}, {{{0,8}},50}, {{{0,9}},197},
	{{{81,7}},11},  {{{0,8}},98},  {{{0,8}},34}, {{{0,9}},165},
	{{{0,8}},2},    {{{0,8}},130}, {{{0,8}},66}, {{{0,9}},229},
	{{{80,7}},7},   {{{0,8}},90},  {{{0,8}},26}, {{{0,9}},149},
	{{{84,7}},67},  {{{0,8}},122}, {{{0,8}},58}, {{{0,9}},213},
	{{{82,7}},19},  {{{0,8}},106}, {{{0,8}},42}, {{{0,9}},181},
	{{{0,8}},10},   {{{0,8}},138}, {{{0,8}},74}, {{{0,9}},245},
	{{{80,7}},5},   {{{0,8}},86},  {{{0,8}},22}, {{{192,8}},0},
	{{{83,7}},51},  {{{0,8}},118}, {{{0,8}},54}, {{{0,9}},205},
	{{{81,7}},15},  {{{0,8}},102}, {{{0,8}},38}, {{{0,9}},173},
	{{{0,8}},6},    {{{0,8}},134}, {{{0,8}},70}, {{{0,9}},237},
	{{{80,7}},9},   {{{0,8}},94},  {{{0,8}},30}, {{{0,9}},157},
	{{{84,7}},99},  {{{0,8}},126}, {{{0,8}},62}, {{{0,9}},221},
	{{{82,7}},27},  {{{0,8}},110}, {{{0,8}},46}, {{{0,9}},189},
	{{{0,8}},14},   {{{0,8}},142}, {{{0,8}},78}, {{{0,9}},253},
	{{{96,7}},256}, {{{0,8}},81},  {{{0,8}},17}, {{{85,8}},131},
	{{{82,7}},31},  {{{0,8}},113}, {{{0,8}},49}, {{{0,9}},195},
	{{{80,7}},10},  {{{0,8}},97},  {{{0,8}},33}, {{{0,9}},163},
	{{{0,8}},1},    {{{0,8}},129}, {{{0,8}},65}, {{{0,9}},227},
	{{{80,7}},6},   {{{0,8}},89},  {{{0,8}},25}, {{{0,9}},147},
	{{{83,7}},59},  {{{0,8}},121}, {{{0,8}},57}, {{{0,9}},211},
	{{{81,7}},17},  {{{0,8}},105}, {{{0,8}},41}, {{{0,9}},179},
	{{{0,8}},9},    {{{0,8}},137}, {{{0,8}},73}, {{{0,9}},243},
	{{{80,7}},4},   {{{0,8}},85},  {{{0,8}},21}, {{{80,8}},258},
	{{{83,7}},43},  {{{0,8}},117}, {{{0,8}},53}, {{{0,9}},203},
	{{{81,7}},13},  {{{0,8}},101}, {{{0,8}},37}, {{{0,9}},171},
	{{{0,8}},5},    {{{0,8}},133}, {{{0,8}},69}, {{{0,9}},235},
	{{{80,7}},8},   {{{0,8}},93},  {{{0,8}},29}, {{{0,9}},155},
	{{{84,7}},83},  {{{0,8}},125}, {{{0,8}},61}, {{{0,9}},219},
	{{{82,7}},23},  {{{0,8}},109}, {{{0,8}},45}, {{{0,9}},187},
	{{{0,8}},13},   {{{0,8}},141}, {{{0,8}},77}, {{{0,9}},251},
	{{{80,7}},3},   {{{0,8}},83},  {{{0,8}},19}, {{{85,8}},195},
	{{{83,7}},35},  {{{0,8}},115}, {{{0,8}},51}, {{{0,9}},199},
	{{{81,7}},11},  {{{0,8}},99},  {{{0,8}},35}, {{{0,9}},167},
	{{{0,8}},3},    {{{0,8}},131}, {{{0,8}},67}, {{{0,9}},231},
	{{{80,7}},7},   {{{0,8}},91},  {{{0,8}},27}, {{{0,9}},151},
	{{{84,7}},67},  {{{0,8}},123}, {{{0,8}},59}, {{{0,9}},215},
	{{{82,7}},19},  {{{0,8}},107}, {{{0,8}},43}, {{{0,9}},183},
	{{{0,8}},11},   {{{0,8}},139}, {{{0,8}},75}, {{{0,9}},247},
	{{{80,7}},5},   {{{0,8}},87},  {{{0,8}},23}, {{{192,8}},0},
	{{{83,7}},51},  {{{0,8}},119}, {{{0,8}},55}, {{{0,9}},207},
	{{{81,7}},15},  {{{0,8}},103}, {{{0,8}},39}, {{{0,9}},175},
	{{{0,8}},7},    {{{0,8}},135}, {{{0,8}},71}, {{{0,9}},239},
	{{{80,7}},9},   {{{0,8}},95},  {{{0,8}},31}, {{{0,9}},159},
	{{{84,7}},99},  {{{0,8}},127}, {{{0,8}},63}, {{{0,9}},223},
	{{{82,7}},27},  {{{0,8}},111}, {{{0,8}},47}, {{{0,9}},191},
	{{{0,8}},15},   {{{0,8}},143}, {{{0,8}},79}, {{{0,9}},255}
} ;
//---------------------------------------------------------------------------------
JZipEnumerator::inflate_huft JZipEnumerator::fixed_td[] =
{
	{{{80,5}},1},  {{{87,5}},257},  {{{83,5}},17},  {{{91,5}},4097},
	{{{81,5}},5},  {{{89,5}},1025}, {{{85,5}},65},  {{{93,5}},16385},
	{{{80,5}},3},  {{{88,5}},513},  {{{84,5}},33},  {{{92,5}},8193},
	{{{82,5}},9},  {{{90,5}},2049}, {{{86,5}},129}, {{{192,5}},24577},
	{{{80,5}},2},  {{{87,5}},385},  {{{83,5}},25},  {{{91,5}},6145},
	{{{81,5}},7},  {{{89,5}},1537}, {{{85,5}},97},  {{{93,5}},24577},
	{{{80,5}},4},  {{{88,5}},769},  {{{84,5}},49},  {{{92,5}},12289},
	{{{82,5}},13}, {{{90,5}},3073}, {{{86,5}},193}, {{{192,5}},24577}
} ;
//---------------------------------------------------------------------------------
JZipEnumerator::JZipEnumerator()
{
	u32FilesCount = 0;
	u32FileChange = CompressNoChange;
	m_pclsUnzipFile = NULL ;
}
//---------------------------------------------------------------------------------
BOOLEAN JZipEnumerator::SetHandle (JFile *i_pclsFile) 
{
	m_pclsZipFile = i_pclsFile ;
	if ( m_pclsZipFile->Seek( m_u32CentralPos ,JFile::FBEGIN) == FALSE )
	{
		PutLog( FILE_SEEK_ERROR );
		return FALSE ;
	}
	if ( getLong(&osCentralHeader.uL) == UNZ_ERRNO )
	{
		PutLog( ZIP_CANNOT_GETLONG );
		return FALSE ; 
	}

	if ( getShort(&osCentralHeader.number_disk) == UNZ_ERRNO ) 
	{
		PutLog( ZIP_CANNOT_GETSHORT );
		return FALSE ; 
	}

	if (getShort (&osCentralHeader.number_disk_with_CD) == UNZ_ERRNO)
	{
		PutLog( ZIP_CANNOT_GETSHORT );
		return FALSE ; 
	}

	if (getShort (&osCentralHeader.number_entry) == UNZ_ERRNO)
	{
		PutLog( ZIP_CANNOT_GETSHORT );
		return FALSE ; 
	}

	if (getShort (&osCentralHeader.number_entry_CD) == UNZ_ERRNO)
	{
		PutLog( ZIP_CANNOT_GETSHORT );
		return FALSE ; 
	}

	if ((osCentralHeader.number_entry_CD != osCentralHeader.number_entry) || (osCentralHeader.number_disk_with_CD != 0) || (osCentralHeader.number_disk != 0))
	{
		PutLog( ZIP_FILE_FORMAT_ERROR );
		JString Message ;
		Message = i_pclsFile->GetDisplayName();
		Message += JString(MSC(FILE_COMMPERS_FORMAT_ERROR));
		MessageQueue->push(Message);
		return FALSE ;
	}

	if ( getLong(&osCentralHeader.size_central_dir) == UNZ_ERRNO )
	{
		PutLog( ZIP_CANNOT_GETLONG );
		return FALSE ; 
	}
	
	if ( getLong(&osCentralHeader.offset_central_dir) == UNZ_ERRNO )
	{
		PutLog( ZIP_CANNOT_GETLONG );
		return FALSE ; 
	}

	if (getShort (&osCentralHeader.size_comment) == UNZ_ERRNO)
	{
		PutLog( ZIP_CANNOT_GETSHORT );
		return FALSE ; 
	}

	if (m_u32CentralPos < osCentralHeader.offset_central_dir + osCentralHeader.size_central_dir)
	{
		PutLog( ZIP_FILE_FORMAT_ERROR );
		JString Message ;
		Message = i_pclsFile->GetDisplayName();
		Message += JString(MSC(FILE_COMMPERS_FORMAT_ERROR));
		MessageQueue->push(Message);
		return FALSE ; 
	}

	
	wcscpy_s (m_strCurrentFileName, m_u16FileNameSize, m_pclsZipFile->GetDisplayName().c_str());
	//_tcsncpy ( m_strCurrentFileName , m_pclsZipFile->GetDisplayName().c_str() , m_u16FileNameSize) ;
	wcscat_s (m_strCurrentFileName, m_u16FileNameSize, TEXT("->"));
	//_tcsncat ( m_strCurrentFileName , TEXT("->") , m_u16FileNameSize) ;
	m_strCurrentFileName[m_u16FileNameSize-1] = NULL ;

	NamePointer = m_strCurrentFileName + lstrlen(m_strCurrentFileName);
	byte_before_the_zipfile =  m_u32CentralPos - (osCentralHeader.offset_central_dir + osCentralHeader.size_central_dir) ;
	pos_in_central_dir = osCentralHeader.offset_central_dir ;
	num_file = 0 ;
	return TRUE ;
}
//---------------------------------------------------------------------------------
BOOLEAN JZipEnumerator::GetFile()
{
	UINT32 SizeVar  ;
	UINT32 offset_local_extrafield ;
	UINT32 size_local_extrafield ;
	_enUnZipRetVal res;
	UINT8  unzbuf[BufferSize] ;
	
	if ( CheckCurrentFileCoherencyHeader (SizeVar, offset_local_extrafield , size_local_extrafield )== UNZ_ERRNO ) 
	{
		return FALSE ;
	}

	pfile_in_zip_read_info.read_buffer =(UINT8 *) SMHeapAlloc( UNZ_BUFSIZE )  ;
	if (!pfile_in_zip_read_info.read_buffer)
	{
		return FALSE ;
	}
	pfile_in_zip_read_info.offset_local_extrafield = offset_local_extrafield ;
	pfile_in_zip_read_info.size_local_extrafield   = size_local_extrafield ;
	pfile_in_zip_read_info.pos_local_extrafield    = 0 ;
	pfile_in_zip_read_info.stream_initialised = 0 ;

	pfile_in_zip_read_info.crc32_wait = cur_file_info.crc ;
	pfile_in_zip_read_info.crc32 = 0 ;
	pfile_in_zip_read_info.compression_method = cur_file_info.compression_method ;
	pfile_in_zip_read_info.byte_before_the_zipfile = byte_before_the_zipfile ;
	pfile_in_zip_read_info.stream.total_out = 0 ;

	if (cur_file_info.compression_method)
	{
		pfile_in_zip_read_info.stream.zalloc = (alloc_func)0 ;
		pfile_in_zip_read_info.stream.zfree  = (free_func)0 ;
		pfile_in_zip_read_info.stream.opaque = (void *)0 ;
		if ( inflateInit2() == Z_OK ) 
			pfile_in_zip_read_info.stream_initialised = 1 ;
	}
	pfile_in_zip_read_info.rest_read_compressed = cur_file_info.compressed_size ;
	pfile_in_zip_read_info.rest_read_uncompressed = cur_file_info.uncompressed_size ;

	BOOLEAN extlochead = (cur_file_info.flag & 8) != 0 ;
	if (extlochead)
	{
		pfile_in_zip_read_info.crcenctest = (UINT8)((cur_file_info.dosDate >> 8) & 0xff) ;
	}
	else
	{
		pfile_in_zip_read_info.crcenctest = (UINT8)(cur_file_info.crc >> 24) ;
	}

	pfile_in_zip_read_info.encheadleft = (pfile_in_zip_read_info.encrypted ? 12 : 0) ;


	pfile_in_zip_read_info.pos_in_zipfile = cur_file_info.Offset_curfile + SIZEZIPLOCALHEADER + SizeVar ;

	pfile_in_zip_read_info.stream.avail_in = (UINT32)0 ;

	if ( JFile::GetTempFile<JCompressFile>( m_pclsUnzipFile, _T("Jav") ) == FALSE || m_pclsUnzipFile == NULL ) 
	{
		PutLog(CAN_NOT_OPEN_FILE);
		JString Message = JString(m_strCurrentFileName);
		Message += JString(MSC(FILE_CREATE_TEMP_FILE));
		MessageQueue->push(Message); 
		return FALSE ;
	}
	m_pclsUnzipFile->SetCompressor(this);
	while (1)
	{
		BOOLEAN reached_eof  = FALSE ;

		res = unzReadCurrentFile (unzbuf, &reached_eof) ;
		if (res != Z_OK) 
		{
			break ;
		}
		
		if ( m_pclsUnzipFile->Write(unzbuf ,WriteSize) == FALSE ) 
		{
			PutLog(FILE_WRITE_ERROR);
			break ;
		}

		if (reached_eof)
		{
			break ;
		}
	}
	unzCloseCurrentFile();
	if (res == Z_OK)
	{
		if (pfile_in_zip_read_info.rest_read_uncompressed == 0)
		{
			if (pfile_in_zip_read_info.crc32 != pfile_in_zip_read_info.crc32_wait)
			{		
				PutLog(ZIP_CRC_DONT_MATCH);
				JString Message = JString(m_strCurrentFileName);
				Message += JString(MSC(CRC_ERROR));
				MessageQueue->push(Message); 
				delete m_pclsUnzipFile ;
				m_pclsUnzipFile = NULL ;
				return FALSE ;
			}

		}
		m_pclsUnzipFile->SetDisplayName(JString(m_strCurrentFileName));
		return TRUE ;
	}
	else
	{
		JString Message = JString(m_strCurrentFileName);
		Message += JString(MSC(UNCOMMPESS_CROUPTED));
		MessageQueue->push(Message); 
		delete m_pclsUnzipFile ;
		m_pclsUnzipFile = NULL ;
		return FALSE ;
	}	
}
//-----------------------------------------------------------------------------
JZipEnumerator::_enUnZipRetVal JZipEnumerator::unzReadCurrentFile(UINT8 unzbuf[] , BOOLEAN *reached_eof)
{
	UINT32 iRead = 0 ;
	_enUnZipRetVal err = UNZ_ERRNO ;
	pfile_in_zip_read_info ;
	pfile_in_zip_read_info.stream.next_out = unzbuf ;
	pfile_in_zip_read_info.stream.avail_out = BufferSize ;

	if (BufferSize>pfile_in_zip_read_info.rest_read_uncompressed)
		pfile_in_zip_read_info.stream.avail_out = (UINT32)pfile_in_zip_read_info.rest_read_uncompressed ;
	while (pfile_in_zip_read_info.stream.avail_out > 0 )
	{
		if ((pfile_in_zip_read_info.stream.avail_in == 0) && (pfile_in_zip_read_info.rest_read_compressed > 0))
		{
			UINT32 uReadThis = UNZ_BUFSIZE ;
			if (pfile_in_zip_read_info.rest_read_compressed<uReadThis)
				uReadThis = (UINT32)pfile_in_zip_read_info.rest_read_compressed ;
				if (uReadThis == 0)
				{
					return UNZ_EOF ;
				}

				UINT32 SeekValue = pfile_in_zip_read_info.pos_in_zipfile + pfile_in_zip_read_info.byte_before_the_zipfile ;
				if (m_pclsZipFile->Seek(SeekValue, JFile::FBEGIN) == FALSE ) 
				{
					return UNZ_ERRNO ;
				}
				if (m_pclsZipFile->Read(pfile_in_zip_read_info.read_buffer, uReadThis ) == FALSE)
				{
					return UNZ_ERRNO ;
				}

				pfile_in_zip_read_info.pos_in_zipfile += uReadThis ;
				pfile_in_zip_read_info.rest_read_compressed -= uReadThis ;
				pfile_in_zip_read_info.stream.next_in  = (BYTE*)pfile_in_zip_read_info.read_buffer ;
				pfile_in_zip_read_info.stream.avail_in = (UINT32)uReadThis ;
		}
	
		if (pfile_in_zip_read_info.compression_method == 0)
		{
			UINT32 uDoCopy, i ;
			if (pfile_in_zip_read_info.stream.avail_out < pfile_in_zip_read_info.stream.avail_in)
				uDoCopy = pfile_in_zip_read_info.stream.avail_out ;
			else
				uDoCopy = pfile_in_zip_read_info.stream.avail_in ;

			for (i = 0 ; i < uDoCopy ; i++)
			{
				*(pfile_in_zip_read_info.stream.next_out + i) = *(pfile_in_zip_read_info.stream.next_in + i) ;
			}
			pfile_in_zip_read_info.crc32 =  crc::crc32Zip(pfile_in_zip_read_info.crc32, pfile_in_zip_read_info.stream.next_out, uDoCopy) ;
			pfile_in_zip_read_info.rest_read_uncompressed -= uDoCopy ;
			pfile_in_zip_read_info.stream.avail_in        -= uDoCopy ;
			pfile_in_zip_read_info.stream.avail_out       -= uDoCopy ;
			pfile_in_zip_read_info.stream.next_out        += uDoCopy ;
			pfile_in_zip_read_info.stream.next_in         += uDoCopy ;
			pfile_in_zip_read_info.stream.total_out       += uDoCopy ;
			iRead += uDoCopy ;
			if (pfile_in_zip_read_info.rest_read_uncompressed == 0)
			{
				if (reached_eof != 0)
					*reached_eof = true ;
			}
			err = Z_OK;
		}
		else
		{
			UINT32 uOutThis ,uTotalOutBefore, uTotalOutAfter ;
			const UINT8 *bufBefore ;

			_enUnZipRetVal flush = Z_SYNC_FLUSH ;
			uTotalOutBefore = pfile_in_zip_read_info.stream.total_out ;
			bufBefore = pfile_in_zip_read_info.stream.next_out ;
			//
			err = inflate (flush) ;
			//
			if (err != Z_STREAM_END && err != Z_OK)
			{
				break ;
			}
			uTotalOutAfter = pfile_in_zip_read_info.stream.total_out ;
			uOutThis = uTotalOutAfter - uTotalOutBefore ;
			pfile_in_zip_read_info.crc32 =  crc::crc32Zip(pfile_in_zip_read_info.crc32, bufBefore, (UINT32)(uOutThis)) ;
			pfile_in_zip_read_info.rest_read_uncompressed -= uOutThis ;
			iRead += (UINT32)(uTotalOutAfter - uTotalOutBefore) ;

			if (err == Z_STREAM_END || pfile_in_zip_read_info.rest_read_uncompressed == 0)
			{
				if (reached_eof != 0)
					*reached_eof = true ;
//				WriteSize = iRead ;
				break ;
		
			}
			if (err != Z_OK)
				break ;
		}
	}

	if (err == Z_OK || err == Z_STREAM_END)
	{
		WriteSize = iRead ;
		return Z_OK ;
	}
	
	return err ;
}
//------------------------------------------------------------------------------
JZipEnumerator::_enUnZipRetVal JZipEnumerator::CheckCurrentFileCoherencyHeader(UINT32 &SizeVar,UINT32 &offset_local_extrafield ,UINT32 &size_local_extrafield)
{
	UINT32 ReadSeek ; 
	UINT32 Magic ;
	UINT16 Data , Flage ; 
	UINT32 u32Data ;
	UINT16 size_filename ;
	UINT32 uiFilePointer =  pos_in_central_dir + byte_before_the_zipfile ;
	ReadSeek = cur_file_info.Offset_curfile + byte_before_the_zipfile ;
	if ( m_pclsZipFile->Seek( ReadSeek ,JFile::FBEGIN) == FALSE ) 
	{
		PutLog(FILE_SEEK_ERROR);
		return UNZ_ERRNO ; 
	}
	if (getLong(&Magic) == UNZ_ERRNO)	
	{
		PutLog( ZIP_CANNOT_GETLONG );
		return UNZ_ERRNO ; 
	}
	if ( Magic != 0x04034b50) 
		return UNZ_BADZIPFILE ;

	if ( getShort(&Data) == UNZ_ERRNO ) 
	{
		PutLog(ZIP_CANNOT_GETSHORT) ;
		return UNZ_ERRNO ; 
	}

	if (getShort (&Flage) == UNZ_ERRNO)
	{
		PutLog(ZIP_CANNOT_GETSHORT) ;
		return UNZ_ERRNO ; 
	}

	if (getShort (&Data) == UNZ_ERRNO)
	{
		PutLog(ZIP_CANNOT_GETSHORT) ;
		return UNZ_ERRNO ; 
	}

	if ( Data != cur_file_info.compression_method ) 
	{
		return UNZ_BADZIPFILE ;
	}

	if (cur_file_info.compression_method != 0 && cur_file_info.compression_method != Z_DEFLATED)
		return UNZ_BADZIPFILE ;

	if (getLong(&u32Data) == UNZ_ERRNO )
	{
		return UNZ_ERRNO ; 
	}

	if (getLong(&u32Data) == UNZ_ERRNO )
	{
		return UNZ_ERRNO ; 
	}

	if (u32Data != cur_file_info.crc &&	(Flage & 8) == 0)
	{
		return UNZ_BADZIPFILE ;
	}

	if (getLong(&u32Data) == UNZ_ERRNO )
	{
		return UNZ_BADZIPFILE ;
	}

	if (u32Data != cur_file_info.compressed_size && (Flage & 8) == 0)
	{
		return UNZ_BADZIPFILE ;
	}

	if ( getLong(&u32Data) == UNZ_ERRNO )
	{
		return UNZ_BADZIPFILE ;
	}

	if (u32Data != cur_file_info.uncompressed_size && (Flage & 8) == 0)
	{
		return UNZ_BADZIPFILE ;
	}

	if ( getShort(&size_filename) ==  UNZ_ERRNO ) 
	{
		return UNZ_BADZIPFILE ;
	}
	
	if (size_filename != cur_file_info.size_filename)
	{
		return UNZ_BADZIPFILE ;
	}	
	SizeVar = size_filename;

	if ( getShort(&Data) ==  UNZ_ERRNO ) 
	{
		return UNZ_BADZIPFILE ;
	}

	offset_local_extrafield = offset_curfile +SIZEZIPLOCALHEADER + size_filename;
	size_local_extrafield = Data ;
	SizeVar += size_local_extrafield ;

	return Z_OK ;  
}
//-------------------------------------------------------------------------------------
BOOLEAN JZipEnumerator::HasNextFile()
{
	BOOLEAN IsDir ;
	UINT8 Host ;

	do{

		if ( num_file == osCentralHeader.number_entry )
		{
			return FALSE ;
		}

		if (GetFileInfoInternal() == UNZ_ERRNO) 
		{
			JString Message ;
			Message = m_pclsZipFile->GetDisplayName();
			Message += JString(MSC(FILE_COMMPERS_FORMAT_ERROR));
			MessageQueue->push(Message);
			return FALSE ; 
		}

		pos_in_central_dir += SIZECENTRALDIRITEM + cur_file_info.size_filename + 
			cur_file_info.size_file_extra + cur_file_info.size_file_comment ;
		num_file++;
					
		Host = cur_file_info.version >> 8 ;
		IsDir = FALSE ;
		if (Host == 0 || Host == 7 || Host == 11 || Host == 14 )
		{
			IsDir = (cur_file_info.external_fa & 0x00000010 ) != 0 ;
		}
		else 
		{
			IsDir = (cur_file_info.external_fa & 0x40000000 ) != 0 ;
		}
		if ((cur_file_info.flag & 1) != 0)
		{
			JString Message = JString(m_strCurrentFileName);
			Message += JString(MSC(FILE_COMPERSS_PROTECT));
			MessageQueue->push(Message); 
			continue ;
		}

	}while(IsDir || cur_file_info.uncompressed_size == 0); // Pass Word Detect ;
	
	//u32FilesCount++;
	current_file_ok = TRUE ;
	return TRUE ;
}
//-------------------------------------------------------------------------------------
JZipEnumerator::_enUnZipRetVal JZipEnumerator::GetFileInfoInternalForClean()
{
	UINT32 u32Magic ;
	size_t ReadSize ;
	UINT32 uiFilePointer =  pos_in_central_dir + byte_before_the_zipfile ;
	ZeroMemory(&cur_file_info, sizeof(unz_file_info));

	if ( m_pclsZipFile->Seek(uiFilePointer , JFile::FBEGIN) == FALSE )
	{
		return  UNZ_ERRNO ;
	}

	if (getLong(&u32Magic) == UNZ_ERRNO)
	{
		return  UNZ_ERRNO ;
	}

	if(u32Magic != 0x02014b50) 
	{
		return UNZ_BADZIPFILE ;
	}

	ReadSize = sizeof(unz_file_info) - sizeof(UINT8 *) ;
	if ( m_pclsZipFile->Read(&cur_file_info , ReadSize) == FALSE || ReadSize != sizeof(unz_file_info) - sizeof(UINT8 *)) 
	{
		return UNZ_ERRNO ;
	}


	ReadSize = cur_file_info.size_filename + cur_file_info.size_file_extra + cur_file_info.size_file_comment;
	cur_file_info.TempBlock = new UINT8 [ReadSize + 1];
	if (!cur_file_info.TempBlock)
	{
		return UNZ_ERRNO ;
	}

	ZeroMemory(cur_file_info.TempBlock, ReadSize + 1);
	if ( m_pclsZipFile->Read(cur_file_info.TempBlock , ReadSize) == FALSE || ReadSize != cur_file_info.size_filename + cur_file_info.size_file_extra + cur_file_info.size_file_comment) 
	{
		delete cur_file_info.TempBlock;
		return UNZ_ERRNO ;
	}
	return Z_OK ; 
}
//-------------------------------------------------------------------------------------
JZipEnumerator::_enUnZipRetVal JZipEnumerator::GetFileInfoInternal()
{
	UINT32 u32Magic ;
	UINT32 ReadSize ;
	UINT32 uiFilePointer =  pos_in_central_dir + byte_before_the_zipfile ;
	ZeroMemory(&cur_file_info, sizeof(unz_file_info));
	if ( m_pclsZipFile->Seek(uiFilePointer , JFile::FBEGIN) == FALSE )
	{
		return  UNZ_ERRNO ;
	}

	if (getLong(&u32Magic) == UNZ_ERRNO)
	{
		return  UNZ_ERRNO ;
	}

	if(u32Magic != 0x02014b50) 
	{
		return UNZ_BADZIPFILE ;
	}

	ReadSize = sizeof(unz_file_info) - sizeof(UINT8 *) ;
	if ( m_pclsZipFile->Read(&cur_file_info , ReadSize) == FALSE || ReadSize != sizeof(unz_file_info) - sizeof(UINT8 *)) 
	{
		return UNZ_ERRNO ;
	}

	if (cur_file_info.size_filename > 0)
	{
		ReadSize = min(cur_file_info.size_filename ,(MAX_PATH -1) ) ;
		m_szCurrentFileName[ReadSize] = NULL ;
		if (m_pclsZipFile->Read(m_szCurrentFileName ,ReadSize) == FALSE ) 
		{
			PutLog(FILE_READ_ERROR);
			return UNZ_ERRNO ; 
		}
		ReadSize = cur_file_info.size_filename - ReadSize ;
		if (ReadSize != 0)
		{
			if ( m_pclsZipFile->Seek(ReadSize , JFile::FCURRENT) == FALSE ) 
			{
				PutLog(FILE_SEEK_ERROR);
				return UNZ_ERRNO ;
			}
		}
	}

#ifdef UNICODE
	MultiByteToWideChar (CP_OEMCP, 0, m_szCurrentFileName  , -1, NamePointer , m_u16FileNameSize - (NamePointer - m_strCurrentFileName) );
#else 
	strncpy (m_szCurrentFileName , NamePointer , m_u16FileNameSize - (NamePointer - m_strCurrentFileName));
#endif

	NamePointer [(m_u16FileNameSize - (NamePointer - m_strCurrentFileName) -1 )] = NULL ;
	
	ReadSize = cur_file_info.size_file_extra + cur_file_info.size_file_comment;
	if ( m_pclsZipFile->Seek(ReadSize , JFile::FCURRENT) == FALSE ) 
	{
	 	PutLog(FILE_SEEK_ERROR);
	 	return UNZ_ERRNO ;
	}

	return Z_OK ; 
}
//--------------------------------------------------------------------------------
JZipEnumerator::_enUnZipRetVal JZipEnumerator::getLong(UINT32 *o_u32X)
{
	//UINT8 u8i; 
	//UINT32 u32Temp ;
	size_t Readsize = sizeof(UINT32) ;
	assert(o_u32X) ;

	
	if ( m_pclsZipFile->Read(o_u32X , Readsize ) == FALSE  || Readsize != sizeof(UINT32)) 
	{
		PutLog(FILE_READ_ERROR);
		return UNZ_ERRNO ;
	}
		

/*	__asm
	{
		ror	u32Temp, 32
	}
	INT64 FileSeek = - 4;
	File->Seek(FileSeek , JFile::FCURRENT);
	if ( getByte(&u8i) == UNZ_ERRNO )
	{
		PutLog(ZIP_CANNOT_GETBYTE) ;
		return UNZ_ERRNO ;
	}
	u32Temp =(UINT32)u8i;

	if ( getByte(&u8i) == UNZ_ERRNO )
	{
		PutLog(ZIP_CANNOT_GETBYTE) ;
		return UNZ_ERRNO ;
	}
	u32Temp +=((UINT32)u8i)<<8;

	if ( getByte(&u8i) == UNZ_ERRNO )
	{
		PutLog(ZIP_CANNOT_GETBYTE) ;
		return UNZ_ERRNO ;
	}
	u32Temp +=((UINT32)u8i)<<16;
	
	if ( getByte(&u8i) == UNZ_ERRNO )
	{
		PutLog(ZIP_CANNOT_GETBYTE) ;
		return UNZ_ERRNO ;
	}
	u32Temp +=((UINT32)u8i)<<24;

	*o_u32X = u32Temp ; */

	return Z_OK ;
}
//---------------------------------------------------------------------------------
JZipEnumerator::_enUnZipRetVal JZipEnumerator::getByte(UINT8 *o_u8X)
{
	UINT8 u8_Temp ;
	size_t Readsize = 1 ;
	assert(o_u8X) ;
	if ( m_pclsZipFile->Read(&u8_Temp , Readsize ) == FALSE  || Readsize != 1) 
	{
		PutLog(FILE_READ_ERROR);
		return UNZ_ERRNO ;
	}
	* o_u8X = u8_Temp ;
	return Z_OK ;
}
//-----------------------------------------------------------------------------------
JZipEnumerator::_enUnZipRetVal JZipEnumerator::getShort(UINT16 *o_u16X)
{
	//UINT16 u16_Temp ;
	//UINT8 u8i; 

	assert(o_u16X) ;
	size_t RreadSize = sizeof(UINT16) ;
	if ( m_pclsZipFile->Read(o_u16X , RreadSize) == FALSE || RreadSize != sizeof(UINT16) ) 
	{
				return UNZ_ERRNO ;
	}

/*	INT64 SeekFile = - 2 ;
	if (File->Seek(SeekFile , JFile::FCURRENT ) == FALSE )
	{
		return UNZ_ERRNO ;
	}
	if ( getByte(&u8i) == UNZ_ERRNO )
	{
		PutLog(ZIP_CANNOT_GETBYTE) ;
		return UNZ_ERRNO ;
	}

	u16_Temp =(UINT32)u8i;

	if ( getByte(&u8i) == UNZ_ERRNO )
	{
		PutLog(ZIP_CANNOT_GETBYTE) ;
		return UNZ_ERRNO ;
	}

	u16_Temp +=((UINT32)u8i)<<8;

	*o_u16X = u16_Temp ;*/

	return Z_OK ;

}
//--------------------------------------------------------------------
void JZipEnumerator::ImproveFileName(TCHAR TempFileName[])
{
 TCHAR *sfn ;
 /*while(1)
 {
	 if (sfn[0] != 0 && sfn[1] == ':')
	 {
		 sfn += 2 ;
		 continue ;
	 }
	 switch (sfn[0])
	 {
	 case  '\\' :  
	 case '/' :
		 sfn++ ;
		 continue ;
	 break ;
	 }
	 const TCHAR *c ;
	 c = _tcsstr (sfn, TEXT("\\..\\"));
	 if (c != 0)
	 {
		 sfn = c + 4 ;
		 continue ;
	 }
	 c = _tcsstr (sfn, TEXT("/../"));
	 if (c != 0)
	 {
		 sfn = c + 4 ;
		 continue ;
	 }
	 c = _tcsstr (sfn, TEXT("/..\\"));
	 if (c != 0)
	 {
		 sfn = c + 4 ;
		 continue ;
	 }
	 break;
 }
 */
	sfn = _tcsrchr(TempFileName , TEXT('\\'));
	if (sfn == NULL)
	{
		return ;
	}
	//StringCchCopy (sfn, wcslen(TempFileName) - (TempFileName - sfn), TempFileName);
	//lstrcpy(sfn ,TempFileName) ;  
}
//------------------------------------------------------------------------------
/*JZipEnumerator::_enZipRetVal JZipEnumerator::OpenCurrentFile()
{
	if (current_file_ok == FALSE)
	{
		PutLog(PARAMETER_INVALID);
		return UNZ_ERRNO ;
	}

}*/
//-------------------------------------------------------------------------------
JZipEnumerator::_enUnZipRetVal JZipEnumerator::inflateInit2()
{
	pfile_in_zip_read_info.stream.state = (struct internal_state *)SMHeapAlloc(sizeof (struct internal_state)) ;
	if (pfile_in_zip_read_info.stream.state == NULL)
	{
		return Z_MEM_ERROR;
	}
	pfile_in_zip_read_info.stream.state->nowrap = 1 ;
	pfile_in_zip_read_info.stream.state->wbits = 15 ;
	if ((pfile_in_zip_read_info.stream.state->blocks = inflate_blocks_new ()) == NULL)
	{
		inflateEnd () ;
		return Z_MEM_ERROR ;
	}
	inflateReset() ;
	return Z_OK ;

}
//--------------------------------------------------------------------------------------------
JZipEnumerator::_enUnZipRetVal JZipEnumerator::inflateReset ()
{
	if (pfile_in_zip_read_info.stream.state == NULL)
		return Z_STREAM_ERROR ;

	pfile_in_zip_read_info.stream.total_in = pfile_in_zip_read_info.stream.total_out = 0 ;
	pfile_in_zip_read_info.stream.msg = NULL ;
	pfile_in_zip_read_info.stream.state->mode = pfile_in_zip_read_info.stream.state->nowrap ? IM_BLOCKS : IM_METHOD ;
	inflate_blocks_reset (pfile_in_zip_read_info.stream.state->blocks,NULL) ;
	return Z_OK ;
}
//-----------------------------------------------------------------------
JZipEnumerator::inflate_blocks_state * JZipEnumerator::inflate_blocks_new ()       // window size
{
	UINT32 w = 1 << 15 ;
	inflate_blocks_state *s ;

	if ((s = (inflate_blocks_state *)SMHeapAlloc(sizeof (struct inflate_blocks_state))) == NULL)
	{
		return s ;
	}
	if ((s->hufts = (inflate_huft *)SMHeapAlloc(sizeof (inflate_huft) * MANY)) == NULL)
	{
		SMHeapFree(s) ;
		return NULL ;
	}
	if ((s->window = (UINT8 *)SMHeapAlloc(w)) == NULL)
	{
		SMHeapFree(s->hufts) ;
		SMHeapFree(s) ;
		return NULL ;
	}
	s->end = s->window + w ;
	s->checkfn = NULL ;
	s->mode = IBM_TYPE ;
	inflate_blocks_reset (s,NULL) ;
	return s ;
}
//-----------------------------------------------------------------------
void JZipEnumerator::inflate_blocks_reset(inflate_blocks_state *s, UINT32 *c)
{
	if (c != NULL)
		*c = s->check ;
	if (s->mode == IBM_BTREE || s->mode == IBM_DTREE)
		SMHeapFree (s->sub.trees.blens) ;
	if (s->mode == IBM_CODES)
		SMHeapFree(s->sub.decode.codes) ;
	s->mode = IBM_TYPE ;
	s->bitk = 0 ;
	s->bitb = 0 ;
	s->read = s->write = s->window ;
}
//-----------------------------------------------------------------------
JZipEnumerator::_enUnZipRetVal JZipEnumerator::inflateEnd ()
{
	if (pfile_in_zip_read_info.stream.state == NULL )
		return Z_STREAM_ERROR ;

	if (pfile_in_zip_read_info.stream.state->blocks != NULL)
	{
		inflate_blocks_reset (pfile_in_zip_read_info.stream.state->blocks, NULL) ;
		SMHeapFree(pfile_in_zip_read_info.stream.state->blocks->window);
		SMHeapFree(pfile_in_zip_read_info.stream.state->blocks->hufts) ;
		SMHeapFree(pfile_in_zip_read_info.stream.state->blocks);
	}

	SMHeapFree(pfile_in_zip_read_info.stream.state) ;
	pfile_in_zip_read_info.stream.state = NULL ;
	return Z_OK ;
}
//-----------------------------------------------------------------------
/*UINT32 JZipEnumerator::ucrc32 (UINT32 crc, const BYTE *buf, UINT32 len)
{
	if (buf == NULL)
		return 0L ;
	crc = crc ^ 0xffffffffL ;
	while (len >= 8)
	{
		CRC_DO8 (buf) ;
		len -= 8 ;
	}
	if (len)
		do
		{
			CRC_DO1 (buf) ;
		} while (--len) ;
	return crc ^ 0xffffffffL ;
}*/
//-----------------------------------------------------------------------
JZipEnumerator::_enUnZipRetVal JZipEnumerator::inflate (JZipEnumerator::_enUnZipRetVal f)
{
	UINT32  b ;
	_enUnZipRetVal  r ;

	if (pfile_in_zip_read_info.stream.state == NULL || pfile_in_zip_read_info.stream.next_in == NULL)
	{
		return Z_STREAM_ERROR ;
	}
	f = f == Z_FINISH ? Z_BUF_ERROR : Z_OK ;
	r = Z_BUF_ERROR ;
	while (1)
	switch (pfile_in_zip_read_info.stream.state->mode)
	{
		case IM_METHOD:
			IM_NEEDBYTE
				if (((pfile_in_zip_read_info.stream.state->sub.method = IM_NEXTBYTE) & 0xf) != Z_DEFLATED)
				{
					pfile_in_zip_read_info.stream.state->mode = IM_BAD ;
					PutLog(ZIP_UNKNOWN_COMPRESSION_METHOD); 
					pfile_in_zip_read_info.stream.state->sub.marker = 5 ;       // can't try inflateSync
					break ;
				}
				if ((pfile_in_zip_read_info.stream.state->sub.method >> 4) + 8 > pfile_in_zip_read_info.stream.state->wbits)
				{
					pfile_in_zip_read_info.stream.state->mode = IM_BAD ;
					PutLog(ZIP_INVALID_WINDOW_SIZE);
					pfile_in_zip_read_info.stream.state->sub.marker = 5 ;       // can't try inflateSync
					break ;
				}
				pfile_in_zip_read_info.stream.state->mode = IM_FLAG ;

		case IM_FLAG:
			IM_NEEDBYTE
				b = IM_NEXTBYTE ;
			if (((pfile_in_zip_read_info.stream.state->sub.method << 8) + b) % 31)
			{
				pfile_in_zip_read_info.stream.state->mode = IM_BAD ;
				PutLog(ZIP_INCORRECT_HEADER_CHECK);
				pfile_in_zip_read_info.stream.state->sub.marker = 5 ;       // can't try inflateSync
				break ;
			}
			if (!(b & PRESET_DICT))
			{
				pfile_in_zip_read_info.stream.state->mode = IM_BLOCKS ;
				break ;
			}
			pfile_in_zip_read_info.stream.state->mode = IM_DICT4 ;

		case IM_DICT4:
			IM_NEEDBYTE
				pfile_in_zip_read_info.stream.state->sub.check.need = (UINT32)IM_NEXTBYTE << 24 ;
			pfile_in_zip_read_info.stream.state->mode = IM_DICT3 ;

		case IM_DICT3:
			IM_NEEDBYTE
				pfile_in_zip_read_info.stream.state->sub.check.need += (UINT32)IM_NEXTBYTE << 16 ;
			pfile_in_zip_read_info.stream.state->mode = IM_DICT2 ;

		case IM_DICT2:
			IM_NEEDBYTE
				pfile_in_zip_read_info.stream.state->sub.check.need += (UINT32)IM_NEXTBYTE << 8 ;
			pfile_in_zip_read_info.stream.state->mode = IM_DICT1 ;

		case IM_DICT1:
			IM_NEEDBYTE ; r ;
			pfile_in_zip_read_info.stream.state->sub.check.need += (UINT32)IM_NEXTBYTE ;
			pfile_in_zip_read_info.stream.adler = pfile_in_zip_read_info.stream.state->sub.check.need ;
			pfile_in_zip_read_info.stream.state->mode = IM_DICT0 ;
			return Z_NEED_DICT ;

		case IM_DICT0:
			pfile_in_zip_read_info.stream.state->mode = IM_BAD ;
			PutLog(ZIP_NEED_DICTIONARY)
			pfile_in_zip_read_info.stream.state->sub.marker = 0 ;       // can try inflateSync
			return Z_STREAM_ERROR ;

		case IM_BLOCKS:
			r = inflate_blocks (pfile_in_zip_read_info.stream.state->blocks, r) ;
			if (r == Z_DATA_ERROR)
			{
				pfile_in_zip_read_info.stream.state->mode = IM_BAD ;
				pfile_in_zip_read_info.stream.state->sub.marker = 0 ;       // can try inflateSync
				break ;
			}
			if (r == Z_OK)
				r = f ;
			if (r != Z_STREAM_END)
				return r ;
			r = f ;
			inflate_blocks_reset (pfile_in_zip_read_info.stream.state->blocks, &pfile_in_zip_read_info.stream.state->sub.check.was) ;
			if (pfile_in_zip_read_info.stream.state->nowrap)
			{
				pfile_in_zip_read_info.stream.state->mode = IM_DONE ;
				break ;
			}
			pfile_in_zip_read_info.stream.state->mode = IM_CHECK4 ;

		case IM_CHECK4:
			IM_NEEDBYTE
				pfile_in_zip_read_info.stream.state->sub.check.need = (UINT32)IM_NEXTBYTE << 24 ;
			pfile_in_zip_read_info.stream.state->mode = IM_CHECK3 ;

		case IM_CHECK3:
			IM_NEEDBYTE
				pfile_in_zip_read_info.stream.state->sub.check.need += (UINT32)IM_NEXTBYTE << 16 ;
			pfile_in_zip_read_info.stream.state->mode = IM_CHECK2 ;

		case IM_CHECK2:
			IM_NEEDBYTE
				pfile_in_zip_read_info.stream.state->sub.check.need += (UINT32)IM_NEXTBYTE << 8 ;
			pfile_in_zip_read_info.stream.state->mode = IM_CHECK1 ;

		case IM_CHECK1:
			IM_NEEDBYTE
				pfile_in_zip_read_info.stream.state->sub.check.need += (UINT32)IM_NEXTBYTE ;

			if (pfile_in_zip_read_info.stream.state->sub.check.was != pfile_in_zip_read_info.stream.state->sub.check.need)
			{
				pfile_in_zip_read_info.stream.state->mode = IM_BAD ;
				PutLog(ZIP_INCORRECT_DATA_CHECK);
				pfile_in_zip_read_info.stream.state->sub.marker = 5 ;       // can't try inflateSync
				break ;
			}
			pfile_in_zip_read_info.stream.state->mode = IM_DONE ;

		case IM_DONE:
			return Z_STREAM_END ;

		case IM_BAD:
			return Z_DATA_ERROR ;

		default:
			return Z_STREAM_ERROR ;
	}
}

JZipEnumerator::_enUnZipRetVal JZipEnumerator::inflate_blocks (inflate_blocks_state *s,  JZipEnumerator::_enUnZipRetVal r) // initial return code
{
	UINT32  t ;             // temporary storage
	UINT32 b ;             // bit buffer
	UINT32  k ;             // bits in bit buffer
	UINT8 *p ;             // input data pointer
	UINT32  n ;             // bytes available there
	UINT8 *q ;             // output window write pointer
	UINT32  m ;             // bytes to end of window or read pointer

	LOAD

		// process input based on current state
		while (1)
		switch (s->mode)
		{
			case IBM_TYPE:
				NEEDBITS(3)
					t = (UINT32)b & 7 ;
				s->last = t & 1 ;
				switch (t >> 1)
				{
				case 0:                         // stored
					DUMPBITS(3)
						t = k & 7 ;                 // go to byte boundary
					DUMPBITS(t)
						s->mode = IBM_LENS ;        // get length of stored block
					break ;

				case 1:                         // fixed
					{
						UINT32 bl, bd ;
						const inflate_huft *tl, *td ;

						inflate_trees_fixed (&bl, &bd, &tl, &td) ;
						s->sub.decode.codes = inflate_codes_new (bl, bd, tl, td) ;
						if (s->sub.decode.codes == NULL)
						{
							r = Z_MEM_ERROR ;
							LEAVE
						}
					}
					DUMPBITS(3)
						s->mode = IBM_CODES ;
					break ;

				case 2:                         // dynamic
					DUMPBITS(3)
						s->mode = IBM_TABLE ;
					break ;

				case 3:                         // illegal
					DUMPBITS(3)
						s->mode = IBM_BAD ;
					PutLog(ZIP_INVALID_BLOCK_TYPE) ;
					r = Z_DATA_ERROR ;
					LEAVE
				}
				break ;

			case IBM_LENS:
				NEEDBITS(32)
					if ((((~b) >> 16) & 0xffff) != (b & 0xffff))
					{
						s->mode = IBM_BAD ;
						PutLog(ZIP_INVALID_STORED_BLOCK_LENGTHS) ;
						r = Z_DATA_ERROR ;
						LEAVE
					}
					s->sub.left = (UINT32)b & 0xffff ;
					b = k = 0 ;                      // dump bits
					s->mode = s->sub.left ? IBM_STORED : (s->last ? IBM_DRY : IBM_TYPE) ;
					break ;

			case IBM_STORED:
				if (n == 0)
					LEAVE
					NEEDOUT
					t = s->sub.left ;
				if (t > n)
					t = n ;
				if (t > m)
					t = m ;
				memcpy (q, p, t) ;
				p += t ;
				n -= t ;
				q += t ;
				m -= t ;
				if ((s->sub.left -= t) != 0)
					break ;
				s->mode = s->last ? IBM_DRY : IBM_TYPE ;
				break ;

			case IBM_TABLE:
				NEEDBITS(14)
					s->sub.trees.table = t = (UINT32)b & 0x3fff ;
				if ((t & 0x1f) > 29 || ((t >> 5) & 0x1f) > 29)
				{
					s->mode = IBM_BAD ;
					PutLog(ZIP_TOO_MANY_LENGTH_OR_DISTANCE_SYMBOLS);
					r = Z_DATA_ERROR ;
					LEAVE
				}
				t = 258 + (t & 0x1f) + ((t >> 5) & 0x1f) ;
				if ((s->sub.trees.blens = (UINT32*)SMHeapAlloc(t * sizeof (UINT32))) == NULL)
				{
					r = Z_MEM_ERROR ;
					LEAVE
				}
				DUMPBITS(14)
					s->sub.trees.index = 0 ;
				s->mode = IBM_BTREE ;

			case IBM_BTREE:
				while (s->sub.trees.index < 4 + (s->sub.trees.table >> 10))
				{
					NEEDBITS(3)
						s->sub.trees.blens[border[s->sub.trees.index++]] = (UINT32)b & 7 ;
					DUMPBITS(3)
				}
				while (s->sub.trees.index < 19)
					s->sub.trees.blens[border[s->sub.trees.index++]] = 0 ;
				s->sub.trees.bb = 7 ;
				r = inflate_trees_bits (s->sub.trees.blens, &s->sub.trees.bb, &s->sub.trees.tb, s->hufts) ;
				if (r != Z_OK)
				{
					if (r == Z_DATA_ERROR)
					{
						SMHeapFree (s->sub.trees.blens) ;
						s->mode = IBM_BAD ;
					}
					LEAVE
				}
				s->sub.trees.index = 0 ;
				s->mode = IBM_DTREE ;

			case IBM_DTREE:
				while (t = s->sub.trees.table, s->sub.trees.index < 258 + (t & 0x1f) + ((t >> 5) & 0x1f))
				{
					inflate_huft *h ;
					UINT32 i, j, c ;

					t = s->sub.trees.bb ;
					NEEDBITS(t)
						h = s->sub.trees.tb + ((UINT32)b & inflate_mask[t]) ;
					t = h->word.what.Bits ;
					c = h->base ;
					if (c < 16)
					{
						DUMPBITS(t)
							s->sub.trees.blens[s->sub.trees.index++] = c ;
					}
					else // c == 16..18
					{
						i = c == 18 ? 7 : c - 14 ;
						j = c == 18 ? 11 : 3 ;
						NEEDBITS(t + i)
							DUMPBITS(t)
							j += (UINT32)b & inflate_mask[i] ;
						DUMPBITS(i)
							i = s->sub.trees.index ;
						t = s->sub.trees.table ;
						if (i + j > 258 + (t & 0x1f) + ((t >> 5) & 0x1f) || (c == 16 && i < 1))
						{
							SMHeapFree( s->sub.trees.blens) ;
							s->mode = IBM_BAD ;
							PutLog(ZIP_INVALID_BIT_LENGTH_REPEAT);
							r = Z_DATA_ERROR ;
							LEAVE
						}
						c = c == 16 ? s->sub.trees.blens[i - 1] : 0 ;
						do
						{
							s->sub.trees.blens[i++] = c ;
						} while (--j) ;
						s->sub.trees.index = i ;
					}
				}
				s->sub.trees.tb = NULL ;
				{
					UINT32 bl, bd ;
					inflate_huft *tl, *td ;
					inflate_codes_state *c ;

					bl = 9 ;         // must be <= 9 for lookahead assumptions
					bd = 6 ;         // must be <= 9 for lookahead assumptions
					t = s->sub.trees.table ;
					r = inflate_trees_dynamic (257 + (t & 0x1f), 1 + ((t >> 5) & 0x1f),
						s->sub.trees.blens, &bl, &bd, &tl, &td, s->hufts) ;
					if (r != Z_OK)
					{
						if (r == (UINT32)Z_DATA_ERROR)
						{
							SMHeapFree( s->sub.trees.blens);
							s->mode = IBM_BAD ;
						}
						LEAVE
					}
					if ((c = inflate_codes_new (bl, bd, tl, td)) == NULL)
					{
						r = Z_MEM_ERROR ;
						LEAVE
					}
					s->sub.decode.codes = c ;
				}
				SMHeapFree( s->sub.trees.blens);
				s->mode = IBM_CODES ;

			case IBM_CODES:
				UPDATE
					if ((r = inflate_codes (s, r)) != Z_STREAM_END)
						return inflate_flush (s, r) ;
				r = Z_OK ;
				SMHeapFree(s->sub.decode.codes) ;
				LOAD
				if (!s->last)
				{
					s->mode = IBM_TYPE ;
					break ;
				}
				s->mode = IBM_DRY ;

			case IBM_DRY:
				FLUSH
					if (s->read != s->write)
						LEAVE
						s->mode = IBM_DONE ;

			case IBM_DONE:
				r = Z_STREAM_END ;
				LEAVE

			case IBM_BAD:
				r = Z_DATA_ERROR ;
				LEAVE

			default:
				r = Z_STREAM_ERROR ;
				LEAVE
		}
}
//--------------------------------------------------------------------------
JZipEnumerator::_enUnZipRetVal JZipEnumerator::inflate_trees_bits (UINT32 *c,           // 19 code lengths
								UINT32 *bb,          // bits tree desired/actual depth
								inflate_huft **tb, // bits tree result
								inflate_huft *hp  // space for trees
								)
					
{
	assert(c && bb && tb && hp);
	_enUnZipRetVal  r ;
	UINT32  hn = 0 ;        // hufts used in space
	UINT32  *v ;             // work area for huft_build

	if ((v = (UINT32*)SMHeapAlloc(19*sizeof (UINT32))) == NULL)
		return Z_MEM_ERROR ;

	r = huft_build (c, 19, 19, (UINT16*)NULL, (UINT8*)NULL, tb, bb, hp, &hn, v) ;
	if (r == Z_DATA_ERROR)
	{
		 PutLog(ZIP_OVERSUBSCRIBED_DYNAMIC_BIT_LENGTHS_TREE);
	}
	else if (r == Z_BUF_ERROR || *bb == 0)
	{
		PutLog(ZIP_INCOMPLETE_DYNAMIC_BIT_LENGTHS_TREE);
		r = Z_DATA_ERROR ;
	}
	SMHeapFree(v) ;
	return r ;
}

//---------------------------------------------------------------------------
void JZipEnumerator::inflate_trees_fixed (UINT32 *bl, UINT32 *bd, const inflate_huft ** tl, const inflate_huft **td)                
{
	*bl = fixed_bl ;
	*bd = fixed_bd ;
	*tl = fixed_tl ;
	*td = fixed_td ;
}
//---------------------------------------------------------------------------
JZipEnumerator::_enUnZipRetVal JZipEnumerator::huft_build (UINT32 *b,           
								UINT32 n,             
								UINT32 s,             
								const UINT16 *d,      
								const UINT8 *e,      
								inflate_huft **t,  
								UINT32 *m,            
								inflate_huft *hp,   
								UINT32 *hn,           
								UINT32 *v)            
{
	UINT32 a ;                       // counter for codes of length k
	UINT32 c[BMAX + 1] ;             // bit length count table
	UINT32 f ;                       // i repeats in table every f entries
	int g ;                        // maximum code length
	int h ;                        // table level
	register UINT32 i ;              // counter, current code
	register UINT32 j ;              // counter
	register int k ;               // number of bits in current code
	int l ;                        // bits per table (returned in m)
	UINT32 mask ;                    // (1 << w) - 1, to avoid cc -O bug on HP
	register UINT32 *p ;             // pointer into c[], b[], or v[]
	inflate_huft *q ;              // points to current table
	inflate_huft r ;      // table entry for structure assignment
	inflate_huft *u[BMAX] ;        // table stack
	register int w ;               // bits before this table == (l * h)
	UINT32 x[BMAX + 1] ;             // bit offsets, then code stack
	UINT32 *xp ;                     // pointer into x
	int y ;                        // number of dummy codes added
	UINT32 z ;                       // number of entries in current table

	// Generate counts for each bit length
	p = c ;
	#define C0 *p++ = 0 ;
	#define C2 C0 C0 C0 C0
	#define C4 C2 C2 C2 C2
    // clear c[]--assume BMAX + 1 is 16
	C4 ; p ;
	p = b ;
	i = n ;
	do
	{
		c[*p++]++ ;                  // assume all entries <= BMAX
	} while (--i) ;
	if (c[0] == n)                   // null input--all zero length codes
	{
		*t = (inflate_huft *)NULL ;
		*m = 0 ;
		return Z_OK ;
	}

	// Find minimum and maximum length, bound *m by those
	l = *m ;
	for (j = 1 ; j <= BMAX ; j++)
		if (c[j])
			break ;
	k = j ;                          // minimum code length
	if ((UINT32)l < j)
		l = j ;
	for (i = BMAX ; i ; i--)
		if (c[i])
			break ;
	g = i ;                          // maximum code length
	if ((UINT32)l > i)
		l = i ;
	*m = l ;

	// Adjust last length count to fill out codes, if needed
	for (y = 1 << j ; j < i ; j++, y <<= 1)
		if ((y -= c[j]) < 0)
			return Z_DATA_ERROR ;
	if ((y -= c[i]) < 0)
		return Z_DATA_ERROR ;
	c[i] += y ;

	// Generate starting offsets into the value table for each length
	x[1] = j = 0 ;
	p = c + 1 ;
	xp = x + 2 ;
	while (--i)
	{                 // note that i == g from above
		*xp++ = (j += *p++) ;
	}

	// Make a table of values in order of bit lengths
	p = b ;
	i = 0 ;
	do
	{
		if ((j = *p++) != 0)
			v[x[j]++] = i ;
	} while (++i < n) ;
	n = x[g] ;                       // set n to length of v


	// Generate the Huffman codes and for each, make the table entries
	x[0] = i = 0 ;                 // first Huffman code is zero
	p = v ;                        // grab values in bit order
	h = -1 ;                       // no tables yet--level -1
	w = -l ;                       // bits decoded == (l * h)
	u[0] = (inflate_huft *)NULL ;        // just to keep compilers happy
	q = (inflate_huft *)NULL ;   // ditto
	z = 0 ;                        // ditto

	// go through the bit lengths (k already is bits in shortest code)
	for ( ; k <= g ; k++)
	{
		a = c[k] ;
		while (a--)
		{
			// here i is the Huffman code of length k bits for value *p
			// make tables up to required level
			while (k > w + l)
			{
				h++ ;
				w += l ;                             // previous table always l bits

				// compute minimum size table less than or equal to l bits
				z = g - w ;
				z = z > (UINT32)l ? l : z ;            // table size upper limit
				if ((f = 1 << (j = k - w)) > a + 1)  // try a k-w bit table
				{                                    // too few codes for k-w bit table
					f -= a + 1 ;                     // deduct codes from patterns left
					xp = c + k ;
					if (j < z)
						while (++j < z)              // try smaller tables up to z bits
						{
							if ((f <<= 1) <= *++xp)
								break ;              // enough codes to use up j bits
							f -= *xp ;               // else deduct codes from patterns
						}
				}
				z = 1 << j ;                         // table entries for j-bit table

				// allocate new table
				if (*hn + z > MANY)     // (note: doesn't matter for fixed)
					return Z_DATA_ERROR ;  // overflow of MANY
				u[h] = q = hp + *hn ;
				*hn += z ;

				// connect to last table, if there is one
				if (h)
				{
					x[h] = i ;                          // save pattern for backing up
					r.word.what.Bits = (UINT8)l ;        // bits to dump before this table
					r.word.what.Exop = (UINT8)j ;        // bits in this table
					j = i >> (w - l) ;
					r.base = (UINT32)(q - u[h - 1] - j) ; // offset to this table
					u[h - 1][j] = r ;                   // connect to last table
				}
				else
					*t = q ;               // first table is returned result
			}

			// set up table entry in r
			r.word.what.Bits = (UINT8)(k - w) ;
			if (p >= v + n)
				r.word.what.Exop = 128 + 64 ;      // out of values--invalid code
			else if (*p < s)
			{
				r.word.what.Exop = (UINT8)(*p < 256 ? 0 : 32 + 64) ;     // 256 is end-of-block
				r.base = *p++ ;          // simple code is just the value
			}
			else
			{
				r.word.what.Exop = (UINT8)(e[*p - s] + 16 + 64) ;// non-simple--look up in lists
				r.base = d[*p++ - s] ;
			}

			f = 1 << (k - w) ;
			for (j = i >> w ; j < z ; j += f)
				q[j] = r ;

			
			for (j = 1 << (k - 1) ; i & j ; j >>= 1)
				i ^= j ;
			i ^= j ;

	
			mask = (1 << w) - 1 ;   
			while ((i & mask) != x[h])
			{
				h-- ;  
				w -= l ;
				mask = (1 << w) - 1 ;
			}
		}
	}
	return y != 0 && g != 1 ? Z_BUF_ERROR : Z_OK ;
}
//---------------------------------------------------------------------------
JZipEnumerator::_enUnZipRetVal JZipEnumerator::inflate_trees_dynamic (UINT32 nl,           // number of literal/length codes
													UINT32 nd,           // number of distance codes
													UINT32 *c,           // that many (total) code lengths
													UINT32 *bl,          // literal desired/actual bit depth
													UINT32 *bd,          // distance desired/actual bit depth
													inflate_huft **tl, // literal/length tree result
													inflate_huft **td, // distance tree result
													inflate_huft *hp
													)       // for messages
{
	assert(c && bl && 	bd &&  tl  && td && hp) ;
	_enUnZipRetVal   r ;
	UINT32  hn = 0 ;   // hufts used in space
	UINT32 *v ;        // work area for huft_build

	// allocate work area
	if ((v = (UINT32*)SMHeapAlloc(288 * sizeof (UINT32))) == NULL)
		return Z_MEM_ERROR ;

	// build literal/length tree
	r = huft_build (c, nl, 257, cplens, cplext, tl, bl, hp, &hn, v) ;
	if (r != Z_OK || *bl == 0)
	{
		if (r == Z_DATA_ERROR)
		{
			PutLog(ZIP_OVERSUBSCRIBED_LITERAL_LENGTH_TREE);
		}
		else if (r != Z_MEM_ERROR)
		{
			PutLog(ZIP_INCOMPLETE_LITERAL_LENGTH_TREE);
			r = Z_DATA_ERROR ;
		}
		SMHeapFree(v);
		return r ;
	}

	r = huft_build (c + nl, nd, 0, cpdist, cpdext, td, bd, hp, &hn, v) ;
	if (r != Z_OK || (*bd == 0 && nl > 257))
	{
		if (r == Z_DATA_ERROR)
		{
			PutLog(ZIP_OVERSUBSCRIBED_DISTANCE_TREE);
		}
		else if (r == Z_BUF_ERROR)
		{
			PutLog(ZIP_INCOMPLETE_DISTANCE_TREE);
			r = Z_DATA_ERROR ;
		}
		else if (r != Z_MEM_ERROR)
		{
			PutLog(ZIP_EMPTY_DISTANCE_TREE_WITH_LENGTHS);
			r = Z_DATA_ERROR ;
		}
		SMHeapFree(v) ;
		return r ;
	}

	SMHeapFree(v) ;
	return Z_OK ;
}

//-------------------------------------------------------------------------------------------
JZipEnumerator::inflate_codes_state *JZipEnumerator::inflate_codes_new (UINT32 bl, UINT32 bd, const inflate_huft *tl,
														 const inflate_huft *td )
{
	assert(tl && td) ;
	inflate_codes_state *c ;
	if ((c = (inflate_codes_state *)SMHeapAlloc( sizeof (struct inflate_codes_state) )) != NULL)
	{
		c->mode  = START ;
		c->lbits = (UINT8)bl ;
		c->dbits = (UINT8)bd ;
		c->ltree = tl ;
		c->dtree = td ;
	}
	return c ;
}
//-------------------------------------------------------------------------------------------
JZipEnumerator::_enUnZipRetVal JZipEnumerator::inflate_codes (inflate_blocks_state *s, _enUnZipRetVal r)
{
	UINT32  j ;                // temporary storage
	const inflate_huft *t ;  // temporary pointer
	UINT32  e ;                // extra bits or operation
	UINT32 b ;                // bit buffer
	UINT32  k ;                // bits in bit buffer
	UINT8 *p ;                // input data pointer
	UINT32  n ;                // bytes available there
	UINT8 *q ;                // output window write pointer
	UINT32  m ;                // bytes to end of window or read pointer
	UINT8 *f ;                // pointer to copy strings from
	inflate_codes_state *c = s->sub.decode.codes ;  // codes state
	assert(s);
	// copy input/output information to locals (UPDATE macro restores)
	LOAD

		// process input and output based on current state
		while(1)
		switch (c->mode)
		{                                     // waiting for "i:"=input, "o:"=output, "x:"=nothing
			case START:                       // x: set up for LEN

				if (m >= 258 && n >= 10)
				{
					UPDATE
						r = inflate_fast (c->lbits, c->dbits, c->ltree, c->dtree, s) ;
					LOAD
						if (r != Z_OK)
						{
							c->mode = r == Z_STREAM_END ? WASH : BADCODE ;
							break ;
						}
				}
				c->sub.code.need = c->lbits ;
				c->sub.code.tree = c->ltree ;
				c->mode = LEN ;

			case LEN:                         // i: get length/literal/eob next
				j = c->sub.code.need ;
				NEEDBITS(j)
					t = c->sub.code.tree + ((UINT32)b & inflate_mask[j]) ;
				DUMPBITS(t->word.what.Bits)
					e = (UINT32)(t->word.what.Exop) ;
				if (e == 0)                   // literal
				{
					c->sub.lit = t->base ;
					c->mode = LIT ;
					break ;
				}
				if (e & 16)                   // length
				{
					c->sub.copy.get = e & 15 ;
					c->len = t->base ;
					c->mode = LENEXT ;
					break ;
				}
				if ((e & 64) == 0)            // next table
				{
					c->sub.code.need = e ;
					c->sub.code.tree = t + t->base ;
					break ;
				}
				if (e & 32)                   // end of block
				{
					c->mode = WASH ;
					break ;
				}
				c->mode = BADCODE ;           // invalid code
				PutLog(ZIP_INVALID_LITERAL_LENGTH_CODE);
				r = Z_DATA_ERROR ;
				LEAVE

			case LENEXT:                      // i: getting length extra (have base)
				j = c->sub.copy.get ;
				NEEDBITS(j)
					c->len += (UINT32)b & inflate_mask[j] ;
				DUMPBITS(j)
					c->sub.code.need = c->dbits ;
				c->sub.code.tree = c->dtree ;
				c->mode = DIST ;

			case DIST:                        // i: get distance next
				j = c->sub.code.need ;
				NEEDBITS(j)
					t = c->sub.code.tree + ((UINT32)b & inflate_mask[j]) ;
				DUMPBITS(t->word.what.Bits)
					e = (UINT32)(t->word.what.Exop) ;
				if (e & 16)                   // distance
				{
					c->sub.copy.get  = e & 15 ;
					c->sub.copy.dist = t->base ;
					c->mode = DISTEXT ;
					break ;
				}
				if ((e & 64) == 0)            // next table
				{
					c->sub.code.need = e ;
					c->sub.code.tree = t + t->base ;
					break ;
				}
				c->mode = BADCODE ;           // invalid code
				PutLog(ZIP_INVALID_DISTANCE_CODE);
				r = Z_DATA_ERROR ;
				LEAVE

			case DISTEXT:                     // i: getting distance extra
				j = c->sub.copy.get ;
				NEEDBITS(j)
					c->sub.copy.dist += (UINT32)b & inflate_mask[j] ;
				DUMPBITS(j)
				c->mode = COPY ;

			case COPY:                        // o: copying bytes in window, waiting for space
				f = q - c->sub.copy.dist ;
				while (f < s->window)         // modulo window size-"while" instead
					f += s->end - s->window ; // of "if" handles invalid distances
				while (c->len)
				{
					NEEDOUT
						OUTBYTE(*f++)
						if (f == s->end)
							f = s->window ;
					c->len-- ;
				}
				c->mode = START ;
				break ;

			case LIT:                         // o: got literal, waiting for output space
				NEEDOUT
					OUTBYTE(c->sub.lit)
					c->mode = START ;
				break ;

			case WASH:                        // o: got eob, possibly more output
				if (k > 7)                    // return unused byte, if any
				{
					//Assert(k < 16, "inflate_codes grabbed too many bytes")
					k -= 8 ;
					n++ ;
					p-- ;                     // can always return one
				}
				FLUSH
					if (s->read != s->write)
						LEAVE
						c->mode = END ;

			case END:
				r = Z_STREAM_END ;
				LEAVE

			case BADCODE:                     // x: got error
				r = Z_DATA_ERROR ;
				LEAVE

			default:
				r = Z_STREAM_ERROR ;
				LEAVE
		}
}
//--------------------------------------------------------------------------------------------
JZipEnumerator::_enUnZipRetVal JZipEnumerator::inflate_fast (UINT32 bl, UINT32 bd, const inflate_huft *tl,
						  const inflate_huft *td, // need separate declaration for Borland C + +
						  inflate_blocks_state *s)
{
	assert( tl && td && s) ;
	const inflate_huft *t ; // temporary pointer
	UINT32   e ;              // extra bits or operation
	UINT32  b ;              // bit buffer
	UINT32   k ;              // bits in bit buffer
	UINT8  *p ;              // input data pointer
	UINT32   n ;              // bytes available there
	UINT8  *q ;              // output window write pointer
	UINT32   m ;              // bytes to end of window or read pointer
	UINT32   ml ;             // mask for literal/length tree
	UINT32   md ;             // mask for distance tree
	UINT32   c ;              // bytes to copy
	UINT32   d ;              // distance back to copy from
	UINT8  *r ;              // copy source pointer

	// load input, output, bit values
	LOAD

		// initialize masks
		ml = inflate_mask[bl] ;
	md = inflate_mask[bd] ;

	// do until not enough input or output space for fast loop
	do                          // assume called with m >= 258 && n >= 10
	{
		// get literal/length code
		GRABBITS(20)                // max bits for literal/length code
			if ((e = (t = tl + ((UINT32)b & ml))->word.what.Exop) == 0)
			{
				DUMPBITS(t->word.what.Bits)
				*q++ = (UINT8)t->base ;
				m-- ;
				continue ;
			}
			while(1)
			{
				DUMPBITS(t->word.what.Bits)
					if (e & 16)
					{
						// get extra bits for length
						e &= 15 ;
						c = t->base + ((UINT32)b & inflate_mask[e]) ;
						DUMPBITS(e)

						// decode distance base of block to copy
						GRABBITS(15) ;           // max bits for distance code
						e = (t = td + ((UINT32)b & md))->word.what.Exop ;
						while(1)
						{
							DUMPBITS(t->word.what.Bits)
								if (e & 16)
								{
									// get extra bits to add to distance base
									e &= 15 ;
									GRABBITS(e)         // get extra bits (up to 13)
										d = t->base + ((UINT32)b & inflate_mask[e]) ;
									DUMPBITS(e)
									// do the copy
									m -= c ;
									r = q - d ;
									if (r < s->window)                  // wrap if needed
									{
										do
										{
											r += s->end - s->window ;        // force pointer in window
										} while (r < s->window) ;            // covers invalid distances
										e = (UINT32) (s->end - r) ;
										if (c > e)
										{
											c -= e ;                         // wrapped copy
											do
											{
												*q++ = *r++ ;
											} while (--e) ;
											r = s->window ;
											do
											{
												*q++ = *r++ ;
											} while (--c) ;
										}
										else                              // normal copy
										{
											*q++ = *r++ ; c-- ;
											*q++ = *r++ ; c-- ;
											do
											{
												*q++ = *r++ ;
											} while (--c) ;
										}
									}
									else                                /* normal copy */
									{
										*q++ = *r++ ; c-- ;
										*q++ = *r++ ; c-- ;
										do
										{
											*q++ = *r++ ;
										} while (--c) ;
									}
									break ;
								}
								else if ((e & 64) == 0)
								{
									t += t->base ;
									e = (t += ((UINT32)b & inflate_mask[e]))->word.what.Exop ;
								}
								else
								{

									PutLog(ZIP_INVALID_DISTANCE_CODE);
									UNGRAB
										UPDATE
										return Z_DATA_ERROR ;
								}
						} ;
						break ;
					}
					if ((e & 64) == 0)
					{
						t += t->base ;
						if ((e = (t += ((UINT32)b & inflate_mask[e]))->word.what.Exop) == 0)
						{
							DUMPBITS(t->word.what.Bits)
							*q++ = (BYTE)t->base ;
							m-- ;
							break ;
						}
					}
					else if (e & 32)
					{
						UNGRAB
							UPDATE
							return Z_STREAM_END ;
					}
					else
					{
						PutLog(ZIP_INVALID_LITERAL_LENGTH_CODE);
						UNGRAB
							UPDATE
							return Z_DATA_ERROR ;
					}
			} ;
	} while (m >= 258 && n >= 10) ;

	// not enough input or output--restore pointers and return
	UNGRAB
		UPDATE
		return Z_OK ;
}

// copy as much as possible from the sliding window to the output area
JZipEnumerator::_enUnZipRetVal JZipEnumerator::inflate_flush (inflate_blocks_state *s, _enUnZipRetVal r)
{
	assert(s);
	UINT32 n ;
	UINT8 *p ;
	UINT8 *q ;

	// local copies of source and destination pointers
	p = pfile_in_zip_read_info.stream.next_out ;
	q = s->read ;

	// compute number of bytes to copy as far as end of window
	n = (UINT32)((q <= s->write ? s->write : s->end) - q) ;
	if (n > pfile_in_zip_read_info.stream.avail_out)
		n = pfile_in_zip_read_info.stream.avail_out ;
	if (n && r == Z_BUF_ERROR)
		r = Z_OK ;

	// update counters
	pfile_in_zip_read_info.stream.avail_out -= n ;
	pfile_in_zip_read_info.stream.total_out += n ;

	// update check information
	if (s->checkfn != NULL)
		pfile_in_zip_read_info.stream.adler = s->check = (*s->checkfn)(s->check, q, n) ;

	// copy as far as end of window
	if (n != 0)          // check for n!=0 to avoid waking up CodeGuard
	{
		memcpy (p, q, n) ;
		p += n ;
		q += n ;
	}

	// see if more to copy at beginning of window
	if (q == s->end)
	{
		// wrap pointers
		q = s->window ;
		if (s->write == s->end)
			s->write = s->window ;

		// compute bytes to copy
		n = (UINT32)(s->write - q) ;
		if (n > pfile_in_zip_read_info.stream.avail_out)
			n = pfile_in_zip_read_info.stream.avail_out ;
		if (n && r == Z_BUF_ERROR)
			r = Z_OK ;

		// update counters
		pfile_in_zip_read_info.stream.avail_out -= n ;
		pfile_in_zip_read_info.stream.total_out += n ;

		// update check information
		if (s->checkfn != NULL)
			pfile_in_zip_read_info.stream.adler = s->check = (*s->checkfn)(s->check, q, n) ;

		// copy
		if (n != 0)
		{
			memcpy (p, q, n) ;
			p +=n ;
			q +=n ;
		}
	}

	// update pointers
	pfile_in_zip_read_info.stream.next_out = p ;
	s->read = q ;

	// done
	return r ;
}
inline UINT32 JZipEnumerator::unzlocal_SearchCentralDir (JFile * i_pclsFile)
{

	UINT32 SeekValue = 0;
	UINT8 buf [BUFREADCOMMENT + 4] ;

	if ( i_pclsFile->Seek(SeekValue,JFile::FBEGIN) == FALSE )
	{
		return 0xFFFFFFFF ;
	}

	UINT32 Magic ; 
	SeekValue = sizeof (Magic) ;
	if ( i_pclsFile->Read(&Magic , SeekValue) == FALSE || SeekValue != sizeof (Magic)) 
	{
		return 0xFFFFFFFF ; 
	}
	if (Magic != 0x04034b50 )
	{
		return 0xFFFFFFFF ; 
	}

	UINT32 uSizeFile = i_pclsFile->GetFileLength();
	if (uSizeFile == 0)
	{
		return 0xFFFFFFFF ;
	}

	UINT32 uMaxBack = 0xFFFF ; // maximum size of global comment
	if (uMaxBack > uSizeFile)
		uMaxBack = uSizeFile ;

	UINT32 uPosFound = 0xFFFFFFFF ;
	UINT32 uBackRead = 4 ;
	while (uBackRead < uMaxBack)
	{
		UINT32 uReadSize, uReadPos ;
		int i ;
		if (uBackRead + BUFREADCOMMENT > uMaxBack)
			uBackRead = uMaxBack ;
		else
			uBackRead += BUFREADCOMMENT ;

		uReadPos = uSizeFile - uBackRead ;
		uReadSize = ((BUFREADCOMMENT + 4) < (uSizeFile - uReadPos)) ? (BUFREADCOMMENT + 4) : (uSizeFile - uReadPos) ;
		if (i_pclsFile->Seek(uReadPos, JFile::FBEGIN) == FALSE)
		{
			break ;
		}
		if (i_pclsFile->Read(buf, uReadSize ) == FALSE )
		{
			break ;
		}
		for (i = (int)uReadSize - 3 ; (i--) >= 0 ; )
		{
			
			if (*(UINT32 *)(buf + i) == 0x06054b50 ) 
			{
				uPosFound = uReadPos + i ;
				break ;
			}
		}
		if (uPosFound != 0)
			break ;
	}
	return uPosFound ;
}
//--------------------------------------------------------------------
void JZipEnumerator::SetDeleteIndex(UINT32 u32Index)
{
	ocDeleteIndexList.push_back(u32Index);
}
//--------------------------------------------------------------------
void JZipEnumerator::SetReplaceIndex(JString ocFileNameinZip, JString ocFileName)
{
	ocReplacedItemIndex.insert(Pair(ocFileNameinZip, ocFileName));
}
//--------------------------------------------------------------------
void JZipEnumerator::unzCloseCurrentFile ()
{
	if (pfile_in_zip_read_info.read_buffer != NULL)
	{
		SMHeapFree (pfile_in_zip_read_info.read_buffer) ;
		pfile_in_zip_read_info.read_buffer = NULL ;
	}

	if (pfile_in_zip_read_info.stream_initialised)
	{
		inflateEnd();
	}
	pfile_in_zip_read_info.stream_initialised = 0 ;
}
//----------------------------------------------------------------------
BOOLEAN JZipEnumerator::CloseCompessFile()
{
	if (ocDeleteIndexList.size() > 0)
	{
		ocZipFileName = m_pclsZipFile->GetName();
		// Call CreateThread for deleting or replacing zip files
		//CreateThread(NULL, 0, CleanThread, this, 0, NULL);
		CleanZipFile();
/*		return FALSE;*/
	}
	else
	{
		m_pclsZipFile->Close();
	}
	return TRUE;
}
//-----------------------------------------------------------------------
UINT32 JZipEnumerator::GetCurrentFileIndex()
{
	return (num_file - 1) ;
}
//-----------------------------------------------------------------------
JFile* JZipEnumerator::GetCurrentFile() 
{
	return m_pclsUnzipFile ;
}
//-----------------------------------------------------------------------
void  JZipEnumerator::SetMessageQueue(queue <JString> * i_MessageQueue)
{
	MessageQueue = i_MessageQueue ;	
}
//-----------------------------------------------------------------------
IUnCompersser * JZipEnumerator::IsArchive( JFile * i_pclsFile)
{
	UINT32 u32CenteralDir = unzlocal_SearchCentralDir(i_pclsFile) ;
	if ( u32CenteralDir == 0xFFFFFFFF ) 
	{
		return NULL ;
	}
	JZipEnumerator* Zip= new JZipEnumerator();
	if (Zip == FALSE)
	{
		return  NULL ;
	}
	Zip->m_u32CentralPos = u32CenteralDir ;
	return Zip;
}
//-----------------------------------------------------------------------
UINT32 JZipEnumerator::CleanZipFile()
{
	list <unz_file_info> ocDirectoryList;
	list <unz_file_info> :: iterator pocDirectoryListIterator;
	JFile ocZipCleanFile;
	UINT32 u32Size, u32CentralDirectorySize = 0, u32Counter = 0, u32SeekParam = 0, u32DeletedCounter = 0, u32Magic = 0x02014b50;
	if(!ocZipCleanFile.Open(ocZipFileName, FALSE, TRUE))
	{
		// Could Not Open Archive For Write
		//CloseHandle(m_pclsZipFile->GetHandle());
		m_pclsZipFile->CloseHandle();
		if(!ocZipCleanFile.Open(ocZipFileName, FALSE, TRUE))
		{
			return -1;
		}
	}
	m_pclsZipFile = &ocZipCleanFile;
	list <UINT32> :: iterator iListIterator;
	map <JString, JString>::iterator iReplaceIterator;
	num_file = 0;
	pos_in_central_dir = osCentralHeader.offset_central_dir ;
	BOOLEAN bCheck;
	if (ocDeleteIndexList.size() > 0)
	{
		BOOLEAN IsDir ;
		UINT8 Host ;
		u32FileChange = CompressFileChanged;
		do{
			if ( num_file == osCentralHeader.number_entry )
			{
				break;
			}

			for (iListIterator = ocDeleteIndexList.begin(), bCheck = FALSE; iListIterator != ocDeleteIndexList.end() && !bCheck; ++iListIterator)
			{
				if (u32Counter == *iListIterator)
				{
					u32Counter++;
					u32DeletedCounter++;
					bCheck = TRUE;
				}
			}

			if (GetFileInfoInternalForClean() == JZipEnumerator::UNZ_ERRNO)
			{
				return FALSE ;
			}


			pos_in_central_dir += SIZECENTRALDIRITEM + cur_file_info.size_filename + 
				cur_file_info.size_file_extra + cur_file_info.size_file_comment ;
			num_file++;

			if(bCheck) 
			{
				continue;
			}

			ocDirectoryList.push_back( cur_file_info );
			Host = cur_file_info.version >> 8 ;
			IsDir = FALSE ;
			if (Host == 0 || Host == 7 || Host == 11 || Host == 14 )
			{
				IsDir = (cur_file_info.external_fa & 0x00000010 ) != 0 ;
			}
			else 
			{
				IsDir = (cur_file_info.external_fa & 0x40000000 ) != 0 ;
			}
			if ((cur_file_info.flag & 1) != 0)
			{
				continue ;
			}
			u32Counter++;

		}while(TRUE);

		if (!ocDirectoryList.empty())
		{
			ocZipCleanFile.Seek(u32SeekParam, JFile::FBEGIN);
			for (pocDirectoryListIterator = ocDirectoryList.begin(); pocDirectoryListIterator != ocDirectoryList.end(); ++pocDirectoryListIterator)
			{
				if (u32SeekParam != pocDirectoryListIterator->Offset_curfile)
				{
					UINT32 u32TempSeekParam = pocDirectoryListIterator->Offset_curfile;
					u32Size = sizeof(JZipEnumerator :: unz_file_Header) + pocDirectoryListIterator->size_filename + pocDirectoryListIterator->size_file_extra + pocDirectoryListIterator->compressed_size;;
					UINT8 * TempBuffer = new UINT8 [u32Size];

					ocZipCleanFile.Seek(u32TempSeekParam, JFile::FBEGIN);
					ocZipCleanFile.Read(TempBuffer, u32Size);

					ocZipCleanFile.Seek(u32SeekParam, JFile::FBEGIN);
					ocZipCleanFile.Write(TempBuffer, u32Size);
					pocDirectoryListIterator->Offset_curfile = u32SeekParam;
					delete TempBuffer;
				}
				u32SeekParam += sizeof(JZipEnumerator :: unz_file_Header) + pocDirectoryListIterator->size_filename + pocDirectoryListIterator->size_file_extra + pocDirectoryListIterator->compressed_size;
			}
			ocZipCleanFile.Seek(u32SeekParam, JFile::FBEGIN);

		}
		else
		{
			if (ocReplacedItemIndex.size() == 0)
			{
				u32FileChange = CompressFileDeleted;
				ocZipCleanFile.Close();
				ocZipCleanFile.Delete(ocZipFileName);
			}
		}
	}

	ocZipCleanFile.Seek(u32SeekParam, JFile::FBEGIN);
	// Iterate The Map for replaced file in zip
	for(iReplaceIterator = ocReplacedItemIndex.begin(); iReplaceIterator != ocReplacedItemIndex.end(); iReplaceIterator++)
	{
		SubZipEnumator ocZipCreator;
		UINT8 * pu8Buffer;

		pu8Buffer = ocZipCreator.CreateZipFromFile(iReplaceIterator->first, iReplaceIterator->second);
		if (pu8Buffer == NULL)
		{
			JString Message = JString(iReplaceIterator->first);
			Message += JString(MSC(CANNOT_CREATE_ZIP_ENTRY));
			MessageQueue->push(Message); 
			//return -1;
			continue;
		}
		u32Size = ocZipCreator.GetFileAndHeaderSize();		
		ocZipCreator.osFileInfo.Offset_curfile = u32SeekParam;
		ocDirectoryList.push_back( ocZipCreator.osFileInfo );

		WideCharToMultiByte(CP_OEMCP, 0, iReplaceIterator->first.c_str(), -1, (char*)ocZipCreator.osFileInfo.TempBlock, ocZipCreator.osFileInfo.size_filename, 0, 0);

		ocZipCleanFile.Write(pu8Buffer, u32Size);
		ocZipCreator.Close();
		JFile::Delete(iReplaceIterator->second);
		u32SeekParam += u32Size;
		osCentralHeader.number_entry++;
	}

	///

	osCentralHeader.number_entry -= u32DeletedCounter;
	osCentralHeader.number_entry_CD = osCentralHeader.number_entry;

	ocZipCleanFile.Seek(u32SeekParam, JFile::FBEGIN);
	osCentralHeader.offset_central_dir = u32SeekParam;
	for (pocDirectoryListIterator = ocDirectoryList.begin(); pocDirectoryListIterator != ocDirectoryList.end(); ++pocDirectoryListIterator)
	{
		u32Size = sizeof(UINT32);
		u32CentralDirectorySize += u32Size;
		ocZipCleanFile.Write(&u32Magic, u32Size);

		u32Size = sizeof(JZipEnumerator :: unz_file_info) - 4;
		u32CentralDirectorySize += u32Size;
		JZipEnumerator :: unz_file_info ocTemp = *pocDirectoryListIterator;
		ocZipCleanFile.Write(&ocTemp, u32Size);

		u32Size = pocDirectoryListIterator->size_filename + pocDirectoryListIterator->size_file_extra + pocDirectoryListIterator->size_file_comment;
		u32CentralDirectorySize += u32Size;
		ocZipCleanFile.Write(pocDirectoryListIterator->TempBlock, u32Size);
	}

	osCentralHeader.size_central_dir = u32CentralDirectorySize;

	u32Size = sizeof(JZipEnumerator :: CentralHeader);
	u32SeekParam = 0;
	ocZipCleanFile.Seek(u32SeekParam, JFile::FCURRENT);
	ocZipCleanFile.Write(&osCentralHeader, u32Size);

	ocZipCleanFile.Truncate();
	ocZipCleanFile.Close();
	return 0;
}
UINT32 JZipEnumerator::GetFilesCount()
{
	return u32FilesCount;
}