//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package cca.cfd;


public class DriverPlainJavaPort extends DriverAbstractPort {

  public DriverPlainJavaPort() {
    super();
  }
  

  public void go(final String configFile) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.go(configFile);
      //_destination.unlock();
    //}
  }
  
  public void goParallel(final String configFile) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.goParallel(configFile);
      //_destination.unlock();
    //}
  }
  
  
  
  

}
 


