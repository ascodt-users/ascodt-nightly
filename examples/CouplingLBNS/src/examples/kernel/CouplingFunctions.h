#ifndef _COUPLING_FUNCTIONS_H_
#define _COUPLING_FUNCTIONS_H_

#include "Definitions.h"
#include "Parameters.h"
#include "CouplingDefinitions.h"


/** Maps the location of a point to the quantities of the interpolation polynomial
 * @param regularizedPosition Position of the desired point transformed to the stencil coordinate
 * system
 * @return location Location vector. Output of the feature map in the interpolation.
 */
void getLocationVector (FLOAT * const location, const FLOAT * const regularizedPosition);

/** Returns feature maps for the derivatives.
 * The interpolating polynomial is differentiated to obtain values for the derivatives.
 * The differentiation is performed by using the derivatives of the map.
 * @parameter regularizedPosition Position converted to the stencil's coordinate system
 * @parameter flip Array stating in which directions the stencil has been flipped
 * @return derX Location vector for the derivative in x
 * @return derY Location vector for the derivative in y
 * @return derZ Location vector for the derivative in z
 */
void getDerCoefficientVector (FLOAT * const derX, FLOAT * const derY, FLOAT * const derZ,
                              const FLOAT * const regularizedPosition, const int * const flip );

/** Dot product
 * It is easier to put it here than to link to BLAS
 * @param v1 First vector
 * @param v2 Second vector
 * @param n Number of elements in the vectors
 * @return Dot product of the vectors
 */
FLOAT dot(const FLOAT * const v1, const FLOAT * const v2, int n);

/** Matrix-vector product
 * Included here so that there's no need to use BLAS
 * @param matrix Matrix parameter
 * @param vector Vector parameter
 * @param rows Number of rows in the matrix
 * @param columns Number of columns in the matrix
 * @return result Resulting vector
 */
void matrix_vector(const FLOAT matrix[][stencilSize], const FLOAT * const vector,
                   FLOAT * const result, int rows, int columns);

/** Returns the size of the overlap region
 * @param parameters Parameter structure of the simulation
 * @return Size of the overlap in NS cells
 */
int getOverlapWidth (const Parameters & parameters);

#endif
