
#include "OperationsFunctions.h"
#ifndef _DEBUG
#include "All_Defines.h"
#include "StateMachine.h"
#pragma pack (push, 1)

// All Opcode table with reference are in 'arTable_Base' table
SMTableBlock arTable_Base [] = {
	//00 /r
	{ADD8, r_Slash_m8, r8, NotDef, (Pointer)NULL, eADD8, 0xA},
	//01 /r
	{ADD, r_Slash_m32, r32, NotDef, ADD16, eADD, 0xB},
	//02 /r
	{ADD8, r8, r_Slash_m8, NotDef, (Pointer)NULL, eADD8, 0xA},
	//03 /r
	{ADD, r32, r_Slash_m32, NotDef, ADD16, eADD, 0xB},
	//04 ib
	{ADD8, AL, imm8, NotDef, (Pointer)NULL, eADD8, 0x8},
	//05 id
	{ADD, EAX, imm32, NotDef, ADD16, eADD, 0x9},
	//06 
	{PUSH, ES, NotDef, NotDef, (Pointer)NULL, ePUSH, 0x0},
	//07
	{POP, ES, NotDef, NotDef, (Pointer)NULL, ePOP, 0x0},
	//08 /r
	{OR8, r_Slash_m8, r8, NotDef, (Pointer)NULL, eOR8, 0xA},
	//09 /r
	{OR, r_Slash_m32, r32, NotDef, OR16, eOR, 0xB},
	//0A /r
	{OR8, r8, r_Slash_m8, NotDef, (Pointer)NULL, eOR8, 0xA},
	//0B /r
	{OR, r32, r_Slash_m32, NotDef, OR16, eOR, 0xB},
	//0C ib
	{OR8, AL, imm8, NotDef, (Pointer)NULL, eOR8, 0x8},
	//0D id
	{OR, EAX, imm32, NotDef, OR16, eOR, 0x9},
	//0E 
	{PUSH, CS, NotDef, NotDef, (Pointer)NULL, ePUSH, 0x0},
	//0F 00
	{(Pointer)0x00001100, r_Slash_m32, NotDef, NotDef, (Pointer)NULL, Ins, 0x3},
	//10 /r
	{ADC8, r_Slash_m8, r8, NotDef, (Pointer)NULL, eADC8, 0xA},
	//11 /r
	{ADC, r_Slash_m32, r32, NotDef, ADC16, eADC, 0xB},
	//12 /r
	{ADC8, r8, r_Slash_m8, NotDef, (Pointer)NULL, eADC8, 0xA},
	//13 /r 
	{ADC, r32, r_Slash_m32, NotDef, ADC16, eADC, 0xB},
	//14 ib
	{ADC8, AL, imm8, NotDef, (Pointer)NULL, eADC8, 0x8},
	//15 id
	{ADC, EAX, imm32, NotDef, ADC16, eADC, 0x9},
	//16 
	{PUSH, SS, NotDef, NotDef, (Pointer)NULL, ePUSH, 0x0},
	//17
	{POP, SS, NotDef, NotDef, (Pointer)NULL, ePOP, 0x0},
	//18 /r
	{SBB8, r_Slash_m8, r8, NotDef, (Pointer)NULL, eSBB8, 0xA},
	//19 /r
	{SBB, r_Slash_m32, r32, NotDef, SBB16, eSBB, 0xB},
	//1A /r
	{SBB8, r8, r_Slash_m8, NotDef, (Pointer)NULL, eSBB8, 0xA},
	//1B /r
	{SBB, r32, r_Slash_m32, NotDef, SBB16, eSBB, 0xB},
	//1C ib
	{SBB8, AL, imm8, NotDef, (Pointer)NULL, eSBB8, 0x8},
	//1D id
	{SBB, EAX, imm32, NotDef, SBB16, eSBB, 0x9},
	//1E 
	{PUSH, DS, NotDef, NotDef, (Pointer)NULL, ePUSH, 0x0},
	//1F
	{POP, DS, NotDef, NotDef, (Pointer)NULL, ePOP, 0x0},
	//20 /r
	{AND8, r_Slash_m8, r8, NotDef, (Pointer)NULL, eAND8, 0xA},
	//21 /r 
	{AND, r_Slash_m32, r32, NotDef, AND16, eAND, 0xB},
	//22 /r 
	{AND8, r8, r_Slash_m8, NotDef, (Pointer)NULL, eAND8, 0xA},
	//23 /r 
	{AND, r32, r_Slash_m32, NotDef, AND16, eAND, 0xB},
	//24 ib 
	{AND8, AL, imm8, NotDef, (Pointer)NULL, eAND8, 0x8},
	//25 id 
	{AND, EAX, imm32, NotDef, AND16, eAND, 0x9},
	//26
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//27
	{DAA, NotDef, NotDef, NotDef, (Pointer)NULL, eDAA, 0x0},
	//28 /r
	{SUB8, r_Slash_m8, r8, NotDef, (Pointer)NULL, eSUB8, 0xA},
	//29 /r 
	{SUB, r_Slash_m32, r32, NotDef, SUB16, eSUB, 0xB},
	//2A /r 
	{SUB8, r8, r_Slash_m8, NotDef, (Pointer)NULL, eSUB8, 0xA},
	//2B /r 
	{SUB, r32, r_Slash_m32, NotDef, SUB16, eSUB, 0xB},
	//2C ib 
	{SUB8, AL, imm8, NotDef, (Pointer)NULL, eSUB8, 0x8},
	//2D id 
	{SUB, EAX, imm32, NotDef, SUB16, eSUB, 0x9},
	//2E
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//2F
	{DAS, NotDef, NotDef, NotDef, (Pointer)NULL, eDAS, 0x0},
	//30 /r
	{XOR8, r_Slash_m8, r8, NotDef, (Pointer)NULL, eXOR8, 0xB},
	//31 /r
	{XOR, r_Slash_m32, r32, NotDef, XOR16, eXOR, 0xB},
	//32 /r 
	{XOR8, r8, r_Slash_m8, NotDef, (Pointer)NULL, eXOR8, 0xB},
	//33 /r 
	{XOR, r32, r_Slash_m32, NotDef, XOR16, eXOR, 0xB},
	//34 ib 
	{XOR8, AL, imm8, NotDef, (Pointer)NULL, eXOR8, 0x8},
	//35 id 
	{XOR, EAX, imm32, NotDef, XOR16, eXOR, 0x9},
	//36
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//37
	{AAA, NotDef, NotDef, NotDef, (Pointer)NULL, eAAA, 0x0},
	//38 /r
	{CMP8, r_Slash_m8, r8, NotDef, (Pointer)NULL, eCMP8, 0x2},
	//39 /r 
	{CMP, r_Slash_m32, r32, NotDef, CMP16, eCMP, 0x3},
	//3A /r 
	{CMP8, r8, r_Slash_m8, NotDef, (Pointer)NULL, eCMP8, 0x2},
	//3B /r 
	{CMP, r32, r_Slash_m32, NotDef, CMP16, eCMP, 0x3},
	//3C ib 
	{CMP8, AL, imm8, NotDef, (Pointer)NULL, eCMP8, 0x0},
	//3D id 
	{CMP, EAX, imm32, NotDef, CMP16, eCMP, 0x1},
	//3E
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//3F
	{AAS, NotDef, NotDef, NotDef, (Pointer)NULL, eAAS, 0x0},
	//40
	{INC, EAX, NotDef, NotDef, INC16, eINC, 0x9},
	//41
	{INC, ECX, NotDef, NotDef, INC16, eINC, 0x9},
	//42
	{INC, EDX, NotDef, NotDef, INC16, eINC, 0x9},
	//43
	{INC, EBX, NotDef, NotDef, INC16, eINC, 0x9},
	//44
	{INC, ESP, NotDef, NotDef, INC16, eINC, 0x9},
	//45
	{INC, EBP, NotDef, NotDef, INC16, eINC, 0x9},
	//46
	{INC, ESI, NotDef, NotDef, INC16, eINC, 0x9},
	//47
	{INC, EDI, NotDef, NotDef, INC16, eINC, 0x9},
	//48
	{DEC, EAX, NotDef, NotDef, DEC16, eDEC, 0x9},
	//49
	{DEC, ECX, NotDef, NotDef, DEC16, eDEC, 0x9},
	//4A
	{DEC, EDX, NotDef, NotDef, DEC16, eDEC, 0x9},
	//4B
	{DEC, EBX, NotDef, NotDef, DEC16, eDEC, 0x9},
	//4C
	{DEC, ESP, NotDef, NotDef, DEC16, eDEC, 0x9},
	//4D
	{DEC, EBP, NotDef, NotDef, DEC16, eDEC, 0x9},
	//4E
	{DEC, ESI, NotDef, NotDef, DEC16, eDEC, 0x9},
	//4F
	{DEC, EDI, NotDef, NotDef, DEC16, eDEC, 0x9},
	//50
	{PUSH, EAX, NotDef, NotDef, PUSH16, ePUSH, 0x1},
	//51
	{PUSH, ECX, NotDef, NotDef, PUSH16, ePUSH, 0x1},
	//52
	{PUSH, EDX, NotDef, NotDef, PUSH16, ePUSH, 0x1},
	//53
	{PUSH, EBX, NotDef, NotDef, PUSH16, ePUSH, 0x1},
	//54
	{PUSH, ESP, NotDef, NotDef, PUSH16, ePUSH, 0x1},
	//55
	{PUSH, EBP, NotDef, NotDef, PUSH16, ePUSH, 0x1},
	//56
	{PUSH, ESI, NotDef, NotDef, PUSH16, ePUSH, 0x1},
	//57
	{PUSH, EDI, NotDef, NotDef, PUSH16, ePUSH, 0x1},
	//58
	{POP, EAX, NotDef, NotDef, POP16, ePOP, 0x1},
	//59
	{POP, ECX, NotDef, NotDef, POP16, ePOP, 0x1},
	//5A
	{POP, EDX, NotDef, NotDef, POP16, ePOP, 0x1},
	//5B
	{POP, EBX, NotDef, NotDef, POP16, ePOP, 0x1},
	//5C
	{POP, ESP, NotDef, NotDef, POP16, ePOP, 0x1},
	//5D
	{POP, EBP, NotDef, NotDef, POP16, ePOP, 0x1},
	//5E
	{POP, ESI, NotDef, NotDef, POP16, ePOP, 0x1},
	//5F
	{POP, EDI, NotDef, NotDef, POP16, ePOP, 0x1},
	//60  
	{PUSHAD, NotDef, NotDef, NotDef, PUSHAD16, ePUSHAD, 0x1},
	//61  
	{POPAD, NotDef, NotDef, NotDef, POPAD16, ePOPAD, 0x1},
	//62 /r  
	{BOUND, r32, m32_Amp_32, NotDef, (Pointer)NULL, eBOUND, 0x0},
	//63 /r
	{ARPL, r_Slash_m16, r16, NotDef, ARPL16, eARPL, 0x3},
	//64
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//65
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//66
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//67
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//68 
	{PUSH, imm32, NotDef, NotDef, (Pointer)NULL, ePUSH, 0x0},
	//69 /r id
	{IMUL, r32, imm32, NotDef, IMUL16, eIMUL, 0x1},
	//6A 
	{PUSH8, imm8, NotDef, NotDef, (Pointer)NULL, ePUSH8, 0x0},
	//6B /r ib
	{IMUL, r32, r_Slash_m32, imm8, IMUL16, eIMUL, 0x3},
	//6C 
	{INSB, NotDef, NotDef, NotDef, (Pointer)NULL, eINSB, 0x4},
	//6D 
	{INSD, NotDef, NotDef, NotDef, (Pointer)NULL, eINSD, 0x4},
	//6E  
	{OUTSB, NotDef, NotDef, NotDef, (Pointer)NULL, eOUTSB, 0x4},
	//6F  
	{OUTSD, NotDef, NotDef, NotDef, (Pointer)NULL, eOUTSD, 0x4},
	//70 cb   
	{JO, rel8, NotDef, NotDef, (Pointer)NULL, eJO, 0x0},
	//71 cb    
	{JNO, rel8, NotDef, NotDef, (Pointer)NULL, eJNO, 0x0},
	//72 cb    
	{JB, rel8, NotDef, NotDef, (Pointer)NULL, eJB, 0x0},
	//73 cb    
	{JNB, rel8, NotDef, NotDef, (Pointer)NULL, eJNB, 0x0},
	//74 cb    
	{JZ, rel8, NotDef, NotDef, (Pointer)NULL, eJZ, 0x0},
	//75 cb    
	{JNZ, rel8, NotDef, NotDef, (Pointer)NULL, eJNZ, 0x0},
	//76 cb    
	{JNA, rel8, NotDef, NotDef, (Pointer)NULL, eJNA, 0x0},
	//77 cb    
	{JNBE, rel8, NotDef, NotDef, (Pointer)NULL, eJNBE, 0x0},
	//78 cb    
	{JS, rel8, NotDef, NotDef, (Pointer)NULL, eJS, 0x0},
	//79 cb    
	{JNS, rel8, NotDef, NotDef, (Pointer)NULL, eJNS, 0x0},
	//7A cb    
	{JPE, rel8, NotDef, NotDef, (Pointer)NULL, eJPE, 0x0},
	//7B cb    
	{JPO, rel8, NotDef, NotDef, (Pointer)NULL, eJPO, 0x0},
	//7C cb    
	{JNGE, rel8, NotDef, NotDef, (Pointer)NULL, eJNGE, 0x0},
	//7D cb    
	{JNL, rel8, NotDef, NotDef, (Pointer)NULL, eJNL, 0x0},
	//7E cb    
	{JNG, rel8, NotDef, NotDef, (Pointer)NULL, eJNG, 0x0},
	//7F cb    
	{JNLE, rel8, NotDef, NotDef, (Pointer)NULL, eJNLE, 0x0},
	//80 /0 ib
	{(Pointer)0x0000030B, r_Slash_m8, imm8, NotDef, (Pointer)NULL, Ins, 0xA},
	//81 /0 id
	{(Pointer)0x0000030C, r_Slash_m32, imm32, NotDef, (Pointer)NULL, Ins, 0xB},
	//82
	{ADD8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eADD8, 0xA},
	//83 /0 ib
	{(Pointer)0x0000030D, r_Slash_m32, imm8, NotDef, (Pointer)NULL, Ins, 0xB},
	//84 /r
	{TEST8, r_Slash_m8, r8, NotDef, (Pointer)NULL, eTEST8, 0x2},
	//85 /r 
	{TEST, r_Slash_m32, r32, NotDef, TEST16, eTEST, 0x3},
	//86 /r 
	{XCHG8, r8, r_Slash_m8, NotDef, (Pointer)NULL, eXCHG8, 0xA},
	//87 /r 
	{XCHG, r32, r_Slash_m32, NotDef, XCHG16, eXCHG, 0xB},
	//88 /r
	{MOV8, r_Slash_m8, r8, NotDef, (Pointer)NULL, eMOV8, 0x3},
	//89 /r 
	{MOV, r_Slash_m32, r32, NotDef, MOV16, eMOV, 0x3},
	//8A /r 
	{MOV8, r8, r_Slash_m8, NotDef, (Pointer)NULL, eMOV8, 0x3},
	//8B /r 
	{MOV, r32, r_Slash_m32, NotDef, MOV16, eMOV, 0x3},
	//8C /r
	{MOV, r_Slash_m16, Sreg, NotDef, MOV16, eMOV, 0x3},
	//8D /r
	{LEA, r32, LEA32, NotDef, (Pointer)NULL, eLEA, 0x3},
	//8E /r 
	{MOV, Sreg, r_Slash_m16, NotDef, MOV16, eMOV, 0x3},
	//8F /0
	{(Pointer)0x0000030E, m32, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//90 
	{NOP, NotDef, NotDef, NotDef, (Pointer)NULL, eNOP, 0x0},
	//91
	{XCHG, EAX, ECX, NotDef, XCHG16, eXCHG, 0x9},
	//92
	{XCHG, EAX, EDX, NotDef, XCHG16, eXCHG, 0x9},
	//93
	{XCHG, EAX, EBX, NotDef, XCHG16, eXCHG, 0x9},
	//94
	{XCHG, EAX, ESP, NotDef, XCHG16, eXCHG, 0x9},
	//95
	{XCHG, EAX, EBP, NotDef, XCHG16, eXCHG, 0x9},
	//96
	{XCHG, EAX, ESI, NotDef, XCHG16, eXCHG, 0x9},
	//97
	{XCHG, EAX, EDI, NotDef, XCHG16, eXCHG, 0x9},
	//98 
	{CWDE, NotDef, NotDef, NotDef, (Pointer)NULL, eCWDE, 0x0},
	//99  
	{CDQ, NotDef, NotDef, NotDef, (Pointer)NULL, eCDQ, 0x0},
	//9A cp 
	{CALL, ptr16_Colon_32, NotDef, NotDef, (Pointer)NULL, eCALL, 0x0},
	//9B   
	{FWAIT, NotDef, NotDef, NotDef, (Pointer)NULL, eFWAIT, 0x0},
	//9C   
	{PUSHFD, NotDef, NotDef, NotDef, (Pointer)NULL, ePUSHFD, 0x0},
	//9D   
	{POPFD, NotDef, NotDef, NotDef, (Pointer)NULL, ePOPFD, 0x0},
	//9E   
	{SAHF, NotDef, NotDef, NotDef, (Pointer)NULL, eSAHF, 0x0},
	//9F   
	{LAHF, NotDef, NotDef, NotDef, (Pointer)NULL, eLAHF, 0x0},
	//A0 
	{MOV8, AL, moffs8, NotDef, (Pointer)NULL, eMOV8, 0x0},
	//A1 
	{MOV, EAX, moffs32, NotDef, MOV16, eMOV, 0x3},
	//A2 
	{MOV8, moffs8, AL, NotDef, (Pointer)NULL, eMOV8, 0x0},
	//A3 
	{MOV, moffs32, EAX, NotDef, MOV16, eMOV, 0x3},
	//A4  
	{MOVSB, NotDef, NotDef, NotDef, (Pointer)NULL, eMOVSB, 0x4},
	//A5  
	{MOVSD, NotDef, NotDef, NotDef, MOVSD16, eMOVSD, 0x5},
	//A6 
	{CMPSB, NotDef, NotDef, NotDef, (Pointer)NULL, eCMPSB, 0x4},
	//A7 
	{CMPSD, NotDef, NotDef, NotDef, CMPSD16, eCMPSD, 0x5},
	//A8 ib 
	{TEST8, AL, imm8, NotDef, (Pointer)NULL, eTEST8, 0x0},
	//A9 id 
	{TEST, EAX, imm32, NotDef, TEST16, eTEST, 0x1},
	//AA 
	{STOSB, NotDef, NotDef, NotDef, STOSB16, eSTOSB, 0x5},
	//AB 
	{STOSD, NotDef, NotDef, NotDef, STOSD16, eSTOSD, 0x5},
	//AC 
	{LODSB, NotDef, NotDef, NotDef, LODSB16, eLODSB, 0x5},
	//AD 
	{LODSD, NotDef, NotDef, NotDef, LODSD16, eLODSD, 0x5},
	//AE 
	{SCASB, NotDef, NotDef, NotDef, SCASB16, eSCASB, 0x5},
	//AF 
	{SCASD, NotDef, NotDef, NotDef, SCASD16, eSCASD, 0x5},
	//B0
	{MOV8, AL, imm8, NotDef, (Pointer)NULL, eMOV8, 0x0},
	//B1
	{MOV8, CL, imm8, NotDef, (Pointer)NULL, eMOV8, 0x0},
	//B2
	{MOV8, DL, imm8, NotDef, (Pointer)NULL, eMOV8, 0x0},
	//B3
	{MOV8, BL, imm8, NotDef, (Pointer)NULL, eMOV8, 0x0},
	//B4
	{MOV8, AH, imm8, NotDef, (Pointer)NULL, eMOV8, 0x0},
	//B5
	{MOV8, CH, imm8, NotDef, (Pointer)NULL, eMOV8, 0x0},
	//B6
	{MOV8, DH, imm8, NotDef, (Pointer)NULL, eMOV8, 0x0},
	//B7
	{MOV8, BH, imm8, NotDef, (Pointer)NULL, eMOV8, 0x0},
	//B8
	{MOV, EAX, imm32, NotDef, MOV16, eMOV, 0x1},
	//B9
	{MOV, ECX, imm32, NotDef, MOV16, eMOV, 0x1},
	//BA
	{MOV, EDX, imm32, NotDef, MOV16, eMOV, 0x1},
	//BB
	{MOV, EBX, imm32, NotDef, MOV16, eMOV, 0x1},
	//BC
	{MOV, ESP, imm32, NotDef, MOV16, eMOV, 0x1},
	//BD
	{MOV, EBP, imm32, NotDef, MOV16, eMOV, 0x1},
	//BE
	{MOV, ESI, imm32, NotDef, MOV16, eMOV, 0x1},
	//BF
	{MOV, EDI, imm32, NotDef, MOV16, eMOV, 0x1},
	//C0 /0 ib 
	{(Pointer)0x0000030F, r_Slash_m8, imm8, NotDef, (Pointer)NULL, Ins, 0x2},
	//C1 /0 ib 
	{(Pointer)0x00000310, r_Slash_m32, imm8, NotDef, (Pointer)NULL, Ins, 0x3},
	//C2 iw 
	{RET, imm16, NotDef, NotDef, (Pointer)NULL, eRET, 0x0},
	//C3
	{RET, NotDef, NotDef, NotDef, (Pointer)NULL, eRET, 0x0},
	//C4 /r
	{LES, r32, m16_Colon_32, NotDef, LES16, eLES, 0x2},
	//C5 /r
	{LDS, r32, m16_Colon_32, NotDef, LDS16, eLDS, 0x2},
	//C6 /0 
	{(Pointer)0x00000311, r_Slash_m8, imm8, NotDef, (Pointer)NULL, Ins, 0x2},
	//C7 /0 
	{(Pointer)0x00000312, r_Slash_m32, imm32, NotDef, (Pointer)NULL, Ins, 0x3},
	//C8 iw ib 
	{ENTER8, imm16, imm8, NotDef, (Pointer)NULL, eENTER8, 0x0},
	//C9 
	{LEAVE, NotDef, NotDef, NotDef, LEAVE16, eLEAVE, 0x1},
	//CA iw 
	{RETF, imm16, NotDef, NotDef, (Pointer)NULL, eRETF, 0x0},
	//CB 
	{RETF, NotDef, NotDef, NotDef, (Pointer)NULL, eRETF, 0x0},
	//CC
	{INT3, NotDef, NotDef, NotDef, (Pointer)NULL, eINT3, 0x0},
	//CD ib 
	{INTn8, imm8, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//CE 
	{INTO, NotDef, NotDef, NotDef, (Pointer)NULL, eINTO, 0x0},
	//CF 
	{IRETD, NotDef, NotDef, NotDef, (Pointer)NULL, eIRETD, 0x0},
	//D0 /0 
	{(Pointer)0x00000313, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, Ins, 0x2},
	//D1 /0 
	{(Pointer)0x00000314, r_Slash_m32, NotDef, NotDef, (Pointer)NULL, Ins, 0x3},
	//D2 /0 
	{(Pointer)0x00000315, r_Slash_m8, CL, NotDef, (Pointer)NULL, Ins, 0x2},
	//D3 /0 
	{(Pointer)0x00000316, r_Slash_m32, CL, NotDef, (Pointer)NULL, Ins, 0x3},
	//D4 ib
	{AAM, NotDef, NotDef, NotDef, (Pointer)NULL, eAAM, 0x0},
	//D5 ib   
	{AAD, NotDef, NotDef, NotDef, (Pointer)NULL, eAAD, 0x0},
	//D6
	{SetAlc, NotDef, NotDef, NotDef, (Pointer)NULL, eSetAlc, 0x0},
	//D7 
	{XLATB, NotDef, NotDef, NotDef, (Pointer)NULL, eXLATB, 0x0},
	//D8 /0
	{(Pointer)0x01817200, m32, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 /0  
	{(Pointer)0x01A19200, m32real, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA /0 
	{(Pointer)0x01C1B200, m32int, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB /0 
	{(Pointer)0x01E1D200, m32int, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC /0    
	{(Pointer)0x0201F200, m64real, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD /0    
	{(Pointer)0x02221200, m64real, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE /0    
	{(Pointer)0x02423200, m16int, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF /0    
	{(Pointer)0x02625200, m16int, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//E0 cb    
	{LOOPNZ, rel8, NotDef, NotDef, (Pointer)NULL, eLOOPNZ, 0x0},
	//E1 cb    
	{LOOPZ, rel8, NotDef, NotDef, (Pointer)NULL, eLOOPZ, 0x0},
	//E2 cb    
	{LOOP, rel8, NotDef, NotDef, (Pointer)NULL, eLOOP, 0x0},
	//E3 cb    
	{JECXZ, rel8, NotDef, NotDef, (Pointer)NULL, eJECXZ, 0x2},
	//E4 ib    
	{IN_8, AL, imm8, NotDef, (Pointer)NULL, eIN_8, 0x0},
	//E5 ib    
	{IN_8, EAX, imm8, NotDef, (Pointer)NULL, eIN_8, 0x1},
	//E6 ib    
	{OUT_8, imm8, AL, NotDef, (Pointer)NULL, eOUT_8, 0x0},
	//E7 ib    
	{OUT_8, imm8, EAX, NotDef, (Pointer)NULL, eOUT_8, 0x1},
	//E8 cd    
	{CALL, rel32, NotDef, NotDef, (Pointer)NULL, eCALL, 0x0},
	//E9 cd    
	{JMP, rel32, NotDef, NotDef, (Pointer)NULL, eJMP, 0x0},
	//EA cp    
	{JMP, ptr16_Colon_32, NotDef, NotDef, (Pointer)NULL, eJMP, 0x0},
	//EB cb    
	{JMP, rel8, NotDef, NotDef, (Pointer)NULL, eJMP, 0x0},
	//EC    
	{IN_8, AL, DX, NotDef, (Pointer)NULL, eIN_8, 0x0},
	//ED    
	{IN_, EAX, DX, NotDef, IN_16, eIN_, 0x1},
	//EE   
	{OUT_8, DX, AL, NotDef, (Pointer)NULL, eOUT_8, 0x0},
	//EF   
	{OUT_, DX, EAX, NotDef, OUT_16, eOUT_, 0x1},
	//F0
	{LOCK, NotDef, NotDef, NotDef, (Pointer)NULL, eLOCK, 0x0},
	//F1 ICEBP
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//F2
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//F3
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//F4  
	{HLT, NotDef, NotDef, NotDef, (Pointer)NULL, eHLT, 0x0},
	//F5  
	{CMC, NotDef, NotDef, NotDef, (Pointer)NULL, eCMC, 0x0},
	//F6 /0 ib
	{(Pointer)0x00000327, r_Slash_m8, imm8, NotDef, (Pointer)NULL, Ins, 0x2},
	//F7 /0 id
	{(Pointer)0x00000328, r_Slash_m32, imm32, NotDef, (Pointer)NULL, Ins, 0x3},
	//F8  
	{CLC, NotDef, NotDef, NotDef, (Pointer)NULL, eCLC, 0x0},
	//F9  
	{STC, NotDef, NotDef, NotDef, (Pointer)NULL, eSTC, 0x0},
	//FA  
	{CLI, NotDef, NotDef, NotDef, (Pointer)NULL, eCLI, 0x0},
	//FB  
	{STI, NotDef, NotDef, NotDef, (Pointer)NULL, eSTI, 0x0},
	//FC  
	{CLD, NotDef, NotDef, NotDef, (Pointer)NULL, eCLD, 0x0},
	//FD  
	{STD, NotDef, NotDef, NotDef, (Pointer)NULL, eSTD, 0x0},
	//FE /0  
	{(Pointer)0x00000329, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, Ins, 0xA},
	//FF /0  
	{(Pointer)0x0000032A, r_Slash_m32, NotDef, NotDef, (Pointer)NULL, Ins, 0xB}
};

SMTableBlock arTable_0F [] = {
	//0F 00 /0
	{(Pointer)0x00000302, r_Slash_m32, NotDef, NotDef, (Pointer)NULL, Ins, 0x3},
	//0F 01 /0
	{(Pointer)0x00000303, m, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 02 /r
	{LAR, r32, r_Slash_m32, NotDef, LAR16, eLAR, 0x3},
	//0F 03 /r
	{LSL, r32, r_Slash_m32, NotDef, LSL16, eLSL, 0x3},
	//0F 04
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 05
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 06
	{CLTS, NotDef, NotDef, NotDef, (Pointer)NULL, eCLTS, 0x0},
	//0F 07
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 08 
	{INVD, NotDef, NotDef, NotDef, (Pointer)NULL, eINVD, 0x0},
	//0F 09 
	{WBINVD, NotDef, NotDef, NotDef, (Pointer)NULL, eWBINVD, 0x0},
	//0F 0A
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 0B 
	{UD2, NotDef, NotDef, NotDef, (Pointer)NULL, eUD2, 0x0},
	//0F 0C
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 0D
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 0E FEMMS
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 0F
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 10 /r 
	{MOVUPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eMOVUPS, 0x4},
	//0F 11 /r 
	{MOVUPS, xmm2_Slash_m128, xmm, NotDef, (Pointer)NULL, eMOVUPS, 0x4},
	//0F 12 /r 
	{MOVLPS, xmm, m64, NotDef, (Pointer)NULL, eMOVLPS, 0x0},
	//0F 13 /r 
	{MOVLPS, m64, xmm, NotDef, (Pointer)NULL, eMOVLPS, 0x0},
	//0F 14 /r 
	{UNPCKLPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eUNPCKLPS, 0x0},
	//0F 15 /r 
	{UNPCKHPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eUNPCKHPS, 0x0},
	//0F 16 /r 
	{MOVHPS, xmm, m64, NotDef, (Pointer)NULL, eMOVHPS, 0x0},
	//0F 17 /r 
	{MOVHPS, m64, xmm, NotDef, (Pointer)NULL, eMOVHPS, 0x0},
	//0F 18 /0 
	{(Pointer)0x00000304, m8, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 19
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 1A
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 1B
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 1C
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 1D
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 1E
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 1F
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 20 /r
	{MOV, r32, CR0, NotDef, (Pointer)NULL, eMOV, 0x0},
	//0F 21 /r
	{MOV, r32, DR0_DR7, NotDef, (Pointer)NULL, eMOV, 0x0},
	//0F 22 /r
	{MOV, CR0, r32, NotDef, (Pointer)NULL, eMOV, 0x0},
	//0F 23 /r
	{MOV, DR0_DR7, r32, NotDef, (Pointer)NULL, eMOV, 0x0},
	//0F 24
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 25
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 26
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 27
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 28 /r 
	{MOVAPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eMOVAPS, 0x0},
	//0F 29 /r 
	{MOVAPS, xmm2_Slash_m128, xmm, NotDef, (Pointer)NULL, eMOVAPS, 0x0},
	//0F 2A /r 
	{CVTPI2PS, xmm, mm_Slash_m64, NotDef, (Pointer)NULL, eCVTPI2PS, 0x4},
	//0F 2B, /r
	{MOVNTPS, m128, xmm, NotDef, (Pointer)NULL, eMOVNTPS, 0x0},
	//0F 2C /r 
	{CVTTPS2PI, mm, xmm_Slash_m64, NotDef, (Pointer)NULL, eCVTTPS2PI, 0x4},
	//0F 2D /r 
	{CVTPS2PI, mm, xmm_Slash_m64, NotDef, (Pointer)NULL, eCVTPS2PI, 0x4},
	//0F 2E /r
	{UCOMISS, xmm, xmm2_Slash_m32, NotDef, (Pointer)NULL, eUCOMISS, 0x0},
	//0F 2F /r
	{COMISS, xmm, xmm2_Slash_m32, NotDef, (Pointer)NULL, eCOMISS, 0x0},
	//0F 30 
	{WRMSR, NotDef, NotDef, NotDef, (Pointer)NULL, eWRMSR, 0x0},
	//0F 31 
	{RDTSC, EAX, EDX, NotDef, (Pointer)NULL, eRDTSC, 0x0},
	//0F 32 
	{RDMSR, NotDef, NotDef, NotDef, (Pointer)NULL, eRDMSR, 0x0},
	//0F 33 
	{RDPMC, NotDef, NotDef, NotDef, (Pointer)NULL, eRDPMC, 0x0},
	//0F 34 
	{SYSENTER, NotDef, NotDef, NotDef, (Pointer)NULL, eSYSENTER, 0x0},
	//0F 35 
	{SYSEXIT, NotDef, NotDef, NotDef, (Pointer)NULL, eSYSEXIT, 0x0},
	//0F 36
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 37
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 38
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 39
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 3A
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 3B
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 3C
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 3D
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 3E
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 3F
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 40 /r
	{CMOVO, r32, r_Slash_m32, NotDef, CMOVO16, eCMOVO, 0x3},
	//0F 41 /r
	{CMOVNO, r32, r_Slash_m32, NotDef, CMOVNO16, eCMOVNO, 0x3},
	//0F 42 /r
	{CMOVC, r32, r_Slash_m32, NotDef, CMOVC16, eCMOVC, 0x3},
	//0F 43 /r
	{CMOVAE, r32, r_Slash_m32, NotDef, CMOVAE16, eCMOVAE, 0x3},
	//0F 44 /r
	{CMOVZ, r32, r_Slash_m32, NotDef, CMOVZ16, eCMOVZ, 0x3},
	//0F 45 /r
	{CMOVNZ, r32, r_Slash_m32, NotDef, CMOVNZ16, eCMOVNZ, 0x3},
	//0F 46 /r
	{CMOVNA, r32, r_Slash_m32, NotDef, CMOVNA16, eCMOVNA, 0x3},
	//0F 47 /r
	{CMOVNBE, r32, r_Slash_m32, NotDef, CMOVNBE16, eCMOVNBE, 0x3},
	//0F 48 /r
	{CMOVS, r32, r_Slash_m32, NotDef, CMOVS16, eCMOVS, 0x3},
	//0F 49 /r
	{CMOVNS, r32, r_Slash_m32, NotDef, CMOVNS16, eCMOVNS, 0x3},
	//0F 4A /r
	{CMOVPE, r32, r_Slash_m32, NotDef, CMOVPE16, eCMOVPE, 0x3},
	//0F 4B /r
	{CMOVPO, r32, r_Slash_m32, NotDef, CMOVPO16, eCMOVPO, 0x3},
	//0F 4C /r
	{CMOVNGE, r32, r_Slash_m32, NotDef, CMOVNGE16, eCMOVNGE, 0x3},
	//0F 4D /r
	{CMOVNL, r32, r_Slash_m32, NotDef, CMOVNL16, eCMOVNL, 0x3},
	//0F 4E /r
	{CMOVNG, r32, r_Slash_m32, NotDef, CMOVNG16, eCMOVNG, 0x3},
	//0F 4F /r
	{CMOVNLE, r32, r_Slash_m32, NotDef, CMOVNLE16, eCMOVNLE, 0x3},
	//0F 50 /r 
	{MOVMSKPS, r32, xmm, NotDef, (Pointer)NULL, eMOVMSKPS, 0x0},
	//0F 51 /r 
	{SQRTPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eSQRTPS, 0x4},
	//0F 52 /r 
	{RSQRTPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eRSQRTPS, 0x4},
	//0F 53 /r 
	{RCPPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eRCPPS, 0x4},
	//0F 54 /r 
	{ANDPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eANDPS, 0x0},
	//0F 55 /r 
	{ANDNPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eANDNPS, 0x0},
	//0F 56 /r 
	{ORPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eORPS, 0x0},
	//0F 57 /r 
	{XORPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eXORPS, 0x0},
	//0F 58 /r 
	{ADDPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eADDPS, 0x4},
	//0F 59 /r 
	{MULPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eMULPS, 0x4},
	//0F 5A
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 5B
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 5C /r 
	{SUBPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eSUBPS, 0x4},
	//0F 5D /r 
	{MINPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eMINPS, 0x4},
	//0F 5E /r 
	{DIVPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eDIVPS, 0x4},
	//0F 5F /r 
	{MAXPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eMAXPS, 0x4},
	//0F 60 /r
	{PUNPCKLBW, mm, mm_Slash_m32, NotDef, (Pointer)NULL, ePUNPCKLBW, 0x0},
	//0F 61 /r
	{PUNPCKLWD, mm, mm_Slash_m32, NotDef, (Pointer)NULL, ePUNPCKLWD, 0x0},
	//0F 62 /r
	{PUNPCKLDQ, mm, mm_Slash_m32, NotDef, (Pointer)NULL, ePUNPCKLDQ, 0x0},
	//0F 63 /r
	{PACKSSWB, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePACKSSWB, 0x0},
	//0F 64 /r
	{PCMPGTB, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePCMPGTB, 0x0},
	//0F 65 /r
	{PCMPGTW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePCMPGTW, 0x0},
	//0F 66 /r
	{PCMPGTD, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePCMPGTD, 0x0},
	//0F 67 /r
	{PACKUSWB, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePACKUSWB, 0x0},
	//0F 68 /r
	{PUNPCKHBW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePUNPCKHBW, 0x0},
	//0F 69 /r
	{PUNPCKHWD, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePUNPCKHWD, 0x0},
	//0F 6A /r
	{PUNPCKHDQ, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePUNPCKHDQ, 0x0},
	//0F 6B /r
	{PACKSSDW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePACKSSDW, 0x0},
	//0F 6C
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 6D
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 6E /r
	{MOVD, mm, r_Slash_m32, NotDef, MOVD16, eMOVD, 0x3},
	//0F 6F /r
	{MOVQ, mm, mm_Slash_m64, NotDef, (Pointer)NULL, eMOVQ, 0x0},
	//0F 70 /r ib 
	{PSHUFW, mm, mm_Slash_m64, imm8, (Pointer)NULL, ePSHUFW, 0x0},
	//0F 71 /2 ib 
	{(Pointer)0x00000305, mm, imm8, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 72 /2 ib 
	{(Pointer)0x00000306, mm, imm8, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 73 /2 ib
	{(Pointer)0x00000307, mm, imm8, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 74 /r
	{PCMPEQB, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePCMPEQB, 0x0},
	//0F 75 /r
	{PCMPEQW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePCMPEQW, 0x0},
	//0F 76 /r
	{PCMPEQD, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePCMPEQD, 0x0},
	//0F 77 
	{EMMS, NotDef, NotDef, NotDef, (Pointer)NULL, eEMMS, 0x0},
	//0F 78
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 79
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 7A
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 7B
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 7C
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 7D
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 7E /r
	{MOVD, r_Slash_m32, mm, NotDef, MOVD16, eMOVD, 0x3},
	//0F 7F /r
	{MOVQ, mm_Slash_m64, mm, NotDef, (Pointer)NULL, eMOVQ, 0x0},
	//0F 80 cw/cd
	{JO, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJO, 0x1},
	//0F 81 cw/cd
	{JNO, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJNO, 0x1},
	//0F 82 cw/cd
	{JC, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJC, 0x1},
	//0F 83 cw/cd
	{JAE, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJAE, 0x1},
	//0F 84 cw/cd
	{JZ, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJZ, 0x1},
	//0F 85 cw/cd
	{JNZ, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJNZ, 0x1},
	//0F 86 cw/cd
	{JNA, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJNA, 0x1},
	//0F 87 cw/cd
	{JNBE, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJNBE, 0x1},
	//0F 88 cw/cd
	{JS, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJS, 0x1},
	//0F 89 cw/cd
	{JNS, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJNS, 0x1},
	//0F 8A cw/cd
	{JPE, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJPE, 0x1},
	//0F 8B cw/cd
	{JPO, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJPO, 0x1},
	//0F 8C cw/cd
	{JNGE, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJNGE, 0x1},
	//0F 8D cw/cd
	{JNL, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJNL, 0x1},
	//0F 8E cw/cd
	{JNG, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJNG, 0x1},
	//0F 8F cw/cd
	{JNLE, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJNLE, 0x1},
	//0F 90
	{SETO8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETO8, 0x2},
	//0F 91
	{SETNO8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETNO8, 0x2},
	//0F 92
	{SETB8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETB8, 0x2},
	//0F 93
	{SETNB8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETNB8, 0x2},
	//0F 94
	{SETZ8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETZ8, 0x2},
	//0F 95
	{SETNZ8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETNZ8, 0x2},
	//0F 96
	{SETNA8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETNA8, 0x2},
	//0F 97
	{SETNBE8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETNBE8, 0x2},
	//0F 98 
	{SETS8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETS8, 0x2},
	//0F 99
	{SETNS8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETNS8, 0x2},
	//0F 9A
	{SETPE8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETPE8, 0x2},
	//0F 9B
	{SETPO8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETPO8, 0x2},
	//0F 9C
	{SETNGE8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETNGE8, 0x2},
	//0F 9D
	{SETNL8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETNL8, 0x2},
	//0F 9E
	{SETNG8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETNG8, 0x2},
	//0F 9F
	{SETNLE8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETNLE8, 0x2},
	//0F A0
	{PUSH, FS, NotDef, NotDef, (Pointer)NULL, ePUSH, 0x0},
	//0F A1
	{POP, FS, NotDef, NotDef, (Pointer)NULL, ePOP, 0x0},
	//0F A2
	{CPUID, NotDef, NotDef, NotDef, (Pointer)NULL, eCPUID, 0x0},
	//0F A3
	{BT, r_Slash_m32, r32, NotDef, BT16, eBT, 0x3},
	//0F A4
	{SHLD, r_Slash_m32, r32, imm8, SHLD16, eSHLD, 0x3},
	//0F A5
	{SHLD, r_Slash_m32, r32, CL, SHLD16, eSHLD, 0x3},
	//0F A6
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F A7
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F A8
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F A9
	{POP, GS, NotDef, NotDef, (Pointer)NULL, ePOP, 0x0},
	//0F AA
	{RSM, NotDef, NotDef, NotDef, (Pointer)NULL, eRSM, 0x0},
	//0F AB
	{BTS, r_Slash_m32, r32, NotDef, BTS16, eBTS, 0xB},
	//0F AC
	{SHRD, r_Slash_m32, r32, imm8, SHRD16, eSHRD, 0x3},
	//0F AD
	{SHRD, r_Slash_m32, r32, CL, SHRD16, eSHRD, 0x3},
	//0F AE /0
	{(Pointer)0x00000308, m512byte, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F AF /r
	{IMUL, r32, r_Slash_m32, NotDef, IMUL16, eIMUL, 0x3},
	//0F B0 /r
	{CMPXCHG8, r_Slash_m8, r8, NotDef, (Pointer)NULL, eCMPXCHG8, 0xA},
	//0F B1 /r
	{CMPXCHG, r_Slash_m32, r32, NotDef, CMPXCHG16, eCMPXCHG, 0xB},
	//0F B2 /r
	{LSS, r32, m16_Colon_32, NotDef, LSS16, eLSS, 0x2},
	//0F B3
	{BTR, r_Slash_m32, r32, NotDef, BTR16, eBTR, 0xB},
	//0F B4 /r
	{LFS, r32, m16_Colon_32, NotDef, LFS16, eLFS, 0x2},
	//0F B5 /r
	{LGS, r32, m16_Colon_32, NotDef, LGS16, eLGS, 0x2},
	//0F B6 /r
	{MOVZX8, r32, r_Slash_m8, NotDef, (Pointer)NULL, eMOVZX8, 0x2},
	//0F B7 /r
	{MOVZX, r32, r_Slash_m16, NotDef, MOVZX16, eMOVZX, 0x3},
	//0F B8
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F B9
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F BA /4 ib
	{(Pointer)0x00000309, r_Slash_m32, imm8, NotDef, (Pointer)NULL, Ins, 0x3},
	//0F BB
	{BTC, r_Slash_m32, r32, NotDef, BTC16, eBTC, 0xB},
	//0F BC 
	{BSF, r32, r_Slash_m32, NotDef, BSF16, eBSF, 0x3},
	//0F BD
	{BSR, r32, r_Slash_m32, NotDef, BSR16, eBSR, 0x3},
	//0F BE /r
	{MOVSX8, r32, r_Slash_m8, NotDef, (Pointer)NULL, eMOVSX8, 0x2},
	//0F BF /r
	{MOVSX, r32, r_Slash_m16, NotDef, MOVSX16, eMOVSX, 0x3},
	//0F C0 /r
	{XADD8, r_Slash_m8, r8, NotDef, (Pointer)NULL, eXADD8, 0xA},
	//0F C1 /r
	{XADD, r_Slash_m32, r32, NotDef, XADD16, eXADD, 0xB},
	//0F C2 /r ib
	{CMPPS, xmm, xmm2_Slash_m128, imm8, (Pointer)NULL, eCMPPS, 0x4},
	//0F C3
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F C4 /r ib
	{PINSRW, mm, r32_Slash_m16, imm8, (Pointer)NULL, ePINSRW, 0x0},
	//0F C5 /r ib
	{PEXTRW, r32, mm, imm8, (Pointer)NULL, ePEXTRW, 0x0},
	//0F C6 /r ib
	{SHUFPS, xmm, xmm2_Slash_m128, imm8, (Pointer)NULL, eSHUFPS, 0x0},
	//0F C7 /1 m64 
	{(Pointer)0x0000030A, m64, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F C8
	{BSWAP, EAX, NotDef, NotDef, (Pointer)NULL, eBSWAP, 0x0},
	//0F C9
	{BSWAP, ECX, NotDef, NotDef, (Pointer)NULL, eBSWAP, 0x0},
	//0F CA
	{BSWAP, EDX, NotDef, NotDef, (Pointer)NULL, eBSWAP, 0x0},
	//0F CB
	{BSWAP, EBX, NotDef, NotDef, (Pointer)NULL, eBSWAP, 0x0},
	//0F CC
	{BSWAP, ESP, NotDef, NotDef, (Pointer)NULL, eBSWAP, 0x0},
	//0F CD
	{BSWAP, EBP, NotDef, NotDef, (Pointer)NULL, eBSWAP, 0x0},
	//0F CE
	{BSWAP, ESI, NotDef, NotDef, (Pointer)NULL, eBSWAP, 0x0},
	//0F CF
	{BSWAP, EDI, NotDef, NotDef, (Pointer)NULL, eBSWAP, 0x0},
	//0F D0
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F D1 /r
	{PSRLW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePSRLW, 0x0},
	//0F D2 /r
	{PSRLD, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePSRLD, 0x0},
	//0F D3 /r
	{PSRLQ, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePSRLQ, 0x0},
	//0F D4
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F D5 /r
	{PMULLW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePMULLW, 0x0},
	//0F D6
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F D7 /r
	{PMOVMSKB, r32, mm, NotDef, (Pointer)NULL, ePMOVMSKB, 0x0},
	//0F D8 /r
	{PSUBUSB, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePSUBUSB, 0x0},
	//0F D9 /r
	{PSUBUSW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePSUBUSW, 0x0},
	//0F DA, /r
	{PMINUB, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePMINUB, 0x0},
	//0F DB /r
	{PAND, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePAND, 0x0},
	//0F DC /r
	{PADDUSB, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePADDUSB, 0x0},
	//0F DD /r
	{PADDUSW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePADDUSW, 0x0},
	//0F DE /r
	{PMAXUB, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePMAXUB, 0x0},
	//0F DF /r
	{PANDN, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePANDN, 0x0},
	//0F E0 /r
	{PAVGB, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePAVGB, 0x0},
	//0F E1 /r
	{PSRAW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePSRAW, 0x0},
	//0F E2 /r
	{PSRAD, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePSRAD, 0x0},
	//0F E3 /r
	{PAVGW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePAVGW, 0x0},
	//0F E4 /r
	{PMULHUW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePMULHUW, 0x0},
	//0F E5 /r
	{PMULHW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePMULHW, 0x0},
	//0F E6
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F E7 /r
	{MOVNTQ, m64, mm, NotDef, (Pointer)NULL, eMOVNTQ, 0x0},
	//0F E8 /r
	{PSUBSB, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePSUBSB, 0x0},
	//0F E9 /r
	{PSUBSW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePSUBSW, 0x0},
	//0F EA /r
	{PMINSW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePMINSW, 0x0},
	//0F EB /r
	{POR, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePOR, 0x0},
	//0F EC /r
	{PADDSB, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePADDSB, 0x0},
	//0F ED /r
	{PADDSW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePADDSW, 0x0},
	//0F EE /r
	{PMAXSW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePMAXSW, 0x0},
	//0F EF /r
	{PXOR, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePXOR, 0x0},
	//0F F0
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F F1 /r
	{PSLLW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePSLLW, 0x0},
	//0F F2 /r
	{PSLLD, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePSLLD, 0x0},
	//0F F3 /r
	{PSLLQ, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePSLLQ, 0x0},
	//0F F4
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F F5 /r
	{PMADDWD, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePMADDWD, 0x0},
	//0F F6 /r
	{PSADBW, NotDef, NotDef, NotDef, (Pointer)NULL, ePSADBW, 0x0},
	//0F F7 /r
	{MASKMOVQ, NotDef, NotDef, NotDef, (Pointer)NULL, eMASKMOVQ, 0x0},
	//0F F8 /r
	{PSUBB, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePSUBB, 0x0},
	//0F F9 /r
	{PSUBW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePSUBW, 0x0},
	//0F FA /r
	{PSUBD, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePSUBD, 0x0},
	//0F FB
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F FC /r
	{PADDB, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePADDB, 0x0},
	//0F FD /r
	{PADDW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePADDW, 0x0},
	//0F FE /r
	{PADDD, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePADDD, 0x0},
	//0F FF
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock arTable_0F00Ext [] = {
	//0F 00 /0
	{SLDT, r_Slash_m32, NotDef, NotDef, SLDT16, eSLDT, 0x3},
	//0F 00 /1
	{STR, r_Slash_m16, NotDef, NotDef, STR16, eSTR, 0x3},
	//0F 00 /2
	{LLDT, r_Slash_m16, NotDef, NotDef, LLDT16, eLLDT, 0x3},
	//0F 00 /3
	{LTR, r_Slash_m16, NotDef, NotDef, LTR16, eLTR, 0x3},
	//0F 00 /4
	{VERR, r_Slash_m16, NotDef, NotDef, VERR16, eVERR, 0x3},
	//0F 00 /5
	{VERW, r_Slash_m16, NotDef, NotDef, VERW16, eVERW, 0x3},
	//0F 00 /6
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 00 /7
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock arTable_0F01Ext [] = {
	//0F 01 /0
	{SGDT, m, NotDef, NotDef, (Pointer)NULL, eSGDT, 0x0},
	//0F 01 /1
	{SIDT, m, NotDef, NotDef, (Pointer)NULL, eSIDT, 0x0},
	//0F 01 /2
	{LGDT, m16_Amp_32, NotDef, NotDef, (Pointer)NULL, eLGDT, 0x0},
	//0F 01 /3
	{LIDT, m16_Amp_32, NotDef, NotDef, (Pointer)NULL, eLIDT, 0x0},
	//0F 01 /4
	{SMSW, r32_Slash_m16, NotDef, NotDef, (Pointer)NULL, eSMSW, 0x0},
	//0F 01 /5
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 01 /6
	{LMSW, r_Slash_m16, NotDef, NotDef, LMSW16, eLMSW, 0x3},
	//0F 01 /7
	{INVLPG, m, NotDef, NotDef, (Pointer)NULL, eINVLPG, 0x0},
};

SMTableBlock arTable_0F18Ext [] = {
	//0F 18 /0 
	{PREFETCHNTA8, m8, NotDef, NotDef, (Pointer)NULL, ePREFETCHNTA8, 0x0},
	//0F 18 /1 
	{PREFETCHT08, m8, NotDef, NotDef, (Pointer)NULL, ePREFETCHT08, 0x0},
	//0F 18 /2 
	{PREFETCHT18, m8, NotDef, NotDef, (Pointer)NULL, ePREFETCHT18, 0x0},
	//0F 18 /3 
	{PREFETCHT28, m8, NotDef, NotDef, (Pointer)NULL, ePREFETCHT28, 0x0},
	//0F 18 /4
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 18 /5
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 18 /6
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 18 /7
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock arTable_0F71Ext [] = {
	//0F 71 /0
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 71 /1
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 71 /2 ib 
	{PSRLW8, mm, imm8, NotDef, (Pointer)NULL, ePSRLW8, 0x0},
	//0F 71 /3
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 71 /4 ib
	{PSRAW8, mm, imm8, NotDef, (Pointer)NULL, ePSRAW8, 0x0},
	//0F 71 /5
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 71 /6 ib
	{PSLLW8, mm, imm8, NotDef, (Pointer)NULL, ePSLLW8, 0x0},
	//0F 71 /7
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock arTable_0F72Ext [] = {
	//0F 72 /0
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 72 /1
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 72 /2 ib 
	{PSRLD8, mm, imm8, NotDef, (Pointer)NULL, ePSRLD8, 0x0},
	//0F 72 /3
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 72 /4 ib
	{PSRAD8, mm, imm8, NotDef, (Pointer)NULL, ePSRAD8, 0x0},
	//0F 72 /5
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 72 /6 ib
	{PSLLD8, mm, imm8, NotDef, (Pointer)NULL, ePSLLD8, 0x0},
	//0F 72 /7
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock arTable_0F73Ext [] = {
	//0F 73 /0
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 73 /1
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 73 /2 ib
	{PSRLQ8, mm, imm8, NotDef, (Pointer)NULL, ePSRLQ8, 0x0},
	//0F 73 /3
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 73 /4
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 73 /5
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 73 /6 ib
	{PSLLQ8, mm, imm8, NotDef, (Pointer)NULL, ePSLLQ8, 0x0},
	//0F 73 /7
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock arTable_0FAEExt [] = {
	//0F AE /0
	{FXSAVE, m512byte, NotDef, NotDef, (Pointer)NULL, eFXSAVE, 0x0},
	//0F AE /1
	{FXRSTOR, m512byte, NotDef, NotDef, (Pointer)NULL, eFXRSTOR, 0x0},
	//0F AE /2
	{LDMXCSR, m32, NotDef, NotDef, (Pointer)NULL, eLDMXCSR, 0x0},
	//0F AE /3
	{STMXCSR, m32, NotDef, NotDef, (Pointer)NULL, eSTMXCSR, 0x0},
	//0F AE /4
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F AE /5
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F AE /6
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F AE /7
	{SFENCE, NotDef, NotDef, NotDef, (Pointer)NULL, eSFENCE, 0x0},
};

SMTableBlock arTable_0FBAExt [] = {
	//0F BA /0
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F BA /1
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F BA /2
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F BA /3
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F BA /4 ib
	{BT, r_Slash_m32, imm8, NotDef, BT16, eBT, 0x3},
	//0F BA /5 ib
	{BTS, r_Slash_m32, imm8, NotDef, BTS16, eBTS, 0xB},
	//0F BA /6 ib
	{BTR, r_Slash_m32, imm8, NotDef, BTR16, eBTR, 0xB},
	//0F BA /7 ib
	{BTC, r_Slash_m32, imm8, NotDef, BTC16, eBTC, 0xB},
};

SMTableBlock arTable_0FC7Ext [] = {
	//0F C7 /0
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F C7 /1 m64 
	{CMPXCHG8B, m64, NotDef, NotDef, (Pointer)NULL, eCMPXCHG8B, 0x0},
	//0F C7 /2
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F C7 /3
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F C7 /4
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F C7 /5
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F C7 /6
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F C7 /7
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock arTable_80Ext [] = {
	//80 /0 ib
	{ADD8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eADD8, 0xA},
	//80 /1 ib
	{OR8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eOR8, 0xA},
	//80 /2 ib
	{ADC8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eADC8, 0xA},
	//80 /3 ib
	{SBB8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eSBB8, 0xA},
	//80 /4 ib
	{AND8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eAND8, 0xA},
	//80 /5 ib
	{SUB8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eSUB8, 0xA},
	//80 /6 ib
	{XOR8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eXOR8, 0xA},
	//80 /7 ib 
	{CMP8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eCMP8, 0x2},
};

SMTableBlock arTable_81Ext [] = {
	//81 /0 id
	{ADD, r_Slash_m32, imm32, NotDef, ADD16, eADD, 0xB},
	//81 /1 id
	{OR, r_Slash_m32, imm32, NotDef, OR16, eOR, 0xB},
	//81 /2 iw
	{ADC, r_Slash_m32, imm32, NotDef, ADC16, eADC, 0xB},
	//81 /3 id
	{SBB, r_Slash_m32, imm32, NotDef, SBB16, eSBB, 0xB},
	//81 /4 id
	{AND, r_Slash_m32, imm32, NotDef, AND16, eAND, 0xB},
	//81 /5 id
	{SUB, r_Slash_m32, imm32, NotDef, SUB16, eSUB, 0xB},
	//81 /6 id 
	{XOR, r_Slash_m32, imm32, NotDef, XOR16, eXOR, 0xB},
	//81 /7 id 
	{CMP, r_Slash_m32, imm32, NotDef, CMP16, eCMP, 0x3},
};

SMTableBlock arTable_83Ext [] = {
	//83 /0 ib
	{ADD, r_Slash_m32, imm8, NotDef, ADD16, eADD, 0xB},
	//83 /1 ib
	{OR, r_Slash_m32, imm8, NotDef, OR16, eOR, 0xB},
	//83 /2 ib
	{ADC, r_Slash_m32, imm8, NotDef, ADC16, eADC, 0xB},
	//83 /3 ib
	{SBB, r_Slash_m32, imm8, NotDef, SBB16, eSBB, 0xB},
	//83 /4 ib
	{AND, r_Slash_m32, imm8, NotDef, AND16, eAND, 0xB},
	//83 /5 ib
	{SUB, r_Slash_m32, imm8, NotDef, SUB16, eSUB, 0xB},
	//83 /6 ib 
	{XOR, r_Slash_m32, imm8, NotDef, XOR16, eXOR, 0xB},
	//83 /7 ib 
	{CMP, r_Slash_m32, imm8, NotDef, CMP16, eCMP, 0x3},
};

SMTableBlock arTable_8FExt [] = {
	//8F /0
	{POP, m32, NotDef, NotDef, (Pointer)NULL, ePOP, 0x0},
	//8F /1
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//8F /2
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//8F /3
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//8F /4
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//8F /5
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//8F /6
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//8F /7
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock arTable_C0Ext [] = {
	//C0 /0 ib 
	{ROL8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eROL8, 0x2},
	//C0 /1 ib 
	{ROR8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eROR8, 0x2},
	//C0 /2 ib 
	{RCL8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eRCL8, 0x2},
	//C0 /3 ib 
	{RCR8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eRCR8, 0x2},
	//C0 /4 ib 
	{SHL8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eSHL8, 0x2},
	//C0 /5 ib 
	{SHR8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eSHR8, 0x2},
	//C0 /6
	{SHL8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eSHL8, 0x2},
	//C0 /7 ib 
	{SAR8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eSAR8, 0x2},
};

SMTableBlock arTable_C1Ext [] = {
	//C1 /0 ib 
	{ROL, r_Slash_m32, imm8, NotDef, ROL16, eROL, 0x3},
	//C1 /1 ib 
	{ROR, r_Slash_m32, imm8, NotDef, ROR16, eROR, 0x3},
	//C1 /2 ib 
	{RCL, r_Slash_m32, imm8, NotDef, RCL16, eRCL, 0x3},
	//C1 /3 ib 
	{RCR, r_Slash_m32, imm8, NotDef, RCR16, eRCR, 0x3},
	//C1 /4 ib 
	{SHL, r_Slash_m32, imm8, NotDef, SHL16, eSHL, 0x3},
	//C1 /5 ib 
	{SHR, r_Slash_m32, imm8, NotDef, SHR16, eSHR, 0x3},
	//C1 /6
	{SHL, r_Slash_m32, imm8, NotDef, SHL16, eSHL, 0x3},
	//C1 /7 ib
	{SAR, r_Slash_m32, imm8, NotDef, SAR16, eSAR, 0x3},
};

SMTableBlock arTable_C6Ext [] = {
	//C6 /0 
	{MOV8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eMOV8, 0x2},
	//C6 /1
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//C6 /2
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//C6 /3
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//C6 /4
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//C6 /5
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//C6 /6
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//C6 /7
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock arTable_C7Ext [] = {
	//C7 /0 
	{MOV, r_Slash_m32, imm32, NotDef, MOV16, eMOV, 0x3},
	//C7 /1
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//C7 /2
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//C7 /3
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//C7 /4
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//C7 /5
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//C7 /6
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//C7 /7
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock arTable_D0Ext [] = {
	//D0 /0 
	{ROL8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eROL8, 0x2},
	//D0 /1
	{ROR8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eROR8, 0x2},
	//D0 /2
	{RCL8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eRCL8, 0x2},
	//D0 /3
	{RCR8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eRCR8, 0x2},
	//D0 /4  
	{SHL8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSHL8, 0x2},
	//D0 /5  
	{SHR8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSHR8, 0x2},
	//D0 /6
	{SHL8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSHL8, 0x2},
	//D0 /7  
	{SAR8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSAR8, 0x2},
};

SMTableBlock arTable_D1Ext [] = {
	//D1 /0 
	{ROL, r_Slash_m32, NotDef, NotDef, ROL16, eROL, 0x3},
	//D1 /1 
	{ROR, r_Slash_m32, NotDef, NotDef, ROR16, eROR, 0x3},
	//D1 /2 
	{RCL, r_Slash_m32, NotDef, NotDef, RCL16, eRCL, 0x3},
	//D1 /3 
	{RCR, r_Slash_m32, NotDef, NotDef, RCR16, eRCR, 0x3},
	//D1 /4  
	{SHL, r_Slash_m32, NotDef, NotDef, SHL16, eSHL, 0x3},
	//D1 /5  
	{SHR, r_Slash_m32, NotDef, NotDef, SHR16, eSHR, 0x3},
	//D1 /6
	{SHL, r_Slash_m32, NotDef, NotDef, SHL16, eSHL, 0x3},
	//D1 /7  
	{SAR, r_Slash_m32, NotDef, NotDef, SAR16, eSAR, 0x3},
};

SMTableBlock arTable_D2Ext [] = {
	//D2 /0 
	{ROL8, r_Slash_m8, CL, NotDef, (Pointer)NULL, eROL8, 0x2},
	//D2 /1 
	{ROR8, r_Slash_m8, CL, NotDef, (Pointer)NULL, eROR8, 0x2},
	//D2 /2 
	{RCL8, r_Slash_m8, CL, NotDef, (Pointer)NULL, eRCL8, 0x2},
	//D2 /3 
	{RCR8, r_Slash_m8, CL, NotDef, (Pointer)NULL, eRCR8, 0x2},
	//D2 /4  
	{SHL8, r_Slash_m8, CL, NotDef, (Pointer)NULL, eSHL8, 0x2},
	//D2 /5  
	{SHR8, r_Slash_m8, CL, NotDef, (Pointer)NULL, eSHR8, 0x2},
	//D2 /6
	{SHL8, r_Slash_m8, CL, NotDef, (Pointer)NULL, eSHL8, 0x2},
	//D2 /7  
	{SAR8, r_Slash_m8, CL, NotDef, (Pointer)NULL, eSAR8, 0x2},
};

SMTableBlock arTable_D3Ext [] = {
	//D3 /0 
	{ROL8, r_Slash_m32, CL, NotDef, (Pointer)NULL, eROL8, 0x3},
	//D3 /1 
	{ROR8, r_Slash_m32, CL, NotDef, (Pointer)NULL, eROR8, 0x3},
	//D3 /2 
	{RCL8, r_Slash_m32, CL, NotDef, (Pointer)NULL, eRCL8, 0x3},
	//D3 /3 
	{RCR8, r_Slash_m32, CL, NotDef, (Pointer)NULL, eRCR8, 0x3},
	//D3 /4  
	{SHL8, r_Slash_m32, CL, NotDef, (Pointer)NULL, eSHL8, 0x3},
	//D3 /5  
	{SHR8, r_Slash_m32, CL, NotDef, (Pointer)NULL, eSHR8, 0x3},
	//D3 /6
	{SHL8, r_Slash_m32, CL, NotDef, (Pointer)NULL, eSHL8, 0x3},
	//D3 /7  
	{SAR8, r_Slash_m32, CL, NotDef, (Pointer)NULL, eSAR8, 0x3},
};

SMTableBlock arTable_D8Ext [] = {
	//D8 /0
	{FADD, m32, NotDef, NotDef, (Pointer)NULL, eFADD, 0x0},
	//D8 /1
	{FMUL, m32real, NotDef, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//D8 /2 
	{FCOM, m32real, NotDef, NotDef, (Pointer)NULL, eFCOM, 0x0},
	//D8 /3 
	{FCOMP, m32real, NotDef, NotDef, (Pointer)NULL, eFCOMP, 0x0},
	//D8 /4 
	{FSUB, m32real, NotDef, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//D8 /5 
	{FSUBR, m32real, NotDef, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//D8 /6 
	{FDIV, m32real, NotDef, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//D8 /7 
	{FDIVR, m32real, NotDef, NotDef, (Pointer)NULL, eFDIVR, 0x0},
};

SMTableBlock arTable_D8_Abnormal [] = {
	//D8 C0
	{FADD, ST__0__, ST__0__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//D8 C1
	{FADD, ST__0__, ST__1__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//D8 C2
	{FADD, ST__0__, ST__2__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//D8 C3
	{FADD, ST__0__, ST__3__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//D8 C4
	{FADD, ST__0__, ST__4__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//D8 C5
	{FADD, ST__0__, ST__5__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//D8 C6
	{FADD, ST__0__, ST__6__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//D8 C7
	{FADD, ST__0__, ST__7__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//D8 C8
	{FMUL, ST__0__, ST__8__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//D8 C9
	{FMUL, ST__0__, ST__9__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//D8 CA
	{FMUL, ST__0__, ST__10__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//D8 CB
	{FMUL, ST__0__, ST__11__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//D8 CC
	{FMUL, ST__0__, ST__12__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//D8 CD
	{FMUL, ST__0__, ST__13__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//D8 CE
	{FMUL, ST__0__, ST__14__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//D8 CF
	{FMUL, ST__0__, ST__15__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//D8 D0
	{FCOM, ST__0__, NotDef, NotDef, (Pointer)NULL, eFCOM, 0x0},
	//D8 D1
	{FCOM, ST__1__, NotDef, NotDef, (Pointer)NULL, eFCOM, 0x0},
	//D8 D2
	{FCOM, ST__2__, NotDef, NotDef, (Pointer)NULL, eFCOM, 0x0},
	//D8 D3
	{FCOM, ST__3__, NotDef, NotDef, (Pointer)NULL, eFCOM, 0x0},
	//D8 D4
	{FCOM, ST__4__, NotDef, NotDef, (Pointer)NULL, eFCOM, 0x0},
	//D8 D5
	{FCOM, ST__5__, NotDef, NotDef, (Pointer)NULL, eFCOM, 0x0},
	//D8 D6
	{FCOM, ST__6__, NotDef, NotDef, (Pointer)NULL, eFCOM, 0x0},
	//D8 D7
	{FCOM, ST__7__, NotDef, NotDef, (Pointer)NULL, eFCOM, 0x0},
	//D8 D8
	{FCOMP, ST__8__, NotDef, NotDef, (Pointer)NULL, eFCOMP, 0x0},
	//D8 D9
	{FCOMP, ST__9__, NotDef, NotDef, (Pointer)NULL, eFCOMP, 0x0},
	//D8 DA
	{FCOMP, ST__10__, NotDef, NotDef, (Pointer)NULL, eFCOMP, 0x0},
	//D8 DB
	{FCOMP, ST__11__, NotDef, NotDef, (Pointer)NULL, eFCOMP, 0x0},
	//D8 DC
	{FCOMP, ST__12__, NotDef, NotDef, (Pointer)NULL, eFCOMP, 0x0},
	//D8 DD
	{FCOMP, ST__13__, NotDef, NotDef, (Pointer)NULL, eFCOMP, 0x0},
	//D8 DE
	{FCOMP, ST__14__, NotDef, NotDef, (Pointer)NULL, eFCOMP, 0x0},
	//D8 DF
	{FCOMP, ST__15__, NotDef, NotDef, (Pointer)NULL, eFCOMP, 0x0},
	//D8 E0
	{FSUB, ST__0__, ST__0__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//D8 E1
	{FSUB, ST__0__, ST__1__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//D8 E2
	{FSUB, ST__0__, ST__2__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//D8 E3
	{FSUB, ST__0__, ST__3__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//D8 E4
	{FSUB, ST__0__, ST__4__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//D8 E5
	{FSUB, ST__0__, ST__5__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//D8 E6
	{FSUB, ST__0__, ST__6__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//D8 E7
	{FSUB, ST__0__, ST__7__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//D8 E8
	{FSUBR, ST__0__, ST__8__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//D8 E9
	{FSUBR, ST__0__, ST__9__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//D8 EA
	{FSUBR, ST__0__, ST__10__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//D8 EB
	{FSUBR, ST__0__, ST__11__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//D8 EC
	{FSUBR, ST__0__, ST__12__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//D8 ED
	{FSUBR, ST__0__, ST__13__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//D8 EE
	{FSUBR, ST__0__, ST__14__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//D8 EF
	{FSUBR, ST__0__, ST__15__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//D8 F0
	{FDIV, ST__0__, ST__0__, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//D8 F1
	{FDIV, ST__0__, ST__1__, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//D8 F2
	{FDIV, ST__0__, ST__2__, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//D8 F3
	{FDIV, ST__0__, ST__3__, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//D8 F4
	{FDIV, ST__0__, ST__4__, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//D8 F5
	{FDIV, ST__0__, ST__5__, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//D8 F6
	{FDIV, ST__0__, ST__6__, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//D8 F7
	{FDIV, ST__0__, ST__7__, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//D8 F8
	{FDIVR, ST__0__, ST__8__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
	//D8 F9
	{FDIVR, ST__0__, ST__9__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
	//D8 FA
	{FDIVR, ST__0__, ST__10__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
	//D8 FB
	{FDIVR, ST__0__, ST__11__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
	//D8 FC
	{FDIVR, ST__0__, ST__12__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
	//D8 FD
	{FDIVR, ST__0__, ST__13__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
	//D8 FE
	{FDIVR, ST__0__, ST__14__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
	//D8 FF
	{FDIVR, ST__0__, ST__15__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
};

SMTableBlock arTable_D9Ext [] = {
	//D9 /0  
	{FLD, m32real, NotDef, NotDef, (Pointer)NULL, eFLD, 0x0},
	//D9 /1
	{FXCH, m32real, NotDef, NotDef, (Pointer)NULL, eFXCH, 0x0},
	//D9 /2 
	{FST, m32real, NotDef, NotDef, (Pointer)NULL, eFST, 0x0},
	//D9 /3 
	{FSTP, m32real, NotDef, NotDef, (Pointer)NULL, eFSTP, 0x0},
	//D9 /4 
	{FLDENV, m14_Slash_28byte, NotDef, NotDef, (Pointer)NULL, eFLDENV, 0x0},
	//D9 /5 
	{FLDCW, m2byte, NotDef, NotDef, (Pointer)NULL, eFLDCW, 0x0},
	//D9 /6 
	{FNSTENV, m14_Slash_28byte, NotDef, NotDef, (Pointer)NULL, eFNSTENV, 0x0},
	//D9 /7 
	{FNSTCW, m2byte, NotDef, NotDef, (Pointer)NULL, eFNSTCW, 0x0},
};

SMTableBlock arTable_D9_Abnormal [] = {
	//D9 C0
	{FLD, ST__0__, NotDef, NotDef, (Pointer)NULL, eFLD, 0x0},
	//D9 C1
	{FLD, ST__1__, NotDef, NotDef, (Pointer)NULL, eFLD, 0x0},
	//D9 C2
	{FLD, ST__2__, NotDef, NotDef, (Pointer)NULL, eFLD, 0x0},
	//D9 C3
	{FLD, ST__3__, NotDef, NotDef, (Pointer)NULL, eFLD, 0x0},
	//D9 C4
	{FLD, ST__4__, NotDef, NotDef, (Pointer)NULL, eFLD, 0x0},
	//D9 C5
	{FLD, ST__5__, NotDef, NotDef, (Pointer)NULL, eFLD, 0x0},
	//D9 C6
	{FLD, ST__6__, NotDef, NotDef, (Pointer)NULL, eFLD, 0x0},
	//D9 C7
	{FLD, ST__7__, NotDef, NotDef, (Pointer)NULL, eFLD, 0x0},
	//D9 C8
	{FXCH, ST__8__, NotDef, NotDef, (Pointer)NULL, eFXCH, 0x0},
	//D9 C9
	{FXCH, ST__9__, NotDef, NotDef, (Pointer)NULL, eFXCH, 0x0},
	//D9 CA
	{FXCH, ST__10__, NotDef, NotDef, (Pointer)NULL, eFXCH, 0x0},
	//D9 CB
	{FXCH, ST__11__, NotDef, NotDef, (Pointer)NULL, eFXCH, 0x0},
	//D9 CC
	{FXCH, ST__12__, NotDef, NotDef, (Pointer)NULL, eFXCH, 0x0},
	//D9 CD
	{FXCH, ST__13__, NotDef, NotDef, (Pointer)NULL, eFXCH, 0x0},
	//D9 CE
	{FXCH, ST__14__, NotDef, NotDef, (Pointer)NULL, eFXCH, 0x0},
	//D9 CF
	{FXCH, ST__15__, NotDef, NotDef, (Pointer)NULL, eFXCH, 0x0},
	//D9 D0  
	{FNOP, NotDef, NotDef, NotDef, (Pointer)NULL, eFNOP, 0x0},
	//D9 D1
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 D2
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 D3
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 D4
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 D5
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 D6
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 D7
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 D8
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 D9
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 DA
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 DB
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 DC
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 DD
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 DE
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 DF
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 E0  
	{FCHS, NotDef, NotDef, NotDef, (Pointer)NULL, eFCHS, 0x0},
	//D9 E1  
	{FABS, NotDef, NotDef, NotDef, (Pointer)NULL, eFABS, 0x0},
	//D9 E2
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 E3
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 E4  
	{FTST, NotDef, NotDef, NotDef, (Pointer)NULL, eFTST, 0x0},
	//D9 E5  
	{FXAM, NotDef, NotDef, NotDef, (Pointer)NULL, eFXAM, 0x0},
	//D9 E6
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 E7
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 E8  
	{FLD1, NotDef, NotDef, NotDef, (Pointer)NULL, eFLD1, 0x0},
	//D9 E9  
	{FLDL2T, NotDef, NotDef, NotDef, (Pointer)NULL, eFLDL2T, 0x0},
	//D9 EA  
	{FLDL2E, NotDef, NotDef, NotDef, (Pointer)NULL, eFLDL2E, 0x0},
	//D9 EB  
	{FLDPI, NotDef, NotDef, NotDef, (Pointer)NULL, eFLDPI, 0x0},
	//D9 EC  
	{FLDLG2, NotDef, NotDef, NotDef, (Pointer)NULL, eFLDLG2, 0x0},
	//D9 ED  
	{FLDLN2, NotDef, NotDef, NotDef, (Pointer)NULL, eFLDLN2, 0x0},
	//D9 EE  
	{FLDZ, NotDef, NotDef, NotDef, (Pointer)NULL, eFLDZ, 0x0},
	//D9 EF
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 F0  
	{F2XM1, NotDef, NotDef, NotDef, (Pointer)NULL, eF2XM1, 0x0},
	//D9 F1  
	{FYL2X, NotDef, NotDef, NotDef, (Pointer)NULL, eFYL2X, 0x0},
	//D9 F2  
	{FPTAN, NotDef, NotDef, NotDef, (Pointer)NULL, eFPTAN, 0x0},
	//D9 F3  
	{FPATAN, NotDef, NotDef, NotDef, (Pointer)NULL, eFPATAN, 0x0},
	//D9 F4  
	{FXTRACT, NotDef, NotDef, NotDef, (Pointer)NULL, eFXTRACT, 0x0},
	//D9 F5  
	{FPREM1, NotDef, NotDef, NotDef, (Pointer)NULL, eFPREM1, 0x0},
	//D9 F6  
	{FDECSTP, NotDef, NotDef, NotDef, (Pointer)NULL, eFDECSTP, 0x0},
	//D9 F7  
	{FINCSTP, NotDef, NotDef, NotDef, (Pointer)NULL, eFINCSTP, 0x0},
	//D9 F8  
	{FPREM, NotDef, NotDef, NotDef, (Pointer)NULL, eFPREM, 0x0},
	//D9 F9  
	{FYL2XP1, NotDef, NotDef, NotDef, (Pointer)NULL, eFYL2XP1, 0x0},
	//D9 FA  
	{FSQRT, NotDef, NotDef, NotDef, (Pointer)NULL, eFSQRT, 0x0},
	//D9 FB  
	{FSINCOS, NotDef, NotDef, NotDef, (Pointer)NULL, eFSINCOS, 0x0},
	//D9 FC  
	{FRNDINT, NotDef, NotDef, NotDef, (Pointer)NULL, eFRNDINT, 0x0},
	//D9 FD  
	{FSCALE, NotDef, NotDef, NotDef, (Pointer)NULL, eFSCALE, 0x0},
	//D9 FE  
	{FSIN, NotDef, NotDef, NotDef, (Pointer)NULL, eFSIN, 0x0},
	//D9 FF  
	{FCOS, NotDef, NotDef, NotDef, (Pointer)NULL, eFCOS, 0x0},
};

SMTableBlock arTable_DAExt [] = {
	//DA /0 
	{FIADD, m32int, NotDef, NotDef, (Pointer)NULL, eFIADD, 0x0},
	//DA /1  
	{FIMUL, m32int, NotDef, NotDef, (Pointer)NULL, eFIMUL, 0x0},
	//DA /2   
	{FICOM, m32int, NotDef, NotDef, (Pointer)NULL, eFICOM, 0x0},
	//DA /3   
	{FICOMP, m32int, NotDef, NotDef, (Pointer)NULL, eFICOMP, 0x0},
	//DA /4   
	{FISUB, m32int, NotDef, NotDef, (Pointer)NULL, eFISUB, 0x0},
	//DA /5   
	{FISUBR, m32int, NotDef, NotDef, (Pointer)NULL, eFISUBR, 0x0},
	//DA /6   
	{FIDIV, m32int, NotDef, NotDef, (Pointer)NULL, eFIDIV, 0x0},
	//DA /7   
	{FIDIVR, m32int, NotDef, NotDef, (Pointer)NULL, eFIDIVR, 0x0},
};

SMTableBlock arTable_DA_Abnormal [] = {
	//DA C0
	{FCMOVB, ST__0__, ST__0__, NotDef, (Pointer)NULL, eFCMOVB, 0x0},
	//DA C1
	{FCMOVB, ST__0__, ST__1__, NotDef, (Pointer)NULL, eFCMOVB, 0x0},
	//DA C2
	{FCMOVB, ST__0__, ST__2__, NotDef, (Pointer)NULL, eFCMOVB, 0x0},
	//DA C3
	{FCMOVB, ST__0__, ST__3__, NotDef, (Pointer)NULL, eFCMOVB, 0x0},
	//DA C4
	{FCMOVB, ST__0__, ST__4__, NotDef, (Pointer)NULL, eFCMOVB, 0x0},
	//DA C5
	{FCMOVB, ST__0__, ST__5__, NotDef, (Pointer)NULL, eFCMOVB, 0x0},
	//DA C6
	{FCMOVB, ST__0__, ST__6__, NotDef, (Pointer)NULL, eFCMOVB, 0x0},
	//DA C7
	{FCMOVB, ST__0__, ST__7__, NotDef, (Pointer)NULL, eFCMOVB, 0x0},
	//DA C8
	{FCMOVE, ST__0__, ST__8__, NotDef, (Pointer)NULL, eFCMOVE, 0x0},
	//DA C9
	{FCMOVE, ST__0__, ST__9__, NotDef, (Pointer)NULL, eFCMOVE, 0x0},
	//DA CA
	{FCMOVE, ST__0__, ST__10__, NotDef, (Pointer)NULL, eFCMOVE, 0x0},
	//DA CB
	{FCMOVE, ST__0__, ST__11__, NotDef, (Pointer)NULL, eFCMOVE, 0x0},
	//DA CC
	{FCMOVE, ST__0__, ST__12__, NotDef, (Pointer)NULL, eFCMOVE, 0x0},
	//DA CD
	{FCMOVE, ST__0__, ST__13__, NotDef, (Pointer)NULL, eFCMOVE, 0x0},
	//DA CE
	{FCMOVE, ST__0__, ST__14__, NotDef, (Pointer)NULL, eFCMOVE, 0x0},
	//DA CF
	{FCMOVE, ST__0__, ST__15__, NotDef, (Pointer)NULL, eFCMOVE, 0x0},
	//DA D0
	{FCMOVBE, ST__0__, ST__0__, NotDef, (Pointer)NULL, eFCMOVBE, 0x0},
	//DA D1
	{FCMOVBE, ST__0__, ST__1__, NotDef, (Pointer)NULL, eFCMOVBE, 0x0},
	//DA D2
	{FCMOVBE, ST__0__, ST__2__, NotDef, (Pointer)NULL, eFCMOVBE, 0x0},
	//DA D3
	{FCMOVBE, ST__0__, ST__3__, NotDef, (Pointer)NULL, eFCMOVBE, 0x0},
	//DA D4
	{FCMOVBE, ST__0__, ST__4__, NotDef, (Pointer)NULL, eFCMOVBE, 0x0},
	//DA D5
	{FCMOVBE, ST__0__, ST__5__, NotDef, (Pointer)NULL, eFCMOVBE, 0x0},
	//DA D6
	{FCMOVBE, ST__0__, ST__6__, NotDef, (Pointer)NULL, eFCMOVBE, 0x0},
	//DA D7
	{FCMOVBE, ST__0__, ST__7__, NotDef, (Pointer)NULL, eFCMOVBE, 0x0},
	//DA D8
	{FCMOVU, ST__0__, ST__8__, NotDef, (Pointer)NULL, eFCMOVU, 0x0},
	//DA D9
	{FCMOVU, ST__0__, ST__9__, NotDef, (Pointer)NULL, eFCMOVU, 0x0},
	//DA DA
	{FCMOVU, ST__0__, ST__10__, NotDef, (Pointer)NULL, eFCMOVU, 0x0},
	//DA DB
	{FCMOVU, ST__0__, ST__11__, NotDef, (Pointer)NULL, eFCMOVU, 0x0},
	//DA DC
	{FCMOVU, ST__0__, ST__12__, NotDef, (Pointer)NULL, eFCMOVU, 0x0},
	//DA DD
	{FCMOVU, ST__0__, ST__13__, NotDef, (Pointer)NULL, eFCMOVU, 0x0},
	//DA DE
	{FCMOVU, ST__0__, ST__14__, NotDef, (Pointer)NULL, eFCMOVU, 0x0},
	//DA DF
	{FCMOVU, ST__0__, ST__15__, NotDef, (Pointer)NULL, eFCMOVU, 0x0},
	//DA E0
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA E1
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA E2
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA E3
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA E4
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA E5
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA E6
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA E7
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA E8
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA E9
	{FUCOMPP, NotDef, NotDef, NotDef, (Pointer)NULL, eFUCOMPP, 0x0},
	//DA EA
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA EB
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA EC
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA ED
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA EE
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA EF
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA F0
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA F1
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA F2
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA F3
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA F4
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA F5
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA F6
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA F7
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA F8
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA F9
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA FA
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA FB
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA FC
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA FD
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA FE
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA FF
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock arTable_DBExt [] = {
	//DB /0 
	{FILD, m32int, NotDef, NotDef, (Pointer)NULL, eFILD, 0x0},
	//DB /1
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB /2 
	{FIST, m32int, NotDef, NotDef, (Pointer)NULL, eFIST, 0x0},
	//DB /3 
	{FISTP, m32int, NotDef, NotDef, (Pointer)NULL, eFISTP, 0x0},
	//DB /4
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB /5 
	{FLD8, m80real, NotDef, NotDef, (Pointer)NULL, eFLD8, 0x0},
	//DB /6
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB /7 
	{FSTP8, m80real, NotDef, NotDef, (Pointer)NULL, eFSTP8, 0x0},
};

SMTableBlock arTable_DB_Abnormal [] = {
	//DB C0
	{FCMOVNB, ST__0__, ST__0__, NotDef, (Pointer)NULL, eFCMOVNB, 0x0},
	//DB C1
	{FCMOVNB, ST__0__, ST__1__, NotDef, (Pointer)NULL, eFCMOVNB, 0x0},
	//DB C2
	{FCMOVNB, ST__0__, ST__2__, NotDef, (Pointer)NULL, eFCMOVNB, 0x0},
	//DB C3
	{FCMOVNB, ST__0__, ST__3__, NotDef, (Pointer)NULL, eFCMOVNB, 0x0},
	//DB C4
	{FCMOVNB, ST__0__, ST__4__, NotDef, (Pointer)NULL, eFCMOVNB, 0x0},
	//DB C5
	{FCMOVNB, ST__0__, ST__5__, NotDef, (Pointer)NULL, eFCMOVNB, 0x0},
	//DB C6
	{FCMOVNB, ST__0__, ST__6__, NotDef, (Pointer)NULL, eFCMOVNB, 0x0},
	//DB C7
	{FCMOVNB, ST__0__, ST__7__, NotDef, (Pointer)NULL, eFCMOVNB, 0x0},
	//DB C8
	{FCMOVNE, ST__0__, ST__8__, NotDef, (Pointer)NULL, eFCMOVNE, 0x0},
	//DB C9
	{FCMOVNE, ST__0__, ST__9__, NotDef, (Pointer)NULL, eFCMOVNE, 0x0},
	//DB CA
	{FCMOVNE, ST__0__, ST__10__, NotDef, (Pointer)NULL, eFCMOVNE, 0x0},
	//DB CB
	{FCMOVNE, ST__0__, ST__11__, NotDef, (Pointer)NULL, eFCMOVNE, 0x0},
	//DB CC
	{FCMOVNE, ST__0__, ST__12__, NotDef, (Pointer)NULL, eFCMOVNE, 0x0},
	//DB CD
	{FCMOVNE, ST__0__, ST__13__, NotDef, (Pointer)NULL, eFCMOVNE, 0x0},
	//DB CE
	{FCMOVNE, ST__0__, ST__14__, NotDef, (Pointer)NULL, eFCMOVNE, 0x0},
	//DB CF
	{FCMOVNE, ST__0__, ST__15__, NotDef, (Pointer)NULL, eFCMOVNE, 0x0},
	//DB D0
	{FCMOVNBE, ST__0__, ST__0__, NotDef, (Pointer)NULL, eFCMOVNBE, 0x0},
	//DB D1
	{FCMOVNBE, ST__0__, ST__1__, NotDef, (Pointer)NULL, eFCMOVNBE, 0x0},
	//DB D2
	{FCMOVNBE, ST__0__, ST__2__, NotDef, (Pointer)NULL, eFCMOVNBE, 0x0},
	//DB D3
	{FCMOVNBE, ST__0__, ST__3__, NotDef, (Pointer)NULL, eFCMOVNBE, 0x0},
	//DB D4
	{FCMOVNBE, ST__0__, ST__4__, NotDef, (Pointer)NULL, eFCMOVNBE, 0x0},
	//DB D5
	{FCMOVNBE, ST__0__, ST__5__, NotDef, (Pointer)NULL, eFCMOVNBE, 0x0},
	//DB D6
	{FCMOVNBE, ST__0__, ST__6__, NotDef, (Pointer)NULL, eFCMOVNBE, 0x0},
	//DB D7
	{FCMOVNBE, ST__0__, ST__7__, NotDef, (Pointer)NULL, eFCMOVNBE, 0x0},
	//DB D8
	{FCMOVNU, ST__0__, ST__8__, NotDef, (Pointer)NULL, eFCMOVNU, 0x0},
	//DB D9
	{FCMOVNU, ST__0__, ST__9__, NotDef, (Pointer)NULL, eFCMOVNU, 0x0},
	//DB DA
	{FCMOVNU, ST__0__, ST__10__, NotDef, (Pointer)NULL, eFCMOVNU, 0x0},
	//DB DB
	{FCMOVNU, ST__0__, ST__11__, NotDef, (Pointer)NULL, eFCMOVNU, 0x0},
	//DB DC
	{FCMOVNU, ST__0__, ST__12__, NotDef, (Pointer)NULL, eFCMOVNU, 0x0},
	//DB DD
	{FCMOVNU, ST__0__, ST__13__, NotDef, (Pointer)NULL, eFCMOVNU, 0x0},
	//DB DE
	{FCMOVNU, ST__0__, ST__14__, NotDef, (Pointer)NULL, eFCMOVNU, 0x0},
	//DB DF
	{FCMOVNU, ST__0__, ST__15__, NotDef, (Pointer)NULL, eFCMOVNU, 0x0},
	//DB E0
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB E1
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB E2   
	{FNCLEX, NotDef, NotDef, NotDef, (Pointer)NULL, eFNCLEX, 0x0},
	//DB E3    
	{FNINIT, NotDef, NotDef, NotDef, (Pointer)NULL, eFNINIT, 0x0},
	//DB E4
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB E5
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB E6
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB E7
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB E8
	{FUCOMI, ST, ST__8__, NotDef, (Pointer)NULL, eFUCOMI, 0x0},
	//DB E9
	{FUCOMI, ST, ST__9__, NotDef, (Pointer)NULL, eFUCOMI, 0x0},
	//DB EA
	{FUCOMI, ST, ST__10__, NotDef, (Pointer)NULL, eFUCOMI, 0x0},
	//DB EB
	{FUCOMI, ST, ST__11__, NotDef, (Pointer)NULL, eFUCOMI, 0x0},
	//DB EC
	{FUCOMI, ST, ST__12__, NotDef, (Pointer)NULL, eFUCOMI, 0x0},
	//DB ED
	{FUCOMI, ST, ST__13__, NotDef, (Pointer)NULL, eFUCOMI, 0x0},
	//DB EE
	{FUCOMI, ST, ST__14__, NotDef, (Pointer)NULL, eFUCOMI, 0x0},
	//DB EF
	{FUCOMI, ST, ST__15__, NotDef, (Pointer)NULL, eFUCOMI, 0x0},
	//DB F0
	{FCOMI, ST, ST__0__, NotDef, (Pointer)NULL, eFCOMI, 0x0},
	//DB F1
	{FCOMI, ST, ST__1__, NotDef, (Pointer)NULL, eFCOMI, 0x0},
	//DB F2
	{FCOMI, ST, ST__2__, NotDef, (Pointer)NULL, eFCOMI, 0x0},
	//DB F3
	{FCOMI, ST, ST__3__, NotDef, (Pointer)NULL, eFCOMI, 0x0},
	//DB F4
	{FCOMI, ST, ST__4__, NotDef, (Pointer)NULL, eFCOMI, 0x0},
	//DB F5
	{FCOMI, ST, ST__5__, NotDef, (Pointer)NULL, eFCOMI, 0x0},
	//DB F6
	{FCOMI, ST, ST__6__, NotDef, (Pointer)NULL, eFCOMI, 0x0},
	//DB F7
	{FCOMI, ST, ST__7__, NotDef, (Pointer)NULL, eFCOMI, 0x0},
	//DB F8
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB F9
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB FA
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB FB
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB FC
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB FD
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB FE
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB FF
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock arTable_DCExt [] = {
	//DC /0    
	{FADD, m64real, NotDef, NotDef, (Pointer)NULL, eFADD, 0x0},
	//DC /1    
	{FMUL, m64real, NotDef, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//DC /2    
	{FCOM, m64real, NotDef, NotDef, (Pointer)NULL, eFCOM, 0x0},
	//DC /3    
	{FCOMP, m64real, NotDef, NotDef, (Pointer)NULL, eFCOMP, 0x0},
	//DC /4    
	{FSUB, m64real, NotDef, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//DC /5    
	{FSUBR, m64real, NotDef, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//DC /6    
	{FDIV, m64real, NotDef, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//DC /7    
	{FDIVR, m64real, NotDef, NotDef, (Pointer)NULL, eFDIVR, 0x0},
};

SMTableBlock arTable_DC_Abnormal [] = {
	//DC C0
	{FADD, ST__0__, ST__0__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//DC C1
	{FADD, ST__1__, ST__0__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//DC C2
	{FADD, ST__2__, ST__0__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//DC C3
	{FADD, ST__3__, ST__0__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//DC C4
	{FADD, ST__4__, ST__0__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//DC C5
	{FADD, ST__5__, ST__0__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//DC C6
	{FADD, ST__6__, ST__0__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//DC C7
	{FADD, ST__7__, ST__0__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//DC C8
	{FMUL, ST__8__, ST__0__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//DC C9
	{FMUL, ST__9__, ST__0__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//DC CA
	{FMUL, ST__10__, ST__0__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//DC CB
	{FMUL, ST__11__, ST__0__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//DC CC
	{FMUL, ST__12__, ST__0__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//DC CD
	{FMUL, ST__13__, ST__0__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//DC CE
	{FMUL, ST__14__, ST__0__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//DC CF
	{FMUL, ST__15__, ST__0__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//DC D0
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC D1
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC D2
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC D3
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC D4
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC D5
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC D6
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC D7
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC D8
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC D9
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC DA
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC DB
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC DC
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC DD
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC DE
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC DF
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC E0
	{FSUBR, ST__0__, ST__0__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//DC E1
	{FSUBR, ST__1__, ST__0__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//DC E2
	{FSUBR, ST__2__, ST__0__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//DC E3
	{FSUBR, ST__3__, ST__0__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//DC E4
	{FSUBR, ST__4__, ST__0__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//DC E5
	{FSUBR, ST__5__, ST__0__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//DC E6
	{FSUBR, ST__6__, ST__0__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//DC E7
	{FSUBR, ST__7__, ST__0__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//DC E8
	{FSUB, ST__8__, ST__0__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//DC E9
	{FSUB, ST__9__, ST__0__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//DC EA
	{FSUB, ST__10__, ST__0__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//DC EB
	{FSUB, ST__11__, ST__0__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//DC EC
	{FSUB, ST__12__, ST__0__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//DC ED
	{FSUB, ST__13__, ST__0__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//DC EE
	{FSUB, ST__14__, ST__0__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//DC EF
	{FSUB, ST__15__, ST__0__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//DC F0
	{FDIVR, ST__0__, ST__0__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
	//DC F1
	{FDIVR, ST__1__, ST__0__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
	//DC F2
	{FDIVR, ST__2__, ST__0__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
	//DC F3
	{FDIVR, ST__3__, ST__0__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
	//DC F4
	{FDIVR, ST__4__, ST__0__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
	//DC F5
	{FDIVR, ST__5__, ST__0__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
	//DC F6
	{FDIVR, ST__6__, ST__0__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
	//DC F7
	{FDIVR, ST__7__, ST__0__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
	//DC F8
	{FDIV, ST__8__, ST__0__, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//DC F9
	{FDIV, ST__9__, ST__0__, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//DC FA
	{FDIV, ST__10__, ST__0__, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//DC FB
	{FDIV, ST__11__, ST__0__, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//DC FC
	{FDIV, ST__12__, ST__0__, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//DC FD
	{FDIV, ST__13__, ST__0__, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//DC FE
	{FDIV, ST__14__, ST__0__, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//DC FF
	{FDIV, ST__15__, ST__0__, NotDef, (Pointer)NULL, eFDIV, 0x0},
};

SMTableBlock arTable_DDExt [] = {
	//DD /0    
	{FLD, m64real, NotDef, NotDef, (Pointer)NULL, eFLD, 0x0},
	//DD /1
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD /2    
	{FST, m64real, NotDef, NotDef, (Pointer)NULL, eFST, 0x0},
	//DD /3    
	{FSTP, m64real, NotDef, NotDef, (Pointer)NULL, eFSTP, 0x0},
	//DD /4    
	{FRSTOR, m94_Slash_108byte, NotDef, NotDef, (Pointer)NULL, eFRSTOR, 0x0},
	//DD /5
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD /6    
	{FNSAVE, m94_Slash_108byte, NotDef, NotDef, (Pointer)NULL, eFNSAVE, 0x0},
	//DD /7    
	{FNSTSW, m2byte, NotDef, NotDef, (Pointer)NULL, eFNSTSW, 0x0},
};

SMTableBlock arTable_DD_Abnormal [] = {
	//DD C0
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD C1
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD C2
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD C3
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD C4
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD C5
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD C6
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD C7
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD C8
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD C9
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD CA
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD CB
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD CC
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD CD
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD CE
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD CF
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD D0
	{FST, ST__0__, NotDef, NotDef, (Pointer)NULL, eFST, 0x0},
	//DD D1
	{FST, ST__1__, NotDef, NotDef, (Pointer)NULL, eFST, 0x0},
	//DD D2
	{FST, ST__2__, NotDef, NotDef, (Pointer)NULL, eFST, 0x0},
	//DD D3
	{FST, ST__3__, NotDef, NotDef, (Pointer)NULL, eFST, 0x0},
	//DD D4
	{FST, ST__4__, NotDef, NotDef, (Pointer)NULL, eFST, 0x0},
	//DD D5
	{FST, ST__5__, NotDef, NotDef, (Pointer)NULL, eFST, 0x0},
	//DD D6
	{FST, ST__6__, NotDef, NotDef, (Pointer)NULL, eFST, 0x0},
	//DD D7
	{FST, ST__7__, NotDef, NotDef, (Pointer)NULL, eFST, 0x0},
	//DD D8
	{FSTP, ST__8__, NotDef, NotDef, (Pointer)NULL, eFSTP, 0x0},
	//DD D9
	{FSTP, ST__9__, NotDef, NotDef, (Pointer)NULL, eFSTP, 0x0},
	//DD DA
	{FSTP, ST__10__, NotDef, NotDef, (Pointer)NULL, eFSTP, 0x0},
	//DD DB
	{FSTP, ST__11__, NotDef, NotDef, (Pointer)NULL, eFSTP, 0x0},
	//DD DC
	{FSTP, ST__12__, NotDef, NotDef, (Pointer)NULL, eFSTP, 0x0},
	//DD DD
	{FSTP, ST__13__, NotDef, NotDef, (Pointer)NULL, eFSTP, 0x0},
	//DD DE
	{FSTP, ST__14__, NotDef, NotDef, (Pointer)NULL, eFSTP, 0x0},
	//DD DF
	{FSTP, ST__15__, NotDef, NotDef, (Pointer)NULL, eFSTP, 0x0},
	//DD E0
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD E1    
	{FUCOM, NotDef, NotDef, NotDef, (Pointer)NULL, eFUCOM, 0x0},
	//DD E2
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD E3
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD E4
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD E5
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD E6
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD E7
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD E8
	{FUCOMP, ST__8__, NotDef, NotDef, (Pointer)NULL, eFUCOMP, 0x0},
	//DD E9
	{FUCOMP, ST__9__, NotDef, NotDef, (Pointer)NULL, eFUCOMP, 0x0},
	//DD EA
	{FUCOMP, ST__10__, NotDef, NotDef, (Pointer)NULL, eFUCOMP, 0x0},
	//DD EB
	{FUCOMP, ST__11__, NotDef, NotDef, (Pointer)NULL, eFUCOMP, 0x0},
	//DD EC
	{FUCOMP, ST__12__, NotDef, NotDef, (Pointer)NULL, eFUCOMP, 0x0},
	//DD ED
	{FUCOMP, ST__13__, NotDef, NotDef, (Pointer)NULL, eFUCOMP, 0x0},
	//DD EE
	{FUCOMP, ST__14__, NotDef, NotDef, (Pointer)NULL, eFUCOMP, 0x0},
	//DD EF
	{FUCOMP, ST__15__, NotDef, NotDef, (Pointer)NULL, eFUCOMP, 0x0},
	//DD F0
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD F1
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD F2
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD F3
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD F4
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD F5
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD F6
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD F7
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD F8
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD F9
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD FA
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD FB
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD FC
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD FD
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD FE
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD FF
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock arTable_DEExt [] = {
	//DE /0    
	{FIADD, m16int, NotDef, NotDef, (Pointer)NULL, eFIADD, 0x0},
	//DE /1    
	{FIMUL, m16int, NotDef, NotDef, (Pointer)NULL, eFIMUL, 0x0},
	//DE /2    
	{FICOM, m16int, NotDef, NotDef, (Pointer)NULL, eFICOM, 0x0},
	//DE /3    
	{FICOMP, m16int, NotDef, NotDef, (Pointer)NULL, eFICOMP, 0x0},
	//DE /4    
	{FISUB, m16int, NotDef, NotDef, (Pointer)NULL, eFISUB, 0x0},
	//DE /5    
	{FISUBR, m16int, NotDef, NotDef, (Pointer)NULL, eFISUBR, 0x0},
	//DE /6    
	{FIDIV, m16int, NotDef, NotDef, (Pointer)NULL, eFIDIV, 0x0},
	//DE /7    
	{FIDIVR, m16int, NotDef, NotDef, (Pointer)NULL, eFIDIVR, 0x0},
};

SMTableBlock arTable_DE_Abnormal [] = {
	//DE C0
	{FADDP, ST__0__, ST__0__, NotDef, (Pointer)NULL, eFADDP, 0x0},
	//DE C1
	{FADDP, ST__1__, ST__0__, NotDef, (Pointer)NULL, eFADDP, 0x0},
	//DE C2
	{FADDP, ST__2__, ST__0__, NotDef, (Pointer)NULL, eFADDP, 0x0},
	//DE C3
	{FADDP, ST__3__, ST__0__, NotDef, (Pointer)NULL, eFADDP, 0x0},
	//DE C4
	{FADDP, ST__4__, ST__0__, NotDef, (Pointer)NULL, eFADDP, 0x0},
	//DE C5
	{FADDP, ST__5__, ST__0__, NotDef, (Pointer)NULL, eFADDP, 0x0},
	//DE C6
	{FADDP, ST__6__, ST__0__, NotDef, (Pointer)NULL, eFADDP, 0x0},
	//DE C7
	{FADDP, ST__7__, ST__0__, NotDef, (Pointer)NULL, eFADDP, 0x0},
	//DE C8
	{FMULP, ST__8__, ST__0__, NotDef, (Pointer)NULL, eFMULP, 0x0},
	//DE C9
	{FMULP, ST__9__, ST__0__, NotDef, (Pointer)NULL, eFMULP, 0x0},
	//DE CA
	{FMULP, ST__10__, ST__0__, NotDef, (Pointer)NULL, eFMULP, 0x0},
	//DE CB
	{FMULP, ST__11__, ST__0__, NotDef, (Pointer)NULL, eFMULP, 0x0},
	//DE CC
	{FMULP, ST__12__, ST__0__, NotDef, (Pointer)NULL, eFMULP, 0x0},
	//DE CD
	{FMULP, ST__13__, ST__0__, NotDef, (Pointer)NULL, eFMULP, 0x0},
	//DE CE
	{FMULP, ST__14__, ST__0__, NotDef, (Pointer)NULL, eFMULP, 0x0},
	//DE CF
	{FMULP, ST__15__, ST__0__, NotDef, (Pointer)NULL, eFMULP, 0x0},
	//DE D0
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE D1
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE D2
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE D3
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE D4
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE D5
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE D6
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE D7
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE D8
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE D9    
	{FCOMPP, NotDef, NotDef, NotDef, (Pointer)NULL, eFCOMPP, 0x0},
	//DE DA
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE DB
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE DC
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE DD
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE DE
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE DF
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE E0
	{FSUBRP, ST__0__, ST__0__, NotDef, (Pointer)NULL, eFSUBRP, 0x0},
	//DE E1
	{FSUBRP, ST__1__, ST__0__, NotDef, (Pointer)NULL, eFSUBRP, 0x0},
	//DE E2
	{FSUBRP, ST__2__, ST__0__, NotDef, (Pointer)NULL, eFSUBRP, 0x0},
	//DE E3
	{FSUBRP, ST__3__, ST__0__, NotDef, (Pointer)NULL, eFSUBRP, 0x0},
	//DE E4
	{FSUBRP, ST__4__, ST__0__, NotDef, (Pointer)NULL, eFSUBRP, 0x0},
	//DE E5
	{FSUBRP, ST__5__, ST__0__, NotDef, (Pointer)NULL, eFSUBRP, 0x0},
	//DE E6
	{FSUBRP, ST__6__, ST__0__, NotDef, (Pointer)NULL, eFSUBRP, 0x0},
	//DE E7
	{FSUBRP, ST__7__, ST__0__, NotDef, (Pointer)NULL, eFSUBRP, 0x0},
	//DE E8
	{FSUBP, ST__8__, ST__0__, NotDef, (Pointer)NULL, eFSUBP, 0x0},
	//DE E9
	{FSUBP, ST__9__, ST__0__, NotDef, (Pointer)NULL, eFSUBP, 0x0},
	//DE EA
	{FSUBP, ST__10__, ST__0__, NotDef, (Pointer)NULL, eFSUBP, 0x0},
	//DE EB
	{FSUBP, ST__11__, ST__0__, NotDef, (Pointer)NULL, eFSUBP, 0x0},
	//DE EC
	{FSUBP, ST__12__, ST__0__, NotDef, (Pointer)NULL, eFSUBP, 0x0},
	//DE ED
	{FSUBP, ST__13__, ST__0__, NotDef, (Pointer)NULL, eFSUBP, 0x0},
	//DE EE
	{FSUBP, ST__14__, ST__0__, NotDef, (Pointer)NULL, eFSUBP, 0x0},
	//DE EF
	{FSUBP, ST__15__, ST__0__, NotDef, (Pointer)NULL, eFSUBP, 0x0},
	//DE F0
	{FDIVRP, ST__0__, ST__0__, NotDef, (Pointer)NULL, eFDIVRP, 0x0},
	//DE F1
	{FDIVRP, ST__1__, ST__0__, NotDef, (Pointer)NULL, eFDIVRP, 0x0},
	//DE F2
	{FDIVRP, ST__2__, ST__0__, NotDef, (Pointer)NULL, eFDIVRP, 0x0},
	//DE F3
	{FDIVRP, ST__3__, ST__0__, NotDef, (Pointer)NULL, eFDIVRP, 0x0},
	//DE F4
	{FDIVRP, ST__4__, ST__0__, NotDef, (Pointer)NULL, eFDIVRP, 0x0},
	//DE F5
	{FDIVRP, ST__5__, ST__0__, NotDef, (Pointer)NULL, eFDIVRP, 0x0},
	//DE F6
	{FDIVRP, ST__6__, ST__0__, NotDef, (Pointer)NULL, eFDIVRP, 0x0},
	//DE F7
	{FDIVRP, ST__7__, ST__0__, NotDef, (Pointer)NULL, eFDIVRP, 0x0},
	//DE F8
	{FDIVP, ST__8__, ST__0__, NotDef, (Pointer)NULL, eFDIVP, 0x0},
	//DE F9
	{FDIVP, ST__9__, ST__0__, NotDef, (Pointer)NULL, eFDIVP, 0x0},
	//DE FA
	{FDIVP, ST__10__, ST__0__, NotDef, (Pointer)NULL, eFDIVP, 0x0},
	//DE FB
	{FDIVP, ST__11__, ST__0__, NotDef, (Pointer)NULL, eFDIVP, 0x0},
	//DE FC
	{FDIVP, ST__12__, ST__0__, NotDef, (Pointer)NULL, eFDIVP, 0x0},
	//DE FD
	{FDIVP, ST__13__, ST__0__, NotDef, (Pointer)NULL, eFDIVP, 0x0},
	//DE FE
	{FDIVP, ST__14__, ST__0__, NotDef, (Pointer)NULL, eFDIVP, 0x0},
	//DE FF
	{FDIVP, ST__15__, ST__0__, NotDef, (Pointer)NULL, eFDIVP, 0x0},
};

SMTableBlock arTable_DFExt [] = {
	//DF /0    
	{FILD, m16int, NotDef, NotDef, (Pointer)NULL, eFILD, 0x0},
	//DF /1
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF /2    
	{FIST, m16int, NotDef, NotDef, (Pointer)NULL, eFIST, 0x0},
	//DF /3    
	{FISTP, m16int, NotDef, NotDef, (Pointer)NULL, eFISTP, 0x0},
	//DF /4    
	{FBLD8, m80dec, NotDef, NotDef, (Pointer)NULL, eFBLD8, 0x0},
	//DF /5    
	{FILD, m64int, NotDef, NotDef, (Pointer)NULL, eFILD, 0x0},
	//DF /6    
	{FBSTP8, m80bcd, NotDef, NotDef, (Pointer)NULL, eFBSTP8, 0x0},
	//DF /7    
	{FISTP, m64int, NotDef, NotDef, (Pointer)NULL, eFISTP, 0x0},
};

SMTableBlock arTable_DF_Abnormal [] = {
	//DF C0
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF C1
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF C2
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF C3
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF C4
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF C5
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF C6
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF C7
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF C8
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF C9
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF CA
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF CB
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF CC
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF CD
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF CE
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF CF
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF D0
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF D1
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF D2
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF D3
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF D4
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF D5
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF D6
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF D7
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF D8
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF D9
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF DA
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF DB
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF DC
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF DD
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF DE
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF DF
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF E0    
	{FNSTSW, AX, NotDef, NotDef, (Pointer)NULL, eFNSTSW, 0x0},
	//DF E1
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF E2
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF E3
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF E4
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF E5
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF E6
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF E7
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF E8
	{FUCOMIP, ST, ST__8__, NotDef, (Pointer)NULL, eFUCOMIP, 0x0},
	//DF E9
	{FUCOMIP, ST, ST__9__, NotDef, (Pointer)NULL, eFUCOMIP, 0x0},
	//DF EA
	{FUCOMIP, ST, ST__10__, NotDef, (Pointer)NULL, eFUCOMIP, 0x0},
	//DF EB
	{FUCOMIP, ST, ST__11__, NotDef, (Pointer)NULL, eFUCOMIP, 0x0},
	//DF EC
	{FUCOMIP, ST, ST__12__, NotDef, (Pointer)NULL, eFUCOMIP, 0x0},
	//DF ED
	{FUCOMIP, ST, ST__13__, NotDef, (Pointer)NULL, eFUCOMIP, 0x0},
	//DF EE
	{FUCOMIP, ST, ST__14__, NotDef, (Pointer)NULL, eFUCOMIP, 0x0},
	//DF EF
	{FUCOMIP, ST, ST__15__, NotDef, (Pointer)NULL, eFUCOMIP, 0x0},
	//DF F0
	{FCOMIP, ST, ST__0__, NotDef, (Pointer)NULL, eFCOMIP, 0x0},
	//DF F1
	{FCOMIP, ST, ST__1__, NotDef, (Pointer)NULL, eFCOMIP, 0x0},
	//DF F2
	{FCOMIP, ST, ST__2__, NotDef, (Pointer)NULL, eFCOMIP, 0x0},
	//DF F3
	{FCOMIP, ST, ST__3__, NotDef, (Pointer)NULL, eFCOMIP, 0x0},
	//DF F4
	{FCOMIP, ST, ST__4__, NotDef, (Pointer)NULL, eFCOMIP, 0x0},
	//DF F5
	{FCOMIP, ST, ST__5__, NotDef, (Pointer)NULL, eFCOMIP, 0x0},
	//DF F6
	{FCOMIP, ST, ST__6__, NotDef, (Pointer)NULL, eFCOMIP, 0x0},
	//DF F7
	{FCOMIP, ST, ST__7__, NotDef, (Pointer)NULL, eFCOMIP, 0x0},
	//DF F8
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF F9
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF FA
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF FB
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF FC
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF FD
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF FE
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF FF
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock arTable_F6Ext [] = {
	//F6 /0 ib
	{TEST8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eTEST8, 0x2},
	//F6 /1
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//F6 /2  
	{NOT8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eNOT8, 0xA},
	//F6 /3  
	{NEG8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eNEG8, 0xA},
	//F6 /4  
	{MUL8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eMUL8, 0x2},
	//F6 /5  
	{IMUL8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eIMUL8, 0x2},
	//F6 /6  
	{DIV8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eDIV8, 0x2},
	//F6 /7  
	{IDIV8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eIDIV8, 0x2},
};

SMTableBlock arTable_F7Ext [] = {
	//F7 /0 id
	{TEST, r_Slash_m32, imm32, NotDef, TEST16, eTEST, 0x3},
	//F7 /1
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//F7 /2  
	{NOT, r_Slash_m32, NotDef, NotDef, NOT16, eNOT, 0xB},
	//F7 /3  
	{NEG, r_Slash_m32, NotDef, NotDef, NEG16, eNEG, 0xB},
	//F7 /4  
	{MUL, r_Slash_m32, NotDef, NotDef, MUL16, eMUL, 0x3},
	//F7 /5  
	{IMUL, r_Slash_m32, NotDef, NotDef, IMUL16, eIMUL, 0x3},
	//F7 /6  
	{DIV, r_Slash_m32, NotDef, NotDef, DIV16, eDIV, 0x3},
	//F7 /7  
	{IDIV, r_Slash_m32, NotDef, NotDef, IDIV16, eIDIV, 0x3},
};

SMTableBlock arTable_FEExt [] = {
	//FE /0  
	{INC8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eINC8, 0xA},
	//FE /1  
	{DEC8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eDEC8, 0xA},
	//FE /2
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//FE /3
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//FE /4
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//FE /5
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//FE /6
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//FE /7
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock arTable_FFExt [] = {
	//FF /0  
	{INC, r_Slash_m32, NotDef, NotDef, INC16, eINC, 0xB},
	//FF /1  
	{DEC, r_Slash_m32, NotDef, NotDef, DEC16, eDEC, 0xB},
	//FF /2  
	{CALL, r_Slash_m32, NotDef, NotDef, CALL16, eCALL, 0x3},
	//FF /3  
	{CALL, m16_Colon_32, NotDef, NotDef, CALL16, eCALL, 0x2},
	//FF /4  
	{JMP, r_Slash_m32, NotDef, NotDef, JMP16, eJMP, 0x3},
	//FF /5  
	{JMP, m16_Colon_32, NotDef, NotDef, JMP16, eJMP, 0x2},
	//FF /6  
	{PUSH, r_Slash_m32, NotDef, NotDef, PUSH16, ePUSH, 0x3},
	//FF /7
	{NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock *poarTableList[] = 
{	arTable_Base,
	arTable_0F,
	arTable_0F00Ext,
	arTable_0F01Ext,
	arTable_0F18Ext,
	arTable_0F71Ext,
	arTable_0F72Ext,
	arTable_0F73Ext,
	arTable_0FAEExt,
	arTable_0FBAExt,
	arTable_0FC7Ext,
	arTable_80Ext,
	arTable_81Ext,
	arTable_83Ext,
	arTable_8FExt,
	arTable_C0Ext,
	arTable_C1Ext,
	arTable_C6Ext,
	arTable_C7Ext,
	arTable_D0Ext,
	arTable_D1Ext,
	arTable_D2Ext,
	arTable_D3Ext,
	arTable_D8Ext,
	arTable_D8_Abnormal,
	arTable_D9Ext,
	arTable_D9_Abnormal,
	arTable_DAExt,
	arTable_DA_Abnormal,
	arTable_DBExt,
	arTable_DB_Abnormal,
	arTable_DCExt,
	arTable_DC_Abnormal,
	arTable_DDExt,
	arTable_DD_Abnormal,
	arTable_DEExt,
	arTable_DE_Abnormal,
	arTable_DFExt,
	arTable_DF_Abnormal,
	arTable_F6Ext,
	arTable_F7Ext,
	arTable_FEExt,
	arTable_FFExt,
};
#pragma pack (pop)
#endif
