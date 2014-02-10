subroutine de_tum_foobar_f2c_nsd_create_client_instance(self,host,port,buffer_size) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     type(c_ptr)::host
     integer(kind=c_int)::port
     integer(kind=c_int)::buffer_size
end subroutine de_tum_foobar_f2c_nsd_create_client_instance


subroutine de_tum_foobar_f2c_nsd_destroy_instance(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
end subroutine de_tum_foobar_f2c_nsd_destroy_instance

subroutine  de_tum_foobar_f2c_nsd_foo(self,&
	data,data_len) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	real(kind=c_double),intent(in),dimension(*)::data
	integer(kind=c_int),intent(in)::data_len

end subroutine de_tum_foobar_f2c_nsd_foo
subroutine  de_tum_foobar_f2c_nsd_bar(self,&
	data,data_len) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     	real(kind=c_double),intent(inout),dimension(*)::data
	integer(kind=c_int),intent(in)::data_len

end subroutine de_tum_foobar_f2c_nsd_bar
subroutine  de_tum_foobar_f2c_nsd_reset(self) bind(c)
     use, intrinsic :: iso_c_binding
     integer(kind=c_long_long)::self
     
end subroutine de_tum_foobar_f2c_nsd_reset
