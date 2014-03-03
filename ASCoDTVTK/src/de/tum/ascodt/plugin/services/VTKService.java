package de.tum.ascodt.plugin.services;


import org.eclipse.swt.widgets.Display;
import org.eclipse.ui.PartInitException;
import org.eclipse.ui.PlatformUI;

import vtk.vtkProp;
import vtk.vtkRenderWindowInteractor;
import de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice;
import de.tum.ascodt.plugin.views.VTKView;
import de.tum.ascodt.plugin.vtk.VTKPipeline;
import de.tum.ascodt.utils.exceptions.ASCoDTException;


/**
 * 
 * @author Atanas Atanasov
 *         This service is access point to the vtk view. Clients can add,
 *         remove, turn on/off pipelines
 *         To repaint the complete scene invoke the repaint method
 */
public class VTKService {

  private VTKView _view;

  public void addObserver(final String event, final Object target,
      final String method) {
    PlatformUI.getWorkbench().getDisplay().syncExec(new Runnable() {

      @Override
      public void run() {
        try {
          initView();
          getVTKView().addObserver(event, target, method);
        } catch (PartInitException e) {
          ErrorWriterDevice.getInstance().showError(getClass().getName(),
              "getVTKView()", "vtk view cannot be initialized", e);
        } catch (InterruptedException e) {
          ErrorWriterDevice.getInstance().showError(getClass().getName(),
              "addPipeline()", "vtk view waitng thread interrupted", e);
        } catch (ASCoDTException e) {
          ErrorWriterDevice.getInstance().showError(getClass().getName(),
              "removePipeline()",
              "Cannot remove the vtk pipeline from the view", e);
        }
      }

    });

  }

  /**
   * add visualization pipeline to specific vtk view
   * 
   * @param vtkProp
   *          actor of the pipeline
   */
  public void addPipeline(final vtkProp pipeline) {
    PlatformUI.getWorkbench().getDisplay().asyncExec(new Runnable() {

      @Override
      public void run() {
        try {
          initView();
          getVTKView().addPipeline(pipeline);
          repaint();
        } catch (PartInitException e) {
          ErrorWriterDevice.getInstance().showError(getClass().getName(),
              "getVTKView()", "vtk view cannot be initialized", e);
        } catch (InterruptedException e) {
          ErrorWriterDevice.getInstance().showError(getClass().getName(),
              "addPipeline()", "vtk view waitng thread interrupted", e);
        } catch (ASCoDTException e) {
          ErrorWriterDevice.getInstance().showError(getClass().getName(),
              "addPipeline()", "Cannot add new pipeline", e);
        }
      }

    });
  }

  public vtkRenderWindowInteractor getInteractor() throws PartInitException,
      InterruptedException, ASCoDTException {
    initView();
    return getVTKView().getInteractor();
  }

  /**
   * A getter for the vtk view
   * 
   * @return
   * @throws ASCoDTException
   * @throws PartInitException
   */
  private VTKView getVTKView() throws ASCoDTException {
    if (isValid()) {
      return _view;
    }

    throw new ASCoDTException(getClass().getName(), "getVTKView()",
        "calling getVTKView() with non valid eclipse setup", null);
  }

  private void initView() throws InterruptedException, PartInitException {
    while (!isValid()) {
      Thread.sleep(100);
    }
    if (_view == null) {
      setView((VTKView)PlatformUI.getWorkbench().getActiveWorkbenchWindow()
          .getActivePage().showView(VTKView.ID));
    }
  }

  /**
   * validity check if the vtk view can be displayed
   * 
   * @return
   */
  private boolean isValid() {

    if (_view == null) {

      boolean res = false;
      class CustomRunnable implements Runnable {

        boolean _valid = false;

        @Override
        public void run() {
          _valid = !(PlatformUI.getWorkbench() == null ||
              PlatformUI.getWorkbench().getActiveWorkbenchWindow() == null || PlatformUI
              .getWorkbench().getActiveWorkbenchWindow().getActivePage() == null);
        }
      }
      CustomRunnable r = new CustomRunnable();
      Display.getDefault().syncExec(r);
      res = r._valid;
      return res;

    }
    return true;
  }

  public void lock() {

    try {
      getVTKView().lock();
    } catch (ASCoDTException e) {
      ErrorWriterDevice.getInstance()
          .showError(getClass().getName(), "removePipeline()",
              "Cannot remove the vtk pipeline from the view", e);
    }

  }

  public void registerPipelineForPicking(final VTKPipeline pipe) {
    PlatformUI.getWorkbench().getDisplay().asyncExec(new Runnable() {

      @Override
      public void run() {
        try {
          initView();

          getVTKView().registerPipelineForPicking(pipe);
        } catch (ASCoDTException e) {
          ErrorWriterDevice.getInstance().showError(getClass().getName(),
              "removePipeline()",
              "Cannot remove the vtk pipeline from the view", e);
        } catch (PartInitException e) {
          // TODO Auto-generated catch block
          e.printStackTrace();
        } catch (InterruptedException e) {
          // TODO Auto-generated catch block
          e.printStackTrace();
        }
      }
    });
  }

  /**
   * remove visualization pipeline from specific vtk view
   * 
   * @param vtkProp
   */
  public void removePipeline(final vtkProp vtkProp) {

    try {
      getVTKView().removePipeline(vtkProp);
    } catch (ASCoDTException e) {
      ErrorWriterDevice.getInstance()
          .showError(getClass().getName(), "removePipeline()",
              "Cannot remove the vtk pipeline from the view", e);
    }

  }

  /**
   * repaint a specific vtk view
   */
  public void repaint() {

    try {
      getVTKView().render();
    } catch (ASCoDTException e) {
      ErrorWriterDevice.getInstance()
          .showError(getClass().getName(), "removePipeline()",
              "Cannot remove the vtk pipeline from the view", e);
    }

  }

  public void setView(VTKView view) {
    _view = view;
  }

  public void unlock() {

    try {
      getVTKView().unlock();
    } catch (ASCoDTException e) {
      ErrorWriterDevice.getInstance()
          .showError(getClass().getName(), "removePipeline()",
              "Cannot remove the vtk pipeline from the view", e);
    }

  }

  public void unregisterPipelineForPicking(VTKPipeline pipe) {
    try {
      getVTKView().unregisterPipelineForPicking(pipe);
    } catch (ASCoDTException e) {
      ErrorWriterDevice.getInstance()
          .showError(getClass().getName(), "removePipeline()",
              "Cannot remove the vtk pipeline from the view", e);
    }
  }
}
