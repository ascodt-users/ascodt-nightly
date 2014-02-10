subroutine  examples_heat_stencilc2socket_plain_port_create_client_instance(self,host,port,buffer_size) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     type(c_ptr)::host
     integer(kind=c_int)::port
     integer(kind=c_int)::buffer_size
     
     
end subroutine examples_heat_stencilc2socket_plain_port_create_client_instance


subroutine  examples_heat_stencilc2socket_plain_port_destroy_instance(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
end subroutine examples_heat_stencilc2socket_plain_port_destroy_instance

subroutine  examples_heat_stencilc2socket_plain_port_getStencil(self,&
	stencil,stencil_len) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	real(kind=c_double),intent(inout),dimension(*)::stencil
	integer(kind=c_int),intent(in)::stencil_len

end subroutine examples_heat_stencilc2socket_plain_port_getStencil
