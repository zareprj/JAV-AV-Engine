// This file contains texts for translating binary operation such as Function Binary or Condition Expression

#include "BinaryTranslate.h"
#include "strsafe.h"
#ifdef ALLOC_PRAGMA
#pragma alloc_text(PAGE, TranslateFunc)
#pragma alloc_text(PAGE, GetForReg)
#pragma alloc_text(PAGE, Translate)
#endif

// List of Texts order by BytesEnum enum definition
WCHAR * pszBinaryString []=
{
	L"Inst",
	L"InstCount",
	L"Opcode",
	L"ModRM",
	L"SIB",
	L"Data",
	L"MemByteRegDigit",
	L"MemByteReg",
	L"MemByteDigit",
	L"MemWordRegDigit",
	L"MemWordReg",
	L"MemWordDigit",
	L"MemDwordRegDigit",
	L"MemDwordReg",
	L"MemDwordDigit",
	L"ax",
	L"eax",
	L"al",
	L"ah",
	L"cx",
	L"ecx",
	L"cl",
	L"ch",
	L"dx",
	L"edx",
	L"dl",
	L"dh",
	L"bx",
	L"ebx",
	L"bl",
	L"bh",
	L"sp",
	L"esp",
	L"bp",
	L"ebp",
	L"si",
	L"esi",
	L"di",
	L"edi",
	L"eip",
	L"ByteDigit",
	L"WordDigit",
	L"DwordDigit",

	L"=",
	L"!=",
	L">",
	L"<",
	L">=",
	L"<=",
	L"+",
	L"-",
	L"*",
	L"/",
	L"&",
	L"|",
	L"^",
	L"&&",
	L"||",
	L"Instruction",
	L"StackDown",
	L"Operand0",
	L"Operand1",
	L"Param",
	L"ParentParam",
	L"SetEntryPoint",
	L"GetEntryPoint",
	L",",
	L";",
	L"TRUE",
	L"FALSE",
	L"Jump",
	L"Return",
	L"Min",
	L"Read",
	L"ReadMem",
	L"Write",
	L"Seek",
	L"SeekPhysical",
	L"Begin",
	L"Current",
	L"End",
	
	L"RVAToOffset",
	L"OffsetToRVA",

	L"GetCurrecntSectionIndex",
	

	L"Truncate",
	L"SetZero",
	L"Alloc",
	L"Free",

	L"SetVirusLength",
	L"GetFileLength",

	L"AAA",
	L"AAD",
	L"AAM",
	L"AAS",
	L"AAS8",
	L"ADC",
	L"ADC16",
	L"ADC8",
	L"ADD",
	L"ADD16",
	L"ADD8",
	L"ADDPS",
	L"ADDSS",
	L"AND",
	L"AND16",
	L"AND8",
	L"ANDNPS",
	L"ANDPS",
	L"ARPL",
	L"ARPL16",
	L"BOUND",
	L"BOUND16",
	L"BSF",
	L"BSF16",
	L"BSR",
	L"BSR16",
	L"BSWAP",
	L"BSWAP16",
	L"BT",
	L"BT16",
	L"BT8",
	L"BTC",
	L"BTC16",
	L"BTC8",
	L"BTR",
	L"BTR16",
	L"BTR8",
	L"BTS",
	L"BTS16",
	L"BTS8",
	L"CALL",
	L"CALL16",
	L"CBW",
	L"CDQ",
	L"CLC",
	L"CLD",
	L"CLI",
	L"CLTS",
	L"CMC",
	L"CMOVAE",
	L"CMOVAE16",
	L"CMOVC",
	L"CMOVC16",
	L"CMOVNA",
	L"CMOVNA16",
	L"CMOVNBE",
	L"CMOVNBE16",
	L"CMOVNG",
	L"CMOVNG16",
	L"CMOVNGE",
	L"CMOVNGE16",
	L"CMOVNL",
	L"CMOVNL16",
	L"CMOVNLE",
	L"CMOVNLE16",
	L"CMOVNO",
	L"CMOVNO16",
	L"CMOVNS",
	L"CMOVNS16",
	L"CMOVNZ",
	L"CMOVNZ16",
	L"CMOVO",
	L"CMOVO16",
	L"CMOVPE",
	L"CMOVPE16",
	L"CMOVPO",
	L"CMOVPO16",
	L"CMOVS",
	L"CMOVS16",
	L"CMOVZ",
	L"CMOVZ16",
	L"CMP",
	L"CMP16",
	L"CMP8",
	L"CMPPS",
	L"CMPSB",
	L"CMPSD",
	L"CMPSD16",
	L"CMPSS",
	L"CMPXCHG",
	L"CMPXCHG16",
	L"CMPXCHG8",
	L"CMPXCHG8B",
	L"COMISS",
	L"CPUID",
	L"CVTPI2PS",
	L"CVTPS2PI",
	L"CVTSI2SS",
	L"CVTSS2SI",
	L"CVTTPS2PI",
	L"CVTTSS2SI",
	L"CWD",
	L"CWDE",
	L"DAA",
	L"DAA8",
	L"DAS",
	L"DAS8",
	L"DEC",
	L"DEC16",
	L"DEC8",
	L"DIV",
	L"DIV16",
	L"DIV8",
	L"DIVPS",
	L"DIVSS",
	L"EMMS",
	L"ENTER",
	L"ENTER8",
	L"F2XM1",
	L"FABS",
	L"FADD",
	L"FADDP",
	L"FBLD",
	L"FBLD8",
	L"FBSTP",
	L"FBSTP8",
	L"FCHS",
	L"FCLEX",
	L"FCMOVB",
	L"FCMOVBE",
	L"FCMOVE",
	L"FCMOVNB",
	L"FCMOVNBE",
	L"FCMOVNE",
	L"FCMOVNU",
	L"FCMOVU",
	L"FCOM",
	L"FCOMI",
	L"FCOMIP",
	L"FCOMP",
	L"FCOMPP",
	L"FCOS",
	L"FDECSTP",
	L"FDIV",
	L"FDIVP",
	L"FDIVR",
	L"FDIVRP",
	L"FFREE",
	L"FIADD",
	L"FICOM",
	L"FICOMP",
	L"FIDIV",
	L"FIDIVR",
	L"FILD",
	L"FIMUL",
	L"FINCSTP",
	L"FINIT",
	L"FIST",
	L"FISTP",
	L"FISUB",
	L"FISUBR",
	L"FLD",
	L"FLD1",
	L"FLD8",
	L"FLDCW",
	L"FLDENV",
	L"FLDL2E",
	L"FLDL2T",
	L"FLDLG2",
	L"FLDLN2",
	L"FLDPI",
	L"FLDZ",
	L"FMUL",
	L"FMULP",
	L"FNCLEX",
	L"FNINIT",
	L"FNOP",
	L"FNSAVE",
	L"FNSTCW",
	L"FNSTENV",
	L"FNSTSW",
	L"FNSTSW16",
	L"FPATAN",
	L"FPREM",
	L"FPREM1",
	L"FPTAN",
	L"FRNDINT",
	L"FRSTOR",
	L"FSAVE",
	L"FSCALE",
	L"FSIN",
	L"FSINCOS",
	L"FSQRT",
	L"FST",
	L"FSTCW",
	L"FSTENV",
	L"FSTP",
	L"FSTP8",
	L"FSTSW",
	L"FSUB",
	L"FSUBP",
	L"FSUBR",
	L"FSUBRP",
	L"FTST",
	L"FUCOM",
	L"FUCOMI",
	L"FUCOMIP",
	L"FUCOMP",
	L"FUCOMPP",
	L"FWAIT",
	L"FXAM",
	L"FXCH",
	L"FXRSTOR",
	L"FXSAVE",
	L"FXTRACT",
	L"FYL2X",
	L"FYL2XP1",
	L"HLT",
	L"IDIV",
	L"IDIV16",
	L"IDIV8",
	L"IMUL",
	L"IMUL16",
	L"IMUL8",
	L"IN_",
	L"IN_16",
	L"IN_8",
	L"INC",
	L"INC16",
	L"INC8",
	L"INS",
	L"INSB",
	L"INSD",
	L"INSW",
	L"INT3",            
	L"INTO",
	L"INVD",
	L"INVLPG",
	L"IRET",
	L"IRETD",
	L"JAE",
	L"JB",
	L"JC",
	L"JECXZ",
	L"JMP",
	L"JMP16",
	L"JNA",
	L"JNB",
	L"JNBE",
	L"JNG",
	L"JNGE",
	L"JNL",
	L"JNLE",
	L"JNO",
	L"JNS",
	L"JNZ",
	L"JO",
	L"JPE",
	L"JPO",
	L"JS",
	L"JZ",
	L"LAHF",
	L"LAR",
	L"LAR16",
	L"LDMXCSR",
	L"LDS",
	L"LDS16",
	L"LEA",
	L"LEA16",
	L"LEAVE",
	L"LEAVE16",
	L"LES",
	L"LES16",
	L"LFS",
	L"LFS16",
	L"LGDT",
	L"LGS",
	L"LGS16",
	L"LIDT",
	L"LLDT",
	L"LLDT16",
	L"LMSW",
	L"LMSW16",
	L"LOCK",
	L"LODS",
	L"LODSB",
	L"LODSB16",
	L"LODSD",
	L"LODSD16",
	L"LOOP",
	L"LOOPNZ",
	L"LOOPZ",
	L"LSL",
	L"LSL16",
	L"LSS",
	L"LSS16",
	L"LTR",
	L"LTR16",
	L"MASKMOVQ",
	L"MAXPS",
	L"MAXSS",
	L"MINPS",
	L"MINSS",
	L"MOV",
	L"MOV16",
	L"MOV8",
	L"MOVAPS",
	L"MOVD",
	L"MOVD16",
	L"MOVHLPS",
	L"MOVHPS",
	L"MOVLHPS",
	L"MOVLPS",
	L"MOVMSKPS",
	L"MOVNTPS",
	L"MOVNTQ",
	L"MOVQ",
	L"MOVSB",
	L"MOVSD",
	L"MOVSD16",
	L"MOVSS",
	L"MOVSX",
	L"MOVSX16",
	L"MOVSX8",
	L"MOVUPS",
	L"MOVZX",
	L"MOVZX16",
	L"MOVZX8",
	L"MUL",
	L"MUL16",
	L"MUL8",
	L"MULPS",
	L"MULSS",
	L"NEG",
	L"NEG16",
	L"NEG8",
	L"NOP",
	L"NOT",
	L"NOT16",
	L"NOT8",
	L"OR",
	L"OR16",
	L"OR8",
	L"ORPS",
	L"OUT_",
	L"OUT_16",
	L"OUT_8",
	L"OUTS",
	L"OUTSB",
	L"OUTSD",
	L"OUTSW",
	L"PACKSSDW",
	L"PACKSSWB",
	L"PACKUSWB",
	L"PADDB",
	L"PADDD",
	L"PADDSB",
	L"PADDSW",
	L"PADDUSB",
	L"PADDUSW",
	L"PADDW",
	L"PAND",
	L"PANDN",
	L"PAVGB",
	L"PAVGW",
	L"PCMPEQB",
	L"PCMPEQD",
	L"PCMPEQW",
	L"PCMPGTB",
	L"PCMPGTD",
	L"PCMPGTW",
	L"PEXTRW",
	L"PINSRW",
	L"PMADDWD",
	L"PMAXSW",
	L"PMAXUB",
	L"PMINSW",
	L"PMINUB",
	L"PMOVMSKB",
	L"PMOVMSKB16",
	L"PMULHUW",
	L"PMULHW",
	L"PMULLW",
	L"POP",
	L"POP16",
	L"POP8",
	L"POPAD",
	L"POPAD16",
	L"POPF",
	L"POPFD",
	L"POPFD16",
	L"POR",
	L"PREFETCHNTA8",
	L"PREFETCHT08",
	L"PREFETCHT18",
	L"PREFETCHT28",
	L"PSADBW",
	L"PSHUFW",
	L"PSLLD",
	L"PSLLD8",
	L"PSLLQ",
	L"PSLLQ8",
	L"PSLLW",
	L"PSLLW8",
	L"PSRAD",
	L"PSRAD8",
	L"PSRAW",
	L"PSRAW8",
	L"PSRLD",
	L"PSRLD8",
	L"PSRLQ",
	L"PSRLQ8",
	L"PSRLW",
	L"PSRLW8",
	L"PSUBB",
	L"PSUBD",
	L"PSUBSB",
	L"PSUBSW",
	L"PSUBUSB",
	L"PSUBUSW",
	L"PSUBW",
	L"PUNPCKHBW",
	L"PUNPCKHDQ",
	L"PUNPCKHWD",
	L"PUNPCKLBW",
	L"PUNPCKLDQ",
	L"PUNPCKLWD",
	L"PUSH",
	L"PUSH16",
	L"PUSH8",
	L"PUSHAD",
	L"PUSHAD16",
	L"PUSHF",
	L"PUSHFD",
	L"PUSHFD16",
	L"PXOR",
	L"RCL",
	L"RCL16",
	L"RCL8",
	L"RCPPS",
	L"RCPSS",
	L"RCR",
	L"RCR16",
	L"RCR8",
	L"RDMSR",
	L"RDPMC",
	L"RDTSC",
	L"REP",
	L"REPE",
	L"REPNE",
	L"REPNZ",
	L"REPZ",
	L"RET",
	L"RETF",
	L"ROL",
	L"ROL16",
	L"ROL8",
	L"ROR",
	L"ROR16",
	L"ROR8",
	L"RSM",
	L"RSQRTPS",
	L"RSQRTSS",
	L"SAHF",
	L"SAL",
	L"SAL16",
	L"SAL8",
	L"SAR",
	L"SAR16",
	L"SAR8",
	L"SBB",
	L"SBB16",
	L"SBB8",
	L"SCAS",
	L"SCASB",
	L"SCASB16",
	L"SCASD",
	L"SCASD16",
	L"SETB8",
	L"SETNA8",
	L"SETNB8",
	L"SETNBE8",
	L"SETNG8",
	L"SETNGE8",
	L"SETNL8",
	L"SETNLE8",
	L"SETNO8",
	L"SETNS8",
	L"SETNZ8",
	L"SETO8",
	L"SETPE8",
	L"SETPO8",
	L"SETS8",
	L"SETZ8",
	L"SFENCE",
	L"SGDT",
	L"SHL",
	L"SHL16",
	L"SHL8",
	L"SHLD",
	L"SHLD16",
	L"SHR",
	L"SHR16",
	L"SHR8",
	L"SHRD",
	L"SHRD16",
	L"SHUFPS",
	L"SIDT",
	L"SLDT",
	L"SLDT16",
	L"SMSW",
	L"SMSW16",
	L"SQRTPS",
	L"SQRTSS",
	L"STC",
	L"STD",
	L"STI",
	L"STMXCSR",
	L"STOS",
	L"STOSB",
	L"STOSB16",
	L"STOSD",
	L"STOSD16",
	L"STR",
	L"STR16",
	L"SUB",
	L"SUB16",
	L"SUB8",
	L"SUBPS",
	L"SUBSS",
	L"SYSENTER",
	L"SYSEXIT",
	L"TEST",
	L"TEST16",
	L"TEST8",
	L"UCOMISS",
	L"UD2",
	L"UNPCKHPS",
	L"UNPCKLPS",
	L"VERR",
	L"VERR16",
	L"VERW",
	L"VERW16",
	L"WAIT",
	L"WBINVD",
	L"WRMSR",
	L"XADD",
	L"XADD16",
	L"XADD8",
	L"XCHG",
	L"XCHG16",
	L"XCHG8",
	L"XLAT",
	L"XLATB",
	L"XOR",
	L"XOR16",
	L"XOR8",
	L"XORPS"
};

// Translate Condition Expression 
void Translate(ConditionExpression * posCondition, WCHAR * pszOutputString, UINT32 nOutputLength)
{
	FunctionBinary * posFunction = (FunctionBinary *)SMAlloc(sizeof(FunctionBinary));
	PAGED_CODE();

	if (posFunction == NULL)
	{
		return;
	}
	posFunction->pbyExp = posCondition->pbyExp;
	posFunction->nLength = posCondition->nLength;
	TranslateFunc(posFunction, pszOutputString, nOutputLength);
	SMFree(posFunction);
}

// Get Reg Text
BOOLEAN GetForReg( UINT8 byRegIndex, WCHAR * pszOutputString, UINT32 nOutputLength ) 
{
	PAGED_CODE();

	switch (byRegIndex)
	{
	case ax:		
		StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ax]);
		StringCchCatW(pszOutputString, nOutputLength, L" ");
		return TRUE;

	case eax:
		StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eax]);
		StringCchCatW(pszOutputString, nOutputLength, L" ");
		return TRUE;

	case al:
		StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[al]);
		StringCchCatW(pszOutputString, nOutputLength, L" ");
		return TRUE;

	case ah:
		StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ah]);
		StringCchCatW(pszOutputString, nOutputLength, L" ");
		return TRUE;

	case cx:
		StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[cx]);
		StringCchCatW(pszOutputString, nOutputLength, L" ");
		return TRUE;

	case ecx:
		StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ecx]);
		StringCchCatW(pszOutputString, nOutputLength, L" ");
		return TRUE;

	case cl:
		StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[cl]);
		StringCchCatW(pszOutputString, nOutputLength, L" ");
		return TRUE;

	case ch:
		StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ch]);
		StringCchCatW(pszOutputString, nOutputLength, L" ");
		return TRUE;

	case dx:
		StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[dx]);
		StringCchCatW(pszOutputString, nOutputLength, L" ");
		return TRUE;

	case edx:
		StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[edx]);
		StringCchCatW(pszOutputString, nOutputLength, L" ");
		return TRUE;

	case dl:
		StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[dl]);
		StringCchCatW(pszOutputString, nOutputLength, L" ");
		return TRUE;

	case dh:
		StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[dh]);
		StringCchCatW(pszOutputString, nOutputLength, L" ");
		return TRUE;

	case bx:
		StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[bx]);
		StringCchCatW(pszOutputString, nOutputLength, L" ");
		return TRUE;

	case ebx:
		StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ebx]);
		StringCchCatW(pszOutputString, nOutputLength, L" ");
		return TRUE;

	case bl:
		StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[bl]);
		StringCchCatW(pszOutputString, nOutputLength, L" ");
		return TRUE;

	case bh:
		StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[bh]);
		StringCchCatW(pszOutputString, nOutputLength, L" ");
		return TRUE;

	case sp:
		StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[sp]);
		StringCchCatW(pszOutputString, nOutputLength, L" ");
		return TRUE;

	case esp:
		StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[esp]);
		StringCchCatW(pszOutputString, nOutputLength, L" ");
		return TRUE;

	case bp:
		StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[bp]);
		StringCchCatW(pszOutputString, nOutputLength, L" ");
		return TRUE;

	case ebp:
		StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ebp]);
		StringCchCatW(pszOutputString, nOutputLength, L" ");
		return TRUE;

	case si:
		StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[si]);
		StringCchCatW(pszOutputString, nOutputLength, L" ");
		return TRUE;

	case esi:
		StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[esi]);
		StringCchCatW(pszOutputString, nOutputLength, L" ");
		return TRUE;

	case di:
		StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[di]);
		StringCchCatW(pszOutputString, nOutputLength, L" ");
		return TRUE;

	case edi:
		StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[edi]);
		StringCchCatW(pszOutputString, nOutputLength, L" ");
		return TRUE;

	case eip:
		StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eip]);
		StringCchCatW(pszOutputString, nOutputLength, L" ");
		return TRUE;

	case Operand0:
		StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Operand0]);
		StringCchCatW(pszOutputString, nOutputLength, L" ");
		return TRUE;

	case Operand1:
		StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Operand1]);
		StringCchCatW(pszOutputString, nOutputLength, L" ");
		return TRUE;

	case Opcode:
		StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Opcode]);
		StringCchCatW(pszOutputString, nOutputLength, L" ");
		return TRUE;

	case Data:
		StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Data]);
		StringCchCatW(pszOutputString, nOutputLength, L" ");
		return TRUE;
	}
	return FALSE;
}

// Translate Function Binary 
void TranslateFunc(FunctionBinary * posFunction, WCHAR * pszOutputString, UINT32 nOutputLength)
{
	UINT32	nLength = 0;
	PAGED_CODE();

	StringCchCopyW(pszOutputString, nOutputLength, L"");
	
	while (nLength != posFunction->nLength)
	{
		switch (posFunction->pbyExp[nLength++])
		{
		case Ins:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Ins]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");			
			break;

		case InsCount:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[InsCount]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			break;

		case Opcode:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Opcode]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			break;

		case ModRM:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ModRM]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			break;

		case SIB:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[SIB]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			break;

		case Data:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Data]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
//			return TRUE;
			break;

		case MemByteRegDigit:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[MemByteRegDigit]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case MemByteReg:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[MemByteReg]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
//			__asm int 3
			break;

		case MemByteDigit:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[MemByteDigit]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case MemWordRegDigit:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[MemWordRegDigit]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case MemWordReg:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[MemWordReg]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
//			__asm int 3
			break;

		case MemWordDigit:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[MemWordDigit]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case MemDwordRegDigit:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[MemDwordRegDigit]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case MemDwordReg:
			{
				UINT32 nStringLength ;
				StringCchCatW(pszOutputString, nOutputLength, L" [");
				if (!GetForReg(posFunction->pbyExp[nLength++], pszOutputString, nOutputLength))
				{
					if(posFunction->pbyExp[nLength - 1] == Param)
					{
						StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Param]);
						StringCchLengthW(pszOutputString, nOutputLength, &nStringLength);
						StringCchPrintfW(pszOutputString, nOutputLength, L"%s%d ", pszOutputString, posFunction->pbyExp[nLength++]);
					}
				}
				StringCchCatW(pszOutputString, nOutputLength, L"] ");
				break;
			}

		case MemDwordDigit:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[MemDwordDigit]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case ax:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ax]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case eax:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eax]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case al:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[al]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case ah:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ah]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case cx:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[cx]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case ecx:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ecx]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case cl:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[cl]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case ch:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ch]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case dx:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[dx]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case edx:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[edx]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case dl:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[dl]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case dh:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[dh]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case bx:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[bx]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case ebx:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ebx]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case bl:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[bl]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case bh:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[bh]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case sp:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[sp]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case esp:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[esp]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
//			__asm int 3
			break;

		case bp:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[bp]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case ebp:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ebp]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case si:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[si]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case esi:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[esi]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case di:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[di]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case edi:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[edi]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case eip:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eip]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			break;


		case ByteDigit:
			{
				WCHAR pszTemp[3];
				StringCchPrintfW(pszTemp, 3, L"%X", posFunction->pbyExp[nLength++]);
				StringCchCatW(pszOutputString, nOutputLength, pszTemp);
				StringCchCatW(pszOutputString, nOutputLength, L" ");
				break;
			}

		case WordDigit:
			{
				WCHAR pszTemp[5];
				StringCchPrintfW(pszTemp, 5, L"%X", *(UINT16*)(posFunction->pbyExp + nLength));
				nLength += 2;
				StringCchCatW(pszOutputString, nOutputLength, pszTemp);
				StringCchCatW(pszOutputString, nOutputLength, L" ");
//				__asm int 3
				break;
			}

		case DwordDigit:
			{
				WCHAR pszTemp[9];
				StringCchPrintfW(pszTemp, 9, L"%X", *(UINT32*)(posFunction->pbyExp + nLength));
				nLength += 4;
				StringCchCatW(pszOutputString, nOutputLength, pszTemp);
				StringCchCatW(pszOutputString, nOutputLength, L" ");
//				__asm int 3
				break;
			}

		case Equal:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Equal]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			break;

		case NotEqual:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[NotEqual]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
//			__asm int 3
			break;

		case Greater:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Greater]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
//			__asm int 3
			break;

		case Lower:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Lower]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
//			__asm int 3
			break;

		case EqualGreater:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[EqualGreater]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
//			__asm int 3
			break;

		case EqualLower:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[EqualLower]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
//			__asm int 3
			break;

		case Plus:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Plus]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
//			__asm int 3
			break;

		case Minus:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Minus]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
//			__asm int 3
			break;

		case Multiply:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Multiply]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case Divide:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Divide]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case And:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[And]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
//			__asm int 3
			break;

		case Or:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Or]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
//			__asm int 3
			break;

		case Xor:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Xor]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case ConditionAnd:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ConditionAnd]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
//			__asm int 3
			break;

		case ConditionOr:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ConditionOr]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			break;

		case ParentParam:
			{
				UINT32 nStringLength ;
				StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ParentParam]);
				StringCchLengthW(pszOutputString, nOutputLength, &nStringLength);
				StringCchPrintfW(pszOutputString, nOutputLength, L"%s%d ", pszOutputString, posFunction->pbyExp[nLength++]);
			}
			break;

		case Instruction:
			{
				
				switch(*(UINT16*)&(posFunction->pbyExp[nLength]))
				{
				case eAAA:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eAAA]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eAAD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eAAD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eAAM:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eAAM]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eAAS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eAAS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eAAS8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eAAS8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eADC:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eADC]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eADC16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eADC16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eADC8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eADC8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eADD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eADD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eADD16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eADD16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eADD8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eADD8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eADDPS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eADDPS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eADDSS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eADDSS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eAND:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eAND]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eAND16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eAND16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eAND8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eAND8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eANDNPS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eANDNPS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eANDPS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eANDPS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eARPL:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eARPL]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eARPL16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eARPL16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eBOUND:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eBOUND]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eBOUND16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eBOUND16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eBSF:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eBSF]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eBSF16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eBSF16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eBSR:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eBSR]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eBSR16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eBSR16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eBSWAP:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eBSWAP]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eBSWAP16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eBSWAP16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eBT:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eBT]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eBT16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eBT16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eBT8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eBT8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eBTC:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eBTC]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eBTC16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eBTC16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eBTC8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eBTC8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eBTR:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eBTR]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eBTR16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eBTR16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eBTR8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eBTR8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eBTS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eBTS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eBTS16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eBTS16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eBTS8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eBTS8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCALL:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCALL]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCALL16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCALL16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCBW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCBW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCDQ:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCDQ]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCLC:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCLC]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCLD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCLD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCLI:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCLI]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCLTS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCLTS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMC:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMC]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVAE:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVAE]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVAE16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVAE16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVC:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVC]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVC16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVC16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVNA:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVNA]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVNA16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVNA16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVNBE:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVNBE]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVNBE16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVNBE16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVNG:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVNG]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVNG16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVNG16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVNGE:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVNGE]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVNGE16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVNGE16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVNL:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVNL]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVNL16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVNL16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVNLE:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVNLE]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVNLE16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVNLE16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVNO:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVNO]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVNO16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVNO16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVNS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVNS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVNS16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVNS16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVNZ:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVNZ]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVNZ16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVNZ16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVO:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVO]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVO16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVO16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVPE:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVPE]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVPE16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVPE16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVPO:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVPO]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVPO16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVPO16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVS16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVS16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVZ:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVZ]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMOVZ16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMOVZ16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMP:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMP]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMP16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMP16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMP8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMP8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMPPS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMPPS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMPSB:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMPSB]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMPSD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMPSD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMPSD16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMPSD16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMPSS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMPSS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMPXCHG:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMPXCHG]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMPXCHG16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMPXCHG16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMPXCHG8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMPXCHG8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCMPXCHG8B:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCMPXCHG8B]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCOMISS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCOMISS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCPUID:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCPUID]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCVTPI2PS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCVTPI2PS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCVTPS2PI:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCVTPS2PI]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCVTSI2SS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCVTSI2SS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCVTSS2SI:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCVTSS2SI]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCVTTPS2PI:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCVTTPS2PI]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCVTTSS2SI:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCVTTSS2SI]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCWD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCWD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eCWDE:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eCWDE]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eDAA:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eDAA]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eDAA8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eDAA8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eDAS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eDAS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eDAS8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eDAS8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eDEC:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eDEC]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eDEC16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eDEC16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eDEC8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eDEC8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eDIV:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eDIV]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eDIV16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eDIV16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eDIV8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eDIV8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eDIVPS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eDIVPS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eDIVSS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eDIVSS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eEMMS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eEMMS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eENTER:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eENTER]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eENTER8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eENTER8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eF2XM1:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eF2XM1]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFABS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFABS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFADD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFADD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFADDP:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFADDP]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFBLD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFBLD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFBLD8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFBLD8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFBSTP:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFBSTP]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFBSTP8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFBSTP8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFCHS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFCHS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFCLEX:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFCLEX]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFCMOVB:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFCMOVB]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFCMOVBE:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFCMOVBE]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFCMOVE:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFCMOVE]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFCMOVNB:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFCMOVNB]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFCMOVNBE:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFCMOVNBE]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFCMOVNE:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFCMOVNE]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFCMOVNU:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFCMOVNU]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFCMOVU:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFCMOVU]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFCOM:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFCOM]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFCOMI:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFCOMI]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFCOMIP:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFCOMIP]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFCOMP:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFCOMP]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFCOMPP:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFCOMPP]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFCOS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFCOS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFDECSTP:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFDECSTP]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFDIV:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFDIV]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFDIVP:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFDIVP]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFDIVR:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFDIVR]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFDIVRP:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFDIVRP]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFFREE:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFFREE]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFIADD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFIADD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFICOM:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFICOM]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFICOMP:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFICOMP]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFIDIV:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFIDIV]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFIDIVR:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFIDIVR]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFILD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFILD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFIMUL:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFIMUL]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFINCSTP:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFINCSTP]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFINIT:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFINIT]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFIST:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFIST]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFISTP:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFISTP]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFISUB:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFISUB]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFISUBR:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFISUBR]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFLD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFLD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFLD1:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFLD1]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFLD8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFLD8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFLDCW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFLDCW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFLDENV:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFLDENV]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFLDL2E:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFLDL2E]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFLDL2T:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFLDL2T]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFLDLG2:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFLDLG2]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFLDLN2:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFLDLN2]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFLDPI:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFLDPI]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFLDZ:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFLDZ]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFMUL:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFMUL]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFMULP:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFMULP]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFNCLEX:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFNCLEX]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFNINIT:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFNINIT]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFNOP:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFNOP]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFNSAVE:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFNSAVE]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFNSTCW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFNSTCW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFNSTENV:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFNSTENV]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFNSTSW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFNSTSW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFNSTSW16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFNSTSW16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFPATAN:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFPATAN]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFPREM:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFPREM]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFPREM1:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFPREM1]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFPTAN:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFPTAN]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFRNDINT:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFRNDINT]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFRSTOR:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFRSTOR]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFSAVE:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFSAVE]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFSCALE:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFSCALE]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFSIN:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFSIN]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFSINCOS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFSINCOS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFSQRT:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFSQRT]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFST:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFST]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFSTCW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFSTCW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFSTENV:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFSTENV]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFSTP:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFSTP]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFSTP8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFSTP8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFSTSW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFSTSW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFSUB:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFSUB]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFSUBP:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFSUBP]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFSUBR:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFSUBR]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFSUBRP:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFSUBRP]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFTST:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFTST]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFUCOM:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFUCOM]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFUCOMI:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFUCOMI]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFUCOMIP:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFUCOMIP]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFUCOMP:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFUCOMP]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFUCOMPP:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFUCOMPP]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFWAIT:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFWAIT]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFXAM:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFXAM]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFXCH:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFXCH]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFXRSTOR:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFXRSTOR]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFXSAVE:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFXSAVE]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFXTRACT:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFXTRACT]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFYL2X:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFYL2X]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eFYL2XP1:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eFYL2XP1]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eHLT:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eHLT]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eIDIV:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eIDIV]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eIDIV16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eIDIV16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eIDIV8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eIDIV8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eIMUL:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eIMUL]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eIMUL16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eIMUL16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eIMUL8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eIMUL8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eIN_:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eIN_]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eIN_16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eIN_16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eIN_8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eIN_8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eINC:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eINC]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eINC16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eINC16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eINC8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eINC8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eINS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eINS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eINSB:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eINSB]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eINSD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eINSD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eINSW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eINSW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eINT3:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eINT3]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eINTO:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eINTO]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eINVD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eINVD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eINVLPG:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eINVLPG]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eIRET:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eIRET]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eIRETD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eIRETD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eJAE:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eJAE]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eJB:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eJB]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eJC:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eJC]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eJECXZ:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eJECXZ]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eJMP:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eJMP]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eJMP16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eJMP16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eJNA:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eJNA]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eJNB:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eJNB]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eJNBE:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eJNBE]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eJNG:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eJNG]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eJNGE:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eJNGE]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eJNL:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eJNL]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eJNLE:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eJNLE]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eJNO:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eJNO]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eJNS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eJNS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eJNZ:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eJNZ]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eJO:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eJO]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eJPE:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eJPE]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eJPO:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eJPO]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eJS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eJS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eJZ:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eJZ]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLAHF:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLAHF]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLAR:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLAR]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLAR16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLAR16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLDMXCSR:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLDMXCSR]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLDS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLDS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLDS16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLDS16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLEA:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLEA]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLEA16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLEA16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLEAVE:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLEAVE]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLEAVE16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLEAVE16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLES:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLES]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLES16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLES16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLFS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLFS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLFS16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLFS16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLGDT:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLGDT]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLGS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLGS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLGS16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLGS16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLIDT:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLIDT]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLLDT:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLLDT]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLLDT16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLLDT16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLMSW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLMSW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLMSW16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLMSW16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLOCK:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLOCK]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLODS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLODS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLODSB:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLODSB]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLODSB16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLODSB16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLODSD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLODSD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLODSD16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLODSD16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLOOP:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLOOP]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLOOPNZ:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLOOPNZ]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLOOPZ:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLOOPZ]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLSL:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLSL]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLSL16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLSL16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLSS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLSS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLSS16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLSS16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLTR:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLTR]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eLTR16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eLTR16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMASKMOVQ:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMASKMOVQ]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMAXPS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMAXPS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMAXSS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMAXSS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMINPS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMINPS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMINSS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMINSS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMOV:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMOV]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMOV16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMOV16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMOV8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMOV8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMOVAPS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMOVAPS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMOVD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMOVD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMOVD16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMOVD16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMOVHLPS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMOVHLPS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMOVHPS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMOVHPS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMOVLHPS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMOVLHPS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMOVLPS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMOVLPS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMOVMSKPS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMOVMSKPS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMOVNTPS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMOVNTPS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMOVNTQ:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMOVNTQ]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMOVQ:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMOVQ]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMOVSB:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMOVSB]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMOVSD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMOVSD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMOVSD16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMOVSD16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMOVSS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMOVSS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMOVSX:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMOVSX]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMOVSX16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMOVSX16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMOVSX8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMOVSX8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMOVUPS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMOVUPS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMOVZX:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMOVZX]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMOVZX16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMOVZX16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMOVZX8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMOVZX8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMUL:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMUL]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMUL16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMUL16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMUL8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMUL8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMULPS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMULPS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eMULSS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eMULSS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eNEG:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eNEG]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eNEG16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eNEG16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eNEG8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eNEG8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eNOP:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eNOP]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eNOT:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eNOT]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eNOT16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eNOT16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eNOT8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eNOT8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eOR:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eOR]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eOR16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eOR16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eOR8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eOR8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eORPS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eORPS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eOUT_:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eOUT_]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eOUT_16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eOUT_16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eOUT_8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eOUT_8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eOUTS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eOUTS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eOUTSB:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eOUTSB]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eOUTSD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eOUTSD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eOUTSW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eOUTSW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePACKSSDW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePACKSSDW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePACKSSWB:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePACKSSWB]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePACKUSWB:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePACKUSWB]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePADDB:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePADDB]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePADDD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePADDD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePADDSB:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePADDSB]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePADDSW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePADDSW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePADDUSB:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePADDUSB]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePADDUSW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePADDUSW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePADDW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePADDW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePAND:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePAND]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePANDN:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePANDN]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePAVGB:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePAVGB]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePAVGW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePAVGW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePCMPEQB:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePCMPEQB]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePCMPEQD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePCMPEQD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePCMPEQW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePCMPEQW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePCMPGTB:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePCMPGTB]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePCMPGTD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePCMPGTD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePCMPGTW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePCMPGTW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePEXTRW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePEXTRW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePINSRW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePINSRW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePMADDWD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePMADDWD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePMAXSW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePMAXSW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePMAXUB:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePMAXUB]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePMINSW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePMINSW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePMINUB:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePMINUB]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePMOVMSKB:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePMOVMSKB]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePMOVMSKB16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePMOVMSKB16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePMULHUW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePMULHUW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePMULHW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePMULHW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePMULLW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePMULLW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePOP:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePOP]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePOP16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePOP16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePOP8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePOP8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePOPAD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePOPAD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePOPAD16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePOPAD16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePOPF:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePOPF]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePOPFD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePOPFD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePOPFD16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePOPFD16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePOR:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePOR]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePREFETCHNTA8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePREFETCHNTA8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePREFETCHT08:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePREFETCHT08]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePREFETCHT18:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePREFETCHT18]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePREFETCHT28:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePREFETCHT28]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePSADBW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePSADBW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePSHUFW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePSHUFW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePSLLD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePSLLD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePSLLD8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePSLLD8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePSLLQ:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePSLLQ]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePSLLQ8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePSLLQ8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePSLLW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePSLLW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePSLLW8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePSLLW8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePSRAD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePSRAD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePSRAD8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePSRAD8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePSRAW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePSRAW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePSRAW8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePSRAW8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePSRLD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePSRLD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePSRLD8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePSRLD8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePSRLQ:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePSRLQ]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePSRLQ8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePSRLQ8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePSRLW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePSRLW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePSRLW8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePSRLW8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePSUBB:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePSUBB]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePSUBD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePSUBD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePSUBSB:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePSUBSB]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePSUBSW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePSUBSW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePSUBUSB:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePSUBUSB]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePSUBUSW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePSUBUSW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePSUBW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePSUBW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePUNPCKHBW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePUNPCKHBW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePUNPCKHDQ:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePUNPCKHDQ]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePUNPCKHWD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePUNPCKHWD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePUNPCKLBW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePUNPCKLBW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePUNPCKLDQ:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePUNPCKLDQ]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePUNPCKLWD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePUNPCKLWD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePUSH:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePUSH]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePUSH16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePUSH16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePUSH8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePUSH8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePUSHAD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePUSHAD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePUSHAD16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePUSHAD16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePUSHF:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePUSHF]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePUSHFD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePUSHFD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePUSHFD16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePUSHFD16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case ePXOR:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ePXOR]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eRCL:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eRCL]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eRCL16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eRCL16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eRCL8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eRCL8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eRCPPS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eRCPPS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eRCPSS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eRCPSS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eRCR:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eRCR]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eRCR16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eRCR16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eRCR8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eRCR8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eRDMSR:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eRDMSR]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eRDPMC:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eRDPMC]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eRDTSC:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eRDTSC]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eREP:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eREP]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eREPE:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eREPE]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eREPNE:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eREPNE]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eREPNZ:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eREPNZ]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eREPZ:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eREPZ]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eRET:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eRET]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eRETF:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eRETF]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eROL:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eROL]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eROL16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eROL16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eROL8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eROL8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eROR:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eROR]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eROR16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eROR16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eROR8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eROR8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eRSM:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eRSM]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eRSQRTPS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eRSQRTPS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eRSQRTSS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eRSQRTSS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSAHF:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSAHF]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSAL:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSAL]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSAL16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSAL16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSAL8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSAL8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSAR:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSAR]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSAR16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSAR16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSAR8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSAR8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSBB:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSBB]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSBB16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSBB16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSBB8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSBB8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSCAS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSCAS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSCASB:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSCASB]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSCASB16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSCASB16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSCASD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSCASD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSCASD16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSCASD16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSETB8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSETB8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSETNA8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSETNA8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSETNB8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSETNB8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSETNBE8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSETNBE8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSETNG8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSETNG8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSETNGE8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSETNGE8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSETNL8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSETNL8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSETNLE8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSETNLE8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSETNO8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSETNO8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSETNS8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSETNS8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSETNZ8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSETNZ8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSETO8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSETO8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSETPE8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSETPE8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSETPO8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSETPO8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSETS8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSETS8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSETZ8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSETZ8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSFENCE:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSFENCE]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSGDT:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSGDT]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSHL:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSHL]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSHL16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSHL16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSHL8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSHL8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSHLD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSHLD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSHLD16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSHLD16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSHR:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSHR]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSHR16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSHR16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSHR8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSHR8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSHRD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSHRD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSHRD16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSHRD16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSHUFPS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSHUFPS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSIDT:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSIDT]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSLDT:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSLDT]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSLDT16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSLDT16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSMSW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSMSW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSMSW16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSMSW16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSQRTPS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSQRTPS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSQRTSS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSQRTSS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSTC:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSTC]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSTD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSTD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSTI:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSTI]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSTMXCSR:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSTMXCSR]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSTOS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSTOS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSTOSB:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSTOSB]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSTOSB16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSTOSB16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSTOSD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSTOSD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSTOSD16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSTOSD16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSTR:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSTR]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSTR16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSTR16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSUB:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSUB]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSUB16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSUB16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSUB8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSUB8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSUBPS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSUBPS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSUBSS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSUBSS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSYSENTER:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSYSENTER]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eSYSEXIT:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eSYSEXIT]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eTEST:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eTEST]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eTEST16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eTEST16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eTEST8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eTEST8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eUCOMISS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eUCOMISS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eUD2:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eUD2]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eUNPCKHPS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eUNPCKHPS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eUNPCKLPS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eUNPCKLPS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eVERR:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eVERR]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eVERR16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eVERR16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eVERW:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eVERW]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eVERW16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eVERW16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eWAIT:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eWAIT]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eWBINVD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eWBINVD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eWRMSR:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eWRMSR]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eXADD:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eXADD]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eXADD16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eXADD16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eXADD8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eXADD8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eXCHG:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eXCHG]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eXCHG16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eXCHG16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eXCHG8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eXCHG8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eXLAT:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eXLAT]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eXLATB:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eXLATB]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eXOR:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eXOR]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eXOR16:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eXOR16]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eXOR8:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eXOR8]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				case eXORPS:
					StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[eXORPS]);
					StringCchCatW(pszOutputString, nOutputLength, L" ");
					break;

				}
				nLength += 2;
				break;
			}

		case StackDown:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[StackDown]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case Operand0:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Operand0]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
//			__asm int 3
			break;

		case Operand1:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Operand1]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
//			__asm int 3
			break;

		case Param:
			{
				UINT32 nStringLength ;
				StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Param]);
				StringCchLengthW(pszOutputString, nOutputLength, &nStringLength);
				StringCchPrintfW(pszOutputString, nOutputLength, L"%s%d ", pszOutputString, posFunction->pbyExp[nLength++]);

// 				StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Param]);
// 				UINT32 nStringLength = StringCchLengthW(pszOutputString);
// 				pszOutputString[nStringLength] = '0' + posFunction->pbyExp[nLength++];
// 				pszOutputString[nStringLength + 1] = '\0';
// 				StringCchCatW(pszOutputString, nOutputLength, L" ");
			}
			break;

		case Colon:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Colon]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			break;

		case SemiColon:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[SemiColon]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			return;

		case TruE:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[TruE]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			break;

		case FalsE:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[FalsE]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			__asm int 3
			break;

		case Jump:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Jump]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
//			__asm int 3
			break;

		case Return:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Return]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
//			__asm int 3
			break;

		case Min:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Min]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
//			__asm int 3
			break;

		case Begin:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Begin]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			break;

		case Current:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Current]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			break;

		case End:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[End]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			break;

		case RVAToOffset:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[RVAToOffset]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			break;

		case OffsetToRVA:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[OffsetToRVA]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			break;

		case GetCurrecntSectionIndex:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[GetCurrecntSectionIndex]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			break;

		case SetEntryPoint:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[SetEntryPoint]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			break;

		case GetEntryPoint:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[GetEntryPoint]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			break;

		case ReadMem:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[ReadMem]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			break;

		case Read:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Read]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			break;

		case Write:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Write]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			break;

		case SetZero:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[SetZero]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			break;

		case Seek:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Seek]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			break;

		case Truncate:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Truncate]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			break;

		case Alloc:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Alloc]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			break;

		case Free:
			StringCchCatW(pszOutputString, nOutputLength, pszBinaryString[Free]);
			StringCchCatW(pszOutputString, nOutputLength, L" ");
			break;
		}
	}
}

