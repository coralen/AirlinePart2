#ifndef __AIR_MANAGER__
#define __AIR_MANAGER__

#include "include/Airport.h"
#include "include/list.h"
#include "def.h"

typedef struct
{
	LIST	airportsList;
//	int			airportsCount;
}AirportManager;

int		initManager(AirportManager* pManager);
int countAirportsInList(NODE* pNode);
int		addAirport(AirportManager* pManager);
int		initAirport(Airport* pPort, AirportManager* pManager);
Airport* findAirportByCode(const AirportManager* pManager, const char* code);
int		checkUniqeCode(const char* code, const AirportManager* pManager);
void	printAirports(const AirportManager* pManager);
void	freeManager(AirportManager* pManager);
void	freeAirportList(AirportManager* pManager);
BOOL compareCodes(const char* code1,const char* code2);
NODE* findCorrectPlaceForAirport(NODE* pNode, Airport* pPort);
#endif