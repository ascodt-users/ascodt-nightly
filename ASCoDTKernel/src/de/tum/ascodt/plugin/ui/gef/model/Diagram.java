package de.tum.ascodt.plugin.ui.gef.model;


import java.util.HashSet;
import java.util.Set;

import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;


/**
 * This class represents the model of the ASCoDT diagram. This is the root
 * object
 * of the workbench. Each inserted component is a child of the diagram.
 * 
 * @author Atanas Atansov
 * 
 */
@XmlRootElement
public class Diagram extends ModelElement {
  /**
	 *
	 */
  private static final long serialVersionUID = 1L;
  /** Property ID to use when a child is added to this diagram. */
  public static final String CHILD_ADDED_PROP = "ASCoDTDiagram.ChildAdded";
  /** Property ID to use when a child is removed from this diagram. */
  public static final String CHILD_REMOVED_PROP = "ASCoDTDiagram.ChildRemoved";
  /**
   * the zoom factor
   */
  private double zoom = 1.0;

  /**
   * Add a geometry to this diagram.
   * 
   * @param geometry
   *          a non-null geometry instance
   * @return true, if the geometry was added, false otherwise
   */
  public boolean addChild(Geometry geometry) {
    if (geometry != null && children.add(geometry)) {
      firePropertyChange(CHILD_ADDED_PROP, null, geometry);
      return true;
    }
    return false;
  }

  @XmlElement(name = "component")
  public Set<Component> getComponents() {
    Set<Component> components = new HashSet<Component>();

    for (Geometry geometry : getChildren()) {
      if (!(geometry instanceof Component)) {
        continue;
      }

      Component component = (Component)geometry;

      components.add(component);
    }

    return components;
  }

  @XmlElement(name = "connection")
  public Set<Connection> getConnections() {
    Set<Connection> connections = new HashSet<Connection>();

    for (Component component : getComponents()) {
      for (Connection connection : component.getOutputConnections()) {
        connections.add(connection);
      }

      for (Connection connection : component.getInputConnections()) {
        connections.add(connection);
      }
    }

    return connections;
  }

  /**
   * @return the zoom
   */
  @XmlTransient
  public double getZoom() {
    return zoom;
  }

  /**
   * Remove a geometry from this diagram.
   * 
   * @param geometry
   *          a non-null geometry instance;
   * @return true, if the geometry was removed, false otherwise
   */
  public boolean removeChild(Geometry geometry) {
    if (geometry != null && children.remove(geometry)) {
      firePropertyChange(CHILD_REMOVED_PROP, null, geometry);
      return true;
    }
    return false;
  }

  /**
   * @param zoom
   *          the zoom to set
   */
  public void setZoom(double zoom) {
    this.zoom = zoom;
  }
}
