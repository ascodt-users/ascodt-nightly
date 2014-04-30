subroutine  cca_cfd_lbsolverc2socket_plain_port_create_client_instance(self,host,port,buffer_size) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     type(c_ptr)::host
     integer(kind=c_int)::port
     integer(kind=c_int)::buffer_size
     
     
end subroutine cca_cfd_lbsolverc2socket_plain_port_create_client_instance


subroutine  cca_cfd_lbsolverc2socket_plain_port_destroy_instance(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
end subroutine cca_cfd_lbsolverc2socket_plain_port_destroy_instance

subroutine  cca_cfd_lbsolverc2socket_plain_port_setup(self,&
	inputScenario) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	type(c_ptr),intent(in)::inputScenario

end subroutine cca_cfd_lbsolverc2socket_plain_port_setup
subroutine  cca_cfd_lbsolverc2socket_plain_port_setupCommForNSRegion(self,&
	startOfRegion,startOfRegion_len,&
	endOfRegion,endOfRegion_len,&
	commids,commids_len) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	integer(kind=c_int),intent(in),dimension(*)::startOfRegion
	integer(kind=c_int),intent(in)::startOfRegion_len
	integer(kind=c_int),intent(in),dimension(*)::endOfRegion
	integer(kind=c_int),intent(in)::endOfRegion_len
	integer(kind=c_int),intent(in)::commids_len
	type(c_ptr),dimension(*),intent(in)::commids

end subroutine cca_cfd_lbsolverc2socket_plain_port_setupCommForNSRegion
subroutine  cca_cfd_lbsolverc2socket_plain_port_solve(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     
end subroutine cca_cfd_lbsolverc2socket_plain_port_solve
subroutine  cca_cfd_lbsolverc2socket_plain_port_solveOneTimestep(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     
end subroutine cca_cfd_lbsolverc2socket_plain_port_solveOneTimestep
subroutine  cca_cfd_lbsolverc2socket_plain_port_setVelocities(self,&
	velocitiesX,velocitiesX_len,&
	velocitiesY,velocitiesY_len,&
	velocitiesZ,velocitiesZ_len) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	real(kind=c_double),intent(in),dimension(*)::velocitiesX
	integer(kind=c_int),intent(in)::velocitiesX_len
	real(kind=c_double),intent(in),dimension(*)::velocitiesY
	integer(kind=c_int),intent(in)::velocitiesY_len
	real(kind=c_double),intent(in),dimension(*)::velocitiesZ
	integer(kind=c_int),intent(in)::velocitiesZ_len

end subroutine cca_cfd_lbsolverc2socket_plain_port_setVelocities
subroutine  cca_cfd_lbsolverc2socket_plain_port_setPressure(self,&
	pressure,pressure_len) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	real(kind=c_double),intent(in),dimension(*)::pressure
	integer(kind=c_int),intent(in)::pressure_len

end subroutine cca_cfd_lbsolverc2socket_plain_port_setPressure
subroutine  cca_cfd_lbsolverc2socket_plain_port_setGradients(self,&
	gradients,gradients_len) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	real(kind=c_double),intent(in),dimension(*)::gradients
	integer(kind=c_int),intent(in)::gradients_len

end subroutine cca_cfd_lbsolverc2socket_plain_port_setGradients
subroutine  cca_cfd_lbsolverc2socket_plain_port_closeLBProfiles(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     
end subroutine cca_cfd_lbsolverc2socket_plain_port_closeLBProfiles
subroutine  cca_cfd_lbsolverc2socket_plain_port_printLBDensity(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     
end subroutine cca_cfd_lbsolverc2socket_plain_port_printLBDensity
subroutine  cca_cfd_lbsolverc2socket_plain_port_printLBProfiles(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     
end subroutine cca_cfd_lbsolverc2socket_plain_port_printLBProfiles
subroutine  cca_cfd_lbsolverc2socket_plain_port_forwardVelocities(self,&
	keys,keys_len,&
	offsets,offsets_len,&
	flips,flips_len,&
	values,values_len,&
	ackn) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	integer(kind=c_int),intent(in),dimension(*)::keys
	integer(kind=c_int),intent(in)::keys_len
	integer(kind=c_int),intent(in),dimension(*)::offsets
	integer(kind=c_int),intent(in)::offsets_len
	integer(kind=c_int),intent(in),dimension(*)::flips
	integer(kind=c_int),intent(in)::flips_len
	real(kind=c_double),intent(in),dimension(*)::values
	integer(kind=c_int),intent(in)::values_len
	integer(kind=c_int),intent(inout)::ackn

end subroutine cca_cfd_lbsolverc2socket_plain_port_forwardVelocities
subroutine  cca_cfd_lbsolverc2socket_plain_port_forwardPressure(self,&
	keys,keys_len,&
	offsets,offsets_len,&
	flips,flips_len,&
	values,values_len,&
	ackn) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	integer(kind=c_int),intent(in),dimension(*)::keys
	integer(kind=c_int),intent(in)::keys_len
	integer(kind=c_int),intent(in),dimension(*)::offsets
	integer(kind=c_int),intent(in)::offsets_len
	integer(kind=c_int),intent(in),dimension(*)::flips
	integer(kind=c_int),intent(in)::flips_len
	real(kind=c_double),intent(in),dimension(*)::values
	integer(kind=c_int),intent(in)::values_len
	integer(kind=c_int),intent(inout)::ackn

end subroutine cca_cfd_lbsolverc2socket_plain_port_forwardPressure
subroutine  cca_cfd_lbsolverc2socket_plain_port_syncr(self,&
	value) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	integer(kind=c_int),intent(inout)::value

end subroutine cca_cfd_lbsolverc2socket_plain_port_syncr
subroutine  cca_cfd_lbsolverc2socket_plain_port_plot(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     
end subroutine cca_cfd_lbsolverc2socket_plain_port_plot
