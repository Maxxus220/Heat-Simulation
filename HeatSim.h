#include <easy3d/core/model.h>

void clearArray(easy3d::Model* (&array) [XDIM][YDIM][ZDIM]);
bool checkCoordinates(int* point3D);
bool checkSingleCoordinate(int coord, int dimSize);
void enterDataPoints(easy3d::Model* (&array) [XDIM][YDIM][ZDIM]);
