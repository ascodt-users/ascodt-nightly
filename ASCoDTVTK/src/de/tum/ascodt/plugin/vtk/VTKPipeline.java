package de.tum.ascodt.plugin.vtk;


import org.eclipse.ui.PartInitException;

import de.tum.ascodt.plugin.ASCoDTVTKPlugin;
import de.tum.ascodt.plugin.utils.tracing.Trace;
import de.tum.ascodt.utils.exceptions.ASCoDTException;

import vtk.*;

/**
 * An abstract class, which encapsulates a vtk pipeline. The derived class
 * should define the vtk pipeline in createPipeline method. After initialisation
 * the pipeline is added to the vtk view. To control the visibility of the pipeline on 
 * can use the visiblity setters. Only pipelines defined in createPipeline will be added 
 * to the vtk view and removed by object destruction
 * @author Atanas Atanasov
 *
 */
public abstract class VTKPipeline {
	
	/**
	 * reference to pipeline
	 */
	protected vtkProp _pipeline;
	private Trace _trace=new Trace(VTKPipeline.class.getCanonicalName());
	protected VTKPipeline(){
		
		_pipeline=createPipeline();
		assert(_pipeline!=null);
		ASCoDTVTKPlugin.getDefault().getVTKService().addPipeline(_pipeline);
	}
	protected abstract vtkProp createPipeline();
	
	public void registerForPicking(){
		ASCoDTVTKPlugin.getDefault().getVTKService().registerPipelineForPicking(this);
	}
	
	public void unregisterForPicking(){
		ASCoDTVTKPlugin.getDefault().getVTKService().unregisterPipelineForPicking(this);
	}
	
	/**
	 * controls the visibility of the pipeline
	 * @param visibility
	 */
	public void setVisiblity(boolean visibility){
		assert(_pipeline!=null);
		_pipeline.SetVisibility((visibility)?1:0);
		ASCoDTVTKPlugin.getDefault().getVTKService().repaint();
		
	}
	public vtkRenderWindowInteractor getInteractor() throws ASCoDTException{
		try {
			return ASCoDTVTKPlugin.getDefault().getVTKService().getInteractor();
		} catch (Exception e) {
			throw new ASCoDTException(VTKPipeline.class.getCanonicalName(),"getInteractor()",e.getLocalizedMessage(),e);
		}
	}
	
	public void addObserver(String event,String method){
		ASCoDTVTKPlugin.getDefault().getVTKService().addObserver(event, this, method);
	}
	
	public void lock(){
		ASCoDTVTKPlugin.getDefault().getVTKService().lock();
	}
	
	public void unlock(){
		ASCoDTVTKPlugin.getDefault().getVTKService().unlock();
	}
	
	public void repaint(){
		ASCoDTVTKPlugin.getDefault().getVTKService().repaint();
	}
	
	public void dispose(){

		unregisterForPicking();
		finalize();
		repaint();
	}
	/**
	 * here we need to free the memory used by the pipeline
	 */
	protected void finalize(){
		if(_pipeline!=null){
			_trace.in("finalize()");
			ASCoDTVTKPlugin.getDefault().getVTKService().removePipeline(_pipeline);
			_pipeline=null;
			_trace.out("finalize()");
		}
	}
	
	abstract public void OnPickEvent(double[] pos);
	

}
