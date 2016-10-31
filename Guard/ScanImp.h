#ifndef __SCANIMP__ 
#define __SCANIMP__
#include "iomonitor.h" 

NTSTATUS ScanFile( IN  PFileHandle FH ) ;
NTSTATUS DeleteVirus(IN PFileHandle i_pocFH);

#endif