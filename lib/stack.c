#include "include/stack.h"

// create stack
stackptr CreateStack()
{
    stackptr stack = calloc(1, sizeof(struct Stack));
    stack->index = calloc(1, sizeof(Int32));
    stack->size = stack->cur = 0;
    return stack;
}

// free stack
void FreeStack(stackptr stack)
{
    free(stack->index);
    free(stack);
}

// expand
void _ExpandStack(stackptr stack)
{
    stack->size += StackMaxLen;
    stack->index = realloc(stack->index, stack->size * sizeof(Int32));
}

// reduce
void _ReduceStack(stackptr stack)
{
    stack->size -= StackMaxLen;
    stack->index = realloc(stack->index, stack->size * sizeof(Int32));
}

// push
void Push(stackptr stack, Int32 val)
{
    if(stack->cur >= stack->size)_ExpandStack(stack);
    (stack->index)[stack->cur] = val;
    stack->cur++;
}

// pop
Int32 Pop(stackptr stack)
{
    if(stack->cur == 0)return -1;
    Int32 val = (stack->index)[--stack->cur];
    if(stack->cur <= stack->size - StackMaxLen)_ReduceStack(stack);
    return val;
}

// empty
boolean Empty(stackptr stack)
{
    return (stack->size == 0)?true : false;
}

//------------------------------------END------------------------------------------//