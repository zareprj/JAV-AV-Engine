#ifndef ALL_DEFINE_ADDED
#define ALL_DEFINE_ADDED
#include "iomonitor.h"
#include <xmmintrin.h>
/*#include "SMTypeDefine.h"*/
// #include "SMFile.h"
 #include "FileInformation.h"
// #include "SMBuffer.h"
#include "Header.h"
#include <strsafe.h>
//#include "MemoryTree.h"


#define SMString	WCHAR*
#define StackSize	0x3FFF

#define NothingAndContinue		0x00000000
#define VirusAndCleaned			0x00000001
#define VirusAndNotCleaned		0x00000002
#define NotVirus				0x00000003

typedef struct tagSMFile		SMFile,				*PSMFile;
typedef struct _SMBuffer        SMBuffer ,			*PSMBuffer ;
typedef struct _FileInformation FileInformation,	*PFileInformation;
#ifndef  BOOLEAN
#define BOOLEAN UINT8 
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#pragma pack (push, 1)

//	Structure used for mmx and STx
typedef struct _QDouble
{	
	struct  
	{
		unsigned __int16 Sign:1;
		unsigned __int16 Exponent:15;
	};
	struct  
	{
		UINT64 Integer:1;
		UINT64 Fraction:63;
	};
} QDouble;


typedef struct _Registers
{
	// Registers
	union
	{
		// Exact Registers
		struct
		{
			// EAX
			union
			{
				UINT32	EAX;
				union
				{
					struct
					{
						UINT8 	AL;
						UINT8 	AH;
					};
					UINT16	AX;
				};
			};

			// ECX
			union
			{
				UINT32	ECX;
				union
				{
					struct	
					{
						UINT8 	CL;
						UINT8 	CH;
					};
					UINT16	CX;
				};
			};

			// EDX
			union
			{
				UINT32	EDX;
				union
				{
					struct
					{
						UINT8 	DL;
						UINT8 	DH;
					};
					UINT16	DX;
				};
			};

			// EBX
			union
			{
				UINT32	EBX;
				union
				{
					struct
					{
						UINT8 	BL;
						UINT8 	BH;
					};
					UINT16	BX;
				};
			};

			// ESP
			union
			{
				UINT32	ESP;
				UINT16	SP;
			};

			// EBP
			union
			{
				UINT32	EBP;
				UINT16	BP;
			};

			// ESI
			union
			{
				UINT32	ESI;
				UINT16	SI;
			};

			// EDI
			union
			{
				UINT32	EDI;
				UINT16	DI;
			};	

			// EIP
			UINT32	EIP;

		};

		// Array of Registers
		union 
		{			
			union
			{
				struct
				{
					UINT8 	L;
					UINT8 	H;
				};
				UINT16	X;
			};
			UINT32	EX;

		}Regs[9];		
	};

	// EFlag
	union
	{
		struct
		{
			UINT32	nCF:1; //Carry Flag
			UINT32	nFF0:1;// = 1, Not Define
			UINT32	nPF:1; //Parity Flag
			UINT32	nFF1:1;// = 0, Not Define
			UINT32	nAF:1; //Auxiliary Flag
			UINT32	nFF2:1; // = 0 Not Define
			UINT32	nZF:1; //Zero Flag
			UINT32	nSF:1; //Sign Flag
			UINT32	nTF:1; //Trap Flag  (Single Step)
			UINT32	nIF:1; //Interrupt Flag
			UINT32	nDF:1; //Direction Flag
			UINT32	nOF:1; //Overflow flag
			UINT32	nIOPL:1; //I/O Privilege Level  (286+ only)
			UINT32	nNT:1; //Nested Task Flag  (286+ only)
			UINT32	nFF3:1; // = 0 Not Define
			UINT32	nRF:1; //Resume Flag (386+ only)
			UINT32	nVM:1;  //Virtual Mode Flag (386+ only)
		};
		UINT32	nEFlag;
	};
} Registers;


// FPU words
typedef struct	_FPU
{
	// Control Word
	union
	{
		struct
		{
			UINT32	nPrecisionCW : 1;
			UINT32	nUnderflowCW : 1;
			UINT32	nOverflowCW : 1;
			UINT32	nZero_DivideCW : 1;
			UINT32	nDenormal_Operand : 1;
			UINT32	nInvalid_OperationCW : 1;
			UINT32	nReserve0 : 2;
			UINT32	nPrecision_ControlCW : 2;
			UINT32	nRounding_ControlCW : 2;				
			UINT32	nInfinity_ControlCW : 1;
		};
		UINT32 nControlWord;
	};

	// Status Word
	union
	{
		struct
		{
			UINT32	nPrecisionSW : 1;
			UINT32	nUnderflowSW : 1;
			UINT32	nOverflowSW : 1;
			UINT32	nZero_DivideSW : 1;
			UINT32	nDenormalized_OperandSW : 1;
			UINT32	nInvalid_OperationSW : 1;
			UINT32	nStack_FaultSW : 1;
			UINT32	nError_Summary_StatusSW : 1;
			UINT32	nC0 : 1;
			UINT32	nC1 : 1;
			UINT32	nC2 : 1;
			UINT32	nTop : 3;
			UINT32	nC3 : 1;
			UINT32	nBusyFPU : 1;
		};
		UINT32 nStatusWord;	
	};

	// Tag Word
	union
	{
		struct
		{
			UINT32 nTag0 : 2;
			UINT32 nTag1 : 2;
			UINT32 nTag2 : 2;
			UINT32 nTag3 : 2;
			UINT32 nTag4 : 2;
			UINT32 nTag5 : 2;
			UINT32 nTag6 : 2;
			UINT32 nTag7 : 2;
		};
		UINT32 nTagWord;
	};


	UINT32  nFPU_Instruction_Pointer_Offset;
	UINT16	nFPU_Instruction_Pointer_Selector;
	struct
	{
		UINT16	nOpcode : 10;		
	};		
	UINT32	nFPU_Operand_Pointer_Offset;
	UINT32	nFPU_Operand_Pointer_Selector : 16;
	
	// STx and MMX
	union
	{
		struct
		{
			union
			{
				QDouble osST0;
				UINT64	nMM0;
				UINT64	resrve0[2];
			};
			union
			{
				QDouble osST1;
				UINT64	nMM1;
				UINT64	resrve1[2];
			};
			union
			{
				QDouble osST2;
				UINT64	nMM2;
				UINT64	resrve2[2];
			};
			union
			{
				QDouble osST3;
				UINT64	nMM3;
				UINT64	resrve3[2];
			};
			union
			{
				QDouble osST4;
				UINT64	nMM4;
				UINT64	resrve4[2];
			};
			union
			{
				QDouble osST5;
				UINT64	nMM5;
				UINT64	resrve5[2];
			};
			union
			{
				QDouble osST6;
				UINT64	nMM6;
				UINT64	resrve6[2];
			};
			union
			{
				QDouble osST7;
				UINT64	nMM7;
				UINT64	resrve7[2];
			};
		};	
		QDouble arosST[8];
		UINT64	arnMMX[8];
		UINT64	resrve[8][2];
	};

	// XMMX
	union
	{
		struct  
		{
			__m128	nXMM0;
			__m128	nXMM1;
			__m128	nXMM2;
			__m128	nXMM3;
			__m128	nXMM4;
			__m128	nXMM5;
			__m128	nXMM6;
			__m128	nXMM7;
		};
		__m128	arnXMMX[8];
	};
	UINT8	_resrve[224];
} FPU;

typedef enum _SMBytesEnum SMBytesEnum;
//	Structure for Opcode information
typedef struct _OpcodeBlock
{
	UINT8	arbyOpcode[15];
	union
	{
		struct
		{
			UINT32		nOperand0 ;
			UINT32		nOperand1 ;
			UINT32		nOperand2 ;
		};
		UINT32		arnOperands[3];
	};
	UINT32		nData;
	BOOLEAN		bData;
	UINT32		nOperandsMemSize;
	UINT32		nOperandsMemIndex;
	UINT32		nCountOperand;
	union
	{
		struct
		{
			UINT8		b66 : 1 ;
			UINT8		b67 : 1 ;
			UINT8		bRep : 1 ;
			UINT8		bSeg : 1 ;
			UINT8		bLock : 1 ;
		};
		UINT8 Prefix;
	};
	UINT8	nBlockLength;
	UINT8	nOpcodeLength;

	BOOLEAN		bIsIgnored;	
	BOOLEAN		IsReadMemoryFailed;

	Pointer		pFunction;
	SMBytesEnum	eInstruction;
#if _DEBUG
	WCHAR	*szOpcode;
	WCHAR	*szOperand1;
	WCHAR	*szOperand2;
	WCHAR	*szOperand3;
#endif
}OpcodeBlock;

//	Segment Structure
typedef struct  _Segments
{
	UINT32	nFs;
	UINT32	nES;
	UINT32	nCS;
	UINT32	nDS;
	UINT32	nFS;
	UINT32	nGS;
}Segments;

typedef struct  _avl_table avl_table;
typedef struct _MemoryCreated MemoryCreated;
//////////////////////////////////////////////////////////////////////////
/////////////////// For Loading State Machine Dat File ///////////////////
//////////////////////////////////////////////////////////////////////////
typedef struct _TableHeader 
{
	UINT32 nGroupTableIndexCount, nStateNumberCount, nConditionStateCount, nFunctionBinariesCount, nConditionIndexCount, 
		   nFunctionLength, nConditionExpsLength,
		   nCleanVirusTableIndexCount, nCleanStateNumberCount, nCleanConditionStateCount, nCleanConditionIndexCount, 
		   nCleanFunctionLength, nCleanConditionExpsLength, nVirusNameTableAddress, nVirusNameLength;
}TableHeader;

typedef struct _VirusTables
{
	UINT32 nVirusIndex;
	UINT32 nParamCount;
	UINT32 nRootState;
}VirusTables;

// struct  VirusLength
// {
// 	UINT32 nIndex;
// 	UINT32 Length;
// };

typedef struct _StateTables
{
	UINT32 nIndex;
	UINT32 nCount;
}StateTables;

typedef struct  _Condition_State
{
	UINT32 nConditionIndex;
	UINT32 nNextStateIndex;
	union
	{
		UINT32 nFunctionOffset;
		UINT32 nFunctionId;
		UINT32 nVirusId;
	};
}Condition_State;

typedef struct _ConditionExpression
{
	UINT32  nLength;
	UINT8 * pbyExp;
}ConditionExpression;

typedef struct _FunctionBinary
{
	UINT32  nLength;
	UINT8   byIsChangeContext;
	UINT8   byType;
	UINT8 * pbyExp;
}FunctionBinary;

typedef struct _VirusParam
{
	UINT32  nCount;
	UINT32 * pnParams;
}VirusParam;

//////////////////////////////////////////////////////////////////////////
typedef struct _VirusLnk
{
	union
	{
		VirusTables posGroupTbl;
		VirusTables posVirusTbl;
	};
	VirusParam  osParam;
	UINT32		nInstructionCounter;
	UINT32		nVirusLength;
	UINT32		u32VirusId;
	struct _VirusLnk *pNext;
	struct _VirusLnk *pPrevious;
}VirusLnk;
//	Main Structure used for Virtual Machine
typedef struct _VirtualMachine
{
	struct  
	{
		// Cpu
		// For Opcode
		OpcodeBlock osOpcodeBlock;
		UINT32	nTmpOffset;
		UINT32  nInsCounter;
		UINT32	nImm;
		BOOLEAN		bFlagRM;
		BOOLEAN		bFlagSIB;
		union
		{
			struct
			{
				UINT8 byR_M:3;
				UINT8 byReg:3;
				UINT8 byMod:2;
			};
			UINT8 byMod_R_M;
		};
		// Sib
		union
		{
			struct
			{
				UINT8 byBase:3;
				UINT8 byIndex:3;
				UINT8 byScale:2;			
			};
			UINT8 bySIB;
		};

#if _DEBUG
		WCHAR	szInstruction[200];
#endif

		// For Registers
		Registers	osReg;
		Segments	osSegments;
		FPU			osFReg;
		UINT16 arn16BitReg[8];

		// For File 
		//SMString	*pocFilePath;
		SMFile				*posFile;
		PFileInformation	posInfoOFFile;
		SMBuffer			*posBuffer;

		// For Check 
		UINT32	nFlag;

		// VMem
		// For Opcode Buffer
		UINT8	*pnMemOpcodeBuffer;
		UINT8	 nOpcodeCurIndx;

		// For Code Executing
		UINT8	*pnCodeBuffer;
		BOOLEAN bIsCodeBufferPresent;
		UINT32	nCodeLength;
		UINT32  u32Config ; 

		// For Jcc Enable or Disable
		BOOLEAN	bIsJccEnabled;
		//For log File
#if _DEBUG
		SMString	*pocLogFilePath;
		SMFile		*pocLogFile;
#endif
	}Context;

	// For All Virus List
	VirusLnk *posVirusLink;	
	UINT32	 nVirusLnkCount;

	PFileHandle		phFileHandle;
// 	WCHAR*			wsDosDeviceName;
// 	WCHAR*			wsFileName;

	VirusLnk osCleanVirusLnk;


	// For Memory Tree
	struct avl_table		*posMainMemoryTree;
	MemoryCreated	*posLastUsedMemoryTree;
// 	MemoryCreated	*posMainMemoryCreated;
// 	MemoryDel		*posMemoryDel;
	UINT8			 pnMiddleBuffer[4096];

	// For write Buffer
	BOOLEAN		IsBufForWrite;

	//For Stack
	UINT32			arnStack[StackSize];
	BOOLEAN			IsNodeCreated;
	BOOLEAN			IsOverflowHappend;
	BOOLEAN			IsUnderflowHappend;
} VirtualMachine ;

typedef struct _SMVM
{
	BOOLEAN				m_bIsUsed;
	VirtualMachine		m_osVm;
}SMVirtualMachinePack, *PSMVirtualMachinePack;

typedef struct _SMVirtualMachineStack 
{
	VirtualMachine				**m_parosVMStack;
	PSMVirtualMachinePack		*m_parosVirtualMachinesPack;
	UINT32						m_nCount;
	INT32						m_nTop;
	UINT32						m_u32VirusID;
}SMVirtualMachineStack, *PSMVirtualMachineStack ;

#define ZeroMemory(Destination,Length) memset((Destination), 0 ,(Length))
typedef enum _SMBytesEnum
{
	Ins,
	InsCount,
	Opcode,
	ModRM,
	SIB,
	Data,

	MemByteRegDigit,
	MemByteReg,
	MemByteDigit,
	MemWordRegDigit,
	MemWordReg,
	MemWordDigit,
	MemDwordRegDigit,
	MemDwordReg,
	MemDwordDigit,

	ax,
	eax,
	al,
	ah,
	cx,
	ecx,
	cl,
	ch,
	dx,
	edx,
	dl,
	dh,
	bx,
	ebx,
	bl,
	bh,
	sp,
	esp,
	bp,
	ebp,
	si,
	esi,
	di,
	edi,
	eip,

	ByteDigit,
	WordDigit,
	DwordDigit,

	Equal,
	NotEqual,
	Greater,
	Lower,
	EqualGreater,
	EqualLower,
	Plus,
	Minus,
	Multiply,
	Divide,
	And,
	Or,
	Xor,
	ConditionAnd,
	ConditionOr,
	Instruction,
	StackDown,
	Operand0,
	Operand1,
	Param,
	ParentParam,
	SetEntryPoint,
	GetEntryPoint,
	Colon,
	SemiColon,
	TruE,
	FalsE,
	Jump,
	Return,
	Min,

	Read,
	ReadMem,
	Write,

	Seek,
	SeekPhysical,
	Begin,
	Current,
	End,

	RVAToOffset,
	OffsetToRVA,
	
	GetCurrecntSectionIndex,

	Truncate,
	SetZero,
	Alloc,
	Free,

	SetVirusLength,
	GetFileLength, 

	eAAA,
	eAAD,
	eAAM,
	eAAS,
	eAAS8,
	eADC,
	eADC16,
	eADC8,
	eADD,
	eADD16,
	eADD8,
	eADDPS,
	eADDSS,
	eAND,
	eAND16,
	eAND8,
	eANDNPS,
	eANDPS,
	eARPL,
	eARPL16,
	eBOUND,
	eBOUND16,
	eBSF,
	eBSF16,
	eBSR,
	eBSR16,
	eBSWAP,
	eBSWAP16,
	eBT,
	eBT16,
	eBT8,
	eBTC,
	eBTC16,
	eBTC8,
	eBTR,
	eBTR16,
	eBTR8,
	eBTS,
	eBTS16,
	eBTS8,
	eCALL,
	eCALL16,
	eCBW,
	eCDQ,
	eCLC,
	eCLD,
	eCLI,
	eCLTS,
	eCMC,
	eCMOVAE,
	eCMOVAE16,
	eCMOVC,
	eCMOVC16,
	eCMOVNA,
	eCMOVNA16,
	eCMOVNBE,
	eCMOVNBE16,
	eCMOVNG,
	eCMOVNG16,
	eCMOVNGE,
	eCMOVNGE16,
	eCMOVNL,
	eCMOVNL16,
	eCMOVNLE,
	eCMOVNLE16,
	eCMOVNO,
	eCMOVNO16,
	eCMOVNS,
	eCMOVNS16,
	eCMOVNZ,
	eCMOVNZ16,
	eCMOVO,
	eCMOVO16,
	eCMOVPE,
	eCMOVPE16,
	eCMOVPO,
	eCMOVPO16,
	eCMOVS,
	eCMOVS16,
	eCMOVZ,
	eCMOVZ16,
	eCMP,
	eCMP16,
	eCMP8,
	eCMPPS,
	eCMPSB,
	eCMPSD,
	eCMPSD16,
	eCMPSS,
	eCMPXCHG,
	eCMPXCHG16,
	eCMPXCHG8,
	eCMPXCHG8B,
	eCOMISS,
	eCPUID,
	eCVTPI2PS,
	eCVTPS2PI,
	eCVTSI2SS,
	eCVTSS2SI,
	eCVTTPS2PI,
	eCVTTSS2SI,
	eCWD,
	eCWDE,
	eDAA,
	eDAA8,
	eDAS,
	eDAS8,
	eDEC,
	eDEC16,
	eDEC8,
	eDIV,
	eDIV16,
	eDIV8,
	eDIVPS,
	eDIVSS,
	eEMMS,
	eENTER,
	eENTER8,
	eF2XM1,
	eFABS,
	eFADD,
	eFADDP,
	eFBLD,
	eFBLD8,
	eFBSTP,
	eFBSTP8,
	eFCHS,
	eFCLEX,
	eFCMOVB,
	eFCMOVBE,
	eFCMOVE,
	eFCMOVNB,
	eFCMOVNBE,
	eFCMOVNE,
	eFCMOVNU,
	eFCMOVU,
	eFCOM,
	eFCOMI,
	eFCOMIP,
	eFCOMP,
	eFCOMPP,
	eFCOS,
	eFDECSTP,
	eFDIV,
	eFDIVP,
	eFDIVR,
	eFDIVRP,
	eFFREE,
	eFIADD,
	eFICOM,
	eFICOMP,
	eFIDIV,
	eFIDIVR,
	eFILD,
	eFIMUL,
	eFINCSTP,
	eFINIT,
	eFIST,
	eFISTP,
	eFISUB,
	eFISUBR,
	eFLD,
	eFLD1,
	eFLD8,
	eFLDCW,
	eFLDENV,
	eFLDL2E,
	eFLDL2T,
	eFLDLG2,
	eFLDLN2,
	eFLDPI,
	eFLDZ,
	eFMUL,
	eFMULP,
	eFNCLEX,
	eFNINIT,
	eFNOP,
	eFNSAVE,
	eFNSTCW,
	eFNSTENV,
	eFNSTSW,
	eFNSTSW16,
	eFPATAN,
	eFPREM,
	eFPREM1,
	eFPTAN,
	eFRNDINT,
	eFRSTOR,
	eFSAVE,
	eFSCALE,
	eFSIN,
	eFSINCOS,
	eFSQRT,
	eFST,
	eFSTCW,
	eFSTENV,
	eFSTP,
	eFSTP8,
	eFSTSW,
	eFSUB,
	eFSUBP,
	eFSUBR,
	eFSUBRP,
	eFTST,
	eFUCOM,
	eFUCOMI,
	eFUCOMIP,
	eFUCOMP,
	eFUCOMPP,
	eFWAIT,
	eFXAM,
	eFXCH,
	eFXRSTOR,
	eFXSAVE,
	eFXTRACT,
	eFYL2X,
	eFYL2XP1,
	eHLT,
	eIDIV,
	eIDIV16,
	eIDIV8,
	eIMUL,
	eIMUL16,
	eIMUL8,
	eIN_,
	eIN_16,
	eIN_8,
	eINC,
	eINC16,
	eINC8,
	eINS,
	eINSB,
	eINSD,
	eINSW,
	eINT3,            
	eINTO,
	eINVD,
	eINVLPG,
	eIRET,
	eIRETD,
	eJAE,
	eJB,
	eJC,
	eJECXZ,
	eJMP,
	eJMP16,
	eJNA,
	eJNB,
	eJNBE,
	eJNG,
	eJNGE,
	eJNL,
	eJNLE,
	eJNO,
	eJNS,
	eJNZ,
	eJO,
	eJPE,
	eJPO,
	eJS,
	eJZ,
	eLAHF,
	eLAR,
	eLAR16,
	eLDMXCSR,
	eLDS,
	eLDS16,
	eLEA,
	eLEA16,
	eLEAVE,
	eLEAVE16,
	eLES,
	eLES16,
	eLFS,
	eLFS16,
	eLGDT,
	eLGS,
	eLGS16,
	eLIDT,
	eLLDT,
	eLLDT16,
	eLMSW,
	eLMSW16,
	eLOCK,
	eLODS,
	eLODSB,
	eLODSB16,
	eLODSD,
	eLODSD16,
	eLOOP,
	eLOOPNZ,
	eLOOPZ,
	eLSL,
	eLSL16,
	eLSS,
	eLSS16,
	eLTR,
	eLTR16,
	eMASKMOVQ,
	eMAXPS,
	eMAXSS,
	eMINPS,
	eMINSS,
	eMOV,
	eMOV16,
	eMOV8,
	eMOVAPS,
	eMOVD,
	eMOVD16,
	eMOVHLPS,
	eMOVHPS,
	eMOVLHPS,
	eMOVLPS,
	eMOVMSKPS,
	eMOVNTPS,
	eMOVNTQ,
	eMOVQ,
	eMOVSB,
	eMOVSD,
	eMOVSD16,
	eMOVSS,
	eMOVSX,
	eMOVSX16,
	eMOVSX8,
	eMOVUPS,
	eMOVZX,
	eMOVZX16,
	eMOVZX8,
	eMUL,
	eMUL16,
	eMUL8,
	eMULPS,
	eMULSS,
	eNEG,
	eNEG16,
	eNEG8,
	eNOP,
	eNOT,
	eNOT16,
	eNOT8,
	eOR,
	eOR16,
	eOR8,
	eORPS,
	eOUT_,
	eOUT_16,
	eOUT_8,
	eOUTS,
	eOUTSB,
	eOUTSD,
	eOUTSW,
	ePACKSSDW,
	ePACKSSWB,
	ePACKUSWB,
	ePADDB,
	ePADDD,
	ePADDSB,
	ePADDSW,
	ePADDUSB,
	ePADDUSW,
	ePADDW,
	ePAND,
	ePANDN,
	ePAVGB,
	ePAVGW,
	ePCMPEQB,
	ePCMPEQD,
	ePCMPEQW,
	ePCMPGTB,
	ePCMPGTD,
	ePCMPGTW,
	ePEXTRW,
	ePINSRW,
	ePMADDWD,
	ePMAXSW,
	ePMAXUB,
	ePMINSW,
	ePMINUB,
	ePMOVMSKB,
	ePMOVMSKB16,
	ePMULHUW,
	ePMULHW,
	ePMULLW,
	ePOP,
	ePOP16,
	ePOP8,
	ePOPAD,
	ePOPAD16,
	ePOPF,
	ePOPFD,
	ePOPFD16,
	ePOR,
	ePREFETCHNTA8,
	ePREFETCHT08,
	ePREFETCHT18,
	ePREFETCHT28,
	ePSADBW,
	ePSHUFW,
	ePSLLD,
	ePSLLD8,
	ePSLLQ,
	ePSLLQ8,
	ePSLLW,
	ePSLLW8,
	ePSRAD,
	ePSRAD8,
	ePSRAW,
	ePSRAW8,
	ePSRLD,
	ePSRLD8,
	ePSRLQ,
	ePSRLQ8,
	ePSRLW,
	ePSRLW8,
	ePSUBB,
	ePSUBD,
	ePSUBSB,
	ePSUBSW,
	ePSUBUSB,
	ePSUBUSW,
	ePSUBW,
	ePUNPCKHBW,
	ePUNPCKHDQ,
	ePUNPCKHWD,
	ePUNPCKLBW,
	ePUNPCKLDQ,
	ePUNPCKLWD,
	ePUSH,
	ePUSH16,
	ePUSH8,
	ePUSHAD,
	ePUSHAD16,
	ePUSHF,
	ePUSHFD,
	ePUSHFD16,
	ePXOR,
	eRCL,
	eRCL16,
	eRCL8,
	eRCPPS,
	eRCPSS,
	eRCR,
	eRCR16,
	eRCR8,
	eRDMSR,
	eRDPMC,
	eRDTSC,
	eREP,
	eREPE,
	eREPNE,
	eREPNZ,
	eREPZ,
	eRET,
	eRETF,
	eROL,
	eROL16,
	eROL8,
	eROR,
	eROR16,
	eROR8,
	eRSM,
	eRSQRTPS,
	eRSQRTSS,
	eSAHF,
	eSAL,
	eSAL16,
	eSAL8,
	eSAR,
	eSAR16,
	eSAR8,
	eSBB,
	eSBB16,
	eSBB8,
	eSCAS,
	eSCASB,
	eSCASB16,
	eSCASD,
	eSCASD16,
	eSetAlc,
	eSETB8,
	eSETNA8,
	eSETNB8,
	eSETNBE8,
	eSETNG8,
	eSETNGE8,
	eSETNL8,
	eSETNLE8,
	eSETNO8,
	eSETNS8,
	eSETNZ8,
	eSETO8,
	eSETPE8,
	eSETPO8,
	eSETS8,
	eSETZ8,
	eSFENCE,
	eSGDT,
	eSHL,
	eSHL16,
	eSHL8,
	eSHLD,
	eSHLD16,
	eSHR,
	eSHR16,
	eSHR8,
	eSHRD,
	eSHRD16,
	eSHUFPS,
	eSIDT,
	eSLDT,
	eSLDT16,
	eSMSW,
	eSMSW16,
	eSQRTPS,
	eSQRTSS,
	eSTC,
	eSTD,
	eSTI,
	eSTMXCSR,
	eSTOS,
	eSTOSB,
	eSTOSB16,
	eSTOSD,
	eSTOSD16,
	eSTR,
	eSTR16,
	eSUB,
	eSUB16,
	eSUB8,
	eSUBPS,
	eSUBSS,
	eSYSENTER,
	eSYSEXIT,
	eTEST,
	eTEST16,
	eTEST8,
	eUCOMISS,
	eUD2,
	eUNPCKHPS,
	eUNPCKLPS,
	eVERR,
	eVERR16,
	eVERW,
	eVERW16,
	eWAIT,
	eWBINVD,
	eWRMSR,
	eXADD,
	eXADD16,
	eXADD8,
	eXCHG,
	eXCHG16,
	eXCHG8,
	eXLAT,
	eXLATB,
	eXOR,
	eXOR16,
	eXOR8,
	eXORPS

} SMBytesEnum;

#pragma pack(pop)
#endif