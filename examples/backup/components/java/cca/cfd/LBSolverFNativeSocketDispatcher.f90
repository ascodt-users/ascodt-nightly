module cca_cfd_LBSolverFNativeSocketDispatcher
use, intrinsic :: iso_c_binding
implicit none


type, public :: LBSolverNativeSocketDispatcher
     integer(kind=c_long_long )::reference
     contains
     procedure,public::createClientDispatcherInstanceForC
     procedure,public::createClientDispatcherInstance
     procedure,public::destroyDispatcherInstance
     
     
     	procedure,public::setup
	procedure,private::setup_internal
	procedure,public::setupCommForNSRegion
	procedure,private::setupCommForNSRegion_internal
	procedure,public::solve
	procedure,private::solve_internal
	procedure,public::solveOneTimestep
	procedure,private::solveOneTimestep_internal
	procedure,public::setVelocities
	procedure,private::setVelocities_internal
	procedure,public::setPressure
	procedure,private::setPressure_internal
	procedure,public::setGradients
	procedure,private::setGradients_internal
	procedure,public::closeLBProfiles
	procedure,private::closeLBProfiles_internal
	procedure,public::printLBDensity
	procedure,private::printLBDensity_internal
	procedure,public::printLBProfiles
	procedure,private::printLBProfiles_internal
	procedure,public::forwardVelocities
	procedure,private::forwardVelocities_internal
	procedure,public::forwardPressure
	procedure,private::forwardPressure_internal
	procedure,public::syncr
	procedure,private::syncr_internal
	procedure,public::plot
	procedure,private::plot_internal

end type LBSolverNativeSocketDispatcher
contains
subroutine createClientDispatcherInstanceForC(this,host,port,buffer_size)
    class(LBSolverNativeSocketDispatcher)::this
    character(kind=c_char),dimension(*)::host
    integer(kind=c_int)::port
    integer(kind=c_int)::buffer_size
    this%reference=0
    call cca_cfd_lbsolver_f2c_nsd_create_client_instance(this%reference,host,port,buffer_size)
    
    

end subroutine createClientDispatcherInstanceForC

subroutine createClientDispatcherInstance(this,host,port,buffer_size)
    class(LBSolverNativeSocketDispatcher)::this
    character(*)::host
    integer::port
    integer::buffer_size
    call this%createClientDispatcherInstanceForC(host//c_null_char,port,buffer_size)
    
    

end subroutine createClientDispatcherInstance

subroutine destroyDispatcherInstance(this)
     class(LBSolverNativeSocketDispatcher)::this
     call cca_cfd_lbsolver_f2c_nsd_destroy_instance(this%reference)

end subroutine destroyDispatcherInstance

subroutine plot_internal(this)
     use, intrinsic :: iso_c_binding
     class(LBSolverNativeSocketDispatcher)::this
     
     call cca_cfd_lbsolver_f2c_nsd_plot(this%reference)
end subroutine plot_internal

subroutine plot(this)
     use, intrinsic :: iso_c_binding
     class(LBSolverNativeSocketDispatcher)::this
     
     call this%plot_internal()
end subroutine plot
subroutine syncr_internal(this,&
	value)
     use, intrinsic :: iso_c_binding
     class(LBSolverNativeSocketDispatcher)::this
     	integer(kind=c_int),intent(inout)::value

     call cca_cfd_lbsolver_f2c_nsd_syncr(this%reference,&
value)
end subroutine syncr_internal

subroutine syncr(this,&
	value)
     use, intrinsic :: iso_c_binding
     class(LBSolverNativeSocketDispatcher)::this
     	integer,intent(inout)::value

     call this%syncr_internal(&
value)
end subroutine syncr
subroutine forwardPressure_internal(this,&
	keys,keys_len,&
	offsets,offsets_len,&
	flips,flips_len,&
	values,values_len,&
	ackn)
     use, intrinsic :: iso_c_binding
     class(LBSolverNativeSocketDispatcher)::this
     	integer(kind=c_int),intent(in),dimension(*)::keys
	integer(kind=c_int),intent(in)::keys_len
	integer(kind=c_int),intent(in),dimension(*)::offsets
	integer(kind=c_int),intent(in)::offsets_len
	integer(kind=c_int),intent(in),dimension(*)::flips
	integer(kind=c_int),intent(in)::flips_len
	real(kind=c_double),intent(in),dimension(*)::values
	integer(kind=c_int),intent(in)::values_len
	integer(kind=c_int),intent(inout)::ackn

     call cca_cfd_lbsolver_f2c_nsd_forwardPressure(this%reference,&
keys,keys_len,&
offsets,offsets_len,&
flips,flips_len,&
values,values_len,&
ackn)
end subroutine forwardPressure_internal

subroutine forwardPressure(this,&
	keys,keys_len,&
	offsets,offsets_len,&
	flips,flips_len,&
	values,values_len,&
	ackn)
     use, intrinsic :: iso_c_binding
     class(LBSolverNativeSocketDispatcher)::this
     	integer,intent(in),dimension(*)::keys
	integer,intent(in)::keys_len
	integer,intent(in),dimension(*)::offsets
	integer,intent(in)::offsets_len
	integer,intent(in),dimension(*)::flips
	integer,intent(in)::flips_len
	real(8),intent(in),dimension(*)::values
	integer,intent(in)::values_len
	integer,intent(inout)::ackn

     call this%forwardPressure_internal(&
keys,keys_len,&
offsets,offsets_len,&
flips,flips_len,&
values,values_len,&
ackn)
end subroutine forwardPressure
subroutine forwardVelocities_internal(this,&
	keys,keys_len,&
	offsets,offsets_len,&
	flips,flips_len,&
	values,values_len,&
	componentSize,componentSize_len,&
	ackn)
     use, intrinsic :: iso_c_binding
     class(LBSolverNativeSocketDispatcher)::this
     	integer(kind=c_int),intent(in),dimension(*)::keys
	integer(kind=c_int),intent(in)::keys_len
	integer(kind=c_int),intent(in),dimension(*)::offsets
	integer(kind=c_int),intent(in)::offsets_len
	integer(kind=c_int),intent(in),dimension(*)::flips
	integer(kind=c_int),intent(in)::flips_len
	real(kind=c_double),intent(in),dimension(*)::values
	integer(kind=c_int),intent(in)::values_len
	integer(kind=c_int),intent(in),dimension(*)::componentSize
	integer(kind=c_int),intent(in)::componentSize_len
	integer(kind=c_int),intent(inout)::ackn

     call cca_cfd_lbsolver_f2c_nsd_forwardVelocities(this%reference,&
keys,keys_len,&
offsets,offsets_len,&
flips,flips_len,&
values,values_len,&
componentSize,componentSize_len,&
ackn)
end subroutine forwardVelocities_internal

subroutine forwardVelocities(this,&
	keys,keys_len,&
	offsets,offsets_len,&
	flips,flips_len,&
	values,values_len,&
	componentSize,componentSize_len,&
	ackn)
     use, intrinsic :: iso_c_binding
     class(LBSolverNativeSocketDispatcher)::this
     	integer,intent(in),dimension(*)::keys
	integer,intent(in)::keys_len
	integer,intent(in),dimension(*)::offsets
	integer,intent(in)::offsets_len
	integer,intent(in),dimension(*)::flips
	integer,intent(in)::flips_len
	real(8),intent(in),dimension(*)::values
	integer,intent(in)::values_len
	integer,intent(in),dimension(*)::componentSize
	integer,intent(in)::componentSize_len
	integer,intent(inout)::ackn

     call this%forwardVelocities_internal(&
keys,keys_len,&
offsets,offsets_len,&
flips,flips_len,&
values,values_len,&
componentSize,componentSize_len,&
ackn)
end subroutine forwardVelocities
subroutine printLBProfiles_internal(this)
     use, intrinsic :: iso_c_binding
     class(LBSolverNativeSocketDispatcher)::this
     
     call cca_cfd_lbsolver_f2c_nsd_printLBProfiles(this%reference)
end subroutine printLBProfiles_internal

subroutine printLBProfiles(this)
     use, intrinsic :: iso_c_binding
     class(LBSolverNativeSocketDispatcher)::this
     
     call this%printLBProfiles_internal()
end subroutine printLBProfiles
subroutine printLBDensity_internal(this)
     use, intrinsic :: iso_c_binding
     class(LBSolverNativeSocketDispatcher)::this
     
     call cca_cfd_lbsolver_f2c_nsd_printLBDensity(this%reference)
end subroutine printLBDensity_internal

subroutine printLBDensity(this)
     use, intrinsic :: iso_c_binding
     class(LBSolverNativeSocketDispatcher)::this
     
     call this%printLBDensity_internal()
end subroutine printLBDensity
subroutine closeLBProfiles_internal(this)
     use, intrinsic :: iso_c_binding
     class(LBSolverNativeSocketDispatcher)::this
     
     call cca_cfd_lbsolver_f2c_nsd_closeLBProfiles(this%reference)
end subroutine closeLBProfiles_internal

subroutine closeLBProfiles(this)
     use, intrinsic :: iso_c_binding
     class(LBSolverNativeSocketDispatcher)::this
     
     call this%closeLBProfiles_internal()
end subroutine closeLBProfiles
subroutine setGradients_internal(this,&
	gradients,gradients_len)
     use, intrinsic :: iso_c_binding
     class(LBSolverNativeSocketDispatcher)::this
     	real(kind=c_double),intent(in),dimension(*)::gradients
	integer(kind=c_int),intent(in)::gradients_len

     call cca_cfd_lbsolver_f2c_nsd_setGradients(this%reference,&
gradients,gradients_len)
end subroutine setGradients_internal

subroutine setGradients(this,&
	gradients,gradients_len)
     use, intrinsic :: iso_c_binding
     class(LBSolverNativeSocketDispatcher)::this
     	real(8),intent(in),dimension(*)::gradients
	integer,intent(in)::gradients_len

     call this%setGradients_internal(&
gradients,gradients_len)
end subroutine setGradients
subroutine setPressure_internal(this,&
	pressure,pressure_len)
     use, intrinsic :: iso_c_binding
     class(LBSolverNativeSocketDispatcher)::this
     	real(kind=c_double),intent(in),dimension(*)::pressure
	integer(kind=c_int),intent(in)::pressure_len

     call cca_cfd_lbsolver_f2c_nsd_setPressure(this%reference,&
pressure,pressure_len)
end subroutine setPressure_internal

subroutine setPressure(this,&
	pressure,pressure_len)
     use, intrinsic :: iso_c_binding
     class(LBSolverNativeSocketDispatcher)::this
     	real(8),intent(in),dimension(*)::pressure
	integer,intent(in)::pressure_len

     call this%setPressure_internal(&
pressure,pressure_len)
end subroutine setPressure
subroutine setVelocities_internal(this,&
	velocitiesX,velocitiesX_len,&
	velocitiesY,velocitiesY_len,&
	velocitiesZ,velocitiesZ_len)
     use, intrinsic :: iso_c_binding
     class(LBSolverNativeSocketDispatcher)::this
     	real(kind=c_double),intent(in),dimension(*)::velocitiesX
	integer(kind=c_int),intent(in)::velocitiesX_len
	real(kind=c_double),intent(in),dimension(*)::velocitiesY
	integer(kind=c_int),intent(in)::velocitiesY_len
	real(kind=c_double),intent(in),dimension(*)::velocitiesZ
	integer(kind=c_int),intent(in)::velocitiesZ_len

     call cca_cfd_lbsolver_f2c_nsd_setVelocities(this%reference,&
velocitiesX,velocitiesX_len,&
velocitiesY,velocitiesY_len,&
velocitiesZ,velocitiesZ_len)
end subroutine setVelocities_internal

subroutine setVelocities(this,&
	velocitiesX,velocitiesX_len,&
	velocitiesY,velocitiesY_len,&
	velocitiesZ,velocitiesZ_len)
     use, intrinsic :: iso_c_binding
     class(LBSolverNativeSocketDispatcher)::this
     	real(8),intent(in),dimension(*)::velocitiesX
	integer,intent(in)::velocitiesX_len
	real(8),intent(in),dimension(*)::velocitiesY
	integer,intent(in)::velocitiesY_len
	real(8),intent(in),dimension(*)::velocitiesZ
	integer,intent(in)::velocitiesZ_len

     call this%setVelocities_internal(&
velocitiesX,velocitiesX_len,&
velocitiesY,velocitiesY_len,&
velocitiesZ,velocitiesZ_len)
end subroutine setVelocities
subroutine solveOneTimestep_internal(this)
     use, intrinsic :: iso_c_binding
     class(LBSolverNativeSocketDispatcher)::this
     
     call cca_cfd_lbsolver_f2c_nsd_solveOneTimestep(this%reference)
end subroutine solveOneTimestep_internal

subroutine solveOneTimestep(this)
     use, intrinsic :: iso_c_binding
     class(LBSolverNativeSocketDispatcher)::this
     
     call this%solveOneTimestep_internal()
end subroutine solveOneTimestep
subroutine solve_internal(this)
     use, intrinsic :: iso_c_binding
     class(LBSolverNativeSocketDispatcher)::this
     
     call cca_cfd_lbsolver_f2c_nsd_solve(this%reference)
end subroutine solve_internal

subroutine solve(this)
     use, intrinsic :: iso_c_binding
     class(LBSolverNativeSocketDispatcher)::this
     
     call this%solve_internal()
end subroutine solve
subroutine setupCommForNSRegion_internal(this,&
	startOfRegion,startOfRegion_len,&
	endOfRegion,endOfRegion_len,&
	commids,commids_len)
     use, intrinsic :: iso_c_binding
     class(LBSolverNativeSocketDispatcher)::this
     	integer(kind=c_int),intent(in),dimension(*)::startOfRegion
	integer(kind=c_int),intent(in)::startOfRegion_len
	integer(kind=c_int),intent(in),dimension(*)::endOfRegion
	integer(kind=c_int),intent(in)::endOfRegion_len
	integer(kind=c_int),intent(in)::commids_len
	type(c_ptr),dimension(*),intent(in)::commids

     call cca_cfd_lbsolver_f2c_nsd_setupCommForNSRegion(this%reference,&
startOfRegion,startOfRegion_len,&
endOfRegion,endOfRegion_len,&
commids,commids_len)
end subroutine setupCommForNSRegion_internal

subroutine setupCommForNSRegion(this,&
	startOfRegion,startOfRegion_len,&
	endOfRegion,endOfRegion_len,&
	commids,commids_len)
     use, intrinsic :: iso_c_binding
     class(LBSolverNativeSocketDispatcher)::this
     	integer,intent(in),dimension(*)::startOfRegion
	integer,intent(in)::startOfRegion_len
	integer,intent(in),dimension(*)::endOfRegion
	integer,intent(in)::endOfRegion_len
	character(*),intent(in),dimension(*)::commids
	integer,intent(in)::commids_len
	type(c_ptr),dimension(commids_len) :: commidsPtrArray
	integer::commids_ns
	character(255), dimension(commids_len), target :: commidsFSArray
	do commids_ns = 1, commids_len
		commidsFSArray(commids_ns) = commids(commids_ns)// C_NULL_CHAR
		commidsPtrArray(commids_ns) = C_LOC(commidsFSArray(commids_ns))
	end do

     call this%setupCommForNSRegion_internal(&
startOfRegion,startOfRegion_len,&
endOfRegion,endOfRegion_len,&
commidsPtrArray,commids_len)
end subroutine setupCommForNSRegion
subroutine setup_internal(this,&
	inputScenario)
     use, intrinsic :: iso_c_binding
     class(LBSolverNativeSocketDispatcher)::this
     	character(kind=c_char),dimension(*),intent(in)::inputScenario

     call cca_cfd_lbsolver_f2c_nsd_setup(this%reference,&
inputScenario)
end subroutine setup_internal

subroutine setup(this,&
	inputScenario)
     use, intrinsic :: iso_c_binding
     class(LBSolverNativeSocketDispatcher)::this
     	character(*),intent(in)::inputScenario

     call this%setup_internal(&
inputScenario//c_null_char)
end subroutine setup

end module  cca_cfd_LBSolverFNativeSocketDispatcher
