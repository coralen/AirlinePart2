#ifndef __BIN_FILES__
#define __BIN_FILES__

#include "Airline.h"

int writeAirlineToBFile(FILE* pFile, Airline* pComp);
int writePlaneArrToBFile(FILE* pFile, Plane* pPlaneArr, int count);
int writePlaneToBFile(FILE* pFile, Plane* pPlane);
int writeFlightArrToBFile(FILE* pFile, Flight** pFlightArr, int count);
int writeFlightToBFile(FILE* pFile, Flight* pFlight);
int readAirlineFromBFile(FILE* pFile, Airline* pComp);
int readPlaneArrFromBFile(FILE* pFile, Plane* pPlaneArr, const int planeCount);
int readPlaneFromBFile(FILE* pFile, Plane* pPlane);
int readFlightArrFromBFile(FILE* pFile, Flight** pFlightArr, const int flightCount, Plane* pPlaneArr, const int planeCount);
int readFlightFromBFile(FILE* pFile, Flight* pFlight, Plane* pPlaneArr, const int planeCount);

#endif