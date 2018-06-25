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
#include "include/stringProcess.h"
#include "include/filter.h"
#include "include/types.h"

// UI related constants
#define MAX_RESULT_NUM 99

// IO pool related constants


// File related constants
#define MAX_BOOK_CAP   32768
#define MAX_FILE_NUM   128
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
#define RETURN      6
#define QUIT       -1

#ifdef WIN32
#include <windows.h>
#endif

// Clear Screen for win and linux
void ClearScreen();

typedef char string2[3];
typedef char string7[8];
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

// Database operation
void insert();
void lookup();
void delete();

// UI
Int32 getMode();
void showInterface();
void showBook(bookptr book, Int32 index);
void insertUI(bookptr book);
void insertUIReturn();
void lookupUI();
void lookupUIHead();
Int32 lookupUIBody(Int32 *res);
void lookupUITail();
void deleteUI(bookptr book);
void deleteUIReturn();
// void deleteUIHead();
// void deleteUITail();

// HDD operation
void readAllFile();
boolean writeToDB(bookptr book, Uint32 *datPosPtr);
boolean deleteFromDB(bookptr book, Uint32 datPos);

// RAM operation
boolean add2ChainHash(bookptr book, Uint32 datPos);
boolean compareISBN(blockptr dst, blockptr param);
boolean compareName(blockptr dst, blockptr param);
boolean compareKeyword(blockptr dst, blockptr param);
boolean compareAuthor(blockptr dst, blockptr param);


#endif