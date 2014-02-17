package de.tum.ascodt.plugin.ui.gef.editparts;


import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;

import org.eclipse.draw2d.IFigure;
import org.eclipse.draw2d.PolygonDecoration;
import org.eclipse.draw2d.PolylineConnection;
import org.eclipse.gef.EditPolicy;
import org.eclipse.gef.commands.Command;
import org.eclipse.gef.editparts.AbstractConnectionEditPart;
import org.eclipse.gef.editpolicies.ConnectionEditPolicy;
import org.eclipse.gef.editpolicies.ConnectionEndpointEditPolicy;
import org.eclipse.gef.requests.GroupRequest;

import de.tum.ascodt.plugin.ui.gef.commands.LinkDeleteCommand;
import de.tum.ascodt.plugin.ui.gef.model.Link;
import de.tum.ascodt.plugin.ui.gef.model.ModelElement;


public class LinkEditPart extends AbstractConnectionEditPart implements
    PropertyChangeListener {

  /**
   * Upon activation, attach to the model element as a property change listener.
   */
  @Override
  public void activate() {
    if (!isActive()) {
      super.activate();
      ((ModelElement)getModel()).addPropertyChangeListener(this);
    }
  }

  @Override
  protected void createEditPolicies() {
    // Makes the connection show a feedback, when selected by the user.
    installEditPolicy(EditPolicy.CONNECTION_ENDPOINTS_ROLE,
        new ConnectionEndpointEditPolicy());
    installEditPolicy(EditPolicy.CONNECTION_ROLE, new ConnectionEditPolicy() {
      @Override
      protected Command getDeleteCommand(GroupRequest request) {
        return new LinkDeleteCommand(getCastedModel());
      }
    });

  }

  /*
   * (non-Javadoc)
   * 
   * @see org.eclipse.gef.editparts.AbstractGraphicalEditPart#createFigure()
   */
  @Override
  protected IFigure createFigure() {
    PolylineConnection connection = (PolylineConnection)super.createFigure();
    connection.setTargetDecoration(new PolygonDecoration()); // arrow at target
                                                             // endpoint
    connection.setLineStyle(getCastedModel().getLineStyle()); // line drawing
                                                              // style
    return connection;
  }

  /**
   * Upon deactivation, detach from the model element as a property change
   * listener.
   */
  @Override
  public void deactivate() {
    if (isActive()) {
      super.deactivate();
      ((ModelElement)getModel()).removePropertyChangeListener(this);
    }
  }

  private Link getCastedModel() {
    return (Link)getModel();
  }

  /*
   * (non-Javadoc)
   * 
   * @see
   * java.beans.PropertyChangeListener#propertyChange(java.beans.PropertyChangeEvent
   * )
   */
  @Override
  public void propertyChange(PropertyChangeEvent event) {
    String property = event.getPropertyName();
    if (Link.LINESTYLE_PROP.equals(property)) {
      ((PolylineConnection)getFigure()).setLineStyle(getCastedModel()
          .getLineStyle());
    }
    refreshVisuals();
  }
}
