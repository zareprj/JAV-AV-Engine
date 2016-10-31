//
//  Values are 32 bit values laid out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//
//
// Define the facility codes
//
#define FACILITY_SYSTEM                  0x0
#define FACILITY_STUBS                   0x3
#define FACILITY_RUNTIME                 0x2
#define FACILITY_IO_ERROR_CODE           0x4


//
// Define the severity codes
//
#define STATUS_SEVERITY_WARNING          0x2
#define STATUS_SEVERITY_SUCCESS          0x0
#define STATUS_SEVERITY_INFORMATIONAL    0x1
#define STATUS_SEVERITY_ERROR            0x3


//
// MessageId: ERROR_FILE_ALREADYOPEN
//
// MessageText:
//
// file is Opened already.
//
#define ERROR_FILE_ALREADYOPEN           ((DWORD)0xC0020001L)

//
// MessageId: ENUM_PROCESS_ERROR
//
// MessageText:
//
// error occurrence doing enum process.
//
#define ENUM_PROCESS_ERROR               ((DWORD)0xC0020002L)

//
// MessageId: CREATE_TREE_MODULE
//
// MessageText:
//
// error occurrence doing create Tree Module.
//
#define CREATE_TREE_MODULE               ((DWORD)0xC0020003L)

//
// MessageId: NON_ENOUGH_MEMORY
//
// MessageText:
//
// non ENOUGH memory.
//
#define NON_ENOUGH_MEMORY                ((DWORD)0xC0020004L)

//
// MessageId: NOT_MODULE_NAME
//
// MessageText:
//
// can not get module file name .
//
#define NOT_MODULE_NAME                  ((DWORD)0xC0020005L)

//
// MessageId: ENUM_SERVICE
//
// MessageText:
//
// error occurrence doing enum service .
//
#define ENUM_SERVICE                     ((DWORD)0xC0020006L)

//
// MessageId: CREATE_TREE_SERVICE
//
// MessageText:
//
// error occurrence doing create tree service .
//
#define CREATE_TREE_SERVICE              ((DWORD)0xC0020007L)

//
// MessageId: EXCEPTION_ERROR
//
// MessageText:
//
// throw a EXCEPTION  .
//
#define EXCEPTION_ERROR                  ((DWORD)0xC0020008L)

//
// MessageId: LOAD_ADVAPI32
//
// MessageText:
//
// can not load advapi library.
//
#define LOAD_ADVAPI32                    ((DWORD)0xC0020009L)

//
// MessageId: OPEN_PROCESS_TOKEN
//
// MessageText:
//
// can not open process token.
//
#define OPEN_PROCESS_TOKEN               ((DWORD)0xC002000AL)

//
// MessageId: ADJUST_TOKEN_PRIVILEGE
//
// MessageText:
//
// can not afjust token provilage.
//
#define ADJUST_TOKEN_PRIVILEGE           ((DWORD)0xC002000BL)

//
// MessageId: LOAD_PSAPI
//
// MessageText:
//
// can not load psapi library.
//
#define LOAD_PSAPI                       ((DWORD)0xC002000CL)

//
// MessageId: ENUM_PROCESS
//
// MessageText:
//
// can not enum process.
//
#define ENUM_PROCESS                     ((DWORD)0xC002000DL)

//
// MessageId: OPEN_PROCESS
//
// MessageText:
//
// can not open process.
//
#define OPEN_PROCESS                     ((DWORD)0xC002000EL)

//
// MessageId: ENUM_PROCESS_MODULE
//
// MessageText:
//
// can not enum process module.
//
#define ENUM_PROCESS_MODULE              ((DWORD)0xC002000FL)

//
// MessageId: GET_PROCESS_NAME
//
// MessageText:
//
// can not get process name.
//
#define GET_PROCESS_NAME                 ((DWORD)0xC0020010L)

//
// MessageId: GET_MODULE_KERNEL_INFORMATION
//
// MessageText:
//
// can not get KERNEL32 module information.
//
#define GET_MODULE_KERNEL_INFORMATION    ((DWORD)0xC0020011L)

//
// MessageId: GET_MODULE_INFORMATION
//
// MessageText:
//
// can not get module information.
//
#define GET_MODULE_INFORMATION           ((DWORD)0xC0020012L)

//
// MessageId: MODULE_ENTRY_ERROR
//
// MessageText:
//
// In module list found a null entry.
//
#define MODULE_ENTRY_ERROR               ((DWORD)0xC0020013L)

//
// MessageId: SERVICE_ENTRY_ERROR
//
// MessageText:
//
// In service list found a null entry.
//
#define SERVICE_ENTRY_ERROR              ((DWORD)0xC0020014L)

//
// MessageId: LOOKUP_PRIVILEGE_VALUE
//
// MessageText:
//
// can not Lookup privilage value.
//
#define LOOKUP_PRIVILEGE_VALUE           ((DWORD)0xC0020015L)

//
// MessageId: SET_CURRENT_DRICTORY
//
// MessageText:
//
// can not set current drictory.
//
#define SET_CURRENT_DRICTORY             ((DWORD)0xC0020016L)

//
// MessageId: FIND_FRIST_FILE
//
// MessageText:
//
// can not find frist file.
//
#define FIND_FRIST_FILE                  ((DWORD)0xC0020017L)

//
// MessageId: GET_FILE_ATTRIBUTE
//
// MessageText:
//
// can not get file Attribute.
//
#define GET_FILE_ATTRIBUTE               ((DWORD)0xC0020018L)

//
// MessageId: GET_NEXT_STATE
//
// MessageText:
//
// Error get next State.
//
#define GET_NEXT_STATE                   ((DWORD)0xC0020019L)

//
// MessageId: GET_SYSTEM_DIRECTORY
//
// MessageText:
//
// Can not get system directory.
//
#define GET_SYSTEM_DIRECTORY             ((DWORD)0xC002001AL)

//
// MessageId: NAME_NOT_IMPOROVE
//
// MessageText:
//
// Can not get system directory.
//
#define NAME_NOT_IMPOROVE                ((DWORD)0xC002001BL)

//
// MessageId: CAN_NOT_OPEN_FILE
//
// MessageText:
//
// Can not Open File.
//
#define CAN_NOT_OPEN_FILE                ((DWORD)0xC002001DL)

//
// MessageId: PARAMETER_INVALID
//
// MessageText:
//
// send Parameter is invalid .
//
#define PARAMETER_INVALID                ((DWORD)0xC002001EL)

//
// MessageId: BUFFER_ERROR
//
// MessageText:
//
// Buffering take a error.
//
#define BUFFER_ERROR                     ((DWORD)0xC002001FL)

//
// MessageId: FILE_SEEK_ERROR
//
// MessageText:
//
// Error in Seek on File.
//
#define FILE_SEEK_ERROR                  ((DWORD)0xC0020020L)

//
// MessageId: FILE_READ_ERROR
//
// MessageText:
//
// Error in Read on File.
//
#define FILE_READ_ERROR                  ((DWORD)0xC0020021L)

//
// MessageId: ZIP_CANNOT_GETBYTE
//
// MessageText:
//
// Error in zip Get Byte.
//
#define ZIP_CANNOT_GETBYTE               ((DWORD)0xC0020022L)

//
// MessageId: ZIP_CANNOT_GETSHORT
//
// MessageText:
//
// Error in zip Get short.
//
#define ZIP_CANNOT_GETSHORT              ((DWORD)0xC0020023L)

//
// MessageId: ZIP_CANNOT_GETLONG
//
// MessageText:
//
// Error in zip Get long.
//
#define ZIP_CANNOT_GETLONG               ((DWORD)0xC0020024L)

//
// MessageId: ZIP_UNKNOWN_COMPRESSION_METHOD
//
// MessageText:
//
// unknown compression method.
//
#define ZIP_UNKNOWN_COMPRESSION_METHOD   ((DWORD)0xC0020025L)

//
// MessageId: ZIP_INVALID_WINDOW_SIZE
//
// MessageText:
//
// invalid window size
//
#define ZIP_INVALID_WINDOW_SIZE          ((DWORD)0xC0020026L)

//
// MessageId: ZIP_INCORRECT_HEADER_CHECK
//
// MessageText:
//
// incorrect header check
//
#define ZIP_INCORRECT_HEADER_CHECK       ((DWORD)0xC0020027L)

//
// MessageId: ZIP_NEED_DICTIONARY
//
// MessageText:
//
// need dictionary
//
#define ZIP_NEED_DICTIONARY              ((DWORD)0xC0020028L)

//
// MessageId: ZIP_INCORRECT_DATA_CHECK
//
// MessageText:
//
// incorrect data check
//
#define ZIP_INCORRECT_DATA_CHECK         ((DWORD)0xC0020029L)

//
// MessageId: ZIP_INVALID_BLOCK_TYPE
//
// MessageText:
//
// invalid block type
//
#define ZIP_INVALID_BLOCK_TYPE           ((DWORD)0xC002002AL)

//
// MessageId: ZIP_INVALID_STORED_BLOCK_LENGTHS
//
// MessageText:
//
// invalid stored block lengths
//
#define ZIP_INVALID_STORED_BLOCK_LENGTHS ((DWORD)0xC002002BL)

//
// MessageId: ZIP_TOO_MANY_LENGTH_OR_DISTANCE_SYMBOLS
//
// MessageText:
//
// too many length or distance symbols
//
#define ZIP_TOO_MANY_LENGTH_OR_DISTANCE_SYMBOLS ((DWORD)0xC002002CL)

//
// MessageId: ZIP_INVALID_BIT_LENGTH_REPEAT
//
// MessageText:
//
// invalid bit length repeat
//
#define ZIP_INVALID_BIT_LENGTH_REPEAT    ((DWORD)0xC002002DL)

//
// MessageId: ZIP_OVERSUBSCRIBED_DYNAMIC_BIT_LENGTHS_TREE
//
// MessageText:
//
// oversubscribed dynamic bit lengths tree
//
#define ZIP_OVERSUBSCRIBED_DYNAMIC_BIT_LENGTHS_TREE ((DWORD)0xC002002EL)

//
// MessageId: ZIP_INCOMPLETE_DYNAMIC_BIT_LENGTHS_TREE
//
// MessageText:
//
// incomplete dynamic bit lengths tree
//
#define ZIP_INCOMPLETE_DYNAMIC_BIT_LENGTHS_TREE ((DWORD)0xC002002FL)

//
// MessageId: ZIP_OVERSUBSCRIBED_LITERAL_LENGTH_TREE
//
// MessageText:
//
// oversubscribed literal/length tree
//
#define ZIP_OVERSUBSCRIBED_LITERAL_LENGTH_TREE ((DWORD)0xC0020030L)

//
// MessageId: ZIP_INCOMPLETE_LITERAL_LENGTH_TREE
//
// MessageText:
//
// incomplete literal/length tree
//
#define ZIP_INCOMPLETE_LITERAL_LENGTH_TREE ((DWORD)0xC0020031L)

//
// MessageId: ZIP_OVERSUBSCRIBED_DISTANCE_TREE
//
// MessageText:
//
// oversubscribed distance tree
//
#define ZIP_OVERSUBSCRIBED_DISTANCE_TREE ((DWORD)0xC0020032L)

//
// MessageId: ZIP_INCOMPLETE_DISTANCE_TREE
//
// MessageText:
//
// incomplete distance tree
//
#define ZIP_INCOMPLETE_DISTANCE_TREE     ((DWORD)0xC0020033L)

//
// MessageId: ZIP_EMPTY_DISTANCE_TREE_WITH_LENGTHS
//
// MessageText:
//
// empty distance tree with lengths
//
#define ZIP_EMPTY_DISTANCE_TREE_WITH_LENGTHS ((DWORD)0xC0020034L)

//
// MessageId: ZIP_INVALID_LITERAL_LENGTH_CODE
//
// MessageText:
//
// invalid literal/length code
//
#define ZIP_INVALID_LITERAL_LENGTH_CODE  ((DWORD)0xC0020035L)

//
// MessageId: ZIP_INVALID_DISTANCE_CODE
//
// MessageText:
//
// invalid distance code
//
#define ZIP_INVALID_DISTANCE_CODE        ((DWORD)0xC0020036L)

//
// MessageId: FILE_WRITE_ERROR
//
// MessageText:
//
// Error in write on File.
//
#define FILE_WRITE_ERROR                 ((DWORD)0xC0020037L)

//
// MessageId: ZIP_CRC_DONT_MATCH
//
// MessageText:
//
// Error match crc in zip.
//
#define ZIP_CRC_DONT_MATCH               ((DWORD)0xC0020038L)

//
// MessageId: RAR_CAN_NOT_READ_MAIN_HEADER
//
// MessageText:
//
// Can :not Read Main Header.
//
#define RAR_CAN_NOT_READ_MAIN_HEADER     ((DWORD)0xC0020039L)

//
// MessageId: RAR_CAN_NOT_CREATE_TEMP_FILE
//
// MessageText:
//
// Rar : Can not Create Temp File
//
#define RAR_CAN_NOT_CREATE_TEMP_FILE     ((DWORD)0xC002003AL)

//
// MessageId: RAR_CAN_NOT_COPY_FILE_UPACK
//
// MessageText:
//
// Rar : Can not Copy File Upack
//
#define RAR_CAN_NOT_COPY_FILE_UPACK      ((DWORD)0xC002003BL)

//
// MessageId: RAR_ALLOC_TOO_BUFFER
//
// MessageText:
//
// Rar : alloc Too buffer For rar
//
#define RAR_ALLOC_TOO_BUFFER             ((DWORD)0xC002003DL)

//
// MessageId: RAR_CAN_NOT_COPY_FILE_UNPACK
//
// MessageText:
//
// Rar : Can not Copy File unpack
//
#define RAR_CAN_NOT_COPY_FILE_UNPACK     ((DWORD)0xC002003FL)

//
// MessageId: RAR_CRC_ERROR
//
// MessageText:
//
// Rar : Crc Error
//
#define RAR_CRC_ERROR                    ((DWORD)0xC0020040L)

//
// MessageId: RAR_CORRUPT_FILE_DETECTED
//
// MessageText:
//
// Rar : Corrupt file detected
//
#define RAR_CORRUPT_FILE_DETECTED        ((DWORD)0xC0020041L)

//
// MessageId: RAR_ERROR_IN_GET_CHAR
//
// MessageText:
//
// Rar : Error in Get Char
//
#define RAR_ERROR_IN_GET_CHAR            ((DWORD)0xC0020042L)

//
// MessageId: FILE_COMPERSS_PROTECT
//
// MessageText:
//
// : Pass Word Protetct
//
#define FILE_COMPERSS_PROTECT            ((DWORD)0x40020043L)

//
// MessageId: FORMATMESSAGE_ERROR
//
// MessageText:
//
// Error in format message 
//
#define FORMATMESSAGE_ERROR              ((DWORD)0xC0020044L)

//
// MessageId: CRC_ERROR
//
// MessageText:
//
// : CRC not match
//
#define CRC_ERROR                        ((DWORD)0x40020045L)

//
// MessageId: UNCOMMPESS_CROUPTED
//
// MessageText:
//
// : ?Corrupted
//
#define UNCOMMPESS_CROUPTED              ((DWORD)0x40020046L)

//
// MessageId: ZIP_FILE_FORMAT_ERROR
//
// MessageText:
//
// zip file format error 
//
#define ZIP_FILE_FORMAT_ERROR            ((DWORD)0xC0020047L)

//
// MessageId: FILE_COMMPERS_FORMAT_ERROR
//
// MessageText:
//
// : ?Error in Commpresion Fromat
//
#define FILE_COMMPERS_FORMAT_ERROR       ((DWORD)0x40020048L)

//
// MessageId: FILE_CREATE_TEMP_FILE
//
// MessageText:
//
// : ?Error in create temp file 
//
#define FILE_CREATE_TEMP_FILE            ((DWORD)0x40020049L)

//
// MessageId: CANNOT_SEARCH_DIRCTORY
//
// MessageText:
//
// : ? can not sreach dirctory
//
#define CANNOT_SEARCH_DIRCTORY           ((DWORD)0x4002004AL)

//
// MessageId: CANNOT_OPEN_THIS_FILE
//
// MessageText:
//
// : ? can not open file
//
#define CANNOT_OPEN_THIS_FILE            ((DWORD)0x4002004BL)

//
// MessageId: CANNOT_ACCESS_DEBUG
//
// MessageText:
//
// Can not access debug privilage (For better enum module)
//
#define CANNOT_ACCESS_DEBUG              ((DWORD)0x4002004CL)

//
// MessageId: CANNOT_ENUM_PROCESS
//
// MessageText:
//
// Error in enum process
//
#define CANNOT_ENUM_PROCESS              ((DWORD)0x4002004DL)

//
// MessageId: CANNOT_ENUM_SERVICE
//
// MessageText:
//
// Error in enum service
//
#define CANNOT_ENUM_SERVICE              ((DWORD)0x4002004EL)

//
// MessageId: CAN_NOT_OPEN_MODULE_FILE_NAME
//
// MessageText:
//
// ?Error in open module name;
//
#define CAN_NOT_OPEN_MODULE_FILE_NAME    ((DWORD)0xC002004FL)

//
// MessageId: CAN_NOT_GETVOLUMEPATHNAME
//
// MessageText:
//
// ?Can not GetVolumePathName;
//
#define CAN_NOT_GETVOLUMEPATHNAME        ((DWORD)0xC0020050L)

//
// MessageId: CAN_NOT_GETVOLUMEINFORMATION
//
// MessageText:
//
// ?Can not GetVolumeInformation;
//
#define CAN_NOT_GETVOLUMEINFORMATION     ((DWORD)0xC0020051L)

//
// MessageId: CAN_NOT_OPENSCMANAGER
//
// MessageText:
//
// ?Can not OpenSCManager;
//
#define CAN_NOT_OPENSCMANAGER            ((DWORD)0xC0020052L)

//
// MessageId: CONNET_TO_DEVICE
//
// MessageText:
//
// Connect to Device;
//
#define CONNET_TO_DEVICE                 ((DWORD)0x40020053L)

//
// MessageId: CAN_NOT_CONNECT_TO_DEVICE
//
// MessageText:
//
// Can not connect to device;
//
#define CAN_NOT_CONNECT_TO_DEVICE        ((DWORD)0xC0020054L)

//
// MessageId: FIND_VIRUS
//
// MessageText:
//
// A Virus Found :
// Virus found , Virus name : %1 ,File name : %2
//
#define FIND_VIRUS                       ((DWORD)0x40020055L)

//
// MessageId: CANNOT_CREATE_ZIP_ENTRY
//
// MessageText:
//
// Can not Create Zip Format
//
#define CANNOT_CREATE_ZIP_ENTRY          ((DWORD)0xC0020056L)

//
// MessageId: CANNOT_CREATE_SERVICE
//
// MessageText:
//
// Create Service failed ErrNo
//
#define CANNOT_CREATE_SERVICE            ((DWORD)0xC0020057L)

//
// MessageId: SERVICE_INSTALLED_SUCCESSFULLY
//
// MessageText:
//
// Service installed successfully
//
#define SERVICE_INSTALLED_SUCCESSFULLY   ((DWORD)0x40020058L)

//
// MessageId: CANNOT_OPEN_SERVICE
//
// MessageText:
//
// OpenService failed
//
#define CANNOT_OPEN_SERVICE              ((DWORD)0xC0020059L)

//
// MessageId: CANNOT_DELETE_SERVICE
//
// MessageText:
//
// Delete Service failed
//
#define CANNOT_DELETE_SERVICE            ((DWORD)0xC002005AL)

//
// MessageId: SERVICE_DELETE_SUCCESSFULLY
//
// MessageText:
//
// Service deleted successfully
//
#define SERVICE_DELETE_SUCCESSFULLY      ((DWORD)0x4002005BL)

//
// MessageId: START_SERVICE_FAILED
//
// MessageText:
//
// Start Service failed
//
#define START_SERVICE_FAILED             ((DWORD)0xC002005CL)

//
// MessageId: SERVICE_START_DURINGPENDING
//
// MessageText:
//
// Service start pending
//
#define SERVICE_START_DURINGPENDING      ((DWORD)0x4002005DL)

//
// MessageId: QUERYSERVICESTATUSEX_FAILED
//
// MessageText:
//
// QueryServiceStatusEx failed
//
#define QUERYSERVICESTATUSEX_FAILED      ((DWORD)0xC002005EL)

//
// MessageId: SERVICE_ALREADY_STOPPED
//
// MessageText:
//
// Service is already stopped
//
#define SERVICE_ALREADY_STOPPED          ((DWORD)0x4002005FL)

//
// MessageId: SERVICE_STOPPED_SUCCESSFULLY
//
// MessageText:
//
// Service stopped successfully
//
#define SERVICE_STOPPED_SUCCESSFULLY     ((DWORD)0x40020060L)

//
// MessageId: STOP_DEPENDENT_SERVICES
//
// MessageText:
//
// Stop Dependent Services
//
#define STOP_DEPENDENT_SERVICES          ((DWORD)0x40020061L)

//
// MessageId: SERVICE_STOP_TIMED_OUT
//
// MessageText:
//
// Service stop timed out
//
#define SERVICE_STOP_TIMED_OUT           ((DWORD)0x40020062L)

//
// MessageId: CONTROL_SERVICE_FAILED
//
// MessageText:
//
// Control Service failed
//
#define CONTROL_SERVICE_FAILED           ((DWORD)0xC0020063L)

//
// MessageId: SERVICE_STOPPED_SUCCESSFULLY
//
// MessageText:
//
// SERVICE_STOPPED_SUCCESSFULLY
//
#define SERVICE_STOPPED_SUCCESSFULLY     ((DWORD)0x40020064L)

//
// MessageId: COMMANDLINETOARGVW_FAILED
//
// MessageText:
//
// CommandLineToArgvW failed
//
#define COMMANDLINETOARGVW_FAILED        ((DWORD)0xC0020065L)

//
// MessageId: COMMANDLINETOARGVW_FAILED
//
// MessageText:
//
// CommandLineToArgvW failed
//
#define COMMANDLINETOARGVW_FAILED        ((DWORD)0xC0020066L)

//
// MessageId: RPCSERVERREGISTERIF2_FAILD
//
// MessageText:
//
// RpcServerRegisterIf2 Faild
//
#define RPCSERVERREGISTERIF2_FAILD       ((DWORD)0xC0020067L)

//
// MessageId: RPCSERVERUSEPROTSEQEP_FAILD
//
// MessageText:
//
// Rpcserveruseprotseqep Faild 
//
#define RPCSERVERUSEPROTSEQEP_FAILD      ((DWORD)0xC0020068L)

//
// MessageId: CALLING_RPCSERVERLISTEN
//
// MessageText:
//
// Calling RpcServerListen
//
#define CALLING_RPCSERVERLISTEN          ((DWORD)0xC0020069L)

//
// MessageId: RPCSERVERLISTEN_FAILD
//
// MessageText:
//
// RpcServerListen faild 
//
#define RPCSERVERLISTEN_FAILD            ((DWORD)0xC002006AL)

//
// MessageId: RPCMGMTWAITSERVERLISTEN_FAILD
//
// MessageText:
//
// Rpc mgmt waitserver listen faild
//
#define RPCMGMTWAITSERVERLISTEN_FAILD    ((DWORD)0xC002006BL)

//
// MessageId: SERVICESTOP
//
// MessageText:
//
// Service Stop
//
#define SERVICESTOP                      ((DWORD)0x4002006CL)

//
// MessageId: CREATELISTENTHREAD_FAILD
//
// MessageText:
//
// Create listen thread faild
//
#define CREATELISTENTHREAD_FAILD         ((DWORD)0xC002006DL)

//
// MessageId: PROCESSSTART
//
// MessageText:
//
// Process Start
//
#define PROCESSSTART                     ((DWORD)0x4002006EL)

//
// MessageId: PATHFORMATERROR
//
// MessageText:
//
// Path format Error
//
#define PATHFORMATERROR                  ((DWORD)0xC002006FL)

//
// MessageId: OPTIONERROE
//
// MessageText:
//
// Option Error
//
#define OPTIONERROE                      ((DWORD)0xC0020070L)

//
// MessageId: NOCOMMANDLINE
//
// MessageText:
//
// NOCOMMANDLINE
//
#define NOCOMMANDLINE                    ((DWORD)0x40020071L)

//
// MessageId: BADCOMMANDLINE
//
// MessageText:
//
// BADCOMMANDLINE
//
#define BADCOMMANDLINE                   ((DWORD)0x40020072L)

//
// MessageId: DELETE_VIRUS
//
// MessageText:
//
// A Virus Found :
// Virus delete , Virus name : %1 ,File name : %2
//
#define DELETE_VIRUS                     ((DWORD)0x40020073L)

//
// MessageId: CLEAN_VIRUS
//
// MessageText:
//
// A Virus Found :
// Virus clean , Virus name : %1 ,File name : %2
//
#define CLEAN_VIRUS                      ((DWORD)0x40020074L)

//
// MessageId: ERROR_DELETE_VIRUS
//
// MessageText:
//
// A Virus Found :
// Error virus delete , File name : %1
//
#define ERROR_DELETE_VIRUS               ((DWORD)0x40020075L)

//
// MessageId: ERROR_CLEAN_VIRUS
//
// MessageText:
//
// A Virus Found :
// Error virus clean , File name : %1
//
#define ERROR_CLEAN_VIRUS                ((DWORD)0x40020076L)

