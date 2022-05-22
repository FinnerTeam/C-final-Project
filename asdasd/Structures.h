#pragma once

//*********************Data Structures*****************************
typedef struct treeNode
{
	char* instrument;
	unsigned short insId;
	int numOfMusicians;
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
	char* instrument;
	bool isBooked;
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
	int currInst;
	char currInsImportance;
	float currInstPrice;
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
	ConcertInstrument data;
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