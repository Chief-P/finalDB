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
	boolean isWrite, isAdd;

	// User interface: Get info
	insertUIGet(book);

	isWrite = writeToDB(book);

	// Synchronized ram and hdd op
	if (isWrite)
		isAdd = add2ChainHash(book);

	if (isWrite && !isAdd)
		deleteFromDB(book);

	free(book);

	// Return message
	insertUIReturn(isWrite && isAdd);
}

void lookup()
{
	Int32 res[MAX_RESULT_NUM];
	Int32 length;

	// User interface: Head
	lookupUIHead();

	// User interface: Core operation
	length = lookupUICore(res);

	// Return message
	lookupUIReturn(length);
}

void delete()
{
    bookptr book = calloc(1, sizeof(struct Book));
	Int32 index;
	boolean isSuc;

	// User interface： Get info
	isSuc = deleteUIGet(book, &index);

	if (isSuc)
	{
		deleteFromDB(book);

		deleteFromChainHash(book, index);
	}

	free(book);

	// Return message
	deleteUIReturn(isSuc);
}

void update()
{
	bookptr book = calloc(1, sizeof(struct Book));
	Int32 index;
	boolean isGet, isUp;

	// User interface: Get info to delete
	isGet = updateUIDel(book, &index);

	if (isGet)
	{
		deleteFromDB(book);

		// Not deleted from chain in fact
		deleteFromChainHash(book, index);

		// User interface: Get info to update
		isUp = updateUIGet(book, index);
		printf("%s\n", book->isbn);
		printf("%s\n", book->name);
		printf("%s\n", book->keywords[0]);
		printf("%s\n", book->authors[0]);

		if (isUp)
		{
			writeToDB(book);

			add2ChainHash(book);
		}
	}

	free(book);
	printf("ok");

	updateUIReturn(isGet && isUp);
}