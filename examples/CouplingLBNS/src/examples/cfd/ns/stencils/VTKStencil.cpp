#include "VTKStencil.h"

// TODO Correct performance issues for big matrices still required

void writeVTKHeader ( std::ostream & file, const FlowField & flowField ) {

    file << "# vtk DataFile Version 2.0" << std::endl
        << "I need something to put here" << std::endl
        << "ASCII" << std::endl << std::endl;
}


void writePoints (std::ostream & file, const FlowField & flowField,
                  const Parameters & parameters){

    // Number of points in every direction
    int px = flowField.getNx() + 1;
    int py = flowField.getNy() + 1;
    int pz = flowField.getDim()==2 ? 1 : flowField.getNz() + 1;

    std::string grid;
    char buffer[256];

    grid.reserve ( ( file.precision() + 6 ) * px * py * pz * 3 );

    sprintf ( buffer, "DATASET STRUCTURED_GRID\nDIMENSIONS %d %d %d\nPOINTS %d float\n",
                            px, py, pz, px * py * pz);
    grid.append ( buffer );

    for ( int k = parameters.parallel.firstCorner[2]; k < parameters.parallel.firstCorner[2]+ pz; k++ ){
        for ( int j = parameters.parallel.firstCorner[1]; j < parameters.parallel.firstCorner[1] + py; j++ ){
            for ( int i = parameters.parallel.firstCorner[0]; i < parameters.parallel.firstCorner[0] + px; i++ ){
                sprintf (buffer, "%f %f %f\n", i * parameters.geometry.dx,
                         j * parameters.geometry.dy,
                         k * parameters.geometry.dz );
                grid.append ( buffer );
            }
        }
    }
    grid.append ("\n");

    file << grid;
}


VTKStencil::VTKStencil (const Parameters & parameters) :
    FieldStencil<FlowField> ( parameters ), _prefix(parameters.vtk.prefix), _written(false) {

//    _prefix = parameters.vtk.prefix;
//    _written = false;
}


void VTKStencil::apply ( FlowField & flowField, int i, int j ) {

    assertion ( flowField.getDim() == 2 );

    FLOAT pressure, *velocity;

    if ((flowField.getFlags().getValue(i,j) & OBSTACLE_SELF) == 0){
        flowField.getPressureAndVelocity(pressure, velocity, i, j);

        pressureStream << pressure << std::endl;

        velocityStream << velocity[0] << " "
            << velocity[1] << " 0" << std::endl;
    } else {
        pressureStream << "0.0" << std::endl;
        velocityStream << "0.0 0.0 0.0" << std::endl;
    }
}


void VTKStencil::apply ( FlowField & flowField, int i, int j, int k ) {

    assertion ( flowField.getDim() == 3 );

    FLOAT pressure, *velocity;

    if ((flowField.getFlags().getValue(i,j,k) & OBSTACLE_SELF) == 0){
        flowField.getPressureAndVelocity(pressure, velocity, i, j, k);

        pressureStream << pressure << std::endl;

        velocityStream << velocity[0] << " "
            << velocity[1] << " "
            << velocity[2] << std::endl;
    } else {
        pressureStream << "0.0" << std::endl;
        velocityStream << velocity[0] << " "
                    << velocity[1] << " "
                    << velocity[2] << std::endl;
    }
}


void VTKStencil::openFile ( const FlowField & flowField, FLOAT time ){

    // This relates to openning the file with the correct name
    _written = false;
    std::stringstream namestream;
    std::string name;
    namestream.precision (4);
    namestream << _prefix << "." << _parameters.parallel.rank << "." << time << ".vtk";
    name = namestream.str ();
    _ofile.open ( name.c_str() );
    namestream.str("");

    writeVTKHeader ( _ofile, flowField );

    writePoints ( _ofile, flowField, _parameters );
}


void VTKStencil::write ( FlowField & flowField ){

    if (flowField.getDim() == 2){
        // Write pressure
        _ofile << "CELL_DATA " << flowField.getNx() * flowField.getNy() << std::endl
            << "SCALARS pressure float 1" << std::endl
            << "LOOKUP_TABLE default" << std::endl;
        _ofile << pressureStream.str() << std::endl;
        pressureStream.str("");

        // Write velocity
        // _ofile << "CELL_DATA " << flowField.getNx() * flowField.getNy() << std::endl
       _ofile << "VECTORS velocity float" << std::endl;
        _ofile << velocityStream.str() << std::endl;
        velocityStream.str("");
    }

    if (flowField.getDim() == 3){
        // Write pressure
        _ofile << "CELL_DATA " << flowField.getNx() * flowField.getNy() * flowField.getNz()
            << std::endl
            << "SCALARS pressure float 1" << std::endl
            << "LOOKUP_TABLE default" << std::endl;
        _ofile << pressureStream.str() << std::endl;
        pressureStream.str("");

        // Write velocity
        // _ofile << "CELL_DATA " << flowField.getNx() * flowField.getNy() << std::endl
       _ofile << "VECTORS velocity float" << std::endl;
        _ofile << velocityStream.str() << std::endl;
        velocityStream.str("");
    }

    _written = true;
}


void VTKStencil::closeFile () {
    _ofile. close ();
}
