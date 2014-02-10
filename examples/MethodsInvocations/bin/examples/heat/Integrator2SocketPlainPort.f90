module examples_heat_Integrator2SocketPort 
use, intrinsic :: iso_c_binding
implicit none


type, public :: Integrator2SocketPort
     
     integer(kind=c_long_long )::reference
     contains
     procedure,public::create_port_client_instance
     procedure,public::create_port_client_instance_for_c
     procedure,public::destroyPortInstance
     procedure,public::step

end type Integrator2SocketPort
contains

subroutine create_port_client_instance_for_c(this,host,port,buffer_size)
    class(Integrator2SocketPort)::this
    integer(kind=c_int)::port
    character(kind=c_char),dimension(*)::host
    integer(kind=c_int)::buffer_size
    call examples_heat_integratorc2socket_plain_port_create_client_instance(this%reference,host,port,buffer_size)
    

end subroutine create_port_client_instance_for_c

subroutine create_port_client_instance(this,host,port,buffer_size)
    class(Integrator2SocketPort)::this
    integer::port
    character(*)::host
    integer::buffer_size
    call this%create_port_client_instance_for_c(host//c_null_char,port,buffer_size)
    

end subroutine create_port_client_instance



subroutine destroyPortInstance(this)
     class(Integrator2SocketPort)::this
     call examples_heat_integratorc2socket_plain_port_destroy_instance(this%reference)

end subroutine destroyPortInstance

subroutine step(this,&
	dims,dims_len,&
	dt,&
	rhs,rhs_len,&
	stencil,stencil_len,&
	dof)
     use, intrinsic :: iso_c_binding
     class(Integrator2SocketPort)::this
     	integer,intent(in),dimension(*)::dims
	integer,intent(in)::dims_len
	real(8),intent(in)::dt
	real(8),intent(in),dimension(*)::rhs
	integer,intent(in)::rhs_len
	real(8),intent(in),dimension(*)::stencil
	integer,intent(in)::stencil_len
	character(len=1),dimension(:),intent(in) ::dof

     
     call examples_heat_integratorc2socket_plain_port_step(this%reference,&
dims,dims_len,&
dt,&
rhs,rhs_len,&
stencil,stencil_len,&
)
end subroutine step

end module  examples_heat_Integrator2SocketPort
