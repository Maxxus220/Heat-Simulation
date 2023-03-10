#include <easy3d/renderer/drawable_triangles.h>
#include <easy3d/renderer/renderer.h>
#include <easy3d/renderer/camera.h>
#include <easy3d/core/model.h>
#include <easy3d/renderer/state.h>
#include <easy3d/renderer/average_color_blending.h>
#include <3rd_party/glfw/include/GLFW/glfw3.h>
#include "Parameters.h"
#include "SimAlgos.h"
#include "TransparencyViewer.h"

using namespace easy3d;

using array_t = Model* (*) [XDIM][YDIM][ZDIM];

namespace mfsim {
    extern array_t g_heatSim;
}

TransparencyViewer::TransparencyViewer(const std::string& title) : Viewer(title) {
    transparency = new AverageColorBlending(camera());
}

void TransparencyViewer::draw() const {

    if(!current_model()) return;

    // Build triangle list for drawing
    std::vector<TrianglesDrawable*> surfaces;
    for (auto model : models_) {
        for (auto drawable : model->renderer()->triangles_drawables()) {
            if (drawable->type() == Drawable::DT_TRIANGLES)
                    surfaces.push_back(dynamic_cast<TrianglesDrawable*>(drawable));
        }
    }

    transparency->draw(surfaces);
}

bool TransparencyViewer::key_press_event(int key, int modifiers) {
    if(key == GLFW_KEY_N) {
        // Next step in simulation
        avgNeighbours(*mfsim::g_heatSim);
        update();
        return true;
    }
    else {
        return Viewer::key_press_event(key, modifiers);
    }
}

     