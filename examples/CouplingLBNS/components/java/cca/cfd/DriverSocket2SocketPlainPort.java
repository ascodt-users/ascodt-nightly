//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package cca.cfd;


public class DriverSocket2SocketPlainPort extends cca.cfd.DriverPlainJavaPort implements cca.cfd.DriverSocketPort{
  long _ref;
  private String _host;
  private int _port;
  public DriverSocket2SocketPlainPort(String host,int port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
    _host=host;
    _port=port;
  }
  
  public void open () throws de.tum.ascodt.utils.exceptions.ASCoDTException{
  }
  
  @Override
  public void processFinished(int arg0) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
     
  }
  
  public long getReference(){
    return _ref;
  }  
  
  public void setReference(long ref){
     _ref=ref;
  }
  
  public String getHost(){
     return _host;
  }
  public int getPort(){
     return _port;
  }
  
}
 


