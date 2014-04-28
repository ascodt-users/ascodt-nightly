//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package cca.cfd;

public abstract class LB2NSAbstractSocketPort extends SocketComponent implements LB2NSSocketPort{

  protected LB2NS  _destination;
  
  public LB2NSAbstractSocketPort() throws de.tum.ascodt.utils.exceptions.ASCoDTException {
    _destination = null;
  }
  
  public LB2NSAbstractSocketPort(String host,int port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
    super(host,port);
    _destination = null;
  }
  
  public long getReference(){
    return 0;
  }
  
  public void setReference(long ref){
    //return 0;
  }
  /**
   * Connect a uses port.
   *
   * @throw If already connected to another port.
   * @see Operation with name of any implementing component 
   */
  public void connect(LB2NS  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
    if (_destination!=null) {
      throw new de.tum.ascodt.utils.exceptions.ASCoDTException( getClass().getName(), "connect(...)", "port already was connected", null );
    }
    _destination = port;
  }
    
  /**
   * Disconnect a port.
   * 
   * @throw If already not connected to type port.
   * @see Operation with name of any implementing component 
   */
  public void disconnect(LB2NS  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
    if (_destination==null) {
          return;
    }
    if (_destination!=port) {
      throw new de.tum.ascodt.utils.exceptions.ASCoDTException( getClass().getName(), "disconnect(...)", "tried to disconnect port from port that was not connected before", null );
    }
    _destination = null;
  }
  
//  public void lock() {
//    if (_destination!=null) {
//      _destination.lock();
//    }
//  }
 
//  public void unlock() {
//    if (_destination!=null) {
//      _destination.unlock();
//    }
//  }
  
}
 


