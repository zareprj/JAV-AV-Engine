
#ifndef OperationsFunctions_ADDED
#define OperationsFunctions_ADDED
#include "All_Defines.h"
#define Func_Prefix void	__fastcall 
#define Func_Params void	VirtualMachine *posVm


//	Assembly Function Prototypes

//Func_Prefix AAA8 (VirtualMachine *posVm);
Func_Prefix AAA (VirtualMachine *posVm);

Func_Prefix AAD (VirtualMachine *posVm);
Func_Prefix AAM (VirtualMachine *posVm);

Func_Prefix AAS8 (VirtualMachine *posVm);
Func_Prefix AAS (VirtualMachine *posVm);

Func_Prefix ADC8 (VirtualMachine *posVm);
Func_Prefix ADC16 (VirtualMachine *posVm);
Func_Prefix ADC (VirtualMachine *posVm);
Func_Prefix ADD8 (VirtualMachine *posVm);
Func_Prefix ADD16 (VirtualMachine *posVm);
Func_Prefix ADD (VirtualMachine *posVm);
Func_Prefix ADDPS (VirtualMachine *posVm);
Func_Prefix ADDSS (VirtualMachine *posVm);

Func_Prefix AND8 (VirtualMachine *posVm);
Func_Prefix AND16 (VirtualMachine *posVm);
Func_Prefix AND (VirtualMachine *posVm);
Func_Prefix ANDNPS (VirtualMachine *posVm);
Func_Prefix ANDPS (VirtualMachine *posVm);

Func_Prefix ARPL16 (VirtualMachine *posVm);
Func_Prefix ARPL (VirtualMachine *posVm);

Func_Prefix BOUND16 (VirtualMachine *posVm);
Func_Prefix BOUND (VirtualMachine *posVm);

Func_Prefix BSF16 (VirtualMachine *posVm);
Func_Prefix BSF (VirtualMachine *posVm);

Func_Prefix BSR16 (VirtualMachine *posVm);
Func_Prefix BSR (VirtualMachine *posVm);

Func_Prefix BSWAP16 (VirtualMachine *posVm);
Func_Prefix BSWAP (VirtualMachine *posVm);

Func_Prefix BT8 (VirtualMachine *posVm);
Func_Prefix BT16 (VirtualMachine *posVm);
Func_Prefix BT (VirtualMachine *posVm);

Func_Prefix BTC8 (VirtualMachine *posVm);
Func_Prefix BTC16 (VirtualMachine *posVm);
Func_Prefix BTC (VirtualMachine *posVm);

Func_Prefix BTR8 (VirtualMachine *posVm);
Func_Prefix BTR16 (VirtualMachine *posVm);
Func_Prefix BTR (VirtualMachine *posVm);

Func_Prefix BTS8 (VirtualMachine *posVm);
Func_Prefix BTS16 (VirtualMachine *posVm);
Func_Prefix BTS (VirtualMachine *posVm);

//Func_Prefix CALL8 (VirtualMachine *posVm);
Func_Prefix CALL16 (VirtualMachine *posVm);
Func_Prefix CALL (VirtualMachine *posVm);

Func_Prefix CBW (VirtualMachine *posVm);
Func_Prefix CWDE (VirtualMachine *posVm);
Func_Prefix CLC (VirtualMachine *posVm);
Func_Prefix CLD (VirtualMachine *posVm);
Func_Prefix CLI (VirtualMachine *posVm);
Func_Prefix CLTS (VirtualMachine *posVm);
Func_Prefix CMC (VirtualMachine *posVm);

Func_Prefix CMP8 (VirtualMachine *posVm);
Func_Prefix CMP16 (VirtualMachine *posVm);
Func_Prefix CMP (VirtualMachine *posVm);
Func_Prefix CMPSB (VirtualMachine *posVm);
Func_Prefix CMPSD16 (VirtualMachine *posVm);
Func_Prefix CMPSD (VirtualMachine *posVm);
Func_Prefix CMPSS (VirtualMachine *posVm);

Func_Prefix CMPXCHG8 (VirtualMachine *posVm);
Func_Prefix CMPXCHG16 (VirtualMachine *posVm);
Func_Prefix CMPXCHG (VirtualMachine *posVm);

Func_Prefix CMPXCHG8B (VirtualMachine *posVm);
Func_Prefix COMISS (VirtualMachine *posVm);
Func_Prefix CPUID (VirtualMachine *posVm);
Func_Prefix CVTPI2PS (VirtualMachine *posVm);
Func_Prefix CVTPS2PI (VirtualMachine *posVm);
Func_Prefix CVTSI2SS (VirtualMachine *posVm);
Func_Prefix CVTSS2SI (VirtualMachine *posVm);
Func_Prefix CVTTPS2PI (VirtualMachine *posVm);
Func_Prefix CVTTSS2SI (VirtualMachine *posVm);
Func_Prefix CWD (VirtualMachine *posVm);
Func_Prefix CDQ (VirtualMachine *posVm);

Func_Prefix DAA8 (VirtualMachine *posVm);
Func_Prefix DAA (VirtualMachine *posVm);

Func_Prefix DAS8 (VirtualMachine *posVm);
Func_Prefix DAS (VirtualMachine *posVm);

Func_Prefix DEC8 (VirtualMachine *posVm);
Func_Prefix DEC16 (VirtualMachine *posVm);
Func_Prefix DEC (VirtualMachine *posVm);

Func_Prefix DIV8 (VirtualMachine *posVm);
Func_Prefix DIV16 (VirtualMachine *posVm);
Func_Prefix DIV (VirtualMachine *posVm);

Func_Prefix DIVPS (VirtualMachine *posVm);
Func_Prefix DIVSS (VirtualMachine *posVm);
Func_Prefix EMMS (VirtualMachine *posVm);

Func_Prefix ENTER8 (VirtualMachine *posVm);
Func_Prefix ENTER (VirtualMachine *posVm);

Func_Prefix F2XM1 (VirtualMachine *posVm);
Func_Prefix FABS (VirtualMachine *posVm);
Func_Prefix FADD (VirtualMachine *posVm);
Func_Prefix FADDP (VirtualMachine *posVm);
Func_Prefix FIADD (VirtualMachine *posVm);

Func_Prefix FBLD8 (VirtualMachine *posVm);
Func_Prefix FBLD (VirtualMachine *posVm);

Func_Prefix FBSTP8 (VirtualMachine *posVm);
Func_Prefix FBSTP (VirtualMachine *posVm);

Func_Prefix FCHS (VirtualMachine *posVm);
Func_Prefix FCLEX (VirtualMachine *posVm);
Func_Prefix FNCLEX (VirtualMachine *posVm);
Func_Prefix FCOM (VirtualMachine *posVm);
Func_Prefix FCOMP (VirtualMachine *posVm);
Func_Prefix FCOMPP (VirtualMachine *posVm);
Func_Prefix FCOMI (VirtualMachine *posVm);
Func_Prefix FCOMIP (VirtualMachine *posVm);
Func_Prefix FUCOMI (VirtualMachine *posVm);
Func_Prefix FUCOMIP (VirtualMachine *posVm);
Func_Prefix FCOS (VirtualMachine *posVm);
Func_Prefix FDECSTP (VirtualMachine *posVm);
Func_Prefix FDIV (VirtualMachine *posVm);
Func_Prefix FDIVP (VirtualMachine *posVm);
Func_Prefix FIDIV (VirtualMachine *posVm);
Func_Prefix FDIVR (VirtualMachine *posVm);
Func_Prefix FDIVRP (VirtualMachine *posVm);
Func_Prefix FIDIVR (VirtualMachine *posVm);
Func_Prefix FFREE (VirtualMachine *posVm);
Func_Prefix FICOM (VirtualMachine *posVm);
Func_Prefix FICOMP (VirtualMachine *posVm);
Func_Prefix FILD (VirtualMachine *posVm);
Func_Prefix FINCSTP (VirtualMachine *posVm);
Func_Prefix FINIT (VirtualMachine *posVm);
Func_Prefix FNINIT (VirtualMachine *posVm);
Func_Prefix FIST (VirtualMachine *posVm);
Func_Prefix FISTP (VirtualMachine *posVm);

Func_Prefix FLD8 (VirtualMachine *posVm);
Func_Prefix FLD (VirtualMachine *posVm);

Func_Prefix FLD1 (VirtualMachine *posVm);
Func_Prefix FLDL2T (VirtualMachine *posVm);
Func_Prefix FLDL2E (VirtualMachine *posVm);
Func_Prefix FLDPI (VirtualMachine *posVm);
Func_Prefix FLDLG2 (VirtualMachine *posVm);
Func_Prefix FLDLN2 (VirtualMachine *posVm);
Func_Prefix FLDZ (VirtualMachine *posVm);
Func_Prefix FLDCW (VirtualMachine *posVm);
Func_Prefix FLDENV (VirtualMachine *posVm);
Func_Prefix FMUL (VirtualMachine *posVm);
Func_Prefix FMULP (VirtualMachine *posVm);
Func_Prefix FIMUL (VirtualMachine *posVm);
Func_Prefix FNOP (VirtualMachine *posVm);
Func_Prefix FPATAN (VirtualMachine *posVm);
Func_Prefix FPREM (VirtualMachine *posVm);
Func_Prefix FPREM1 (VirtualMachine *posVm);
Func_Prefix FPTAN (VirtualMachine *posVm);
Func_Prefix FRNDINT (VirtualMachine *posVm);
Func_Prefix FRSTOR (VirtualMachine *posVm);
Func_Prefix FSAVE (VirtualMachine *posVm);
Func_Prefix FNSAVE (VirtualMachine *posVm);
Func_Prefix FSCALE (VirtualMachine *posVm);
Func_Prefix FSIN (VirtualMachine *posVm);
Func_Prefix FSINCOS (VirtualMachine *posVm);
Func_Prefix FSQRT (VirtualMachine *posVm);
Func_Prefix FST (VirtualMachine *posVm);

Func_Prefix FSTP8 (VirtualMachine *posVm);
Func_Prefix FSTP (VirtualMachine *posVm);

Func_Prefix FSTCW (VirtualMachine *posVm);
Func_Prefix FNSTCW (VirtualMachine *posVm);
Func_Prefix FSTENV (VirtualMachine *posVm);
Func_Prefix FNSTENV (VirtualMachine *posVm);
Func_Prefix FSTSW (VirtualMachine *posVm);

Func_Prefix FNSTSW16 (VirtualMachine *posVm);
Func_Prefix FNSTSW (VirtualMachine *posVm);

Func_Prefix FSUB (VirtualMachine *posVm);
Func_Prefix FSUBP (VirtualMachine *posVm);
Func_Prefix FISUB (VirtualMachine *posVm);
Func_Prefix FSUBR (VirtualMachine *posVm);
Func_Prefix FSUBRP (VirtualMachine *posVm);
Func_Prefix FISUBR (VirtualMachine *posVm);
Func_Prefix FTST (VirtualMachine *posVm);
Func_Prefix FUCOM (VirtualMachine *posVm);
Func_Prefix FUCOMP (VirtualMachine *posVm);
Func_Prefix FUCOMPP (VirtualMachine *posVm);
Func_Prefix FXAM (VirtualMachine *posVm);
Func_Prefix FXCH (VirtualMachine *posVm);
Func_Prefix FXRSTOR (VirtualMachine *posVm);
Func_Prefix FXSAVE (VirtualMachine *posVm);
Func_Prefix FXTRACT (VirtualMachine *posVm);
Func_Prefix FYL2X (VirtualMachine *posVm);
Func_Prefix FYL2XP1 (VirtualMachine *posVm);
Func_Prefix HLT (VirtualMachine *posVm);

Func_Prefix IDIV8 (VirtualMachine *posVm);
Func_Prefix IDIV16 (VirtualMachine *posVm);
Func_Prefix IDIV (VirtualMachine *posVm);

Func_Prefix IMUL8 (VirtualMachine *posVm);
Func_Prefix IMUL16 (VirtualMachine *posVm);
Func_Prefix IMUL (VirtualMachine *posVm);

Func_Prefix IN_16 (VirtualMachine *posVm);
Func_Prefix IN_8 (VirtualMachine *posVm);
Func_Prefix IN_ (VirtualMachine *posVm);

Func_Prefix INC8 (VirtualMachine *posVm);
Func_Prefix INC16 (VirtualMachine *posVm);
Func_Prefix INC (VirtualMachine *posVm);
Func_Prefix INS (VirtualMachine *posVm);
Func_Prefix INSB (VirtualMachine *posVm);
Func_Prefix INSW (VirtualMachine *posVm);
Func_Prefix INSD (VirtualMachine *posVm);
Func_Prefix INTn8 (VirtualMachine *posVm);
Func_Prefix INTO (VirtualMachine *posVm);
Func_Prefix INT3 (VirtualMachine *posVm);
Func_Prefix INVD (VirtualMachine *posVm);
Func_Prefix INVLPG (VirtualMachine *posVm);
Func_Prefix IRET (VirtualMachine *posVm);
Func_Prefix IRETD (VirtualMachine *posVm);

Func_Prefix JMP16 (VirtualMachine *posVm);
Func_Prefix JMP (VirtualMachine *posVm);

Func_Prefix LAHF (VirtualMachine *posVm);

Func_Prefix LAR16 (VirtualMachine *posVm);
Func_Prefix LAR (VirtualMachine *posVm);

Func_Prefix LDMXCSR (VirtualMachine *posVm);

Func_Prefix LDS16 (VirtualMachine *posVm);
Func_Prefix LDS (VirtualMachine *posVm);

Func_Prefix LES16 (VirtualMachine *posVm);
Func_Prefix LES (VirtualMachine *posVm);

Func_Prefix LFS16 (VirtualMachine *posVm);
Func_Prefix LFS (VirtualMachine *posVm);

Func_Prefix LGS16 (VirtualMachine *posVm);
Func_Prefix LGS (VirtualMachine *posVm);

Func_Prefix LSS16 (VirtualMachine *posVm);
Func_Prefix LSS (VirtualMachine *posVm);

Func_Prefix LEA16 (VirtualMachine *posVm);
Func_Prefix LEA (VirtualMachine *posVm);

Func_Prefix LEAVE16 (VirtualMachine *posVm);
Func_Prefix LEAVE (VirtualMachine *posVm);

Func_Prefix LGDT (VirtualMachine *posVm);
Func_Prefix LIDT (VirtualMachine *posVm);

Func_Prefix LLDT16 (VirtualMachine *posVm);
Func_Prefix LLDT (VirtualMachine *posVm);

Func_Prefix LMSW16 (VirtualMachine *posVm);
Func_Prefix LMSW (VirtualMachine *posVm);

Func_Prefix LOCK (VirtualMachine *posVm);
Func_Prefix LODS (VirtualMachine *posVm);

Func_Prefix LODSB16 (VirtualMachine *posVm);
Func_Prefix LODSB (VirtualMachine *posVm);
Func_Prefix LODSD16 (VirtualMachine *posVm);
Func_Prefix LODSD (VirtualMachine *posVm);
Func_Prefix LOOP (VirtualMachine *posVm);

Func_Prefix LSL16 (VirtualMachine *posVm);
Func_Prefix LSL (VirtualMachine *posVm);

Func_Prefix LTR16 (VirtualMachine *posVm);
Func_Prefix LTR (VirtualMachine *posVm);

Func_Prefix MASKMOVQ (VirtualMachine *posVm);
Func_Prefix MAXPS (VirtualMachine *posVm);
Func_Prefix MAXSS (VirtualMachine *posVm);
Func_Prefix MINPS (VirtualMachine *posVm);
Func_Prefix MINSS (VirtualMachine *posVm);

Func_Prefix MOV8 (VirtualMachine *posVm);
Func_Prefix MOV16 (VirtualMachine *posVm);
Func_Prefix MOV (VirtualMachine *posVm);

// Func_Prefix MOV_Control (VirtualMachine *posVm);
// Func_Prefix MOV_Debug (VirtualMachine *posVm);

Func_Prefix MOVAPS (VirtualMachine *posVm);

Func_Prefix MOVD16 (VirtualMachine *posVm);
Func_Prefix MOVD (VirtualMachine *posVm);

Func_Prefix MOVHLPS (VirtualMachine *posVm);
Func_Prefix MOVHPS (VirtualMachine *posVm);
Func_Prefix MOVLHPS (VirtualMachine *posVm);
Func_Prefix MOVLPS (VirtualMachine *posVm);
Func_Prefix MOVMSKPS (VirtualMachine *posVm);
Func_Prefix MOVNTPS (VirtualMachine *posVm);
Func_Prefix MOVNTQ (VirtualMachine *posVm);
Func_Prefix MOVQ (VirtualMachine *posVm);
//Func_Prefix MOVS (VirtualMachine *posVm);
Func_Prefix MOVSB (VirtualMachine *posVm);
Func_Prefix MOVSD16 (VirtualMachine *posVm);
Func_Prefix MOVSD (VirtualMachine *posVm);
Func_Prefix MOVSS (VirtualMachine *posVm);

Func_Prefix MOVSX8 (VirtualMachine *posVm);
Func_Prefix MOVSX16 (VirtualMachine *posVm);
Func_Prefix MOVSX (VirtualMachine *posVm);

Func_Prefix MOVUPS (VirtualMachine *posVm);

Func_Prefix MOVZX8 (VirtualMachine *posVm);
Func_Prefix MOVZX16 (VirtualMachine *posVm);
Func_Prefix MOVZX (VirtualMachine *posVm);

Func_Prefix MUL8 (VirtualMachine *posVm);
Func_Prefix MUL16 (VirtualMachine *posVm);
Func_Prefix MUL (VirtualMachine *posVm);

Func_Prefix MULPS (VirtualMachine *posVm);
Func_Prefix MULSS (VirtualMachine *posVm);

Func_Prefix NEG8 (VirtualMachine *posVm);
Func_Prefix NEG16 (VirtualMachine *posVm);
Func_Prefix NEG (VirtualMachine *posVm);

Func_Prefix NOP (VirtualMachine *posVm);

Func_Prefix NOT8 (VirtualMachine *posVm);
Func_Prefix NOT16 (VirtualMachine *posVm);
Func_Prefix NOT (VirtualMachine *posVm);

Func_Prefix OR8 (VirtualMachine *posVm);
Func_Prefix OR16 (VirtualMachine *posVm);
Func_Prefix OR (VirtualMachine *posVm);
Func_Prefix ORPS (VirtualMachine *posVm);

Func_Prefix OUT_8 (VirtualMachine *posVm);
Func_Prefix OUT_16 (VirtualMachine *posVm);
Func_Prefix OUT_ (VirtualMachine *posVm);

Func_Prefix OUTS (VirtualMachine *posVm);
Func_Prefix OUTSB (VirtualMachine *posVm);
Func_Prefix OUTSW (VirtualMachine *posVm);
Func_Prefix OUTSD (VirtualMachine *posVm);
Func_Prefix PACKSSWB (VirtualMachine *posVm);
Func_Prefix PACKSSDW (VirtualMachine *posVm);
Func_Prefix PACKUSWB (VirtualMachine *posVm);
Func_Prefix PADDB (VirtualMachine *posVm);
Func_Prefix PADDW (VirtualMachine *posVm);
Func_Prefix PADDD (VirtualMachine *posVm);
Func_Prefix PADDSB (VirtualMachine *posVm);
Func_Prefix PADDSW (VirtualMachine *posVm);
Func_Prefix PADDUSB (VirtualMachine *posVm);
Func_Prefix PADDUSW (VirtualMachine *posVm);
Func_Prefix PAND (VirtualMachine *posVm);
Func_Prefix PANDN (VirtualMachine *posVm);
Func_Prefix PAVGB (VirtualMachine *posVm);
Func_Prefix PAVGW (VirtualMachine *posVm);
Func_Prefix PCMPEQB (VirtualMachine *posVm);
Func_Prefix PCMPEQW (VirtualMachine *posVm);
Func_Prefix PCMPEQD (VirtualMachine *posVm);
Func_Prefix PCMPGTB (VirtualMachine *posVm);
Func_Prefix PCMPGTW (VirtualMachine *posVm);
Func_Prefix PCMPGTD (VirtualMachine *posVm);
Func_Prefix PEXTRW (VirtualMachine *posVm);
Func_Prefix PINSRW (VirtualMachine *posVm);
Func_Prefix PMADDWD (VirtualMachine *posVm);
Func_Prefix PMAXSW (VirtualMachine *posVm);
Func_Prefix PMAXUB (VirtualMachine *posVm);
Func_Prefix PMINSW (VirtualMachine *posVm);
Func_Prefix PMINUB (VirtualMachine *posVm);

Func_Prefix PMOVMSKB16 (VirtualMachine *posVm);
Func_Prefix PMOVMSKB (VirtualMachine *posVm);

Func_Prefix PMULHUW (VirtualMachine *posVm);
Func_Prefix PMULHW (VirtualMachine *posVm);
Func_Prefix PMULLW (VirtualMachine *posVm);

Func_Prefix POP8 (VirtualMachine *posVm);
Func_Prefix POP16 (VirtualMachine *posVm);
Func_Prefix POP (VirtualMachine *posVm);
//Func_Prefix POPA (VirtualMachine *posVm);

Func_Prefix POPAD16 (VirtualMachine *posVm);
Func_Prefix POPAD (VirtualMachine *posVm);
Func_Prefix POPF (VirtualMachine *posVm);

Func_Prefix POPFD16 (VirtualMachine *posVm);
Func_Prefix POPFD (VirtualMachine *posVm);

Func_Prefix POR (VirtualMachine *posVm);
//Func_Prefix PREFETCH (VirtualMachine *posVm);
Func_Prefix PSADBW (VirtualMachine *posVm);
Func_Prefix PSHUFW (VirtualMachine *posVm);

Func_Prefix PSLLW8 (VirtualMachine *posVm);
Func_Prefix PSLLW (VirtualMachine *posVm);

Func_Prefix PSLLD8 (VirtualMachine *posVm);
Func_Prefix PSLLD (VirtualMachine *posVm);

Func_Prefix PSLLQ8 (VirtualMachine *posVm);
Func_Prefix PSLLQ (VirtualMachine *posVm);

Func_Prefix PSRAW8 (VirtualMachine *posVm);
Func_Prefix PSRAW (VirtualMachine *posVm);

Func_Prefix PSRAD8 (VirtualMachine *posVm);
Func_Prefix PSRAD (VirtualMachine *posVm);

Func_Prefix PSRLW8 (VirtualMachine *posVm);
Func_Prefix PSRLW (VirtualMachine *posVm);

Func_Prefix PSRLD8 (VirtualMachine *posVm);
Func_Prefix PSRLD (VirtualMachine *posVm);

Func_Prefix PSRLQ8 (VirtualMachine *posVm);
Func_Prefix PSRLQ (VirtualMachine *posVm);

Func_Prefix PSUBB (VirtualMachine *posVm);
Func_Prefix PSUBW (VirtualMachine *posVm);
Func_Prefix PSUBD (VirtualMachine *posVm);
Func_Prefix PSUBSB (VirtualMachine *posVm);
Func_Prefix PSUBSW (VirtualMachine *posVm);
Func_Prefix PSUBUSB (VirtualMachine *posVm);
Func_Prefix PSUBUSW (VirtualMachine *posVm);
Func_Prefix PUNPCKHBW (VirtualMachine *posVm);
Func_Prefix PUNPCKHWD (VirtualMachine *posVm);
Func_Prefix PUNPCKHDQ (VirtualMachine *posVm);
Func_Prefix PUNPCKLBW (VirtualMachine *posVm);
Func_Prefix PUNPCKLWD (VirtualMachine *posVm);
Func_Prefix PUNPCKLDQ (VirtualMachine *posVm);

Func_Prefix PUSH8 (VirtualMachine *posVm);
Func_Prefix PUSH16 (VirtualMachine *posVm);
Func_Prefix PUSH (VirtualMachine *posVm);
//Func_Prefix PUSHA (VirtualMachine *posVm);

Func_Prefix PUSHAD16 (VirtualMachine *posVm);
Func_Prefix PUSHAD (VirtualMachine *posVm);
Func_Prefix PUSHF (VirtualMachine *posVm);

Func_Prefix PUSHFD16 (VirtualMachine *posVm);
Func_Prefix PUSHFD (VirtualMachine *posVm);

Func_Prefix PXOR (VirtualMachine *posVm);

Func_Prefix RCL8 (VirtualMachine *posVm);
Func_Prefix RCL16 (VirtualMachine *posVm);
Func_Prefix RCL (VirtualMachine *posVm);

Func_Prefix RCR8 (VirtualMachine *posVm);
Func_Prefix RCR16 (VirtualMachine *posVm);
Func_Prefix RCR (VirtualMachine *posVm);

Func_Prefix ROL8 (VirtualMachine *posVm);
Func_Prefix ROL16 (VirtualMachine *posVm);
Func_Prefix ROL (VirtualMachine *posVm);

Func_Prefix ROR8 (VirtualMachine *posVm);
Func_Prefix ROR16 (VirtualMachine *posVm);
Func_Prefix ROR (VirtualMachine *posVm);

Func_Prefix RCPPS (VirtualMachine *posVm);
Func_Prefix RCPSS (VirtualMachine *posVm);
Func_Prefix RDMSR (VirtualMachine *posVm);
Func_Prefix RDPMC (VirtualMachine *posVm);
Func_Prefix RDTSC (VirtualMachine *posVm);
Func_Prefix REP (VirtualMachine *posVm);
Func_Prefix REPE (VirtualMachine *posVm);
Func_Prefix REPZ (VirtualMachine *posVm);
Func_Prefix REPNE (VirtualMachine *posVm);
Func_Prefix REPNZ (VirtualMachine *posVm);

Func_Prefix RETF (VirtualMachine *posVm);
Func_Prefix RET (VirtualMachine *posVm);

Func_Prefix RSM (VirtualMachine *posVm);
Func_Prefix RSQRTPS (VirtualMachine *posVm);
Func_Prefix RSQRTSS (VirtualMachine *posVm);
Func_Prefix SAHF (VirtualMachine *posVm);

Func_Prefix SAL8 (VirtualMachine *posVm);
Func_Prefix SAL16 (VirtualMachine *posVm);
Func_Prefix SAL (VirtualMachine *posVm);

Func_Prefix SAR8 (VirtualMachine *posVm);
Func_Prefix SAR16 (VirtualMachine *posVm);
Func_Prefix SAR (VirtualMachine *posVm);

Func_Prefix SHL8 (VirtualMachine *posVm);
Func_Prefix SHL16 (VirtualMachine *posVm);
Func_Prefix SHL (VirtualMachine *posVm);

Func_Prefix SHR8 (VirtualMachine *posVm);
Func_Prefix SHR16 (VirtualMachine *posVm);
Func_Prefix SHR (VirtualMachine *posVm);

Func_Prefix SBB8 (VirtualMachine *posVm);
Func_Prefix SBB16 (VirtualMachine *posVm);
Func_Prefix SBB (VirtualMachine *posVm);
Func_Prefix SCAS (VirtualMachine *posVm);

Func_Prefix SCASB16 (VirtualMachine *posVm);
Func_Prefix SCASB (VirtualMachine *posVm);

Func_Prefix SCASD16 (VirtualMachine *posVm);
Func_Prefix SCASD (VirtualMachine *posVm);
Func_Prefix SFENCE (VirtualMachine *posVm);
Func_Prefix SGDT (VirtualMachine *posVm);
Func_Prefix SIDT (VirtualMachine *posVm);

Func_Prefix SHLD16 (VirtualMachine *posVm);
Func_Prefix SHLD (VirtualMachine *posVm);

Func_Prefix SHRD16 (VirtualMachine *posVm);
Func_Prefix SHRD (VirtualMachine *posVm);

Func_Prefix SHUFPS (VirtualMachine *posVm);

Func_Prefix SLDT16 (VirtualMachine *posVm);
Func_Prefix SLDT (VirtualMachine *posVm);

Func_Prefix SMSW16 (VirtualMachine *posVm);
Func_Prefix SMSW (VirtualMachine *posVm);

Func_Prefix SQRTPS (VirtualMachine *posVm);
Func_Prefix SQRTSS (VirtualMachine *posVm);
Func_Prefix STC (VirtualMachine *posVm);
Func_Prefix STD (VirtualMachine *posVm);
Func_Prefix STI (VirtualMachine *posVm);
Func_Prefix STMXCSR (VirtualMachine *posVm);
Func_Prefix STOS (VirtualMachine *posVm);

Func_Prefix STOSB16 (VirtualMachine *posVm);
Func_Prefix STOSB (VirtualMachine *posVm);

Func_Prefix STOSD16 (VirtualMachine *posVm);
Func_Prefix STOSD (VirtualMachine *posVm);

Func_Prefix STR16 (VirtualMachine *posVm);
Func_Prefix STR (VirtualMachine *posVm);

Func_Prefix SUB8 (VirtualMachine *posVm);
Func_Prefix SUB16 (VirtualMachine *posVm);
Func_Prefix SUB (VirtualMachine *posVm);
Func_Prefix SUBPS (VirtualMachine *posVm);
Func_Prefix SUBSS (VirtualMachine *posVm);
Func_Prefix SYSENTER (VirtualMachine *posVm);
Func_Prefix SYSEXIT (VirtualMachine *posVm);

Func_Prefix TEST16 (VirtualMachine *posVm);
Func_Prefix TEST8 (VirtualMachine *posVm);
Func_Prefix TEST (VirtualMachine *posVm);

Func_Prefix UCOMISS (VirtualMachine *posVm);
Func_Prefix UD2 (VirtualMachine *posVm);
Func_Prefix UNPCKHPS (VirtualMachine *posVm);
Func_Prefix UNPCKLPS (VirtualMachine *posVm);

Func_Prefix VERR16 (VirtualMachine *posVm);
Func_Prefix VERR (VirtualMachine *posVm);
Func_Prefix VERW16 (VirtualMachine *posVm);
Func_Prefix VERW (VirtualMachine *posVm);

Func_Prefix WAIT (VirtualMachine *posVm);
Func_Prefix FWAIT (VirtualMachine *posVm);
Func_Prefix WBINVD (VirtualMachine *posVm);
Func_Prefix WRMSR (VirtualMachine *posVm);

Func_Prefix XADD8 (VirtualMachine *posVm);
Func_Prefix XADD16 (VirtualMachine *posVm);
Func_Prefix XADD (VirtualMachine *posVm);

Func_Prefix XCHG8 (VirtualMachine *posVm);
Func_Prefix XCHG16 (VirtualMachine *posVm);
Func_Prefix XCHG (VirtualMachine *posVm);

Func_Prefix XLAT (VirtualMachine *posVm);
Func_Prefix XLATB (VirtualMachine *posVm);
Func_Prefix XOR8 (VirtualMachine *posVm);
Func_Prefix XOR16 (VirtualMachine *posVm);
Func_Prefix XOR (VirtualMachine *posVm);
Func_Prefix XORPS (VirtualMachine *posVm);

// Manual Added
Func_Prefix CMOVO16 (VirtualMachine *posVm);
Func_Prefix CMOVO (VirtualMachine *posVm);

Func_Prefix CMOVNO16 (VirtualMachine *posVm);
Func_Prefix CMOVNO (VirtualMachine *posVm);

Func_Prefix CMOVC16 (VirtualMachine *posVm);
Func_Prefix CMOVC (VirtualMachine *posVm);

Func_Prefix CMOVAE16 (VirtualMachine *posVm);
Func_Prefix CMOVAE (VirtualMachine *posVm);

Func_Prefix CMOVZ16 (VirtualMachine *posVm);
Func_Prefix CMOVZ (VirtualMachine *posVm);

Func_Prefix CMOVNZ16 (VirtualMachine *posVm);
Func_Prefix CMOVNZ (VirtualMachine *posVm);

Func_Prefix CMOVNA16 (VirtualMachine *posVm);
Func_Prefix CMOVNA (VirtualMachine *posVm);

Func_Prefix CMOVNBE16 (VirtualMachine *posVm);
Func_Prefix CMOVNBE (VirtualMachine *posVm);

Func_Prefix CMOVS16 (VirtualMachine *posVm);
Func_Prefix CMOVS (VirtualMachine *posVm);

Func_Prefix CMOVNS16 (VirtualMachine *posVm);
Func_Prefix CMOVNS (VirtualMachine *posVm);

Func_Prefix CMOVPE16 (VirtualMachine *posVm);
Func_Prefix CMOVPE (VirtualMachine *posVm);

Func_Prefix CMOVPO16 (VirtualMachine *posVm);
Func_Prefix CMOVPO (VirtualMachine *posVm);

Func_Prefix CMOVNGE16 (VirtualMachine *posVm);
Func_Prefix CMOVNGE (VirtualMachine *posVm);

Func_Prefix CMOVNL16 (VirtualMachine *posVm);
Func_Prefix CMOVNL (VirtualMachine *posVm);

Func_Prefix CMOVNG16 (VirtualMachine *posVm);
Func_Prefix CMOVNG (VirtualMachine *posVm);

Func_Prefix CMOVNLE16 (VirtualMachine *posVm);
Func_Prefix CMOVNLE (VirtualMachine *posVm);


Func_Prefix FCMOVB (VirtualMachine *posVm);
Func_Prefix FCMOVE (VirtualMachine *posVm);
Func_Prefix FCMOVBE (VirtualMachine *posVm);
Func_Prefix FCMOVU (VirtualMachine *posVm);
Func_Prefix FCMOVNB (VirtualMachine *posVm);
Func_Prefix FCMOVNE (VirtualMachine *posVm);
Func_Prefix FCMOVNBE (VirtualMachine *posVm);
Func_Prefix FCMOVNU (VirtualMachine *posVm);

Func_Prefix JO (VirtualMachine *posVm);
Func_Prefix JNO (VirtualMachine *posVm);
Func_Prefix JC (VirtualMachine *posVm);
Func_Prefix JAE (VirtualMachine *posVm);
Func_Prefix JZ (VirtualMachine *posVm);
Func_Prefix JNZ (VirtualMachine *posVm);
Func_Prefix JNA (VirtualMachine *posVm);
Func_Prefix JNBE (VirtualMachine *posVm);
Func_Prefix JS (VirtualMachine *posVm);
Func_Prefix JNS (VirtualMachine *posVm);
Func_Prefix JPE (VirtualMachine *posVm);
Func_Prefix JPO (VirtualMachine *posVm);
Func_Prefix JNGE (VirtualMachine *posVm);
Func_Prefix JNL (VirtualMachine *posVm);
Func_Prefix JNG (VirtualMachine *posVm);
Func_Prefix JNLE (VirtualMachine *posVm);
Func_Prefix JB (VirtualMachine *posVm);
Func_Prefix JNB (VirtualMachine *posVm);
Func_Prefix JECXZ16(VirtualMachine *posVm);
Func_Prefix JECXZ(VirtualMachine *posVm);

Func_Prefix LOOPNZ (VirtualMachine *posVm);
Func_Prefix LOOPZ (VirtualMachine *posVm);

Func_Prefix SETO8 (VirtualMachine *posVm);
Func_Prefix SETNO8 (VirtualMachine *posVm);
Func_Prefix SETB8 (VirtualMachine *posVm);
Func_Prefix SETNB8 (VirtualMachine *posVm);
Func_Prefix SETZ8 (VirtualMachine *posVm);
Func_Prefix SETNZ8 (VirtualMachine *posVm);
Func_Prefix SETNA8 (VirtualMachine *posVm);
Func_Prefix SETNBE8 (VirtualMachine *posVm);
Func_Prefix SETS8 (VirtualMachine *posVm);
Func_Prefix SETNS8 (VirtualMachine *posVm);
Func_Prefix SETPE8 (VirtualMachine *posVm);
Func_Prefix SETPO8 (VirtualMachine *posVm);
Func_Prefix SETNGE8 (VirtualMachine *posVm);
Func_Prefix SETNL8 (VirtualMachine *posVm);
Func_Prefix SETNG8 (VirtualMachine *posVm);
Func_Prefix SETNLE8 (VirtualMachine *posVm);

Func_Prefix CMPPS (VirtualMachine *posVm);

Func_Prefix SetAlc (VirtualMachine *posVm);


Func_Prefix PREFETCHT08 (VirtualMachine *posVm);
Func_Prefix PREFETCHT18 (VirtualMachine *posVm);
Func_Prefix PREFETCHT28 (VirtualMachine *posVm);
Func_Prefix PREFETCHNTA8 (VirtualMachine *posVm);


Func_Prefix	PreMov_String (VirtualMachine *posVm, UINT8	nChunckSize);
Func_Prefix	Mov_String (VirtualMachine *posVm, UINT32	nSizeOfBuffer);
#endif