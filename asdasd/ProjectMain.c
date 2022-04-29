#include "ProjectHeader.h"


int main()
{
	FILE* InstrumentsData = fopen("Instruments.txt", "r");
	if (InstrumentsData == NULL) 
	{
		perror("Unable to open file!");
		exit(1);
	};




	char** InstrumentsArr = NULL;
	InstrumentsArr  = DynamicAllocation1(InstrumentsArr,1,MALLOC);

	return 0;
}
