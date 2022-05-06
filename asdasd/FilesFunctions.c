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
    return count_lines;
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

    Musician** MusicianGroup = DynamicAllocation2(MusicianGroup, *sizeOfFile, MALLOC);
    CheckMem(MusicianGroup);

    char* Line = DynamicAllocation1(Line, DEFAULT_BUFFER, MALLOC);
    while (fscanf(MusiciansData, "%s", Line) && i < lines_in_file)
    {
        Line = DynamicAllocation1(Line, strlen(Line) + 1, REALLOC);
        InsertDataToMusicianGroup(insTree,MusicianGroup[i], Line);
        i++;
        Line = DynamicAllocation1(Line, DEFAULT_BUFFER, MALLOC);
    }
    fclose(MusiciansData);
    return MusicianGroup;
    
    
    
    /* MallocArrguments(MusicianGroup[0],);*/


}

void InsertDataToMusicianGroup(InstrumentTree insTree,Musician* MusicianGroup, char* FreshData)
{
    char ch;
    bool next_word = false;
    int  DataCol = 0,Data_LogicSize = 0,Data_PhyisicalSize = 1, Position = NAME;
    int FullName_LogicSize = 0,FullName_PhisicalSize = 1;
    char** data, ** name;
    FirstAllocation(data, name);
    MPIList MusicianKit;
   
    for (ch = getchar(FreshData); ch != '\n'; ch = getchar(FreshData))
    {
        if (!CheckValid(ch))
        {
            Check_Physic_To_Logic(Data_LogicSize, &Data_PhyisicalSize, data);
            data[Data_LogicSize][DataCol++] = ch;
          
            if (next_word == true)
            {
                if (findInsId(insTree, data[Data_LogicSize - 1]) != -1)
                {
                    Position = INSTRUMENT;
                }
                switch (Position)
                {
                case NAME:
                    Check_Physic_To_Logic(FullName_LogicSize, &FullName_PhisicalSize, name);
                    name[FullName_LogicSize] = DynamicAllocation1(name[FullName_LogicSize], strlen(data[Data_LogicSize - 1]) + 1, REALLOC);
                    strcpy(name[FullName_LogicSize++], data[Data_LogicSize - 1]);
                    break;
                case INSTRUMENT:


                    break;
                case PRICE:


                    break;

                default:
                    break;
                }
                next_word == false;
            }
        }
        else if (next_word == false)
        {
            data[Data_LogicSize][DataCol] = '\0';
            DataCol = 0;
            Data_LogicSize++;
            next_word = true;
        }
  
    }
   
}

bool CheckValid(char ch)
{
    return(ch != ' '
        || ch != ',' || ch != '.'
        || ch != ';' || ch != '?'
        || ch != '!' || ch != '-'
        || ch != '\t'|| ch != "'"
        || ch != '(' || ch != ')'
        || ch != '[' || ch != ']'
        || ch != '{' || ch != '}'
        || ch != '<' || ch != '>'
        || ch != '~' || ch != '_');
}

void Check_Physic_To_Logic(int logicSize, int* PhyisicSize, void** Data_to_check)
{
    if (logicSize == *PhyisicSize)
    {
        (*PhyisicSize) *= 2;
        Data_to_check = DynamicAllocation2(Data_to_check, PhyisicSize, REALLOC);
    }
}
void FirstAllocation(char** data, char** name)
{
    char** name = DynamicAllocation2(name, 1, MALLOC);
    CheckMem(name);
    char** data = DynamicAllocation2(data, 1, MALLOC);
    CheckMem(data);
    data[0] = DynamicAllocation1(data[0], FIRST_NAME, MALLOC);
    CheckMem(data[0]);
    name[0] = DynamicAllocation1(name[0], FIRST_NAME, MALLOC);
    CheckMem(name[0]);
}
void MallocArrguments(Musician* MusicianGroup,int Name_Size)
{
    MusicianGroup->name = DynamicAllocation2(MusicianGroup->name, Name_Size, MALLOC); 
}