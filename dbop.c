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

	// Add to Block and HashTable
	if (!isWrite)
		return;
	boolean isAdd = addToHash(book);

	// Delete from DB
	if (isAdd)
		return;
	// deleteFromDB(book);
}

void lookup()
{
	// User interface
	lookupUI();
}