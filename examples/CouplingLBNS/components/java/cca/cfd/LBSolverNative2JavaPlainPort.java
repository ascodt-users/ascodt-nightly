//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package cca.cfd;


public class LBSolverNative2JavaPlainPort extends LBSolverAbstractPort {

  private long _ref;
  public LBSolverNative2JavaPlainPort() {
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
  public void disconnect(LBSolver  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
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
  
  
  

  public void setupCommForNSRegion(final int startOfRegion[],final int endOfRegion[],final String commids[]) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.setupCommForNSRegion(startOfRegion,endOfRegion,commids);
      //_destination.unlock();
    //}
  }
  
  public void setupCommForNSRegionParallel(final int startOfRegion[],final int endOfRegion[],final String commids[]) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.setupCommForNSRegionParallel(startOfRegion,endOfRegion,commids);
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
  
  
  

  public void solveOneTimestep() {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.solveOneTimestep();
      //_destination.unlock();
    //}
  }
  
  public void solveOneTimestepParallel() {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.solveOneTimestepParallel();
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
  
  
  

  public void setPressure(final double pressure[]) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.setPressure(pressure);
      //_destination.unlock();
    //}
  }
  
  public void setPressureParallel(final double pressure[]) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.setPressureParallel(pressure);
      //_destination.unlock();
    //}
  }
  
  
  

  public void setGradients(final double gradients[]) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.setGradients(gradients);
      //_destination.unlock();
    //}
  }
  
  public void setGradientsParallel(final double gradients[]) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.setGradientsParallel(gradients);
      //_destination.unlock();
    //}
  }
  
  
  

  public void closeLBProfiles() {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.closeLBProfiles();
      //_destination.unlock();
    //}
  }
  
  public void closeLBProfilesParallel() {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.closeLBProfilesParallel();
      //_destination.unlock();
    //}
  }
  
  
  

  public void printLBDensity() {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.printLBDensity();
      //_destination.unlock();
    //}
  }
  
  public void printLBDensityParallel() {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.printLBDensityParallel();
      //_destination.unlock();
    //}
  }
  
  
  

  public void printLBProfiles() {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.printLBProfiles();
      //_destination.unlock();
    //}
  }
  
  public void printLBProfilesParallel() {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.printLBProfilesParallel();
      //_destination.unlock();
    //}
  }
  
  
  

  public void forwardVelocities(int keys[],int offsets[],int flips[],double values[],int ackn[]) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.forwardVelocities(keys,offsets,flips,values,ackn);
      //_destination.unlock();
    //}
  }
  
  public void forwardVelocitiesParallel(int keys[],int offsets[],int flips[],double values[],int ackn[]) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.forwardVelocitiesParallel(keys,offsets,flips,values,ackn);
      //_destination.unlock();
    //}
  }
  
  
  

  public void forwardPressure(int keys[],int offsets[],int flips[],double values[],int ackn[]) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.forwardPressure(keys,offsets,flips,values,ackn);
      //_destination.unlock();
    //}
  }
  
  public void forwardPressureParallel(int keys[],int offsets[],int flips[],double values[],int ackn[]) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.forwardPressureParallel(keys,offsets,flips,values,ackn);
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
  
  
  


}
 


