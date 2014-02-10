module examples_heat_Plotter2D2SocketPort 
use, intrinsic :: iso_c_binding
implicit none


type, public :: Plotter2D2SocketPort
     
     integer(kind=c_long_long )::reference
     contains
     procedure,public::create_port_client_instance
     procedure,public::create_port_client_instance_for_c
     procedure,public::destroyPortInstance
     procedure,public::plotPoint

end type Plotter2D2SocketPort
contains

subroutine create_port_client_instance_for_c(this,host,port,buffer_size)
    class(Plotter2D2SocketPort)::this
    integer(kind=c_int)::port
    character(kind=c_char),dimension(*)::host
    integer(kind=c_int)::buffer_size
    call examples_heat_plotter2dc2socket_plain_port_create_client_instance(this%reference,host,port,buffer_size)
    

end subroutine create_port_client_instance_for_c

subroutine create_port_client_instance(this,host,port,buffer_size)
    class(Plotter2D2SocketPort)::this
    integer::port
    character(*)::host
    integer::buffer_size
    call this%create_port_client_instance_for_c(host//c_null_char,port,buffer_size)
    

end subroutine create_port_client_instance



subroutine destroyPortInstance(this)
     class(Plotter2D2SocketPort)::this
     call examples_heat_plotter2dc2socket_plain_port_destroy_instance(this%reference)

end subroutine destroyPortInstance

subroutine plotPoint(this,&
	name,&
	x,&
	y)
     use, intrinsic :: iso_c_binding
     class(Plotter2D2SocketPort)::this
     	character(*),intent(in)::name
	real(8),intent(in)::x
	real(8),intent(in)::y

     
     call examples_heat_plotter2dc2socket_plain_port_plotPoint(this%reference,&
name,&
x,&
y)
end subroutine plotPoint

end module  examples_heat_Plotter2D2SocketPort
