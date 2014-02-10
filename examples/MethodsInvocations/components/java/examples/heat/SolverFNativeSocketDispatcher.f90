module examples_heat_SolverFNativeSocketDispatcher
use, intrinsic :: iso_c_binding
implicit none


type, public :: SolverNativeSocketDispatcher
     integer(kind=c_long_long )::reference
     contains
     procedure,public::createClientDispatcherInstanceForC
     procedure,public::createClientDispatcherInstance
     procedure,public::destroyDispatcherInstance
     
     
     	procedure,public::setup
	procedure,private::setup_internal
	procedure,public::solve
	procedure,private::solve_internal

end type SolverNativeSocketDispatcher
contains
subroutine createClientDispatcherInstanceForC(this,host,port,buffer_size)
    class(SolverNativeSocketDispatcher)::this
    character(kind=c_char),dimension(*)::host
    integer(kind=c_int)::port
    integer(kind=c_int)::buffer_size
    this%reference=0
    call examples_heat_solver_f2c_nsd_create_client_instance(this%reference,host,port,buffer_size)
    
    

end subroutine createClientDispatcherInstanceForC

subroutine createClientDispatcherInstance(this,host,port,buffer_size)
    class(SolverNativeSocketDispatcher)::this
    character(*)::host
    integer::port
    integer::buffer_size
    call this%createClientDispatcherInstanceForC(host//c_null_char,port,buffer_size)
    
    

end subroutine createClientDispatcherInstance

subroutine destroyDispatcherInstance(this)
     class(SolverNativeSocketDispatcher)::this
     call examples_heat_solver_f2c_nsd_destroy_instance(this%reference)

end subroutine destroyDispatcherInstance

subroutine solve_internal(this,&
	dims,dims_len,&
	stencil,stencil_len,&
	rhs,rhs_len,&
	dof_handle)
     use, intrinsic :: iso_c_binding
     class(SolverNativeSocketDispatcher)::this
     	integer(kind=c_int),intent(in),dimension(*)::dims
	integer(kind=c_int),intent(in)::dims_len
	real(kind=c_double),intent(in),dimension(*)::stencil
	integer(kind=c_int),intent(in)::stencil_len
	real(kind=c_double),intent(in),dimension(*)::rhs
	integer(kind=c_int),intent(in)::rhs_len

     call examples_heat_solver_f2c_nsd_solve(this%reference,&
dims,dims_len,&
stencil,stencil_len,&
rhs,rhs_len,&
)
end subroutine solve_internal

subroutine solve(this,&
	dims,dims_len,&
	stencil,stencil_len,&
	rhs,rhs_len,&
	dof_handle)
     use, intrinsic :: iso_c_binding
     class(SolverNativeSocketDispatcher)::this
     	integer,intent(in),dimension(*)::dims
	integer,intent(in)::dims_len
	real(8),intent(in),dimension(*)::stencil
	integer,intent(in)::stencil_len
	real(8),intent(in),dimension(*)::rhs
	integer,intent(in)::rhs_len
	character(len=1),dimension(:),intent(in) ::dof_handle

     call this%solve_internal(&
dims,dims_len,&
stencil,stencil_len,&
rhs,rhs_len,&
)
end subroutine solve
subroutine setup_internal(this,&
	precision,&
	iterations)
     use, intrinsic :: iso_c_binding
     class(SolverNativeSocketDispatcher)::this
     	real(kind=c_double),intent(in)::precision
	integer(kind=c_int),intent(in)::iterations

     call examples_heat_solver_f2c_nsd_setup(this%reference,&
precision,&
iterations)
end subroutine setup_internal

subroutine setup(this,&
	precision,&
	iterations)
     use, intrinsic :: iso_c_binding
     class(SolverNativeSocketDispatcher)::this
     	real(8),intent(in)::precision
	integer,intent(in)::iterations

     call this%setup_internal(&
precision,&
iterations)
end subroutine setup

end module  examples_heat_SolverFNativeSocketDispatcher
