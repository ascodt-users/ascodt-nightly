module examples_heat_StencilFNativeSocketDispatcher
use, intrinsic :: iso_c_binding
implicit none


type, public :: StencilNativeSocketDispatcher
     integer(kind=c_long_long )::reference
     contains
     procedure,public::createClientDispatcherInstanceForC
     procedure,public::createClientDispatcherInstance
     procedure,public::destroyDispatcherInstance
     
     
     	procedure,public::getStencil
	procedure,private::getStencil_internal

end type StencilNativeSocketDispatcher
contains
subroutine createClientDispatcherInstanceForC(this,host,port,buffer_size)
    class(StencilNativeSocketDispatcher)::this
    character(kind=c_char),dimension(*)::host
    integer(kind=c_int)::port
    integer(kind=c_int)::buffer_size
    this%reference=0
    call examples_heat_stencil_f2c_nsd_create_client_instance(this%reference,host,port,buffer_size)
    
    

end subroutine createClientDispatcherInstanceForC

subroutine createClientDispatcherInstance(this,host,port,buffer_size)
    class(StencilNativeSocketDispatcher)::this
    character(*)::host
    integer::port
    integer::buffer_size
    call this%createClientDispatcherInstanceForC(host//c_null_char,port,buffer_size)
    
    

end subroutine createClientDispatcherInstance

subroutine destroyDispatcherInstance(this)
     class(StencilNativeSocketDispatcher)::this
     call examples_heat_stencil_f2c_nsd_destroy_instance(this%reference)

end subroutine destroyDispatcherInstance

subroutine getStencil_internal(this,&
	stencil,stencil_len)
     use, intrinsic :: iso_c_binding
     class(StencilNativeSocketDispatcher)::this
     	real(kind=c_double),intent(inout),dimension(*)::stencil
	integer(kind=c_int),intent(in)::stencil_len

     call examples_heat_stencil_f2c_nsd_getStencil(this%reference,&
stencil,stencil_len)
end subroutine getStencil_internal

subroutine getStencil(this,&
	stencil,stencil_len)
     use, intrinsic :: iso_c_binding
     class(StencilNativeSocketDispatcher)::this
     	real(8),intent(inout),dimension(*)::stencil
	integer,intent(in)::stencil_len

     call this%getStencil_internal(&
stencil,stencil_len)
end subroutine getStencil

end module  examples_heat_StencilFNativeSocketDispatcher
