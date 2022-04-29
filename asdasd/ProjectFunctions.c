#include "ProjectHeader.h"

void FileToArray(FILE* file, char** InstrumentsArr)
{
    char chunk[150];

    // Store the chunks of text into a line buffer
    size_t len = sizeof(chunk);
    char* line = malloc(len);
    if (line == NULL) {
        perror("Unable to allocate memory for the line buffer.");
        exit(1);
    }

    // "Empty" the string
    line[0] = '\0';

    while (fgets(chunk, sizeof(chunk), file) != NULL) {
        // Resize the line buffer if necessary
        size_t len_used = strlen(line);
        size_t chunk_used = strlen(chunk);

        if (len - len_used < chunk_used) {
            len *= 2;
            if ((line = realloc(line, len)) == NULL) {
                perror("Unable to reallocate memory for the line buffer.");
                free(line);
                exit(1);
            }
        }

        // Copy the chunk to the end of the line buffer
        strncpy(line + len_used, chunk, len - len_used);
        len_used += chunk_used;

        // Check if line contains '\n', if yes process the line of text
        if (line[len_used - 1] == '\n') {
            // fputs(line, stdout);
            // fputs("|*\n", stdout);
            printf("line length: %zd\n", len_used);
            // "Empty" the line buffer
            line[0] = '\0';
        }
    }
    /*int StartSize = 1, LogicSize = 0;
    while (fgets(InstrumentsArr, 150, file)) {
        printf("%s\n", InstrumentsArr);
    }*/
}

char** DynamicAllocation1(char** ptr_ptr, int NewSize, int Format)
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
void CheckMem(void* mem)
{
    if (mem == NULL)
    {
        exit(EXIT_FAILURE);
    }

}