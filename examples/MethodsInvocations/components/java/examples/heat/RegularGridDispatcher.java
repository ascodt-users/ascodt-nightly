//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package examples.heat;


public class RegularGridDispatcher implements RegularGrid {

  protected java.util.Set<RegularGrid>  _destinations;
  
  public RegularGridDispatcher() {
    _destinations = java.util.Collections.synchronizedSet(new java.util.HashSet<RegularGrid>());
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
  public void connect(RegularGrid  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
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
  public void disconnect(RegularGrid  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
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
  
  public void setOffset(final double offset[]) {
    for(RegularGrid port: _destinations)
      port.setOffset(offset);
  }
  
  public void setOffsetForIntegerEnums(final double offset[]) {
    for(RegularGrid port: _destinations){
      
      port.setOffset(offset);
      
    }
  }
  public void setDomain(final double domain[]) {
    for(RegularGrid port: _destinations)
      port.setDomain(domain);
  }
  
  public void setDomainForIntegerEnums(final double domain[]) {
    for(RegularGrid port: _destinations){
      
      port.setDomain(domain);
      
    }
  }
  public void setDimensions(final int dimensions[]) {
    for(RegularGrid port: _destinations)
      port.setDimensions(dimensions);
  }
  
  public void setDimensionsForIntegerEnums(final int dimensions[]) {
    for(RegularGrid port: _destinations){
      
      port.setDimensions(dimensions);
      
    }
  }
  public void addCellScalars(final String variableName,final double scalars[]) {
    for(RegularGrid port: _destinations)
      port.addCellScalars(variableName,scalars);
  }
  
  public void addCellScalarsForIntegerEnums(final String variableName,final double scalars[]) {
    for(RegularGrid port: _destinations){
      
      port.addCellScalars(variableName,scalars);
      
    }
  }
  public void render() {
    for(RegularGrid port: _destinations)
      port.render();
  }
  
  public void renderForIntegerEnums() {
    for(RegularGrid port: _destinations){
      
      port.render();
      
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
 


