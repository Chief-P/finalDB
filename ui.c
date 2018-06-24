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
extern boolean isFileExisted[MAXFILE];
extern boolean isFileFull[MAXFILE];

void insertUI(bookptr book)
{
    clear();
	puts("-----Insert Mode-----");
	puts("* Please enter the information of book");
	puts("* Press Enter if not existed");

	printf("ISBN: ");
	while (!getString(book->isbn, LENISBN, true, true))
	{
		puts("* Please enter a valid ISBN (13 digits)");
		printf("ISBN: ");
	}

	printf("Name: ");
	while (!getString(book->name, LENNAME, false, false))
	{
		puts("* Please enter a valid Name (max length 127)");
		printf("Name: ");
	}

	for (i = 0; i < MAXKEYWORDS; ++i)
	{
		printf("Keyword %ld: ", i + 1);
		while (!getString(book->keywords[i], LENKEYWORD, false, true))
		{
			puts("* Please enter a valid Keyword (max length 127)");
			printf("Keyword %ld: ", i + 1);
		}
	}

	for (i = 0; i < MAXAUTHORS; ++i)
	{
		printf("Author %ld: ", i + 1);
		while (!getString(book->authors[i], LENAUTHOR, false, true))
		{
			puts("* Please enter a valid Author (max length 127)");
			printf("Author %ld: ", i + 1);
		}
	}

	puts("---Successfully Inserted---");
}