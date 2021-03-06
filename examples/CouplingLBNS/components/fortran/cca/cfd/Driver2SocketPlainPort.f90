module cca_cfd_Driver2SocketPort 
use, intrinsic :: iso_c_binding
implicit none


type, public :: Driver2SocketPort
     
     integer(kind=c_long_long )::reference
     contains
     procedure,public::create_port_client_instance
     procedure,public::create_port_client_instance_for_c
     procedure,public::destroyPortInstance
     procedure,public::go

end type Driver2SocketPort
contains

subroutine create_port_client_instance_for_c(this,host,port,buffer_size)
    class(Driver2SocketPort)::this
    integer(kind=c_int)::port
    character(kind=c_char),dimension(*)::host
    integer(kind=c_int)::buffer_size
    call cca_cfd_driverc2socket_plain_port_create_client_instance(this%reference,host,port,buffer_size)
    

end subroutine create_port_client_instance_for_c

subroutine create_port_client_instance(this,host,port,buffer_size)
    class(Driver2SocketPort)::this
    integer::port
    character(*)::host
    integer::buffer_size
    call this%create_port_client_instance_for_c(host//c_null_char,port,buffer_size)
    

end subroutine create_port_client_instance



subroutine destroyPortInstance(this)
     class(Driver2SocketPort)::this
     call cca_cfd_driverc2socket_plain_port_destroy_instance(this%reference)

end subroutine destroyPortInstance

subroutine go(this,&
	configFile)
     use, intrinsic :: iso_c_binding
     class(Driver2SocketPort)::this
     	character(*),intent(in)::configFile

     
     call cca_cfd_driverc2socket_plain_port_go(this%reference,&
configFile)
end subroutine go

end module  cca_cfd_Driver2SocketPort
