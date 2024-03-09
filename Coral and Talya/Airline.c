#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Airline.h"
#include "Airport.h"
#include "General.h"
#include "airlineFile.h"

void initAirline(Airline* pComp)
{
	//printf("-----------  Init Airline\n");
	pComp->name = getStrExactName("Enter Airline name");
	setDefaults(pComp);
}

void setDefaults(Airline* pComp)
{
	pComp->flightArr = NULL;
	pComp->flightCount = 0;
	pComp->planeArr = NULL;
	pComp->planeCount = 0;
	pComp->sortField = eNone;
}

int initAirlineFromFile(Airline* pComp, AirportManager* pManager, const char* fileName)
{
	setDefaults(pComp);
	if (!readAirlineFromFile(pComp, pManager, fileName)) return 0;
	return 1;
}


int saveAirlineToFile(const Airline* pComp, const char* fileName)
{
	FILE* pFile = NULL;

	if (!(pFile = fopen(fileName, "wb"))) return 0;
	if (!writeAirlineToBFile(pFile, pComp))
	{
		fclose(pFile);
		return 0;
	}
	fclose(pFile);
	return 1;
}

int	addFlight(Airline* pComp, AirportManager* pManager)
{
	if (countAirportsInList(&pManager->airportsList.head) < 2)
	{
		printf("There are not enough airport to set a flight\n");
		return 0;
	}
	if (pComp->planeCount == 0)
	{
		printf("There is no plane in company\n");
		return 0;
	}

	Flight* pFlight = NULL;
	if (!(pFlight = (Flight*)calloc(1, sizeof(Flight)))) return 0;
	Plane* thePlane = FindAPlane(pComp);
	printAirports(pManager);
	initFlight(pFlight, thePlane, pManager);

	pComp->flightArr = (Flight**)realloc(pComp->flightArr, (pComp->flightCount + 1) * sizeof(Flight*));
	if (!pComp->flightArr)
	{
		free(pFlight);
		return 0;
	}
	pComp->flightArr[pComp->flightCount] = pFlight;
	pComp->flightCount++;
	return 1;
}

int addPlane(Airline* pComp)
{
	pComp->planeArr = (Plane*)realloc(pComp->planeArr, (pComp->planeCount + 1) * sizeof(Plane));
	if (!pComp->planeArr) return 0;
	initPlane(&pComp->planeArr[pComp->planeCount], pComp->planeArr, pComp->planeCount);
	pComp->planeCount++;
	return 1;
}

Plane* FindAPlane(Airline* pComp)
{
	printf("Choose a plane from list, type its serial Number\n");
	printPlanesArr(pComp->planeArr, pComp->planeCount);
	int sn;
	Plane* temp = NULL;
	do {
		scanf("%d", &sn);
		temp = findPlaneBySN(pComp->planeArr, pComp->planeCount, sn);
		if (!temp)
			printf("No plane with that serial number! Try again!\n");
	} while (temp == NULL);

	return temp;
}

void sortFlight(Airline* pComp)
{
	int option;
	printf("\n\n");
	printf("Base on what field do you want to sort?\n");
	do {
		for (int i = 0; i < NUM_OF_SORT_TYPES; i++)
			printf("Enter %d for %s\n", i + 1, sortFields[i]);
		scanf("%d", &option);
	} while (option < 1 || option > NUM_OF_SORT_TYPES);

	pComp->sortField = (eSort)option;

	switch (pComp->sortField)
	{
	case eSourceCode:
		qsort(pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareBySourceCode);
		break;

	case eDestCode:
		qsort(pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareByDestCode);
		break;

	case eDate:
		qsort(pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareByDate);
		break;
	}

}

void findFlight(const Airline* pComp)
{
	if (pComp->sortField == eNone)
	{
		printf("The search cannot be performed, array not sorted\n");
		return;
	}

	Flight** found = NULL;
	Flight tmpFlight;
	Flight* pTmpFlight = &tmpFlight;

	switch (pComp->sortField)
	{
	case eSourceCode:
		printf("Origin: \n");
		getAirportCode(tmpFlight.sourceCode);
		found = bsearch(&pTmpFlight, pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareBySourceCode);
		break;

	case eDestCode:
		printf("Destination: \n");
		getAirportCode(tmpFlight.destCode);
		found = bsearch(&pTmpFlight, pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareByDestCode);
		break;

	case eDate:
		getCorrectDate(&tmpFlight.date);
		found = bsearch(&pTmpFlight, pComp->flightArr, pComp->flightCount, sizeof(Flight*), compareByDate);
		break;
	}

	if (found)
	{
		printf("Flight found, ");
		printFlight(*found);
		printf("\n");
	}
	else printf("Flight was not found\n");
}

int readAirlineFromFile(Airline* pComp, AirportManager* pManager, const char* fileName)
{
	FILE* pFile = fopen(fileName, "rb");
	if (!pFile) return 0;
	if (!readAirlineFromBFile(pFile, pComp, pManager))
	{
		fclose(pFile);
		return 0;
	}
	fclose(pFile);
	return 1;
}

void printCompany(const Airline* pComp)
{
	printf("Airline %s\n", pComp->name);
	printf("\n -------- Has %d planes\n", pComp->planeCount);
	printPlanesArr(pComp->planeArr, pComp->planeCount);
	printf("\n\n -------- Has %d flights\n", pComp->flightCount);
	printFlightArr(pComp->flightArr, pComp->flightCount);
}

void	printFlightArr(Flight** const flightArr, int size)
{
	generalArrayFunction(flightArr, size, sizeof(Flight*), printFlightWrapper);
}

void printFlightWrapper(void* pFlightPtr)
{
	Flight* pFlight = *((Flight**)pFlightPtr); 
	printFlight(pFlight);
}


void	printPlanesArr(Plane* arr, int size)
{
	generalArrayFunction(arr, size, sizeof(Plane), printPlaneWrapper);
}

void printPlaneWrapper(void* pPlane)
{
	printPlane((const Plane*)pPlane);
}

void	doPrintFlightsWithPlaneType(const Airline* pComp)
{
	ePlaneType type = getPlaneType();
	int count = 0;
	printf("Flights with plane type %s:\n", GetPlaneTypeStr(type));
	for (int i = 0; i < pComp->flightCount; i++)
	{
		if (isPlaneTypeInFlight(pComp->flightArr[i], type))
		{
			printFlight(pComp->flightArr[i]);
			count++;
		}
	}
	if (count == 0)
		printf("Sorry - could not find a flight with plane type %s:\n", GetPlaneTypeStr(type));
	printf("\n");
}

void	freeFlightArr(Flight** const flightArr, int size) 
{
	if (flightArr == NULL) return;
	generalArrayFunction(flightArr, size, sizeof(Flight*), freeFlightWrapper); 
}

void freeFlightWrapper(void* pFlight)
{
	Flight* flight = *(Flight**)pFlight;
	free(flight);
}

void	freePlanes(Plane* arr, int size)
{
	for (int i = 0; i < size; i++)
		freePlane(&arr[i]);
}

void	freeCompany(Airline* pComp)
{
	freeFlightArr(pComp->flightArr, pComp->flightCount);
	free(pComp->flightArr);
	free(pComp->planeArr);
	free(pComp->name);
}
