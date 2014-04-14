subroutine  cca_cfd_nssolverc2socket_plain_port_create_client_instance(self,host,port,buffer_size) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     type(c_ptr)::host
     integer(kind=c_int)::port
     integer(kind=c_int)::buffer_size
     
     
end subroutine cca_cfd_nssolverc2socket_plain_port_create_client_instance


subroutine  cca_cfd_nssolverc2socket_plain_port_destroy_instance(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
end subroutine cca_cfd_nssolverc2socket_plain_port_destroy_instance

subroutine  cca_cfd_nssolverc2socket_plain_port_setup(self,&
	inputScenario) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	type(c_ptr),intent(in)::inputScenario

end subroutine cca_cfd_nssolverc2socket_plain_port_setup
subroutine  cca_cfd_nssolverc2socket_plain_port_setupCommForLBRegion(self,&
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

end subroutine cca_cfd_nssolverc2socket_plain_port_setupCommForLBRegion
subroutine  cca_cfd_nssolverc2socket_plain_port_solve(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     
end subroutine cca_cfd_nssolverc2socket_plain_port_solve
subroutine  cca_cfd_nssolverc2socket_plain_port_solveOneTimestepPhaseOne(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     
end subroutine cca_cfd_nssolverc2socket_plain_port_solveOneTimestepPhaseOne
subroutine  cca_cfd_nssolverc2socket_plain_port_solveOneTimestepPhaseTwo(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     
end subroutine cca_cfd_nssolverc2socket_plain_port_solveOneTimestepPhaseTwo
subroutine  cca_cfd_nssolverc2socket_plain_port_setVelocities(self,&
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

end subroutine cca_cfd_nssolverc2socket_plain_port_setVelocities
subroutine  cca_cfd_nssolverc2socket_plain_port_printNSPressure(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     
end subroutine cca_cfd_nssolverc2socket_plain_port_printNSPressure
subroutine  cca_cfd_nssolverc2socket_plain_port_printNSProfiles(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     
end subroutine cca_cfd_nssolverc2socket_plain_port_printNSProfiles
subroutine  cca_cfd_nssolverc2socket_plain_port_closeNSProfiles(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     
end subroutine cca_cfd_nssolverc2socket_plain_port_closeNSProfiles
subroutine  cca_cfd_nssolverc2socket_plain_port_iterateBoundary(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     
end subroutine cca_cfd_nssolverc2socket_plain_port_iterateBoundary
subroutine  cca_cfd_nssolverc2socket_plain_port_iterateInner(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     
end subroutine cca_cfd_nssolverc2socket_plain_port_iterateInner
subroutine  cca_cfd_nssolverc2socket_plain_port_forwardVelocities(self,&
	keys,keys_len,&
	offsets,offsets_len,&
	flips,flips_len,&
	values,values_len,&
	componentSize,componentSize_len,&
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
	integer(kind=c_int),intent(in),dimension(*)::componentSize
	integer(kind=c_int),intent(in)::componentSize_len
	integer(kind=c_int),intent(inout)::ackn

end subroutine cca_cfd_nssolverc2socket_plain_port_forwardVelocities
subroutine  cca_cfd_nssolverc2socket_plain_port_plot(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     
end subroutine cca_cfd_nssolverc2socket_plain_port_plot
subroutine  cca_cfd_nssolverc2socket_plain_port_syncr(self,&
	value) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	integer(kind=c_int),intent(inout)::value

end subroutine cca_cfd_nssolverc2socket_plain_port_syncr
