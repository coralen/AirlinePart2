#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "BinaryFiles.h"


int writeAirlineToBFile(FILE* pFile, Airline* pComp)
{
	int len = strlen(pComp->name) + 1;
	if (fwrite(&len, sizeof(int), 1, pFile) != 1) return 0;
	if (fwrite(pComp->name, sizeof(char), len, pFile) != len) return 0;
	if (fwrite(&pComp->planeCount, sizeof(int), 1, pFile) != 1) return 0;
	if (!writePlaneArrToBFile(pFile, pComp->planeArr, pComp->planeCount)) return 0;
	if (fwrite(&pComp->flightCount, sizeof(int), 1, pFile) != 1) return 0;
	if (!writeFlightArrToBFile(pFile, pComp->flightArr, pComp->flightCount)) return 0;
	return 1;
}

int writePlaneArrToBFile(FILE* pFile, Plane* pPlaneArr, int count)
{
	for (int i = 0; i < count; i++)
	{
		if (!writePlaneToBFile(pFile, &pPlaneArr[i]))
		{
			fclose(pFile);
			return 0;
		}
	}
	return 1;
}

int writePlaneToBFile(FILE* pFile, Plane* pPlane)
{
	if (fwrite(&pPlane->serialNum, sizeof(int), 1, pFile) != 1) return 0;
	if (fwrite(&pPlane->type, sizeof(ePlaneType), 1, pFile) != 1) return 0;
	return 1;
}

int writeFlightArrToBFile(FILE* pFile, Flight** pFlightArr, int count)
{
	for (int i = 0; i < count; i++)
	{
		if (!writeFlightToBFile(pFile, pFlightArr[i]))
		{
			fclose(pFile);
			return 0;
		}
	}
	return 1;
}

int writeFlightToBFile(FILE* pFile, Flight* pFlight)
{
	int len = strlen(pFlight->sourceCode); // for both source and dest codes
	
	if (fwrite(&len, sizeof(int), 1, pFile) != 1) return 0;
	if (fwrite(pFlight->sourceCode, sizeof(char), len, pFile) != len) return 0;

	if (fwrite(&len, sizeof(int), 1, pFile) != 1) return 0;
	if (fwrite(pFlight->destCode, sizeof(char), len, pFile) != len) return 0;

	if (fwrite(&pFlight->flightPlane.serialNum, sizeof(int), 1, pFile) != 1) return 0; 
	if (fwrite(&pFlight->date, sizeof(Date), 1, pFile) != 1) return 0;
	return 1;
}

int readAirlineFromBFile(FILE* pFile, Airline* pComp)
{
	int len;

	if (fread(&len, sizeof(int), 1, pFile) != 1) return 0;
	pComp->name = (char*)malloc(len * sizeof(char));
	if (!pComp->name) return 0;
	if (fread(pComp->name, sizeof(char), len, pFile) != len) return 0;

	if (fread(&pComp->planeCount, sizeof(int), 1, pFile) != 1) return 0;
	pComp->planeArr = (Plane*)realloc(pComp->planeArr, (pComp->planeCount) * sizeof(Plane));
	if (!pComp->planeArr) return 0;
	readPlaneArrFromBFile(pFile, pComp->planeArr, pComp->planeCount);

	if (fread(&pComp->flightCount, sizeof(int), 1, pFile) != 1) return 0;
	pComp->flightArr = (Flight**)realloc(pComp->flightArr, (pComp->flightCount) * sizeof(Flight*));
	if (!pComp->flightArr) return 0;
	readFlightArrFromBFile(pFile, pComp->flightArr, pComp->flightCount, pComp->planeArr, pComp->planeCount);

	return 1;
}

int readPlaneArrFromBFile(FILE* pFile, Plane* planeArr, const int planeCount)
{
	Plane* pPlane = NULL;
	for (int i = 0; i < planeCount; i++)
	{
		pPlane = (Plane*)calloc(1, sizeof(Plane));
		if (!pPlane) return 0;
		if (!readPlaneFromBFile(pFile, pPlane)) return 0;
		planeArr[i] = *pPlane;
	}
	return 1;
}

int readPlaneFromBFile(FILE* pFile, Plane* pPlane)
{
	if (fread(&pPlane->serialNum, sizeof(int), 1, pFile) != 1) return 0;
	if (fread(&pPlane->type, sizeof(ePlaneType), 1, pFile) != 1) return 0;
	return 1;
}

int readFlightArrFromBFile(FILE* pFile, Flight** pFlightArr, const int flightCount, Plane* planeArr, const int planeCount)
{
	Flight* pFlight = NULL;
	for (int i = 0; i < flightCount; i++)
	{
		pFlight = (Flight*)calloc(1, sizeof(Flight));
		if (!pFlight) return 0;
		if (!readFlightFromBFile(pFile, pFlight, planeArr, planeCount)) return 0;
		pFlightArr[i] = pFlight;
	}
	return 1;
}

int readFlightFromBFile(FILE* pFile, Flight* pFlight, Plane* planeArr, const int planeCount)
{
	int len, serialNumber;
	if (fread(&len, sizeof(int), 1, pFile) != 1) return 0;
	if (fread(pFlight->sourceCode, sizeof(char), len, pFile) != len) return 0;
	pFlight->sourceCode[len] = '\0';

	if (fread(&len, sizeof(int), 1, pFile) != 1) return 0;
	if (fread(pFlight->destCode, sizeof(char), len, pFile) != len) return 0;
	pFlight->destCode[len] = '\0';

	if (fread(&serialNumber, sizeof(int), 1, pFile) != 1) return 0;
	pFlight->flightPlane = *findPlaneBySN(planeArr, planeCount, serialNumber);

	if (fread(&pFlight->date, sizeof(Date), 1, pFile) != 1) return 0;
	return 1;
}