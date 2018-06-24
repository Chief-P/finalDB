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

boolean writeDB(bookptr book)
{
	Int32 i;
    boolean isWrite = true;
	for (i = 0; i < MAXFILE; ++i)
	{
		if (!isFileExisted)
		{
			char postFix[2] = {i + '0', '\0'};
			string fileName = strcat("dat", postFix);
			Int32 fileID = AddFile(pool, fileName, WBIN);
			Int32 header = 1;
			if (WriteFile(pool, header, fileID, sizeof(header), 0, 0))
			{
				isWrite = false;
				puts("Fatal error: Fail to write file!");
				break;
			}
			if (AppendFile(pool, book, fileID, sizeof(book)))
				puts("Fatal error: Fail to append file!");
			if (CloseFile(pool, fileID))
				puts("Fatal error: Fail to close file!");
			break;
		}
		else if (!isFileFull[i])
		{
			char postFix[2] = {i + '0', '\0'};
			string fileName = strcat("dat", postFix);
			Int32 fileID = AddFile(pool, fileName, ABIN);
			if (AppendFile(pool, book, fileID, sizeof(book)))
				puts("Fatal error: Fail to append file!");
			if (CloseFile(pool, fileID))
				puts("Fatal error: Fail to close file!");
			break;
		}
	}
	if (i == MAXFILE)
	{
		puts("Fatal error: DB is full!");
		return;
	}
}