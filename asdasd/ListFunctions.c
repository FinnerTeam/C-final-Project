#include "ProjectHeader.h"

void makeEmptyMPIList(MPIList* lst) //Sets lst as empty.
{
	lst->head = lst->tail = NULL;
}

bool isMPIListEmpty(MPIList lst) //Check whether lst is empty.
{
	return lst.head == NULL;
}

void insertDataToEndOfMPIList(MPIList* lst, char* instrumentName, unsigned int insId, float price, MPIListNode* next, MPIListNode* prev) //Inserts new data to the end of lst.
{
	MPIListNode* node = NULL;
	node = createNewMPIListNode(instrumentName, insId, price, next, prev);
	insertMPIListNodeToEndOfList(lst, node);
}

MPIListNode* createNewMPIListNode(char* instrumentName, unsigned int insId, float price, MPIListNode* next, MPIListNode* prev) //Creates a new MPIListNode.
{
	MPIListNode* output = (MPIListNode*)malloc(sizeof(MPIListNode));
	CheckMem(output);
	
	output->instrument = NULL;
	output->instrument = DynamicAllocation1(output->instrument, strlen(instrumentName) + 1, MALLOC);
	CheckMem(output->instrument);
	if (instrumentName != '\0')
	{
		strcpy(output->instrument, instrumentName);
	}
	output->Data.insId = insId; output->Data.price = price; output->next = next, output->prev = prev;

	return output;
}

void insertMPIListNodeToEndOfList(MPIList* lst, MPIListNode* node) //Inserts node to the end of lst.
{
	if (isMPIListEmpty(*lst))
		lst->head = lst->tail = node;

	else
	{
		node->prev = lst->tail;
		lst->tail->next = node;
		lst->tail = node;
	}
}

bool MPIListBinarySearch(MPIList* lst, int insId) //Searches for insId in lst. Returns true/false.
{
	bool output = false;

	MPIListNode* currN = findMidElem(lst);

	while (currN != NULL)
	{
		if (currN->Data.insId == insId)
			output = true;

		else if (currN->Data.insId < insId)
			currN = currN->next;

		else
			currN = currN->prev;
	}

	return output;
}

MPIListNode* findMidElem(MPIList* lst) //Finds mid element in lst.
{
	MPIListNode* currS = lst->head, * currO = NULL, * currE = lst->tail;

	while (currS != currE && !currO)
	{
		if (currS->next != currE)
		{
			currS = currS->next;
			currE = currE->prev;
		}

		else
			currO = currS;
	}

	currO = currS;
	return currO;
}
		