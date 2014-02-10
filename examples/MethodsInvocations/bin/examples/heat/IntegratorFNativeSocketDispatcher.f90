module examples_heat_IntegratorFNativeSocketDispatcher
use, intrinsic :: iso_c_binding
implicit none


type, public :: IntegratorNativeSocketDispatcher
     integer(kind=c_long_long )::reference
     contains
     procedure,public::createClientDispatcherInstanceForC
     procedure,public::createClientDispatcherInstance
     procedure,public::destroyDispatcherInstance
     
     
     	procedure,public::step
	procedure,private::step_internal

end type IntegratorNativeSocketDispatcher
contains
subroutine createClientDispatcherInstanceForC(this,host,port,buffer_size)
    class(IntegratorNativeSocketDispatcher)::this
    character(kind=c_char),dimension(*)::host
    integer(kind=c_int)::port
    integer(kind=c_int)::buffer_size
    this%reference=0
    call examples_heat_integrator_f2c_nsd_create_client_instance(this%reference,host,port,buffer_size)
    
    

end subroutine createClientDispatcherInstanceForC

subroutine createClientDispatcherInstance(this,host,port,buffer_size)
    class(IntegratorNativeSocketDispatcher)::this
    character(*)::host
    integer::port
    integer::buffer_size
    call this%createClientDispatcherInstanceForC(host//c_null_char,port,buffer_size)
    
    

end subroutine createClientDispatcherInstance

subroutine destroyDispatcherInstance(this)
     class(IntegratorNativeSocketDispatcher)::this
     call examples_heat_integrator_f2c_nsd_destroy_instance(this%reference)

end subroutine destroyDispatcherInstance

subroutine step_internal(this,&
	dims,dims_len,&
	dt,&
	rhs,rhs_len,&
	stencil,stencil_len,&
	dof)
     use, intrinsic :: iso_c_binding
     class(IntegratorNativeSocketDispatcher)::this
     	integer(kind=c_int),intent(in),dimension(*)::dims
	integer(kind=c_int),intent(in)::dims_len
	real(kind=c_double),intent(in)::dt
	real(kind=c_double),intent(in),dimension(*)::rhs
	integer(kind=c_int),intent(in)::rhs_len
	real(kind=c_double),intent(in),dimension(*)::stencil
	integer(kind=c_int),intent(in)::stencil_len

     call examples_heat_integrator_f2c_nsd_step(this%reference,&
dims,dims_len,&
dt,&
rhs,rhs_len,&
stencil,stencil_len,&
)
end subroutine step_internal

subroutine step(this,&
	dims,dims_len,&
	dt,&
	rhs,rhs_len,&
	stencil,stencil_len,&
	dof)
     use, intrinsic :: iso_c_binding
     class(IntegratorNativeSocketDispatcher)::this
     	integer,intent(in),dimension(*)::dims
	integer,intent(in)::dims_len
	real(8),intent(in)::dt
	real(8),intent(in),dimension(*)::rhs
	integer,intent(in)::rhs_len
	real(8),intent(in),dimension(*)::stencil
	integer,intent(in)::stencil_len
	character(len=1),dimension(:),intent(in) ::dof

     call this%step_internal(&
dims,dims_len,&
dt,&
rhs,rhs_len,&
stencil,stencil_len,&
)
end subroutine step

end module  examples_heat_IntegratorFNativeSocketDispatcher
