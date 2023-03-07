#include <iostream>
#include "Parameters.h"
#include <easy3d/viewer/viewer.h>
#include <easy3d/util/initializer.h>
#include <easy3d/core/surface_mesh.h>
#include <easy3d/fileio/surface_mesh_io.h>
#include "Resources.h"
#include "HeatSim.h"
#include "RenderUtils.h"
#include "TransparencyViewer.h"
#include "SimUtils.h"

#define EZ3D

using namespace std;
using namespace easy3d;
using array_t = Model* (&) [XDIM][YDIM][ZDIM];


namespace mfresources {
    SurfaceMesh g_cube;
}

namespace mfsim {
    array_t heatSim;
}

int main() {
#ifndef EZ3D

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

    initialize();
    TransparencyViewer viewer("Test");

    // Load in cube resource
    if(!io::load_ply("../resources/cube.ply", &mfresources::g_cube)) {
        cout << "Failed to load model file" << endl;
        return EXIT_FAILURE;
    }

    if(!add_cube(&viewer, 0, 0, 1)) {
        return EXIT_FAILURE;
    }

    if(!add_cube(&viewer, 0, 0, 0)) {
        return EXIT_FAILURE;
    }

    viewer.set_background_color(BACKGROUND_COLOR);

    return viewer.run();
    
    return EXIT_SUCCESS;
}

void clearArray(Model* (&array) [XDIM][YDIM][ZDIM]) {
    #pragma omp parallel for
    for(int x = 0; x < XDIM; x++) {
    for(int y = 0; y < YDIM; y++) {
    for(int z = 0; z < ZDIM; z++) {
        array[x][y][z] = nullptr;
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

void enterDataPoints(Model* (&array) [XDIM][YDIM][ZDIM]) {
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

        if(checkCoordinates(point)) {
            set_heat(temperature, point[0], point[1], point[2], array);
        }
        else {
            cout << "Invalid coordinates, point not set" << endl;
        }
    }
}