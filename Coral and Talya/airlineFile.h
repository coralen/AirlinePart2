#ifndef __BIN_FILES__
#define __BIN_FILES__

#include "Airline.h"

int writeAirlineToBFile(FILE* pFile, const Airline* pComp);
int writeFlightArrToBFile(FILE* pFile, Flight** const flightArr, const int count);
int writeFlightToBFile(FILE* pFile, const Flight* pFlight);
int readAirlineFromBFile(FILE* pFile, Airline* pComp, AirportManager* pManager);
int readFlightArrFromBFile(FILE* pFile, AirportManager* pManager, Flight** pFlightArr, const int flightCount, Plane* planeArr, const int planeCount);
int readFlightFromBFile(FILE* pFile, AirportManager* pManager, Flight* pFlight, Plane* planeArr, const int planeCount);

#endif