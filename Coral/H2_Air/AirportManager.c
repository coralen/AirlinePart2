#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "AirportManager.h"
#include "General.h"
#include "TextFiles.h"


// to delete
//int	initManager(AirportManager* pManager)
//{
//	pManager->airportsCount = 0;
//	pManager->airportsArray = NULL;
//
//	return 1;
//}

// coral added
int initManager(AirportManager* pManager, const char* fileName)
{
	pManager->airportsCount = 0; // check if needed
	pManager->airportsArray = NULL; // check if needed

	if (!readManagerFromFile(pManager, fileName)) {
		
		// add here the implementation for list
		
		return 2;
	}

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

	pManager->airportsArray = (Airport**)realloc(pManager->airportsArray,
		(pManager->airportsCount + 1) * sizeof(Airport*));
	if (!pManager->airportsArray)
	{
		freeAirport(pPort);
		free(pPort);
		return 0;
	}
	
	
	pManager->airportsArray[pManager->airportsCount] = pPort;
	pManager->airportsCount++;
	return 1;
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
	for (int i = 0; i < pManager->airportsCount; i++)
	{
		if (isAirportCode(pManager->airportsArray[i], code))
			return pManager->airportsArray[i];
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

// coral added
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
	printf("there are %d airports\n", pManager->airportsCount);
	for (int i = 0; i < pManager->airportsCount; i++)
	{
		printAirport(pManager->airportsArray[i]);
		printf("\n");
	}
}

void	freeManager(AirportManager* pManager)
{
	freeAirportArr(pManager);
}


void	freeAirportArr(AirportManager* pManager)
{
	for (int i = 0; i < pManager->airportsCount; i++)
	{
		freeAirport(pManager->airportsArray[i]);
		free(pManager->airportsArray[i]);
	}
	free(pManager->airportsArray);
}