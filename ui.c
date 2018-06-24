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

void ClearScreen()
{
#ifdef WIN32
	system("cls");
#elif __linux__
	printf("\033[H\033[J");
#else
	printf("Platform not supported\n");
#endif
}

// Get the current mode
Int32 getMode()
{
	Int32 res;
	string2 c;

	// Press Enter to exit
	if (mode == INSERT || mode == LOOKUP || mode == REMOVE || mode == UPDATE)
		return MENU;

	printf("$ ");
	while (!getString(c, 1, true, false))
		printf("$ ");

	switch (c[0])
	{
		case 'i' : res = INSERT; break;
		case 'l' : res = LOOKUP; break;
		case 'u' : res = UPDATE; break;
		case 'r' : res = REMOVE; break;
		// case 'v' : res = VIEW; break;
		case 'q' : res = QUIT; break;
		default : res = MENU;
	}

	return res;
}

// Interface
void showInterface()
{
	ClearScreen();
	puts("|----Book Management System----|");
	puts("|------------------------------|");
	puts("|      Insert    :    i        |");
	puts("|      Lookup    :    l        |");
	puts("|      Update    :    u        |");
	puts("|      Remove    :    r        |");
	// puts("|        View    :    v        |");
	puts("|        Quit    :    q        |");
	puts("|------------------------------|");
	puts("* Please enter your command");
}

// Insert UI
void insertUI(bookptr book)
{
	Int32 i;

    ClearScreen();
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
	blockptr param;
	bookptr book = calloc(1, sizeof(struct Book));

	ClearScreen();
	puts("-----Lookup Mode------");
	puts("* Please enter from isbn/name/keyword/author");
	
	string7 key;
	while (!getString(key, sizeof(key), false, false) 
		|| !(key[0] == 'i' || key[0] == 'n' || key[0] == 'k' || key[0] == 'a'))
		puts("* Please enter a valid Key from isbn/name/keyword/author");
	
	switch (key[0])
	{
		case 'i' :
		case 'I' :
			while (!getString(book->isbn, LEN_ISBN, false, false))
				puts("* Please enter a valid value (max length 13)");
			stack = SearchHash(isbnHashT, Hash(book->isbn, strlen(book->isbn), TIME33));
			if (stack == nullptr)
			{
				puts("---Not found in DB---");
				return;
			}
			param = CreateBlock(book, sizeof(struct Book));
			Filter(stack, chain, compareISBN, param);
			break;
		case 'n' :
		case 'N' :
			while (!getString(book->name, LEN_NAME, false, false))
				puts("* Please enter a valid value (max length 127)");
			stack = SearchHash(nameHashT, Hash(book->name, strlen(book->name), TIME33));
			if (stack == nullptr)
			{
				puts("---Not found in DB---");
				return;
			}
			param = CreateBlock(book, sizeof(struct Book));
			Filter(stack, chain, compareName, param);
			break;
		case 'k' :
		case 'K' :
			while (!getString(book->keywords[0], LEN_KEYWORD, false, false))
				puts("* Please enter a valid value (max length 127)");
			stack = SearchHash(keywordsHashT, Hash(book->keywords[0], strlen(book->keywords[0]), TIME33));
			if (stack == nullptr)
			{
				puts("---Not found in DB---");
				return;
			}
			param = CreateBlock(book, sizeof(struct Book));
			Filter(stack, chain, compareKeyword, param);
			break;
		case 'a' :
		case 'A' :
			while (!getString(book->authors[0], LEN_NAME, false, false))
				puts("* Please enter a valid value (max length 127)");
			stack = SearchHash(authorsHashT, Hash(book->authors[0], strlen(book->authors[0]), TIME33));
			if (stack == nullptr)
			{
				puts("---Not found in DB---");
				return;
			}
			param = CreateBlock(book, sizeof(struct Book));
			Filter(stack, chain, compareAuthor, param);
			break;
	}

	free(book);
	FreeBlock(param);
	FreeStack(stack);
}