#include "ProjectHeader.h"

//General dynamic allocation function.
void* DynamicAllocation(void* ptr_ptr, size_t elemSize, size_t num_Of_elements, int Format)
{
    if (Format == REALLOC)
    {
        ptr_ptr = realloc(ptr_ptr, num_Of_elements * elemSize);

        CheckMem(ptr_ptr);
        return ptr_ptr;
    }

    if (Format == MALLOC)
    {
        ptr_ptr = malloc(num_Of_elements * elemSize);
        CheckMem(ptr_ptr);
        return ptr_ptr;
    }

    return NULL;
}
