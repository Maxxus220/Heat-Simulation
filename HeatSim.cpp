#include <iostream>
#include "Parameters.h"
#include "bgfx.h"
#include "HeatSim.h"

#define BGFX

using namespace std;

int main() {
#ifndef BGFX
    using array_t = float (&) [XDIM][YDIM][ZDIM];

    // Initialize 3d array to represent space (temp)
    float * tempsBeforeRaw = new float[XDIM*YDIM*ZDIM];
    float * tempsAfterRaw = new float[XDIM*YDIM*ZDIM];
    array_t tempsBefore = reinterpret_cast<array_t>(tempsBeforeRaw);
    array_t tempsAfter = reinterpret_cast<array_t>(tempsAfterRaw);
    clearArray(tempsBefore);
    clearArray(tempsAfter);

    // Allow users to enter heat data points
    enterDataPoints(tempsBefore);

    // Start simulation steps

    // Calculate density at each point

    // Spread heat proportionally (by difference) across neighbours

    // Save "frame" of spread or render or both

    // Check if max transfer was below simulation end threshold
    // If so end simulation

    // Repeat up to start simulation steps

    // Allow for looking at history of simulation and playback
#endif

    bgfx::init();

    return 0;
}

void clearArray(float (&array) [XDIM][YDIM][ZDIM]) {
    #pragma omp parallel for
    for(int x = 0; x < XDIM; x++) {
    for(int y = 0; y < YDIM; y++) {
    for(int z = 0; z < ZDIM; z++) {
        array[x][y][z] = 0;
    }
    }
    }
}

bool checkCoordinates(int* point3D) {
    return checkSingleCoordinate(point3D[0], XDIM) && 
            checkSingleCoordinate(point3D[1], YDIM) && 
            checkSingleCoordinate(point3D[2], ZDIM);
}

bool checkSingleCoordinate(int coord, int dimSize) {
    return coord >= 0 && coord < dimSize;
}

void enterDataPoints(float (&array) [XDIM][YDIM][ZDIM]) {
    int* point = new int[3];
    point[0] = 0;
    point[1] = 0;
    point[2] = 0;

    float temperature;

    while(!(point[0] == -1 || point[1] == -1 || point[2] == -1)) {
        cout << "Enter a 3d point (-1 to quit):" << std::endl;
        cout << "X Coordinate: ";
        cin >> point[0];
        if(point[0] == -1) break;

        cout << "Y Coordinate: ";
        cin >> point[1];
        if(point[1] == -1) break;

        cout << "Z Coordinate: ";
        cin >> point[2];
        if(point[2] == -1) break;

        cout << "Temperature: ";
        cin >> temperature;

        if(checkCoordinates(point)) array[point[0]][point[1]][point[2]] = temperature;
    }
}