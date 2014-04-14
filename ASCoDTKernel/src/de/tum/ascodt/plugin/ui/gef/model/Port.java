package de.tum.ascodt.plugin.ui.gef.model;


import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlID;


/**
 * Gef model representing one port
 * 
 * @author atanasoa
 * 
 */
public class Port extends Geometry {
  /**
   * the class for this port
   */
  @XmlAttribute(name = "className")
  protected String className;

  @XmlAttribute(name = "classId")
  protected int classId;

  /**
   * holds the connectable flag
   */
  protected boolean isConnectable;

  /**
	 * 
	 */
  private static final long serialVersionUID = 1L;

  public Port(String value, int classId) {
    className = value;
    this.classId = classId;
  }

  public int getClassId() {
    return classId;
  }

  public String getDescription() {
    return className;
  }

  @XmlAttribute(name = "index")
  @XmlID
  public String getIndex() {
    return Integer.toString(System.identityHashCode(this));
  }

  public boolean isConnectable() {
    return isConnectable;
  }

  /**
   * 
   * @param flag
   *          connectable flag
   */
  public void setIsConnectable(boolean flag) {
    isConnectable = flag;
  }

}
