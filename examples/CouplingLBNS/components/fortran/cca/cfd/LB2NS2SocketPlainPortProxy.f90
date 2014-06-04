subroutine  cca_cfd_lb2nsc2socket_plain_port_create_client_instance(self,host,port,buffer_size) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     type(c_ptr)::host
     integer(kind=c_int)::port
     integer(kind=c_int)::buffer_size
     
     
end subroutine cca_cfd_lb2nsc2socket_plain_port_create_client_instance


subroutine  cca_cfd_lb2nsc2socket_plain_port_destroy_instance(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
end subroutine cca_cfd_lb2nsc2socket_plain_port_destroy_instance

subroutine  cca_cfd_lb2nsc2socket_plain_port_iterateBoundary(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     
end subroutine cca_cfd_lb2nsc2socket_plain_port_iterateBoundary
subroutine  cca_cfd_lb2nsc2socket_plain_port_iterateInner(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     
end subroutine cca_cfd_lb2nsc2socket_plain_port_iterateInner
subroutine  cca_cfd_lb2nsc2socket_plain_port_retrieveTimestep(self,&
	dt) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	real(kind=c_double),intent(inout)::dt

end subroutine cca_cfd_lb2nsc2socket_plain_port_retrieveTimestep
subroutine  cca_cfd_lb2nsc2socket_plain_port_retrieveVelocitiesSize(self,&
	memoryX,&
	memoryY,&
	memoryZ) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	integer(kind=c_int),intent(inout)::memoryX
	integer(kind=c_int),intent(inout)::memoryY
	integer(kind=c_int),intent(inout)::memoryZ

end subroutine cca_cfd_lb2nsc2socket_plain_port_retrieveVelocitiesSize
subroutine  cca_cfd_lb2nsc2socket_plain_port_retrieveVelocitiesCopy(self,&
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

end subroutine cca_cfd_lb2nsc2socket_plain_port_retrieveVelocitiesCopy