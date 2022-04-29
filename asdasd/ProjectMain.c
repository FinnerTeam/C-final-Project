#include "ProjectHeader.h"

void main()
{
	FILE* InstrumentsData = NULL;
	char** InstrumentsArr = NULL;
    InstrumentsArr= DynamicAllocation2(InstrumentsArr, START_SIZE, MALLOC);
	FileToArr(InstrumentsData, InstrumentsArr);
}