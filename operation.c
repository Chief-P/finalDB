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

void insert()
{
    bookptr book = calloc(1, sizeof(struct Book));
	Int32 i;

	// User interface
	insertUI(book);

	// Write into DB
	boolean isWrite = writeDB

	// Add to Block and HashTable
	boolean isAdd = true;
	if (!isWrite)
		return;
    blockptr block = CreateBlock(book, sizeof(struct Book));
	Int32 index = AddChain(chain, block);
    AddHash(isbnHashT, Hash(book->isbn, sizeof(book->isbn), TIME33), index);
    AddHash(nameHashT, Hash(book->name, sizeof(book->name), TIME33), index);
    AddHash(keywordsHashT, )

	// Delete from DB
	if (isAdd)
		return;
	
}

void lookup()
{
	clear();
	puts("Please enter the attribute of book");

}

void 