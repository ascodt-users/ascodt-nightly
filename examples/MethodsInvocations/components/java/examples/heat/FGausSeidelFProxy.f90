subroutine FGausSeidel_fproxy_createInstance(this) 
     Use examples_heat_FGausSeidelImplementation
     Use, intrinsic :: iso_c_binding
     Type( c_ptr ),intent(inout) :: this
     allocate(FGausSeidel_instance)
     call FGausSeidel_instance%createInstance()
     this=c_loc(FGausSeidel_instance)
end subroutine FGausSeidel_fproxy_createInstance

subroutine FGausSeidel_fproxy_destroyInstance(this) 
     Use examples_heat_FGausSeidelImplementation
     Use, intrinsic :: iso_c_binding
     Type( c_ptr ),intent(in) :: this
     type( FGausSeidelImplementation ),pointer :: pt
     call c_f_pointer(this,pt)
     call pt%destroyInstance()
     deallocate(pt)
end subroutine FGausSeidel_fproxy_destroyInstance


subroutine FGausSeidel_fproxy_setup(this,&
	precision,&
	iterations) 
    Use examples_heat_FGausSeidelImplementation
    Use, intrinsic :: iso_c_binding
    Type( c_ptr ),intent(in) :: this
    type( FGausSeidelImplementation ),pointer :: pt
    	real(kind=c_double),intent(in)::precision
	integer(kind=c_int),intent(in)::iterations

    
    call c_f_pointer(this,pt)
    call pt%setup(&
precision,&
iterations)
end subroutine FGausSeidel_fproxy_setup

subroutine FGausSeidel_fproxy_solve(this,&
	dims,dims_len,&
	stencil,stencil_len,&
	rhs,rhs_len,&
	dof_handle) 
    Use examples_heat_FGausSeidelImplementation
    Use, intrinsic :: iso_c_binding
    Type( c_ptr ),intent(in) :: this
    type( FGausSeidelImplementation ),pointer :: pt
    	integer(kind=c_int),intent(in),dimension(*)::dims
	integer(kind=c_int),intent(in)::dims_len
	real(kind=c_double),intent(in),dimension(*)::stencil
	integer(kind=c_int),intent(in)::stencil_len
	real(kind=c_double),intent(in),dimension(*)::rhs
	integer(kind=c_int),intent(in)::rhs_len
	type(c_ptr),intent(in)::dof_handle
	character(len=1), allocatable ::dof_handle_handle(:)
	integer::dof_handle_len

    dof_handle_len = size(transfer(dof_handle, dof_handle_handle))
allocate(dof_handle_handle(dof_handle_len))
dof_handle_handle = transfer(dof_handle, dof_handle_handle)

    call c_f_pointer(this,pt)
    call pt%solve(&
dims,dims_len,&
stencil,stencil_len,&
rhs,rhs_len,&
dof_handle_handle)
end subroutine FGausSeidel_fproxy_solve
