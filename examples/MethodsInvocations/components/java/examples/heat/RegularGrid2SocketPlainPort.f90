module examples_heat_RegularGrid2SocketPort 
use, intrinsic :: iso_c_binding
implicit none


type, public :: RegularGrid2SocketPort
     
     integer(kind=c_long_long )::reference
     contains
     procedure,public::create_port_client_instance
     procedure,public::create_port_client_instance_for_c
     procedure,public::destroyPortInstance
     procedure,public::setOffset
procedure,public::setDomain
procedure,public::setDimensions
procedure,public::addCellScalars
procedure,public::render

end type RegularGrid2SocketPort
contains

subroutine create_port_client_instance_for_c(this,host,port,buffer_size)
    class(RegularGrid2SocketPort)::this
    integer(kind=c_int)::port
    character(kind=c_char),dimension(*)::host
    integer(kind=c_int)::buffer_size
    call examples_heat_regulargridc2socket_plain_port_create_client_instance(this%reference,host,port,buffer_size)
    

end subroutine create_port_client_instance_for_c

subroutine create_port_client_instance(this,host,port,buffer_size)
    class(RegularGrid2SocketPort)::this
    integer::port
    character(*)::host
    integer::buffer_size
    call this%create_port_client_instance_for_c(host//c_null_char,port,buffer_size)
    

end subroutine create_port_client_instance



subroutine destroyPortInstance(this)
     class(RegularGrid2SocketPort)::this
     call examples_heat_regulargridc2socket_plain_port_destroy_instance(this%reference)

end subroutine destroyPortInstance

subroutine render(this)
     use, intrinsic :: iso_c_binding
     class(RegularGrid2SocketPort)::this
     
     
     call examples_heat_regulargridc2socket_plain_port_render(this%reference)
end subroutine render
subroutine addCellScalars(this,&
	variableName,&
	scalars,scalars_len)
     use, intrinsic :: iso_c_binding
     class(RegularGrid2SocketPort)::this
     	character(*),intent(in)::variableName
	real(8),intent(in),dimension(*)::scalars
	integer,intent(in)::scalars_len

     
     call examples_heat_regulargridc2socket_plain_port_addCellScalars(this%reference,&
variableName,&
scalars,scalars_len)
end subroutine addCellScalars
subroutine setDimensions(this,&
	dimensions,dimensions_len)
     use, intrinsic :: iso_c_binding
     class(RegularGrid2SocketPort)::this
     	integer,intent(in),dimension(*)::dimensions
	integer,intent(in)::dimensions_len

     
     call examples_heat_regulargridc2socket_plain_port_setDimensions(this%reference,&
dimensions,dimensions_len)
end subroutine setDimensions
subroutine setDomain(this,&
	domain,domain_len)
     use, intrinsic :: iso_c_binding
     class(RegularGrid2SocketPort)::this
     	real(8),intent(in),dimension(*)::domain
	integer,intent(in)::domain_len

     
     call examples_heat_regulargridc2socket_plain_port_setDomain(this%reference,&
domain,domain_len)
end subroutine setDomain
subroutine setOffset(this,&
	offset,offset_len)
     use, intrinsic :: iso_c_binding
     class(RegularGrid2SocketPort)::this
     	real(8),intent(in),dimension(*)::offset
	integer,intent(in)::offset_len

     
     call examples_heat_regulargridc2socket_plain_port_setOffset(this%reference,&
offset,offset_len)
end subroutine setOffset

end module  examples_heat_RegularGrid2SocketPort
