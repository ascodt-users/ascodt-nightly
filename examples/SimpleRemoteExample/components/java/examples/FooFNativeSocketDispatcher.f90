module examples_FooFNativeSocketDispatcher
use, intrinsic :: iso_c_binding
implicit none


type, public :: FooNativeSocketDispatcher
     integer(kind=c_long_long )::reference
     contains
     procedure,public::createClientDispatcherInstanceForC
     procedure,public::createClientDispatcherInstance
     procedure,public::destroyDispatcherInstance
     
     
     	procedure,public::bar
	procedure,private::bar_internal

end type FooNativeSocketDispatcher
contains
subroutine createClientDispatcherInstanceForC(this,host,port,buffer_size)
    class(FooNativeSocketDispatcher)::this
    character(kind=c_char),dimension(*)::host
    integer(kind=c_int)::port
    integer(kind=c_int)::buffer_size
    this%reference=0
    call examples_foo_f2c_nsd_create_client_instance(this%reference,host,port,buffer_size)
    
    

end subroutine createClientDispatcherInstanceForC

subroutine createClientDispatcherInstance(this,host,port,buffer_size)
    class(FooNativeSocketDispatcher)::this
    character(*)::host
    integer::port
    integer::buffer_size
    call this%createClientDispatcherInstanceForC(host//c_null_char,port,buffer_size)
    
    

end subroutine createClientDispatcherInstance

subroutine destroyDispatcherInstance(this)
     class(FooNativeSocketDispatcher)::this
     call examples_foo_f2c_nsd_destroy_instance(this%reference)

end subroutine destroyDispatcherInstance

subroutine bar_internal(this,&
	a,&
	b)
     use, intrinsic :: iso_c_binding
     class(FooNativeSocketDispatcher)::this
     	integer(kind=c_int),intent(in)::a
	integer(kind=c_int),intent(in)::b

     call examples_foo_f2c_nsd_bar(this%reference,&
a,&
b)
end subroutine bar_internal

subroutine bar(this,&
	a,&
	b)
     use, intrinsic :: iso_c_binding
     class(FooNativeSocketDispatcher)::this
     	integer,intent(in)::a
	integer,intent(in)::b

     call this%bar_internal(&
a,&
b)
end subroutine bar

end module  examples_FooFNativeSocketDispatcher
