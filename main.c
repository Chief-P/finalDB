#include "include/myhead.h"

// Mode
int mode = INTERFACE;

// Chain and HashTable
chainptr chain;
hashtptr isbnHashT;
hashtptr nameHashT;
hashtptr keywordsHashT;
hashtptr authorsHashT;

int main(int argc, char const *argv[])
{
    chain = CreateChain();
    isbnHashT = CreateHashTable();
    nameHashT = CreateHashTable();
    keywordsHashT = CreateHashTable();
    authorsHashT = CreateHashTable();

    showMenu();
    
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
			// case LOOKUP :
			// 	lookup();
			// 	break;
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

	return 0;
}