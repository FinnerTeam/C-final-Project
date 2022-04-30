#pragma once
#include "ProjectHeader.h"
//*********************PROTOTYPES***************************************************
TreeNode* createNewTreeNode(char* instrument, unsigned short insId, TreeNode* left, TreeNode* right);
int findInsId(InstrumentTree tree, char* instrument);
void checkMemoryAllocation(void* p);
void checkFile(FILE* f);
char** DynamicAllocation2(char** ptr_ptr, int NewSize, int Format);
void CheckMem(void* mem);
int FileLinesLen(FILE* InstrumentsData);
char** FileToArr(FILE* InstrumentsData, char** InstrumentsArr);
char* DynamicAllocation1(char* Ptr, int NewSize, int Format);
void CheckFile(FILE* file);
void DeleteDuplication(char** InstrumentsArr, int size);
void maxHeapify(MaxHeap* maxHeap, int index);
MaxHeap* createAndBuildHeap(char** arr, int size);
void heapSort(char*** arr, int size);
void swapStrings(char** stringA, char** stringB);