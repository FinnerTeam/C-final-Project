#include "ProjectHeader.h"
/// <summary>
/// Utillities Functions for every Data Structure functions
/// </summary>
/// <param name="ch"></param>
/// <returns></returns>
/// 
/// 
// check if the chat validate
bool CheckValid(char ch) 
{
    return(ch != ' '
        && ch != ',' && ch != '.'
        && ch != ';' && ch != '?'
        && ch != '!' && ch != '-'
        && ch != '\t' && ch != 39
        && ch != '(' && ch != ')'
        && ch != '[' && ch != ']'
        && ch != '{' && ch != '}'
        && ch != '<' && ch != '>'
        && ch != '~' && ch != '_');
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
    {
        MusicianKit->tail->Data.price = (float)atoi(data->data[*(data->logicsize) - 1]);
    }
    sortMPIList(MusicianKit);
    if (*(name->logicsize) < *(name->physicalSize))
    {
        name->data = DynamicAllocation2(name->data, *(name->logicsize), REALLOC);
    }
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
        insertDataToEndOfMPIList(MusicianKit, data->data[*(data->logicsize) - 1], insId, 0, NULL, NULL);
        *InstrumentRead = false;
        *PriceRead = true;
        break;
    }
    case PRICE:
    {                                   //Needs to check about the float.. if there is really float inputs from the user.
        MusicianKit->tail->Data.price = (float)atoi(data->data[*(data->logicsize) - 1]);
        *InstrumentRead = true;
        *PriceRead = false;
        break;
    }
    default:
        break;
    }
}