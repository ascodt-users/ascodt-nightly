package de.tum.ascodt.plugin.ui.gef.model;

import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlTransient;


public class UsePort extends Port {
  @XmlAttribute(name = "alias")
  private String ref;
  @XmlAttribute(name = "createId")
  private int createId;
  @XmlAttribute(name = "connectId")
  private int connectId;
  @XmlAttribute(name = "disconnectId")
  private int disconnectId;
  /**
	 * 
	 */
  private static final long serialVersionUID = 1L;

  public UsePort(
      String key, 
      String value, 
      int classId,
      int createId,
      int connectId,
      int disconnetId
      ) {
    super(key + ":" + value, classId);
    setReference(key);
    setCreateId(createId);
    setConnectId(connectId);
    setDisconnectId(disconnetId);
  }
  @XmlTransient
  public String getReference() {
    return ref;
  }
 
  public void setReference(String ref) {
    this.ref = ref;
  }
  public void setCreateId(int createId){
    this.createId=createId;
  }
  public void setConnectId(int connectId){
    this.connectId=connectId;
  }
  public void setDisconnectId(int disconnetId){
    this.disconnectId=disconnetId;
  }
}
