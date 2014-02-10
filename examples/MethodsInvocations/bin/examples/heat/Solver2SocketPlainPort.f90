module examples_heat_Solver2SocketPort 
use, intrinsic :: iso_c_binding
implicit none


type, public :: Solver2SocketPort
     
     integer(kind=c_long_long )::reference
     contains
     procedure,public::create_port_client_instance
     procedure,public::create_port_client_instance_for_c
     procedure,public::destroyPortInstance
     procedure,public::setup
procedure,public::solve

end type Solver2SocketPort
contains

subroutine create_port_client_instance_for_c(this,host,port,buffer_size)
    class(Solver2SocketPort)::this
    integer(kind=c_int)::port
    character(kind=c_char),dimension(*)::host
    integer(kind=c_int)::buffer_size
    call examples_heat_solverc2socket_plain_port_create_client_instance(this%reference,host,port,buffer_size)
    

end subroutine create_port_client_instance_for_c

subroutine create_port_client_instance(this,host,port,buffer_size)
    class(Solver2SocketPort)::this
    integer::port
    character(*)::host
    integer::buffer_size
    call this%create_port_client_instance_for_c(host//c_null_char,port,buffer_size)
    

end subroutine create_port_client_instance



subroutine destroyPortInstance(this)
     class(Solver2SocketPort)::this
     call examples_heat_solverc2socket_plain_port_destroy_instance(this%reference)

end subroutine destroyPortInstance

subroutine solve(this,&
	dims,dims_len,&
	stencil,stencil_len,&
	rhs,rhs_len,&
	dof_handle)
     use, intrinsic :: iso_c_binding
     class(Solver2SocketPort)::this
     	integer,intent(in),dimension(*)::dims
	integer,intent(in)::dims_len
	real(8),intent(in),dimension(*)::stencil
	integer,intent(in)::stencil_len
	real(8),intent(in),dimension(*)::rhs
	integer,intent(in)::rhs_len
	character(len=1),dimension(:),intent(in) ::dof_handle

     
     call examples_heat_solverc2socket_plain_port_solve(this%reference,&
dims,dims_len,&
stencil,stencil_len,&
rhs,rhs_len,&
)
end subroutine solve
subroutine setup(this,&
	precision,&
	iterations)
     use, intrinsic :: iso_c_binding
     class(Solver2SocketPort)::this
     	real(8),intent(in)::precision
	integer,intent(in)::iterations

     
     call examples_heat_solverc2socket_plain_port_setup(this%reference,&
precision,&
iterations)
end subroutine setup

end module  examples_heat_Solver2SocketPort
