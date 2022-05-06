#include "ProjectHeader.h"
void main()
{
	int arrSize;
	FILE* InstrumentsData = NULL;
	char** InstrumentsArr = NULL;
	InstrumentsArr = FileToArr(InstrumentsData, InstrumentsArr, &arrSize);
	DeleteDuplication(InstrumentsArr, &arrSize); //Irrelevant.
	InstrumentTree insTree = buildBinaryTreeFromArray(InstrumentsArr, arrSize);
	findInsId(insTree, "Guitar"); //testing;
}