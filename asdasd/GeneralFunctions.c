#include "ProjectHeader.h"

void createMusiciansCollection(Musician**** Collection, int numOfInstruments, Musician** MusiciansGroup, int numOfMusicians,InstrumentTree tree) //Creates the MusiciansCollection array.
{
    Musician*** output = (Musician***)malloc(sizeof(Musician**) * numOfInstruments);
    CheckMem(output);

    for (int i = 0; i < numOfInstruments; i++)
    {
        int j, k = 0, subArrayLogSize = 0, subArrayPhySize = 1;
        output[i] = (Musician**)malloc(sizeof(Musician*) * subArrayPhySize);
        CheckMem(output[i]);
        for (j = 0; j < numOfMusicians; j++)
        {
            if (searchInMPIList(&(MusiciansGroup[j]->instruments), i))
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
        updateNumOfMusicians(tree, subArrayLogSize, i);
    }
    *Collection = output;
}

//int ComparePrices(void* first,void* second) 
//{
//    MPIListNode nodeA = *((MPIListNode*)first);
//    MPIListNode nodeB = *((MPIListNode*)second);
//    return nodeA.Data.price - nodeB.Data.price;
//}
void arrangeConcert(Musician*** MusicianCollection, InstrumentTree insTree) //Scans concerts's info from user and matches musicians to them.
{
    char input = getchar();
    Concert currConcert;
    MPIListNode* curr;
    CIListNode* curr_concert;
    while (input != '\n')
    {
        currConcert.name = getName(input);
        currConcert.date_of_concert = getConcertDate();
        currConcert.instruments = createConcertInstrumentsList(insTree);
        curr_concert = currConcert.instruments.head;
        while (curr_concert != NULL)
        {
            curr = (*MusicianCollection)[curr_concert->data.inst]->instruments.head;
            while (curr != NULL)
            {
                int num_of_musicians = findInsId_Counter(insTree, curr_concert->data.inst);
                /*qsort(&(*MusicianCollection[curr_concert->data.inst]), num_of_musicians, sizeof(Musician*), ComparePrices);*/
                curr = curr->next;
            }


            curr_concert = curr_concert->next;
        }
   
        //qsort
        //match musicians
        //print

        free(&currConcert.instruments);
        input = getchar();
    }
}

char* getName(char firstLetter) //Scans for user's input name.
{
    char* output = NULL;
    int stringLogSize = 0, stringPhySize = 1;
    output = (char*)malloc(sizeof(char) * stringPhySize);
    CheckMem(output);
    char input = firstLetter;

    while (input != ' ')
    {
        if (stringLogSize == stringPhySize)
        {
            stringPhySize *= 2;
            output = (char*)realloc(output, sizeof(char) * stringPhySize);
            CheckMem(output);
        }

        output[stringLogSize] = input;
        stringLogSize++;
        input = getchar();
    }

    output = (char*)realloc(output, sizeof(char) * (stringLogSize + 1));
    CheckMem(output);
    output[stringLogSize] = '\0';

    return output;
}

Date getConcertDate() //Generates concert's date.
{
    Date output;

    output.day = buildDate(DAY);
    output.month = buildDate(MONTH);
    output.year = buildDate(YEAR);
    output.hour = buildHour();

    return output;
}

CIList createConcertInstrumentsList(InstrumentTree insTree) //Creates a CI list for a concert.
{
    CIList output;
    makeEmptyCIList(&output);
    char input = getchar(), importance;
    int numOfInstruments;
    
    while (input != '\n')
    {
        char* insName = getName(input);
        numOfInstruments = getNumOfInstruments();
        importance = getchar();

        insertDataToEndOfCIList(&output, numOfInstruments, findInsId(insTree, insName), importance, NULL);
        free(insName);

        input = getchar();

        if (input == ' ')
            input = getchar();
    }

    return output;
}

int getNumOfInstruments() //Returns num of instrument for a concert.
{
    int output = 0, iteration = 0;
    char input = getchar();

    while (input != ' ')
    {
        output += (input - '0') * recPow(10, iteration);
        iteration++;
        input = getchar();
    }

    return output;
}