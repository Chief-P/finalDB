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

// void readFileTable()
// {
// }

// void writeFileTable()
// {
// }

// Read from DB and initialize
void readAllFile()
{
	Int32 i, j;
	printf("Loading...");
	for (i = 0; i < MAX_FILE_NUM; ++i)
	{
		char fileName[5] = "dat ";
		fileName[3] = (char)('0' + i);
		Int32 fileID = AddFile(pool, fileName, RBIN);
		if (fileID == -1)
		{
			isFileExisted[i] = false;
			isFileFull[i] = false;
			continue;
		}
		else
			isFileExisted[i] = true;

		Int32 header;
		if (ReadFileU(pool, fileID, sizeof(header), 0, SEEK_SET, &header))
			puts("Fatal error: Fail to read file!");
		printf("header: %ld\n", header);
		if (header == BLOCK_NUM)
			isFileFull[i] = true;
		else
			isFileFull[i] = false;

		for (j = 0; j < header; ++j)
		{
			bookptr bookBuf = calloc(1, sizeof(struct Book));
			if (ReadFileU(pool, fileID, sizeof(struct Book), 0, SEEK_CUR, bookBuf))
				puts("Fatal error: Fail to read file!");
			printf("%s\n", bookBuf->isbn);
			add2ChainHash(bookBuf);
			free(bookBuf);
		}
		system("pause");
	}
}

boolean writeToDB(bookptr book)
{
	Int32 i;
	for (i = 0; i < MAX_FILE_NUM; ++i)
	{
		// If file num is more than 9, modify here
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
			book->filePos = i;
			book->bookPos = 0;
			printf("header: %ld", header);
			if (Write2File(pool, &header, fileID, sizeof(header), 0, SEEK_SET))
			{
				puts("Fatal error: Fail to write file!");
				return false;
			}
			isFileExisted[i] = true; // Update
			if (Write2File(pool, book, fileID, sizeof(struct Book), 0, SEEK_CUR))
			{
				puts("Fatal error: Fail to write file!");
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
			// Rollback is not realized
			fileName[3] = (char)('0' + i);

			// Modify the header
			Int32 fileID = AddFile(pool, fileName, WRBIN);
			if (fileID == -1)
			{
				puts("Fatal error: Fail to add file!");
				return false;
			}
			Int32 header;
			if (ReadFileU(pool, fileID, sizeof(header), 0, SEEK_SET, &header))
			{
				puts("Fatal error: Fail to read file!");
				return false;
			}
			++header;
			printf("header: %ld", header);
			if (Write2File(pool, &header, fileID, sizeof(header), 0, SEEK_SET))
			{
				puts("Fatal error: Fail to write file!");
				return false;
			}
			if (CloseFile(pool, fileID))
			{
				puts("Fatal error: Fail to close file!");
				return false;
			}
			if (header == BLOCK_NUM)
				isFileFull[i] = true;

			// Append the book
			fileID = AddFile(pool, fileName, ABIN);
			if (fileID == -1)
			{
				puts("Fatal error: Fail to add file!");
				return false;
			}
			book->filePos = i;
			book->bookPos = header - 1;
			if (AppendFile(pool, book, fileID, sizeof(struct Book)))
			{
				puts("Fatal error: Fail to append file!");
				return false;
			}
			CloseFile(pool, fileID);

			return true;
		}
	}

	puts("Fatal error: DB is full!");
	return false;
}

// Lazy delete
boolean deleteFromDB(bookptr book)
{
	// If file num is more than 9, modify here
	char fileName[5] = "dat ";
	fileName[3] = (char)(book->filePos + '0');
	Int32 fileID = AddFile(pool, fileName, WRBIN);
	if (fileID == -1)
	{
		puts("Fatal error: Fail to add file!");
		return false;
	}

	Int32 header;
	bookptr bookBuf = calloc(1, sizeof(struct Book));
	ReadFileU(pool, fileID, sizeof(header), 0, SEEK_SET, &header);
	ReadFileU(pool, fileID, sizeof(struct Book), -(Int32)(sizeof(struct Book)), SEEK_END, bookBuf);
	Write2File(pool, bookBuf, fileID, sizeof(struct Book), sizeof(struct Book) * book->bookPos, SEEK_SET);
	--header;
	Write2File(pool, &header, fileID, sizeof(header), 0, SEEK_SET);
	CloseFile(pool, fileID);
	free(bookBuf);
}