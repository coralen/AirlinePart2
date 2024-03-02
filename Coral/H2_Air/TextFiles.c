#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "TextFiles.h"
#include "General.h"

int writeAirportManagerToTextFile(FILE* pFile, AirportManager* pManager)
{
	fprintf(pFile, "%d\n", pManager->airportsCount);
	for (int i = 0; i < pManager->airportsCount; i++)
		if (!writeAirportToTextFile(pFile, pManager->airportsArray[i])) return 0;
	return 1;
}

int writeAirportToTextFile(FILE* pFile, Airport* pAirport)
{
	if (fprintf(pFile, "%s\n", pAirport->name) < 0) return 0;
	if (fprintf(pFile, "%s\n", pAirport->country) < 0) return 0;
	if (fprintf(pFile, "%s\n", pAirport->code) < 0) return 0;
	return 1;
}

int readAirportManagerFromTextFile(FILE* pFile, AirportManager* pManager) // add readAirportArrFromTextFile and move the "for" loop
{
	if (fscanf(pFile, "%d\n", &pManager->airportsCount) != 1) return 0;

	Airport* pPort = NULL; 

	pManager->airportsArray = (Airport**)realloc(pManager->airportsArray, (pManager->airportsCount) * sizeof(Airport*));

	for (int i = 0; i < pManager->airportsCount; i++)
	{
		pPort = (Airport*)calloc(1, sizeof(Airport));
		if (!pPort) return 0;
		if (!readAirportFromTextFile(pFile, pPort)) return 0;
		pManager->airportsArray[i] = pPort;
	}
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
