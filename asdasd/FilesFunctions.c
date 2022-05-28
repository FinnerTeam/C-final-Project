#include "ProjectHeader.h"

int FileLinesLen(FILE* FileData) //Counts number of rows in a file.
{
    char ch;
    int count_lines = 0;
    for (ch = getc(FileData); ch != EOF; ch = getc(FileData))
        if (ch == '\n')
            count_lines++;
    return count_lines + 1;
}

char** FileToArr(char* fileName, int* sizeOfFile) //Creates an array of strings from instruments's file.
{
    int i = 0;
    FILE* instrumentsFile = fopen(fileName, "r");
    CheckFile(instrumentsFile);
    int lines_in_file = FileLinesLen(instrumentsFile);
    *sizeOfFile = lines_in_file;
    fseek(instrumentsFile, 0, SEEK_SET);

    char** InstrumentsArr = NULL;
    InstrumentsArr = (char**)DynamicAllocation(InstrumentsArr, sizeof(char*), lines_in_file, MALLOC);
    InstrumentsArr[0] = (char*)DynamicAllocation(InstrumentsArr[0], sizeof(char), DEFAULT_BUFFER, MALLOC);

    while (i < lines_in_file && fscanf(instrumentsFile, "%s", InstrumentsArr[i]))
    {
        InstrumentsArr[i] = (char*)DynamicAllocation(InstrumentsArr[i], sizeof(char),strlen(InstrumentsArr[i]) + 1, REALLOC);
        i++;

        if (i < lines_in_file)
            InstrumentsArr[i] = (char*)DynamicAllocation(InstrumentsArr[i], sizeof(char), DEFAULT_BUFFER, MALLOC);
    }

    fclose(instrumentsFile);
    return InstrumentsArr;
}

Musician** createMusiciansGroup(InstrumentTree insTree, int* sizeOfFile, char* fileName) //Creates the Musicians Group array.
{
    FILE* musiciansFile = fopen(fileName, "r");
    CheckFile(musiciansFile);
    *sizeOfFile = FileLinesLen(musiciansFile);
    Musician** output = NULL;
    output = (Musician**)DynamicAllocation(output, sizeof(Musician*), (*sizeOfFile), MALLOC);
    int fileIndex = 0;
    fseek(musiciansFile, 0, SEEK_SET);

    for (int i = 0; i < *sizeOfFile; i++)
    {
        output[i] = createMusician(insTree, &fileIndex, musiciansFile);
        fileIndex = 0;
    }

    fclose(musiciansFile);
    return output;
}

Musician* createMusician(InstrumentTree insTree, int* fileIndex, FILE* musiciansFile) //Creates a new Musician.
{
    Musician* output = NULL;
    output = (Musician*)DynamicAllocation(output, sizeof(Musician), 1, MALLOC);
    char* line = NULL;
    int index = *fileIndex;

    output->name = getMusicianName(&index, insTree, musiciansFile, &line, &output);
    output->instruments = createMusicianMPIList(insTree, &index, musiciansFile, &line);
    output->currInst = 0;
    output->currInstPrice = (float)0;
    output->currInsImportance = '0';
    output->isBooked = false;

    return output;
}

char** getMusicianName(int* index, InstrumentTree insTree, FILE* musiciansFile, char** line, Musician** currMusician) //Generates musician's name.
{
    char** output = NULL;
    output = (char**)DynamicAllocation(output, sizeof(char*), DEFAULT_BUFFER, MALLOC); //Row len is max 150.
    *line = (char*)DynamicAllocation(line, sizeof(char), DEFAULT_BUFFER, MALLOC);
    int arrLogSize = 0, lineIndex = 0, backupIndex = 0;
    bool foundInstrument = false;
    fgets(*line, DEFAULT_BUFFER, musiciansFile);

    while (!foundInstrument)
    {
        output[arrLogSize] = NULL;
        extractCharacters(&output[arrLogSize], *line, &lineIndex);

        if (findInsId(insTree, output[arrLogSize]) != -1)
        {
            foundInstrument = true;
            free(output[arrLogSize]);
            *index = backupIndex;
            (*currMusician)->nameLen = arrLogSize;
        }

        else
            arrLogSize++;

        backupIndex = lineIndex;
    }

    output = (char**)DynamicAllocation(output, sizeof(char*), arrLogSize, REALLOC);
    return output;
}

MPIList createMusicianMPIList(InstrumentTree insTree, int* index, FILE* musiciansFile, char** line) //Creates a musician's MPI list.
{
    MPIList output;
    makeEmptyMPIList(&output);
    int stringsCounter = 0, indexCounter = *index;
    char* inputString = NULL, * protector = NULL;
    protector = (char*)DynamicAllocation(protector, sizeof(char), DEFAULT_BUFFER, MALLOC);
    bool foundLast = false;

    while (!foundLast)
    {
        inputString = NULL;
        extractCharacters(&inputString, *line, index);
        stringsCounter++;

        if (strlen(inputString) == 0)
            foundLast = true;

        if (stringsCounter % 2 == 0 && !foundLast)
            insertDataToEndOfMPIList(&output, protector, findInsId(insTree, protector), (float)(atoi(inputString)), NULL);

        else
            strcpy(protector, inputString);

        free(inputString);
    }

    free(*line);
    free(protector);
    return output;
}