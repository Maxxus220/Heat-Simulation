#include "Parameters.h"
#include "SimUtils.h"
#include "RenderUtils.h"
#include <easy3d/renderer/drawable_triangles.h>
#include <easy3d/renderer/renderer.h>
#include <easy3d/core/surface_mesh.h>

using namespace easy3d;
using namespace std;

Model* add_sim_cube(Viewer* viewer, int x, int y, int z, Model* (&grid) [XDIM][YDIM][ZDIM]) {

    Model* new_cube;

    if((new_cube = add_cube(viewer, x, y, z)) == nullptr) {
        return new_cube;
    }

    grid[x][y][z] = new_cube;
    return new_cube;
}

void set_heat(float heat, int x, int y, int z, Model* (&grid) [XDIM][YDIM][ZDIM]) {
    SurfaceMesh* cube = dynamic_cast<SurfaceMesh*>(grid[x][y][z]);

    cube->remove_model_property("Color");
    cube->add_model_property<vec4>("Color", vec4(convert_heat_to_red(heat), 0, 0, 1));
}

float get_heat(int x, int y, int z, Model* (&grid) [XDIM][YDIM][ZDIM]) {
    SurfaceMesh* cube = dynamic_cast<SurfaceMesh*>(grid[x][y][z]);
    
    return convert_red_to_heat(cube->get_model_property<vec4>("Color")[0].r);
}

float convert_red_to_heat(float red) {
    // return ((red-0.1f) / 0.9f) * 100;
    return red * 100;
}

float convert_heat_to_red(float heat) {
    // return ((heat / 100) * 0.9f) + 0.1f;
    return heat / 100;
}
