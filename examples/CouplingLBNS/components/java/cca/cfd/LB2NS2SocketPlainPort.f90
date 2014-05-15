module cca_cfd_LB2NS2SocketPort 
use, intrinsic :: iso_c_binding
implicit none


type, public :: LB2NS2SocketPort
     
     integer(kind=c_long_long )::reference
     contains
     procedure,public::create_port_client_instance
     procedure,public::create_port_client_instance_for_c
     procedure,public::destroyPortInstance
     procedure,public::iterateBoundary
procedure,public::iterateInner
procedure,public::retrieveTimestep
procedure,public::retrieveVelocitiesSize
procedure,public::retrieveVelocitiesCopy

end type LB2NS2SocketPort
contains

subroutine create_port_client_instance_for_c(this,host,port,buffer_size)
    class(LB2NS2SocketPort)::this
    integer(kind=c_int)::port
    character(kind=c_char),dimension(*)::host
    integer(kind=c_int)::buffer_size
    call cca_cfd_lb2nsc2socket_plain_port_create_client_instance(this%reference,host,port,buffer_size)
    

end subroutine create_port_client_instance_for_c

subroutine create_port_client_instance(this,host,port,buffer_size)
    class(LB2NS2SocketPort)::this
    integer::port
    character(*)::host
    integer::buffer_size
    call this%create_port_client_instance_for_c(host//c_null_char,port,buffer_size)
    

end subroutine create_port_client_instance



subroutine destroyPortInstance(this)
     class(LB2NS2SocketPort)::this
     call cca_cfd_lb2nsc2socket_plain_port_destroy_instance(this%reference)

end subroutine destroyPortInstance

subroutine retrieveVelocitiesCopy(this,&
	velocityX,velocityX_len,&
	velocityY,velocityY_len,&
	velocityZ,velocityZ_len)
     use, intrinsic :: iso_c_binding
     class(LB2NS2SocketPort)::this
     	real(8),intent(inout),dimension(*)::velocityX
	integer,intent(in)::velocityX_len
	real(8),intent(inout),dimension(*)::velocityY
	integer,intent(in)::velocityY_len
	real(8),intent(inout),dimension(*)::velocityZ
	integer,intent(in)::velocityZ_len

     
     call cca_cfd_lb2nsc2socket_plain_port_retrieveVelocitiesCopy(this%reference,&
velocityX,velocityX_len,&
velocityY,velocityY_len,&
velocityZ,velocityZ_len)
end subroutine retrieveVelocitiesCopy
subroutine retrieveVelocitiesSize(this,&
	memoryX,&
	memoryY,&
	memoryZ)
     use, intrinsic :: iso_c_binding
     class(LB2NS2SocketPort)::this
     	integer,intent(inout)::memoryX
	integer,intent(inout)::memoryY
	integer,intent(inout)::memoryZ

     
     call cca_cfd_lb2nsc2socket_plain_port_retrieveVelocitiesSize(this%reference,&
memoryX,&
memoryY,&
memoryZ)
end subroutine retrieveVelocitiesSize
subroutine retrieveTimestep(this,&
	dt)
     use, intrinsic :: iso_c_binding
     class(LB2NS2SocketPort)::this
     	real(8),intent(inout)::dt

     
     call cca_cfd_lb2nsc2socket_plain_port_retrieveTimestep(this%reference,&
dt)
end subroutine retrieveTimestep
subroutine iterateInner(this)
     use, intrinsic :: iso_c_binding
     class(LB2NS2SocketPort)::this
     
     
     call cca_cfd_lb2nsc2socket_plain_port_iterateInner(this%reference)
end subroutine iterateInner
subroutine iterateBoundary(this)
     use, intrinsic :: iso_c_binding
     class(LB2NS2SocketPort)::this
     
     
     call cca_cfd_lb2nsc2socket_plain_port_iterateBoundary(this%reference)
end subroutine iterateBoundary

end module  cca_cfd_LB2NS2SocketPort
