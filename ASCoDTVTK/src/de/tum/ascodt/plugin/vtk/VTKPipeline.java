package de.tum.ascodt.plugin.vtk;


import vtk.vtkProp;
import vtk.vtkRenderWindowInteractor;
import de.tum.ascodt.plugin.ASCoDTVTKPlugin;
import de.tum.ascodt.plugin.utils.tracing.Trace;
import de.tum.ascodt.utils.exceptions.ASCoDTException;


/**
 * An abstract class, which encapsulates a vtk pipeline. The derived class
 * should define the vtk pipeline in createPipeline method. After initialisation
 * the pipeline is added to the vtk view. To control the visibility of the
 * pipeline on
 * can use the visiblity setters. Only pipelines defined in createPipeline will
 * be added
 * to the vtk view and removed by object destruction
 * 
 * @author Atanas Atanasov
 * 
 */
public abstract class VTKPipeline {

  /**
   * reference to pipeline
   */
  private vtkProp _pipeline;
  private Trace _trace = new Trace(VTKPipeline.class.getCanonicalName());

  protected VTKPipeline() {

    _pipeline = createPipeline();
    assert _pipeline != null;
    ASCoDTVTKPlugin.getDefault().getVTKService().addPipeline(_pipeline);
  }

  public void addObserver(String event, String method) {
    ASCoDTVTKPlugin.getDefault().getVTKService()
        .addObserver(event, this, method);
  }

  protected abstract vtkProp createPipeline();

  public void dispose() {

    unregisterForPicking();
    finalize();
    repaint();
  }

  /**
   * here we need to free the memory used by the pipeline
   */
  @Override
  protected void finalize() {
    if (_pipeline != null) {
      _trace.in("finalize()");
      ASCoDTVTKPlugin.getDefault().getVTKService().removePipeline(_pipeline);
      _pipeline = null;
      _trace.out("finalize()");
    }
  }

  public vtkRenderWindowInteractor getInteractor() throws ASCoDTException {
    try {
      return ASCoDTVTKPlugin.getDefault().getVTKService().getInteractor();
    } catch (Exception e) {
      throw new ASCoDTException(VTKPipeline.class.getCanonicalName(),
          "getInteractor()", e.getLocalizedMessage(), e);
    }
  }

  public void lock() {
    ASCoDTVTKPlugin.getDefault().getVTKService().lock();
  }

  abstract public void OnPickEvent(double[] pos);

  public void registerForPicking() {
    ASCoDTVTKPlugin.getDefault().getVTKService()
        .registerPipelineForPicking(this);
  }

  public void repaint() {
    ASCoDTVTKPlugin.getDefault().getVTKService().repaint();
  }

  /**
   * controls the visibility of the pipeline
   * 
   * @param visibility
   */
  public void setVisiblity(boolean visibility) {
    assert _pipeline != null;
    _pipeline.SetVisibility(visibility ? 1 : 0);
    ASCoDTVTKPlugin.getDefault().getVTKService().repaint();

  }

  public void unlock() {
    ASCoDTVTKPlugin.getDefault().getVTKService().unlock();
  }

  public void unregisterForPicking() {
    ASCoDTVTKPlugin.getDefault().getVTKService()
        .unregisterPipelineForPicking(this);
  }

}
