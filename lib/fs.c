
#include "include/fs.h"

// Create a pool
IOPoolptr CreateIOPool()
{
    IOPoolptr NewPool = calloc(1, sizeof(struct IOPool));
    NewPool->_size = 0;
    NewPool->Buffer = calloc(1, 0);
    NewPool->files = calloc(1, sizeof(fileptr));
    NewPool->_filemode = calloc(1, sizeof(Int32));
    return NewPool;
}

// Free a IOPool
void FreeIOPool(IOPoolptr Pool)
{
    Int32 i = 0;
    for(i = 0; i < Pool->_size; i++){
        CloseFile(Pool, i);
    }
    free(Pool->Buffer);
    free(Pool->files);
    free(Pool->_filemode);
    free(Pool);
}

// Add a file
Int32 AddFile(IOPoolptr Pool, const string filename, Int32 filemode)
{
    if(Pool->_size == IOPoolMaxSize)return -1;
    fileptr file;
    switch(filemode){
        case RFILE: {
            file = fopen(filename, "r");
            break;
        }
        case RBIN:  {
            file = fopen(filename, "rb");
            break;
        }
        case WFILE: {
            file = fopen(filename, "w");
            break;
        }
        case WBIN:  {
            file = fopen(filename, "wb");
            break;
        }
        case WRFILE:{
            file = fopen(filename, "r+");
            break;
        }
        case WRBIN: {
            file = fopen(filename, "rb+");
            break;
        }
        case AFILE: {
            file = fopen(filename, "a+");
            break;
        }
        case ABIN:  {
            file = fopen(filename, "ab+");
            break;
        }
        default:    {
            return -1;
        }
    }
    if(!file)return -1;
    Int32 index = ++Pool->_size;
    Pool->files = (fileptr*)realloc((void*)Pool->files, sizeof(fileptr)*index);
    Pool->_filemode = (Int32*)realloc((void*)Pool->_filemode, sizeof(Int32)*index);
    Pool->files[index - 1] = file;
    Pool->_filemode[index - 1] = filemode;
    return index - 1; 
}

// Close a file
boolean CloseFile(IOPoolptr Pool, const Int32 FileID)
{
    Int32 status = fclose(Pool->files[FileID]);
    if(!status)return 0;
    return 1;
}

// Readfile
boolean ReadFileB(IOPoolptr Pool, const Int32 FileID, const Int32 size, const Int32 offset, const Int32 origin)
{
    Int32 mode = Pool->_filemode[FileID] || 0x50;
    fileptr file = Pool->files[FileID];
    if(!mode)return 1;
    if(feof(file))return 2;
    Pool->Buffer = realloc(Pool->Buffer, size + 1);
    fseek(file, offset, origin);
    Int32 _size = fread(Pool->Buffer, size, 1, file);
    if(_size != 1)return 2;
    return 0;   
}

// Readfile with user's buffer
boolean ReadFileU(IOPoolptr Pool, const Int32 FileID, const Int32 size, const Int32 offset,  const Int32 origin, Gptr buffer)
{
    Int32 mode = Pool->_filemode[FileID] || 0x50;
    fileptr file = Pool->files[FileID];
    if(!mode)return 1;
    if(feof(file))return 2;
    buffer = calloc(1 , (size + 1));
    fseek(file, offset, origin);
    Int32 _size = fread(buffer, size, 1, file);
    if(_size != 1)return 2;
    return 0;
}


// Writefile
boolean Write2File(IOPoolptr Pool, Gptr buffer ,const Int32 FileID, const Int32 size, const Int32 offset, const Int32 origin)
{
    Int32 mode = Pool->_filemode[FileID] || 0x20;
    fileptr file = Pool->files[FileID];
    if(!mode)return 1;
    Pool->Buffer = realloc(Pool->Buffer, 0);
    fseek(file, offset, origin);
    Int32 _size = fwrite(buffer, size, 1, file);
    if(_size != 1)return 2;
    return 0;  
}

boolean AppendFile(IOPoolptr Pool, Gptr buffer, const Int32 FileID, const Int32 size)
{
    Int32 mode = Pool->_filemode[FileID] || 0x60;
    fileptr file = Pool->files[FileID];
    if(!mode)return 1;
    Pool->Buffer = realloc(Pool->Buffer, 0);
    if(mode == 0x20)fseek(file, 0, SEEK_END);
    Int32 _size = fwrite(buffer, size, 1, file);
    if(_size != 1)return 2;
    return 0;
}

//------------------------------------END------------------------------------------//
