#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "airlineFile.h"


int writeAirlineToBFile(FILE* pFile, const Airline* pComp)
{
	int len = (int)(strlen(pComp->name)) + 1;
	if (fwrite(&len, sizeof(int), 1, pFile) != 1) return 0;
	if (fwrite(pComp->name, sizeof(char), len, pFile) != len) return 0;
	if (fwrite(&pComp->planeCount, sizeof(int), 1, pFile) != 1) return 0;
	if (fwrite(pComp->planeArr, sizeof(Plane), pComp->planeCount, pFile) != pComp->planeCount) return 0;
	if (fwrite(&pComp->flightCount, sizeof(int), 1, pFile) != 1) return 0;
	if (!writeFlightArrToBFile(pFile, pComp->flightArr, pComp->flightCount)) return 0;
	return 1;
}

int writeFlightArrToBFile(FILE* pFile, Flight** const flightArr, const int count)
{
	for (int i = 0; i < count; i++)
	{
		if (!writeFlightToBFile(pFile, flightArr[i]))
		{
			fclose(pFile);
			return 0;
		}
	}
	return 1;
}

int writeFlightToBFile(FILE* pFile, const Flight* pFlight)
{
	if (fwrite(pFlight->sourceCode, sizeof(char), IATA_LENGTH, pFile) != IATA_LENGTH) return 0;
	if (fwrite(pFlight->destCode, sizeof(char), IATA_LENGTH, pFile) != IATA_LENGTH) return 0;
	if (fwrite(&pFlight->flightPlane.serialNum, sizeof(int), 1, pFile) != 1) return 0;
	if (fwrite(&pFlight->date, sizeof(Date), 1, pFile) != 1) return 0;
	return 1;
}

int readAirlineFromBFile(FILE* pFile, Airline* pComp, AirportManager* pManager)
{
	int len;

	if (fread(&len, sizeof(int), 1, pFile) != 1) return 0;
	pComp->name = (char*)malloc(len * sizeof(char));
	if (!pComp->name) return 0;
	if (fread(pComp->name, sizeof(char), len, pFile) != len) return 0;

	if (fread(&pComp->planeCount, sizeof(int), 1, pFile) != 1) return 0;
	pComp->planeArr = (Plane*)realloc(pComp->planeArr, (pComp->planeCount) * sizeof(Plane));
	if (!pComp->planeArr) return 0;
	if (fread(pComp->planeArr, sizeof(Plane), pComp->planeCount, pFile) != pComp->planeCount) return 0;

	if (fread(&pComp->flightCount, sizeof(int), 1, pFile) != 1) return 0;
	pComp->flightArr = (Flight**)realloc(pComp->flightArr, (pComp->flightCount) * sizeof(Flight*));
	if (!pComp->flightArr) return 0;
	readFlightArrFromBFile(pFile, pManager, pComp->flightArr, pComp->flightCount, pComp->planeArr, pComp->planeCount);

	return 1;
}

int readFlightArrFromBFile(FILE* pFile, AirportManager* pManager, Flight** pFlightArr, const int flightCount, Plane* planeArr, const int planeCount)
{
	Flight* pFlight = NULL;
	for (int i = 0; i < flightCount; i++)
	{
		pFlight = (Flight*)calloc(1, sizeof(Flight));
		if (!pFlight) return 0;
		if (!readFlightFromBFile(pFile, pManager, pFlight, planeArr, planeCount)) return 0;
		pFlightArr[i] = pFlight;
	}
	return 1;
}

int readFlightFromBFile(FILE* pFile, AirportManager* pManager, Flight* pFlight, Plane* planeArr, const int planeCount)
{
	int serialNumber;
	if (fread(pFlight->sourceCode, sizeof(char), IATA_LENGTH, pFile) != IATA_LENGTH) return 0;
	pFlight->sourceCode[IATA_LENGTH] = '\0';
	if (!findAirportByCode(pManager, pFlight->sourceCode)) return 0;

	if (fread(pFlight->destCode, sizeof(char), IATA_LENGTH, pFile) != IATA_LENGTH) return 0;
	pFlight->destCode[IATA_LENGTH] = '\0';
	if (!findAirportByCode(pManager, pFlight->destCode)) return 0;

	if (pFlight->sourceCode == pFlight->destCode) return 0;

	if (fread(&serialNumber, sizeof(int), 1, pFile) != 1) return 0;
	pFlight->flightPlane = *findPlaneBySN(planeArr, planeCount, serialNumber);

	if (fread(&pFlight->date, sizeof(Date), 1, pFile) != 1) return 0;

	return 1;
}