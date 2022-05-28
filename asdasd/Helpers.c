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

void updateCurrentInsIDAndImportance(Musician** musiciansArr, int arrSize,
    int insID, char importance, char* currInstName) //Updates insID, importance & price for each musician.
{
    for (int i = 0; i < arrSize; i++)
    {
        if (!musiciansArr[i]->isBooked)
        {
            musiciansArr[i]->currInsImportance = importance;
            musiciansArr[i]->currInst = insID;
            musiciansArr[i]->currInstPrice = findInstPrice(musiciansArr[i]->instruments, insID);
            musiciansArr[i]->currInstName = currInstName;
        }
    }
}

float findInstPrice(MPIList lst, int insID) //Finds instruments insID's price at lst.
{
    MPIListNode* curr = lst.head;
    float output = 0.0;

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
    int output = 0;
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

void extractCharacters(char** destinationString, char* line, int* lineIndex) //Extracts valid characters from musicians's file.
{
    *destinationString = (char*)DynamicAllocation(*destinationString, sizeof(char), strlen(line) + 1, MALLOC);
    size_t destLogSize = 0;
    bool foundInvalid = false, foundFirstLetter = false;

    for (int i = *lineIndex; i < strlen(line) && !foundInvalid; i++)
    {
        if (CheckValid(line[i]))
        {
            foundFirstLetter = true;
            (*destinationString)[destLogSize] = line[i];
            destLogSize++;
        }

        else if (foundFirstLetter)
        {
            foundInvalid = true;
            *lineIndex = i;
        }
    }
    
    *destinationString = (char*)DynamicAllocation(*destinationString, sizeof(char), destLogSize + 1, REALLOC);
    (*destinationString)[destLogSize] = '\0';
}

void scanForConcertInfo(Concert* concert, char firstLetter, InstrumentTree insTree) //Scans for concert info.
{
    concert->No_OfMusicians = 0;
    concert->name = getName(firstLetter);
    concert->date_of_concert = getConcertDate();
    concert->instruments = createConcertInstrumentsList(insTree, &concert->No_OfMusicians);
}

char* getName(char firstLetter) //Scans for user's input name.
{
    char* output = NULL;
    size_t stringLogSize = 0, stringPhySize = 1;
    output = (char*)DynamicAllocation(output, sizeof(char), stringPhySize, MALLOC);
    char input = firstLetter;

    while (input != ' ')
    {
        if (stringLogSize == stringPhySize)
        {
            stringPhySize *= 2;
            output = (char*)DynamicAllocation(output, sizeof(char), stringPhySize, REALLOC);
        }

        output[stringLogSize] = input;
        stringLogSize++;
        input = getchar();
    }

    output = (char*)DynamicAllocation(output, sizeof(char), stringLogSize + 1, REALLOC);
    output[stringLogSize] = '\0';

    return output;
}

Date getConcertDate() //Generates concert's date.
{
    Date output;
    int hour, minutes;
    char colon;

    (void)scanf("%d", &output.day);
    (void)scanf("%d", &output.month);
    (void)scanf("%d", &output.year);
    (void)scanf("%d", &hour);
    (void)scanf("%c", &colon);
    (void)scanf("%d", &minutes);
    output.hour = (float)(hour + (minutes / HOUR));

    return output;
}

CIList createConcertInstrumentsList(InstrumentTree insTree, unsigned short* numOfInsts) //Creates a CI list for a concert.
{
    CIList output;
    makeEmptyCIList(&output);
    char input = getchar(), importance;
    int numOfInstruments, digImportance;

    if (input == ' ')
        input = getchar();

    while (input != '\n')
    {
        char* insName = getName(input);
        (void)scanf("%d", &numOfInstruments);
        (void)scanf("%d", &digImportance);

        importance = digImportance + '0';

        insertDataToEndOfCIList(&output, numOfInstruments, findInsId(insTree, insName), importance, NULL);
        free(insName);

        (*numOfInsts) = *numOfInsts + numOfInstruments;

        input = getchar();

        if (input == ' ')
            input = getchar();
    }

    return output;
}

void resetBookingInfo(Musician** musiciansGroup, int numOfMusicians) //Resets booking info after each concert.
{
    for (int i = 0; i < numOfMusicians; i++)
        musiciansGroup[i]->isBooked = false;
}