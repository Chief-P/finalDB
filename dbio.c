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
extern boolean isFileExisted[MAXFILENUM];
extern boolean isFileFull[MAXFILENUM];

boolean writeDB(bookptr book)
{
	Int32 i;
	char dat[4] = "dat";

	for (i = 0; i < MAXFILENUM; ++i)
	{
		if (!isFileExisted)
		{
			char postFix[2] = {i + '0', '\0'};
			string fileName = strcat(dat, postFix);
			Int32 fileID = AddFile(pool, fileName, WBIN);
			if (fileID == -1)
			{
				puts("Fatal error: Fail to add file!");
				return false;
			}
			Int32 header = 1;
			if (WriteFile(pool, header, fileID, sizeof(header), 0, 0))
			{
				puts("Fatal error: Fail to write file!");
				return false;
			}
			isFileExisted[i] = true; // Update
			if (AppendFile(pool, book, fileID, sizeof(book)))
			{
				puts("Fatal error: Fail to append file!");
				return false;
			}
			if (CloseFile(pool, fileID))
			{
				puts("Fatal error: Fail to close file!");
				return false;
			}
			return true;
		}
		else if (!isFileFull[i])
		{
			char postFix[2] = {i + '0', '\0'};
			string fileName = strcat(dat, postFix);
			Int32 fileID = AddFile(pool, fileName, WRBIN);
			if (fileID == -1)
			{
				puts("Fatal error: Fail to add file!");
				return false;
			}
			if (AppendFile(pool, book, fileID, sizeof(book)))
			{
				puts("Fatal error: Fail to append file!");
				return false;
			}
			Int32 header;
			if (ReadFileU(pool, fileID, sizeof(header), 0, 0, header))
			{
				puts("Fatal error: Fail to read file!");
				return false;
			}
			if (WriteFile(pool, ++header, fileID, sizeof(header), 0, 0))
			{
				puts("Fatal error: Fail to write file!");
				return false;
			}
			if (header == BLOCKNUM)
				isFileFull[i] = true;
			if (CloseFile(pool, fileID))
			{
				puts("Fatal error: Fail to close file!");
				return false;
			}
			return true;
		}
	}

	puts("Fatal error: DB is full!");
	return false;
}