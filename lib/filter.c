#include "include/filter.h"

stackptr Filter(stackptr Src, chainptr chain, Callback _cmp, blockptr param)
{
    if(Src == nullptr)return nullptr;
    stackptr temp = CreateStack();
    Int32 u;
    blockptr block;
    while(!Empty(Src)){
        u = Pop(Src);
        block = GetChain(chain, u);
        if(_cmp(block, param)){
            Push(temp, u);
        }
    }
    return temp;
}

//------------------------------------END------------------------------------------//
