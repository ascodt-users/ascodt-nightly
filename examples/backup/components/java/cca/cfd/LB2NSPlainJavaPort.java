//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package cca.cfd;


public class LB2NSPlainJavaPort extends LB2NSAbstractPort {

  public LB2NSPlainJavaPort() {
    super();
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
  
  
  

  public void retrieveTimestep(double dt[]) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.retrieveTimestep(dt);
      //_destination.unlock();
    //}
  }
  
  public void retrieveTimestepParallel(double dt[]) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.retrieveTimestepParallel(dt);
      //_destination.unlock();
    //}
  }
  
  
  

  public void retrieveVelocitiesSize(int memoryX[],int memoryY[],int memoryZ[]) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.retrieveVelocitiesSize(memoryX,memoryY,memoryZ);
      //_destination.unlock();
    //}
  }
  
  public void retrieveVelocitiesSizeParallel(int memoryX[],int memoryY[],int memoryZ[]) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.retrieveVelocitiesSizeParallel(memoryX,memoryY,memoryZ);
      //_destination.unlock();
    //}
  }
  
  
  

  public void retrieveVelocitiesCopy(double velocityX[],double velocityY[],double velocityZ[]) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.retrieveVelocitiesCopy(velocityX,velocityY,velocityZ);
      //_destination.unlock();
    //}
  }
  
  public void retrieveVelocitiesCopyParallel(double velocityX[],double velocityY[],double velocityZ[]) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.retrieveVelocitiesCopyParallel(velocityX,velocityY,velocityZ);
      //_destination.unlock();
    //}
  }
  
  
  
  

}
 

