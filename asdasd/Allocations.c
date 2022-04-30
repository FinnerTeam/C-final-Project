#include "ProjectHeader.h"

//Dynamic allocation function  for char*
char* DynamicAllocation1(char* Ptr, int NewSize, int Format)
{
    if (Format == REALLOC)
    {
        Ptr = (char*)realloc(Ptr, NewSize * sizeof(char));
        CheckMem(Ptr);
        return Ptr;
    }
    if (Format == MALLOC)
    {
        Ptr = (char*)malloc(NewSize * sizeof(char));
        CheckMem(Ptr);
        return Ptr;

    }
    return NULL;
}

//Dynamic allocation function  for char**
char** DynamicAllocation2(char** ptr_ptr, int NewSize, int Format)
{
    if (Format == REALLOC)
    {
        ptr_ptr = (char**)realloc(ptr_ptr, NewSize * sizeof(char*));

        CheckMem(ptr_ptr);
        return ptr_ptr;
    }
    if (Format == MALLOC)
    {
        ptr_ptr = (char**)malloc(NewSize * sizeof(char*));
        CheckMem(ptr_ptr);
        return ptr_ptr;

    }
    return NULL;
}
