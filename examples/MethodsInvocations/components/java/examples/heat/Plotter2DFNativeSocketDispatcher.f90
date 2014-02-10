module examples_heat_Plotter2DFNativeSocketDispatcher
use, intrinsic :: iso_c_binding
implicit none


type, public :: Plotter2DNativeSocketDispatcher
     integer(kind=c_long_long )::reference
     contains
     procedure,public::createClientDispatcherInstanceForC
     procedure,public::createClientDispatcherInstance
     procedure,public::destroyDispatcherInstance
     
     
     	procedure,public::plotPoint
	procedure,private::plotPoint_internal

end type Plotter2DNativeSocketDispatcher
contains
subroutine createClientDispatcherInstanceForC(this,host,port,buffer_size)
    class(Plotter2DNativeSocketDispatcher)::this
    character(kind=c_char),dimension(*)::host
    integer(kind=c_int)::port
    integer(kind=c_int)::buffer_size
    this%reference=0
    call examples_heat_plotter2d_f2c_nsd_create_client_instance(this%reference,host,port,buffer_size)
    
    

end subroutine createClientDispatcherInstanceForC

subroutine createClientDispatcherInstance(this,host,port,buffer_size)
    class(Plotter2DNativeSocketDispatcher)::this
    character(*)::host
    integer::port
    integer::buffer_size
    call this%createClientDispatcherInstanceForC(host//c_null_char,port,buffer_size)
    
    

end subroutine createClientDispatcherInstance

subroutine destroyDispatcherInstance(this)
     class(Plotter2DNativeSocketDispatcher)::this
     call examples_heat_plotter2d_f2c_nsd_destroy_instance(this%reference)

end subroutine destroyDispatcherInstance

subroutine plotPoint_internal(this,&
	name,&
	x,&
	y)
     use, intrinsic :: iso_c_binding
     class(Plotter2DNativeSocketDispatcher)::this
     	character(kind=c_char),dimension(*),intent(in)::name
	real(kind=c_double),intent(in)::x
	real(kind=c_double),intent(in)::y

     call examples_heat_plotter2d_f2c_nsd_plotPoint(this%reference,&
name,&
x,&
y)
end subroutine plotPoint_internal

subroutine plotPoint(this,&
	name,&
	x,&
	y)
     use, intrinsic :: iso_c_binding
     class(Plotter2DNativeSocketDispatcher)::this
     	character(*),intent(in)::name
	real(8),intent(in)::x
	real(8),intent(in)::y

     call this%plotPoint_internal(&
name//c_null_char,&
x,&
y)
end subroutine plotPoint

end module  examples_heat_Plotter2DFNativeSocketDispatcher
