package de.tum.ascodt.plugin.ui.editors.gef;


import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.EventObject;
import java.util.List;
import java.util.Vector;

import org.eclipse.core.resources.IFile;
import org.eclipse.core.resources.IProject;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.core.runtime.SafeRunner;
import org.eclipse.draw2d.geometry.Dimension;
import org.eclipse.gef.ContextMenuProvider;
import org.eclipse.gef.DefaultEditDomain;
import org.eclipse.gef.GraphicalViewer;
import org.eclipse.gef.MouseWheelHandler;
import org.eclipse.gef.MouseWheelZoomHandler;
import org.eclipse.gef.SnapToGeometry;
import org.eclipse.gef.SnapToGrid;
import org.eclipse.gef.dnd.TemplateTransferDropTargetListener;
import org.eclipse.gef.editparts.ScalableFreeformRootEditPart;
import org.eclipse.gef.editparts.ZoomManager;
import org.eclipse.gef.ui.actions.ToggleGridAction;
import org.eclipse.gef.ui.actions.ToggleSnapToGeometryAction;
import org.eclipse.gef.ui.actions.ZoomInAction;
import org.eclipse.gef.ui.actions.ZoomOutAction;
import org.eclipse.gef.ui.parts.GraphicalEditor;
import org.eclipse.gef.ui.parts.GraphicalViewerKeyHandler;
import org.eclipse.jface.action.IAction;
import org.eclipse.jface.commands.ActionHandler;
import org.eclipse.jface.util.SafeRunnable;
import org.eclipse.swt.SWT;
import org.eclipse.ui.IEditorInput;
import org.eclipse.ui.IEditorPart;
import org.eclipse.ui.IFileEditorInput;
import org.eclipse.ui.PartInitException;
import org.eclipse.ui.PlatformUI;
import org.eclipse.ui.handlers.IHandlerService;

import de.tum.ascodt.plugin.project.ProjectBuilder;
import de.tum.ascodt.plugin.ui.gef.commands.ComponentDeleteCommand;
import de.tum.ascodt.plugin.ui.gef.commands.ConnectionCommand;
import de.tum.ascodt.plugin.ui.gef.model.Component;
import de.tum.ascodt.plugin.ui.gef.model.Connection;
import de.tum.ascodt.plugin.ui.gef.model.Diagram;
import de.tum.ascodt.plugin.ui.gef.model.Geometry;
import de.tum.ascodt.plugin.ui.views.Palette;
import de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice;
import de.tum.ascodt.utils.exceptions.ASCoDTException;


/**
 * This class implements a gef editor for the cca workbench
 * 
 * @author Atanas Atanasov
 * 
 */
public class WorkbenchEditor extends GraphicalEditor {
  public static String ID = WorkbenchEditor.class.getCanonicalName();

  /**
   * the workbench root model reference
   */
  private Diagram _diagram;
  private org.eclipse.jface.util.TransferDropTargetListener _templateDropListener;

  public WorkbenchEditor() {
    super();
    setEditDomain(new DefaultEditDomain(this));
  }

  public void close() {
    try {
      System.out.println("closing editor");

    } catch (Exception e) {
      ErrorWriterDevice.getInstance().println(e);
    }
  }

  /**
   * @see org.eclipse.gef.ui.parts.GraphicalEditor#commandStackChanged(java.util.EventObject)
   */
  @Override
  public void commandStackChanged(EventObject event) {

    firePropertyChange(IEditorPart.PROP_DIRTY);
    super.commandStackChanged(event);
  }

  /**
   * setup the edit parts factories, zoom support and context menu provider
   */
  @Override
  protected void configureGraphicalViewer() {
    super.configureGraphicalViewer();
    ScalableFreeformRootEditPart root = new ScalableFreeformRootEditPart();

    List<String> zoomLevels = new ArrayList<String>(3);
    zoomLevels.add(ZoomManager.FIT_ALL);
    zoomLevels.add(ZoomManager.FIT_WIDTH);
    zoomLevels.add(ZoomManager.FIT_HEIGHT);
    root.getZoomManager().setZoomLevelContributions(zoomLevels);
    IAction zoomIn = new ZoomInAction(root.getZoomManager());
    IAction zoomOut = new ZoomOutAction(root.getZoomManager());
    getActionRegistry().registerAction(zoomIn);
    getActionRegistry().registerAction(zoomOut);
    IHandlerService service = (IHandlerService)getEditorSite().getService(
        IHandlerService.class);

    service.activateHandler(zoomIn.getActionDefinitionId(), new ActionHandler(
        zoomIn));

    service.activateHandler(zoomOut.getActionDefinitionId(), new ActionHandler(
        zoomOut));
    GraphicalViewer viewer = getGraphicalViewer();

    getGraphicalViewer().setEditPartFactory(
        new EditPartsFactory(ProjectBuilder.getInstance()
            .getProject(getProject()).getName()));
    try {
      Palette pallette = (Palette)PlatformUI.getWorkbench()
          .getActiveWorkbenchWindow().getActivePage().showView(Palette.ID);
      getEditDomain().setPaletteViewer(pallette.getViewer());
      pallette
          .setProject(ProjectBuilder.getInstance().getProject(getProject()));
    } catch (PartInitException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    }

    viewer.setRootEditPart(root);
    viewer.setKeyHandler(new GraphicalViewerKeyHandler(viewer));
    viewer.addDropTargetListener(new TemplateTransferDropTargetListener(
        getGraphicalViewer()));
    viewer.setProperty(SnapToGrid.PROPERTY_GRID_SPACING, new Dimension(32, 32));
    viewer.setProperty(SnapToGrid.PROPERTY_GRID_ENABLED, false);

    viewer.setProperty(SnapToGrid.PROPERTY_GRID_VISIBLE, false);
    ZoomManager manager = (ZoomManager)getGraphicalViewer().getProperty(
        ZoomManager.class.toString());
    if (manager != null) {
      manager.setZoom(_diagram.getZoom());
    }
    // Scroll-wheel Zoom
    getGraphicalViewer().setProperty(
        MouseWheelHandler.KeyGenerator.getKey(SWT.MOD1),
        MouseWheelZoomHandler.SINGLETON);
    IAction showGrid = new ToggleGridAction(getGraphicalViewer());
    getActionRegistry().registerAction(showGrid);

    /** * Snap To Geometry ** */
    getGraphicalViewer().setProperty(SnapToGeometry.PROPERTY_SNAP_ENABLED,
        new Boolean(false/*
                          * getProcess().
                          * isSnapToGeometryEnabled
                          * ()
                          */));
    IAction snapAction = new ToggleSnapToGeometryAction(getGraphicalViewer());
    getActionRegistry().registerAction(snapAction);

    ContextMenuProvider cmProvider = new ASCoDTContextMenuProvider(viewer,
        getActionRegistry());
    viewer.setContextMenu(cmProvider);

  }

  @Override
  public void dispose() {
    if (getGraphicalViewer() != null) {
      System.out.println("disposing we");
      getGraphicalViewer().setEditPartFactory(null);
      getGraphicalViewer().removeDropTargetListener(_templateDropListener);

      {
        Vector<ComponentDeleteCommand> commands = new Vector<ComponentDeleteCommand>();
        Vector<ConnectionCommand> connectionCommands = new Vector<ConnectionCommand>();
        for (Geometry geometry : _diagram.getChildren()) {

          if (geometry instanceof Component) {
            Component component = (Component)geometry;

            for (Connection con : component.getConnections()) {
              ConnectionCommand connCmd = new ConnectionCommand();
              connCmd.setConnection(con);
              connCmd.setSource(null);
              connCmd.setTarget(null);
              connCmd.setSourcePort(null);
              connCmd.setTargetPort(null);
              connectionCommands.add(connCmd);
            }
            ComponentDeleteCommand deleteCmd = new ComponentDeleteCommand();
            deleteCmd.setParent(_diagram);
            deleteCmd.setChild(component);
            commands.add(deleteCmd);
          }
        }
        for (ConnectionCommand deleteConn : connectionCommands) {
          System.out.println("deleting connection");
          getCommandStack().execute(deleteConn);
        }
        for (ComponentDeleteCommand deleteCmd : commands) {
          System.out.println("deleting components");
          getCommandStack().execute(deleteCmd);
        }
        commands.clear();
      }
      // getEditDomain().removeViewer(_paletteViewer);
      _templateDropListener = null;
      // _paletteViewer=null;
      _diagram = null;
      try {
        Palette pallette = (Palette)PlatformUI.getWorkbench()
            .getActiveWorkbenchWindow().getActivePage().showView(Palette.ID);
        getEditDomain().removeViewer(pallette.getViewer());

      } catch (PartInitException e) {
        // TODO Auto-generated catch block
        e.printStackTrace();
      }
    }
  }

  /**
   * This method stores the current state of the workbench
   */
  @Override
  public void doSave(final IProgressMonitor progressMonitor) {
    SafeRunner.run(new SafeRunnable() {
      @Override
      public void run() throws Exception {
        ByteArrayOutputStream out = new ByteArrayOutputStream();
        writeToOutputStream(out);
        IFile file = ((IFileEditorInput)getEditorInput()).getFile();
        file.setContents(new ByteArrayInputStream(out.toByteArray()), true,
            false, progressMonitor);
        // saveComponents();
        getCommandStack().markSaveLocation();

      }

    });
  }

  @Override
  protected void finalize() {
    System.out.println("finalizing editor");
  }

  /**
   * @return the project for this editor
   */
  public IProject getProject() {
    return ((IFileEditorInput)getEditorInput()).getFile().getProject();
  }

  /**
   * here we should hook the drop event listener to the palette
   */
  @Override
  protected void initializeGraphicalViewer() {
    _templateDropListener = new TemplateTransferDropTargetListener(
        getGraphicalViewer());
    getGraphicalViewer().addDropTargetListener(_templateDropListener);

    getGraphicalViewer().setContents(_diagram);

  }

  /**
   * load all saved components and the connections
   * 
   * @param file
   * @throws ClassNotFoundException
   * @throws IOException
   * @throws CoreException
   */
  private void loadComponents(IFile file) throws ASCoDTException {

    try {
      InputStream in = file.getContents(true);

      if (in != null) {
        ObjectInputStream oin = new ObjectInputStream(in);
        Object o = oin.readObject();
        if (o != null && o instanceof Diagram) {
          _diagram = (Diagram)o;
        }
        oin.close();
      }
      if (_diagram != null) {
        for (Geometry geometry : _diagram.getChildren()) {
          if (geometry instanceof Component) {
            Component component = (Component)geometry;
            ProjectBuilder
                .getInstance()
                .getNewInstanceFactory(
                    ProjectBuilder.getInstance().getProject(file.getProject()),
                    component.getClassName(), component.getTarget())
                .loadObject(component);
          }

        }

        for (Geometry geometry : _diagram.getChildren()) {
          if (geometry instanceof Component) {
            Component component = (Component)geometry;

            component.reconnect();
          }

        }
      }
    } catch (CoreException e) {
      throw new ASCoDTException(WorkbenchEditor.class.getCanonicalName(),
          "loadComponents()", e.getMessage() + "\n" + e.getCause(), e);
    } catch (IOException e) {
      throw new ASCoDTException(WorkbenchEditor.class.getCanonicalName(),
          "loadComponents()", e.getMessage() + "\n" + e.getCause(), e);
    } catch (ClassNotFoundException e) {
      throw new ASCoDTException(WorkbenchEditor.class.getCanonicalName(),
          "loadComponents()", e.getMessage() + "\n" + e.getCause(), e);
    }

  }

  /**
   * if the editor has the focus the palette should use classpath repository of
   * the current editor
   */
  @Override
  public void setFocus() {
    // Job job = new Job("Pallete Initialisation") {
    //
    // @Override
    // protected IStatus run(IProgressMonitor monitor) {
    // try {
    //
    // return Status.OK_STATUS;
    // } catch (Exception e) {
    // return Status.CANCEL_STATUS;
    // }
    // }
    //
    // };
    // job.schedule();

  }

  /**
   * (non-Javadoc)
   * 
   * @see org.eclipse.ui.part.EditorPart#setInput(org.eclipse.ui.IEditorInput)
   */
  @Override
  protected void setInput(IEditorInput input) {

    super.setInput(input);
    IFile file = ((IFileEditorInput)input).getFile();

    try {
      file.refreshLocal(0, null);
      loadComponents(file);
    } catch (ASCoDTException e) {
      ErrorWriterDevice.getInstance().println(e);
    } catch (CoreException e) {
      ErrorWriterDevice.getInstance().println(e);
    }
    if (_diagram == null) {
      _diagram = new Diagram();

    }

  }

  /**
   * write all components currently used on the workbench to the given output
   * stream
   * 
   * @param out
   * @throws IOException
   * @throws ComponentEntryException
   */
  private void writeToOutputStream(OutputStream out) throws IOException {
    ObjectOutputStream outputStream = new ObjectOutputStream(out);
    outputStream.writeObject(_diagram);
    outputStream.close();
  }

  /*
   * public void connectToPalette(final Palette palette) {
   * Display.getDefault().asyncExec(new Runnable(){
   * 
   * @Override
   * public void run() {
   * _paletteViewer=palette.getViewer();
   * 
   * 
   * }
   * 
   * });
   * }
   */
}
