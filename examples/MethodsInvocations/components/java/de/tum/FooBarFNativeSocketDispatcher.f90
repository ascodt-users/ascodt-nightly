module de_tum_FooBarFNativeSocketDispatcher
use, intrinsic :: iso_c_binding
implicit none


type, public :: FooBarNativeSocketDispatcher
     integer(kind=c_long_long )::reference
     contains
     procedure,public::createClientDispatcherInstanceForC
     procedure,public::createClientDispatcherInstance
     procedure,public::destroyDispatcherInstance
     
     
     	procedure,public::foo
	procedure,private::foo_internal
	procedure,public::bar
	procedure,private::bar_internal
	procedure,public::reset
	procedure,private::reset_internal

end type FooBarNativeSocketDispatcher
contains
subroutine createClientDispatcherInstanceForC(this,host,port,buffer_size)
    class(FooBarNativeSocketDispatcher)::this
    character(kind=c_char),dimension(*)::host
    integer(kind=c_int)::port
    integer(kind=c_int)::buffer_size
    this%reference=0
    call de_tum_foobar_f2c_nsd_create_client_instance(this%reference,host,port,buffer_size)
    
    

end subroutine createClientDispatcherInstanceForC

subroutine createClientDispatcherInstance(this,host,port,buffer_size)
    class(FooBarNativeSocketDispatcher)::this
    character(*)::host
    integer::port
    integer::buffer_size
    call this%createClientDispatcherInstanceForC(host//c_null_char,port,buffer_size)
    
    

end subroutine createClientDispatcherInstance

subroutine destroyDispatcherInstance(this)
     class(FooBarNativeSocketDispatcher)::this
     call de_tum_foobar_f2c_nsd_destroy_instance(this%reference)

end subroutine destroyDispatcherInstance

subroutine reset_internal(this)
     use, intrinsic :: iso_c_binding
     class(FooBarNativeSocketDispatcher)::this
     
     call de_tum_foobar_f2c_nsd_reset(this%reference)
end subroutine reset_internal

subroutine reset(this)
     use, intrinsic :: iso_c_binding
     class(FooBarNativeSocketDispatcher)::this
     
     call this%reset_internal()
end subroutine reset
subroutine bar_internal(this,&
	data,data_len)
     use, intrinsic :: iso_c_binding
     class(FooBarNativeSocketDispatcher)::this
     	real(kind=c_double),intent(inout),dimension(*)::data
	integer(kind=c_int),intent(in)::data_len

     call de_tum_foobar_f2c_nsd_bar(this%reference,&
data,data_len)
end subroutine bar_internal

subroutine bar(this,&
	data,data_len)
     use, intrinsic :: iso_c_binding
     class(FooBarNativeSocketDispatcher)::this
     	real(8),intent(inout),dimension(*)::data
	integer,intent(in)::data_len

     call this%bar_internal(&
data,data_len)
end subroutine bar
subroutine foo_internal(this,&
	data,data_len)
     use, intrinsic :: iso_c_binding
     class(FooBarNativeSocketDispatcher)::this
     	real(kind=c_double),intent(in),dimension(*)::data
	integer(kind=c_int),intent(in)::data_len

     call de_tum_foobar_f2c_nsd_foo(this%reference,&
data,data_len)
end subroutine foo_internal

subroutine foo(this,&
	data,data_len)
     use, intrinsic :: iso_c_binding
     class(FooBarNativeSocketDispatcher)::this
     	real(8),intent(in),dimension(*)::data
	integer,intent(in)::data_len

     call this%foo_internal(&
data,data_len)
end subroutine foo

end module  de_tum_FooBarFNativeSocketDispatcher
