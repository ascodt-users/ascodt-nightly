module examples_heat_Stencil2SocketPort 
use, intrinsic :: iso_c_binding
implicit none


type, public :: Stencil2SocketPort
     
     integer(kind=c_long_long )::reference
     contains
     procedure,public::create_port_client_instance
     procedure,public::create_port_client_instance_for_c
     procedure,public::destroyPortInstance
     procedure,public::getStencil

end type Stencil2SocketPort
contains

subroutine create_port_client_instance_for_c(this,host,port,buffer_size)
    class(Stencil2SocketPort)::this
    integer(kind=c_int)::port
    character(kind=c_char),dimension(*)::host
    integer(kind=c_int)::buffer_size
    call examples_heat_stencilc2socket_plain_port_create_client_instance(this%reference,host,port,buffer_size)
    

end subroutine create_port_client_instance_for_c

subroutine create_port_client_instance(this,host,port,buffer_size)
    class(Stencil2SocketPort)::this
    integer::port
    character(*)::host
    integer::buffer_size
    call this%create_port_client_instance_for_c(host//c_null_char,port,buffer_size)
    

end subroutine create_port_client_instance



subroutine destroyPortInstance(this)
     class(Stencil2SocketPort)::this
     call examples_heat_stencilc2socket_plain_port_destroy_instance(this%reference)

end subroutine destroyPortInstance

subroutine getStencil(this,&
	stencil,stencil_len)
     use, intrinsic :: iso_c_binding
     class(Stencil2SocketPort)::this
     	real(8),intent(inout),dimension(*)::stencil
	integer,intent(in)::stencil_len

     
     call examples_heat_stencilc2socket_plain_port_getStencil(this%reference,&
stencil,stencil_len)
end subroutine getStencil

end module  examples_heat_Stencil2SocketPort
