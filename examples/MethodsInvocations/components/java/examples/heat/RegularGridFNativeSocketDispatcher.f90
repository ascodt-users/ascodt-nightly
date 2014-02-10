module examples_heat_RegularGridFNativeSocketDispatcher
use, intrinsic :: iso_c_binding
implicit none


type, public :: RegularGridNativeSocketDispatcher
     integer(kind=c_long_long )::reference
     contains
     procedure,public::createClientDispatcherInstanceForC
     procedure,public::createClientDispatcherInstance
     procedure,public::destroyDispatcherInstance
     
     
     	procedure,public::setOffset
	procedure,private::setOffset_internal
	procedure,public::setDomain
	procedure,private::setDomain_internal
	procedure,public::setDimensions
	procedure,private::setDimensions_internal
	procedure,public::addCellScalars
	procedure,private::addCellScalars_internal
	procedure,public::render
	procedure,private::render_internal

end type RegularGridNativeSocketDispatcher
contains
subroutine createClientDispatcherInstanceForC(this,host,port,buffer_size)
    class(RegularGridNativeSocketDispatcher)::this
    character(kind=c_char),dimension(*)::host
    integer(kind=c_int)::port
    integer(kind=c_int)::buffer_size
    this%reference=0
    call examples_heat_regulargrid_f2c_nsd_create_client_instance(this%reference,host,port,buffer_size)
    
    

end subroutine createClientDispatcherInstanceForC

subroutine createClientDispatcherInstance(this,host,port,buffer_size)
    class(RegularGridNativeSocketDispatcher)::this
    character(*)::host
    integer::port
    integer::buffer_size
    call this%createClientDispatcherInstanceForC(host//c_null_char,port,buffer_size)
    
    

end subroutine createClientDispatcherInstance

subroutine destroyDispatcherInstance(this)
     class(RegularGridNativeSocketDispatcher)::this
     call examples_heat_regulargrid_f2c_nsd_destroy_instance(this%reference)

end subroutine destroyDispatcherInstance

subroutine render_internal(this)
     use, intrinsic :: iso_c_binding
     class(RegularGridNativeSocketDispatcher)::this
     
     call examples_heat_regulargrid_f2c_nsd_render(this%reference)
end subroutine render_internal

subroutine render(this)
     use, intrinsic :: iso_c_binding
     class(RegularGridNativeSocketDispatcher)::this
     
     call this%render_internal()
end subroutine render
subroutine addCellScalars_internal(this,&
	variableName,&
	scalars,scalars_len)
     use, intrinsic :: iso_c_binding
     class(RegularGridNativeSocketDispatcher)::this
     	character(kind=c_char),dimension(*),intent(in)::variableName
	real(kind=c_double),intent(in),dimension(*)::scalars
	integer(kind=c_int),intent(in)::scalars_len

     call examples_heat_regulargrid_f2c_nsd_addCellScalars(this%reference,&
variableName,&
scalars,scalars_len)
end subroutine addCellScalars_internal

subroutine addCellScalars(this,&
	variableName,&
	scalars,scalars_len)
     use, intrinsic :: iso_c_binding
     class(RegularGridNativeSocketDispatcher)::this
     	character(*),intent(in)::variableName
	real(8),intent(in),dimension(*)::scalars
	integer,intent(in)::scalars_len

     call this%addCellScalars_internal(&
variableName//c_null_char,&
scalars,scalars_len)
end subroutine addCellScalars
subroutine setDimensions_internal(this,&
	dimensions,dimensions_len)
     use, intrinsic :: iso_c_binding
     class(RegularGridNativeSocketDispatcher)::this
     	integer(kind=c_int),intent(in),dimension(*)::dimensions
	integer(kind=c_int),intent(in)::dimensions_len

     call examples_heat_regulargrid_f2c_nsd_setDimensions(this%reference,&
dimensions,dimensions_len)
end subroutine setDimensions_internal

subroutine setDimensions(this,&
	dimensions,dimensions_len)
     use, intrinsic :: iso_c_binding
     class(RegularGridNativeSocketDispatcher)::this
     	integer,intent(in),dimension(*)::dimensions
	integer,intent(in)::dimensions_len

     call this%setDimensions_internal(&
dimensions,dimensions_len)
end subroutine setDimensions
subroutine setDomain_internal(this,&
	domain,domain_len)
     use, intrinsic :: iso_c_binding
     class(RegularGridNativeSocketDispatcher)::this
     	real(kind=c_double),intent(in),dimension(*)::domain
	integer(kind=c_int),intent(in)::domain_len

     call examples_heat_regulargrid_f2c_nsd_setDomain(this%reference,&
domain,domain_len)
end subroutine setDomain_internal

subroutine setDomain(this,&
	domain,domain_len)
     use, intrinsic :: iso_c_binding
     class(RegularGridNativeSocketDispatcher)::this
     	real(8),intent(in),dimension(*)::domain
	integer,intent(in)::domain_len

     call this%setDomain_internal(&
domain,domain_len)
end subroutine setDomain
subroutine setOffset_internal(this,&
	offset,offset_len)
     use, intrinsic :: iso_c_binding
     class(RegularGridNativeSocketDispatcher)::this
     	real(kind=c_double),intent(in),dimension(*)::offset
	integer(kind=c_int),intent(in)::offset_len

     call examples_heat_regulargrid_f2c_nsd_setOffset(this%reference,&
offset,offset_len)
end subroutine setOffset_internal

subroutine setOffset(this,&
	offset,offset_len)
     use, intrinsic :: iso_c_binding
     class(RegularGridNativeSocketDispatcher)::this
     	real(8),intent(in),dimension(*)::offset
	integer,intent(in)::offset_len

     call this%setOffset_internal(&
offset,offset_len)
end subroutine setOffset

end module  examples_heat_RegularGridFNativeSocketDispatcher
