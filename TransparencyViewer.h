#pragma once

#include <easy3d/viewer/viewer.h>
#include <easy3d/renderer/dual_depth_peeling.h>
#include <easy3d/renderer/drawable_triangles.h>
#include <easy3d/renderer/renderer.h>
#include <easy3d/renderer/camera.h>
#include <easy3d/core/model.h>
#include <easy3d/renderer/state.h>


class TransparencyViewer : public easy3d::Viewer
{
public:
    TransparencyViewer(const std::string& title = "");
 
protected:
 
    void draw() const override;
  
private:
    easy3d::Transparency* transparency;
};