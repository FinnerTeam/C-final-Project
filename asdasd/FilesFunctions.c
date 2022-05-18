#include "ProjectHeader.h"

int FileLinesLen(FILE* FileData, char* FileName)
{
    char ch;
    int count_lines = 0;
    FileData = fopen(FileName, "r");
    CheckFile(FileData);
    for (ch = getc(FileData); ch != EOF; ch = getc(FileData))
        if (ch == '\n')
            count_lines++;
    fclose(FileData);
    return count_lines + 1;
}

char** FileToArr(FILE* InstrumentsData, char** InstrumentsArr, int* sizeOfFile)
{
    int i = 0;
    int lines_in_file = FileLinesLen(InstrumentsData, INSTRUMENTSFILE);
    *sizeOfFile = lines_in_file;
    InstrumentsData = fopen(INSTRUMENTSFILE, "r");
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

Musician** FileToArr_Musicians(InstrumentTree insTree, FILE* MusiciansData, int* sizeOfFile)
{
    int i = 0, Logicsize = 0, PhyiscalSize = 1;
    
    int lines_in_file = FileLinesLen(MusiciansData,MUSICIANSFILE);
    *sizeOfFile = lines_in_file;
    MusiciansData = fopen(MUSICIANSFILE, "r");
    CheckFile(MusiciansData);

    Musician** MusicianGroup = (Musician**)malloc(sizeof(Musician*) * (*sizeOfFile));
    CheckMem(MusicianGroup);

    char* Line = NULL;
    Line = DynamicAllocation1(Line, DEFAULT_BUFFER, MALLOC);
    while (fgets(Line , DEFAULT_BUFFER, MusiciansData) && i < lines_in_file )
    {
        Line = DynamicAllocation1(Line, strlen(Line)+1 , REALLOC);
        MusicianGroup[i] = (Musician*)malloc(sizeof(Musician));
        CheckMem(MusicianGroup[i]);
        InsertDataToMusicianGroup(insTree,MusicianGroup[i], Line);
        i++;
        Line = DynamicAllocation1(Line, DEFAULT_BUFFER, MALLOC);
    }
    free(Line);
    fclose(MusiciansData);
    return MusicianGroup;
}

void InsertDataToMusicianGroup(InstrumentTree insTree, Musician* MusicianGroup, char* FreshData)
{
    char ch;
    bool next_word = false, InstrumentRead = false, PriceRead = false;
    int insId = -1, DataCol = 0, Position = NAME, i = 0;
    DATATYPE name, data;
    InstallizeFirst(&data, &name);
    MPIList MusicianKit;
    makeEmptyMPIList(&MusicianKit);

    while(FreshData[i] != '\n' && FreshData[i] !='\0')
    {
        ch = FreshData[i++];
        if (CheckValid(ch))
        {
            data.data[*(data.logicsize)][DataCol++] = ch;
            if (next_word == true)
            {
                if (PriceRead == false)
                    CheckExistInTree(&insId, &Position, &InstrumentRead,insTree,data);

                else
                    Position = PRICE;

                Selector(Position, &data, &name, &MusicianKit, &InstrumentRead, &PriceRead, insId);
                next_word = false;
            }
        }
        else 
            if (next_word == false)
                NextWordOperation(&data, &DataCol, &next_word);
    }
    EndOfReadOperation(MusicianGroup,PriceRead, &MusicianKit, &data, &name);    
}