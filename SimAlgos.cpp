#include "SimAlgos.h"
#include "SimUtils.h"

using namespace easy3d;
using namespace std;

void laplacian(Model* (&array) [XDIM][YDIM][ZDIM]) {
    #pragma omp parallel for
    for(int i = 0; i < XDIM; i++) {
    for(int j = 0; j < YDIM; j++) {
    for(int k = 0; k < ZDIM; k++) {
        float newHeat = get_heat(i,j,k,array) * -6 +
            get_heat(i+1,j,k,array) +
            get_heat(i-1,j,k,array) +
            get_heat(i,j+1,k,array) +
            get_heat(i,j-1,k,array) +
            get_heat(i,j,k+1,array) +
            get_heat(i,j,k-1,array);
        set_heat(newHeat, i, j, k, array);
    }
    }
    }
}