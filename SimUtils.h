#pragma once

#include <easy3d/core/model.h>

easy3d::Model* add_sim_cube(easy3d::Viewer* viewer, int x, int y, int z, easy3d::Model* (&grid) [XDIM][YDIM][ZDIM]);
void set_heat(float heat, int x, int y, int z, easy3d::Model* (&grid) [XDIM][YDIM][ZDIM]);
float get_heat(int x, int y, int z, easy3d::Model* (&grid) [XDIM][YDIM][ZDIM]);
float convert_red_to_heat(float red);
float convert_heat_to_red(float heat);
