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
