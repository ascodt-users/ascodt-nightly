package de.tum.ascodt.plugin.ui.gef.model;


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
  protected String className;

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
