#include <iostream>
#include "Parameters.h"
#include <easy3d/util/initializer.h>
#include <easy3d/core/surface_mesh.h>
#include <easy3d/fileio/surface_mesh_io.h>
#include "Resources.h"
#include "HeatSim.h"
#include "RenderUtils.h"
#include "TransparencyViewer.h"
#include "SimUtils.h"

using namespace std;
using namespace easy3d;
using array_t = Model* (*) [XDIM][YDIM][ZDIM];


namespace mfresources {
    SurfaceMesh g_cube;
}

namespace mfsim {
    array_t g_heatSim;

}

int main() {
    // Setup easy3D
    easy3d::initialize();
    TransparencyViewer viewer("Heat Simulation");
    viewer.set_background_color(BACKGROUND_COLOR);
    // Load in cube resource
    if(!io::load_ply("../resources/cube.ply", &mfresources::g_cube)) {
        cout << "Failed to load model file" << endl;
        return EXIT_FAILURE;
    }

    // Initialize 3d array to represent space (temp)
    Model* (*heatSimRaw) = new Model*[XDIM*YDIM*ZDIM];
    mfsim::g_heatSim = reinterpret_cast<array_t>(heatSimRaw);
    clearArray(*mfsim::g_heatSim);
    initializeArray(&viewer, *mfsim::g_heatSim);

    // Allow users to enter heat data points
    enterDataPoints(*mfsim::g_heatSim);

    // Run easy3D (it will handle simulation with key events; see TransparencyViewer.cpp TransparencyViewer::key_press_event)
    return viewer.run();
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

void initializeArray(Viewer* viewer, Model* (&array) [XDIM][YDIM][ZDIM]) {
    for(int x = 0; x < XDIM; x++) {
    for(int y = 0; y < YDIM; y++) {
    for(int z = 0; z < ZDIM; z++) {
        add_sim_cube(viewer, x, y, z, array);
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

    delete point;
}