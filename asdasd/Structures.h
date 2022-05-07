#pragma once
//*********************Data Structures*****************************
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
	int* logicsize;
	int* physicalSize;
	char** data;
}DATATYPE;
typedef struct
{
	unsigned short insId;
	float price;
} MusicianPriceInstrument;

typedef struct MPIlistNode
{
	struct MPIlistNode* next;
	struct MPIlistNode* prev;
	char* instrument;
	MusicianPriceInstrument Data;
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

typedef struct
{
	int size;
	char** arr;
} MaxHeap;