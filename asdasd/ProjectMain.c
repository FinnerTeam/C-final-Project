#include "ProjectHeader.h"
void main()
{
	int arrSize;
	FILE* InstrumentsData = NULL;
	char** InstrumentsArr = NULL;
	InstrumentsArr = FileToArr(InstrumentsData, InstrumentsArr, &arrSize);
	heapSort(&InstrumentsArr, arrSize);
	DeleteDuplication(InstrumentsArr, &arrSize);
	InstrumentTree insTree = BuildTreeFromArray(InstrumentsArr, arrSize);
}