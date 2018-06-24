#include "include/window.h"

void _ResetCursor()
{
#ifdef WIN32
    system("cls");
#elif __linux__
    printf("\033[H\033[J");
#else
    printf("Platform not supported\n");
#endif
}

vectorptr CreateVector(Int32 X, Int32 Y, Int32 len, string data)
{
    vectorptr vector = calloc(1, sizeof(struct Vector)); 
    vector->data = calloc(1, strlen(data) + 1);
    for(int i = 0; i < len; i++)
        if(data[i] ==  '\n'){
            FreeVector(vector);
            return nullptr;
        }
    vector->X = X;
    vector->Y = Y;
    vector->Len = len;
    return vector;
}

void FreeVector(vectorptr vector)
{
    if(vector != nullptr){
        free(vector->data);
        free(vector);
    }
}


