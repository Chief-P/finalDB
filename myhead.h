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
#define MAX_FILE_NUM   1024
#define FILE_SIZE      364544
#define BLOCK_NUM      256
#define BLOCK_SIZE     1424
#define HEADER_POS     0
#define CONTENT_POS    1
#define HEADER_SIZE    4

// Book related constants
#define MAX_KEYWORDS   5
#define MAX_AUTHORS    5
#define LEN_ISBN       13
#define LEN_NAME       127
#define LEN_KEYWORD    127
#define LEN_AUTHOR     127

// Error related constants
#define ADD_FILE_ERROR

// Mode
#define MENU        0
#define INSERT      1
#define LOOKUP      2
#define UPDATE      3
#define REMOVE      4
#define VIEW        5
#define QUIT       -1

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
	string127 keywords[MAX_KEYWORDS];
	string127 authors[MAX_AUTHORS];
};
typedef struct Book *bookptr;

// Operation
void insert();
void lookup();

// UI
Int32 getMode();
void showInterface();
void insertUI(bookptr book);

// DB IO
boolean writeToDB(bookptr book);

// Hash Ad
boolean addToHash(bookptr book);

#endif