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
    Musician* output = NULL;
    output = (Musician*)DynamicAllocation(output, sizeof(Musician), 1, MALLOC);
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
    //(char**)malloc(sizeof(char*) * DEFAULT_BUFFER); 
    char** output = NULL;
    output = (char**)DynamicAllocation(output, sizeof(char*), DEFAULT_BUFFER, MALLOC);//Row len is max 150.
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
                //(char*)realloc(output[arrLogSize], sizeof(char) * (stringLogSize + 1));
                output[arrLogSize] = (char*)DynamicAllocation(output[arrLogSize], sizeof(char), stringLogSize + 1, REALLOC);
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
                //(char*)malloc(sizeof(char) * DEFAULT_BUFFER);
                output[arrLogSize] = (char*)DynamicAllocation(output[arrLogSize], sizeof(char), DEFAULT_BUFFER, MALLOC);//Row len is max 150.
                CheckMem(output[arrLogSize]); beginningOfString = indexCounter;
            }
            output[arrLogSize][stringLogSize] = input;
            stringLogSize++;
        }
        fscanf(musiciansFile, "%c", &input);
        indexCounter++;
    }
    //(char**)realloc(output, sizeof(char*) * arrLogSize);
    output = (char**)DynamicAllocation(output, sizeof(char*), arrLogSize, REALLOC);
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
    int stringLogSize = 0, counter = 0; char* inputString = NULL;
    //(char*)malloc(sizeof(char) * DEFAULT_BUFFER); 
    char* protector = NULL;
    protector = (char*)DynamicAllocation(protector, sizeof(char), DEFAULT_BUFFER, MALLOC);
    
    while (input != '\n' && input != '\0' && (*index) <= fileSize)
    {
        if (CheckValid(input))
        {
            if (stringLogSize == 0)
            {
                //(char*)malloc(sizeof(char) * DEFAULT_BUFFER);
                inputString = (char*)DynamicAllocation(inputString, sizeof(char), DEFAULT_BUFFER, MALLOC);
                CheckMem(inputString);
            }

            inputString[stringLogSize] = input;
            stringLogSize++;
        }

        else if (stringLogSize > 0)
        {
            // (char*)realloc(inputString, sizeof(char) * (stringLogSize + 1));
            inputString = (char*)DynamicAllocation(inputString, sizeof(char), stringLogSize + 1, REALLOC);
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