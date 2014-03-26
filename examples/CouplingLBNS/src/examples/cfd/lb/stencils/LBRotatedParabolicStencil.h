#include "Stencil.h"
#include "Parameters.h"
#include "../LBField.h"

/** Class used to generate boundaries that contain pressures, velocities and shears corresponding
 * to parabolic channel flow.
 */
class LBRotatedParabolicStencil : public GlobalBoundaryStencil<LBField> {

    private:

        FLOAT _gradRho[3];          //! The density gradient
        FLOAT _unitaryGradRho[3];   //! Unitary vector with the derection fo the pressure gradient

        FLOAT _plateNormal[3];      //! Unitary vector normal to the plates

        FLOAT _pivot[3];          //! One of the corners in the plain

        FLOAT _plateSeparation;
        FLOAT _halfPlateSeparation;

        FLOAT _gradNorm;        //! Magnitude of the gradient

        FLOAT _speedFactor;

        // To compute the density using the position and a projection of the pressure gradient, we
        // need the density at one of the corners. It turns out that only four values are required.
        // These variables store them

        FLOAT _firstDensity0;
        FLOAT _firstDensityX;
        FLOAT _firstDensityY;
        FLOAT _firstDensityZ;

    public:

        LBRotatedParabolicStencil (const Parameters & parameters,
                                   FLOAT gradRhoX, FLOAT gradRhoY, FLOAT gradRhoZ,
                                   FLOAT plateNormalX, FLOAT plateNormalY, FLOAT PlateNormalZ);

        FLOAT getGradRhoComponent(const FLOAT * const vector) const;     //! Get the component of a vector in the direction of gradRho
        FLOAT getPlateNormalComponent(const FLOAT * const vector) const;

        const FLOAT * const getPlateNormal() const;
        const FLOAT * const getUnitaryGradRho() const;
        const FLOAT * const getPivot() const;
        const FLOAT getGradientMagnitude () const;
        const FLOAT getPlateSeparation () const;

        void applyLeftWall   (LBField & field, int i, int j);
        void applyRightWall  (LBField & field, int i, int j);
        void applyBottomWall (LBField & field, int i, int j);
        void applyTopWall    (LBField & field, int i, int j);

        void applyLeftWall   (LBField & field, int i, int j, int k);
        void applyRightWall  (LBField & field, int i, int j, int k);
        void applyBottomWall (LBField & field, int i, int j, int k);
        void applyTopWall    (LBField & field, int i, int j, int k);
        void applyFrontWall  (LBField & field, int i, int j, int k);
        void applyBackWall   (LBField & field, int i, int j, int k);
};
