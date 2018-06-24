#include "myhead.h"

// Mode
Int32 mode;

// Chain and HashTable
chainptr chain;
hashtptr isbnHashT;
hashtptr nameHashT;
hashtptr keywordsHashT;
hashtptr authorsHashT;

// IO pool
IOPoolptr pool;
boolean isFileExisted[MAX_FILE_NUM];
boolean isFileFull[MAX_FILE_NUM];

int main(int argc, char const *argv[])
{
	// Initialize
	mode = MENU;

    chain = CreateChain();
    isbnHashT = CreateHashTable();
    nameHashT = CreateHashTable();
    keywordsHashT = CreateHashTable();
    authorsHashT = CreateHashTable();

	pool = CreateIOPool();

    readAllFile();
    
	showInterface();

	while (1)
	{
		mode = getMode();

		if (mode == QUIT)
			break;

		switch (mode)
		{
			case MENU :
				showInterface();
				break;
			case INSERT :
				insert();
				break;
			case LOOKUP :
				lookup();
				break;
			// case UPDATE :
			// 	update();
			// 	break;
			// case REMOVE :
			// 	delete();
			// 	break;
			// case VIEW :
			// 	view();
			// 	break;
		}
	}

	puts("OK");

	// Free structure
	FreeChain(chain);
	FreeHashTable(isbnHashT);
	FreeHashTable(nameHashT);
	FreeHashTable(keywordsHashT);
	FreeHashTable(authorsHashT);
	FreeIOPool(pool);

	return 0;
}