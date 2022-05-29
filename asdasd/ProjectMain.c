#include "ProjectHeader.h"

//Advanced Programming in C Course: Project
//Submittion by: Ben Cohen (209174549), Elior Migdal (313455321). 
//GitHub repository we work as a team with https://github.com/FinnerTeam/C-final-Project/tree/development/asdasd

void main(int argc, char* argv[])
{
	int NO_instruments, NO_musicians;
	
	char** InstrumentsArr = FileToArr(argv[1], &NO_instruments);
	InstrumentTree insTree = buildBinaryTreeFromArray(InstrumentsArr, NO_instruments);
	Musician** MusiciansGroup = createMusiciansGroup(insTree, &NO_musicians, argv[2]);
	Musician*** MusiciansCollection = createMusiciansCollection(NO_instruments, MusiciansGroup, NO_musicians, insTree);
	arrangeConcert(MusiciansCollection, insTree, MusiciansGroup, NO_musicians);
	freeAll(&InstrumentsArr, NO_instruments, &insTree, &MusiciansGroup, NO_musicians, &MusiciansCollection, NO_instruments);
}