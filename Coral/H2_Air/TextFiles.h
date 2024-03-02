#ifndef __TEXT_FILES__
#define __TEXT_FILES__

#include "AirportManager.h"

int writeAirportManagerToTextFile(FILE* pFile, AirportManager* pManager);
int writeAirportToTextFile(FILE* pFile, Airport* pAirport);
int readAirportManagerFromTextFile(FILE* pFile, AirportManager* pManager);
int readAirportFromTextFile(FILE* pFile, Airport** pAirport);

#endif