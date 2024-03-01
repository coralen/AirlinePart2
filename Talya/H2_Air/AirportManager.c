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
    L_insert( &pManager->airportsList.head,  pPort);
	//pManager->airportsList[pManager->airportsCount] = pPort;
	//pManager->airportsCount++;
	return 1;
}

int countAirportsInList(const LIST* airportsList){
    int countAirports=1;

    if (!airportsList) return False;

    while (!airportsList->head.key){
        countAirports++;
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

    NODE* ptr=pManager->airportsList.head.key;
    while (!ptr){
        if (isAirportCode(ptr->key, code))
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
    printf("there are %d airports\n", countAirportsInList(&pManager->airportsList));

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