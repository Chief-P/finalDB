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

boolean addToHash(bookptr book)
{
    Int32 i;

    blockptr block = CreateBlock(book, sizeof(struct Book));
	Int32 index = AddChain(chain, block);

    AddHash(isbnHashT, Hash(book->isbn, strlen(book->isbn), TIME33), index);
    AddHash(nameHashT, Hash(book->name, strlen(book->name), TIME33), index);
    for (i = 0; i < MAX_KEYWORDS; ++i)
        AddHash(keywordsHashT, Hash(book->keywords[i], strlen(book->keywords[i]), TIME33), index);
    for (i = 0; i < MAX_AUTHORS; ++i)
        AddHash(authorsHashT, Hash(book->authors[i], strlen(book->authors[i]), TIME33), index);
    
    return true; // To be improved, value should include file index
}

boolean compare(blockptr dst, blockptr param)
{
    
}