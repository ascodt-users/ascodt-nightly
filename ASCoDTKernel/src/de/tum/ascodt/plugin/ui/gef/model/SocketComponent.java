package de.tum.ascodt.plugin.ui.gef.model;

import javax.xml.bind.annotation.XmlAttribute;

public class SocketComponent extends Component {

  private int port;
  private String host;
  /**
   * 
   */
  private static final long serialVersionUID = 1L;

  @XmlAttribute(name = "port")
  public int getPort() {
    return port;
  }
  public void setPort(int port){
    this.port=port;
  }
  @XmlAttribute(name = "host")
  public String getHost() {
    return host;
  }
  public void setHost(String host){
    this.host=host;
  }

  
}
