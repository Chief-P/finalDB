#include "include/block.h"

// create block
blockptr CreateBlock(Gptr data, Int32 size)
{
    blockptr block = (blockptr)calloc(1, sizeof(struct Block));
    block->_size = 0;
    if(data == nullptr)block->_data = calloc(1, 0);
    else{
        block->_size = size;
        block->_data = calloc(1, size + 1);
        memcpy(block->_data, data, size);
    }
    return block;
}

// free a block
void FreeBlock(blockptr block)
{
    free(block->_data);
    free(block);
}

// copy data to a buffer
boolean GetData(blockptr block, Gptr buffer)
{
    if(buffer == nullptr|| block == nullptr)return 1;
    memcpy(buffer, block->_data, block->_size);
    return 0;
}

// get the dataptr
Gptr GetPtr(blockptr block)
{
    if(block == nullptr)return nullptr;
    return block->_data;
}

// set a block
boolean SetBlock(blockptr block, Gptr buffer, Int32 size)
{
    if(buffer == nullptr || block== nullptr)return 1;
    block->_size = size;
    block->_data = realloc(block->_data, size + 1);
    memcpy(block->_data, buffer, size);
    return 0;
}

// clear a block
void ClearBlock(blockptr block)
{
    block->_size = 0;
    free(block->_data);
}

//------------------------------------END------------------------------------------//

