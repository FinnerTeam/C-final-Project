#include "ProjectHeader.h"

void freeAll(char*** InstrumentsArr, int sizeOfInsArr, InstrumentTree* insTree,
	Musician*** MusiciansGroup, int sizeOfMGroup, Musician**** MusiciansCollection, int sizeOfMCol) //Frees all projects's memrory allocations.
{
	freeArr(*InstrumentsArr, sizeOfInsArr);
	freeInstrumentsTree(*insTree);
	freeMusiciansGroup(*MusiciansGroup, sizeOfMGroup);
	freeMusiciansCollection(*MusiciansCollection, sizeOfMCol);
}

void freeArr(char** instrumentsArr, int size) //Frees instrumentsArr.
{
	for (int i = 0; i < size; i++)
		free(instrumentsArr[i]);

	free(instrumentsArr);
}

void freeInstrumentsTree(InstrumentTree tr) //Frees the instruments tree.
{
	recFreeInstrumentsTree(tr.root);
}

void recFreeInstrumentsTree(TreeNode* root) //Recursively frees the instruments tree.
{
	if (root == NULL)
		return;

	else if (root->left == NULL && root->right == NULL)
	{
		free(root->instrument);
		free(root);
		return;
	}

	else
	{
		recFreeInstrumentsTree(root->left);
		recFreeInstrumentsTree(root->right);

		free(root->instrument);
		free(root);
	}
}

void freeMusiciansGroup(Musician** MusiciansGroup, int size) //Frees MusiciansGroup.
{
	int i;

	for (i = 0; i < size; i++)
	{
		freeArr(MusiciansGroup[i]->name, MusiciansGroup[i]->nameLen);
		freeMPIList(MusiciansGroup[i]->instruments);
		free(MusiciansGroup[i]);
	}

	free(MusiciansGroup);
}

void freeMPIList(MPIList lst) //Frees MPIList.
{
	recFreeMPIList(lst.head);
}

void recFreeMPIList(MPIListNode* head) //Recursively frees MPIList.
{
	if (head == NULL)
		return;

	else
	{
		recFreeMPIList(head->next);
		free(head->instrument);
		free(head);
	}
}

void freeCIList(CIList* lst) //Frees a CI List.
{
	recFreeCIList(lst->head);
}

void recFreeCIList(CIListNode* head) //Recursively frees a CI list.
{
	if (head == NULL)
		return;

	else
	{
		recFreeCIList(head->next);
		free(head);
	}
}

void freeMusiciansCollection(Musician*** MusiciansCollection, int size) //Frees MusiciansCollection.
{
	for (int i = 0; i < size; i++)
		free(MusiciansCollection[i]);

	free(MusiciansCollection);
}