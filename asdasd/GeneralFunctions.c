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

void arrangeConcert(Musician*** MusicianCollection, InstrumentTree insTree,
    Musician** MusiciansGroup, int numOfMusicians) //Scans concerts's info from user and matches musicians to them.
{
    char input = getchar(), currImportance;
    Concert currConcert;
    CIListNode* currInstrument = NULL;
    int currInsID, currInsNumOfMusicians;

    while (input != '\n')
    {
        scanForConcertInfo(&currConcert.name, input, &currConcert.date_of_concert, &currConcert.instruments, insTree);
        currInstrument = currConcert.instruments.head;

        while (currInstrument != NULL)
        {
            currInsID = currInstrument->data.inst;
            currImportance = currInstrument->data.importance;
            currInsNumOfMusicians = findInsId_Counter(insTree, currInsID);
            updateCurrentInsIDAndImportance(MusicianCollection[currInsID], currInsNumOfMusicians, currInsID, currImportance);
            qsort(MusicianCollection[currInsID], currInsNumOfMusicians, sizeof(Musician*), compareMusicians);

            currInstrument = currInstrument->next;
        }
        //maybe flag
        //add print concert
        resetBookingInfo(MusiciansGroup, numOfMusicians);
        freeCIList(&currConcert.instruments);

        input = getchar();
    }
}