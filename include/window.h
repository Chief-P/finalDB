#ifndef WINDOW_H
#define WINDOW_H

#include "include/types.h"
#include <stdio.h>

#ifdef WIN32
#include <windows.h>
#endif

void clear();

struct Vector{
    Int32 len;
    string  data;
};
typedef struct Vector vectorptr;

struct Window{
    Int32 X, Y;
    Int32 width, height;
};
typedef struct Window windowptr;

#endif