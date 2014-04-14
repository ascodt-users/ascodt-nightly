//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package examples;


public class DriverNative2JavaPlainPort extends DriverAbstractPort {

  private long _ref;
  public DriverNative2JavaPlainPort() {
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
  public void disconnect(Driver  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
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

  public void go() {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.go();
      //_destination.unlock();
    //}
  }
  
  public void goParallel() {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.goParallel();
      //_destination.unlock();
    //}
  }
  
  
  


}
 


