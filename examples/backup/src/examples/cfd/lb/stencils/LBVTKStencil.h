#ifndef _LB_VTK_STENCIL_H_
#define _LB_VTK_STENCIL_H_

#include "Definitions.h"
#include "Parameters.h"
#include "Stencil.h"
#include "../LBField.h"
#include <string>
#include <fstream>
#include <sstream>

/** Stencil for writting VTK files
 *
 * When iterated with, creates a VTK file.
 */
class LBVTKStencil : public FieldStencil<LBField> {

    private:

        std::string _prefix;    //! Prefix to be attached to the vtk files
        std::ofstream _ofile;   //! Output file stream
        bool _written;          //! Whether the file has already been written
        int count;
        FLOAT _secondMoment[6];

        std::stringstream pressureStream;   //! Stream for the pressure data
        std::stringstream velocityStream;   //! Stream for the velocity data

        std::stringstream xxStream;
        std::stringstream xyStream;
        std::stringstream yyStream;
        std::stringstream xzStream;
        std::stringstream yzStream;
        std::stringstream zzStream;

        FLOAT _velocity [3];

    public:

        /** Constructor
         *
         * @param prefix String with the prefix of the name of the VTK files
         */
        LBVTKStencil ( const Parameters & parameters );

        /** 2D operation for one position
         *
         * @param flowField State of the flow field
         * @param i Position in the x direction
         * @param j Position in the y direction
         */
        void apply ( LBField & field, int i, int j );

        /** 3D operation for one position
         *
         * @param flowField State of the flow field
         * @param i Position in the x direction
         * @param j Position in the y direction
         * @param k Position in the z direction
         */
        void apply ( LBField & field, int i, int j, int k );

        /** Open output file
         * Opens the output file and prepares for writing.
         * It also writes the header of the file and the points og the grid.
         * @param flowField State of the flow field
         * @param time Current simulation time in double format
         */
        void openFile ( const LBField & field, FLOAT time );

        /** Writes the information to the file
         * @param flowField Flow field to be written
         */
        void write ( LBField & field );

        /** Finish writing. Must be called once the file has been written.
         *
         * Stores all the streams and closes the file.
         */
        void closeFile ();

        /** Set the prefix for the files. Can be used to override the name given in the parameters
         * @param prefix New prefix
         */
        void setPrefix(const std::string prefix);
};

#endif
