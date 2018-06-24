#include "myhead.h"

// Mode
extern Int32 mode;

// Chain and HashTable
extern chainptr chain;
extern hashtptr isbnHashT;
extern hashtptr nameHashT;
extern hashtptr keywordsHashT;
extern hashtptr authorsHashT;

// IO pool
extern IOPoolptr pool;
extern boolean isFileExisted[MAX_FILE_NUM];
extern boolean isFileFull[MAX_FILE_NUM];

// Get the current mode
Int32 getMode()
{
	Int32 res;
	char c;

	printf("$ ");
	c = getchar();
	getchar();

	switch (c)
	{
		case 'i' : res = INSERT; break;
		case 'l' : res = LOOKUP; break;
		case 'u' : res = UPDATE; break;
		case 'r' : res = REMOVE; break;
		case 'v' : res = VIEW; break;
		case 'q' : res = QUIT; break;
		default : res = MENU;
	}

	return res;
}

// Interface
void showInterface()
{
	clear();
	puts("|----Book Management System----|");
	puts("|------------------------------|");
	puts("|      Insert    :    i        |");
	puts("|      Lookup    :    l        |");
	puts("|      Update    :    u        |");
	puts("|      Remove    :    r        |");
	puts("|        View    :    v        |");
	puts("|        Quit    :    q        |");
	puts("|------------------------------|");
	puts("* Please enter your command");
}

// Insert UI
void insertUI(bookptr book)
{
	Int32 i;

    clear();
	puts("-----Insert Mode-----");
	puts("* Please enter the information of book");
	puts("* Press Enter to pass");

	printf("ISBN: ");
	while (!getString(book->isbn, LEN_ISBN, true, true))
	{
		puts("* Please enter a valid ISBN (13 digits)");
		printf("ISBN: ");
	}

	printf("Name: ");
	while (!getString(book->name, LEN_NAME, false, false))
	{
		puts("* Please enter a valid Name (max length 127)");
		printf("Name: ");
	}

	for (i = 0; i < MAX_KEYWORDS; ++i)
	{
		printf("Keyword %ld: ", i + 1);
		while (!getString(book->keywords[i], LEN_KEYWORD, false, true))
		{
			puts("* Please enter a valid Keyword (max length 127)");
			printf("Keyword %ld: ", i + 1);
		}
	}

	for (i = 0; i < MAX_AUTHORS; ++i)
	{
		printf("Author %ld: ", i + 1);
		while (!getString(book->authors[i], LEN_AUTHOR, false, true))
		{
			puts("* Please enter a valid Author (max length 127)");
			printf("Author %ld: ", i + 1);
		}
	}

	puts("---Successfully Inserted---");
}

void lookupUI()
{
	stackptr stack;

	clear();
	puts("-----Lookup Mode------");
	puts("* Please enter from isbn/name/keyword/author");
	
	string7 key;
	while (!getString(key, sizeof(key), false, false) 
		|| !(key[0] == 'i' || key[0] == 'n' || key[0] == 'k' || key[0] == 'a'))
		puts("* Please enter a valid Key from isbn/name/keyword/author");
	
	string127 buf;
	while (!getString(buf, sizeof(buf), false, false))
		puts("* Please enter a valid value (max length 127)");

	switch(key[0])
	{
		case 'i' :
		case 'I' :
			stack = SearchHash(isbnHashT, Hash(buf, strlen(buf), TIME33));
			break;
		case 'n' :
		case 'N' :
			stack = SearchHash(nameHashT, Hash(buf, strlen(buf), TIME33));
			break;
		case 'k' :
		case 'K' :
			stack = SearchHash(keywordsHashT, Hash(buf, strlen(buf), TIME33));
			break;
		case 'a' :
		case 'A' :
			stack = SearchHash(authorsHashT, Hash(buf, strlen(buf), TIME33));
			break;
	}

	if (stack == nullptr)
	{
		puts("---Not found in DB---");
		return;
	}

	// Display results
	
	FreeStack(stack);
}