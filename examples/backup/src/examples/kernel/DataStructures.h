#ifndef _DATA_STRUCTURES_H_
#define _DATA_STRUCTURES_H_

#include "Definitions.h"

/** Storage of a scalar field
 *
 * Parent of storage classes. Contains the data pointer and sizes in each
 * dimension. Uses floating point
 */
class Field
{
    protected:

        //! Pointer to the data array
        FLOAT* _data;

        const int _size_x; //! Size of the field in x direction, including ghost layers
        const int _size_y; //! Size of the field in y direction, including ghost layers
        const int _size_z; //! Size of the field in z direction, including ghost layers
        const int _components; //! Number of components per position
        const int _dim;        //! Number of dimensions of the field
        const int _size;       //! Total size of the data array

        //! Contains whether data points to currently allocated memory
        bool _allocated;

        //! Initializes the field to zero
        void _initialize ();


    public:

        /** Field empty constructor.
         */
        Field ();

        /** Constructor for the field
         *
         * General constructor. Takes the three arguments even if the matrix is
         * two dimensional. Doesn't allocate memory, only sets the dimensions
         *
         * @param Nx Number of cells in the x direction
         * @param Ny Number of cells in the y direction
         * @param Nz Number of cells in the z direction
         */
        Field ( int Nx, int Ny, int Nz, int dim, int components );

        /** Destructor
         *
         * Deallocates the data for all the fields
         */
        virtual ~Field ();

        /** Returns the number of cells in the x direction
         *
         * @return The size in the x direction
         */
        virtual int getNx () const;

        /** Returns the number of cells in the y direction
         *
         * @return The size in the y direction
         */
        virtual int getNy () const;

        /** Returns the number of cells in the z direction
         *
         * @return The size in the z direction
         */
        virtual int getNz () const;

        /** Get dimensionality of the array
         *
         * @return The dimension of the array
         */
        virtual int getDim () const;

        /** Index to array position mapper
         *
         * Index mapper. Converts the given index to the corresponding position
         * in the array.
         *
         * @param i x index
         * @param j y index
         * @param k z index
         *
         * @return Position in the array
         */
        virtual int index2array ( int i, int j, int k = 0 ) const;

};


/** Scalar field representation
 *
 * Stores a scalar field of floats. Derived from Field.
 */
class ScalarField: public Field
{

    public:

        /** 2D scalar field constructor.
         *
         * Sets the size of the data array and allocates data for the 2D field
         *
         * @param Nx Number of cells in direction x
         * @param Ny Number of cells in direction y
         */
        ScalarField ( int Nx, int Ny );

        /** 3D scalar field constructor.
         *
         * Sets the size of the data array and allocates data for the 3D field
         *
         * @param Nx Number of cells in direction x
         * @param Ny Number of cells in direction y
         * @param Nz Number of cells in direction z
         */
        ScalarField ( int Nx, int Ny, int Nz );

        /** Acces to element in scalar field
         *
         * Returns a reference to an element of the scalar field, so that it
         * can be read and written.
         * @param i x index
         * @param j y index
         * @param k z index. Not required for arrays of dimension two.
         */
        FLOAT & getScalar ( int i, int j, int k = 0 );

        /** Prints the contents of the field
         *
         * Shows the content of the scalar field by printing them to stdout. Only clear if the
         * matrix is small enough. Used for debugging.
         *
         * @param title A label for the printed matrix
         */
        void show (const std::string title = "");

};


/** Vector field representation
 *
 * Stores a vector field of floats. Derived from Field.
 */
class VectorField: public Field
{

    public:

        /** 2D Vector field constructor.
         *
         * Sets the size of the data array and allocates data for the 2D field
         *
         * @param Nx Number of cells in direction x
         * @param Ny Number of cells in direction y
         * @param Nz Number of cells in direction z
         */
        VectorField ( int Nx, int Ny );

        /** 3D Vector field constructor.
         *
         * Sets the size of the data array and allocates data for the 3D field
         *
         * @param Nx Number of cells in direction x
         * @param Ny Number of cells in direction y
         * @param Nz Number of cells in direction z
         */
        VectorField ( int Nx, int Ny, int Nz );

        /** Copies the values of the vector into the desired position in the
         * field
         *
         * Copies dimension number of values from the array passed as argument
         * to the position given by the indexes
         *
         * @param value Pointer to the array with the elements that will be
         * placed in the field
         * @param i x index
         * @param j y index
         * @param k z index
         */
        void setVector ( const FLOAT* value, int i, int j, int k = 0 );

        /** Non constant acces to an element in the vector field
         *
         * Returns a pointer to the position in the array that can be used to
         * modify it.
         *
         * @param i x index
         * @param j y index
         * @param k z index
         */
        FLOAT* getVector ( int i, int j, int k = 0 );

        /** Prints the contents of the field
         *
         * Shows the content of the first two components of a vector field by printing them to
         * stdout. Only clear if the matrix is small enough. Used for debugging.
         *
         * @param title A label for the printed matrix
         */
        void show (const std::string title = "");
};


/** Integer field
 * 
 * Integer field with one value per position. Intended to represent flag
 * fields. Implemented because templates are undesirable at this point
 */
class IntScalarField : public Field {

    private:

        int *_data;

        /** Initialize the array with zeros
         *
         * Had to be redeclared here because the object of the parent class
         * writes floats and caused a memory access violation.
         */
        void _initialize ();

    public:

        /** 2D constructor
         *
         * @param Nx Size in the x direction
         * @param Ny Size in the Y direction
         */
        IntScalarField ( int Nx, int Ny );

        /** 3D constructor
         *
         * @param Nx Size in the x direction
         * @param Ny Size in the Y direction
         * @param Nz SIze in the Z direction
         */
        IntScalarField ( int Nx, int Ny, int Nz );

        /** Access field values
         *
         * Returns a reference to the element with the given index
         *
         * @param i X index
         * @param j Y index
         * @param k Z index
         */
        int & getValue ( int i, int j, int k = 0 );

};


#endif
