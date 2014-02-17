package de.tum.ascodt.plugin.ui.gef.model;


public class UsePort extends Port {
  private String ref;

  /**
	 * 
	 */
  private static final long serialVersionUID = 1L;

  public UsePort(String key, String value, int classId) {
    super(key + ":" + value, classId);
    setReference(key);
  }

  public String getReference() {
    return ref;
  }

  public void setReference(String ref) {
    this.ref = ref;
  }
}
