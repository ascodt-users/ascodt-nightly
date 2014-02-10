module examples_heat_fMesh2SocketPort 
use, intrinsic :: iso_c_binding
implicit none


type, public :: fMesh2SocketPort
     
     integer(kind=c_long_long )::reference
     contains
     procedure,public::create_port_client_instance
     procedure,public::create_port_client_instance_for_c
     procedure,public::destroyPortInstance
     procedure,public::allocate
procedure,public::copyData
procedure,public::getData

end type fMesh2SocketPort
contains

subroutine create_port_client_instance_for_c(this,host,port,buffer_size)
    class(fMesh2SocketPort)::this
    integer(kind=c_int)::port
    character(kind=c_char),dimension(*)::host
    integer(kind=c_int)::buffer_size
    call examples_heat_fmeshc2socket_plain_port_create_client_instance(this%reference,host,port,buffer_size)
    

end subroutine create_port_client_instance_for_c

subroutine create_port_client_instance(this,host,port,buffer_size)
    class(fMesh2SocketPort)::this
    integer::port
    character(*)::host
    integer::buffer_size
    call this%create_port_client_instance_for_c(host//c_null_char,port,buffer_size)
    

end subroutine create_port_client_instance



subroutine destroyPortInstance(this)
     class(fMesh2SocketPort)::this
     call examples_heat_fmeshc2socket_plain_port_destroy_instance(this%reference)

end subroutine destroyPortInstance

subroutine getData(this,&
	handle)
     use, intrinsic :: iso_c_binding
     class(fMesh2SocketPort)::this
     	character(len=1),dimension(:),intent(inout) ::handle

     
     call examples_heat_fmeshc2socket_plain_port_getData(this%reference,&
)
end subroutine getData
subroutine copyData(this,&
	data,data_len)
     use, intrinsic :: iso_c_binding
     class(fMesh2SocketPort)::this
     	real(8),intent(inout),dimension(*)::data
	integer,intent(in)::data_len

     
     call examples_heat_fmeshc2socket_plain_port_copyData(this%reference,&
data,data_len)
end subroutine copyData
subroutine allocate(this,&
	dim,dim_len)
     use, intrinsic :: iso_c_binding
     class(fMesh2SocketPort)::this
     	integer,intent(in),dimension(*)::dim
	integer,intent(in)::dim_len

     
     call examples_heat_fmeshc2socket_plain_port_allocate(this%reference,&
dim,dim_len)
end subroutine allocate

end module  examples_heat_fMesh2SocketPort
