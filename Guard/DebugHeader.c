
#include "OperationsFunctions.h"
#if _DEBUG
#include "All_Defines.h"
#pragma pack (push, 1)

// All Opcode table with reference are in 'arTable_Base' table
SMTableBlock arTable_Base [] = {
	//00 /r
	{L"ADD",ADD8, r_Slash_m8, r8, NotDef, (Pointer)NULL, eADD8, 0xA},
	//01 /r
	{L"ADD",ADD, r_Slash_m32, r32, NotDef, ADD16, eADD, 0xB},
	//02 /r
	{L"ADD",ADD8, r8, r_Slash_m8, NotDef, (Pointer)NULL, eADD8, 0xA},
	//03 /r
	{L"ADD",ADD, r32, r_Slash_m32, NotDef, ADD16, eADD, 0xB},
	//04 ib
	{L"ADD",ADD8, AL, imm8, NotDef, (Pointer)NULL, eADD8, 0x8},
	//05 id
	{L"ADD",ADD, EAX, imm32, NotDef, ADD16, eADD, 0x9},
	//06 
	{L"PUSH",PUSH, ES, NotDef, NotDef, (Pointer)NULL, ePUSH, 0x0},
	//07
	{L"POP",POP, ES, NotDef, NotDef, (Pointer)NULL, ePOP, 0x0},
	//08 /r
	{L"OR",OR8, r_Slash_m8, r8, NotDef, (Pointer)NULL, eOR8, 0xA},
	//09 /r
	{L"OR",OR, r_Slash_m32, r32, NotDef, OR16, eOR, 0xB},
	//0A /r
	{L"OR",OR8, r8, r_Slash_m8, NotDef, (Pointer)NULL, eOR8, 0xA},
	//0B /r
	{L"OR",OR, r32, r_Slash_m32, NotDef, OR16, eOR, 0xB},
	//0C ib
	{L"OR",OR8, AL, imm8, NotDef, (Pointer)NULL, eOR8, 0x8},
	//0D id
	{L"OR",OR, EAX, imm32, NotDef, OR16, eOR, 0x9},
	//0E 
	{L"PUSH",PUSH, CS, NotDef, NotDef, (Pointer)NULL, ePUSH, 0x0},
	//0F 00
	{L"(Pointer)0xF0001100",(Pointer)0xF0001100, r_Slash_m32, NotDef, NotDef, (Pointer)NULL, Ins, 0x3},
	//10 /r
	{L"ADC",ADC8, r_Slash_m8, r8, NotDef, (Pointer)NULL, eADC8, 0xA},
	//11 /r
	{L"ADC",ADC, r_Slash_m32, r32, NotDef, ADC16, eADC, 0xB},
	//12 /r
	{L"ADC",ADC8, r8, r_Slash_m8, NotDef, (Pointer)NULL, eADC8, 0xA},
	//13 /r 
	{L"ADC",ADC, r32, r_Slash_m32, NotDef, ADC16, eADC, 0xB},
	//14 ib
	{L"ADC",ADC8, AL, imm8, NotDef, (Pointer)NULL, eADC8, 0x8},
	//15 id
	{L"ADC",ADC, EAX, imm32, NotDef, ADC16, eADC, 0x9},
	//16 
	{L"PUSH",PUSH, SS, NotDef, NotDef, (Pointer)NULL, ePUSH, 0x0},
	//17
	{L"POP",POP, SS, NotDef, NotDef, (Pointer)NULL, ePOP, 0x0},
	//18 /r
	{L"SBB",SBB8, r_Slash_m8, r8, NotDef, (Pointer)NULL, eSBB8, 0xA},
	//19 /r
	{L"SBB",SBB, r_Slash_m32, r32, NotDef, SBB16, eSBB, 0xB},
	//1A /r
	{L"SBB",SBB8, r8, r_Slash_m8, NotDef, (Pointer)NULL, eSBB8, 0xA},
	//1B /r
	{L"SBB",SBB, r32, r_Slash_m32, NotDef, SBB16, eSBB, 0xB},
	//1C ib
	{L"SBB",SBB8, AL, imm8, NotDef, (Pointer)NULL, eSBB8, 0x8},
	//1D id
	{L"SBB",SBB, EAX, imm32, NotDef, SBB16, eSBB, 0x9},
	//1E 
	{L"PUSH",PUSH, DS, NotDef, NotDef, (Pointer)NULL, ePUSH, 0x0},
	//1F
	{L"POP",POP, DS, NotDef, NotDef, (Pointer)NULL, ePOP, 0x0},
	//20 /r
	{L"AND",AND8, r_Slash_m8, r8, NotDef, (Pointer)NULL, eAND8, 0xA},
	//21 /r 
	{L"AND",AND, r_Slash_m32, r32, NotDef, AND16, eAND, 0xB},
	//22 /r 
	{L"AND",AND8, r8, r_Slash_m8, NotDef, (Pointer)NULL, eAND8, 0xA},
	//23 /r 
	{L"AND",AND, r32, r_Slash_m32, NotDef, AND16, eAND, 0xB},
	//24 ib 
	{L"AND",AND8, AL, imm8, NotDef, (Pointer)NULL, eAND8, 0x8},
	//25 id 
	{L"AND",AND, EAX, imm32, NotDef, AND16, eAND, 0x9},
	//26 ES
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//27
	{L"DAA",DAA, NotDef, NotDef, NotDef, (Pointer)NULL, eDAA, 0x0},
	//28 /r
	{L"SUB",SUB8, r_Slash_m8, r8, NotDef, (Pointer)NULL, eSUB8, 0xA},
	//29 /r 
	{L"SUB",SUB, r_Slash_m32, r32, NotDef, SUB16, eSUB, 0xB},
	//2A /r 
	{L"SUB",SUB8, r8, r_Slash_m8, NotDef, (Pointer)NULL, eSUB8, 0xA},
	//2B /r 
	{L"SUB",SUB, r32, r_Slash_m32, NotDef, SUB16, eSUB, 0xB},
	//2C ib 
	{L"SUB",SUB8, AL, imm8, NotDef, (Pointer)NULL, eSUB8, 0x8},
	//2D id 
	{L"SUB",SUB, EAX, imm32, NotDef, SUB16, eSUB, 0x9},
	//2E CS
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//2F
	{L"DAS",DAS, NotDef, NotDef, NotDef, (Pointer)NULL, eDAS, 0x0},
	//30 /r
	{L"XOR",XOR8, r_Slash_m8, r8, NotDef, (Pointer)NULL, eXOR8, 0xB},
	//31 /r
	{L"XOR",XOR, r_Slash_m32, r32, NotDef, XOR16, eXOR, 0xB},
	//32 /r 
	{L"XOR",XOR8, r8, r_Slash_m8, NotDef, (Pointer)NULL, eXOR8, 0xB},
	//33 /r 
	{L"XOR",XOR, r32, r_Slash_m32, NotDef, XOR16, eXOR, 0xB},
	//34 ib 
	{L"XOR",XOR8, AL, imm8, NotDef, (Pointer)NULL, eXOR8, 0x8},
	//35 id 
	{L"XOR",XOR, EAX, imm32, NotDef, XOR16, eXOR, 0x9},
	//36 SS
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//37
	{L"AAA",AAA, NotDef, NotDef, NotDef, (Pointer)NULL, eAAA, 0x0},
	//38 /r
	{L"CMP",CMP8, r_Slash_m8, r8, NotDef, (Pointer)NULL, eCMP8, 0x2},
	//39 /r 
	{L"CMP",CMP, r_Slash_m32, r32, NotDef, CMP16, eCMP, 0x3},
	//3A /r 
	{L"CMP",CMP8, r8, r_Slash_m8, NotDef, (Pointer)NULL, eCMP8, 0x2},
	//3B /r 
	{L"CMP",CMP, r32, r_Slash_m32, NotDef, CMP16, eCMP, 0x3},
	//3C ib 
	{L"CMP",CMP8, AL, imm8, NotDef, (Pointer)NULL, eCMP8, 0x0},
	//3D id 
	{L"CMP",CMP, EAX, imm32, NotDef, CMP16, eCMP, 0x1},
	//3E DS
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//3F
	{L"AAS",AAS, NotDef, NotDef, NotDef, (Pointer)NULL, eAAS, 0x0},
	//40
	{L"INC",INC, EAX, NotDef, NotDef, INC16, eINC, 0x9},
	//41
	{L"INC",INC, ECX, NotDef, NotDef, INC16, eINC, 0x9},
	//42
	{L"INC",INC, EDX, NotDef, NotDef, INC16, eINC, 0x9},
	//43
	{L"INC",INC, EBX, NotDef, NotDef, INC16, eINC, 0x9},
	//44
	{L"INC",INC, ESP, NotDef, NotDef, INC16, eINC, 0x9},
	//45
	{L"INC",INC, EBP, NotDef, NotDef, INC16, eINC, 0x9},
	//46
	{L"INC",INC, ESI, NotDef, NotDef, INC16, eINC, 0x9},
	//47
	{L"INC",INC, EDI, NotDef, NotDef, INC16, eINC, 0x9},
	//48
	{L"DEC",DEC, EAX, NotDef, NotDef, DEC16, eDEC, 0x9},
	//49
	{L"DEC",DEC, ECX, NotDef, NotDef, DEC16, eDEC, 0x9},
	//4A
	{L"DEC",DEC, EDX, NotDef, NotDef, DEC16, eDEC, 0x9},
	//4B
	{L"DEC",DEC, EBX, NotDef, NotDef, DEC16, eDEC, 0x9},
	//4C
	{L"DEC",DEC, ESP, NotDef, NotDef, DEC16, eDEC, 0x9},
	//4D
	{L"DEC",DEC, EBP, NotDef, NotDef, DEC16, eDEC, 0x9},
	//4E
	{L"DEC",DEC, ESI, NotDef, NotDef, DEC16, eDEC, 0x9},
	//4F
	{L"DEC",DEC, EDI, NotDef, NotDef, DEC16, eDEC, 0x9},
	//50
	{L"PUSH",PUSH, EAX, NotDef, NotDef, PUSH16, ePUSH, 0x1},
	//51
	{L"PUSH",PUSH, ECX, NotDef, NotDef, PUSH16, ePUSH, 0x1},
	//52
	{L"PUSH",PUSH, EDX, NotDef, NotDef, PUSH16, ePUSH, 0x1},
	//53
	{L"PUSH",PUSH, EBX, NotDef, NotDef, PUSH16, ePUSH, 0x1},
	//54
	{L"PUSH",PUSH, ESP, NotDef, NotDef, PUSH16, ePUSH, 0x1},
	//55
	{L"PUSH",PUSH, EBP, NotDef, NotDef, PUSH16, ePUSH, 0x1},
	//56
	{L"PUSH",PUSH, ESI, NotDef, NotDef, PUSH16, ePUSH, 0x1},
	//57
	{L"PUSH",PUSH, EDI, NotDef, NotDef, PUSH16, ePUSH, 0x1},
	//58
	{L"POP",POP, EAX, NotDef, NotDef, POP16, ePOP, 0x1},
	//59
	{L"POP",POP, ECX, NotDef, NotDef, POP16, ePOP, 0x1},
	//5A
	{L"POP",POP, EDX, NotDef, NotDef, POP16, ePOP, 0x1},
	//5B
	{L"POP",POP, EBX, NotDef, NotDef, POP16, ePOP, 0x1},
	//5C
	{L"POP",POP, ESP, NotDef, NotDef, POP16, ePOP, 0x1},
	//5D
	{L"POP",POP, EBP, NotDef, NotDef, POP16, ePOP, 0x1},
	//5E
	{L"POP",POP, ESI, NotDef, NotDef, POP16, ePOP, 0x1},
	//5F
	{L"POP",POP, EDI, NotDef, NotDef, POP16, ePOP, 0x1},
	//60  
	{L"PUSHAD",PUSHAD, NotDef, NotDef, NotDef, PUSHAD16, ePUSHAD, 0x1},
	//61  
	{L"POPAD",POPAD, NotDef, NotDef, NotDef, POPAD16, ePOPAD, 0x1},
	//62 /r  
	{L"BOUND",BOUND, r32, m32_Amp_32, NotDef, (Pointer)NULL, eBOUND, 0x0},
	//63 /r
	{L"ARPL",ARPL, r_Slash_m16, r16, NotDef, ARPL16, eARPL, 0x3},
	//64 FS
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//65 GS
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//66
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//67
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//68 
	{L"PUSH",PUSH, imm32, NotDef, NotDef, (Pointer)NULL, ePUSH, 0x0},
	//69 /r id
	{L"IMUL",IMUL, r32, r_Slash_m32, imm32, IMUL16, eIMUL, 0x1},
	//6A 
	{L"PUSH",PUSH8, imm8, NotDef, NotDef, (Pointer)NULL, ePUSH8, 0x0},
	//6B /r ib
	{L"IMUL",IMUL, r32, r_Slash_m32, imm8, IMUL16, eIMUL, 0x3},
	//6C 
	{L"INSB",INSB, NotDef, NotDef, NotDef, (Pointer)NULL, eINSB, 0x4},
	//6D 
	{L"INSD",INSD, NotDef, NotDef, NotDef, (Pointer)NULL, eINSD, 0x4},
	//6E  
	{L"OUTSB",OUTSB, NotDef, NotDef, NotDef, (Pointer)NULL, eOUTSB, 0x4},
	//6F  
	{L"OUTSD",OUTSD, NotDef, NotDef, NotDef, (Pointer)NULL, eOUTSD, 0x4},
	//70 cb   
	{L"JO",JO, rel8, NotDef, NotDef, (Pointer)NULL, eJO, 0x0},
	//71 cb    
	{L"JNO",JNO, rel8, NotDef, NotDef, (Pointer)NULL, eJNO, 0x0},
	//72 cb    
	{L"JB",JB, rel8, NotDef, NotDef, (Pointer)NULL, eJB, 0x0},
	//73 cb    
	{L"JNB",JNB, rel8, NotDef, NotDef, (Pointer)NULL, eJNB, 0x0},
	//74 cb    
	{L"JZ",JZ, rel8, NotDef, NotDef, (Pointer)NULL, eJZ, 0x0},
	//75 cb    
	{L"JNZ",JNZ, rel8, NotDef, NotDef, (Pointer)NULL, eJNZ, 0x0},
	//76 cb    
	{L"JNA",JNA, rel8, NotDef, NotDef, (Pointer)NULL, eJNA, 0x0},
	//77 cb    
	{L"JNBE",JNBE, rel8, NotDef, NotDef, (Pointer)NULL, eJNBE, 0x0},
	//78 cb    
	{L"JS",JS, rel8, NotDef, NotDef, (Pointer)NULL, eJS, 0x0},
	//79 cb    
	{L"JNS",JNS, rel8, NotDef, NotDef, (Pointer)NULL, eJNS, 0x0},
	//7A cb    
	{L"JPE",JPE, rel8, NotDef, NotDef, (Pointer)NULL, eJPE, 0x0},
	//7B cb    
	{L"JPO",JPO, rel8, NotDef, NotDef, (Pointer)NULL, eJPO, 0x0},
	//7C cb    
	{L"JNGE",JNGE, rel8, NotDef, NotDef, (Pointer)NULL, eJNGE, 0x0},
	//7D cb    
	{L"JNL",JNL, rel8, NotDef, NotDef, (Pointer)NULL, eJNL, 0x0},
	//7E cb    
	{L"JNG",JNG, rel8, NotDef, NotDef, (Pointer)NULL, eJNG, 0x0},
	//7F cb    
	{L"JNLE",JNLE, rel8, NotDef, NotDef, (Pointer)NULL, eJNLE, 0x0},
	//80 /0 ib
	{L"(Pointer)0xF000030B",(Pointer)0xF000030B, r_Slash_m8, imm8, NotDef, (Pointer)NULL, Ins, 0xA},
	//81 /0 id
	{L"(Pointer)0xF000030C",(Pointer)0xF000030C, r_Slash_m32, imm32, NotDef, (Pointer)NULL, Ins, 0xB},
	//82
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//83 /0 ib
	{L"(Pointer)0xF000030D",(Pointer)0xF000030D, r_Slash_m32, imm8, NotDef, (Pointer)NULL, Ins, 0xB},
	//84 /r
	{L"TEST",TEST8, r_Slash_m8, r8, NotDef, (Pointer)NULL, eTEST8, 0x2},
	//85 /r 
	{L"TEST",TEST, r_Slash_m32, r32, NotDef, TEST16, eTEST, 0x3},
	//86 /r 
	{L"XCHG",XCHG8, r8, r_Slash_m8, NotDef, (Pointer)NULL, eXCHG8, 0xA},
	//87 /r 
	{L"XCHG",XCHG, r32, r_Slash_m32, NotDef, XCHG16, eXCHG, 0xB},
	//88 /r
	{L"MOV",MOV8, r_Slash_m8, r8, NotDef, (Pointer)NULL, eMOV8, 0x3},
	//89 /r 
	{L"MOV",MOV, r_Slash_m32, r32, NotDef, MOV16, eMOV, 0x3},
	//8A /r 
	{L"MOV",MOV8, r8, r_Slash_m8, NotDef, (Pointer)NULL, eMOV8, 0x3},
	//8B /r 
	{L"MOV",MOV, r32, r_Slash_m32, NotDef, MOV16, eMOV, 0x3},
	//8C /r
	{L"MOV",MOV, r_Slash_m16, Sreg, NotDef, MOV16, eMOV, 0x3},
	//8D /r
	{L"LEA",LEA, r32, LEA32, NotDef, (Pointer)NULL, eLEA, 0x3},
	//8E /r 
	{L"MOV",MOV, Sreg, r_Slash_m16, NotDef, MOV16, eMOV, 0x3},
	//8F /0
	{L"(Pointer)0xF000030E",(Pointer)0xF000030E, m32, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//90 
	{L"NOP",NOP, NotDef, NotDef, NotDef, (Pointer)NULL, eNOP, 0x0},
	//91
	{L"XCHG",XCHG, EAX, ECX, NotDef, XCHG16, eXCHG, 0x9},
	//92
	{L"XCHG",XCHG, EAX, EDX, NotDef, XCHG16, eXCHG, 0x9},
	//93
	{L"XCHG",XCHG, EAX, EBX, NotDef, XCHG16, eXCHG, 0x9},
	//94
	{L"XCHG",XCHG, EAX, ESP, NotDef, XCHG16, eXCHG, 0x9},
	//95
	{L"XCHG",XCHG, EAX, EBP, NotDef, XCHG16, eXCHG, 0x9},
	//96
	{L"XCHG",XCHG, EAX, ESI, NotDef, XCHG16, eXCHG, 0x9},
	//97
	{L"XCHG",XCHG, EAX, EDI, NotDef, XCHG16, eXCHG, 0x9},
	//98 
	{L"CWDE",CWDE, NotDef, NotDef, NotDef, (Pointer)NULL, eCWDE, 0x0},
	//99  
	{L"CDQ",CDQ, NotDef, NotDef, NotDef, (Pointer)NULL, eCDQ, 0x0},
	//9A cp 
	{L"CALL",CALL, ptr16_Colon_32, NotDef, NotDef, (Pointer)NULL, eCALL, 0x0},
	//9B   
	{L"FWAIT",FWAIT, NotDef, NotDef, NotDef, (Pointer)NULL, eFWAIT, 0x0},
	//9C   
	{L"PUSHFD",PUSHFD, NotDef, NotDef, NotDef, (Pointer)NULL, ePUSHFD, 0x0},
	//9D   
	{L"POPFD",POPFD, NotDef, NotDef, NotDef, (Pointer)NULL, ePOPFD, 0x0},
	//9E   
	{L"SAHF",SAHF, NotDef, NotDef, NotDef, (Pointer)NULL, eSAHF, 0x0},
	//9F   
	{L"LAHF",LAHF, NotDef, NotDef, NotDef, (Pointer)NULL, eLAHF, 0x0},
	//A0 
	{L"MOV",MOV8, AL, moffs8, NotDef, (Pointer)NULL, eMOV8, 0x0},
	//A1 
	{L"MOV",MOV, EAX, moffs32, NotDef, MOV16, eMOV, 0x3},
	//A2 
	{L"MOV",MOV8, moffs8, AL, NotDef, (Pointer)NULL, eMOV8, 0x0},
	//A3 
	{L"MOV",MOV, moffs32, EAX, NotDef, MOV16, eMOV, 0x3},
	//A4  
	{L"MOVSB",MOVSB, NotDef, NotDef, NotDef, (Pointer)NULL, eMOVSB, 0x4},
	//A5  
	{L"MOVSD",MOVSD, NotDef, NotDef, NotDef, MOVSD16, eMOVSD, 0x5},
	//A6 
	{L"CMPSB",CMPSB, NotDef, NotDef, NotDef, (Pointer)NULL, eCMPSB, 0x4},
	//A7 
	{L"CMPSD",CMPSD, NotDef, NotDef, NotDef, CMPSD16, eCMPSD, 0x5},
	//A8 ib 
	{L"TEST",TEST8, AL, imm8, NotDef, (Pointer)NULL, eTEST8, 0x0},
	//A9 id 
	{L"TEST",TEST, EAX, imm32, NotDef, TEST16, eTEST, 0x1},
	//AA 
	{L"STOSB",STOSB, NotDef, NotDef, NotDef, STOSB16, eSTOSB, 0x5},
	//AB 
	{L"STOSD",STOSD, NotDef, NotDef, NotDef, STOSD16, eSTOSD, 0x5},
	//AC 
	{L"LODSB",LODSB, NotDef, NotDef, NotDef, LODSB16, eLODSB, 0x5},
	//AD 
	{L"LODSD",LODSD, NotDef, NotDef, NotDef, LODSD16, eLODSD, 0x5},
	//AE 
	{L"SCASB",SCASB, NotDef, NotDef, NotDef, SCASB16, eSCASB, 0x5},
	//AF 
	{L"SCASD",SCASD, NotDef, NotDef, NotDef, SCASD16, eSCASD, 0x5},
	//B0
	{L"MOV",MOV8, AL, imm8, NotDef, (Pointer)NULL, eMOV8, 0x0},
	//B1
	{L"MOV",MOV8, CL, imm8, NotDef, (Pointer)NULL, eMOV8, 0x0},
	//B2
	{L"MOV",MOV8, DL, imm8, NotDef, (Pointer)NULL, eMOV8, 0x0},
	//B3
	{L"MOV",MOV8, BL, imm8, NotDef, (Pointer)NULL, eMOV8, 0x0},
	//B4
	{L"MOV",MOV8, AH, imm8, NotDef, (Pointer)NULL, eMOV8, 0x0},
	//B5
	{L"MOV",MOV8, CH, imm8, NotDef, (Pointer)NULL, eMOV8, 0x0},
	//B6
	{L"MOV",MOV8, DH, imm8, NotDef, (Pointer)NULL, eMOV8, 0x0},
	//B7
	{L"MOV",MOV8, BH, imm8, NotDef, (Pointer)NULL, eMOV8, 0x0},
	//B8
	{L"MOV",MOV, EAX, imm32, NotDef, MOV16, eMOV, 0x1},
	//B9
	{L"MOV",MOV, ECX, imm32, NotDef, MOV16, eMOV, 0x1},
	//BA
	{L"MOV",MOV, EDX, imm32, NotDef, MOV16, eMOV, 0x1},
	//BB
	{L"MOV",MOV, EBX, imm32, NotDef, MOV16, eMOV, 0x1},
	//BC
	{L"MOV",MOV, ESP, imm32, NotDef, MOV16, eMOV, 0x1},
	//BD
	{L"MOV",MOV, EBP, imm32, NotDef, MOV16, eMOV, 0x1},
	//BE
	{L"MOV",MOV, ESI, imm32, NotDef, MOV16, eMOV, 0x1},
	//BF
	{L"MOV",MOV, EDI, imm32, NotDef, MOV16, eMOV, 0x1},
	//C0 /0 ib 
	{L"(Pointer)0xF000030F",(Pointer)0xF000030F, r_Slash_m8, imm8, NotDef, (Pointer)NULL, Ins, 0x2},
	//C1 /0 ib 
	{L"(Pointer)0xF0000310",(Pointer)0xF0000310, r_Slash_m32, imm8, NotDef, (Pointer)NULL, Ins, 0x3},
	//C2 iw 
	{L"RET",RET, imm16, NotDef, NotDef, (Pointer)NULL, eRET, 0x0},
	//C3
	{L"RET",RET, NotDef, NotDef, NotDef, (Pointer)NULL, eRET, 0x0},
	//C4 /r
	{L"LES",LES, r32, m16_Colon_32, NotDef, LES16, eLES, 0x2},
	//C5 /r
	{L"LDS",LDS, r32, m16_Colon_32, NotDef, LDS16, eLDS, 0x2},
	//C6 /0 
	{L"(Pointer)0xF0000311",(Pointer)0xF0000311, r_Slash_m8, imm8, NotDef, (Pointer)NULL, Ins, 0x2},
	//C7 /0 
	{L"(Pointer)0xF0000312",(Pointer)0xF0000312, r_Slash_m32, imm32, NotDef, (Pointer)NULL, Ins, 0x3},
	//C8 iw ib 
	{L"ENTER",ENTER8, imm16, imm8, NotDef, (Pointer)NULL, eENTER8, 0x0},
	//C9 
	{L"LEAVE",LEAVE, NotDef, NotDef, NotDef, LEAVE16, eLEAVE, 0x1},
	//CA iw 
	{L"RETF",RETF, imm16, NotDef, NotDef, (Pointer)NULL, eRETF, 0x0},
	//CB 
	{L"RETF",RETF, NotDef, NotDef, NotDef, (Pointer)NULL, eRETF, 0x0},
	//CC
	{L"INT3",INT3, NotDef, NotDef, NotDef, (Pointer)NULL, eINT3, 0x0},
	//CD ib 
	{L"INTn",INTn8, imm8, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//CE 
	{L"INTO",INTO, NotDef, NotDef, NotDef, (Pointer)NULL, eINTO, 0x0},
	//CF 
	{L"IRETD",IRETD, NotDef, NotDef, NotDef, (Pointer)NULL, eIRETD, 0x0},
	//D0 /0 
	{L"(Pointer)0xF0000313",(Pointer)0xF0000313, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, Ins, 0x2},
	//D1 /0 
	{L"(Pointer)0xF0000314",(Pointer)0xF0000314, r_Slash_m32, NotDef, NotDef, (Pointer)NULL, Ins, 0x3},
	//D2 /0 
	{L"(Pointer)0xF0000315",(Pointer)0xF0000315, r_Slash_m8, CL, NotDef, (Pointer)NULL, Ins, 0x2},
	//D3 /0 
	{L"(Pointer)0xF0000316",(Pointer)0xF0000316, r_Slash_m32, CL, NotDef, (Pointer)NULL, Ins, 0x3},
	//D4 ib
	{L"AAM",AAM, NotDef, NotDef, NotDef, (Pointer)NULL, eAAM, 0x0},
	//D5 ib   
	{L"AAD",AAD, NotDef, NotDef, NotDef, (Pointer)NULL, eAAD, 0x0},
	//D6
	{L"SetAlc",SetAlc, NotDef, NotDef, NotDef, (Pointer)NULL, eSetAlc, 0x0},
	//D7 
	{L"XLATB",XLATB, NotDef, NotDef, NotDef, (Pointer)NULL, eXLATB, 0x0},
	//D8 /0
	{L"(Pointer)0xF1817200",(Pointer)0xF1817200, m32, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 /0  
	{L"(Pointer)0xF1A19200",(Pointer)0xF1A19200, m32real, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA /0 
	{L"(Pointer)0xF1C1B200",(Pointer)0xF1C1B200, m32int, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB /0 
	{L"(Pointer)0xF1E1D200",(Pointer)0xF1E1D200, m32int, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC /0    
	{L"(Pointer)0xF201F200",(Pointer)0xF201F200, m64real, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD /0    
	{L"(Pointer)0xF2221200",(Pointer)0xF2221200, m64real, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE /0    
	{L"(Pointer)0xF2423200",(Pointer)0xF2423200, m16int, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF /0    
	{L"(Pointer)0xF2625200",(Pointer)0xF2625200, m16int, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//E0 cb    
	{L"LOOPNZ",LOOPNZ, rel8, NotDef, NotDef, (Pointer)NULL, eLOOPNZ, 0x0},
	//E1 cb    
	{L"LOOPZ",LOOPZ, rel8, NotDef, NotDef, (Pointer)NULL, eLOOPZ, 0x0},
	//E2 cb    
	{L"LOOP",LOOP, rel8, NotDef, NotDef, (Pointer)NULL, eLOOP, 0x0},
	//E3 cb    
	{L"JECXZ",JECXZ, rel8, NotDef, NotDef, (Pointer)NULL, eJECXZ, 0x2},
	//E4 ib    
	{L"IN_",IN_8, AL, imm8, NotDef, (Pointer)NULL, eIN_8, 0x0},
	//E5 ib    
	{L"IN_",IN_8, EAX, imm8, NotDef, (Pointer)NULL, eIN_8, 0x1},
	//E6 ib    
	{L"OUT_",OUT_8, imm8, AL, NotDef, (Pointer)NULL, eOUT_8, 0x0},
	//E7 ib    
	{L"OUT_",OUT_8, imm8, EAX, NotDef, (Pointer)NULL, eOUT_8, 0x1},
	//E8 cd    
	{L"CALL",CALL, rel32, NotDef, NotDef, (Pointer)NULL, eCALL, 0x0},
	//E9 cd    
	{L"JMP",JMP, rel32, NotDef, NotDef, (Pointer)NULL, eJMP, 0x0},
	//EA cp    
	{L"JMP",JMP, ptr16_Colon_32, NotDef, NotDef, (Pointer)NULL, eJMP, 0x0},
	//EB cb    
	{L"JMP",JMP, rel8, NotDef, NotDef, (Pointer)NULL, eJMP, 0x0},
	//EC    
	{L"IN_",IN_8, AL, DX, NotDef, (Pointer)NULL, eIN_8, 0x0},
	//ED    
	{L"IN_",IN_, EAX, DX, NotDef, IN_16, eIN_, 0x1},
	//EE   
	{L"OUT_",OUT_8, DX, AL, NotDef, (Pointer)NULL, eOUT_8, 0x0},
	//EF   
	{L"OUT_",OUT_, DX, EAX, NotDef, OUT_16, eOUT_, 0x1},
	//F0
	{L"LOCK",LOCK, NotDef, NotDef, NotDef, (Pointer)NULL, eLOCK, 0x0},
	//F1 ICEBP
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//F2 rep
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//F3 rep
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//F4  
	{L"HLT",HLT, NotDef, NotDef, NotDef, (Pointer)NULL, eHLT, 0x0},
	//F5  
	{L"CMC",CMC, NotDef, NotDef, NotDef, (Pointer)NULL, eCMC, 0x0},
	//F6 /0 ib
	{L"(Pointer)0xF0000327",(Pointer)0xF0000327, r_Slash_m8, imm8, NotDef, (Pointer)NULL, Ins, 0x2},
	//F7 /0 id
	{L"(Pointer)0xF0000328",(Pointer)0xF0000328, r_Slash_m32, imm32, NotDef, (Pointer)NULL, Ins, 0x3},
	//F8  
	{L"CLC",CLC, NotDef, NotDef, NotDef, (Pointer)NULL, eCLC, 0x0},
	//F9  
	{L"STC",STC, NotDef, NotDef, NotDef, (Pointer)NULL, eSTC, 0x0},
	//FA  
	{L"CLI",CLI, NotDef, NotDef, NotDef, (Pointer)NULL, eCLI, 0x0},
	//FB  
	{L"STI",STI, NotDef, NotDef, NotDef, (Pointer)NULL, eSTI, 0x0},
	//FC  
	{L"CLD",CLD, NotDef, NotDef, NotDef, (Pointer)NULL, eCLD, 0x0},
	//FD  
	{L"STD",STD, NotDef, NotDef, NotDef, (Pointer)NULL, eSTD, 0x0},
	//FE /0  
	{L"(Pointer)0xF0000329",(Pointer)0xF0000329, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, Ins, 0xA},
	//FF /0  
	{L"(Pointer)0xF000032A",(Pointer)0xF000032A, r_Slash_m32, NotDef, NotDef, (Pointer)NULL, Ins, 0xB}
};

SMTableBlock arTable_0F [] = {
	//0F 00 /0
	{L"(Pointer)0xF0000302",(Pointer)0xF0000302, r_Slash_m32, NotDef, NotDef, (Pointer)NULL, Ins, 0x3},
	//0F 01 /0
	{L"(Pointer)0xF0000303",(Pointer)0xF0000303, m, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 02 /r
	{L"LAR",LAR, r32, r_Slash_m32, NotDef, LAR16, eLAR, 0x3},
	//0F 03 /r
	{L"LSL",LSL, r32, r_Slash_m32, NotDef, LSL16, eLSL, 0x3},
	//0F 04
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 05 SYSCALL
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 06
	{L"CLTS",CLTS, NotDef, NotDef, NotDef, (Pointer)NULL, eCLTS, 0x0},
	//0F 07 SYSRET
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 08 
	{L"INVD",INVD, NotDef, NotDef, NotDef, (Pointer)NULL, eINVD, 0x0},
	//0F 09 
	{L"WBINVD",WBINVD, NotDef, NotDef, NotDef, (Pointer)NULL, eWBINVD, 0x0},
	//0F 0A
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 0B 
	{L"UD2",UD2, NotDef, NotDef, NotDef, (Pointer)NULL, eUD2, 0x0},
	//0F 0C
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 0D
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 0E
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 0F
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 10 /r 
	{L"MOVUPS",MOVUPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eMOVUPS, 0x4},
	//0F 11 /r 
	{L"MOVUPS",MOVUPS, xmm2_Slash_m128, xmm, NotDef, (Pointer)NULL, eMOVUPS, 0x4},
	//0F 12 /r 
	{L"MOVLPS",MOVLPS, xmm, m64, NotDef, (Pointer)NULL, eMOVLPS, 0x0},
	//0F 13 /r 
	{L"MOVLPS",MOVLPS, m64, xmm, NotDef, (Pointer)NULL, eMOVLPS, 0x0},
	//0F 14 /r 
	{L"UNPCKLPS",UNPCKLPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eUNPCKLPS, 0x0},
	//0F 15 /r 
	{L"UNPCKHPS",UNPCKHPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eUNPCKHPS, 0x0},
	//0F 16 /r 
	{L"MOVHPS",MOVHPS, xmm, m64, NotDef, (Pointer)NULL, eMOVHPS, 0x0},
	//0F 17 /r 
	{L"MOVHPS",MOVHPS, m64, xmm, NotDef, (Pointer)NULL, eMOVHPS, 0x0},
	//0F 18 /0 
	{L"(Pointer)0xF0000304",(Pointer)0xF0000304, m8, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 19
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 1A
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 1B
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 1C
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 1D
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 1E
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 1F
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 20 /r
	{L"MOV",MOV, r32, CR0, NotDef, (Pointer)NULL, eMOV, 0x0},
	//0F 21 /r
	{L"MOV",MOV, r32, DR0_DR7, NotDef, (Pointer)NULL, eMOV, 0x0},
	//0F 22 /r
	{L"MOV",MOV, CR0, r32, NotDef, (Pointer)NULL, eMOV, 0x0},
	//0F 23 /r
	{L"MOV",MOV, DR0_DR7, r32, NotDef, (Pointer)NULL, eMOV, 0x0},
	//0F 24
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 25
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 26
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 27
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 28 /r 
	{L"MOVAPS",MOVAPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eMOVAPS, 0x0},
	//0F 29 /r 
	{L"MOVAPS",MOVAPS, xmm2_Slash_m128, xmm, NotDef, (Pointer)NULL, eMOVAPS, 0x0},
	//0F 2A /r 
	{L"CVTPI2PS",CVTPI2PS, xmm, mm_Slash_m64, NotDef, (Pointer)NULL, eCVTPI2PS, 0x4},
	//0F 2B, /r
	{L"MOVNTPS",MOVNTPS, m128, xmm, NotDef, (Pointer)NULL, eMOVNTPS, 0x0},
	//0F 2C /r 
	{L"CVTTPS2PI",CVTTPS2PI, mm, xmm_Slash_m64, NotDef, (Pointer)NULL, eCVTTPS2PI, 0x4},
	//0F 2D /r 
	{L"CVTPS2PI",CVTPS2PI, mm, xmm_Slash_m64, NotDef, (Pointer)NULL, eCVTPS2PI, 0x4},
	//0F 2E /r
	{L"UCOMISS",UCOMISS, xmm, xmm2_Slash_m32, NotDef, (Pointer)NULL, eUCOMISS, 0x0},
	//0F 2F /r
	{L"COMISS",COMISS, xmm, xmm2_Slash_m32, NotDef, (Pointer)NULL, eCOMISS, 0x0},
	//0F 30 
	{L"WRMSR",WRMSR, NotDef, NotDef, NotDef, (Pointer)NULL, eWRMSR, 0x0},
	//0F 31 
	{L"RDTSC",RDTSC, EAX, EDX, NotDef, (Pointer)NULL, eRDTSC, 0x0},
	//0F 32 
	{L"RDMSR",RDMSR, NotDef, NotDef, NotDef, (Pointer)NULL, eRDMSR, 0x0},
	//0F 33 
	{L"RDPMC",RDPMC, NotDef, NotDef, NotDef, (Pointer)NULL, eRDPMC, 0x0},
	//0F 34 
	{L"SYSENTER",SYSENTER, NotDef, NotDef, NotDef, (Pointer)NULL, eSYSENTER, 0x0},
	//0F 35 
	{L"SYSEXIT",SYSEXIT, NotDef, NotDef, NotDef, (Pointer)NULL, eSYSEXIT, 0x0},
	//0F 36
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 37
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 38
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 39
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 3A
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 3B
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 3C
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 3D
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 3E
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 3F
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 40 /r
	{L"CMOVO",CMOVO, r32, r_Slash_m32, NotDef, CMOVO16, eCMOVO, 0x3},
	//0F 41 /r
	{L"CMOVNO",CMOVNO, r32, r_Slash_m32, NotDef, CMOVNO16, eCMOVNO, 0x3},
	//0F 42 /r
	{L"CMOVC",CMOVC, r32, r_Slash_m32, NotDef, CMOVC16, eCMOVC, 0x3},
	//0F 43 /r
	{L"CMOVAE",CMOVAE, r32, r_Slash_m32, NotDef, CMOVAE16, eCMOVAE, 0x3},
	//0F 44 /r
	{L"CMOVZ",CMOVZ, r32, r_Slash_m32, NotDef, CMOVZ16, eCMOVZ, 0x3},
	//0F 45 /r
	{L"CMOVNZ",CMOVNZ, r32, r_Slash_m32, NotDef, CMOVNZ16, eCMOVNZ, 0x3},
	//0F 46 /r
	{L"CMOVNA",CMOVNA, r32, r_Slash_m32, NotDef, CMOVNA16, eCMOVNA, 0x3},
	//0F 47 /r
	{L"CMOVNBE",CMOVNBE, r32, r_Slash_m32, NotDef, CMOVNBE16, eCMOVNBE, 0x3},
	//0F 48 /r
	{L"CMOVS",CMOVS, r32, r_Slash_m32, NotDef, CMOVS16, eCMOVS, 0x3},
	//0F 49 /r
	{L"CMOVNS",CMOVNS, r32, r_Slash_m32, NotDef, CMOVNS16, eCMOVNS, 0x3},
	//0F 4A /r
	{L"CMOVPE",CMOVPE, r32, r_Slash_m32, NotDef, CMOVPE16, eCMOVPE, 0x3},
	//0F 4B /r
	{L"CMOVPO",CMOVPO, r32, r_Slash_m32, NotDef, CMOVPO16, eCMOVPO, 0x3},
	//0F 4C /r
	{L"CMOVNGE",CMOVNGE, r32, r_Slash_m32, NotDef, CMOVNGE16, eCMOVNGE, 0x3},
	//0F 4D /r
	{L"CMOVNL",CMOVNL, r32, r_Slash_m32, NotDef, CMOVNL16, eCMOVNL, 0x3},
	//0F 4E /r
	{L"CMOVNG",CMOVNG, r32, r_Slash_m32, NotDef, CMOVNG16, eCMOVNG, 0x3},
	//0F 4F /r
	{L"CMOVNLE",CMOVNLE, r32, r_Slash_m32, NotDef, CMOVNLE16, eCMOVNLE, 0x3},
	//0F 50 /r 
	{L"MOVMSKPS",MOVMSKPS, r32, xmm, NotDef, (Pointer)NULL, eMOVMSKPS, 0x0},
	//0F 51 /r 
	{L"SQRTPS",SQRTPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eSQRTPS, 0x4},
	//0F 52 /r 
	{L"RSQRTPS",RSQRTPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eRSQRTPS, 0x4},
	//0F 53 /r 
	{L"RCPPS",RCPPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eRCPPS, 0x4},
	//0F 54 /r 
	{L"ANDPS",ANDPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eANDPS, 0x0},
	//0F 55 /r 
	{L"ANDNPS",ANDNPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eANDNPS, 0x0},
	//0F 56 /r 
	{L"ORPS",ORPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eORPS, 0x0},
	//0F 57 /r 
	{L"XORPS",XORPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eXORPS, 0x0},
	//0F 58 /r 
	{L"ADDPS",ADDPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eADDPS, 0x4},
	//0F 59 /r 
	{L"MULPS",MULPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eMULPS, 0x4},
	//0F 5A
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 5B
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 5C /r 
	{L"SUBPS",SUBPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eSUBPS, 0x4},
	//0F 5D /r 
	{L"MINPS",MINPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eMINPS, 0x4},
	//0F 5E /r 
	{L"DIVPS",DIVPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eDIVPS, 0x4},
	//0F 5F /r 
	{L"MAXPS",MAXPS, xmm, xmm2_Slash_m128, NotDef, (Pointer)NULL, eMAXPS, 0x4},
	//0F 60 /r
	{L"PUNPCKLBW",PUNPCKLBW, mm, mm_Slash_m32, NotDef, (Pointer)NULL, ePUNPCKLBW, 0x0},
	//0F 61 /r
	{L"PUNPCKLWD",PUNPCKLWD, mm, mm_Slash_m32, NotDef, (Pointer)NULL, ePUNPCKLWD, 0x0},
	//0F 62 /r
	{L"PUNPCKLDQ",PUNPCKLDQ, mm, mm_Slash_m32, NotDef, (Pointer)NULL, ePUNPCKLDQ, 0x0},
	//0F 63 /r
	{L"PACKSSWB",PACKSSWB, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePACKSSWB, 0x0},
	//0F 64 /r
	{L"PCMPGTB",PCMPGTB, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePCMPGTB, 0x0},
	//0F 65 /r
	{L"PCMPGTW",PCMPGTW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePCMPGTW, 0x0},
	//0F 66 /r
	{L"PCMPGTD",PCMPGTD, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePCMPGTD, 0x0},
	//0F 67 /r
	{L"PACKUSWB",PACKUSWB, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePACKUSWB, 0x0},
	//0F 68 /r
	{L"PUNPCKHBW",PUNPCKHBW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePUNPCKHBW, 0x0},
	//0F 69 /r
	{L"PUNPCKHWD",PUNPCKHWD, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePUNPCKHWD, 0x0},
	//0F 6A /r
	{L"PUNPCKHDQ",PUNPCKHDQ, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePUNPCKHDQ, 0x0},
	//0F 6B /r
	{L"PACKSSDW",PACKSSDW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePACKSSDW, 0x0},
	//0F 6C
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 6D
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 6E /r
	{L"MOVD",MOVD, mm, r_Slash_m32, NotDef, MOVD16, eMOVD, 0x3},
	//0F 6F /r
	{L"MOVQ",MOVQ, mm, mm_Slash_m64, NotDef, (Pointer)NULL, eMOVQ, 0x0},
	//0F 70 /r ib 
	{L"PSHUFW",PSHUFW, mm, mm_Slash_m64, imm8, (Pointer)NULL, ePSHUFW, 0x0},
	//0F 71 /2 ib 
	{L"(Pointer)0xF0000305",(Pointer)0xF0000305, mm, imm8, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 72 /2 ib 
	{L"(Pointer)0xF0000306",(Pointer)0xF0000306, mm, imm8, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 73 /2 ib
	{L"(Pointer)0xF0000307",(Pointer)0xF0000307, mm, imm8, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 74 /r
	{L"PCMPEQB",PCMPEQB, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePCMPEQB, 0x0},
	//0F 75 /r
	{L"PCMPEQW",PCMPEQW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePCMPEQW, 0x0},
	//0F 76 /r
	{L"PCMPEQD",PCMPEQD, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePCMPEQD, 0x0},
	//0F 77 
	{L"EMMS",EMMS, NotDef, NotDef, NotDef, (Pointer)NULL, eEMMS, 0x0},
	//0F 78
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 79
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 7A
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 7B
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 7C
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 7D
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 7E /r
	{L"MOVD",MOVD, r_Slash_m32, mm, NotDef, MOVD16, eMOVD, 0x3},
	//0F 7F /r
	{L"MOVQ",MOVQ, mm_Slash_m64, mm, NotDef, (Pointer)NULL, eMOVQ, 0x0},
	//0F 80 cw/cd
	{L"JO",JO, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJO, 0x1},
	//0F 81 cw/cd
	{L"JNO",JNO, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJNO, 0x1},
	//0F 82 cw/cd
	{L"JC",JC, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJC, 0x1},
	//0F 83 cw/cd
	{L"JAE",JAE, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJAE, 0x1},
	//0F 84 cw/cd
	{L"JZ",JZ, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJZ, 0x1},
	//0F 85 cw/cd
	{L"JNZ",JNZ, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJNZ, 0x1},
	//0F 86 cw/cd
	{L"JNA",JNA, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJNA, 0x1},
	//0F 87 cw/cd
	{L"JNBE",JNBE, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJNBE, 0x1},
	//0F 88 cw/cd
	{L"JS",JS, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJS, 0x1},
	//0F 89 cw/cd
	{L"JNS",JNS, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJNS, 0x1},
	//0F 8A cw/cd
	{L"JPE",JPE, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJPE, 0x1},
	//0F 8B cw/cd
	{L"JPO",JPO, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJPO, 0x1},
	//0F 8C cw/cd
	{L"JNGE",JNGE, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJNGE, 0x1},
	//0F 8D cw/cd
	{L"JNL",JNL, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJNL, 0x1},
	//0F 8E cw/cd
	{L"JNG",JNG, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJNG, 0x1},
	//0F 8F cw/cd
	{L"JNLE",JNLE, rel16_Slash_32, NotDef, NotDef, (Pointer)NULL, eJNLE, 0x1},
	//0F 90
	{L"SETO",SETO8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETO8, 0x2},
	//0F 91
	{L"SETNO",SETNO8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETNO8, 0x2},
	//0F 92
	{L"SETB",SETB8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETB8, 0x2},
	//0F 93
	{L"SETNB",SETNB8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETNB8, 0x2},
	//0F 94
	{L"SETZ",SETZ8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETZ8, 0x2},
	//0F 95
	{L"SETNZ",SETNZ8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETNZ8, 0x2},
	//0F 96
	{L"SETNA",SETNA8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETNA8, 0x2},
	//0F 97
	{L"SETNBE",SETNBE8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETNBE8, 0x2},
	//0F 98 
	{L"SETS",SETS8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETS8, 0x2},
	//0F 99
	{L"SETNS",SETNS8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETNS8, 0x2},
	//0F 9A
	{L"SETPE",SETPE8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETPE8, 0x2},
	//0F 9B
	{L"SETPO",SETPO8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETPO8, 0x2},
	//0F 9C
	{L"SETNGE",SETNGE8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETNGE8, 0x2},
	//0F 9D
	{L"SETNL",SETNL8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETNL8, 0x2},
	//0F 9E
	{L"SETNG",SETNG8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETNG8, 0x2},
	//0F 9F
	{L"SETNLE",SETNLE8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSETNLE8, 0x2},
	//0F A0
	{L"PUSH",PUSH, FS, NotDef, NotDef, (Pointer)NULL, ePUSH, 0x0},
	//0F A1
	{L"POP",POP, FS, NotDef, NotDef, (Pointer)NULL, ePOP, 0x0},
	//0F A2
	{L"CPUID",CPUID, NotDef, NotDef, NotDef, (Pointer)NULL, eCPUID, 0x0},
	//0F A3
	{L"BT",BT, r_Slash_m32, r32, NotDef, BT16, eBT, 0x3},
	//0F A4
	{L"SHLD",SHLD, r_Slash_m32, r32, imm8, SHLD16, eSHLD, 0x3},
	//0F A5
	{L"SHLD",SHLD, r_Slash_m32, r32, CL, SHLD16, eSHLD, 0x3},
	//0F A6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F A7
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F A8
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F A9
	{L"POP",POP, GS, NotDef, NotDef, (Pointer)NULL, ePOP, 0x0},
	//0F AA
	{L"RSM",RSM, NotDef, NotDef, NotDef, (Pointer)NULL, eRSM, 0x0},
	//0F AB
	{L"BTS",BTS, r_Slash_m32, r32, NotDef, BTS16, eBTS, 0xB},
	//0F AC
	{L"SHRD",SHRD, r_Slash_m32, r32, imm8, SHRD16, eSHRD, 0x3},
	//0F AD
	{L"SHRD",SHRD, r_Slash_m32, r32, CL, SHRD16, eSHRD, 0x3},
	//0F AE /0
	{L"(Pointer)0xF0000308",(Pointer)0xF0000308, m512byte, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F AF /r
	{L"IMUL",IMUL, r32, r_Slash_m32, NotDef, IMUL16, eIMUL, 0x3},
	//0F B0 /r
	{L"CMPXCHG",CMPXCHG8, r_Slash_m8, r8, NotDef, (Pointer)NULL, eCMPXCHG8, 0xA},
	//0F B1 /r
	{L"CMPXCHG",CMPXCHG, r_Slash_m32, r32, NotDef, CMPXCHG16, eCMPXCHG, 0xB},
	//0F B2 /r
	{L"LSS",LSS, r32, m16_Colon_32, NotDef, LSS16, eLSS, 0x2},
	//0F B3
	{L"BTR",BTR, r_Slash_m32, r32, NotDef, BTR16, eBTR, 0xB},
	//0F B4 /r
	{L"LFS",LFS, r32, m16_Colon_32, NotDef, LFS16, eLFS, 0x2},
	//0F B5 /r
	{L"LGS",LGS, r32, m16_Colon_32, NotDef, LGS16, eLGS, 0x2},
	//0F B6 /r
	{L"MOVZX",MOVZX8, r32, r_Slash_m8, NotDef, (Pointer)NULL, eMOVZX8, 0x2},
	//0F B7 /r
	{L"MOVZX",MOVZX, r32, r_Slash_m16, NotDef, MOVZX16, eMOVZX, 0x3},
	//0F B8
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F B9
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F BA /4 ib
	{L"(Pointer)0xF0000309",(Pointer)0xF0000309, r_Slash_m32, imm8, NotDef, (Pointer)NULL, Ins, 0x3},
	//0F BB
	{L"BTC",BTC, r_Slash_m32, r32, NotDef, BTC16, eBTC, 0xB},
	//0F BC 
	{L"BSF",BSF, r32, r_Slash_m32, NotDef, BSF16, eBSF, 0x3},
	//0F BD
	{L"BSR",BSR, r32, r_Slash_m32, NotDef, BSR16, eBSR, 0x3},
	//0F BE /r
	{L"MOVSX",MOVSX8, r32, r_Slash_m8, NotDef, (Pointer)NULL, eMOVSX8, 0x2},
	//0F BF /r
	{L"MOVSX",MOVSX, r32, r_Slash_m16, NotDef, MOVSX16, eMOVSX, 0x3},
	//0F C0 /r
	{L"XADD",XADD8, r_Slash_m8, r8, NotDef, (Pointer)NULL, eXADD8, 0xA},
	//0F C1 /r
	{L"XADD",XADD, r_Slash_m32, r32, NotDef, XADD16, eXADD, 0xB},
	//0F C2 /r ib
	{L"CMPPS",CMPPS, xmm, xmm2_Slash_m128, imm8, (Pointer)NULL, eCMPPS, 0x4},
	//0F C3
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F C4 /r ib
	{L"PINSRW",PINSRW, mm, r32_Slash_m16, imm8, (Pointer)NULL, ePINSRW, 0x0},
	//0F C5 /r ib
	{L"PEXTRW",PEXTRW, r32, mm, imm8, (Pointer)NULL, ePEXTRW, 0x0},
	//0F C6 /r ib
	{L"SHUFPS",SHUFPS, xmm, xmm2_Slash_m128, imm8, (Pointer)NULL, eSHUFPS, 0x0},
	//0F C7 /1 m64 
	{L"(Pointer)0xF000030A",(Pointer)0xF000030A, m64, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F C8
	{L"BSWAP",BSWAP, EAX, NotDef, NotDef, (Pointer)NULL, eBSWAP, 0x0},
	//0F C9
	{L"BSWAP",BSWAP, ECX, NotDef, NotDef, (Pointer)NULL, eBSWAP, 0x0},
	//0F CA
	{L"BSWAP",BSWAP, EDX, NotDef, NotDef, (Pointer)NULL, eBSWAP, 0x0},
	//0F CB
	{L"BSWAP",BSWAP, EBX, NotDef, NotDef, (Pointer)NULL, eBSWAP, 0x0},
	//0F CC
	{L"BSWAP",BSWAP, ESP, NotDef, NotDef, (Pointer)NULL, eBSWAP, 0x0},
	//0F CD
	{L"BSWAP",BSWAP, EBP, NotDef, NotDef, (Pointer)NULL, eBSWAP, 0x0},
	//0F CE
	{L"BSWAP",BSWAP, ESI, NotDef, NotDef, (Pointer)NULL, eBSWAP, 0x0},
	//0F CF
	{L"BSWAP",BSWAP, EDI, NotDef, NotDef, (Pointer)NULL, eBSWAP, 0x0},
	//0F D0
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F D1 /r
	{L"PSRLW",PSRLW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePSRLW, 0x0},
	//0F D2 /r
	{L"PSRLD",PSRLD, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePSRLD, 0x0},
	//0F D3 /r
	{L"PSRLQ",PSRLQ, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePSRLQ, 0x0},
	//0F D4
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F D5 /r
	{L"PMULLW",PMULLW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePMULLW, 0x0},
	//0F D6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F D7 /r
	{L"PMOVMSKB",PMOVMSKB, r32, mm, NotDef, (Pointer)NULL, ePMOVMSKB, 0x0},
	//0F D8 /r
	{L"PSUBUSB",PSUBUSB, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePSUBUSB, 0x0},
	//0F D9 /r
	{L"PSUBUSW",PSUBUSW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePSUBUSW, 0x0},
	//0F DA, /r
	{L"PMINUB",PMINUB, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePMINUB, 0x0},
	//0F DB /r
	{L"PAND",PAND, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePAND, 0x0},
	//0F DC /r
	{L"PADDUSB",PADDUSB, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePADDUSB, 0x0},
	//0F DD /r
	{L"PADDUSW",PADDUSW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePADDUSW, 0x0},
	//0F DE /r
	{L"PMAXUB",PMAXUB, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePMAXUB, 0x0},
	//0F DF /r
	{L"PANDN",PANDN, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePANDN, 0x0},
	//0F E0 /r
	{L"PAVGB",PAVGB, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePAVGB, 0x0},
	//0F E1 /r
	{L"PSRAW",PSRAW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePSRAW, 0x0},
	//0F E2 /r
	{L"PSRAD",PSRAD, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePSRAD, 0x0},
	//0F E3 /r
	{L"PAVGW",PAVGW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePAVGW, 0x0},
	//0F E4 /r
	{L"PMULHUW",PMULHUW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePMULHUW, 0x0},
	//0F E5 /r
	{L"PMULHW",PMULHW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePMULHW, 0x0},
	//0F E6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F E7 /r
	{L"MOVNTQ",MOVNTQ, m64, mm, NotDef, (Pointer)NULL, eMOVNTQ, 0x0},
	//0F E8 /r
	{L"PSUBSB",PSUBSB, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePSUBSB, 0x0},
	//0F E9 /r
	{L"PSUBSW",PSUBSW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePSUBSW, 0x0},
	//0F EA /r
	{L"PMINSW",PMINSW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePMINSW, 0x0},
	//0F EB /r
	{L"POR",POR, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePOR, 0x0},
	//0F EC /r
	{L"PADDSB",PADDSB, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePADDSB, 0x0},
	//0F ED /r
	{L"PADDSW",PADDSW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePADDSW, 0x0},
	//0F EE /r
	{L"PMAXSW",PMAXSW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePMAXSW, 0x0},
	//0F EF /r
	{L"PXOR",PXOR, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePXOR, 0x0},
	//0F F0
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F F1 /r
	{L"PSLLW",PSLLW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePSLLW, 0x0},
	//0F F2 /r
	{L"PSLLD",PSLLD, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePSLLD, 0x0},
	//0F F3 /r
	{L"PSLLQ",PSLLQ, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePSLLQ, 0x0},
	//0F F4
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F F5 /r
	{L"PMADDWD",PMADDWD, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePMADDWD, 0x0},
	//0F F6 /r
	{L"PSADBW",PSADBW, NotDef, NotDef, NotDef, (Pointer)NULL, ePSADBW, 0x0},
	//0F F7 /r
	{L"MASKMOVQ",MASKMOVQ, NotDef, NotDef, NotDef, (Pointer)NULL, eMASKMOVQ, 0x0},
	//0F F8 /r
	{L"PSUBB",PSUBB, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePSUBB, 0x0},
	//0F F9 /r
	{L"PSUBW",PSUBW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePSUBW, 0x0},
	//0F FA /r
	{L"PSUBD",PSUBD, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePSUBD, 0x0},
	//0F FB
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F FC /r
	{L"PADDB",PADDB, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePADDB, 0x0},
	//0F FD /r
	{L"PADDW",PADDW, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePADDW, 0x0},
	//0F FE /r
	{L"PADDD",PADDD, mm, mm_Slash_m64, NotDef, (Pointer)NULL, ePADDD, 0x0},
	//0F FF
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock arTable_0F00Ext [] = {
	//0F 00 /0
	{L"SLDT",SLDT, r_Slash_m32, NotDef, NotDef, SLDT16, eSLDT, 0x3},
	//0F 00 /1
	{L"STR",STR, r_Slash_m16, NotDef, NotDef, STR16, eSTR, 0x3},
	//0F 00 /2
	{L"LLDT",LLDT, r_Slash_m16, NotDef, NotDef, LLDT16, eLLDT, 0x3},
	//0F 00 /3
	{L"LTR",LTR, r_Slash_m16, NotDef, NotDef, LTR16, eLTR, 0x3},
	//0F 00 /4
	{L"VERR",VERR, r_Slash_m16, NotDef, NotDef, VERR16, eVERR, 0x3},
	//0F 00 /5
	{L"VERW",VERW, r_Slash_m16, NotDef, NotDef, VERW16, eVERW, 0x3},
	//0F 00 /6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 00 /7
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock arTable_0F01Ext [] = {
	//0F 01 /0
	{L"SGDT",SGDT, m, NotDef, NotDef, (Pointer)NULL, eSGDT, 0x0},
	//0F 01 /1
	{L"SIDT",SIDT, m, NotDef, NotDef, (Pointer)NULL, eSIDT, 0x0},
	//0F 01 /2
	{L"LGDT",LGDT, m16_Amp_32, NotDef, NotDef, (Pointer)NULL, eLGDT, 0x0},
	//0F 01 /3
	{L"LIDT",LIDT, m16_Amp_32, NotDef, NotDef, (Pointer)NULL, eLIDT, 0x0},
	//0F 01 /4
	{L"SMSW",SMSW, r32_Slash_m16, NotDef, NotDef, (Pointer)NULL, eSMSW, 0x0},
	//0F 01 /5
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 01 /6
	{L"LMSW",LMSW, r_Slash_m16, NotDef, NotDef, LMSW16, eLMSW, 0x3},
	//0F 01 /7
	{L"INVLPG",INVLPG, m, NotDef, NotDef, (Pointer)NULL, eINVLPG, 0x0},
};

SMTableBlock arTable_0F18Ext [] = {
	//0F 18 /0 
	{L"PREFETCHNTA",PREFETCHNTA8, m8, NotDef, NotDef, (Pointer)NULL, ePREFETCHNTA8, 0x0},
	//0F 18 /1 
	{L"PREFETCHT0",PREFETCHT08, m8, NotDef, NotDef, (Pointer)NULL, ePREFETCHT08, 0x0},
	//0F 18 /2 
	{L"PREFETCHT1",PREFETCHT18, m8, NotDef, NotDef, (Pointer)NULL, ePREFETCHT18, 0x0},
	//0F 18 /3 
	{L"PREFETCHT2",PREFETCHT28, m8, NotDef, NotDef, (Pointer)NULL, ePREFETCHT28, 0x0},
	//0F 18 /4
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 18 /5
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 18 /6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 18 /7
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock arTable_0F71Ext [] = {
	//0F 71 /0
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 71 /1
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 71 /2 ib 
	{L"PSRLW",PSRLW8, mm, imm8, NotDef, (Pointer)NULL, ePSRLW8, 0x0},
	//0F 71 /3
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 71 /4 ib
	{L"PSRAW",PSRAW8, mm, imm8, NotDef, (Pointer)NULL, ePSRAW8, 0x0},
	//0F 71 /5
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 71 /6 ib
	{L"PSLLW",PSLLW8, mm, imm8, NotDef, (Pointer)NULL, ePSLLW8, 0x0},
	//0F 71 /7
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock arTable_0F72Ext [] = {
	//0F 72 /0
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 72 /1
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 72 /2 ib 
	{L"PSRLD",PSRLD8, mm, imm8, NotDef, (Pointer)NULL, ePSRLD8, 0x0},
	//0F 72 /3
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 72 /4 ib
	{L"PSRAD",PSRAD8, mm, imm8, NotDef, (Pointer)NULL, ePSRAD8, 0x0},
	//0F 72 /5
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 72 /6 ib
	{L"PSLLD",PSLLD8, mm, imm8, NotDef, (Pointer)NULL, ePSLLD8, 0x0},
	//0F 72 /7
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock arTable_0F73Ext [] = {
	//0F 73 /0
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 73 /1
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 73 /2 ib
	{L"PSRLQ",PSRLQ8, mm, imm8, NotDef, (Pointer)NULL, ePSRLQ8, 0x0},
	//0F 73 /3
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 73 /4
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 73 /5
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F 73 /6 ib
	{L"PSLLQ",PSLLQ8, mm, imm8, NotDef, (Pointer)NULL, ePSLLQ8, 0x0},
	//0F 73 /7
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock arTable_0FAEExt [] = {
	//0F AE /0
	{L"FXSAVE",FXSAVE, m512byte, NotDef, NotDef, (Pointer)NULL, eFXSAVE, 0x0},
	//0F AE /1
	{L"FXRSTOR",FXRSTOR, m512byte, NotDef, NotDef, (Pointer)NULL, eFXRSTOR, 0x0},
	//0F AE /2
	{L"LDMXCSR",LDMXCSR, m32, NotDef, NotDef, (Pointer)NULL, eLDMXCSR, 0x0},
	//0F AE /3
	{L"STMXCSR",STMXCSR, m32, NotDef, NotDef, (Pointer)NULL, eSTMXCSR, 0x0},
	//0F AE /4
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F AE /5
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F AE /6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F AE /7
	{L"SFENCE",SFENCE, NotDef, NotDef, NotDef, (Pointer)NULL, eSFENCE, 0x0},
};

SMTableBlock arTable_0FBAExt [] = {
	//0F BA /0
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F BA /1
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F BA /2
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F BA /3
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F BA /4 ib
	{L"BT",BT, r_Slash_m32, imm8, NotDef, BT16, eBT, 0x3},
	//0F BA /5 ib
	{L"BTS",BTS, r_Slash_m32, imm8, NotDef, BTS16, eBTS, 0xB},
	//0F BA /6 ib
	{L"BTR",BTR, r_Slash_m32, imm8, NotDef, BTR16, eBTR, 0xB},
	//0F BA /7 ib
	{L"BTC",BTC, r_Slash_m32, imm8, NotDef, BTC16, eBTC, 0xB},
};

SMTableBlock arTable_0FC7Ext [] = {
	//0F C7 /0
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F C7 /1 m64 
	{L"CMPXCHGB",CMPXCHG8B, m64, NotDef, NotDef, (Pointer)NULL, eCMPXCHG8B, 0x0},
	//0F C7 /2
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F C7 /3
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F C7 /4
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F C7 /5
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F C7 /6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//0F C7 /7
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock arTable_80Ext [] = {
	//80 /0 ib
	{L"ADD",ADD8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eADD8, 0xA},
	//80 /1 ib
	{L"OR",OR8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eOR8, 0xA},
	//80 /2 ib
	{L"ADC",ADC8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eADC8, 0xA},
	//80 /3 ib
	{L"SBB",SBB8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eSBB8, 0xA},
	//80 /4 ib
	{L"AND",AND8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eAND8, 0xA},
	//80 /5 ib
	{L"SUB",SUB8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eSUB8, 0xA},
	//80 /6 ib
	{L"XOR",XOR8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eXOR8, 0xA},
	//80 /7 ib 
	{L"CMP",CMP8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eCMP8, 0x2},
};

SMTableBlock arTable_81Ext [] = {
	//81 /0 id
	{L"ADD",ADD, r_Slash_m32, imm32, NotDef, ADD16, eADD, 0xB},
	//81 /1 id
	{L"OR",OR, r_Slash_m32, imm32, NotDef, OR16, eOR, 0xB},
	//81 /2 iw
	{L"ADC",ADC, r_Slash_m32, imm32, NotDef, ADC16, eADC, 0xB},
	//81 /3 id
	{L"SBB",SBB, r_Slash_m32, imm32, NotDef, SBB16, eSBB, 0xB},
	//81 /4 id
	{L"AND",AND, r_Slash_m32, imm32, NotDef, AND16, eAND, 0xB},
	//81 /5 id
	{L"SUB",SUB, r_Slash_m32, imm32, NotDef, SUB16, eSUB, 0xB},
	//81 /6 id 
	{L"XOR",XOR, r_Slash_m32, imm32, NotDef, XOR16, eXOR, 0xB},
	//81 /7 id 
	{L"CMP",CMP, r_Slash_m32, imm32, NotDef, CMP16, eCMP, 0x3},
};

SMTableBlock arTable_83Ext [] = {
	//83 /0 ib
	{L"ADD",ADD, r_Slash_m32, imm8, NotDef, ADD16, eADD, 0xB},
	//83 /1 ib
	{L"OR",OR, r_Slash_m32, imm8, NotDef, OR16, eOR, 0xB},
	//83 /2 ib
	{L"ADC",ADC, r_Slash_m32, imm8, NotDef, ADC16, eADC, 0xB},
	//83 /3 ib
	{L"SBB",SBB, r_Slash_m32, imm8, NotDef, SBB16, eSBB, 0xB},
	//83 /4 ib
	{L"AND",AND, r_Slash_m32, imm8, NotDef, AND16, eAND, 0xB},
	//83 /5 ib
	{L"SUB",SUB, r_Slash_m32, imm8, NotDef, SUB16, eSUB, 0xB},
	//83 /6 ib 
	{L"XOR",XOR, r_Slash_m32, imm8, NotDef, XOR16, eXOR, 0xB},
	//83 /7 ib 
	{L"CMP",CMP, r_Slash_m32, imm8, NotDef, CMP16, eCMP, 0x3},
};

SMTableBlock arTable_8FExt [] = {
	//8F /0
	{L"POP",POP, m32, NotDef, NotDef, (Pointer)NULL, ePOP, 0x0},
	//8F /1
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//8F /2
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//8F /3
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//8F /4
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//8F /5
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//8F /6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//8F /7
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock arTable_C0Ext [] = {
	//C0 /0 ib 
	{L"ROL",ROL8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eROL8, 0x2},
	//C0 /1 ib 
	{L"ROR",ROR8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eROR8, 0x2},
	//C0 /2 ib 
	{L"RCL",RCL8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eRCL8, 0x2},
	//C0 /3 ib 
	{L"RCR",RCR8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eRCR8, 0x2},
	//C0 /4 ib 
	{L"SHL",SHL8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eSHL8, 0x2},
	//C0 /5 ib 
	{L"SHR",SHR8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eSHR8, 0x2},
	//C0 /6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//C0 /7 ib 
	{L"SAR",SAR8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eSAR8, 0x2},
};

SMTableBlock arTable_C1Ext [] = {
	//C1 /0 ib 
	{L"ROL",ROL, r_Slash_m32, imm8, NotDef, ROL16, eROL, 0x3},
	//C1 /1 ib 
	{L"ROR",ROR, r_Slash_m32, imm8, NotDef, ROR16, eROR, 0x3},
	//C1 /2 ib 
	{L"RCL",RCL, r_Slash_m32, imm8, NotDef, RCL16, eRCL, 0x3},
	//C1 /3 ib 
	{L"RCR",RCR, r_Slash_m32, imm8, NotDef, RCR16, eRCR, 0x3},
	//C1 /4 ib 
	{L"SHL",SHL, r_Slash_m32, imm8, NotDef, SHL16, eSHL, 0x3},
	//C1 /5 ib 
	{L"SHR",SHR, r_Slash_m32, imm8, NotDef, SHR16, eSHR, 0x3},
	//C1 /6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//C1 /7 ib
	{L"SAR",SAR, r_Slash_m32, imm8, NotDef, SAR16, eSAR, 0x3},
};

SMTableBlock arTable_C6Ext [] = {
	//C6 /0 
	{L"MOV",MOV8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eMOV8, 0x2},
	//C6 /1
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//C6 /2
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//C6 /3
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//C6 /4
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//C6 /5
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//C6 /6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//C6 /7
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock arTable_C7Ext [] = {
	//C7 /0 
	{L"MOV",MOV, r_Slash_m32, imm32, NotDef, MOV16, eMOV, 0x3},
	//C7 /1
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//C7 /2
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//C7 /3
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//C7 /4
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//C7 /5
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//C7 /6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//C7 /7
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock arTable_D0Ext [] = {
	//D0 /0 
	{L"ROL ",ROL8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eROL8, 0x2},
	//D0 /1
	{L"ROR",ROR8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eROR8, 0x2},
	//D0 /2
	{L"RCL",RCL8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eRCL8, 0x2},
	//D0 /3
	{L"RCR",RCR8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eRCR8, 0x2},
	//D0 /4  
	{L"SHL",SHL8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSHL8, 0x2},
	//D0 /5  
	{L"SHR",SHR8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSHR8, 0x2},
	//D0 /6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D0 /7  
	{L"SAR",SAR8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eSAR8, 0x2},
};

SMTableBlock arTable_D1Ext [] = {
	//D1 /0 
	{L"ROL ",ROL, r_Slash_m32, NotDef, NotDef, ROL16, eROL, 0x3},
	//D1 /1 
	{L"ROR ",ROR, r_Slash_m32, NotDef, NotDef, ROR16, eROR, 0x3},
	//D1 /2 
	{L"RCL ",RCL, r_Slash_m32, NotDef, NotDef, RCL16, eRCL, 0x3},
	//D1 /3 
	{L"RCR ",RCR, r_Slash_m32, NotDef, NotDef, RCR16, eRCR, 0x3},
	//D1 /4  
	{L"SHL",SHL, r_Slash_m32, NotDef, NotDef, SHL16, eSHL, 0x3},
	//D1 /5  
	{L"SHR",SHR, r_Slash_m32, NotDef, NotDef, SHR16, eSHR, 0x3},
	//D1 /6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D1 /7  
	{L"SAR",SAR, r_Slash_m32, NotDef, NotDef, SAR16, eSAR, 0x3},
};

SMTableBlock arTable_D2Ext [] = {
	//D2 /0 
	{L"ROL ",ROL8, r_Slash_m8, CL, NotDef, (Pointer)NULL, eROL8, 0x2},
	//D2 /1 
	{L"ROR ",ROR8, r_Slash_m8, CL, NotDef, (Pointer)NULL, eROR8, 0x2},
	//D2 /2 
	{L"RCL ",RCL8, r_Slash_m8, CL, NotDef, (Pointer)NULL, eRCL8, 0x2},
	//D2 /3 
	{L"RCR ",RCR8, r_Slash_m8, CL, NotDef, (Pointer)NULL, eRCR8, 0x2},
	//D2 /4  
	{L"SHL",SHL8, r_Slash_m8, CL, NotDef, (Pointer)NULL, eSHL8, 0x2},
	//D2 /5  
	{L"SHR",SHR8, r_Slash_m8, CL, NotDef, (Pointer)NULL, eSHR8, 0x2},
	//D2 /6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D2 /7  
	{L"SAR",SAR8, r_Slash_m8, CL, NotDef, (Pointer)NULL, eSAR8, 0x2},
};

SMTableBlock arTable_D3Ext [] = {
	//D3 /0 
	{L"ROL ",ROL8, r_Slash_m32, CL, NotDef, (Pointer)NULL, eROL8, 0x3},
	//D3 /1 
	{L"ROR ",ROR8, r_Slash_m32, CL, NotDef, (Pointer)NULL, eROR8, 0x3},
	//D3 /2 
	{L"RCL ",RCL8, r_Slash_m32, CL, NotDef, (Pointer)NULL, eRCL8, 0x3},
	//D3 /3 
	{L"RCR ",RCR8, r_Slash_m32, CL, NotDef, (Pointer)NULL, eRCR8, 0x3},
	//D3 /4  
	{L"SHL",SHL8, r_Slash_m32, CL, NotDef, (Pointer)NULL, eSHL8, 0x3},
	//D3 /5  
	{L"SHR",SHR8, r_Slash_m32, CL, NotDef, (Pointer)NULL, eSHR8, 0x3},
	//D3 /6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D3 /7  
	{L"SAR",SAR8, r_Slash_m32, CL, NotDef, (Pointer)NULL, eSAR8, 0x3},
};

SMTableBlock arTable_D8Ext [] = {
	//D8 /0
	{L"FADD",FADD, m32, NotDef, NotDef, (Pointer)NULL, eFADD, 0x0},
	//D8 /1
	{L"FMUL",FMUL, m32real, NotDef, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//D8 /2 
	{L"FCOM",FCOM, m32real, NotDef, NotDef, (Pointer)NULL, eFCOM, 0x0},
	//D8 /3 
	{L"FCOMP",FCOMP, m32real, NotDef, NotDef, (Pointer)NULL, eFCOMP, 0x0},
	//D8 /4 
	{L"FSUB",FSUB, m32real, NotDef, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//D8 /5 
	{L"FSUBR",FSUBR, m32real, NotDef, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//D8 /6 
	{L"FDIV",FDIV, m32real, NotDef, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//D8 /7 
	{L"FDIVR",FDIVR, m32real, NotDef, NotDef, (Pointer)NULL, eFDIVR, 0x0},
};

SMTableBlock arTable_D8_Abnormal [] = {
	//D8 C0
	{L"FADD",FADD, ST__0__, ST__0__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//D8 C1
	{L"FADD",FADD, ST__0__, ST__1__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//D8 C2
	{L"FADD",FADD, ST__0__, ST__2__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//D8 C3
	{L"FADD",FADD, ST__0__, ST__3__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//D8 C4
	{L"FADD",FADD, ST__0__, ST__4__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//D8 C5
	{L"FADD",FADD, ST__0__, ST__5__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//D8 C6
	{L"FADD",FADD, ST__0__, ST__6__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//D8 C7
	{L"FADD",FADD, ST__0__, ST__7__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//D8 C8
	{L"FMUL",FMUL, ST__0__, ST__8__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//D8 C9
	{L"FMUL",FMUL, ST__0__, ST__9__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//D8 CA
	{L"FMUL",FMUL, ST__0__, ST__10__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//D8 CB
	{L"FMUL",FMUL, ST__0__, ST__11__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//D8 CC
	{L"FMUL",FMUL, ST__0__, ST__12__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//D8 CD
	{L"FMUL",FMUL, ST__0__, ST__13__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//D8 CE
	{L"FMUL",FMUL, ST__0__, ST__14__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//D8 CF
	{L"FMUL",FMUL, ST__0__, ST__15__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//D8 D0
	{L"FCOM",FCOM, ST__0__, NotDef, NotDef, (Pointer)NULL, eFCOM, 0x0},
	//D8 D1
	{L"FCOM",FCOM, ST__1__, NotDef, NotDef, (Pointer)NULL, eFCOM, 0x0},
	//D8 D2
	{L"FCOM",FCOM, ST__2__, NotDef, NotDef, (Pointer)NULL, eFCOM, 0x0},
	//D8 D3
	{L"FCOM",FCOM, ST__3__, NotDef, NotDef, (Pointer)NULL, eFCOM, 0x0},
	//D8 D4
	{L"FCOM",FCOM, ST__4__, NotDef, NotDef, (Pointer)NULL, eFCOM, 0x0},
	//D8 D5
	{L"FCOM",FCOM, ST__5__, NotDef, NotDef, (Pointer)NULL, eFCOM, 0x0},
	//D8 D6
	{L"FCOM",FCOM, ST__6__, NotDef, NotDef, (Pointer)NULL, eFCOM, 0x0},
	//D8 D7
	{L"FCOM",FCOM, ST__7__, NotDef, NotDef, (Pointer)NULL, eFCOM, 0x0},
	//D8 D8
	{L"FCOMP",FCOMP, ST__8__, NotDef, NotDef, (Pointer)NULL, eFCOMP, 0x0},
	//D8 D9
	{L"FCOMP",FCOMP, ST__9__, NotDef, NotDef, (Pointer)NULL, eFCOMP, 0x0},
	//D8 DA
	{L"FCOMP",FCOMP, ST__10__, NotDef, NotDef, (Pointer)NULL, eFCOMP, 0x0},
	//D8 DB
	{L"FCOMP",FCOMP, ST__11__, NotDef, NotDef, (Pointer)NULL, eFCOMP, 0x0},
	//D8 DC
	{L"FCOMP",FCOMP, ST__12__, NotDef, NotDef, (Pointer)NULL, eFCOMP, 0x0},
	//D8 DD
	{L"FCOMP",FCOMP, ST__13__, NotDef, NotDef, (Pointer)NULL, eFCOMP, 0x0},
	//D8 DE
	{L"FCOMP",FCOMP, ST__14__, NotDef, NotDef, (Pointer)NULL, eFCOMP, 0x0},
	//D8 DF
	{L"FCOMP",FCOMP, ST__15__, NotDef, NotDef, (Pointer)NULL, eFCOMP, 0x0},
	//D8 E0
	{L"FSUB",FSUB, ST__0__, ST__0__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//D8 E1
	{L"FSUB",FSUB, ST__0__, ST__1__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//D8 E2
	{L"FSUB",FSUB, ST__0__, ST__2__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//D8 E3
	{L"FSUB",FSUB, ST__0__, ST__3__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//D8 E4
	{L"FSUB",FSUB, ST__0__, ST__4__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//D8 E5
	{L"FSUB",FSUB, ST__0__, ST__5__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//D8 E6
	{L"FSUB",FSUB, ST__0__, ST__6__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//D8 E7
	{L"FSUB",FSUB, ST__0__, ST__7__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//D8 E8
	{L"FSUBR",FSUBR, ST__0__, ST__8__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//D8 E9
	{L"FSUBR",FSUBR, ST__0__, ST__9__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//D8 EA
	{L"FSUBR",FSUBR, ST__0__, ST__10__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//D8 EB
	{L"FSUBR",FSUBR, ST__0__, ST__11__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//D8 EC
	{L"FSUBR",FSUBR, ST__0__, ST__12__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//D8 ED
	{L"FSUBR",FSUBR, ST__0__, ST__13__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//D8 EE
	{L"FSUBR",FSUBR, ST__0__, ST__14__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//D8 EF
	{L"FSUBR",FSUBR, ST__0__, ST__15__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//D8 F0
	{L"FDIV",FDIV, ST__0__, ST__0__, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//D8 F1
	{L"FDIV",FDIV, ST__0__, ST__1__, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//D8 F2
	{L"FDIV",FDIV, ST__0__, ST__2__, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//D8 F3
	{L"FDIV",FDIV, ST__0__, ST__3__, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//D8 F4
	{L"FDIV",FDIV, ST__0__, ST__4__, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//D8 F5
	{L"FDIV",FDIV, ST__0__, ST__5__, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//D8 F6
	{L"FDIV",FDIV, ST__0__, ST__6__, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//D8 F7
	{L"FDIV",FDIV, ST__0__, ST__7__, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//D8 F8
	{L"FDIVR",FDIVR, ST__0__, ST__8__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
	//D8 F9
	{L"FDIVR",FDIVR, ST__0__, ST__9__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
	//D8 FA
	{L"FDIVR",FDIVR, ST__0__, ST__10__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
	//D8 FB
	{L"FDIVR",FDIVR, ST__0__, ST__11__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
	//D8 FC
	{L"FDIVR",FDIVR, ST__0__, ST__12__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
	//D8 FD
	{L"FDIVR",FDIVR, ST__0__, ST__13__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
	//D8 FE
	{L"FDIVR",FDIVR, ST__0__, ST__14__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
	//D8 FF
	{L"FDIVR",FDIVR, ST__0__, ST__15__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
};

SMTableBlock arTable_D9Ext [] = {
	//D9 /0  
	{L"FLD",FLD, m32real, NotDef, NotDef, (Pointer)NULL, eFLD, 0x0},
	//D9 /1
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 /2 
	{L"FST",FST, m32real, NotDef, NotDef, (Pointer)NULL, eFST, 0x0},
	//D9 /3 
	{L"FSTP",FSTP, m32real, NotDef, NotDef, (Pointer)NULL, eFSTP, 0x0},
	//D9 /4 
	{L"FLDENV",FLDENV, m14_Slash_28byte, NotDef, NotDef, (Pointer)NULL, eFLDENV, 0x0},
	//D9 /5 
	{L"FLDCW",FLDCW, m2byte, NotDef, NotDef, (Pointer)NULL, eFLDCW, 0x0},
	//D9 /6 
	{L"FNSTENV ",FNSTENV, m14_Slash_28byte, NotDef, NotDef, (Pointer)NULL, eFNSTENV, 0x0},
	//D9 /7 
	{L"FNSTCW",FNSTCW, m2byte, NotDef, NotDef, (Pointer)NULL, eFNSTCW, 0x0},
};

SMTableBlock arTable_D9_Abnormal [] = {
	//D9 C0
	{L"FLD",FLD, ST__0__, NotDef, NotDef, (Pointer)NULL, eFLD, 0x0},
	//D9 C1
	{L"FLD",FLD, ST__1__, NotDef, NotDef, (Pointer)NULL, eFLD, 0x0},
	//D9 C2
	{L"FLD",FLD, ST__2__, NotDef, NotDef, (Pointer)NULL, eFLD, 0x0},
	//D9 C3
	{L"FLD",FLD, ST__3__, NotDef, NotDef, (Pointer)NULL, eFLD, 0x0},
	//D9 C4
	{L"FLD",FLD, ST__4__, NotDef, NotDef, (Pointer)NULL, eFLD, 0x0},
	//D9 C5
	{L"FLD",FLD, ST__5__, NotDef, NotDef, (Pointer)NULL, eFLD, 0x0},
	//D9 C6
	{L"FLD",FLD, ST__6__, NotDef, NotDef, (Pointer)NULL, eFLD, 0x0},
	//D9 C7
	{L"FLD",FLD, ST__7__, NotDef, NotDef, (Pointer)NULL, eFLD, 0x0},
	//D9 C8
	{L"FXCH",FXCH, ST__8__, NotDef, NotDef, (Pointer)NULL, eFXCH, 0x0},
	//D9 C9
	{L"FXCH",FXCH, ST__9__, NotDef, NotDef, (Pointer)NULL, eFXCH, 0x0},
	//D9 CA
	{L"FXCH",FXCH, ST__10__, NotDef, NotDef, (Pointer)NULL, eFXCH, 0x0},
	//D9 CB
	{L"FXCH",FXCH, ST__11__, NotDef, NotDef, (Pointer)NULL, eFXCH, 0x0},
	//D9 CC
	{L"FXCH",FXCH, ST__12__, NotDef, NotDef, (Pointer)NULL, eFXCH, 0x0},
	//D9 CD
	{L"FXCH",FXCH, ST__13__, NotDef, NotDef, (Pointer)NULL, eFXCH, 0x0},
	//D9 CE
	{L"FXCH",FXCH, ST__14__, NotDef, NotDef, (Pointer)NULL, eFXCH, 0x0},
	//D9 CF
	{L"FXCH",FXCH, ST__15__, NotDef, NotDef, (Pointer)NULL, eFXCH, 0x0},
	//D9 D0  
	{L"FNOP",FNOP, NotDef, NotDef, NotDef, (Pointer)NULL, eFNOP, 0x0},
	//D9 D1
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 D2
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 D3
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 D4
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 D5
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 D6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 D7
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 D8
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 D9
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 DA
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 DB
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 DC
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 DD
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 DE
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 DF
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 E0  
	{L"FCHS",FCHS, NotDef, NotDef, NotDef, (Pointer)NULL, eFCHS, 0x0},
	//D9 E1  
	{L"FABS",FABS, NotDef, NotDef, NotDef, (Pointer)NULL, eFABS, 0x0},
	//D9 E2
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 E3
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 E4  
	{L"FTST",FTST, NotDef, NotDef, NotDef, (Pointer)NULL, eFTST, 0x0},
	//D9 E5  
	{L"FXAM",FXAM, NotDef, NotDef, NotDef, (Pointer)NULL, eFXAM, 0x0},
	//D9 E6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 E7
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 E8  
	{L"FLD1",FLD1, NotDef, NotDef, NotDef, (Pointer)NULL, eFLD1, 0x0},
	//D9 E9  
	{L"FLDL2T",FLDL2T, NotDef, NotDef, NotDef, (Pointer)NULL, eFLDL2T, 0x0},
	//D9 EA  
	{L"FLDL2E",FLDL2E, NotDef, NotDef, NotDef, (Pointer)NULL, eFLDL2E, 0x0},
	//D9 EB  
	{L"FLDPI",FLDPI, NotDef, NotDef, NotDef, (Pointer)NULL, eFLDPI, 0x0},
	//D9 EC  
	{L"FLDLG2",FLDLG2, NotDef, NotDef, NotDef, (Pointer)NULL, eFLDLG2, 0x0},
	//D9 ED  
	{L"FLDLN2",FLDLN2, NotDef, NotDef, NotDef, (Pointer)NULL, eFLDLN2, 0x0},
	//D9 EE  
	{L"FLDZ",FLDZ, NotDef, NotDef, NotDef, (Pointer)NULL, eFLDZ, 0x0},
	//D9 EF
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//D9 F0  
	{L"F2XM1",F2XM1, NotDef, NotDef, NotDef, (Pointer)NULL, eF2XM1, 0x0},
	//D9 F1  
	{L"FYL2X",FYL2X, NotDef, NotDef, NotDef, (Pointer)NULL, eFYL2X, 0x0},
	//D9 F2  
	{L"FPTAN",FPTAN, NotDef, NotDef, NotDef, (Pointer)NULL, eFPTAN, 0x0},
	//D9 F3  
	{L"FPATAN",FPATAN, NotDef, NotDef, NotDef, (Pointer)NULL, eFPATAN, 0x0},
	//D9 F4  
	{L"FXTRACT",FXTRACT, NotDef, NotDef, NotDef, (Pointer)NULL, eFXTRACT, 0x0},
	//D9 F5  
	{L"FPREM1",FPREM1, NotDef, NotDef, NotDef, (Pointer)NULL, eFPREM1, 0x0},
	//D9 F6  
	{L"FDECSTP",FDECSTP, NotDef, NotDef, NotDef, (Pointer)NULL, eFDECSTP, 0x0},
	//D9 F7  
	{L"FINCSTP",FINCSTP, NotDef, NotDef, NotDef, (Pointer)NULL, eFINCSTP, 0x0},
	//D9 F8  
	{L"FPREM",FPREM, NotDef, NotDef, NotDef, (Pointer)NULL, eFPREM, 0x0},
	//D9 F9  
	{L"FYL2XP1",FYL2XP1, NotDef, NotDef, NotDef, (Pointer)NULL, eFYL2XP1, 0x0},
	//D9 FA  
	{L"FSQRT",FSQRT, NotDef, NotDef, NotDef, (Pointer)NULL, eFSQRT, 0x0},
	//D9 FB  
	{L"FSINCOS",FSINCOS, NotDef, NotDef, NotDef, (Pointer)NULL, eFSINCOS, 0x0},
	//D9 FC  
	{L"FRNDINT",FRNDINT, NotDef, NotDef, NotDef, (Pointer)NULL, eFRNDINT, 0x0},
	//D9 FD  
	{L"FSCALE",FSCALE, NotDef, NotDef, NotDef, (Pointer)NULL, eFSCALE, 0x0},
	//D9 FE  
	{L"FSIN",FSIN, NotDef, NotDef, NotDef, (Pointer)NULL, eFSIN, 0x0},
	//D9 FF  
	{L"FCOS",FCOS, NotDef, NotDef, NotDef, (Pointer)NULL, eFCOS, 0x0},
};

SMTableBlock arTable_DAExt [] = {
	//DA /0 
	{L"FIADD",FIADD, m32int, NotDef, NotDef, (Pointer)NULL, eFIADD, 0x0},
	//DA /1  
	{L"FIMUL",FIMUL, m32int, NotDef, NotDef, (Pointer)NULL, eFIMUL, 0x0},
	//DA /2   
	{L"FICOM",FICOM, m32int, NotDef, NotDef, (Pointer)NULL, eFICOM, 0x0},
	//DA /3   
	{L"FICOMP",FICOMP, m32int, NotDef, NotDef, (Pointer)NULL, eFICOMP, 0x0},
	//DA /4   
	{L"FISUB",FISUB, m32int, NotDef, NotDef, (Pointer)NULL, eFISUB, 0x0},
	//DA /5   
	{L"FISUBR",FISUBR, m32int, NotDef, NotDef, (Pointer)NULL, eFISUBR, 0x0},
	//DA /6   
	{L"FIDIV",FIDIV, m32int, NotDef, NotDef, (Pointer)NULL, eFIDIV, 0x0},
	//DA /7   
	{L"FIDIVR",FIDIVR, m32int, NotDef, NotDef, (Pointer)NULL, eFIDIVR, 0x0},
};

SMTableBlock arTable_DA_Abnormal [] = {
	//DA C0
	{L"FCMOVB",FCMOVB, ST__0__, ST__0__, NotDef, (Pointer)NULL, eFCMOVB, 0x0},
	//DA C1
	{L"FCMOVB",FCMOVB, ST__0__, ST__1__, NotDef, (Pointer)NULL, eFCMOVB, 0x0},
	//DA C2
	{L"FCMOVB",FCMOVB, ST__0__, ST__2__, NotDef, (Pointer)NULL, eFCMOVB, 0x0},
	//DA C3
	{L"FCMOVB",FCMOVB, ST__0__, ST__3__, NotDef, (Pointer)NULL, eFCMOVB, 0x0},
	//DA C4
	{L"FCMOVB",FCMOVB, ST__0__, ST__4__, NotDef, (Pointer)NULL, eFCMOVB, 0x0},
	//DA C5
	{L"FCMOVB",FCMOVB, ST__0__, ST__5__, NotDef, (Pointer)NULL, eFCMOVB, 0x0},
	//DA C6
	{L"FCMOVB",FCMOVB, ST__0__, ST__6__, NotDef, (Pointer)NULL, eFCMOVB, 0x0},
	//DA C7
	{L"FCMOVB",FCMOVB, ST__0__, ST__7__, NotDef, (Pointer)NULL, eFCMOVB, 0x0},
	//DA C8
	{L"FCMOVE",FCMOVE, ST__0__, ST__8__, NotDef, (Pointer)NULL, eFCMOVE, 0x0},
	//DA C9
	{L"FCMOVE",FCMOVE, ST__0__, ST__9__, NotDef, (Pointer)NULL, eFCMOVE, 0x0},
	//DA CA
	{L"FCMOVE",FCMOVE, ST__0__, ST__10__, NotDef, (Pointer)NULL, eFCMOVE, 0x0},
	//DA CB
	{L"FCMOVE",FCMOVE, ST__0__, ST__11__, NotDef, (Pointer)NULL, eFCMOVE, 0x0},
	//DA CC
	{L"FCMOVE",FCMOVE, ST__0__, ST__12__, NotDef, (Pointer)NULL, eFCMOVE, 0x0},
	//DA CD
	{L"FCMOVE",FCMOVE, ST__0__, ST__13__, NotDef, (Pointer)NULL, eFCMOVE, 0x0},
	//DA CE
	{L"FCMOVE",FCMOVE, ST__0__, ST__14__, NotDef, (Pointer)NULL, eFCMOVE, 0x0},
	//DA CF
	{L"FCMOVE",FCMOVE, ST__0__, ST__15__, NotDef, (Pointer)NULL, eFCMOVE, 0x0},
	//DA D0
	{L"FCMOVBE",FCMOVBE, ST__0__, ST__0__, NotDef, (Pointer)NULL, eFCMOVBE, 0x0},
	//DA D1
	{L"FCMOVBE",FCMOVBE, ST__0__, ST__1__, NotDef, (Pointer)NULL, eFCMOVBE, 0x0},
	//DA D2
	{L"FCMOVBE",FCMOVBE, ST__0__, ST__2__, NotDef, (Pointer)NULL, eFCMOVBE, 0x0},
	//DA D3
	{L"FCMOVBE",FCMOVBE, ST__0__, ST__3__, NotDef, (Pointer)NULL, eFCMOVBE, 0x0},
	//DA D4
	{L"FCMOVBE",FCMOVBE, ST__0__, ST__4__, NotDef, (Pointer)NULL, eFCMOVBE, 0x0},
	//DA D5
	{L"FCMOVBE",FCMOVBE, ST__0__, ST__5__, NotDef, (Pointer)NULL, eFCMOVBE, 0x0},
	//DA D6
	{L"FCMOVBE",FCMOVBE, ST__0__, ST__6__, NotDef, (Pointer)NULL, eFCMOVBE, 0x0},
	//DA D7
	{L"FCMOVBE",FCMOVBE, ST__0__, ST__7__, NotDef, (Pointer)NULL, eFCMOVBE, 0x0},
	//DA D8
	{L"FCMOVU",FCMOVU, ST__0__, ST__8__, NotDef, (Pointer)NULL, eFCMOVU, 0x0},
	//DA D9
	{L"FCMOVU",FCMOVU, ST__0__, ST__9__, NotDef, (Pointer)NULL, eFCMOVU, 0x0},
	//DA DA
	{L"FCMOVU",FCMOVU, ST__0__, ST__10__, NotDef, (Pointer)NULL, eFCMOVU, 0x0},
	//DA DB
	{L"FCMOVU",FCMOVU, ST__0__, ST__11__, NotDef, (Pointer)NULL, eFCMOVU, 0x0},
	//DA DC
	{L"FCMOVU",FCMOVU, ST__0__, ST__12__, NotDef, (Pointer)NULL, eFCMOVU, 0x0},
	//DA DD
	{L"FCMOVU",FCMOVU, ST__0__, ST__13__, NotDef, (Pointer)NULL, eFCMOVU, 0x0},
	//DA DE
	{L"FCMOVU",FCMOVU, ST__0__, ST__14__, NotDef, (Pointer)NULL, eFCMOVU, 0x0},
	//DA DF
	{L"FCMOVU",FCMOVU, ST__0__, ST__15__, NotDef, (Pointer)NULL, eFCMOVU, 0x0},
	//DA E0
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA E1
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA E2
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA E3
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA E4
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA E5
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA E6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA E7
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA E8
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA E9
	{L"FUCOMPP",FUCOMPP, NotDef, NotDef, NotDef, (Pointer)NULL, eFUCOMPP, 0x0},
	//DA EA
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA EB
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA EC
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA ED
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA EE
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA EF
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA F0
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA F1
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA F2
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA F3
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA F4
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA F5
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA F6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA F7
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA F8
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA F9
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA FA
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA FB
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA FC
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA FD
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA FE
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DA FF
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock arTable_DBExt [] = {
	//DB /0 
	{L"FILD",FILD, m32int, NotDef, NotDef, (Pointer)NULL, eFILD, 0x0},
	//DB /1
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB /2 
	{L"FIST",FIST, m32int, NotDef, NotDef, (Pointer)NULL, eFIST, 0x0},
	//DB /3 
	{L"FISTP",FISTP, m32int, NotDef, NotDef, (Pointer)NULL, eFISTP, 0x0},
	//DB /4
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB /5 
	{L"FLD",FLD8, m80real, NotDef, NotDef, (Pointer)NULL, eFLD8, 0x0},
	//DB /6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB /7 
	{L"FSTP",FSTP8, m80real, NotDef, NotDef, (Pointer)NULL, eFSTP8, 0x0},
};

SMTableBlock arTable_DB_Abnormal [] = {
	//DB C0
	{L"FCMOVNB",FCMOVNB, ST__0__, ST__0__, NotDef, (Pointer)NULL, eFCMOVNB, 0x0},
	//DB C1
	{L"FCMOVNB",FCMOVNB, ST__0__, ST__1__, NotDef, (Pointer)NULL, eFCMOVNB, 0x0},
	//DB C2
	{L"FCMOVNB",FCMOVNB, ST__0__, ST__2__, NotDef, (Pointer)NULL, eFCMOVNB, 0x0},
	//DB C3
	{L"FCMOVNB",FCMOVNB, ST__0__, ST__3__, NotDef, (Pointer)NULL, eFCMOVNB, 0x0},
	//DB C4
	{L"FCMOVNB",FCMOVNB, ST__0__, ST__4__, NotDef, (Pointer)NULL, eFCMOVNB, 0x0},
	//DB C5
	{L"FCMOVNB",FCMOVNB, ST__0__, ST__5__, NotDef, (Pointer)NULL, eFCMOVNB, 0x0},
	//DB C6
	{L"FCMOVNB",FCMOVNB, ST__0__, ST__6__, NotDef, (Pointer)NULL, eFCMOVNB, 0x0},
	//DB C7
	{L"FCMOVNB",FCMOVNB, ST__0__, ST__7__, NotDef, (Pointer)NULL, eFCMOVNB, 0x0},
	//DB C8
	{L"FCMOVNE",FCMOVNE, ST__0__, ST__8__, NotDef, (Pointer)NULL, eFCMOVNE, 0x0},
	//DB C9
	{L"FCMOVNE",FCMOVNE, ST__0__, ST__9__, NotDef, (Pointer)NULL, eFCMOVNE, 0x0},
	//DB CA
	{L"FCMOVNE",FCMOVNE, ST__0__, ST__10__, NotDef, (Pointer)NULL, eFCMOVNE, 0x0},
	//DB CB
	{L"FCMOVNE",FCMOVNE, ST__0__, ST__11__, NotDef, (Pointer)NULL, eFCMOVNE, 0x0},
	//DB CC
	{L"FCMOVNE",FCMOVNE, ST__0__, ST__12__, NotDef, (Pointer)NULL, eFCMOVNE, 0x0},
	//DB CD
	{L"FCMOVNE",FCMOVNE, ST__0__, ST__13__, NotDef, (Pointer)NULL, eFCMOVNE, 0x0},
	//DB CE
	{L"FCMOVNE",FCMOVNE, ST__0__, ST__14__, NotDef, (Pointer)NULL, eFCMOVNE, 0x0},
	//DB CF
	{L"FCMOVNE",FCMOVNE, ST__0__, ST__15__, NotDef, (Pointer)NULL, eFCMOVNE, 0x0},
	//DB D0
	{L"FCMOVNBE",FCMOVNBE, ST__0__, ST__0__, NotDef, (Pointer)NULL, eFCMOVNBE, 0x0},
	//DB D1
	{L"FCMOVNBE",FCMOVNBE, ST__0__, ST__1__, NotDef, (Pointer)NULL, eFCMOVNBE, 0x0},
	//DB D2
	{L"FCMOVNBE",FCMOVNBE, ST__0__, ST__2__, NotDef, (Pointer)NULL, eFCMOVNBE, 0x0},
	//DB D3
	{L"FCMOVNBE",FCMOVNBE, ST__0__, ST__3__, NotDef, (Pointer)NULL, eFCMOVNBE, 0x0},
	//DB D4
	{L"FCMOVNBE",FCMOVNBE, ST__0__, ST__4__, NotDef, (Pointer)NULL, eFCMOVNBE, 0x0},
	//DB D5
	{L"FCMOVNBE",FCMOVNBE, ST__0__, ST__5__, NotDef, (Pointer)NULL, eFCMOVNBE, 0x0},
	//DB D6
	{L"FCMOVNBE",FCMOVNBE, ST__0__, ST__6__, NotDef, (Pointer)NULL, eFCMOVNBE, 0x0},
	//DB D7
	{L"FCMOVNBE",FCMOVNBE, ST__0__, ST__7__, NotDef, (Pointer)NULL, eFCMOVNBE, 0x0},
	//DB D8
	{L"FCMOVNU",FCMOVNU, ST__0__, ST__8__, NotDef, (Pointer)NULL, eFCMOVNU, 0x0},
	//DB D9
	{L"FCMOVNU",FCMOVNU, ST__0__, ST__9__, NotDef, (Pointer)NULL, eFCMOVNU, 0x0},
	//DB DA
	{L"FCMOVNU",FCMOVNU, ST__0__, ST__10__, NotDef, (Pointer)NULL, eFCMOVNU, 0x0},
	//DB DB
	{L"FCMOVNU",FCMOVNU, ST__0__, ST__11__, NotDef, (Pointer)NULL, eFCMOVNU, 0x0},
	//DB DC
	{L"FCMOVNU",FCMOVNU, ST__0__, ST__12__, NotDef, (Pointer)NULL, eFCMOVNU, 0x0},
	//DB DD
	{L"FCMOVNU",FCMOVNU, ST__0__, ST__13__, NotDef, (Pointer)NULL, eFCMOVNU, 0x0},
	//DB DE
	{L"FCMOVNU",FCMOVNU, ST__0__, ST__14__, NotDef, (Pointer)NULL, eFCMOVNU, 0x0},
	//DB DF
	{L"FCMOVNU",FCMOVNU, ST__0__, ST__15__, NotDef, (Pointer)NULL, eFCMOVNU, 0x0},
	//DB E0
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB E1
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB E2   
	{L"FNCLEX",FNCLEX, NotDef, NotDef, NotDef, (Pointer)NULL, eFNCLEX, 0x0},
	//DB E3    
	{L"FNINIT",FNINIT, NotDef, NotDef, NotDef, (Pointer)NULL, eFNINIT, 0x0},
	//DB E4
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB E5
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB E6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB E7
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB E8
	{L"FUCOMI",FUCOMI, ST, ST__8__, NotDef, (Pointer)NULL, eFUCOMI, 0x0},
	//DB E9
	{L"FUCOMI",FUCOMI, ST, ST__9__, NotDef, (Pointer)NULL, eFUCOMI, 0x0},
	//DB EA
	{L"FUCOMI",FUCOMI, ST, ST__10__, NotDef, (Pointer)NULL, eFUCOMI, 0x0},
	//DB EB
	{L"FUCOMI",FUCOMI, ST, ST__11__, NotDef, (Pointer)NULL, eFUCOMI, 0x0},
	//DB EC
	{L"FUCOMI",FUCOMI, ST, ST__12__, NotDef, (Pointer)NULL, eFUCOMI, 0x0},
	//DB ED
	{L"FUCOMI",FUCOMI, ST, ST__13__, NotDef, (Pointer)NULL, eFUCOMI, 0x0},
	//DB EE
	{L"FUCOMI",FUCOMI, ST, ST__14__, NotDef, (Pointer)NULL, eFUCOMI, 0x0},
	//DB EF
	{L"FUCOMI",FUCOMI, ST, ST__15__, NotDef, (Pointer)NULL, eFUCOMI, 0x0},
	//DB F0
	{L"FCOMI",FCOMI, ST, ST__0__, NotDef, (Pointer)NULL, eFCOMI, 0x0},
	//DB F1
	{L"FCOMI",FCOMI, ST, ST__1__, NotDef, (Pointer)NULL, eFCOMI, 0x0},
	//DB F2
	{L"FCOMI",FCOMI, ST, ST__2__, NotDef, (Pointer)NULL, eFCOMI, 0x0},
	//DB F3
	{L"FCOMI",FCOMI, ST, ST__3__, NotDef, (Pointer)NULL, eFCOMI, 0x0},
	//DB F4
	{L"FCOMI",FCOMI, ST, ST__4__, NotDef, (Pointer)NULL, eFCOMI, 0x0},
	//DB F5
	{L"FCOMI",FCOMI, ST, ST__5__, NotDef, (Pointer)NULL, eFCOMI, 0x0},
	//DB F6
	{L"FCOMI",FCOMI, ST, ST__6__, NotDef, (Pointer)NULL, eFCOMI, 0x0},
	//DB F7
	{L"FCOMI",FCOMI, ST, ST__7__, NotDef, (Pointer)NULL, eFCOMI, 0x0},
	//DB F8
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB F9
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB FA
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB FB
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB FC
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB FD
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB FE
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DB FF
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock arTable_DCExt [] = {
	//DC /0    
	{L"FADD",FADD, m64real, NotDef, NotDef, (Pointer)NULL, eFADD, 0x0},
	//DC /1    
	{L"FMUL",FMUL, m64real, NotDef, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//DC /2    
	{L"FCOM",FCOM, m64real, NotDef, NotDef, (Pointer)NULL, eFCOM, 0x0},
	//DC /3    
	{L"FCOMP",FCOMP, m64real, NotDef, NotDef, (Pointer)NULL, eFCOMP, 0x0},
	//DC /4    
	{L"FSUB",FSUB, m64real, NotDef, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//DC /5    
	{L"FSUBR",FSUBR, m64real, NotDef, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//DC /6    
	{L"FDIV",FDIV, m64real, NotDef, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//DC /7    
	{L"FDIVR",FDIVR, m64real, NotDef, NotDef, (Pointer)NULL, eFDIVR, 0x0},
};

SMTableBlock arTable_DC_Abnormal [] = {
	//DC C0
	{L"FADD",FADD, ST__0__, ST__0__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//DC C1
	{L"FADD",FADD, ST__1__, ST__0__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//DC C2
	{L"FADD",FADD, ST__2__, ST__0__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//DC C3
	{L"FADD",FADD, ST__3__, ST__0__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//DC C4
	{L"FADD",FADD, ST__4__, ST__0__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//DC C5
	{L"FADD",FADD, ST__5__, ST__0__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//DC C6
	{L"FADD",FADD, ST__6__, ST__0__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//DC C7
	{L"FADD",FADD, ST__7__, ST__0__, NotDef, (Pointer)NULL, eFADD, 0x0},
	//DC C8
	{L"FMUL",FMUL, ST__8__, ST__0__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//DC C9
	{L"FMUL",FMUL, ST__9__, ST__0__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//DC CA
	{L"FMUL",FMUL, ST__10__, ST__0__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//DC CB
	{L"FMUL",FMUL, ST__11__, ST__0__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//DC CC
	{L"FMUL",FMUL, ST__12__, ST__0__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//DC CD
	{L"FMUL",FMUL, ST__13__, ST__0__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//DC CE
	{L"FMUL",FMUL, ST__14__, ST__0__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//DC CF
	{L"FMUL",FMUL, ST__15__, ST__0__, NotDef, (Pointer)NULL, eFMUL, 0x0},
	//DC D0
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC D1
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC D2
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC D3
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC D4
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC D5
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC D6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC D7
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC D8
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC D9
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC DA
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC DB
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC DC
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC DD
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC DE
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC DF
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DC E0
	{L"FSUBR",FSUBR, ST__0__, ST__0__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//DC E1
	{L"FSUBR",FSUBR, ST__1__, ST__0__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//DC E2
	{L"FSUBR",FSUBR, ST__2__, ST__0__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//DC E3
	{L"FSUBR",FSUBR, ST__3__, ST__0__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//DC E4
	{L"FSUBR",FSUBR, ST__4__, ST__0__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//DC E5
	{L"FSUBR",FSUBR, ST__5__, ST__0__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//DC E6
	{L"FSUBR",FSUBR, ST__6__, ST__0__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//DC E7
	{L"FSUBR",FSUBR, ST__7__, ST__0__, NotDef, (Pointer)NULL, eFSUBR, 0x0},
	//DC E8
	{L"FSUB",FSUB, ST__8__, ST__0__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//DC E9
	{L"FSUB",FSUB, ST__9__, ST__0__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//DC EA
	{L"FSUB",FSUB, ST__10__, ST__0__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//DC EB
	{L"FSUB",FSUB, ST__11__, ST__0__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//DC EC
	{L"FSUB",FSUB, ST__12__, ST__0__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//DC ED
	{L"FSUB",FSUB, ST__13__, ST__0__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//DC EE
	{L"FSUB",FSUB, ST__14__, ST__0__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//DC EF
	{L"FSUB",FSUB, ST__15__, ST__0__, NotDef, (Pointer)NULL, eFSUB, 0x0},
	//DC F0
	{L"FDIVR",FDIVR, ST__0__, ST__0__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
	//DC F1
	{L"FDIVR",FDIVR, ST__1__, ST__0__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
	//DC F2
	{L"FDIVR",FDIVR, ST__2__, ST__0__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
	//DC F3
	{L"FDIVR",FDIVR, ST__3__, ST__0__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
	//DC F4
	{L"FDIVR",FDIVR, ST__4__, ST__0__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
	//DC F5
	{L"FDIVR",FDIVR, ST__5__, ST__0__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
	//DC F6
	{L"FDIVR",FDIVR, ST__6__, ST__0__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
	//DC F7
	{L"FDIVR",FDIVR, ST__7__, ST__0__, NotDef, (Pointer)NULL, eFDIVR, 0x0},
	//DC F8
	{L"FDIV",FDIV, ST__8__, ST__0__, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//DC F9
	{L"FDIV",FDIV, ST__9__, ST__0__, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//DC FA
	{L"FDIV",FDIV, ST__10__, ST__0__, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//DC FB
	{L"FDIV",FDIV, ST__11__, ST__0__, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//DC FC
	{L"FDIV",FDIV, ST__12__, ST__0__, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//DC FD
	{L"FDIV",FDIV, ST__13__, ST__0__, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//DC FE
	{L"FDIV",FDIV, ST__14__, ST__0__, NotDef, (Pointer)NULL, eFDIV, 0x0},
	//DC FF
	{L"FDIV",FDIV, ST__15__, ST__0__, NotDef, (Pointer)NULL, eFDIV, 0x0},
};

SMTableBlock arTable_DDExt [] = {
	//DD /0    
	{L"FLD",FLD, m64real, NotDef, NotDef, (Pointer)NULL, eFLD, 0x0},
	//DD /1
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD /2    
	{L"FST",FST, m64real, NotDef, NotDef, (Pointer)NULL, eFST, 0x0},
	//DD /3    
	{L"FSTP",FSTP, m64real, NotDef, NotDef, (Pointer)NULL, eFSTP, 0x0},
	//DD /4    
	{L"FRSTOR",FRSTOR, m94_Slash_108byte, NotDef, NotDef, (Pointer)NULL, eFRSTOR, 0x0},
	//DD /5
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD /6    
	{L"FNSAVE",FNSAVE, m94_Slash_108byte, NotDef, NotDef, (Pointer)NULL, eFNSAVE, 0x0},
	//DD /7    
	{L"FNSTSW",FNSTSW, m2byte, NotDef, NotDef, (Pointer)NULL, eFNSTSW, 0x0},
};

SMTableBlock arTable_DD_Abnormal [] = {
	//DD C0
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD C1
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD C2
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD C3
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD C4
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD C5
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD C6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD C7
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD C8
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD C9
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD CA
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD CB
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD CC
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD CD
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD CE
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD CF
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD D0
	{L"FST",FST, ST__0__, NotDef, NotDef, (Pointer)NULL, eFST, 0x0},
	//DD D1
	{L"FST",FST, ST__1__, NotDef, NotDef, (Pointer)NULL, eFST, 0x0},
	//DD D2
	{L"FST",FST, ST__2__, NotDef, NotDef, (Pointer)NULL, eFST, 0x0},
	//DD D3
	{L"FST",FST, ST__3__, NotDef, NotDef, (Pointer)NULL, eFST, 0x0},
	//DD D4
	{L"FST",FST, ST__4__, NotDef, NotDef, (Pointer)NULL, eFST, 0x0},
	//DD D5
	{L"FST",FST, ST__5__, NotDef, NotDef, (Pointer)NULL, eFST, 0x0},
	//DD D6
	{L"FST",FST, ST__6__, NotDef, NotDef, (Pointer)NULL, eFST, 0x0},
	//DD D7
	{L"FST",FST, ST__7__, NotDef, NotDef, (Pointer)NULL, eFST, 0x0},
	//DD D8
	{L"FSTP",FSTP, ST__8__, NotDef, NotDef, (Pointer)NULL, eFSTP, 0x0},
	//DD D9
	{L"FSTP",FSTP, ST__9__, NotDef, NotDef, (Pointer)NULL, eFSTP, 0x0},
	//DD DA
	{L"FSTP",FSTP, ST__10__, NotDef, NotDef, (Pointer)NULL, eFSTP, 0x0},
	//DD DB
	{L"FSTP",FSTP, ST__11__, NotDef, NotDef, (Pointer)NULL, eFSTP, 0x0},
	//DD DC
	{L"FSTP",FSTP, ST__12__, NotDef, NotDef, (Pointer)NULL, eFSTP, 0x0},
	//DD DD
	{L"FSTP",FSTP, ST__13__, NotDef, NotDef, (Pointer)NULL, eFSTP, 0x0},
	//DD DE
	{L"FSTP",FSTP, ST__14__, NotDef, NotDef, (Pointer)NULL, eFSTP, 0x0},
	//DD DF
	{L"FSTP",FSTP, ST__15__, NotDef, NotDef, (Pointer)NULL, eFSTP, 0x0},
	//DD E0
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD E1    
	{L"FUCOM",FUCOM, NotDef, NotDef, NotDef, (Pointer)NULL, eFUCOM, 0x0},
	//DD E2
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD E3
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD E4
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD E5
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD E6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD E7
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD E8
	{L"FUCOMP",FUCOMP, ST__8__, NotDef, NotDef, (Pointer)NULL, eFUCOMP, 0x0},
	//DD E9
	{L"FUCOMP",FUCOMP, ST__9__, NotDef, NotDef, (Pointer)NULL, eFUCOMP, 0x0},
	//DD EA
	{L"FUCOMP",FUCOMP, ST__10__, NotDef, NotDef, (Pointer)NULL, eFUCOMP, 0x0},
	//DD EB
	{L"FUCOMP",FUCOMP, ST__11__, NotDef, NotDef, (Pointer)NULL, eFUCOMP, 0x0},
	//DD EC
	{L"FUCOMP",FUCOMP, ST__12__, NotDef, NotDef, (Pointer)NULL, eFUCOMP, 0x0},
	//DD ED
	{L"FUCOMP",FUCOMP, ST__13__, NotDef, NotDef, (Pointer)NULL, eFUCOMP, 0x0},
	//DD EE
	{L"FUCOMP",FUCOMP, ST__14__, NotDef, NotDef, (Pointer)NULL, eFUCOMP, 0x0},
	//DD EF
	{L"FUCOMP",FUCOMP, ST__15__, NotDef, NotDef, (Pointer)NULL, eFUCOMP, 0x0},
	//DD F0
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD F1
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD F2
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD F3
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD F4
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD F5
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD F6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD F7
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD F8
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD F9
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD FA
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD FB
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD FC
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD FD
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD FE
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DD FF
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock arTable_DEExt [] = {
	//DE /0    
	{L"FIADD",FIADD, m16int, NotDef, NotDef, (Pointer)NULL, eFIADD, 0x0},
	//DE /1    
	{L"FIMUL",FIMUL, m16int, NotDef, NotDef, (Pointer)NULL, eFIMUL, 0x0},
	//DE /2    
	{L"FICOM",FICOM, m16int, NotDef, NotDef, (Pointer)NULL, eFICOM, 0x0},
	//DE /3    
	{L"FICOMP",FICOMP, m16int, NotDef, NotDef, (Pointer)NULL, eFICOMP, 0x0},
	//DE /4    
	{L"FISUB",FISUB, m16int, NotDef, NotDef, (Pointer)NULL, eFISUB, 0x0},
	//DE /5    
	{L"FISUBR",FISUBR, m16int, NotDef, NotDef, (Pointer)NULL, eFISUBR, 0x0},
	//DE /6    
	{L"FIDIV",FIDIV, m16int, NotDef, NotDef, (Pointer)NULL, eFIDIV, 0x0},
	//DE /7    
	{L"FIDIVR",FIDIVR, m16int, NotDef, NotDef, (Pointer)NULL, eFIDIVR, 0x0},
};

SMTableBlock arTable_DE_Abnormal [] = {
	//DE C0
	{L"FADDP",FADDP, ST__0__, ST__0__, NotDef, (Pointer)NULL, eFADDP, 0x0},
	//DE C1
	{L"FADDP",FADDP, ST__1__, ST__0__, NotDef, (Pointer)NULL, eFADDP, 0x0},
	//DE C2
	{L"FADDP",FADDP, ST__2__, ST__0__, NotDef, (Pointer)NULL, eFADDP, 0x0},
	//DE C3
	{L"FADDP",FADDP, ST__3__, ST__0__, NotDef, (Pointer)NULL, eFADDP, 0x0},
	//DE C4
	{L"FADDP",FADDP, ST__4__, ST__0__, NotDef, (Pointer)NULL, eFADDP, 0x0},
	//DE C5
	{L"FADDP",FADDP, ST__5__, ST__0__, NotDef, (Pointer)NULL, eFADDP, 0x0},
	//DE C6
	{L"FADDP",FADDP, ST__6__, ST__0__, NotDef, (Pointer)NULL, eFADDP, 0x0},
	//DE C7
	{L"FADDP",FADDP, ST__7__, ST__0__, NotDef, (Pointer)NULL, eFADDP, 0x0},
	//DE C8
	{L"FMULP",FMULP, ST__8__, ST__0__, NotDef, (Pointer)NULL, eFMULP, 0x0},
	//DE C9
	{L"FMULP",FMULP, ST__9__, ST__0__, NotDef, (Pointer)NULL, eFMULP, 0x0},
	//DE CA
	{L"FMULP",FMULP, ST__10__, ST__0__, NotDef, (Pointer)NULL, eFMULP, 0x0},
	//DE CB
	{L"FMULP",FMULP, ST__11__, ST__0__, NotDef, (Pointer)NULL, eFMULP, 0x0},
	//DE CC
	{L"FMULP",FMULP, ST__12__, ST__0__, NotDef, (Pointer)NULL, eFMULP, 0x0},
	//DE CD
	{L"FMULP",FMULP, ST__13__, ST__0__, NotDef, (Pointer)NULL, eFMULP, 0x0},
	//DE CE
	{L"FMULP",FMULP, ST__14__, ST__0__, NotDef, (Pointer)NULL, eFMULP, 0x0},
	//DE CF
	{L"FMULP",FMULP, ST__15__, ST__0__, NotDef, (Pointer)NULL, eFMULP, 0x0},
	//DE D0
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE D1
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE D2
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE D3
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE D4
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE D5
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE D6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE D7
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE D8
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE D9    
	{L"FCOMPP",FCOMPP, NotDef, NotDef, NotDef, (Pointer)NULL, eFCOMPP, 0x0},
	//DE DA
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE DB
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE DC
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE DD
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE DE
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE DF
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DE E0
	{L"FSUBRP",FSUBRP, ST__0__, ST__0__, NotDef, (Pointer)NULL, eFSUBRP, 0x0},
	//DE E1
	{L"FSUBRP",FSUBRP, ST__1__, ST__0__, NotDef, (Pointer)NULL, eFSUBRP, 0x0},
	//DE E2
	{L"FSUBRP",FSUBRP, ST__2__, ST__0__, NotDef, (Pointer)NULL, eFSUBRP, 0x0},
	//DE E3
	{L"FSUBRP",FSUBRP, ST__3__, ST__0__, NotDef, (Pointer)NULL, eFSUBRP, 0x0},
	//DE E4
	{L"FSUBRP",FSUBRP, ST__4__, ST__0__, NotDef, (Pointer)NULL, eFSUBRP, 0x0},
	//DE E5
	{L"FSUBRP",FSUBRP, ST__5__, ST__0__, NotDef, (Pointer)NULL, eFSUBRP, 0x0},
	//DE E6
	{L"FSUBRP",FSUBRP, ST__6__, ST__0__, NotDef, (Pointer)NULL, eFSUBRP, 0x0},
	//DE E7
	{L"FSUBRP",FSUBRP, ST__7__, ST__0__, NotDef, (Pointer)NULL, eFSUBRP, 0x0},
	//DE E8
	{L"FSUBP",FSUBP, ST__8__, ST__0__, NotDef, (Pointer)NULL, eFSUBP, 0x0},
	//DE E9
	{L"FSUBP",FSUBP, ST__9__, ST__0__, NotDef, (Pointer)NULL, eFSUBP, 0x0},
	//DE EA
	{L"FSUBP",FSUBP, ST__10__, ST__0__, NotDef, (Pointer)NULL, eFSUBP, 0x0},
	//DE EB
	{L"FSUBP",FSUBP, ST__11__, ST__0__, NotDef, (Pointer)NULL, eFSUBP, 0x0},
	//DE EC
	{L"FSUBP",FSUBP, ST__12__, ST__0__, NotDef, (Pointer)NULL, eFSUBP, 0x0},
	//DE ED
	{L"FSUBP",FSUBP, ST__13__, ST__0__, NotDef, (Pointer)NULL, eFSUBP, 0x0},
	//DE EE
	{L"FSUBP",FSUBP, ST__14__, ST__0__, NotDef, (Pointer)NULL, eFSUBP, 0x0},
	//DE EF
	{L"FSUBP",FSUBP, ST__15__, ST__0__, NotDef, (Pointer)NULL, eFSUBP, 0x0},
	//DE F0
	{L"FDIVRP",FDIVRP, ST__0__, ST__0__, NotDef, (Pointer)NULL, eFDIVRP, 0x0},
	//DE F1
	{L"FDIVRP",FDIVRP, ST__1__, ST__0__, NotDef, (Pointer)NULL, eFDIVRP, 0x0},
	//DE F2
	{L"FDIVRP",FDIVRP, ST__2__, ST__0__, NotDef, (Pointer)NULL, eFDIVRP, 0x0},
	//DE F3
	{L"FDIVRP",FDIVRP, ST__3__, ST__0__, NotDef, (Pointer)NULL, eFDIVRP, 0x0},
	//DE F4
	{L"FDIVRP",FDIVRP, ST__4__, ST__0__, NotDef, (Pointer)NULL, eFDIVRP, 0x0},
	//DE F5
	{L"FDIVRP",FDIVRP, ST__5__, ST__0__, NotDef, (Pointer)NULL, eFDIVRP, 0x0},
	//DE F6
	{L"FDIVRP",FDIVRP, ST__6__, ST__0__, NotDef, (Pointer)NULL, eFDIVRP, 0x0},
	//DE F7
	{L"FDIVRP",FDIVRP, ST__7__, ST__0__, NotDef, (Pointer)NULL, eFDIVRP, 0x0},
	//DE F8
	{L"FDIVP",FDIVP, ST__8__, ST__0__, NotDef, (Pointer)NULL, eFDIVP, 0x0},
	//DE F9
	{L"FDIVP",FDIVP, ST__9__, ST__0__, NotDef, (Pointer)NULL, eFDIVP, 0x0},
	//DE FA
	{L"FDIVP",FDIVP, ST__10__, ST__0__, NotDef, (Pointer)NULL, eFDIVP, 0x0},
	//DE FB
	{L"FDIVP",FDIVP, ST__11__, ST__0__, NotDef, (Pointer)NULL, eFDIVP, 0x0},
	//DE FC
	{L"FDIVP",FDIVP, ST__12__, ST__0__, NotDef, (Pointer)NULL, eFDIVP, 0x0},
	//DE FD
	{L"FDIVP",FDIVP, ST__13__, ST__0__, NotDef, (Pointer)NULL, eFDIVP, 0x0},
	//DE FE
	{L"FDIVP",FDIVP, ST__14__, ST__0__, NotDef, (Pointer)NULL, eFDIVP, 0x0},
	//DE FF
	{L"FDIVP",FDIVP, ST__15__, ST__0__, NotDef, (Pointer)NULL, eFDIVP, 0x0},
};

SMTableBlock arTable_DFExt [] = {
	//DF /0    
	{L"FILD",FILD, m16int, NotDef, NotDef, (Pointer)NULL, eFILD, 0x0},
	//DF /1
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF /2    
	{L"FIST",FIST, m16int, NotDef, NotDef, (Pointer)NULL, eFIST, 0x0},
	//DF /3    
	{L"FISTP",FISTP, m16int, NotDef, NotDef, (Pointer)NULL, eFISTP, 0x0},
	//DF /4    
	{L"FBLD",FBLD8, m80dec, NotDef, NotDef, (Pointer)NULL, eFBLD8, 0x0},
	//DF /5    
	{L"FILD",FILD, m64int, NotDef, NotDef, (Pointer)NULL, eFILD, 0x0},
	//DF /6    
	{L"FBSTP",FBSTP8, m80bcd, NotDef, NotDef, (Pointer)NULL, eFBSTP8, 0x0},
	//DF /7    
	{L"FISTP",FISTP, m64int, NotDef, NotDef, (Pointer)NULL, eFISTP, 0x0},
};

SMTableBlock arTable_DF_Abnormal [] = {
	//DF C0
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF C1
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF C2
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF C3
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF C4
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF C5
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF C6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF C7
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF C8
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF C9
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF CA
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF CB
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF CC
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF CD
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF CE
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF CF
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF D0
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF D1
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF D2
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF D3
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF D4
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF D5
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF D6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF D7
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF D8
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF D9
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF DA
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF DB
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF DC
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF DD
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF DE
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF DF
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF E0    
	{L"FNSTSW",FNSTSW, AX, NotDef, NotDef, (Pointer)NULL, eFNSTSW, 0x0},
	//DF E1
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF E2
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF E3
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF E4
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF E5
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF E6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF E7
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF E8
	{L"FUCOMIP",FUCOMIP, ST, ST__8__, NotDef, (Pointer)NULL, eFUCOMIP, 0x0},
	//DF E9
	{L"FUCOMIP",FUCOMIP, ST, ST__9__, NotDef, (Pointer)NULL, eFUCOMIP, 0x0},
	//DF EA
	{L"FUCOMIP",FUCOMIP, ST, ST__10__, NotDef, (Pointer)NULL, eFUCOMIP, 0x0},
	//DF EB
	{L"FUCOMIP",FUCOMIP, ST, ST__11__, NotDef, (Pointer)NULL, eFUCOMIP, 0x0},
	//DF EC
	{L"FUCOMIP",FUCOMIP, ST, ST__12__, NotDef, (Pointer)NULL, eFUCOMIP, 0x0},
	//DF ED
	{L"FUCOMIP",FUCOMIP, ST, ST__13__, NotDef, (Pointer)NULL, eFUCOMIP, 0x0},
	//DF EE
	{L"FUCOMIP",FUCOMIP, ST, ST__14__, NotDef, (Pointer)NULL, eFUCOMIP, 0x0},
	//DF EF
	{L"FUCOMIP",FUCOMIP, ST, ST__15__, NotDef, (Pointer)NULL, eFUCOMIP, 0x0},
	//DF F0
	{L"FCOMIP",FCOMIP, ST, ST__0__, NotDef, (Pointer)NULL, eFCOMIP, 0x0},
	//DF F1
	{L"FCOMIP",FCOMIP, ST, ST__1__, NotDef, (Pointer)NULL, eFCOMIP, 0x0},
	//DF F2
	{L"FCOMIP",FCOMIP, ST, ST__2__, NotDef, (Pointer)NULL, eFCOMIP, 0x0},
	//DF F3
	{L"FCOMIP",FCOMIP, ST, ST__3__, NotDef, (Pointer)NULL, eFCOMIP, 0x0},
	//DF F4
	{L"FCOMIP",FCOMIP, ST, ST__4__, NotDef, (Pointer)NULL, eFCOMIP, 0x0},
	//DF F5
	{L"FCOMIP",FCOMIP, ST, ST__5__, NotDef, (Pointer)NULL, eFCOMIP, 0x0},
	//DF F6
	{L"FCOMIP",FCOMIP, ST, ST__6__, NotDef, (Pointer)NULL, eFCOMIP, 0x0},
	//DF F7
	{L"FCOMIP",FCOMIP, ST, ST__7__, NotDef, (Pointer)NULL, eFCOMIP, 0x0},
	//DF F8
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF F9
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF FA
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF FB
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF FC
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF FD
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF FE
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//DF FF
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock arTable_F6Ext [] = {
	//F6 /0 ib
	{L"TEST",TEST8, r_Slash_m8, imm8, NotDef, (Pointer)NULL, eTEST8, 0x2},
	//F6 /1
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//F6 /2  
	{L"NOT",NOT8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eNOT8, 0xA},
	//F6 /3  
	{L"NEG",NEG8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eNEG8, 0xA},
	//F6 /4  
	{L"MUL",MUL8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eMUL8, 0x2},
	//F6 /5  
	{L"IMUL",IMUL8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eIMUL8, 0x2},
	//F6 /6  
	{L"DIV",DIV8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eDIV8, 0x2},
	//F6 /7  
	{L"IDIV",IDIV8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eIDIV8, 0x2},
};

SMTableBlock arTable_F7Ext [] = {
	//F7 /0 id
	{L"TEST",TEST, r_Slash_m32, imm32, NotDef, TEST16, eTEST, 0x3},
	//F7 /1
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//F7 /2  
	{L"NOT",NOT, r_Slash_m32, NotDef, NotDef, NOT16, eNOT, 0xB},
	//F7 /3  
	{L"NEG",NEG, r_Slash_m32, NotDef, NotDef, NEG16, eNEG, 0xB},
	//F7 /4  
	{L"MUL",MUL, r_Slash_m32, NotDef, NotDef, MUL16, eMUL, 0x3},
	//F7 /5  
	{L"IMUL",IMUL, r_Slash_m32, NotDef, NotDef, IMUL16, eIMUL, 0x3},
	//F7 /6  
	{L"DIV",DIV, r_Slash_m32, NotDef, NotDef, DIV16, eDIV, 0x3},
	//F7 /7  
	{L"IDIV",IDIV, r_Slash_m32, NotDef, NotDef, IDIV16, eIDIV, 0x3},
};

SMTableBlock arTable_FEExt [] = {
	//FE /0  
	{L"INC",INC8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eINC8, 0xA},
	//FE /1  
	{L"DEC",DEC8, r_Slash_m8, NotDef, NotDef, (Pointer)NULL, eDEC8, 0xA},
	//FE /2
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//FE /3
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//FE /4
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//FE /5
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//FE /6
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
	//FE /7
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
};

SMTableBlock arTable_FFExt [] = {
	//FF /0  
	{L"INC",INC, r_Slash_m32, NotDef, NotDef, INC16, eINC, 0xB},
	//FF /1  
	{L"DEC",DEC, r_Slash_m32, NotDef, NotDef, DEC16, eDEC, 0xB},
	//FF /2  
	{L"CALL",CALL, r_Slash_m32, NotDef, NotDef, CALL16, eCALL, 0x3},
	//FF /3  
	{L"CALL",CALL, m16_Colon_32, NotDef, NotDef, CALL16, eCALL, 0x2},
	//FF /4  
	{L"JMP",JMP, r_Slash_m32, NotDef, NotDef, JMP16, eJMP, 0x3},
	//FF /5  
	{L"JMP",JMP, m16_Colon_32, NotDef, NotDef, JMP16, eJMP, 0x2},
	//FF /6  
	{L"PUSH",PUSH, r_Slash_m32, NotDef, NotDef, PUSH16, ePUSH, 0x3},
	//FF /7
	{L"NULL",NULL, NotDef, NotDef, NotDef, (Pointer)NULL, Ins, 0x0},
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
