package de.tum.ascodt.plugin.views;


import java.awt.Frame;
import java.lang.reflect.InvocationTargetException;
import java.util.LinkedList;
import java.util.List;

import javax.swing.SwingUtilities;

import org.eclipse.swt.SWT;
import org.eclipse.swt.awt.SWT_AWT;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.ui.part.ViewPart;

import vtk.vtkActor;
import vtk.vtkCanvas;
import vtk.vtkCellPicker;
import vtk.vtkInteractorStyleTrackballCamera;
import vtk.vtkProp;
import vtk.vtkRenderWindowInteractor;
import de.tum.ascodt.plugin.utils.tracing.Trace;
import de.tum.ascodt.plugin.vtk.VTKPipeline;
import de.tum.ascodt.utils.exceptions.ASCoDTException;


/**
 * This view can be used to represent vtk pipelines
 * 
 * @author Atanas Atanasov
 * 
 */
public class VTKView extends ViewPart {

  public static final String ID = VTKView.class.getCanonicalName();

  /**
   * a controller where to embed the vtk window
   */
  private Composite _composite;

  /**
   * vtk canvas object
   */
  private vtkCanvas _panel;
  private vtkCellPicker _picker;

  private Frame _frame;
  private List<VTKPipeline> _pickablePipelines;
  private Trace _trace = new Trace(VTKView.class.getCanonicalName());

  public VTKView() {
    _pickablePipelines = new LinkedList<VTKPipeline>();
  }

  public void addObserver(String event, Object target, String method) {
    _panel.GetRenderWindow().GetInteractor().AddObserver(event, target, method);
  }

  /**
   * This function adds a vtk pipeline to the current view
   * 
   * @param actor
   *          the actor representing the current pipeline
   * @throws InvocationTargetException
   * @throws InterruptedException
   */
  public void addPipeline(final vtkProp actor) throws ASCoDTException {
    _trace.in("addPipeline()");
    if (_panel != null) {
      if (!SwingUtilities.isEventDispatchThread()) {
        SwingUtilities.invokeLater(new Runnable() {

          @Override
          public void run() {
            _panel.GetRenderWindow()
                  .GetRenderers()
                  .GetFirstRenderer()
                  .AddViewProp(actor);
          }

        });
      } else {
        _panel.GetRenderWindow()
              .GetRenderers()
              .GetFirstRenderer()
              .AddViewProp(actor);
      }
    }
    _trace.out("addPipeline()");
  }

  /**
   * method to setup the content of the view
   */
  @Override
  public void createPartControl(Composite parent) {
    _composite = new Composite(parent, SWT.EMBEDDED);
    _frame = SWT_AWT.new_Frame(_composite);
    _panel = new vtkCanvas();
    vtkActor dummyActor = new vtkActor();
    // _panel.GetRenderWindow().DoubleBufferOn();
    _panel.GetRenderWindow()
          .GetRenderers()
          .GetFirstRenderer()
          .AddActor(dummyActor);
    _panel.GetRenderWindow()
          .GetInteractor()
          .SetInteractorStyle(new vtkInteractorStyleTrackballCamera());
    _panel.GetRenderWindow()
          .GetRenderers()
          .GetFirstRenderer()
          .SetBackground(0, 0, 0);
    // _picker=new vtkCellPicker();
    // _panel.addMouseMotionListener(new MouseMotionListener(){
    //
    // @Override
    // public void mouseDragged(MouseEvent e) {
    //
    // }
    //
    // @Override
    // public void mouseMoved(MouseEvent e) {
    // lock();
    // double [] pos=null;
    // int
    // pick_flag=_picker.Pick(e.getX(),_panel.getHeight()-e.getY()-1,0.0,_panel.GetRenderWindow().GetRenderers().GetFirstRenderer());
    // if(pick_flag==1)
    // pos=_picker.GetPickPosition();
    //
    // unlock();
    // if(pos!=null){
    // for(VTKPipeline pipeline:_pickablePipelines)
    // pipeline.OnPickEvent(pos);
    //
    // }else
    // for(VTKPipeline pipeline:_pickablePipelines)
    // pipeline.OnPickEvent(new double[]{0.0,0.0,0.0});
    //
    //
    // }
    //
    // });
    _frame.add(_panel);

  }

  public vtkRenderWindowInteractor getInteractor() {
    return _panel.GetRenderWindow().GetInteractor();
  }

  public void lock() {
    // if(!SwingUtilities.isEventDispatchThread()){
    // try {
    // SwingUtilities.invokeLater(new Runnable(){
    //
    // @Override
    // public void run() {
    // _panel.lock();
    //
    // }
    //
    // });
    // } catch (InterruptedException e) {
    // throw new ASCoDTException(getClass().getName(), "addPipeline()",
    // "add pipeline interrupted", e);
    // } catch (InvocationTargetException e) {
    // throw new ASCoDTException(getClass().getName(), "addPipeline()",
    // "invocation error during add pipeline", e);
    // }
    // }else{
    // _panel.lock();
    // }
  }

  public void registerPipelineForPicking(VTKPipeline pipe) {
    _pickablePipelines.add(pipe);
  }

  /**
   * this function removes a pipeline from the existing view
   * 
   * @param act
   *          the actor to be removed
   * @throws InvocationTargetException
   * @throws InterruptedException
   */
  public void removePipeline(final vtkProp act) throws ASCoDTException {
    _trace.in("removePipeline()");
    if (!SwingUtilities.isEventDispatchThread()) {
      SwingUtilities.invokeLater(new Runnable() {

        @Override
        public void run() {
          if (_panel.GetRenderWindow()
                    .GetRenderers()
                    .GetFirstRenderer()
                    .GetViewProps()
                    .IsItemPresent(act) != 0) {
            _panel.GetRenderWindow()
                  .GetRenderers()
                  .GetFirstRenderer()
                  .RemoveViewProp(act);
          }
        }

      });

    } else {
      if (_panel.GetRenderWindow()
                .GetRenderers()
                .GetFirstRenderer()
                .GetViewProps()
                .IsItemPresent(act) != 0) {
        _panel.GetRenderWindow()
              .GetRenderers()
              .GetFirstRenderer()
              .RemoveViewProp(act);
      }
    }
    _trace.out("removePipeline()");
  }

  /**
   * this method repaints the vtk window
   * 
   * @throws InterruptedException
   * @throws InvocationTargetException
   */
  public void render() throws ASCoDTException {
    _trace.in("render()");

    if (!SwingUtilities.isEventDispatchThread()) {
      SwingUtilities.invokeLater(new Runnable() {
        @Override
        public void run() {
          lock();
          _panel.Render();
          unlock();
        }
      });
    } else {
      lock();
      _panel.Render();
      unlock();
    }
    _trace.out("render()");
  }

  @Override
  public void setFocus() {
    if (_composite != null) {
      _composite.setFocus();
    }
  }

  public void unlock() {
    // if(!SwingUtilities.isEventDispatchThread()){
    // try {
    // SwingUtilities.invokeLater(new Runnable(){
    //
    // @Override
    // public void run() {
    // _panel.unlock();
    //
    // }
    //
    // });
    // } catch (InterruptedException e) {
    // throw new ASCoDTException(getClass().getName(), "addPipeline()",
    // "add pipeline interrupted", e);
    // } catch (InvocationTargetException e) {
    // throw new ASCoDTException(getClass().getName(), "addPipeline()",
    // "invocation error during add pipeline", e);
    // }
    // }else{
    // _panel.unlock();
    // }
  }

  public void unregisterPipelineForPicking(VTKPipeline pipe) {
    _pickablePipelines.remove(pipe);
  }

}
