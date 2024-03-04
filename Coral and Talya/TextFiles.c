#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TextFiles.h"
#include "General.h"
#include "list.h"


int writeAirportManagerToTextFile(FILE* pFile, AirportManager* pManager)
{
	NODE* ptr = &pManager->airportsList.head;
	
	fprintf(pFile, "%d\n", countAirportsInList(&pManager->airportsList.head));
	
	while (!ptr) {
		if (!writeAirportToTextFile(pFile, (Airport*)ptr->key)) return 0;
		ptr = ptr->next;
	}
	return 1;
}

int writeAirportToTextFile(FILE* pFile, Airport* pAirport)
{
	if (fprintf(pFile, "%s\n", pAirport->name) < 0) return 0;
	if (fprintf(pFile, "%s\n", pAirport->country) < 0) return 0;
	if (fprintf(pFile, "%s\n", pAirport->code) < 0) return 0;
	return 1;
}

int readAirportManagerFromTextFile(FILE* pFile, AirportManager* pManager) 
{
	L_init(&pManager->airportsList);
	NODE* ptr = &pManager->airportsList.head;
	Airport* pPort = NULL;
	int count = 0;

	if (fscanf(pFile, "%d\n", &count) != 1) return 0;

	while (count > 0) {
		pPort = (Airport*)calloc(1, sizeof(Airport));
		if (!pPort) return 0;
		if (!readAirportFromTextFile(pFile, pPort)) return 0;
		if (!L_insert(ptr, pPort)) return 0;
		ptr = ptr->next;
		count--;
	}

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

	//NODE* ptr = &pManager->airportsList.head;
	

	return 1;
}

int readAirportFromTextFile(FILE* pFile, Airport* pAirport)
{
	char tmp[MAX_STR_LEN] = { 0 };

	if (!fscanf(pFile, " %[^\n]\n", tmp)) return 0;
	pAirport->name = _strdup(tmp);
	if (!fscanf(pFile, " %[^\n]\n", tmp)) return 0;
	pAirport->country = _strdup(tmp);
	if (!fscanf(pFile, "%s\n", tmp)) return 0;
	strcpy(pAirport->code, tmp);
	return 1;
}
