//ÏÑ Çä ÝÇíá ÊæÇÈÚ ˜ÇÑ ÈÇ ÝÇíá Èå æÇÓØå Âí ÂÑ í íÇÏå ÓÇÒí ÔÏå ÇÓÊ
#include "ntifs.h"
#include "log.h"
#include "FileApiBYIRP.h"
#ifdef ALLOC_PRAGMA

#pragma alloc_text( PAGE , ReadByIRPFromFileObject )	
#pragma alloc_text( PAGE , IRPGetFileAttributes )
#pragma alloc_text( PAGE , IRPGetFileName )
#pragma alloc_text( PAGE , IRPGetFileCurrentOffset )
#pragma alloc_text( PAGE , IRPGetFileSize )
#pragma alloc_text( PAGE , IRPDeleteFile )
#pragma alloc_text( PAGE , IRPSetEndFile )
#pragma alloc_text( PAGE , IRPSetPositionFile )
#pragma alloc_text( PAGE , IRPFlushFile )
#pragma alloc_text( PAGE , WriteByIRPFromFileObject )
#endif

NTSTATUS 
FsIoMakeSetFileEndOfFileInformationRequest(
	PFILE_OBJECT FileObject,
	PDEVICE_OBJECT DeviceObjectHint,
	PLARGE_INTEGER FileEnd);

NTSTATUS 
QueryInfoCompletion(
					IN PDEVICE_OBJECT  DeviceObject,
					IN PIRP  Irp,
					IN PKEVENT  FinishEvent) ;

//  Çíä ÊÇÈÚ ˜ÇãáÔíä ÑæÊíä ÎæÇäÏå ãíÈÇÔÏ æ æä ÓíÇÓÊ ÈÑäÇãå ÇÓÊ ˜å Âí ÂÑ í ÓÇÎÊå ÔÏå Èå Ô˜á äÏ ÈÇÑ ãÕÑÝ ÈÇÔÏ æ ÏÑ ÎæÇÓÊ ÏíÑ åã ÇÓÊÝÇÏå ÔæÏ ÏÑ äÊíÌå Çíä ÊÇÈå ÓÊ ÔÏå ÊÇ Âí ÂÑ í ÊæÓØ Âí Âæ ãäÌÑ Ç˜ äÔæÏ
NTSTATUS  IoCompletionReadIo( PDEVICE_OBJECT  DeviceObject,PIRP  Irp, PVOID  Context ) 
{

	*Irp->UserIosb = Irp->IoStatus;


	if (Irp->PendingReturned)
		KeSetEvent(
		(PKEVENT)Context,
		IO_NO_INCREMENT,
		FALSE);


		return STATUS_MORE_PROCESSING_REQUIRED;
}
//----------------------------------------------------------------------------------------------------
/*NTSTATUS ReadByIRPFromFileObject (JBuffer *posJBuffer, _ModuleDescriptor  *Buffer , PULONG Size , __int64 Offset )
//NTSTATUS ReadByIRPFromFileObject( IN PFileHandle FH , PVOID Buffer , PULONG Size , __int64 Offset )
{
	LARGE_INTEGER BigOffset ;
	KEVENT Hevent;
	IO_STATUS_BLOCK IoStatusBlock;
	PIO_STACK_LOCATION irpSp;
	PIRP ReadIrp;
	NTSTATUS status;
	PFileHandle FH = posJBuffer->File ;
	PAGED_CODE () ;

	ASSERT(FH!=NULL); 

	BigOffset.QuadPart = Offset ;
	KeInitializeEvent(&Hevent, SynchronizationEvent, FALSE);

	ReadIrp = IoBuildSynchronousFsdRequest ( IRP_MJ_READ ,  FH->FileSysDevice , Buffer->Pointer , *Size , &BigOffset , &Hevent ,&IoStatusBlock) ;

	if (!ReadIrp)
		return STATUS_INSUFFICIENT_RESOURCES;

	irpSp = IoGetNextIrpStackLocation(ReadIrp);
	irpSp->FileObject = FH->FileObject;
	irpSp->DeviceObject = FH->FileSysDevice ;
	// for fat bug 
	SetFlag(ReadIrp->Flags, IRP_NOCACHE ) ;


	status = IoCallDriver(
		FH->FileSysDevice,
		ReadIrp);

	if (status == STATUS_PENDING)
	{
		KeWaitForSingleObject( &Hevent ,Executive ,KernelMode ,FALSE , NULL);
	}
	status = IoStatusBlock.Status;
	*Size = IoStatusBlock.Information ;
	return status;
}*/

//----------------------------------------------------------------------------------------------------
/*NTSTATUS ReadByIRPFromFileObject( IN PFileHandle FH , PMDL Mdl , PULONG Size , __int64 Offset )
{
	KEVENT Hevent;
	PIRP ReadIrp  = NULL ;
	IO_STATUS_BLOCK IoStatusBlock;
	PIO_STACK_LOCATION irpSp;
	NTSTATUS status;
	__try
	{
		KeInitializeEvent(&Hevent, SynchronizationEvent, FALSE);
		ReadIrp = IoAllocateIrp(FH->FileSysDevice->StackSize, FALSE);
		if (!ReadIrp)
		{
			return STATUS_INSUFFICIENT_RESOURCES;;
		}

		IoInitializeIrp(ReadIrp,IoSizeOfIrp(FH->FileSysDevice->StackSize),FH->FileSysDevice->StackSize);

		ReadIrp->MdlAddress = Mdl;
		//ReadIrp->UserEvent = &Hevent;
		ReadIrp->UserIosb = &IoStatusBlock;
		ReadIrp->Tail.Overlay.Thread = PsGetCurrentThread();
		ReadIrp->Tail.Overlay.OriginalFileObject= FH->FileObject;
		ReadIrp->RequestorMode = KernelMode;
		ReadIrp->Flags = IRP_READ_OPERATION;
		SetFlag(ReadIrp->Flags, IRP_SYNCHRONOUS_API ) ;
		SetFlag(ReadIrp->Flags, IRP_NOCACHE );
		ReadIrp->IoStatus.Status = STATUS_SUCCESS;
		irpSp = IoGetNextIrpStackLocation(ReadIrp);
		irpSp->MajorFunction = IRP_MJ_READ;
		irpSp->MinorFunction = 0 ;
		irpSp->DeviceObject = FH->FileSysDevice;
		irpSp->FileObject = FH->FileObject;
		IoSetCompletionRoutine(ReadIrp, IoCompletionReadIo, &Hevent, TRUE, TRUE, TRUE);

		irpSp->Parameters.Read.Length = *Size;

		irpSp->Parameters.Read.ByteOffset =*((LARGE_INTEGER*) (&Offset));

		status = IoCallDriver(
			FH->FileSysDevice,
			ReadIrp);

		if (status == STATUS_PENDING)
		{
			KeWaitForSingleObject( &Hevent ,Executive ,KernelMode ,FALSE , NULL);
		}

		status = IoStatusBlock.Status;
		*Size = IoStatusBlock.Information ;
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{

		if (ReadIrp)
			IoFreeIrp(ReadIrp);

		return GetExceptionCode();

	}
	return status;

}
*/

// Çíä ÊÇÈÚ ÈÑÇí ÎæÇäÏä ÏÇÏå ÇÒ ÏÑæä ÝÇíá äæÔÊå ÔÏå ÇÓÊ 
// Ïæ ÊÇÈÚ ÈÇáÇ ˜å Èå ÕæÑÊ ˜ÇãäÊ äæÔÊå ÔÏå ÇäÏ ãíÊæÇääÏ ÌÇí Çíä ÊÇÈÚ ÑÇ ÏÑ ÕæÑÊí ˜å Çíä ÊÇÈÚ ÏÇÑ ãÔ˜á ÔÏ æÏÑ ÍÇáÇÊí ÏÇÑ ÎØÇ ÑÏíäÏ Çíä ÊÇÈÚ ÈÇ ÊæÇÈÚ ãØãÆä ÊÑ ÈÇáÇ ÇíÒíäí ÔæäÏ
NTSTATUS ReadByIRPFromFileObject (SMBuffer *posJBuffer, SMModuleDescriptor  *Buffer , PULONG Size , __int64 Offset )
{
	NTSTATUS Status;
	PIO_STACK_LOCATION NextIrpStack;
	IO_STATUS_BLOCK IoStatusBlock;
	PFileHandle FH = posJBuffer->File ;
	PIRP ReadIrp = posJBuffer->Irp ;
	PAGED_CODE () ;
	__try
	{
		if (FH->FileSysDevice->DriverObject->FastIoDispatch->FastIoRead(FH->FileObject ,((LARGE_INTEGER*) (&Offset)) , *Size , TRUE , 0 , Buffer->Pointer , &IoStatusBlock , FH->FileSysDevice ) != FALSE )
		{
			return STATUS_SUCCESS ;
		}
		ASSERT(ReadIrp);
		IoInitializeIrp(ReadIrp,IoSizeOfIrp(FH->FileSysDevice->StackSize),FH->FileSysDevice->StackSize);
		ReadIrp->RequestorMode = KernelMode;
		ReadIrp->UserIosb = &IoStatusBlock;
		ReadIrp->Flags = IRP_SYNCHRONOUS_API /*| IRP_NOCACHE*/;
		ReadIrp->IoStatus.Status = STATUS_SUCCESS;
		ReadIrp->Tail.Overlay.Thread = KeGetCurrentThread();

		NextIrpStack = IoGetNextIrpStackLocation(ReadIrp);
		NextIrpStack->MajorFunction = IRP_MJ_READ;
		NextIrpStack->MinorFunction = 0;
		NextIrpStack->DeviceObject = FH->FileSysDevice;
		NextIrpStack->FileObject = FH->FileObject;
		NextIrpStack->Parameters.Read.ByteOffset = *((LARGE_INTEGER*) (&Offset));;
		NextIrpStack->Parameters.Read.Length = *Size;

		if (FlagOn(FH->FileSysDevice->Flags, DO_BUFFERED_IO))
		{
			ReadIrp->AssociatedIrp.SystemBuffer = Buffer->Pointer ; 
		}
		else
			if (FlagOn(FH->FileSysDevice->Flags, DO_DIRECT_IO))
			{
				//////////////////////////////DbgBreakPoint();

				ReadIrp->MdlAddress = Buffer->mdl ;
			}
			else
			{
				ReadIrp->UserBuffer = Buffer->Pointer ;
			}


			KeInitializeEvent(
				posJBuffer->phEvent,
				NotificationEvent,
				FALSE);



			IoSetCompletionRoutine(
				ReadIrp,
				IoCompletionReadIo,
				posJBuffer->phEvent,
				TRUE,
				TRUE,
				TRUE);


			Status = IoCallDriver(	FH->FileSysDevice,	ReadIrp);

			if (Status == STATUS_PENDING)
			{
				KeWaitForSingleObject(	posJBuffer->phEvent, Executive,	KernelMode,	FALSE,	NULL);
			}

			Status = IoStatusBlock.Status;
			return Status;

	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		//////////////////////////////DbgBreakPoint();
		Status = GetExceptionCode();

		return Status;
	}

}
//
//----------------------------------------------------------------------------------------------------
NTSTATUS IRPGetFileAttributes( IN PFileHandle FH , PULONG FileAttrib )
{
	IO_STATUS_BLOCK IoStatusBlock;
	KEVENT Hevent;
	PIRP Irp;
	LARGE_INTEGER BigOffset = {0} ;
	FILE_BASIC_INFORMATION osFileAttributeTagInformation;
	PIO_STACK_LOCATION irpSp;
	NTSTATUS status;
	PAGED_CODE () ;
	ASSERT(FH!=NULL); 

	KeInitializeEvent(&Hevent, SynchronizationEvent, FALSE); 
	Irp = IoBuildSynchronousFsdRequest ( IRP_MJ_QUERY_INFORMATION , FH->FileSysDevice , &osFileAttributeTagInformation , sizeof(FILE_BASIC_INFORMATION) , &BigOffset , &Hevent ,&IoStatusBlock) ;

	if (!Irp)
		return STATUS_INSUFFICIENT_RESOURCES;

	Irp->AssociatedIrp.SystemBuffer = &osFileAttributeTagInformation;

	irpSp = IoGetNextIrpStackLocation(Irp);
	irpSp->FileObject = FH->FileObject;
	irpSp->DeviceObject = FH->FileSysDevice ;
	irpSp->Parameters.QueryFile.FileInformationClass = FileBasicInformation ; 
	irpSp->Parameters.QueryFile.Length = sizeof (FILE_BASIC_INFORMATION) ;

	status = IoCallDriver(
		FH->FileSysDevice,
		Irp);
	if (status == STATUS_PENDING)
	{
		KeWaitForSingleObject( &Hevent ,Executive ,KernelMode ,FALSE , NULL);
	}

	status = IoStatusBlock.Status;
	if (NT_SUCCESS (status))
	{
		if (FileAttrib)
			*FileAttrib = osFileAttributeTagInformation.FileAttributes ;
	}

	return status;

}
//---------------------------------------------------------------------
NTSTATUS IRPGetFileName( IN PFileHandle FH, unsigned char *NameBuffer )
{

	IO_STATUS_BLOCK IoStatusBlock;
	KEVENT Hevent;
	PIRP Irp;
	LARGE_INTEGER BigOffset = {0} ;
	ULONG DeviceNameSize ;
	PIO_STACK_LOCATION irpSp;
	NTSTATUS status;

	PAGED_CODE () ;
	ASSERT(FH!=NULL); 

	KeInitializeEvent(&Hevent, SynchronizationEvent, FALSE); 	
	Irp = IoBuildSynchronousFsdRequest ( IRP_MJ_QUERY_INFORMATION , FH->FileSysDevice , NameBuffer , NameInformationBefferSize, &BigOffset , &Hevent ,&IoStatusBlock) ;
	if (!Irp)
		return STATUS_INSUFFICIENT_RESOURCES;

	Irp->AssociatedIrp.SystemBuffer = NameBuffer ;
	
	irpSp = IoGetNextIrpStackLocation(Irp);
	irpSp->Parameters.QueryFile.FileInformationClass = FileNameInformation ; 
	irpSp->Parameters.QueryFile.Length =NameInformationBefferSize ;
	irpSp->FileObject = FH->FileObject;
	irpSp->DeviceObject = FH->FileSysDevice ;
	
	status = IoCallDriver(
		FH->FileSysDevice,
		Irp);

	if (status == STATUS_PENDING)
	{
		KeWaitForSingleObject( &Hevent ,Executive ,KernelMode ,FALSE , NULL);
	}
	return  IoStatusBlock.Status;

}
//--------------------------------------------------------------------------------------
NTSTATUS IRPGetFileCurrentOffset( IN PFileHandle FH,LARGE_INTEGER *CurrentByteOffset )
{
	IO_STATUS_BLOCK IoStatusBlock;
	KEVENT Hevent;
	PIRP Irp;
	LARGE_INTEGER BigOffset = {0} ;
	FILE_POSITION_INFORMATION FilePositionTagInformation;
	PIO_STACK_LOCATION irpSp;
	NTSTATUS status;
	PAGED_CODE () ;
	ASSERT(FH!=NULL); 

	if (CurrentByteOffset == NULL )
	{
		PutLog(L"Invalid Parameter" , STATUS_INVALID_PARAMETER) ;
		return STATUS_INVALID_PARAMETER ;
	}

	KeInitializeEvent(&Hevent, SynchronizationEvent, FALSE); 
	Irp = IoBuildSynchronousFsdRequest ( IRP_MJ_QUERY_INFORMATION , FH->FileSysDevice , &FilePositionTagInformation , sizeof(FILE_POSITION_INFORMATION) , &BigOffset , &Hevent ,&IoStatusBlock) ;
	if (!Irp)
		return STATUS_INSUFFICIENT_RESOURCES;

	Irp->AssociatedIrp.SystemBuffer = &FilePositionTagInformation ;

	irpSp = IoGetNextIrpStackLocation(Irp);
	irpSp->FileObject = FH->FileObject;
	irpSp->DeviceObject = FH->FileSysDevice ;
	irpSp->Parameters.QueryFile.FileInformationClass = FilePositionInformation ; 
	irpSp->Parameters.QueryFile.Length = sizeof(FILE_POSITION_INFORMATION) ;

	status = IoCallDriver(
		FH->FileSysDevice,
		Irp);
	if (status == STATUS_PENDING)
	{
		KeWaitForSingleObject( &Hevent ,Executive ,KernelMode ,FALSE , NULL);
	}

	status = IoStatusBlock.Status;
	if (NT_SUCCESS (status))
	{
		*CurrentByteOffset = FilePositionTagInformation.CurrentByteOffset ;
	}

	return status;

}
//--------------------------------------------------------------------------------
NTSTATUS IRPGetFileSize( SMBuffer *posJBuffer , LARGE_INTEGER *FileSize )
{

	IO_STATUS_BLOCK IoStatusBlock;
	PIRP Irp = posJBuffer->Irp;
	PFileHandle FH = posJBuffer->File ;
	FILE_STANDARD_INFORMATION FileStandardTagInformation;
	PIO_STACK_LOCATION irpSp;
	NTSTATUS status;
	PAGED_CODE () ;
	ASSERT(FH!=NULL && FileSize); 

	IoInitializeIrp(Irp,IoSizeOfIrp(FH->FileSysDevice->StackSize),FH->FileSysDevice->StackSize);
	Irp->RequestorMode = KernelMode;
	Irp->UserIosb = &IoStatusBlock;
	Irp->Flags = IRP_SYNCHRONOUS_API ;
	Irp->IoStatus.Status = STATUS_SUCCESS;
	Irp->Tail.Overlay.Thread = KeGetCurrentThread();
	Irp->AssociatedIrp.SystemBuffer = &FileStandardTagInformation ;

	irpSp = IoGetNextIrpStackLocation(Irp);
	irpSp->MajorFunction = IRP_MJ_QUERY_INFORMATION;
	irpSp->FileObject = FH->FileObject;
	irpSp->DeviceObject = FH->FileSysDevice ;
	irpSp->Parameters.QueryFile.FileInformationClass = FileStandardInformation ; 
	irpSp->Parameters.QueryFile.Length = sizeof(FILE_STANDARD_INFORMATION) ;

	IoSetCompletionRoutine(
				Irp,
				IoCompletionReadIo,
				posJBuffer->phEvent,
				TRUE,
				TRUE,
				TRUE);

	status = IoCallDriver
		(
		FH->FileSysDevice,
		Irp
		);
	if (status == STATUS_PENDING)
	{
		KeWaitForSingleObject( posJBuffer->phEvent ,Executive ,KernelMode ,FALSE , NULL);
	}

	status = IoStatusBlock.Status;
	if (NT_SUCCESS (status))
	{
		*FileSize = FileStandardTagInformation.EndOfFile;
	}

	return status;
}
//--------------------------------------------------------------------------------
NTSTATUS IRPDeleteFile(IN  PFileHandle FH ) 
{
	IO_STATUS_BLOCK IoStatusBlock;
	KEVENT Hevent;
	PIRP Irp;
	LARGE_INTEGER BigOffset = {0} ;
	FILE_DISPOSITION_INFORMATION FileDispostionTagInformation;
	PIO_STACK_LOCATION irpSp;
	NTSTATUS status;

	PAGED_CODE () ;
	FileDispostionTagInformation.DeleteFile = TRUE ;
	KeInitializeEvent(&Hevent, SynchronizationEvent, FALSE); 
	Irp = IoBuildSynchronousFsdRequest ( IRP_MJ_SET_INFORMATION , FH->FileSysDevice , &FileDispostionTagInformation , sizeof(FILE_DISPOSITION_INFORMATION) , &BigOffset , &Hevent ,&IoStatusBlock ) ;
	if (!Irp)
		return STATUS_INSUFFICIENT_RESOURCES;

	Irp->IoStatus.Status =  STATUS_SUCCESS ;
	Irp->AssociatedIrp.SystemBuffer = &FileDispostionTagInformation ;
	irpSp = IoGetNextIrpStackLocation(Irp);
	irpSp->FileObject = FH->FileObject;
	irpSp->DeviceObject = FH->FileSysDevice ;
	irpSp->Parameters.SetFile.FileInformationClass = FileDispositionInformation ;
	irpSp->Parameters.SetFile.Length = sizeof(FILE_DISPOSITION_INFORMATION) ;
	irpSp->Parameters.SetFile.FileObject = FH->FileObject ;

	status = IoCallDriver(
		FH->FileSysDevice,
		Irp);
	if (status == STATUS_PENDING)
	{
		KeWaitForSingleObject( &Hevent ,Executive ,KernelMode ,FALSE , NULL);
	}

	status = IoStatusBlock.Status;
	return status;
}
//--------------------------------------------------------------------------------
NTSTATUS IRPSetEndFile(IN  PFileHandle FH , LARGE_INTEGER EndOfFile ) 
{
	IO_STATUS_BLOCK IoStatusBlock;
	KEVENT Hevent;
	PIRP Irp;
	LARGE_INTEGER BigOffset = {0} ;
	FILE_END_OF_FILE_INFORMATION FileEndOfFileTagInformation;
	PIO_STACK_LOCATION irpSp;
	NTSTATUS status;

	PAGED_CODE () ;
	ASSERT(FH!=NULL); 

	FileEndOfFileTagInformation.EndOfFile = EndOfFile ;
	KeInitializeEvent(&Hevent, SynchronizationEvent, FALSE); 
	Irp = IoBuildSynchronousFsdRequest ( IRP_MJ_SET_INFORMATION , FH->FileSysDevice , &FileEndOfFileTagInformation , sizeof(FILE_END_OF_FILE_INFORMATION) , &BigOffset , &Hevent ,&IoStatusBlock ) ;
	if (!Irp)
		return STATUS_INSUFFICIENT_RESOURCES;
	Irp->AssociatedIrp.SystemBuffer = &FileEndOfFileTagInformation  ;
	irpSp = IoGetNextIrpStackLocation(Irp);
	irpSp->FileObject = FH->FileObject;
	irpSp->DeviceObject = FH->FileSysDevice ;
	irpSp->Parameters.SetFile.FileInformationClass = FileEndOfFileInformation ;
	irpSp->Parameters.SetFile.Length = sizeof(FILE_END_OF_FILE_INFORMATION) ;
	irpSp->Parameters.SetFile.FileObject = NULL ;

	status = IoCallDriver(
		FH->FileSysDevice,
		Irp);
	if (status == STATUS_PENDING)
	{
		KeWaitForSingleObject( &Hevent ,Executive ,KernelMode ,FALSE , NULL);
	}

	status = IoStatusBlock.Status;
	return status;
}
//--------------------------------------------------------------------------------
NTSTATUS IRPSetPositionFile(IN  PFileHandle FH , PLARGE_INTEGER Offset ) 
{
	IO_STATUS_BLOCK IoStatusBlock;
	KEVENT Hevent;
	PIRP Irp;
	LARGE_INTEGER BigOffset = {0} ;
	FILE_POSITION_INFORMATION FilePositionTagInformation;
	PIO_STACK_LOCATION irpSp;
	NTSTATUS status;

	PAGED_CODE () ;
	ASSERT(FH!=NULL); 

	FilePositionTagInformation.CurrentByteOffset = *Offset ;

	KeInitializeEvent(&Hevent, SynchronizationEvent, FALSE); 
	Irp = IoBuildSynchronousFsdRequest ( IRP_MJ_SET_INFORMATION , FH->FileSysDevice , &FilePositionTagInformation , sizeof(FILE_POSITION_INFORMATION) , &BigOffset , &Hevent ,&IoStatusBlock ) ;
	if (!Irp)
		return STATUS_INSUFFICIENT_RESOURCES;

	Irp->IoStatus.Status =  STATUS_SUCCESS ;
	Irp->AssociatedIrp.SystemBuffer = &FilePositionTagInformation ;
	irpSp = IoGetNextIrpStackLocation(Irp);
	irpSp->FileObject = FH->FileObject;
	irpSp->DeviceObject = FH->FileSysDevice ;
	irpSp->Parameters.SetFile.FileInformationClass = FilePositionInformation ;
	irpSp->Parameters.SetFile.Length = sizeof(FILE_POSITION_INFORMATION) ;
	irpSp->Parameters.SetFile.FileObject = FH->FileObject;

	status = IoCallDriver(
		FH->FileSysDevice,
		Irp);
	if (status == STATUS_PENDING)
	{
		KeWaitForSingleObject( &Hevent ,Executive ,KernelMode ,FALSE , NULL);
	}

	status = IoStatusBlock.Status;
	
	return 	status;/*FsIoMakeSetFileEndOfFileInformationRequest( FH->FileObject , FH->FileSysDevice , Offset) ;*/
}
//--------------------------------------------------------------------------------------------------
NTSTATUS 
FsIoMakeQueryStandardFileInformationRequest(
	PFILE_OBJECT FileObject,
	PDEVICE_OBJECT DeviceObjectHint,
	PFILE_STANDARD_INFORMATION FileStdInfo)
	/*++

	Routine Description:

	Arguments:

	Return Value:

	--*/
{
	NTSTATUS Status;
	PIRP QueryIrp = NULL;
	PIO_STACK_LOCATION irpSp;
	IO_STATUS_BLOCK UserIosb;
	KEVENT FinishEvent;


	PAGED_CODE();

	__try
	{

		QueryIrp = IoAllocateIrp(
			DeviceObjectHint->StackSize,
			FALSE);

		if (!QueryIrp)
			return STATUS_INSUFFICIENT_RESOURCES;

		IoInitializeIrp(
			QueryIrp,
			IoSizeOfIrp(DeviceObjectHint->StackSize),
			DeviceObjectHint->StackSize);

		QueryIrp->RequestorMode = KernelMode;

		QueryIrp->UserIosb = &UserIosb;

		QueryIrp->Tail.Overlay.Thread  = KeGetCurrentThread();

		QueryIrp->IoStatus.Status = STATUS_SUCCESS;

		QueryIrp->AssociatedIrp.SystemBuffer = FileStdInfo;


		irpSp = IoGetNextIrpStackLocation(QueryIrp);

		irpSp->MajorFunction = IRP_MJ_QUERY_INFORMATION;

		irpSp->Parameters.QueryFile.FileInformationClass = FileStandardInformation;

		irpSp->Parameters.QueryFile.Length = sizeof(FILE_STANDARD_INFORMATION);

		irpSp->DeviceObject = DeviceObjectHint;

		irpSp->FileObject = FileObject;

		KeInitializeEvent(	&FinishEvent,	NotificationEvent,		FALSE);

		IoSetCompletionRoutine(
			QueryIrp,
			QueryInfoCompletion,
			&FinishEvent,
			TRUE,
			TRUE,
			TRUE);

		Status = IoCallDriver(
			DeviceObjectHint,
			QueryIrp);

		if (Status == STATUS_PENDING)
			KeWaitForSingleObject(
			&FinishEvent,
			Executive,
			KernelMode,
			FALSE,
			NULL);


		return UserIosb.Status;


	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{

		if (QueryIrp)
			IoFreeIrp(QueryIrp);

		return GetExceptionCode();

	}

	return STATUS_SUCCESS;
}
//-------------------------------------------------------------------------------------------------
NTSTATUS 
		FsIoMakeSetFileEndOfFileInformationRequest(
		PFILE_OBJECT FileObject,
		PDEVICE_OBJECT DeviceObjectHint,
		PLARGE_INTEGER FileEnd)
		/*++

		Routine Description:



		Arguments:



		Return Value:



		--*/
	{
		NTSTATUS Status;
		PIRP SetIrp = NULL;
		PIO_STACK_LOCATION irpSp;
		IO_STATUS_BLOCK UserIosb;
		KEVENT FinishEvent;
		FILE_POSITION_INFORMATION FileEndInfo;


		PAGED_CODE();

		__try
		{

			SetIrp = IoAllocateIrp(
				DeviceObjectHint->StackSize,
				FALSE);

			if (!SetIrp)
				return STATUS_INSUFFICIENT_RESOURCES;

			IoInitializeIrp(
				SetIrp,
				IoSizeOfIrp(DeviceObjectHint->StackSize),
				DeviceObjectHint->StackSize);

			SetIrp->RequestorMode = KernelMode;
			SetFlag(SetIrp->Flags, IRP_NOCACHE ) ;
			SetFlag(SetIrp->Flags, IRP_SYNCHRONOUS_API ) ;
			SetIrp->UserIosb = &UserIosb;

			SetIrp->Tail.Overlay.Thread  = KeGetCurrentThread();

			SetIrp->IoStatus.Status = STATUS_SUCCESS;

			FileEndInfo.CurrentByteOffset = *FileEnd;

			SetIrp->AssociatedIrp.SystemBuffer = &FileEndInfo;

			irpSp = IoGetNextIrpStackLocation(SetIrp);

			irpSp->MajorFunction = IRP_MJ_SET_INFORMATION;


			irpSp->Parameters.SetFile.FileInformationClass = FilePositionInformation;

			irpSp->Parameters.SetFile.Length = sizeof(FILE_POSITION_INFORMATION);


			irpSp->DeviceObject = DeviceObjectHint;

			irpSp->FileObject = FileObject;

			KeInitializeEvent(
				&FinishEvent,
				NotificationEvent,
				FALSE);

			IoSetCompletionRoutine(
				SetIrp,
				QueryInfoCompletion,
				&FinishEvent,
				TRUE,
				TRUE,
				TRUE);

			Status = IoCallDriver(
				DeviceObjectHint,
				SetIrp);

			if (Status == STATUS_PENDING)
				KeWaitForSingleObject(
				&FinishEvent,
				Executive,
				KernelMode,
				FALSE,
				NULL);


			return UserIosb.Status;


		}
		__except(EXCEPTION_EXECUTE_HANDLER)
		{

			if (SetIrp)
				IoFreeIrp(SetIrp);

			return GetExceptionCode();

		}

		return STATUS_SUCCESS;
}

//--------------------------------------------------------------------------------------------------
NTSTATUS 
QueryInfoCompletion(
					IN PDEVICE_OBJECT  DeviceObject,
					IN PIRP  Irp,
					IN PKEVENT  FinishEvent)
					/*++

					Routine Description:



					Arguments:



					Return Value:



					--*/
{
	UNREFERENCED_PARAMETER(DeviceObject);


	ASSERT( NULL != Irp->UserIosb );


	*Irp->UserIosb = Irp->IoStatus;




	if (Irp->PendingReturned)
		KeSetEvent(
		FinishEvent,
		IO_NO_INCREMENT,
		FALSE);

	IoFreeIrp(Irp);
	Irp = NULL;

	return STATUS_MORE_PROCESSING_REQUIRED;
}
//--------------------------------------------------------------------------------------------------

NTSTATUS IRPFlushFile(IN PFileHandle FH)
{

	IO_STATUS_BLOCK IoStatusBlock;
	KEVENT Hevent;
	PIRP Irp;
	LARGE_INTEGER BigOffset = {0} ;
	ULONG DeviceNameSize ;
	PIO_STACK_LOCATION irpSp;
	NTSTATUS status;

	PAGED_CODE();

	PAGED_CODE () ;
	ASSERT(FH!=NULL); 

	KeInitializeEvent(&Hevent, SynchronizationEvent, FALSE); 	
	Irp = IoBuildSynchronousFsdRequest ( IRP_MJ_FLUSH_BUFFERS , FH->FileSysDevice , NULL , 0, &BigOffset , &Hevent ,&IoStatusBlock) ;
	if (!Irp)
		return STATUS_INSUFFICIENT_RESOURCES;

	irpSp = IoGetNextIrpStackLocation(Irp);
	irpSp->FileObject = FH->FileObject;
	irpSp->DeviceObject = FH->FileSysDevice ;

	status = IoCallDriver(
		FH->FileSysDevice,
		Irp);

	if (status == STATUS_PENDING)
	{
		KeWaitForSingleObject( &Hevent ,Executive ,KernelMode ,FALSE , NULL);
	}

	return IoStatusBlock.Status;

}
//--------------------------------------------------------------------------------------------------------------------
NTSTATUS WriteByIRPFromFileObject (IN PFileHandle FH, UCHAR  *Buffer , PULONG Size , LARGE_INTEGER  *Offset )
{
	NTSTATUS Status;
	PIO_STACK_LOCATION NextIrpStack;
	IO_STATUS_BLOCK IoStatusBlock;
	PIRP WriteIrp ;
	KEVENT Hevent;
	LARGE_INTEGER BigOffset = {0} ;
	PAGED_CODE () ;
	__try
	{
		if (FH->FileSysDevice->DriverObject->FastIoDispatch->FastIoWrite(FH->FileObject ,((LARGE_INTEGER*) (&Offset)) , *Size , TRUE , 0 , Buffer, &IoStatusBlock , FH->FileSysDevice ) != FALSE )
		{
			return STATUS_SUCCESS ;
		}
	
		KeInitializeEvent(&Hevent, SynchronizationEvent, FALSE); 	
		WriteIrp = IoBuildSynchronousFsdRequest ( IRP_MJ_WRITE , FH->FileSysDevice ,Buffer ,*Size , &BigOffset, &Hevent ,&IoStatusBlock) ;
		WriteIrp->RequestorMode = KernelMode;
		WriteIrp->UserIosb = &IoStatusBlock;

		NextIrpStack = IoGetNextIrpStackLocation(WriteIrp);
		NextIrpStack->MajorFunction = IRP_MJ_WRITE;
		NextIrpStack->MinorFunction = 0;
		NextIrpStack->DeviceObject = FH->FileSysDevice;
		NextIrpStack->FileObject = FH->FileObject;
		NextIrpStack->Parameters.Write.ByteOffset = *((LARGE_INTEGER*) (&Offset));;
		NextIrpStack->Parameters.Write.Length = *Size;
		WriteIrp->AssociatedIrp.SystemBuffer = Buffer ; 


			KeInitializeEvent(
				&Hevent,
				NotificationEvent,
				FALSE);



			IoSetCompletionRoutine(
				WriteIrp,
				IoCompletionReadIo,
				&Hevent,
				TRUE,
				TRUE,
				TRUE);


			Status = IoCallDriver(	FH->FileSysDevice,	WriteIrp);

			if (Status == STATUS_PENDING)
			{
				KeWaitForSingleObject(&Hevent, Executive,KernelMode,	FALSE,	NULL);
			}

			Status = IoStatusBlock.Status;
			return Status;

	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		//////////////////////////////DbgBreakPoint();
		Status = GetExceptionCode();

		return Status;
	}

}
