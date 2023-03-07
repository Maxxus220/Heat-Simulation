cmake_minimum_required(VERSION 3.22.1)
set(CMAKE_CXX_STANDARD 11)       

project(HeatSim)

set(Easy3D_DIR ./gfx/Easy3D/Release/)

SET(SOURCES 
    "HeatSim.cpp"
    "RenderUtils.cpp"
    "TransparencyViewer.cpp"
    "SimUtils.cpp"
)

find_package(Easy3D COMPONENTS viewer REQUIRED) 
find_package(glfw3 REQUIRED)

include_directories(${GLFW_INCLUDE_DIRS})

add_executable(HeatSim ${SOURCES})           

target_link_libraries(HeatSim easy3d::viewer) 
target_link_libraries(HeatSim ${GLFW_LIBRARIES})