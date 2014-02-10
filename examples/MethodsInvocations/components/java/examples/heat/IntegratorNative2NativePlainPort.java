//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package examples.heat;


public class IntegratorNative2NativePlainPort extends IntegratorAbstractPort {
  private long _ref;
  public IntegratorNative2NativePlainPort() {
    super();
    createInstance();
  }
  /**
   * proxy for the native factory method
   */  
  public native void createInstance();
  
  /**
   * frees the memory of the component
   */
  public native void destroyInstance(long ref);
  
  
  /**
   * Connect a uses port.
   *
   * @throw If already connected to another port.
   * @see Operation with name of any implementing component 
   */
  @Override
  public void connect(Integrator  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
    super.connect(port);
    connect(_ref,_destination.getReference());
  }
  
  public native void connect(long ref,long cca_application);
   
  /**
   * Disconnect a port.
   * 
   * @throw If already not connected to type port.
   * @see Operation with name of any implementing component 
   */
  public void disconnect(Integrator  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
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

  public void step(final int dims[],final double dt,final double rhs[],final double stencil[],final long dof) {
    //DO NOTHING HERE
  }
  
  

}
 


