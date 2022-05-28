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

int arrangeMusicians_for_concert(Musician*** concertMusician,Musician** MusicianCollection,int logSize ,int MusicianNeeded,int* index)
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
void printMusicianName(char** MusicianName, int nameLen)
{
    for (int i = 0; i < nameLen; i++)
    {
        printf(" %s ", MusicianName[i]);
    }
}
void printMusicianDetails(Musician** musicians,int logSize)
{
    float sum = 0;
    for (int i = 0; i < logSize; i++)
    {
        printMusicianName(musicians[i]->name, musicians[i]->nameLen);
        sum += musicians[i]->currInstPrice;
        printf("- %s (%lf),", musicians[i]->currInstName,musicians[i]->currInstPrice);
    }
    printf(". Totla cost: %lf.", sum);
}
void printDetails(Concert* currConcert)
{
    int first = 0, last = 0;
    
    printf("%s ", currConcert->name);
    printf("%d ", currConcert->date_of_concert.day);
    printf("%d ", currConcert->date_of_concert.month);
    printf("%d ", currConcert->date_of_concert.year);

    first = (int)currConcert->date_of_concert.hour;
    last = (int)((currConcert->date_of_concert.hour - first) * 60);
    printf("%d:%d: ", first, last);
    printMusicianDetails(currConcert->musicians, currConcert->No_OfMusicians);
}
void printConcert(int Succeed,Concert* currConcert)
{
    int res = RESULT(Succeed);
    switch (res)
    {
    case FAIL:
        printf("Could not find musicians for the concert %s", currConcert->name);
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
    char input = 's', currImportance;
    Concert currConcert = { 0 };
    CIListNode* currInstrument = NULL;
    int currInsID, currInsNumOfMusicians;
    unsigned short No_of_musicians = 0;
    int Succeed = 0;
    int index = 0;
    while (input != '\n')
    {
<<<<<<< Updated upstream
        scanForConcertInfo(&currConcert, input, insTree);
=======
       /* int some = FileLinesLenSTDIN();
        
        currConcert.name = (char*)DynamicAllocation(currConcert.name, sizeof(char), some, MALLOC);
        fscanf(stdin,"%s", currConcert.name);*/
        scanForConcertInfo(&currConcert.name, input, &currConcert.date_of_concert, &currConcert.instruments, insTree);
>>>>>>> Stashed changes
        currInstrument = currConcert.instruments.head;
        currConcert.musicians = (Musician**)DynamicAllocation(currConcert.musicians, sizeof(Musician*), currConcert.No_OfMusicians,MALLOC);
        while (currInstrument != NULL && Succeed != FAIL)
        {
            currInsID = currInstrument->data.inst;
            currImportance = currInstrument->data.importance;
            currInsNumOfMusicians = findInsId_Counter(insTree, currInsID);
            updateCurrentInsIDAndImportance(MusicianCollection[currInsID], currInsNumOfMusicians, currInsID, currImportance, findInstrumentName(insTree, currInsID));
            qsort(MusicianCollection[currInsID], currInsNumOfMusicians, sizeof(Musician*), compareMusicians);
            Succeed = arrangeMusicians_for_concert(&currConcert.musicians, MusicianCollection[currInsID], currInsNumOfMusicians,currInstrument->data.num, &index);
            currInstrument = currInstrument->next;
        }
<<<<<<< Updated upstream
        //add print concert
=======
        printConcert(Succeed, &currConcert);
>>>>>>> Stashed changes
        resetBookingInfo(MusiciansGroup, numOfMusicians);
        free(currConcert.musicians);
        freeCIList(&currConcert.instruments);

        input = getchar();
    }
}