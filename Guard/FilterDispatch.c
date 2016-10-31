// اين فايل حاوي توابعي است که روتين هاي هندل آي آر پي هاي از آي او منجر را بر عهده دارد و ان را ها به لايه پايي ميدهد
#include "ntifs.h"
#include "FilterDispatch.h"
#include "iomonitor.h"
#include "log.h" 
#include "FileApiBYIRP.h"
#include "IFunc.h"
#include "ScanImp.h"
#include "All_Defines.h"

#ifdef ALLOC_PRAGMA
  #pragma alloc_text( PAGE, FilterDefualtRutin )
  #pragma alloc_text( PAGE, FilterCreateFileRutin )
  #pragma alloc_text( PAGE, FilterCloseFileRutin ) 
  #pragma alloc_text( PAGE, FilterReadDefualtRutin ) 
#endif

//-------------------------------------------------------------------------------
NTSTATUS FilterReadDefualtRutin (IN PDEVICE_OBJECT DeviceObject,IN PIRP Irp , PIO_STACK_LOCATION  irpStack )
{
	PDEVICE_EXTENSION_AV pdx = (PDEVICE_EXTENSION_AV) DeviceObject->DeviceExtension ;

	IoSkipCurrentIrpStackLocation(Irp);
		
	return IoCallDriver(pdx->LowerDevice, Irp);
}

//-----------------------------------------------------------------------
NTSTATUS FilterDefualtRutin (IN PDEVICE_OBJECT DeviceObject,IN PIRP Irp , PIO_STACK_LOCATION  irpStack )
{
	PDEVICE_EXTENSION_AV pdx = (PDEVICE_EXTENSION_AV) DeviceObject->DeviceExtension ;

	IoSkipCurrentIrpStackLocation(Irp);
		
	return IoCallDriver(pdx->LowerDevice, Irp);
}
//-----------------------------------------------------------------------
NTSTATUS FilterCreateFileRutin (IN PDEVICE_OBJECT DeviceObject,IN PIRP Irp , PIO_STACK_LOCATION  irpStack )// اين تابع به اعضاي فراخواني آر آي پي ايحاد فايل فراخواني ميشود 
// عمليات جسجتو فايل و تطبيق الگو در اين فايل انجام ميشود
// اين تابع در صورتي اقدام به بررسي فايل ميکند که فايل مذکور براي خواندن باز شده باشد
// به علت اهميت اين تابع قسمتهاي مهم کامنت گزاري شده است
{

	PDEVICE_EXTENSION_AV pdx = (PDEVICE_EXTENSION_AV) DeviceObject->DeviceExtension ;
	KEVENT Hevent; 
	NTSTATUS status  ;
	KEVENT CreateEnded = {0};
	ULONG CreateOptions = 0;
	ULONG CreateDisposition = 0;
	//unsigned char Entry ;
	KIRQL CurrentIRQL ; 
	UNICODE_STRING FileName ;
	WCHAR *FileNameBuf ;
//	PFileObjectEntry TempFileObjectEntry ;
	ULONG FileAttrib ; 
	BOOLEAN Directory ;
	BOOLEAN DeleteOnClose ;
	BOOLEAN PageFile ;
	BOOLEAN OpenTargetDir ;
	UINT32	u32Result;
	FileHandle fileHandel ;

	PAGED_CODE();	

	CreateOptions = ((irpStack->Parameters.Create.Options) & 0x00FFFFFF); 
	Directory = (CreateOptions & FILE_DIRECTORY_FILE)? TRUE:FALSE; 
	DeleteOnClose = (CreateOptions & FILE_DELETE_ON_CLOSE)? TRUE: FALSE;
	PageFile = (irpStack->Flags & SL_OPEN_PAGING_FILE) ? TRUE: FALSE;
	OpenTargetDir = (irpStack->Flags & SL_OPEN_TARGET_DIRECTORY) ? TRUE : FALSE;
	CreateDisposition = ((irpStack->Parameters.Create.Options >> 24)&0xFF); 


	if (PageFile || Directory || OpenTargetDir || (( PDEVICE_EXTENSION_AV )DeviceObject->DeviceExtension)->MODEL != VolumeMounted  ) // براي با پس کردن فايل هاي از نوع دايکتوري و مپ شده در داخل حافظه 
	{
		return FilterDefualtRutin(DeviceObject , Irp , irpStack);
	}
	if (!(irpStack->Parameters.Create.SecurityContext->DesiredAccess & FILE_READ_DATA) && !(irpStack->Parameters.Create.SecurityContext->DesiredAccess & FILE_EXECUTE)) // بررسي ميکند که حتما براي خواندن بار شده باشد
	{
		return FilterDefualtRutin(DeviceObject , Irp , irpStack);
	}

	if ((CreateDisposition == FILE_OVERWRITE_IF || CreateDisposition == FILE_OVERWRITE ||
		  CreateDisposition == FILE_SUPERSEDE ||
		  CreateDisposition == FILE_CREATE ) && DeleteOnClose ) // براي فايل	هايي که در زمان بسته شده هندل ازبين ميرود بررسي ميشود که اگر به صورتي باشد که باز شده فايل مستلزم ايجاد فايل جديد باشد در نتيجه ميبايد باي پس شود
	{
		return FilterDefualtRutin(DeviceObject , Irp , irpStack);
	}

	if (BooleanFlagOn(CreateOptions,FILE_COMPLETE_IF_OPLOCKED )) // در اکثر مواقع براي کنترل بافر سمت کلاينت در حالتي که درخواست از سيستم ديگري موجود در شبکه باشد سيستم از اين فلگ استفاده ميکند 
		// در حال حاضر ما حالت را باي پس کرده وان شالله تا به بعد پيرامون اين حالت تحقيقات بيشتري شود
	{
		return FilterDefualtRutin(DeviceObject , Irp , irpStack);
	}
	if (BooleanFlagOn(CreateOptions, FILE_OPEN_BY_FILE_ID)) //اين حالت توسط برنامه هاي خاصي مانند وب سرور ها و يا فايل سرور ها براي سرعت بخشي به عمليات باز کردن فايل استفاده ميشود. بنا بر عملکرد 
		// مثال عمل کرده تا ان شا الله تا در زمان مقدور به بررسي بيشتر آن به پردازيم
	{
		Irp->IoStatus.Status      = STATUS_NOT_SUPPORTED;
		Irp->IoStatus.Information = 0;
		IoCompleteRequest( Irp, IO_NO_INCREMENT );
		return STATUS_NOT_SUPPORTED ;
	}

	if ( CreateDisposition == FILE_OVERWRITE_IF || 
		 CreateDisposition == FILE_OVERWRITE ||
		 CreateDisposition == FILE_CREATE ) //در زماني که بار کردن فايل منجر به ايجاد يک فايل جديد شود در حال حاضر باي پس ميشود ولي کن روتين کامنت شده 
		 // فايل آبجکت را در درون جدول هشي قرار ميدهد تا در زمان بست فايل آن را بررسي کند که هم اکنون به صورت کامنت شده در آمده در نتيجه ويروس در اين حالت ميتواند ايجاد و يا در داخل فايل به نوشته شود 
		 // و تنها امکان خوانده شدن ندارد 
	{
		/* Entry = ((ULONG)irpStack->FileObject) & 0x000000FF ; 	
		 ExAcquireFastMutex (&GV.gbAllocLookAside)  ;
		 TempFileObjectEntry = ExAllocateFromNPagedLookasideList(&GV.NPLLHashTableEntry);
		 ExReleaseFastMutex  (&GV.gbAllocLookAside)  ;
		 if (!TempFileObjectEntry)
		 {
			PutLog (L"Can not Alloc Memory for make hash table Enty" , STATUS_INSUFFICIENT_RESOURCES) ;
			return FilterDefualtRutin(DeviceObject , Irp , irpStack);
		 }

		 TempFileObjectEntry->FileObject = irpStack->FileObject ;

		 KeAcquireSpinLock ( &(GV.FileObjectHashTeble[Entry].ObjectListSpinLock) , &CurrentIRQL );
		 InsertTailList(&(GV.FileObjectHashTeble[Entry].FileObjectHashTeble) , &(TempFileObjectEntry->Entry)) ;
		 KeReleaseSpinLock ( &(GV.FileObjectHashTeble[Entry].ObjectListSpinLock) , CurrentIRQL );*/
		 
		 return FilterDefualtRutin(DeviceObject , Irp , irpStack);
	}
	
	KeInitializeEvent( &CreateEnded,  NotificationEvent, FALSE); 

	IoCopyCurrentIrpStackLocationToNext (Irp);

	IoSetCompletionRoutine (Irp , IoCompletionCreateFileIo , &CreateEnded , TRUE ,TRUE , TRUE  ) ;

	status = IoCallDriver( pdx->LowerDevice , Irp);


	if (status == STATUS_PENDING)
	{
		KeWaitForSingleObject( &CreateEnded, Executive, KernelMode, FALSE, NULL);
	}
	if ( CreateDisposition == FILE_OPEN_IF && Irp->IoStatus.Information == FILE_CREATED ) // در زماني که فايل با فلگي اگر باشد باز ميشود و اگر نباشد ساخته ميشود و اگر ساخته شده باشد باز باي پس ميشود
	{
		Irp->IoStatus.Status = status;
		IoCompleteRequest(Irp, IO_NO_INCREMENT);
		return status;	
	}
	
    if (NT_SUCCESS(status) && !(FlagOn (irpStack->FileObject->Flags , FO_REMOTE_ORIGIN )) && !(FlagOn (irpStack->FileObject->Flags , FO_VOLUME_OPEN )) &&
							  !(FlagOn (irpStack->FileObject->Flags , FO_DIRECT_DEVICE_OPEN )) && !(FlagOn (irpStack->FileObject->Flags , FO_HANDLE_CREATED ))) // در اين جا شروطي که 
							  // بررسي ميشود که قبل از بررسي فايل انجام ميشود
							  // اين شروط شامل : موفقيت عمليات ايجاد 
							  // فايل در داخل کامپيوتر جاري باشدو از درون شبکه باز نشده باشد
							  // فايل باشد و درايو نباشد
							  // ديواس نباشد
							  // قبلا هندلي از آن موجود نباشد
	{
		PWCHAR TempPoniter ;
		unsigned char NameBuffer[NameInformationBefferSize]  ;

		{
			{
				fileHandel.FileObject = irpStack->FileObject ; 
				fileHandel.FileSysDevice = pdx->LowerDevice ; 
				fileHandel.wsFileName = ((PFILE_NAME_INFORMATION)NameBuffer)->FileName;
				fileHandel.wsDosDeviceName = pdx->DosDeviceName;

				status = IRPGetFileName(&fileHandel, NameBuffer) ;  // نام فايل در اينجا بدست ميآيد 
				// نام فايل را نيز ميتوان ازفايل آبجکت به بدست آورد
				// ولي به دليل اينکه نام در فايل آبجکت پس از عمليات ايجاد معتبر نميباشد در نتيجه از اين تابع استفاده کرديم 
				// البته ميتوان قبل از فراخواني سطوح پايي نام را از فايل آبجکت خواند ولي خوب نکرديم و ديگر هيج
				
				//PutLog (FileNameBuf , status) ;
				if (!NT_SUCCESS(status))
				{
					PutLog (L"Can not get name" , status) ;
					status = Irp->IoStatus.Status;
					IoCompleteRequest(Irp, IO_NO_INCREMENT);
					return status;
				}
				
				if ( memcmp (((PFILE_NAME_INFORMATION)NameBuffer)->FileName , L"\\$MFT" , min (((PFILE_NAME_INFORMATION)NameBuffer)->FileNameLength , sizeof ("\\$MFT"))) == 0 )// بررسي ميشود فايل جز فايل هاي فايل سيستم نباشد البته در حاضر تنها يکي از آنها بررسي ميشود که اين بايد اضافه گردد و همچنين بررسي شود نوع فايل سيستم از نوع ان تي اف اس باشد
				{
					status = Irp->IoStatus.Status;
					IoCompleteRequest(Irp, IO_NO_INCREMENT);
					return status;
				}
		

				if ( !NT_SUCCESS(IRPGetFileAttributes (&fileHandel , &FileAttrib) )  ) // اتريتبوت فايل را بدست ميآوريم
				{
					PutLog (L"Can not get file attributes" , status) ;
					status = Irp->IoStatus.Status;
					IoCompleteRequest(Irp, IO_NO_INCREMENT);
					return status;	 	
				}

				if (FileAttrib & FILE_ATTRIBUTE_DIRECTORY) // بررسي ميشود از نوع دايکتوري است يا خير البته هنوز چک نشده است که آيا داکتوري دسرسي خواندن باز ميشود 
					// به معنا که اگر ما در انتدا روتين بررسي ميکنيم که فقط با دسترسي خواندن تابع ادامه پيدا کند ايا هيچ وقت اين شرط درست ميشود 
					// و اين به دليل است شرط فقط خواندن بعد از نوشین اين شرط گذاشته شده است
				{
					PutLog (L"is Directory" , 0);
					status = Irp->IoStatus.Status;
					IoCompleteRequest(Irp, IO_NO_INCREMENT);
					return status;	 	
				}
				
				status = Irp->IoStatus.Status;

				do 
				{
					u32Result = ScanFile(&fileHandel);
				} while (u32Result == VirusAndCleaned);
				if (NT_SUCCESS(u32Result)) // عمليات بررسي فايل ايجاد شده در درون اين تابع انجام ميشود
				{
					
				/*	if (NT_SUCCESS( CleanVirus(&fileHandel , FileNameBuf , pdx->DosDeviceName)))
					{
						IoCompleteRequest(Irp, IO_NO_INCREMENT);
						return status;	
					}
					else
					{
						IoCancelFileOpen ( pdx->LowerDevice , irpStack->FileObject ) ; // با فراخواني اين تابع به فايل سيستم پيغام متوقف سازي فايل ايجاد شده داده ميشود
						CleanVirus(&fileHandel , FileNameBuf , pdx->DosDeviceName);
					}*/
					IoCancelFileOpen ( pdx->LowerDevice , irpStack->FileObject ) ;
					Irp->IoStatus.Status = STATUS_ACCESS_DENIED ;
					status = STATUS_ACCESS_DENIED ;
					Irp->IoStatus.Information = 0 ;
				}
			}
		}
	}
	else
	{
		status = Irp->IoStatus.Status;
	}
	
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

	return status;	

}
//----------------------------------------------------------------------------------------
NTSTATUS  IoCompletionCreateFileIo( PDEVICE_OBJECT  DeviceObject,PIRP  Irp, PVOID  Context ) 
{
	if (Irp->PendingReturned)
	{
		KeSetEvent((PKEVENT) Context, IO_NO_INCREMENT, FALSE);
	}

	return STATUS_MORE_PROCESSING_REQUIRED;
}
//---------------------------------------------------------------------------------------------
// در زماني که فايل سيستم جديدي و يا واليومي جديدي مونت شود اين تابع توسط آي او منيجر فراخواني ميشود
NTSTATUS FilterFSControl ( PDEVICE_OBJECT DeviceObject, PIRP Irp , PIO_STACK_LOCATION  irpStack )
{
	NTSTATUS status  ;
	switch (irpStack->MinorFunction)
	{
		case IRP_MN_MOUNT_VOLUME :
			  status = CtrlMountVolume (DeviceObject , Irp , irpStack) ;
			break ;
		case IRP_MN_LOAD_FILE_SYSTEM:
			  status = CtrlLoadFs (DeviceObject , Irp , irpStack) ;
			break;
		default:
			status = FilterDefualtRutin(DeviceObject , Irp , irpStack) ;
			break ;
	}
	
	return status ;
}
//--------------------------------------------------------------------------------------------
// اين تابع در زمان بسته شدن فايل فراخواني شده 
// توضيحات قسمتهاي کامنت شده در روتين ايجاد فايل آورده شده است 
NTSTATUS FilterCloseFileRutin (IN PDEVICE_OBJECT DeviceObject,IN PIRP Irp , PIO_STACK_LOCATION  irpStack ) 
{
	ULONG index ;
	KIRQL CurrentIRQL ; 
	PLIST_ENTRY ListEntry ;
	PFileObjectEntry TempNode ;
	//NTSTATUS status = STATUS_SUCCESS ;
	//WCHAR *Name , *wcsQustoinMark = L"\\?";
	FileHandle FH ;
	//PDEVICE_EXTENSION_AV pdx = (PDEVICE_EXTENSION_AV) DeviceObject->DeviceExtension ;

 	PAGED_CODE();	
	/*index = ((ULONG)irpStack->FileObject)& 0x000000ff	;
	KeAcquireSpinLock ( &((*(GV.FileObjectHashTeble+index)).ObjectListSpinLock) , &CurrentIRQL );

	ListEntry = (*(GV.FileObjectHashTeble+index)).FileObjectHashTeble.Flink;
	
	while (ListEntry != &(*(GV.FileObjectHashTeble+index)).FileObjectHashTeble )
	{
		 TempNode = CONTAINING_RECORD ( ListEntry , FileObjectEntry , Entry ) ; 	
		 if ( TempNode->FileObject == irpStack->FileObject )
		 {
			RemoveEntryList(ListEntry);
			KeReleaseSpinLock ( &((*(GV.FileObjectHashTeble+index)).ObjectListSpinLock) , CurrentIRQL );
			ExAcquireFastMutex (&GV.gbAllocLookAside)  ;
			ExFreeToNPagedLookasideList (&GV.NPLLHashTableEntry , TempNode);
			ExReleaseFastMutex (&GV.gbAllocLookAside)  ;
			return FilterDefualtRutin(DeviceObject , Irp , irpStack);		
		 }
		 ListEntry = ListEntry->Flink ;
	}

	KeReleaseSpinLock ( &((*(GV.FileObjectHashTeble+index)).ObjectListSpinLock) , CurrentIRQL );
	*/

	return FilterDefualtRutin(DeviceObject , Irp , irpStack);		
	
}