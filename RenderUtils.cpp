#include <easy3d/core/surface_mesh.h>
#include <easy3d/renderer/drawable_triangles.h>
#include <easy3d/renderer/renderer.h>
#include <easy3d/renderer/state.h>
#include "Resources.h"
#include "RenderUtils.h"
#include "Parameters.h"

using namespace std;
using namespace easy3d;

void position_model(Model* model, int x, int y, int z);
void make_model_transparent(Model* model);
void enable_flat_lighting(Model* model);

Model* add_cube(Viewer* viewer, int x, int y, int z) {
    SurfaceMesh* new_cube_mesh = new SurfaceMesh(mfresources::g_cube);

    Model* new_cube;

    if((new_cube = viewer->add_model(new_cube_mesh)) == nullptr) {
        cout << "Failed to add cube to viewer" << endl;
        return new_cube;
    }

    position_model(new_cube, x, y, z);

    make_model_transparent(new_cube);

    enable_flat_lighting(new_cube);

    set_model_coloring_method(new_cube, State::Method::UNIFORM_COLOR);
    set_model_uniform_color(new_cube, DEFAULT_COLOR);
    
    return new_cube;
}

void set_model_coloring_method(Model* model, State::Method method) {
    for(auto drawable : model->renderer()->triangles_drawables()) {
        if (drawable->type() == Drawable::DT_TRIANGLES) {
            drawable->set_coloring_method(method);
        }
    }
}

void set_model_uniform_color(Model* model, vec4 color) {
    for(auto drawable : model->renderer()->triangles_drawables()) {
        if (drawable->type() == Drawable::DT_TRIANGLES) {
            drawable->set_color(color);
        }
    }
}

vec4 get_model_uniform_color(Model* model) {
    for(auto drawable : model->renderer()->triangles_drawables()) {
        if (drawable->type() == Drawable::DT_TRIANGLES) {
            return drawable->color();
        }
    }
    return vec4(-1,-1,-1,-1);
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

void enable_flat_lighting(Model* model) {
    for(auto drawable : model->renderer()->triangles_drawables()) {
        State::Material mat = drawable->material();
        mat.shininess = 0.5f;
        drawable->set_material(mat);
    }
}