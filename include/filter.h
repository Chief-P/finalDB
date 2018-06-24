#ifndef FILTER_H
#define FILTER_H

#include "include/types.h"
#include "include/stack.h"
#include "include/chain.h"
#include <math.h>
#include <stdlib.h>

typedef boolean(*Callback)(blockptr dst, blockptr param);

/*
* filter the hash collision
* it should send a compare function and a param to this filter
* the compare function should return 1 if you need such data, outher wise it should return 0
* you should send a unnull stack to this function
* chain is needed which you storage the useful datas
* it will return a new stack your origin stack will be keep
* @ params  
*
*/
stackptr Filter(stackptr Src, chainptr chain, Callback _cmp, blockptr param);

//------------------------------------END------------------------------------------//
#endif