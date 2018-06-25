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
extern Int32 index2dat[MAX_BOOK_CAP];

void insert()
{
    bookptr book = calloc(1, sizeof(struct Book));
	Uint32 datPos;

	// User interface
	insertUI(book);

	// Write into DB
	boolean isWrite = writeToDB(book, &datPos);

	// Add to Chain and HashTable
	if (!isWrite)
		return;
	boolean isAdd = add2ChainHash(book, datPos);

	// Delete from DB
	// if (isAdd)
	// 	return;
	// deleteFromDB(book);

	free(book);

	insertUIReturn();
}

void lookup()
{
	// User interface
	lookupUI();
}

void delete()
{
    bookptr book = calloc(1, sizeof(struct Book));

	// User interface
	deleteUI(book);

	// Delete from DB
	deleteFromDB(book);

	// Remove from Chain and HashTable
	removeFromChainHash(book);

	free(book);

	deleteUIReturn();
}