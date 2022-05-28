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
    InstrumentsArr =(char**)DynamicAllocation(InstrumentsArr,sizeof(char*), lines_in_file, MALLOC);
    InstrumentsArr[0] = (char*)DynamicAllocation(InstrumentsArr[0], sizeof(char), DEFAULT_BUFFER, MALLOC);

    while (fscanf(instrumentsFile, "%s", InstrumentsArr[i]) && i < lines_in_file)
    {
        InstrumentsArr[i] = (char*)DynamicAllocation(InstrumentsArr[i], sizeof(char),strlen(InstrumentsArr[i]) + 1, REALLOC);
        i++;
        InstrumentsArr[i] = (char*)DynamicAllocation(InstrumentsArr[i], sizeof(char),DEFAULT_BUFFER, MALLOC);
    }
    fclose(instrumentsFile);
    return InstrumentsArr;
}
// check ben
//////Musician** FileToArr_Musicians(InstrumentTree insTree, FILE* MusiciansData, int* sizeOfFile) //Creates an array of musicians.
//////{
//////    int i = 0, Logicsize = 0, PhyiscalSize = 1;
//////    
//////    int lines_in_file = FileLinesLen(MusiciansData, MUSICIANSFILE);
//////    *sizeOfFile = lines_in_file;
//////    MusiciansData = fopen(MUSICIANSFILE, "r");
//////    CheckFile(MusiciansData);
//////    //(Musician**)malloc(sizeof(Musician*) * (*sizeOfFile));
//////    Musician** MusicianGroup = NULL;
//////    MusicianGroup = (Musician**)DynamicAllocation(MusicianGroup, sizeof(Musician*), (*sizeOfFile), MALLOC);
//////    CheckMem(MusicianGroup);
//////
//////    char* Line = NULL;
//////    Line = (char*)DynamicAllocation(Line,sizeof(char), DEFAULT_BUFFER, MALLOC);
//////    while (fgets(Line , DEFAULT_BUFFER, MusiciansData) && i < lines_in_file )
//////    {
//////        Line = (char*)DynamicAllocation(Line,sizeof(char), strlen(Line)+1 , REALLOC);
//////        MusicianGroup[i] = (Musician*) DynamicAllocation(MusicianGroup[i], sizeof(Musician), 1, MALLOC);;
//////        CheckMem(MusicianGroup[i]);
//////        InsertDataToMusicianGroup(insTree, MusicianGroup[i], Line);
//////        i++;
//////        Line = (char*)DynamicAllocation(Line,sizeof(char), DEFAULT_BUFFER, MALLOC);
//////    }
//////    free(Line);
//////    fclose(MusiciansData);
//////    return MusicianGroup;
//////}
// check ben
//void InsertDataToMusicianGroup(InstrumentTree insTree, Musician* MusicianGroup, char* FreshData) //Inserts new data to musicians array.
//{
//    char ch;
//    bool next_word = false, InstrumentRead = false, PriceRead = false, First = true, End = false;
//    int insId = -1, DataCol = 0, Position = NAME, i = 0;
//    DATATYPE name, data;
//    InstallizeFirst(&data, &name);
//    MPIList MusicianKit;
//    makeEmptyMPIList(&MusicianKit);
//
//    while(FreshData[i] != '\0')
//    {
//        ch = FreshData[i];
//        if (FreshData[i + 1] == '\n' && !End && !CheckValid(ch))
//        {
//            priceAtend(&data, DataCol, &MusicianKit);
//            PriceRead = false;
//            End = true;
//        }
//
//        if (CheckValid(ch))
//        {
//            First = false;
//            data.data[*(data.logicsize)][DataCol++] = ch;
//            if (next_word == true)
//            {
//                if (PriceRead == false)
//                    CheckExistInTree(&insId, &Position, &InstrumentRead,insTree,data);
//
//                else
//                    Position = PRICE;
//
//                Selector(Position, &data, &name, &MusicianKit, &InstrumentRead, &PriceRead, insId);
//                next_word = false;
//            }   
//           
//        }
//        else 
//            if (next_word == false && First == false && End == false)
//                NextWordOperation(&data, &DataCol, &next_word);
//
//        i++;
//    }
//
//    EndOfReadOperation(MusicianGroup,PriceRead, &MusicianKit, &data, &name);    
//}

Musician** createMusiciansGroup(InstrumentTree insTree, int* sizeOfFile, char* fileName) //Creates the Musicians Group array.
{
    FILE* musiciansFile = fopen(fileName, "r");
    CheckFile(musiciansFile);
    *sizeOfFile = FileLinesLen(musiciansFile);
    //(Musician**)malloc(sizeof(Musician*) * (*sizeOfFile));
    Musician** output = NULL;
    output = (Musician**)DynamicAllocation(output, sizeof(Musician*), (*sizeOfFile), MALLOC);
    int fileIndex = 0;
    fseek(musiciansFile, 0, SEEK_SET);

    for (int i = 0; i < *sizeOfFile; i++)
        output[i] = createMusician(insTree, &fileIndex, musiciansFile);

    fclose(musiciansFile);
    return output;
}

Musician* createMusician(InstrumentTree insTree, int* fileIndex, FILE* musiciansFile) //Creates a new Musician.
{
    Musician* output = NULL;
    output = (Musician*)DynamicAllocation(output, sizeof(Musician), 1, MALLOC);
    char* line = NULL;
    int index = *fileIndex;

    output->name = getMusicianName(&index, insTree, musiciansFile, &line);
    output->instruments = createMusicianMPIList(insTree, &index, musiciansFile, &line);
    output->currInst = output->currInstPrice = output->currInsImportance = 0;
    output->isBooked = false;

    *fileIndex = index;

    return output;
}

char** getMusicianName(int* index, InstrumentTree insTree, FILE* musiciansFile, char** line) //Generates musician's name.
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