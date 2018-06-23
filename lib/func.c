#include "include/myhead.h"

// Mode
extern int mode = INTERFACE;

// Chain and HashTable
extern chainptr chain;
extern hashtptr isbnHashT;
extern hashtptr nameHashT;
extern hashtptr keywordsHashT;
extern hashtptr authorsHashT;

void insert()
{
    bookptr book = calloc(1, sizeof(struct Book));
	Int32 i, numKeywords, numAuthors;

	clear();
	puts("-----Insert Mode-----");
	puts("* Please enter the information of book");
	printf("ISBN: ");
	scanf("%s", book->isbn);
	printf("Name: ");
	scanf("%s", book->name);

	printf("The number of keywords: ");
	scanf("%ld", &numKeywords);
	while (numKeywords > MAXKEYWORDS || numKeywords < 1)
	{
		puts("Please enter a valid number (1 ~ 5)");
		printf("The number of keywords: ");
		scanf("%ld", &numKeywords);
	}
	for (i = 0; i < numKeywords; ++i)
	{
		printf("Keyword %ld: ", i + 1);
		scanf("%s", book->keywords[i]);
	}

	printf("The number of authors: ");
	scanf("%ld", &numAuthors);
	while (numAuthors > MAXAUTHORS || numAuthors < 1)
	{
		puts("Please enter a valid number (1 ~ 5)");
		printf("The number of authors: ");
		scanf("%ld", &numAuthors);
	}
	for (i = 0; i < numAuthors; ++i)
	{
		printf("Author %ld: ", i + 1);
		scanf("%s", book->authors[i]);
	}
	puts("---Successfully Inserted---");

    blockptr block = CreateBlock(book, sizeof(struct Book));
	Int32 index = AddChain(chain, block);
    AddHash(isbnHashT, Hash(book->isbn, sizeof(book->isbn), TIME33), index);
    AddHash(nameHashT, Hash(book->name, sizeof(book->name), TIME33), index);
    for (i = 0; i < numKeywords; ++i)
        AddHash(keywordsHashT, )
}

void lookup()
{
	clear();
	puts("Please enter the attribute of book");

}