#include "ProjectHeader.h"

void makeEmptyMPIList(MPIList* lst) //Sets lst as empty.
{
	lst->head = lst->tail = NULL;
}

bool isMPIListEmpty(MPIList lst) //Check whether lst is empty.
{
	return lst.head == NULL;
}

void insertDataToEndOfMPIList(MPIList* lst, char* instrumentName, unsigned int insId, float price, MPIListNode* next) //Inserts new data to the end of lst.
{
	MPIListNode* node = NULL;
	node = createNewMPIListNode(instrumentName, insId, price, next);
	insertMPIListNodeToEndOfList(lst, node);
}

MPIListNode* createNewMPIListNode(char* instrumentName, unsigned int insId, float price, MPIListNode* next) //Creates a new MPIListNode.
{
	MPIListNode* output = NULL;
	output = (MPIListNode*)DynamicAllocation(output, sizeof(MPIListNode), 1, MALLOC);
	
	output->instrument = NULL;
	output->instrument = (char*)DynamicAllocation(output->instrument,sizeof(char), strlen(instrumentName) + 1, MALLOC);

	if (instrumentName != '\0')
		strcpy(output->instrument, instrumentName);

	output->Data.insId = insId; output->Data.price = price; output->next = next;

	return output;
}

void insertMPIListNodeToEndOfList(MPIList* lst, MPIListNode* node) //Inserts node to the end of lst.
{
	if (isMPIListEmpty(*lst))
		lst->head = lst->tail = node;

	else
	{
		lst->tail->next = node;
		lst->tail = node;
	}
}

void insertDataToEndOfCIList(CIList* lst, int num, int insId, char importance, CIListNode* next) //Inserts new data to a CI list.
{
	CIListNode* node = createNewCIListNode(num, insId, importance, NULL);
	insertCIListNodeToEndList(lst, node);
}

CIListNode* createNewCIListNode(int num, int insId, char importance, CIListNode* next) //Creates a new CIListNode.
{
	CIListNode* output = NULL;
	output = (CIListNode*)DynamicAllocation(output, sizeof(CIListNode), 1, MALLOC);

	output->data.importance = importance;
	output->data.inst = insId;
	output->data.num = num;
	output->next = next;

	return output;
}

void insertCIListNodeToEndList(CIList* lst, CIListNode* node) //Inserts a node to the end of a CI list.
{
	if (isEmptyCIList(lst))
		lst->head = lst->tail = node;

	else
	{
		lst->tail->next = node;
		lst->tail = node;
	}
}

bool isEmptyCIList(CIList* lst) //Checks whether lst is empty.
{
	return lst->head == NULL;
}

void makeEmptyCIList(CIList* lst) //Makes lst an empty list.
{
	lst->head = lst->tail = NULL;
}

bool searchInMPIList(MPIList* lst, int insId) //Searches for insId in a given MPIList.
{
	bool found = false;
	MPIListNode* curr = lst->head;

	while (curr != NULL && !found)
	{
		if (curr->Data.insId == insId)
			found = true;

		curr = curr->next;
	}

	return found;
}