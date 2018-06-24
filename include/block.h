#ifndef BLOCK_H
#define BLOCK_H

#include "include/types.h"
#include <stdlib.h>
#include <string.h>

struct Block{
    // Should be data
    Gptr *_data;

    // Should be the size(you should define it at it's constructed)
    Int32 _size;
};
typedef struct Block *blockptr;

/*
* create a block 
* @params (data:Gptr, size:Int32)
* @return block:blockptr
*/
blockptr CreateBlock(Gptr data, Int32 size);

/*
* free a block 
* @params block:blockptr
* @return void
*/
void FreeBlock(blockptr block);

/*
* copy data to a buffer from a block 
* @params (block:blockptr, buffer:Gptr)
* @return succ(0)/fail(1):boolean
*/
boolean GetData(blockptr block, Gptr buffer);

/*
* get the dataptr from a block (Not Recommanded) 
* @params block:blockptr
* @return data:Gptr
*/
Gptr GetPtr(blockptr block);

/*
* set the block from a buffer 
* @params (block:blockptr, buffer:Gptr, size:Int32)
* @return succ(0)/fail(1):boolean
*/
boolean SetBlock(blockptr block, Gptr buffer, Int32 size);

/*
* clear the block 
* @params (block:blockptr)
* @return void
*/
void ClearBlock(blockptr block);

//------------------------------------END------------------------------------------//
#endif