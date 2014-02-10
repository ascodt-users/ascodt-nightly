subroutine examples_heat_regulargrid_f2c_nsd_create_client_instance(self,host,port,buffer_size) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     type(c_ptr)::host
     integer(kind=c_int)::port
     integer(kind=c_int)::buffer_size
end subroutine examples_heat_regulargrid_f2c_nsd_create_client_instance


subroutine examples_heat_regulargrid_f2c_nsd_destroy_instance(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
end subroutine examples_heat_regulargrid_f2c_nsd_destroy_instance

subroutine  examples_heat_regulargrid_f2c_nsd_setOffset(self,&
	offset,offset_len) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	real(kind=c_double),intent(in),dimension(*)::offset
	integer(kind=c_int),intent(in)::offset_len

end subroutine examples_heat_regulargrid_f2c_nsd_setOffset
subroutine  examples_heat_regulargrid_f2c_nsd_setDomain(self,&
	domain,domain_len) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	real(kind=c_double),intent(in),dimension(*)::domain
	integer(kind=c_int),intent(in)::domain_len

end subroutine examples_heat_regulargrid_f2c_nsd_setDomain
subroutine  examples_heat_regulargrid_f2c_nsd_setDimensions(self,&
	dimensions,dimensions_len) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	integer(kind=c_int),intent(in),dimension(*)::dimensions
	integer(kind=c_int),intent(in)::dimensions_len

end subroutine examples_heat_regulargrid_f2c_nsd_setDimensions
subroutine  examples_heat_regulargrid_f2c_nsd_addCellScalars(self,&
	variableName,&
	scalars,scalars_len) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	type(c_ptr),intent(in)::variableName
	real(kind=c_double),intent(in),dimension(*)::scalars
	integer(kind=c_int),intent(in)::scalars_len

end subroutine examples_heat_regulargrid_f2c_nsd_addCellScalars
subroutine  examples_heat_regulargrid_f2c_nsd_render(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     
end subroutine examples_heat_regulargrid_f2c_nsd_render
