#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "AirportManager.h"
#include "General.h"
#include "TextFiles.h"


int initManager(AirportManager* pManager, const char* fileName)
{

	if (!readManagerFromFile(pManager, fileName)) {
		if (!L_init(&pManager->airportsList)) return 0;
		
		return 2;
	}

	return 1;
}


int	addAirport(AirportManager* pManager)
{
	Airport* pPort = (Airport*)calloc(1, sizeof(Airport));
	if (!pPort)
		return 0;

	if (!initAirport(pPort, pManager))
	{
		freeAirport(pPort);
		free(pPort);
		return 0;
	}

	if (!&pManager->airportsList.head)
	{
		freeAirport(pPort);
		free(pPort);
		return 0;
	}

	NODE* ptr = findCorrectPlaceForAirport(&pManager->airportsList.head, pPort);
	if (!L_insert(ptr, pPort)) 
	{
		freeAirport(pPort);
		free(pPort);
		return 0;
	}

	return 1;
}

NODE* findCorrectPlaceForAirport(NODE* pNode, Airport* pPort) 
{
	NODE* ptr = pNode->next;
	NODE* ptrTemp = pNode;

	while (ptr != NULL) 
	{
		const char* currentCode = ((Airport*)ptr->key)->code;
		if (compareCodes(pPort->code, currentCode)) {
			return ptrTemp; 
		}
		ptrTemp = ptr; 
		ptr = ptr->next;

	}
	return ptrTemp; 
}

BOOL compareCodes(const char* code1, const char* code2) 
{
	for (int i = 0; i < IATA_LENGTH; i++) {
		if (code1[i] < code2[i]) return False;
		if (code1[i] > code2[i]) return True;
	}
	return False;
}

int countAirportsInList(NODE* pNode) 
{
	int countAirports = 0;
	NODE* ptr = pNode;

	if (!ptr) return countAirports;

	while (ptr->next != NULL) {
		countAirports++;
		ptr = ptr->next;
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
	NODE* ptr = pManager->airportsList.head.next;
	while (ptr) 
	{
		if (ptr->key && isAirportCode(((Airport*)ptr->key), code))
			return ptr->key;
		ptr = ptr->next;
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


int saveManagerToFile(const AirportManager* pManager, const char* fileName)
{
	FILE* pFile;
	pFile = fopen(fileName, "w");
	if (!pFile) return 0;

	if (!writeAirportManagerToTextFile(pFile, pManager)) return 0;

	fclose(pFile);
	return 1;
}

int readManagerFromFile(AirportManager* pManager, const char* fileName)
{
	FILE* pFile = fopen(fileName, "r");
	if (!pFile) return 0;
	if (!readAirportManagerFromTextFile(pFile, pManager)) return 0;
	fclose(pFile);
	return 1;
}

void	printAirports(const AirportManager* pManager)
{
	printf("there are %d airports\n", countAirportsInList(&pManager->airportsList.head));
	L_print(&pManager->airportsList, (void (*)(const void*)) printAirport);
}

void	freeManager(AirportManager* pManager)
{
	freeAirportList(pManager);
}


void	freeAirportList(AirportManager* pManager)
{
	NODE* ptr = pManager->airportsList.head.next;

	while (!ptr) {
		NODE* next = ptr->next;
		L_free(&pManager->airportsList, (void (*)(void*))freeAirport);
		ptr = next;
	}
}