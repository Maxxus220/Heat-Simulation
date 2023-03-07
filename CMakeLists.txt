cmake_minimum_required(VERSION 3.22.1)
project(HeatSim)

set(Easy3D_DIR ./gfx/Easy3D/Release/)
set(CMAKE_CXX_STANDARD 11)       
SET(SOURCES 
    "HeatSim.cpp"
    "RenderUtils.cpp"
    "TransparencyViewer.cpp"
    "SimUtils.cpp"
)

find_package(Easy3D COMPONENTS viewer REQUIRED) 
add_executable(HeatSim ${SOURCES})                    
target_link_libraries(HeatSim easy3d::viewer) 