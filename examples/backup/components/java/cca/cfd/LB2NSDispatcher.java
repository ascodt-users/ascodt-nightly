//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package cca.cfd;


public class LB2NSDispatcher implements LB2NS {

  protected java.util.Set<LB2NS>  _destinations;
  
  public LB2NSDispatcher() {
    _destinations = java.util.Collections.synchronizedSet(new java.util.HashSet<LB2NS>());
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
  public void connect(LB2NS  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
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
  public void disconnect(LB2NS  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
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
  
  public void iterateBoundary() {
    for(LB2NS port: _destinations)
      port.iterateBoundary();
  }
  
  public void iterateBoundaryParallel() {
    for(LB2NS port: _destinations)
      port.iterateBoundaryParallel();
  }
  
  public void iterateBoundaryForIntegerEnums() {
    for(LB2NS port: _destinations){
      
      port.iterateBoundary();
      
    }
  }
  public void iterateInner() {
    for(LB2NS port: _destinations)
      port.iterateInner();
  }
  
  public void iterateInnerParallel() {
    for(LB2NS port: _destinations)
      port.iterateInnerParallel();
  }
  
  public void iterateInnerForIntegerEnums() {
    for(LB2NS port: _destinations){
      
      port.iterateInner();
      
    }
  }
  public void retrieveTimestep(double dt[]) {
    for(LB2NS port: _destinations)
      port.retrieveTimestep(dt);
  }
  
  public void retrieveTimestepParallel(double dt[]) {
    for(LB2NS port: _destinations)
      port.retrieveTimestepParallel(dt);
  }
  
  public void retrieveTimestepForIntegerEnums(double dt[]) {
    for(LB2NS port: _destinations){
      
      port.retrieveTimestep(dt);
      
    }
  }
  public void retrieveVelocitiesSize(int memoryX[],int memoryY[],int memoryZ[]) {
    for(LB2NS port: _destinations)
      port.retrieveVelocitiesSize(memoryX,memoryY,memoryZ);
  }
  
  public void retrieveVelocitiesSizeParallel(int memoryX[],int memoryY[],int memoryZ[]) {
    for(LB2NS port: _destinations)
      port.retrieveVelocitiesSizeParallel(memoryX,memoryY,memoryZ);
  }
  
  public void retrieveVelocitiesSizeForIntegerEnums(int memoryX[],int memoryY[],int memoryZ[]) {
    for(LB2NS port: _destinations){
      
      port.retrieveVelocitiesSize(memoryX,memoryY,memoryZ);
      
    }
  }
  public void retrieveVelocitiesCopy(double velocityX[],double velocityY[],double velocityZ[]) {
    for(LB2NS port: _destinations)
      port.retrieveVelocitiesCopy(velocityX,velocityY,velocityZ);
  }
  
  public void retrieveVelocitiesCopyParallel(double velocityX[],double velocityY[],double velocityZ[]) {
    for(LB2NS port: _destinations)
      port.retrieveVelocitiesCopyParallel(velocityX,velocityY,velocityZ);
  }
  
  public void retrieveVelocitiesCopyForIntegerEnums(double velocityX[],double velocityY[],double velocityZ[]) {
    for(LB2NS port: _destinations){
      
      port.retrieveVelocitiesCopy(velocityX,velocityY,velocityZ);
      
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
 

