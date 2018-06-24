#ifndef FS_H
#define FS_H

#include <stdio.h>
#include <stdlib.h>
#include "include/types.h"
#define IOPoolMaxSize 1024
typedef FILE *fileptr;

#define     RFILE      0x11 // 00010001
#define     RBIN       0x12 // 00010010
#define     WFILE      0x21 // 00100001
#define     WBIN       0x22 // 00100010
#define     WRFILE     0x31 // 00110001
#define     WRBIN      0x32 // 00110010
#define     AFILE      0x41 // 01000001
#define     ABIN       0x42 // 01000010

struct IOPool{
    Int32       _size;
    
    // Read/Write buffer 
    // Warning: when do anything in this pool this buffer would be flushed 
    Gptr        Buffer;
    
    // files should be here
    fileptr     *files;
    
    // filemodes
    Int32      *_filemode;
};
typedef struct IOPool *IOPoolptr;

/*
* Create a IOPool
* @ params void
* @ return Pool:IOpoolptr
*/
IOPoolptr CreateIOPool();

/*
* Destroy a IOPool
* @ params Pool:IOPoolptr
* @ return void
*/
void FreeIOPool(IOPoolptr Pool);

/*
* Add a file to the pool
* @ params filename:string
* @ return fail(-1)/FileID:Int32
*/
Int32 AddFile(IOPoolptr Pool,const string filename, Int32 filemode);

/*
* Close a file from the pool
* @ params FileID:Int32
* @ return succ(0)/fail(>=1):boolean
*/
boolean CloseFile(IOPoolptr Pool, const Int32 FileID);

/*
* Read to buffer 
* @ params (FileID:Int32, size:Int32, offset:Int32, origin:Int32)
* @ return succ(0)/fail(>=1):boolean
*/
boolean ReadFile(IOPoolptr Pool, const Int32 FileID, const Int32 size, const Int32 offset,  const Int32 origin);

/*
* Read to custom buffer 
* @ params (FileID:Int32, size:Int32, offset:Int32, origin:Int32, buffer:Gptr)
* @ return succ(0)/fail(>=1):boolean
*/
boolean ReadFileU(IOPoolptr Pool, const Int32 FileID, const Int32 size, const Int32 offset,  const Int32 origin, Gptr buffer);

/*
* Write from a buffer 
* @ params (buffer:Gptr, FileID:Int32, size:Int32, offset:Int32, origin:Int32)
* @ return succ(0)/fail(>=1):boolean
*/
boolean Write2File(IOPoolptr Pool, Gptr buffer ,const Int32 FileID, const Int32 size, const Int32 offset, const Int32 origin);

/*
* Append from a buffer 
* @ params (buffer:Gptr, FileID:Int32, size:Int32)
* @ return succ(0)/fail(>=1):boolean
*/
boolean AppendFile(IOPoolptr Pool, Gptr buffer, const Int32 FileID, const Int32 size);

//------------------------------------END------------------------------------------//
#endif