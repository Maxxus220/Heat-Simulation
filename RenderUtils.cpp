#include "Resources.h"
#include "RenderUtils.h"

using namespace std;
using namespace easy3d;


Model* add_cube(Viewer* viewer, int x, int y, int z) {
    SurfaceMesh* new_cube_mesh = new SurfaceMesh(mfresources::g_cube);

    Model* new_cube;

    if((new_cube = viewer->add_model(new_cube_mesh)) == nullptr) {
        cout << "Failed to add cube to viewer" << endl;
        return new_cube;
    }

    // Add x,y,z to each vertice
    const int GRID_SIZE = 2;
    for(int i = 0; i < dynamic_cast<SurfaceMesh*>(new_cube)->vertices_size(); i++) {
        new_cube->points()[i].x += x * GRID_SIZE;
        new_cube->points()[i].y += y * GRID_SIZE;
        new_cube->points()[i].z += z * GRID_SIZE;
    }

    return new_cube;
}