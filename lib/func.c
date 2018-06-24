#include "include/myhead.h"

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

/*
 * Get string with length restriction
 * @ return succ(1)/fail(0):boolean
 */
boolean getString(string s, const Int32 maxLen, const boolean isFixed, const boolean allowEmpty)
{
	if (maxLen <= 0)
		return false;

	char c;
	Int32 curLen = 0;

	while ((c = getchar()))
	{
		// Process newline
		if (c == '\n')
		{
			if (curLen == 0 && !allowEmpty)
				return false;
			else if (curLen <= maxLen)
			{
				if (isFixed && curLen != maxLen)
					return false;
				
				// Fill the string
				while (curLen <= maxLen)
					s[curLen++] = '\0';
				return true;
			}
		}

		// Process other char
		s[curLen] = c;
		++curLen;
		if (curLen > maxLen)
		{
			// setbuf(stdin, NULL);
			fflush(stdin);
			return false;
		}
	}

	return false;
}

// Linear-read all file
void readAllFile()
{
    Int32 i, j;
    boolean isFailed;
    for (i = 0; i < BLOCKNUM; ++i)
    {
		char postFix[2] = {i + '0', '\0'};
        string fileName = strcat("dat", postFix);
		Int32 fileID = AddFile(pool, fileName, RBIN);
		Int32 headBuf;
		string blockBuf = calloc(1, BLOCKSIZE);
        isFailed = ReadFileU(pool, fileID, FILESIZE, HEADERSIZE, 0, headBuf);
		if (isFailed)
			break;
		for (j = 0; j < headBuf; ++j)
    }
}

void insert()
{
    bookptr book = calloc(1, sizeof(struct Book));
	Int32 i;

	// User interface
	clear();
	puts("-----Insert Mode-----");
	puts("* Please enter the information of book");
	puts("* Press Enter if not existed");

	printf("ISBN: ");
	while (!getString(book->isbn, LENISBN, true, true))
	{
		puts("* Please enter a valid ISBN (13 digits)");
		printf("ISBN: ");
	}

	printf("Name: ");
	while (!getString(book->name, LENNAME, false, false))
	{
		puts("* Please enter a valid Name (max length 127)");
		printf("Name: ");
	}

	for (i = 0; i < MAXKEYWORDS; ++i)
	{
		printf("Keyword %ld: ", i + 1);
		while (!getString(book->keywords[i], LENKEYWORD, false, true))
		{
			puts("* Please enter a valid Keyword (max length 127)");
			printf("Keyword %ld: ", i + 1);
		}
	}

	for (i = 0; i < MAXAUTHORS; ++i)
	{
		printf("Author %ld: ", i + 1);
		while (!getString(book->authors[i], LENAUTHOR, false, true))
		{
			puts("* Please enter a valid Author (max length 127)");
			printf("Author %ld: ", i + 1);
		}
	}

	puts("---Successfully Inserted---");

	// Write into DB
	boolean isWritten = true;
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
				isWritten = false;
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

	char postFix[2] = {i + '0', '\0'};
	string fileName = strcat("dat", postFix);


	// Add to Block and HashTable
    blockptr block = CreateBlock(book, sizeof(struct Book));
	Int32 index = AddChain(chain, block);
    AddHash(isbnHashT, Hash(book->isbn, sizeof(book->isbn), TIME33), index);
    AddHash(nameHashT, Hash(book->name, sizeof(book->name), TIME33), index);
    for (i = 0; i < numKeywords; ++i)
        AddHash(keywordsHashT, )
}

void lookup()
{
	clear();
	puts("Please enter the attribute of book");

}