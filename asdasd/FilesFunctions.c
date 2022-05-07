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
    int  DataCol = 0, Position = NAME;
    DATATYPE name;
    DATATYPE data;
    InstallizeFirst( &data, &name);
    MPIList MusicianKit;
    makeEmptyMPIList(&MusicianKit);
    int i = 0;
    while(FreshData[i] != '\n' && FreshData[i] !='\0')
    {
        ch = FreshData[i++];
        if (CheckValid(ch))
        {
            data.data[*(data.logicsize)][DataCol++] = ch;
            if (next_word == true)
            {
                if (PriceRead == false)
                {
                    CheckExistInTree(&insId, &Position, &InstrumentRead,insTree,data);
                }
                else
                {
                    Position = PRICE;
                }
                Selector(Position, &data, &name, &MusicianKit, &InstrumentRead, &PriceRead, insId);
                next_word = false;
            }
        }
        else 
        {
            if (next_word == false)
            {
                NextWordOperation(&data, &DataCol, &next_word);
            } 
        }
    }
    EndOfReadOperation(MusicianGroup,PriceRead, &MusicianKit, &data, &name);    
}

void createMusiciansCollection(Musician**** Collection,int numOfInstruments, Musician** MusiciansGroup, int numOfMusicians) //Creates the MusiciansCollection array.
{
    Musician*** output = NULL;
    output = (Musician***)malloc(sizeof(Musician**) * numOfInstruments);
    CheckMem(output);
    int i, j, k, subArrayLogSize, subArrayPhySize = 1;

    for (i = 0; i < numOfInstruments; i++)
    {
        output[i] = (Musician**)malloc(sizeof(Musician*) * subArrayPhySize);
        CheckMem(output[i]);
        subArrayLogSize = 0;
        for (j = 0; j < numOfMusicians; j++)
        {
            if (MPIListBinarySearch(&(MusiciansGroup[j]->instruments), i))
            {
                if (subArrayLogSize == subArrayPhySize)
                {
                    subArrayPhySize *= 2;
                    output[i] = (Musician**)realloc(output[i], sizeof(Musician*) * subArrayPhySize);
                    CheckMem(output[i]);
                }
                output[i][subArrayLogSize] = MusiciansGroup[j];
                subArrayLogSize++;
                if (j == numOfMusicians - 1 && subArrayPhySize > subArrayLogSize)
                {
                    output[i] = (Musician**)realloc(output[i], sizeof(Musician*) * subArrayLogSize);
                    CheckMem(output[i]);
                }
            }
        }
    }
    *Collection = output;

}
//=======
//>>>>>>> Stashed changes
