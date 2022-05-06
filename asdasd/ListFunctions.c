#include "ProjectHeader.h"

void makeEmptyMPIList(MPIList* lst) //Sets lst as empty.
{
	lst->head = lst->tail = NULL;
}

bool isMPIListEmpty(MPIList lst) //Check whether lst is empty.
{
	return lst.head == NULL;
}

void insertDataToEndOfMPIList(MPIList lst, char* instrumentName, unsigned int insId, float price, MPIListNode* next) //Inserts new data to the end of lst.
{
	MPIListNode* node = NULL;
	node = createNewMPIListNode(instrumentName, insId, price, next);
	insertMPIListNodeToEndOfList(lst, node);
}

MPIListNode* createNewMPIListNode(char* instrumentName, unsigned int insId, float price, MPIListNode* next) //Creates a new MPIListNode.
{
	MPIListNode* output = (MPIListNode*)malloc(sizeof(MPIListNode));
	CheckMem(output);

	output->instrument = (char*)malloc(sizeof(char) * (strlen(instrumentName) + 1));
	CheckMem(output->instrument);

	strcpy(output->instrument, instrumentName);
	output->Data.insId = insId; output->Data.price = price; output->next = next;

	return output;
}

void insertMPIListNodeToEndOfList(MPIList lst, MPIListNode* node) //Inserts node to the end of lst.
{
	if (isListEmpty(lst))
		lst.head = lst.tail = node;

	else
	{
		lst.tail->next = node;
		lst.tail = node;
	}
}
		