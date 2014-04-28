//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package cca.cfd;


public class NSSolverNative2JavaPlainPort extends NSSolverAbstractPort {

  private long _ref;
  public NSSolverNative2JavaPlainPort() {
    super();
    createInstance();
  }
  
  public native void createInstance();
  public native void destroyInstance(long ref);
  /**
   * Disconnect a port.
   * 
   * @throw If already not connected to type port.
   * @see Operation with name of any implementing component 
   */
  public void disconnect(NSSolver  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
     super.disconnect(port);
  }
  
  public void destroy(){
     destroyInstance(_ref);    
  }
  public long getReference(){
    return _ref;
  }  
  
  public void setReference(long ref){
     _ref=ref;
  }

  public void setup(final String inputScenario) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.setup(inputScenario);
      //_destination.unlock();
    //}
  }
  
  public void setupParallel(final String inputScenario) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.setupParallel(inputScenario);
      //_destination.unlock();
    //}
  }
  
  
  

  public void setupCommForLBRegion(final int startOfRegion[],final int endOfRegion[],final String commids[]) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.setupCommForLBRegion(startOfRegion,endOfRegion,commids);
      //_destination.unlock();
    //}
  }
  
  public void setupCommForLBRegionParallel(final int startOfRegion[],final int endOfRegion[],final String commids[]) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.setupCommForLBRegionParallel(startOfRegion,endOfRegion,commids);
      //_destination.unlock();
    //}
  }
  
  
  

  public void solve() {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.solve();
      //_destination.unlock();
    //}
  }
  
  public void solveParallel() {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.solveParallel();
      //_destination.unlock();
    //}
  }
  
  
  

  public void solveOneTimestepPhaseOne() {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.solveOneTimestepPhaseOne();
      //_destination.unlock();
    //}
  }
  
  public void solveOneTimestepPhaseOneParallel() {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.solveOneTimestepPhaseOneParallel();
      //_destination.unlock();
    //}
  }
  
  
  

  public void solveOneTimestepPhaseTwo() {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.solveOneTimestepPhaseTwo();
      //_destination.unlock();
    //}
  }
  
  public void solveOneTimestepPhaseTwoParallel() {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.solveOneTimestepPhaseTwoParallel();
      //_destination.unlock();
    //}
  }
  
  
  

  public void setVelocities(final double velocitiesX[],final double velocitiesY[],final double velocitiesZ[]) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.setVelocities(velocitiesX,velocitiesY,velocitiesZ);
      //_destination.unlock();
    //}
  }
  
  public void setVelocitiesParallel(final double velocitiesX[],final double velocitiesY[],final double velocitiesZ[]) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.setVelocitiesParallel(velocitiesX,velocitiesY,velocitiesZ);
      //_destination.unlock();
    //}
  }
  
  
  

  public void printNSPressure() {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.printNSPressure();
      //_destination.unlock();
    //}
  }
  
  public void printNSPressureParallel() {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.printNSPressureParallel();
      //_destination.unlock();
    //}
  }
  
  
  

  public void printNSProfiles() {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.printNSProfiles();
      //_destination.unlock();
    //}
  }
  
  public void printNSProfilesParallel() {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.printNSProfilesParallel();
      //_destination.unlock();
    //}
  }
  
  
  

  public void closeNSProfiles() {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.closeNSProfiles();
      //_destination.unlock();
    //}
  }
  
  public void closeNSProfilesParallel() {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.closeNSProfilesParallel();
      //_destination.unlock();
    //}
  }
  
  
  

  public void iterateBoundary() {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.iterateBoundary();
      //_destination.unlock();
    //}
  }
  
  public void iterateBoundaryParallel() {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.iterateBoundaryParallel();
      //_destination.unlock();
    //}
  }
  
  
  

  public void iterateInner() {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.iterateInner();
      //_destination.unlock();
    //}
  }
  
  public void iterateInnerParallel() {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.iterateInnerParallel();
      //_destination.unlock();
    //}
  }
  
  
  

  public void forwardVelocities(int keys[],int offsets[],int flips[],double values[],int componentSize[],int ackn[]) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.forwardVelocities(keys,offsets,flips,values,componentSize,ackn);
      //_destination.unlock();
    //}
  }
  
  public void forwardVelocitiesParallel(int keys[],int offsets[],int flips[],double values[],int componentSize[],int ackn[]) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.forwardVelocitiesParallel(keys,offsets,flips,values,componentSize,ackn);
      //_destination.unlock();
    //}
  }
  
  
  

  public void plot() {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.plot();
      //_destination.unlock();
    //}
  }
  
  public void plotParallel() {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.plotParallel();
      //_destination.unlock();
    //}
  }
  
  
  

  public void syncr(int value[]) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.syncr(value);
      //_destination.unlock();
    //}
  }
  
  public void syncrParallel(int value[]) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.syncrParallel(value);
      //_destination.unlock();
    //}
  }
  
  
  


}
 


