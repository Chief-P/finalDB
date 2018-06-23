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

#define MAXKEYWORDS 5
#define MAXAUTHORS  5
#define LENISBN     10
#define LENNAME     10
#define LENKEYWORD  20
#define LENAUTHOR   20

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

int mode = INTERFACE;

chainptr chain;
hashtptr isbnHashT;
hashtptr nameHashT;
hashtptr keywordsHashT;
hashtptr authorsHashT;

struct Book
{
	string isbn;
	string name;
	string keywords[MAXKEYWORDS];
	string authors[MAXAUTHORS];
};
typedef struct Book *bookptr;

// Get the current mode
int getMode()
{
	int res;
	char c;

	printf("$ ");
	c = getchar();
	getchar();

	switch (c)
	{
		case 'i' : res = INSERT; break;
		case 'l' : res = LOOKUP; break;
		case 'u' : res = UPDATE; break;
		case 'd' : res = DELETE; break;
		case 'v' : res = VIEW; break;
		case 'q' : res = QUIT; break;
		default : res = INTERFACE;
	}

	return res;
}

void showMenu()
{
    clear();
    puts("Read from an existed db or create a new one?");
    puts("* Read   :  r");
    puts("* Create :  c");
    puts("* Please enter your command");
}

void showInterface()
{
	clear();
	puts("|----Book Management System----|");
	puts("|------------------------------|");
	puts("|      Insert    :    i        |");
	puts("|      Lookup    :    l        |");
	puts("|      Update    :    u        |");
	puts("|      Delete    :    d        |");
	puts("|        View    :    v        |");
	puts("|        Quit    :    q        |");
	puts("|------------------------------|");
	puts("* Please enter your command");
}

void insert()
{
    bookptr book = calloc(1, sizeof(struct Book));
	Int32 i, numKeywords, numAuthors;
	char isbn[LENISBN], name[LENNAME];
	char keywords[MAXKEYWORDS][LENKEYWORD], authors[MAXAUTHORS][LENAUTHOR];

	clear();
	puts("-----Insert Mode-----");
	puts("* Please enter the information of book");
	printf("ISBN: ");
	scanf("%s", isbn);
	printf("Name: ");
	scanf("%s", name);

	printf("The number of keywords: ");
	scanf("%ld", &numKeywords);
	while (numKeywords > MAXKEYWORDS || numKeywords < 0)
	{
		puts("Please enter a valid number (0 ~ 5)");
		printf("The number of keywords: ");
		scanf("%ld", &numKeywords);
	}
	for (i = 0; i < numKeywords; ++i)
	{
		printf("Keyword %ld: ", i + 1);
		scanf("%s", keywords[i]);
	}

	printf("The number of authors: ");
	scanf("%ld", &numAuthors);
	while (numAuthors > MAXAUTHORS || numAuthors < 0)
	{
		puts("Please enter a valid number (0 ~ 5)");
		printf("The number of authors: ");
		scanf("%ld", &numAuthors);
	}
	for (i = 0; i < numAuthors; ++i)
	{
		printf("Author %ld: ", i + 1);
		scanf("%s", authors[i]);
	}
	puts("---Successfully Inserted---");

	book->isbn = isbn;
	book->name = name;
    for (i = 0; i < numKeywords; ++i)
        book->keywords[i] = keywords[i];
    for (i = 0; i < numAuthors; ++i)
        book->authors[i] = authors[i];

    blockptr block = CreateBlock(book, sizeof(struct Book));
    Uint32 hash = Hash(book->isbn, 8, TIME33);
    SetChain(chain, hash, block);
    AddHash(isbnHashT, Hash(book->isbn), 8, TIME31H);
    AddHash(nameHashT, Hash(book->name), 8, TIME31H);
    for (i = 0; i < numKeywords; ++i)
        AddHash(keywordsHashT, )
}

void lookup()
{
	clear();
	puts("Please enter the attribute of book");

}

int main(int argc, char const *argv[])
{
    chain = CreateChain();
    isbnHashT = CreateHashTable();
    nameHashT = CreateHashTable();
    keywordsHashT = CreateHashTable();
    authorsHashT = CreateHashTable();

    showMenu();
    
	showInterface();

	while (1)
	{
		mode = getMode();

		if (mode == QUIT)
			break;

		switch (mode)
		{
			case INTERFACE :
				showInterface();
				break;
			case INSERT :
				insert();
				break;
			// case LOOKUP :
			// 	lookup();
			// 	break;
			// case UPDATE :
			// 	update();
			// 	break;
			// case DELETE :
			// 	delete();
			// 	break;
			// case VIEW :
			// 	view();
			// 	break;
		}
	}

	return 0;
}