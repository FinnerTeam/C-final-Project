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
    InstrumentsArr = DynamicAllocation2(InstrumentsArr, lines_in_file, MALLOC);
    InstrumentsArr[0] = DynamicAllocation1(InstrumentsArr[0], DEFAULT_BUFFER, MALLOC);

    while (fscanf(instrumentsFile, "%s", InstrumentsArr[i]) && i < lines_in_file)
    {
        InstrumentsArr[i] = DynamicAllocation1(InstrumentsArr[i], strlen(InstrumentsArr[i]) + 1, REALLOC);
        i++;
        InstrumentsArr[i] = DynamicAllocation1(InstrumentsArr[i], DEFAULT_BUFFER, MALLOC);
    }
    fclose(instrumentsFile);
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

Musician** createMusiciansGroup(InstrumentTree insTree, int* sizeOfFile, char* fileName) //Creates the Musicians Group array.
{
    FILE* musiciansFile = fopen(fileName, "r");
    CheckFile(musiciansFile);
    *sizeOfFile = FileLinesLen(musiciansFile);
    Musician** output = (Musician**)malloc(sizeof(Musician*) * (*sizeOfFile));
    CheckMem(output);
    int fileIndex = 0;
    fseek(musiciansFile, 0, SEEK_SET);

    for (int i = 0; i < *sizeOfFile; i++)
        output[i] = createMusician(insTree, &fileIndex, musiciansFile);

    fclose(musiciansFile);
    return output;
}

Musician* createMusician(InstrumentTree insTree, int* fileIndex, FILE* musiciansFile) //Creates a new Musician.
{
    Musician* output = (Musician*)malloc(sizeof(Musician));
    CheckMem(output);
    int index = *fileIndex;

    output->name = getMusicianName(&index, insTree, musiciansFile);
    output->instruments = createMusicianMPIList(insTree, &index, musiciansFile);
    output->currInst = output->currInstPrice = output->currInsImportance = 0;
    output->isBooked = false;

    *fileIndex = index;

    return output;
}

char** getMusicianName(int* index, InstrumentTree insTree, FILE* musiciansFile) //Generates musician's name.
{
    char** output = (char**)malloc(sizeof(char*) * DEFAULT_BUFFER); CheckMem(output); //Row len is max 150.
    int arrLogSize = 0, stringLogSize = 0, indexCounter = *index, beginningOfString;
    fseek(musiciansFile, *index, SEEK_SET);
    char input; fscanf(musiciansFile, "%c", &input);
    bool foundInstrument = false;

    while (input != '\n' && !foundInstrument)
    {
        if (!CheckValid(input))
        {
            if (arrLogSize == 0 && stringLogSize == 0)
            {
                fscanf(musiciansFile, "%c", &input); indexCounter++; continue;
            }
            else if (arrLogSize >= 0 && stringLogSize != 0)
            {
                output[arrLogSize] = (char*)realloc(output[arrLogSize], sizeof(char) * (stringLogSize + 1)); CheckMem(output[arrLogSize]);
                output[arrLogSize][stringLogSize] = '\0';
                if (findInsId(insTree, output[arrLogSize]) != -1)
                {
                    foundInstrument = true; *index = beginningOfString; free(output[arrLogSize]);
                }
                else
                {
                    arrLogSize++; stringLogSize = 0;
                }
            }
        }
        else //Valid character.
        {
            if (stringLogSize == 0)
            {
                output[arrLogSize] = (char*)malloc(sizeof(char) * DEFAULT_BUFFER); //Row len is max 150.
                CheckMem(output[arrLogSize]); beginningOfString = indexCounter;
            }
            output[arrLogSize][stringLogSize] = input;
            stringLogSize++;
        }
        fscanf(musiciansFile, "%c", &input);
        indexCounter++;
    }

    output = (char**)realloc(output, sizeof(char*) * arrLogSize);
    CheckMem(output);
    return output;
}

MPIList createMusicianMPIList(InstrumentTree insTree, int* index, FILE* musiciansFile) //Creates a musician's MPI list.
{
    MPIList output; makeEmptyMPIList(&output);
    fseek(musiciansFile, 0, SEEK_END);
    long fileSize = ftell(musiciansFile);
    fseek(musiciansFile, *index, SEEK_SET);
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
                insertDataToEndOfMPIList(&output, protector, findInsId(insTree, protector), (float)((atoi)(inputString)), NULL);
                
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
        insertDataToEndOfMPIList(&output, protector, findInsId(insTree, protector), (float)((atoi)(inputString)), NULL);
        free(inputString);
        free(protector);
    }

    else
        free(protector);

    (*index) = (*index) + 2; //Move to next line.
    return output;
}