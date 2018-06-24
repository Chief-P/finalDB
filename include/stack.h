#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <string.h>
#include "include/types.h"

#define StackMaxLen 16

struct Stack{
    // the Int32 data
    // It should be the index of something
    Int32 *index;

    // the current size
    Int32 cur;

    // the max size of current stack
    Int32 size;
};
typedef struct Stack *stackptr;


/*
* create a Int32 stack
* @ params void
* @ return stack:stackptr
*/
stackptr CreateStack();

/*
* free a Int32 stack
* @ params stack:stackptr
* @ return void
*/
void FreeStack(stackptr stack);

/*
* expand a stack (It shouldn't be used as a puclic method)
* @params stack:stackptr
* @return void
*/
void _ExpandStack(stackptr stack);

/*
* reduce a stack (It shouldn't be used as a puclic method)
* @params stack:stackptr
* @return void
*/
void _ReduceStack(stackptr stack);

/*
* push to a stack
* @ params (stack:stackptr, val:Int32)
* @ return void
*/
void Push(stackptr stack, Int32 val);

/*
* pop an element
* @ params stack:stackptr
* @ return val:Int32
*/
Int32 Pop(stackptr stack);

/*
* determine if a stack is empty
* @ params stack:stackptr
* @ return empty
*/
boolean Empty(stackptr stack);

//------------------------------------END------------------------------------------//

#endif