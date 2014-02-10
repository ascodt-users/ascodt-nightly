module de_tum_FooBar2SocketPort 
use, intrinsic :: iso_c_binding
implicit none


type, public :: FooBar2SocketPort
     
     integer(kind=c_long_long )::reference
     contains
     procedure,public::create_port_client_instance
     procedure,public::create_port_client_instance_for_c
     procedure,public::destroyPortInstance
     procedure,public::foo
procedure,public::bar
procedure,public::reset

end type FooBar2SocketPort
contains

subroutine create_port_client_instance_for_c(this,host,port,buffer_size)
    class(FooBar2SocketPort)::this
    integer(kind=c_int)::port
    character(kind=c_char),dimension(*)::host
    integer(kind=c_int)::buffer_size
    call de_tum_foobarc2socket_plain_port_create_client_instance(this%reference,host,port,buffer_size)
    

end subroutine create_port_client_instance_for_c

subroutine create_port_client_instance(this,host,port,buffer_size)
    class(FooBar2SocketPort)::this
    integer::port
    character(*)::host
    integer::buffer_size
    call this%create_port_client_instance_for_c(host//c_null_char,port,buffer_size)
    

end subroutine create_port_client_instance



subroutine destroyPortInstance(this)
     class(FooBar2SocketPort)::this
     call de_tum_foobarc2socket_plain_port_destroy_instance(this%reference)

end subroutine destroyPortInstance

subroutine reset(this)
     use, intrinsic :: iso_c_binding
     class(FooBar2SocketPort)::this
     
     
     call de_tum_foobarc2socket_plain_port_reset(this%reference)
end subroutine reset
subroutine bar(this,&
	data,data_len)
     use, intrinsic :: iso_c_binding
     class(FooBar2SocketPort)::this
     	real(8),intent(inout),dimension(*)::data
	integer,intent(in)::data_len

     
     call de_tum_foobarc2socket_plain_port_bar(this%reference,&
data,data_len)
end subroutine bar
subroutine foo(this,&
	data,data_len)
     use, intrinsic :: iso_c_binding
     class(FooBar2SocketPort)::this
     	real(8),intent(in),dimension(*)::data
	integer,intent(in)::data_len

     
     call de_tum_foobarc2socket_plain_port_foo(this%reference,&
data,data_len)
end subroutine foo

end module  de_tum_FooBar2SocketPort
