#ifndef CHAIN_H
#define CHAIN_H
#include "include/types.h"
#include "include/block.h"
#define ChainMaxLen 256

struct Chain{
    // the max length of the current chain
    Int32 _length;
    
    // the current index
    Int32 _index;
    
    // should be no nullptr 
    // the chain is [0...n]
    blockptr *blocks;
};
typedef struct Chain *chainptr;

/*
* create a chain 
* @params void
* @return chain:chainptr
*/
chainptr CreateChain();

/*
* free a chain 
* @params chain:chainptr
* @return void
*/
void FreeChain(chainptr chain);

/*
* expand a chain (It shouldn't be used as a puclic method)
* @params (chain:chainptr)
* @return void
*/
void _ExpandChain(chainptr chain);

/*
* add a block to the chain
* 
* you needn't expand the length of chain on your own 
* this will be automatic
* 
* @params (chain: chainptr, block: blockptr)
* @return index:Int32
*/
Int32 AddChain(chainptr chain, blockptr block);

/*
* get a ptr of a block 
* @params (chain:chainptr, pos:Int32)
* @return block:blockptr
*/
blockptr GetChain(chainptr chain, Int32 pos);

/*
* set a block to a position of a chain 
* @params (chain:chainptr, pos:Int32, block:blockptr)
* @return succ(0)/fail(>=1):boolean
*/
boolean SetChain(chainptr chain, Int32 pos, blockptr block);

/*
* swap two blocks of a chain
* @params (chain:chainptr, a:Int32, b:Int32)
* @return succ(0)/fail(>=1):boolean
*/
boolean SwapChainEle(chainptr chain, Int32 a, Int32 b);

//------------------------------------END------------------------------------------//
#endif