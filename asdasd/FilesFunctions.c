#include "ProjectHeader.h"
int FileLinesLen(FILE* InstrumentsData)
{
    char ch;
    int count_lines = 0;
    InstrumentsData = fopen("Instruments.txt", "r");
    CheckFile(InstrumentsData);
    for (ch = getc(InstrumentsData); ch != EOF; ch = getc(InstrumentsData))
        if (ch == '\n')
            count_lines++;
    fclose(InstrumentsData);
    return count_lines;
}
char** FileToArr(FILE* InstrumentsData, char** InstrumentsArr, int* sizeOfFile)
{
    int i = 0;
    int lines_in_file = FileLinesLen(InstrumentsData);
    *sizeOfFile = lines_in_file;
    InstrumentsData = fopen("Instruments.txt", "r");
    CheckFile(InstrumentsData);
    InstrumentsArr = DynamicAllocation2(InstrumentsArr, lines_in_file, MALLOC);
    InstrumentsArr[0] = DynamicAllocation1(InstrumentsArr[0], DEFAULT_BUFFER, MALLOC);

    while (fscanf(InstrumentsData, "%s", InstrumentsArr[i]) && i < lines_in_file)
    {
        InstrumentsArr[i] = DynamicAllocation1(InstrumentsArr[i], strlen(InstrumentsArr[i]) + 1, REALLOC);
        i++;
        InstrumentsArr[i] = DynamicAllocation1(InstrumentsArr[i], DEFAULT_BUFFER, MALLOC);
    }
    fclose(InstrumentsData);
    return InstrumentsArr;

}
