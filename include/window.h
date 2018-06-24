#ifndef WINDOW_H
#define WINDOW_H

#include "include/types.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MaxVector 1024

#ifdef WIN32
#include <windows.h>
#endif

void _ResetCursor();

struct Vector{
    Int32   X, Y;
    Int32   Len;
    string  data;
};
typedef struct Vector *vectorptr;

vectorptr CreateVector(Int32 X, Int32 Y, Int32 len, string data);

void FreeVector(vectorptr vector);

void FillVector(vectorptr vector, char ch);

struct Window{
    Int32           X, Y;
    Int32           width, height;
    string          winin;
    Int32           vectornum;
    vectorptr       vectors[MaxVector];
    char            winout[256][256];
    boolean isLeaf;
};
typedef struct Window *windowptr;

windowptr CreateWindow();

void FreeWindow(windowptr window);

Int32 AddVector(windowptr window, vectorptr vector);

boolean DelVector(windowptr window, Int32 vecID);

void Draw(windowptr);

#endif