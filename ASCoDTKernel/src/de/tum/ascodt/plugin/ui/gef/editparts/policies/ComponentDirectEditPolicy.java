package de.tum.ascodt.plugin.ui.gef.editparts.policies;


import org.eclipse.gef.commands.Command;
import org.eclipse.gef.editpolicies.DirectEditPolicy;
import org.eclipse.gef.requests.DirectEditRequest;
import org.eclipse.jface.viewers.CellEditor;

import de.tum.ascodt.plugin.ui.gef.commands.ResetReferenceForComponentCommand;
import de.tum.ascodt.plugin.ui.gef.editparts.ComponentEditPart;
import de.tum.ascodt.plugin.ui.gef.model.Component;


public class ComponentDirectEditPolicy extends DirectEditPolicy {
  private String oldValue;

  /**
   * @see DirectEditPolicy#getDirectEditCommand(org.eclipse.gef.requests.DirectEditRequest)
   */
  @Override
  protected Command getDirectEditCommand(DirectEditRequest request) {
    ResetReferenceForComponentCommand cmd =
        new ResetReferenceForComponentCommand();
    Component component = (Component)getHost().getModel();
    cmd.setSource(component);
    cmd.setOldReference(component.getReference());

    CellEditor cellEditor = request.getCellEditor();
    cmd.setReference((String)cellEditor.getValue());
    return cmd;
  }

  /**
   * @param request
   */
  @Override
  protected void revertOldEditValue(DirectEditRequest request) {
    CellEditor cellEditor = request.getCellEditor();
    cellEditor.setValue(oldValue);
    ComponentEditPart componentPart = (ComponentEditPart)getHost();
    componentPart.revertReferenceChange(oldValue);

  }

  /**
   * @see DirectEditPolicy#showCurrentEditValue(org.eclipse.gef.requests.DirectEditRequest)
   */
  @Override
  protected void showCurrentEditValue(DirectEditRequest request) {
    String value = (String)request.getCellEditor().getValue();
    ComponentEditPart componentPart = (ComponentEditPart)getHost();
    componentPart.handleReferenceChange(value);
  }

  /**
   * @param to
   *          Revert request
   */
  @Override
  protected void storeOldEditValue(DirectEditRequest request) {
    CellEditor cellEditor = request.getCellEditor();
    oldValue = (String)cellEditor.getValue();
  }
}
