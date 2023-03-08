#include "SimAlgos.h"
#include "SimUtils.h"

using namespace easy3d;
using namespace std;

using array_tf = float (&) [XDIM][YDIM][ZDIM];

void laplacian(Model* (&array) [XDIM][YDIM][ZDIM]) {

    float* newTempsRaw = new float [XDIM*YDIM*ZDIM];
    array_tf newTemps = reinterpret_cast<array_tf>(*newTempsRaw);

    #pragma omp parallel for
    for(int i = 1; i < XDIM-1; i++) {
    for(int j = 1; j < YDIM-1; j++) {
    for(int k = 1; k < ZDIM-1; k++) {
        newTemps[i][j][k] = get_heat(i,j,k,array) * -6 +
            get_heat(i+1,j,k,array) +
            get_heat(i-1,j,k,array) +
            get_heat(i,j+1,k,array) +
            get_heat(i,j-1,k,array) +
            get_heat(i,j,k+1,array) +
            get_heat(i,j,k-1,array);
    }
    }
    }

    #pragma omp parallel for
    for(int i = 1; i < XDIM-1; i++) {
    for(int j = 1; j < YDIM-1; j++) {
    for(int k = 1; k < ZDIM-1; k++) {
        set_heat(newTemps[i][j][k], i, j, k, array);
    }
    }
    }

    delete newTempsRaw;
}