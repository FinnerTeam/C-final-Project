#include "ProjectHeader.h"
//DeleteDuplication(InstrumentsArr, &arrSize); //Irrelevant.

void main()
{
	int NO_instruments, NO_musicians;
	Musician** MusiciansGroup = NULL;
	FILE* InstrumentsData = NULL;
	FILE* MusiciansData = NULL;
	char** InstrumentsArr = NULL;
	InstrumentsArr = FileToArr(InstrumentsData, InstrumentsArr, &NO_instruments);
	InstrumentTree insTree = buildBinaryTreeFromArray(InstrumentsArr, NO_instruments);
<<<<<<< Updated upstream
	MusiciansGroup = FileToArr_Musicians(insTree, MusiciansData, &NO_musicians);
	Musician*** MusiciansCollection = NULL;
	MusiciansCollection = createMusiciansCollection(NO_instruments, MusiciansGroup, NO_musicians);
=======
	MusiciansGroup = FileToArr_Musicians(insTree, MusiciansData, &NO_musicians);// Tested Already, working .

>>>>>>> Stashed changes
}