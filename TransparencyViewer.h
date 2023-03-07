#pragma once

#include <easy3d/viewer/viewer.h>
#include <easy3d/renderer/dual_depth_peeling.h>

class TransparencyViewer : public easy3d::Viewer
{
public:
    TransparencyViewer(const std::string& title = "");
 
protected:
 
    void draw() const override;
    bool key_press_event(int key, int modifiers) override;
  
private:
    easy3d::Transparency* transparency;
};