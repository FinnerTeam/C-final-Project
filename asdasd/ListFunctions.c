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

	return currO;
}

void sortMPIList(MPIList* lst) //Sorts MPIList
{
	MPIListNode* start = lst->head, * end = start->next, * prevStart = start->prev, * nextStart = start->next, * prevEnd = NULL, * nextEnd = NULL;

	if (end != NULL)
	{
		prevEnd = end->prev;
		nextEnd = end->next;
	}

	while (start != NULL)
	{
		if (end == NULL)
		{
			start = start->next;
			if (start != NULL)
				end = start->next;
		}

		else if (start->Data.insId >= end->Data.insId && start->next != end)
		{
			if (start != lst->head && end != lst->tail)
			{
				start->next = nextEnd; start->prev = prevEnd;
				end->next = nextStart; end->prev = prevStart;

				prevStart->next = nextStart->prev = end;
				prevEnd->next = nextEnd->prev = start;
			}

			else if (start == lst->head && end != lst->tail)
			{
				start->next = nextEnd; start->prev = prevEnd;
				end->prev = NULL; end->next = nextStart;

				nextStart->prev = end;
				prevEnd->next = nextEnd->prev = start;

				lst->head = end;
			}

			else if (start != lst->head && end == lst->tail)
			{
				start->next = NULL; start->prev = prevEnd;
				end->next = nextStart; end->prev = prevStart;

				prevEnd->next = start;
				prevStart->next = nextStart->prev = end;

				lst->tail = start;
			}

			else if (start == lst->head && end == lst->tail)
			{
				start->next = NULL; start->prev = prevEnd;
				end->prev = NULL; end->next = nextStart;

				prevEnd->next = start;
				nextStart->prev = end;

				lst->head = end;
				lst->tail = start;
			}
		}

		else if (start->Data.insId >= end->Data.insId && start->next == end)
		{
			start->next = nextEnd;
			if(nextEnd != NULL)
				nextEnd->prev = start;
			if (nextEnd == NULL)
				lst->tail = start;
			start->prev = end;

			end->prev = prevStart;
			if(prevStart != NULL)
				prevStart->next = end;
			if (prevStart == NULL)
				lst->head = end;
			end->next = start;
		}
		
		else
		{
			end = end->next;
			if (end != NULL)
			{
				prevEnd = end->prev;
				nextEnd = end->next;
			}
		}

		start = nextStart;
		if (start != NULL)
		{
			prevStart = start->prev;
			nextStart = start->next;
		}

		end = nextEnd;
		if (end != NULL)
		{
			prevEnd = end->prev;
			nextEnd = end->next;
		}
	}
}
		