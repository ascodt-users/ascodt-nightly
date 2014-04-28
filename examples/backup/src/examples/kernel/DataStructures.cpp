#include "DataStructures.h"


// Functions for scalar and vector fields -------------------------------------

Field::Field () :
    _size_x ( 0 ), _size_y ( 0 ), _size_z ( 0 ), _components ( 0 ),
    _dim ( 0 ), _size ( 0 ) {
    _data = NULL;
    _allocated = false;
}

Field::Field ( int Nx, int Ny, int Nz, int dim, int components ):
    _size_x ( Nx ), _size_y ( Ny ), _size_z ( Nz ), _components ( components ),
    _dim( dim ), _size ( components * Nx * Ny * Nz ) {

    _data = new FLOAT [ _size ];

    // Check if the data was allocated successfully
    if (_data == 0){
        handleError ( 1, "Unable to allocate memory" );
    }

    _allocated = true;
    _initialize ();
}


Field::~Field () {
    if (_allocated){
        delete[] _data;
    }
}

int Field::getNx () const {
    return _size_x;
}

int Field::getNy () const {
    return _size_y;
}

int Field::getNz () const {
    return _size_z;
}

int Field::getDim () const {
    return _dim;
}

void Field::_initialize () {
    for (int i = 0; i < _size; i++){
        _data[i] = 0;
    }
}

inline int Field::index2array ( int i, int j, int k ) const {

    // Check that the indexes are within bounds
    assertion ( ( i < _size_x ) && ( j < _size_y ) && ( k < _size_z ) );
    assertion ( ( i >= 0 ) && ( j >= 0 ) && ( k >= 0 )  );

    return  _components * ( i + ( j * _size_x ) + ( k * _size_x * _size_y ) );
}



// Functions specific to the scalar field -------------------------------------


ScalarField::ScalarField ( int Nx, int Ny ):
    Field ( Nx, Ny, 1, 2, 1 ) {}


ScalarField::ScalarField ( int Nx, int Ny, int Nz ):
    Field ( Nx, Ny, Nz, 3, 1 ) {}


FLOAT& ScalarField::getScalar ( int i, int j, int k ) {
    return _data [ index2array ( i, j, k ) ];
}

void ScalarField::show(const std::string title){
    std::cout << std::endl << "--- " << title << " ---" << std::endl;
    for (int k = 0; k < _size_z; k++){
        for (int j = _size_y-1; j > -1; j--){
            for (int i = 0; i < _size_x; i++){
                std::cout << getScalar(i,j,k) << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}



// Functions related to the vector field --------------------------------------

VectorField::VectorField ( int Nx, int Ny ):
    Field ( Nx, Ny, 1 , 2, 2 ) {}


VectorField::VectorField ( int Nx, int Ny, int Nz ):
    Field ( Nx, Ny, Nz, 3, 3 ) {}


FLOAT* VectorField::getVector ( int i, int j, int k ) {
    return &_data[index2array( i, j, k )];
}


void VectorField::setVector ( const FLOAT* value,
                              int i,
                              int j,
                              int k ) {

    assertion ( value != NULL );

    FLOAT* pointer = _data + index2array ( i, j, k );
    for ( int i = 0; i < _dim; i++ ){
        pointer[i] = value[i];
    }
}

void VectorField::show(const std::string title){
    std::cout << std::endl << "--- " << title << " ---" << std::endl;
    std::cout << "Component 1" << std::endl;
    for (int k = 0; k < _size_z; k++){
        for (int j = _size_y-1; j > -1; j--){
            for (int i = 0; i < _size_x; i++){
                std::cout << getVector(i,j,k)[0] << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    std::cout << "Component 2" << std::endl;
    for (int k = 0; k < _size_z; k++){
        for (int j = _size_y-1; j > -1; j--){
            for (int i = 0; i < _size_x; i++){
                std::cout << getVector(i,j,k)[1] << "\t";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}

//----------------------------------------------------------------------------
// Stuff related to the integer scalar field

IntScalarField::IntScalarField ( int Nx, int Ny ) : Field ( Nx, Ny, 1, 2, 1 ) {

    // Allocate space for the structure
    _data = new int [ _size ];

    // Check if the data was allocated successfully
    if (_data == 0){
        handleError ( 1, "Unable to allocate memory" );
    }

    _allocated = true;
    _initialize();
}


IntScalarField::IntScalarField ( int Nx, int Ny, int Nz ) :
    Field ( Nx, Ny, Nz, 3, 1 ) {

    // Allocate space for the structure
    _data = new int [ _size ];

    // Check if the data was allocated successfully
    if (_data == 0){
        handleError ( 1, "Unable to allocate memory" );
    }

    _allocated = true;
    _initialize();
}


void IntScalarField::_initialize () {
    for ( int i = 0; i < _size; i++ ){
        _data[i] = 0;
    }
}


int & IntScalarField::getValue ( int i, int j, int k ) {
    return _data[ index2array (i, j, k) ];
}
