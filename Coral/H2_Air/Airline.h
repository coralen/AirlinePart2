#ifndef __COMP__
#define __COMP__

#include "Flight.h"
#include "AirportManager.h"

#define NUM_OF_SORT_TYPES 3 // coral added

// Coral added
typedef enum {
	eNone, eSourceCode, eDestCode, eDate
} eSort;

// Coral added
static const char* sortFields[NUM_OF_SORT_TYPES] = { "Source Code", "Dest Code", "Date" };

typedef struct
{
	char*		name;
	int			flightCount;
	Flight**	flightArr;
	int			planeCount;
	Plane*		planeArr;
	eSort		sortField; // Coral added
}Airline;

void	initAirline(Airline* pComp);
int		initAirlineFromFile(Airline* pComp, AirportManager* pManager, const char* fileName);
int		addFlight(Airline* pComp,const AirportManager* pManager);
int		addPlane(Airline* pComp);
int		saveAirlineToFile(const Airline* pComp, const char* fileName);
int		readAirlineFromFile(Airline* pComp, AirportManager* pManager, const char* fileName);
Plane*	FindAPlane(Airline* pComp);
void	printCompany(const Airline* pComp);
void	printFlightArr(Flight** arr, int size);
void	printPlanesArr(Plane* arr,int size);
void	doPrintFlightsWithPlaneType(const Airline* pComp);
void	freeFlightArr(Flight** arr, int size);
void	freePlanes(Plane* arr, int size);
void	freeCompany(Airline* pComp);
void	sortAirline(Airline* pComp);
void	FindAFlightInSorted(const Airline* pComp);

#endif

