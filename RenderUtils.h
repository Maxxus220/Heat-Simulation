#pragma once

#include <easy3d/viewer/viewer.h>
#include <easy3d/core/model.h>
#include <easy3d/renderer/state.h>

easy3d::Model* add_cube(easy3d::Viewer* viewer, int x, int y, int z);
void set_model_coloring_method(easy3d::Model* model, easy3d::State::Method method);
void set_model_uniform_color(easy3d::Model* model, easy3d::vec4 color);
easy3d::vec4 get_model_uniform_color(easy3d::Model* model);