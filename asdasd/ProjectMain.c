#include "ProjectHeader.h"
//DeleteDuplication(InstrumentsArr, &arrSize); //Irrelevant.
void main()
{
	int NO_instruments;
	int NO_musicians;
	Musician** MusiciansGroup = NULL;
	FILE* InstrumentsData = NULL;
	FILE* MusiciansData = NULL;
	char** InstrumentsArr = NULL;
	InstrumentsArr = FileToArr(InstrumentsData, InstrumentsArr, &NO_instruments);
	InstrumentTree insTree = buildBinaryTreeFromArray(InstrumentsArr, NO_instruments);
	MusiciansGroup = FileToArr_Musicians(insTree,MusiciansData, &NO_musicians);// Tested Already, working .
	