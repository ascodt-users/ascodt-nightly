#include "CouplingFunctions.h"


void getLocationVector (FLOAT * const location, const FLOAT * const regularizedPosition){

    const FLOAT x = regularizedPosition[0];
    const FLOAT y = regularizedPosition[1];
    const FLOAT z = regularizedPosition[2];

    // The location is provided with respect to the vertex of the triangle with the straight angle
#if defined(ODDSTENCIL) || defined(THIRDORDERSTENCIL)
    location[0] = 1.0;
    location[1] = x;
    location[2] = y;
    location[3] = z;
    location[4] = x * x;
    location[5] = x * y;
    location[6] = x * z;
    location[7] = y * y;
    location[8] = y * z;
    location[9] = z * z;
#endif
#ifdef THIRDORDERSTENCIL
    location[10] = x * x * x;
    location[11] = y * y * y;
    location[12] = z * z * z;
    location[13] = x * x * y;
    location[14] = x * x * z;
    location[15] = x * y * y;
    location[16] = y * y * z;
    location[17] = x * z * z;
    location[18] = y * z * z;
    location[19] = x * y * z;
#endif

#ifdef DQUADRATICSTENCIL
    location[0]  = 1.0;
    location[1]  = x;
    location[2]  = y;
    location[3]  = z;
    location[4]  = x * x;
    location[5]  = x * y;
    location[6]  = x * z;
    location[7]  = y * y;
    location[8]  = y * z;
    location[9]  = z * z;
    location[10] = x * y * y;
    location[11] = x * z * z;
    location[12] = x * x * y;
    location[13] = y * z * z;
    location[14] = x * x * z;
    location[15] = y * y * z;
    location[16] = x * y * z;
    location[17] = x * x * y * y;
    location[18] = x * x * y * z;
    location[19] = x * x * z * z;
    location[20] = x * y * y * z;
    location[21] = x * y * z * z;
    location[22] = x * x * z * z;
    location[23] = x * x * y * z * z;
    location[24] = x * x * y * y * z;
    location[25] = x * y * y * z * z;
    location[26] = x * x * y * y * z * z;
#endif
}


void getDerCoefficientVector (FLOAT * const derX, FLOAT * const derY, FLOAT * const derZ,
                              const FLOAT * const regularizedPosition, const int * const flip ){

    const FLOAT x = regularizedPosition[0];
    const FLOAT y = regularizedPosition[1];
    const FLOAT z = regularizedPosition[2];

    // More vectors for the derivatives. They will change sign according to how the stencil was
    // flipped, so we include it here
#if defined(ODDSTENCIL) || defined(THIRDORDERSTENCIL)
    derX[0] = 0.0;
    derX[1] = (double) flip[0];
    derX[2] = 0.0;
    derX[3] = 0.0;
    derX[4] = 2.0 * x * (double)flip[0];
    derX[5] = y * (double)flip[0];
    derX[6] = z * (double)flip[0];
    derX[7] = 0.0;
    derX[8] = 0.0;
    derX[9] = 0.0;
#ifndef ODDSTENCIL
    derX[10] = 3.0 * x * x * (double)flip[0];
    derX[11] = 0.0;
    derX[12] = 0.0;
    derX[13] = 2.0 * x * y * (double)flip[0];
    derX[14] = 2.0 * x * z * (double)flip[0];
    derX[15] = y * y * (double)flip[0];
    derX[16] = 0.0;
    derX[17] = z * z * (double)flip[0];
    derX[18] = 0.0;
    derX[19] = y * z * (double)flip[0];
#endif

    derY[0] = 0.0;
    derY[1] = 0.0;
    derY[2] = (double) flip[1];;
    derY[3] = 0.0;
    derY[4] = 0.0;
    derY[5] = x * (double)flip[1];
    derY[6] = 0.0;
    derY[7] = 2.0 * y * (double)flip[1];
    derY[8] = z * (double)flip[1];
    derY[9] = 0.0;
#ifndef ODDSTENCIL
    derY[10] = 0.0;
    derY[11] = 3.0 * y * y * (double)flip[1];
    derY[12] = 0.0;
    derY[13] = x * x * (double)flip[1];
    derY[14] = 0.0;
    derY[15] = 2.0 * x * y * (double)flip[1];
    derY[16] = 2.0 * z * y * (double)flip[1];
    derY[17] = 0.0;
    derY[18] = z * z * (double)flip[1];
    derY[19] = x * z * (double)flip[1];
#endif

    derZ[0] = 0.0;
    derZ[1] = 0.0;
    derZ[2] = 0.0;
    derZ[3] = (double) flip[2];
    derZ[4] = 0.0;
    derZ[5] = 0.0;
    derZ[6] = x * (double)flip[2];
    derZ[7] = 0.0;
    derZ[8] = y * (double)flip[2];
    derZ[9] = 2.0 * z * (double)flip[2];
#ifndef ODDSTENCIL
    derZ[10] = 0.0;
    derZ[11] = 0.0;
    derZ[12] = 3.0 * z * z * (double)flip[2];
    derZ[13] = 0.0;
    derZ[14] = x * x * (double)flip[2];
    derZ[15] = 0.0;
    derZ[16] = y * y * (double)flip[2];
    derZ[17] = 2.0 * x * z * (double)flip[2];
    derZ[18] = 2.0 * y * z * (double)flip[2];
    derZ[19] = x * y * (double)flip[2];
#endif
#endif

#ifdef DQUADRATICSTENCIL
    derX[0]  = 0.0;
    derX[1]  = flip[0];
    derX[2]  = 0.0;
    derX[3]  = 0.0;
    derX[4]  = 2.0 * x * flip[0];
    derX[5]  = y * flip[0];
    derX[6]  = z * flip[0];
    derX[7]  = 0.0;
    derX[8]  = 0.0;
    derX[9]  = 0.0;
    derX[10] = y * y * flip[0];
    derX[11] = z * z * flip[0];
    derX[12] = 2.0 * x * y * flip[0];
    derX[13] = 0.0;
    derX[14] = 2.0 * x * z * flip[0];
    derX[15] = 0.0;
    derX[16] = y * z * flip[0];
    derX[17] = 2.0 * x * y * y * flip[0];
    derX[18] = 2.0 * x * y * z * flip[0];
    derX[19] = 2.0 * x * z * z * flip[0];
    derX[20] = y * y * z * flip[0];
    derX[21] = y * z * z * flip[0];
    derX[22] = 0.0;
    derX[23] = 2.0 * x * y * z * z * flip[0];
    derX[24] = 2.0 * x * y * y * z * flip[0];
    derX[25] = y * y * z * z * flip[0];
    derX[26] = 2.0 * x * y * y * z * z * flip[0];

    derY[0]  = 0.0;
    derY[1]  = 0.0;
    derY[2]  = flip[1];
    derY[3]  = 0.0;
    derY[4]  = 0.0;
    derY[5]  = x * flip[1];
    derY[6]  = 0.0;
    derY[7]  = 2.0 * y * flip[1];
    derY[8]  = z * flip[1];
    derY[9]  = 0.0;
    derY[10] = 2.0 * x * y * flip[1];
    derY[11] = 0.0;
    derY[12] = x * x * flip[1];
    derY[13] = z * z * flip[1];
    derY[14] = 0.0;
    derY[15] = 2.0 * y * z * flip[1];
    derY[16] = x * z * flip[1];
    derY[17] = 2.0 * x * x * y * flip[1];
    derY[18] = x * x * z * flip[1];
    derY[19] = 0.0;
    derY[20] = 2.0 * x * y * z * flip[1];
    derY[21] = x * z * z * flip[1];
    derY[22] = 2.0 * y * z * z * flip[1];
    derY[23] = x * x * z * z * flip[1];
    derY[24] = 2.0 * x * x * y * z * flip[1];
    derY[25] = 2.0 * x * y * z * z * flip[1];
    derY[26] = 2.0 * x * x * y * z * z * flip[1];

    derZ[0]  = 0.0;
    derZ[1]  = 0.0;
    derZ[2]  = 0.0;
    derZ[3]  = flip[2];
    derZ[4]  = 0.0;
    derZ[5]  = 0.0;
    derZ[6]  = x * flip[2];
    derZ[7]  = 0.0;
    derZ[8]  = y * flip[2];
    derZ[9]  = 2.0 * z * flip[2];
    derZ[10] = 0.0;
    derZ[11] = 2.0 * x * z * flip[2];
    derZ[12] = 0.0;
    derZ[13] = 2.0 * y * z * flip[2];
    derZ[14] = x * x * flip[2];
    derZ[15] = y * y * flip[2];
    derZ[16] = x * y * flip[2];
    derZ[17] = 0.0;
    derZ[18] = x * x * y * flip[2];
    derZ[19] = 2.0 * x * x * z * flip[2];
    derZ[20] = x * y * y * flip[2];
    derZ[21] = 2.0 * x * y * z * flip[2];
    derZ[22] = 2.0 * y * y * z * flip[2];
    derZ[23] = 2.0 * x * x * y * z * flip[2];
    derZ[24] = x * x * y * y * flip[2];
    derZ[25] = 2.0 * x * y * y * z * flip[2];
    derZ[26] = 2.0 * x * x * y * y * z * z * flip[2];
#endif
}


FLOAT dot(const FLOAT * const v1, const FLOAT * const v2, int n){
    FLOAT sum = 0;
    for (int i = 0; i < n; i++){
        sum += v1[i] * v2[i];
    }
    return sum;
}


void matrix_vector(const FLOAT matrix[][stencilSize], const FLOAT * const vector,
                   FLOAT * const result, int rows, int columns){
    for (int i = 0; i < rows; i++){
        result[i] = 0;
        for (int j = 0; j < columns; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }
}


int getOverlapWidth (const Parameters & parameters){
    return parameters.coupling.overlap;
}
