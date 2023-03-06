#include "Resources.h"
#include "RenderUtils.h"
#include "Parameters.h"

using namespace std;
using namespace easy3d;

void position_model(Model* model, int x, int y, int z);
void make_model_transparent(Model* model);

Model* add_cube(Viewer* viewer, int x, int y, int z) {
    SurfaceMesh* new_cube_mesh = new SurfaceMesh(mfresources::g_cube);

    Model* new_cube;

    if((new_cube = viewer->add_model(new_cube_mesh)) == nullptr) {
        cout << "Failed to add cube to viewer" << endl;
        return new_cube;
    }

    position_model(new_cube, x, y, z);


    make_model_transparent(new_cube);

    dynamic_cast<SurfaceMesh*>(new_cube)->add_model_property<vec4>("Color", DEFAULT_COLOR);
    

    return new_cube;
}

void position_model(Model* model, int x, int y, int z) {
    const int GRID_SIZE = 2;
    for(int i = 0; i < dynamic_cast<SurfaceMesh*>(model)->vertices_size(); i++) {
        model->points()[i].x += x * GRID_SIZE;
        model->points()[i].y += y * GRID_SIZE;
        model->points()[i].z += z * GRID_SIZE;
    }
}

void make_model_transparent(Model* model) {
    auto faces = model->renderer()->get_triangles_drawable("faces");
    if(faces) {
        faces->set_opacity(OPACITY); 
    }
}