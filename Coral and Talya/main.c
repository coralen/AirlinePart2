#include <stdio.h>
#include <stdlib.h>

#include "Airline.h"
#include "AirportManager.h"
#include "General.h"
#include "airlineFile.h"


#define MANAGER_FILE_NAME "airport_authority.txt"
#define AIRLINE_FILE_NAME "airline.bin"

#define EXIT			-1

typedef enum
{
	eAddAirport, eAddPlane, eAddFlight, ePrintCompany, ePrintAirports,
	ePrintFlightsPlaneType, eSortFlight, eFindFlight, eNofOptions
} eMenuOptions;

const char* str[eNofOptions] = { "Add Airport","Add Plane","Add Flight",
								"Print Airline", "Print all Airports",
								"Print all flights with plane type",
								"Sort Flight", "Find Flight" };



int menu();
int initManagerAndAirline(AirportManager* pManager, Airline* pCompany);

int main()
{
	AirportManager	manager;
	Airline			company;

	initManagerAndAirline(&manager, &company);

	int option;
	int stop = 0;


	do
	{
		option = menu();
		switch (option)
		{
		case eAddPlane:
			if (!addPlane(&company))
				printf("Error adding plane\n");
			break;

		case eAddAirport:
			if (!addAirport(&manager))
				printf("Error adding airport\n");
			break;

		case eAddFlight:
			if (!addFlight(&company, &manager))
				printf("Error adding flight\n");
			break;

		case ePrintCompany:
			printCompany(&company);
			break;

		case ePrintAirports:
			printAirports(&manager);
			break;

		case ePrintFlightsPlaneType:
			doPrintFlightsWithPlaneType(&company);
			break;

		case eSortFlight:
			sortFlight(&company);
			break;

		case eFindFlight:
			findFlight(&company);
			break;

		case EXIT:
			saveAirlineToFile(&company, AIRLINE_FILE_NAME);
			saveManagerToFile(&manager, MANAGER_FILE_NAME);
			printf("Bye bye\n");
			stop = 1;
			break;

		default:
			printf("Wrong option\n");
			break;
		}
	} while (!stop);

	freeManager(&manager);
	freeCompany(&company);

	return 1;
}

int menu()
{
	int option;
	printf("\n\n");
	printf("Please choose one of the following options\n");
	for (int i = 0; i < eNofOptions; i++)
		printf("%d - %s\n", i, str[i]);
	printf("%d - Quit\n", EXIT);
	scanf("%d", &option);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	return option;
}

int initManagerAndAirline(AirportManager* pManager, Airline* pCompany)
{
	if (!initManager(pManager, MANAGER_FILE_NAME)) return 0;
	if (!initAirlineFromFile(pCompany, pManager, AIRLINE_FILE_NAME)) initAirline(pCompany);
	return 1;
}