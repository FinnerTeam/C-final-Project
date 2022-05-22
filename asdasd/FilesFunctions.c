#include "ProjectHeader.h"

int FileLinesLen(FILE* FileData, char* FileName) //Counts number of rows in a file.
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

char** FileToArr(FILE* InstrumentsData, char** InstrumentsArr, int* sizeOfFile) //Creates an array of strings from instruments's file.
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

Musician** FileToArr_Musicians(InstrumentTree insTree, FILE* MusiciansData, int* sizeOfFile) //Creates an array of musicians.
{
    int i = 0, Logicsize = 0, PhyiscalSize = 1;
    
    int lines_in_file = FileLinesLen(MusiciansData, MUSICIANSFILE);
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
        InsertDataToMusicianGroup(insTree, MusicianGroup[i], Line);
        i++;
        Line = DynamicAllocation1(Line, DEFAULT_BUFFER, MALLOC);
    }
    free(Line);
    fclose(MusiciansData);
    return MusicianGroup;
}

void InsertDataToMusicianGroup(InstrumentTree insTree, Musician* MusicianGroup, char* FreshData) //Inserts new data to musicians array.
{
    char ch;
    bool next_word = false, InstrumentRead = false, PriceRead = false, First = true, End = false;
    int insId = -1, DataCol = 0, Position = NAME, i = 0;
    DATATYPE name, data;
    InstallizeFirst(&data, &name);
    MPIList MusicianKit;
    makeEmptyMPIList(&MusicianKit);

    while(FreshData[i] != '\0')
    {
        ch = FreshData[i];

        if (i == 50)
            printf("here");

        if (FreshData[i + 1] == '\n' && !End && !CheckValid(ch))
        {
            priceAtend(&data, DataCol, &MusicianKit);
            PriceRead = false;
            End = true;
        }

        if (CheckValid(ch))
        {
            First = false;
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
            if (next_word == false && First == false && End == false)
                NextWordOperation(&data, &DataCol, &next_word);

        i++;
    }

    EndOfReadOperation(MusicianGroup,PriceRead, &MusicianKit, &data, &name);    
}

Musician** createMusiciansGroup(InstrumentTree insTree, FILE* MusiciansData, int* sizeOfFile) //Creates the Musicians Group array.
{
    *sizeOfFile = FileLinesLen(MusiciansData, MUSICIANSFILE);
    Musician** output = (Musician**)malloc(sizeof(Musician*) * (*sizeOfFile));
    CheckMem(output);
    int fileIndex = 0;

    for (int i = 0; i < *sizeOfFile; i++)
        output[i] = createMusician(insTree, &fileIndex);

    return output;
}

Musician* createMusician(InstrumentTree insTree, int* fileIndex) //Creates a new Musician.
{
    Musician* output = (Musician*)malloc(sizeof(Musician));
    CheckMem(output);
    int index = *fileIndex;

    output->name = getMusicianName(&index, insTree);
    output->instruments = createMusicianMPIList(insTree, &index);
    output->currInst = output->currInstPrice = output->currInsImportance = 0;

    *fileIndex = index;

    return output;
}

char** getMusicianName(int* index, InstrumentTree insTree) //Generates musician's name.
{
    char** output = (char**)malloc(sizeof(char*) * DEFAULT_BUFFER); CheckMem(output);
    int arrLogSize = 0, stringLogSize = 0, indexCounter = *index, beginningOfString;
    FILE* musiciansFile = fopen(MUSICIANSFILE, "r"); CheckFile(musiciansFile); fseek(musiciansFile, *index, SEEK_SET);
    char input; fscanf(musiciansFile, "%c", &input);
    bool foundInstrument = false;

    while (input != '\n' && !foundInstrument)
    {
        if (!CheckValid(input))
        {
            if (arrLogSize == 0 && stringLogSize == 0)
            {
                fscanf(musiciansFile, "%c", &input);
                indexCounter++;
                continue;
            }
                
            else if (arrLogSize >= 0 && stringLogSize != 0)
            {
                output[arrLogSize] = (char*)realloc(output[arrLogSize], sizeof(char) * (stringLogSize + 1));
                CheckMem(output[arrLogSize]);
                output[arrLogSize][stringLogSize] = '\0';

                if (findInsId(insTree, output[arrLogSize]) != -1)
                {
                    foundInstrument = true;
                    *index = beginningOfString;
                    free(output[arrLogSize]);
                }

                else
                {
                    arrLogSize++;
                    stringLogSize = 0;
                }
            }
        }

        else
        {
            if (stringLogSize == 0)
            {
                output[arrLogSize] = (char*)malloc(sizeof(char) * DEFAULT_BUFFER);
                CheckMem(output[arrLogSize]);
                beginningOfString = indexCounter;
            }

            output[arrLogSize][stringLogSize] = input;
            stringLogSize++;
        }

        fscanf(musiciansFile, "%c", &input);
        indexCounter++;
    }

    fclose(musiciansFile);
    output = (char**)realloc(output, sizeof(char*) * arrLogSize);
    return output;
}

MPIList createMusicianMPIList(InstrumentTree insTree, int* index) //Creates a musician's MPI list.
{
    MPIList output; makeEmptyMPIList(&output);
    FILE* musiciansFile = fopen(MUSICIANSFILE, "r"); CheckFile(musiciansFile); fseek(musiciansFile, 0, SEEK_END);
    long fileSize = ftell(musiciansFile); fseek(musiciansFile, *index, SEEK_SET);
    char input; fscanf(musiciansFile, "%c", &input);
    int stringLogSize = 0, counter = 0;
    char* protector = (char*)malloc(sizeof(char) * DEFAULT_BUFFER); char* inputString = NULL; CheckMem(protector);
    
    while (input != '\n' && input != '\0' && (*index) <= fileSize)
    {
        if (CheckValid(input))
        {
            if (stringLogSize == 0)
            {
                inputString = (char*)malloc(sizeof(char) * DEFAULT_BUFFER);
                CheckMem(inputString);
            }

            inputString[stringLogSize] = input;
            stringLogSize++;
        }

        else if (stringLogSize > 0)
        {
            inputString = (char*)realloc(inputString, sizeof(char) * (stringLogSize + 1));
            CheckMem(inputString);
            inputString[stringLogSize] = '\0';
            stringLogSize = 0;
            counter++;

            if (counter % 2 == 0)
                insertDataToEndOfMPIList(&output, protector, findInsId(insTree, protector), (float)((atoi)(inputString)), false, NULL);
                
            else
                strcpy(protector, inputString);

            free(inputString);
            inputString = NULL;
        }
        fscanf(musiciansFile, "%c", &input);
        (*index) = (*index) + 1;
    }

    if ((input == '\0' || input == '\n') && inputString != NULL)
    {
        insertDataToEndOfMPIList(&output, protector, findInsId(insTree, protector), (float)((atoi)(inputString)), false, NULL);
        free(inputString);
        free(protector);
    }

    else
        free(protector);

    (*index) = (*index) + 2; //Move to next line.
    fclose(musiciansFile);
    return output;
}