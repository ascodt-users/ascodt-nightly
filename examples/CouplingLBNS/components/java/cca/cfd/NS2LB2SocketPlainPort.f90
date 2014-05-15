module cca_cfd_NS2LB2SocketPort 
use, intrinsic :: iso_c_binding
implicit none


type, public :: NS2LB2SocketPort
     
     integer(kind=c_long_long )::reference
     contains
     procedure,public::create_port_client_instance
     procedure,public::create_port_client_instance_for_c
     procedure,public::destroyPortInstance
     procedure,public::iterate
procedure,public::retrieveTimestep
procedure,public::retrieveVelocitiesSize
procedure,public::retrieveVelocitiesCopy
procedure,public::retrieveJacobianCopy
procedure,public::retrievePressureCopy

end type NS2LB2SocketPort
contains

subroutine create_port_client_instance_for_c(this,host,port,buffer_size)
    class(NS2LB2SocketPort)::this
    integer(kind=c_int)::port
    character(kind=c_char),dimension(*)::host
    integer(kind=c_int)::buffer_size
    call cca_cfd_ns2lbc2socket_plain_port_create_client_instance(this%reference,host,port,buffer_size)
    

end subroutine create_port_client_instance_for_c

subroutine create_port_client_instance(this,host,port,buffer_size)
    class(NS2LB2SocketPort)::this
    integer::port
    character(*)::host
    integer::buffer_size
    call this%create_port_client_instance_for_c(host//c_null_char,port,buffer_size)
    

end subroutine create_port_client_instance



subroutine destroyPortInstance(this)
     class(NS2LB2SocketPort)::this
     call cca_cfd_ns2lbc2socket_plain_port_destroy_instance(this%reference)

end subroutine destroyPortInstance

subroutine retrievePressureCopy(this,&
	pressure,pressure_len)
     use, intrinsic :: iso_c_binding
     class(NS2LB2SocketPort)::this
     	real(8),intent(inout),dimension(*)::pressure
	integer,intent(in)::pressure_len

     
     call cca_cfd_ns2lbc2socket_plain_port_retrievePressureCopy(this%reference,&
pressure,pressure_len)
end subroutine retrievePressureCopy
subroutine retrieveJacobianCopy(this,&
	jacobian,jacobian_len)
     use, intrinsic :: iso_c_binding
     class(NS2LB2SocketPort)::this
     	real(8),intent(inout),dimension(*)::jacobian
	integer,intent(in)::jacobian_len

     
     call cca_cfd_ns2lbc2socket_plain_port_retrieveJacobianCopy(this%reference,&
jacobian,jacobian_len)
end subroutine retrieveJacobianCopy
subroutine retrieveVelocitiesCopy(this,&
	velocityX,velocityX_len,&
	velocityY,velocityY_len,&
	velocityZ,velocityZ_len)
     use, intrinsic :: iso_c_binding
     class(NS2LB2SocketPort)::this
     	real(8),intent(inout),dimension(*)::velocityX
	integer,intent(in)::velocityX_len
	real(8),intent(inout),dimension(*)::velocityY
	integer,intent(in)::velocityY_len
	real(8),intent(inout),dimension(*)::velocityZ
	integer,intent(in)::velocityZ_len

     
     call cca_cfd_ns2lbc2socket_plain_port_retrieveVelocitiesCopy(this%reference,&
velocityX,velocityX_len,&
velocityY,velocityY_len,&
velocityZ,velocityZ_len)
end subroutine retrieveVelocitiesCopy
subroutine retrieveVelocitiesSize(this,&
	memory)
     use, intrinsic :: iso_c_binding
     class(NS2LB2SocketPort)::this
     	integer,intent(inout)::memory

     
     call cca_cfd_ns2lbc2socket_plain_port_retrieveVelocitiesSize(this%reference,&
memory)
end subroutine retrieveVelocitiesSize
subroutine retrieveTimestep(this,&
	timestep)
     use, intrinsic :: iso_c_binding
     class(NS2LB2SocketPort)::this
     	real(8),intent(inout)::timestep

     
     call cca_cfd_ns2lbc2socket_plain_port_retrieveTimestep(this%reference,&
timestep)
end subroutine retrieveTimestep
subroutine iterate(this)
     use, intrinsic :: iso_c_binding
     class(NS2LB2SocketPort)::this
     
     
     call cca_cfd_ns2lbc2socket_plain_port_iterate(this%reference)
end subroutine iterate

end module  cca_cfd_NS2LB2SocketPort
