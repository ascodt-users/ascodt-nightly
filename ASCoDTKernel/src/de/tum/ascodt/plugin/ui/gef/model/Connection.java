package de.tum.ascodt.plugin.ui.gef.model;


import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlIDREF;
import javax.xml.bind.annotation.XmlTransient;


/**
 * This class represents the ui model of connection between ports
 * 
 * @author atanasoa
 * 
 */
public class Connection extends ModelElement {
  /**
	 * 
	 */
  private static final long serialVersionUID = 1L;

  public static final String ID = Connection.class.getCanonicalName();

  /**
   * Used for indicating that a Link with dotted line style should be created.
   */
  public static final String SOLID_CONNECTION = "Solid";

  private Component source;
  private Component target;
  private Port targetPort;
  private Port sourcePort;

  public void attachSource() {
    if (getSource() == null ||
        getSource().getSourceConnections().contains(this)) {
      return;
    }
    getSource().connectOutput(this);
  }

  public boolean attachTarget() {
    if (getTarget() == null ||
        getTarget().getTargetConnections().contains(this)) {
      return false;
    }
    return getTarget().connectInput(this);
  }

  public void detachSource() {
    if (getSource() == null) {
      return;
    }
    getSource().disconnectOutput(this);
  }

  public void detachTarget() {
    if (getTarget() == null) {
      return;
    }
    getTarget().disconnectInput(this);
  }

  @XmlTransient
  public Component getSource() {
    return source;
  }

  @XmlAttribute(name = "source")
  @XmlIDREF
  public Port getSourcePort() {
    return sourcePort;
  }

  @XmlTransient
  public Component getTarget() {
    return target;
  }

  @XmlAttribute(name = "destination")
  @XmlIDREF
  public Port getTargetPort() {
    return targetPort;
  }

  public void setSource(Component comp) {
    Object old = source;
    source = comp;
    firePropertyChange("source", old, source);//$NON-NLS-1$
  }

  public void setSourcePort(Port port) {
    Object old = sourcePort;
    sourcePort = port;
    firePropertyChange("sourceTerminal", old, sourcePort);//$NON-NLS-1$
  }

  public void setTarget(Component comp) {
    Object old = target;
    target = comp;
    firePropertyChange("target", old, target);//$NON-NLS-1$
  }

  public void setTargetPort(Port port) {
    Object old = targetPort;
    targetPort = port;
    firePropertyChange("targetTerminal", old, port);//$NON-NLS-1$
  }

}
