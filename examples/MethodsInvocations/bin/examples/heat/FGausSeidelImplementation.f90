!
! ASCoDT - Advanced Scientific Computing Development Toolkit
!
! This file was generated by ASCoDT's simplified SIDL compiler.
!
! Authors: Tobias Weinzierl, Atanas Atanasov   
!
module examples_heat_FGausSeidelImplementation
use examples_heat_fgausseidelAbstractImplementation
implicit none

type, extends ( FGausSeidelAbstractImplementation ), public :: FGausSeidelImplementation 
     ! Declaration of private members
     private 
     !list of procedures
     contains
     procedure,public::createInstance
     procedure,public::destroyInstance
     procedure,public::setup
procedure,public::solve

end type FGausSeidelImplementation
type(FGausSeidelImplementation ),allocatable::FGausSeidel_instance
contains 

subroutine createInstance(this)
    class( FGausSeidelImplementation)::this
    
end subroutine createInstance

subroutine destroyInstance(this)
     class( FGausSeidelImplementation)::this
     !put your destructor code here
end subroutine destroyInstance

subroutine solve(this,&
	dims,dims_len,&
	stencil,stencil_len,&
	rhs,rhs_len,&
	dof_handle)
    Use, intrinsic :: iso_c_binding
    class( FGausSeidelImplementation)::this
    	integer,intent(in),dimension(*)::dims
	integer,intent(in)::dims_len
	real(8),intent(in),dimension(*)::stencil
	integer,intent(in)::stencil_len
	real(8),intent(in),dimension(*)::rhs
	integer,intent(in)::rhs_len
	character(len=1),dimension(:),intent(in) ::dof_handle
        real(8),dimension(:),pointer::dof
	real(8)::residual 
	real(8)::temp
        real(8)::prec
	integer::center_index=0
	integer::center_index_left=0
	integer::center_index_right=0
	integer::center_index_bottom=0
	integer::center_index_top=0
        integer::i,j
	type(c_ptr)::ptr
	ptr=transfer(dof_handle,ptr) 
        call c_f_pointer(ptr,dof, shape=[dims(1)*dims(2)])
        residual = 2000.0
	temp=0.0
	prec=0.000006
	do while(residual>prec)
		residual=0.0
		do i=1,dims(2)-2
			do j=1,dims(1)-2 
				center_index = i*(dims(1))+j+1
				center_index_left = i*(dims(1))+j
				center_index_right = i*(dims(1))+j+2
				center_index_bottom = (i-1)*(dims(1))+j+1
				center_index_top= (i+1)*(dims(1))+j+1
				dof(center_index)= (rhs(center_index)-stencil(2)*dof(center_index_bottom) &
				                      -stencil(4)*dof(center_index_top) &
				                      -stencil(1)*dof(center_index_left) &
				                      -stencil(5)*dof(center_index_right))/stencil(3) 
			end do
		end do

		do i=1,dims(2)-2
			do j=1,dims(1)-2 
						center_index = i*(dims(1))+j+1
						center_index_left = i*(dims(1))+j
						center_index_right = i*(dims(1))+j+2
						center_index_bottom = (i-1)*(dims(1))+j+1
						center_index_top = (i+1)*(dims(1))+j+1

						temp= (rhs(center_index) &
								      -stencil(3)*dof(center_index) &
						                      -stencil(2)*dof(center_index_bottom) &
						                      -stencil(4)*dof(center_index_top) &
						                      -stencil(1)*dof(center_index_left) &
						                      -stencil(5)*dof(center_index_right))
						residual =residual+ (temp*temp)
			end do
		end do
		residual = sqrt(residual/((real(dims(1))-2.0)*(real(dims(2))-2.0)))
	end do
    !put your implementation here
end subroutine solve
subroutine setup(this,&
	precision,&
	iterations)
    class( FGausSeidelImplementation)::this
    	real(8),intent(in)::precision
	integer,intent(in)::iterations

    !put your implementation here
end subroutine setup


end module  examples_heat_FGausSeidelImplementation



PROGRAM FGausSeidel
    call main_loop()

end PROGRAM