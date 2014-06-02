module cca_cfd_LB2NSFNativeSocketDispatcher
use, intrinsic :: iso_c_binding
implicit none


type, public :: LB2NSNativeSocketDispatcher
     integer(kind=c_long_long )::reference
     contains
     procedure,public::createClientDispatcherInstanceForC
     procedure,public::createClientDispatcherInstance
     procedure,public::destroyDispatcherInstance
     
     
     	procedure,public::iterateBoundary
	procedure,private::iterateBoundary_internal
	procedure,public::iterateInner
	procedure,private::iterateInner_internal
	procedure,public::retrieveTimestep
	procedure,private::retrieveTimestep_internal
	procedure,public::retrieveVelocitiesSize
	procedure,private::retrieveVelocitiesSize_internal
	procedure,public::retrieveVelocitiesCopy
	procedure,private::retrieveVelocitiesCopy_internal

end type LB2NSNativeSocketDispatcher
contains
subroutine createClientDispatcherInstanceForC(this,host,port,buffer_size)
    class(LB2NSNativeSocketDispatcher)::this
    character(kind=c_char),dimension(*)::host
    integer(kind=c_int)::port
    integer(kind=c_int)::buffer_size
    this%reference=0
    call cca_cfd_lb2ns_f2c_nsd_create_client_instance(this%reference,host,port,buffer_size)
    
    

end subroutine createClientDispatcherInstanceForC

subroutine createClientDispatcherInstance(this,host,port,buffer_size)
    class(LB2NSNativeSocketDispatcher)::this
    character(*)::host
    integer::port
    integer::buffer_size
    call this%createClientDispatcherInstanceForC(host//c_null_char,port,buffer_size)
    
    

end subroutine createClientDispatcherInstance

subroutine destroyDispatcherInstance(this)
     class(LB2NSNativeSocketDispatcher)::this
     call cca_cfd_lb2ns_f2c_nsd_destroy_instance(this%reference)

end subroutine destroyDispatcherInstance

subroutine retrieveVelocitiesCopy_internal(this,&
	velocityX,velocityX_len,&
	velocityY,velocityY_len,&
	velocityZ,velocityZ_len)
     use, intrinsic :: iso_c_binding
     class(LB2NSNativeSocketDispatcher)::this
     	real(kind=c_double),intent(inout),dimension(*)::velocityX
	integer(kind=c_int),intent(in)::velocityX_len
	real(kind=c_double),intent(inout),dimension(*)::velocityY
	integer(kind=c_int),intent(in)::velocityY_len
	real(kind=c_double),intent(inout),dimension(*)::velocityZ
	integer(kind=c_int),intent(in)::velocityZ_len

     call cca_cfd_lb2ns_f2c_nsd_retrieveVelocitiesCopy(this%reference,&
velocityX,velocityX_len,&
velocityY,velocityY_len,&
velocityZ,velocityZ_len)
end subroutine retrieveVelocitiesCopy_internal

subroutine retrieveVelocitiesCopy(this,&
	velocityX,velocityX_len,&
	velocityY,velocityY_len,&
	velocityZ,velocityZ_len)
     use, intrinsic :: iso_c_binding
     class(LB2NSNativeSocketDispatcher)::this
     	real(8),intent(inout),dimension(*)::velocityX
	integer,intent(in)::velocityX_len
	real(8),intent(inout),dimension(*)::velocityY
	integer,intent(in)::velocityY_len
	real(8),intent(inout),dimension(*)::velocityZ
	integer,intent(in)::velocityZ_len

     call this%retrieveVelocitiesCopy_internal(&
velocityX,velocityX_len,&
velocityY,velocityY_len,&
velocityZ,velocityZ_len)
end subroutine retrieveVelocitiesCopy
subroutine retrieveVelocitiesSize_internal(this,&
	memoryX,&
	memoryY,&
	memoryZ)
     use, intrinsic :: iso_c_binding
     class(LB2NSNativeSocketDispatcher)::this
     	integer(kind=c_int),intent(inout)::memoryX
	integer(kind=c_int),intent(inout)::memoryY
	integer(kind=c_int),intent(inout)::memoryZ

     call cca_cfd_lb2ns_f2c_nsd_retrieveVelocitiesSize(this%reference,&
memoryX,&
memoryY,&
memoryZ)
end subroutine retrieveVelocitiesSize_internal

subroutine retrieveVelocitiesSize(this,&
	memoryX,&
	memoryY,&
	memoryZ)
     use, intrinsic :: iso_c_binding
     class(LB2NSNativeSocketDispatcher)::this
     	integer,intent(inout)::memoryX
	integer,intent(inout)::memoryY
	integer,intent(inout)::memoryZ

     call this%retrieveVelocitiesSize_internal(&
memoryX,&
memoryY,&
memoryZ)
end subroutine retrieveVelocitiesSize
subroutine retrieveTimestep_internal(this,&
	dt)
     use, intrinsic :: iso_c_binding
     class(LB2NSNativeSocketDispatcher)::this
     	real(kind=c_double),intent(inout)::dt

     call cca_cfd_lb2ns_f2c_nsd_retrieveTimestep(this%reference,&
dt)
end subroutine retrieveTimestep_internal

subroutine retrieveTimestep(this,&
	dt)
     use, intrinsic :: iso_c_binding
     class(LB2NSNativeSocketDispatcher)::this
     	real(8),intent(inout)::dt

     call this%retrieveTimestep_internal(&
dt)
end subroutine retrieveTimestep
subroutine iterateInner_internal(this)
     use, intrinsic :: iso_c_binding
     class(LB2NSNativeSocketDispatcher)::this
     
     call cca_cfd_lb2ns_f2c_nsd_iterateInner(this%reference)
end subroutine iterateInner_internal

subroutine iterateInner(this)
     use, intrinsic :: iso_c_binding
     class(LB2NSNativeSocketDispatcher)::this
     
     call this%iterateInner_internal()
end subroutine iterateInner
subroutine iterateBoundary_internal(this)
     use, intrinsic :: iso_c_binding
     class(LB2NSNativeSocketDispatcher)::this
     
     call cca_cfd_lb2ns_f2c_nsd_iterateBoundary(this%reference)
end subroutine iterateBoundary_internal

subroutine iterateBoundary(this)
     use, intrinsic :: iso_c_binding
     class(LB2NSNativeSocketDispatcher)::this
     
     call this%iterateBoundary_internal()
end subroutine iterateBoundary

end module  cca_cfd_LB2NSFNativeSocketDispatcher
