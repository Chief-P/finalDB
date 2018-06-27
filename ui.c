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

	if (mode == RETURN)
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

// Display the info of book
void showBook(bookptr book, Int32 index)
{
	Int32 i;

	printf("* Book [%ld]\n", index);
	if (strlen(book->isbn))
		printf("ISBN: %s\n", book->isbn);
	if (strlen(book->name))
		printf("Name: %s\n", book->name);
	for (i = 0; i < MAX_KEYWORDS; ++i)
		if (strlen(book->keywords[i]))
			printf("Keyword %ld: %s\n", i + 1, book->keywords[i]);
	for (i = 0; i < MAX_AUTHORS; ++i)
		if (strlen(book->authors[i]))
			printf("Author %ld: %s\n", i + 1, book->authors[i]);
	puts("////////////////////////////////////////////////////");
}

// Function as system("pause");
void showReturn()
{
	printf("* ");
	system("pause");
	// puts("* Press Enter to return");
	// printf("$ ");
	// string2 tmp;
	// getString(tmp, 1, false, true);
	mode = RETURN;
}

// Insert UI
void insertUIGet(bookptr book)
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
}

void insertUIReturn(boolean isSuc)
{
	if (isSuc)
		puts("---Successfully Inserted---");
	else
		puts("---Fail to insert---");

	showReturn();
}

void lookupUIHead()
{
	ClearScreen();
	puts("-----Lookup Mode------");
	puts("* Please enter a Key from isbn/name/keyword/author");
}

/*
* Core of Lookup
* Called in lookup, delete and update
* @ param: res(record list of index in chain)
* @ return: list length
*/
Int32 lookupUICore(Int32 *res)
{
	stackptr stack, filteredStack;
	blockptr param;
	bookptr book = calloc(1, sizeof(struct Book));
	Int32 i;

	string7 key;
	while (!getString(key, sizeof(key), false, false) 
		|| !(key[0] == 'i' || key[0] == 'n' || key[0] == 'k' || key[0] == 'a'))
		puts("* Please enter a valid Key from isbn/name/keyword/author");
	
	// Check initial character, not secure
	puts("* Please enter corresponding value");
	switch (key[0])
	{
		case 'i' :
		case 'I' :
			while (!getString(book->isbn, LEN_ISBN, false, false))
				puts("* Please enter a valid value (max length 13)");
			stack = SearchHash(isbnHashT, Hash(book->isbn, strlen(book->isbn), TIME33));
			if (stack == nullptr)
				return 0;
			param = CreateBlock(book, sizeof(struct Book));
			filteredStack =  Filter(stack, chain, compareISBN, param);
			break;
		case 'n' :
		case 'N' :
			while (!getString(book->name, LEN_NAME, false, false))
				puts("* Please enter a valid value (max length 127)");
			stack = SearchHash(nameHashT, Hash(book->name, strlen(book->name), TIME33));
			if (stack == nullptr)
				return 0;
			param = CreateBlock(book, sizeof(struct Book));
			filteredStack = Filter(stack, chain, compareName, param);
			break;
		case 'k' :
		case 'K' :
			while (!getString(book->keywords[0], LEN_KEYWORD, false, false))
				puts("* Please enter a valid value (max length 127)");
			stack = SearchHash(keywordsHashT, Hash(book->keywords[0], strlen(book->keywords[0]), TIME33));
			if (stack == nullptr)
				return 0;
			param = CreateBlock(book, sizeof(struct Book));
			filteredStack = Filter(stack, chain, compareKeyword, param);
			break;
		case 'a' :
		case 'A' :
			while (!getString(book->authors[0], LEN_NAME, false, false))
				puts("* Please enter a valid value (max length 127)");
			stack = SearchHash(authorsHashT, Hash(book->authors[0], strlen(book->authors[0]), TIME33));
			if (stack == nullptr)
				return 0;
			param = CreateBlock(book, sizeof(struct Book));
			filteredStack = Filter(stack, chain, compareAuthor, param);
			break;
	}

	// Output
	i = 0;
	while(!Empty(filteredStack) && i < MAX_RESULT_NUM)
	{
		res[i] = Pop(filteredStack);
		GetData(GetChain(chain, res[i]), book);
		showBook(book, i++);
	}

	free(book);
	FreeBlock(param);
	FreeStack(stack);

	return i;
}

void lookupUIReturn(boolean isSuc)
{
	if (isSuc)
		puts("---Successfully found---");
	else
		puts("---Not found in DB---");

	showReturn();
}


// Delete UI: get the to-be-deleted book
boolean deleteUIGet(bookptr book, Int32 *index)
{
	Int32 res[MAX_RESULT_NUM];
	Int32 i;

	ClearScreen();
	puts("-----Delete Mode------");
	puts("* Please enter a Key from isbn/name/keyword/author");

	const Int32 resLen = lookupUICore(res);
	if (!resLen)
		return false;

	puts("* Please enter the index of the book in the list");
	string2 iBuf;

	do
	{
		while (!getString(iBuf, 2, false, false))
			puts("* Please enter a valid i from the book list");
		i = atoi(iBuf);
		if (i >= resLen || i < 0)
			puts("* Index should be in the list above");
	} while (i >= resLen || i < 0);
	
	*index = res[i];
	GetData(GetChain(chain, *index), book);

	return true;
}

void deleteUIReturn(boolean isSuc)
{
	if (isSuc)
		puts("---Successfully deleted---");
	else
		puts("---Not found in DB---");

	showReturn();
}

boolean updateUIDel(bookptr book, Int32 *index)
{
	Int32 res[MAX_RESULT_NUM];

	ClearScreen();
	puts("-----Update Mode------");
	puts("* Please enter a Key from isbn/name/keyword/author to find the book");

	const Int32 resLen = lookupUICore(res);
	if (!resLen)
		return false;

	puts("* Please enter the index of the book in the list");
	string2 iBuf;
	Int32 i = resLen + 1;
	do
	{
		while (!getString(iBuf, 2, false, false))
			puts("* Please enter a valid value (max length 2)");
		i = atoi(iBuf);
		if (i > resLen || i < 0)
			puts("* Index should be in the list above");
	} while (i > resLen || i < 0);
		
	*index = res[i];
	GetData(GetChain(chain, *index), book);

	return true;
}

boolean updateUIGet(bookptr book, Int32 index)
{
	string1 iStr;
	Int32 i;

	puts("* Please enter the to-be-updated Key from isbn/name/keyword/author");
	string7 key;
	while (!getString(key, sizeof(key), false, false) 
		|| !(key[0] == 'i' || key[0] == 'n' || key[0] == 'k' || key[0] == 'a'))
		puts("* Please enter a valid Key from isbn/name/keyword/author");

	switch (key[0])
	{
		case 'i' :
		case 'I' :
			puts("* Please enter the new value");
			while (!getString(book->isbn, LEN_ISBN, false, false))
				puts("* Please enter a valid value (max length 13)");
			break;
		case 'n' :
		case 'N' :
			puts("* Please enter the new value");
			while (!getString(book->name, LEN_NAME, false, false))
				puts("* Please enter a valid value (max length 127)");
			break;
		case 'k' :
		case 'K' :
			puts("* Please enter the index of the keyword");
			do
			{
				while (!getString(iStr, 1, true, false))
					puts("* Please enter a valid value (max length 1)");
				i = (Int32)atoi(iStr);
				printf("%s ", iStr);
				// printf("%ld", i);
				// Fail to tell alphabet, atoi sucks
				if (i > MAX_KEYWORDS || i < 0)
					puts("* Please enter a valid index (1 ~ 5)");
			} while (i > MAX_KEYWORDS || i < 0);

			puts("* Please enter the new value");
			while (!getString(book->keywords[i - 1], LEN_KEYWORD, false, false))
				puts("* Please enter a valid value (max length 127)");
			break;
		case 'a' :
		case 'A' :
			puts("* Please enter the index of the author");
			do
			{
				while (!getString(iStr, 1, true, false))
					puts("* Please enter a valid value (max length 1)");
				i = atoi(iStr);
				if (i > MAX_AUTHORS || i < 0)
					puts("* Please enter a valid index (1 ~ 5)");
			} while (i > MAX_AUTHORS || i < 0);

			puts("* Please enter the new value");
			while (!getString(book->authors[i - 1], LEN_AUTHOR, false, false))
				puts("* Please enter a valid value (max length 127)");
			break;
	}

	return true;
}

void updateUIReturn(boolean isSuc)
{
	if (isSuc)
		puts("---Successfully updated---");
	else
		puts("---Fail to update---");

	showReturn();
}
