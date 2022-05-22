#include "ProjectHeader.h"

void main()
{
	int NO_instruments, NO_musicians;
	FILE* InstrumentsData = NULL, * MusiciansData = NULL;
	char** InstrumentsArr = NULL;
	Musician** MusiciansGroup = NULL;
	Musician*** MusiciansCollection = NULL;
	
	InstrumentsArr = FileToArr(InstrumentsData, InstrumentsArr, &NO_instruments);
	InstrumentTree insTree = buildBinaryTreeFromArray(InstrumentsArr, NO_instruments);
	MusiciansGroup = createMusiciansGroup(insTree, MusiciansData, &NO_musicians);
	createMusiciansCollection(&MusiciansCollection,NO_instruments, MusiciansGroup, NO_musicians, insTree);
	arrangeConcert(MusiciansCollection, insTree);
}