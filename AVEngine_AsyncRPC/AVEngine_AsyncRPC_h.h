

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __AVEngine_AsyncRPC_h_h__
#define __AVEngine_AsyncRPC_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __AVEngine_AsyncRPC_INTERFACE_DEFINED__
#define __AVEngine_AsyncRPC_INTERFACE_DEFINED__

/* interface AVEngine_AsyncRPC */
/* [unique][version][uuid] */ 

typedef struct _SYSTEMTIME_
    {
    unsigned short wYear;
    unsigned short wMonth;
    unsigned short wDayOfWeek;
    unsigned short wDay;
    unsigned short wHour;
    unsigned short wMinute;
    unsigned short wSecond;
    unsigned short wMilliseconds;
    } 	SYSTEMTIME_;

#define	DEFAULT_ASYNC_DELAY	( 20 )

#define	DEFAULT_PROTOCOL_SEQUENCE	( L"ncalrpc" )

#define	DEFAULT_ENDPOINT	( L"8765" )

typedef /* [public][public][public] */ 
enum __MIDL_AVEngine_AsyncRPC_0001
    {	JustMemory	= 0,
	MemoryAndFile	= ( JustMemory + 1 ) ,
	JustFile	= ( MemoryAndFile + 1 ) 
    } 	eScanPlace;

typedef /* [public][public][public] */ 
enum __MIDL_AVEngine_AsyncRPC_0002
    {	NoClean	= 0,
	Clean	= ( NoClean + 1 ) ,
	Quarantine	= ( Clean + 1 ) ,
	AskUsr	= ( Quarantine + 1 ) 
    } 	eCleanOption;

typedef /* [public][public][public][public][public][public][public][public][public][public][public] */ 
enum __MIDL_AVEngine_AsyncRPC_0003
    {	successfull	= 0,
	fail	= ( successfull + 1 ) 
    } 	eOperationResualtState;

typedef struct _ScanConfig_
    {
    unsigned char ZipFile;
    unsigned char RarFile;
    unsigned char ExecuteableOnly;
    unsigned char MemDll;
    unsigned char MemProcess;
    unsigned char MemService;
    unsigned char JustFileOnly;
    eCleanOption oeCleanOption;
    eScanPlace oeScanPlace;
    const wchar_t *pwszFilterString;
    const wchar_t *pathToScan;
    } 	ScanConfig;

typedef struct _QuarantineFileStructure
    {
    SYSTEMTIME_ osTime;
    unsigned int u32FileIndex;
    unsigned int u32NameSize;
    unsigned int u32PathSize;
    unsigned int u32ReasonSize;
    wchar_t szFileName[ 260 ];
    wchar_t szFullPath[ 520 ];
    wchar_t szReason[ 260 ];
    } 	QuarantineFileStructure;

typedef struct _ScanEndJobReport_
    {
    wchar_t headComment[ 1024 ];
    wchar_t tailComment[ 1024 ];
    unsigned int numberOftotalScan;
    unsigned short numberOfFailedToScan;
    unsigned int numberOfArchiveFile;
    unsigned short numberOfTotalDetection;
    unsigned short numberOfInfected;
    unsigned short numberOfDeleted;
    unsigned short numberOfCleaned;
    unsigned short numberOfQuaratine;
    } 	ScanEndJobReport;

typedef struct _StatusMessage_
    {
    unsigned int b_havemessage;
    unsigned int precentToComplete;
    wchar_t currentScanPath[ 1024 ];
    } 	StatusMessage;

typedef struct _ScanMessage_
    {
    wchar_t Message[ 1024 ];
    } 	ScanMessage;

typedef struct _ScanMessage_ BigString;

/* [async] */ void  AsyncStartScan( 
    /* [in] */ PRPC_ASYNC_STATE AsyncStartScan_AsyncHandle,
    handle_t hBinding,
    /* [in] */ ScanConfig _ScanConfig,
    /* [out] */ eOperationResualtState *_eOperationResualtState);

void SyncGetScanEndJobReport( 
    handle_t hBinding,
    /* [out] */ ScanEndJobReport *_scanEndJobReport);

void SyncPause( 
    handle_t hBinding,
    /* [out] */ eOperationResualtState *_eOperationResualtState);

void SyncContinue( 
    handle_t hBinding,
    /* [out] */ eOperationResualtState *_eOperationResualtState);

/* [async] */ void  AsyncStopScan( 
    /* [in] */ PRPC_ASYNC_STATE AsyncStopScan_AsyncHandle,
    handle_t hBinding,
    /* [out] */ eOperationResualtState *_eOperationResualtState);

/* [async] */ void  AsyncSaveAndExit( 
    /* [in] */ PRPC_ASYNC_STATE AsyncSaveAndExit_AsyncHandle,
    handle_t hBinding,
    /* [out] */ eOperationResualtState *_eOperationResualtState);

/* [async] */ void  AsyncGetStatusMessage( 
    /* [in] */ PRPC_ASYNC_STATE AsyncGetStatusMessage_AsyncHandle,
    handle_t hBinding,
    /* [out] */ StatusMessage *_StatusMessage);

/* [async] */ void  AsyncGetNextMessageScan( 
    /* [in] */ PRPC_ASYNC_STATE AsyncGetNextMessageScan_AsyncHandle,
    handle_t hBinding,
    /* [out] */ ScanMessage *_ScanMessage);

/* [async] */ void  AsyncStartQuarantine( 
    /* [in] */ PRPC_ASYNC_STATE AsyncStartQuarantine_AsyncHandle,
    handle_t hBinding,
    /* [out] */ eOperationResualtState *_eOperationResualtState);

/* [async] */ void  AsyncGetQuarantineCount( 
    /* [in] */ PRPC_ASYNC_STATE AsyncGetQuarantineCount_AsyncHandle,
    handle_t hBinding,
    /* [out] */ unsigned int *pu32Count);

/* [async] */ void  AsyncMoveFileToQuarantine( 
    /* [in] */ PRPC_ASYNC_STATE AsyncMoveFileToQuarantine_AsyncHandle,
    handle_t hBinding,
    /* [in] */ BigString *posFilePath,
    /* [in] */ BigString *posReason,
    /* [out] */ eOperationResualtState *_eOperationResualtState);

/* [async] */ void  AsyncGetQuarantinedFileInfo( 
    /* [in] */ PRPC_ASYNC_STATE AsyncGetQuarantinedFileInfo_AsyncHandle,
    handle_t hBinding,
    /* [in] */ unsigned int *pu32Index,
    /* [in] */ QuarantineFileStructure *posHQF,
    /* [out] */ eOperationResualtState *_eOperationResualtState);

/* [async] */ void  AsyncRemoveFileFromQuarantine( 
    /* [in] */ PRPC_ASYNC_STATE AsyncRemoveFileFromQuarantine_AsyncHandle,
    handle_t hBinding,
    /* [out] */ eOperationResualtState *_eOperationResualtState,
    /* [in] */ unsigned int *pu32Index);

/* [async] */ void  AsyncRestore( 
    /* [in] */ PRPC_ASYNC_STATE AsyncRestore_AsyncHandle,
    handle_t hBinding,
    /* [out] */ eOperationResualtState *_eOperationResualtState,
    /* [in] */ unsigned int *pu32Index,
    /* [in] */ BigString *pszPathToExtract);

void Shutdown( 
    handle_t hBinding);



extern RPC_IF_HANDLE AVEngine_AsyncRPC_v1_0_c_ifspec;
extern RPC_IF_HANDLE AVEngine_AsyncRPC_v1_0_s_ifspec;
#endif /* __AVEngine_AsyncRPC_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


