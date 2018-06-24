#include "include/myhead.h"

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
boolean isFileExisted[MAXFILE];
boolean isFileFull[MAXFILE];

int main(int argc, char const *argv[])
{
	// Initialize
	mode = INTERFACE;

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
			case INTERFACE :
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
			// case DELETE :
			// 	delete();
			// 	break;
			// case VIEW :
			// 	view();
			// 	break;
		}
	}

	// Free structure
	FreeChain(chain);
	FreeHashTable(isbnHashT);
	FreeHashTable(nameHashT);
	FreeHashTable(keywordsHashT);
	FreeHashTable(authorsHashT);
	FreeIOPool(pool);

	return 0;
}