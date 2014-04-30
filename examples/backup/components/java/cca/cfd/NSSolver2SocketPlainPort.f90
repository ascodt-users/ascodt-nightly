module cca_cfd_NSSolver2SocketPort 
use, intrinsic :: iso_c_binding
implicit none


type, public :: NSSolver2SocketPort
     
     integer(kind=c_long_long )::reference
     contains
     procedure,public::create_port_client_instance
     procedure,public::create_port_client_instance_for_c
     procedure,public::destroyPortInstance
     procedure,public::setup
procedure,public::setupCommForLBRegion
procedure,public::solve
procedure,public::solveOneTimestepPhaseOne
procedure,public::solveOneTimestepPhaseTwo
procedure,public::setVelocities
procedure,public::printNSPressure
procedure,public::printNSProfiles
procedure,public::closeNSProfiles
procedure,public::iterateBoundary
procedure,public::iterateInner
procedure,public::forwardVelocities
procedure,public::plot
procedure,public::syncr

end type NSSolver2SocketPort
contains

subroutine create_port_client_instance_for_c(this,host,port,buffer_size)
    class(NSSolver2SocketPort)::this
    integer(kind=c_int)::port
    character(kind=c_char),dimension(*)::host
    integer(kind=c_int)::buffer_size
    call cca_cfd_nssolverc2socket_plain_port_create_client_instance(this%reference,host,port,buffer_size)
    

end subroutine create_port_client_instance_for_c

subroutine create_port_client_instance(this,host,port,buffer_size)
    class(NSSolver2SocketPort)::this
    integer::port
    character(*)::host
    integer::buffer_size
    call this%create_port_client_instance_for_c(host//c_null_char,port,buffer_size)
    

end subroutine create_port_client_instance



subroutine destroyPortInstance(this)
     class(NSSolver2SocketPort)::this
     call cca_cfd_nssolverc2socket_plain_port_destroy_instance(this%reference)

end subroutine destroyPortInstance

subroutine syncr(this,&
	value)
     use, intrinsic :: iso_c_binding
     class(NSSolver2SocketPort)::this
     	integer,intent(inout)::value

     
     call cca_cfd_nssolverc2socket_plain_port_syncr(this%reference,&
value)
end subroutine syncr
subroutine plot(this)
     use, intrinsic :: iso_c_binding
     class(NSSolver2SocketPort)::this
     
     
     call cca_cfd_nssolverc2socket_plain_port_plot(this%reference)
end subroutine plot
subroutine forwardVelocities(this,&
	keys,keys_len,&
	offsets,offsets_len,&
	flips,flips_len,&
	values,values_len,&
	componentSize,componentSize_len,&
	ackn)
     use, intrinsic :: iso_c_binding
     class(NSSolver2SocketPort)::this
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

     
     call cca_cfd_nssolverc2socket_plain_port_forwardVelocities(this%reference,&
keys,keys_len,&
offsets,offsets_len,&
flips,flips_len,&
values,values_len,&
componentSize,componentSize_len,&
ackn)
end subroutine forwardVelocities
subroutine iterateInner(this)
     use, intrinsic :: iso_c_binding
     class(NSSolver2SocketPort)::this
     
     
     call cca_cfd_nssolverc2socket_plain_port_iterateInner(this%reference)
end subroutine iterateInner
subroutine iterateBoundary(this)
     use, intrinsic :: iso_c_binding
     class(NSSolver2SocketPort)::this
     
     
     call cca_cfd_nssolverc2socket_plain_port_iterateBoundary(this%reference)
end subroutine iterateBoundary
subroutine closeNSProfiles(this)
     use, intrinsic :: iso_c_binding
     class(NSSolver2SocketPort)::this
     
     
     call cca_cfd_nssolverc2socket_plain_port_closeNSProfiles(this%reference)
end subroutine closeNSProfiles
subroutine printNSProfiles(this)
     use, intrinsic :: iso_c_binding
     class(NSSolver2SocketPort)::this
     
     
     call cca_cfd_nssolverc2socket_plain_port_printNSProfiles(this%reference)
end subroutine printNSProfiles
subroutine printNSPressure(this)
     use, intrinsic :: iso_c_binding
     class(NSSolver2SocketPort)::this
     
     
     call cca_cfd_nssolverc2socket_plain_port_printNSPressure(this%reference)
end subroutine printNSPressure
subroutine setVelocities(this,&
	velocitiesX,velocitiesX_len,&
	velocitiesY,velocitiesY_len,&
	velocitiesZ,velocitiesZ_len)
     use, intrinsic :: iso_c_binding
     class(NSSolver2SocketPort)::this
     	real(8),intent(in),dimension(*)::velocitiesX
	integer,intent(in)::velocitiesX_len
	real(8),intent(in),dimension(*)::velocitiesY
	integer,intent(in)::velocitiesY_len
	real(8),intent(in),dimension(*)::velocitiesZ
	integer,intent(in)::velocitiesZ_len

     
     call cca_cfd_nssolverc2socket_plain_port_setVelocities(this%reference,&
velocitiesX,velocitiesX_len,&
velocitiesY,velocitiesY_len,&
velocitiesZ,velocitiesZ_len)
end subroutine setVelocities
subroutine solveOneTimestepPhaseTwo(this)
     use, intrinsic :: iso_c_binding
     class(NSSolver2SocketPort)::this
     
     
     call cca_cfd_nssolverc2socket_plain_port_solveOneTimestepPhaseTwo(this%reference)
end subroutine solveOneTimestepPhaseTwo
subroutine solveOneTimestepPhaseOne(this)
     use, intrinsic :: iso_c_binding
     class(NSSolver2SocketPort)::this
     
     
     call cca_cfd_nssolverc2socket_plain_port_solveOneTimestepPhaseOne(this%reference)
end subroutine solveOneTimestepPhaseOne
subroutine solve(this)
     use, intrinsic :: iso_c_binding
     class(NSSolver2SocketPort)::this
     
     
     call cca_cfd_nssolverc2socket_plain_port_solve(this%reference)
end subroutine solve
subroutine setupCommForLBRegion(this,&
	startOfRegion,startOfRegion_len,&
	endOfRegion,endOfRegion_len,&
	commids,commids_len)
     use, intrinsic :: iso_c_binding
     class(NSSolver2SocketPort)::this
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

     
     call cca_cfd_nssolverc2socket_plain_port_setupCommForLBRegion(this%reference,&
startOfRegion,startOfRegion_len,&
endOfRegion,endOfRegion_len,&
commids,commids_len)
end subroutine setupCommForLBRegion
subroutine setup(this,&
	inputScenario)
     use, intrinsic :: iso_c_binding
     class(NSSolver2SocketPort)::this
     	character(*),intent(in)::inputScenario

     
     call cca_cfd_nssolverc2socket_plain_port_setup(this%reference,&
inputScenario)
end subroutine setup

end module  cca_cfd_NSSolver2SocketPort
