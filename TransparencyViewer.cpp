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
        for (auto d : m->renderer()->triangles_drawables()) {
            if (d->type() == Drawable::DT_TRIANGLES)
                    surfaces.push_back(dynamic_cast<TrianglesDrawable*>(d));
        }
    }

    transparency->draw(surfaces);
}
     