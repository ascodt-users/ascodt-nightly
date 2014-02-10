subroutine examples_heat_fmesh_f2c_nsd_create_client_instance(self,host,port,buffer_size) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     type(c_ptr)::host
     integer(kind=c_int)::port
     integer(kind=c_int)::buffer_size
end subroutine examples_heat_fmesh_f2c_nsd_create_client_instance


subroutine examples_heat_fmesh_f2c_nsd_destroy_instance(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
end subroutine examples_heat_fmesh_f2c_nsd_destroy_instance

subroutine  examples_heat_fmesh_f2c_nsd_allocate(self,&
	dim,dim_len) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	integer(kind=c_int),intent(in),dimension(*)::dim
	integer(kind=c_int),intent(in)::dim_len

end subroutine examples_heat_fmesh_f2c_nsd_allocate
subroutine  examples_heat_fmesh_f2c_nsd_copyData(self,&
	data,data_len) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	real(kind=c_double),intent(inout),dimension(*)::data
	integer(kind=c_int),intent(in)::data_len

end subroutine examples_heat_fmesh_f2c_nsd_copyData
subroutine  examples_heat_fmesh_f2c_nsd_getData(self,&
	handle) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     
end subroutine examples_heat_fmesh_f2c_nsd_getData
