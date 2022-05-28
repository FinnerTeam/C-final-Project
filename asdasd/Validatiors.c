#include "ProjectHeader.h"

void CheckMem(void* mem) //Checks memory allocation.
{
    if (mem == NULL)
    {
        perror("Memory allocation failed!");
        exit(EXIT_FAILURE);
    }

}

void CheckFile(FILE* file) //Checks if file was opened currectly.
{
    if (file == NULL)
    {
        perror("Failed to open file!");
        exit(EXIT_FAILURE);
    }
}