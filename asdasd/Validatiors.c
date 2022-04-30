#include "ProjectHeader.h"

void CheckMem(void* mem)
{
    if (mem == NULL)
    {
        exit(EXIT_FAILURE);
    }

}
void CheckFile(FILE* file)
{
    if (file == NULL)
    {
        perror("Failed to open file!");
        exit(EXIT_FAILURE);
    }
}