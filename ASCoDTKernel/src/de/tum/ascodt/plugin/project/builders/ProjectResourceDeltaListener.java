package de.tum.ascodt.plugin.project.builders;


import org.eclipse.core.resources.IResourceDelta;
import org.eclipse.core.resources.IResourceDeltaVisitor;
import org.eclipse.core.runtime.CoreException;

import de.tum.ascodt.plugin.project.Project;
import de.tum.ascodt.plugin.project.ProjectBuilder;
import de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice;
import de.tum.ascodt.plugin.utils.tracing.Trace;
import de.tum.ascodt.sidlcompiler.frontend.node.Start;
import de.tum.ascodt.sidlcompiler.symboltable.BuildSymbolTable.Mode;
import de.tum.ascodt.utils.exceptions.ASCoDTException;


/**
 * A resource listener used by the project builder to determine if changes
 * to the sidl resources have occured.
 * 
 * @author Atanas Atanasov
 * 
 */
public class ProjectResourceDeltaListener implements IResourceDeltaVisitor {
  private Trace _trace =
      new Trace(ProjectResourceDeltaListener.class.getCanonicalName());
  private boolean _hasChanged = false;

  /**
   * Builds the changed/added resource
   * 
   * @param delta
   *          delta object
   * @param project
   *          the current project
   * @param mode
   * @throws ASCoDTException
   */
  public void buildResource(IResourceDelta delta, Project project, Mode mode) throws ASCoDTException {

    Start startSymbol =
        SiDLBuilder.buildStartSymbolsForSIDLResource(delta.getResource()
                                                          .getLocation()
                                                          .toPortableString());
    SiDLBuilder.extendSymbolTable(startSymbol,
                                  project.getSymbolTable(),
                                  delta.getResource()
                                       .getLocation()
                                       .toPortableString());
    _hasChanged = true;
  }

  public boolean hasChanged() {
    return _hasChanged;
  }

  public void reset() {
    _hasChanged = false;
  }

  /**
   * visits changed/added/removed resources
   */
  @Override
  public boolean visit(IResourceDelta delta) throws CoreException {
    _trace.in("visit()", delta.toString());
    try {

      if (delta.getResource().getName().contains(".sidl") && delta.getResource()
                                                                  .getLocation()
                                                                  .toPortableString()
                                                                  .contains(delta.getResource()
                                                                                 .getProject()
                                                                                 .getName() + "/sidl")) {
        Project project =
            ProjectBuilder.getInstance().getProject(delta.getResource()
                                                         .getProject());

        switch (delta.getKind()) {
        case IResourceDelta.ADDED:
          buildResource(delta, project, Mode.APPEND);
          break;
        case IResourceDelta.REMOVED:
          break;
        case IResourceDelta.CHANGED:
          buildResource(delta, project, Mode.MODIFIED);
          break;
        }

      }
    } catch (ASCoDTException e) {
      ErrorWriterDevice.getInstance().println(e);
    }
    _trace.out("visit()", delta.toString());
    return true;
  }

}
