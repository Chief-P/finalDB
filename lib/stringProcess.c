#include <include/stringProcess.h>

// Get a string
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