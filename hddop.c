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


boolean writeToDB(bookptr book)
{
	Int32 i;
	for (i = 0; i < MAX_FILE_NUM; ++i)
	{
		char fileName[5] = "dat ";
		if (!isFileExisted[i])
		{
			fileName[3] = (char)('0' + i);
			Int32 fileID = AddFile(pool, fileName, WBIN);
			if (fileID == -1)
			{
				puts("Fatal error: Fail to add file!");
				return false;
			}
			Int32 header = 1;
			if (Write2File(pool, header, fileID, sizeof(header), 0, 0))
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
			fileName[3] = (char)('0' + i);
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
			if (Write2File(pool, ++header, fileID, sizeof(header), 0, 0))
			{
				puts("Fatal error: Fail to write file!");
				return false;
			}
			if (header == BLOCK_NUM)
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