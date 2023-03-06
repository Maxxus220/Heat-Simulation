#include "RenderUtils.h"

extern SurfaceMesh mfresources::cube;


Model* add_cube(Viewer* viewer, int x, int y, int z) {
    Model* new_cube;

    if((new_cube = viewer->add_model(&mfresources::cube)) == nullptr) {
        cout << "Failed to add cube to viewer" << endl;
        return new_cube;
    }

    // Add x,y,z to each vertice
    for(int i = 0; i < new_cube->vertices_size(); i++) {
        new_cube->points()[i].x += x;
        new_cube->points()[i].y += y;
        new_cube->points()[i].z += z;
    }

    return new_cube;
}