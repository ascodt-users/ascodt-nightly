subroutine  examples_heat_plotter2dc2socket_plain_port_create_client_instance(self,host,port,buffer_size) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     type(c_ptr)::host
     integer(kind=c_int)::port
     integer(kind=c_int)::buffer_size
     
     
end subroutine examples_heat_plotter2dc2socket_plain_port_create_client_instance


subroutine  examples_heat_plotter2dc2socket_plain_port_destroy_instance(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
end subroutine examples_heat_plotter2dc2socket_plain_port_destroy_instance

subroutine  examples_heat_plotter2dc2socket_plain_port_plotPoint(self,&
	name,&
	x,&
	y) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	type(c_ptr),intent(in)::name
	real(kind=c_double),intent(in)::x
	real(kind=c_double),intent(in)::y

end subroutine examples_heat_plotter2dc2socket_plain_port_plotPoint
