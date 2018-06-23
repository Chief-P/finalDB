#include "include/chain.h"

// create chain
chainptr CreateChain()
{
    chainptr chain = (chainptr)calloc(1, sizeof(struct Chain));
    chain->_length = ChainMaxLen;
    chain->_index  = 0;
    chain->blocks  = (blockptr*)calloc(ChainMaxLen, sizeof(blockptr));
    return chain;
}

// free a chain
void FreeChain(chainptr chain)
{
    Int32 index = chain->_index;
    while(index){
        FreeBlock((chain->blocks)[--index]);
    }
    free(chain->blocks);
    free(chain);
}

// expand a chain
void _ExpandChain(chainptr chain)
{
    chain->_length += ChainMaxLen;
    chain->blocks = (blockptr*)realloc((Gptr)(chain->blocks), chain->_length * sizeof(blockptr));
}

// add a block
Int32 AddChain(chainptr chain, blockptr block)
{
    if(chain->_index >= chain->_length){
        _ExpandChain(chain);
    }
    Int32 index = chain->_index;
    (chain->blocks)[index] = block;
    chain->_index++;
    return chain->_index - 1;   
}

// get a block
blockptr GetChain(chainptr chain, Int32 pos)
{
    if(pos >= chain->_index)return nullptr;
    return (chain->blocks)[pos];
}

// redefine a block
boolean SetChain(chainptr chain, Int32 pos, blockptr block)
{
    if(pos >= chain->_index)return 1;
    (chain->blocks)[pos] = block;
    return 0;
}

// swap two blocks
boolean SwapChainEle(chainptr chain, Int32 a, Int32 b)
{
    if(a >= chain->_index || b >= chain->_index)return 1;
    blockptr temp = (chain->blocks)[a];
    (chain->blocks)[a] = (chain->blocks)[b];
    (chain->blocks)[b] = temp;
    return 0;
}

//------------------------------------END------------------------------------------//