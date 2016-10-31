
#include "OperationsFunctions.h"
#include "All_Defines.h"
#include "Mem.h"
#include "CPU.h"

//#define CONDITION
// Notice : 1. For Naked function must put a Ret() macro to return
//			2. To set breakpoint on Naked function it must be on an instruction not on the function prototype

//	macro for save EFlag register into VirtualMachine structure
#define FlagSaver(X)   __asm pushfd\
	__asm pop eax\
	__asm mov	X, eax

//	macro for restore EFlag from VirtualMachine structure into EFlag register 
#define FlagRestore(X)   __asm mov	eax , X\
	__asm push	eax\
	__asm popfd


#define BreakPoint()	__asm int 3

#ifdef ALLOC_PRAGMA
#pragma alloc_text(PAGE, AAA)
#pragma alloc_text(PAGE, AAD)
#pragma alloc_text(PAGE, AAM)
#pragma alloc_text(PAGE, AAS8)
#pragma alloc_text(PAGE, AAS)
#pragma alloc_text(PAGE, ADC8)
#pragma alloc_text(PAGE, ADC16)
#pragma alloc_text(PAGE, ADC)
#pragma alloc_text(PAGE, ADD8)
#pragma alloc_text(PAGE, ADD16)
#pragma alloc_text(PAGE, ADD)
#pragma alloc_text(PAGE, ADDPS)
#pragma alloc_text(PAGE, ADDSS)
#pragma alloc_text(PAGE, AND8)
#pragma alloc_text(PAGE, AND16)
#pragma alloc_text(PAGE, AND)
#pragma alloc_text(PAGE, ANDNPS)
#pragma alloc_text(PAGE, ANDPS)
#pragma alloc_text(PAGE, ARPL16)
#pragma alloc_text(PAGE, ARPL)
#pragma alloc_text(PAGE, BOUND16)
#pragma alloc_text(PAGE, BOUND)
#pragma alloc_text(PAGE, BSF16)
#pragma alloc_text(PAGE, BSF)
#pragma alloc_text(PAGE, BSR16)
#pragma alloc_text(PAGE, BSR)
#pragma alloc_text(PAGE, BSWAP16)
#pragma alloc_text(PAGE, BSWAP)
#pragma alloc_text(PAGE, BT8)
#pragma alloc_text(PAGE, BT16)
#pragma alloc_text(PAGE, BT)
#pragma alloc_text(PAGE, BTC8)
#pragma alloc_text(PAGE, BTC16)
#pragma alloc_text(PAGE, BTC)
#pragma alloc_text(PAGE, BTR8)
#pragma alloc_text(PAGE, BTR16)
#pragma alloc_text(PAGE, BTR)
#pragma alloc_text(PAGE, BTS8)
#pragma alloc_text(PAGE, BTS16)
#pragma alloc_text(PAGE, BTS)
#pragma alloc_text(PAGE, CALL16)
#pragma alloc_text(PAGE, CALL)
#pragma alloc_text(PAGE, CBW)
#pragma alloc_text(PAGE, CWDE)
#pragma alloc_text(PAGE, CLC)
#pragma alloc_text(PAGE, CLD)
#pragma alloc_text(PAGE, CLI)
#pragma alloc_text(PAGE, CLTS)
#pragma alloc_text(PAGE, CMC)
#pragma alloc_text(PAGE, CMP8)
#pragma alloc_text(PAGE, CMP16)
#pragma alloc_text(PAGE, CMP)
#pragma alloc_text(PAGE, CMPSB)
#pragma alloc_text(PAGE, CMPSD16)
#pragma alloc_text(PAGE, CMPSD)
#pragma alloc_text(PAGE, CMPSS)
#pragma alloc_text(PAGE, CMPXCHG8)
#pragma alloc_text(PAGE, CMPXCHG16)
#pragma alloc_text(PAGE, CMPXCHG)
#pragma alloc_text(PAGE, CMPXCHG8B)
#pragma alloc_text(PAGE, COMISS)
#pragma alloc_text(PAGE, CPUID)
#pragma alloc_text(PAGE, CVTPI2PS)
#pragma alloc_text(PAGE, CVTPS2PI)
#pragma alloc_text(PAGE, CVTSI2SS)
#pragma alloc_text(PAGE, CVTSS2SI)
#pragma alloc_text(PAGE, CVTTPS2PI)
#pragma alloc_text(PAGE, CVTTSS2SI)
#pragma alloc_text(PAGE, CWD)
#pragma alloc_text(PAGE, CDQ)
#pragma alloc_text(PAGE, DAA8)
#pragma alloc_text(PAGE, DAA)
#pragma alloc_text(PAGE, DAS8)
#pragma alloc_text(PAGE, DAS)
#pragma alloc_text(PAGE, DEC8)
#pragma alloc_text(PAGE, DEC16)
#pragma alloc_text(PAGE, DEC)
#pragma alloc_text(PAGE, DIV8)
#pragma alloc_text(PAGE, DIV16)
#pragma alloc_text(PAGE, DIV)
#pragma alloc_text(PAGE, DIVPS)
#pragma alloc_text(PAGE, DIVSS)
#pragma alloc_text(PAGE, EMMS)
#pragma alloc_text(PAGE, ENTER8)
#pragma alloc_text(PAGE, ENTER)
#pragma alloc_text(PAGE, F2XM1)
#pragma alloc_text(PAGE, FABS)
#pragma alloc_text(PAGE, FADD)
#pragma alloc_text(PAGE, FADDP)
#pragma alloc_text(PAGE, FIADD)
#pragma alloc_text(PAGE, FBLD8)
#pragma alloc_text(PAGE, FBLD)
#pragma alloc_text(PAGE, FBSTP8)
#pragma alloc_text(PAGE, FBSTP)
#pragma alloc_text(PAGE, FCHS)
#pragma alloc_text(PAGE, FCLEX)
#pragma alloc_text(PAGE, FNCLEX)
#pragma alloc_text(PAGE, FCOM)
#pragma alloc_text(PAGE, FCOMP)
#pragma alloc_text(PAGE, FCOMPP)
#pragma alloc_text(PAGE, FCOMI)
#pragma alloc_text(PAGE, FCOMIP)
#pragma alloc_text(PAGE, FUCOMI)
#pragma alloc_text(PAGE, FUCOMIP)
#pragma alloc_text(PAGE, FCOS)
#pragma alloc_text(PAGE, FDECSTP)
#pragma alloc_text(PAGE, FDIV)
#pragma alloc_text(PAGE, FDIVP)
#pragma alloc_text(PAGE, FIDIV)
#pragma alloc_text(PAGE, FDIVR)
#pragma alloc_text(PAGE, FDIVRP)
#pragma alloc_text(PAGE, FIDIVR)
#pragma alloc_text(PAGE, FFREE)
#pragma alloc_text(PAGE, FICOM)
#pragma alloc_text(PAGE, FICOMP)
#pragma alloc_text(PAGE, FILD)
#pragma alloc_text(PAGE, FINCSTP)
#pragma alloc_text(PAGE, FINIT)
#pragma alloc_text(PAGE, FNINIT)
#pragma alloc_text(PAGE, FIST)
#pragma alloc_text(PAGE, FISTP)
#pragma alloc_text(PAGE, FLD8)
#pragma alloc_text(PAGE, FLD)
#pragma alloc_text(PAGE, FLD1)
#pragma alloc_text(PAGE, FLDL2T)
#pragma alloc_text(PAGE, FLDL2E)
#pragma alloc_text(PAGE, FLDPI)
#pragma alloc_text(PAGE, FLDLG2)
#pragma alloc_text(PAGE, FLDLN2)
#pragma alloc_text(PAGE, FLDZ)
#pragma alloc_text(PAGE, FLDCW)
#pragma alloc_text(PAGE, FLDENV)
#pragma alloc_text(PAGE, FMUL)
#pragma alloc_text(PAGE, FMULP)
#pragma alloc_text(PAGE, FIMUL)
#pragma alloc_text(PAGE, FNOP)
#pragma alloc_text(PAGE, FPATAN)
#pragma alloc_text(PAGE, FPREM)
#pragma alloc_text(PAGE, FPREM1)
#pragma alloc_text(PAGE, FPTAN)
#pragma alloc_text(PAGE, FRNDINT)
#pragma alloc_text(PAGE, FRSTOR)
#pragma alloc_text(PAGE, FSAVE)
#pragma alloc_text(PAGE, FNSAVE)
#pragma alloc_text(PAGE, FSCALE)
#pragma alloc_text(PAGE, FSIN)
#pragma alloc_text(PAGE, FSINCOS)
#pragma alloc_text(PAGE, FSQRT)
#pragma alloc_text(PAGE, FST)
#pragma alloc_text(PAGE, FSTP8)
#pragma alloc_text(PAGE, FSTP)
#pragma alloc_text(PAGE, FSTCW)
#pragma alloc_text(PAGE, FNSTCW)
#pragma alloc_text(PAGE, FSTENV)
#pragma alloc_text(PAGE, FNSTENV)
#pragma alloc_text(PAGE, FSTSW)
#pragma alloc_text(PAGE, FNSTSW16)
#pragma alloc_text(PAGE, FNSTSW)
#pragma alloc_text(PAGE, FSUB)
#pragma alloc_text(PAGE, FSUBP)
#pragma alloc_text(PAGE, FISUB)
#pragma alloc_text(PAGE, FSUBR)
#pragma alloc_text(PAGE, FSUBRP)
#pragma alloc_text(PAGE, FISUBR)
#pragma alloc_text(PAGE, FTST)
#pragma alloc_text(PAGE, FUCOM)
#pragma alloc_text(PAGE, FUCOMP)
#pragma alloc_text(PAGE, FUCOMPP)
#pragma alloc_text(PAGE, FXAM)
#pragma alloc_text(PAGE, FXCH)
#pragma alloc_text(PAGE, FXRSTOR)
#pragma alloc_text(PAGE, FXSAVE)
#pragma alloc_text(PAGE, FXTRACT)
#pragma alloc_text(PAGE, FYL2X)
#pragma alloc_text(PAGE, FYL2XP1)
#pragma alloc_text(PAGE, HLT)
#pragma alloc_text(PAGE, IDIV8)
#pragma alloc_text(PAGE, IDIV16)
#pragma alloc_text(PAGE, IDIV)
#pragma alloc_text(PAGE, IMUL8)
#pragma alloc_text(PAGE, IMUL16)
#pragma alloc_text(PAGE, IMUL)
#pragma alloc_text(PAGE, IN_16)
#pragma alloc_text(PAGE, IN_8)
#pragma alloc_text(PAGE, IN_)
#pragma alloc_text(PAGE, INC8)
#pragma alloc_text(PAGE, INC16)
#pragma alloc_text(PAGE, INC)
#pragma alloc_text(PAGE, INS)
#pragma alloc_text(PAGE, INSB)
#pragma alloc_text(PAGE, INSW)
#pragma alloc_text(PAGE, INSD)
#pragma alloc_text(PAGE, INTn8)
#pragma alloc_text(PAGE, INTO)
#pragma alloc_text(PAGE, INT3)
#pragma alloc_text(PAGE, INVD)
#pragma alloc_text(PAGE, INVLPG)
#pragma alloc_text(PAGE, IRET)
#pragma alloc_text(PAGE, IRETD)
#pragma alloc_text(PAGE, JMP16)
#pragma alloc_text(PAGE, JMP)
#pragma alloc_text(PAGE, LAHF)
#pragma alloc_text(PAGE, LAR16)
#pragma alloc_text(PAGE, LAR)
#pragma alloc_text(PAGE, LDMXCSR)
#pragma alloc_text(PAGE, LDS16)
#pragma alloc_text(PAGE, LDS)
#pragma alloc_text(PAGE, LES16)
#pragma alloc_text(PAGE, LES)
#pragma alloc_text(PAGE, LFS16)
#pragma alloc_text(PAGE, LFS)
#pragma alloc_text(PAGE, LGS16)
#pragma alloc_text(PAGE, LGS)
#pragma alloc_text(PAGE, LSS16)
#pragma alloc_text(PAGE, LSS)
#pragma alloc_text(PAGE, LEA16)
#pragma alloc_text(PAGE, LEA)
#pragma alloc_text(PAGE, LEAVE16)
#pragma alloc_text(PAGE, LEAVE)
#pragma alloc_text(PAGE, LGDT)
#pragma alloc_text(PAGE, LIDT)
#pragma alloc_text(PAGE, LLDT16)
#pragma alloc_text(PAGE, LLDT)
#pragma alloc_text(PAGE, LMSW16)
#pragma alloc_text(PAGE, LMSW)
#pragma alloc_text(PAGE, LOCK)
#pragma alloc_text(PAGE, LODS)
#pragma alloc_text(PAGE, LODSB16)
#pragma alloc_text(PAGE, LODSB)
#pragma alloc_text(PAGE, LODSD16)
#pragma alloc_text(PAGE, LODSD)
#pragma alloc_text(PAGE, LOOP)
#pragma alloc_text(PAGE, LSL16)
#pragma alloc_text(PAGE, LSL)
#pragma alloc_text(PAGE, LTR16)
#pragma alloc_text(PAGE, LTR)
#pragma alloc_text(PAGE, MASKMOVQ)
#pragma alloc_text(PAGE, MAXPS)
#pragma alloc_text(PAGE, MAXSS)
#pragma alloc_text(PAGE, MINPS)
#pragma alloc_text(PAGE, MINSS)
#pragma alloc_text(PAGE, PreMov_String)
#pragma alloc_text(PAGE, Mov_String)
#pragma alloc_text(PAGE, MOV8)
#pragma alloc_text(PAGE, MOV16)
#pragma alloc_text(PAGE, MOV)
#pragma alloc_text(PAGE, MOVAPS)
#pragma alloc_text(PAGE, MOVD16)
#pragma alloc_text(PAGE, MOVD)
#pragma alloc_text(PAGE, MOVHLPS)
#pragma alloc_text(PAGE, MOVHPS)
#pragma alloc_text(PAGE, MOVLHPS)
#pragma alloc_text(PAGE, MOVLPS)
#pragma alloc_text(PAGE, MOVMSKPS)
#pragma alloc_text(PAGE, MOVNTPS)
#pragma alloc_text(PAGE, MOVNTQ)
#pragma alloc_text(PAGE, MOVQ)
#pragma alloc_text(PAGE, MOVSB)
#pragma alloc_text(PAGE, MOVSD16)
#pragma alloc_text(PAGE, MOVSD)
#pragma alloc_text(PAGE, MOVSS)
#pragma alloc_text(PAGE, MOVSX8)
#pragma alloc_text(PAGE, MOVSX16)
#pragma alloc_text(PAGE, MOVSX)
#pragma alloc_text(PAGE, MOVUPS)
#pragma alloc_text(PAGE, MOVZX8)
#pragma alloc_text(PAGE, MOVZX16)
#pragma alloc_text(PAGE, MOVZX)
#pragma alloc_text(PAGE, MUL8)
#pragma alloc_text(PAGE, MUL16)
#pragma alloc_text(PAGE, MUL)
#pragma alloc_text(PAGE, MULPS)
#pragma alloc_text(PAGE, MULSS)
#pragma alloc_text(PAGE, NEG8)
#pragma alloc_text(PAGE, NEG16)
#pragma alloc_text(PAGE, NEG)
#pragma alloc_text(PAGE, NOP)
#pragma alloc_text(PAGE, NOT8)
#pragma alloc_text(PAGE, NOT16)
#pragma alloc_text(PAGE, NOT)
#pragma alloc_text(PAGE, OR8)
#pragma alloc_text(PAGE, OR16)
#pragma alloc_text(PAGE, OR)
#pragma alloc_text(PAGE, ORPS)
#pragma alloc_text(PAGE, OUT_8)
#pragma alloc_text(PAGE, OUT_16)
#pragma alloc_text(PAGE, OUT_)
#pragma alloc_text(PAGE, OUTS)
#pragma alloc_text(PAGE, OUTSB)
#pragma alloc_text(PAGE, OUTSW)
#pragma alloc_text(PAGE, OUTSD)
#pragma alloc_text(PAGE, PACKSSWB)
#pragma alloc_text(PAGE, PACKSSDW)
#pragma alloc_text(PAGE, PACKUSWB)
#pragma alloc_text(PAGE, PADDB)
#pragma alloc_text(PAGE, PADDW)
#pragma alloc_text(PAGE, PADDD)
#pragma alloc_text(PAGE, PADDSB)
#pragma alloc_text(PAGE, PADDSW)
#pragma alloc_text(PAGE, PADDUSB)
#pragma alloc_text(PAGE, PADDUSW)
#pragma alloc_text(PAGE, PAND)
#pragma alloc_text(PAGE, PANDN)
#pragma alloc_text(PAGE, PAVGB)
#pragma alloc_text(PAGE, PAVGW)
#pragma alloc_text(PAGE, PCMPEQB)
#pragma alloc_text(PAGE, PCMPEQW)
#pragma alloc_text(PAGE, PCMPEQD)
#pragma alloc_text(PAGE, PCMPGTB)
#pragma alloc_text(PAGE, PCMPGTW)
#pragma alloc_text(PAGE, PCMPGTD)
#pragma alloc_text(PAGE, PEXTRW)
#pragma alloc_text(PAGE, PINSRW)
#pragma alloc_text(PAGE, PMADDWD)
#pragma alloc_text(PAGE, PMAXSW)
#pragma alloc_text(PAGE, PMAXUB)
#pragma alloc_text(PAGE, PMINSW)
#pragma alloc_text(PAGE, PMINUB)
#pragma alloc_text(PAGE, PMOVMSKB16)
#pragma alloc_text(PAGE, PMOVMSKB)
#pragma alloc_text(PAGE, PMULHUW)
#pragma alloc_text(PAGE, PMULHW)
#pragma alloc_text(PAGE, PMULLW)
#pragma alloc_text(PAGE, POP8)
#pragma alloc_text(PAGE, POP16)
#pragma alloc_text(PAGE, POP)
#pragma alloc_text(PAGE, POPAD16)
#pragma alloc_text(PAGE, POPAD)
#pragma alloc_text(PAGE, POPF)
#pragma alloc_text(PAGE, POPFD16)
#pragma alloc_text(PAGE, POPFD)
#pragma alloc_text(PAGE, POR)
#pragma alloc_text(PAGE, PSADBW)
#pragma alloc_text(PAGE, PSHUFW)
#pragma alloc_text(PAGE, PSLLW8)
#pragma alloc_text(PAGE, PSLLW)
#pragma alloc_text(PAGE, PSLLD8)
#pragma alloc_text(PAGE, PSLLD)
#pragma alloc_text(PAGE, PSLLQ8)
#pragma alloc_text(PAGE, PSLLQ)
#pragma alloc_text(PAGE, PSRAW8)
#pragma alloc_text(PAGE, PSRAW)
#pragma alloc_text(PAGE, PSRAD8)
#pragma alloc_text(PAGE, PSRAD)
#pragma alloc_text(PAGE, PSRLW8)
#pragma alloc_text(PAGE, PSRLW)
#pragma alloc_text(PAGE, PSRLD8)
#pragma alloc_text(PAGE, PSRLD)
#pragma alloc_text(PAGE, PSRLQ8)
#pragma alloc_text(PAGE, PSRLQ)
#pragma alloc_text(PAGE, PSUBB)
#pragma alloc_text(PAGE, PSUBW)
#pragma alloc_text(PAGE, PSUBD)
#pragma alloc_text(PAGE, PSUBSB)
#pragma alloc_text(PAGE, PSUBSW)
#pragma alloc_text(PAGE, PSUBUSB)
#pragma alloc_text(PAGE, PSUBUSW)
#pragma alloc_text(PAGE, PUNPCKHBW)
#pragma alloc_text(PAGE, PUNPCKHWD)
#pragma alloc_text(PAGE, PUNPCKHDQ)
#pragma alloc_text(PAGE, PUNPCKLBW)
#pragma alloc_text(PAGE, PUNPCKLWD)
#pragma alloc_text(PAGE, PUNPCKLDQ)
#pragma alloc_text(PAGE, PUSH8)
#pragma alloc_text(PAGE, PUSH16)
#pragma alloc_text(PAGE, PUSH)
//#pragma alloc_text(PAGE, //PUSHA)
#pragma alloc_text(PAGE, PUSHAD16)
#pragma alloc_text(PAGE, PUSHAD)
#pragma alloc_text(PAGE, PUSHF)
#pragma alloc_text(PAGE, PUSHFD16)
#pragma alloc_text(PAGE, PUSHFD)
#pragma alloc_text(PAGE, PXOR)
#pragma alloc_text(PAGE, RCL8)
#pragma alloc_text(PAGE, RCL16)
#pragma alloc_text(PAGE, RCL)
#pragma alloc_text(PAGE, RCR8)
#pragma alloc_text(PAGE, RCR16)
#pragma alloc_text(PAGE, RCR)
#pragma alloc_text(PAGE, ROL8)
#pragma alloc_text(PAGE, ROL16)
#pragma alloc_text(PAGE, ROL)
#pragma alloc_text(PAGE, ROR8)
#pragma alloc_text(PAGE, ROR16)
#pragma alloc_text(PAGE, ROR)
#pragma alloc_text(PAGE, RCPPS)
#pragma alloc_text(PAGE, RCPSS)
#pragma alloc_text(PAGE, RDMSR)
#pragma alloc_text(PAGE, RDPMC)
#pragma alloc_text(PAGE, RDTSC)
#pragma alloc_text(PAGE, REP)
#pragma alloc_text(PAGE, REPE)
#pragma alloc_text(PAGE, REPZ)
#pragma alloc_text(PAGE, REPNE)
#pragma alloc_text(PAGE, REPNZ)
#pragma alloc_text(PAGE, RETF)
#pragma alloc_text(PAGE, RET)
#pragma alloc_text(PAGE, RSM)
#pragma alloc_text(PAGE, RSQRTPS)
#pragma alloc_text(PAGE, RSQRTSS)
#pragma alloc_text(PAGE, SAHF)
#pragma alloc_text(PAGE, SAL8)
#pragma alloc_text(PAGE, SAL16)
#pragma alloc_text(PAGE, SAL)
#pragma alloc_text(PAGE, SAR8)
#pragma alloc_text(PAGE, SAR16)
#pragma alloc_text(PAGE, SAR)
#pragma alloc_text(PAGE, SHL8)
#pragma alloc_text(PAGE, SHL16)
#pragma alloc_text(PAGE, SHL)
#pragma alloc_text(PAGE, SHR8)
#pragma alloc_text(PAGE, SHR16)
#pragma alloc_text(PAGE, SHR)
#pragma alloc_text(PAGE, SBB8)
#pragma alloc_text(PAGE, SBB16)
#pragma alloc_text(PAGE, SBB)
#pragma alloc_text(PAGE, SCAS)
#pragma alloc_text(PAGE, SCASB16)
#pragma alloc_text(PAGE, SCASB)
#pragma alloc_text(PAGE, SCASD16)
#pragma alloc_text(PAGE, SCASD)
#pragma alloc_text(PAGE, SFENCE)
#pragma alloc_text(PAGE, SGDT)
#pragma alloc_text(PAGE, SIDT)
#pragma alloc_text(PAGE, SHLD16)
#pragma alloc_text(PAGE, SHLD)
#pragma alloc_text(PAGE, SHRD16)
#pragma alloc_text(PAGE, SHRD)
#pragma alloc_text(PAGE, SHUFPS)
#pragma alloc_text(PAGE, SLDT16)
#pragma alloc_text(PAGE, SLDT)
#pragma alloc_text(PAGE, SMSW16)
#pragma alloc_text(PAGE, SMSW)
#pragma alloc_text(PAGE, SQRTPS)
#pragma alloc_text(PAGE, SQRTSS)
#pragma alloc_text(PAGE, STC)
#pragma alloc_text(PAGE, STD)
#pragma alloc_text(PAGE, STI)
#pragma alloc_text(PAGE, STMXCSR)
#pragma alloc_text(PAGE, STOS)
#pragma alloc_text(PAGE, STOSB16)
#pragma alloc_text(PAGE, STOSB)
#pragma alloc_text(PAGE, STOSD16)
#pragma alloc_text(PAGE, STOSD)
#pragma alloc_text(PAGE, STR16)
#pragma alloc_text(PAGE, STR)
#pragma alloc_text(PAGE, SUB8)
#pragma alloc_text(PAGE, SUB16)
#pragma alloc_text(PAGE, SUB)
#pragma alloc_text(PAGE, SUBPS)
#pragma alloc_text(PAGE, SUBSS)
#pragma alloc_text(PAGE, SYSENTER)
#pragma alloc_text(PAGE, SYSEXIT)
#pragma alloc_text(PAGE, TEST16)
#pragma alloc_text(PAGE, TEST8)
#pragma alloc_text(PAGE, TEST)
#pragma alloc_text(PAGE, UCOMISS)
#pragma alloc_text(PAGE, UD2)
#pragma alloc_text(PAGE, UNPCKHPS)
#pragma alloc_text(PAGE, UNPCKLPS)
#pragma alloc_text(PAGE, VERR16)
#pragma alloc_text(PAGE, VERR)
#pragma alloc_text(PAGE, VERW16)
#pragma alloc_text(PAGE, VERW)
#pragma alloc_text(PAGE, WAIT)
#pragma alloc_text(PAGE, FWAIT)
#pragma alloc_text(PAGE, WBINVD)
#pragma alloc_text(PAGE, WRMSR)
#pragma alloc_text(PAGE, XADD8)
#pragma alloc_text(PAGE, XADD16)
#pragma alloc_text(PAGE, XADD)
#pragma alloc_text(PAGE, XCHG8)
#pragma alloc_text(PAGE, XCHG16)
#pragma alloc_text(PAGE, XCHG)
#pragma alloc_text(PAGE, XLAT)
#pragma alloc_text(PAGE, XLATB)
#pragma alloc_text(PAGE, XOR8)
#pragma alloc_text(PAGE, XOR16)
#pragma alloc_text(PAGE, XOR)
#pragma alloc_text(PAGE, XORPS)
#pragma alloc_text(PAGE, CMOVO16)
#pragma alloc_text(PAGE, CMOVO)
#pragma alloc_text(PAGE, CMOVNO16)
#pragma alloc_text(PAGE, CMOVNO)
#pragma alloc_text(PAGE, CMOVC16)
#pragma alloc_text(PAGE, CMOVC)
#pragma alloc_text(PAGE, CMOVAE16)
#pragma alloc_text(PAGE, CMOVAE)
#pragma alloc_text(PAGE, CMOVZ16)
#pragma alloc_text(PAGE, CMOVZ)
#pragma alloc_text(PAGE, CMOVNZ16)
#pragma alloc_text(PAGE, CMOVNZ)
#pragma alloc_text(PAGE, CMOVNA16)
#pragma alloc_text(PAGE, CMOVNA)
#pragma alloc_text(PAGE, CMOVNBE16)
#pragma alloc_text(PAGE, CMOVNBE)
#pragma alloc_text(PAGE, CMOVS16)
#pragma alloc_text(PAGE, CMOVS)
#pragma alloc_text(PAGE, CMOVNS16)
#pragma alloc_text(PAGE, CMOVNS)
#pragma alloc_text(PAGE, CMOVPE16)
#pragma alloc_text(PAGE, CMOVPE)
#pragma alloc_text(PAGE, CMOVPO16)
#pragma alloc_text(PAGE, CMOVPO)
#pragma alloc_text(PAGE, CMOVNGE16)
#pragma alloc_text(PAGE, CMOVNGE)
#pragma alloc_text(PAGE, CMOVNL16)
#pragma alloc_text(PAGE, CMOVNL)
#pragma alloc_text(PAGE, CMOVNG16)
#pragma alloc_text(PAGE, CMOVNG)
#pragma alloc_text(PAGE, CMOVNLE16)
#pragma alloc_text(PAGE, CMOVNLE)
#pragma alloc_text(PAGE, FCMOVB)
#pragma alloc_text(PAGE, FCMOVE)
#pragma alloc_text(PAGE, FCMOVBE)
#pragma alloc_text(PAGE, FCMOVU)
#pragma alloc_text(PAGE, FCMOVNB)
#pragma alloc_text(PAGE, FCMOVNE)
#pragma alloc_text(PAGE, FCMOVNBE)
#pragma alloc_text(PAGE, FCMOVNU)
#pragma alloc_text(PAGE, JO)
#pragma alloc_text(PAGE, JNO)
#pragma alloc_text(PAGE, JC)
#pragma alloc_text(PAGE, JAE)
#pragma alloc_text(PAGE, JZ)
#pragma alloc_text(PAGE, JNZ)
#pragma alloc_text(PAGE, JNA)
#pragma alloc_text(PAGE, JNBE)
#pragma alloc_text(PAGE, JS)
#pragma alloc_text(PAGE, JNS)
#pragma alloc_text(PAGE, JPE)
#pragma alloc_text(PAGE, JPO)
#pragma alloc_text(PAGE, JNGE)
#pragma alloc_text(PAGE, JNL)
#pragma alloc_text(PAGE, JNG)
#pragma alloc_text(PAGE, JNLE)
#pragma alloc_text(PAGE, JB)
#pragma alloc_text(PAGE, JNB)
#pragma alloc_text(PAGE, JECXZ16)
#pragma alloc_text(PAGE, JECXZ)
#pragma alloc_text(PAGE, LOOPNZ)
#pragma alloc_text(PAGE, LOOPZ)
#pragma alloc_text(PAGE, SETO8)
#pragma alloc_text(PAGE, SETNO8)
#pragma alloc_text(PAGE, SETB8)
#pragma alloc_text(PAGE, SETNB8)
#pragma alloc_text(PAGE, SETZ8)
#pragma alloc_text(PAGE, SETNZ8)
#pragma alloc_text(PAGE, SETNA8)
#pragma alloc_text(PAGE, SETNBE8)
#pragma alloc_text(PAGE, SETS8)
#pragma alloc_text(PAGE, SETNS8)
#pragma alloc_text(PAGE, SETPE8)
#pragma alloc_text(PAGE, SETPO8)
#pragma alloc_text(PAGE, SETNGE8)
#pragma alloc_text(PAGE, SETNL8)
#pragma alloc_text(PAGE, SETNG8)
#pragma alloc_text(PAGE, SETNLE8)
#pragma alloc_text(PAGE, CMPPS)
#pragma alloc_text(PAGE, SetAlc)
#pragma alloc_text(PAGE, PREFETCHT08)
#pragma alloc_text(PAGE, PREFETCHT18)
#pragma alloc_text(PAGE, PREFETCHT28)
#pragma alloc_text(PAGE, PREFETCHNTA8)
#endif
Func_Prefix  AAA (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF ((AL AND 0FH) > 9) OR (AF = 1) 
	// THEN 
	// AL � (AL + 6); 
	// AH � AH + 1; 
	// AF � 1; 
	// CF � 1; 
	// ELSE 
	// AF � 0; 
	// CF � 0; 
	// FI; 
	// AL � AL AND 0FH; 
	// Flags Affected 
	// The AF and CF flags are set to 1 if the adjustment results in a decimal carry; otherwise they are 
	// cleared to 0. The OF, SF, ZF, and PF flags are undefined. 
	// Exceptions (All Operating Modes) 
	// None. 

	//BreakPoint()
}

Func_Prefix  AAD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// tempAL � AL; 
	// tempAH � AH; 
	// AL � (tempAL + (tempAH * imm8)) AND FFH; (* imm8 is set to 0AH for the AAD mnemonic *) 
	// AH � 0 
	// The immediate value (imm8) is taken from the second byte of the instruction. 
	// Flags Affected 
	// The SF, ZF, and PF flags are set according to the result; the OF, AF, and CF flags are undefined. 
	// Exceptions (All Operating Modes) 
	// None. 

//	//BreakPoint()
}

Func_Prefix  AAM (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// tempAL � AL; 
	// AH � tempAL / imm8; (* imm8 is set to 0AH for the AAD mnemonic *) 
	// AL � tempAL MOD imm8; 
	// The immediate value (imm8) is taken from the second byte of the instruction. 
	// Flags Affected 
	// The SF, ZF, and PF flags are set according to the result. The OF, AF, and CF flags are undefined. 
	// Exceptions (All Operating Modes) 
	// None with the default immediate value of 0AH. If, however, an immediate value of 0 is used, it 
	// will cause a #DE (divide error) exception. 

	//BreakPoint()
}

Func_Prefix  AAS8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}
Func_Prefix  AAS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF ((AL AND 0FH) > 9) OR (AF = 1) 
	// THEN 
	// AL � AL � 6; 
	// AH � AH � 1; 
	// AF � 1; 
	// CF � 1; 
	// ELSE 
	// CF � 0; 
	// AF � 0; 
	// FI; 
	// AL � AL AND 0FH; 
	// Flags Affected 
	// The AF and CF flags are set to 1 if there is a decimal borrow; otherwise, they are cleared to 0. 
	// The OF, SF, ZF, and PF flags are undefined. 
	// Exceptions (All Operating Modes) 
	// None. 

	//BreakPoint()
}

Func_Prefix  ADC8 (VirtualMachine *posVm)
{
	UINT32	nEFlag = posVm->Context.osReg.nEFlag;
	UINT32	nEFlagOld, nOperand1, nOperand2 ;
	PAGED_CODE();

	FlagSaver(nEFlagOld);
	FlagRestore(nEFlag);

	nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm mov ecx , [ecx]
	__asm adc byte ptr [eax] , cl
	
	FlagSaver(nEFlag);
	FlagRestore(nEFlagOld);

	posVm->Context.osReg.nEFlag = nEFlag;
}

Func_Prefix  ADC16 (VirtualMachine *posVm)
{
	UINT32	nEFlag = posVm->Context.osReg.nEFlag;
	UINT32	nEFlagOld, nOperand1, nOperand2 ;
	PAGED_CODE();

	FlagSaver(nEFlagOld);
	FlagRestore(nEFlag);

	nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm mov ecx , [ecx]
	__asm adc byte ptr [eax] , cl
	
	FlagSaver(nEFlag);
	FlagRestore(nEFlagOld);

	posVm->Context.osReg.nEFlag = nEFlag;
}

Func_Prefix  ADC (VirtualMachine *posVm)
{
	UINT32	nEFlag = posVm->Context.osReg.nEFlag;
	UINT32	nEFlagOld, nOperand1, nOperand2 ;
	
	PAGED_CODE();
	
	
	FlagSaver(nEFlagOld);
	FlagRestore(nEFlag);

	nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm mov ecx , [ecx]
	__asm adc dword ptr [eax] , ecx
	
	FlagSaver(nEFlag);
	FlagRestore(nEFlagOld);
	
	posVm->Context.osReg.nEFlag = nEFlag;

	// DEST � DEST + SRC + CF; 
	// Flags Affected 
	// The OF, SF, ZF, AF, CF, and PF flags are set according to the result. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination is located in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

}

Func_Prefix  ADD8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	*(UINT8 *)posVm->Context.osOpcodeBlock.nOperand0 += *(UINT8 *)posVm->Context.osOpcodeBlock.nOperand1;
	FlagSaver(nEFlag);
	posVm->Context.osReg.nEFlag = nEFlag;
}

Func_Prefix  ADD16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	*(((UINT16 *)posVm->Context.osOpcodeBlock.nOperand0)) += *((UINT16 *)posVm->Context.osOpcodeBlock.nOperand1);
	FlagSaver(nEFlag);
	posVm->Context.osReg.nEFlag = nEFlag;
}

Func_Prefix  ADD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	*(((UINT32 *)posVm->Context.osOpcodeBlock.nOperand0)) += *((UINT32 *)posVm->Context.osOpcodeBlock.nOperand1);	
	FlagSaver(nEFlag);
	posVm->Context.osReg.nEFlag = nEFlag;

	// DEST � DEST + SRC; 
	// Flags Affected 
	// The OF, SF, ZF, AF, CF, and PF flags are set according to the result. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination is located in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 
}

Func_Prefix  ADDPS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// bayad baraye in dastor F3 Prefix ro barresi kard chenancheh TRUE bood dastor ADDSS ejra mishavad
	// Baraye in manzor index mmx pass shode be tabe index register haye EXX mishavad hamchenin size hafeze dar operand dovom
	// az 64 be 32 tabdil mishavad

	// DEST[31-0] = DEST[31-0] + SRC/m128[31-0]; 
	// DEST[63-32] = DEST[63-32] + SRC/m128[63-32]; 
	// DEST[95-64] = DEST[95-64] + SRC/m128[95-64]; 
	// DEST[127-96] = DEST[127-96] + SRC/m128[127-96]; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_add_ps(__m128 a, __m128 b) 
	// Adds the four SP FP values of a and b. 
	// Exceptions 
	// General protection exception if not aligned on 16-byte boundary, regardless of segment. 
	// Numeric Exceptions 
	// Overflow, Underflow, Invalid, Precision, Denormal. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF(fault-code) For a page fault 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #XM For an unmasked Streaming 
	// (CR4.OSXMMEXCPT =1). 
	// SIMD Extension numeric exception 
	// #UD For an unmasked Streaming 
	// (CR4.OSXMMEXCPT =0). 
	// SIMD Extension numeric exception 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #XM 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =1). 
	// #UD 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =0). 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF(fault-code) For a page fault. 

	//BreakPoint()
}

Func_Prefix  ADDSS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST[31-0] = DEST[31-0] + SRC/m32[31-0]; 
	// DEST[63-32] = DEST[63-32]; 
	// DEST[95-64] = DEST[95-64]; 
	// DEST[127-96] = DEST[127-96]; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_add_ss(__m128 a, __m128 b) 
	// Adds the lower SP FP (single-precision, floating-point) values of a and b; the upper three SP FP 
	// values are passed through from a. 
	// Exceptions 
	// None. 
	// Numeric Exceptions 
	// Overflow, Underflow, Invalid, Precision, Denormal. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, 
	// FS, or GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF(fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #AC For unaligned memory reference. To enable #AC exceptions, three 
	// conditions must be TRUE (CR0.AM is set; EFLAGS.AC is set; and 
	// current CPL is 3). 
	// #XM For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =1). 
	// #UD For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =0). 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// Interrupt 13 If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #XM For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =1). 
	// #UD For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =0). 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #AC For unaligned memory reference if the current privilege level is 3. 
	// #PF (fault-code) For a page fault. 

	//BreakPoint()
}

Func_Prefix  AND8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	UINT32	nOperand1, nOperand2 ;
	PAGED_CODE();
	
	nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm	mov	cl, byte ptr[ecx]
	__asm	and byte ptr [eax], cl
	FlagSaver(nEFlag);
	posVm->Context.osReg.nEFlag = nEFlag;
}

Func_Prefix  AND16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	UINT32	nOperand1, nOperand2 ;
	PAGED_CODE();
	nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm	mov	ecx, dword ptr[ecx]
	__asm	and word ptr [eax], cx
	FlagSaver(nEFlag);
	posVm->Context.osReg.nEFlag = nEFlag;
}

Func_Prefix  AND (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	UINT32	nOperand1, nOperand2 ;
	PAGED_CODE();
	nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm	mov	ecx, dword ptr[ecx]
	__asm	and dword ptr [eax], ecx
	FlagSaver(nEFlag);
	posVm->Context.osReg.nEFlag = nEFlag;
	// DEST � DEST AND SRC; 
	// Flags Affected 
	// The OF and CF flags are cleared; the SF, ZF, and PF flags are set according to the result. The 
	// state of the AF flag is undefined. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination operand points to a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 
}

Func_Prefix  ANDNPS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST[127-0] = NOT (DEST[127-0]) AND SRC/m128[127-0]; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_andnot_ps(__m128 a, __m128 b) 
	// Computes the bitwise AND-NOT of the four SP FP values of a and b. 
	// Exceptions 
	// General protection exception if not aligned on 16-byte boundary, regardless of segment. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF(fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real-Address Mode Exceptions 
	// Interrupt 13 If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF(fault-code) For a page fault. 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Comments 
	// The usage of Repeat Prefix (F3H) with ANDNPS is reserved. Different processor implementations 
	// may handle this prefix differently. Usage of this prefix with ANDNPS risks incompatibility 
	// with future processors. 

	//BreakPoint()
}

Func_Prefix  ANDPS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST[127-0] AND= SRC/m128[127-0]; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_and_ps(__m128 a, __m128 b) 
	// Computes the bitwise And of the four SP FP values of a and b. 
	// Exceptions 
	// General protection exception if not aligned on 16-byte boundary, regardless of segment. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF(fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real-Address Mode Exceptions 
	// Interrupt 13 If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual-8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF(fault-code) For a page fault. 
	// Comments 
	// The usage of Repeat Prefix (F3H) with ANDPS is reserved. Different processor implementations 
	// may handle this prefix differently. Usage of this prefix with ANDPS risks incompatibility 
	// with future processors. 

	//BreakPoint()
}

Func_Prefix  ARPL16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  ARPL (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF DEST(RPL) < SRC(RPL) 
	// THEN 
	// ZF � 1; 
	// DEST(RPL) � SRC(RPL); 
	// ELSE 
	// ZF � 0; 
	// FI; 
	// Flags Affected 
	// The ZF flag is set to 1 if the RPL field of the destination operand is less than that of the source 
	// operand; otherwise, is cleared to 0. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination is located in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #UD The ARPL instruction is not recognized in real-address mode. 
	// Virtual-8086 Mode Exceptions 
	// #UD The ARPL instruction is not recognized in virtual-8086 mode. 

	//BreakPoint()
}

Func_Prefix  BOUND16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  BOUND (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF (ArrayIndex < LowerBound OR ArrayIndex > (UppderBound + OperandSize/8])) 
	// (* Below lower bound or above upper bound *) 
	// THEN 
	// #BR; 
	// FI; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #BR If the bounds test fails. 
	// #UD If second operand is not a memory location. 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #BR If the bounds test fails. 
	// #UD If second operand is not a memory location. 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #BR If the bounds test fails. 
	// #UD If second operand is not a memory location. 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

//	//BreakPoint()
}

Func_Prefix  BSF16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  BSF (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF SRC = 0 
	// THEN 
	// ZF � 1; 
	// DEST is undefined; 
	// ELSE 
	// ZF � 0; 
	// temp � 0; 
	// WHILE Bit(SRC, temp) = 0 
	// DO 
	// temp � temp + 1; 
	// DEST � temp; 
	// OD; 
	// FI; 
	// Flags Affected 
	// The ZF flag is set to 1 if all the source operand is 0; otherwise, the ZF flag is cleared. The CF, 
	// OF, SF, AF, and PF, flags are undefined. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) 
	// If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  BSR16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  BSR (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF SRC = 0 
	// THEN 
	// ZF � 1; 
	// DEST is undefined; 
	// ELSE 
	// ZF � 0; 
	// temp � OperandSize � 1; 
	// WHILE Bit(SRC, temp) = 0 
	// DO 
	// temp � temp - 1; 
	// DEST � temp; 
	// OD; 
	// FI; 
	// Flags Affected 
	// The ZF flag is set to 1 if all the source operand is 0; otherwise, the ZF flag is cleared. The CF, 
	// OF, SF, AF, and PF, flags are undefined. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) 
	// If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  BSWAP16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  BSWAP (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// TEMP � DEST 
	// DEST(7..0) � TEMP(31..24) 
	// DEST(15..8) � TEMP(23..16) 
	// DEST(23..16) � TEMP(15..8) 
	// DEST(31..24) � TEMP(7..0) 
	// Flags Affected 
	// None. 
	// Exceptions (All Operating Modes) 
	// None. 

	//BreakPoint()
}

Func_Prefix  BT8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}

Func_Prefix  BT16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}

Func_Prefix  BT (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// CF � Bit(BitBase, BitOffset) 
	// Flags Affected 
	// The CF flag contains the value of the selected bit. The OF, SF, ZF, AF, and PF flags are 
	// undefined. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  BTC8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}

Func_Prefix  BTC16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}

Func_Prefix  BTC (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// CF � Bit(BitBase, BitOffset) 
	// Bit(BitBase, BitOffset) � NOT Bit(BitBase, BitOffset); 
	// Flags Affected 
	// The CF flag contains the value of the selected bit before it is complemented. The OF, SF, ZF, 
	// AF, and PF flags are undefined. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination operand points to a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  BTR8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}

Func_Prefix  BTR16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}

Func_Prefix  BTR (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// CF � Bit(BitBase, BitOffset) 
	// Bit(BitBase, BitOffset) � 0; 
	// Flags Affected 
	// The CF flag contains the value of the selected bit before it is cleared. The OF, SF, ZF, AF, and 
	// PF flags are undefined. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination operand points to a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  BTS8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}

Func_Prefix  BTS16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}

Func_Prefix  BTS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// CF � Bit(BitBase, BitOffset) 
	// Bit(BitBase, BitOffset) � 1; 
	// Flags Affected 
	// The CF flag contains the value of the selected bit before it is set. The OF, SF, ZF, AF, and PF 
	// flags are undefined. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination operand points to a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 
	//BreakPoint()
}


// No Flag Affected
Func_Prefix  CALL16 (VirtualMachine *posVm)
{
	PAGED_CODE();
	posVm->Context.osReg.EIP = ((UINT32*)(posVm->Context.osOpcodeBlock.nOperand0))[0];

	//BreakPoint()
}


Func_Prefix  CALL (VirtualMachine *posVm)
{
	PAGED_CODE();
	if (posVm->Context.osOpcodeBlock.nOperand0 == 0)
	{
		return;
	}
	PushStack(posVm, posVm->Context.osReg.EIP);
	switch(posVm->Context.osOpcodeBlock.nOperandsMemSize)
	{
	case 0:
		if (!posVm->Context.bFlagRM)
		{
			posVm->Context.osReg.EIP += (INT32)*((UINT32*)(posVm->Context.osOpcodeBlock.nOperand0));
			break;
		}

	default:
		// If CALL API, CALL ds:DIGIT[REG], CALL ds:DIGIT happend EIP set to nowhere
		if ((posVm->Context.bFlagRM && (posVm->Context.byMod_R_M == 0x15 || posVm->Context.byReg == 0x5 || (posVm->Context.bFlagSIB && posVm->Context.byBase == 0x5)))
			|| *((UINT32*)(posVm->Context.osOpcodeBlock.nOperand0)) < posVm->Context.posInfoOFFile->m_osPEExeHeader.ImageBase)
		{
			posVm->Context.osReg.EIP = 0xFFFFFFFF;
			break;
		}
		posVm->Context.osReg.EIP = *((UINT32*)(posVm->Context.osOpcodeBlock.nOperand0));
		break;
	}

	// IF near call 
	// THEN IF near relative call 
	// IF the instruction pointer is not within code segment limit THEN #GP(0); FI; 
	// THEN IF OperandSize = 32 
	// THEN 
	// IF stack not large enough for a 4-byte 
	// Push(EIP); 
	// EIP � EIP + DEST; (* DEST is rel32 *) 
	// ELSE (* OperandSize = 16 *) 
	// IF stack not large enough for a 2-byte 
	// Push(IP); 
	// EIP � (EIP + DEST) AND 0000FFFFH; (* DEST is rel16 *) 
	// FI; 
	// FI; 
	// ELSE (* near absolute call *) 
	// IF the instruction pointer is not within code segment limit THEN #GP(0); FI; 
	// IF OperandSize = 32 
	// THEN 
	// IF stack not large enough for a 4-byte 
	// Push(EIP); 
	// EIP � DEST; (* DEST is r/m32 *) 
	// ELSE (* OperandSize = 16 *) 
	// IF stack not large enough for a 2-byte 
	// Push(IP); 
	// EIP � DEST AND 0000FFFFH; (* DEST is r/m16 *) 
	// FI; 
	// FI: 
	// FI; 
	// IF far call AND (PE = 0 OR (PE = 1 AND VM = 1)) (* real-address or virtual-8086 mode *) 
	// THEN 
	// IF OperandSize = 32 
	// THEN 
	// IF stack not large enough for a 6-byte 
	// IF the instruction pointer is not within code segment limit THEN #GP(0); FI; 
	// Push(CS); (* padded with 16 high-order bits *) 
	// Push(EIP); 
	// CS � DEST[47:32]; (* DEST is ptr16:32 or [m16:32] *) 
	// EIP � DEST[31:0]; (* DEST is ptr16:32 or [m16:32] *) 
	// ELSE (* OperandSize = 16 *) 
	// IF stack not large enough for a 4-byte 
	// IF the instruction pointer is not within code segment limit THEN #GP(0); FI; 
	// Push(CS); 
	// Push(IP); 
	// CS � DEST[31:16]; (* DEST is ptr16:16 or [m16:16] *) 
	// EIP � DEST[15:0]; (* DEST is ptr16:16 or [m16:16] *) 
	// EIP � EIP AND 0000FFFFH; (* clear upper 16 bits *) 
	// FI; 
	// FI; 
	// IF far call AND (PE = 1 AND VM = 0) (* Protected mode, not virtual-8086 mode *) 
	// THEN 
	// IF segment selector in target operand null THEN #GP(0); FI; 
	// IF segment selector index not within descriptor table limits 
	// THEN #GP(new code segment selector); 
	// FI; 
	// Read type and access rights of selected segment descriptor; 
	// IF segment type is not a conforming or nonconforming code segment, call gate, 
	// task gate, or TSS THEN #GP(segment selector); FI; 
	// Depending on type and access rights 
	// GO TO CONFORMING-CODE-SEGMENT; 
	// GO TO NONCONFORMING-CODE-SEGMENT; 
	// GO TO CALL-GATE; 
	// GO TO TASK-GATE; 
	// GO TO TASK-STATE-SEGMENT; 
	// FI; 
	// CONFORMING-CODE-SEGMENT: 
	// IF DPL > CPL THEN #GP(new code segment selector); FI; 
	// IF segment not present THEN #NP(new code segment selector); FI; 
	// IF OperandSize = 32 
	// THEN 
	// IF stack not large enough for a 6-byte 
	// IF the instruction pointer is not within code segment limit THEN #GP(0); FI; 
	// Push(CS); (* padded with 16 high-order bits *) 
	// Push(EIP); 
	// CS � DEST(NewCodeSegmentSelector); 
	// (* segment descriptor information also loaded *) 
	// CS(RPL) � CPL 
	// EIP � DEST(offset); 
	// ELSE (* OperandSize = 16 *) 
	// IF stack not large enough for a 4-byte 
	// IF the instruction pointer is not within code segment limit THEN #GP(0); FI; 
	// Push(CS); 
	// Push(IP); 
	// CS � DEST(NewCodeSegmentSelector); 
	// (* segment descriptor information also loaded *) 
	// CS(RPL) � CPL 
	// EIP � DEST(offset) AND 0000FFFFH; (* clear upper 16 bits *) 
	// FI; 
	// END; 
	// NONCONFORMING-CODE-SEGMENT: 
	// IF (RPL > CPL) OR (DPL � CPL) THEN #GP(new code segment selector); FI; 
	// IF segment not present THEN #NP(new code segment selector); FI; 
	// IF stack not large enough for 
	// tempEIP � DEST(offset) 
	// IF OperandSize=16 
	// THEN 
	// tempEIP � tempEIP AND 0000FFFFH; (* clear upper 16 bits *) 
	// FI; 
	// IF tempEIP outside code segment limit THEN #GP(0); FI; 
	// IF OperandSize = 32 
	// THEN 
	// Push(CS); (* padded with 16 high-order bits *) 
	// Push(EIP); 
	// CS � DEST(NewCodeSegmentSelector); 
	// (* segment descriptor information also loaded *) 
	// CS(RPL) � CPL; 
	// EIP � tempEIP; 
	// ELSE (* OperandSize = 16 *) 
	// Push(CS); 
	// Push(IP); 
	// CS � DEST(NewCodeSegmentSelector); 
	// (* segment descriptor information also loaded *) 
	// CS(RPL) � CPL; 
	// EIP � tempEIP; 
	// FI; 
	// END; 
	// CALL-GATE: 
	// IF call gate DPL < CPL or RPL THEN #GP(call gate selector); FI; 
	// IF call gate not present THEN #NP(call gate selector); FI; 
	// IF call gate code-segment selector is null THEN #GP(0); FI; 
	// IF call gate code-segment selector index is outside descriptor table limits 
	// THEN #GP(code segment selector); FI; 
	// Read code segment descriptor; 
	// IF code-segment segment descriptor does not indicate a code segment 
	// OR code-segment segment descriptor DPL > CPL 
	// THEN #GP(code segment selector); FI; 
	// IF code segment not present THEN #NP(new code segment selector); FI; 
	// IF code segment is non-conforming AND DPL < CPL 
	// THEN go to MORE-PRIVILEGE; 
	// ELSE go to SAME-PRIVILEGE; 
	// FI; 
	// END; 
	// MORE-PRIVILEGE: 
	// IF current TSS is 32-bit TSS 
	// THEN 
	// TSSstackAddress � new code segment (DPL * 8) + 4 
	// IF (TSSstackAddress + 7) > TSS limit 
	// THEN #TS(current TSS selector); FI; 
	// newSS � TSSstackAddress + 4; 
	// newESP � stack address; 
	// ELSE (* TSS is 16-bit *) 
	// TSSstackAddress � new code segment (DPL * 4) + 2 
	// IF (TSSstackAddress + 4) > TSS limit 
	// THEN #TS(current TSS selector); FI; 
	// newESP � TSSstackAddress; 
	// newSS � TSSstackAddress + 2; 
	// FI; 
	// IF stack segment selector is null THEN #TS(stack segment selector); FI; 
	// IF stack segment selector index is not within its descriptor table limits 
	// THEN #TS(SS selector); FI 
	// Read code segment descriptor; 
	// IF stack segment selector�s RPL � DPL of code segment 
	// OR stack segment DPL � DPL of code segment 
	// OR stack segment is not a writable data segment 
	// THEN #TS(SS selector); FI 
	// IF stack segment not present THEN #SS(SS selector); FI; 
	// IF CallGateSize = 32 
	// THEN 
	// IF stack does not have room for parameters plus 16 bytes 
	// THEN #SS(SS selector); FI; 
	// IF CallGate(InstructionPointer) not within code segment limit THEN #GP(0); FI; 
	// SS � newSS; 
	// (* segment descriptor information also loaded *) 
	// ESP � newESP; 
	// CS:EIP � CallGate(CS:InstructionPointer); 
	// (* segment descriptor information also loaded *) 
	// Push(oldSS:oldESP); (* from calling procedure *) 
	// temp � parameter count from call gate, masked to 5 bits; 
	// Push(parameters from calling procedure�s stack, temp) 
	// Push(oldCS:oldEIP); (* 
	// ELSE (* CallGateSize = 16 *) 
	// IF stack does not have room for parameters plus 8 bytes 
	// THEN #SS(SS selector); FI; 
	// IF (CallGate(InstructionPointer) AND FFFFH) not within code segment limit 
	// THEN #GP(0); FI; 
	// SS � newSS; 
	// (* segment descriptor information also loaded *) 
	// ESP � newESP; 
	// CS:IP � CallGate(CS:InstructionPointer); 
	// (* segment descriptor information also loaded *) 
	// Push(oldSS:oldESP); (* from calling procedure *) 
	// temp � parameter count from call gate, masked to 5 bits; 
	// Push(parameters from calling procedure�s stack, temp) 
	// Push(oldCS:oldEIP); (* 
	// FI; 
	// CPL � CodeSegment(DPL) 
	// CS(RPL) � CPL 
	// END; 
	// SAME-PRIVILEGE: 
	// IF CallGateSize = 32 
	// THEN 
	// IF stack does not have room for 8 bytes 
	// THEN #SS(0); FI; 
	// IF EIP not within code segment limit then #GP(0); FI; 
	// CS:EIP � CallGate(CS:EIP) (* segment descriptor information also loaded *) 
	// Push(oldCS:oldEIP); (* 
	// ELSE (* CallGateSize = 16 *) 
	// IF stack does not have room for parameters plus 4 bytes 
	// THEN #SS(0); FI; 
	// IF IP not within code segment limit THEN #GP(0); FI; 
	// CS:IP � CallGate(CS:instruction pointer) 
	// (* segment descriptor information also loaded *) 
	// Push(oldCS:oldIP); (* 
	// FI; 
	// CS(RPL) � CPL 
	// END; 
	// TASK-GATE: 
	// IF task gate DPL < CPL or RPL 
	// THEN #GP(task gate selector); 
	// FI; 
	// IF task gate not present 
	// THEN #NP(task gate selector); 
	// FI; 
	// Read the TSS segment selector in the task-gate descriptor; 
	// IF TSS segment selector local/global bit is set to local 
	// OR index not within GDT limits 
	// THEN #GP(TSS selector); 
	// FI; 
	// Access TSS descriptor in GDT; 
	// IF TSS descriptor specifies that the TSS is busy (low-order 5 bits set to 00001) 
	// THEN #GP(TSS selector); 
	// FI; 
	// IF TSS not present 
	// THEN #NP(TSS selector); 
	// FI; 
	// SWITCH-TASKS (with nesting) to TSS; 
	// IF EIP not within code segment limit 
	// THEN #GP(0); 
	// FI; 
	// END; 
	// TASK-STATE-SEGMENT: 
	// IF TSS DPL < CPL or RPL 
	// OR TSS descriptor indicates TSS not available 
	// THEN #GP(TSS selector); 
	// FI; 
	// IF TSS is not present 
	// THEN #NP(TSS selector); 
	// FI; 
	// SWITCH-TASKS (with nesting) to TSS 
	// IF EIP not within code segment limit 
	// THEN #GP(0); 
	// FI; 
	// END; 
	// Flags Affected 
	// All flags are affected if a task switch occurs; no flags are affected if a task switch does not occur. 
	// Protected Mode Exceptions 
	// #GP(0) 
	// If target offset in destination operand is beyond the new code segment 
	// limit. 
	// If the segment selector in the destination operand is null. 
	// If the code segment selector in the gate is null. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #GP(selector) If code segment or gate or TSS selector index is outside descriptor table 
	// limits. 
	// If the segment descriptor pointed to by the segment selector in the 
	// destination operand is not for a conforming-code segment, nonconforming-
	// code segment, call gate, task gate, or task state segment. 
	// If the DPL for a nonconforming-code segment is not equal to the CPL or 
	// the RPL for the segment�s segment selector is greater than the CPL. 
	// If the DPL for a conforming-code segment is greater than the CPL. 
	// If the DPL from a call-gate, task-gate, or TSS segment descriptor is less 
	// than the CPL or than the RPL of the call-gate, task-gate, or TSS�s segment 
	// selector. 
	// If the segment descriptor for a segment selector from a call gate does not 
	// indicate it is a code segment. 
	// If the segment selector from a call gate is beyond the descriptor table 
	// limits. 
	// If the DPL for a code-segment obtained from a call gate is greater than the 
	// CPL. 
	// If the segment selector for a TSS has its local/global bit set for local. 
	// If a TSS segment descriptor specifies that the TSS is busy or not available. 
	// #SS(0) If pushing the 
	// the stack exceeds the bounds of the stack segment, when no stack switch 
	// occurs. 
	// If a memory operand effective address is outside the SS segment limit. 
	// #SS(selector) 
	// If pushing the 
	// the stack exceeds the bounds of the stack segment, when a stack switch 
	// occurs. 
	// If the SS register is being loaded as part of a stack switch and the segment 
	// pointed to is marked not present. 
	// If stack segment does not have room for the 
	// stack segment pointer, when stack switch occurs. 
	// #NP(selector) If a code segment, data segment, stack segment, call gate, task gate, or 
	// TSS is not present. 
	// #TS(selector) If the new stack segment selector and ESP are beyond the end of the TSS. 
	// If the new stack segment selector is null. 
	// If the RPL of the new stack segment selector in the TSS is not equal to the 
	// DPL of the code segment being accessed. 
	// If DPL of the stack segment descriptor for the new stack segment is not 
	// equal to the DPL of the code segment descriptor. 
	// If the new stack segment is not a writable data segment. 
	// If segment-selector index for stack segment is outside descriptor table 
	// limits. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If an unaligned memory access occurs when the CPL is 3 and alignment 
	// checking is enabled. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the target offset is beyond the code segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the target offset is beyond the code segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If an unaligned memory access occurs when alignment checking is 
	// enabled. 
}

Func_Prefix  CBW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CWDE (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF OperandSize = 16 (* instruction = CBW *) 
	// THEN AX � SignExtend(AL); 
	// ELSE (* OperandSize = 32, instruction = CWDE *) 
	// EAX � SignExtend(AX); 
	// FI; 
	// Flags Affected 
	// None. 
	// Exceptions (All Operating Modes) 
	// None. 
	// CDQ�Convert Double to Quad 
	// Refer to entry for CWD/CDQ � Convert Word to Doubleword/Convert Doubleword to Quad-
	// word. 

	//BreakPoint()
}

Func_Prefix  CLC (VirtualMachine *posVm)
{
	UINT32	nEFlag = posVm->Context.osReg.nEFlag;
	UINT32	nEFlagOld;

	FlagSaver(nEFlagOld);
	FlagRestore(nEFlag);

	__asm clc

	FlagSaver(nEFlag);	
	FlagRestore(nEFlagOld);

	nEFlag = posVm->Context.osReg.nEFlag;

	// CF � 0; 
	// Flags Affected 
	// The CF flag is cleared to 0. The OF, ZF, SF, AF, and PF flags are unaffected. 
	// Exceptions (All Operating Modes) 
	// None. 
}

Func_Prefix  CLD (VirtualMachine *posVm)
{
	PAGED_CODE();
	posVm->Context.osReg.nDF = 0;
	// DF � 0; 
	// Flags Affected 
	// The DF flag is cleared to 0. The CF, OF, ZF, SF, AF, and PF flags are unaffected. 
	// Exceptions (All Operating Modes) 
	// None. 
}

Func_Prefix  CLI (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF PE = 0 (* Executing in real-address mode *) 
	// THEN 
	// IF � 0; 
	// ELSE 
	// IF VM = 0 (* Executing in protected mode *) 
	// THEN 
	// IF CPL � IOPL 
	// THEN 
	// IF � 0; 
	// ELSE 
	// #GP(0); 
	// FI; 
	// FI; 
	// ELSE (* Executing in Virtual-8086 mode *) 
	// IF IOPL = 3 
	// THEN 
	// IF � 0 
	// ELSE 
	// #GP(0); 
	// FI; 
	// FI; 
	// FI; 
	// Flags Affected 
	// The IF is cleared to 0 if the CPL is equal to or less than the IOPL; otherwise, it is not affected. 
	// The other flags in the EFLAGS register are unaffected. 
	// Protected Mode Exceptions 
	// #GP(0) 
	// If the CPL is greater (has less privilege) than the IOPL of the current 
	// program or procedure. 
	// Real-Address Mode Exceptions 
	// None. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) 
	// If the CPL is greater (has less privilege) than the IOPL of the current 
	// program or procedure. 

	//BreakPoint()
}

Func_Prefix  CLTS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// CR0(TS) � 0; 
	// Flags Affected 
	// The TS flag in CR0 register is cleared. 
	// Protected Mode Exceptions 
	// #GP(0) If the CPL is greater than 0. 
	// Real-Address Mode Exceptions 
	// None. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If the CPL is greater than 0. 

	//BreakPoint()
}

Func_Prefix  CMC (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// CF � NOT CF; 
	// Flags Affected 
	// The CF flag contains the complement of its original value. The OF, ZF, SF, AF, and PF flags are 
	// unaffected. 
	// Exceptions (All Operating Modes) 
	// None. 

//	//BreakPoint()
}

Func_Prefix  CMOVO16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVO (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVNO16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVNO (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVC16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVC (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVAE16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVAE (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVZ16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVZ (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVNZ16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVNZ (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVNA16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVNA (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVNBE16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVNBE (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVS16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVNS16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVNS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVPE16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVPE (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVPO16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVPO (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVNGE16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVNGE (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVNL16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVNL (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVNG16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVNG (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVNLE16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMOVNLE (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// temp � DEST 
	// IF condition TRUE 
	// THEN 
	// DEST � SRC 
	// ELSE 
	// DEST � temp 
	// FI; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  CMP8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	UINT32	nOperand1, nOperand2 ;
	PAGED_CODE();
	nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm	mov	ecx , [ecx]
	__asm	cmp	byte ptr [eax] , cl
	FlagSaver(nEFlag);
	posVm->Context.osReg.nEFlag = nEFlag;
}

Func_Prefix  CMP16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMP (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	UINT32	nOperand1, nOperand2 ;
	PAGED_CODE();
	nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm	mov	ecx , [ecx]
	__asm	cmp	dword ptr [eax] , ecx
	FlagSaver(nEFlag);
	posVm->Context.osReg.nEFlag = nEFlag;
	// temp � SRC1 - SignExtend(SRC2); 
	// ModifyStatusFlags; (* Modify status flags in the same manner as the SUB instruction*) 
	// Flags Affected 
	// The CF, OF, SF, ZF, AF, and PF flags are set according to the result. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 
	// CMPPS�Packed Single-FP Compare 
	// Opcode 
	// Instruction Description 
	// 0F,C2,/r,ib 
	// CMPPS xmm1, Compare packed SP FP numbers from XMM2/Mem to packed SP 
	// xmm2/m128, imm8 FP numbers in XMM1 register using imm8 as predicate. 
	// Description 
	// For each individual pair of SP FP numbers, the CMPPS instruction 
	// or an all "0" 32-bit mask, using the comparison predicate specified by imm8. 
	// CMPPS xmm1, xmm2/m128, imm8 
	// (imm8=0) 
	// == 
	// == 
	// True False True False 
	// Figure 3-7. Operation of the CMPPS (Imm8=0) Instruction 
	// CMPPS xmm1, xmm2/m128,imm8 
	// (Imm8=1) 
	// <<<< 
	// False True False True 
	// Figure 3-8. Operation of the CMPPS (Imm8=1) Instruction 
	// Xmm1 10.0 2.0 
	// Xmm2/ 
	// m128 
	// Xmm1 
	// 10.0 
	// 00000000 11111111 00000000 11111111 
	// 9.0 
	// 10.0 2.0 9.0 1.0 Xmm1 
	// Xmm1 
	// Xmm2/
	// m128 3.0 11.0 9.0 4.0 
	// 00000000 00000000 11111111 11111111 
	// CMPPS xmm1, xmm2/m128, imm8 (imm8=2) 
	// <= <= <= 
	// Xmm1 
	// Xmm2/ 
	// m128 
	// Xmm1 
	// 3.0 
	// 00000000 11111111 11111111 11111111 
	// 9.0 
	// 10.0 2.0 
	// False True True True 
	// Figure 3-9. Operation of the CMPPS (Imm8=2) Instruction 
	// CMPPS xmm1, xmm2/m128,imm8 (Imm8=3) 
	// 10.0 QNaN 9.0 1.0 Xmm1 
	// ???? 
	// Xmm1 
	// Xmm2/
	// m128 3.0 11.0 9.0 QNaN 
	// 00000000 00000000 11111111 11111111 
	// True 
	// False False True 
	// Figure 3-10. Operation of the CMPPS (Imm8=3) Instruction 
	// CMPPS xmm1, xmm2/m128, imm8 (imm8=4) 
	// != != != 
	// Xmm1 
	// Xmm2/ 
	// m128 
	// Xmm1 
	// 3.0 
	// 00000000 11111111 11111111 11111111 
	// 9.0 
	// 10.0 2.0 
	// True True False True 
	// Figure 3-11. Operation of the CMPPS (Imm8=4) Instruction 
	// CMPPS xmm1, xmm2/m128,imm8 (Imm8=5) 
	// Xmm1 
	// Xmm2/
	// m128 3.0 
	// 10.0 
	// 11.0 9.0 4.0 
	// 2.0 9.0 1.0 
	// !< !< 
	// 00000000 00000000 11111111 11111111 
	// Xmm1 
	// True False True False 
	// Figure 3-12. Operation of the CMPPS (Imm8=5) Instruction 
	// CMPPS xmm1, xmm2/m128, imm8 (imm8=6) 
	// !<= !<= 
	// Xmm1 
	// Xmm2/ 
	// m128 
	// Xmm1 
	// 3.0 
	// 00000000 00000000 00000000 11111111 
	// 9.0 
	// 10.0 2.0 
	// True False False False 
	// Figure 3-13. Operation of the CMPPS (Imm8=6) Instruction 
	// CMPPS xmm1, xmm2/m128,imm8 (Imm8=7) 
	// Xmm1 
	// Xmm2/
	// m128 3.0 
	// 10.0 
	// 11.0 9.0 QNaN 
	// QNaN 9.0 1.0 
	// !? !? 
	// 00000000 00000000 11111111 11111111 
	// Xmm1 
	// True False True False 
	// Figure 3-14. Operation of the CMPPS (Imm8=7) Instruction 
	// Note that a subsequent computational instruction which uses this mask as an input operand will 
	// not generate a fault, since a mask of all "0�s" corresponds to an FP value of +0.0 and a mask of 
	// all "1�s" corresponds to an FP value of -qNaN. Some of the comparisons can be achieved only 
	// through software emulation. For these comparisons the programmer must swap the operands, 
	// copying registers when necessary to protect the data that will now be in the destination, and then 
	// perform the compare using a different predicate. The predicate to be used for these emulations 
	// is listed in the table under the heading "Emulation". The following table shows the different 
	// comparison types: 
	// : 
	// Predicate Description Relation Emulation imm8 
	// Encoding 
	// Result if 
	// NaN 
	// Operand 
	// Q/SNaN 
	// Operand 
	// Signals 
	// Invalid 
	// eq equal xmm1 == 
	// xmm2 
	// 000B False No 
	// lt less-than xmm1 < 
	// xmm2 
	// 001B False Yes 
	// le less-than-or-equal xmm1 <= 
	// xmm2 
	// 010B False Yes 
	// greater than xmm1 > 
	// xmm2 
	// swap, 
	// protect, lt 
	// False Yes 
	// greater-than-orequal 
	// xmm1 >= 
	// xmm2 
	// swap 
	// protect, le 
	// False Yes 
	// unord unordered xmm1 ? 
	// xmm2 
	// 011B True No 
	// neq not-equal !(xmm1 == 
	// xmm2) 
	// 100B True No 
	// nlt not-less-than !(xmm1 < 
	// xmm2) 
	// 101B True Yes 
	// nle not-less-than-orequal 
	// !(xmm1 <= 
	// xmm2) 
	// 110B True Yes 
	// not-greater-than !(xmm1 > 
	// xmm2) 
	// swap, 
	// protect, nlt 
	// True Yes 
	// not-greater-than-orequal 
	// !(xmm1 >= 
	// xmm2) 
	// swap, 
	// protect, nle 
	// True Yes 
	// ord ordered !(xmm1 ? 
	// xmm2) 
	// 111B False No 
	// NOTE: 
	// The greater-than, greater-than-or-equal, not-greater-than, and not-greater-than-or-equal relations are not 
	// directly implemented in hardware. 
	// Operation 


}

Func_Prefix  CMPSB (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMPSD16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMPSD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// temp �SRC1 - SRC2; 
	// SetStatusFlags(temp); 
	// IF (byte comparison) 
	// THEN IF DF = 0 
	// THEN 
	// (E)SI � (E)SI + 1; 
	// (E)DI � (E)DI + 1; 
	// ELSE 
	// (E)SI � (E)SI � 1; 
	// (E)DI � (E)DI � 1; 
	// FI; 
	// ELSE IF (word comparison) 
	// THEN IF DF = 0 
	// (E)SI � (E)SI + 2; 
	// (E)DI � (E)DI + 2; 
	// ELSE 
	// (E)SI � (E)SI � 2; 
	// (E)DI � (E)DI � 2; 
	// FI; 
	// ELSE (* doubleword comparison*) 
	// THEN IF DF = 0 
	// (E)SI � (E)SI + 4; 
	// (E)DI � (E)DI + 4; 
	// ELSE 
	// (E)SI � (E)SI � 4; 
	// (E)DI � (E)DI � 4; 
	// FI; 
	// FI; 
	// CMPS/CMPSB/CMPSW/CMPSD�Compare String Operands 
	// Flags Affected 
	// The CF, OF, SF, ZF, AF, and PF flags are set according to the temporary result of the comparison. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  CMPSS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF (imm8 = 0) THEN 
	// OP = "EQ"; 
	// ELSE 
	// IF (imm8 = 1) THEN 
	// OP = "LT"; 
	// ELSE 
	// IF (imm8 = 2) THEN 
	// OP = "LE"; 
	// ELSE 
	// IF (imm8 = 3) THEN 
	// OP = "UNORD"; 
	// ELSE 
	// IF (imm8 = 4) THEN 
	// OP = "NE"; 
	// ELSE 
	// IF (imm8 = 5) THEN 
	// OP = "NLT"; 
	// ELSE 
	// IF (imm8 = 6) THEN 
	// OP = "NLE"; 
	// ELSE 
	// IF (imm8 = 7) THEN 
	// OP = "ORD"; 
	// FI 
	// FI 
	// FI 
	// FI 
	// FI 
	// FI 
	// FI 
	// FI 
	// CMP0 = DEST[31-0] OP SRC/m128[31-0]; 
	// IF (CMP0 = TRUE) THEN 
	// DEST[31-0] = 0XFFFFFFFF; 
	// DEST[63-32] = DEST[63-32]; 
	// DEST[95-64] = DEST[95-64]; 
	// DEST[127-96] = DEST[127-96]; 
	// ELSE 
	// DEST[31-0] = 0X00000000; 
	// DEST[63-32] = DEST[63-32]; 
	// DEST[95-64] = DEST[95-64]; 
	// DEST[127-96] = DEST[127-96]; 
	// FI 
	// Intel C/C++ Compiler Intrinsic Equivalents 
	// __m128 _mm_cmpeq_ss(__m128 a, __m128 b) 
	// Compare for equality. 
	// __m128 _mm_cmplt_ss(__m128 a, __m128 b) 
	// Compare for less-than. 
	// __m128 _mm_cmple_ss(__m128 a, __m128 b) 
	// Compare for less-than-or-equal. 
	// __m128 _mm_cmpgt_ss(__m128 a, __m128 b) 
	// Compare for greater-than. 
	// __m128 _mm_cmpge_ss(__m128 a, __m128 b) 
	// Compare for greater-than-or-equal. 
	// __m128 _mm_cmpneq_ss(__m128 a, __m128 b) 
	// Compare for inequality. 
	// __m128 _mm_cmpnlt_ss(__m128 a, __m128 b) 
	// Compare for not-less-than. 
	// __m128 _mm_cmpnle_ss(__m128 a, __m128 b) 
	// Compare for not-less-than-or-equal. 
	// __m128 _mm_cmpngt_ss(__m128 a, __m128 b) 
	// Compare for not-greater-than. 
	// __m128 _mm_cmpnge_ss(__m128 a, __m128 b) 
	// Compare for not-greater-than-or-equal. 
	// __m128 _mm_cmpord_ss(__m128 a, __m128 b) 
	// Compare for ordered. 
	// __m128 _mm_cmpunord_ss(__m128 a, __m128 b) 
	// Compare for unordered. 
	// Exceptions 
	// None. 
	// Numeric Exceptions 
	// Invalid if sNaN operand, invalid if qNaN and predicate as listed in above table, denormal. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #AC For unaligned memory reference. To enable #AC exceptions, thtions must be TRUE (CR0.AM is set; EFLAGS.AC is set; currentree condiCPL 
	// is 3). 
	// #XM For an unmasked Streaming 
	// (CR4.OSXMMEXCPT =1). 
	// SIMD Extension numeric exception 
	// #UD For an unmasked Streaming 
	// (CR4.OSXMMEXCPT =0). 
	// SIMD Extension numeric exception 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #XM 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =1). 
	// #UD 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =0). 
	// #UD 
	// If CR4.OSFXSR(bit 9) = 0. 
	// #UD 
	// If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #AC For unaligned memory reference if the current privilege level is 3. 
	// #PF (fault-code) For a page fault. 
	// Comments 
	// Compilers and assemblers should implement the following 2-operand pseudo-ops in addition to 
	// the 3-operand CMPSS instruction. 
	// Pseudo-Op Implementation 
	// CMPEQSS xmm1, xmm2 
	// CMPLTSS xmm1, xmm2 
	// CMPLESS xmm1, xmm2 
	// CMPUNORDSS xmm1, xmm2 
	// CMPNEQSS xmm1, xmm2 
	// CMPNLTSS xmm1, xmm2 
	// CMPNLESS xmm1, xmm2 
	// CMPORDSS xmm1, xmm2 
	// CMPSS xmm1,xmm2, 0 
	// CMPSS xmm1,xmm2, 1 
	// CMPSS xmm1,xmm2, 2 
	// CMPSS xmm1,xmm2, 3 
	// CMPSS xmm1,xmm2, 4 
	// CMPSS xmm1,xmm2, 5 
	// CMPSS xmm1,xmm2, 6 
	// CMPSS xmm1,xmm2, 7 
	// The greater-than relations not implemented in hardware require more than one instruction to 
	// emulate in software and therefore should not be implemented as pseudo-ops. (For these, the 
	// programmer should reverse the operands of the corresponding less than relations and use move 
	// instructions to ensure that the mask is moved to the correct destination register and that the 
	// source operand is left intact.) 
	// Bits 7-4 of the immediate field are reserved. Different processors may handle them differently. 
	// Usage of these bits risks incompatibility with future processors. 

	//BreakPoint()
}

Func_Prefix  CMPXCHG8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMPXCHG16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CMPXCHG (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// (* accumulator = AL, AX, or EAX, depending on whether *) 
	// (* a byte, word, or doubleword comparison is being performed*) 
	// IF accumulator = DEST 
	// THEN 
	// ZF � 1 
	// DEST � SRC 
	// ELSE 
	// ZF � 0 
	// accumulator � DEST 
	// FI; 
	// Flags Affected 
	// The ZF flag is set if the values in the destination operand and register AL, AX, or EAX are equal; 
	// otherwise it is cleared. The CF, PF, AF, SF, and OF flags are set according to the results of the 
	// comparison operation. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination is located in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  CMPXCHG8B (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF (EDX:EAX = DEST) 
	// ZF � 1 
	// DEST � ECX:EBX 
	// ELSE 
	// ZF � 0 
	// EDX:EAX � DEST 
	// Flags Affected 
	// The ZF flag is set if the destination operand and EDX:EAX are equal; otherwise it is cleared. 
	// The CF, PF, AF, SF, and OF flags are unaffected. 
	// Protected Mode Exceptions 
	// #UD If the destination operand is not a memory location. 
	// #GP(0) If the destination is located in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #UD If the destination operand is not a memory location. 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #UD If the destination operand is not a memory location. 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  COMISS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// OF = 0; 
	// SF = 0; 
	// AF = 0; 
	// IF ((DEST[31-0] UNORD SRC/m32[31-0]) = TRUE) THEN 
	// ZF = 1; 
	// PF = 1; 
	// CF = 1; 
	// ELSE 
	// IF ((DEST[31-0] GTRTHAN SRC/m32[31-0]) = TRUE)THEN 
	// ZF = 0; 
	// PF = 0; 
	// CF = 0; 
	// ELSE 
	// IF ((DEST[31-0] LESSTHAN SRC/m32[31-0]) = TRUE THEN 
	// ZF = 0; 
	// PF = 0; 
	// CF = 1; 
	// ELSE 
	// ZF = 1; 
	// PF = 0; 
	// CF = 0; 
	// FI 
	// FI 
	// FI 
	// COMISS�Scalar Ordered Single-FP Compare And Set EFLAGS 
	// Intel C/C++ Compiler Intrinsic Equivalents 
	// int_mm_comieq_ss(__m128 a, __m128 b) 
	// Compares the lower SP FP value of a and b for a equal to b. If a and b are equal, 1 is 
	// Otherwise 0 is 
	// int_mm_comilt_ss(__m128 a, __m128 b) 
	// Compares the lower SP FP value of a and b for a less than b. If a is less than b, 1 is 
	// Otherwise 0 is 
	// int_mm_comile_ss(__m128 a, __m128 b) 
	// Compares the lower SP FP value of a and b for a less than or equal to b. If a is less than or equal 
	// to b, 1 is 
	// int_mm_comigt_ss(__m128 a, __m128 b) 
	// Compares the lower SP FP value of a and b for a greater than b. If a is greater than b are equal, 
	// 1 is 
	// int_mm_comige_ss(__m128 a, __m128 b) 
	// Compares the lower SP FP value of a and b for a greater than or equal to b. If a is greater than 
	// or equal to b, 1 is 
	// int_mm_comineq_ss(__m128 a, __m128 b) 
	// Compares the lower SP FP value of a and b for a not equal to b. If a and b are not equal, 1 is 
	// 
	// Exceptions 
	// None. 
	// COMISS�Scalar Ordered Single-FP Compare And Set EFLAGS 
	// Numeric Exceptions 
	// Invalid (if sNaN or qNaN operands), Denormal. Integer EFLAGS values will not be updated in 
	// the presence of unmasked numeric exceptions. 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #AC For unaligned memory reference. To enabtions must be TRUE(CR0.AM is set; EFLAle #AC excGS.AC is septions, three condiet; 
	// current CPL is 3). 
	// #XM For an unmasked Streaming SIMD(CR4.OSXMMEXCPT =1). 
	// Extension numeric exception 
	// #UD For an unmasked Streaming SIMD(CR4.OSXMMEXCPT =0). 
	// Extension numeric exception 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #XM 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =1). 
	// #UD 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =0). 
	// #UD 
	// If CR4.OSFXSR(bit 9) = 0. 
	// #UD 
	// If CPUID.XMM(EDX bit 25) = 0. 
	// COMISS�Scalar Ordered Single-FP Compare And Set EFLAGS 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #AC For unaligned memory reference if the current privilege level is 3. 
	// #PF (fault-code) For a page fault. 
	// Comments 
	// COMISS differs from UCOMISS and COMISS in that it signals an invalid numeric exception 
	// when a source operand is either a qNaN or an sNaN operand; UCOMISS signals invalid only a 
	// source operand is an sNaN. 
	// The usage of Repeat (F2H, F3H) and Operand-Size (66H) prefixes with COMISS is reserved. 
	// Different processor implementations may handle this prefix differently. Usage of this prefix 
	// with COMISS risks incompatibility with future processors. 

	//BreakPoint()
}

Func_Prefix  CPUID (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// CASE (EAX) OF 
	// EAX = 0: 
	// EAX � highest input value understood by CPUID; (* 2 for Pentium� Pro processor *) 
	// EBX � Vendor identification string; 
	// EDX � Vendor identification string; 
	// ECX � Vendor identification string; 
	// BREAK; 
	// EAX = 1: 
	// EAX[3:0] � Stepping ID; 
	// EAX[7:4] � Model; 
	// EAX[11:8] � Family; 
	// EAX[13:12] � Processor type; 
	// EAX[31:12] � Reserved; 
	// EBX � Reserved;ECX � Reserved; 
	// EDX � Feature flags; (* Refer to Figure 3-27 *) 
	// BREAK; 
	// EAX = 2: 
	// EAX � Cache and TLB information; 
	// EBX � Cache and TLB information; 
	// ECX � Cache and TLB information; 
	// EDX � Cache and TLB information; 
	// BREAK; 
	// DEFAULT: (* EAX > highest value recognized by CPUID *) 
	// EAX � reserved, undefined; 
	// EBX � reserved, undefined; 
	// ECX � reserved, undefined; 
	// EDX � reserved, undefined; 
	// BREAK; 
	// ESAC; 
	// Flags Affected 
	// None. 
	// Exceptions (All Operating Modes) 
	// None. 

	//BreakPoint()
}

Func_Prefix  CVTPI2PS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// bayad baraye in dastor F3 Prefix ro barresi kard chenancheh TRUE bood dastor CVTSI2SS ejra mishavad
	// Baraye in manzor index mmx pass shode be tabe index register haye EXX mishavad hamchenin size hafeze dar operand dovom
	// az 64 be 32 tabdil mishavad


	// DEST[31-0] = (float) (SRC/m64[31-0]); 
	// DEST[63-32] = (float) (SRC/m64[63-32]); 
	// DEST[95-64] = DEST[95-64]; 
	// DEST[127-96] = DEST[127-96]; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_cvt_pi2ps(__m128 a, __m64 b) 
	// __m128 _mm_cvtpi32_ps(__m128 a, __m64 b) 
	// Convert the two 32-bit integer values in packed form in b to two SP FP values; the upper two 
	// SP FP values are passed through from a. 
	// CVTPI2PS�Packed Signed INT32 to Packed Single-FP Conversion 
	// Exceptions 
	// None. 
	// Numeric Exceptions 
	// Precision. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #AC For unaligned memory reference. To enable #AC exceptions, thtions must be TRUE(CR0.AM is set; EFLAGS.AC is set; current 
	// ree condi-
	// CPL is 3). 
	// #XM For an unmasked Streaming 
	// (CR4.OSXMMEXCPT =1). 
	// SIMD Extension numeric exception 
	// #UD For an unmasked Streaming 
	// (CR4.OSXMMEXCPT =0). 
	// SIMD Extension numeric exception 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// CVTPI2PS�Packed Signed INT32 to Packed Single-FP Conversion 
	// Real Address Mode Exceptions 
	// Interrupt 13 If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #AC For unaligned memory reference. 
	// #XM For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =1). 
	// #UD For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =0). 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #AC For unaligned memory reference if the current privilege level is 3. 
	// #PF (fault-code) For a page fault. 
	// CVTPI2PS�Packed Signed INT32 to Packed Single-FP Conversion 
	// Comments 
	// This instruction behaves identically to original MMX� instructions, in the presence of x87-FP 
	// instructions: 
	// � 
	// Transition from x87-FP to MMX� technology (TOS=0, FP valid bits set to all valid). 
	// � 
	// MMX� instructions write ones (1s) to the exponent part of the corresponding x87-FP 
	// register. 
	// However, the use of a memory source operand with this instruction will not result in the above 
	// transition from x87-FP to MMX� technology. 
	// Prioritizing for fault and assist behavior for CVTPI2PS is as follows: 
	// Memory source 
	// 1. 
	// Invalid opcode (CR0.EM=1) 
	// 2. 
	// DNA (CR0.TS=1) 
	// 3. 
	// #SS or #GP, for limit violation 
	// 4. 
	// #PF, page fault 
	// 5. 
	// Streaming SIMD Extensions numeric fault (i.e., precision) 
	// Register source 
	// 1. 
	// Invalid opcode (CR0.EM=1) 
	// 2. 
	// DNA (CR0.TS=1) 
	// 3. 
	// #MF, pending x87-FP fault signaled 
	// 4. 
	// After 
	// 5. 
	// Streaming SIMD Extensions numeric fault (i.e., precision) 

	//BreakPoint()
}

Func_Prefix  CVTPS2PI (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//
	// bayad baraye in dastor F3 Prefix ro barresi kard chenancheh TRUE bood dastor CVTSS2SI ejra mishavad
	// Baraye in manzor index mmx pass shode be tabe index register haye EXX mishavad hamchenin size hafeze dar operand dovom
	// az 64 be 32 tabdil mishavad
	//
	// DEST[31-0] = (int) (SRC/m64[31-0]); 
	// DEST[63-32]= (int) (SRC/m64[63-32]); 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m64 _mm_cvt_ps2pi(__m128 a) 
	// __m64 _mm_cvtps_pi32(__m128 a) 
	// Convert the two lower SP FP values of a to two 32-bit integers with truncation, 
	// integers in packed form. 
	// CVTPS2PI�Packed Single-FP to Packed INT32 Conversion 
	// Exceptions 
	// None. 
	// Numeric Exceptions 
	// Invalid, Precision. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #AC For unaligned memory reference. To enable #AC exceptions, ttions must be TRUE(CR0.AM is set; EFLAGS.AC is set; current 
	// hree condi-
	// CPL is 3). 
	// #XM For an unmasked Streaming 
	// (CR4.OSXMMEXCPT =1). 
	// SIMD Extension numeric exception 
	// #UD For an unmasked Streaming 
	// (CR4.OSXMMEXCPT =0). 
	// SIMD Extension numeric exception 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// CVTPS2PI�Packed Single-FP to Packed INT32 Conversion 
	// Real Address Mode Exceptions 
	// Interrupt 13 If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #XM For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =1). 
	// #UD For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =0). 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #AC For unaligned memory reference if the current privilege level is 3. 
	// #PF (fault-code) For a page fault. 
	// CVTPS2PI�Packed Single-FP to Packed INT32 Conversion 
	// Comments 
	// This instruction behaves identically to original MMX� instructions, in the presence of x87-FP 
	// instructions: 
	// � 
	// Transition from x87-FP to MMX� technology (TOS=0, FP valid bits set to all valid). 
	// � 
	// MMX� instructions write ones (1s) to the exponent part of the corresponding x87-FP 
	// register. 
	// Prioritizing for fault and assist behavior for CVTPS2PI is as follows: 
	// Memory source 
	// 1. 
	// Invalid opcode (CR0.EM=1) 
	// 2. 
	// DNA (CR0.TS=1) 
	// 3. 
	// #MF, pending x87-FP fault signaled 
	// 4. 
	// After 
	// 5. 
	// #SS or #GP, for limit violation 
	// 6. 
	// #PF, page fault 
	// 7. 
	// Streaming SIMD Extensions numeric fault (i.e., invalid, precision) 
	// Register source 
	// 1. 
	// Invalid opcode (CR0.EM=1) 
	// 2. 
	// DNA (CR0.TS=1) 
	// 3. 
	// #MF, pending x87-FP fault signaled 
	// 4. 
	// After 
	// 5. 
	// Streaming SIMD Extensions numeric fault (i.e., precision) 

	//BreakPoint()
}

Func_Prefix  CVTSI2SS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST[31-0] = (float) (R/m32); 
	// DEST[63-32] = DEST[63-32]; 
	// DEST[95-64] = DEST[95-64]; 
	// DEST[127-96] = DEST[127-96]; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_cvt_si2ss(__m128 a, int b) 
	// __m128 _mm_cvtsi32_ss(__m128 a, int b) 
	// Convert the 32-bit integer value b to an SP FP value; the upper three SP FP values are passed 
	// through from a. 
	// CVTSI2SS�Scalar Signed INT32 to Single-FP Conversion 
	// Exceptions 
	// None. 
	// Numeric Exceptions 
	// Precision. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #AC For unaligned memory reference. To enable #AC exceptions, thtions must be TRUE(CR0.AM is set; EFLAGS.AC is set; current 
	// ree condi-
	// CPL is 3). 
	// #XM For an unmasked Streaming 
	// (CR4.OSXMMEXCPT =1). 
	// SIMD Extension numeric exception 
	// #UD For an unmasked Streaming 
	// (CR4.OSXMMEXCPT =0). 
	// SIMD Extension numeric exception 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// CVTSI2SS�Scalar Signed INT32 to Single-FP Conversion 
	// Real Address Mode Exceptions 
	// Interrupt 13 If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #XM For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =1). 
	// #UD For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =0). 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #AC For unaligned memory reference if the current privilege level is 3. 
	// #PF (fault-code) For a page fault. 

	//BreakPoint()
}

Func_Prefix  CVTSS2SI (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// r32 = (int) (SRC/m32[31-0]); 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// int_mm_cvt_ss2si(__m128 a) 
	// int_mm_cvtss_si32(__m128 a) 
	// Convert the lower SP FP value of a to a 32-bit integer according to the current rounding mode. 
	// CVTSS2SI�Scalar Single-FP to Signed INT32 Conversion 
	// Exceptions 
	// None. 
	// Numeric Exceptions 
	// Invalid, Precision. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #AC For unaligned memory reference.To enabtions must be TRUE(CR0.AM is set; EFLAle #AC excGS.AC is septions, three condiet; 
	// current CPL is 3). 
	// #XM For an unmasked Streaming SIMD(CR4.OSXMMEXCPT =1). 
	// Extension numeric exception 
	// #UD For an unmasked Streaming SIMD(CR4.OSXMMEXCPT = 0). 
	// Extension numeric exception 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// CVTSS2SI�Scalar Single-FP to Signed INT32 Conversion 
	// Real Address Mode Exceptions 
	// Interrupt 13 If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #XM For an unmasked Streaming 
	// (CR4.OSXMMEXCPT =1). 
	// SIMD Extension numeric exception 
	// #UD For an unmasked Streaming 
	// (CR4.OSXMMEXCPT =0). 
	// SIMD Extension numeric exception 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #AC For unaligned memory reference if the current privilege level is 3. 
	// #PF (fault-code) For a page fault. 

	//BreakPoint()
}

Func_Prefix  CVTTPS2PI (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// bayad baraye in dastor F3 Prefix ro barresi kard chenancheh TRUE bood dastor CVTTSS2SI ejra mishavad
	// Baraye in manzor index mmx pass shode be tabe index register haye EXX mishavad hamchenin size hafeze dar operand dovom
	// az 64 be 32 tabdil mishavad


	// DEST[31-0] = (int) (SRC/m64[31-0]); 
	// DEST[63-32]= (int) (SRC/m64[63-32]); 
	// CVTTPS2PI�Packed Single-FP to Packed INT32 Conversion 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m64 _mm_cvtt_ps2pi(__m128 a) 
	// __m64 _mm_cvttps_pi32(__m128 a) 
	// Convert the two lower SP FP values of a to two 32-bit integers according to the current rounding 
	// mode, 
	// Exceptions 
	// None. 
	// Numeric Exceptions 
	// Invalid, Precision. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #AC For unaligned memory reference. To enable #AC exceptions, ttions must be TRUE(CR0.AM is set; EFLAGS.AC is set; current 
	// hree condi-
	// CPL is 3). 
	// #XM For an unmasked Streaming 
	// (CR4.OSXMMEXCPT =1). 
	// SIMD Extension numeric exception 
	// #UD For an unmasked Streaming 
	// (CR4.OSXMMEXCPT =0). 
	// SIMD Extension numeric exception 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// CVTTPS2PI�Packed Single-FP to Packed INT32 Conversion 
	// Real Address Mode Exceptions 
	// Interrupt 13 If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #XM For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =1). 
	// #UD For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =0). 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #AC For unaligned memory reference if the current privilege level is 3. 
	// #PF (fault-code) For a page fault. 
	// CVTTPS2PI�Packed Single-FP to Packed INT32 Conversion 
	// Comments 
	// This instruction behaves identically to original MMX� instructions, in the presence of x87-FP 
	// instructions, including: 
	// � 
	// Transition from x87-FP to MMX� technology (TOS=0, FP valid bits set to all valid). 
	// � 
	// MMX� instructions write ones (1s) to the exponent part of the corresponding x87-FP 
	// register. 
	// Prioritizing for fault and assist behavior for CVTTPS2PI is as follows: 
	// Memory source 
	// 1. 
	// Invalid opcode (CR0.EM=1) 
	// 2. 
	// DNA (CR0.TS=1) 
	// 3. 
	// #MF, pending x87-FP fault signaled 
	// 4. 
	// After 
	// 5. 
	// #SS or #GP, for limit violation 
	// 6. 
	// #PF, page fault 
	// 7. 
	// Streaming SIMD Extensions numeric fault (i.e., precision) 
	// Register source 
	// 1. 
	// Invalid opcode (CR0.EM=1) 
	// 2. 
	// DNA (CR0.TS=1) 
	// 3. 
	// #MF, pending x87-FP fault signaled 
	// 4. 
	// After 
	// 5. 
	// Streaming SIMD Extensions numeric fault (i.e., precision) 

	//BreakPoint()
}

Func_Prefix  CVTTSS2SI (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// r32 = (INT) (SRC/m32[31-0]); 
	// CVTTSS2SI�Scalar Single-FP to Signed INT32 Conversion 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// int_mm_cvtt_ss2si(__m128 a) 
	// int_mm_cvttss_si32(__m128 a) 
	// Convert the lower SP FP value of a to a 32-bit integer according to the current rounding mode. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// _m64_m_from_int(int_i) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// _m64_mm_cvttsi32_si64(int_i) 
	// Convert the integer object i to a 64-bit __m64 object. The integer value is zero extended to 64 
	// bits. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// int_m_to_int(__m64_m) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// int_mm_cvtsi64_si32(__m64_m) 
	// Convert the lower 32 bits of the __m64 object m to an integer. 
	// Exceptions 
	// None. 
	// Numeric Exceptions 
	// Invalid, Precision. 
	// CVTTSS2SI�Scalar Single-FP to Signed INT32 Conversion 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #AC For unaligned memory reference. To enabtions must be TRUE(CR0.AM is set; EFLAle #AC excGS.AC is septions, three condiet; 
	// current CPL is 3). 
	// #XM For an unmasked Streaming SIMD(CR4.OSXMMEXCPT =1). 
	// Extension numeric exception 
	// #UD For an unmasked Streaming SIMD(CR4.OSXMMEXCPT =0). 
	// Extension numeric exception 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #XM 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =1). 
	// #UD 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =0). 
	// #UD 
	// If CR4.OSFXSR(bit 9) = 0. 
	// #UD 
	// If CPUID.XMM(EDX bit 25) = 0. 
	// CVTTSS2SI�Scalar Single-FP to Signed INT32 Conversion 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #AC For unaligned memory reference if the current privilege level is 3. 
	// #PF (fault-code) For a page fault. 

	//BreakPoint()
}

Func_Prefix  CWD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  CDQ (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF OperandSize = 16 (* CWD instruction *) 
	// THEN DX � SignExtend(AX); 
	// ELSE (* OperandSize = 32, CDQ instruction *) 
	// EDX � SignExtend(EAX); 
	// FI; 
	// Flags Affected 
	// None. 
	// Exceptions (All Operating Modes) 
	// None. 
	// CWDE�Convert Word to Doubleword 
	// Refer to entry for CBW/CWDE�Convert Byte to Word/Convert Word to Doubleword. 

	//BreakPoint()
}

Func_Prefix  DAA8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}
Func_Prefix  DAA (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF (((AL AND 0FH) > 9) or AF = 1) 
	// THEN 
	// AL � AL + 6; 
	// CF � CF OR CarryFromLastAddition; (* CF OR carry from AL � AL + 6 *) 
	// AF � 1; 
	// ELSE 
	// AF � 0; 
	// FI; 
	// IF ((AL AND F0H) > 90H) or CF = 1) 
	// THEN 
	// AL � AL + 60H; 
	// CF � 1; 
	// ELSE 
	// CF � 0; 
	// FI; 
	// Example 
	// ADD AL, BL Before: AL=79H BL=35H EFLAGS(OSZAPC)=XXXXXX 
	// After: AL=AEH BL=35H EFLAGS(0SZAPC)=110000 
	// DAA Before: AL=2EH BL=35H EFLAGS(OSZAPC)=110000 
	// After: AL=04H BL=35H EFLAGS(0SZAPC)=X00101 
	// Flags Affected 
	// The CF and AF flags are set if the adjustment of the value results in a decimal carry in either 
	// digit of the result (refer to the �Operation� section above). The SF, ZF, and PF flags are set 
	// according to the result. The OF flag is undefined. 
	// Exceptions (All Operating Modes) 
	// None. 

	//BreakPoint()
}

Func_Prefix DAS8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}

Func_Prefix  DAS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF (AL AND 0FH) > 9 ORAF = 1 
	// THEN 
	// AL � AL - 6; 
	// CF � CF OR BorrowFromLastSubtraction; (* CF OR borrow from AL � AL - 6 *) 
	// AF � 1; 
	// ELSE AF � 0; 
	// FI; 
	// IF ((AL > 9FH) or CF = 1) 
	// THEN 
	// AL � AL - 60H; 
	// CF � 1; 
	// ELSE CF � 0; 
	// FI; 
	// Example 
	// SUB AL, BL Before: AL=35H BL=47H EFLAGS(OSZAPC)=XXXXXX 
	// After: AL=EEH BL=47H EFLAGS(0SZAPC)=010111 
	// DAA Before: AL=EEH BL=47H EFLAGS(OSZAPC)=010111 
	// After: AL=88H BL=47H EFLAGS(0SZAPC)=X10111 
	// Flags Affected 
	// The CF and AF flags are set if the adjustment of the value results in a decimal borrow in either 
	// digit of the result (refer to the �Operation� section above). The SF, ZF, and PF flags are set 
	// according to the result. The OF flag is undefined. 
	// Exceptions (All Operating Modes) 
	// None. 

	//BreakPoint()
}

Func_Prefix  DEC8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	UINT32	nOperand1, nOperand2 ;
	PAGED_CODE();

	nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm dec byte ptr [eax]
	FlagSaver(nEFlag);
	posVm->Context.osReg.nEFlag = nEFlag;
}

Func_Prefix  DEC16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	UINT32	nOperand1, nOperand2 ;
	PAGED_CODE();

	nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm dec word ptr [eax]
	FlagSaver(nEFlag);
	posVm->Context.osReg.nEFlag = nEFlag;
}

Func_Prefix  DEC (VirtualMachine *posVm)
{
	UINT32	nEFlag, nOperand1;
	PAGED_CODE();

	nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	__asm	mov	eax	,  nOperand1	
	__asm dec dword ptr [eax]
	FlagSaver(nEFlag);
	posVm->Context.osReg.nEFlag = nEFlag;
	// DEST � DEST � 1; 
	// Flags Affected 
	// The CF flag is not affected. The OF, SF, ZF, AF, and PF flags are set according to the result. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination operand is located in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 
}

Func_Prefix  DIV8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}

Func_Prefix  DIV16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}

Func_Prefix  DIV (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF SRC = 0 
	// THEN #DE; (* divide error *) 
	// FI; 
	// IF OpernadSize = 8 (* word/byte operation *) 
	// THEN 
	// temp � AX / SRC; 
	// IF temp > FFH 
	// THEN #DE; (* divide error *) ; 
	// ELSE 
	// AL � temp; 
	// AH � AX MOD SRC; 
	// FI; 
	// ELSE 
	// IF OperandSize = 16 (* doubleword/word operation *) 
	// THEN 
	// temp � DX:AX / SRC; 
	// IF temp > FFFFH 
	// THEN #DE; (* divide error *) ; 
	// ELSE 
	// AX � temp; 
	// DX � DX:AX MOD SRC; 
	// FI; 
	// ELSE (* quaUINT32/doubleword operation *) 
	// temp � EDX:EAX / SRC; 
	// IF temp > FFFFFFFFH 
	// THEN #DE; (* divide error *) ; 
	// ELSE 
	// EAX � temp; 
	// EDX � EDX:EAX MOD SRC; 
	// FI; 
	// FI; 
	// FI; 
	// Flags Affected 
	// The CF, OF, SF, ZF, AF, and PF flags are undefined. 
	// Protected Mode Exceptions 
	// #DE If the source operand (divisor) is 0 
	// If the quotient is too large for the designated register. 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #DE 
	// If the source operand (divisor) is 0. 
	// If the quotient is too large for the designated register. 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #DE If the source operand (divisor) is 0. 
	// If the quotient is too large for the designated register. 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  DIVPS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// bayad baraye in dastor F3 Prefix ro barresi kard chenancheh TRUE bood dastor DIVSS ejra mishavad
	// Baraye in manzor index mmx pass shode be tabe index register haye EXX mishavad hamchenin size hafeze dar operand dovom
	// az 64 be 32 tabdil mishavad


	// DEST[31-0] = DEST[31-0] / (SRC/m128[31-0]); 
	// DEST[63-32] = DEST[63-32] / (SRC/m128[63-32]); 
	// DEST[95-64] = DEST[95-64] / (SRC/m128[95-64]); 
	// DEST[127-96] = DEST[127-96] / (SRC/m128[127-96]); 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_div_ps(__m128 a, __m128 b) 
	// Divides the four SP FP values of a and b. 
	// Exceptions 
	// General protection exception if not aligned on 16-byte boundary, regardless of segment. 
	// Numeric Exceptions 
	// Overflow, Underflow, Invalid, Divide-by-Zero, Precision, Denormal. 
	// Protected Mode Exceptions 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #GP (0) for an illegal memory operand effective address in the CS, Dor GS segments. 
	// S, ES, FS, 
	// #SS (0) for an illegal address in the SS segment. 
	// #PF (fault-code) for a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #XM For an unmasked Streaming 
	// (CR4.OSXMMEXCPT =1) 
	// SIMD Extension numeric exception 
	// #UD For an unmasked Streaming 
	// (CR4.OSXMMEXCPT =0). 
	// SIMD Extension numeric exception 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// Interrupt 13 If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #XM For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =1). 
	// #UD For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =0). 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF(fault-code). If a page fault occurs. 

	//BreakPoint()
}

Func_Prefix  DIVSS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST[31-0] = DEST[31-0] / (SRC/m32[31-0]); 
	// DEST[63-32] = DEST[63-32]; 
	// DEST[95-64] = DEST[95-64]; 
	// DEST[127-96] = DEST[127-96]; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_div_ss(__m128 a, __m128 b) 
	// Divides the lower SP FP values of a and b; the upper three SP FP values are passed through from 
	// a. 
	// Exceptions 
	// None. Overflow, Underflow, Invalid, Divide-by-Zero, Precision, Denormal. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #AC For unaligned memory reference. To enabtions must be TRUE(CR0.AM is set; EFLAle #AC excGS.AC is septions, three condiet; 
	// current CPL is 3). 
	// #XM For an unmasked Streaming SIMD(CR4.OSXMMEXCPT =1). 
	// Extension numeric exception 
	// #UD For an unmasked Streaming SIMD(CR4.OSXMMEXCPT =0). 
	// Extension numeric exception 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #XM 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =1). 
	// #UD 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =0). 
	// #UD 
	// If CR4.OSFXSR(bit 9) = 0. 
	// #UD 
	// If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #AC For unaligned memory reference if the current privilege level is 3. 
	// #PF (fault-code) For a page fault. 

	//BreakPoint()
}

Func_Prefix  EMMS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// FPUTagWord � FFFF 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// void_m_empty() 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// void_mm_empty() 
	// Clears the MMX� technology state. 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// Real-Address Mode Exceptions 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// Virtual-8086 Mode Exceptions 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 

	//BreakPoint()
}

Func_Prefix  ENTER8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  ENTER (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// NestingLevel � NestingLevel MOD 32 
	// IF StackSize = 32 
	// THEN 
	// Push(EBP) ; 
	// FrameTemp � ESP; 
	// ELSE (* StackSize = 16*) 
	// Push(BP); 
	// FrameTemp � SP; 
	// FI; 
	// IF NestingLevel = 0 
	// THEN GOTO CONTINUE; 
	// FI; 
	// IF (NestingLevel > 0) 
	// FOR i � 1 TO (NestingLevel - 1) 
	// DO 
	// IF OperandSize = 32 
	// THEN 
	// IF StackSize = 32 
	// EBP � EBP - 4; 
	// Push([EBP]); (* doubleword push *) 
	// ELSE (* StackSize = 16*) 
	// BP � BP - 4; 
	// Push([BP]); (* doubleword push *) 
	// FI; 
	// ELSE (* OperandSize = 16 *) 
	// IF StackSize = 32 
	// THEN 
	// EBP � EBP - 2; 
	// Push([EBP]); (* word push *) 
	// ELSE (* StackSize = 16*) 
	// BP � BP - 2; 
	// Push([BP]); (* word push *) 
	// FI; 
	// FI; 
	// OD; 
	// IF OperandSize = 32 
	// THEN 
	// Push(FrameTemp); (* doubleword push *) 
	// ELSE (* OperandSize = 16 *) 
	// Push(FrameTemp); (* word push *) 
	// FI; 
	// GOTO CONTINUE; 
	// FI; 
	// CONTINUE: 
	// IF StackSize = 32 
	// THEN 
	// EBP � FrameTemp 
	// ESP � EBP - Size; 
	// ELSE (* StackSize = 16*) 
	// BP � FrameTemp 
	// SP � BP - Size; 
	// FI; 
	// END; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #SS(0) If the new value of the SP or ESP register is outside the stack segment 
	// limit. 
	// #PF(fault-code) If a page fault occurs. 
	// Real-Address Mode Exceptions 
	// #SS(0) 
	// If the new value of the SP or ESP register is outside the stack segment 
	// limit. 
	// Virtual-8086 Mode Exceptions 
	// #SS(0) 
	// If the new value of the SP or ESP register is outside the stack segment 
	// limit. 
	// #PF(fault-code) 
	// If a page fault occurs. 

	//BreakPoint()
}

Func_Prefix  F2XM1 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// ST(0) � (2ST(0) - 1); 
	// FPU Flags Affected 
	// C1 Set to 0 if stack underflow occurred. 
	// Indicates rounding direction if the inexact result exception (#P) is generated: 
	// 0 = not roundup; 1 = roundup. 
	// C0, C2, C3 Undefined. 
	// Floating-Point Exceptions 
	// #IS Stack underflow occurred. 
	// #IA Source operand is an sNaN value or unsupported format. 
	// #D Result is a denormal value. 
	// #U Result is too small for destination format. 
	// #P Value cannot be represented exactly in destination format. 
	// Protected Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Real-Address Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #NM EM or TS in CR0 is set. 

	//BreakPoint()
}

Func_Prefix  FABS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// ST(0) � |ST(0)| 
	// FPU Flags Affected 
	// C1 Set to 0 if stack underflow occurred; otherwise, cleared to 0. 
	// C0, C2, C3 Undefined. 
	// Floating-Point Exceptions 
	// #IS Stack underflow occurred. 
	// Protected Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Real-Address Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #NM EM or TS in CR0 is set. 

	//BreakPoint()
}

Func_Prefix  FADD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FADDP (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FIADD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF instruction is FIADD 
	// THEN 
	// DEST � DEST + ConvertExtendedReal(SRC); 
	// ELSE (* source operand is real number *) 
	// DEST � DEST + SRC; 
	// FI; 
	// IF instruction = FADDP 
	// THEN 
	// PopRegisterStack; 
	// FI; 
	// FPU Flags Affected 
	// C1 Set to 0 if stack underflow occurred. 
	// Indicates rounding direction if the inexact result exception (#P) is generated: 
	// 0 = not roundup; 1 = roundup. 
	// C0, C2, C3 Undefined. 
	// Floating-Point Exceptions 
	// #IS Stack underflow occurred. 
	// #IA Operand is an sNaN value or unsupported format. 
	// Operands are infinities of unlike sign. 
	// #D Source operand is a denormal value. 
	// #U Result is too small for destination format. 
	// #O Result is too large for destination format. 
	// #P Value cannot be represented exactly in destination format. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix FBLD8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint();
}

Func_Prefix  FBLD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// TOP � TOP - 1; 
	// ST(0) � ExtendedReal(SRC); 
	// FPU Flags Affected 
	// C1 Set to 1 if stack overflow occurred; otherwise, cleared to 0. 
	// C0, C2, C3 Undefined. 
	// Floating-Point Exceptions 
	// #IS Stack overflow occurred. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) 
	// If a memory operand effective address is outside the SS segment limit. 
	// #NM 
	// EM or TS in CR0 is set. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  FBSTP8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint();
}

Func_Prefix  FBSTP (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST � BCD(ST(0)); 
	// PopRegisterStack; 
	// FPU Flags Affected 
	// C1 Set to 0 if stack underflow occurred. 
	// Indicates rounding direction if the inexact exception (#P) is generated: 
	// 0 = not roundup; 1 = roundup. 
	// C0, C2, C3 Undefined. 
	// Floating-Point Exceptions 
	// #IS Stack underflow occurred. 
	// #IA Source operand is empty; contains a NaN, ��, or unsupported format; or 
	// contains value that exceeds 18 BCD digits in length. 
	// #P Value cannot be represented exactly in destination format. 
	// Protected Mode Exceptions 
	// #GP(0) If a segment register is being loaded with a segment selector that points to 
	// a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  FCHS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// SignBit(ST(0)) � NOT (SignBit(ST(0))) 
	// FPU Flags Affected 
	// C1 Set to 0 if stack underflow occurred; otherwise, cleared to 0. 
	// C0, C2, C3 Undefined. 
	// Floating-Point Exceptions 
	// #IS Stack underflow occurred. 
	// Protected Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Real-Address Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #NM EM or TS in CR0 is set. 

	//BreakPoint()
}

Func_Prefix  FCLEX (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FNCLEX (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// FPUStatusWord[0..7] � 0; 
	// FPUStatusWord[15] � 0; 
	// FPU Flags Affected 
	// The PE, UE, OE, ZE, DE, IE, ES, SF, and B flags in the FPU status word are cleared. The C0, 
	// C1, C2, and C3 flags are undefined. 
	// Floating-Point Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Real-Address Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #NM EM or TS in CR0 is set. 

	//BreakPoint()
}

Func_Prefix  FCMOVB (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FCMOVE (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FCMOVBE (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FCMOVU (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FCMOVNB (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FCMOVNE (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FCMOVNBE (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FCMOVNU (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF condition TRUE 
	// ST(0) � ST(i) 
	// FI; 
	// FPU Flags Affected 
	// C1 Set to 0 if stack underflow occurred. 
	// C0, C2, C3 Undefined. 
	// Floating-Point Exceptions 
	// #IS Stack underflow occurred. 
	// Integer Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Real-Address Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #NM EM or TS in CR0 is set. 

	//BreakPoint()
}

Func_Prefix  FCOM (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FCOMP (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FCOMPP (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// CASE (relation of operands) OF 
	// ST > SRC: C3, C2, C0 � 000; 
	// ST < SRC: C3, C2, C0 � 001; 
	// ST = SRC: C3, C2, C0 � 100; 
	// ESAC; 
	// IF ST(0) or SRC = NaN or unsupported format 
	// THEN 
	// #IA 
	// IF FPUControlWord.IM = 1 
	// THEN 
	// C3, C2, C0 � 111; 
	// FI; 
	// FI; 
	// IF instruction = FCOMP 
	// THEN 
	// PopRegisterStack; 
	// FI; 
	// IF instruction = FCOMPP 
	// THEN 
	// PopRegisterStack; 
	// PopRegisterStack; 
	// FI; 
	// FPU Flags Affected 
	// C1 Set to 0 if stack underflow occurred; otherwise, cleared to 0. 
	// C0, C2, C3 Refer to table on previous page. 
	// Floating-Point Exceptions 
	// #IS Stack underflow occurred. 
	// #IA One or both operands are NaN values or have unsupported formats. 
	// Register is marked empty. 
	// #D One or both operands are denormal values. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// #NM 
	// EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) 
	// If a memory operand effective address is outside the SS segment limit. 
	// #NM 
	// EM or TS in CR0 is set. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  FCOMI (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FCOMIP (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FUCOMI (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FUCOMIP (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// CASE (relation of operands) OF 
	// ST(0) > ST(i): ZF, PF, CF � 000; 
	// ST(0) < ST(i): ZF, PF, CF � 001; 
	// ST(0) = ST(i): ZF, PF, CF � 100; 
	// ESAC; 
	// IF instruction is FCOMI or FCOMIP 
	// THEN 
	// IF ST(0) or ST(i) = NaN or unsupported format 
	// THEN 
	// #IA 
	// IF FPUControlWord.IM = 1 
	// THEN 
	// ZF, PF, CF � 111; 
	// FI; 
	// FI; 
	// FI; 
	// IF instruction is FUCOMI or FUCOMIP 
	// THEN 
	// IF ST(0) or ST(i) = QNaN, but not SNaN or unsupported format 
	// THEN 
	// ZF, PF, CF � 111; 
	// ELSE (* ST(0) or ST(i) is SNaN or unsupported format *) 
	// #IA; 
	// IF FPUControlWord.IM = 1 
	// THEN 
	// ZF, PF, CF � 111; 
	// FI; 
	// FI; 
	// FI; 
	// IF instruction is FCOMIP or FUCOMIP 
	// THEN 
	// PopRegisterStack; 
	// FI; 
	// FCOMI/FCOMIP/FUCOMI/FUCOMIP�Compare Real and Set 
	// FPU Flags Affected 
	// C1 Set to 0 if stack underflow occurred; otherwise, cleared to 0. 
	// C0, C2, C3 Not affected. 
	// Floating-Point Exceptions 
	// #IS Stack underflow occurred. 
	// #IA (FCOMI or FCOMIP instruction) One or both operands are NaN values or 
	// have unsupported formats. 
	// (FUCOMI or FUCOMIP instruction) One or both operands are sNaN 
	// values (but not qNaNs) or have undefined formats. Detection of a qNaN 
	// value does not raise an invalid-operand exception. 
	// Protected Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Real-Address Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #NM EM or TS in CR0 is set. 

	//BreakPoint()
}

Func_Prefix  FCOS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF |ST(0)| < 263 
	// THEN 
	// C2 � 0; 
	// ST(0) � cosine(ST(0)); 
	// ELSE (*source operand is out-of-range *) 
	// C2 � 1; 
	// FI; 
	// FPU Flags Affected 
	// C1 Set to 0 if stack underflow occurred. 
	// Indicates rounding direction if the inexact result exception (#P) is generated: 
	// 0 = not roundup; 1 = roundup. 
	// Undefined if C2 is 1. 
	// C2 Set to 1 if source operand is outside the range -263 to +263; otherwise, 
	// cleared to 0. 
	// C0, C3 Undefined. 
	// Floating-Point Exceptions 
	// #IS Stack underflow occurred. 
	// #IA Source operand is an sNaN value, �, or unsupported format. 
	// #D Result is a denormal value. 
	// #U Result is too small for destination format. 
	// #P Value cannot be represented exactly in destination format. 
	// Protected Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Real-Address Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #NM EM or TS in CR0 is set. 

	//BreakPoint()
}

Func_Prefix  FDECSTP (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF TOP = 0 
	// THEN TOP � 7; 
	// ELSE TOP � TOP � 1; 
	// FI; 
	// FPU Flags Affected 
	// The C1 flag is set to 0; otherwise, cleared to 0. The C0, C2, and C3 flags are undefined. 
	// Floating-Point Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Real-Address Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #NM EM or TS in CR0 is set. 

	//BreakPoint()
}

Func_Prefix  FDIV (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FDIVP (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FIDIV (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF SRC = 0 
	// THEN 
	// #Z 
	// ELSE 
	// IF instruction is FIDIV 
	// THEN 
	// DEST � DEST / ConvertExtendedReal(SRC); 
	// ELSE (* source operand is real number *) 
	// DEST � DEST / SRC; 
	// FI; 
	// FI; 
	// IF instruction = FDIVP 
	// THEN 
	// PopRegisterStack 
	// FI; 
	// FPU Flags Affected 
	// C1 
	// Set to 0 if stack underflow occurred. 
	// Indicates rounding direction if the inexact result exception (#P) is generated: 
	// 0 = not roundup; 1 = roundup. 
	// C0, C2, C3 
	// Undefined. 
	// Floating-Point Exceptions 
	// #IS Stack underflow occurred. 
	// #IA Operand is an sNaN value or unsupported format. 
	// �� / ��; �0 / �0 
	// #D 
	// Result is a denormal value. 
	// #Z 
	// DEST / �0, where DEST is not equal to �0. 
	// #U 
	// Result is too small for destination format. 
	// #O 
	// Result is too large for destination format. 
	// #P 
	// Value cannot be represented exactly in destination format. 
	// Protected Mode Exceptions 
	// #GP(0) 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) 
	// If a memory operand effective address is outside the SS segment limit. 
	// #NM 
	// EM or TS in CR0 is set. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// #NM 
	// EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  FDIVR (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FDIVRP (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FIDIVR (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF DEST = 0 
	// THEN 
	// #Z 
	// ELSE 
	// IF instruction is FIDIVR 
	// THEN 
	// DEST � ConvertExtendedReal(SRC) / DEST; 
	// ELSE (* source operand is real number *) 
	// DEST � SRC / DEST; 
	// FI; 
	// FI; 
	// IF instruction = FDIVRP 
	// THEN 
	// PopRegisterStack 
	// FI; 
	// FPU Flags Affected 
	// C1 
	// Set to 0 if stack underflow occurred. 
	// Indicates rounding direction if the inexact result exception (#P) is generated: 
	// 0 = not roundup; 1 = roundup. 
	// C0, C2, C3 
	// Undefined. 
	// Floating-Point Exceptions 
	// #IS Stack underflow occurred. 
	// #IA Operand is an sNaN value or unsupported format. 
	// �� / ��; �0 / �0 
	// #D 
	// Result is a denormal value. 
	// #Z 
	// SRC / �0, where SRC is not equal to �0. 
	// #U 
	// Result is too small for destination format. 
	// #O 
	// Result is too large for destination format. 
	// #P 
	// Value cannot be represented exactly in destination format. 
	// Protected Mode Exceptions 
	// #GP(0) 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) 
	// If a memory operand effective address is outside the SS segment limit. 
	// #NM 
	// EM or TS in CR0 is set. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// #NM 
	// EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  FFREE (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// TAG(i) � 11B; 
	// FPU Flags Affected 
	// C0, C1, C2, C3 undefined. 
	// Floating-Point Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Real-Address Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #NM EM or TS in CR0 is set. 

	//BreakPoint()
}

Func_Prefix  FICOM (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FICOMP (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// CASE (relation of operands) OF 
	// ST(0) > SRC: C3, C2, C0 � 000; 
	// ST(0) < SRC: C3, C2, C0 � 001; 
	// ST(0) = SRC: C3, C2, C0 � 100; 
	// Unordered: C3, C2, C0 � 111; 
	// ESAC; 
	// IF instruction = FICOMP 
	// THEN 
	// PopRegisterStack; 
	// FI; 
	// FPU Flags Affected 
	// C1 Set to 0 if stack underflow occurred; otherwise, set to 0. 
	// C0, C2, C3 Refer to table on previous page. 
	// Floating-Point Exceptions 
	// #IS Stack underflow occurred. 
	// #IA One or both operands are NaN values or have unsupported formats. 
	// #D One or both operands are denormal values. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  FILD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// TOP � TOP - 1; 
	// ST(0) � ExtendedReal(SRC); 
	// FPU Flags Affected 
	// C1 Set to 1 if stack overflow occurred; cleared to 0 otherwise. 
	// C0, C2, C3 Undefined. 
	// Floating-Point Exceptions 
	// #IS Stack overflow occurred. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) 
	// If a memory operand effective address is outside the SS segment limit. 
	// #NM 
	// EM or TS in CR0 is set. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  FINCSTP (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF TOP = 7 
	// THEN TOP � 0; 
	// ELSE TOP � TOP + 1; 
	// FI; 
	// FPU Flags Affected 
	// The C1 flag is set to 0; otherwise, cleared to 0. The C0, C2, and C3 flags are undefined. 
	// Floating-Point Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Real-Address Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #NM EM or TS in CR0 is set. 

	//BreakPoint()
}

Func_Prefix  FINIT (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FNINIT (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// FPUControlWord � 037FH; 
	// FPUStatusWord � 0; 
	// FPUTagWord � FFFFH; 
	// FPUDataPointer � 0; 
	// FPUInstructionPointer � 0; 
	// FPULastInstructionOpcode � 0; 
	// FPU Flags Affected 
	// C0, C1, C2, C3 cleared to 0. 
	// Floating-Point Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Real-Address Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Comments 
	// This instruction has no effect on the state of SIMD floating-point registers. 

	//BreakPoint()
}

Func_Prefix  FIST (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FISTP (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST � Integer(ST(0)); 
	// IF instruction = FISTP 
	// THEN 
	// PopRegisterStack; 
	// FI; 
	// FPU Flags Affected 
	// C1 Set to 0 if stack underflow occurred. 
	// Indicates rounding direction of if the inexact exception (#P) is generated: 
	// 0 = not roundup; 1 = roundup. 
	// Cleared to 0 otherwise. 
	// C0, C2, C3 Undefined. 
	// Floating-Point Exceptions 
	// #IS Stack underflow occurred. 
	// #IA Source operand is too large for the destination format 
	// Source operand is a NaN value or unsupported format. 
	// #P Value cannot be represented exactly in destination format. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination is located in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// #NM 
	// EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) 
	// If a memory operand effective address is outside the SS segment limit. 
	// #NM 
	// EM or TS in CR0 is set. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  FLD8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint();
}

Func_Prefix  FLD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF SRC is ST(i) 
	// THEN 
	// temp � ST(i) 
	// TOP � TOP - 1; 
	// IF SRC is memory-operand 
	// THEN 
	// ST(0) � ExtendedReal(SRC); 
	// ELSE (* SRC is ST(i) *) 
	// ST(0) � temp; 
	// FPU Flags Affected 
	// C1 Set to 1 if stack overflow occurred; otherwise, cleared to 0. 
	// C0, C2, C3 Undefined. 
	// Floating-Point Exceptions 
	// #IS Stack overflow occurred. 
	// #IA Source operand is an sNaN value or unsupported format. 
	// #D Source operand is a denormal value. Does not occur if the source operand 
	// is in extended-real format. 
	// Protected Mode Exceptions 
	// #GP(0) If destination is located in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// #NM 
	// EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) 
	// If a memory operand effective address is outside the SS segment limit. 
	// #NM 
	// EM or TS in CR0 is set. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  FLD1 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FLDL2T (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FLDL2E (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FLDPI (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FLDLG2 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FLDLN2 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FLDZ (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// TOP � TOP - 1; 
	// ST(0) � CONSTANT; 
	// FPU Flags Affected 
	// C1 Set to 1 if stack overflow occurred; otherwise, cleared to 0. 
	// C0, C2, C3 Undefined. 
	// Floating-Point Exceptions 
	// #IS Stack overflow occurred. 
	// Protected Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Real-Address Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// FLD1/FLDL2T/FLDL2E/FLDPI/FLDLG2/FLDLN2/FLDZ�Load 
	// Virtual-8086 Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Intel Architecture Compatibility 
	// When the RC field is set to round to nearest mode, the FPU produces the same constants that is 
	// produced by the Intel 8087 and Intel287 math coprocessors. 

	//BreakPoint()
}

Func_Prefix  FLDCW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// FPUControlWord � SRC; 
	// FPU Flags Affected 
	// C0, C1, C2, C3 undefined. 
	// Floating-Point Exceptions 
	// None; however, this operation might unmask a pending exception in the FPU status word. That 
	// exception is then generated upon execution of the next �waiting� floating-point instruction. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// #NM 
	// EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) 
	// If a memory operand effective address is outside the SS segment limit. 
	// #NM 
	// EM or TS in CR0 is set. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  FLDENV (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// FPUControlWord � SRC(FPUControlWord); 
	// FPUStatusWord � SRC(FPUStatusWord); 
	// FPUTagWord � SRC(FPUTagWord); 
	// FPUDataPointer � SRC(FPUDataPointer); 
	// FPUInstructionPointer � SRC(FPUInstructionPointer); 
	// FPULastInstructionOpcode � SRC(FPULastInstructionOpcode); 
	// FPU Flags Affected 
	// The C0, C1, C2, C3 flags are loaded. 
	// 3-214 
	// Floating-Point Exceptions 
	// None; however, if an unmasked exception is loaded in the status word, it is generated upon 
	// execution of the next �waiting� floating-point instruction. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// #NM 
	// EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) 
	// If a memory operand effective address is outside the SS segment limit. 
	// #NM 
	// EM or TS in CR0 is set. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  FMUL (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FMULP (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FIMUL (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF instruction is FIMUL 
	// THEN 
	// DEST � DEST * ConvertExtendedReal(SRC); 
	// ELSE (* source operand is real number *) 
	// DEST � DEST * SRC; 
	// FI; 
	// IF instruction = FMULP 
	// THEN 
	// PopRegisterStack 
	// FI; 
	// FPU Flags Affected 
	// C1 Set to 0 if stack underflow occurred. 
	// Indicates rounding direction if the inexact result exception (#P) fault is 
	// generated: 0 = not roundup; 1 = roundup. 
	// C0, C2, C3 Undefined. 
	// Floating-Point Exceptions 
	// #IS Stack underflow occurred. 
	// #IA Operand is an sNaN value or unsupported format. 
	// One operand is �0 and the other is ��. 
	// #D Source operand is a denormal value. 
	// #U Result is too small for destination format. 
	// #O Result is too large for destination format. 
	// #P Value cannot be represented exactly in destination format. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  FNOP (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FPATAN (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// ST(1) � arctan(ST(1) / ST(0)); 
	// PopRegisterStack; 
	// FPU Flags Affected 
	// C1 Set to 0 if stack underflow occurred. 
	// Indicates rounding direction if the inexact result exception (#P) is generated: 
	// 0 = not roundup; 1 = roundup. 
	// C0, C2, C3 Undefined. 
	// Floating-Point Exceptions 
	// #IS Stack underflow occurred. 
	// #IA Source operand is an sNaN value or unsupported format. 
	// #D Source operand is a denormal value. 
	// #U Result is too small for destination format. 
	// #P Value cannot be represented exactly in destination format. 
	// Protected Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Real-Address Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #NM EM or TS in CR0 is set. 

	//BreakPoint()
}

Func_Prefix  FPREM (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// D � exponent(ST(0)) � exponent(ST(1)); 
	// IF D< 64 
	// THEN 
	// Q � Integer(TruncateTowardZero(ST(0) / ST(1))); 
	// ST(0) � ST(0) � (ST(1) * Q); 
	// C2 � 0; 
	// C0, C3, C1 � LeastSignificantBits(Q); (* Q2, Q1, Q0 *) 
	// ELSE 
	// C2 � 1; 
	// N � an implementation-dependent number between 32 and 63; 
	// QQ � Integer(TruncateTowardZero((ST(0) / ST(1)) / 2(D - N))); 
	// ST(0) � ST(0) � (ST(1) * QQ * 2(D - N)); 
	// FI; 
	// FPU Flags Affected 
	// C0 Set to bit 2 (Q2) of the quotient. 
	// C1 Set to 0 if stack underflow occurred; otherwise, set to least significant bit 
	// of quotient (Q0). 
	// C2 Set to 0 if reduction complete; set to 1 if incomplete. 
	// C3 Set to bit 1 (Q1) of the quotient. 
	// Floating-Point Exceptions 
	// #IS Stack underflow occurred. 
	// #IA Source operand is an sNaN value, modulus is 0, dividend is �, or unsupported 
	// format. 
	// #D Source operand is a denormal value. 
	// #U Result is too small for destination format. 
	// Protected Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Real-Address Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #NM EM or TS in CR0 is set. 

	//BreakPoint()
}

Func_Prefix  FPREM1 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// D � exponent(ST(0)) � exponent(ST(1)); 
	// IF D < 64 
	// THEN 
	// Q � Integer(RoundTowardNearestInteger(ST(0) / ST(1))); 
	// ST(0) � ST(0) � (ST(1) * Q); 
	// C2 � 0; 
	// C0, C3, C1 � LeastSignificantBits(Q); (* Q2, Q1, Q0 *) 
	// ELSE 
	// C2 � 1; 
	// N � an implementation-dependent number between 32 and 63; 
	// QQ � Integer(TruncateTowardZero((ST(0) / ST(1)) / 2(D - N))); 
	// ST(0) � ST(0) � (ST(1) * QQ * 2(D - N)); 
	// FI; 
	// FPU Flags Affected 
	// C0 Set to bit 2 (Q2) of the quotient. 
	// C1 Set to 0 if stack underflow occurred; otherwise, set to least significant bit 
	// of quotient (Q0). 
	// C2 Set to 0 if reduction complete; set to 1 if incomplete. 
	// C3 Set to bit 1 (Q1) of the quotient. 
	// Floating-Point Exceptions 
	// #IS Stack underflow occurred. 
	// #IA Source operand is an sNaN value, modulus (divisor) is 0, dividend is �, or 
	// unsupported format. 
	// #D Source operand is a denormal value. 
	// #U Result is too small for destination format. 
	// Protected Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Real-Address Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #NM EM or TS in CR0 is set. 

	//BreakPoint()
}

Func_Prefix  FPTAN (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF ST(0) < 263 
	// THEN 
	// C2 � 0; 
	// ST(0) � tan(ST(0)); 
	// TOP � TOP - 1; 
	// ST(0) � 1.0; 
	// ELSE (*source operand is out-of-range *) 
	// C2 � 1; 
	// FI; 
	// FPU Flags Affected 
	// C1 
	// Set to 0 if stack underflow occurred; set to 1 if stack overflow occurred. 
	// Indicates rounding direction if the inexact result exception (#P) is generated: 
	// 0 = not roundup; 1 = roundup. 
	// C2 
	// Set to 1 if source operand is outside the range -263 to +263; otherwise, 
	// cleared to 0. 
	// C0, C3 
	// Undefined. 
	// Floating-Point Exceptions 
	// #IS Stack underflow occurred. 
	// #IA Source operand is an sNaN value, �, or unsupported format. 
	// #D Source operand is a denormal value. 
	// #U Result is too small for destination format. 
	// #P Value cannot be represented exactly in destination format. 
	// Protected Mode Exceptions 
	// #NM 
	// EM or TS in CR0 is set. 
	// Real-Address Mode Exceptions 
	// #NM 
	// EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #NM 
	// EM or TS in CR0 is set. 

	//BreakPoint()
}

Func_Prefix  FRNDINT (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// ST(0) � RoundToIntegralValue(ST(0)); 
	// FPU Flags Affected 
	// C1 Set to 0 if stack underflow occurred. 
	// Indicates rounding direction if the inexact result exception (#P) is generated: 
	// 0 = not roundup; 1 = roundup. 
	// C0, C2, C3 Undefined. 
	// Floating-Point Exceptions 
	// #IS Stack underflow occurred. 
	// #IA Source operand is an sNaN value or unsupported format. 
	// #D Source operand is a denormal value. 
	// #P Source operand is not an integral value. 
	// Protected Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Real-Address Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #NM EM or TS in CR0 is set. 

	//BreakPoint()
}

Func_Prefix  FRSTOR (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// FPUControlWord � SRC(FPUControlWord); 
	// FPUStatusWord � SRC(FPUStatusWord); 
	// FPUTagWord � SRC(FPUTagWord); 
	// FPUDataPointer � SRC(FPUDataPointer); 
	// FPUInstructionPointer � SRC(FPUInstructionPointer); 
	// FPULastInstructionOpcode � SRC(FPULastInstructionOpcode); 
	// ST(0) � SRC(ST(0)); 
	// ST(1) � SRC(ST(1)); 
	// ST(2) � SRC(ST(2)); 
	// ST(3) � SRC(ST(3)); 
	// ST(4) � SRC(ST(4)); 
	// ST(5) � SRC(ST(5)); 
	// ST(6) � SRC(ST(6)); 
	// ST(7) � SRC(ST(7)); 
	// FPU Flags Affected 
	// The C0, C1, C2, C3 flags are loaded. 
	// Floating-Point Exceptions 
	// None; however, this operation might unmask an existing exception that has been detected but 
	// not generated, because it was masked. Here, the exception is generated at the completion of the 
	// instruction. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 
	// Comments 
	// This instruction has no effect on the state of SIMD floating-point registers. 

	//BreakPoint()
}

Func_Prefix  FSAVE (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FNSAVE (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// (* Save FPU State and Registers *) 
	// DEST(FPUControlWord) � FPUControlWord; 
	// DEST(FPUStatusWord) � FPUStatusWord; 
	// DEST(FPUTagWord) � FPUTagWord; 
	// DEST(FPUDataPointer) � FPUDataPointer; 
	// DEST(FPUInstructionPointer) � FPUInstructionPointer; 
	// DEST(FPULastInstructionOpcode) � FPULastInstructionOpcode; 
	// DEST(ST(0)) � ST(0); 
	// DEST(ST(1)) � ST(1); 
	// DEST(ST(2)) � ST(2); 
	// DEST(ST(3)) � ST(3); 
	// DEST(ST(4)) � ST(4); 
	// DEST(ST(5)) � ST(5); 
	// DEST(ST(6)) � ST(6); 
	// DEST(ST(7)) � ST(7); 
	// (* Initialize FPU *) 
	// FPUControlWord � 037FH; 
	// FPUStatusWord � 0; 
	// FPUTagWord � FFFFH; 
	// FPUDataPointer � 0; 
	// FPUInstructionPointer � 0; 
	// FPULastInstructionOpcode � 0; 
	// FPU Flags Affected 
	// The C0, C1, C2, and C3 flags are saved and then cleared. 
	// Floating-Point Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If destination is located in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// #NM 
	// EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) 
	// If a memory operand effective address is outside the SS segment limit. 
	// #NM 
	// EM or TS in CR0 is set. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 
	// Comments 
	// This instruction has no effect on the state of SIMD floating-point registers. 

	//BreakPoint()
}

Func_Prefix  FSCALE (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// ST(0) � ST(0) * 2ST(1); 
	// FPU Flags Affected 
	// C1 Set to 0 if stack underflow occurred. 
	// Indicates rounding direction if the inexact result exception (#P) is generated: 
	// 0 = not roundup; 1 = roundup. 
	// C0, C2, C3 Undefined. 
	// Floating-Point Exceptions 
	// #IS Stack underflow occurred. 
	// #IA Source operand is an sNaN value or unsupported format. 
	// #D Source operand is a denormal value. 
	// #U Result is too small for destination format. 
	// #O Result is too large for destination format. 
	// #P Value cannot be represented exactly in destination format. 
	// Protected Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Real-Address Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #NM EM or TS in CR0 is set. 

	//BreakPoint()
}

Func_Prefix  FSIN (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF ST(0) < 263 
	// THEN 
	// C2 � 0; 
	// ST(0) � sin(ST(0)); 
	// ELSE (* source operand out of range *) 
	// C2 � 1; 
	// FI: 
	// FPU Flags Affected 
	// C1 Set to 0 if stack underflow occurred. 
	// Indicates rounding direction if the inexact result exception (#P) is generated: 
	// 0 = not roundup; 1 = roundup. 
	// C2 Set to 1 if source operand is outside the range -263 to +263; otherwise, 
	// cleared to 0. 
	// C0, C3 Undefined. 
	// Floating-Point Exceptions 
	// #IS Stack underflow occurred. 
	// #IA Source operand is an sNaN value, �, or unsupported format. 
	// #D Source operand is a denormal value. 
	// #P Value cannot be represented exactly in destination format. 
	// Protected Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Real-Address Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #NM EM or TS in CR0 is set. 

	//BreakPoint()
}

Func_Prefix  FSINCOS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF ST(0) < 263 
	// THEN 
	// C2 � 0; 
	// TEMP � cosine(ST(0)); 
	// ST(0) � sine(ST(0)); 
	// TOP � TOP - 1; 
	// ST(0) � TEMP; 
	// ELSE (* source operand out of range *) 
	// C2 � 1; 
	// FI: 
	// FPU Flags Affected 
	// C1 Set to 0 if stack underflow occurred; set to 1 of stack overflow occurs. 
	// Indicates rounding direction if the exception (#P) is generated: 0 = not 
	// roundup; 1 = roundup. 
	// C2 Set to 1 if source operand is outside the range -263 to +263; otherwise, 
	// cleared to 0. 
	// C0, C3 Undefined. 
	// Floating-Point Exceptions 
	// #IS Stack underflow occurred. 
	// #IA Source operand is an sNaN value, �, or unsupported format. 
	// #D Source operand is a denormal value. 
	// #U Result is too small for destination format. 
	// #P Value cannot be represented exactly in destination format. 
	// Protected Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Real-Address Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #NM EM or TS in CR0 is set. 

	//BreakPoint()
}

Func_Prefix  FSQRT (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// ST(0) � SquareRoot(ST(0)); 
	// FPU Flags Affected 
	// C1 Set to 0 if stack underflow occurred. 
	// Indicates rounding direction if inexact result exception (#P) is generated: 
	// 0 = not roundup; 1 = roundup. 
	// C0, C2, C3 Undefined. 
	// Floating-Point Exceptions 
	// #IS Stack underflow occurred. 
	// #IA Source operand is an sNaN value or unsupported format. 
	// Source operand is a negative value (except for -0). 
	// #D Source operand is a denormal value. 
	// #P Value cannot be represented exactly in destination format. 
	// Protected Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Real-Address Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #NM EM or TS in CR0 is set. 

	//BreakPoint()
}

Func_Prefix  FST (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FSTP8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}

Func_Prefix  FSTP (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST � ST(0); 
	// IF instruction = FSTP 
	// THEN 
	// PopRegisterStack; 
	// FI; 
	// FPU Flags Affected 
	// C1 Set to 0 if stack underflow occurred. 
	// Indicates rounding direction of if the floating-point inexact exception (#P) 
	// is generated: 0 = not roundup; 1 = roundup. 
	// C0, C2, C3 Undefined. 
	// Floating-Point Exceptions 
	// #IS Stack underflow occurred. 
	// #IA Source operand is an sNaN value or unsupported format. 
	// #U Result is too small for the destination format. 
	// #O Result is too large for the destination format. 
	// #P Value cannot be represented exactly in destination format. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination is located in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  FSTCW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FNSTCW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST � FPUControlWord; 
	// FPU Flags Affected 
	// The C0, C1, C2, and C3 flags are undefined. 
	// Floating-Point Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination is located in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// #NM 
	// EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) 
	// If a memory operand effective address is outside the SS segment limit. 
	// #NM 
	// EM or TS in CR0 is set. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  FSTENV (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FNSTENV (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST(FPUControlWord) � FPUControlWord; 
	// DEST(FPUStatusWord) � FPUStatusWord; 
	// DEST(FPUTagWord) � FPUTagWord; 
	// DEST(FPUDataPointer) � FPUDataPointer; 
	// DEST(FPUInstructionPointer) � FPUInstructionPointer; 
	// DEST(FPULastInstructionOpcode) � FPULastInstructionOpcode; 
	// FPU Flags Affected 
	// The C0, C1, C2, and C3 are undefined. 
	// Floating-Point Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination is located in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  FSTSW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FNSTSW16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FNSTSW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST � FPUStatusWord; 
	// FPU Flags Affected 
	// The C0, C1, C2, and C3 are undefined. 
	// Floating-Point Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination is located in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  FSUB (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FSUBP (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FISUB (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF instruction is FISUB 
	// THEN 
	// DEST � DEST - ConvertExtendedReal(SRC); 
	// ELSE (* source operand is real number *) 
	// DEST � DEST - SRC; 
	// FI; 
	// IF instruction is FSUBP 
	// THEN 
	// PopRegisterStack 
	// FI; 
	// FPU Flags Affected 
	// C1 Set to 0 if stack underflow occurred. 
	// Indicates rounding direction if the inexact result exception (#P) fault is 
	// generated: 0 = not roundup; 1 = roundup. 
	// C0, C2, C3 Undefined. 
	// Floating-Point Exceptions 
	// #IS Stack underflow occurred. 
	// #IA Operand is an sNaN value or unsupported format. 
	// Operands are infinities of like sign. 
	// #D Source operand is a denormal value. 
	// #U Result is too small for destination format. 
	// #O Result is too large for destination format. 
	// #P Value cannot be represented exactly in destination format. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  FSUBR (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FSUBRP (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FISUBR (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF instruction is FISUBR 
	// THEN 
	// DEST � ConvertExtendedReal(SRC) - DEST; 
	// ELSE (* source operand is real number *) 
	// DEST � SRC - DEST; 
	// FI; 
	// IF instruction = FSUBRP 
	// THEN 
	// PopRegisterStack 
	// FI; 
	// FPU Flags Affected 
	// C1 Set to 0 if stack underflow occurred. 
	// Indicates rounding direction if the inexact result exception (#P) fault is 
	// generated: 0 = not roundup; 1 = roundup. 
	// C0, C2, C3 Undefined. 
	// Floating-Point Exceptions 
	// #IS Stack underflow occurred. 
	// #IA Operand is an sNaN value or unsupported format. 
	// Operands are infinities of like sign. 
	// #D Source operand is a denormal value. 
	// #U Result is too small for destination format. 
	// #O Result is too large for destination format. 
	// #P Value cannot be represented exactly in destination format. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NM EM or TS in CR0 is set. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  FTST (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// CASE (relation of operands) OF 
	// Not comparable: C3, C2, C0 � 111; 
	// ST(0) > 0.0: C3, C2, C0 � 000; 
	// ST(0) < 0.0: C3, C2, C0 � 001; 
	// ST(0) = 0.0: C3, C2, C0 � 100; 
	// ESAC; 
	// FPU Flags Affected 
	// C1 Set to 0 if stack underflow occurred; otherwise, cleared to 0. 
	// C0, C2, C3 Refer to above table. 
	// Floating-Point Exceptions 
	// #IS Stack underflow occurred. 
	// #IA The source operand is a NaN value or is in an unsupported format. 
	// #D The source operand is a denormal value. 
	// Protected Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Real-Address Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #NM EM or TS in CR0 is set. 

	//BreakPoint()
}

Func_Prefix  FUCOM (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FUCOMP (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FUCOMPP (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// CASE (relation of operands) OF 
	// ST > SRC: C3, C2, C0 � 000; 
	// ST < SRC: C3, C2, C0 � 001; 
	// ST = SRC: C3, C2, C0 � 100; 
	// ESAC; 
	// IF ST(0) or SRC = QNaN, but not SNaN or unsupported format 
	// THEN 
	// C3, C2, C0 � 111; 
	// ELSE (* ST(0) or SRC is SNaN or unsupported format *) 
	// #IA; 
	// IF FPUControlWord.IM = 1 
	// THEN 
	// C3, C2, C0 � 111; 
	// FI; 
	// FI; 
	// IF instruction = FUCOMP 
	// THEN 
	// PopRegisterStack; 
	// FI; 
	// IF instruction = FUCOMPP 
	// THEN 
	// PopRegisterStack; 
	// PopRegisterStack; 
	// FI; 
	// FPU Flags Affected 
	// C1 
	// Set to 0 if stack underflow occurred. 
	// C0, C2, C3 
	// Refer to table on previous page. 
	// Floating-Point Exceptions 
	// #IS 
	// Stack underflow occurred. 
	// #IA 
	// One or both operands are sNaN values or have unsupported formats. 
	// Detection of a qNaN value in and of itself does not raise an invalid-
	// operand exception. 
	// #D 
	// One or both operands are denormal values. 
	// FUCOM/FUCOMP/FUCOMPP�Unordered Compare Real 
	// Protected Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Real-Address Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// FWAIT�Wait 
	// Refer to entry for WAIT/FWAIT�Wait. 

	//BreakPoint()
}

Func_Prefix  FXAM (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// C1 � sign bit of ST; (* 0 for positive, 1 for negative *) 
	// CASE (class of value or number in ST(0)) OF 
	// Unsupported:C3, C2, C0 � 000; 
	// NaN: C3, C2, C0 � 001; 
	// Normal: C3, C2, C0 � 010; 
	// Infinity: C3, C2, C0 � 011; 
	// Zero: C3, C2, C0 � 100; 
	// Empty: C3, C2, C0 � 101; 
	// Denormal: C3, C2, C0 � 110; 
	// ESAC; 
	// FPU Flags Affected 
	// C1 Sign of value in ST(0). 
	// C0, C2, C3 Refer to table above. 
	// Floating-Point Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Real-Address Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #NM EM or TS in CR0 is set. 

	//BreakPoint()
}

Func_Prefix  FXCH (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF number-of-operands is 1 
	// THEN 
	// temp � ST(0); 
	// ST(0) � SRC; 
	// SRC � temp; 
	// ELSE 
	// temp � ST(0); 
	// ST(0) � ST(1); 
	// ST(1) � temp; 
	// FPU Flags Affected 
	// C1 Set to 0 if stack underflow occurred; otherwise, cleared to 0. 
	// C0, C2, C3 Undefined. 
	// Floating-Point Exceptions 
	// #IS Stack underflow occurred. 
	// Protected Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Real-Address Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #NM EM or TS in CR0 is set. 

	//BreakPoint()
}

Func_Prefix  FXRSTOR (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// FP and MMX� technology state and Streaming SIMD Extension state = m512byte; 
	// Exceptions 
	// #AC 
	// If exception detection is disabled, a general protection exception is 
	// signaled if the address is not aligned on 16-byte boundary. Note that if 
	// #AC is enabled (and CPL is 3), signaling of #AC is not guaranteed and 
	// may vary with implementation. In all implementations where #AC is not 
	// signaled, a general protection fault will instead be signaled. In addition, 
	// the width of the alignment check when #AC is enabled may also vary with 
	// implementation; for instance, for a given implementation, #AC might be 
	// signaled for a 2-byte misalignment, whereas #GP might be signaled for all 
	// other misalignments (4-/8-/16-byte). Invalid opcode exception if instruction 
	// is preceded by a LOCK override prefix. General protection fault if 
	// reserved bits of MXCSR are loaded with non-zero values. 
	// Numeric Exceptions 
	// None. 
	// FXRSTOR�Restore FP And MMX� State And Streaming SIMD 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments, or if an attempt is made to load non-zero values to reserved 
	// bits in the MXCSR field. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #NM If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #AC For unaligned memory reference. To enable #AC exceptions, three conditions 
	// must be TRUE(CR0.AM is set; EFLAGS.AC is set; current CPL is 3). 
	// Real Address Mode Exceptions 
	// Interrupt 13 If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #NM If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #AC For unaligned memory reference if the current privilege level is 3. 
	// #PF (fault-code) For a page fault. 
	// Comments 
	// State saved with FXSAVE and restored with FRSTOR, and state saved with FSAVE and restored 
	// with FXRSTOR, will result in incorrect restoration of state in the processor. The address size 
	// prefix will have the usual effect on address calculation, but will have no effect on the format of 
	// the FXRSTOR image. 
	// The use of Repeat (F2H, F3H) and Operand-size (66H) prefixes with FXRSTOR is reserved. 
	// Different processor implementations may handle these prefixes differently. Usage of these 
	// prefixes with FXRSTOR risks incompatibility with future processors. 

	//BreakPoint()
}

Func_Prefix  FXSAVE (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// m512byte = FP and MMX� technology state and Streaming SIMD Extension state; 
	// Exceptions 
	// #AC If exception detection is disabled, a general protection exception is 
	// signaled if the address is not aligned on 16-byte boundary. Note that if 
	// #AC is enabled (and CPL is 3), signaling of #AC is not guaranteed and 
	// may vary with implementation. In all implementations where #AC is not 
	// signaled, a general protection fault will instead be signaled. In addition, 
	// the width of the alignment check when #AC is enabled may also vary with 
	// implementation; for instance, for a given implementation, #AC might be 
	// signaled for a 2-byte misalignment, whereas #GP might be signaled for all 
	// other misalignments (4-/8-/16-byte). Invalid opcode exception if instruction 
	// is preceded by a LOCK override prefix. 
	// Numeric Exceptions 
	// Invalid, Precision. 
	// Protected Mode Exceptions 
	// #GP(0) 
	// For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) 
	// For an illegal address in the SS segment. 
	// #PF (fault-code) 
	// For a page fault. 
	// #NM 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #AC 
	// For unaligned memory reference. To enable #AC exceptions, three conditions 
	// must be TRUE(CR0.AM is set; EFLAGS.AC is set; current CPL is 3). 
	// FXSAVE�Store FP and MMX� State And Streaming SIMD 
	// Real Address Mode Exceptions 
	// Interrupt 13 If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #NM If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #AC For unaligned memory reference if the current privilege level is 3. 
	// #PF (fault-code) For a page fault. 
	// Comments 
	// State saved with FXSAVE and restored with FRSTOR, and state saved with FSAVE and restored 
	// with FXRSTOR, will result in incorrect restoration of state in the processor. The address size 
	// prefix will have the usual effect on address calculation, but will have no effect on the format of 
	// the FXSAVE image. 
	// The use of Repeat (F2H, F3H) and Operand-size (66H) prefixes with FXSAVE is reserved. 
	// Different processor implementations may handle these prefixes differently. Usage of these 
	// prefixes with FXSAVE risks incompatibility with future processors. 

	//BreakPoint()
}

Func_Prefix  FXTRACT (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// TEMP � Significand(ST(0)); 
	// ST(0) � Exponent(ST(0)); 
	// TOP� TOP - 1; 
	// ST(0) � TEMP; 
	// FPU Flags Affected 
	// C1 Set to 0 if stack underflow occurred; set to 1 if stack overflow occurred. 
	// C0, C2, C3 Undefined. 
	// Floating-Point Exceptions 
	// #IS Stack underflow occurred. 
	// Stack overflow occurred. 
	// #IA Source operand is an sNaN value or unsupported format. 
	// #Z ST(0) operand is �0. 
	// #D Source operand is a denormal value. 
	// Protected Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Real-Address Mode Exceptions 
	// #NM EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #NM EM or TS in CR0 is set. 

	//BreakPoint()
}

Func_Prefix  FYL2X (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// ST(1) � ST(1) * log2ST(0); 
	// PopRegisterStack; 
	// FPU Flags Affected 
	// C1 
	// Set to 0 if stack underflow occurred. 
	// Indicates rounding direction if the inexact result exception (#P) is generated: 
	// 0 = not roundup; 1 = roundup. 
	// C0, C2, C3 
	// Undefined. 
	// Floating-Point Exceptions 
	// #IS 
	// Stack underflow occurred. 
	// #IA 
	// Either operand is an sNaN or unsupported format. 
	// Source operand in register ST(0) is a negative finite value (not -0). 
	// #Z 
	// Source operand in register ST(0) is �0. 
	// #D 
	// Source operand is a denormal value. 
	// #U 
	// Result is too small for destination format. 
	// #O 
	// Result is too large for destination format. 
	// #P 
	// Value cannot be represented exactly in destination format. 
	// Protected Mode Exceptions 
	// #NM 
	// EM or TS in CR0 is set. 
	// Real-Address Mode Exceptions 
	// #NM 
	// EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #NM 
	// EM or TS in CR0 is set. 

	//BreakPoint()
}

Func_Prefix  FYL2XP1 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// ST(1) � ST(1) * log2(ST(0) + 1.0); 
	// PopRegisterStack; 
	// FPU Flags Affected 
	// C1 
	// Set to 0 if stack underflow occurred. 
	// Indicates rounding direction if the inexact result exception (#P) is 
	// generated: 0 = not roundup; 1 = roundup. 
	// C0, C2, C3 
	// Undefined. 
	// Floating-Point Exceptions 
	// #IS Stack underflow occurred. 
	// #IA Either operand is an sNaN value or unsupported format. 
	// #D Source operand is a denormal value. 
	// #U Result is too small for destination format. 
	// #O Result is too large for destination format. 
	// #P Value cannot be represented exactly in destination format. 
	// Protected Mode Exceptions 
	// #NM 
	// EM or TS in CR0 is set. 
	// Real-Address Mode Exceptions 
	// #NM 
	// EM or TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #NM 
	// EM or TS in CR0 is set. 

	//BreakPoint()
}

Func_Prefix  HLT (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// Enter Halt state; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If the current privilege level is not 0. 
	// Real-Address Mode Exceptions 
	// None. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If the current privilege level is not 0. 

	//BreakPoint()
}

Func_Prefix  IDIV8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}

Func_Prefix  IDIV16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}

Func_Prefix  IDIV (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF SRC = 0 
	// THEN #DE; (* divide error *) 
	// FI; 
	// IF OpernadSize = 8 (* word/byte operation *) 
	// THEN 
	// temp � AX / SRC; (* signed division *) 
	// IF (temp > 7FH) OR (temp < 80H) 
	// (* if a positive result is greater than 7FH or a negative result is less than 80H *) 
	// THEN #DE; (* divide error *) ; 
	// ELSE 
	// AL � temp; 
	// AH � AX SignedModulus SRC; 
	// FI; 
	// ELSE 
	// IF OpernadSize = 16 (* doubleword/word operation *) 
	// THEN 
	// temp � DX:AX / SRC; (* signed division *) 
	// IF (temp > 7FFFH) OR (temp < 8000H) 
	// (* if a positive result is greater than 7FFFH *) 
	// (* or a negative result is less than 8000H *) 
	// THEN #DE; (* divide error *) ; 
	// ELSE 
	// AX � temp; 
	// DX � DX:AX SignedModulus SRC; 
	// FI; 
	// ELSE (* quaUINT32/doubleword operation *) 
	// temp � EDX:EAX / SRC; (* signed division *) 
	// IF (temp > 7FFFFFFFH) OR (temp < 80000000H) 
	// (* if a positive result is greater than 7FFFFFFFH *) 
	// (* or a negative result is less than 80000000H *) 
	// THEN #DE; (* divide error *) ; 
	// ELSE 
	// EAX � temp; 
	// EDX � EDXE:AX SignedModulus SRC; 
	// FI; 
	// FI; 
	// FI; 
	// Flags Affected 
	// The CF, OF, SF, ZF, AF, and PF flags are undefined. 
	// Protected Mode Exceptions 
	// #DE If the source operand (divisor) is 0. 
	// The signed result (quotient) is too large for the destination. 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #DE If the source operand (divisor) is 0. 
	// The signed result (quotient) is too large for the destination. 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #DE If the source operand (divisor) is 0. 
	// The signed result (quotient) is too large for the destination. 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  IMUL8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  IMUL16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  IMUL (VirtualMachine *posVm)
{
	UINT32	nEFlag, nOperand1;
	PAGED_CODE();
	
	nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;	
	
	if (posVm->Context.osOpcodeBlock.nCountOperand == 1)
	{
		__asm	mov	eax	,  nOperand1
		__asm	imul [eax]
		FlagSaver(nEFlag);
	}
	else if (posVm->Context.osOpcodeBlock.nCountOperand == 2)
	{
		UINT32 nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
		__asm	mov	eax	,  nOperand1
		__asm	mov	ecx ,  nOperand2
		__asm	mov	edx ,  dword ptr[eax]
		__asm	imul edx, dword ptr[ecx]
		FlagSaver(nEFlag);
		__asm	mov	ecx ,  nOperand1
		__asm	mov	[ecx] ,  edx
	}
	else 
	{
		UINT32 nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
		UINT32 nOperand3 = posVm->Context.osOpcodeBlock.nOperand2;
		__asm	mov	ecx ,  nOperand3
		__asm	mov	edx ,  nOperand2
		__asm	mov	edx ,  dword ptr[edx]
		__asm	imul edx, dword ptr[ecx]
		FlagSaver(nEFlag);
		__asm	mov	eax	,  nOperand1
		__asm	mov	[eax] ,  edx		
	}
	posVm->Context.osReg.nEFlag = nEFlag;
	// IF (NumberOfOperands = 1) 
	// THEN IF (OperandSize = 8) 
	// THEN 
	// AX � AL * SRC (* signed multiplication *) 
	// IF ((AH = 00H) OR (AH = FFH)) 
	// THEN CF = 0; OF = 0; 
	// ELSE CF = 1; OF = 1; 
	// FI; 
	// ELSE IF OperandSize = 16 
	// THEN 
	// DX:AX � AX * SRC (* signed multiplication *) 
	// IF ((DX = 0000H) OR (DX = FFFFH)) 
	// THEN CF = 0; OF = 0; 
	// ELSE CF = 1; OF = 1; 
	// FI; 
	// ELSE (* OperandSize = 32 *) 
	// EDX:EAX � EAX * SRC (* signed multiplication *) 
	// IF ((EDX = 00000000H) OR (EDX = FFFFFFFFH)) 
	// THEN CF = 0; OF = 0; 
	// ELSE CF = 1; OF = 1; 
	// FI; 
	// FI; 
	// ELSE IF (NumberOfOperands = 2) 
	// THEN 
	// temp � DEST * SRC (* signed multiplication; temp is double DEST size*) 
	// DEST � DEST * SRC (* signed multiplication *) 
	// IF temp � DEST 
	// THEN CF = 1; OF = 1; 
	// ELSE CF = 0; OF = 0; 
	// FI; 
	// ELSE (* NumberOfOperands = 3 *) 
	// DEST � SRC1 * SRC2 (* signed multiplication *) 
	// temp � SRC1 * SRC2 (* signed multiplication; temp is double SRC1 size *) 
	// IF temp � DEST 
	// THEN CF = 1; OF = 1; 
	// ELSE CF = 0; OF = 0; 
	// FI; 
	// FI; 
	// FI; 
	// Flags Affected 
	// For the one operand form of the instruction, the CF and OF flags are set when significant bits 
	// are carried into the upper half of the result and cleared when the result fits exactly in the lower 
	// half of the result. For the two- and three-operand forms of the instruction, the CF and OF flags 
	// are set when the result must be truncated to fit in the destination operand size and cleared when 
	// the result fits exactly in the destination operand size. The SF, ZF, AF, and PF flags are undefined. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

}

Func_Prefix  IN_8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


//	//BreakPoint()
}

Func_Prefix  IN_16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  IN_ (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF ((PE = 1) AND ((CPL > IOPL) OR (VM = 1))) 
	// THEN (* Protected mode with CPL > IOPL or virtual-8086 mode *) 
	// IF (Any I/O Permission Bit for I/O port being accessed = 1) 
	// THEN (* I/O operation is not allowed *) 
	// #GP(0); 
	// ELSE ( * I/O operation is allowed *) 
	// DEST � SRC; (* Reads from selected I/O port *) 
	// FI; 
	// ELSE (Real Mode or Protected Mode with CPL � IOPL *) 
	// DEST � SRC; (* Reads from selected I/O port *) 
	// FI; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) 
	// If the CPL is greater than (has less privilege) the I/O privilege level (IOPL) 
	// and any of the corresponding I/O permission bits in TSS for the I/O port 
	// being accessed is 1. 
	// Real-Address Mode Exceptions 
	// None. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) 
	// If any of the I/O permission bits in the TSS for the I/O port being accessed 
	// is 1. 

	//BreakPoint()
}

Func_Prefix  INC8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;	
	UINT32 nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	UINT32 nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
	PAGED_CODE();
	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm inc byte ptr [eax]
	FlagSaver(nEFlag);
	posVm->Context.osReg.nEFlag = nEFlag;
	////BreakPoint()
}

Func_Prefix  INC16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	UINT32 nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	UINT32 nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
	PAGED_CODE();
	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm inc word ptr [eax]
	FlagSaver(nEFlag);
	posVm->Context.osReg.nEFlag = nEFlag;
	//BreakPoint()
}

Func_Prefix  INC (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	UINT32 nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	PAGED_CODE();
	__asm	mov	eax	,  nOperand1
	__asm inc dword ptr [eax]
	FlagSaver(nEFlag);
	posVm->Context.osReg.nEFlag = nEFlag;
	// DEST � DEST +1; 
	// Flags Affected 
	// The CF flag is not affected. The OF, SF, ZF, AF, and PF flags are set according to the result. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination operand is located in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made.
}

Func_Prefix  INS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  INSB (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  INSW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  INSD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF ((PE = 1) AND ((CPL > IOPL) OR (VM = 1))) 
	// THEN (* Protected mode with CPL > IOPL or virtual-8086 mode *) 
	// IF (Any I/O Permission Bit for I/O port being accessed = 1) 
	// THEN (* I/O operation is not allowed *) 
	// #GP(0); 
	// ELSE ( * I/O operation is allowed *) 
	// DEST � SRC; (* Reads from I/O port *) 
	// FI; 
	// ELSE (Real Mode or Protected Mode with CPL � IOPL *) 
	// DEST � SRC; (* Reads from I/O port *) 
	// FI; 
	// IF (byte transfer) 
	// THEN IF DF = 0 
	// THEN (E)DI � (E)DI + 1; 
	// ELSE (E)DI � (E)DI � 1; 
	// FI; 
	// ELSE IF (word transfer) 
	// THEN IF DF = 0 
	// THEN (E)DI � (E)DI + 2; 
	// ELSE (E)DI � (E)DI � 2; 
	// FI; 
	// ELSE (* doubleword transfer *) 
	// THEN IF DF = 0 
	// THEN (E)DI � (E)DI + 4; 
	// ELSE (E)DI � (E)DI � 4; 
	// FI; 
	// FI; 
	// FI; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If the CPL is greater than (has less privilege) the I/O privilege level (IOPL) 
	// and any of the corresponding I/O permission bits in TSS for the I/O port 
	// being accessed is 1. 
	// If the destination is located in a nonwritable segment. 
	// If an illegal memory operand effective address in the ES segments is 
	// given. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) 
	// If any of the I/O permission bits in the TSS for the I/O port being accessed 
	// is 1. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  INTn8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// not important
}

Func_Prefix  INTO (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


//	//BreakPoint()
}

Func_Prefix  INT3 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// The following operational description applies not only to the INT n and INTO instructions, but 
	// also to external interrupts and exceptions. 
	// IF PE=0 
	// THEN 
	// GOTO REAL-ADDRESS-MODE; 
	// ELSE (* PE=1 *) 
	// IF (VM=1 AND IOPL < 3 AND INT n) 
	// THEN 
	// #GP(0); 
	// ELSE (* protected mode or virtual-8086 mode interrupt *) 
	// GOTO PROTECTED-MODE; 
	// FI; 
	// FI; 
	// REAL-ADDRESS-MODE: 
	// IF ((DEST * 4) + 3) is not within IDT limit THEN #GP; FI; 
	// IF stack not large enough for a 6-byte 
	// Push (EFLAGS[15:0]); 
	// IF � 0; (* Clear interrupt flag *) 
	// TF � 0; (* Clear trap flag *) 
	// AC � 0; (*Clear AC flag*) 
	// Push(CS); 
	// Push(IP); 
	// (* No error codes are pushed *) 
	// CS � IDT(Descriptor (vector_number * 4), selector)); 
	// EIP � IDT(Descriptor (vector_number * 4), offset)); (* 16-bit offset AND 0000FFFFH *) 
	// END; 
	// PROTECTED-MODE: 
	// IF ((DEST * 8) + 7) is not within IDT limits 
	// OR selected IDT descriptor is not an interrupt-, trap-, or task-gate type 
	// THEN #GP((DEST * 8) + 2 + EXT); 
	// (* EXT is bit 0 in error code *) 
	// FI; 
	// IF software interrupt (* generated by INT n, INT 3, or INTO *) 
	// THEN 
	// IF gate descriptor DPL < CPL 
	// THEN #GP((vector_number * 8) + 2 ); 
	// (* PE=1, DPL<CPL, software interrupt *) 
	// FI; 
	// FI; 
	// IF gate not present THEN #NP((vector_number * 8) + 2 + EXT); FI; 
	// IF task gate (* specified in the selected interrupt table descriptor *) 
	// THEN GOTO TASK-GATE; 
	// ELSE GOTO TRAP-OR-INTERRUPT-GATE; (* PE=1, trap/interrupt gate *) 
	// FI; 
	// END; 
	// TASK-GATE: (* PE=1, task gate *) 
	// Read segment selector in task gate (IDT descriptor); 
	// IF local/global bit is set to local 
	// OR index not within GDT limits 
	// THEN #GP(TSS selector); 
	// FI; 
	// Access TSS descriptor in GDT; 
	// IF TSS descriptor specifies that the TSS is busy (low-order 5 bits set to 00001) 
	// THEN #GP(TSS selector); 
	// FI; 
	// IF TSS not present 
	// THEN #NP(TSS selector); 
	// FI; 
	// SWITCH-TASKS (with nesting) to TSS; 
	// IF interrupt caused by fault with error code 
	// THEN 
	// IF stack limit does not allow push of error code 
	// THEN #SS(0); 
	// FI; 
	// Push(error code); 
	// FI; 
	// IF EIP not within code segment limit 
	// THEN #GP(0); 
	// FI; 
	// END; 
	// TRAP-OR-INTERRUPT-GATE 
	// Read segment selector for trap or interrupt gate (IDT descriptor); 
	// IF segment selector for code segment is null 
	// THEN #GP(0H + EXT); (* null selector with EXT flag set *) 
	// FI; 
	// IF segment selector is not within its descriptor table limits 
	// THEN #GP(selector + EXT); 
	// FI; 
	// Read trap or interrupt handler descriptor; 
	// IF descriptor does not indicate a code segment 
	// OR code segment descriptor DPL > CPL 
	// THEN #GP(selector + EXT); 
	// FI; 
	// IF trap or interrupt gate segment is not present, 
	// THEN #NP(selector + EXT); 
	// FI; 
	// IF code segment is non-conforming AND DPL < CPL 
	// THEN IF VM=0 
	// THEN 
	// GOTO INTER-PRIVILEGE-LEVEL-INTERRUPT; 
	// (* PE=1, interrupt or trap gate, nonconforming *) 
	// (* code segment, DPL<CPL, VM=0 *) 
	// ELSE (* VM=1 *) 
	// IF code segment DPL � 0 THEN #GP(new code segment selector); FI; 
	// GOTO INTERRUPT-FROM-VIRTUAL-8086-MODE; 
	// (* PE=1, interrupt or trap gate, DPL<CPL, VM=1 *) 
	// FI; 
	// ELSE (* PE=1, interrupt or trap gate, DPL � CPL *) 
	// IF VM=1 THEN #GP(new code segment selector); FI; 
	// IF code segment is conforming OR code segment DPL = CPL 
	// THEN 
	// GOTO INTRA-PRIVILEGE-LEVEL-INTERRUPT; 
	// ELSE 
	// #GP(CodeSegmentSelector + EXT); 
	// (* PE=1, interrupt or trap gate, nonconforming *) 
	// (* code segment, DPL>CPL *) 
	// FI; 
	// FI; 
	// END; 
	// INTER-PREVILEGE-LEVEL-INTERRUPT 
	// (* PE=1, interrupt or trap gate, non-conforming code segment, DPL<CPL *) 
	// (* Check segment selector and descriptor for stack of new privilege level in current TSS *) 
	// IF current TSS is 32-bit TSS 
	// THEN 
	// TSSstackAddress � (new code segment DPL * 8) + 4 
	// IF (TSSstackAddress + 7) > TSS limit 
	// THEN #TS(current TSS selector); FI; 
	// NewSS � TSSstackAddress + 4; 
	// NewESP � stack address; 
	// ELSE (* TSS is 16-bit *) 
	// TSSstackAddress � (new code segment DPL * 4) + 2 
	// IF (TSSstackAddress + 4) > TSS limit 
	// THEN #TS(current TSS selector); FI; 
	// NewESP � TSSstackAddress; 
	// NewSS � TSSstackAddress + 2; 
	// FI; 
	// IF segment selector is null THEN #TS(EXT); FI; 
	// IF segment selector index is not within its descriptor table limits 
	// OR segment selector�s RPL � DPL of code segment, 
	// THEN #TS(SS selector + EXT); 
	// FI; 
	// Read segment descriptor for stack segment in GDT or LDT; 
	// IF stack segment DPL � DPL of code segment, 
	// OR stack segment does not indicate writable data segment, 
	// THEN #TS(SS selector + EXT); 
	// FI; 
	// IF stack segment not present THEN #SS(SS selector+EXT); FI; 
	// IF 32-bit gate 
	// THEN 
	// IF new stack does not have room for 24 bytes (error code pushed) 
	// OR 20 bytes (no error code pushed) 
	// THEN #SS(segment selector + EXT); 
	// FI; 
	// ELSE (* 16-bit gate *) 
	// IF new stack does not have room for 12 bytes (error code pushed) 
	// OR 10 bytes (no error code pushed); 
	// THEN #SS(segment selector + EXT); 
	// FI; 
	// FI; 
	// IF instruction pointer is not within code segment limits THEN #GP(0); FI; 
	// SS:ESP � TSS(NewSS:NewESP) (* segment descriptor information also loaded *) 
	// IF 32-bit gate 
	// THEN 
	// CS:EIP � Gate(CS:EIP); (* segment descriptor information also loaded *) 
	// ELSE (* 16-bit gate *) 
	// CS:IP � Gate(CS:IP); (* segment descriptor information also loaded *) 
	// FI; 
	// IF 32-bit gate 
	// THEN 
	// Push(far pointer to old stack); (* old SS and ESP, 3 words padded to 4 *); 
	// Push(EFLAGS); 
	// Push(far pointer to 
	// Push(ErrorCode); (* if needed, 4 bytes *) 
	// ELSE(* 16-bit gate *) 
	// Push(far pointer to old stack); (* old SS and SP, 2 words *); 
	// Push(EFLAGS(15..0)); 
	// Push(far pointer to 
	// Push(ErrorCode); (* if needed, 2 bytes *) 
	// FI; 
	// CPL � CodeSegmentDescriptor(DPL); 
	// CS(RPL) � CPL; 
	// IF interrupt gate 
	// THEN IF � 0 (* interrupt flag to 0 (disabled) *); FI; 
	// TF � 0; 
	// VM � 0; 
	// RF � 0; 
	// NT � 0; 
	// END; 
	// INTERRUPT-FROM-VIRTUAL-8086-MODE: 
	// (* Check segment selector and descriptor for privilege level 0 stack in current TSS *) 
	// IF current TSS is 32-bit TSS 
	// THEN 
	// TSSstackAddress � (new code segment DPL * 8) + 4 
	// IF (TSSstackAddress + 7) > TSS limit 
	// THEN #TS(current TSS selector); FI; 
	// NewSS � TSSstackAddress + 4; 
	// NewESP � stack address; 
	// ELSE (* TSS is 16-bit *) 
	// TSSstackAddress � (new code segment DPL * 4) + 2 
	// IF (TSSstackAddress + 4) > TSS limit 
	// THEN #TS(current TSS selector); FI; 
	// NewESP � TSSstackAddress; 
	// NewSS � TSSstackAddress + 2; 
	// FI; 
	// IF segment selector is null THEN #TS(EXT); FI; 
	// IF segment selector index is not within its descriptor table limits 
	// OR segment selector�s RPL � DPL of code segment, 
	// THEN #TS(SS selector + EXT); 
	// FI; 
	// Access segment descriptor for stack segment in GDT or LDT; 
	// IF stack segment DPL � DPL of code segment, 
	// OR stack segment does not indicate writable data segment, 
	// THEN #TS(SS selector + EXT); 
	// FI; 
	// IF stack segment not present THEN #SS(SS selector+EXT); FI; 
	// IF 32-bit gate 
	// THEN 
	// IF new stack does not have room for 40 bytes (error code pushed) 
	// OR 36 bytes (no error code pushed); 
	// THEN #SS(segment selector + EXT); 
	// FI; 
	// ELSE (* 16-bit gate *) 
	// IF new stack does not have room for 20 bytes (error code pushed) 
	// OR 18 bytes (no error code pushed); 
	// THEN #SS(segment selector + EXT); 
	// FI; 
	// FI; 
	// IF instruction pointer is not within code segment limits THEN #GP(0); FI; 
	// tempEFLAGS � EFLAGS; 
	// VM � 0; 
	// TF � 0; 
	// RF � 0; 
	// IF service through interrupt gate THEN IF � 0; FI; 
	// TempSS � SS; 
	// TempESP � ESP; 
	// SS:ESP � TSS(SS0:ESP0); (* Change to level 0 stack segment *) 
	// (* Following pushes are 16 bits for 16-bit gate and 32 bits for 32-bit gates *) 
	// (* Segment selector pushes in 32-bit mode are padded to two words *) 
	// Push(GS); 
	// Push(FS); 
	// Push(DS); 
	// Push(ES); 
	// Push(TempSS); 
	// Push(TempESP); 
	// Push(TempEFlags); 
	// Push(CS); 
	// Push(EIP); 
	// GS � 0; (*segment registers nullified, invalid in protected mode *) 
	// FS � 0; 
	// DS � 0; 
	// ES � 0; 
	// CS � Gate(CS); 
	// IF OperandSize=32 
	// THEN 
	// EIP � Gate(instruction pointer); 
	// ELSE (* OperandSize is 16 *) 
	// EIP � Gate(instruction pointer) AND 0000FFFFH; 
	// FI; 
	// (* Starts execution of new routine in Protected Mode *) 
	// END; 
	// INTRA-PRIVILEGE-LEVEL-INTERRUPT: 
	// (* PE=1, DPL = CPL or conforming segment *) 
	// IF 32-bit gate 
	// THEN 
	// IF current stack does not have room for 16 bytes (error code pushed) 
	// OR 12 bytes (no error code pushed); THEN #SS(0); 
	// FI; 
	// ELSE (* 16-bit gate *) 
	// IF current stack does not have room for 8 bytes (error code pushed) 
	// OR 6 bytes (no error code pushed); THEN #SS(0); 
	// FI; 
	// IF instruction pointer not within code segment limit THEN #GP(0); FI; 
	// IF 32-bit gate 
	// THEN 
	// Push (EFLAGS); 
	// Push (far pointer to 
	// CS:EIP � Gate(CS:EIP); (* segment descriptor information also loaded *) 
	// Push (ErrorCode); (* if any *) 
	// ELSE (* 16-bit gate *) 
	// Push (FLAGS); 
	// Push (far pointer to 
	// CS:IP � Gate(CS:IP); (* segment descriptor information also loaded *) 
	// Push (ErrorCode); (* if any *) 
	// FI; 
	// CS(RPL) � CPL; 
	// IF interrupt gate 
	// THEN 
	// IF � 0; FI; 
	// TF � 0; 
	// NT � 0; 
	// VM � 0; 
	// RF � 0; 
	// FI; 
	// END; 
	// Flags Affected 
	// The EFLAGS register is pushed onto the stack. The IF, TF, NT, AC, RF, and VM flags may be 
	// cleared, depending on the mode of operation of the processor when the INT instruction is 
	// executed (refer to the �Operation� section). If the interrupt uses a task gate, any flags may be set 
	// or cleared, controlled by the EFLAGS image in the new task�s TSS. 
	// Protected Mode Exceptions 
	// #GP(0) If the instruction pointer in the IDT or in the interrupt-, trap-, or task gate 
	// is beyond the code segment limits. 
	// #GP(selector) If the segment selector in the interrupt-, trap-, or task gate is null. 
	// If a interrupt-, trap-, or task gate, code segment, or TSS segment selector 
	// index is outside its descriptor table limits. 
	// If the interrupt vector number is outside the IDT limits. 
	// If an IDT descriptor is not an interrupt-, trap-, or task-descriptor. 
	// If an interrupt is generated by the INT n, INT 3, or INTO instruction and 
	// the DPL of an interrupt-, trap-, or task-descriptor is less than the CPL. 
	// If the segment selector in an interrupt- or trap-gate does not point to a 
	// segment descriptor for a code segment. 
	// If the segment selector for a TSS has its local/global bit set for local. 
	// If a TSS segment descriptor specifies that the TSS is busy or not available. 
	// #SS(0) If pushing the 
	// the bounds of the stack segment and no stack switch occurs. 
	// #SS(selector) If the SS register is being loaded and the segment pointed to is marked not 
	// present. 
	// If pushing the 
	// exceeds the bounds of the new stack segment when a stack switch occurs. 
	// #NP(selector) If code segment, interrupt-, trap-, or task gate, or TSS is not present. 
	// #TS(selector) If the RPL of the stack segment selector in the TSS is not equal to the DPL 
	// of the code segment being accessed by the interrupt or trap gate. 
	// If DPL of the stack segment descriptor pointed to by the stack segment 
	// selector in the TSS is not equal to the DPL of the code segment descriptor 
	// for the interrupt or trap gate. 
	// If the stack segment selector in the TSS is null. 
	// If the stack segment for the TSS is not a writable data segment. 
	// If segment-selector index for stack segment is outside descriptor table 
	// limits. 
	// #PF(fault-code) If a page fault occurs. 
	// Real-Address Mode Exceptions 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the interrupt vector number is outside the IDT limits. 
	// #SS If stack limit violation on push. 
	// If pushing the 
	// the bounds of the stack segment. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) (For INT n, INTO, or BOUND instruction) If the IOPL is less than 3 or the 
	// DPL of the interrupt-, trap-, or task-gate descriptor is not equal to 3. 
	// If the instruction pointer in the IDT or in the interrupt-, trap-, or task gate 
	// is beyond the code segment limits. 
	// #GP(selector) If the segment selector in the interrupt-, trap-, or task gate is null. 
	// If a interrupt-, trap-, or task gate, code segment, or TSS segment selector 
	// index is outside its descriptor table limits. 
	// If the interrupt vector number is outside the IDT limits. 
	// If an IDT descriptor is not an interrupt-, trap-, or task-descriptor. 
	// If an interrupt is generated by the INT n instruction and the DPL of an 
	// interrupt-, trap-, or task-descriptor is less than the CPL. 
	// If the segment selector in an interrupt- or trap-gate does not point to a 
	// segment descriptor for a code segment. 
	// If the segment selector for a TSS has its local/global bit set for local. 
	// #SS(selector) If the SS register is being loaded and the segment pointed to is marked not 
	// present. 
	// If pushing the 
	// data segments exceeds the bounds of the stack segment. 
	// #NP(selector) If code segment, interrupt-, trap-, or task gate, or TSS is not present. 
	// #TS(selector) If the RPL of the stack segment selector in the TSS is not equal to the DPL 
	// of the code segment being accessed by the interrupt or trap gate. 
	// If DPL of the stack segment descriptor for the TSS�s stack segment is not 
	// equal to the DPL of the code segment descriptor for the interrupt or trap 
	// gate. 
	// If the stack segment selector in the TSS is null. 
	// If the stack segment for the TSS is not a writable data segment. 
	// If segment-selector index for stack segment is outside descriptor table 
	// limits. 
	// #PF(fault-code) If a page fault occurs. 
	// #BP If the INT 3 instruction is executed. 
	// #OF If the INTO instruction is executed and the OF flag is set. 

	//BreakPoint()
}

Func_Prefix  INVD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// Flush(InternalCaches); 
	// SignalFlush(ExternalCaches); 
	// Continue (* Continue execution); 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If the current privilege level is not 0. 
	// Real-Address Mode Exceptions 
	// None. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) The INVD instruction cannot be executed in virtual-8086 mode. 

	//BreakPoint()
}

Func_Prefix  INVLPG (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// Flush(RelevantTLBEntries); 
	// Continue (* Continue execution); 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If the current privilege level is not 0. 
	// #UD Operand is a register. 
	// Real-Address Mode Exceptions 
	// #UD Operand is a register. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) The INVLPG instruction cannot be executed at the virtual-8086 mode. 

	//BreakPoint()
}

Func_Prefix  IRET (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  IRETD (VirtualMachine *posVm){
	UINT32	nEFlag;
	PAGED_CODE();
	// IF PE = 0 
	// THEN 
	// GOTO REAL-ADDRESS-MODE:; 
	// ELSE 
	// GOTO PROTECTED-MODE; 
	// FI; 
	// REAL-ADDRESS-MODE; 
	// IF OperandSize = 32 
	// THEN 
	// IF top 12 bytes of stack not within stack limits THEN #SS; FI; 
	// IF instruction pointer not within code segment limits THEN #GP(0); FI; 
	// EIP � Pop(); 
	// CS � Pop(); (* 32-bit pop, high-order 16 bits discarded *) 
	// tempEFLAGS � Pop(); 
	// EFLAGS � (tempEFLAGS AND 257FD5H) OR (EFLAGS AND 1A0000H); 
	// ELSE (* OperandSize = 16 *) 
	// IF top 6 bytes of stack are not within stack limits THEN #SS; FI; 
	// IF instruction pointer not within code segment limits THEN #GP(0); FI; 
	// EIP � Pop(); 
	// EIP � EIP AND 0000FFFFH; 
	// CS � Pop(); (* 16-bit pop *) 
	// EFLAGS[15:0] � Pop(); 
	// FI; 
	// END; 
	// PROTECTED-MODE: 
	// IF VM = 1 (* Virtual-8086 mode: PE=1, VM=1 *) 
	// THEN 
	// GOTO 
	// FI; 
	// IF NT = 1 
	// THEN 
	// GOTO TASK-
	// FI; 
	// IF OperandSize=32 
	// THEN 
	// IF top 12 bytes of stack not within stack limits 
	// THEN #SS(0) 
	// FI; 
	// tempEIP � Pop(); 
	// tempCS � Pop(); 
	// tempEFLAGS � Pop(); 
	// ELSE (* OperandSize = 16 *) 
	// IF top 6 bytes of stack are not within stack limits 
	// THEN #SS(0); 
	// FI; 
	// tempEIP � Pop(); 
	// tempCS � Pop(); 
	// tempEFLAGS � Pop(); 
	// tempEIP � tempEIP AND FFFFH; 
	// tempEFLAGS � tempEFLAGS AND FFFFH; 
	// FI; 
	// IF tempEFLAGS(VM) = 1 AND CPL=0 
	// THEN 
	// GOTO 
	// (* PE=1, VM=1 in EFLAGS image *) 
	// ELSE 
	// GOTO PROTECTED-MODE-
	// (* PE=1, VM=0 in EFLAGS image *) 
	// FI; 
	// 
	// (* Processor is in virtual-8086 mode when I
	// IF IOPL=3 (* Virtual mode: PE=1, VM=1, IOPL=3 *) 
	// THEN IF OperandSize = 32 
	// THEN 
	// IF top 12 bytes of stack not within stack limits THEN #SS(0); FI; 
	// IF instruction pointer not within code segment limits THEN #GP(0); FI; 
	// EIP � Pop(); 
	// CS � Pop(); (* 32-bit pop, high-order 16 bits discarded *) 
	// EFLAGS � Pop(); 
	// (*VM,IOPL,VIP,and VIF EFLAGS bits are not modified by pop *) 
	// ELSE (* OperandSize = 16 *) 
	// IF top 6 bytes of stack are not within stack limits THEN #SS(0); FI; 
	// IF instruction pointer not within code segment limits THEN #GP(0); FI; 
	// EIP � Pop(); 
	// EIP � EIP AND 0000FFFFH; 
	// CS � Pop(); (* 16-bit pop *) 
	// EFLAGS[15:0] � Pop(); (* IOPL in EFLAGS is not modified by pop *) 
	// FI; 
	// ELSE 
	// #GP(0); (* trap to virtual-8086 monitor: PE=1, VM=1, IOPL<3 *) 
	// FI; 
	// END; 
	// 
	// (* Interrupted procedure was in virtual-8086 mode: PE=1, VM=1 in flags image *) 
	// IF top 24 bytes of stack are not within stack segment limits 
	// THEN #SS(0); 
	// FI; 
	// IF instruction pointer not within code segment limits 
	// THEN #GP(0); 
	// FI; 
	// CS � tempCS; 
	// EIP � tempEIP; 
	// EFLAGS � tempEFLAGS 
	// TempESP � Pop(); 
	// TempSS � Pop(); 
	// ES � Pop(); (* pop 2 words; throw away high-order word *) 
	// DS � Pop(); (* pop 2 words; throw away high-order word *) 
	// FS � Pop(); (* pop 2 words; throw away high-order word *) 
	// GS � Pop(); (* pop 2 words; throw away high-order word *) 
	// SS:ESP � TempSS:TempESP; 
	// (* Resume execution in Virtual-8086 mode *) 
	// END; 
	// TASK-
	// Read segment selector in link field of current TSS; 
	// IF local/global bit is set to local 
	// OR index not within GDT limits 
	// THEN #GP(TSS selector); 
	// FI; 
	// Access TSS for task specified in link field of current TSS; 
	// IF TSS descriptor type is not TSS or if the TSS is marked not busy 
	// THEN #GP(TSS selector); 
	// FI; 
	// IF TSS not present 
	// THEN #NP(TSS selector); 
	// FI; 
	// SWITCH-TASKS (without nesting) to TSS specified in link field of current TSS; 
	// Mark the task just abandoned as NOT BUSY; 
	// IF EIP is not within code segment limit 
	// THEN #GP(0); 
	// FI; 
	// END; 
	// PROTECTED-MODE-
	// IF 
	// IF 
	// THEN GP(selector; FI; 
	// Read segment descriptor pointed to by the 
	// IF 
	// IF 
	// IF 
	// AND 
	// THEN #GP(selector); FI; 
	// IF 
	// IF 
	// THEN GOTO 
	// ELSE GOTO 
	// FI; 
	// END; 
	// 
	// IF EIP is not within code segment limits THEN #GP(0); FI; 
	// EIP � tempEIP; 
	// CS � tempCS; (* segment descriptor information also loaded *) 
	// EFLAGS (CF, PF, AF, ZF, SF, TF, DF, OF, NT) � tempEFLAGS; 
	// IF OperandSize=32 
	// THEN 
	// EFLAGS(RF, AC, ID) � tempEFLAGS; 
	// FI; 
	// IF CPL � IOPL 
	// THEN 
	// EFLAGS(IF) � tempEFLAGS; 
	// FI; 
	// IF CPL = 0 
	// THEN 
	// EFLAGS(IOPL) � tempEFLAGS; 
	// IF OperandSize=32 
	// THEN EFLAGS(VM, VIF, VIP) � tempEFLAGS; 
	// FI; 
	// FI; 
	// END; 
	// 
	// IF OperandSize=32 
	// THEN 
	// IF top 8 bytes on stack are not within limits THEN #SS(0); FI; 
	// ELSE (* OperandSize=16 *) 
	// IF top 4 bytes on stack are not within limits THEN #SS(0); FI; 
	// FI; 
	// Read 
	// IF stack segment selector is null THEN #GP(0); FI; 
	// IF 
	// THEN #GP(SSselector); FI; 
	// Read segment descriptor pointed to by 
	// IF stack segment selector RPL � RPL of the 
	// IF stack segment selector RPL � RPL of the 
	// OR the stack segment descriptor does not indicate a a writable data segment; 
	// OR stack segment DPL � RPL of the 
	// THEN #GP(SS selector); 
	// FI; 
	// IF stack segment is not present THEN #SS(SS selector); FI; 
	// IF tempEIP is not within code segment limit THEN #GP(0); FI; 
	// EIP � tempEIP; 
	// CS � tempCS; 
	// EFLAGS (CF, PF, AF, ZF, SF, TF, DF, OF, NT) � tempEFLAGS; 
	// IF OperandSize=32 
	// THEN 
	// EFLAGS(RF, AC, ID) � tempEFLAGS; 
	// FI; 
	// IF CPL � IOPL 
	// THEN 
	// EFLAGS(IF) � tempEFLAGS; 
	// FI; 
	// IF CPL = 0 
	// THEN 
	// EFLAGS(IOPL) � tempEFLAGS; 
	// IF OperandSize=32 
	// THEN EFLAGS(VM, VIF, VIP) � tempEFLAGS; 
	// FI; 
	// FI; 
	// CPL � RPL of the 
	// FOR each of segment register (ES, FS, GS, and DS) 
	// DO; 
	// IF segment register points to data or non-conforming code segment 
	// AND CPL > segment descriptor DPL (* stored in hidden part of segment register *) 
	// THEN (* segment register invalid *) 
	// SegmentSelector � 0; (* null segment selector *) 
	// FI; 
	// OD; 
	// END: 
	// Flags Affected 
	// All the flags and fields in the EFLAGS register are potentially modified, depending on the mode 
	// of operation of the processor. If performing a 
	// EFLAGS register will be modified according to the EFLAGS image stored in the previous task�s 
	// TSS. 
	// Protected Mode Exceptions 
	// #GP(0) 
	// If the 
	// If the 
	// #GP(selector) 
	// If a segment selector index is outside its descriptor table limits. 
	// If the 
	// If the DPL of a conforming-code segment is greater than the 
	// segment selector RPL. 
	// If the DPL for a nonconforming-code segment is not equal to the RPL of 
	// the code segment selector. 
	// If the stack segment descriptor DPL is not equal to the RPL of the 
	// code segment selector. 
	// If the stack segment is not a writable data segment. 
	// If the stack segment selector RPL is not equal to the RPL of the 
	// segment selector. 
	// If the segment descriptor for a code segment does not indicate it is a code 
	// segment. 
	// If the segment selector for a TSS has its local/global bit set for local. 
	// If a TSS segment descriptor specifies that the TSS is busy or not available. 
	// #SS(0) If the top bytes of stack are not within stack limits. 
	// #NP(selector) If the 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If an unaligned memory reference occurs when the CPL is 3 and alignment 
	// checking is enabled. 
	// Real-Address Mode Exceptions 
	// #GP If the 
	// #SS If the top bytes of stack are not within stack limits. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If the 
	// IF IOPL not equal to 3 
	// #PF(fault-code) If a page fault occurs. 
	// #SS(0) If the top bytes of stack are not within stack limits. 
	// #AC(0) If an unaligned memory reference occurs and alignment checking is 
	// enabled. 

	//BreakPoint()
}

Func_Prefix  JO (VirtualMachine *posVm)
{
	PAGED_CODE();
	if (posVm->Context.bIsJccEnabled)
	{
		if (posVm->Context.osReg.nOF == 1)
		{
			posVm->Context.osReg.EIP += (INT32)((UINT32*)(posVm->Context.osOpcodeBlock.nOperand0))[0];
		}
	}
}

Func_Prefix  JNO (VirtualMachine *posVm)
{
	PAGED_CODE();
	if (posVm->Context.bIsJccEnabled)
	{
		if (posVm->Context.osReg.nOF == 0)
		{
			posVm->Context.osReg.EIP += (INT32)((UINT32*)(posVm->Context.osOpcodeBlock.nOperand0))[0];
		}
	}
}

Func_Prefix  JC (VirtualMachine *posVm)
{
	PAGED_CODE();
	if (posVm->Context.bIsJccEnabled)
	{	
		if (posVm->Context.osReg.nCF == 1)
		{
			posVm->Context.osReg.EIP += (INT32)((UINT32*)(posVm->Context.osOpcodeBlock.nOperand0))[0];
		}
	}
}

Func_Prefix  JAE (VirtualMachine *posVm)
{
	PAGED_CODE();
	if (posVm->Context.bIsJccEnabled)
	{
		if (posVm->Context.osReg.nCF == 0)
		{
			posVm->Context.osReg.EIP += (INT32)((UINT32*)(posVm->Context.osOpcodeBlock.nOperand0))[0];
		}
	}
}

Func_Prefix  JZ (VirtualMachine *posVm)
{
	PAGED_CODE();
	if (posVm->Context.bIsJccEnabled)
	{
		if (posVm->Context.osReg.nZF == 1)
		{
			posVm->Context.osReg.EIP += (INT32)((UINT32*)(posVm->Context.osOpcodeBlock.nOperand0))[0];
		}
	}
}

Func_Prefix  JNZ (VirtualMachine *posVm)
{	
	PAGED_CODE();
	if (posVm->Context.bIsJccEnabled)
	{	
		if (posVm->Context.osReg.nZF == 0)
		{		
			posVm->Context.osReg.EIP += (INT32)((UINT32*)(posVm->Context.osOpcodeBlock.nOperand0))[0];
		}
	}
}

Func_Prefix  JNA (VirtualMachine *posVm)
{
	PAGED_CODE();
	if (posVm->Context.bIsJccEnabled)
	{
		if ((posVm->Context.osReg.nCF == 1) || (posVm->Context.osReg.nZF == 1))
		{
			posVm->Context.osReg.EIP += (INT32)((UINT32*)(posVm->Context.osOpcodeBlock.nOperand0))[0];
		}
	}
}

Func_Prefix  JNBE (VirtualMachine *posVm)
{
	PAGED_CODE();
	if (posVm->Context.bIsJccEnabled)
	{
		if ((posVm->Context.osReg.nCF == 0) && (posVm->Context.osReg.nZF == 0))
		{
			posVm->Context.osReg.EIP += (INT32)((UINT32*)(posVm->Context.osOpcodeBlock.nOperand0))[0];
		}
	}
}

Func_Prefix  JS (VirtualMachine *posVm)
{
	PAGED_CODE();
	if (posVm->Context.bIsJccEnabled)
	{
		if (posVm->Context.osReg.nSF == 1)
		{
			posVm->Context.osReg.EIP += (INT32)((UINT32*)(posVm->Context.osOpcodeBlock.nOperand0))[0];
		}
	}
}

Func_Prefix  JNS (VirtualMachine *posVm)
{
	PAGED_CODE();
	if (posVm->Context.bIsJccEnabled)
	{
		if (posVm->Context.osReg.nSF == 0)
		{
			posVm->Context.osReg.EIP += (INT32)((UINT32*)(posVm->Context.osOpcodeBlock.nOperand0))[0];
		}
	}
}

Func_Prefix  JPE (VirtualMachine *posVm)
{
	PAGED_CODE();
	if (posVm->Context.bIsJccEnabled)
	{
		if (posVm->Context.osReg.nPF == 1)
		{
			posVm->Context.osReg.EIP += (INT32)((UINT32*)(posVm->Context.osOpcodeBlock.nOperand0))[0];
		}
	}
}

Func_Prefix  JPO (VirtualMachine *posVm)
{
	PAGED_CODE();
	if (posVm->Context.bIsJccEnabled)
	{
		if (posVm->Context.osReg.nPF == 0)
		{
			posVm->Context.osReg.EIP += (INT32)((UINT32*)(posVm->Context.osOpcodeBlock.nOperand0))[0];
		}
	}
}

Func_Prefix  JNGE (VirtualMachine *posVm)
{
	PAGED_CODE();
	if (posVm->Context.bIsJccEnabled)
	{
		if (posVm->Context.osReg.nSF != posVm->Context.osReg.nOF)
		{
			posVm->Context.osReg.EIP += (INT32)((UINT32*)(posVm->Context.osOpcodeBlock.nOperand0))[0];
		}
	}
}

Func_Prefix  JNL (VirtualMachine *posVm)
{
	PAGED_CODE();
	if (posVm->Context.bIsJccEnabled)
	{
		if (posVm->Context.osReg.nSF == posVm->Context.osReg.nOF)
		{
			posVm->Context.osReg.EIP += (INT32)((UINT32*)(posVm->Context.osOpcodeBlock.nOperand0))[0];
		}
	}
}

Func_Prefix  JNG (VirtualMachine *posVm)
{
	PAGED_CODE();
	if (posVm->Context.bIsJccEnabled)
	{
		if ((posVm->Context.osReg.nZF == 1) && (posVm->Context.osReg.nSF == posVm->Context.osReg.nOF))
		{
			posVm->Context.osReg.EIP += (INT32)((UINT32*)(posVm->Context.osOpcodeBlock.nOperand0))[0];
		}
	}
}

Func_Prefix  JB (VirtualMachine *posVm)
{
	PAGED_CODE();
	if (posVm->Context.bIsJccEnabled)
	{
		if (posVm->Context.osReg.nCF == 1)
		{
			posVm->Context.osReg.EIP += (INT32)((UINT32*)(posVm->Context.osOpcodeBlock.nOperand0))[0];
		}
	}
}

Func_Prefix  JNB (VirtualMachine *posVm)
{
	PAGED_CODE();
	if (posVm->Context.bIsJccEnabled)
	{
		if (posVm->Context.osReg.nCF == 0)
		{
			posVm->Context.osReg.EIP += (INT32)((UINT32*)(posVm->Context.osOpcodeBlock.nOperand0))[0];
		}
	}
}

Func_Prefix  JECXZ(VirtualMachine *posVm)
{
	PAGED_CODE();
	if (posVm->Context.bIsJccEnabled)
	{
		if (posVm->Context.nFlag & p67)
		{
			if (posVm->Context.osReg.CX == 0)
			{
				posVm->Context.osReg.EIP += (INT32)((UINT32*)(posVm->Context.osOpcodeBlock.nOperand0))[0];
			}
		}
		else
		{
			if (posVm->Context.osReg.ECX == 0)
			{
				posVm->Context.osReg.EIP += (INT32)((UINT32*)(posVm->Context.osOpcodeBlock.nOperand0))[0];
			}
		}
	}

}

Func_Prefix  JNLE (VirtualMachine *posVm)
{
	PAGED_CODE();
	if (posVm->Context.bIsJccEnabled)
	{
		if ((posVm->Context.osReg.nZF == 0) && (posVm->Context.osReg.nSF == posVm->Context.osReg.nOF))
		{
			posVm->Context.osReg.EIP += (INT32)((UINT32*)(posVm->Context.osOpcodeBlock.nOperand0))[0];
		}
	}
	// IF condition 
	// THEN 
	// EIP � EIP + SignExtend(DEST); 
	// IF OperandSize = 16 
	// THEN 
	// EIP � EIP AND 0000FFFFH; 
	// FI; 
	// FI; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) 
	// If the offset being jumped to is beyond the limits of the CS segment. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If the offset being jumped to is beyond the limits of the CS segment or is 
	// outside of the effective address space from 0 to FFFFH. This condition can 
	// occur if 32-address size override prefix is used. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) 
	// If the offset being jumped to is beyond the limits of the CS segment or is 
	// outside of the effective address space from 0 to FFFFH. This condition can 
	// occur if 32-address size override prefix is used. 
}


// No Flag Affected
Func_Prefix JMP16 (VirtualMachine *posVm)
{
	PAGED_CODE();
	posVm->Context.osReg.EIP = ((UINT32*)(posVm->Context.osOpcodeBlock.nOperand0))[0];
}

Func_Prefix  JMP (VirtualMachine *posVm)
{
	PAGED_CODE();
	if(posVm->Context.osOpcodeBlock.nOperand0 == 0)
	{
		return;
	}
	switch(posVm->Context.osOpcodeBlock.nOperandsMemSize)
	{
	case 0:
		if (!posVm->Context.bFlagRM)
		{
			posVm->Context.osReg.EIP += (INT32)((UINT32*)(posVm->Context.osOpcodeBlock.nOperand0))[0];
			break;
		}
	default:
		// If Jmp API, Jmp ds:DIGIT[REG], Jmp ds:DIGIT happend EIP set to nowhere
		if (posVm->Context.bFlagRM && (posVm->Context.byMod_R_M == 0x25 || posVm->Context.byReg == 0x5 || (posVm->Context.bFlagSIB && posVm->Context.byBase == 0x5)))
		{
			posVm->Context.osReg.EIP = 0xFFFFFFFF;
		}
		else
		{
			posVm->Context.osReg.EIP = ((UINT32*)(posVm->Context.osOpcodeBlock.nOperand0))[0];
		}
		break;
	}

	// IF near jump 
	// THEN IF near relative jump 
	// THEN 
	// tempEIP � EIP + DEST; (* EIP is instruction following JMP instruction*) 
	// ELSE (* near absolute jump *) 
	// tempEIP � DEST; 
	// FI; 
	// IF tempEIP is beyond code segment limit THEN #GP(0); FI; 
	// IF OperandSize = 32 
	// THEN 
	// EIP � tempEIP; 
	// ELSE (* OperandSize=16 *) 
	// EIP � tempEIP AND 0000FFFFH; 
	// FI; 
	// FI: 
	// IF far jump AND (PE = 0 OR (PE = 1 AND VM = 1)) (* real-address or virtual-8086 mode *) 
	// THEN 
	// tempEIP � DEST(offset); (* DEST is ptr16:32 or [m16:32] *) 
	// IF tempEIP is beyond code segment limit THEN #GP(0); FI; 
	// CS � DEST(segment selector); (* DEST is ptr16:32 or [m16:32] *) 
	// IF OperandSize = 32 
	// THEN 
	// EIP � tempEIP; (* DEST is ptr16:32 or [m16:32] *) 
	// ELSE (* OperandSize = 16 *) 
	// EIP � tempEIP AND 0000FFFFH; (* clear upper 16 bits *) 
	// FI; 
	// FI; 
	// IF far jump AND (PE = 1 AND VM = 0) (* Protected mode, not virtual-8086 mode *) 
	// THEN 
	// IF effective address in the CS, DS, ES, FS, GS, or SS segment is illegal 
	// OR segment selector in target operand null 
	// THEN #GP(0); 
	// FI; 
	// IF segment selector index not within descriptor table limits 
	// THEN #GP(new selector); 
	// FI; 
	// Read type and access rights of segment descriptor; 
	// IF segment type is not a conforming or nonconforming code segment, call gate, 
	// task gate, or TSS THEN #GP(segment selector); FI; 
	// Depending on type and access rights 
	// GO TO CONFORMING-CODE-SEGMENT; 
	// GO TO NONCONFORMING-CODE-SEGMENT; 
	// GO TO CALL-GATE; 
	// GO TO TASK-GATE; 
	// GO TO TASK-STATE-SEGMENT; 
	// ELSE 
	// #GP(segment selector); 
	// FI; 
	// CONFORMING-CODE-SEGMENT: 
	// IF DPL > CPL THEN #GP(segment selector); FI; 
	// IF segment not present THEN #NP(segment selector); FI; 
	// tempEIP � DEST(offset); 
	// IF OperandSize=16 
	// THEN tempEIP � tempEIP AND 0000FFFFH; 
	// FI; 
	// IF tempEIP not in code segment limit THEN #GP(0); FI; 
	// CS � DEST(SegmentSelector); (* segment descriptor information also loaded *) 
	// CS(RPL) � CPL 
	// EIP � tempEIP; 
	// END; 
	// NONCONFORMING-CODE-SEGMENT: 
	// IF (RPL > CPL) OR (DPL � CPL) THEN #GP(code segment selector); FI; 
	// IF segment not present THEN #NP(segment selector); FI; 
	// IF instruction pointer outside code segment limit THEN #GP(0); FI; 
	// tempEIP � DEST(offset); 
	// IF OperandSize=16 
	// THEN tempEIP � tempEIP AND 0000FFFFH; 
	// FI; 
	// IF tempEIP not in code segment limit THEN #GP(0); FI; 
	// CS � DEST(SegmentSelector); (* segment descriptor information also loaded *) 
	// CS(RPL) � CPL 
	// EIP � tempEIP; 
	// END; 
	// CALL-GATE: 
	// IF call gate DPL < CPL 
	// OR call gate DPL < call gate segment-selector RPL 
	// THEN #GP(call gate selector); FI; 
	// IF call gate not present THEN #NP(call gate selector); FI; 
	// IF call gate code-segment selector is null THEN #GP(0); FI; 
	// IF call gate code-segment selector index is outside descriptor table limits 
	// THEN #GP(code segment selector); FI; 
	// Read code segment descriptor; 
	// IF code-segment segment descriptor does not indicate a code segment 
	// OR code-segment segment descriptor is conforming and DPL > CPL 
	// OR code-segment segment descriptor is non-conforming and DPL � CPL 
	// THEN #GP(code segment selector); FI; 
	// IF code segment is not present THEN #NP(code-segment selector); FI; 
	// IF instruction pointer is not within code-segment limit THEN #GP(0); FI; 
	// tempEIP � DEST(offset); 
	// IF GateSize=16 
	// THEN tempEIP � tempEIP AND 0000FFFFH; 
	// FI; 
	// IF tempEIP not in code segment limit THEN #GP(0); FI; 
	// CS � DEST(SegmentSelector); (* segment descriptor information also loaded *) 
	// CS(RPL) � CPL 
	// EIP � tempEIP; 
	// END; 
	// TASK-GATE: 
	// IF task gate DPL < CPL 
	// OR task gate DPL < task gate segment-selector RPL 
	// THEN #GP(task gate selector); FI; 
	// IF task gate not present THEN #NP(gate selector); FI; 
	// Read the TSS segment selector in the task-gate descriptor; 
	// IF TSS segment selector local/global bit is set to local 
	// OR index not within GDT limits 
	// OR TSS descriptor specifies that the TSS is busy 
	// THEN #GP(TSS selector); FI; 
	// IF TSS not present THEN #NP(TSS selector); FI; 
	// SWITCH-TASKS to TSS; 
	// IF EIP not within code segment limit THEN #GP(0); FI; 
	// END; 
	// TASK-STATE-SEGMENT: 
	// IF TSS DPL < CPL 
	// OR TSS DPL < TSS segment-selector RPL 
	// OR TSS descriptor indicates TSS not available 
	// THEN #GP(TSS selector); FI; 
	// IF TSS is not present THEN #NP(TSS selector); FI; 
	// SWITCH-TASKS to TSS 
	// IF EIP not within code segment limit THEN #GP(0); FI; 
	// END; 
	// Flags Affected 
	// All flags are affected if a task switch occurs; no flags are affected if a task switch does not occur. 
	// Protected Mode Exceptions 
	// #GP(0) If offset in target operand, call gate, or TSS is beyond the code segment 
	// limits. 
	// If the segment selector in the destination operand, call gate, task gate, or 
	// TSS is null. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #GP(selector) If segment selector index is outside descriptor table limits. 
	// If the segment descriptor pointed to by the segment selector in the 
	// destination operand is not for a conforming-code segment, nonconforming-
	// code segment, call gate, task gate, or task state segment. 
	// If the DPL for a nonconforming-code segment is not equal to the CPL 
	// (When not using a call gate.) If the RPL for the segment�s segment selector 
	// is greater than the CPL. 
	// If the DPL for a conforming-code segment is greater than the CPL. 
	// If the DPL from a call-gate, task-gate, or TSS segment descriptor is less 
	// than the CPL or than the RPL of the call-gate, task-gate, or TSS�s segment 
	// selector. 
	// If the segment descriptor for selector in a call gate does not indicate it is a 
	// code segment. 
	// If the segment descriptor for the segment selector in a task gate does not 
	// indicate available TSS. 
	// If the segment selector for a TSS has its local/global bit set for local. 
	// If a TSS segment descriptor specifies that the TSS is busy or not available. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NP (selector) If the code segment being accessed is not present. 
	// If call gate, task gate, or TSS not present. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. (Only occurs when fetching 
	// target from memory.) 
	// Real-Address Mode Exceptions 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) 
	// If the target operand is beyond the code segment limits. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. (Only occurs when fetching target from memory.) 
}

Func_Prefix  LAHF (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// AH � EFLAGS(SF:ZF:0:AF:0:PF:1:CF); 
	// Flags Affected 
	// None (that is, the state of the flags in the EFLAGS register is not affected). 
	// Exceptions (All Operating Modes) 
	// None. 


	//BreakPoint()
}

Func_Prefix  LAR16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  LAR (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF SRC(Offset) > descriptor table limit THEN ZF � 0; FI; 
	// Read segment descriptor; 
	// IF SegmentDescriptor(Type) � conforming code segment 
	// AND (CPL > DPL) OR (RPL > DPL) 
	// OR Segment type is not valid for instruction 
	// THEN 
	// ZF � 0 
	// ELSE 
	// IF OperandSize = 32 
	// THEN 
	// DEST � [SRC] AND 00FxFF00H; 
	// ELSE (*OperandSize = 16*) 
	// DEST � [SRC] AND FF00H; 
	// FI; 
	// FI; 
	// Flags Affected 
	// The ZF flag is set to 1 if the access rights are loaded successfully; otherwise, it is cleared to 0. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. (Only occurs when fetching 
	// target from memory.) 
	// Real-Address Mode Exceptions 
	// #UD The LAR instruction is not recognized in real-address mode. 
	// Virtual-8086 Mode Exceptions 
	// #UD The LAR instruction cannot be executed in virtual-8086 mode. 

	//BreakPoint()
}

Func_Prefix  LDMXCSR (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// MXCSR = m32; 
	// LDMXCSR�Load Streaming SIMD Extension Control/Status 
	// C/C++ Compiler Intrinsic Equivalent 
	// _mm_setcsr(unsigned int i) 
	// Sets the control register to the value specified. 
	// Exceptions 
	// General protection fault if reserved bits are loaded with non-zero values. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF(fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. #AC for unaligned memory reference. To enable 
	// #AC exceptions, three conditions must be TRUE(CR0.AM is set; 
	// EFLAGS.AC is set; current CPL is 3). 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #UD 
	// If CR4.OSFXSR(bit 9) = 0. 
	// #UD 
	// If CPUID.XMM(EDX bit 25) = 0. 
	// LDMXCSR�Load Streaming SIMD Extension Control/Status 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF(fault-code) For a page fault. 
	// #AC For unaligned memory reference. 
	// Comments 
	// The usage of Repeat Prefix (F3H) with LDMXCSR is reserved. Different processor implementations 
	// may handle this prefix differently. Usage of this prefix with LDMXCSR risks incompatibility 
	// with future processors. 

	//BreakPoint()
}

Func_Prefix  LDS16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  LDS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();



//	//BreakPoint()
}

Func_Prefix  LES16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  LES (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  LFS16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  LFS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  LGS16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  LGS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  LSS16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  LSS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF Protected Mode 
	// THEN IF SS is loaded 
	// THEN IF SegementSelector = null 
	// THEN #GP(0); 
	// FI; 
	// ELSE IF Segment selector index is not within descriptor table limits 
	// OR Segment selector RPL � CPL 
	// OR Access rights indicate nonwritable data segment 
	// OR DPL � CPL 
	// THEN #GP(selector); 
	// FI; 
	// ELSE IF Segment marked not present 
	// THEN #SS(selector); 
	// FI; 
	// SS � SegmentSelector(SRC); 
	// SS � SegmentDescriptor([SRC]); 
	// ELSE IF DS, ES, FS, or GS is loaded with non-null segment selector 
	// THEN IF Segment selector index is not within descriptor table limits 
	// OR Access rights indicate segment neither data nor readable code segment 
	// OR (Segment is data or nonconforming-code segment 
	// AND both RPL and CPL > DPL) 
	// THEN #GP(selector); 
	// FI; 
	// ELSE IF Segment marked not present 
	// THEN #NP(selector); 
	// FI; 
	// SegmentRegister � SegmentSelector(SRC) AND RPL; 
	// SegmentRegister � SegmentDescriptor([SRC]); 
	// ELSE IF DS, ES, FS or GS is loaded with a null selector: 
	// SegmentRegister � NullSelector; 
	// SegmentRegister(DescriptorValidBit) � 0; (*hidden flag; not accessible by software*) 
	// FI; 
	// FI; 
	// IF (Real-Address or Virtual-8086 Mode) 
	// THEN 
	// SegmentRegister � SegmentSelector(SRC); 
	// FI; 
	// DEST � Offset(SRC); 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #UD If source operand is not a memory location. 
	// #GP(0) If a null selector is loaded into the SS register. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #GP(selector) If the SS register is being loaded and any of the following is TRUE: the 
	// segment selector index is not within the descriptor table limits, the 
	// segment selector RPL is not equal to CPL, the segment is a nonwritable 
	// data segment, or DPL is not equal to CPL. 
	// If the DS, ES, FS, or GS register is being loaded with a non-null segment 
	// selector and any of the following is TRUE: the segment selector index is not 
	// within descriptor table limits, the segment is neither a data nor a readable 
	// code segment, or the segment is a data or nonconforming-code segment 
	// and both RPL and CPL are greater than DPL. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #SS(selector) If the SS register is being loaded and the segment is marked not present. 
	// #NP(selector) If DS, ES, FS, or GS register is being loaded with a non-null segment 
	// selector and the segment is marked not present. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS If a memory operand effective address is outside the SS segment limit. 
	// #UD If source operand is not a memory location. 
	// Virtual-8086 Mode Exceptions 
	// #UD If source operand is not a memory location. 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 
	//BreakPoint()
}


// No Flags Affected
Func_Prefix  LEA16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();

	//BreakPoint()
}


Func_Prefix  LEA (VirtualMachine *posVm)
{
	PAGED_CODE();
// 	__asm mov 
// 	__asm lea 
// 	if (posVm->Context.osOpcodeBlock.nOperandsMemSize > 0)
// 	{
// 		*(UINT32*)(posVm->Context.osOpcodeBlock.nOperand0) = *(UINT32*)posVm->Context.osOpcodeBlock.nOperand1;
// 	}
// 	else 
// 	{
		*(UINT32*)(posVm->Context.osOpcodeBlock.nOperand0) = posVm->Context.osOpcodeBlock.nOperand1;
//	}
	// IF OperandSize = 16 AND AddressSize = 16 
	// THEN 
	// DEST � EffectiveAddress(SRC); (* 16-bit address *) 
	// ELSE IF OperandSize = 16 AND AddressSize = 32 
	// THEN 
	// temp � EffectiveAddress(SRC); (* 32-bit address *) 
	// DEST � temp[0..15]; (* 16-bit address *) 
	// ELSE IF OperandSize = 32 AND AddressSize = 16 
	// THEN 
	// temp � EffectiveAddress(SRC); (* 16-bit address *) 
	// DEST � ZeroExtend(temp); (* 32-bit address *) 
	// ELSE IF OperandSize = 32 AND AddressSize = 32 
	// THEN 
	// DEST � EffectiveAddress(SRC); (* 32-bit address *) 
	// FI; 
	// FI; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #UD If source operand is not a memory location. 
	// Real-Address Mode Exceptions 
	// #UD If source operand is not a memory location. 
	// Virtual-8086 Mode Exceptions 
	// #UD If source operand is not a memory location. 	
}

Func_Prefix  LEAVE16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}

Func_Prefix  LEAVE (VirtualMachine *posVm)
{
	PAGED_CODE();
	if (posVm->Context.osReg.EBP == 0)
	{
		return;
	}
	posVm->Context.osReg.ESP = posVm->Context.osReg.EBP;	
	posVm->Context.osReg.EBP = PopStack(posVm);
	// IF StackAddressSize = 32 
	// THEN 
	// ESP � EBP; 
	// ELSE (* StackAddressSize = 16*) 
	// SP � BP; 
	// FI; 
	// IF OperandSize = 32 
	// THEN 
	// EBP � Pop(); 
	// ELSE (* OperandSize = 16*) 
	// BP � Pop(); 
	// FI; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #SS(0) If the EBP register points to a location that is not within the limits of the 
	// current stack segment. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If the EBP register points to a location outside of the effective address 
	// space from 0 to 0FFFFH. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) 
	// If the EBP register points to a location outside of the effective address 
	// space from 0 to 0FFFFH. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 
	// LES�Load Full Pointer 
	// Refer to entry for LDS/LES/LFS/LGS/LSS�Load Far Pointer. 
	// LFS�Load Full Pointer 
	// Refer to entry for LDS/LES/LFS/LGS/LSS�Load Far Pointer. 
}

Func_Prefix  LGDT (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  LIDT (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF instruction is LIDT 
	// THEN 
	// IF OperandSize = 16 
	// THEN 
	// IDTR(Limit) � SRC[0:15]; 
	// IDTR(Base) � SRC[16:47] AND 00FFFFFFH; 
	// ELSE (* 32-bit Operand Size *) 
	// IDTR(Limit) � SRC[0:15]; 
	// IDTR(Base) � SRC[16:47]; 
	// FI; 
	// ELSE (* instruction is LGDT *) 
	// IF OperandSize = 16 
	// THEN 
	// GDTR(Limit) � SRC[0:15]; 
	// GDTR(Base) � SRC[16:47] AND 00FFFFFFH; 
	// ELSE (* 32-bit Operand Size *) 
	// GDTR(Limit) � SRC[0:15]; 
	// GDTR(Base) � SRC[16:47]; 
	// FI; FI; 
	// LGDT/LIDT�Load Global/Interrupt Descriptor Table Register 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #UD If source operand is not a memory location. 
	// #GP(0) If the current privilege level is not 0. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// Real-Address Mode Exceptions 
	// #UD If source operand is not a memory location. 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// LGS�Load Full Pointer 
	// Refer to entry for LDS/LES/LFS/LGS/LSS�Load Far Pointer. 

	//BreakPoint()
}

Func_Prefix  LLDT16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  LLDT (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF SRC(Offset) > descriptor table limit THEN #GP(segment selector); FI; 
	// Read segment descriptor; 
	// IF SegmentDescriptor(Type) � LDT THEN #GP(segment selector); FI; 
	// IF segment descriptor is not present THEN #NP(segment selector); 
	// LDTR(SegmentSelector) � SRC; 
	// LDTR(SegmentDescriptor) � GDTSegmentDescriptor; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If the current privilege level is not 0. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #GP(selector) If the selector operand does not point into the Global Descriptor Table or 
	// if the entry in the GDT is not a Local Descriptor Table. 
	// Segment selector is beyond GDT limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #NP(selector) If the LDT descriptor is not present. 
	// #PF(fault-code) If a page fault occurs. 
	// Real-Address Mode Exceptions 
	// #UD The LLDT instruction is not recognized in real-address mode. 
	// Virtual-8086 Mode Exceptions 
	// #UD The LLDT instruction is recognized in virtual-8086 mode. 
	// LIDT�Load Interrupt Descriptor Table Register 
	// Refer to entry for LGDT/LIDT�Load Global/Interrupt Descriptor Table Register. 

	//BreakPoint()
}

Func_Prefix  LMSW16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  LMSW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// CR0[0:3] � SRC[0:3]; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If the current privilege level is not 0. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If the current privilege level is not 0. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 

	//BreakPoint()
}

Func_Prefix  LOCK (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// AssertLOCK#(DurationOfAccompaningInstruction) 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #UD 
	// If the LOCK prefix is used with an instruction not listed in the �Description� 
	// section above. Other exceptions can be generated by the instruction 
	// that the LOCK prefix is being applied to. 
	// Real-Address Mode Exceptions 
	// #UD 
	// If the LOCK prefix is used with an instruction not listed in the �Description� 
	// section above. Other exceptions can be generated by the instruction 
	// that the LOCK prefix is being applied to. 
	// Virtual-8086 Mode Exceptions 
	// #UD 
	// If the LOCK prefix is used with an instruction not listed in the �Description� 
	// section above. Other exceptions can be generated by the instruction 
	// that the LOCK prefix is being applied to. 

	//BreakPoint()
}

Func_Prefix  LODS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  LODSB16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  LODSB (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  LODSD16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  LODSD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF (byte load) 
	// THEN 
	// AL � SRC; (* byte load *) 
	// THEN IF DF = 0 
	// THEN (E)SI � (E)SI + 1; 
	// ELSE (E)SI � (E)SI � 1; 
	// FI; 
	// ELSE IF (word load) 
	// THEN 
	// AX � SRC; (* word load *) 
	// THEN IF DF = 0 
	// THEN (E)SI � (E)SI + 2; 
	// ELSE (E)SI � (E)SI � 2; 
	// FI; 
	// ELSE (* doubleword transfer *) 
	// EAX � SRC; (* doubleword load *) 
	// THEN IF DF = 0 
	// THEN (E)SI � (E)SI + 4; 
	// ELSE (E)SI � (E)SI � 4; 
	// FI; 
	// FI; 
	// FI; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) 
	// If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  LOOP (VirtualMachine *posVm)
{
	PAGED_CODE();
	if (posVm->Context.bIsJccEnabled)
	{
		if (posVm->Context.osReg.ECX != 0)
		{
			posVm->Context.osReg.ECX--;
			posVm->Context.osReg.EIP += *(UINT32*)posVm->Context.osOpcodeBlock.nOperand0;
		}
	}
}

Func_Prefix  LOOPNZ (VirtualMachine *posVm)
{
	PAGED_CODE();
	if (posVm->Context.bIsJccEnabled)
	{
		if (posVm->Context.osReg.ECX != 0 && posVm->Context.osReg.nZF == 1)
		{
			posVm->Context.osReg.EIP += *(UINT32*)posVm->Context.osOpcodeBlock.nOperand0;
		}
	}
}

Func_Prefix  LOOPZ (VirtualMachine *posVm)
{
	PAGED_CODE();
	if (posVm->Context.bIsJccEnabled)
	{
		if (posVm->Context.osReg.ECX != 0 && posVm->Context.osReg.nZF == 0)
		{
			posVm->Context.osReg.EIP += *(UINT32*)posVm->Context.osOpcodeBlock.nOperand0;
		}
	}

		// IF AddressSize = 32 
		// THEN 
		// Count is ECX; 
		// ELSE (* AddressSize = 16 *) 
		// Count is CX; 
		// FI; 
		// Count � Count � 1; 
		// IF instruction is not LOOP 
		// THEN 
		// IF (instruction = LOOPE) OR (instruction = LOOPZ) 
		// THEN 
		// IF (ZF =1) AND (Count � 0) 
		// THEN BranchCond � 1; 
		// ELSE BranchCond � 0; 
		// FI; 
		// FI; 
		// IF (instruction = LOOPNE) OR (instruction = LOOPNZ) 
		// THEN 
		// IF (ZF =0 ) AND (Count � 0) 
		// THEN BranchCond � 1; 
		// ELSE BranchCond � 0; 
		// FI; 
		// FI; 
		// ELSE (* instruction = LOOP *) 
		// IF (Count � 0) 
		// THEN BranchCond � 1; 
		// ELSE BranchCond � 0; 
		// FI; 
		// FI; 
		// IF BranchCond = 1 
		// THEN 
		// EIP � EIP + SignExtend(DEST); 
		// IF OperandSize = 16 
		// THEN 
		// EIP � EIP AND 0000FFFFH; 
		// FI; 
		// ELSE 
		// Terminate loop and continue program execution at EIP; 
		// FI; 
		// Flags Affected 
		// None. 
		// Protected Mode Exceptions 
		// #GP(0) If the offset jumped to is beyond the limits of the code segment. 
		// Real-Address Mode Exceptions 
		// None. 
		// Virtual-8086 Mode Exceptions 
		// None. 
}

Func_Prefix  LSL16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  LSL (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF SRC(Offset) > descriptor table limit 
	// THEN ZF � 0; FI; 
	// Read segment descriptor; 
	// IF SegmentDescriptor(Type) � conforming code segment 
	// AND (CPL > DPL) OR (RPL > DPL) 
	// OR Segment type is not valid for instruction 
	// THEN 
	// ZF � 0 
	// ELSE 
	// temp � SegmentLimit([SRC]); 
	// IF (G = 1) 
	// THEN 
	// temp � ShiftLeft(12, temp) OR 00000FFFH; 
	// FI; 
	// IF OperandSize = 32 
	// THEN 
	// DEST � temp; 
	// ELSE (*OperandSize = 16*) 
	// DEST � temp AND FFFFH; 
	// FI; 
	// FI; 
	// Flags Affected 
	// The ZF flag is set to 1 if the segment limit is loaded successfully; otherwise, it is cleared to 0. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #UD The LSL instruction is not recognized in real-address mode. 
	// Virtual-8086 Mode Exceptions 
	// #UD The LSL instruction is not recognized in virtual-8086 mode. 
	// LSS�Load Full Pointer 
	// Refer to entry for LDS/LES/LFS/LGS/LSS�Load Far Pointer. 

	//BreakPoint()
}

Func_Prefix  LTR16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  LTR (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF SRC(Offset) > descriptor table limit OR IF SRC(type) � global 
	// THEN #GP(segment selector); 
	// FI; 
	// Read segment descriptor; 
	// IF segment descriptor is not for an available TSS THEN #GP(segment selector); FI; 
	// IF segment descriptor is not present THEN #NP(segment selector); 
	// TSSsegmentDescriptor(busy) � 1; 
	// (* Locked read-modify-write operation on the entire descriptor when setting busy flag *) 
	// TaskRegister(SegmentSelector) � SRC; 
	// TaskRegister(SegmentDescriptor) � TSSSegmentDescriptor; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If the current privilege level is not 0. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #GP(selector) If the source selector points to a segment that is not a TSS or to one for a 
	// task that is already busy. 
	// If the selector points to LDT or is beyond the GDT limit. 
	// #NP(selector) If the TSS is marked not present. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// Real-Address Mode Exceptions 
	// #UD The LTR instruction is not recognized in real-address mode. 
	// Virtual-8086 Mode Exceptions 
	// #UD The LTR instruction is not recognized in virtual-8086 mode. 

	//BreakPoint()
}

Func_Prefix  MASKMOVQ (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF (SRC[7] = 1) THEN 
	// m64[EDI] = DEST[7-0]; 
	// ELSE 
	// M64[EDI] = 0X0; 
	// IF (SRC[15] = 1) THEN 
	// m64[EDI] = DEST[15-8]; 
	// ELSE 
	// M64[EDI] = 0X0; 
	// IF (SRC[23] = 1) THEN 
	// m64[EDI] = DEST[23-16]; 
	// ELSE 
	// M64[EDI] = 0X0; 
	// IF (SRC[31] = 1) THEN 
	// m64[EDI] = DEST[31-24]; 
	// ELSE 
	// M64[EDI] = 0X0; 
	// IF (SRC[39] = 1) THEN 
	// m64[EDI] = DEST[39-32]; 
	// ELSE 
	// M64[EDI] = 0X0; 
	// IF (SRC[47] = 1) THEN 
	// m64[EDI] = DEST[47-40]; 
	// ELSE 
	// M64[EDI] = 0X0; 
	// IF (SRC[55] = 1) THEN 
	// m64[EDI] = DEST[55-48]; 
	// ELSE 
	// M64[EDI] = 0X0; 
	// IF (SRC[63] = 1) THEN 
	// m64[EDI] = DEST[63-56]; 
	// ELSE 
	// M64[EDI] = 0X0; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// void_m_maskmovq(__m64d, __m64n, char * p) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// void_mm_maskmove_si64(__m64d, __m64n, char * p) 
	// Conditionally store byte elements of d to address p. The high bit of each byte in the selector n 
	// determines whether the corresponding byte in d will be stored. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #AC For unaligned memory reference. To enable #AC exceptions, three conditions 
	// must be TRUE(CR0.AM is set; EFLAGS.AC is set; current CPL is 3) 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #AC For unaligned memory reference if the current privilege level is 3. 
	// #PF (fault-code) For a page fault. 
	// Comments 
	// MASKMOVQ can be used to improve performance for algorithms which need to merge data on 
	// a byte granularity. MASKMOVQ should not cause a read for ownership; doing so generates 
	// unnecessary bandwidth since data is to be written directly using the byte-mask without allocating 
	// old data prior to the store. Similar to the Streaming SIMD Extension non-temporal store 
	// instructions, MASKMOVQ minimizes pollution of the cache hierarchy. MASKMOVQ implicitly 
	// uses weakly-ordered, write-combining stores (WC). Refer to Section 9.3.9., Cacheability 
	// Control Instructions in Chapter 9, Programming with the Streaming SIMD Extensions of the 
	// Intel Architecture Software Developer�s Manual, Volume 1, for further information about nontemporal 
	// stores. 
	// As a consequence of the resulting weakly-ordered memory consistency model, a fencing operation 
	// such as SFENCE should be used if multiple processors may use different memory types to 
	// read/write the same memory location specified by edi. 
	// This instruction behaves identically to MMX� instructions, in the presence of x87-FP instructions: 
	// transition from x87-FP to MMX� technology (TOS=0, FP valid bits set to all valid). 
	// MASMOVQ ignores the value of CR4.OSFXSR. Since it does not affect the new Streaming 
	// SIMD Extension state, they will not generate an invalid exception if CR4.OSFXSR = 0. 

	//BreakPoint()
}

Func_Prefix  MAXPS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// bayad baraye in dastor F3 Prefix ro barresi kard chenancheh TRUE bood dastor MAXSS ejra mishavad
	// Baraye in manzor index mmx pass shode be tabe index register haye EXX mishavad hamchenin size hafeze dar operand dovom
	// az 64 be 32 tabdil mishavad


	// IF (DEST[31-0]=NaN) THEN 
	// DEST[31-0] = SRC[31-0]; 
	// ELSE 
	// IF (SRC[31-0] = NaN) THEN 
	// DEST[31-0] = SRC[31-0]; 
	// ELSE 
	// IF (DEST[31-0] > SRC/m128[31-0]) THEN 
	// DEST[31-0] = DEST[31-0]; 
	// ELSE 
	// DEST[31-0] = SRC/m128[31-0]; 
	// FI 
	// FI 
	// FI 
	// IF (DEST[63-32]=NaN) THEN 
	// DEST[63-32] = SRC[63-32]; 
	// ELSE 
	// IF (SRC[63-32] = NaN) THEN 
	// DEST[63-32] = SRC[63-32]; 
	// ELSE 
	// IF (DEST[63-32] > SRC/m128[63-32]) THEN 
	// DEST[63-32] = DEST[63-32]; 
	// ELSE 
	// DEST[63-32] = SRC/m128[63-32]; 
	// FI 
	// FI 
	// FI 
	// IF (DEST[95-64]=NaN) THEN 
	// DEST[95-64] = SRC[95-64]; 
	// ELSE 
	// IF (SRC[95-64] = NaN) THEN 
	// DEST[95-64] = SRC[95-64]; 
	// ELSE 
	// IF (DEST[95-64] > SRC/m128[95-64]) THEN 
	// DEST[95-64] = DEST[95-64]; 
	// ELSE 
	// DEST[95-64] = SRC/m128[95-64]; 
	// FI 
	// FI 
	// FI 
	// IF (DEST[127-96]=NaN) THEN 
	// DEST[127-96] = SRC[127-96]; 
	// ELSE 
	// IF (SRC[127-96] = NaN) THEN 
	// DEST[127-96] = SRC[127-96]; 
	// ELSE 
	// IF (DEST[127-96] > SRC/m128[127-96]) THEN 
	// DEST[127-96] = DEST[127-96]; 
	// ELSE 
	// DEST[127-96] = SRC/m128[127-96]; 
	// FI 
	// FI 
	// FI 
	// Exceptions 
	// General protection exception if not aligned on 16-byte boundary, including unaligned reference 
	// within the stack segment. 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_max_ps(__m128 a, __m128 b) 
	// Computes the maximums of the four SP FP values of a and b. 
	// Exceptions 
	// General protection exception if not aligned on 16-byte boundary, regardless of segment. 
	// Numeric Exceptions 
	// Invalid (including qNaN source operand), Denormal. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF(fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #XM For an unmasked Streaming 
	// (CR4.OSXMMEXCPT =1). 
	// SIMD Extension numeric exception 
	// #UD For an unmasked Streaming 
	// (CR4.OSXMMEXCPT =0). 
	// SIMD Extension numeric exception 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// Interrupt 13 If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #XM For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =1). 
	// #UD For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =0). 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF(fault-code) For a page fault. 
	// Comments 
	// Note that if only one source is a NaN for these instructions, the Src2 operand (either NaN or real 
	// value) is written to the result; this differs from the behavior for other instructions as defined in 
	// Table 7-9 in Chapter 7, Floating-Point Unit of the Intel Architecture Software Developer�s 
	// Manual, Volume 1, which is to always write the NaN to the result, regardless of which source 
	// operand contains the NaN. This approach for MAXPS allows compilers to use the MAXPS 
	// instruction for common C conditional constructs. If instead of this behavior, it is required that 
	// the NaN source operand be 
	// sequence of instructions: comparison followed by AND, ANDN, and OR. 

	//BreakPoint()
}

Func_Prefix  MAXSS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF (DEST[31-0]=NaN) THEN 
	// DEST[31-0] = SRC[31-0]; 
	// ELSE 
	// IF (SRC[31-0] = NaN) THEN 
	// DEST[31-0] = SRC[31-0]; 
	// ELSE 
	// IF (DEST[31-0] > SRC/m128[31-0]) THEN 
	// DEST[31-0] = DEST[31-0]; 
	// ELSE 
	// DEST[31-0] = SRC/m128[31-0]; 
	// FI 
	// FI 
	// FI 
	// DEST[63-32]= DEST[63-32]; 
	// DEST[95-64]= DEST[95-64]; 
	// DEST[127-96]= DEST[127-96]; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_max_ss(__m128 a, __m128 b) 
	// Computes the maximum of the lower SP FP values of a and b; the upper three SP FP values are 
	// passed through from a. 
	// Exceptions 
	// None. 
	// Numeric Exceptions 
	// Invalid (including qNaN source operand), Denormal. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #AC For unaligned memory reference. To enable #AC exceptions, thtions must be TRUE(CR0.AM is set; EFLAGS.AC is set; current 
	// ree condi-
	// CPL is 3). 
	// #XM For an unmasked Streaming 
	// (CR4.OSXMMEXCPT =1). 
	// SIMD Extension numeric exception 
	// #UD For an unmasked Streaming 
	// (CR4.OSXMMEXCPT =0). 
	// SIMD Extension numeric exception 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #XM 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =1). 
	// #UD 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =0). 
	// #UD 
	// If CR4.OSFXSR(bit 9) = 0. 
	// #UD 
	// If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #AC For unaligned memory reference if the current privilege level is 3. 
	// #PF (fault-code) For a page fault. 
	// Comments 
	// Note that if only one source is a NaN for these instructions, the Src2 operand (either NaN or real 
	// value) is written to the result; this differs from the behavior for other instructions as defined in 
	// Table 7-9 in Chapter 7, Floating-Point Unit of the Intel Architecture Software Developer�s 
	// Manual, Volume 1, which is to always write the NaN to the result, regardless of which source 
	// operand contains the NaN. The upper three operands are still bypassed from the src1 operand, 
	// as in all other scalar operations. This approach for MAXSS allows compilers to use the MAXSS 
	// instruction for common C conditional constructs. If instead of this behavior, it is required that 
	// the NaN source operand be 
	// sequence of instructions: comparison followed by AND, ANDN, and OR. 

	//BreakPoint()
}

Func_Prefix  MINPS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// bayad baraye in dastor F3 Prefix ro barresi kard chenancheh TRUE bood dastor MINSS ejra mishavad
	// Baraye in manzor index mmx pass shode be tabe index register haye EXX mishavad hamchenin size hafeze dar operand dovom
	// az 64 be 32 tabdil mishavad

	// IF (DEST[31-0]=NaN) THEN 
	// DEST[31-0] = SRC[31-0]; 
	// ELSE 
	// IF (SRC[31-0] = NaN) THEN 
	// DEST[31-0] = SRC[31-0]; 
	// ELSE 
	// IF (DEST[31-0] < SRC/m128[31-0]) THEN 
	// DEST[31-0] = DEST[31-0]; 
	// ELSE 
	// DEST[31-0] = SRC/m128[31-0]; 
	// FI 
	// FI 
	// FI 
	// IF (DEST[63-32]=NaN) THEN 
	// DEST[63-32] = SRC[63-32]; 
	// ELSE 
	// IF (SRC[63-32] = NaN) THEN 
	// DEST[63-32] = SRC[63-32]; 
	// ELSE 
	// IF (DEST[63-32] < SRC/m128[63-32]) THEN 
	// DEST[63-32] = DEST[63-32]; 
	// ELSE 
	// DEST[63-32] = SRC/m128[63-32]; 
	// FI 
	// FI 
	// FI 
	// IF (DEST[95-64]=NaN) THEN 
	// DEST[95-64] = SRC[95-64]; 
	// ELSE 
	// IF (SRC[95-64] = NaN) THEN 
	// DEST[95-64] = SRC[95-64]; 
	// ELSE 
	// IF (DEST[95-64] < SRC/m128[95-64]) THEN 
	// DEST[95-64] = DEST[95-64]; 
	// ELSE 
	// DEST[95-64] = SRC/m128[95-64]; 
	// FI 
	// FI 
	// FI 
	// IF (DEST[127-96]=NaN) THEN 
	// DEST[127-96] = SRC[127-96]; 
	// ELSE 
	// IF (SRC[127-96] = NaN) THEN 
	// DEST[127-96] = SRC[127-96]; 
	// ELSE 
	// IF (DEST[127-96] < SRC/m128[127-96]) THEN 
	// DEST[127-96] = DEST[127-96]; 
	// ELSE 
	// DEST[127-96] = SRC/m128[127-96]; 
	// FI 
	// FI 
	// FI 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_min_ps(__m128 a, __m128 b) 
	// Computes the minimums of the four SP FP values of a and b. 
	// Exceptions 
	// General protection exception if not aligned on 16-byte boundary, regardless of segment. 
	// Numeric Exceptions 
	// Invalid (including qNaN source operand), Denormal. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF(fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #XM For an unmasked Streaming 
	// (CR4.OSXMMEXCPT =1). 
	// SIMD Extension numeric exception 
	// #UD For an unmasked Streaming 
	// (CR4.OSXMMEXCPT =0). 
	// SIMD Extension numeric exception 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #XM 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =1). 
	// #UD 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =0). 
	// #UD 
	// If CR4.OSFXSR(bit 9) = 0. 
	// #UD 
	// If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF(fault-code) For a page fault. 
	// Comments 
	// Note that if only one source is a NaN for these instructions, the Src2 operand (either NaN or real 
	// value) is written to the result; this differs from the behavior for other instructions as defined in 
	// Table 7-9 in Chapter 7, Floating-Point Unit of the Intel Architecture Software Developer�s 
	// Manual, Volume 1, which is to always write the NaN to the result, regardless of which source 
	// operand contains the NaN. This approach for MINPS allows compilers to use the MINPS 
	// instruction for common C conditional constructs. If instead of this behavior, it is required that 
	// the NaN source operand be 
	// sequence of instructions: comparison followed by AND, ANDN, and OR. 

	//BreakPoint()
}

Func_Prefix  MINSS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF (DEST[31-0]=NaN) THEN 
	// DEST[31-0] = SRC[31-0]; 
	// ELSE 
	// IF (SRC[31-0] = NaN) THEN 
	// DEST[31-0] = SRC[31-0]; 
	// ELSE 
	// IF (DEST[31-0] < SRC/m128[31-0]) THEN 
	// DEST[31-0] = DEST[31-0]; 
	// ELSE 
	// DEST[31-0] = SRC/m128[31-0]; 
	// FI 
	// FI 
	// FI 
	// DEST[63-32]= DEST[63-32]; 
	// DEST[95-64]= DEST[95-64]; 
	// DEST[127-96]= DEST[127-96]; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_min_ss(__m128 a, __m128 b) 
	// Computes the minimum of the lower SP FP values of a and b; the upper three SP FP values are 
	// passed through from a. 
	// Exceptions 
	// None. 
	// Numeric Exceptions 
	// Invalid (including qNaN source operand), Denormal. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #AC For unaligned memory reference. To enable #AC exceptions, thtions must be TRUE(CR0.AM is set; EFLAGS.AC is set; current 
	// ree condi-
	// CPL is 3). 
	// #XM For an unmasked Streaming 
	// (CR4.OSXMMEXCPT =1). 
	// SIMD Extension numeric exception 
	// #UD For an unmasked Streaming 
	// (CR4.OSXMMEXCPT =0). 
	// SIMD Extension numeric exception 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #XM 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =1). 
	// #UD 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =0). 
	// #UD 
	// If CR4.OSFXSR(bit 9) = 0. 
	// #UD 
	// If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF (fault-code) For a page fault. 
	// #AC For unaligned memory references. 
	// Comments 
	// Note that if only one source is a NaN for these instructions, the Src2 operand (either NaN or real 
	// value) is written to the result; this differs from the behavior for other instructions as defined in 
	// Table 7-9 in Chapter 7, Floating-Point Unit of the Intel Architecture Software Developer�s 
	// Manual, Volume 1, which is to always write the NaN to the result, regardless of which source 
	// operand contains the NaN. The upper three operands are still bypassed from the src1 operand, 
	// as in all other scalar operations. This approach for MINSS allows compilers to use the MINSS 
	// instruction for common C conditional constructs. If instead of this behavior, it is required that 
	// the NaN source operand be 
	// sequence of instructions: comparison followed by AND, ANDN, and OR. 
	//BreakPoint()
}


// No Flags Affected

Func_Prefix  MOV8 (VirtualMachine *posVm)
{
	PAGED_CODE();
	*(UINT8 *)posVm->Context.osOpcodeBlock.nOperand0 = *((UINT8 *)posVm->Context.osOpcodeBlock.nOperand1);
}


Func_Prefix  MOV16 (VirtualMachine *posVm)
{
	PAGED_CODE();
	*(((UINT16 *)posVm->Context.osOpcodeBlock.nOperand0)) = ((UINT16 *)posVm->Context.osOpcodeBlock.nOperand1)[0];
	//BreakPoint()
}


Func_Prefix  MOV (VirtualMachine *posVm)
{
	PAGED_CODE();
	if (posVm->Context.osOpcodeBlock.nOperand0 == 0 || posVm->Context.osOpcodeBlock.nOperand1 == 0)
	{
		return;
	}
	*(((UINT32 *)posVm->Context.osOpcodeBlock.nOperand0)) = ((UINT32 *)posVm->Context.osOpcodeBlock.nOperand1)[0];
	// DEST � SRC; 
	// Loading a segment register while in protected mode results in special checks and actions, as 
	// described in the following listing. These checks are performed on the segment selector and the 
	// segment descriptor it points to. 
	// IF SS is loaded; 
	// THEN 
	// IF segment selector is null 
	// THEN #GP(0); 
	// FI; 
	// IF segment selector index is outside descriptor table limits 
	// OR segment selector�s RPL � CPL 
	// OR segment is not a writable data segment 
	// OR DPL � CPL 
	// THEN #GP(selector); 
	// FI; 
	// IF segment not marked present 
	// THEN #SS(selector); 
	// ELSE 
	// SS � segment selector; 
	// SS � segment descriptor; 
	// FI; 
	// FI; 
	// IF DS, ES, FS or GS is loaded with non-null selector; 
	// THEN 
	// IF segment selector index is outside descriptor table limits 
	// OR segment is not a data or readable code segment 
	// OR ((segment is a data or nonconforming code segment) 
	// AND (both RPL and CPL > DPL)) 
	// THEN #GP(selector); 
	// IF segment not marked present 
	// THEN #NP(selector); 
	// ELSE 
	// SegmentRegister � segment selector; 
	// SegmentRegister � segment descriptor; 
	// FI; 
	// FI; 
	// IF DS, ES, FS or GS is loaded with a null selector; 
	// THEN 
	// SegmentRegister � segment selector; 
	// SegmentRegister � segment descriptor; 
	// FI; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If attempt is made to load SS register with null segment selector. 
	// If the destination operand is in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #GP(selector) If segment selector index is outside descriptor table limits. 
	// If the SS register is being loaded and the segment selector�s RPL and the 
	// segment descriptor�s DPL are not equal to the CPL. 
	// If the SS register is being loaded and the segment pointed to is a nonwritable 
	// data segment. 
	// If the DS, ES, FS, or GS register is being loaded and the segment pointed 
	// to is not a data or readable code segment. 
	// If the DS, ES, FS, or GS register is being loaded and the segment pointed 
	// to is a data or nonconforming code segment, but both the RPL and the CPL 
	// are greater than the DPL. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #SS(selector) If the SS register is being loaded and the segment pointed to is marked not 
	// present. 
	// #NP If the DS, ES, FS, or GS register is being loaded and the segment pointed 
	// to is marked not present. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// #UD If attempt is made to load the CS register. 
	// Real-Address Mode Exceptions 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS If a memory operand effective address is outside the SS segment limit. 
	// #UD If attempt is made to load the CS register. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 
	// #UD If attempt is made to load the CS register. 
}

Func_Prefix  MOVAPS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF (destination = DEST) THEN 
	// IF (SRC = m128)THEN (* load instruction *) 
	// DEST[127-0] = m128; 
	// ELSE(* move instruction *) 
	// DEST[127=0] = SRC[127-0]; 
	// FI; 
	// ELSE 
	// IF (destination = m128)THEN (* store instruction *) 
	// m128 = SRC[127-0]; 
	// ELSE(* move instruction *) 
	// DEST[127-0] = SRC[127-0]; 
	// FI; 
	// FI; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_load_ps(float * p) 
	// Loads four SP FP values. The address must be 16-byte-aligned. 
	// void_mm_store_ps(float *p, __m128 a) 
	// Stores four SP FP values. The address must be 16-byte-aligned. 
	// Exceptions 
	// General protection exception if not aligned on 16-byte boundary, regardless of segment. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF(fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// Interrupt 13 If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF(fault-code) For a page fault. 
	// Comments 
	// MOVAPS should be used when dealing with 16-byte aligned SP FP numbers. If the data is not 
	// known to be aligned, MOVUPS should be used instead of MOVAPS. The usage of this instruction 
	// should be limited to the cases where the aligned restriction is easy to meet. Processors that 
	// support Streaming SIMD Extension will provide optimal aligned performance for the MOVAPS 
	// instruction. 
	// The usage of Repeat Prefix (F3H) with MOVAPS is reserved. Different processor implementations 
	// may handle this prefix differently. Usage of this prefix with MOVAPS risks incompatibility 
	// with future processors. 


	//BreakPoint()
}

Func_Prefix  MOVD16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  MOVD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF DEST is MMX� technology register 
	// THEN 
	// DEST � ZeroExtend(SRC); 
	// ELSE (* SRC is MMX� technology register *) 
	// DEST � LowOrderDoubleword(SRC); 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination operand is in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual-8086 Mode Exceptions 
	// #GP If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  MOVHLPS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST[127-64] = DEST[127-64]; 
	// DEST[63-0] = SRC[127-64]; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_movehl_ps(__m128 a, __m128 b) 
	// Moves the upper 2 SP FP values of b to the lower 2 SP FP values of the result. The upper 2 SP 
	// FP values of a are passed through to the result. 
	// Exceptions 
	// None 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// Comments 
	// The usage of Repeat (F2H, F3H) and Operand Size (66H) prefixes with MOVHLPS is reserved. 
	// Different processor implementations may handle these prefixes differently. Usage of these 
	// prefixes with MOVHLPS risks incompatibility with future processors. 

	//BreakPoint()
}

Func_Prefix  MOVHPS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF (destination = DEST) THEN(* load instruction *) 
	// DEST[127-64] = m64; 
	// DEST[31-0] = DEST[31-0]; 
	// DEST[63-32] = DEST[63-32]; 
	// ELSE (* store instruction *) 
	// m64 = SRC[127-64]; 
	// FI; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_loadh_pi(__m128 a, __m64 * p) 
	// Sets the upper two SP FP values with 64 bits of data loaded from the address p; the lower two 
	// values are passed through from a. 
	// void_mm_storeh_pi(__m64 * p, __m128 a) 
	// Stores the upper two SP FP values of a to the address p. 
	// Exceptions 
	// None. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #AC For unaligned memory reference. To enable #AC exceptions, three conditions 
	// must be TRUE(CR0.AM is set; EFLAGS.AC is set; current CPL is 3). 
	// #UD If CR4.OSFXSR(bit 9) = 0 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// Interrupt 13 If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF (fault-code) For a page fault. 
	// #AC For unaligned memory reference if the current privilege level is 3. 
	// Comments 
	// The usage of Repeat Prefixes (F2H, F3H) with MOVHPS is reserved. Different processor 
	// implementations may handle these prefixes differently. Usage of these prefixes with MOVHPS 
	// risks incompatibility with future processors. 

	//BreakPoint()
}

Func_Prefix  MOVLHPS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST[127-64] = SRC[63-0]; 
	// DEST[63-0] = DEST[63-0]; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_movelh_ps (__m128 a, __m128 b) 
	// Moves the lower 2 SP FP values of b to the upper 2 SP FP values of the result. The lower 2 SP 
	// FP values of a are passed through to the result. 
	// Exceptions 
	// None. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// Comments 
	// The usage of Repeat (F2H, F3H) and Operand Size (66H) prefixes with MOVLHPS is reserved. 
	// Different processor implementations may handle these prefixes differently. Usage of these 
	// prefixes with MOVLHPS risks incompatibility with future processors. 

	//BreakPoint()
}

Func_Prefix  MOVLPS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF (destination = DEST) THEN(* load instruction *) 
	// DEST[63-0] = m64; 
	// DEST[95-64] = DEST[95-64]; 
	// DEST[127-96] = DEST[127-96]; 
	// ELSE(* store instruction *) 
	// m64 = DEST[63-0]; 
	// FI 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_loadl_pi(__m128 a, __m64 *p) 
	// Sets the lower two SP FP values with 64 bits of data loaded from the address p; the upper two 
	// values are passed through from a. 
	// void_mm_storel_pi(__m64 * p, __m128 a) 
	// Stores the lower two SP FP values of a to the address p. 
	// Exceptions 
	// None. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0 For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #AC For unaligned memory reference. To enable #AC exceptions, three conditions 
	// must be TRUE(CR0.AM is set; EFLAGS.AC is set; current CPL is 3). 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// Interrupt 13 If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF (fault-code) For a page fault. 
	// #AC For unaligned memory reference if the current privilege level is 3. 
	// Comments 
	// The usage of Repeat Prefix (F3H) with MOVLPS is reserved. Different processor implementations 
	// may handle this prefix differently. Usage of this prefix with MOVLPS risks incompatibility 
	// with future processors. 

	//BreakPoint()
}

Func_Prefix  MOVMSKPS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// r32[0] = SRC[31]; 
	// r32[1] = SRC[63]; 
	// r32[2] = SRC[95]; 
	// r32[3] = SRC[127]; 
	// r32[7-4] = 0X0; 
	// r32[15-8] = 0X00; 
	// r32[31-16] = 0X0000; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// int_mm_movemask_ps(__m128 a) 
	// Creates a 4-bit mask from the most significant bits of the four SP FP values. 
	// Exceptions 
	// None. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// Comments 
	// The usage of Repeat Prefix (F3H) with MOVMSKPS is reserved. Different process implementations 
	// may handle this prefix differently. Usage of this prefix with MOVMSKPS risks incompatibility 
	// with future processors. 

	//BreakPoint()
}

Func_Prefix  MOVNTPS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// m128 = SRC; 
	// C/C++ Compiler Intrinsic Equivalent 
	// void_mm_stream_ps(float * p, __m128 a) 
	// Stores the data in a to the address p without polluting the caches. The address must be 16-bytealigned. 
	// Exceptions 
	// General protection exception if not aligned on 16-byte boundary, regardless of segment. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF(fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// MOVNTPS�Move Aligned Four Packed Single-FP Non Temporal 
	// Real Address Mode Exceptions 
	// Interrupt 13 If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF(fault-code) For a page fault. 
	// Comments 
	// MOVTNPS should be used when dealing with 16-byte aligned single-precision FP numbers. 
	// MOVNTPS minimizes pollution in the cache hierarchy. As a consequence of the resulting 
	// weakly-ordered memory consistency model, a fencing operation should be used if multiple 
	// processors may use different memory types to read/write the memory location. Refer to Section 
	// 9.3.9., Cacheability Control Instructions in Chapter 9, Programming with the Streaming SIMD 
	// Extensions of the Intel Architecture Software Developer�s Manual, Volume 1, for further information 
	// about non-temporal stores. 
	// The usage of Repeat Prefix (F3H) with MOVNTPS is reserved. Different processor implementations 
	// may handle this prefix differently. Usage of this prefix with MOVNTPS risks incompatibility 
	// with future processors. 

	//BreakPoint()
}

Func_Prefix  MOVNTQ (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// m64 = SRC; 
	// C/C++ Compiler Intrinsic Equivalent 
	// void_mm_stream_pi(__m64 * p, __m64 a) 
	// Stores the data in a to the address p without polluting the caches. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #AC For unaligned memory reference. To enable #AC exceptions, three conditions 
	// must be TRUE (CR0.AM is set; EFLAGS.AC is set; current CPL is 3) 
	// Real Address Mode Exceptions 
	// Interrupt 13 If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #AC For unaligned memory reference if the current privilege level is 3. 
	// #PF (fault-code) For a page fault. 
	// Comments 
	// MOVNTQ minimizes pollution in the cache hierarchy. As a consequence of the resulting 
	// weakly-ordered memory consistency model, a fencing operation should be used if multiple 
	// processors may use different memory types to read/write the memory location. Refer to Section 
	// 9.3.9., Cacheability Control Instructions in Chapter 9, Programming with the Streaming SIMD 
	// Extensions of the Intel Architecture Software Developer�s Manual, Volume 1, for further information 
	// about non-temporal stores. 
	// MOVNTQ ignores the value of CR4.OSFXSR. Since it does not affect the new Streaming SIMD 
	// Extension state, MOVNTQ will not generate an invalid exception if CR4.OSFXSR = 0. 

	//BreakPoint()
}

Func_Prefix  MOVQ (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST � SRC; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination operand is in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual-8086 Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 
	//BreakPoint()
}

// // Func_Prefix  MOVS (VirtualMachine *posVm)
// {
//UINT32	nEFlag;
//PAGED_CODE();
// //BreakPoint()
// }

Func_Prefix	Mov_String (VirtualMachine *posVm, UINT32	nSizeOfBuffer)
{
	PAGED_CODE();
	if (ReadMemory(posVm, posVm->Context.osReg.ESI, nSizeOfBuffer, FALSE))
	{
		if (!WriteMemory(posVm, posVm->Context.osReg.EDI, nSizeOfBuffer))
		{
			posVm->Context.osReg.EIP = 0xFFFFFFFF;
		}
	}
	else
	{
		posVm->Context.osReg.EIP = 0xFFFFFFFF;
	}
}

Func_Prefix	PreMov_String (VirtualMachine *posVm, UINT8	nChunckSize)
{
	UINT32	nEFlag;
	UINT32	nSizeOfBuffer;
	PAGED_CODE();
	
	if (posVm->Context.nFlag & pRep)
	{
		nSizeOfBuffer = (posVm->Context.osReg.ECX < 512? posVm->Context.osReg.ECX : 512);
		while (posVm->Context.osReg.ECX != 0)
		{
			posVm->Context.osReg.ECX -= nSizeOfBuffer;
			Mov_String (posVm, nSizeOfBuffer);

			if (posVm->Context.osReg.nDF == 0)
			{
				posVm->Context.osReg.ESI -= nSizeOfBuffer;
				posVm->Context.osReg.EDI -= nSizeOfBuffer;
			}
			else
			{
				posVm->Context.osReg.ESI += nSizeOfBuffer;
				posVm->Context.osReg.EDI += nSizeOfBuffer;
			}

			nSizeOfBuffer = (posVm->Context.osReg.ECX < 512? posVm->Context.osReg.ECX : 512);
		} 
	}
	else
	{
		nSizeOfBuffer = nChunckSize;
		Mov_String (posVm, nSizeOfBuffer);

		if (posVm->Context.osReg.nDF == 0)
		{
			posVm->Context.osReg.ESI -= nChunckSize;
			posVm->Context.osReg.EDI -= nChunckSize;
		}
		else
		{
			posVm->Context.osReg.ESI += nChunckSize;
			posVm->Context.osReg.EDI += nChunckSize;
		}
	}
}

Func_Prefix  MOVSB (VirtualMachine *posVm)
{
	VirtualMachine	*posVM;
	PAGED_CODE();

	PreMov_String (posVm, 1);
}

Func_Prefix  MOVSD16 (VirtualMachine *posVm)
{
	PAGED_CODE();
	posVm->Context.osReg.ECX *= 2;
	PreMov_String (posVm, 2);
}

Func_Prefix  MOVSD (VirtualMachine *posVm)
{
	PAGED_CODE();
	posVm->Context.osReg.ECX *= 4;
	PreMov_String (posVm, 4);

	// DEST �SRC; 
	// IF (byte move) 
	// THEN IF DF = 0 
	// THEN 
	// (E)SI � (E)SI + 1; 
	// (E)DI � (E)DI + 1; 
	// ELSE 
	// (E)SI � (E)SI � 1; 
	// (E)DI � (E)DI � 1; 
	// FI; 
	// ELSE IF (word move) 
	// THEN IF DF = 0 
	// (E)SI � (E)SI + 2; 
	// (E)DI � (E)DI + 2; 
	// ELSE 
	// (E)SI � (E)SI � 2; 
	// (E)DI � (E)DI � 2; 
	// FI; 
	// ELSE (* doubleword move*) 
	// THEN IF DF = 0 
	// (E)SI � (E)SI + 4; 
	// (E)DI � (E)DI + 4; 
	// ELSE 
	// (E)SI � (E)SI � 4; 
	// (E)DI � (E)DI � 4; 
	// FI; 
	// FI; 
	// Flags Affected 
	// None. 
	// MOVS/MOVSB/MOVSW/MOVSD�Move Data from String to String 
	// Protected Mode Exceptions 
	// #GP(0) If the destination is located in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 
}

Func_Prefix  MOVSS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF (destination = DEST) THEN 
	// IF (SRC == m32) THEN(* load instruction *) 
	// DEST[31-0] = m32; 
	// DEST [63-32] = 0X00000000; 
	// DEST [95-64] = 0X00000000; 
	// DEST [127-96] = 0X00000000; 
	// ELSE(* move instruction *) 
	// DEST [31-0] = SRC[31-0]; 
	// DEST [63-32] = DEST [63-32]; 
	// DEST [95-64] = DEST [95-64]; 
	// DEST [127-96] = DEST [127-96]; 
	// FI 
	// ELSE 
	// IF (destination = m32) THEN(* store instruction *) 
	// m32 = SRC[31-0]; 
	// ELSE (* move instruction *) 
	// DEST [31-0] = SRC[31-0] 
	// DEST [63-32] = DEST[63-32]; 
	// DEST [95-64] = DEST [95-64]; 
	// DEST [127-96] = DEST [127-96]; 
	// FI 
	// FI 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_load_ss(float * p) 
	// Loads an SP FP value into the low word and clears the upper three words. 
	// void_mm_store_ss(float * p, __m128 a) 
	// Stores the lower SP FP value. 
	// __m128 _mm_move_ss(__m128 a, __m128 b) 
	// Sets the low word to the SP FP value of b. The upper 3 SP FP values are passed through from a. 
	// Exceptions 
	// None. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #AC For unaligned memory reference.To enable #AC exceptions, three conditions 
	// must be TRUE(CR0.AM is set; EFLAGS.AC is set; current CPL is 3). 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #UD 
	// If CR4.OSFXSR(bit 9) = 0. 
	// #UD 
	// If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #AC For unaligned memory reference if the current privilege level is 3. 
	// #PF (fault-code) For a page fault. 

	//BreakPoint()
}

Func_Prefix  MOVSX8 (VirtualMachine *posVm)
{
	UINT32 nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	UINT32 nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
	PAGED_CODE();

	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx	,  nOperand2
	__asm   mov ecx, [ecx]
	__asm   mov eax, [eax]
	__asm   movsx eax, cl
	__asm	mov	ecx ,  nOperand1
	__asm   mov [ecx], eax
}

Func_Prefix  MOVSX16 (VirtualMachine *posVm)
{
	PAGED_CODE();
	//BreakPoint()
}

Func_Prefix  MOVSX (VirtualMachine *posVm)
{
	UINT32 nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	UINT32 nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
	PAGED_CODE();
	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx	,  nOperand2
	__asm   mov ecx, [ecx]
	__asm   mov eax, [eax]
	__asm   movsx eax, ecx
	__asm	mov	ecx ,  nOperand1
	__asm   mov [ecx], eax
	// DEST � SignExtend(SRC); 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 

	/*//BreakPoint()*/
}

Func_Prefix  MOVUPS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// bayad baraye in dastor F3 Prefix ro barresi kard chenancheh TRUE bood dastor MOVSS ejra mishavad
	// Baraye in manzor index mmx pass shode be tabe index register haye EXX mishavad hamchenin size hafeze dar operand dovom
	// az 64 be 32 tabdil mishavad


	// IF (destination = xmm) THEN 
	// IF (SRC = m128)THEN(* load instruction *) 
	// DEST[127-0] = m128; 
	// ELSE (* move instruction *) 
	// DEST[127-0] = SRC[127-0]; 
	// FI 
	// ELSE 
	// IF (destination = m128) THEN(* store instruction *) 
	// m128 = SRC[127-0]; 
	// ELSE (* move instruction *) 
	// DEST[127-0] = SRC[127-0]; 
	// FI 
	// FI 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_loadu_ps(float * p) 
	// Loads four SP FP values. The address need not be 16-byte-aligned. 
	// void_mm_storeu_ps(float *p, __m128 a) 
	// Stores four SP FP values. The address need not be 16-byte-aligned. 
	// Exceptions 
	// None. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code For a page fault. 
	// #UD If CR0.EM = 1. 
	// #AC For unaligned memory reference if the current privilege level is 3. 
	// #NM If TS bit in CR0 is set. 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #AC 
	// For unaligned memory reference if the current privilege level is 3. 
	// #PF (fault-code) 
	// For a page fault. 
	// Comments 
	// MOVUPS should be used with SP FP numbers when that data is known to be unaligned.The 
	// usage of this instruction should be limited to the cases where the aligned restriction is hard or 
	// impossible to meet. Streaming SIMD Extension implementations guarantee optimum unaligned 
	// support for MOVUPS. Efficient Streaming SIMD Extension applications should mainly rely on 
	// MOVAPS, not MOVUPS, when dealing with aligned data. 
	// The usage of Repeat-NE (F2H) and Operand Size (66H) prefixes is reserved. Different 
	// processor implementations may handle these prefixes differently. Usage of these prefixes with 
	// MOVUPS risks incompatibility with future processors. 
	// A linear address of the 128 bit data access, while executing in 16-bit mode, that overlaps the end 
	// of a 16-bit segment is not allowed and is defined as reserved behavior. Different processor 
	// implementations may/may not raise a GP fault in this case if the segment limit has been 
	// exceeded. Additionally, the address that spans the end of the segment may/may not wrap around 
	// to the beginning of the segment. 

	//BreakPoint()
}

Func_Prefix  MOVZX8 (VirtualMachine *posVm)
{
	UINT32 nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	UINT32 nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
	PAGED_CODE();

	if (posVm->Context.osOpcodeBlock.b66)
	{
		__asm	mov	eax	,  nOperand1
		__asm	mov	ecx ,  nOperand2
		__asm   mov eax, [eax]
		__asm   movzx ax, byte ptr [ecx]
		__asm	mov	ecx ,  nOperand1
		__asm   mov word ptr [ecx], ax
	}
	else
	{
		__asm	mov	eax	,  nOperand1
		__asm	mov	ecx ,  nOperand2
		__asm   mov eax, [eax]
		__asm   movzx eax, byte ptr [ecx]
		__asm	mov	ecx ,  nOperand1
		__asm   mov [ecx], eax
	}
}

Func_Prefix  MOVZX16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  MOVZX (VirtualMachine *posVm)
{
	UINT32 nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	UINT32 nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
	PAGED_CODE();

	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx	,  nOperand2
	__asm   mov ecx, [ecx]
	__asm   mov eax, [eax]
	__asm   movzx eax, cx
	__asm	mov	ecx ,  nOperand1
	__asm   mov [ecx], eax

	// DEST � ZeroExtend(SRC); 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	/*//BreakPoint()*/
}



Func_Prefix MUL8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}

Func_Prefix  MUL16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}

Func_Prefix  MUL (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF byte operation 
	// THEN 
	// AX � AL * SRC 
	// ELSE (* word or doubleword operation *) 
	// IF OperandSize = 16 
	// THEN 
	// DX:AX � AX * SRC 
	// ELSE (* OperandSize = 32 *) 
	// EDX:EAX � EAX * SRC 
	// FI; 
	// FI; 
	// Flags Affected 
	// The OF and CF flags are cleared to 0 if the upper half of the result is 0; otherwise, they are set 
	// to 1. The SF, ZF, AF, and PF flags are undefined. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  MULPS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// bayad baraye in dastor F3 Prefix ro barresi kard chenancheh TRUE bood dastor MULSS ejra mishavad
	// Baraye in manzor index mmx pass shode be tabe index register haye EXX mishavad hamchenin size hafeze dar operand dovom
	// az 64 be 32 tabdil mishavad

	// DEST[31-0] = DEST[31-0] * SRC/m128[31-0]; 
	// DEST[63-32] = DEST[63-32] * SRC/m128[63-32]; 
	// DEST[95-64] = DEST[95-64] * SRC/m128[95-64]; 
	// DEST[127-96] = DEST[127-96] * SRC/m128[127-96]; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_mul_ps(__m128 a, __m128 b) 
	// Multiplies the four SP FP values of a and b. 
	// Exceptions 
	// General protection exception if not aligned on 16-byte boundary, regardless of segment. 
	// Numeric Exceptions 
	// Overflow, Underflow, Invalid, Precision, Denormal. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF(fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #XM For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =1). 
	// #UD For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =0). 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #XM 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =1). 
	// #UD 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =0). 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF(fault-code) For a page fault. 

	//BreakPoint()
}

Func_Prefix  MULSS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST[31-0] = DEST[31-0] * SRC/m32[31-0]; 
	// DEST[63-32] = DEST[63-32]; 
	// DEST[95-64] = DEST[95-64]; 
	// DEST[127-96] = DEST[127-96]; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_mul_ss(__m128 a, __m128 b) 
	// Multiplies the lower SP FP values of a and b; the upper three SP FP values are passed through 
	// from a. 
	// Exceptions 
	// None. 
	// Numeric Exceptions 
	// Overflow, Underflow, Invalid, Precision, Denormal. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective aGS segments. 
	// ddress in the CS, DS, ES, FS, or 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #AC For unaligned memory reference. To enabtions must be TRUE(CR0.AM is set; EFLAle #AC excGS.AC is septions, three condiet; 
	// current CPL is 3). 
	// #XM For an unmasked Streaming SIMD(CR4.OSXMMEXCPT =1). 
	// Extension numeric exception 
	// #UD For an unmasked Streaming SIMD(CR4.OSXMMEXCPT =0). 
	// Extension numeric exception 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #XM 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =1). 
	// #UD 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =0). 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #AC For unaligned memory reference if the current privilege level is 3. 
	// #PF (fault-code) For a page fault. 

	//BreakPoint()
}

Func_Prefix  NEG8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}

Func_Prefix  NEG16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}

Func_Prefix  NEG (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF DEST = 0 
	// THEN CF � 0 
	// ELSE CF � 1; 
	// FI; 
	// DEST � � (DEST) 
	// Flags Affected 
	// The CF flag cleared to 0 if the source operand is 0; otherwise it is set to 1. The OF, SF, ZF, AF, 
	// and PF flags are set according to the result. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination is located in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  NOP (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
}

Func_Prefix  NOT8 (VirtualMachine *posVm)
{
	UINT32 nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;	
	PAGED_CODE();
	__asm	mov	eax	,  nOperand1	
	__asm	not byte ptr [eax]
}

Func_Prefix  NOT16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}

Func_Prefix  NOT (VirtualMachine *posVm)
{
	UINT32 nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;	
	PAGED_CODE();
	
	__asm	mov	eax	,  nOperand1	
	__asm	not dword ptr [eax]
	// DEST � NOT DEST; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination operand points to a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 
}

Func_Prefix  OR8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	UINT32 nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	UINT32 nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
	PAGED_CODE();
	
	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm	mov	ecx, dword ptr[ecx]
	__asm	or byte ptr [eax], cl
	FlagSaver(nEFlag);
	posVm->Context.osReg.nEFlag = nEFlag;	
}

Func_Prefix  OR16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  OR (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	UINT32 nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	UINT32 nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
	PAGED_CODE();

	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm	mov	ecx, dword ptr[ecx]
	__asm	or dword ptr [eax], ecx
	FlagSaver(nEFlag);
	posVm->Context.osReg.nEFlag = nEFlag;
	// DEST � DEST OR SRC; 
	// Flags Affected 
	// The OF and CF flags are cleared; the SF, ZF, and PF flags are set according to the result. The 
	// state of the AF flag is undefined. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination operand points to a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 
}

Func_Prefix  ORPS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST[127-0] |= SRC/m128[127-0]; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_or_ps(__m128 a, __m128 b) 
	// Computes the bitwise OR of the four SP FP values of a and b. 
	// Exceptions 
	// General protection exception if not aligned on 16-byte boundary, regardless of segment. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF(fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// Real Address Mode Exceptions 
	// Interrupt 13 If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF(fault-code) For a page fault. 
	// Comments 
	// The usage of Repeat Prefix (F3H) with ORPS is reserved. Different processor implementations 
	// may handle this prefix differently. Usage of this prefix with ORPS risks incompatibility with 
	// future processors. 

	//BreakPoint()
}

Func_Prefix  OUT_8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  OUT_16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  OUT_ (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF ((PE = 1) AND ((CPL > IOPL) OR (VM = 1))) 
	// THEN (* Protected mode with CPL > IOPL or virtual-8086 mode *) 
	// IF (Any I/O Permission Bit for I/O port being accessed = 1) 
	// THEN (* I/O operation is not allowed *) 
	// #GP(0); 
	// ELSE ( * I/O operation is allowed *) 
	// DEST � SRC; (* Writes to selected I/O port *) 
	// FI; 
	// ELSE (Real Mode or Protected Mode with CPL � IOPL *) 
	// DEST � SRC; (* Writes to selected I/O port *) 
	// FI; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) 
	// If the CPL is greater than (has less privilege) the I/O privilege level (IOPL) 
	// and any of the corresponding I/O permission bits in TSS for the I/O port 
	// being accessed is 1. 
	// Real-Address Mode Exceptions 
	// None. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) 
	// If any of the I/O permission bits in the TSS for the I/O port being accessed 
	// is 1. 

	//BreakPoint()
}

Func_Prefix  OUTS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  OUTSB (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  OUTSW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  OUTSD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF ((PE = 1) AND ((CPL > IOPL) OR (VM = 1))) 
	// THEN (* Protected mode with CPL > IOPL or virtual-8086 mode *) 
	// IF (Any I/O Permission Bit for I/O port being accessed = 1) 
	// THEN (* I/O operation is not allowed *) 
	// #GP(0); 
	// ELSE ( * I/O operation is allowed *) 
	// DEST � SRC; (* Writes to I/O port *) 
	// FI; 
	// ELSE (Real Mode or Protected Mode with CPL � IOPL *) 
	// DEST � SRC; (* Writes to I/O port *) 
	// FI; 
	// IF (byte transfer) 
	// THEN IF DF = 0 
	// THEN (E)SI � (E)SI + 1; 
	// ELSE (E)SI � (E)SI � 1; 
	// FI; 
	// ELSE IF (word transfer) 
	// THEN IF DF = 0 
	// THEN (E)SI � (E)SI + 2; 
	// ELSE (E)SI � (E)SI � 2; 
	// FI; 
	// ELSE (* doubleword transfer *) 
	// THEN IF DF = 0 
	// THEN (E)SI � (E)SI + 4; 
	// ELSE (E)SI � (E)SI � 4; 
	// FI; 
	// FI; 
	// FI; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If the CPL is greater than (has less privilege) the I/O privilege level (IOPL) 
	// and any of the corresponding I/O permission bits in TSS for the I/O port 
	// being accessed is 1. 
	// If a memory operand effective address is outside the limit of the CS, DS, 
	// ES, FS, or GS segment. 
	// If the segment register contains a null segment selector. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) 
	// If any of the I/O permission bits in the TSS for the I/O port being accessed 
	// is 1. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  PACKSSWB (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  PACKSSDW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF instruction is PACKSSWB 
	// THEN 
	// DEST(7..0) � SaturateSigneUINT32ToSignedByte DEST(15..0); 
	// DEST(15..8) � SaturateSigneUINT32ToSignedByte DEST(31..16); 
	// DEST(23..16) � SaturateSigneUINT32ToSignedByte DEST(47..32); 
	// DEST(31..24) � SaturateSigneUINT32ToSignedByte DEST(63..48); 
	// DEST(39..32) � SaturateSigneUINT32ToSignedByte SRC(15..0); 
	// DEST(47..40) � SaturateSigneUINT32ToSignedByte SRC(31..16); 
	// DEST(55..48) � SaturateSigneUINT32ToSignedByte SRC(47..32); 
	// DEST(63..56) � SaturateSigneUINT32ToSignedByte SRC(63..48); 
	// ELSE (* instruction is PACKSSDW *) 
	// DEST(15..0) � SaturateSignedDoublewordToSigneUINT32 DEST(31..0); 
	// DEST(31..16) � SaturateSignedDoublewordToSigneUINT32 DEST(63..32); 
	// DEST(47..32) � SaturateSignedDoublewordToSigneUINT32 SRC(31..0); 
	// DEST(63..48) � SaturateSignedDoublewordToSigneUINT32 SRC(63..32); 
	// FI; 
	// Intel C/C++ Compiler Intrinsic Equivalents 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_packsswb (__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_packs_pi16(__m64 m1, __m64 m2) 
	// Pack the four 16-bit values from m1 into the lower four 8-bit values of the result with signed 
	// saturation, and pack the four 16-bit values from m2 into the upper four 8-bit values of the result 
	// with signed saturation. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_packssdw (__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_packs_pi32 (__m64 m1, __m64 m2) 
	// Pack the two 32-bit values from m1 into the lower two 16-bit values of the result with signed 
	// saturation, and pack the two 32-bit values from m2 into the upper two 16-bit values of the result 
	// with signed saturation. 
	// Flags Affected 
	// None. 
	// PACKSSWB/PACKSSDW�Pack with Signed Saturation 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual-8086 Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  PACKUSWB (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST(7..0) � SaturateSigneUINT32ToUnsignedByte DEST(15..0); 
	// DEST(15..8) � SaturateSigneUINT32ToUnsignedByte DEST(31..16); 
	// DEST(23..16) � SaturateSigneUINT32ToUnsignedByte DEST(47..32); 
	// DEST(31..24) � SaturateSigneUINT32ToUnsignedByte DEST(63..48); 
	// DEST(39..32) � SaturateSigneUINT32ToUnsignedByte SRC(15..0); 
	// DEST(47..40) � SaturateSigneUINT32ToUnsignedByte SRC(31..16); 
	// DEST(55..48) � SaturateSigneUINT32ToUnsignedByte SRC(47..32); 
	// DEST(63..56) � SaturateSigneUINT32ToUnsignedByte SRC(63..48); 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_packuswb(__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_packs_pu16(__m64 m1, __m64 m2) 
	// Pack the four 16-bit values from m1 into the lower four 8-bit values of the result with unsigned 
	// saturation, and pack the four 16-bit values from m2 into the upper four 8-bit values of the result 
	// with unsigned saturation. 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual-8086 Mode Exceptions 
	// #GP If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  PADDB (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  PADDW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  PADDD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF instruction is PADDB 
	// THEN 
	// DEST(7..0) � DEST(7..0) + SRC(7..0); 
	// DEST(15..8) � DEST(15..8) + SRC(15..8); 
	// DEST(23..16) � DEST(23..16)+ SRC(23..16); 
	// DEST(31..24) � DEST(31..24) + SRC(31..24); 
	// DEST(39..32) � DEST(39..32) + SRC(39..32); 
	// DEST(47..40) � DEST(47..40)+ SRC(47..40); 
	// DEST(55..48) � DEST(55..48) + SRC(55..48); 
	// DEST(63..56) � DEST(63..56) + SRC(63..56); 
	// ELSEIF instruction is PADDW 
	// THEN 
	// DEST(15..0) � DEST(15..0) + SRC(15..0); 
	// DEST(31..16) � DEST(31..16) + SRC(31..16); 
	// DEST(47..32) � DEST(47..32) + SRC(47..32); 
	// DEST(63..48) � DEST(63..48) + SRC(63..48); 
	// ELSE (* instruction is PADDD *) 
	// DEST(31..0) � DEST(31..0) + SRC(31..0); 
	// DEST(63..32) � DEST(63..32) + SRC(63..32); 
	// FI; 
	// Intel C/C++ Compiler Intrinsic Equivalents 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_paddb(__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_add_pi8(__m64 m1, __m64 m2) 
	// Add the eight 8-bit values in m1 to the eight 8-bit values in m2. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_paddw(__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_addw_pi16(__m64 m1, __m64 m2) 
	// Add the four 16-bit values in m1 to the four 16-bit values in m2. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_paddd(__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_add_pi32(__m64 m1, __m64 m2) 
	// Add the two 32-bit values in m1 to the two 32-bit values in m2. 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// Virtual-8086 Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  PADDSB (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  PADDSW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF instruction is PADDSB 
	// THEN 
	// DEST(7..0) � SaturateToSignedByte(DEST(7..0) + SRC (7..0)) ; 
	// DEST(15..8) � SaturateToSignedByte(DEST(15..8) + SRC(15..8) ); 
	// DEST(23..16) � SaturateToSignedByte(DEST(23..16)+ SRC(23..16) ); 
	// DEST(31..24) � SaturateToSignedByte(DEST(31..24) + SRC(31..24) ); 
	// DEST(39..32) � SaturateToSignedByte(DEST(39..32) + SRC(39..32) ); 
	// DEST(47..40) � SaturateToSignedByte(DEST(47..40)+ SRC(47..40) ); 
	// DEST(55..48) � SaturateToSignedByte(DEST(55..48) + SRC(55..48) ); 
	// DEST(63..56) � SaturateToSignedByte(DEST(63..56) + SRC(63..56) ); 
	// ELSE {(* instruction is PADDSW *) 
	// DEST(15..0) � SaturateToSigneUINT32(DEST(15..0) + SRC(15..0) ); 
	// DEST(31..16) � SaturateToSigneUINT32(DEST(31..16) + SRC(31..16) ); 
	// DEST(47..32) � SaturateToSigneUINT32(DEST(47..32) + SRC(47..32) ); 
	// DEST(63..48) � SaturateToSigneUINT32(DEST(63..48) + SRC(63..48) ); 
	// FI; 
	// Intel C/C++ Compiler Intrinsic Equivalents 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_paddsb(__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_adds_pi8(__m64 m1, __m64 m2) 
	// Add the eight signed 8-bit values in m1 to the eight signed 8-bit values in m2 and saturate. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_paddsw(__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_adds_pi16(__m64 m1, __m64 m2) 
	// Add the four signed 16-bit values in m1 to the four signed 16-bit values in m2 and saturate. 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual-8086 Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  PADDUSB (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  PADDUSW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF instruction is PADDUSB 
	// THEN 
	// DEST(7..0) � SaturateToUnsignedByte(DEST(7..0) + SRC (7..0) ); 
	// DEST(15..8) � SaturateToUnsignedByte(DEST(15..8) + SRC(15..8) ); 
	// DEST(23..16) � SaturateToUnsignedByte(DEST(23..16)+ SRC(23..16) ); 
	// DEST(31..24) � SaturateToUnsignedByte(DEST(31..24) + SRC(31..24) ); 
	// DEST(39..32) � SaturateToUnsignedByte(DEST(39..32) + SRC(39..32) ); 
	// DEST(47..40) � SaturateToUnsignedByte(DEST(47..40)+ SRC(47..40) ); 
	// DEST(55..48) � SaturateToUnsignedByte(DEST(55..48) + SRC(55..48) ); 
	// DEST(63..56) � SaturateToUnsignedByte(DEST(63..56) + SRC(63..56) ); 
	// ELSE {(* instruction is PADDUSW *) 
	// DEST(15..0) � SaturateToUnsigneUINT32(DEST(15..0) + SRC(15..0) ); 
	// DEST(31..16) � SaturateToUnsigneUINT32(DEST(31..16) + SRC(31..16) ); 
	// DEST(47..32) � SaturateToUnsigneUINT32(DEST(47..32) + SRC(47..32) ); 
	// DEST(63..48) � SaturateToUnsigneUINT32(DEST(63..48) + SRC(63..48) ); 
	// FI; 
	// Intel C/C++ Compiler Intrinsic Equivalents 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_paddusb(__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_adds_pu8(__m64 m1, __m64 m2) 
	// Add the eight unsigned 8-bit values in m1 to the eight unsigned 8-bit values in m2 and saturate. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_paddusw(__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_adds_pu16(__m64 m1, __m64 m2) 
	// Add the four unsigned 16-bit values in m1 to the four unsigned 16-bit values in m2 and saturate. 
	// Flags Affected 
	// None. 
	// PADDUSB/PADDUSW�Packed Add Unsigned with Saturation 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual-8086 Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  PAND (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST � DEST AND SRC; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_pand(__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_and_si64(__m64 m1, __m64 m2) 
	// Perform a bitwise AND of the 64-bit value in m1 with the 64-bit value in m2. 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual-8086 Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  PANDN (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST � (NOT DEST) AND SRC; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_pandn(__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_andnot_si64(__m64 m1, __m64 m2) 
	// Perform a logical NOT on the 64-bit value in m1 and use the result in a bitwise AND with the 
	// 64-bit value in m2. 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual-8086 Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  PAVGB (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  PAVGW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF (* instruction = PAVGB *) THEN 
	// X[0] = DEST[7-0]; 
	// Y[0] = SRC/m64[7-0]; 
	// X[1] = DEST[15-8]; 
	// Y[1] = SRC/m64[15-8]; 
	// X[2] = DEST[23-16]; 
	// Y[2] = SRC/m64[23-16]; 
	// X[3] = DEST[31-24]; 
	// Y[3] = SRC/m64[31-24]; 
	// X[4] = DEST[39-32]; 
	// Y[4] = SRC/m64[39-32]; 
	// X[5] = DEST[47-40]; 
	// Y[5] = SRC/m64[47-40]; 
	// X[6] = DEST[55-48]; 
	// Y[6] = SRC/m64[55-48]; 
	// X[7] = DEST[63-56]; 
	// Y[7] = SRC/m64[63-56]; 
	// WHILE (I < 8) 
	// TEMP[I] = ZERO_EXT(X[I], 8) + ZERO_EXT{
	// RES[I] = (TEMP[I] + 1) >> 1; 
	// ENDWHILE 
	// DEST[7-0] = RES[0]; 
	// DEST[15-8] = RES[1]; 
	// DEST[23-16] = RES[2]; 
	// DEST[31-24] = RES[3]; 
	// DEST[39-32] = RES[4]; 
	// DEST[47-40] = RES[5]; 
	// DEST[55-48] = RES[6]; 
	// DEST[63-56] = RES[7]; 
	// ELSE IF (* instruction PAVGW *)THEN 
	// X[0] = DEST[15-0]; 
	// Y[0] = SRC/m64[15-0]; 
	// X[1] = DEST[31-16]; 
	// Y[1] = SRC/m64[31-16]; 
	// X[2] = DEST[47-32]; 
	// Y[2] = SRC/m64[47-32]; 
	// X[3] = DEST[63-48]; 
	// Y[3] = SRC/m64[63-48]; 
	// WHILE (I < 4) 
	// TEMP[I] = ZERO_EXT(X[I], 16) + ZERO_EXT{
	// RES[I] = (TEMP[I] + 1) >> 1; 
	// ENDWHILE 
	// DEST[15-0] = RES[0]; 
	// DEST[31-16] = RES[1]; 
	// DEST[47-32] = RES[2]; 
	// DEST[63-48] = RES[3]; 
	// FI; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64_mm_pavgb(__m64 a, __m64 b) 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64_mm_avg_pu8(__m64 a, __m64 b) 
	// Performs the packed average on the eight 8-bit values of the two operands. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64_mm_pavgw(__m64 a, __m64 b) 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64_mm_avg_pu16(__m64 a, __m64 b) 
	// Performs the packed average on the four 16-bit values of the two operands. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF(fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #AC For unaligned memory reference. To enable #AC exceptions, three conditions 
	// must be TRUE(CR0.AM is set; EFLAGS.AC is set; current CPL is 3). 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF(fault-code) For a page fault. 
	// #AC For unaligned memory references (if the current privilege level is 3). 

	//BreakPoint()
}

Func_Prefix  PCMPEQB (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  PCMPEQW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  PCMPEQD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF instruction is PCMPEQB 
	// THEN 
	// IF DEST(7..0) = SRC(7..0) 
	// THEN DEST(7 0) � FFH; 
	// ELSE DEST(7..0) � 0; 
	// * Continue comparison of second through seventh bytes in DEST and SRC * 
	// IF DEST(63..56) = SRC(63..56) 
	// THEN DEST(63..56) � FFH; 
	// ELSE DEST(63..56) � 0; 
	// ELSE IF instruction is PCMPEQW 
	// THEN 
	// IF DEST(15..0) = SRC(15..0) 
	// THEN DEST(15..0) � FFFFH; 
	// ELSE DEST(15..0) � 0; 
	// * Continue comparison of second and third words in DEST and SRC * 
	// IF DEST(63..48) = SRC(63..48) 
	// THEN DEST(63..48) � FFFFH; 
	// ELSE DEST(63..48) � 0; 
	// ELSE (* instruction is PCMPEQD *) 
	// IF DEST(31..0) = SRC(31..0) 
	// THEN DEST(31..0) � FFFFFFFFH; 
	// ELSE DEST(31..0) � 0; 
	// IF DEST(63..32) = SRC(63..32) 
	// THEN DEST(63..32) � FFFFFFFFH; 
	// ELSE DEST(63..32) � 0; 
	// FI; 
	// PCMPEQB/PCMPEQW/PCMPEQD�Packed Compare for Equal 
	// Intel C/C++ Compiler Intrinsic Equivalents 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_pcmpeqb (__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_cmpeq_pi8 (__m64 m1, __m64 m2) 
	// If the respective 8-bit values in m1 are equal to the respective 8-bit values in m2 set the respective 
	// 8-bit resulting values to all ones, otherwise set them to all zeroes. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_pcmpeqw (__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_cmpeq_pi16 (__m64 m1, __m64 m2) 
	// If the respective 16-bit values in m1 are equal to the respective 16-bit values in m2 set the 
	// respective 16-bit resulting values to all ones, otherwise set them to all zeroes. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_pcmpeqd (__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_cmpeq_pi32 (__m64 m1, __m64 m2) 
	// If the respective 32-bit values in m1 are equal to the respective 32-bit values in m2 set the 
	// respective 32-bit resulting values to all ones, otherwise set them to all zeroes. 
	// Flags Affected 
	// None: 
	// PCMPEQB/PCMPEQW/PCMPEQD�Packed Compare for Equal 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual-8086 Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  PCMPGTB (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  PCMPGTW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  PCMPGTD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF instruction is PCMPGTB 
	// THEN 
	// IF DEST(7..0) > SRC(7..0) 
	// THEN DEST(7 0) � FFH; 
	// ELSE DEST(7..0) � 0; 
	// * Continue comparison of second through seventh bytes in DEST and SRC * 
	// IF DEST(63..56) > SRC(63..56) 
	// THEN DEST(63..56) � FFH; 
	// ELSE DEST(63..56) � 0; 
	// ELSE IF instruction is PCMPGTW 
	// THEN 
	// IF DEST(15..0) > SRC(15..0) 
	// THEN DEST(15..0) � FFFFH; 
	// ELSE DEST(15..0) �0; 
	// * Continue comparison of second and third bytes in DEST and SRC * 
	// IF DEST(63..48) > SRC(63..48) 
	// THEN DEST(63..48) � FFFFH; 
	// ELSE DEST(63..48) � 0; 
	// ELSE {(* instruction is PCMPGTD *) 
	// IF DEST(31..0) > SRC(31..0) 
	// THEN DEST(31..0) � FFFFFFFFH; 
	// ELSE DEST(31..0) � 0; 
	// IF DEST(63..32) > SRC(63..32) 
	// THEN DEST(63..32) � FFFFFFFFH; 
	// ELSE DEST(63..32) � 0; 
	// FI; 
	// PCMPGTB/PCMPGTW/PCMPGTD�Packed Compare for Greater 
	// Intel C/C++ Compiler Intrinsic Equivalents 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_pcmpgtb (__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_cmpgt_pi8 (__m64 m1, __m64 m2) 
	// If the respective 8-bit values in m1 are greater than the respective 8-bit values in m2 set the 
	// respective 8-bit resulting values to all ones, otherwise set them to all zeroes. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_pcmpgtw (__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_pcmpgt_pi16 (__m64 m1, __m64 m2) 
	// If the respective 16-bit values in m1 are greater than the respective 16-bit values in m2 set the 
	// respective 16-bit resulting values to all ones, otherwise set them to all zeroes. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_pcmpgtd (__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_pcmpgt_pi32 (__m64 m1, __m64 m2) 
	// If the respective 32-bit values in m1 are greater than the respective 32-bit values in m2 set the 
	// respective 32-bit resulting values to all ones, otherwise set them all to zeroes. 
	// Flags Affected 
	// None. 
	// PCMPGTB/PCMPGTW/PCMPGTD�Packed Compare for Greater 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual-8086 Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  PEXTRW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// SEL = imm8 AND 0X3; 
	// MM_TEMP = (SRC >> (SEL * 16)) AND 0XFFFF; 
	// r32[15-0] = MM_TEMP[15-0]; 
	// r32[31-16] = 0X0000; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// int_m_pextrw(__m64 a, int n) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// int_mm_extract_pi16(__m64 a, int n) 
	// Extracts one of the four words of a. The selector n must be an immediate. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF(fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #MF If there is a pending FPU exception 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF(fault-code) For a page fault. 

	//BreakPoint()
}

Func_Prefix  PINSRW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// SEL = imm8 AND 0X3; 
	// IF(SEL = 0) THEN 
	// MASK=0X000000000000FFFF; 
	// ELSE 
	// IF(SEL = 1) THEN 
	// MASK=0X00000000FFFF0000 : 
	// ELSE 
	// IF(SEL = 2) THEN 
	// MASK=0XFFFF000000000000; 
	// FI 
	// FI 
	// FI 
	// DEST = (DEST AND NOT MASK) OR ((m16/r32[15-0] << (SEL * 16)) AND MASK); 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_pinsrw(__m64 a, int d, int n) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_insert_pi16(__m64 a, int d, int n) 
	// Inserts word d into one of four words of a. The selector n must be an immediate. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #AC For unaligned memory reference. To enable #AC exceptions, three conditions 
	// must be TRUE(CR0.AM is set; EFLAGS.AC is set; current CPL is 3) 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #AC For unaligned memory reference if the current privilege level is 3. 
	// #PF (fault-code) For a page fault. 

	//BreakPoint()
}

Func_Prefix  PMADDWD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST(31..0) � (DEST(15..0) * SRC(15..0)) + (DEST(31..16) * SRC(31..16)); 
	// DEST(63..32) � (DEST(47..32) * SRC(47..32)) + (DEST(63..48) * SRC(63..48)); 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_pmaddwd(__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_madd_pi16(__m64 m1, __m64 m2) 
	// Multiply four 16-bit values in m1 by four 16-bit values in m2 producing four 32-bit intermediate 
	// results, which are then summed by pairs to produce two 32-bit results. 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual-8086 Mode Exceptions 
	// #GP If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  PMAXSW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF DEST[15-0] > SRC/m64[15-0]) THEN 
	// (DEST[15-0] = DEST[15-0]; 
	// ELSE 
	// (DEST[15-0] = SRC/m64[15-0]; 
	// FI 
	// IF DEST[31-16] > SRC/m64[31-16]) THEN 
	// (DEST[31-16] = DEST[31-16]; 
	// ELSE 
	// (DEST[31-16] = SRC/m64[31-16]; 
	// FI 
	// IF DEST[47-32] > SRC/m64[47-32]) THEN 
	// (DEST[47-32] = DEST[47-32]; 
	// ELSE 
	// (DEST[47-32] SRC/m64[47-32]; 
	// FI 
	// IF DEST[63-48] > SRC/m64[63-48]) THEN 
	// (DEST[63-48] = DEST[63-48]; 
	// ELSE 
	// (DEST[63-48] = SRC/m64[63-48]; 
	// FI 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_pmaxsw(__m64 a, __m64 b) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_max_pi16(__m64 a, __m64 b) 
	// Computes the element-wise maximum of the words in a and b. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #AC For unaligned memory reference. To enable #AC exceptions, three conditions 
	// must be TRUE(CR0.AM is set; EFLAGS.AC is set; current CPL is 3) 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF(fault-code) For a page fault. 
	// #AC For unaligned memory reference if the current privilege level is 3. 

	//BreakPoint()
}

Func_Prefix  PMAXUB (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF DEST[7-0] > SRC/m64[7-0]) THEN 
	// (DEST[7-0] = DEST[7-0]; 
	// ELSE 
	// (DEST[7-0] = SRC/m64[7-0]; 
	// FI 
	// IF DEST[15-8] > SRC/m64[15-8]) THEN 
	// (DEST[15-8] = DEST[15-8]; 
	// ELSE 
	// (DEST[15-8] = SRC/m64[15-8]; 
	// FI 
	// IF DEST[23-16] > SRC/m64[23-16]) THEN 
	// (DEST[23-16] = DEST[23-16]; 
	// ELSE 
	// (DEST[23-16] = SRC/m64[23-16]; 
	// FI 
	// IF DEST[31-24] > SRC/m64[31-24]) THEN 
	// (DEST[31-24] = DEST[31-24]; 
	// ELSE 
	// (DEST[31-24] = SRC/m64[31-24]; 
	// FI 
	// IF DEST[39-32] > SRC/m64[39-32]) THEN 
	// (DEST[39-32] = DEST[39-32]; 
	// ELSE 
	// (DEST[39-32] = SRC/m64[39-32]; 
	// FI 
	// IF DEST[47-40] > SRC/m64[47-40]) THEN 
	// (DEST[47-40] = DEST[47-40]; 
	// ELSE 
	// (DEST[47-40] = SRC/m64[47-40]; 
	// FI 
	// IF DEST[55-48] > SRC/m64[55-48]) THEN 
	// (DEST[55-48] = DEST[55-48]; 
	// ELSE 
	// (DEST[55-48] = SRC/m64[55-48]; 
	// FI 
	// IF DEST[63-56] > SRC/m64[63-56]) THEN 
	// (DEST[63-56] = DEST[63-56]; 
	// ELSE 
	// (DEST[63-56] = SRC/m64[63-56]; 
	// FI 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_pmaxub(__m64 a, __m64 b) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_max_pu8(__m64 a, __m64 b) 
	// Computes the element-wise maximum of the unsigned bytes in a and b. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #AC For unaligned memory reference. To enable #AC exceptions, three conditions 
	// must be TRUE(CR0.AM is set; EFLAGS.AC is set; current CPL is 3) 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF(fault-code) For a page fault. 
	// #AC For unaligned memory reference if the current privilege level is 3. 

	//BreakPoint()
}

Func_Prefix  PMINSW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF DEST[15-0] < SRC/m64[15-0]) THEN 
	// (DEST[15-0] = DEST[15-0]; 
	// ELSE 
	// (DEST[15-0] = SRC/m64[15-0]; 
	// FI 
	// IF DEST[31-16] < SRC/m64[31-16]) THEN 
	// (DEST[31-16] = DEST[31-16]; 
	// ELSE 
	// (DEST[31-16] = SRC/m64[31-16]; 
	// FI 
	// IF DEST[47-32] < SRC/m64[47-32]) THEN 
	// (DEST[47-32] = DEST[47-32]; 
	// ELSE 
	// (DEST[47-32] SRC/m64[47-32]; 
	// FI 
	// IF DEST[63-48] < SRC/m64[63-48]) THEN 
	// (DEST[63-48] = DEST[63-48]; 
	// ELSE 
	// (DEST[63-48] = SRC/m64[63-48]; 
	// FI 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_pminsw(__m64 a, __m64 b) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_min_pi16(__m64 a, __m64 b) 
	// Computes the element-wise minimum of the words in a and b. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #AC For unaligned memory reference. To enable #AC exceptions, three conditions 
	// must be TRUE(CR0.AM is set; EFLAGS.AC is set; current CPL is 3) 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF(fault-code) For a page fault. 
	// #AC For unaligned memory reference if the current privilege level is 3. 

	//BreakPoint()
}

Func_Prefix  PMINUB (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF DEST[7-0] < SRC/m64[7-0]) THEN 
	// (DEST[7-0] = DEST[7-0]; 
	// ELSE 
	// (DEST[7-0] = SRC/m64[7-0]; 
	// FI 
	// IF DEST[15-8] < SRC/m64[15-8]) THEN 
	// (DEST[15-8] = DEST[15-8]; 
	// ELSE 
	// (DEST[15-8] = SRC/m64[15-8]; 
	// FI 
	// IF DEST[23-16] < SRC/m64[23-16]) THEN 
	// (DEST[23-16] = DEST[23-16]; 
	// ELSE 
	// (DEST[23-16] = SRC/m64[23-16]; 
	// FI 
	// IF DEST[31-24] < SRC/m64[31-24]) THEN 
	// (DEST[31-24] = DEST[31-24]; 
	// ELSE 
	// (DEST[31-24] = SRC/m64[31-24]; 
	// FI 
	// IF DEST[39-32] < SRC/m64[39-32]) THEN 
	// (DEST[39-32] = DEST[39-32]; 
	// ELSE 
	// (DEST[39-32] = SRC/m64[39-32]; 
	// FI 
	// IF DEST[47-40] < SRC/m64[47-40]) THEN 
	// (DEST[47-40] = DEST[47-40]; 
	// ELSE 
	// (DEST[47-40] = SRC/m64[47-40]; 
	// FI 
	// IF DEST[55-48] < SRC/m64[55-48]) THEN 
	// (DEST[55-48] = DEST[55-48]; 
	// ELSE 
	// (DEST[55-48] = SRC/m64[55-48]; 
	// FI 
	// IF DEST[63-56] < SRC/m64[63-56]) THEN 
	// (DEST[63-56] = DEST[63-56]; 
	// ELSE 
	// (DEST[63-56] = SRC/m64[63-56]; 
	// FI 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_pminub(__m64 a, __m64 b) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _m_min_pu8(__m64 a, __m64 b) 
	// Computes the element-wise minimum of the unsigned bytes in a and b. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #AC For unaligned memory reference. To enable #AC exceptions, three conditions 
	// must be TRUE(CR0.AM is set; EFLAGS.AC is set; current CPL is 3). 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF(fault-code) For a page fault. 
	// #AC For unaligned memory reference if the current privilege level is 3. 

	//BreakPoint()
}

Func_Prefix  PMOVMSKB16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  PMOVMSKB (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// r32[7] = SRC[63]; r32[6] = SRC[55]; 
	// r32[5] = SRC[47]; r32[4] = SRC[39]; 
	// r32[3] = SRC[31]; r32[2] = SRC[23]; 
	// r32[1] = SRC[15]; r32[0] = SRC[7]; 
	// r32[31-8] = 0X000000; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// int_m_pmovmskb(__m64 a) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// int_mm_movemask_pi8(__m64 a) 
	// Creates an 8-bit mask from the most significant bits of the bytes in a. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #AC For unaligned memory reference. To enable #AC exceptions, three conditions 
	// must be TRUE(CR0.AM is set; EFLAGS.AC is set; current CPL is 3). 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF (fault-code) For a page fault. 
	// #AC For unaligned memory reference if the current privilege level is 3. 

	//BreakPoint()
}

Func_Prefix  PMULHUW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST[15-0] = (DEST[15-0] * SRC/m64[15-0])[31-16]; 
	// DEST[31-16] = (DEST[31-16] * SRC/m64[31-16])[31-16]; 
	// DEST[47-32] = (DEST[47-32] * SRC/m64[47-32])[31-16]; 
	// DEST[63-48] = (DEST[63-48] * SRC/m64[63-48])[31-16]; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_pmulhuw(__m64 a, __m64 b) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_mulhi_pu16(__m64 a, __m64 b) 
	// Multiplies the unsigned words in a and b, 
	// results. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #AC For unaligned memory reference. To enable #AC exceptions, three conditions 
	// must be TRUE(CR0.AM is set; EFLAGS.AC is set; current CPL is 3). 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF(fault-code) For a page fault. 
	// #AC For unaligned memory reference if the current privilege level is 3. 

	//BreakPoint()
}

Func_Prefix  PMULHW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST(15..0) � HighOrderWord(DEST(15..0) * SRC(15..0)); 
	// DEST(31..16) � HighOrderWord(DEST(31..16) * SRC(31..16)); 
	// DEST(47..32) � HighOrderWord(DEST(47..32) * SRC(47..32)); 
	// DEST(63..48) � HighOrderWord(DEST(63..48) * SRC(63..48)); 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_pmulhw(__m64 m1, __m64 m2) 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _mM_mulhi_pi16(__m64 m1, __m64 m2) 
	// Multiply four signed 16-bit values in m1 by four signed 16-bit values in m2 and produce the 
	// high 16 bits of the four results. 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual-8086 Mode Exceptions 
	// #GP If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  PMULLW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST(15..0) � LowOrderWord(DEST(15..0) * SRC(15..0)); 
	// DEST(31..16) � LowOrderWord(DEST(31..16) * SRC(31..16)); 
	// DEST(47..32) � LowOrderWord(DEST(47..32) * SRC(47..32)); 
	// DEST(63..48) � LowOrderWord(DEST(63..48) * SRC(63..48)); 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_pmullw(__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_mullo_pi16(__m64 m1, __m64 m2) 
	// Multiply four 16-bit values in m1 by four 16-bit values in m2 and produce the low 16 bits of the 
	// four results. 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual-8086 Mode Exceptions 
	// #GP If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  POP8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  POP16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  POP (VirtualMachine *posVm)
{
	PAGED_CODE();
	if (posVm->Context.osOpcodeBlock.nOperand0 == 0)
	{
		return;
	}
	*(UINT32*)posVm->Context.osOpcodeBlock.nOperand0 = PopStack(posVm);
	// IF StackAddrSize = 32 
	// THEN 
	// IF OperandSize = 32 
	// THEN 
	// DEST � SS:ESP; (* copy a doubleword *) 
	// ESP � ESP + 4; 
	// ELSE (* OperandSize = 16*) 
	// DEST � SS:ESP; (* copy a word *) 
	// ESP � ESP + 2; 
	// FI; 
	// ELSE (* StackAddrSize = 16* ) 
	// IF OperandSize = 16 
	// THEN 
	// DEST � SS:SP; (* copy a word *) 
	// SP � SP + 2; 
	// ELSE (* OperandSize = 32 *) 
	// DEST � SS:SP; (* copy a doubleword *) 
	// SP � SP + 4; 
	// FI; 
	// FI; 
	// Loading a segment register while in protected mode results in special checks and actions, as 
	// described in the following listing. These checks are performed on the segment selector and the 
	// segment descriptor it points to. 
	// IF SS is loaded; 
	// THEN 
	// IF segment selector is null 
	// THEN #GP(0); 
	// 1. Note that in a sequence of instructions that individually delay interrupts past the following instruction, only 
	// the first instruction in the sequence is guaranteed to delay the interrupt, but subsequent interrupt-delaying 
	// instructions may not delay the interrupt. Thus, in the following instruction sequence: 
	// STI 
	// POP SS 
	// POP ESP 
	// interrupts may be recognized before the POP ESP executes, because STI also delays interrupts for one 
	// instruction. 
	// FI; 
	// IF segment selector index is outside descriptor table limits 
	// OR segment selector�s RPL � CPL 
	// OR segment is not a writable data segment 
	// OR DPL � CPL 
	// THEN #GP(selector); 
	// FI; 
	// IF segment not marked present 
	// THEN #SS(selector); 
	// ELSE 
	// SS � segment selector; 
	// SS � segment descriptor; 
	// FI; 
	// FI; 
	// IF DS, ES, FS or GS is loaded with non-null selector; 
	// THEN 
	// IF segment selector index is outside descriptor table limits 
	// OR segment is not a data or readable code segment 
	// OR ((segment is a data or nonconforming code segment) 
	// AND (both RPL and CPL > DPL)) 
	// THEN #GP(selector); 
	// IF segment not marked present 
	// THEN #NP(selector); 
	// ELSE 
	// SegmentRegister � segment selector; 
	// SegmentRegister � segment descriptor; 
	// FI; 
	// FI; 
	// IF DS, ES, FS or GS is loaded with a null selector; 
	// THEN 
	// SegmentRegister � segment selector; 
	// SegmentRegister � segment descriptor; 
	// FI; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If attempt is made to load SS register with null segment selector. 
	// If the destination operand is in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #GP(selector) If segment selector index is outside descriptor table limits. 
	// If the SS register is being loaded and the segment selector�s RPL and the 
	// segment descriptor�s DPL are not equal to the CPL. 
	// If the SS register is being loaded and the segment pointed to is a nonwritable 
	// data segment. 
	// If the DS, ES, FS, or GS register is being loaded and the segment pointed 
	// to is not a data or readable code segment. 
	// If the DS, ES, FS, or GS register is being loaded and the segment pointed 
	// to is a data or nonconforming code segment, but both the RPL and the CPL 
	// are greater than the DPL. 
	// #SS(0) If the current top of stack is not within the stack segment. 
	// If a memory operand effective address is outside the SS segment limit. 
	// #SS(selector) If the SS register is being loaded and the segment pointed to is marked not 
	// present. 
	// #NP If the DS, ES, FS, or GS register is being loaded and the segment pointed 
	// to is marked not present. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If an unaligned memory reference is made while the current privilege level 
	// is 3 and alignment checking is enabled. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If an unaligned memory reference is made while alignment checking is 
	// enabled. 
}

Func_Prefix  POPAD16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  POPAD (VirtualMachine *posVm)
{
	PAGED_CODE();

	posVm->Context.osReg.EDI = PopStack(posVm);
	posVm->Context.osReg.ESI = PopStack(posVm);
	posVm->Context.osReg.EBP = PopStack(posVm);
	PopStack(posVm);
	posVm->Context.osReg.EBX = PopStack(posVm);
	posVm->Context.osReg.EDX = PopStack(posVm);
	posVm->Context.osReg.ECX = PopStack(posVm);
	posVm->Context.osReg.EAX = PopStack(posVm);

	// IF OperandSize = 32 (* instruction = POPAD *) 
	// THEN 
	// EDI � Pop(); 
	// ESI � Pop(); 
	// EBP � Pop(); 
	// increment ESP by 4 (* skip next 4 bytes of stack *) 
	// EBX � Pop(); 
	// EDX � Pop(); 
	// ECX � Pop(); 
	// EAX � Pop(); 
	// ELSE (* OperandSize = 16, instruction = POPA *) 
	// DI � Pop(); 
	// SI � Pop(); 
	// BP � Pop(); 
	// increment ESP by 2 (* skip next 2 bytes of stack *) 
	// BX � Pop(); 
	// DX � Pop(); 
	// CX � Pop(); 
	// AX � Pop(); 
	// FI; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #SS(0) If the starting or ending stack address is not within the stack segment. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If an unaligned memory reference is made while the current privilege level 
	// is 3 and alignment checking is enabled. 
	// Real-Address Mode Exceptions 
	// #SS If the starting or ending stack address is not within the stack segment. 
	// Virtual-8086 Mode Exceptions 
	// #SS(0) If the starting or ending stack address is not within the stack segment. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If an unaligned memory reference is made while alignment checking is 
	// enabled. 
}

Func_Prefix  POPF (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  POPFD16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  POPFD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF VM=0 (* Not in Virtual-8086 Mode *) 
	// THEN IF CPL=0 
	// THEN 
	// IF OperandSize = 32; 
	// THEN 
	// EFLAGS � Pop(); 
	// (* All non-reserved flags except VIP, VIF, and VM can be modified; *) 
	// (* VIP and VIF are cleared; VM is unaffected*) 
	// ELSE (* OperandSize = 16 *) 
	// EFLAGS[15:0] � Pop(); (* All non-reserved flags can be modified; *) 
	// FI; 
	// ELSE (* CPL > 0 *) 
	// IF OperandSize = 32; 
	// THEN 
	// EFLAGS � Pop() 
	// (* All non-reserved bits except IOPL, VIP, and VIF can be modified; *) 
	// (* IOPL is unaffected; VIP and VIF are cleared; VM is unaffected *) 
	// ELSE (* OperandSize = 16 *) 
	// EFLAGS[15:0] � Pop(); 
	// (* All non-reserved bits except IOPL can be modified *) 
	// (* IOPL is unaffected *) 
	// FI; 
	// FI; 
	// ELSE (* In Virtual-8086 Mode *) 
	// IF IOPL=3 
	// THEN IF OperandSize=32 
	// THEN 
	// EFLAGS � Pop() 
	// (* All non-reserved bits except VM, RF, IOPL, VIP, and VIF *) 
	// (* can be modified; VM, RF, IOPL, VIP, and VIF are unaffected *) 
	// ELSE 
	// EFLAGS[15:0] � Pop() 
	// (* All non-reserved bits except IOPL can be modified *) 
	// (* IOPL is unaffected *) 
	// FI; 
	// ELSE (* IOPL < 3 *) 
	// #GP(0); (* trap to virtual-8086 monitor *) 
	// FI; 
	// FI; 
	// FI; 
	// Flags Affected 
	// All flags except the reserved bits and the VM bit. 
	// Protected Mode Exceptions 
	// #SS(0) If the top of stack is not within the stack segment. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If an unaligned memory reference is made while the current privilege level 
	// is 3 and alignment checking is enabled. 
	// Real-Address Mode Exceptions 
	// #SS 
	// If the top of stack is not within the stack segment. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) 
	// If the I/O privilege level is less than 3. 
	// If an attempt is made to execute the POPF/POPFD instruction with an 
	// operand-size override prefix. 
	// #SS(0) 
	// If the top of stack is not within the stack segment. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If an unaligned memory reference is made while alignment checking is 
	// enabled. 

	//BreakPoint()
}

Func_Prefix  POR (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST � DEST OR SRC; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_por(__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_or_si64(__m64 m1, __m64 m2) 
	// Perform a bitwise OR of the 64-bit value in m1 with the 64-bit value in m2. 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual-8086 Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  PREFETCHT08 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  PREFETCHT18 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  PREFETCHT28 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  PREFETCHNTA8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// FETCH (m8); 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// void_mm_prefetch(char *p, int i) 
	// Loads one cache line of data from address p to a location "closer" to the processor. The value i 
	// specifies the type of prefetch operation. The value i specifies the type of prefetch operation: the 
	// constants _MM_HINT_T0, _MM_HINT_T1, _MM_HINT_T2, and _MM_HINT_NTA should 
	// be used, corresponding to the type of prefetch instruction. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// None. 
	// Real Address Mode Exceptions 
	// None. 
	// Virtual 8086 Mode Exceptions 
	// None. 
	// Comments 
	// This instruction is merely a hint. If executed, this instruction moves data closer to the processor 
	// in anticipation of future use. The performance of these instructions in application code can be 
	// implementation specific. To achieve maximum speedup, code tuning might be necessary for 
	// each implementation. The non temporal hint also minimizes pollution of useful cache data. 
	// PREFETCH instructions ignore the value of CR4.OSFXSR. Since they do not affect the new 
	// Streaming SIMD Extension state, they will not generate an invalid exception if CR4.OSFXSR 
	// = 0. 
	// If the PTE is not in the TLB, the prefetch is ignored. This behavior is specific to the Pentium III 
	// processor and may change with future processor implementations. 

	//BreakPoint()
}

Func_Prefix  PSADBW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// TEMP1 = abs(DEST[7-0] - SRC/m64[7-0]); 
	// TEMP2 = abs(DEST[15-8] - SRC/m64[15-8]); 
	// TEMP3 = abs(DEST[23-16] - SRC/m64[23-16]); 
	// TEMP4 = abs(DEST[31-24] - SRC/m64[31-24]); 
	// TEMP5 = abs(DEST[39-32] - SRC/m64[39-32]); 
	// TEMP6 = abs(DEST[47-40] - SRC/m64[47-40]); 
	// TEMP7 = abs(DEST[55-48] - SRC/m64[55-48]); 
	// TEMP8 = abs(DEST[63-56] - SRC/m64[63-56]); 
	// DEST[15:0] = TEMP1 + TEMP2 + TEMP3 + TEMP4 + TEMP5 + TEMP6 + TEMP7 + TEMP8; 
	// DEST[31:16] = 0X00000000; 
	// DEST[47:32] = 0X00000000; 
	// DEST[63:48] = 0X00000000; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64_m_psadbw(__m64 a,__m64 b) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64_mm_sad_pu8(__m64 a,__m64 b) 
	// Computes the sum of the absolute differences of the unsigned bytes in a and b, 
	// value in the lower word. The upper three words are cleared. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #AC For unaligned memory reference. To enable #AC exceptions, three conditions 
	// must be TRUE(CR0.AM is set; EFLAGS.AC is set; current CPL is 3). 
	// Real Address Mode Exceptions 
	// Interrupt 13 If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF(fault-code) For a page fault. 

	//BreakPoint()
}

Func_Prefix  PSHUFW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST[15-0] = (SRC/m64 >> (imm8[1-0] * 16) )[15-0] 
	// DEST[31-16] = (SRC/m64 >> (imm8[3-2] * 16) )[15-0] 
	// DEST[47-32] = (SRC/m64 >> (imm8[5-4] * 16) )[15-0] 
	// DEST[63-48] = (SRC/m64 >> (imm8[7-6] * 16) )[15-0] 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_pshufw(__m64 a, int n) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_shuffle_pi16(__m64 a, int n) 
	// 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #AC For unaligned memory reference. To enable #AC exceptions, three conditions 
	// must be TRUE(CR0.AM is set; EFLAGS.AC is set; current CPL is 3). 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF(fault-code) For a page fault. 
	// #AC For unaligned memory reference if the current privilege level is 3. 

	//BreakPoint()
}

Func_Prefix  PSLLW8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  PSLLW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix PSLLD8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}

Func_Prefix  PSLLD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}

Func_Prefix  PSLLQ8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}

Func_Prefix  PSLLQ (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF instruction is PSLLW 
	// THEN 
	// DEST(15..0) � DEST(15..0) << COUNT; 
	// DEST(31..16) � DEST(31..16) << COUNT; 
	// DEST(47..32) � DEST(47..32) << COUNT; 
	// DEST(63..48) � DEST(63..48) << COUNT; 
	// ELSE IF instruction is PSLLD 
	// THEN {
	// DEST(31..0) � DEST(31..0) << COUNT; 
	// DEST(63..32) � DEST(63..32) << COUNT; 
	// ELSE (* instruction is PSLLQ *) 
	// DEST � DEST << COUNT; 
	// FI; 
	// Intel C/C++ Compiler Intrinsic Equivalents 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_psllw (__m64 m, __m64 count) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_sll_pi16 (__m64 m, __m64 count) 
	// Shifts four 16-bit values in m left the amount specified by count while shifting in zeroes. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_psllwi (__m64 m, int count) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_slli_pi16 (__m64 m, int count) 
	// Shifts four 16-bit values in m left the amount specified by count while shifting in zeroes. For the 
	// best performance, count should be a constant. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_pslld (__m64 m, __m64 count) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_sll_pi32 (__m64 m, __m64 count) 
	// Shifts two 32-bit values in m left the amount specified by count while shifting in zeroes. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_pslldi (__m64 m, int count) 
	// Shifts two 32-bit values in m left the amount specified by count while shifting in zeroes. For the 
	// best performance, count should be a constant. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_psllq (__m64 m, __m64 count) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_sll_si64 (__m64 m, __m64 count) 
	// Shifts the 64-bit value in m left the amount specified by count while shifting in zeroes. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_psllqi (__m64 m, int count) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_slli_si64 (__m64 m, int count) 
	// Shifts the 64-bit value in m left the amount specified by count while shifting in zeroes. For the 
	// best performance, count should be a constant. 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual-8086 Mode Exceptions 
	// #GP If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix PSRAW8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}

Func_Prefix  PSRAW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}

Func_Prefix  PSRAD8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}

Func_Prefix  PSRAD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF instruction is PSRAW 
	// THEN 
	// DEST(15..0) � SignExtend (DEST(15..0) >> COUNT); 
	// DEST(31..16) � SignExtend (DEST(31..16) >> COUNT); 
	// DEST(47..32) � SignExtend (DEST(47..32) >> COUNT); 
	// DEST(63..48) � SignExtend (DEST(63..48) >> COUNT); 
	// ELSE {(*instruction is PSRAD *) 
	// DEST(31..0) � SignExtend (DEST(31..0) >> COUNT); 
	// DEST(63..32) � SignExtend (DEST(63..32) >> COUNT); 
	// FI; 
	// Intel C/C++ Compiler Intrinsic Equivalents 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_psraw (__m64 m, __m64 count) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_sraw_pi16 (__m64 m, __m64 count) 
	// Shifts four 16-bit values in m right the amount specified by count while shifting in the sign bit. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_psrawi (__m64 m, int count) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_srai_pi16 (__m64 m, int count) 
	// Shifts four 16-bit values in m right the amount specified by count while shifting in the sign bit. 
	// For the best performance, count should be a constant. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_psrad (__m64 m, __m64 count) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_sra_pi32 (__m64 m, __m64 count) 
	// Shifts two 32-bit values in m right the amount specified by count while shifting in the sign bit. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_psradi (__m64 m, int count) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_srai_pi32 (__m64 m, int count) 
	// Shifts two 32-bit values in m right the amount specified by count while shifting in the sign bit. 
	// For the best performance, count should be a constant. 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual-8086 Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  PSRLW8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  PSRLW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix PSRLD8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();	
	//BreakPoint()
}

Func_Prefix  PSRLD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();	
	//BreakPoint()
}

Func_Prefix  PSRLQ8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();	
	//BreakPoint()
}

Func_Prefix  PSRLQ (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF instruction is PSRLW 
	// THEN {
	// DEST(15..0) � DEST(15..0) >> COUNT; 
	// DEST(31..16) � DEST(31..16) >> COUNT; 
	// DEST(47..32) � DEST(47..32) >> COUNT; 
	// DEST(63..48) � DEST(63..48) >> COUNT; 
	// ELSE IF instruction is PSRLD 
	// THEN {
	// DEST(31..0) � DEST(31..0) >> COUNT; 
	// DEST(63..32) � DEST(63..32) >> COUNT; 
	// ELSE (* instruction is PSRLQ *) 
	// DEST � DEST >> COUNT; 
	// FI; 
	// Intel C/C++ Compiler Intrinsic Equivalents 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_psrlw (__m64 m, __m64 count) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_srl_pi16 (__m64 m, __m64 count) 
	// Shifts four 16-bit values in m right the amount specified by count while shifting in zeroes. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_psrlwi (__m64 m, int count) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_srli_pi16 (__m64 m, int count) 
	// Shifts four 16-bit values in m right the amount specified by count while shifting in zeroes. For 
	// the best performance, count should be a constant. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_psrld (__m64 m, __m64 count) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_sri_pi32 (__m64 m, __m64 count) 
	// Shifts two 32-bit values in m right the amount specified by count while shifting in zeroes. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_psrldi (__m64 m, int count) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_srli_pi32 (__m64 m, int count) 
	// Shifts two 32-bit values in m right the amount specified by count while shifting in zeroes. For 
	// the best performance, count should be a constant. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_psrlq (__m64 m, __m64 count) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_srl_si64 (__m64 m, __m64 count) 
	// Shifts the 64-bit value in m right the amount specified by count while shifting in zeroes. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_psrlqi (__m64 m, int count) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_srli_si64 (__m64 m, int count) 
	// Shifts the 64-bit value in m right the amount specified by count while shifting in zeroes. For the 
	// best performance, count should be a constant. 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual-8086 Mode Exceptions 
	// #GP If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  PSUBB (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  PSUBW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  PSUBD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF instruction is PSUBB 
	// THEN 
	// DEST(7..0) � DEST(7..0) � SRC(7..0); 
	// DEST(15..8) � DEST(15..8) � SRC(15..8); 
	// DEST(23..16) � DEST(23..16) � SRC(23..16); 
	// DEST(31..24) � DEST(31..24) � SRC(31..24); 
	// DEST(39..32) � DEST(39..32) � SRC(39..32); 
	// DEST(47..40) � DEST(47..40) � SRC(47..40); 
	// DEST(55..48) � DEST(55..48) � SRC(55..48); 
	// DEST(63..56) � DEST(63..56) � SRC(63..56); 
	// ELSEIF instruction is PSUBW 
	// THEN 
	// DEST(15..0) � DEST(15..0) � SRC(15..0); 
	// DEST(31..16) � DEST(31..16) � SRC(31..16); 
	// DEST(47..32) � DEST(47..32) � SRC(47..32); 
	// DEST(63..48) � DEST(63..48) � SRC(63..48); 
	// ELSE {(* instruction is PSUBD *) 
	// DEST(31..0) � DEST(31..0) � SRC(31..0); 
	// DEST(63..32) � DEST(63..32) � SRC(63..32); 
	// FI; 
	// Intel C/C++ Compiler Intrinsic Equivalents 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_psubb(__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_sub_pi8(__m64 m1, __m64 m2) 
	// Subtract the eight 8-bit values in m2 from the eight 8-bit values in m1. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_psubw(__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_sub_pi16(__m64 m1, __m64 m2) 
	// Subtract the four 16-bit values in m2 from the four 16-bit values in m1. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_psubd(__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_sub_pi32(__m64 m1, __m64 m2) 
	// Subtract the two 32-bit values in m2 from the two 32-bit values in m1. 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// Virtual-8086 Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  PSUBSB (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  PSUBSW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF instruction is PSUBSB 
	// THEN 
	// DEST(7..0) � SaturateToSignedByte(DEST(7..0) � SRC (7..0)); 
	// DEST(15..8) � SaturateToSignedByte(DEST(15..8) � SRC(15..8)); 
	// DEST(23..16) � SaturateToSignedByte(DEST(23..16) � SRC(23..16)); 
	// DEST(31..24) � SaturateToSignedByte(DEST(31..24) � SRC(31..24)); 
	// DEST(39..32) � SaturateToSignedByte(DEST(39..32) � SRC(39..32)); 
	// DEST(47..40) � SaturateToSignedByte(DEST(47..40) � SRC(47..40)); 
	// DEST(55..48) � SaturateToSignedByte(DEST(55..48) � SRC(55..48)); 
	// DEST(63..56) � SaturateToSignedByte(DEST(63..56) � SRC(63..56)) 
	// ELSE (* instruction is PSUBSW *) 
	// DEST(15..0) � SaturateToSigneUINT32(DEST(15..0) � SRC(15..0)); 
	// DEST(31..16) � SaturateToSigneUINT32(DEST(31..16) � SRC(31..16)); 
	// DEST(47..32) � SaturateToSigneUINT32(DEST(47..32) � SRC(47..32)); 
	// DEST(63..48) � SaturateToSigneUINT32(DEST(63..48) � SRC(63..48)); 
	// FI; 
	// Intel C/C++ Compiler Intrinsic Equivalents 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_psubsb(__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_subs_pi8(__m64 m1, __m64 m2) 
	// Subtract the eight signed 8-bit values in m2 from the eight signed 8-bit values in m1 and saturate. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_psubsw(__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_subs_pi16(__m64 m1, __m64 m2) 
	// Subtract the four signed 16-bit values in m2 from the four signed 16-bit values in m1 and saturate. 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual-8086 Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  PSUBUSB (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  PSUBUSW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF instruction is PSUBUSB 
	// THEN 
	// DEST(7..0) � SaturateToUnsignedByte (DEST(7..0 � SRC (7..0) ); 
	// DEST(15..8) � SaturateToUnsignedByte ( DEST(15..8) � SRC(15..8) ); 
	// DEST(23..16) � SaturateToUnsignedByte (DEST(23..16) � SRC(23..16) ); 
	// DEST(31..24) � SaturateToUnsignedByte (DEST(31..24) � SRC(31..24) ); 
	// DEST(39..32) � SaturateToUnsignedByte (DEST(39..32) � SRC(39..32) ); 
	// DEST(47..40) � SaturateToUnsignedByte (DEST(47..40) � SRC(47..40) ); 
	// DEST(55..48) � SaturateToUnsignedByte (DEST(55..48) � SRC(55..48) ); 
	// DEST(63..56) � SaturateToUnsignedByte (DEST(63..56) � SRC(63..56) ); 
	// ELSE {(* instruction is PSUBUSW *) 
	// DEST(15..0) � SaturateToUnsigneUINT32 (DEST(15..0) � SRC(15..0) ); 
	// DEST(31..16) � SaturateToUnsigneUINT32 (DEST(31..16) � SRC(31..16) ); 
	// DEST(47..32) � SaturateToUnsigneUINT32 (DEST(47..32) � SRC(47..32) ); 
	// DEST(63..48) � SaturateToUnsigneUINT32 (DEST(63..48) � SRC(63..48) ); 
	// FI; 
	// Intel C/C++ Compiler Intrinsic Equivalents 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_psubusb(__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_sub_pu8(__m64 m1, __m64 m2) 
	// Subtract the eight unsigned 8-bit values in m2 from the eight unsigned 8-bit values in m1 and 
	// saturate. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_psubusw(__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_sub_pu16(__m64 m1, __m64 m2) 
	// Subtract the four unsigned 16-bit values in m2 from the four unsigned 16-bit values in m1 and 
	// saturate. 
	// Flags Affected 
	// None. 
	// PSUBUSB/PSUBUSW�Packed Subtract Unsigned with Saturation 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual-8086 Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  PUNPCKHBW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  PUNPCKHWD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  PUNPCKHDQ (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF instruction is PUNPCKHBW 
	// THEN 
	// DEST(7..0) � DEST(39..32); 
	// DEST(15..8) � SRC(39..32); 
	// DEST(23..16) � DEST(47..40); 
	// DEST(31..24) � SRC(47..40); 
	// DEST(39..32) � DEST(55..48); 
	// DEST(47..40) � SRC(55..48); 
	// DEST(55..48) � DEST(63..56); 
	// DEST(63..56) � SRC(63..56); 
	// ELSE IF instruction is PUNPCKHW 
	// THEN 
	// DEST(15..0) � DEST(47..32); 
	// DEST(31..16) � SRC(47..32); 
	// DEST(47..32) � DEST(63..48); 
	// DEST(63..48) � SRC(63..48); 
	// ELSE (* instruction is PUNPCKHDQ *) 
	// DEST(31..0) � DEST(63..32) 
	// DEST(63..32) � SRC(63..32); 
	// FI; 
	// PUNPCKHBW/PUNPCKHWD/PUNPCKHDQ�Unpack High Packed 
	// Intel C/C++ Compiler Intrinsic Equivalents 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_punpckhbw (__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_unpckhi_pi8 (__m64 m1, __m64 m2) 
	// Interleave the four 8-bit values from the high half of m1 with the four values from the high half 
	// of m2 and take the least significant element from m1. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_punpckhwd (__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_unpckhi_pi16 (__m64 m1, __m64 m2) 
	// Interleave the two 16-bit values from the high half of m1 with the two values from the high half 
	// of m2 and take the least significant element from m1. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_punpckhdq (__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_unpckhi_pi32 (__m64 m1, __m64 m2) 
	// Interleave the 32-bit value from the high half of m1 with the 32-bit value from the high half of 
	// m2 and take the least significant element from m1. 
	// Flags Affected 
	// None. 
	// PUNPCKHBW/PUNPCKHWD/PUNPCKHDQ�Unpack High Packed 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual-8086 Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  PUNPCKLBW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  PUNPCKLWD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  PUNPCKLDQ (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF instruction is PUNPCKLBW 
	// THEN 
	// DEST(63..56) � SRC(31..24); 
	// DEST(55..48) � DEST(31..24); 
	// DEST(47..40) � SRC(23..16); 
	// DEST(39..32) � DEST(23..16); 
	// DEST(31..24) � SRC(15..8); 
	// DEST(23..16) � DEST(15..8); 
	// DEST(15..8) � SRC(7..0); 
	// DEST(7..0) � DEST(7..0); 
	// ELSE IF instruction is PUNPCKLWD 
	// THEN 
	// DEST(63..48) � SRC(31..16); 
	// DEST(47..32) � DEST(31..16); 
	// DEST(31..16) � SRC(15..0); 
	// DEST(15..0) � DEST(15..0); 
	// ELSE (* instruction is PUNPCKLDQ *) 
	// DEST(63..32) � SRC(31..0); 
	// DEST(31..0) � DEST(31..0); 
	// FI; 
	// PUNPCKLBW/PUNPCKLWD/PUNPCKLDQ�Unpack Low Packed 
	// Intel C/C++ Compiler Intrinsic Equivalents 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_punpcklbw (__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_unpcklo_pi8 (__m64 m1, __m64 m2) 
	// Interleave the four 8-bit values from the low half of m1 with the four values from the low half 
	// of m2 and take the least significant element from m1. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_punpcklwd (__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_unpcklo_pi16 (__m64 m1, __m64 m2) 
	// Interleave the two 16-bit values from the low half of m1 with the two values from the low half 
	// of m2 and take the least significant element from m1. 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_punpckldq (__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_unpcklo_pi32 (__m64 m1, __m64 m2) 
	// Interleave the 32-bit value from the low half of m1 with the 32-bit value from the low half of 
	// m2 and take the least significant element from m1. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// PUNPCKLBW/PUNPCKLWD/PUNPCKLDQ�Unpack Low Packed 
	// Real-Address Mode Exceptions 
	// #GP If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// Virtual-8086 Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 
	//BreakPoint()
}


Func_Prefix  PUSH8 (VirtualMachine *posVm)
{
	PAGED_CODE();
	PushStack(posVm, ((UINT8 *)posVm->Context.osOpcodeBlock.nOperand0)[0]);
}


Func_Prefix  PUSH16 (VirtualMachine *posVm)
{
	PAGED_CODE();
	PushStack(posVm, ((UINT16 *)posVm->Context.osOpcodeBlock.nOperand0)[0]);
}


Func_Prefix  PUSH (VirtualMachine *posVm)
{
	PAGED_CODE();
	if (posVm->Context.osOpcodeBlock.nOperand0 == 0)
	{
		return;
	}
	PushStack(posVm, ((UINT32 *)posVm->Context.osOpcodeBlock.nOperand0)[0]);
	// IF StackAddrSize = 32 
	// THEN 
	// IF OperandSize = 32 
	// THEN 
	// ESP � ESP - 4; 
	// SS:ESP � SRC; (* push doubleword *) 
	// ELSE (* OperandSize = 16*) 
	// ESP � ESP - 2; 
	// SS:ESP � SRC; (* push word *) 
	// FI; 
	// ELSE (* StackAddrSize = 16*) 
	// IF OperandSize = 16 
	// THEN 
	// SP � SP - 2; 
	// SS:SP � SRC; (* push word *) 
	// ELSE (* OperandSize = 32*) 
	// SP � SP - 4; 
	// SS:SP � SRC; (* push doubleword *) 
	// FI; 
	// FI; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS If a memory operand effective address is outside the SS segment limit. 
	// If the new value of the SP or ESP register is outside the stack segment 
	// limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) 
	// If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 
}

Func_Prefix  PUSHAD16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  PUSHAD (VirtualMachine *posVm)
{
	PAGED_CODE();
	posVm->Context.osOpcodeBlock.nOperand0 = posVm->Context.osReg.ESP;	
	PushStack(posVm, posVm->Context.osReg.EAX);
	PushStack(posVm, posVm->Context.osReg.ECX);
	PushStack(posVm, posVm->Context.osReg.EDX);
	PushStack(posVm, posVm->Context.osReg.EBX);
	PushStack(posVm, posVm->Context.osOpcodeBlock.nOperand0);
	PushStack(posVm, posVm->Context.osReg.EBP);
	PushStack(posVm, posVm->Context.osReg.ESI);
	PushStack(posVm, posVm->Context.osReg.EDI);
	// IF OperandSize = 32 (* PUSHAD instruction *) 
	// THEN 
	// Temp � (ESP); 
	// Push(EAX); 
	// Push(ECX); 
	// Push(EDX); 
	// Push(EBX); 
	// Push(Temp); 
	// Push(EBP); 
	// Push(ESI); 
	// Push(EDI); 
	// ELSE (* OperandSize = 16, PUSHA instruction *) 
	// Temp � (SP); 
	// Push(AX); 
	// Push(CX); 
	// Push(DX); 
	// Push(BX); 
	// Push(Temp); 
	// Push(BP); 
	// Push(SI); 
	// Push(DI); 
	// FI; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #SS(0) If the starting or ending stack address is outside the stack segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If an unaligned memory reference is made while the current privilege level 
	// is 3 and alignment checking is enabled. 
	// Real-Address Mode Exceptions 
	// #GP If the ESP or SP register contains 7, 9, 11, 13, or 15. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If the ESP or SP register contains 7, 9, 11, 13, or 15. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If an unaligned memory reference is made while alignment checking is 
	// enabled. 
}

Func_Prefix  PUSHF (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  PUSHFD16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  PUSHFD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF (PE=0) OR (PE=1 AND ((VM=0) OR (VM=1 AND IOPL=3))) 
	// (* Real-Address Mode, Protected mode, or Virtual-8086 mode with IOPL equal to 3 *) 
	// THEN 
	// IF OperandSize = 32 
	// THEN 
	// push(EFLAGS AND 00FCFFFFH); 
	// (* VM and RF EFLAG bits are cleared in image stored on the stack*) 
	// ELSE 
	// push(EFLAGS); (* Lower 16 bits only *) 
	// FI; 
	// ELSE (* In Virtual-8086 Mode with IOPL less than 0 *) 
	// #GP(0); (* Trap to virtual-8086 monitor *) 
	// FI; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #SS(0) If the new value of the ESP register is outside the stack segment boundary. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If an unaligned memory reference is made while the current privilege level 
	// is 3 and alignment checking is enabled. 
	// Real-Address Mode Exceptions 
	// None. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If the I/O privilege level is less than 3. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If an unaligned memory reference is made while alignment checking is 
	// enabled. 

//	//BreakPoint()
}

Func_Prefix  PXOR (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST � DEST XOR SRC; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// Pre-4.0 Intel C/C++ Compiler intrinsic: 
	// __m64 _m_pxor(__m64 m1, __m64 m2) 
	// Version 4.0 and later Intel C/C++ Compiler intrinsic: 
	// __m64 _mm_xor_si64(__m64 m1, __m64 m2) 
	// Perform a bitwise XOR of the 64-bit value in m1 with the 64-bit value in m2. 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #UD If EM in CR0 is set. 
	// #NM If TS in CR0 is set. 
	// #MF If there is a pending FPU exception. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// Virtual-8086 Mode Exceptions 
	// #GP 
	// If any part of the operand lies outside of the effective address space from 
	// 0 to FFFFH. 
	// #UD 
	// If EM in CR0 is set. 
	// #NM 
	// If TS in CR0 is set. 
	// #MF 
	// If there is a pending FPU exception. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  RCL8 (VirtualMachine *posVm)
{
	UINT32	nEFlag = posVm->Context.osReg.nEFlag;
	UINT32	nEFlagOld, nOperand1, nOperand2 ;
	PAGED_CODE();	

	FlagSaver(nEFlagOld);
	FlagRestore(nEFlag);

	nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm	mov ecx , [ecx]
	__asm	rcl byte ptr [eax] , cl

	FlagSaver(nEFlag);
	FlagRestore(nEFlagOld);

	posVm->Context.osReg.nEFlag = nEFlag;
}

Func_Prefix  RCL16 (VirtualMachine *posVm)
{
	UINT32	nEFlag = posVm->Context.osReg.nEFlag;
	UINT32	nEFlagOld, nOperand1, nOperand2 ;
	PAGED_CODE();	

	FlagSaver(nEFlagOld);
	FlagRestore(nEFlag);

	nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm	mov ecx , [ecx]
	__asm	rcl word ptr [eax] , cl

	FlagSaver(nEFlag);
	FlagRestore(nEFlagOld);

	posVm->Context.osReg.nEFlag = nEFlag;
}

Func_Prefix  RCL (VirtualMachine *posVm)
{
	UINT32	nEFlag = posVm->Context.osReg.nEFlag;
	UINT32	nEFlagOld, nOperand1, nOperand2 ;
	PAGED_CODE();	

	FlagSaver(nEFlagOld);
	FlagRestore(nEFlag);

	nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm	mov ecx , [ecx]
	__asm	rcl dword ptr [eax] , cl

	FlagSaver(nEFlag);
	FlagRestore(nEFlagOld);

	posVm->Context.osReg.nEFlag = nEFlag;
}

Func_Prefix  RCR8 (VirtualMachine *posVm)
{
	UINT32	nEFlag = posVm->Context.osReg.nEFlag;
	UINT32	nEFlagOld, nOperand1, nOperand2 ;
	PAGED_CODE();	

	FlagSaver(nEFlagOld);
	FlagRestore(nEFlag);

	nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;

	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm	mov ecx , [ecx]
	__asm	rcr byte ptr [eax] , cl

	FlagSaver(nEFlag);
	FlagRestore(nEFlagOld);

	posVm->Context.osReg.nEFlag = nEFlag;
}

Func_Prefix  RCR16 (VirtualMachine *posVm)
{
	UINT32	nEFlag = posVm->Context.osReg.nEFlag;
	UINT32	nEFlagOld, nOperand1, nOperand2 ;
	PAGED_CODE();	

	FlagSaver(nEFlagOld);
	FlagRestore(nEFlag);

	nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;

	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm	mov ecx , [ecx]
	__asm	rcr word ptr [eax] , cl

	FlagSaver(nEFlag);
	FlagRestore(nEFlagOld);

	posVm->Context.osReg.nEFlag = nEFlag;
}

Func_Prefix  RCR (VirtualMachine *posVm)
{
	UINT32	nEFlag = posVm->Context.osReg.nEFlag;
	UINT32	nEFlagOld, nOperand1, nOperand2 ;
	PAGED_CODE();	

	FlagSaver(nEFlagOld);
	FlagRestore(nEFlag);

	nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;

	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm	mov ecx , [ecx]
	__asm	rcr dword ptr [eax] , cl

	FlagSaver(nEFlag);
	FlagRestore(nEFlagOld);

	posVm->Context.osReg.nEFlag = nEFlag;
}

Func_Prefix  ROL8 (VirtualMachine *posVm)
{
	UINT32	nEFlag = posVm->Context.osReg.nEFlag;
	UINT32	nEFlagOld, nOperand1, nOperand2 ;
	PAGED_CODE();	

	FlagSaver(nEFlagOld);
	FlagRestore(nEFlag);

	nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;

	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm	mov ecx , [ecx]
	__asm	rol byte ptr [eax] , cl

	FlagSaver(nEFlag);
	FlagRestore(nEFlagOld);

	posVm->Context.osReg.nEFlag = nEFlag;
}

Func_Prefix  ROL16 (VirtualMachine *posVm)
{
	UINT32	nEFlag = posVm->Context.osReg.nEFlag;
	UINT32	nEFlagOld, nOperand1, nOperand2 ;
	PAGED_CODE();	

	FlagSaver(nEFlagOld);
	FlagRestore(nEFlag);

	nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;

	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm	mov ecx , [ecx]
	__asm	rol word ptr [eax] , cl

	FlagSaver(nEFlag);
	FlagRestore(nEFlagOld);

	posVm->Context.osReg.nEFlag = nEFlag;
}

Func_Prefix  ROL (VirtualMachine *posVm)
{
	UINT32	nEFlag = posVm->Context.osReg.nEFlag;
	UINT32	nEFlagOld, nOperand1, nOperand2 ;
	PAGED_CODE();	

	FlagSaver(nEFlagOld);
	FlagRestore(nEFlag);

	nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;

	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm	mov ecx , [ecx]
	__asm	rol dword ptr [eax] , cl

	FlagSaver(nEFlag);
	FlagRestore(nEFlagOld);

	posVm->Context.osReg.nEFlag = nEFlag;
}

Func_Prefix  ROR8 (VirtualMachine *posVm)
{
	UINT32	nEFlag = posVm->Context.osReg.nEFlag;
	UINT32	nEFlagOld, nOperand1, nOperand2 ;
	PAGED_CODE();	

	FlagSaver(nEFlagOld);
	FlagRestore(nEFlag);

	nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;

	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm	mov ecx , [ecx]
	__asm	ror byte ptr [eax] , cl

	FlagSaver(nEFlag);
	FlagRestore(nEFlagOld);

	posVm->Context.osReg.nEFlag = nEFlag;
}

Func_Prefix  ROR16 (VirtualMachine *posVm)
{
	UINT32	nEFlag = posVm->Context.osReg.nEFlag;
	UINT32	nEFlagOld, nOperand1, nOperand2 ;
	PAGED_CODE();	

	FlagSaver(nEFlagOld);
	FlagRestore(nEFlag);

	nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;

	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm	mov ecx , [ecx]
	__asm	ror word ptr [eax] , cl

	FlagSaver(nEFlag);
	FlagRestore(nEFlagOld);

	posVm->Context.osReg.nEFlag = nEFlag;
}

Func_Prefix  ROR (VirtualMachine *posVm)
{
	UINT32	nEFlag = posVm->Context.osReg.nEFlag;
	UINT32	nEFlagOld, nOperand1, nOperand2 ;
	PAGED_CODE();	

	FlagSaver(nEFlagOld);
	FlagRestore(nEFlag);

	nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;

	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm	mov ecx , [ecx]
	__asm	ror dword ptr [eax] , cl

	FlagSaver(nEFlag);
	FlagRestore(nEFlagOld);

	posVm->Context.osReg.nEFlag = nEFlag;
	// (* RCL and RCR instructions *) 
	// SIZE � OperandSize 
	// CASE (determine count) OF 
	// SIZE = 8: tempCOUNT � (COUNT AND 1FH) MOD 9; 
	// SIZE = 16: tempCOUNT � (COUNT AND 1FH) MOD 17; 
	// SIZE = 32: tempCOUNT � COUNT AND 1FH; 
	// ESAC; 
	// (* RCL instruction operation *) 
	// WHILE (tempCOUNT � 0) 
	// DO 
	// tempCF � MSB(DEST); 
	// DEST � (DEST * 2) + CF; 
	// CF � tempCF; 
	// tempCOUNT � tempCOUNT � 1; 
	// OD; 
	// ELIHW; 
	// IF COUNT = 1 
	// THEN OF � MSB(DEST) XOR CF; 
	// ELSE OF is undefined; 
	// FI; 
	// (* RCR instruction operation *) 
	// IF COUNT = 1 
	// THEN OF � MSB(DEST) XOR CF; 
	// ELSE OF is undefined; 
	// FI; 
	// WHILE (tempCOUNT � 0) 
	// DO 
	// tempCF � LSB(SRC); 
	// DEST � (DEST / 2) + (CF * 2SIZE); 
	// CF � tempCF; 
	// tempCOUNT � tempCOUNT � 1; 
	// OD; 
	// (* ROL and ROR instructions *) 
	// SIZE � OperandSize 
	// CASE (determine count) OF 
	// SIZE = 8: tempCOUNT � COUNT MOD 8; 
	// SIZE = 16: tempCOUNT � COUNT MOD 16; 
	// SIZE = 32: tempCOUNT � COUNT MOD 32; 
	// ESAC; 
	// (* ROL instruction operation *) 
	// WHILE (tempCOUNT � 0) 
	// DO 
	// tempCF � MSB(DEST); 
	// DEST � (DEST * 2) + tempCF; 
	// tempCOUNT � tempCOUNT � 1; 
	// OD; 
	// ELIHW; 
	// CF � LSB(DEST); 
	// IF COUNT = 1 
	// THEN OF � MSB(DEST) XOR CF; 
	// ELSE OF is undefined; 
	// FI; 
	// (* ROR instruction operation *) 
	// WHILE (tempCOUNT � 0) 
	// DO 
	// tempCF � LSB(SRC); 
	// DEST � (DEST / 2) + (tempCF * 2SIZE); 
	// tempCOUNT � tempCOUNT � 1; 
	// OD; 
	// ELIHW; 
	// CF � MSB(DEST); 
	// IF COUNT = 1 
	// THEN OF � MSB(DEST) XOR MSB - 1(DEST); 
	// ELSE OF is undefined; 
	// FI; 
	// Flags Affected 
	// The CF flag contains the value of the bit shifted into it. The OF flag is affected only for single-
	// bit rotates (refer to �Description� above); it is undefined for multi-bit rotates. The SF, ZF, AF, 
	// and PF flags are not affected. 
	// Protected Mode Exceptions 
	// #GP(0) If the source operand is located in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  RCPPS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// bayad baraye in dastor F3 Prefix ro barresi kard chenancheh TRUE bood dastor RCPSS ejra mishavad
	// Baraye in manzor index mmx pass shode be tabe index register haye EXX mishavad hamchenin size hafeze dar operand dovom
	// az 64 be 32 tabdil mishavad

	// DEST[31-0] = APPROX (1.0/(SRC/m128[31-0])); 
	// DEST[63-32] = APPROX (1.0/(SRC/m128[63-32])); 
	// DEST[95-64] = APPROX (1.0/(SRC/m128[95-64])); 
	// DEST[127-96] = APPROX (1.0/(SRC/m128[127-96])); 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_rcp_ps(__m128 a) 
	// Computes the approximations of the reciprocals of the four SP FP values of a. 
	// Exceptions 
	// General protection exception if not aligned on 16-byte boundary, regardless of segment. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF(fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// Real Address Mode Exceptions 
	// Interrupt 13 If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF(fault-code) For a page fault. 
	// Comments 
	// RCPPS is not affected by the rounding control in MXCSR. Denormal inputs are treated as zeroes 
	// (of the same sign) and underflow results are always flushed to zero, with the sign of the operand. 

	//BreakPoint()
}

Func_Prefix  RCPSS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST[31-0] = APPROX (1.0/(SRC/m32[31-0])); 
	// DEST[63-32] = DEST[63-32]; 
	// DEST[95-64] = DEST[95-64]; 
	// DEST[127-96] = DEST[127-96]; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_rcp_ss(__m128 a) 
	// Computes the approximation of the reciprocal of the lower SP FP value of a; the upper three SP 
	// FP values are passed through. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #AC For unaligned memory reference if the current privilege level is 3. 
	// #NM If TS bit in CR0 is set. 
	// Real Address Mode Exceptions 
	// Interrupt 13 If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #AC For unaligned memory reference if the current privilege level is 3. 
	// #PF (fault-code) For a page fault. 
	// Comments 
	// RCPSS is not affected by the rounding control in MXCSR. Denormal inputs are treated as zeroes 
	// (of the same sign) and underflow results are always flushed to zero, with the sign of the operand. 

	//BreakPoint()
}

Func_Prefix  RDMSR (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// EDX:EAX � MSR[ECX]; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If the current privilege level is not 0. 
	// If the value in ECX specifies a reserved or unimplemented MSR address. 
	// Real-Address Mode Exceptions 
	// #GP If the value in ECX specifies a reserved or unimplemented MSR address. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) The RDMSR instruction is not recognized in virtual-8086 mode. 

	//BreakPoint()
}

Func_Prefix  RDPMC (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF (ECX = 0 OR 1) AND ((CR4.PCE = 1) OR ((CR4.PCE = 0) AND (CPL=0))) 
	// THEN 
	// EDX:EAX � PMC[ECX]; 
	// ELSE (* ECX is not 0 or 1 and/or CR4.PCE is 0 and CPL is 1, 2, or 3 *) 
	// #GP(0); FI; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) 
	// If the current privilege level is not 0 and the PCE flag in the CR4 register 
	// is clear. 
	// If the value in the ECX register is not 0 or 1. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If the PCE flag in the CR4 register is clear. 
	// If the value in the ECX register is not 0 or 1. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) 
	// If the PCE flag in the CR4 register is clear. 
	// If the value in the ECX register is not 0 or 1. 

	//BreakPoint()
}

Func_Prefix  RDTSC (VirtualMachine *posVm)
{
	UINT32	nOperand2 ;
	UINT32 nOperand1 = (UINT32)&posVm->Context.osReg.EAX;
	PAGED_CODE();

	__asm	mov	ecx	,  nOperand1
	nOperand2 = (UINT32)&posVm->Context.osReg.EDX;
	__asm	mov	edi ,  nOperand2
	__asm	rdtsc
	__asm	mov [ecx], eax
	__asm	mov [edi], edx

	// IF (CR4.TSD = 0) OR ((CR4.TSD = 1) AND (CPL=0)) 
	// THEN 
	// EDX:EAX � TimeStampCounter; 
	// ELSE (* CR4 is 1 and CPL is 1, 2, or 3 *) 
	// #GP(0) 
	// FI; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If the TSD flag in register CR4 is set and the CPL is greater than 0. 
	// Real-Address Mode Exceptions 
	// #GP If the TSD flag in register CR4 is set. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If the TSD flag in register CR4 is set. 

	//BreakPoint()
}

Func_Prefix  REP (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  REPE (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  REPZ (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  REPNE (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  REPNZ (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF AddressSize = 16 
	// THEN 
	// use CX for CountReg; 
	// ELSE (* AddressSize = 32 *) 
	// use ECX for CountReg; 
	// FI; 
	// WHILE CountReg � 0 
	// DO 
	// service pending interrupts (if any); 
	// execute associated string instruction; 
	// CountReg � CountReg � 1; 
	// IF CountReg = 0 
	// THEN exit WHILE loop 
	// FI; 
	// IF (repeat prefix is REPZ or REPE) AND (ZF=0) 
	// OR (repeat prefix is REPNZ or REPNE) AND (ZF=1) 
	// THEN exit WHILE loop 
	// FI; 
	// OD; 
	// Flags Affected 
	// None; however, the CMPS and SCAS instructions do set the status flags in the EFLAGS register. 
	// Exceptions (All Operating Modes) 
	// None; however, exceptions can be generated by the instruction a repeat prefix is associated with. 

	//BreakPoint()
}

Func_Prefix RETF (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}

Func_Prefix  RET (VirtualMachine *posVm)
{
	PAGED_CODE();

	posVm->Context.osReg.EIP = PopStack(posVm);
	if(posVm->Context.osOpcodeBlock.nCountOperand == 1)
	{	
		posVm->Context.osReg.ESP += *(UINT32*)posVm->Context.osOpcodeBlock.nOperand0;
	}
	// (* Near 
	// IF instruction = near 
	// THEN; 
	// IF OperandSize = 32 
	// THEN 
	// IF top 12 bytes of stack not within stack limits THEN #SS(0); FI; 
	// EIP � Pop(); 
	// ELSE (* OperandSize = 16 *) 
	// IF top 6 bytes of stack not within stack limits 
	// THEN #SS(0) 
	// FI; 
	// tempEIP � Pop(); 
	// tempEIP � tempEIP AND 0000FFFFH; 
	// IF tempEIP not within code segment limits THEN #GP(0); FI; 
	// EIP � tempEIP; 
	// FI; 
	// IF instruction has immediate operand 
	// THEN IF StackAddressSize=32 
	// THEN 
	// ESP � ESP + SRC; (* release parameters from stack *) 
	// ELSE (* StackAddressSize=16 *) 
	// SP � SP + SRC; (* release parameters from stack *) 
	// FI; 
	// FI; 
	// (* Real-address mode or virtual-8086 mode *) 
	// IF ((PE = 0) OR (PE = 1 AND VM = 1)) AND instruction = far 
	// THEN; 
	// IF OperandSize = 32 
	// THEN 
	// IF top 12 bytes of stack not within stack limits THEN #SS(0); FI; 
	// EIP � Pop(); 
	// CS � Pop(); (* 32-bit pop, high-order 16 bits discarded *) 
	// ELSE (* OperandSize = 16 *) 
	// IF top 6 bytes of stack not within stack limits THEN #SS(0); FI; 
	// tempEIP � Pop(); 
	// tempEIP � tempEIP AND 0000FFFFH; 
	// IF tempEIP not within code segment limits THEN #GP(0); FI; 
	// EIP � tempEIP; 
	// CS � Pop(); (* 16-bit pop *) 
	// FI; 
	// IF instruction has immediate operand 
	// THEN 
	// SP � SP + (SRC AND FFFFH); (* release parameters from stack *) 
	// FI; 
	// FI; 
	// (* Protected mode, not virtual-8086 mode *) 
	// IF (PE = 1 AND VM = 0) AND instruction = far 
	// THEN 
	// IF OperandSize = 32 
	// THEN 
	// IF second doubleword on stack is not within stack limits THEN #SS(0); FI; 
	// ELSE (* OperandSize = 16 *) 
	// IF second word on stack is not within stack limits THEN #SS(0); FI; 
	// FI; 
	// IF 
	// IF 
	// THEN GP(selector; FI; 
	// Obtain descriptor to which 
	// IF 
	// if 
	// IF 
	// AND 
	// THEN #GP(selector); FI; 
	// IF 
	// IF 
	// THEN GOTO 
	// ELSE GOTO 
	// FI; 
	// END;FI; 
	// 
	// IF the 
	// THEN #GP(0); 
	// FI; 
	// IF OperandSize=32 
	// THEN 
	// EIP � Pop(); 
	// CS � Pop(); (* 32-bit pop, high-order 16 bits discarded *) 
	// ESP � ESP + SRC; (* release parameters from stack *) 
	// ELSE (* OperandSize=16 *) 
	// EIP � Pop(); 
	// EIP � EIP AND 0000FFFFH; 
	// CS � Pop(); (* 16-bit pop *) 
	// ESP � ESP + SRC; (* release parameters from stack *) 
	// FI; 
	// 
	// IF top (16 + SRC) bytes of stack are not within stack limits (OperandSize=32) 
	// OR top (8 + SRC) bytes of stack are not within stack limits (OperandSize=16) 
	// THEN #SS(0); FI; 
	// FI; 
	// Read 
	// IF stack segment selector is null THEN #GP(0); FI; 
	// IF 
	// THEN #GP(selector); FI; 
	// Read segment descriptor pointed to by 
	// IF stack segment selector RPL � RPL of the 
	// OR stack segment is not a writable data segment 
	// OR stack segment descriptor DPL � RPL of the 
	// THEN #GP(selector); FI; 
	// IF stack segment not present THEN #SS(StackSegmentSelector); FI; 
	// IF the 
	// CPL � 
	// IF OperandSize=32 
	// THEN 
	// EIP � Pop(); 
	// CS � Pop(); (* 32-bit pop, high-order 16 bits discarded *)
	// (* segment descriptor information also loaded *) 
	// CS(RPL) � CPL; 
	// ESP � ESP + SRC; (* release parameters from called procedure�s stack *) 
	// tempESP � Pop(); 
	// tempSS � Pop(); (* 32-bit pop, high-order 16 bits discarded *)
	// (* segment descriptor information also loaded *) 
	// ESP � tempESP; 
	// SS � tempSS; 
	// ELSE (* OperandSize=16 *) 
	// EIP � Pop(); 
	// EIP � EIP AND 0000FFFFH; 
	// CS � Pop(); (* 16-bit pop; segment descriptor information also loaded *) 
	// CS(RPL) � CPL; 
	// ESP � ESP + SRC; (* release parameters from called procedure�s stack *) 
	// tempESP � Pop(); 
	// tempSS � Pop(); (* 16-bit pop; segment descriptor information also loaded *)
	// (* segment descriptor information also loaded *) 
	// ESP � tempESP; 
	// SS � tempSS; 
	// FI; 
	// FOR each of segment register (ES, FS, GS, and DS) 
	// DO; 
	// IF segment register points to data or non-conforming code segment 
	// AND CPL > segment descriptor DPL; (* DPL in hidden part of segment register *) 
	// THEN (* segment register invalid *) 
	// SegmentSelector � 0; (* null segment selector *) 
	// FI; 
	// OD; 
	// For each of ES, FS, GS, and DS 
	// DO 
	// IF segment selector index is not within descriptor table limits 
	// OR segment descriptor indicates the segment is not a data or 
	// readable code segment 
	// OR if the segment is a data or non-conforming code segment and the segment 
	// descriptor�s DPL < CPL or RPL of code segment�s segment selector 
	// THEN 
	// segment selector register � null selector; 
	// OD; 
	// ESP � ESP + SRC; (* release parameters from calling procedure�s stack *) 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If the 
	// If the 
	// #GP(selector) If the RPL of the 
	// If the 
	// descriptor table limits. 
	// If the 
	// If the 
	// DPL is not equal to the RPL of the code segment�s segment selector 
	// If the 
	// greater than the RPL of the code segment�s segment selector 
	// If the stack segment is not a writable data segment. 
	// If the stack segment selector RPL is not equal to the RPL of the 
	// segment selector. 
	// If the stack segment descriptor DPL is not equal to the RPL of the 
	// code segment selector. 
	// #SS(0) If the top bytes of stack are not within stack limits. 
	// If the 
	// #NP(selector) If the 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If an unaligned memory access occurs when the CPL is 3 and alignment 
	// checking is enabled. 
	// Real-Address Mode Exceptions 
	// #GP If the 
	// #SS If the top bytes of stack are not within stack limits. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If the 
	// #SS(0) If the top bytes of stack are not within stack limits. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If an unaligned memory access occurs when alignment checking is 
	// enabled. 
	// ROL/ROR�Rotate 
	// Refer to entry for RCL/RCR/ROL/ROR�Rotate. 
}

Func_Prefix  RSM (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// 
	// ProcessorState � Restore(SSMDump); 
	// Flags Affected 
	// All. 
	// Protected Mode Exceptions 
	// #UD 
	// If an attempt is made to execute this instruction when the processor is not 
	// in SMM. 
	// Real-Address Mode Exceptions 
	// #UD 
	// If an attempt is made to execute this instruction when the processor is not 
	// in SMM. 
	// Virtual-8086 Mode Exceptions 
	// #UD 
	// If an attempt is made to execute this instruction when the processor is not 
	// in SMM. 

	//BreakPoint()
}

Func_Prefix  RSQRTPS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();	
	// bayad baraye in dastor F3 Prefix ro barresi kard chenancheh TRUE bood dastor RSQRTSS ejra mishavad
	// Baraye in manzor index mmx pass shode be tabe index register haye EXX mishavad hamchenin size hafeze dar operand dovom
	// az 64 be 32 tabdil mishavad


	// DEST[31-0] = APPROX (1.0/SQRT(SRC/m128[31-0])); 
	// DEST[63-32] = APPROX (1.0/SQRT(SRC/m128[63-32])); 
	// DEST[95-64] = APPROX (1.0/SQRT(SRC/m128[95-64])); 
	// DEST[127-96] = APPROX (1.0/SQRT(SRC/m128[127-96])); 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_rsqrt_ps(__m128 a) 
	// Computes the approximations of the reciprocals of the square roots of the four SP FP values of a. 
	// Exceptions 
	// General protection exception if not aligned on 16-byte boundary, regardless of segment. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF(fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// Interrupt 13 If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF(fault-code) For a page fault. 
	// Comments 
	// RSQRTPS is not affected by the rounding control in MXCSR. Denormal inputs are treated as 
	// zeroes (of the same sign) and underflow results are always flushed to zero, with the sign of the 
	// operand. 

	//BreakPoint()
}

Func_Prefix  RSQRTSS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST[31-0] = APPROX (1.0/SQRT(SRC/m32[31-0])); 
	// DEST[63-32] = DEST[63-32]; 
	// DEST[95-64] = DEST[95-64]; 
	// DEST[127-96] = DEST[127-96]; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_rsqrt_ss(__m128 a) 
	// Computes the approximation of the reciprocal of the square root of the lower SP FP value of a; 
	// the upper three SP FP values are passed through. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #AC For unaligned memory reference. To enable #AC exceptions, three conditions 
	// must be TRUE(CR0.AM is set; EFLAGS.AC is set; current CPL is 3) 
	// Real Address Mode Exceptions 
	// Interrupt 13 If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #AC For unaligned memory reference if the current privilege level is 3. 
	// #PF (fault-code) For a page fault. 
	// Comments 
	// RSQRTSS is not affected by the rounding control in MXCSR. Denormal inputs are treated as 
	// zeroes (of the same sign) and underflow results are always flushed to zero, with the sign of the 
	// operand. 

	//BreakPoint()
}

Func_Prefix  SAHF (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// EFLAGS(SF:ZF:0:AF:0:PF:1:CF) � AH; 
	// Flags Affected 
	// The SF, ZF, AF, PF, and CF flags are loaded with values from the AH register. Bits 1, 3, and 5 
	// of the EFLAGS register are unaffected, with the values remaining 1, 0, and 0, respectively. 
	// Exceptions (All Operating Modes) 
	// None. 
	//BreakPoint()
}


Func_Prefix  SAL8 (VirtualMachine *posVm)
{
	UINT32	nEFlag = posVm->Context.osReg.nEFlag;
	UINT32	nEFlagOld, nOperand1, nOperand2;
	PAGED_CODE();

	if (posVm->Context.osOpcodeBlock.nOperand1 == 0)
	{
		FlagSaver(nEFlagOld);
		FlagRestore(nEFlag);

		nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
		nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;

		__asm	mov	eax	,  nOperand1
		__asm	mov	ecx ,  nOperand2
		__asm sal byte ptr [eax] , 1

		FlagSaver(nEFlag);
		FlagRestore(nEFlagOld);

		posVm->Context.osReg.nEFlag = nEFlag;
	}
	else
	{	
		FlagSaver(nEFlagOld);
		FlagRestore(nEFlag);

		nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
		nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
		
		__asm	mov	eax	,  nOperand1
		__asm	mov	ecx ,  nOperand2
		__asm mov ecx , [ecx]
		__asm sal byte ptr [eax] , cl
		
		FlagSaver(nEFlag);
		FlagRestore(nEFlagOld);

		posVm->Context.osReg.nEFlag = nEFlag;
	}

}

Func_Prefix  SAL16 (VirtualMachine *posVm)
{
	UINT32	nEFlag = posVm->Context.osReg.nEFlag;
	UINT32	nEFlagOld, nOperand1, nOperand2;
	PAGED_CODE();

	if (posVm->Context.osOpcodeBlock.nOperand1 == 0)
	{
		nEFlag = posVm->Context.osReg.nEFlag;
	
		FlagSaver(nEFlagOld);
		FlagRestore(nEFlag);
		
		nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
		nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
		__asm	mov	eax	,  nOperand1
		__asm	mov	ecx ,  nOperand2
		__asm sal word ptr [eax] , 1

		FlagSaver(nEFlag);
		FlagRestore(nEFlagOld);

		posVm->Context.osReg.nEFlag = nEFlag;
	}
	else
	{
		nEFlag = posVm->Context.osReg.nEFlag;
		
		FlagSaver(nEFlagOld);
		FlagRestore(nEFlag);
		
		nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
		nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
		__asm	mov	eax	,  nOperand1
		__asm	mov	ecx ,  nOperand2
		__asm mov ecx , [ecx]
		__asm sal word ptr [eax] , cl
		
		FlagSaver(nEFlag);
		FlagRestore(nEFlagOld);

		posVm->Context.osReg.nEFlag = nEFlag;
	}
}

Func_Prefix  SAL (VirtualMachine *posVm)
{
	UINT32	nEFlag = posVm->Context.osReg.nEFlag;
	UINT32	nEFlagOld, nOperand1, nOperand2;
	PAGED_CODE();

	if (posVm->Context.osOpcodeBlock.nOperand1 == 0)
	{
		nEFlag = posVm->Context.osReg.nEFlag;
		
		FlagSaver(nEFlagOld);
		FlagRestore(nEFlag);
		
		nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
		nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
		__asm	mov	eax	,  nOperand1
		__asm	mov	ecx ,  nOperand2
		__asm sal dword ptr [eax] , 1

		FlagSaver(nEFlag);
		FlagRestore(nEFlagOld);

		posVm->Context.osReg.nEFlag = nEFlag;
	}
	else
	{
		nEFlag = posVm->Context.osReg.nEFlag;

		FlagSaver(nEFlagOld);
		FlagRestore(nEFlag);

		nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
		nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
		__asm	mov	eax	,  nOperand1
		__asm	mov	ecx ,  nOperand2
		__asm mov ecx , [ecx]
		__asm sal dword ptr [eax] , cl
		
		FlagSaver(nEFlag);
		FlagRestore(nEFlagOld);

		posVm->Context.osReg.nEFlag = nEFlag;
	}
}

Func_Prefix  SAR8 (VirtualMachine *posVm)
{
	UINT32	nEFlag = posVm->Context.osReg.nEFlag;
	UINT32	nEFlagOld, nOperand1, nOperand2;
	PAGED_CODE();

	if (posVm->Context.osOpcodeBlock.nOperand1 == 0)
	{
		nEFlag = posVm->Context.osReg.nEFlag;
	
		FlagSaver(nEFlagOld);
		FlagRestore(nEFlag);
		
		nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
		nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
		__asm	mov	eax	,  nOperand1
		__asm	mov	ecx ,  nOperand2
		__asm sar byte ptr [eax] , 1

		FlagSaver(nEFlag);
		FlagRestore(nEFlagOld);

		posVm->Context.osReg.nEFlag = nEFlag;
	}
	else
	{
		nEFlag = posVm->Context.osReg.nEFlag;

		FlagSaver(nEFlagOld);
		FlagRestore(nEFlag);

		nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
		nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
		__asm	mov	eax	,  nOperand1
		__asm	mov	ecx ,  nOperand2
		__asm mov ecx , [ecx]
		__asm sar byte ptr [eax] , cl
		
		FlagSaver(nEFlag);
		FlagRestore(nEFlagOld);

		posVm->Context.osReg.nEFlag = nEFlag;
	}
}

Func_Prefix  SAR16 (VirtualMachine *posVm)
{
	UINT32	nEFlag = posVm->Context.osReg.nEFlag;
	UINT32	nEFlagOld, nOperand1, nOperand2;
	PAGED_CODE();

	if (posVm->Context.osOpcodeBlock.nOperand1 == 0)
	{
		nEFlag = posVm->Context.osReg.nEFlag;
		
		FlagSaver(nEFlagOld);
		FlagRestore(nEFlag);

		nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
		nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
		__asm	mov	eax	,  nOperand1
		__asm	mov	ecx ,  nOperand2
		__asm sar word ptr [eax] , 1

		FlagSaver(nEFlag);
		FlagRestore(nEFlagOld);

		posVm->Context.osReg.nEFlag = nEFlag;
	}
	else
	{
		nEFlag = posVm->Context.osReg.nEFlag;
		
		FlagSaver(nEFlagOld);
		FlagRestore(nEFlag);

		nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
		nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
		__asm	mov	eax	,  nOperand1
		__asm	mov	ecx ,  nOperand2
		__asm mov ecx , [ecx]
		__asm sar word ptr [eax] , cl
		
		FlagSaver(nEFlag);
		FlagRestore(nEFlagOld);

		posVm->Context.osReg.nEFlag = nEFlag;
	}
}

Func_Prefix  SAR (VirtualMachine *posVm)
{
	UINT32	nEFlag = posVm->Context.osReg.nEFlag;
	UINT32	nEFlagOld, nOperand1, nOperand2;
	PAGED_CODE();
	
	if (posVm->Context.osOpcodeBlock.nOperand1 == 0)
	{
		nEFlag = posVm->Context.osReg.nEFlag;
		
		FlagSaver(nEFlagOld);
		FlagRestore(nEFlag);

		nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
		nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
		__asm	mov	eax	,  nOperand1
		__asm	mov	ecx ,  nOperand2
		__asm sar dword ptr [eax] , 1

		FlagSaver(nEFlag);
		FlagRestore(nEFlagOld);

		posVm->Context.osReg.nEFlag = nEFlag;
	}
	else
	{
		nEFlag = posVm->Context.osReg.nEFlag;
		
		FlagSaver(nEFlagOld);
		FlagRestore(nEFlag);

		nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
		nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
		__asm	mov	eax	,  nOperand1
		__asm	mov	ecx ,  nOperand2
		__asm mov ecx , [ecx]
		__asm sar dword ptr [eax] , cl

		FlagSaver(nEFlag);
		FlagRestore(nEFlagOld);

		posVm->Context.osReg.nEFlag = nEFlag;
	}
}

Func_Prefix  SHL8 (VirtualMachine *posVm)
{
	UINT32	nEFlag = posVm->Context.osReg.nEFlag;
	UINT32	nEFlagOld, nOperand1, nOperand2;
	PAGED_CODE();

	if (posVm->Context.osOpcodeBlock.nOperand1 == 0)
	{
		nEFlag = posVm->Context.osReg.nEFlag;
		
		FlagSaver(nEFlagOld);
		FlagRestore(nEFlag);

		nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
		nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
		__asm	mov	eax	,  nOperand1
		__asm	mov	ecx ,  nOperand2
		__asm shl byte ptr [eax] , 1

		FlagSaver(nEFlag);
		FlagRestore(nEFlagOld);

		posVm->Context.osReg.nEFlag = nEFlag;
	}
	else
	{
		nEFlag = posVm->Context.osReg.nEFlag;
		
		FlagSaver(nEFlagOld);
		FlagRestore(nEFlag);

		nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
		nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
		__asm	mov	eax	,  nOperand1
		__asm	mov	ecx ,  nOperand2
		__asm mov ecx , [ecx]
		__asm shl byte ptr [eax] , cl

		FlagSaver(nEFlag);
		FlagRestore(nEFlagOld);

		posVm->Context.osReg.nEFlag = nEFlag;
	}
}

Func_Prefix  SHL16 (VirtualMachine *posVm)
{
	UINT32	nEFlag = posVm->Context.osReg.nEFlag;
	UINT32	nEFlagOld, nOperand1, nOperand2;
	PAGED_CODE();

	if (posVm->Context.osOpcodeBlock.nOperand1 == 0)
	{
		nEFlag = posVm->Context.osReg.nEFlag;
		
		FlagSaver(nEFlagOld);
		FlagRestore(nEFlag);

		nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
		nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
		__asm	mov	eax	,  nOperand1
		__asm	mov	ecx ,  nOperand2
		__asm shl word ptr [eax] , 1

		FlagSaver(nEFlag);
		FlagRestore(nEFlagOld);

		posVm->Context.osReg.nEFlag = nEFlag;
	}
	else
	{
		nEFlag = posVm->Context.osReg.nEFlag;
		
		FlagSaver(nEFlagOld);
		FlagRestore(nEFlag);

		nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
		nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
		__asm	mov	eax	,  nOperand1
		__asm	mov	ecx ,  nOperand2
		__asm mov ecx , [ecx]
		__asm shl word ptr [eax] , cl

		FlagSaver(nEFlag);
		FlagRestore(nEFlagOld);

		posVm->Context.osReg.nEFlag = nEFlag;
	}
}

Func_Prefix  SHL (VirtualMachine *posVm)
{
	UINT32	nEFlag = posVm->Context.osReg.nEFlag;
	UINT32	nEFlagOld, nOperand1, nOperand2;
	PAGED_CODE();
	
	if (posVm->Context.osOpcodeBlock.nOperand1 == 0)
	{	
		nEFlag = posVm->Context.osReg.nEFlag;
		
		FlagSaver(nEFlagOld);
		FlagRestore(nEFlag);

		nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
		nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
		__asm	mov	eax	,  nOperand1
		__asm	mov	ecx ,  nOperand2
		__asm shl dword ptr [eax] , 1

		FlagSaver(nEFlag);
		FlagRestore(nEFlagOld);

		posVm->Context.osReg.nEFlag = nEFlag;
	}
	else
	{
		nEFlag = posVm->Context.osReg.nEFlag;
		
		FlagSaver(nEFlagOld);
		FlagRestore(nEFlag);

		nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
		nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
		__asm	mov	eax	,  nOperand1
		__asm	mov	ecx ,  nOperand2
		__asm mov ecx , [ecx]
		__asm shl dword ptr [eax] , cl

		FlagSaver(nEFlag);
		FlagRestore(nEFlagOld);

		posVm->Context.osReg.nEFlag = nEFlag;
	}
}

Func_Prefix  SHR8 (VirtualMachine *posVm)
{
	UINT32	nEFlag = posVm->Context.osReg.nEFlag;
	UINT32	nEFlagOld, nOperand1, nOperand2;
	PAGED_CODE();

	if (posVm->Context.osOpcodeBlock.nOperand1 == 0)
	{
		nEFlag = posVm->Context.osReg.nEFlag;
		
		FlagSaver(nEFlagOld);
		FlagRestore(nEFlag);

		nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
		nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
		__asm	mov	eax	,  nOperand1
		__asm	mov	ecx ,  nOperand2
		__asm shr byte ptr [eax] , 1

		FlagSaver(nEFlag);
		FlagRestore(nEFlagOld);

		posVm->Context.osReg.nEFlag = nEFlag;
	}
	else
	{
		nEFlag = posVm->Context.osReg.nEFlag;
		
		FlagSaver(nEFlagOld);
		FlagRestore(nEFlag);

		nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
		nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
		__asm	mov	eax	,  nOperand1
		__asm	mov	ecx ,  nOperand2
		__asm mov ecx , [ecx]
		__asm shr byte ptr [eax] , cl

		FlagSaver(nEFlag);
		FlagRestore(nEFlagOld);

		posVm->Context.osReg.nEFlag = nEFlag;
	}
}

Func_Prefix  SHR16 (VirtualMachine *posVm)
{
	UINT32	nEFlag = posVm->Context.osReg.nEFlag;
	UINT32	nEFlagOld, nOperand1, nOperand2;
	PAGED_CODE();

	if (posVm->Context.osOpcodeBlock.nOperand1 == 0)
	{
		nEFlag = posVm->Context.osReg.nEFlag;
		
		FlagSaver(nEFlagOld);
		FlagRestore(nEFlag);

		nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
		nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
		__asm	mov	eax	,  nOperand1
		__asm	mov	ecx ,  nOperand2
		__asm shr word ptr [eax] , 1

		FlagSaver(nEFlag);
		FlagRestore(nEFlagOld);

		posVm->Context.osReg.nEFlag = nEFlag;
	}
	else
	{
		nEFlag = posVm->Context.osReg.nEFlag;
		
		FlagSaver(nEFlagOld);
		FlagRestore(nEFlag);

		nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
		nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
		__asm	mov	eax	,  nOperand1
		__asm	mov	ecx ,  nOperand2
		__asm mov ecx , [ecx]
		__asm shr word ptr [eax] , cl

		FlagSaver(nEFlag);
		FlagRestore(nEFlagOld);

		posVm->Context.osReg.nEFlag = nEFlag;
	}
}

Func_Prefix  SHR (VirtualMachine *posVm)
{
	UINT32	nEFlag = posVm->Context.osReg.nEFlag;
	UINT32	nEFlagOld, nOperand1, nOperand2;
	PAGED_CODE();

	if (posVm->Context.osOpcodeBlock.nOperand1 == 0)
	{
		nEFlag = posVm->Context.osReg.nEFlag;
		
		FlagSaver(nEFlagOld);
		FlagRestore(nEFlag);

		nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
		nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
		__asm	mov	eax	,  nOperand1
		__asm	mov	ecx ,  nOperand2
		__asm shr dword ptr [eax] , 1

		FlagSaver(nEFlag);
		FlagRestore(nEFlagOld);

		posVm->Context.osReg.nEFlag = nEFlag;
	}
	else
	{
		nEFlag = posVm->Context.osReg.nEFlag;

		FlagSaver(nEFlagOld);
		FlagRestore(nEFlag);

		nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
		nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
		__asm	mov	eax	,  nOperand1
		__asm	mov	ecx ,  nOperand2
		__asm mov ecx , [ecx]
		__asm shr dword ptr [eax] , cl

		FlagSaver(nEFlag);
		FlagRestore(nEFlagOld);

		posVm->Context.osReg.nEFlag = nEFlag;
	}
	// tempCOUNT � (COUNT AND 1FH); 
	// tempDEST � DEST; 
	// WHILE (tempCOUNT � 0) 
	// DO 
	// IF instruction is SAL or SHL 
	// THEN 
	// CF � MSB(DEST); 
	// ELSE (* instruction is SAR or SHR *) 
	// CF � LSB(DEST); 
	// FI; 
	// IF instruction is SAL or SHL 
	// THEN 
	// DEST � DEST * 2; 
	// ELSE 
	// IF instruction is SAR 
	// THEN 
	// DEST � DEST / 2 (*Signed divide, rounding toward negative infinity*); 
	// ELSE (* instruction is SHR *) 
	// DEST � DEST / 2 ; (* Unsigned divide *); 
	// FI; 
	// FI; 
	// tempCOUNT � tempCOUNT � 1; 
	// OD; 
	// (* Determine overflow for the various instructions *) 
	// IF COUNT = 1 
	// THEN 
	// IF instruction is SAL or SHL 
	// THEN 
	// OF � MSB(DEST) XOR CF; 
	// ELSE 
	// IF instruction is SAR 
	// THEN 
	// OF � 0; 
	// ELSE (* instruction is SHR *) 
	// OF � MSB(tempDEST); 
	// FI; 
	// FI; 
	// ELSE IF COUNT = 0 
	// THEN 
	// All flags remain unchanged; 
	// ELSE (* COUNT neither 1 or 0 *) 
	// OF � undefined; 
	// FI; 
	// FI; 
	// Flags Affected 
	// The CF flag contains the value of the last bit shifted out of the destination operand; it is undefined 
	// for SHL and SHR instructions where the count is greater than or equal to the size (in bits) 
	// of the destination operand. The OF flag is affected only for 1-bit shifts (refer to �Description� 
	// above); otherwise, it is undefined. The SF, ZF, and PF flags are set according to the result. If the 
	// count is 0, the flags are not affected. For a non-zero count, the AF flag is undefined. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination is located in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 
}

Func_Prefix  SBB8 (VirtualMachine *posVm)
{
	UINT32	nEFlag = posVm->Context.osReg.nEFlag;
	UINT32	nEFlagOld, nOperand1, nOperand2;
	PAGED_CODE();
	
	FlagSaver(nEFlagOld);
	FlagRestore(nEFlag);

	nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;

	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm	mov	ecx, dword ptr[ecx]	
	__asm	sbb [eax], cl

	FlagSaver(nEFlag);
	FlagRestore(nEFlagOld);

}

Func_Prefix  SBB16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  SBB (VirtualMachine *posVm)
{
	UINT32	nEFlag = posVm->Context.osReg.nEFlag;
	UINT32	nEFlagOld, nOperand1, nOperand2;
	PAGED_CODE();
	
	FlagSaver(nEFlagOld);
 	FlagRestore(nEFlag);
	
  	nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
  	nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
 
  	__asm	mov	eax	,  nOperand1
  	__asm	mov	ecx ,  nOperand2
  	__asm	mov	ecx, dword ptr[ecx]	
  	__asm	sbb [eax], ecx

	FlagSaver(nEFlag);
	FlagRestore(nEFlagOld);

  	posVm->Context.osReg.nEFlag = nEFlag;

	// DEST � DEST � (SRC + CF); 
	// Flags Affected 
	// The OF, SF, ZF, AF, PF, and CF flags are set according to the result. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination is located in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 
}

Func_Prefix  SCAS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  SCASB16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();

	//BreakPoint()
}

Func_Prefix  SCASB (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  SCASD16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  SCASD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF (byte cmparison) 
	// THEN 
	// temp � AL - SRC; 
	// SetStatusFlags(temp); 
	// THEN IF DF = 0 
	// THEN (E)DI � (E)DI + 1; 
	// ELSE (E)DI � (E)DI � 1; 
	// FI; 
	// ELSE IF (word comparison) 
	// THEN 
	// temp � AX - SRC; 
	// SetStatusFlags(temp) 
	// THEN IF DF = 0 
	// THEN (E)DI � (E)DI + 2; 
	// ELSE (E)DI � (E)DI � 2; 
	// FI; 
	// ELSE (* doubleword comparison *) 
	// temp � EAX - SRC; 
	// SetStatusFlags(temp) 
	// THEN IF DF = 0 
	// THEN (E)DI � (E)DI + 4; 
	// ELSE (E)DI � (E)DI � 4; 
	// FI; 
	// FI; 
	// FI; 
	// Flags Affected 
	// The OF, SF, ZF, AF, PF, and CF flags are set according to the temporary result of the comparison. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the limit of the ES 
	// segment. 
	// If the ES register contains a null segment selector. 
	// If an illegal memory operand effective address in the ES segment is given. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) 
	// If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix SetAlc (VirtualMachine *posVm)
{
	PAGED_CODE();
	if(posVm->Context.osReg.nCF == 0)
	{
		posVm->Context.osReg.AL = 0;
	}
	else
	{
		posVm->Context.osReg.AL = 0xFF;
	}
}

Func_Prefix  SETO8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  SETNO8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  SETB8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  SETNB8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  SETZ8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  SETNZ8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  SETNA8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  SETNBE8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  SETS8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  SETNS8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  SETPE8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  SETPO8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  SETNGE8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  SETNL8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  SETNG8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  SETNLE8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF condition 
	// THEN DEST � 1 
	// ELSE DEST � 0; 
	// FI; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination is located in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 

	//BreakPoint()
}

Func_Prefix  SFENCE (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// WHILE (NOT(preceding_stores_globally_visible)) WAIT(); 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// void_mm_sfence(void) 
	// Guarantees that every preceding store is globally visible before any subsequent store. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// None. 
	// Real-Address Mode Exceptions 
	// None. 
	// Virtual-8086 Mode Exceptions 
	// None. 
	// Comments 
	// SFENCE ignores the value of CR4.OSFXSR. SFENCE will not generate an invalid exception 
	// if CR4.OSFXSR = 0 

	//BreakPoint()
}

Func_Prefix  SGDT (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  SIDT (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF instruction is IDTR 
	// THEN 
	// IF OperandSize = 16 
	// THEN 
	// DEST[0:15] � IDTR(Limit); 
	// DEST[16:39] � IDTR(Base); (* 24 bits of base address loaded; *) 
	// DEST[40:47] � 0; 
	// ELSE (* 32-bit Operand Size *) 
	// DEST[0:15] � IDTR(Limit); 
	// DEST[16:47] � IDTR(Base); (* full 32-bit base address loaded *) 
	// FI; 
	// ELSE (* instruction is SGDT *) 
	// IF OperandSize = 16 
	// THEN 
	// DEST[0:15] � GDTR(Limit); 
	// DEST[16:39] � GDTR(Base); (* 24 bits of base address loaded; *) 
	// DEST[40:47] � 0; 
	// ELSE (* 32-bit Operand Size *) 
	// DEST[0:15] � GDTR(Limit); 
	// DEST[16:47] � GDTR(Base); (* full 32-bit base address loaded *) 
	// FI; FI; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #UD If the destination operand is a register. 
	// #GP(0) If the destination is located in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If an unaligned memory access occurs when the CPL is 3 and alignment 
	// checking is enabled. 
	// SGDT/SIDT�Store Global/Interrupt Descriptor Table Register 
	// Real-Address Mode Exceptions 
	// #UD If the destination operand is a register. 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #UD If the destination operand is a register. 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If an unaligned memory access occurs when alignment checking is 
	// enabled. 
	// SHL/SHR�Shift Instructions 
	// Refer to entry for SAL/SAR/SHL/SHR�Shift. 

	//BreakPoint()
}

Func_Prefix  SHLD16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}

Func_Prefix  SHLD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// COUNT � COUNT MOD 32; 
	// SIZE � OperandSize 
	// IF COUNT = 0 
	// THEN 
	// no operation 
	// ELSE 
	// IF COUNT � SIZE 
	// THEN (* Bad parameters *) 
	// DEST is undefined; 
	// CF, OF, SF, ZF, AF, PF are undefined; 
	// ELSE (* Perform the shift *) 
	// CF � BIT[DEST, SIZE � COUNT]; 
	// (* Last bit shifted out on exit *) 
	// FOR i � SIZE � 1 DOWNTO COUNT 
	// DO 
	// Bit(DEST, i) � Bit(DEST, i � COUNT); 
	// OD; 
	// FOR i � COUNT � 1 DOWNTO 0 
	// DO 
	// BIT[DEST, i] � BIT[SRC, i � COUNT + SIZE]; 
	// OD; 
	// FI; 
	// FI; 
	// Flags Affected 
	// If the count is one or greater, the CF flag is filled with the last bit shifted out of the destination 
	// operand and the SF, ZF, and PF flags are set according to the value of the result. For a 1-bit shift, 
	// the OF flag is set if a sign change occurred; otherwise, it is cleared. For shifts greater than one 
	// bit, the OF flag is undefined. If a shift occurs, the AF flag is undefined. If the count operand is 
	// 0, the flags are not affected. If the count is greater than the operand size, the flags are undefined. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination is located in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}
Func_Prefix  SHRD16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	//BreakPoint()
}

Func_Prefix  SHRD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// COUNT � COUNT MOD 32; 
	// SIZE � OperandSize 
	// IF COUNT = 0 
	// THEN 
	// no operation 
	// ELSE 
	// IF COUNT � SIZE 
	// THEN (* Bad parameters *) 
	// DEST is undefined; 
	// CF, OF, SF, ZF, AF, PF are undefined; 
	// ELSE (* Perform the shift *) 
	// CF � BIT[DEST, COUNT � 1]; (* last bit shifted out on exit *) 
	// FOR i � 0 TO SIZE � 1 � COUNT 
	// DO 
	// BIT[DEST, i] � BIT[DEST, i � COUNT]; 
	// OD; 
	// FOR i � SIZE � COUNT TO SIZE � 1 
	// DO 
	// BIT[DEST,i] � BIT[inBits,i+COUNT � SIZE]; 
	// OD; 
	// FI; 
	// FI; 
	// Flags Affected 
	// If the count is one or greater, the CF flag is filled with the last bit shifted out of the destination 
	// operand and the SF, ZF, and PF flags are set according to the value of the result. For a 1-bit shift, 
	// the OF flag is set if a sign change occurred; otherwise, it is cleared. For shifts greater than one 
	// bit, the OF flag is undefined. If a shift occurs, the AF flag is undefined. If the count operand is 
	// 0, the flags are not affected. If the count is greater than the operand size, the flags are undefined. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination is located in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) 
	// If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  SHUFPS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// FP_SELECT = (imm8 >> 0) AND 0X3; 
	// IF (FP_SELECT = 0) THEN 
	// DEST[31-0] = DEST[31-0]; 
	// ELSE 
	// IF (FP_SELECT = 1) THEN 
	// DEST[31-0] = DEST[63-32]; 
	// ELSE 
	// IF (FP_SELECT = 2) THEN 
	// DEST[31-0] = DEST[95-64]; 
	// ELSE 
	// DEST[31-0] = DEST[127-96]; 
	// FI 
	// FI 
	// FI 
	// FP_SELECT = (imm8 >> 2) AND 0X3; 
	// IF (FP_SELECT = 0) THEN 
	// DEST[63-32] = DEST[31-0]; 
	// ELSE 
	// IF (FP_SELECT = 1) THEN 
	// DEST[63-32] = DEST[63-32]; 
	// ELSE 
	// IF (FP_SELECT = 2) THEN 
	// DEST[63-32] = DEST[95-64]; 
	// ELSE 
	// DEST[63-32] = DEST[127-96]; 
	// FI 
	// FI 
	// FI 
	// FP_SELECT = (imm8 >> 4) AND 0X3; 
	// IF (FP_SELECT = 0) THEN 
	// DEST[95-64] = SRC/m128[31-0]; 
	// ELSE 
	// IF (FP_SELECT = 1) THEN 
	// DEST[95-64] = SRC/m128 [63-32]; 
	// ELSE 
	// IF (FP_SELECT = 2) THEN 
	// DEST[95-64] = SRC/m128 [95-64]; 
	// ELSE 
	// DEST[95-64] = SRC/m128 [127-96]; 
	// FI 
	// FI 
	// FI 
	// FP_SELECT = (imm8 >> 6) AND 0X3; 
	// IF (FP_SELECT = 0) THEN 
	// DEST[127-96] = SRC/m128 [31-0]; 
	// ELSE 
	// IF (FP_SELECT = 1) THEN 
	// DEST[127-96] = SRC/m128 [63-32]; 
	// ELSE 
	// IF (FP_SELECT = 2) THEN 
	// DEST[127-96] = SRC/m128 [95-64]; 
	// ELSE 
	// DEST[127-96] = SRC/m128 [127-96]; 
	// FI 
	// FI 
	// FI 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_shuffle_ps(__m128 a, __m128 b, unsigned int imm8) 
	// Selects four specific SP FP values from a and b, based on the mask i. The mask must be an 
	// immediate. 
	// Exceptions 
	// General protection exception if not aligned on 16-byte boundary, regardless of segment. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF(fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #UD 
	// If CR4.OSFXSR(bit 9) = 0. 
	// #UD 
	// If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF(fault-code) For a page fault. 
	// Comments 
	// The usage of Repeat Prefix (F3H) with SHUFPS is reserved. Different processor implementations 
	// may handle this prefix differently. Usage of this prefix with SHUFPS risks incompatibility 
	// with future processors. 
	// SIDT�Store Interrupt Descriptor Table Register 
	// Refer to entry for SGDT/SIDT�Store Global/Interrupt Descriptor Table Register. 

	//BreakPoint()
}

Func_Prefix  SLDT16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  SLDT (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST � LDTR(SegmentSelector); 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination is located in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #UD The SLDT instruction is not recognized in real-address mode. 
	// Virtual-8086 Mode Exceptions 
	// #UD The SLDT instruction is not recognized in virtual-8086 mode. 

	//BreakPoint()
}

Func_Prefix  SMSW16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  SMSW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST � CR0[15:0]; (* Machine status word *); 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination is located in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) 
	// If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  SQRTPS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// bayad baraye in dastor F3 Prefix ro barresi kard chenancheh TRUE bood dastor SQRTSS ejra mishavad
	// Baraye in manzor index mmx pass shode be tabe index register haye EXX mishavad hamchenin size hafeze dar operand dovom
	// az 64 be 32 tabdil mishavad


	// DEST[31-0] = SQRT (SRC/m128[31-0]); 
	// DEST[63-32] = SQRT (SRC/m128[63-32]); 
	// DEST[95-64] = SQRT (SRC/m128[95-64]); 
	// DEST[127-96] = SQRT (SRC/m128[127-96]); 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_sqrt_ps(__m128 a) 
	// Computes the square roots of the four SP FP values of a. 
	// Exceptions 
	// General protection exception if not aligned on 16-byte boundary, regardless of segment. 
	// Numeric Exceptions 
	// Invalid, Precision, Denormal. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF(fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #XM For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =1). 
	// #UD For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =0). 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #XM 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =1). 
	// #UD 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =0). 
	// #UD 
	// If CR4.OSFXSR(bit 9) = 0. 
	// #UD 
	// If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF(fault-code) For a page fault. 

	//BreakPoint()
}

Func_Prefix  SQRTSS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST[31-0] = SQRT (SRC/m32[31-0]); 
	// DEST[63-32] = DEST[63-32]; 
	// DEST[95-64] = DEST[95-64]; 
	// DEST[127-96] = DEST[127-96]; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_sqrt_ss(__m128 a) 
	// Computes the square root of the lower SP FP value of a; the upper three SP FP values are passed 
	// through. 
	// Exceptions 
	// None. 
	// Numeric Exceptions 
	// Invalid, Precision, Denormal. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #AC For unaligned memory reference. To enable #AC exceptions, thtions must be TRUE(CR0.AM is set; EFLAGS.AC is set; current 
	// ree condi-
	// CPL is 3). 
	// #XM For an unmasked Streaming 
	// (CR4.OSXMMEXCPT =1). 
	// SIMD Extension numeric exception 
	// #UD For an unmasked Streaming 
	// (CR4.OSXMMEXCPT =0). 
	// SIMD Extension numeric exception 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #XM 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =1). 
	// #UD 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =0). 
	// #UD 
	// If CR4.OSFXSR(bit 9) = 0. 
	// #UD 
	// If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #AC For unaligned memory reference if the current privilege level is 3. 
	// #PF (fault-code) For a page fault. 

	//BreakPoint()
}

Func_Prefix  STC (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// CF � 1; 
	// Flags Affected 
	// The CF flag is set. The OF, ZF, SF, AF, and PF flags are unaffected. 
	// Exceptions (All Operating Modes) 
	// None. 

//	//BreakPoint()
}

Func_Prefix  STD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DF � 1; 
	// Flags Affected 
	// The DF flag is set. The CF, OF, ZF, SF, AF, and PF flags are unaffected. 
	// Operation 
	// DF � 1; 
	// Exceptions (All Operating Modes) 
	// None. 

	//BreakPoint()
}

Func_Prefix  STI (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF PE=0 (* Executing in real-address mode *) 
	// THEN 
	// IF � 1; (* Set Interrupt Flag *) 
	// ELSE (* Executing in protected mode or virtual-8086 mode *) 
	// IF VM=0 (* Executing in protected mode*) 
	// THEN 
	// IF IOPL = 3 
	// THEN 
	// IF � 1; 
	// ELSE 
	// IF CPL � IOPL 
	// THEN 
	// IF � 1; 
	// ELSE 
	// #GP(0); 
	// FI; 
	// FI; 
	// ELSE (* Executing in Virtual-8086 mode *) 
	// #GP(0); (* Trap to virtual-8086 monitor *) 
	// FI; 
	// FI; 
	// Flags Affected 
	// The IF flag is set to 1. 
	// Protected Mode Exceptions 
	// #GP(0) 
	// If the CPL is greater (has less privilege) than the IOPL of the current 
	// program or procedure. 
	// Real-Address Mode Exceptions 
	// None. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) 
	// If the CPL is greater (has less privilege) than the IOPL of the current 
	// program or procedure. 

	//BreakPoint()
}

Func_Prefix  STMXCSR (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// m32 = MXCSR; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// _mm_getcsr(void) 
	// 
	// Exceptions 
	// None. 
	// Numeric Exceptions 
	// None. 
	// STMXCSR�Store Streaming SIMD Extension Control/Status 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF(fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #AC For unaligned memory reference. To enable #AC exceptions, three conditions 
	// must be TRUE(CR0.AM is set; EFLAGS.AC is set; current CPL is 3). 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// Interrupt 13 If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF(fault-code) For a page fault. 
	// #AC For unaligned memory reference. 
	// Comments 
	// The usage of Repeat Prefix (F3H) with STMXCSR is reserved. Different processor implementations 
	// may handle this prefix differently. Usage of this prefix with STMXCSR risks incompatibility 
	// with future processors. 

	//BreakPoint()
}

Func_Prefix  STOS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  STOSB16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  STOSB (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  STOSD16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  STOSD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF (byte store) 
	// THEN 
	// DEST � AL; 
	// THEN IF DF = 0 
	// THEN (E)DI � (E)DI + 1; 
	// ELSE (E)DI � (E)DI � 1; 
	// FI; 
	// ELSE IF (word store) 
	// THEN 
	// DEST � AX; 
	// THEN IF DF = 0 
	// THEN (E)DI � (E)DI + 2; 
	// ELSE (E)DI � (E)DI � 2; 
	// FI; 
	// ELSE (* doubleword store *) 
	// DEST � EAX; 
	// THEN IF DF = 0 
	// THEN (E)DI � (E)DI + 4; 
	// ELSE (E)DI � (E)DI � 4; 
	// FI; 
	// FI; 
	// FI; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination is located in a nonwritable segment. 
	// If a memory operand effective address is outside the limit of the ES 
	// segment. 
	// If the ES register contains a null segment selector. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP If a memory operand effective address is outside the ES segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the ES segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 

	//BreakPoint()
}

Func_Prefix  STR16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  STR (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST � TR(SegmentSelector); 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination is a memory operand that is located in a nonwritable 
	// segment or if the effective address is outside the CS, DS, ES, FS, or GS 
	// segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #UD The STR instruction is not recognized in real-address mode. 
	// Virtual-8086 Mode Exceptions 
	// #UD The STR instruction is not recognized in virtual-8086 mode. 

	//BreakPoint()
}

Func_Prefix  SUB8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	*(((UINT8 *)posVm->Context.osOpcodeBlock.nOperand0)) -= *((UINT8 *)posVm->Context.osOpcodeBlock.nOperand1);
	FlagSaver(nEFlag);
	posVm->Context.osReg.nEFlag = nEFlag;
}

Func_Prefix  SUB16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();

	//BreakPoint()
}


Func_Prefix  SUB (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	*(((UINT32 *)posVm->Context.osOpcodeBlock.nOperand0)) -= *((UINT32 *)posVm->Context.osOpcodeBlock.nOperand1);
	FlagSaver(nEFlag);
	posVm->Context.osReg.nEFlag = nEFlag;
	// DEST � DEST � SRC; 
	// Flags Affected 
	// The OF, SF, ZF, AF, PF, and CF flags are set according to the result. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination is located in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 
}

Func_Prefix  SUBPS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// bayad baraye in dastor F3 Prefix ro barresi kard chenancheh TRUE bood dastor SUBSS ejra mishavad
	// Baraye in manzor index mmx pass shode be tabe index register haye EXX mishavad hamchenin size hafeze dar operand dovom
	// az 64 be 32 tabdil mishavad

	// DEST[31-0] = DEST[31-0] - SRC/m128[31-0]; 
	// DEST[63-32] = DEST[63-32] - SRC/m128[63-32]; 
	// DEST[95-64] = DEST[95-64] - SRC/m128[95-64]; 
	// DEST[127-96] = DEST[127-96] - SRC/m128[127-96]; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_sub_ps(__m128 a, __m128 b) 
	// Subtracts the four SP FP values of a and b. 
	// Exceptions 
	// General protection exception if not aligned on 16-byte boundary, regardless of segment. 
	// Numeric Exceptions 
	// Overflow, Underflow, Invalid, Precision, Denormal. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF(fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #XM For an unmasked Streaming 
	// (CR4.OSXMMEXCPT =1). 
	// SIMD Extension numeric exception 
	// #UD For an unmasked Streaming 
	// (CR4.OSXMMEXCPT =0). 
	// SIMD Extension numeric exception 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #XM 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =1). 
	// #UD 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =0). 
	// #UD 
	// If CR4.OSFXSR(bit 9) = 0. 
	// #UD 
	// If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF(fault-code) For a page fault. 

	//BreakPoint()
}

Func_Prefix  SUBSS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST[31-0] = DEST[31-0] - SRC/m32[31-0]; 
	// DEST[63-32] = DEST[63-32]; 
	// DEST[95-64] = DEST[95-64]; 
	// DEST[127-96] = DEST[127-96]; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_sub_ss(__m128 a, __m128 b) 
	// Subtracts the lower SP FP values of a and b. The upper three SP FP values are passed through 
	// from a. 
	// Exceptions 
	// None. 
	// Numeric Exceptions 
	// Overflow, Underflow, Invalid, Precision, Denormal. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #AC For unaligned memory reference. To enabtions must be TRUE(CR0.AM is set; EFLAle #AC excGS.AC is septions, three condiet; 
	// current CPL is 3). 
	// #XM For an unmasked Streaming SIMD(CR4.OSXMMEXCPT =1). 
	// Extension numeric exception 
	// #UD For an unmasked Streaming SIMD(CR4.OSXMMEXCPT =0). 
	// Extension numeric exception 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #XM 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =1). 
	// #UD 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =0). 
	// #UD 
	// If CR4.OSFXSR(bit 9) = 0. 
	// #UD 
	// If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #AC For unaligned memory reference if the current privilege level is 3. 
	// #PF(fault-code) For a page fault. 

	//BreakPoint()
}

Func_Prefix  SYSENTER (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// SYSENTER 
	// IF CR0.PE == 0 THEN #GP(0) 
	// IF SYSENTER_CS_MSR == 0 THEN #GP(0) 
	// EFLAGS.VM := 0 	// Prevent VM86 mode 
	// EFLAGS.IF := 0 	// Mask interrupts 
	// CS.SEL := SYSENTER_CS_MSR 	// Operating system provides CS 
	// 	// Set rest of CS to a fixed value 
	// CS.SEL.CPL := 0 	// CPL = 0 
	// CS.SEL.BASE := 0 	// Flat segment 
	// CS.SEL.LIMIT := 0xFFFF 	// 4G limit 
	// CS.SEL.G := 1 	// 4 KB granularity 
	// CS.SEL.S := 1 
	// CS.SEL.TYPE_xCRA := 1011 	// Execute + Read, Accessed 
	// CS.SEL.D := 1 	// 32 bit code 
	// CS.SEL.DPL := 0 
	// CS.SEL.RPL := 0 
	// CS.SEL.P := 1 
	// SS.SEL := CS.SEL+8 
	// 	// Set rest of SS to a fixed value 
	// SS.SEL.BASE := 0 	// Flat segment 
	// SS.SEL.LIMIT := 0xFFFF 	// 4G limit 
	// SS.SEL.G := 1 	// 4 KB granularity 
	// SS.SEL.S := 1 
	// SS.SEL.TYPE_xCRA := 0011 	// Read/Write, Accessed 
	// SS.SEL.D := 1 	// 32 bit stack 
	// SS.SEL.DPL := 0 
	// SS.SEL.RPL := 0 
	// SS.SEL.P := 1 
	// ESP := SYSENTER_ESP_MSR 
	// EIP := SYSENTER_EIP_MSR 
	// SYSENTER�Fast Transition to System Call Entry Point 
	// Exceptions 
	// #GP(0) If SYSENTER_CS_MSR contains zero. 
	// Numeric Exceptions 
	// None. 
	// Real Address Mode Exceptions 
	// #GP(0) If protected mode is not enabled. 

	//BreakPoint()
}

Func_Prefix  SYSEXIT (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// SYSEXIT 
	// IF SYSENTER_CS_MSR == 0 THEN #GP(0) 
	// IF CR0.PE == 0 THEN #GP(0) 
	// IF CPL <> 0 THEN #GP(0) 
	// 	// Changing CS:EIP and SS:ESP is required 
	// CS.SEL := (SYSENTER_CS_MSR + 16) 	// Selector for 
	// CS.SEL.RPL := 3 
	// 	// Set rest of CS to a fixed value 
	// CS.SEL.BASE := 0 	// Flat segment 
	// CS.SEL.LIMIT := 0xFFFF 	// 4G limit 
	// CS.SEL.G := 1 	// 4 KB granularity 
	// CS.SEL.S := 1 
	// CS.SEL.TYPE_xCRA := 1011 	// Execute, Read, Non-Conforming Code 
	// CS.SEL.D := 1 	// 32 bit code 
	// CS.SEL.DPL := 3 
	// CS.SEL.P := 1 
	// SS.SEL := (SYSENTER_CS_MSR + 24) 
	// SS.SEL.RPL := 3 
	// 	// Set rest of SS to a fixed value 
	// SS.SEL.BASE := 0 	// Flat segment 
	// SS.SEL.LIMIT := 0xFFFF 	// 4G limit 
	// SS.SEL.G := 1 	// 4 KB granularity 
	// SS.SEL.S := 1 
	// SS.SEL.TYPE_xCRA := 0011 	// Expand Up, Read/Write, Data 
	// SS.SEL.D := 1 	// 32 bit stack 
	// SS.SEL.DPL := 3 
	// SS.SEL.CPL := 3 
	// SS.SEL.P := 1 
	// ESP := ECX 
	// EIP := EDX 
	// SYSEXIT�Fast Transition from System Call Entry Point 
	// Exceptions 
	// #GP(0) If SYSENTER_CS_MSR contains zero. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If CPL is non-zero. 
	// Real Address Mode Exceptions 
	// #GP(0) If protected mode is not enabled. 

	//BreakPoint()
}

Func_Prefix  TEST8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	UINT32 nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	UINT32 nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
	PAGED_CODE();	

	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm	mov	ecx, dword ptr[ecx]
	__asm	Test byte ptr [eax], cl
	FlagSaver(nEFlag);
	posVm->Context.osReg.nEFlag = nEFlag;
}

Func_Prefix  TEST16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  TEST (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	UINT32 nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	UINT32 nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
	PAGED_CODE();	

	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm	mov	ecx, dword ptr[ecx]
	__asm	Test dword ptr [eax], ecx
	FlagSaver(nEFlag);
	posVm->Context.osReg.nEFlag = nEFlag;
	// TEMP � SRC1 AND SRC2; 
	// SF � MSB(TEMP); 
	// IF TEMP = 0 
	// THEN ZF � 1; 
	// ELSE ZF � 0; 
	// FI: 
	// PF � BitwiseXNOR(TEMP[0:7]); 
	// CF � 0; 
	// OF � 0; 
	// (*AF is Undefined*) 
	// Flags Affected 
	// The OF and CF flags are cleared to 0. The SF, ZF, and PF flags are set according to the result 
	// (refer to the �Operation� section above). The state of the AF flag is undefined. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 
}

Func_Prefix  UCOMISS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// OF = 0; 
	// SF = 0; 
	// AF = 0; 
	// IF ((DEST[31-0] UNORD SRC/m32[31-0]) = TRUE) THEN 
	// ZF = 1; 
	// PF = 1; 
	// CF = 1; 
	// ELSE 
	// IF ((DEST[31-0] GTRTHAN SRC/m32[31-0]) = TRUE)THEN 
	// ZF = 0; 
	// PF = 0; 
	// CF = 0; 
	// ELSE 
	// IF ((DEST[31-0] LESSTHAN SRC/m32[31-0]) = TRUE THEN 
	// ZF = 0; 
	// PF = 0; 
	// CF = 1; 
	// ELSE 
	// ZF = 1; 
	// PF = 0; 
	// CF = 0; 
	// FI 
	// FI 
	// FI 
	// UCOMISS�Unordered Scalar Single-FP compare and set EFLAGS 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// _mm_ucomieq_ss(__m128 a, __m128 b) 
	// Compares the lower SP FP value of a and b for a equal to b. If a and b are equal, 1 is 
	// Otherwise 0 is 
	// _mm_ucomilt_ss(__m128 a, __m128 b) 
	// Compares the lower SP FP value of a and b for a less than b. If a is less than b, 1 is 
	// Otherwise 0 is 
	// _mm_ucomile_ss(__m128 a, __m128 b) 
	// Compares the lower SP FP value of a and b for a less than or equal to b. If a is less than or equal 
	// to b, 1 is 
	// _mm_ucomigt_ss(__m128 a, __m128 b) 
	// Compares the lower SP FP value of a and b for a greater than b. If a is greater than b are equal, 
	// 1 is 
	// _mm_ucomige_ss(__m128 a, __m128 b) 
	// Compares the lower SP FP value of a and b for a greater than or equal to b. If a is greater than 
	// or equal to b, 1 is 
	// _mm_ucomineq_ss(__m128 a, __m128 b) 
	// Compares the lower SP FP value of a and b for a not equal to b. If a and b are not equal, 1 is 
	// 
	// Exceptions 
	// None. 
	// Numeric Exceptions 
	// Invalid (if sNaN operands), Denormal. Integer EFLAGS values will not be updated in the presence 
	// of unmasked numeric exceptions. 
	// UCOMISS�Unordered Scalar Single-FP compare and set EFLAGS 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF (fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #AC For unaligned memory reference. To enabtions must be TRUE(CR0.AM is set; EFLAle #AC excGS.AC is septions, three condiet; 
	// current CPL is 3). 
	// #XM For an unmasked Streaming SIMD(CR4.OSXMMEXCPT =1). 
	// Extension numeric exception 
	// #UD For an unmasked Streaming SIMD(CR4.OSXMMEXCPT =0). 
	// Extension numeric exception 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #XM 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =1). 
	// #UD 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =0). 
	// #UD 
	// If CR4.OSFXSR(bit 9) = 0. 
	// #UD 
	// If CPUID.XMM(EDX bit 25) = 0. 
	// UCOMISS�Unordered Scalar Single-FP compare and set EFLAGS 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #AC For unaligned memory reference if the current privilege level is 3. 
	// #PF (fault-code) For a page fault. 
	// Comments 
	// UCOMISS differs from COMISS in that it signals an invalid numeric exception when a source 
	// operand is an sNaN; COMISS signals invalid if a source operand is either a qNaN or an sNaN. 
	// The usage of Repeat (F2H, F3H) and Operand-size (66H) prefixes with UCOMISS is reserved. 
	// Different processor implementations may handle these prefixes differently. Usage of these 
	// prefixes with UCOMISS risks incompatibility with future processors. 

	//BreakPoint()
}

Func_Prefix  UD2 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// #UD (* Generates invalid opcode exception *); 
	// Flags Affected 
	// None. 
	// Exceptions (All Operating Modes) 
	// #UD 
	// Instruction is guaranteed to raise an invalid opcode exception in all operating 
	// modes). 

	//BreakPoint()
}

Func_Prefix  UNPCKHPS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST[31-0] = DEST[95-64]; 
	// DEST[63-32] = SRC/m128[95-64]; 
	// DEST[95-64] = DEST[127-96]; 
	// DEST[127-96] = SRC/m128[127-96]; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_unpackhi_ps(__m128 a, __m128 b) 
	// Selects and interleaves the upper two SP FP values from a and b. 
	// Exceptions 
	// General protection exception if not aligned on 16-byte boundary, regardless of segment. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF(fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// Interrupt 13 If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF(fault-code) For a page fault. 
	// Comments 
	// When unpacking from a memory operand, an implementation may decide to fetch only the 
	// appropriate 64 bits. Alignment to 16-byte boundary and normal segment checking will still be 
	// enforced. 
	// The usage of Repeat Prefix (F3H) with UNPCKHPS is reserved. Different processor implementations 
	// may handle this prefix differently. Usage of this prefix with UNPCKHPS risks incompatibility 
	// with future processors. 

	//BreakPoint()
}

Func_Prefix  UNPCKLPS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// DEST[31-0] = DEST[31-0]; 
	// DEST[63-32] = SRC/m128[31-0]; 
	// DEST[95-64] = DEST[63-32]; 
	// DEST[127-96] = SRC/m128[63-32]; 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_unpacklo_ps(__m128 a, __m128 b) 
	// Selects and interleaves the lower two SP FP values from a and b. 
	// Exceptions 
	// General protection exception if not aligned on 16-byte boundary, regardless of segment. 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF(fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// Interrupt 13 If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF(fault-code) For a page fault. 
	// Comments 
	// When unpacking from a memory operand, an implementation may decide to fetch only the 
	// appropriate 64 bits. Alignment to 16-byte boundary and normal segment checking will still be 
	// enforced. 
	// The usage of Repeat Prefixes (F2H, F3H) with UNPCKLPS is reserved. Different processor 
	// implementations may handle this prefix differently. Usage of these prefixes with UNPCKLPS 
	// risks incompatibility with future processors. 

	//BreakPoint()
}

Func_Prefix  VERR16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  VERR (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  VERW16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  VERW (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF SRC(Offset) > (GDTR(Limit) OR (LDTR(Limit)) 
	// THEN 
	// ZF � 0 
	// Read segment descriptor; 
	// IF SegmentDescriptor(DescriptorType) = 0 (* system segment *) 
	// OR (SegmentDescriptor(Type) � conforming code segment) 
	// AND (CPL > DPL) OR (RPL > DPL) 
	// THEN 
	// ZF � 0 
	// ELSE 
	// IF ((Instruction = VERR) AND (segment = readable)) 
	// OR ((Instruction = VERW) AND (segment = writable)) 
	// THEN 
	// ZF � 1; 
	// FI; 
	// FI; 
	// Flags Affected 
	// The ZF flag is set to 1 if the segment is accessible and readable (VERR) or writable (VERW); 
	// otherwise, it is cleared to 0. 
	// Protected Mode Exceptions 
	// The only exceptions generated for these instructions are those related to illegal addressing of the 
	// source operand. 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register is used to access memory and it contains 
	// a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #UD 
	// The VERR and VERW instructions are not recognized in real-address 
	// mode. 
	// Virtual-8086 Mode Exceptions 
	// #UD 
	// The VERR and VERW instructions are not recognized in virtual-8086 
	// mode. 

	//BreakPoint()
}

Func_Prefix  WAIT (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  FWAIT (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// CheckForPendingUnmaskedFloatingPointExceptions; 
	// FPU Flags Affected 
	// The C0, C1, C2, and C3 flags are undefined. 
	// Floating-Point Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #NM MP and TS in CR0 is set. 
	// Real-Address Mode Exceptions 
	// #NM MP and TS in CR0 is set. 
	// Virtual-8086 Mode Exceptions 
	// #NM MP and TS in CR0 is set. 

//	//BreakPoint()
}

Func_Prefix  WBINVD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// WriteBack(InternalCaches); 
	// Flush(InternalCaches); 
	// SignalWriteBack(ExternalCaches); 
	// SignalFlush(ExternalCaches); 
	// Continue (* Continue execution); 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If the current privilege level is not 0. 
	// Real-Address Mode Exceptions 
	// None. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) The WBINVD instruction cannot be executed at the virtual-8086 mode. 

	//BreakPoint()
}

Func_Prefix  WRMSR (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// MSR[ECX] � EDX:EAX; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) 
	// If the current privilege level is not 0. 
	// If the value in ECX specifies a reserved or unimplemented MSR address. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If the value in ECX specifies a reserved or unimplemented MSR address. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) 
	// The WRMSR instruction is not recognized in virtual-8086 mode. 

	//BreakPoint()
}

Func_Prefix  XADD8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  XADD16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  XADD (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	UINT32 nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	UINT32 nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
	PAGED_CODE();	

	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm	mov	ecx, dword ptr[ecx]
	__asm	xadd dword ptr [eax], ecx
	FlagSaver(nEFlag);
	posVm->Context.osReg.nEFlag = nEFlag;
	__asm	mov	eax	,  nOperand2
	__asm	mov	[eax], ecx
	// TEMP � SRC + DEST 
	// SRC � DEST 
	// DEST � TEMP 
	// Flags Affected 
	// The CF, PF, AF, SF, ZF, and OF flags are set according to the result of the addition, which is 
	// stored in the destination operand. 
	// Protected Mode Exceptions 
	// #GP(0) If the destination is located in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) 
	// If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) 
	// If a page fault occurs. 
	// #AC(0) 
	// If alignment checking is enabled and an unaligned memory reference is 
	// made. 

//	//BreakPoint()
}

Func_Prefix  XCHG8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	UINT8 u8Tmp = *((UINT8 *)posVm->Context.osOpcodeBlock.nOperand0);
	PAGED_CODE();	

	*((UINT8 *)posVm->Context.osOpcodeBlock.nOperand0) = *((UINT8 *)posVm->Context.osOpcodeBlock.nOperand1);
	*((UINT8 *)posVm->Context.osOpcodeBlock.nOperand1) = u8Tmp;	
}

Func_Prefix  XCHG16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	UINT16 u16Tmp = *((UINT16 *)posVm->Context.osOpcodeBlock.nOperand0);
	PAGED_CODE();	

	*((UINT16 *)posVm->Context.osOpcodeBlock.nOperand0) = *((UINT16 *)posVm->Context.osOpcodeBlock.nOperand1);
	*((UINT16 *)posVm->Context.osOpcodeBlock.nOperand1) = u16Tmp;	
	//BreakPoint()
}

Func_Prefix  XCHG (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	UINT32 nTmp = *((UINT32 *)posVm->Context.osOpcodeBlock.nOperand0);
	PAGED_CODE();	

	*(UINT32 *)posVm->Context.osOpcodeBlock.nOperand0 = *((UINT32 *)posVm->Context.osOpcodeBlock.nOperand1);
	*((UINT32 *)posVm->Context.osOpcodeBlock.nOperand1) = nTmp;	

	// TEMP � DEST 
	// DEST � SRC 
	// SRC � TEMP 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If either operand is in a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 


}

Func_Prefix  XLAT (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();


	//BreakPoint()
}

Func_Prefix  XLATB (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// IF AddressSize = 16 
	// THEN 
	// AL � (DS:BX + ZeroExtend(AL)) 
	// ELSE (* AddressSize = 32 *) 
	// AL � (DS:EBX + ZeroExtend(AL)); 
	// FI; 
	// Flags Affected 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// Real-Address Mode Exceptions 
	// #GP If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment 
	//BreakPoint()
}


Func_Prefix  XOR8 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	UINT32 nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	UINT32 nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
	PAGED_CODE();	

	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm mov ecx , [ecx]
	__asm xor byte ptr [eax], cl
	FlagSaver(nEFlag);
	posVm->Context.osReg.nEFlag = nEFlag;
	////BreakPoint()
}


Func_Prefix  XOR16 (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	UINT32 nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	UINT32 nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
	PAGED_CODE();	

	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm mov ecx , [ecx]
	__asm xor word ptr [eax], cx
	FlagSaver(nEFlag);
	posVm->Context.osReg.nEFlag = nEFlag;
	//BreakPoint()
}


Func_Prefix  XOR (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	UINT32 nOperand1 = posVm->Context.osOpcodeBlock.nOperand0;
	UINT32 nOperand2 = posVm->Context.osOpcodeBlock.nOperand1;
	PAGED_CODE();	

	__asm	mov	eax	,  nOperand1
	__asm	mov	ecx ,  nOperand2
	__asm mov ecx , [ecx]
	__asm xor dword ptr [eax], ecx
	FlagSaver(nEFlag);
	posVm->Context.osReg.nEFlag = nEFlag;
	// Operation 
	// DEST ش DEST XOR SRC; 
	// Flags Affected 
	// The OF and CF flags are cleared; the SF, ZF, and PF flags are set according to the result. The 
	// state of the AF flag is undefined. 
	// INSTRUCTION SET REFERENCE 
	// XORùLogical Exclusive OR (Continued) 
	// Protected Mode Exceptions 
	// #GP(0) If the destination operand points to a nonwritable segment. 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// If the DS, ES, FS, or GS register contains a null segment selector. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made while the current privilege level is 3. 
	// Real-Address Mode Exceptions 
	// #GP 
	// If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS 
	// If a memory operand effective address is outside the SS segment limit. 
	// Virtual-8086 Mode Exceptions 
	// #GP(0) If a memory operand effective address is outside the CS, DS, ES, FS, or 
	// GS segment limit. 
	// #SS(0) If a memory operand effective address is outside the SS segment limit. 
	// #PF(fault-code) If a page fault occurs. 
	// #AC(0) If alignment checking is enabled and an unaligned memory reference is 
	// made. 
}

Func_Prefix  XORPS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// Operation 
	// DEST[127-0] = DEST/m128[127-0] XOR SRC/m128[127-0] 
	// Intel C/C++ Compiler Intrinsic Equivalent 
	// __m128 _mm_xor_ps(__m128 a, __m128 b) 
	// Computes bitwise EXOR (exclusive-or) of the four SP FP values of a and b. 
	// Exceptions 
	// General protection exception if not aligned on 16-byte boundary, regardless of segment. 
	// INSTRUCTION SET REFERENCE 
	// XORPSùBit-wise Logical Xor for Single-FP Data (Continued) 
	// Numeric Exceptions 
	// None. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF(fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// Interrupt 13 If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual 8086 Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF(fault-code) For a page fault. 
	// Comments 
	// The usage of Repeat Prefix (F3H) with XORPS is reserved. Different processor implementations 
	// may handle this prefix differently. Usage of this prefix with XORPS risks incompatibility. 

	//BreakPoint()
}

Func_Prefix  CMPPS (VirtualMachine *posVm)
{
	UINT32	nEFlag;
	PAGED_CODE();
	// bayad baraye in dastor F3 Prefix ro barresi kard chenancheh TRUE bood dastor CMPSS ejra mishavad
	// Baraye in manzor index mmx pass shode be tabe index register haye EXX mishavad hamchenin size hafeze dar operand dovom
	// az 64 be 32 tabdil mishavad


	// IF (imm8 = 0) THEN 
	// OP = "EQ"; 
	// ELSE 
	// IF (imm8 = 1) THEN 
	// OP = "LT"; 
	// ELSE 
	// IF (imm8 = 2) THEN 
	// OP = "LE"; 
	// ELSE 
	// IF (imm8 = 3) THEN 
	// OP = "UNORD"; 
	// ELSE 
	// IF (imm8 = 4) THEN 
	// OP = "NE"; 
	// ELSE 
	// IF (imm8 = 5) THEN 
	// OP = "NLT"; 
	// ELSE 
	// IF (imm8 = 6) THEN 
	// OP = "NLE"; 
	// ELSE 
	// IF (imm8 = 7) THEN 
	// OP = "ORD"; 
	// FI 
	// FI 
	// FI 
	// FI 
	// FI 
	// FI 
	// FI 
	// FI 
	// CMP0 = DEST[31-0] OP SRC/m128[31-0]; 
	// CMP1 = DEST[63-32] OP SRC/m128[63-32]; 
	// CMP2 = DEST [95-64] OP SRC/m128[95-64]; 
	// CMP3 = DEST[127-96] OP SRC/m128[127-96]; 
	// IF (CMP0 = TRUE) THEN 
	// DEST[31-0] = 0XFFFFFFFF; 
	// DEST[63-32] = 0XFFFFFFFF; 
	// DEST[95-64] = 0XFFFFFFFF; 
	// DEST[127-96] = 0XFFFFFFFF; 
	// ELSE 
	// DEST[31-0] = 0X00000000; 
	// DEST[63-32] = 0X00000000; 
	// DEST[95-64] = 0X00000000; 
	// DEST[127-96] = 0X00000000; 
	// FI 
	// Intel C/C++ Compiler Intrinsic Equivalents 
	// __m128 _mm_cmpeq_ps(__m128 a, __m128 b) 
	// Compare for equality. 
	// __m128 _mm_cmplt_ps(__m128 a, __m128 b) 
	// Compare for less-than. 
	// __m128 _mm_cmple_ps(__m128 a, __m128 b) 
	// Compare for less-than-or-equal. 
	// __m128 _mm_cmpgt_ps(__m128 a, __m128 b) 
	// Compare for greater-than. 
	// __m128 _mm_cmpge_ps(__m128 a, __m128 b) 
	// Compare for greater-than-or-equal. 
	// __m128 _mm_cmpneq_ps(__m128 a, __m128 b) 
	// Compare for inequality. 
	// __m128 _mm_cmpnlt_ps(__m128 a, __m128 b) 
	// Compare for not-less-than. 
	// __m128 _mm_cmpngt_ps(__m128 a, __m128 b) 
	// Compare for not-greater-than. 
	// __m128 _mm_cmpnge_ps(__m128 a, __m128 b) 
	// Compare for not-greater-than-or-equal. 
	// __m128 _mm_cmpord_ps(__m128 a, __m128 b) 
	// Compare for ordered. 
	// __m128 _mm_cmpunord_ps(__m128 a, __m128 b) 
	// Compare for unordered. 
	// __m128 _mm_cmpnle_ps(__m128 a, __m128 b) 
	// Compare for not-less-than-or-equal. 
	// Exceptions 
	// General protection exception if not aligned on 16-byte boundary, regardless of segment. 
	// Numeric Exceptions 
	// Invalid, if sNaN operands, denormal. 
	// Protected Mode Exceptions 
	// #GP(0) For an illegal memory operand effective address in the CS, DS, ES, FS, or 
	// GS segments. 
	// #SS(0) For an illegal address in the SS segment. 
	// #PF(fault-code) For a page fault. 
	// #UD If CR0.EM = 1. 
	// #NM If TS bit in CR0 is set. 
	// #XM For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =1). 
	// #UD For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =0). 
	// #UD If CR4.OSFXSR(bit 9) = 0. 
	// #UD If CPUID.XMM(EDX bit 25) = 0. 
	// Real Address Mode Exceptions 
	// Interrupt 13 
	// If any part of the operand would lie outside of the effective address space 
	// from 0 to 0FFFFH. 
	// #UD 
	// If CR0.EM = 1. 
	// #NM 
	// If TS bit in CR0 is set. 
	// #XM 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =1). 
	// #UD 
	// For an unmasked Streaming SIMD Extension numeric exception 
	// (CR4.OSXMMEXCPT =0). 
	// #UD 
	// If CR4.OSFXSR(bit 9) = 0. 
	// #UD 
	// If CPUID.XMM(EDX bit 25) = 0. 
	// Virtual Mode Exceptions 
	// Same exceptions as in Real Address Mode. 
	// #PF(fault-code) For a page fault. 
	// Comments 
	// Compilers and assemblers should implement the following 2-operand pseudo-ops in addition to 
	// the 3-operand CMPPS instruction: 
	// Pseudo-Op Implementation 
	// CMPEQPS xmm1, xmm2 
	// CMPLTPS xmm1, xmm2 
	// CMPLEPS xmm1, xmm2 
	// CMPUNORDPS xmm1, xmm2 
	// CMPNEQPS xmm1, xmm2 
	// CMPNLTPS xmm1, xmm2 
	// CMPNLEPS xmm1, xmm2 
	// CMPORDPS xmm1, xmm2 
	// CMPPS xmm1,xmm2, 0 
	// CMPPS xmm1,xmm2, 1 
	// CMPPS xmm1,xmm2, 2 
	// CMPPS xmm1,xmm2, 3 
	// CMPPS xmm1,xmm2, 4 
	// CMPPS xmm1,xmm2, 5 
	// CMPPS xmm1,xmm2, 6 
	// CMPPS xmm1,xmm2, 7 
	// The greater-than relations not implemented in hardware require more than one instruction to 
	// emulate in software and therefore should not be implemented as pseudo-ops. (For these, the 
	// programmer should reverse the operands of the corresponding less than relations and use move 
	// instructions to ensure that the mask is moved to the correct destination register and that the 
	// source operand is left intact.) 
	// Bits 7-4 of the immediate field are reserved. Different processors may handle them differently. 
	// Usage of these bits risks incompatibility with future processors. 

	//BreakPoint()
}
