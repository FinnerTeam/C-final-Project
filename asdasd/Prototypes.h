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
int FileLinesLen(FILE* InstrumentsData);
char** FileToArr(FILE* InstrumentsData, char** InstrumentsArr, int* sizeOfFile);
char* DynamicAllocation1(char* Ptr, int NewSize, int Format);
void CheckFile(FILE* file);
void DeleteDuplication(char** InstrumentsArr, int* size);
void maxHeapify(MaxHeap* maxHeap, int index);
MaxHeap* createAndBuildHeap(char** arr, int size);
void heapSort(char*** arr, int size);
void swapStrings(char** stringA, char** stringB);