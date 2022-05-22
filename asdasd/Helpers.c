#include "ProjectHeader.h"

/// Utillities Functions for every Data Structure functions

// check if the chat validate
bool CheckValid(char ch) 
{
    return(ch != ' '
        && ch != ',' && ch != '.'
        && ch != ';' && ch != '?'
        && ch != '!' && ch != '-'
        && ch != '\t' && ch != '\''
        && ch != '(' && ch != ')'
        && ch != '[' && ch != ']'
        && ch != '{' && ch != '}'
        && ch != '<' && ch != '>'
        && ch != '~' && ch != '_'
        && ch != '\n' && ch != ':');
}

// check if  need to realloc  *2 all the time
void Check_Physic_To_Logic(int logicSize, int* PhyisicSize, char*** Data_to_check)
{
    if (logicSize == *PhyisicSize)
    {
        (*PhyisicSize) *= 2;
        *Data_to_check = DynamicAllocation2(*Data_to_check, *PhyisicSize, REALLOC);
    }
}

// First allocation of the FileToArr_Musician function
void FirstAllocation(char*** data, char*** name)
{
    *name = DynamicAllocation2(*name, 1, MALLOC);
    CheckMem(*name);
    *data = DynamicAllocation2(*data, 1, MALLOC);
    CheckMem(*data);
    *(data[0]) = DynamicAllocation1(*(data[0]), FIRST_NAME, MALLOC);
    CheckMem(*(data[0]));
}

void EndOfReadOperation(Musician* MusicianGroup, bool PriceRead, MPIList* MusicianKit, DATATYPE* data, DATATYPE* name)
{
    if (PriceRead == true)
        MusicianKit->tail->Data.price = (float)atoi(data->data[*(data->logicsize) - 1]);

    if (*(name->logicsize) < *(name->physicalSize))
        name->data = DynamicAllocation2(name->data, *(name->logicsize), REALLOC);

    freeDATATYPE(data);

    MusicianGroup->name = DynamicAllocation2(MusicianGroup->name, *(name->logicsize), MALLOC);
    for (int i = 0; i < *(name->logicsize); i++)
    {
        (MusicianGroup->name)[i] = DynamicAllocation1((MusicianGroup->name)[i], strlen(name->data[i]) + 1, MALLOC);
        strcpy((MusicianGroup->name)[i], name->data[i]);
    }
    freeDATATYPE(name);
    MusicianGroup->instruments = *MusicianKit;
}

void NextWordOperation(DATATYPE* data, int* DataCol, bool* next_word)
{
    data->data[*(data->logicsize)] = DynamicAllocation1(data->data[*(data->logicsize)], (*DataCol) + 1, REALLOC);
    data->data[*(data->logicsize)][*DataCol] = '\0';
    *DataCol = 0;
    *(data->logicsize) += 1;
    Check_Physic_To_Logic(*(data->logicsize), data->physicalSize, &(data->data));
    data->data[*(data->logicsize)] = DynamicAllocation1(data->data[*(data->logicsize)], FIRST_NAME, MALLOC);
    *next_word = true;
}

void InstallizeFirst(DATATYPE* data, DATATYPE* name)
{
    data->logicsize = (int*)calloc(1, sizeof(int));
    data->physicalSize = (int*)calloc(1, sizeof(int));
    name->logicsize = (int*)calloc(1, sizeof(int));
    name->physicalSize = (int*)calloc(1, sizeof(int));
    *(data->physicalSize) += 1;
    *(name->physicalSize) += 1;
    FirstAllocation(&(data->data), &(name->data));

}

void priceAtend(DATATYPE* data, int dataCol, MPIList* MusicianKit)
{
    MusicianKit->tail->Data.price = (float)atoi(data->data[*(data->logicsize) - 1]);
}

void CheckExistInTree(int* insId, int* Position, bool* InstrumentRead, InstrumentTree insTree, DATATYPE data)
{
    *insId = findInsId(insTree, data.data[*(data.logicsize) - 1]);
    if (*insId != -1)
    {
        *InstrumentRead = true;
        *Position = INSTRUMENT;
    }
}

void Selector(int Position, DATATYPE* data, DATATYPE* name, MPIList* MusicianKit, bool* InstrumentRead,
    bool* PriceRead, int insId)
{
    switch (Position)
    {
    case NAME:
    {
        Check_Physic_To_Logic(*(name->logicsize), name->physicalSize, &(name->data));

        name->data[*(name->logicsize)] = DynamicAllocation1(name->data[*(name->logicsize)],
            strlen(data->data[*(data->logicsize) - 1]) + 1, MALLOC);

        strcpy(name->data[*(name->logicsize)], data->data[*(data->logicsize) - 1]);
        *(name->logicsize) += 1;
        break;
    }
    case INSTRUMENT:
    {
        insertDataToEndOfMPIList(MusicianKit, data->data[*(data->logicsize) - 1], insId, 0, false, NULL);
        *InstrumentRead = false;
        *PriceRead = true;
        break;
    }
    case PRICE:
    {                                   //Needs to check about the float.. if there is really float inputs from the user. //Checked.
        MusicianKit->tail->Data.price = (float)atoi(data->data[*(data->logicsize) - 1]);
        *InstrumentRead = true;
        *PriceRead = false;
        break;
    }
    default:
        break;
    }
}

int recPow(int base, int exp) //Raises base by exp.
{
    if (exp == 0)
        return 1;

    else if (exp == 1)
        return base;

    return base * recPow(base, exp - 1);
}

int buildDate(int type) //Returns a partial date by type.
{
    int output;
    char input = getchar();

    switch (type)
    {

    case DAY: //same for case MONTH.
        output = (input - '0') * 10;
        input = getchar();
        output += (input - '0');
        break;

    case YEAR:
        output = (input - '0') * 1000;
        for (int i = 2; i >= 0; i--)
        {
            input = getchar();
            output += (input - '0') * recPow(10, i);
        }
    }

    input = getchar(); //flush ' '.

    return output;
}

float buildHour() //Returns an hour by user's input.
{
    float hour = 0, minutes = 0, output;
    char input;

    for (int i = 1; i >= 0; i--)
    {
        input = getchar();
        hour += (input - '0') * recPow(10, i);
    }

    input = getchar(); //flush ':'.

    for (int j = 1; j >= 0; j--)
    {
        input = getchar();
        minutes += (input - '0') * recPow(10, j);
    }

    input = getchar(); //flush ' '.
    output = hour + (minutes / HOUR);
    return output;
}

void updateCurrentInsIDAndImportance(Musician** musiciansArr, int arrSize,
    int insID, char importance) //Updates insID, importance & price for each musician.
{
    for (int i = 0; i < arrSize; i++)
    {
        musiciansArr[i]->currInsImportance = importance;
        musiciansArr[i]->currInst = insID;
        musiciansArr[i]->currInstPrice = findInstPrice(musiciansArr[i]->instruments, insID);
    }
}

float findInstPrice(MPIList lst, int insID) //Finds instruments insID's price at lst.
{
    MPIListNode* curr = lst.head;
    float output;

    while (curr != NULL)
    {
        if (curr->Data.insId == insID)
            output = curr->Data.price;

        curr = curr->next;
    }

    return output;
}

int compareMusicians(void* musicianA, void* musicianB) //Compares musicianA&musicianB's prices for the current instrument.
{
    int output;
    Musician* firstMusician = *(Musician**)musicianA;
    Musician* secondMusician = *(Musician**)musicianB;

    if (firstMusician->currInsImportance == '1')
    {
        if (firstMusician->currInstPrice > secondMusician->currInstPrice)
            output = -1;

        else if (firstMusician->currInstPrice == secondMusician->currInstPrice)
            output = 0;

        else
            output = 1;
    }

    else if (firstMusician->currInsImportance == '0')
    {
        if (firstMusician->currInstPrice >= secondMusician->currInstPrice)
            output = 1;

        else if (firstMusician->currInstPrice == secondMusician->currInstPrice)
            output = 0;

        else
            output = -1;
    }

    return output;
}