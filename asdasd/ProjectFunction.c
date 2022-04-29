#include "ProjectHeader.h"


int FileLinesLen(FILE* InstrumentsData)
{
    char ch;
    int count_lines = 0;
    InstrumentsData = fopen("Instruments.txt", "r");
    CheckMem(InstrumentsData);
    for (ch = getc(InstrumentsData); ch != EOF; ch = getc(InstrumentsData))
        if (ch == '\n') 
            count_lines++; 
    fclose(InstrumentsData);
    return count_lines;
}
void FileToArr(FILE* InstrumentsData, char** InstrumentsArr)
{
    int i = 0;
    int lines_in_file = FileLinesLen(InstrumentsData);
    InstrumentsData = fopen("Instruments.txt", "r");
    CheckMem(InstrumentsData);
    InstrumentsArr = DynamicAllocation2(InstrumentsArr, lines_in_file, REALLOC);
    InstrumentsArr[0] = DynamicAllocation1(InstrumentsArr[0],DEFAULT_BUFFER,MALLOC);

    while (fscanf(InstrumentsData, "%s", InstrumentsArr[i]) && i < lines_in_file)
    {
        InstrumentsArr[i] = DynamicAllocation1(InstrumentsArr[i], strlen(InstrumentsArr[i])+1, REALLOC);
  
        i++;
        InstrumentsArr[i] = DynamicAllocation1(InstrumentsArr[i], DEFAULT_BUFFER , MALLOC);
    }
    fclose(InstrumentsData);

}
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

void CheckMem(void* mem)
{
    if (mem == NULL)
    {
        exit(EXIT_FAILURE);
    }

}