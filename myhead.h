#ifndef MYHEAD_H
#define MYHEAD_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/block.h"
#include "include/chain.h"
#include "include/fs.h"
#include "include/hash.h"
#include "include/hashStorage.h"
#include "include/stack.h"
#include "include/stringProcess.h"
#include "include/types.h"

// IO pool related constants


// File related constants
#define MAXFILENUM  1024
#define FILESIZE    364544
#define BLOCKNUM    256
#define BLOCKSIZE   1424
#define HEADERPOS   0
#define CONTENTPOS  1
#define HEADERSIZE  4

// Book related constants
#define MAXKEYWORDS 5
#define MAXAUTHORS  5
#define LENISBN     13
#define LENNAME     127
#define LENKEYWORD  127
#define LENAUTHOR   127

// Mode
#define INTERFACE 0
#define INSERT    1
#define LOOKUP    2
#define UPDATE    3
#define DELETE    4
#define VIEW      5
#define QUIT     -1

// Clear Screen for UNIX
// #define clear() printf("\e[1;1H\e[2J");

// Clear Screen for win
#define clear() system("cls");

typedef char string13[16];
typedef char string127[128];

// Info of Book
struct Book
{
	string13 isbn;
	string127 name;
	string127 keywords[MAXKEYWORDS];
	string127 authors[MAXAUTHORS];
};
typedef struct Book *bookptr;

// Operation
void insert();
void lookup();

// UI
Int32 getMode();
void showInterface();
void insertUI(bookptr book);

#endif