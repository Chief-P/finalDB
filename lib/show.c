#include "include/myhead.h"

// Get the current mode
int getMode()
{
	int res;
	char c;

	printf("$ ");
	c = getchar();
	getchar();

	switch (c)
	{
		case 'i' : res = INSERT; break;
		case 'l' : res = LOOKUP; break;
		case 'u' : res = UPDATE; break;
		case 'd' : res = DELETE; break;
		case 'v' : res = VIEW; break;
		case 'q' : res = QUIT; break;
		default : res = INTERFACE;
	}

	return res;
}

void showInterface()
{
	clear();
	puts("|----Book Management System----|");
	puts("|------------------------------|");
	puts("|      Insert    :    i        |");
	puts("|      Lookup    :    l        |");
	puts("|      Update    :    u        |");
	puts("|      Delete    :    d        |");
	puts("|        View    :    v        |");
	puts("|        Quit    :    q        |");
	puts("|------------------------------|");
	puts("* Please enter your command");
}