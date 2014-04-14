module examples_Foo2SocketPort 
use, intrinsic :: iso_c_binding
implicit none


type, public :: Foo2SocketPort
     
     integer(kind=c_long_long )::reference
     contains
     procedure,public::create_port_client_instance
     procedure,public::create_port_client_instance_for_c
     procedure,public::destroyPortInstance
     procedure,public::bar

end type Foo2SocketPort
contains

subroutine create_port_client_instance_for_c(this,host,port,buffer_size)
    class(Foo2SocketPort)::this
    integer(kind=c_int)::port
    character(kind=c_char),dimension(*)::host
    integer(kind=c_int)::buffer_size
    call examples_fooc2socket_plain_port_create_client_instance(this%reference,host,port,buffer_size)
    

end subroutine create_port_client_instance_for_c

subroutine create_port_client_instance(this,host,port,buffer_size)
    class(Foo2SocketPort)::this
    integer::port
    character(*)::host
    integer::buffer_size
    call this%create_port_client_instance_for_c(host//c_null_char,port,buffer_size)
    

end subroutine create_port_client_instance



subroutine destroyPortInstance(this)
     class(Foo2SocketPort)::this
     call examples_fooc2socket_plain_port_destroy_instance(this%reference)

end subroutine destroyPortInstance

subroutine bar(this,&
	a,&
	b)
     use, intrinsic :: iso_c_binding
     class(Foo2SocketPort)::this
     	integer,intent(in)::a
	integer,intent(in)::b

     
     call examples_fooc2socket_plain_port_bar(this%reference,&
a,&
b)
end subroutine bar

end module  examples_Foo2SocketPort
