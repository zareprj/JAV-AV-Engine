#include "FileInformation.h"
#include "SMBuffer.h"
#include "SMTypeDefine.h"

 //BOOLEAN RetrieveFilePackerType(UINT8 * i_u8Sb , UINT16 i_u16Size ,UINT32 i_u32Offset ,UINT32 i_u32Type , PJBuffer i_pocBuffer , PFileInformation  i_pocFileInfo )  ; 
 //BOOLEAN CheckPattern (PUINT8 i_u8Sb , UINT16 i_u16Size , PJBuffer i_pocBuffer );
 __inline BOOLEAN CheckPattern( PUINT8 i_u8Sb , UINT16 i_u16Size , PSMBuffer i_pocBuffer )
 {
	 UINT8 *u8Pointer ;
	 INT32  i32TempSize = i_u16Size ;
	 UINT16 u16Count = 0 ;
	 PAGED_CODE () ;
	 u8Pointer = SMGetBuffer(i_pocBuffer ,i_u16Size) ;
	 if ( u8Pointer == NULL )
	 {
		 return FALSE ;
	 }
	 do
	 {
		 while (i32TempSize > u16Count )
		 {
			 if (i_u8Sb[u16Count] == 0xFF)
			 {
				 u16Count ++ ;
				 if (i_u8Sb[u16Count] != 0xff)
				 {
					 i32TempSize -= ( i_u8Sb[u16Count] - 2 ); 
					 u8Pointer += i_u8Sb[u16Count] ; 
					 u16Count ++ ;
					 continue ;
				 }
			 }
			 if ( *u8Pointer != i_u8Sb[u16Count] ) 
			 {
				 return FALSE ;
			 }
			 u16Count ++ ;
			 u8Pointer ++ ;
		 }
		 if ( u16Count == i_u16Size )
			 break ;
		 i32TempSize = u16Count - i32TempSize ; 
		 if (i32TempSize != 0)
		 {
			 SMSetRelativePointer(i_pocBuffer , i32TempSize ) ; 
		 }
		 else
		 {
			 u16Count++;
		 }

		 i_u16Size = i_u16Size - u16Count ; 
		 i32TempSize = i_u16Size ;
		 i_u8Sb += u16Count ;
		 u16Count = 0 ;
		 ASSERT( i32TempSize >= 0 ) ; 

		 u8Pointer = SMGetBuffer( i_pocBuffer ,i32TempSize ) ;
		 if (u8Pointer == NULL)
		 {
			 return FALSE ;
		 }
	 }while (1) ;
	 return TRUE ;
 }

 UINT64  MakeCRC(INT32 i_i32Start , UINT32 i_u32Size , PFileInformation  i_pocFileInfo , PSMBuffer i_pocBuffer);
 UINT64  MakeCRC1(INT32 i_i32Start , UINT32 i_u32Size , PFileInformation  i_pocFileInfo , PSMBuffer i_pocBuffer);
 UINT64  MakeCRC2(UINT32 i_u32Size , PFileInformation  i_pocFileInfo , PSMBuffer i_pocBuffer) ;
 UINT64  MakeCRC3(INT32 i_i32Start , INT32 i_i32ExtendedOffset ,UINT32 i_u32Size , PFileInformation  i_pocFileInfo , PSMBuffer i_pocBuffer );
 UINT64  MakeCRC4(INT32 i_i32Start , INT32 i_i32ExtendedOffset ,UINT32 i_u32Size , PFileInformation i_pocFileInfo , PSMBuffer i_pocBuffer );
 UINT64  MakeCRC5(INT32 i_i32Start , UINT32 i_u32Size , PFileInformation i_pocFileInfo , PSMBuffer i_pocBuffer );
 __inline BOOLEAN RetrieveFilePackerType(UINT8 * i_u8Sb , UINT16 i_u16Size ,UINT32 i_u32Offset ,UINT32 i_u32Type , PSMBuffer i_pocBuffer , PFileInformation  i_pocFileInfo ) 
 {
	 enum 
	 {
		 DirectAccess  = 0 ,
		 ReadOffset = 1 , 
		 ReadReletiveOffset = 2 ,
	 };
	 PAGED_CODE () ;
	 if ( SMSetBufferPointer(i_pocBuffer , i_pocFileInfo->m_nEntryPointOffset)== FALSE ) 
	 {
		 return FALSE; ;
	 } 
	 switch ( i_u32Type )
	 {
	 case DirectAccess: 

		 if ( SMSetRelativePointer(i_pocBuffer , i_u32Offset) == FALSE ) 
		 {
			 return FALSE ;
		 }
		 break;
	 case ReadOffset :
		 {
			 UINT32 *pu32ReletivePointer ; 
			 if ( SMSetRelativePointer(i_pocBuffer ,i_u32Offset) == FALSE ) 
			 {
				 return FALSE ;
			 }
			 pu32ReletivePointer = SMGetBuffer(i_pocBuffer ,4) ; 
			 if (pu32ReletivePointer == NULL)
			 {
				 return FALSE ; 
			 }
			 i_u32Offset = *pu32ReletivePointer - i_pocFileInfo->m_nImageBase;
			 i_u32Offset = SMRvaToOffset(i_pocFileInfo , i_u32Offset) ;

			 if ( SMSetBufferPointer( i_pocBuffer , i_u32Offset) == FALSE ) 
			 {
				 return FALSE ;
			 }
		 }
		 break ;
	 case ReadReletiveOffset :
		 {
			 UINT32 *pu32ReletivePointer ; 
			 UINT32 u32TmpOffset = i_u32Offset + i_pocFileInfo->m_nEntryPointVirtualOffset;
			 if ( SMSetRelativePointer(i_pocBuffer , i_u32Offset) == FALSE ) 
			 {
				 return FALSE ;
			 }
			 pu32ReletivePointer = SMGetBuffer(i_pocBuffer ,4) ; 
			 if (pu32ReletivePointer == NULL)
			 {
				 return FALSE ; 
			 }
			 u32TmpOffset += *pu32ReletivePointer + 4 ;

			 u32TmpOffset = SMRvaToOffset (i_pocFileInfo , u32TmpOffset);
			 if (u32TmpOffset == (ULONG) -1 )
			 {
				 return FALSE ;
			 }
			 if ( SMSetBufferPointer(i_pocBuffer , u32TmpOffset) == FALSE ) 
			 {
				 return FALSE ;
			 }
		 }
		 break ;
	 }
	 if (CheckPattern ( i_u8Sb , i_u16Size , i_pocBuffer) == TRUE)
	 {
		 return TRUE;
	 }
	 return FALSE ;
 }

