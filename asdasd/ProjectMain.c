#include "ProjectHeader.h"

void main()
{
	char arr[] = { "Gamma", "Echo", "Alpha", "Delta", "Beta" };
	mergeSortInstrumentsArr(&arr, 5);
}

void mergeSortInstrumentsArr(char*** instrumentsArr, int size) //Sorts an array of strings.
{
	if (size <= 1)
		return;

	else
	{
		mergeSortInstrumentsArr(instrumentsArr, size / 2);
		mergeSortInstrumentsArr(instrumentsArr + size / 2, size - size / 2);

		mergeInstrumentsArr(instrumentsArr, instrumentsArr, size / 2, instrumentsArr + size / 2, size - size / 2);
	}
}

void mergeInstrumentsArr(char*** instrumentsArr, char*** arrA, int sizeA, char*** arrB, int sizeB) //Merges arrA & arrB.
{
	int indD = 0, indA = 0, indB = 0;

	while (indA < sizeA && indB < sizeB)
	{
		if ((strcmp(*(arrA + indA), *(arrB + indB))) >= 0)
		{
			swapStrings((arrB + indB), (arrA + indA));
			indB++;
		}
			

		else
		{
			swapStrings((arrB + indB), (arrA + indA));
			indA++;
		}
	}
}

void swapStrings(char** stringA, char** stringB) //Swaps stringA and stringB in instrumentsArr.
{
	char* temp;
	strcpy(temp, *stringA);
	strcpy(*stringA, *stringB);
	strcpy(*stringB, temp);
}