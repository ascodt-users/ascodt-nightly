subroutine examples_heat_solver_f2c_nsd_create_client_instance(self,host,port,buffer_size) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     type(c_ptr)::host
     integer(kind=c_int)::port
     integer(kind=c_int)::buffer_size
end subroutine examples_heat_solver_f2c_nsd_create_client_instance


subroutine examples_heat_solver_f2c_nsd_destroy_instance(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
end subroutine examples_heat_solver_f2c_nsd_destroy_instance

subroutine  examples_heat_solver_f2c_nsd_setup(self,&
	precision,&
	iterations) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	real(kind=c_double),intent(in)::precision
	integer(kind=c_int),intent(in)::iterations

end subroutine examples_heat_solver_f2c_nsd_setup
subroutine  examples_heat_solver_f2c_nsd_solve(self,&
	dims,dims_len,&
	stencil,stencil_len,&
	rhs,rhs_len,&
	dof_handle) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	integer(kind=c_int),intent(in),dimension(*)::dims
	integer(kind=c_int),intent(in)::dims_len
	real(kind=c_double),intent(in),dimension(*)::stencil
	integer(kind=c_int),intent(in)::stencil_len
	real(kind=c_double),intent(in),dimension(*)::rhs
	integer(kind=c_int),intent(in)::rhs_len

end subroutine examples_heat_solver_f2c_nsd_solve
