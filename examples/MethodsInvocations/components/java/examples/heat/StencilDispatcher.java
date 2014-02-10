//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package examples.heat;


public class StencilDispatcher implements Stencil {

  protected java.util.Set<Stencil>  _destinations;
  
  public StencilDispatcher() {
    _destinations = java.util.Collections.synchronizedSet(new java.util.HashSet<Stencil>());
  }
  
  public long getReference(){
    return 0;
  }
  
  
  public void setReference(long ref){
  }
  /**
   * Connect a uses port.
   *
   * @throw If already connected to another port.
   * @see Operation with name of any implementing component 
   */
  public void connect(Stencil  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
    if (_destinations==null) {
      throw new de.tum.ascodt.utils.exceptions.ASCoDTException( getClass().getName(), "connect(...)", "port already was connected", null );
    }
    _destinations.add(port);
  }
    
  /**
   * Disconnect a port.
   * 
   * @throw If already not connected to type port.
   * @see Operation with name of any implementing component 
   */
  public void disconnect(Stencil  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
    if (_destinations==null) {
      throw new de.tum.ascodt.utils.exceptions.ASCoDTException( getClass().getName(), "disconnect(...)", "tried to disconnect port that was not connected before", null );
    }
     
    if (!_destinations.contains(port)) {
      throw new de.tum.ascodt.utils.exceptions.ASCoDTException( getClass().getName(), "disconnect(...)", "tried to disconnect port from port that was not connected before", null );
    }
    _destinations.remove(port);
  }
  
  public boolean isConnected(){
     return !_destinations.isEmpty();
  }
  
  public void getStencil(double stencil[]) {
    for(Stencil port: _destinations)
      port.getStencil(stencil);
  }
  
  public void getStencilForIntegerEnums(double stencil[]) {
    for(Stencil port: _destinations){
      
      port.getStencil(stencil);
      
    }
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
 


