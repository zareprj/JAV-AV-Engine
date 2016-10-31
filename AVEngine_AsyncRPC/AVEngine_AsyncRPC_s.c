

/* this ALWAYS GENERATED file contains the RPC server stubs */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Fri Apr 11 09:29:20 2014
 */
/* Compiler settings for ..\AVEngine_AsyncRPC\AVEngine_AsyncRPC.Idl, ..\AVEngine_AsyncRPC\AVEngine_AsyncRPC.Acf:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#if !defined(_M_IA64) && !defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#include <string.h>
#include "AVEngine_AsyncRPC_h.h"

#define TYPE_FORMAT_STRING_SIZE   169                               
#define PROC_FORMAT_STRING_SIZE   553                               
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _AVEngine_AsyncRPC_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } AVEngine_AsyncRPC_MIDL_TYPE_FORMAT_STRING;

typedef struct _AVEngine_AsyncRPC_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } AVEngine_AsyncRPC_MIDL_PROC_FORMAT_STRING;

typedef struct _AVEngine_AsyncRPC_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } AVEngine_AsyncRPC_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};

extern const AVEngine_AsyncRPC_MIDL_TYPE_FORMAT_STRING AVEngine_AsyncRPC__MIDL_TypeFormatString;
extern const AVEngine_AsyncRPC_MIDL_PROC_FORMAT_STRING AVEngine_AsyncRPC__MIDL_ProcFormatString;
extern const AVEngine_AsyncRPC_MIDL_EXPR_FORMAT_STRING AVEngine_AsyncRPC__MIDL_ExprFormatString;

/* Standard interface: AVEngine_AsyncRPC, ver. 1.0,
   GUID={0x7f6c4340,0xeb67,0x11d1,{0xb9,0xd7,0x00,0xc0,0x4f,0xad,0x9a,0x3b}} */


extern const MIDL_SERVER_INFO AVEngine_AsyncRPC_ServerInfo;

extern const RPC_DISPATCH_TABLE AVEngine_AsyncRPC_v1_0_DispatchTable;

static const RPC_SERVER_INTERFACE AVEngine_AsyncRPC___RpcServerInterface =
    {
    sizeof(RPC_SERVER_INTERFACE),
    {{0x7f6c4340,0xeb67,0x11d1,{0xb9,0xd7,0x00,0xc0,0x4f,0xad,0x9a,0x3b}},{1,0}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    (RPC_DISPATCH_TABLE*)&AVEngine_AsyncRPC_v1_0_DispatchTable,
    0,
    0,
    0,
    &AVEngine_AsyncRPC_ServerInfo,
    0x04000000
    };
RPC_IF_HANDLE AVEngine_AsyncRPC_v1_0_s_ifspec = (RPC_IF_HANDLE)& AVEngine_AsyncRPC___RpcServerInterface;

extern const MIDL_STUB_DESC AVEngine_AsyncRPC_StubDesc;


#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need Windows 2000 or later to run this stub because it uses these features:
#error   [async] attribute, /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const AVEngine_AsyncRPC_MIDL_PROC_FORMAT_STRING AVEngine_AsyncRPC__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure AsyncStartScan */

			0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x0 ),	/* 0 */
/*  8 */	NdrFcShort( 0x24 ),	/* x86 Stack size/offset = 36 */
/* 10 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 12 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 14 */	NdrFcShort( 0x0 ),	/* 0 */
/* 16 */	NdrFcShort( 0x1a ),	/* 26 */
/* 18 */	0xc2,		/* Oi2 Flags:  clt must size, has ext, has async handle */
			0x2,		/* 2 */
/* 20 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */
/* 24 */	NdrFcShort( 0x0 ),	/* 0 */
/* 26 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hBinding */

/* 28 */	NdrFcShort( 0x8b ),	/* Flags:  must size, must free, in, by val, */
/* 30 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 32 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */

	/* Parameter _ScanConfig */

/* 34 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 36 */	NdrFcShort( 0x20 ),	/* x86 Stack size/offset = 32 */
/* 38 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Procedure SyncGetScanEndJobReport */


	/* Parameter _eOperationResualtState */

/* 40 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 42 */	NdrFcLong( 0x0 ),	/* 0 */
/* 46 */	NdrFcShort( 0x1 ),	/* 1 */
/* 48 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 50 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 52 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 54 */	NdrFcShort( 0x0 ),	/* 0 */
/* 56 */	NdrFcShort( 0x0 ),	/* 0 */
/* 58 */	0x41,		/* Oi2 Flags:  srv must size, has ext, */
			0x1,		/* 1 */
/* 60 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 62 */	NdrFcShort( 0x0 ),	/* 0 */
/* 64 */	NdrFcShort( 0x0 ),	/* 0 */
/* 66 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hBinding */

/* 68 */	NdrFcShort( 0x113 ),	/* Flags:  must size, must free, out, simple ref, */
/* 70 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 72 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Procedure SyncPause */


	/* Parameter _scanEndJobReport */

/* 74 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 76 */	NdrFcLong( 0x0 ),	/* 0 */
/* 80 */	NdrFcShort( 0x2 ),	/* 2 */
/* 82 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 84 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 86 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 88 */	NdrFcShort( 0x0 ),	/* 0 */
/* 90 */	NdrFcShort( 0x1a ),	/* 26 */
/* 92 */	0x40,		/* Oi2 Flags:  has ext, */
			0x1,		/* 1 */
/* 94 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 96 */	NdrFcShort( 0x0 ),	/* 0 */
/* 98 */	NdrFcShort( 0x0 ),	/* 0 */
/* 100 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hBinding */

/* 102 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 104 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 106 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Procedure SyncContinue */


	/* Parameter _eOperationResualtState */

/* 108 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 110 */	NdrFcLong( 0x0 ),	/* 0 */
/* 114 */	NdrFcShort( 0x3 ),	/* 3 */
/* 116 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 118 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 120 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 122 */	NdrFcShort( 0x0 ),	/* 0 */
/* 124 */	NdrFcShort( 0x1a ),	/* 26 */
/* 126 */	0x40,		/* Oi2 Flags:  has ext, */
			0x1,		/* 1 */
/* 128 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 130 */	NdrFcShort( 0x0 ),	/* 0 */
/* 132 */	NdrFcShort( 0x0 ),	/* 0 */
/* 134 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hBinding */

/* 136 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 138 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 140 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Procedure AsyncStopScan */


	/* Parameter _eOperationResualtState */

/* 142 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 144 */	NdrFcLong( 0x0 ),	/* 0 */
/* 148 */	NdrFcShort( 0x4 ),	/* 4 */
/* 150 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 152 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 154 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 156 */	NdrFcShort( 0x0 ),	/* 0 */
/* 158 */	NdrFcShort( 0x1a ),	/* 26 */
/* 160 */	0xc0,		/* Oi2 Flags:  has ext, has async handle */
			0x1,		/* 1 */
/* 162 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 164 */	NdrFcShort( 0x0 ),	/* 0 */
/* 166 */	NdrFcShort( 0x0 ),	/* 0 */
/* 168 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hBinding */

/* 170 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 172 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 174 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Procedure AsyncSaveAndExit */


	/* Parameter _eOperationResualtState */

/* 176 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 178 */	NdrFcLong( 0x0 ),	/* 0 */
/* 182 */	NdrFcShort( 0x5 ),	/* 5 */
/* 184 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 186 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 188 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 190 */	NdrFcShort( 0x0 ),	/* 0 */
/* 192 */	NdrFcShort( 0x1a ),	/* 26 */
/* 194 */	0xc0,		/* Oi2 Flags:  has ext, has async handle */
			0x1,		/* 1 */
/* 196 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 198 */	NdrFcShort( 0x0 ),	/* 0 */
/* 200 */	NdrFcShort( 0x0 ),	/* 0 */
/* 202 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hBinding */

/* 204 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 206 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 208 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Procedure AsyncGetStatusMessage */


	/* Parameter _eOperationResualtState */

/* 210 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 212 */	NdrFcLong( 0x0 ),	/* 0 */
/* 216 */	NdrFcShort( 0x6 ),	/* 6 */
/* 218 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 220 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 222 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 224 */	NdrFcShort( 0x0 ),	/* 0 */
/* 226 */	NdrFcShort( 0x83c ),	/* 2108 */
/* 228 */	0xc0,		/* Oi2 Flags:  has ext, has async handle */
			0x1,		/* 1 */
/* 230 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 232 */	NdrFcShort( 0x0 ),	/* 0 */
/* 234 */	NdrFcShort( 0x0 ),	/* 0 */
/* 236 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hBinding */

/* 238 */	NdrFcShort( 0x112 ),	/* Flags:  must free, out, simple ref, */
/* 240 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 242 */	NdrFcShort( 0x4e ),	/* Type Offset=78 */

	/* Procedure AsyncGetNextMessageScan */


	/* Parameter _StatusMessage */

/* 244 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 246 */	NdrFcLong( 0x0 ),	/* 0 */
/* 250 */	NdrFcShort( 0x7 ),	/* 7 */
/* 252 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 254 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 256 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 258 */	NdrFcShort( 0x0 ),	/* 0 */
/* 260 */	NdrFcShort( 0x834 ),	/* 2100 */
/* 262 */	0xc0,		/* Oi2 Flags:  has ext, has async handle */
			0x1,		/* 1 */
/* 264 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 266 */	NdrFcShort( 0x0 ),	/* 0 */
/* 268 */	NdrFcShort( 0x0 ),	/* 0 */
/* 270 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hBinding */

/* 272 */	NdrFcShort( 0x112 ),	/* Flags:  must free, out, simple ref, */
/* 274 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 276 */	NdrFcShort( 0x5e ),	/* Type Offset=94 */

	/* Procedure AsyncStartQuarantine */


	/* Parameter _ScanMessage */

/* 278 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 280 */	NdrFcLong( 0x0 ),	/* 0 */
/* 284 */	NdrFcShort( 0x8 ),	/* 8 */
/* 286 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 288 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 290 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 292 */	NdrFcShort( 0x0 ),	/* 0 */
/* 294 */	NdrFcShort( 0x1a ),	/* 26 */
/* 296 */	0xc0,		/* Oi2 Flags:  has ext, has async handle */
			0x1,		/* 1 */
/* 298 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 300 */	NdrFcShort( 0x0 ),	/* 0 */
/* 302 */	NdrFcShort( 0x0 ),	/* 0 */
/* 304 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hBinding */

/* 306 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 308 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 310 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Procedure AsyncGetQuarantineCount */


	/* Parameter _eOperationResualtState */

/* 312 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 314 */	NdrFcLong( 0x0 ),	/* 0 */
/* 318 */	NdrFcShort( 0x9 ),	/* 9 */
/* 320 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 322 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 324 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 326 */	NdrFcShort( 0x0 ),	/* 0 */
/* 328 */	NdrFcShort( 0x1c ),	/* 28 */
/* 330 */	0xc0,		/* Oi2 Flags:  has ext, has async handle */
			0x1,		/* 1 */
/* 332 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 334 */	NdrFcShort( 0x0 ),	/* 0 */
/* 336 */	NdrFcShort( 0x0 ),	/* 0 */
/* 338 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hBinding */

/* 340 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 342 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 344 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AsyncMoveFileToQuarantine */


	/* Parameter pu32Count */

/* 346 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 348 */	NdrFcLong( 0x0 ),	/* 0 */
/* 352 */	NdrFcShort( 0xa ),	/* 10 */
/* 354 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 356 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 358 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 360 */	NdrFcShort( 0x1068 ),	/* 4200 */
/* 362 */	NdrFcShort( 0x1a ),	/* 26 */
/* 364 */	0xc0,		/* Oi2 Flags:  has ext, has async handle */
			0x3,		/* 3 */
/* 366 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 368 */	NdrFcShort( 0x0 ),	/* 0 */
/* 370 */	NdrFcShort( 0x0 ),	/* 0 */
/* 372 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hBinding */

/* 374 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
/* 376 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 378 */	NdrFcShort( 0x5e ),	/* Type Offset=94 */

	/* Parameter posFilePath */

/* 380 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
/* 382 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 384 */	NdrFcShort( 0x5e ),	/* Type Offset=94 */

	/* Parameter posReason */

/* 386 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 388 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 390 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Procedure AsyncGetQuarantinedFileInfo */


	/* Parameter _eOperationResualtState */

/* 392 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 394 */	NdrFcLong( 0x0 ),	/* 0 */
/* 398 */	NdrFcShort( 0xb ),	/* 11 */
/* 400 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 402 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 404 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 406 */	NdrFcShort( 0x8c0 ),	/* 2240 */
/* 408 */	NdrFcShort( 0x1a ),	/* 26 */
/* 410 */	0xc0,		/* Oi2 Flags:  has ext, has async handle */
			0x3,		/* 3 */
/* 412 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 414 */	NdrFcShort( 0x0 ),	/* 0 */
/* 416 */	NdrFcShort( 0x0 ),	/* 0 */
/* 418 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hBinding */

/* 420 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 422 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 424 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pu32Index */

/* 426 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
/* 428 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 430 */	NdrFcShort( 0x8e ),	/* Type Offset=142 */

	/* Parameter posHQF */

/* 432 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 434 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 436 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Procedure AsyncRemoveFileFromQuarantine */


	/* Parameter _eOperationResualtState */

/* 438 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 440 */	NdrFcLong( 0x0 ),	/* 0 */
/* 444 */	NdrFcShort( 0xc ),	/* 12 */
/* 446 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 448 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 450 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 452 */	NdrFcShort( 0x1c ),	/* 28 */
/* 454 */	NdrFcShort( 0x1a ),	/* 26 */
/* 456 */	0xc0,		/* Oi2 Flags:  has ext, has async handle */
			0x2,		/* 2 */
/* 458 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 460 */	NdrFcShort( 0x0 ),	/* 0 */
/* 462 */	NdrFcShort( 0x0 ),	/* 0 */
/* 464 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hBinding */

/* 466 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 468 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 470 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter _eOperationResualtState */

/* 472 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 474 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 476 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure AsyncRestore */


	/* Parameter pu32Index */

/* 478 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 480 */	NdrFcLong( 0x0 ),	/* 0 */
/* 484 */	NdrFcShort( 0xd ),	/* 13 */
/* 486 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 488 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 490 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 492 */	NdrFcShort( 0x850 ),	/* 2128 */
/* 494 */	NdrFcShort( 0x1a ),	/* 26 */
/* 496 */	0xc0,		/* Oi2 Flags:  has ext, has async handle */
			0x3,		/* 3 */
/* 498 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 500 */	NdrFcShort( 0x0 ),	/* 0 */
/* 502 */	NdrFcShort( 0x0 ),	/* 0 */
/* 504 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter hBinding */

/* 506 */	NdrFcShort( 0x2010 ),	/* Flags:  out, srv alloc size=8 */
/* 508 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 510 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Parameter _eOperationResualtState */

/* 512 */	NdrFcShort( 0x148 ),	/* Flags:  in, base type, simple ref, */
/* 514 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 516 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pu32Index */

/* 518 */	NdrFcShort( 0x10a ),	/* Flags:  must free, in, simple ref, */
/* 520 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 522 */	NdrFcShort( 0x5e ),	/* Type Offset=94 */

	/* Procedure Shutdown */


	/* Parameter pszPathToExtract */

/* 524 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 526 */	NdrFcLong( 0x0 ),	/* 0 */
/* 530 */	NdrFcShort( 0xe ),	/* 14 */
/* 532 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 534 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 536 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 538 */	NdrFcShort( 0x0 ),	/* 0 */
/* 540 */	NdrFcShort( 0x0 ),	/* 0 */
/* 542 */	0x40,		/* Oi2 Flags:  has ext, */
			0x0,		/* 0 */
/* 544 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 546 */	NdrFcShort( 0x0 ),	/* 0 */
/* 548 */	NdrFcShort( 0x0 ),	/* 0 */
/* 550 */	NdrFcShort( 0x0 ),	/* 0 */

			0x0
        }
    };

static const AVEngine_AsyncRPC_MIDL_TYPE_FORMAT_STRING AVEngine_AsyncRPC__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/*  4 */	NdrFcShort( 0x18 ),	/* 24 */
/*  6 */	NdrFcShort( 0x0 ),	/* 0 */
/*  8 */	NdrFcShort( 0x10 ),	/* Offset= 16 (24) */
/* 10 */	0x2,		/* FC_CHAR */
			0x2,		/* FC_CHAR */
/* 12 */	0x2,		/* FC_CHAR */
			0x2,		/* FC_CHAR */
/* 14 */	0x2,		/* FC_CHAR */
			0x2,		/* FC_CHAR */
/* 16 */	0x2,		/* FC_CHAR */
			0x3d,		/* FC_STRUCTPAD1 */
/* 18 */	0xd,		/* FC_ENUM16 */
			0xd,		/* FC_ENUM16 */
/* 20 */	0x36,		/* FC_POINTER */
			0x36,		/* FC_POINTER */
/* 22 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 24 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 26 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 28 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 30 */	
			0x25,		/* FC_C_WSTRING */
			0x5c,		/* FC_PAD */
/* 32 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 34 */	0xd,		/* FC_ENUM16 */
			0x5c,		/* FC_PAD */
/* 36 */	
			0x11, 0x0,	/* FC_RP */
/* 38 */	NdrFcShort( 0x8 ),	/* Offset= 8 (46) */
/* 40 */	
			0x1d,		/* FC_SMFARRAY */
			0x1,		/* 1 */
/* 42 */	NdrFcShort( 0x800 ),	/* 2048 */
/* 44 */	0x5,		/* FC_WCHAR */
			0x5b,		/* FC_END */
/* 46 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 48 */	NdrFcShort( 0x1018 ),	/* 4120 */
/* 50 */	NdrFcShort( 0x0 ),	/* 0 */
/* 52 */	NdrFcShort( 0x0 ),	/* Offset= 0 (52) */
/* 54 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 56 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (40) */
/* 58 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 60 */	NdrFcShort( 0xffec ),	/* Offset= -20 (40) */
/* 62 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 64 */	0x3e,		/* FC_STRUCTPAD2 */
			0x8,		/* FC_LONG */
/* 66 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 68 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 70 */	0x6,		/* FC_SHORT */
			0x3e,		/* FC_STRUCTPAD2 */
/* 72 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 74 */	
			0x11, 0x0,	/* FC_RP */
/* 76 */	NdrFcShort( 0x2 ),	/* Offset= 2 (78) */
/* 78 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 80 */	NdrFcShort( 0x808 ),	/* 2056 */
/* 82 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 84 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 86 */	NdrFcShort( 0xffd2 ),	/* Offset= -46 (40) */
/* 88 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 90 */	
			0x11, 0x0,	/* FC_RP */
/* 92 */	NdrFcShort( 0x2 ),	/* Offset= 2 (94) */
/* 94 */	
			0x15,		/* FC_STRUCT */
			0x1,		/* 1 */
/* 96 */	NdrFcShort( 0x800 ),	/* 2048 */
/* 98 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 100 */	NdrFcShort( 0xffc4 ),	/* Offset= -60 (40) */
/* 102 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 104 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 106 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 108 */	
			0x11, 0x8,	/* FC_RP [simple_pointer] */
/* 110 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 112 */	
			0x11, 0x0,	/* FC_RP */
/* 114 */	NdrFcShort( 0x1c ),	/* Offset= 28 (142) */
/* 116 */	
			0x15,		/* FC_STRUCT */
			0x1,		/* 1 */
/* 118 */	NdrFcShort( 0x10 ),	/* 16 */
/* 120 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 122 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 124 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 126 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 128 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 130 */	
			0x1d,		/* FC_SMFARRAY */
			0x1,		/* 1 */
/* 132 */	NdrFcShort( 0x208 ),	/* 520 */
/* 134 */	0x5,		/* FC_WCHAR */
			0x5b,		/* FC_END */
/* 136 */	
			0x1d,		/* FC_SMFARRAY */
			0x1,		/* 1 */
/* 138 */	NdrFcShort( 0x410 ),	/* 1040 */
/* 140 */	0x5,		/* FC_WCHAR */
			0x5b,		/* FC_END */
/* 142 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 144 */	NdrFcShort( 0x840 ),	/* 2112 */
/* 146 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 148 */	NdrFcShort( 0xffe0 ),	/* Offset= -32 (116) */
/* 150 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 152 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 154 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 156 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (130) */
/* 158 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 160 */	NdrFcShort( 0xffe8 ),	/* Offset= -24 (136) */
/* 162 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 164 */	NdrFcShort( 0xffde ),	/* Offset= -34 (130) */
/* 166 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */

			0x0
        }
    };

static const unsigned short AVEngine_AsyncRPC_FormatStringOffsetTable[] =
    {
    0,
    40,
    74,
    108,
    142,
    176,
    210,
    244,
    278,
    312,
    346,
    392,
    438,
    478,
    524
    };


static const MIDL_STUB_DESC AVEngine_AsyncRPC_StubDesc = 
    {
    (void *)& AVEngine_AsyncRPC___RpcServerInterface,
    MIDL_user_allocate,
    MIDL_user_free,
    0,
    0,
    0,
    0,
    0,
    AVEngine_AsyncRPC__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x700022b, /* MIDL Version 7.0.555 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

static const RPC_DISPATCH_FUNCTION AVEngine_AsyncRPC_table[] =
    {
    NdrAsyncServerCall,
    NdrServerCall2,
    NdrServerCall2,
    NdrServerCall2,
    NdrAsyncServerCall,
    NdrAsyncServerCall,
    NdrAsyncServerCall,
    NdrAsyncServerCall,
    NdrAsyncServerCall,
    NdrAsyncServerCall,
    NdrAsyncServerCall,
    NdrAsyncServerCall,
    NdrAsyncServerCall,
    NdrAsyncServerCall,
    NdrServerCall2,
    0
    };
static const RPC_DISPATCH_TABLE AVEngine_AsyncRPC_v1_0_DispatchTable = 
    {
    15,
    (RPC_DISPATCH_FUNCTION*)AVEngine_AsyncRPC_table
    };

static const SERVER_ROUTINE AVEngine_AsyncRPC_ServerRoutineTable[] = 
    {
    (SERVER_ROUTINE)AsyncStartScan,
    (SERVER_ROUTINE)SyncGetScanEndJobReport,
    (SERVER_ROUTINE)SyncPause,
    (SERVER_ROUTINE)SyncContinue,
    (SERVER_ROUTINE)AsyncStopScan,
    (SERVER_ROUTINE)AsyncSaveAndExit,
    (SERVER_ROUTINE)AsyncGetStatusMessage,
    (SERVER_ROUTINE)AsyncGetNextMessageScan,
    (SERVER_ROUTINE)AsyncStartQuarantine,
    (SERVER_ROUTINE)AsyncGetQuarantineCount,
    (SERVER_ROUTINE)AsyncMoveFileToQuarantine,
    (SERVER_ROUTINE)AsyncGetQuarantinedFileInfo,
    (SERVER_ROUTINE)AsyncRemoveFileFromQuarantine,
    (SERVER_ROUTINE)AsyncRestore,
    (SERVER_ROUTINE)Shutdown
    };

static const MIDL_SERVER_INFO AVEngine_AsyncRPC_ServerInfo = 
    {
    &AVEngine_AsyncRPC_StubDesc,
    AVEngine_AsyncRPC_ServerRoutineTable,
    AVEngine_AsyncRPC__MIDL_ProcFormatString.Format,
    AVEngine_AsyncRPC_FormatStringOffsetTable,
    0,
    0,
    0,
    0};
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

