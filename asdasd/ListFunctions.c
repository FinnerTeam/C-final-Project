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
	bool right=false, left = false;
	MPIListNode* currN = findMidElem(lst);

	while (currN != NULL&& !output && !(right && left))
	{
		if (currN->Data.insId == insId)
			output = true;

		else if (currN->Data.insId < insId)
		{
			right = true;
			currN = currN->next;
		}

		else
		{
			currN = currN->prev;
			left = true;
		}
	}

	return output;
}

MPIListNode* findMidElem(MPIList* lst) //Finds mid element in lst.
{
	MPIListNode* currS = lst->head, * currO = currS, * currE = lst->tail;

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

	return currO;
}

void sortMPIList(MPIList* lst) //Sorts MPIList
{
	MPIListNode* start = lst->head, * end = start->next;

	bool isHead = false, isTail = false;

	while (start != NULL)
	{
		if (end == NULL)
		{
			start = start->next;

			if (start != NULL)
				end = start->next;

			continue;
		}

		updateBooleanVariables(lst, start, end, &isHead, &isTail);

		MPIListNode* tempStart = start->next, * tempEnd = end->next, * tempGen = NULL;

		if (start->Data.insId >= end->Data.insId)
		{
			swapMPIListNodes(start, end);
			updateMPIListHeadAndTail(lst, end, start, isHead, isTail);
			tempGen = start; start = end; end = tempGen;
		}

		else
			end = end->next;
		
	}
}

void swapMPIListNodes(MPIListNode* nodeA, MPIListNode* nodeB) //Swaps nodeA&nodeB.
{
	MPIListNode* tempA = nodeA, * tempB = nodeB, * prevA = nodeA->prev, * nextB = nodeB->next, * nextA = nodeA->next, * prevB = nodeB->prev;

	if (nodeA->prev != NULL)
		nodeA->prev->next = tempB;

	if (nodeB->next != NULL)
		nodeB->next->prev = tempA;

	if (nodeA->next != nodeB)
	{
		nodeA->next->prev = tempB; nodeB->prev->next = tempA;
		nodeA->next = nextB; nodeA->prev = prevB;
		nodeB->next = nextA; nodeB->prev = prevA;
	}

	else if (nodeA->next == nodeB)
	{
		nodeA->prev = tempB; nodeA->next = nextB;
		nodeB->next = tempA; nodeB->prev = prevA;
	}
}

void updateMPIListHeadAndTail(MPIList* lst, MPIListNode* newHead, MPIListNode* newTail,
	bool isHead, bool isTail) //Updates lst's head&tail in sortMPIList function. 
{
	if (isHead)
		lst->head = newHead;

	if (isTail)
		lst->tail = newTail;
}

void insertDataToEndOfCIList(CIList* lst, int num, int insId, char importance, CIListNode* next) //Inserts new data to a CI list.
{
	CIListNode* node = createNewCIListNode(num, insId, importance, NULL);
	insertCIListNodeToEndList(lst, node);
}

CIListNode* createNewCIListNode(int num, int insId, char importance, CIListNode* next) //Creates a new CIListNode.
{
	CIListNode* output = (CIListNode*)malloc(sizeof(CIListNode));
	CheckMem(output);

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