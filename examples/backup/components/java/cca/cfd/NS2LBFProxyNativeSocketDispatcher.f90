subroutine cca_cfd_ns2lb_f2c_nsd_create_client_instance(self,host,port,buffer_size) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     type(c_ptr)::host
     integer(kind=c_int)::port
     integer(kind=c_int)::buffer_size
end subroutine cca_cfd_ns2lb_f2c_nsd_create_client_instance


subroutine cca_cfd_ns2lb_f2c_nsd_destroy_instance(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
end subroutine cca_cfd_ns2lb_f2c_nsd_destroy_instance

subroutine  cca_cfd_ns2lb_f2c_nsd_iterate(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     
end subroutine cca_cfd_ns2lb_f2c_nsd_iterate
subroutine  cca_cfd_ns2lb_f2c_nsd_retrieveTimestep(self,&
	timestep) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	real(kind=c_double),intent(inout)::timestep

end subroutine cca_cfd_ns2lb_f2c_nsd_retrieveTimestep
subroutine  cca_cfd_ns2lb_f2c_nsd_retrieveVelocitiesSize(self,&
	memory) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	integer(kind=c_int),intent(inout)::memory

end subroutine cca_cfd_ns2lb_f2c_nsd_retrieveVelocitiesSize
subroutine  cca_cfd_ns2lb_f2c_nsd_retrieveVelocitiesCopy(self,&
	velocityX,velocityX_len,&
	velocityY,velocityY_len,&
	velocityZ,velocityZ_len) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	real(kind=c_double),intent(inout),dimension(*)::velocityX
	integer(kind=c_int),intent(in)::velocityX_len
	real(kind=c_double),intent(inout),dimension(*)::velocityY
	integer(kind=c_int),intent(in)::velocityY_len
	real(kind=c_double),intent(inout),dimension(*)::velocityZ
	integer(kind=c_int),intent(in)::velocityZ_len

end subroutine cca_cfd_ns2lb_f2c_nsd_retrieveVelocitiesCopy
subroutine  cca_cfd_ns2lb_f2c_nsd_retrieveJacobianCopy(self,&
	jacobian,jacobian_len) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	real(kind=c_double),intent(inout),dimension(*)::jacobian
	integer(kind=c_int),intent(in)::jacobian_len

end subroutine cca_cfd_ns2lb_f2c_nsd_retrieveJacobianCopy
subroutine  cca_cfd_ns2lb_f2c_nsd_retrievePressureCopy(self,&
	pressure,pressure_len) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	real(kind=c_double),intent(inout),dimension(*)::pressure
	integer(kind=c_int),intent(in)::pressure_len

end subroutine cca_cfd_ns2lb_f2c_nsd_retrievePressureCopy
