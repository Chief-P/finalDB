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

boolean add2ChainHash(bookptr book)
{
    Int32 i;

    blockptr block = CreateBlock(book, sizeof(struct Book));
	Int32 index = AddChain(chain, block);
    printf("%ld", index);

    AddHash(isbnHashT, Hash(book->isbn, strlen(book->isbn), TIME33), index);
    AddHash(nameHashT, Hash(book->name, strlen(book->name), TIME33), index);
    for (i = 0; i < MAX_KEYWORDS; ++i)
        AddHash(keywordsHashT, Hash(book->keywords[i], strlen(book->keywords[i]), TIME33), index);
    for (i = 0; i < MAX_AUTHORS; ++i)
        AddHash(authorsHashT, Hash(book->authors[i], strlen(book->authors[i]), TIME33), index);
    
    return true; // To be improved, value should include file index
}

boolean deleteFromChainHash(bookptr book, Int32 index)
{
    Int32 i;
    // Start from 1
    ++index;
    printf("%ld", index);
    
    DelHash(isbnHashT, Hash(book->isbn, strlen(book->isbn), TIME33), index);
    DelHash(nameHashT, Hash(book->name, strlen(book->name), TIME33), index);
    for (i = 0; i < MAX_KEYWORDS; ++i)
        DelHash(keywordsHashT, Hash(book->keywords[i], strlen(book->keywords[i]), TIME33), index);
    for (i = 0; i < MAX_AUTHORS; ++i)
        DelHash(authorsHashT, Hash(book->authors[i], strlen(book->authors[i]), TIME33), index);
    
    return true;
}

boolean compareISBN(blockptr dst, blockptr param)
{
    Int32 i;
    bookptr bufDst = calloc(1, sizeof(struct Book));
    bookptr bufParam = calloc(1, sizeof(struct Book));

    GetData(dst, bufDst);
    GetData(param, bufParam);
    
    Int32 length = sizeof(bufParam->isbn);
    for (i = 0; i < length; ++i)
        if (bufDst->isbn[i] != bufParam->isbn[i])
            return false;

    return true;
}

boolean compareName(blockptr dst, blockptr param)
{
    Int32 i;
    bookptr bufDst = calloc(1, sizeof(struct Book));
    bookptr bufParam = calloc(1, sizeof(struct Book));

    GetData(dst, bufDst);
    GetData(param, bufParam);
    
    Int32 length = sizeof(bufParam->name);
    for (i = 0; i < length; ++i)
        if (bufDst->name[i] != bufParam->name[i])
            return false;

    return true;
}

boolean compareKeyword(blockptr dst, blockptr param)
{
    Int32 i, j;
    bookptr bufDst = calloc(1, sizeof(struct Book));
    bookptr bufParam = calloc(1, sizeof(struct Book));

    GetData(dst, bufDst);
    GetData(param, bufParam);
    
    Int32 length = sizeof(bufParam->keywords[0]);
    for (i = 0; i < MAX_KEYWORDS; ++i)
        for (j = 0; j < length; ++j)
            if ((bufDst->keywords[i])[j] != (bufParam->keywords[0])[j])
                return false;

    return true;
}

boolean compareAuthor(blockptr dst, blockptr param)
{
    Int32 i, j;
    bookptr bufDst = calloc(1, sizeof(struct Book));
    bookptr bufParam = calloc(1, sizeof(struct Book));

    GetData(dst, bufDst);
    GetData(param, bufParam);
    
    Int32 length = sizeof(bufParam->authors[0]);
    for (i = 0; i < MAX_AUTHORS; ++i)
         for (j = 0; j < length; ++j)
            if ((bufDst->authors[i])[j] != (bufParam->authors[0])[j])
                return false;

    return true;
}
