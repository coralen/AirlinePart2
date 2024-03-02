#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "include/AirportManager.h"
#include "include/General.h"

int	initManager(AirportManager* pManager)
{
    //Talya added:
//	pManager->airportsCount = 0;
//	pManager->airportsList = NULL;
    L_init( &pManager->airportsList);
	return 1;
}

int	addAirport(AirportManager* pManager)
{
	Airport* pPort  = (Airport*)calloc(1, sizeof(Airport));
	if (!pPort)
		return 0;

	if (!initAirport(pPort, pManager))
	{
		freeAirport(pPort);
		free(pPort);
		return 0;
	}
//Talya added:
	//pManager->airportsList = (Airport**)realloc(pManager->airportsList,
		//(countAirportsInList(&pManager->airportsList) + 1) * sizeof(Airport*));
	if (!&pManager->airportsList.head)
	{
		freeAirport(pPort);
		free(pPort);
		return 0;
	}
//Talya added:
    NODE* ptr=&pManager->airportsList.head;
    ptr=findCorrectPlaceForAirport( ptr, pPort);
    L_insert(ptr, pPort);
	//pManager->airportsList[pManager->airportsCount] = pPort;
	//pManager->airportsCount++;
	return 1;
}
//Talya added:
NODE* findCorrectPlaceForAirport(NODE* pNode, Airport* pPort){
    NODE *ptr = pNode;
    NODE* ptrTemp = pNode;

    while (ptr) {
        const char *currentCode = ((Airport *) ptr->key)->code;
        if (compareCodes(pPort->code, currentCode)) {
            return ptrTemp; //if the new code comes before the currentCode we return the previous pointer in the list
        }
        ptrTemp=ptr; //if the codes are equal we move on to the next pointer before checking the next code
        ptr=ptr->next;

    }
    return ptrTemp; //if the code should be last in the list we return the pointer that points to Null
}
//talya added:
BOOL compareCodes(const char* code1,const char* code2){
    for (int i=0; i<IATA_LENGTH; i++){
        if (code1[i]<code2[i]) return False;
        if (code1[i]>code2[i]) return True;
    }return False;
}

int countAirportsInList(NODE* pNode){
    int countAirports=0;
    NODE* ptr= pNode;

    if (!ptr) return countAirports;

    while (ptr->next !=NULL){
        countAirports++;
        ptr=ptr->next;
    }

    return countAirports;
}

int  initAirport(Airport* pPort, AirportManager* pManager)
{
	while (1)
	{
		getAirportCode(pPort->code);
		if (checkUniqeCode(pPort->code, pManager))
			break;

		printf("This code already in use - enter a different code\n");
	}

	return initAirportNoCode(pPort);
}

Airport* findAirportByCode(const AirportManager* pManager, const char* code)
{
    //talya changed:

//	for (int i = 0; i < countAirportsInList(&pManager->airportsList); i++)
//	{
//		if (isAirportCode(pManager->airportsList.head.key, code))
//			return pManager->airportsList.head.key;
//	}

    NODE* ptr=&pManager->airportsList.head;
    while (ptr !=NULL){
        if (isAirportCode(((Airport*)ptr->key), code))
            return ptr->key;

        ptr=ptr->next;
    }
	return NULL;
}

int checkUniqeCode(const char* code,const AirportManager* pManager)
{
	Airport* port = findAirportByCode(pManager, code);

	if (port != NULL)
		return 0;

	return 1;
}


void	printAirports(const AirportManager* pManager)
{
    //talya changed the printing
    printf("there are %d airports\n", countAirportsInList(&pManager->airportsList.head));

//    NODE* ptr=pManager->airportsList.head.key;

//    while (ptr){
//        printAirport((Airport *)ptr);
//        ptr=ptr->next;
//    }

    L_print(&pManager->airportsList, (void (*)(const void *)) printAirport);

}

void freeManager(AirportManager* pManager)
{
    freeAirportList(pManager);
}


void	freeAirportList(AirportManager* pManager)
{
	//Talya changed
    NODE* ptr=pManager->airportsList.head.next;

    while (!ptr){
        NODE* next = ptr->next;
        L_free(&pManager->airportsList, (void (*)(void *))freeAirport);
        ptr = next;
    }


//    for (int i = 0; i < pManager->airportsCount; i++)
//	{
//		freeAirport(pManager->airportsList[i]);
//		free(pManager->airportsList[i]);
//	}
	//free(pManager->airportsList);
}