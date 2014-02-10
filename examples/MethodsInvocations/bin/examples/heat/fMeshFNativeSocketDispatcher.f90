module examples_heat_fMeshFNativeSocketDispatcher
use, intrinsic :: iso_c_binding
implicit none


type, public :: fMeshNativeSocketDispatcher
     integer(kind=c_long_long )::reference
     contains
     procedure,public::createClientDispatcherInstanceForC
     procedure,public::createClientDispatcherInstance
     procedure,public::destroyDispatcherInstance
     
     
     	procedure,public::allocate
	procedure,private::allocate_internal
	procedure,public::copyData
	procedure,private::copyData_internal
	procedure,public::getData
	procedure,private::getData_internal

end type fMeshNativeSocketDispatcher
contains
subroutine createClientDispatcherInstanceForC(this,host,port,buffer_size)
    class(fMeshNativeSocketDispatcher)::this
    character(kind=c_char),dimension(*)::host
    integer(kind=c_int)::port
    integer(kind=c_int)::buffer_size
    this%reference=0
    call examples_heat_fmesh_f2c_nsd_create_client_instance(this%reference,host,port,buffer_size)
    
    

end subroutine createClientDispatcherInstanceForC

subroutine createClientDispatcherInstance(this,host,port,buffer_size)
    class(fMeshNativeSocketDispatcher)::this
    character(*)::host
    integer::port
    integer::buffer_size
    call this%createClientDispatcherInstanceForC(host//c_null_char,port,buffer_size)
    
    

end subroutine createClientDispatcherInstance

subroutine destroyDispatcherInstance(this)
     class(fMeshNativeSocketDispatcher)::this
     call examples_heat_fmesh_f2c_nsd_destroy_instance(this%reference)

end subroutine destroyDispatcherInstance

subroutine getData_internal(this,&
	handle)
     use, intrinsic :: iso_c_binding
     class(fMeshNativeSocketDispatcher)::this
     
     call examples_heat_fmesh_f2c_nsd_getData(this%reference,&
)
end subroutine getData_internal

subroutine getData(this,&
	handle)
     use, intrinsic :: iso_c_binding
     class(fMeshNativeSocketDispatcher)::this
     	character(len=1),dimension(:),intent(inout) ::handle

     call this%getData_internal(&
)
end subroutine getData
subroutine copyData_internal(this,&
	data,data_len)
     use, intrinsic :: iso_c_binding
     class(fMeshNativeSocketDispatcher)::this
     	real(kind=c_double),intent(inout),dimension(*)::data
	integer(kind=c_int),intent(in)::data_len

     call examples_heat_fmesh_f2c_nsd_copyData(this%reference,&
data,data_len)
end subroutine copyData_internal

subroutine copyData(this,&
	data,data_len)
     use, intrinsic :: iso_c_binding
     class(fMeshNativeSocketDispatcher)::this
     	real(8),intent(inout),dimension(*)::data
	integer,intent(in)::data_len

     call this%copyData_internal(&
data,data_len)
end subroutine copyData
subroutine allocate_internal(this,&
	dim,dim_len)
     use, intrinsic :: iso_c_binding
     class(fMeshNativeSocketDispatcher)::this
     	integer(kind=c_int),intent(in),dimension(*)::dim
	integer(kind=c_int),intent(in)::dim_len

     call examples_heat_fmesh_f2c_nsd_allocate(this%reference,&
dim,dim_len)
end subroutine allocate_internal

subroutine allocate(this,&
	dim,dim_len)
     use, intrinsic :: iso_c_binding
     class(fMeshNativeSocketDispatcher)::this
     	integer,intent(in),dimension(*)::dim
	integer,intent(in)::dim_len

     call this%allocate_internal(&
dim,dim_len)
end subroutine allocate

end module  examples_heat_fMeshFNativeSocketDispatcher
