#include "Ntifs.h"
#include "ScanImp.h"
#include "SMBuffer.h"
#include "FileInformation.h"
#include "log.h"
#include "IFunc.h"
#include "FileApiBYIRP.h"
#include "SbScaner.h"
#include "strsafe.h"
#include "SMFile.h"
#include "iomonitor.h" 
#include "VirtualMachine.h"
#include "FileIoStruct.h"


#define __DEMOVERSION__

//__inline PSbScaner GetBufferFromPool(IN  PFileHandle FH) ;
__inline void RealseBuffer(PSMBuffer Buf) ;
#ifdef ALLOC_PRAGMA
	#pragma alloc_text( PAGE , ScanFile )
//	#pragma alloc_text( PAGE , GetBufferFromPool ) 
	#pragma alloc_text( PAGE , RealseBuffer ) 
	#pragma alloc_text( PAGE , DeleteVirus )
#endif


//NTSTATUS ChechStuxtNet( IN PJBuffer ImpBuffer);

/*NTSTATUS ScanFile( IN  PFileHandle FH ) 
{
	PJBuffer Buffer = NULL ;
	NTSTATUS status = STATUS_UNSUCCESSFUL ;
	FileInformation  FileInfo = {0} ;
	LARGE_INTEGER OffsetZero = {0} ;
	LONG BufferNum ;
	PAGED_CODE();

	status = KeWaitForSingleObject ( &GV.BufferSemaphore , Executive, KernelMode, FALSE, NULL);
	if ( !NT_SUCCESS(status) ) 
	{
		PutLog(L"can not wait for single object" , status)	;
		return status ;
	}

	BufferNum = InterlockedIncrement(&GV.CurrentBufferAcsess) ;

	ASSERT ( BufferNum - 1 < COUNTFILEJBUFFER ) ;

	Buffer = GV.BufferPool[BufferNum -1 ] ;

	status = SetBufferFile(Buffer , FH ) ;
	if ( !NT_SUCCESS(status) ) 
	{
		InterlockedDecrement( &GV.CurrentBufferAcsess ) ;
		KeReleaseSemaphore ( &GV.BufferSemaphore , IO_NO_INCREMENT , 1, FALSE);

		PutLog(L"can not Set File to buffer" , status)	;
		return status ;
	}

	status = SetFile( &FileInfo, Buffer );
	if ( !NT_SUCCESS (status) )
	{
		ResetInformation(&FileInfo);
		InterlockedDecrement( &GV.CurrentBufferAcsess ) ;
		KeReleaseSemaphore ( &GV.BufferSemaphore , IO_NO_INCREMENT , 1, FALSE);
		IRPSetPositionFile (FH , &OffsetZero);
		PutLog(L"can not Set File to info" , status)	;
		return status ;
	}
	if ( FileInfo.Type != EXE_FILE_PE )
	{
		ResetInformation(&FileInfo);
		InterlockedDecrement( &GV.CurrentBufferAcsess ) ;
		KeReleaseSemaphore ( &GV.BufferSemaphore , IO_NO_INCREMENT , 1, FALSE);
		IRPSetPositionFile (FH , &OffsetZero);
		return STATUS_UNSUCCESSFUL ;
	}
#ifdef __DEMOVERSION__
    status = ChechStuxtNet(Buffer) ;
#endif
	ResetInformation(&FileInfo);
	
	InterlockedDecrement( &GV.CurrentBufferAcsess ) ;

//	BufferNum = KeReadStateSemaphore(&GV.BufferSemaphore) ;
 
	KeReleaseSemaphore ( &GV.BufferSemaphore , IO_NO_INCREMENT , 1, FALSE);
	
	if ( !NT_SUCCESS( IRPSetPositionFile (FH , &OffsetZero)) )
	{
		return STATUS_UNSUCCESSFUL ;
	}
	return status ;
}
*/
#ifdef __DEMOVERSION__
#define SIGNATURENUMBER 3 
#define SizeHeaderGuess 512

//CHAR Array1[] = {0x50 ,0xC7 ,0x45 ,0xE0 ,0x94 ,0x00 ,0x00 ,0x00 ,0xFF ,0x15 ,0x14 ,0x12 ,0x44 ,0x00 ,0x83 ,0x7D ,0xF0 ,0x02 ,0x75 ,0x08 ,0x83 ,0x7D ,0xE4 ,0x05 ,0x72 ,0x1A ,0xEB ,0x14 ,0x83 ,0x7D ,0xF0 ,0x01 ,0x75 ,0x12 ,0x83 ,0x7D ,0xE4 ,0x04 ,0x77 ,0x08 ,0x75 ,0x0A ,0x83 ,0x7D ,0xE8 ,0x00 ,0x76 ,0x04 ,0xC6 ,0x46 ,0x0C ,0x01 ,0x8D ,0x4E ,0x18 ,0xC7 ,0x46 ,0x10 ,0x00 ,0x08 ,0x00 ,0x00 ,0xC7 ,0x46 ,0x14 ,0x00 ,0x70 ,0x44 ,0x00 ,0xE8 ,0xEC ,0xFD ,0xFF ,0xFF ,0x85 ,0xC0 ,0x7D ,0x07 ,0xC6 ,0x05 ,0x61 ,0x7B ,0x45 ,0x00 ,0x01 ,0x8B ,0x4D ,0x74 ,0x8B ,0xC6 ,0x33 ,0xCD ,0x5E ,0xE8 ,0xAE ,0x96 ,0xFE ,0xFF ,0x83 ,0xC5};
//CHAR Array2[] = {0x33 ,0xD2 ,0x85 ,0xFF ,0x76 ,0x0E ,0x8A ,0xC2 ,0xB3 ,0x96 ,0xF6 ,0xEB ,0x30 ,0x04 ,0x0A ,0x42 ,0x3B ,0xD7 ,0x72 ,0xF2 ,0x33 ,0xC0 ,0x39 ,0x45 ,0xFC ,0x76 ,0x14 ,0x8D ,0x57 ,0x01 ,0xD1 ,0xEA ,0x8D ,0x34 ,0x0A ,0x8A ,0x14 ,0x06 ,0x30 ,0x14 ,0x08 ,0x40 ,0x3B ,0x45 ,0xFC ,0x72 ,0xF4 ,0x8D ,0x47 ,0xFF ,0xEB ,0x08 ,0x8A ,0x54 ,0x08 ,0xFF ,0x28 ,0x14 ,0x08 ,0x48 ,0x83 ,0xF8 ,0x01 ,0x73 ,0xF3 ,0xFF ,0x4D ,0xF8 ,0x79 ,0xBA ,0x5E ,0x5B ,0xC9 ,0xC3 ,0xA1 ,0x1C ,0x40 ,0x00 ,0x10 ,0xB9 ,0x4D ,0x5A ,0x00 ,0x00 ,0x66 ,0x39 ,0x08 ,0x74 ,0x03 ,0x33 ,0xC0 ,0xC3 ,0x56 ,0x8B ,0x70 ,0x3C};
//CHAR Array3[] = {0x77 ,0x13 ,0x8B ,0x45 ,0x08 ,0x3B ,0x45 ,0xF0 ,0x74 ,0x1A ,0xFF ,0x45 ,0xF8 ,0x8B ,0x45 ,0xF8 ,0x3B ,0x45 ,0xF4 ,0x72 ,0xCE ,0x33 ,0xF6 ,0x89 ,0x33 ,0x89 ,0x73 ,0x04 ,0x5F ,0x8B ,0xC3 ,0x5E ,0xC9 ,0xC2 ,0x04 ,0x00 ,0x8B ,0x45 ,0xE8 ,0x89 ,0x03 ,0x8B ,0x45 ,0xEC ,0x89 ,0x43 ,0x04 ,0xEB ,0xEB ,0xCC ,0x55 ,0x8B ,0xEC ,0x83 ,0xEC ,0x34 ,0x53 ,0x56 ,0x57 ,0xFF ,0x70 ,0x04 ,0x8D ,0x45 ,0xCC ,0x50 ,0xE8 ,0x6F ,0x0F ,0x00 ,0x00 ,0x85 ,0xC0 ,0x59 ,0x59 ,0x0F ,0x85 ,0x57 ,0x01 ,0x00 ,0x00 ,0x8B ,0x35 ,0x78 ,0x24 ,0x01 ,0x00 ,0x81 ,0xC6 ,0x1C ,0x10 ,0x00 ,0x00 ,0xE8 ,0xB4 ,0x05 ,0x00 ,0x00 ,0x8B ,0xF8};

/*NTSTATUS ScanFile( IN  PFileHandle FH ) 
{
	ULONG             i   , Size;
	__int64           Offset , Align;
	WCHAR             *VirusName = NULL  ;
	UCHAR             Buffer[SizeHeaderGuess] , Buffer2[SizeHeaderGuess];
	NTSTATUS          status = STATUS_UNSUCCESSFUL ;
	LARGE_INTEGER	  OffsetZero = {0} ;
	LPMZEXEHEADER     MZExeHeader ; 
	struct Signature  ISignature2[3] ;

	
	ISignature2[0].FileOffset = 0x3D525;
	ISignature2[0].Size = sizeof (Array1) ;

	ISignature2[0].Array = Array1;
	ISignature2[0].Name = L"Win32/Trojan.jk" ;

	ISignature2[1].FileOffset = 0x0517;
	ISignature2[1].Size = sizeof (Array2);
	ISignature2[1].Name = L"Win32/Stuxnet.ez";
	ISignature2[1].Array =  Array2;

	ISignature2[2].FileOffset = 0x0f96;
	ISignature2[2].Size = sizeof(Array3);
	ISignature2[2].Name = L"Win32/Rootkit.mf";
	ISignature2[2].Array = Array3;

	
	Offset = 0LL ;
	Size = SizeHeaderGuess ; 
	status = ReadByIRPFromFileObject( FH , Buffer , &Size, Offset)  ;
	if (  !NT_SUCCESS (status) ||  Size < SizeHeaderGuess ) 
	{
		IRPSetPositionFile (FH , &OffsetZero);
		return STATUS_UNSUCCESSFUL ;
	}

	if (  *(PUSHORT)Buffer != 0x5a4d && *(PUSHORT)Buffer != 0x4d5a  )
	{
		IRPSetPositionFile (FH , &OffsetZero);
		return STATUS_UNSUCCESSFUL ;
	}

	MZExeHeader = ( LPMZEXEHEADER )Buffer ; 
	Offset = MZExeHeader->NonDosHeaderAddr  ;
	if ( (Offset + sizeof(LONG))  > SizeHeaderGuess) 
	{
		Align = Offset / SizeHeaderGuess ;   
		Align = Align * SizeHeaderGuess ;
		Offset = Offset - Align  ;
		Size = SizeHeaderGuess ; 
		status = ReadByIRPFromFileObject( FH , Buffer ,&Size, Align ) ;
		if ( ! NT_SUCCESS (status) ||  Size < SizeHeaderGuess ) 
		{
			IRPSetPositionFile (FH , &OffsetZero);
			return STATUS_UNSUCCESSFUL ;
		}
	}

	if (  SizeHeaderGuess - Offset < sizeof (ULONG)  ) 
	{
		memcpy ( Buffer , Buffer + Offset , SizeHeaderGuess - Offset ) ;
		Align += SizeHeaderGuess ;
		Size = SizeHeaderGuess ; 
		status = ReadByIRPFromFileObject( FH , Buffer2 , &Size , Align ) ;
		if ( !NT_SUCCESS (status) || Size < SizeHeaderGuess)
		{
			IRPSetPositionFile (FH , &OffsetZero);
			return STATUS_UNSUCCESSFUL ;
		}
		memcpy ( Buffer , Buffer2  , sizeof (ULONG)  - (SizeHeaderGuess - Offset) ) ;
		Offset = 0 ;
	}
		
	if (*(PULONG)(Buffer+ Offset) != 0x00004550 )
	{
		IRPSetPositionFile (FH , &OffsetZero);
		return STATUS_UNSUCCESSFUL ;
	}
	
	
	for (i = 0 ; i < SIGNATURENUMBER ; i++ )
	{
		if ( ISignature2[i].Size > SizeHeaderGuess ) 
		{
			continue ;
		}
		Offset = ISignature2[i].FileOffset ; 
		Align  = Offset / SizeHeaderGuess ;
		Align *= SizeHeaderGuess ;
		Offset = Offset - Align ;
		Size = SizeHeaderGuess ; 
		status = ReadByIRPFromFileObject( FH , Buffer , &Size , Align ) ;
		if ( ! NT_SUCCESS (status) || Size < SizeHeaderGuess)
		{
			continue ;
		}
		if ( Offset + ISignature2[i].Size > SizeHeaderGuess ) 
		{
			memcpy ( Buffer , Buffer + Offset , SizeHeaderGuess - Offset ) ;
			Align += SizeHeaderGuess ;
			Size = SizeHeaderGuess ; 
			status = ReadByIRPFromFileObject( FH , Buffer2 , &Size , Align ) ;
			if ( !NT_SUCCESS (status) || Size < SizeHeaderGuess )
			{
				continue ;
			}
			memcpy ( Buffer , Buffer2  , ISignature2[i].Size - (SizeHeaderGuess - Offset) ) ;
			Offset = 0 ;
		}
		if ( memcmp(Buffer + Offset , ISignature2[i].Array , ISignature2[i].Size ) == 0 ) 
		{
			VirusName = ISignature2[i].Name ; 		
			break ;
		}
	}

	if ( i < SIGNATURENUMBER )
	{
		IRPSetPositionFile (FH , &OffsetZero);

		if( GV.GuiConnect == TRUE  )
		{
			wcscpy ( GV.VirusString ,VirusName ) ;   
			wcscpy ( GV.VirusString , "#") ;
			wcscpy ( GV.VirusString ,  FH->FileObject->FileName.Buffer ) ;

			KeSetEvent(GV.Hevent ,IO_NO_INCREMENT ,1 ) ; 
		}
		return STATUS_SUCCESS ;
	}
	IRPSetPositionFile (FH , &OffsetZero);
	return STATUS_UNSUCCESSFUL ;
}*/

NTSTATUS ScanFile(IN  PFileHandle FH) 
{
	NTSTATUS           status ;
	LARGE_INTEGER	   OffsetZero = {0} ;	
	PSbScaner          posSbscaner ;
	FileInformation    FileInformation ; 
	ULONG              index ;
	PUCHAR             BufferPointer ;	
	UINT32			   u32Result = NotVirus;

	//struct Signature  ISignature2[3] ;

	PAGED_CODE();
	//return STATUS_UNSUCCESSFUL ;
	return STATUS_UNSUCCESSFUL ;

	posSbscaner = SMGetBufferFromPool(FH) ;

	ASSERT(posSbscaner) ;

	status = SMSetBufferFile (posSbscaner->m_pocBuffer) ;
	if (!NT_SUCCESS(status))
	{
		RealseBuffer(posSbscaner->m_pocBuffer);
		return status ;
	}
	ASSERT(posSbscaner->m_pocBuffer->File == FH) ;
	status = SMSetInfoFile (&FileInformation ,posSbscaner->m_pocBuffer) ; 
	if (!NT_SUCCESS(status))
	{
		RealseBuffer(posSbscaner->m_pocBuffer);
		IRPSetPositionFile (FH , &OffsetZero);
		return status ;
	}
	ASSERT(posSbscaner->m_pocBuffer->File == FH) ;
	if (FileInformation.m_osType != EXE_FILE_PE) 
	{
		RealseBuffer(posSbscaner->m_pocBuffer);
		IRPSetPositionFile (FH , &OffsetZero);
		return STATUS_UNSUCCESSFUL ;
	}
	
	SetFileContext(posSbscaner , &FileInformation);
  	if (GetSet(posSbscaner) == TRUE )
  	{
  		if ( IsInfectetPackedVirus(posSbscaner) == TRUE ) 
  		{
  			RealseBuffer(posSbscaner->m_pocBuffer);
  			IRPSetPositionFile (FH , &OffsetZero);
  			SMResetFileInformation(&FileInformation);
			IoCancelFileOpen ( FH->FileSysDevice , FH->FileObject ) ;
			if ( GV.u32DemandConfig & SMAV_SETTING_CLEAN )
				DeleteVirus(FH);
  			return STATUS_SUCCESS ;
  		}
  	}
	
/*	VM_Initialize(posSbscaner->m_posVmStack, posSbscaner->m_pocFileInfo, posSbscaner->m_pocBuffer, FH , GV.u32DemandConfig);
	PutLog(L"Come Into File" , STATUS_SUCCESS );
	PutLog(FH->wsFileName, STATUS_SUCCESS );

	// If there was a virus here and it has been clean by guard, there is no need to check VirusAndCleaned return value
	// It is used for OnDemand scan
	u32Result = VM_Start(posSbscaner->m_posVmStack) ;
	if (u32Result == VirusAndNotCleaned)
	{
		PutLog(L"Release File" , STATUS_SUCCESS);
		PutLog(FH->wsFileName, STATUS_SUCCESS );
		// Insert Code For Get Virus Name HERE!!!!!
		RealseBuffer(posSbscaner->m_pocBuffer);
		IRPSetPositionFile (FH , &OffsetZero);
 		SMResetFileInformation(&FileInformation);
		return STATUS_SUCCESS ;
 	}

	PutLog(L"Release File" , STATUS_SUCCESS);
	PutLog(FH->wsFileName, STATUS_SUCCESS );

	RealseBuffer(posSbscaner->m_pocBuffer);
	IRPSetPositionFile (FH , &OffsetZero);
	SMResetFileInformation(&FileInformation);
	*/
	return (u32Result == VirusAndCleaned ? u32Result : STATUS_UNSUCCESSFUL) ;
}
//----------------------------------------------------------------------------------------
/*__inline PSbScaner GetBufferFromPool( IN PFileHandle FH )
{
	NTSTATUS   status ;
	ULONG CurrentBufferPointer ;
	WCHAR log[100] ;  
	PAGED_CODE();
	status = KeWaitForSingleObject ( &GV.BufferSemaphore , Executive, KernelMode, FALSE, NULL);
	if ( !NT_SUCCESS(status) ) 
	{
		PutLog(L"can not wait for single object" , status)	;
		return NULL ;
	}
	ExAcquireFastMutex (&GV.BufferPointerLock)  ;
	{
		do 
		{
			if (GV.StartBufferAccsess == COUNTFILEJBUFFER - 1 ) 
			{
				GV.StartBufferAccsess = 0 ;
			}
			else
			{
				GV.StartBufferAccsess ++ ;
			}
		} while(GV.BufferPool[GV.StartBufferAccsess]->File != NULL) ;
		GV.BufferPool[GV.StartBufferAccsess]->File = FH ;
		CurrentBufferPointer = GV.StartBufferAccsess ;
	}
	ExReleaseFastMutex  (&GV.BufferPointerLock)  ;

	return GV.SbScanerPool[CurrentBufferPointer] ;
}*/
//---------------------------------------------------------------------------------
void RealseBuffer( PSMBuffer Buf )
{
	PAGED_CODE();
	if ( Buf->Irp )
	{
		IoFreeIrp( Buf->Irp ) ;
		Buf->Irp = NULL ;
	}
	Buf->File = NULL  ; // میدونم اینجا جای اینجور کار را نیست
	KeReleaseSemaphore ( &GV.BufferSemaphore , IO_NO_INCREMENT , 1, FALSE);
	return ;
}
//---------------------------------------------------------------------------------
NTSTATUS DeleteVirus(IN  PFileHandle i_pocFH )
{
	ULONG      ulDesiredAccess  = DELETE | SYNCHRONIZE;
	ULONG      ulShareAccess    = FILE_SHARE_DELETE;
	ULONG      BufferLenght ;
	NTSTATUS   status ;
	PVOID      pvDevice = i_pocFH->FileSysDevice;
	SMFile     ocFile ; 
	WCHAR      wcsFullPathName[MAX_PATH*2] ;
	StringCchPrintfW(wcsFullPathName , MAX_PATH*2, L"%s%s" , i_pocFH->wsDosDeviceName , i_pocFH->wsFileName);
	status = SMOpenFile4Kernel( &ocFile , wcsFullPathName , ulDesiredAccess , ulShareAccess , i_pocFH->FileSysDevice )	;
	if (!NT_SUCCESS (status))
	{
		return status ;
	}
	status = SMFileDelete(&ocFile) ;
	SMCloseFile(&ocFile) ;
	return status;
}
#endif 
