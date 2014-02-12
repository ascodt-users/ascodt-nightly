//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package examples.heat;


public class fMeshNative2JavaPlainPort extends fMeshAbstractPort {

  private long _ref;
  public fMeshNative2JavaPlainPort() {
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
  public void disconnect(fMesh  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
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

  public void allocate(final int dim[]) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.allocate(dim);
      //_destination.unlock();
    //}
  }
  

  public void copyData(double data[]) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.copyData(data);
      //_destination.unlock();
    //}
  }
  

  public void getData(long handle[]) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.getData(handle);
      //_destination.unlock();
    //}
  }
  


}
 

