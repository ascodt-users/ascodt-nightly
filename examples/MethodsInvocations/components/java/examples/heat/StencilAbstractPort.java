//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package examples.heat;


public abstract class StencilAbstractPort implements Stencil {

  protected Stencil  _destination;
  
  public StencilAbstractPort() {
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
  public void connect(Stencil  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
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
  public void disconnect(Stencil  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
    if (_destination==null) {
      throw new de.tum.ascodt.utils.exceptions.ASCoDTException( getClass().getName(), "disconnect(...)", "tried to disconnect port that was not connected before", null );
    }
    if (_destination!=port) {
      throw new de.tum.ascodt.utils.exceptions.ASCoDTException( getClass().getName(), "disconnect(...)", "tried to disconnect port from port that was not connected before", null );
    }
    _destination = null;
  }
  
  public void destroy(){
  
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
 


