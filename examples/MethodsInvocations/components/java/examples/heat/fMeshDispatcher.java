//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package examples.heat;


public class fMeshDispatcher implements fMesh {

  protected java.util.Set<fMesh>  _destinations;
  
  public fMeshDispatcher() {
    _destinations = java.util.Collections.synchronizedSet(new java.util.HashSet<fMesh>());
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
  public void connect(fMesh  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
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
  public void disconnect(fMesh  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
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
  
  public void allocate(final int dim[]) {
    for(fMesh port: _destinations)
      port.allocate(dim);
  }
  
  public void allocateForIntegerEnums(final int dim[]) {
    for(fMesh port: _destinations){
      
      port.allocate(dim);
      
    }
  }
  public void copyData(double data[]) {
    for(fMesh port: _destinations)
      port.copyData(data);
  }
  
  public void copyDataForIntegerEnums(double data[]) {
    for(fMesh port: _destinations){
      
      port.copyData(data);
      
    }
  }
  public void getData(long handle[]) {
    for(fMesh port: _destinations)
      port.getData(handle);
  }
  
  public void getDataForIntegerEnums(long handle[]) {
    for(fMesh port: _destinations){
      
      port.getData(handle);
      
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
 


