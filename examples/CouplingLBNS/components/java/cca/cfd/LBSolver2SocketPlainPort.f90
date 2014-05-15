module cca_cfd_LBSolver2SocketPort 
use, intrinsic :: iso_c_binding
implicit none


type, public :: LBSolver2SocketPort
     
     integer(kind=c_long_long )::reference
     contains
     procedure,public::create_port_client_instance
     procedure,public::create_port_client_instance_for_c
     procedure,public::destroyPortInstance
     procedure,public::setup
procedure,public::setupCommForNSRegion
procedure,public::solve
procedure,public::solveOneTimestep
procedure,public::setVelocities
procedure,public::setPressure
procedure,public::setGradients
procedure,public::closeLBProfiles
procedure,public::printLBDensity
procedure,public::printLBProfiles
procedure,public::forwardVelocities
procedure,public::forwardPressure
procedure,public::syncr
procedure,public::plot

end type LBSolver2SocketPort
contains

subroutine create_port_client_instance_for_c(this,host,port,buffer_size)
    class(LBSolver2SocketPort)::this
    integer(kind=c_int)::port
    character(kind=c_char),dimension(*)::host
    integer(kind=c_int)::buffer_size
    call cca_cfd_lbsolverc2socket_plain_port_create_client_instance(this%reference,host,port,buffer_size)
    

end subroutine create_port_client_instance_for_c

subroutine create_port_client_instance(this,host,port,buffer_size)
    class(LBSolver2SocketPort)::this
    integer::port
    character(*)::host
    integer::buffer_size
    call this%create_port_client_instance_for_c(host//c_null_char,port,buffer_size)
    

end subroutine create_port_client_instance



subroutine destroyPortInstance(this)
     class(LBSolver2SocketPort)::this
     call cca_cfd_lbsolverc2socket_plain_port_destroy_instance(this%reference)

end subroutine destroyPortInstance

subroutine plot(this)
     use, intrinsic :: iso_c_binding
     class(LBSolver2SocketPort)::this
     
     
     call cca_cfd_lbsolverc2socket_plain_port_plot(this%reference)
end subroutine plot
subroutine syncr(this,&
	value)
     use, intrinsic :: iso_c_binding
     class(LBSolver2SocketPort)::this
     	integer,intent(inout)::value

     
     call cca_cfd_lbsolverc2socket_plain_port_syncr(this%reference,&
value)
end subroutine syncr
subroutine forwardPressure(this,&
	keys,keys_len,&
	offsets,offsets_len,&
	flips,flips_len,&
	values,values_len,&
	ackn)
     use, intrinsic :: iso_c_binding
     class(LBSolver2SocketPort)::this
     	integer,intent(in),dimension(*)::keys
	integer,intent(in)::keys_len
	integer,intent(in),dimension(*)::offsets
	integer,intent(in)::offsets_len
	integer,intent(in),dimension(*)::flips
	integer,intent(in)::flips_len
	real(8),intent(in),dimension(*)::values
	integer,intent(in)::values_len
	integer,intent(inout)::ackn

     
     call cca_cfd_lbsolverc2socket_plain_port_forwardPressure(this%reference,&
keys,keys_len,&
offsets,offsets_len,&
flips,flips_len,&
values,values_len,&
ackn)
end subroutine forwardPressure
subroutine forwardVelocities(this,&
	keys,keys_len,&
	offsets,offsets_len,&
	flips,flips_len,&
	values,values_len,&
	ackn)
     use, intrinsic :: iso_c_binding
     class(LBSolver2SocketPort)::this
     	integer,intent(in),dimension(*)::keys
	integer,intent(in)::keys_len
	integer,intent(in),dimension(*)::offsets
	integer,intent(in)::offsets_len
	integer,intent(in),dimension(*)::flips
	integer,intent(in)::flips_len
	real(8),intent(in),dimension(*)::values
	integer,intent(in)::values_len
	integer,intent(inout)::ackn

     
     call cca_cfd_lbsolverc2socket_plain_port_forwardVelocities(this%reference,&
keys,keys_len,&
offsets,offsets_len,&
flips,flips_len,&
values,values_len,&
ackn)
end subroutine forwardVelocities
subroutine printLBProfiles(this)
     use, intrinsic :: iso_c_binding
     class(LBSolver2SocketPort)::this
     
     
     call cca_cfd_lbsolverc2socket_plain_port_printLBProfiles(this%reference)
end subroutine printLBProfiles
subroutine printLBDensity(this)
     use, intrinsic :: iso_c_binding
     class(LBSolver2SocketPort)::this
     
     
     call cca_cfd_lbsolverc2socket_plain_port_printLBDensity(this%reference)
end subroutine printLBDensity
subroutine closeLBProfiles(this)
     use, intrinsic :: iso_c_binding
     class(LBSolver2SocketPort)::this
     
     
     call cca_cfd_lbsolverc2socket_plain_port_closeLBProfiles(this%reference)
end subroutine closeLBProfiles
subroutine setGradients(this,&
	gradients,gradients_len)
     use, intrinsic :: iso_c_binding
     class(LBSolver2SocketPort)::this
     	real(8),intent(in),dimension(*)::gradients
	integer,intent(in)::gradients_len

     
     call cca_cfd_lbsolverc2socket_plain_port_setGradients(this%reference,&
gradients,gradients_len)
end subroutine setGradients
subroutine setPressure(this,&
	pressure,pressure_len)
     use, intrinsic :: iso_c_binding
     class(LBSolver2SocketPort)::this
     	real(8),intent(in),dimension(*)::pressure
	integer,intent(in)::pressure_len

     
     call cca_cfd_lbsolverc2socket_plain_port_setPressure(this%reference,&
pressure,pressure_len)
end subroutine setPressure
subroutine setVelocities(this,&
	velocitiesX,velocitiesX_len,&
	velocitiesY,velocitiesY_len,&
	velocitiesZ,velocitiesZ_len)
     use, intrinsic :: iso_c_binding
     class(LBSolver2SocketPort)::this
     	real(8),intent(in),dimension(*)::velocitiesX
	integer,intent(in)::velocitiesX_len
	real(8),intent(in),dimension(*)::velocitiesY
	integer,intent(in)::velocitiesY_len
	real(8),intent(in),dimension(*)::velocitiesZ
	integer,intent(in)::velocitiesZ_len

     
     call cca_cfd_lbsolverc2socket_plain_port_setVelocities(this%reference,&
velocitiesX,velocitiesX_len,&
velocitiesY,velocitiesY_len,&
velocitiesZ,velocitiesZ_len)
end subroutine setVelocities
subroutine solveOneTimestep(this)
     use, intrinsic :: iso_c_binding
     class(LBSolver2SocketPort)::this
     
     
     call cca_cfd_lbsolverc2socket_plain_port_solveOneTimestep(this%reference)
end subroutine solveOneTimestep
subroutine solve(this)
     use, intrinsic :: iso_c_binding
     class(LBSolver2SocketPort)::this
     
     
     call cca_cfd_lbsolverc2socket_plain_port_solve(this%reference)
end subroutine solve
subroutine setupCommForNSRegion(this,&
	startOfRegion,startOfRegion_len,&
	endOfRegion,endOfRegion_len,&
	commids,commids_len)
     use, intrinsic :: iso_c_binding
     class(LBSolver2SocketPort)::this
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

     
     call cca_cfd_lbsolverc2socket_plain_port_setupCommForNSRegion(this%reference,&
startOfRegion,startOfRegion_len,&
endOfRegion,endOfRegion_len,&
commids,commids_len)
end subroutine setupCommForNSRegion
subroutine setup(this,&
	inputScenario)
     use, intrinsic :: iso_c_binding
     class(LBSolver2SocketPort)::this
     	character(*),intent(in)::inputScenario

     
     call cca_cfd_lbsolverc2socket_plain_port_setup(this%reference,&
inputScenario)
end subroutine setup

end module  cca_cfd_LBSolver2SocketPort
