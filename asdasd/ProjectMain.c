#include "ProjectHeader.h"
void main()
{
	FILE* InstrumentsData = NULL;
	char** InstrumentsArr = NULL;
	int mas;
	InstrumentsArr = FileToArr(InstrumentsData, InstrumentsArr);
	heapSort(&InstrumentsArr, 13);
	DeleteDuplication(InstrumentsArr, 13);
}