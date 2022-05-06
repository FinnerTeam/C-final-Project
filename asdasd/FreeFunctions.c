#include "ProjectHeader.h"

void freeArrOfInstruments(char** instrumentsArr, int size) //Frees instrumentsArr.
{
	int i;

	for (i = 0; i < size; i++)
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
		free(MusiciansGroup[i]->name);
		freeMPIList(MusiciansGroup[i]->instruments);
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