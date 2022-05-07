#pragma once
#include "ProjectHeader.h"
//*********************PROTOTYPES***************************************************
TreeNode* createNewTreeNode(char* instrument, unsigned short insId, TreeNode* left, TreeNode* right);
InstrumentTree buildBinaryTreeFromArray(char** arrOfInstruments, int size);
void insertNodeToTree(TreeNode* root, TreeNode* node);
int findInsId(InstrumentTree tree, char* instrument);
void recFindInsId(TreeNode* root, char* instrument, int* res);
char** DynamicAllocation2(char** ptr_ptr, int NewSize, int Format);
void CheckMem(void* mem);
char** FileToArr(FILE* InstrumentsData, char** InstrumentsArr, int* sizeOfFile);
char* DynamicAllocation1(char* Ptr, int NewSize, int Format);
void CheckFile(FILE* file);
//void DeleteDuplication(char** InstrumentsArr, int* size);
//void maxHeapify(MaxHeap* maxHeap, int index);
//MaxHeap* createAndBuildHeap(char** arr, int size);
//void heapSort(char*** arr, int size);
//void swapStrings(char** stringA, char** stringB);
//<<<<<<< Updated upstream
void makeEmptyMPIList(MPIList* lst);
bool isMPIListEmpty(MPIList lst);
void insertDataToEndOfMPIList(MPIList* lst, char* instrumentName, unsigned int insId, float price, MPIListNode* next);
MPIListNode* createNewMPIListNode(char* instrumentName, unsigned int insId, float price, MPIListNode* next);
void insertMPIListNodeToEndOfList(MPIList* lst, MPIListNode* node);
void freeArr(char** instrumentsArr, int size);
void freeInstrumentsTree(InstrumentTree tr);
void recFreeInstrumentsTree(TreeNode* root);
void freeMusiciansGroup(Musician** MusiciansGroup, int size);
void freeMPIList(MPIList lst);
void recFreeMPIList(MPIListNode* head);
void InsertDataToMusicianGroup(InstrumentTree insTree, Musician* MusicianGroup, char* FreshData);
//=======
int FileLinesLen(FILE* FileData, char* FileName);
Musician** FileToArr_Musicians(InstrumentTree insTree, FILE* MusiciansData, int* sizeOfFile);
void InsertDataToMusicianGroup(InstrumentTree insTree, Musician* MusicianGroup, char* FreshData);
bool CheckValid(char ch);
void MallocArrguments(Musician* MusicianGroup, int Name_Size);
void FirstAllocation(char*** data, char*** name);
void Check_Physic_To_Logic(int logicSize, int* PhyisicSize, char*** Data_to_check);
//>>>>>>> Stashed changes
