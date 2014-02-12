//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package examples.heat;


public class AppDriverBasisJavaImplementation extends examples.heat.AppDriverAbstractJavaImplementation {
	private int[] _dims; 
	private double _tend;
	private double _dt;
	private double [] _stencilCopy;
	private long[] _meshHandle;
	public AppDriverBasisJavaImplementation( String identifier ) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
		super(identifier);
		_dims=new int[2];
		_tend=1.0;
		_dt=1.0/64.0;
		_dims[0]=64;
		_dims[1]=64;
		_stencilCopy=new double[5];
		_meshHandle=new long[1];
	}
	public void setup (){
		int []ghosted_dims =new int [2];
		ghosted_dims[0]=_dims[0]+2;
		ghosted_dims[1]=_dims[1]+2;
		
		this._mesh.allocate(ghosted_dims);
		double []rhs = new double[ghosted_dims[0]*ghosted_dims[1]];
		this._mesh.copyData(rhs);
		this._vis.addCellScalars("T",rhs);
		this._vis.render();
	
	}
	@Override
	public void go() {
		int []ghosted_dims =new int [2];
		ghosted_dims[0]=_dims[0]+2;
		ghosted_dims[1]=_dims[1]+2;
		this._mesh.allocate(ghosted_dims);
		this._vis.setDimensions(
				new int []{ghosted_dims[0],ghosted_dims[1],1}
				);
		this._vis.setOffset(new double[]{0.0,0.0,0.0});

		this._vis.setDomain(new double[]{1.0,1.0,0.0});
		this._mesh.getData(_meshHandle);
		this._stencil.getStencil(_stencilCopy);
		double currentTime=0.0;
		double []rhs = new double[ghosted_dims[0]*ghosted_dims[1]];
		this._mesh.copyData(rhs);
		long startT=System.currentTimeMillis();
		while(currentTime<_tend){
			
			this._integrator.step(ghosted_dims, _dt, rhs, _stencilCopy, _meshHandle[0]);
			currentTime+=_dt;
			this._mesh.copyData(rhs);
			//this._vis.addCellScalars("T",rhs);
			//this._vis.render();
		}
		long endT=System.currentTimeMillis();
		System.out.println("sim time:"+(endT-startT));
	}

	/**
	 * Provides methods block
	 */

}

