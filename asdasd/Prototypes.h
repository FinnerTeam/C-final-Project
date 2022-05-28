#ifndef PROTOTYPES_H
#define PROTOTYPES_H
//***********************************PROTOTYPES***************************************************

    // Tree Functions
    TreeNode* createNewTreeNode(char* instrument, unsigned short insId, int numOfMusicians, TreeNode* left, TreeNode* right);
    InstrumentTree buildBinaryTreeFromArray(char** arrOfInstruments, int size);
    void insertNodeToTree(TreeNode* root, TreeNode* node);
    int findInsId(InstrumentTree tree, char* instrument);
    void recFindInsId(TreeNode* root, char* instrument, int* res);
    int findNumOfMusicians(InstrumentTree tree, int insId);
    int recFindNumOfMusicians(TreeNode* root, int insId);
    void recUpdateNumOfMusicians(TreeNode* root, int numOfMusicians, int insId);
    void updateNumOfMusicians(InstrumentTree tree, int numOfMusicians, int insId);
    char* findInstrumentName(InstrumentTree insTree, int insID);
    char* recFindInstrumentName(TreeNode* root, int insID);




    //List Functions
    void makeEmptyMPIList(MPIList* lst);
    bool isMPIListEmpty(MPIList lst);
    void insertDataToEndOfMPIList(MPIList* lst, char* instrumentName, unsigned int insId, float price, MPIListNode* next);
    MPIListNode* createNewMPIListNode(char* instrumentName, unsigned int insId, float price, MPIListNode* next);
    void insertMPIListNodeToEndOfList(MPIList* lst, MPIListNode* node);
    void makeEmptyCIList(CIList* lst);
    bool isEmptyCIList(CIList* lst);
    void insertCIListNodeToEndList(CIList* lst, CIListNode* node);
    CIListNode* createNewCIListNode(int num, int insId, char importance, CIListNode* next);
    void insertDataToEndOfCIList(CIList* lst, int num, int insId, char importance, CIListNode* next);

    //Memory Allocation Functions
    void* DynamicAllocation(void* ptr_ptr, size_t elemSize, size_t num_Of_elements, int Format);

    //Validators Functions
    void CheckMem(void* mem);
    void CheckFile(FILE* file);

    //Instruments Tree Helpers (Q1)
    char** FileToArr(char* fileName, int* sizeOfFile);

    //Musician Group Helpers (Q3)
    int FileLinesLen(FILE* FileData);
    Musician** createMusiciansGroup(InstrumentTree insTree, int* sizeOfFile, char* fileName);
    Musician* createMusician(InstrumentTree insTree, int* fileIndex, FILE* musiciansFile);
    char** getMusicianName(int* index, InstrumentTree insTree, FILE* musiciansFile, char** line, Musician** currMusician);
    MPIList createMusicianMPIList(InstrumentTree insTree, int* index, FILE* musiciansFile, char** line);
    void extractCharacters(char** destinationString, char* line, int* lineIndex);

    //Musician Collection Helpers (Q4)
    Musician*** createMusiciansCollection(int numOfInstruments, Musician** MusiciansGroup, int numOfMusicians, InstrumentTree tree);
    bool searchInMPIList(MPIList* lst, int insId);

    //Concert Helpers (Q5)
    void arrangeConcert(Musician*** MusicianCollection, InstrumentTree insTree, Musician** MusiciansGroup, int numOfMusicians);
    char* getName(char firstLetter);
    Date getConcertDate();
    CIList createConcertInstrumentsList(InstrumentTree insTree, unsigned short* numOfInsts);
    void updateCurrentInsIDAndImportance(Musician** musiciansArr, int arrSize,
        int insID, char importance, char* currInstName);
    float findInstPrice(MPIList lst, int insID);
    int compareMusicians(void* musicianA, void* musicianB);
    void resetBookingInfo(Musician** musiciansGroup, int numOfMusicians);
    void scanForConcertInfo(Concert* concert, char firstLetter, InstrumentTree insTree);

    //Free Functions
    void freeAll(char*** InstrumentsArr, int sizeOfInsArr, InstrumentTree* insTree,
        Musician*** MusiciansGroup, int sizeOfMGroup, Musician**** MusiciansCollection, int sizeOfMCol);
    void freeArr(char** instrumentsArr, int size);
    void freeInstrumentsTree(InstrumentTree tr);
    void recFreeInstrumentsTree(TreeNode* root);
    void freeMusiciansGroup(Musician** MusiciansGroup, int size);
    void freeMPIList(MPIList lst);
    void recFreeMPIList(MPIListNode* head);
    void freeCIList(CIList* lst);
    void recFreeCIList(CIListNode* head);
    void freeMusiciansCollection(Musician*** MusiciansCollection, int size);
#endif // !PROTOTYPES_H

