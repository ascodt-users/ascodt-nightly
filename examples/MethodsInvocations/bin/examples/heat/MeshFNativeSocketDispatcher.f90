module examples_heat_MeshFNativeSocketDispatcher
use, intrinsic :: iso_c_binding
implicit none


type, public :: MeshNativeSocketDispatcher
     integer(kind=c_long_long )::reference
     contains
     procedure,public::createClientDispatcherInstanceForC
     procedure,public::createClientDispatcherInstance
     procedure,public::destroyDispatcherInstance
     
     
     	procedure,public::allocate
	procedure,private::allocate_internal
	procedure,public::getData
	procedure,private::getData_internal

end type MeshNativeSocketDispatcher
contains
subroutine createClientDispatcherInstanceForC(this,host,port,buffer_size)
    class(MeshNativeSocketDispatcher)::this
    character(kind=c_char),dimension(*)::host
    integer(kind=c_int)::port
    integer(kind=c_int)::buffer_size
    this%reference=0
    call examples_heat_mesh_f2c_nsd_create_client_instance(this%reference,host,port,buffer_size)
    
    

end subroutine createClientDispatcherInstanceForC

subroutine createClientDispatcherInstance(this,host,port,buffer_size)
    class(MeshNativeSocketDispatcher)::this
    character(*)::host
    integer::port
    integer::buffer_size
    call this%createClientDispatcherInstanceForC(host//c_null_char,port,buffer_size)
    
    

end subroutine createClientDispatcherInstance

subroutine destroyDispatcherInstance(this)
     class(MeshNativeSocketDispatcher)::this
     call examples_heat_mesh_f2c_nsd_destroy_instance(this%reference)

end subroutine destroyDispatcherInstance

subroutine getData_internal(this,&
	data,data_len)
     use, intrinsic :: iso_c_binding
     class(MeshNativeSocketDispatcher)::this
     	real(kind=c_double),intent(inout),dimension(*)::data
	integer(kind=c_int),intent(in)::data_len

     call examples_heat_mesh_f2c_nsd_getData(this%reference,&
data,data_len)
end subroutine getData_internal

subroutine getData(this,&
	data,data_len)
     use, intrinsic :: iso_c_binding
     class(MeshNativeSocketDispatcher)::this
     	real(8),intent(inout),dimension(*)::data
	integer,intent(in)::data_len

     call this%getData_internal(&
data,data_len)
end subroutine getData
subroutine allocate_internal(this,&
	dim,dim_len)
     use, intrinsic :: iso_c_binding
     class(MeshNativeSocketDispatcher)::this
     	integer(kind=c_int),intent(in),dimension(*)::dim
	integer(kind=c_int),intent(in)::dim_len

     call examples_heat_mesh_f2c_nsd_allocate(this%reference,&
dim,dim_len)
end subroutine allocate_internal

subroutine allocate(this,&
	dim,dim_len)
     use, intrinsic :: iso_c_binding
     class(MeshNativeSocketDispatcher)::this
     	integer,intent(in),dimension(*)::dim
	integer,intent(in)::dim_len

     call this%allocate_internal(&
dim,dim_len)
end subroutine allocate

end module  examples_heat_MeshFNativeSocketDispatcher
