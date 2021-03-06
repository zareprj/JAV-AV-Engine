#ifndef __IOCTL__
#define __IOCTL__
#define SymblicName L"\\DosDevices\\JavIomonitor" 
#ifndef CTL_CODE
  #pragma message ( \
    "CTL_CODE undefined. Include winioctl.h or wdm.h")
#endif

#define IOCTL_GET_EVENT \
	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, \
		FILE_ANY_ACCESS)

#define IOCTL_ATTACH_DEVICE \
	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_BUFFERED, \
		FILE_ANY_ACCESS)

#define IOCTL_DEATTACH_DEVICE \
	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x803, METHOD_BUFFERED, \
		FILE_ANY_ACCESS)

#define IOCTL_SET_DEVICE \
	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x804, METHOD_BUFFERED, \
	FILE_ANY_ACCESS)

#define IOCTL_DO_SCAN \
	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x805, METHOD_BUFFERED, \
	FILE_ANY_ACCESS)	

#define IOCTL_STOP_SCAN_PROCESS \
	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x806, METHOD_BUFFERED, \
	FILE_ANY_ACCESS)	

#define IOCTL_CREATE_FILE \
		 CTL_CODE(FILE_DEVICE_UNKNOWN, 0x807, METHOD_BUFFERED, \
		 FILE_ANY_ACCESS)	
#define IOCTL_WRITE_FILE \
		 CTL_CODE(FILE_DEVICE_UNKNOWN, 0x808, METHOD_BUFFERED, \
		 FILE_ANY_ACCESS)	
#define IOCTL_READ_FILE \
		 CTL_CODE(FILE_DEVICE_UNKNOWN, 0x809, METHOD_BUFFERED, \
		 FILE_ANY_ACCESS)	
#define IOCTL_SEEK_FILE \
		 CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80A, METHOD_BUFFERED, \
		 FILE_ANY_ACCESS)	
#define IOCTL_SET_END_FILE \
		CTL_CODE(FILE_DEVICE_UNKNOWN , 0x80B, METHOD_BUFFERED, \
		FILE_ANY_ACCESS)
#define  IOCTL_CLOSE_FILE \
		 CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80C, METHOD_BUFFERED, \
		 FILE_ANY_ACCESS)

#define  IOCTL_GET_FILE_SIZE \
	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80D, METHOD_BUFFERED, \
	FILE_ANY_ACCESS)

#define  IOCTL_GET_FILE_ATTRIB \
	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80E, METHOD_BUFFERED, \
	FILE_ANY_ACCESS)

#define  IOCTL_DELETE_FILE \
	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x80F, METHOD_BUFFERED, \
	FILE_ANY_ACCESS)

#define  IOCTL_OPEN_DIRCTORY \
	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x810, METHOD_BUFFERED, \
	FILE_ANY_ACCESS)

#define  IOCTL_LISE_DIRCTORY \
	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x811, METHOD_BUFFERED, \
	FILE_ANY_ACCESS)

#define  IOCTL_OPEN_TEMP_FILE \
	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x812, METHOD_BUFFERED, \
	FILE_ANY_ACCESS)

#define  IOCTL_DELETE_TEMP_FILE \
	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x813, METHOD_BUFFERED, \
	FILE_ANY_ACCESS)

#define IOCTL_GET_NAME \
	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x814, METHOD_BUFFERED, \
	FILE_ANY_ACCESS)

#define IOCTL_GET_PROCESSID \
	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x815, METHOD_BUFFERED, \
	FILE_ANY_ACCESS)

#define IOCTL_CLEAR_CONFIG \
	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x816, METHOD_BUFFERED, \
	FILE_ANY_ACCESS)

#define IOCTL_GET_CLEAN_DELETE \
	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x817, METHOD_BUFFERED, \
	FILE_ANY_ACCESS)

#define IOCTL_SET_DEMAND_CONFIG \
	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x818, METHOD_BUFFERED, \
	FILE_ANY_ACCESS)

#define IOCTL_CLEAR_DEMAND_CONFIG \
	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x819, METHOD_BUFFERED, \
	FILE_ANY_ACCESS)

#define IOCTL_SET_ONACCESS_CONFIG \
	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x820, METHOD_BUFFERED, \
	FILE_ANY_ACCESS)

#define IOCTL_CLEAN_ONACCESS_CONFIG \
	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x821, METHOD_BUFFERED, \
	FILE_ANY_ACCESS)

#endif 
