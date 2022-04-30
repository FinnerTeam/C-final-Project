#include "ProjectHeader.h"
void main()
{
	FILE* InstrumentsData = NULL;
	char** InstrumentsArr = NULL;
	int mas;
<<<<<<< Updated upstream
	int bla;
=======
	int kas;
>>>>>>> Stashed changes
	InstrumentsArr = FileToArr(InstrumentsData, InstrumentsArr);
	heapSort(&InstrumentsArr, 13);
	DeleteDuplication(InstrumentsArr, 13);
}