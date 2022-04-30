#include "ProjectHeader.h"
void main()
{
	FILE* InstrumentsData = NULL;
	char** InstrumentsArr = NULL;
	InstrumentsArr = FileToArr(InstrumentsData, InstrumentsArr);
	heapSort(&InstrumentsArr, 13);
	DeleteDuplication(InstrumentsArr, 13);
	InstrumentTree insTree = BuildTreeFromArray(InstrumentsArr, 10);
}