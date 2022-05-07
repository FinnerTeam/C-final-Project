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
void InsertDataToMusicianGroup(InstrumentTree insTree,Musician* MusicianGroup, char* FreshData)
{
    char ch;
    bool next_word = false;
    bool InstrumentRead = false;
    bool PriceRead = false;
    int insId = -1;
    int  DataCol = 0,Data_LogicSize = 0,Data_PhyisicalSize = 1, Position = NAME;
    int FullName_LogicSize = 0,FullName_PhisicalSize = 1;
    char** data = NULL, ** name = NULL;
    FirstAllocation(&data, &name);
    MPIList MusicianKit;
    makeEmptyMPIList(&MusicianKit);
    int i = 0;
    while(FreshData[i] != '\n' && FreshData[i] !='\0')
    {
        ch = FreshData[i++];
        if (CheckValid(ch))
        {
            data[Data_LogicSize][DataCol++] = ch;
          
            if (next_word == true)
            {
                if (PriceRead == false)
                {
                    insId = findInsId(insTree, data[Data_LogicSize - 1]);
                    if (insId != -1)
                    {
                        InstrumentRead = true;
                        Position = INSTRUMENT;
                    }
                }
                else
                {
                    Position = PRICE;
                }
                switch (Position)
                {
                    case NAME:
                    {
                        Check_Physic_To_Logic(FullName_LogicSize, &FullName_PhisicalSize, &name);
                        name[FullName_LogicSize] = DynamicAllocation1(name[FullName_LogicSize], strlen(data[Data_LogicSize - 1]) + 1, MALLOC);
                        strcpy(name[FullName_LogicSize++], data[Data_LogicSize - 1]);
                        break;
                    }
                    case INSTRUMENT:
                    {
                        insertDataToEndOfMPIList(&MusicianKit, data[Data_LogicSize - 1], insId, 0, NULL);
                        InstrumentRead = false;
                        PriceRead = true;
                        break;
                    }
                    case PRICE:
                    {                                   //Needs to check about the float.. if there is really float inputs from the user.
                        MusicianKit.tail->Data.price = (float)atoi(data[Data_LogicSize - 1]);
                        InstrumentRead = true;
                        PriceRead = false;
                        break;
                    }
                    default:
                        break;
                }
                next_word = false;
            }
        }
        else 
        {
            if (next_word == false)
            {
                data[Data_LogicSize] = DynamicAllocation1(data[Data_LogicSize], DataCol + 1, REALLOC);
                data[Data_LogicSize][DataCol] = '\0';
                DataCol = 0;
                Data_LogicSize++;
                Check_Physic_To_Logic(Data_LogicSize, &Data_PhyisicalSize, &data);
                data[Data_LogicSize] = DynamicAllocation1(data[Data_LogicSize], FIRST_NAME, MALLOC);
                next_word = true;
            } 
        }
    }
    if (PriceRead == true)
    {
        MusicianKit.tail->Data.price = (float)atoi(data[Data_LogicSize - 1]);
    }
    if (FullName_LogicSize < FullName_PhisicalSize)
    {
        name = DynamicAllocation2(name, FullName_LogicSize, REALLOC);
    }
    freeArr(data,Data_LogicSize);
    MusicianGroup->name = DynamicAllocation2(MusicianGroup->name, FullName_LogicSize, MALLOC);
    for (int i = 0; i < FullName_LogicSize; i++)
    {
        (MusicianGroup->name)[i] = DynamicAllocation1((MusicianGroup->name)[i], strlen(name[i]) + 1, MALLOC);
        strcpy((MusicianGroup->name)[i], name[i]);
    }
    freeArr(name,FullName_LogicSize);
    MusicianGroup->instruments = MusicianKit;
}
