#ifndef __BIN_FILES__
#define __BIN_FILES__

#include "Airline.h"

int writeAirlineToBFile(FILE* pFile, const Airline* pComp);
int writePlaneArrToBFile(FILE* pFile, const Plane* pPlaneArr, const int count);
int writePlaneToBFile(FILE* pFile, const Plane* pPlane);
int writeFlightArrToBFile(FILE* pFile, Flight** const flightArr, const int count);
int writeFlightToBFile(FILE* pFile, const Flight* pFlight);
int readAirlineFromBFile(FILE* pFile, Airline* pComp, AirportManager* pManager);
int readPlaneArrFromBFile(FILE* pFile, Plane* pPlaneArr, const int planeCount);
int readPlaneFromBFile(FILE* pFile, Plane* pPlane);
int readFlightArrFromBFile(FILE* pFile, Flight** pFlightArr, const int flightCount, Plane* pPlaneArr, const int planeCount);
int readFlightFromBFile(FILE* pFile, Flight* pFlight, Plane* pPlaneArr, const int planeCount);

#endif