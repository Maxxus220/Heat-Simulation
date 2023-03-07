#include "TransparencyViewer.h"

using namespace easy3d;

TransparencyViewer::TransparencyViewer(const std::string& title) : Viewer(title) {
    transparency = new DualDepthPeeling(camera());
}

void TransparencyViewer::draw() const {

    if(!current_model()) return;

    // Build triangle list for drawing
    std::vector<TrianglesDrawable*> surfaces;
    for (auto m : models_) {
        SurfaceMesh* surfaceMesh = dynamic_cast<SurfaceMesh*>(m);
        for (auto d : m->renderer()->triangles_drawables()) {
            if (d->type() == Drawable::DT_TRIANGLES)
                    surfaces.push_back(dynamic_cast<TrianglesDrawable*>(d));
                    d->set_coloring_method(State::Method::UNIFORM_COLOR);
                    if(surfaceMesh) {
                        d->set_uniform_coloring(surfaceMesh->get_model_property<vec4>("Color")[0]);
                    }
                    else {
                        d->set_uniform_coloring(vec4(1, 1, 1, 1));
                    }
        }
    }

    transparency->draw(surfaces);
}

bool TransparencyViewer::key_press_event(int key, int modifiers) {
    if(key == GLFW_KEY_N) {
        // Next step in simulation
        update();
        return true;
    }
    else {
        return Viewer::key_press_event(key, modifiers);
    }
}

     