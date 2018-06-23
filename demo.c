#include <stdio.h>
#include <string.h>

int main()
{
    char string255[32];
    int suck;
    printf("sizeof: %d  strlen: %d\n", sizeof(string255), strlen(string255));
    printf("sizeof int: %d\n", sizeof(suck));
}