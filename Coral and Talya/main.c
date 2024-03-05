#include <stdio.h>
#include <stdlib.h>
#include "Airline.h"
#include "AirportManager.h"
#include "General.h"
#include "airlineFile.h"



#define MANAGER_FILE_NAME_SRC "airport_authority.txt"
#define AIRLINE_FILE_NAME_SRC "airline.bin"

#define MANAGER_FILE_NAME_DST "airport_authority_out.txt"
#define AIRLINE_FILE_NAME_DST "airline_out.bin"


int initManagerAndAirline(AirportManager* pManager, Airline* pCompany);


int main()
{

	AirportManager	manager;
	Airline			company;



	int opt, res;
	printf("Please choose one of the following options\n");
	printf("1 - Print Airports\n");
	printf("2 - Print Airline\n");
	printf("3 - Add Airport Save\n");
	printf("4 - Add Flight Save\n");
	printf("5 - Add Plane Save\n");
	printf("6 - Sort\n");
	printf("7 - Find\n");
	scanf("%d", &opt);

	switch (opt)
	{
	case 1:
		res = initManager(&manager, MANAGER_FILE_NAME_SRC);
		if (!res)
		{
			printf("error init manager\n");
			return 0;
		}
		printAirports(&manager);
		printf("\n");
		freeManager(&manager);
		break;

	case 2:
		res = initManager(&manager, MANAGER_FILE_NAME_SRC);
		if (!res)
		{
			printf("error init manager\n");
			return 0;
		}

		initAirlineFromFile(&company, &manager, AIRLINE_FILE_NAME_SRC);
		//initAirline(&company);
		//addPlane(&company);
		//addFlight(&company, &manager);
		//saveAirlineToFile(&company, AIRLINE_FILE_NAME_SRC);
		printCompany(&company);
		printf("\n");
		freeManager(&manager);
		freeCompany(&company);

		getchar();
		getchar();
		break;

	case 3:
		res = initManager(&manager, MANAGER_FILE_NAME_SRC);
		if (!res)
		{
			printf("error init manager\n");
			return 0;
		}
		addAirport(&manager);
		printAirports(&manager);
		printf("\n");
		saveManagerToFile(&manager, MANAGER_FILE_NAME_DST);
		freeManager(&manager);
		initManager(&manager, MANAGER_FILE_NAME_DST);
		printAirports(&manager);
		printf("\n");
		freeManager(&manager);
		break;


	case 4:
		if (!initManagerAndAirline(&manager, &company))
		{
			printf("error init");
			return 0;
		}
		addFlight(&company, &manager);
		printf("\n");
		printFlightArr(company.flightArr, company.flightCount);
		printf("\n");
		saveAirlineToFile(&company, AIRLINE_FILE_NAME_DST);
		freeCompany(&company);
		initAirlineFromFile(&company, &manager, AIRLINE_FILE_NAME_DST);
		printf("\n");
		printFlightArr(company.flightArr, company.flightCount);
		printf("\n");
		freeManager(&manager);
		freeCompany(&company);

		getchar();
		getchar();
		break;

	case 5:
		if (!initManagerAndAirline(&manager, &company))
		{
			printf("error init");
			return 0;
		}
		addPlane(&company);
		printPlanesArr(company.planeArr, company.planeCount);
		printf("\n");
		saveAirlineToFile(&company, AIRLINE_FILE_NAME_DST);
		freeCompany(&company);
		freeManager(&manager);
		initManager(&manager, MANAGER_FILE_NAME_DST);
		initAirlineFromFile(&company, &manager, AIRLINE_FILE_NAME_DST);
		printPlanesArr(company.planeArr, company.planeCount);
		printf("\n");
		freeManager(&manager);
		freeCompany(&company);


		getchar();
		getchar();
		break;

	case 6:
		if (!initManagerAndAirline(&manager, &company))
		{
			printf("error init");
			return 0;
		}
		sortFlight(&company);
		printf("\n");
		printCompany(&company);
		freeManager(&manager);
		freeCompany(&company);
		break;

	case 7:
		if (!initManagerAndAirline(&manager, &company))
		{
			printf("error init");
			return 0;
		}
		findFlight(&company);
		sortFlight(&company);
		printf("\n");
		printCompany(&company);
		printf("\n");
		findFlight(&company);
		printf("\n");
		freeManager(&manager);
		freeCompany(&company);
		break;

	}


	return 1;
}


int initManagerAndAirline(AirportManager* pManager, Airline* pCompany)
{
	if (!initManager(pManager, MANAGER_FILE_NAME_SRC)) return 0;
	if (!initAirlineFromFile(pCompany, pManager, AIRLINE_FILE_NAME_SRC)) initAirline(pCompany);
	return 1;
}