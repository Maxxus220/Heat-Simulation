#include <easy3d/core/model.h>
#include <easy3d/viewer/viewer.h>

void clearArray(easy3d::Model* (&array) [XDIM][YDIM][ZDIM]);
bool checkCoordinates(int* point3D);
bool checkSingleCoordinate(int coord, int dimSize);
void enterDataPoints(easy3d::Model* (&array) [XDIM][YDIM][ZDIM]);
void initializeArray(easy3d::Viewer* viewer, easy3d::Model* (&array) [XDIM][YDIM][ZDIM]);
