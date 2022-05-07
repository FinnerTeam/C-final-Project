#include "ProjectHeader.h"
void createMusiciansCollection(Musician**** Collection, int numOfInstruments, Musician** MusiciansGroup, int numOfMusicians) //Creates the MusiciansCollection array.
{
    Musician*** output = NULL;
    output = (Musician***)malloc(sizeof(Musician**) * numOfInstruments);
    CheckMem(output);
    int i, j, k, subArrayLogSize, subArrayPhySize = 1;

    for (i = 0; i < numOfInstruments; i++)
    {
        subArrayPhySize = 1;
        output[i] = (Musician**)malloc(sizeof(Musician*) * subArrayPhySize);
        CheckMem(output[i]);
        subArrayLogSize = 0;
        for (j = 0; j < numOfMusicians; j++)
        {
            if (MPIListBinarySearch(&(MusiciansGroup[j]->instruments), i))
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
    }
    *Collection = output;

}