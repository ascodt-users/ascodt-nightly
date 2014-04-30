module cca_cfd_DriverFNativeSocketDispatcher
use, intrinsic :: iso_c_binding
implicit none


type, public :: DriverNativeSocketDispatcher
     integer(kind=c_long_long )::reference
     contains
     procedure,public::createClientDispatcherInstanceForC
     procedure,public::createClientDispatcherInstance
     procedure,public::destroyDispatcherInstance
     
     
     	procedure,public::go
	procedure,private::go_internal

end type DriverNativeSocketDispatcher
contains
subroutine createClientDispatcherInstanceForC(this,host,port,buffer_size)
    class(DriverNativeSocketDispatcher)::this
    character(kind=c_char),dimension(*)::host
    integer(kind=c_int)::port
    integer(kind=c_int)::buffer_size
    this%reference=0
    call cca_cfd_driver_f2c_nsd_create_client_instance(this%reference,host,port,buffer_size)
    
    

end subroutine createClientDispatcherInstanceForC

subroutine createClientDispatcherInstance(this,host,port,buffer_size)
    class(DriverNativeSocketDispatcher)::this
    character(*)::host
    integer::port
    integer::buffer_size
    call this%createClientDispatcherInstanceForC(host//c_null_char,port,buffer_size)
    
    

end subroutine createClientDispatcherInstance

subroutine destroyDispatcherInstance(this)
     class(DriverNativeSocketDispatcher)::this
     call cca_cfd_driver_f2c_nsd_destroy_instance(this%reference)

end subroutine destroyDispatcherInstance

subroutine go_internal(this,&
	configFile)
     use, intrinsic :: iso_c_binding
     class(DriverNativeSocketDispatcher)::this
     	character(kind=c_char),dimension(*),intent(in)::configFile

     call cca_cfd_driver_f2c_nsd_go(this%reference,&
configFile)
end subroutine go_internal

subroutine go(this,&
	configFile)
     use, intrinsic :: iso_c_binding
     class(DriverNativeSocketDispatcher)::this
     	character(*),intent(in)::configFile

     call this%go_internal(&
configFile//c_null_char)
end subroutine go

end module  cca_cfd_DriverFNativeSocketDispatcher
