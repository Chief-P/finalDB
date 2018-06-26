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

void insert()
{
    bookptr book = calloc(1, sizeof(struct Book));

	// User interface
	insertUI(book);

	// Write into DB
	boolean isWrite = writeToDB(book);

	// Add to Chain and HashTable
	if (!isWrite)
		return;
	boolean isAdd = add2ChainHash(book);

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
	Int32 index;

	// User interface
	deleteUI(book, index);

	// Delete from DB
	deleteFromDB(book);

	// Remove from Chain and HashTable
	deleteFromChainHash(book, index);

	free(book);

	deleteUIReturn();
}

void update()
{
	bookptr book = calloc(1, sizeof(struct Book));
	Int32 index;

	updateUIDel(book, index);

	deleteFromDB(book);

	deleteFromChainHash(book, index);

	updateUI(book, index);

	writeToDB(book);

	add2ChainHash(book);

	free(book);

	updateUIReturn();
}