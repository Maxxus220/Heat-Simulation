# Heat-Simulation

Runs a 3d rendered "heat-simulation". Made with C++, uses the Easy3D C++ graphics library to handle the rendering, and also uses OpenMP for optimizations.

## How to build
This project was developed and exclusively tested on Ubuntu 22.04.2 LTS and requires CMake 3.22.1 or greater.

This project has a few dependencies required before being able to build.

### Easy3d
First off, you will need to clone and build Easy3D.


**Easy3D**: https://github.com/LiangliangNan/Easy3D


Easy3D is also dependent on OpenGL, so before following the build steps for Easy3D, I would first run


    sudo apt-get install libgl1-mesa-dev


to avoid issues.
After that, just follow the steps on the github for Easy3D to build.


Note that the CMakeLists.txt for Heat-Simulation assumes that Easy3D is located within the project folder.


i.e. Heat-Simulation/Easy3D


If you choose to build Easy3D somewhere else you will need to change the line 


    set(Easy3D_DIR ./Easy3D/Release/)


within the CMakeLists.txt for Heat-Simulation to point to your Release folder.

### GLFW
You will also need to install GLFW. You can do so with the following.


    sudo apt-get install libglfw3-dev


### HeatSim
Now you should be able to build the project. To do so, open the terminal in the project's root directory. Then run these commands.

    mkdir build
    cd ./build
    cmake ..
    make

This should create the executable HeatSim. Simply run HeatSim.

## How does HeatSim work?

When you run HeatSim, the program will first ask you to enter coordinates and temperatures to set initial temperatures of various simulation cubes. By default, HeatSim assumes a 15x15x15 space and uses 0 indexing (i.e. 0-14). To change the size parameters, simply edit the XDIM, YDIM, ZDIM, parameters within Parameters.h. When you are finished entering initial values (all values not specified will default to 0), the Easy3D rendering window will appear. You can move to the next frame of simulation by pressing the n key.


NOTE: When entering starting values, the outermost layer of the space will never change values (this is to avoid index out of bounds when simulating). Additionally, cubes will only consider the cubes directly touching them (no diagonals), so starting values set on the outer edges of the space will have no effect on simulation (i.e. In a 15x15x15 space, setting the cube at x: 14, y: 14, z: 14 to have a temperature of 100 will have no effect).