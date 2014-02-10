//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package examples.heat;


public class Plotter2DNativeDispatcher extends Plotter2DDispatcher {
  protected long _ref;
  
  public Plotter2DNativeDispatcher(){
    createInstance();
  }
  
  public native void createInstance(); 
  
  public void destroy(){
    destroyInstance(_ref);
  }
  
  public native void destroyInstance(long ref);
  public long getReference(){
    return _ref;
  }
  /**
   * Connect a uses port.
   *
   * @throw If already connected to another port.
   * @see Operation with name of any implementing component 
   */
  public void connect(Plotter2D  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
    super.connect(port);
    connect(_ref,port.getReference());
  }
  
  public native void connect(long ref, long portRef);
  
  public void disconnect(Plotter2D  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
    super.disconnect(port);
    disconnect(_ref,port.getReference());
  }
  
  public native void disconnect(long ref, long portRef);

}
