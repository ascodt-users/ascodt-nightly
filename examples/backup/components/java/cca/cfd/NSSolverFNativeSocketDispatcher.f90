module cca_cfd_NSSolverFNativeSocketDispatcher
use, intrinsic :: iso_c_binding
implicit none


type, public :: NSSolverNativeSocketDispatcher
     integer(kind=c_long_long )::reference
     contains
     procedure,public::createClientDispatcherInstanceForC
     procedure,public::createClientDispatcherInstance
     procedure,public::destroyDispatcherInstance
     
     
     	procedure,public::setup
	procedure,private::setup_internal
	procedure,public::setupCommForLBRegion
	procedure,private::setupCommForLBRegion_internal
	procedure,public::solve
	procedure,private::solve_internal
	procedure,public::solveOneTimestepPhaseOne
	procedure,private::solveOneTimestepPhaseOne_internal
	procedure,public::solveOneTimestepPhaseTwo
	procedure,private::solveOneTimestepPhaseTwo_internal
	procedure,public::setVelocities
	procedure,private::setVelocities_internal
	procedure,public::printNSPressure
	procedure,private::printNSPressure_internal
	procedure,public::printNSProfiles
	procedure,private::printNSProfiles_internal
	procedure,public::closeNSProfiles
	procedure,private::closeNSProfiles_internal
	procedure,public::iterateBoundary
	procedure,private::iterateBoundary_internal
	procedure,public::iterateInner
	procedure,private::iterateInner_internal
	procedure,public::forwardVelocities
	procedure,private::forwardVelocities_internal
	procedure,public::plot
	procedure,private::plot_internal
	procedure,public::syncr
	procedure,private::syncr_internal

end type NSSolverNativeSocketDispatcher
contains
subroutine createClientDispatcherInstanceForC(this,host,port,buffer_size)
    class(NSSolverNativeSocketDispatcher)::this
    character(kind=c_char),dimension(*)::host
    integer(kind=c_int)::port
    integer(kind=c_int)::buffer_size
    this%reference=0
    call cca_cfd_nssolver_f2c_nsd_create_client_instance(this%reference,host,port,buffer_size)
    
    

end subroutine createClientDispatcherInstanceForC

subroutine createClientDispatcherInstance(this,host,port,buffer_size)
    class(NSSolverNativeSocketDispatcher)::this
    character(*)::host
    integer::port
    integer::buffer_size
    call this%createClientDispatcherInstanceForC(host//c_null_char,port,buffer_size)
    
    

end subroutine createClientDispatcherInstance

subroutine destroyDispatcherInstance(this)
     class(NSSolverNativeSocketDispatcher)::this
     call cca_cfd_nssolver_f2c_nsd_destroy_instance(this%reference)

end subroutine destroyDispatcherInstance

subroutine syncr_internal(this,&
	value)
     use, intrinsic :: iso_c_binding
     class(NSSolverNativeSocketDispatcher)::this
     	integer(kind=c_int),intent(inout)::value

     call cca_cfd_nssolver_f2c_nsd_syncr(this%reference,&
value)
end subroutine syncr_internal

subroutine syncr(this,&
	value)
     use, intrinsic :: iso_c_binding
     class(NSSolverNativeSocketDispatcher)::this
     	integer,intent(inout)::value

     call this%syncr_internal(&
value)
end subroutine syncr
subroutine plot_internal(this)
     use, intrinsic :: iso_c_binding
     class(NSSolverNativeSocketDispatcher)::this
     
     call cca_cfd_nssolver_f2c_nsd_plot(this%reference)
end subroutine plot_internal

subroutine plot(this)
     use, intrinsic :: iso_c_binding
     class(NSSolverNativeSocketDispatcher)::this
     
     call this%plot_internal()
end subroutine plot
subroutine forwardVelocities_internal(this,&
	keys,keys_len,&
	offsets,offsets_len,&
	flips,flips_len,&
	values,values_len,&
	componentSize,componentSize_len,&
	ackn)
     use, intrinsic :: iso_c_binding
     class(NSSolverNativeSocketDispatcher)::this
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

     call cca_cfd_nssolver_f2c_nsd_forwardVelocities(this%reference,&
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
     class(NSSolverNativeSocketDispatcher)::this
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
subroutine iterateInner_internal(this)
     use, intrinsic :: iso_c_binding
     class(NSSolverNativeSocketDispatcher)::this
     
     call cca_cfd_nssolver_f2c_nsd_iterateInner(this%reference)
end subroutine iterateInner_internal

subroutine iterateInner(this)
     use, intrinsic :: iso_c_binding
     class(NSSolverNativeSocketDispatcher)::this
     
     call this%iterateInner_internal()
end subroutine iterateInner
subroutine iterateBoundary_internal(this)
     use, intrinsic :: iso_c_binding
     class(NSSolverNativeSocketDispatcher)::this
     
     call cca_cfd_nssolver_f2c_nsd_iterateBoundary(this%reference)
end subroutine iterateBoundary_internal

subroutine iterateBoundary(this)
     use, intrinsic :: iso_c_binding
     class(NSSolverNativeSocketDispatcher)::this
     
     call this%iterateBoundary_internal()
end subroutine iterateBoundary
subroutine closeNSProfiles_internal(this)
     use, intrinsic :: iso_c_binding
     class(NSSolverNativeSocketDispatcher)::this
     
     call cca_cfd_nssolver_f2c_nsd_closeNSProfiles(this%reference)
end subroutine closeNSProfiles_internal

subroutine closeNSProfiles(this)
     use, intrinsic :: iso_c_binding
     class(NSSolverNativeSocketDispatcher)::this
     
     call this%closeNSProfiles_internal()
end subroutine closeNSProfiles
subroutine printNSProfiles_internal(this)
     use, intrinsic :: iso_c_binding
     class(NSSolverNativeSocketDispatcher)::this
     
     call cca_cfd_nssolver_f2c_nsd_printNSProfiles(this%reference)
end subroutine printNSProfiles_internal

subroutine printNSProfiles(this)
     use, intrinsic :: iso_c_binding
     class(NSSolverNativeSocketDispatcher)::this
     
     call this%printNSProfiles_internal()
end subroutine printNSProfiles
subroutine printNSPressure_internal(this)
     use, intrinsic :: iso_c_binding
     class(NSSolverNativeSocketDispatcher)::this
     
     call cca_cfd_nssolver_f2c_nsd_printNSPressure(this%reference)
end subroutine printNSPressure_internal

subroutine printNSPressure(this)
     use, intrinsic :: iso_c_binding
     class(NSSolverNativeSocketDispatcher)::this
     
     call this%printNSPressure_internal()
end subroutine printNSPressure
subroutine setVelocities_internal(this,&
	velocitiesX,velocitiesX_len,&
	velocitiesY,velocitiesY_len,&
	velocitiesZ,velocitiesZ_len)
     use, intrinsic :: iso_c_binding
     class(NSSolverNativeSocketDispatcher)::this
     	real(kind=c_double),intent(in),dimension(*)::velocitiesX
	integer(kind=c_int),intent(in)::velocitiesX_len
	real(kind=c_double),intent(in),dimension(*)::velocitiesY
	integer(kind=c_int),intent(in)::velocitiesY_len
	real(kind=c_double),intent(in),dimension(*)::velocitiesZ
	integer(kind=c_int),intent(in)::velocitiesZ_len

     call cca_cfd_nssolver_f2c_nsd_setVelocities(this%reference,&
velocitiesX,velocitiesX_len,&
velocitiesY,velocitiesY_len,&
velocitiesZ,velocitiesZ_len)
end subroutine setVelocities_internal

subroutine setVelocities(this,&
	velocitiesX,velocitiesX_len,&
	velocitiesY,velocitiesY_len,&
	velocitiesZ,velocitiesZ_len)
     use, intrinsic :: iso_c_binding
     class(NSSolverNativeSocketDispatcher)::this
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
subroutine solveOneTimestepPhaseTwo_internal(this)
     use, intrinsic :: iso_c_binding
     class(NSSolverNativeSocketDispatcher)::this
     
     call cca_cfd_nssolver_f2c_nsd_solveOneTimestepPhaseTwo(this%reference)
end subroutine solveOneTimestepPhaseTwo_internal

subroutine solveOneTimestepPhaseTwo(this)
     use, intrinsic :: iso_c_binding
     class(NSSolverNativeSocketDispatcher)::this
     
     call this%solveOneTimestepPhaseTwo_internal()
end subroutine solveOneTimestepPhaseTwo
subroutine solveOneTimestepPhaseOne_internal(this)
     use, intrinsic :: iso_c_binding
     class(NSSolverNativeSocketDispatcher)::this
     
     call cca_cfd_nssolver_f2c_nsd_solveOneTimestepPhaseOne(this%reference)
end subroutine solveOneTimestepPhaseOne_internal

subroutine solveOneTimestepPhaseOne(this)
     use, intrinsic :: iso_c_binding
     class(NSSolverNativeSocketDispatcher)::this
     
     call this%solveOneTimestepPhaseOne_internal()
end subroutine solveOneTimestepPhaseOne
subroutine solve_internal(this)
     use, intrinsic :: iso_c_binding
     class(NSSolverNativeSocketDispatcher)::this
     
     call cca_cfd_nssolver_f2c_nsd_solve(this%reference)
end subroutine solve_internal

subroutine solve(this)
     use, intrinsic :: iso_c_binding
     class(NSSolverNativeSocketDispatcher)::this
     
     call this%solve_internal()
end subroutine solve
subroutine setupCommForLBRegion_internal(this,&
	startOfRegion,startOfRegion_len,&
	endOfRegion,endOfRegion_len,&
	commids,commids_len)
     use, intrinsic :: iso_c_binding
     class(NSSolverNativeSocketDispatcher)::this
     	integer(kind=c_int),intent(in),dimension(*)::startOfRegion
	integer(kind=c_int),intent(in)::startOfRegion_len
	integer(kind=c_int),intent(in),dimension(*)::endOfRegion
	integer(kind=c_int),intent(in)::endOfRegion_len
	integer(kind=c_int),intent(in)::commids_len
	type(c_ptr),dimension(*),intent(in)::commids

     call cca_cfd_nssolver_f2c_nsd_setupCommForLBRegion(this%reference,&
startOfRegion,startOfRegion_len,&
endOfRegion,endOfRegion_len,&
commids,commids_len)
end subroutine setupCommForLBRegion_internal

subroutine setupCommForLBRegion(this,&
	startOfRegion,startOfRegion_len,&
	endOfRegion,endOfRegion_len,&
	commids,commids_len)
     use, intrinsic :: iso_c_binding
     class(NSSolverNativeSocketDispatcher)::this
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

     call this%setupCommForLBRegion_internal(&
startOfRegion,startOfRegion_len,&
endOfRegion,endOfRegion_len,&
commidsPtrArray,commids_len)
end subroutine setupCommForLBRegion
subroutine setup_internal(this,&
	inputScenario)
     use, intrinsic :: iso_c_binding
     class(NSSolverNativeSocketDispatcher)::this
     	character(kind=c_char),dimension(*),intent(in)::inputScenario

     call cca_cfd_nssolver_f2c_nsd_setup(this%reference,&
inputScenario)
end subroutine setup_internal

subroutine setup(this,&
	inputScenario)
     use, intrinsic :: iso_c_binding
     class(NSSolverNativeSocketDispatcher)::this
     	character(*),intent(in)::inputScenario

     call this%setup_internal(&
inputScenario//c_null_char)
end subroutine setup

end module  cca_cfd_NSSolverFNativeSocketDispatcher
