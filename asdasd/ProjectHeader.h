#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define START_SIZE 1
#define MALLOC 1
#define REALLOC 2
#define DEFAULT_BUFFER 150
typedef struct treeNode
{
	char* instrument;
	unsigned short insId;
	struct treeNode* left;
	struct treeNode* right;
} TreeNode;

typedef struct tree
{
	TreeNode* root;
} InstrumentTree;

typedef struct
{
	unsigned short insId;
	float price;
} MusicianPriceInstrument;

typedef struct MPIlistNode
{
	struct MPIlistNode* next;
	char* instrument;
	unsigned short insId;
	float price;
} MPIListNode;

typedef struct
{
	MPIListNode* head;
	MPIListNode* tail;
} MPIList;

typedef struct
{
	char** name;
	MPIList instruments;
} Musician;

typedef struct
{
	int day, month, year;
	float hour;
} Date;

typedef struct
{
	int num;
	int inst;
	char importance;
} ConcertInstrument;

typedef struct CIlistNode
{
	struct CIlistNode* next;
	int num;
	int inst;
	char importance;
} CIListNode;

typedef struct
{
	CIListNode* head;
	CIListNode* tail;
} CIList;

typedef struct
{
	Date date_of_concert;
	char* name;
	CIList instruments;
} Concert;

TreeNode* createNewTreeNode(char* instrument, unsigned short insId, TreeNode* left, TreeNode* right);
int findInsId(InstrumentTree tree, char* instrument);
void checkMemoryAllocation(void* p);
void checkFile(FILE* f);
char** DynamicAllocation2(char** ptr_ptr, int NewSize, int Format);
void CheckMem(void* mem);
int FileLinesLen(FILE* InstrumentsData);
void FileToArr(FILE* InstrumentsData, char** InstrumentsArr);
char* DynamicAllocation1(char* Ptr, int NewSize, int Format);