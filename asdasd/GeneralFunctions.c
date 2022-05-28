#include "ProjectHeader.h"

Musician*** createMusiciansCollection(int numOfInstruments, Musician** MusiciansGroup, int numOfMusicians,InstrumentTree tree) //Creates the MusiciansCollection array.
{
    Musician*** output = NULL;
    output = (Musician***)DynamicAllocation(output, sizeof(Musician**), numOfInstruments, MALLOC);

    for (int i = 0; i < numOfInstruments; i++)
    {
        int j, k = 0, subArrayLogSize = 0, subArrayPhySize = 1;
        output[i] = NULL;
        output[i] = (Musician**)DynamicAllocation(output[i], sizeof(Musician*), subArrayPhySize, MALLOC);
        for (j = 0; j < numOfMusicians; j++)
        {
            if (searchInMPIList(&(MusiciansGroup[j]->instruments), i))
            {
                if (subArrayLogSize == subArrayPhySize)
                {
                    subArrayPhySize *= 2;
                    output[i] = (Musician**)DynamicAllocation(output[i], sizeof(Musician*), subArrayPhySize, REALLOC);
                }

                output[i][subArrayLogSize] = MusiciansGroup[j];
                subArrayLogSize++;

                if (j == numOfMusicians - 1 && subArrayPhySize > subArrayLogSize)
                    output[i] = (Musician**)DynamicAllocation(output[i], sizeof(Musician*), subArrayLogSize, REALLOC);
            }
        }
        updateNumOfMusicians(tree, subArrayLogSize, i);
    }

    return output;
}

int arrangeMusicians_for_concert(Musician*** concertMusician, Musician** MusicianCollection,
    int logSize , int MusicianNeeded, int* index) //Matches musicians to a concert.
{
    int counter = 0;
    for (int i = 0; i < logSize && counter < MusicianNeeded; i++)
    {
        if (!MusicianCollection[i]->isBooked)
        {
            (*concertMusician)[((*index)++)] = MusicianCollection[i];
            MusicianCollection[i]->isBooked = true;
            counter++;
        }
    }
    if (counter < MusicianNeeded)
    {
        return FAIL;
    }
    return counter;

}

void printMusicianName(char** MusicianName, int nameLen) //Prints musician's name.
{
    for (int i = 0; i < nameLen; i++)
        printf("%s ", MusicianName[i]);
}

void printMusicianDetails(Musician** musicians, int logSize) //Prints musician's details.
{
    float sum = 0;
    for (int i = 0; i < logSize; i++)
    {
        printMusicianName(musicians[i]->name, musicians[i]->nameLen);
        sum += musicians[i]->currInstPrice;
        CONDITION(i, logSize - 1, musicians[i]->currInstName, (int)musicians[i]->currInstPrice);
    }
    printf("Total cost: %d.\n", (int)sum);
}

void printDate(Date date_of_concert) //Prints the date of the concert.
{
    int first = 0, last = 0;
    PRINTDATE(date_of_concert.day);
    PRINTDATE(date_of_concert.month);
    printf("%d ", date_of_concert.year);
    first = (int)date_of_concert.hour;
    last = (int)((date_of_concert.hour - first) * 60);
    PRINT(last, first);
}

void printDetails(Concert* currConcert) //Prints concert's details.
{
    printf("%s ", currConcert->name);
    printDate(currConcert->date_of_concert);
    printMusicianDetails(currConcert->musicians, currConcert->No_OfMusicians);
}

void printConcert(int Succeed, Concert* currConcert) //Prints concert's details by failure/success in matching musicians.
{
    int res = RESULT(Succeed);
    switch (res)
    {
    case FAIL:
        printf("Could not find musicians for the concert %s\n", currConcert->name);
        break;
    case SUCCEED:
        printDetails(currConcert);
    default:
        break;
    }
}

void arrangeConcert(Musician*** MusicianCollection, InstrumentTree insTree,
    Musician** MusiciansGroup, int numOfMusicians) //Scans concerts's info from user and matches musicians to them.
{
    char input = getchar(), currImportance;
    while (input != '\n')
    {
        int index = 0, currInsID, currInsNumOfMusicians, Succeed = 0;
        Concert currConcert = { 0 };
        CIListNode* currInstrument = NULL;
        unsigned short No_of_musicians = 0;
        scanForConcertInfo(&currConcert, input, insTree);
        currInstrument = currConcert.instruments.head;
        currConcert.musicians = (Musician**)DynamicAllocation(currConcert.musicians, sizeof(Musician*), currConcert.No_OfMusicians ,MALLOC);

        while (currInstrument != NULL && Succeed != FAIL)
        {
            currInsID = currInstrument->data.inst;
            currImportance = currInstrument->data.importance;
            currInsNumOfMusicians = findNumOfMusicians(insTree, currInsID);
            updateCurrentInsIDAndImportance(MusicianCollection[currInsID], currInsNumOfMusicians, currInsID, currImportance, findInstrumentName(insTree, currInsID));
            qsort(MusicianCollection[currInsID], currInsNumOfMusicians, sizeof(Musician*), compareMusicians);
            Succeed = arrangeMusicians_for_concert(&currConcert.musicians, MusicianCollection[currInsID], currInsNumOfMusicians,currInstrument->data.num, &index);  
            currInstrument = currInstrument->next;
        }

        printConcert(Succeed, &currConcert);
        resetBookingInfo(MusiciansGroup, numOfMusicians);
        free(currConcert.name);
        free(currConcert.musicians);
        freeCIList(&currConcert.instruments);

        input = getchar();
    }
}