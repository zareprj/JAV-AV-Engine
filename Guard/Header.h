#ifndef HEADER_ADDED
#define HEADER_ADDED
#include "SMTypeDefine.h"


typedef struct _VirtualMachine VirtualMachine;
typedef enum _SMBytesEnum SMBytesEnum;
typedef enum _OperandType
{
	NotDef,
	AL,
	AX,
	CL,
	DL,
	BL,
	AH,
	CH,
	DH,
	BH,
	CX,
	BX,
	SP,
	BP,
	DI,
	SI,
	CR0,
	CR2,
	CR3,
	CR4,
	CS,
	DR0_DR7,
	DS,
	DX,
	EAX,
	ES,
	FS,
	GS,
	imm16,
	imm32,
	imm8,
	m,
	LEA32,
	m128,
	m14_Slash_28byte,
	m16,
	m16_Amp_16,
	m16_Amp_32,
	m16_Colon_16,
	m16_Colon_32,
	m32_Colon_32,
	m16int,
	m2byte,
	m32,
	m32_Amp_32,
	m32int,
	m32real,
	m512byte,
	m64,
	m64int,
	m64real,
	m8,
	m80bcd,
	m80dec,
	m80real,
	m94_Slash_108byte,
	mm,
	mm_Slash_m32,
	mm_Slash_m64,
	mm1,
	mm2_Slash_m64,
	moffs16,
	moffs32,
	moffs8,
	ptr16_Colon_16,
	ptr16_Colon_32,
	r_Slash_m16,
	r_Slash_m32,
	r_Slash_m8,
	r16,
	r32,
	r32_Slash_m16,
	r8,
	rel16,
	rel16_Slash_32,
	rel32,
	rel8,
	Sreg,
	SS,
	ST,
	ST__0__,
	ST__1__,
	ST__2__,
	ST__3__,
	ST__4__,
	ST__5__,
	ST__6__,
	ST__7__,
	ST__8__,
	ST__9__,
	ST__10__,
	ST__11__,
	ST__12__,
	ST__13__,
	ST__14__,
	ST__15__,
	xmm,
	xmm_Slash_m32,
	xmm_Slash_m64,
	xmm1,
	xmm2_Slash_m128,
	xmm2_Slash_m32,

	EBX,
	ECX,
	EDX,
	ESI,
	EDI,
	EBP,
	ESP,
	EIP,
	EFL
} OperandType;

#pragma pack (push, 1)
typedef void  (__fastcall *Pointer)(VirtualMachine *posVm);

//	Structure use for match from opcode table list
typedef struct _SMTableBlock
{
#if _DEBUG
	WCHAR	*szOpcode;
#endif	
	Pointer pFuncPointer;
	OperandType eOperand1 ;
	OperandType eOperand2 ;
	OperandType eOperand3 ;
	Pointer pNextFuncPointer;
	SMBytesEnum eInstruction;
	UINT8	Prefix;
}SMTableBlock;
#pragma pack (pop)
#endif