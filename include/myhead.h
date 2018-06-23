#ifndef MYHEAD_H
#define MYHEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/block.h"
#include "include/chain.h"
#include "include/fs.h"
#include "include/hash.h"
#include "include/hashStorage.h"
#include "include/stack.h"
#include "include/types.h"

// File related constants
#define FILESIZE 256
#define HEADER   1

// Book related constants
#define MAXKEYWORDS 5
#define MAXAUTHORS  5
#define LENISBN     31
#define LENNAME     31
#define LENKEYWORD  31
#define LENAUTHOR   31

// Mode
#define INTERFACE 0
#define INSERT    1
#define LOOKUP    2
#define UPDATE    3
#define DELETE    4
#define VIEW      5
#define QUIT     -1

// Clear Screen for UNIX
#define clear() printf("\e[1;1H\e[2J");

typedef char string255[32];

// Info of Book
struct Book
{
	string255 isbn;
	string255 name;
	string255 keywords[MAXKEYWORDS];
	string255 authors[MAXAUTHORS];
};
typedef struct Book *bookptr;

#endif