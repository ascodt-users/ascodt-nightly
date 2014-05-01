module cca_cfd_NS2LBFNativeSocketDispatcher
use, intrinsic :: iso_c_binding
implicit none


type, public :: NS2LBNativeSocketDispatcher
     integer(kind=c_long_long )::reference
     contains
     procedure,public::createClientDispatcherInstanceForC
     procedure,public::createClientDispatcherInstance
     procedure,public::destroyDispatcherInstance
     
     
     	procedure,public::iterate
	procedure,private::iterate_internal
	procedure,public::retrieveTimestep
	procedure,private::retrieveTimestep_internal
	procedure,public::retrieveVelocitiesSize
	procedure,private::retrieveVelocitiesSize_internal
	procedure,public::retrieveVelocitiesCopy
	procedure,private::retrieveVelocitiesCopy_internal
	procedure,public::retrieveJacobianCopy
	procedure,private::retrieveJacobianCopy_internal
	procedure,public::retrievePressureCopy
	procedure,private::retrievePressureCopy_internal

end type NS2LBNativeSocketDispatcher
contains
subroutine createClientDispatcherInstanceForC(this,host,port,buffer_size)
    class(NS2LBNativeSocketDispatcher)::this
    character(kind=c_char),dimension(*)::host
    integer(kind=c_int)::port
    integer(kind=c_int)::buffer_size
    this%reference=0
    call cca_cfd_ns2lb_f2c_nsd_create_client_instance(this%reference,host,port,buffer_size)
    
    

end subroutine createClientDispatcherInstanceForC

subroutine createClientDispatcherInstance(this,host,port,buffer_size)
    class(NS2LBNativeSocketDispatcher)::this
    character(*)::host
    integer::port
    integer::buffer_size
    call this%createClientDispatcherInstanceForC(host//c_null_char,port,buffer_size)
    
    

end subroutine createClientDispatcherInstance

subroutine destroyDispatcherInstance(this)
     class(NS2LBNativeSocketDispatcher)::this
     call cca_cfd_ns2lb_f2c_nsd_destroy_instance(this%reference)

end subroutine destroyDispatcherInstance

subroutine retrievePressureCopy_internal(this,&
	pressure,pressure_len)
     use, intrinsic :: iso_c_binding
     class(NS2LBNativeSocketDispatcher)::this
     	real(kind=c_double),intent(inout),dimension(*)::pressure
	integer(kind=c_int),intent(in)::pressure_len

     call cca_cfd_ns2lb_f2c_nsd_retrievePressureCopy(this%reference,&
pressure,pressure_len)
end subroutine retrievePressureCopy_internal

subroutine retrievePressureCopy(this,&
	pressure,pressure_len)
     use, intrinsic :: iso_c_binding
     class(NS2LBNativeSocketDispatcher)::this
     	real(8),intent(inout),dimension(*)::pressure
	integer,intent(in)::pressure_len

     call this%retrievePressureCopy_internal(&
pressure,pressure_len)
end subroutine retrievePressureCopy
subroutine retrieveJacobianCopy_internal(this,&
	jacobian,jacobian_len)
     use, intrinsic :: iso_c_binding
     class(NS2LBNativeSocketDispatcher)::this
     	real(kind=c_double),intent(inout),dimension(*)::jacobian
	integer(kind=c_int),intent(in)::jacobian_len

     call cca_cfd_ns2lb_f2c_nsd_retrieveJacobianCopy(this%reference,&
jacobian,jacobian_len)
end subroutine retrieveJacobianCopy_internal

subroutine retrieveJacobianCopy(this,&
	jacobian,jacobian_len)
     use, intrinsic :: iso_c_binding
     class(NS2LBNativeSocketDispatcher)::this
     	real(8),intent(inout),dimension(*)::jacobian
	integer,intent(in)::jacobian_len

     call this%retrieveJacobianCopy_internal(&
jacobian,jacobian_len)
end subroutine retrieveJacobianCopy
subroutine retrieveVelocitiesCopy_internal(this,&
	velocityX,velocityX_len,&
	velocityY,velocityY_len,&
	velocityZ,velocityZ_len)
     use, intrinsic :: iso_c_binding
     class(NS2LBNativeSocketDispatcher)::this
     	real(kind=c_double),intent(inout),dimension(*)::velocityX
	integer(kind=c_int),intent(in)::velocityX_len
	real(kind=c_double),intent(inout),dimension(*)::velocityY
	integer(kind=c_int),intent(in)::velocityY_len
	real(kind=c_double),intent(inout),dimension(*)::velocityZ
	integer(kind=c_int),intent(in)::velocityZ_len

     call cca_cfd_ns2lb_f2c_nsd_retrieveVelocitiesCopy(this%reference,&
velocityX,velocityX_len,&
velocityY,velocityY_len,&
velocityZ,velocityZ_len)
end subroutine retrieveVelocitiesCopy_internal

subroutine retrieveVelocitiesCopy(this,&
	velocityX,velocityX_len,&
	velocityY,velocityY_len,&
	velocityZ,velocityZ_len)
     use, intrinsic :: iso_c_binding
     class(NS2LBNativeSocketDispatcher)::this
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
	memory)
     use, intrinsic :: iso_c_binding
     class(NS2LBNativeSocketDispatcher)::this
     	integer(kind=c_int),intent(inout)::memory

     call cca_cfd_ns2lb_f2c_nsd_retrieveVelocitiesSize(this%reference,&
memory)
end subroutine retrieveVelocitiesSize_internal

subroutine retrieveVelocitiesSize(this,&
	memory)
     use, intrinsic :: iso_c_binding
     class(NS2LBNativeSocketDispatcher)::this
     	integer,intent(inout)::memory

     call this%retrieveVelocitiesSize_internal(&
memory)
end subroutine retrieveVelocitiesSize
subroutine retrieveTimestep_internal(this,&
	timestep)
     use, intrinsic :: iso_c_binding
     class(NS2LBNativeSocketDispatcher)::this
     	real(kind=c_double),intent(inout)::timestep

     call cca_cfd_ns2lb_f2c_nsd_retrieveTimestep(this%reference,&
timestep)
end subroutine retrieveTimestep_internal

subroutine retrieveTimestep(this,&
	timestep)
     use, intrinsic :: iso_c_binding
     class(NS2LBNativeSocketDispatcher)::this
     	real(8),intent(inout)::timestep

     call this%retrieveTimestep_internal(&
timestep)
end subroutine retrieveTimestep
subroutine iterate_internal(this)
     use, intrinsic :: iso_c_binding
     class(NS2LBNativeSocketDispatcher)::this
     
     call cca_cfd_ns2lb_f2c_nsd_iterate(this%reference)
end subroutine iterate_internal

subroutine iterate(this)
     use, intrinsic :: iso_c_binding
     class(NS2LBNativeSocketDispatcher)::this
     
     call this%iterate_internal()
end subroutine iterate

end module  cca_cfd_NS2LBFNativeSocketDispatcher
