//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package examples.heat;


public class RegularGridSocketDispatcher extends  SocketComponent {
  private long _ref;
  protected java.util.HashSet<RegularGrid>  _destinations;
  
  public RegularGridSocketDispatcher() throws de.tum.ascodt.utils.exceptions.ASCoDTException{
    _destinations = new java.util.HashSet<RegularGrid>();
  
  }
  
  public long getReference(){
    return _ref;
  }
  
  
  public void setReference(long ref){
     _ref=ref;
  }
  @Override
  public void completed(java.nio.channels.AsynchronousSocketChannel result, java.lang.Object attachment) {
    super.completed(result,attachment);
    //createInstance();
   
  }

  @Override
  public void failed(java.lang.Throwable exc, java.lang.Object attachment) {
     // TODO Auto-generated method stub
     
  }
  
  public void createInstance() throws de.tum.ascodt.utils.exceptions.ASCoDTException{
     int methodId=0;
     sendIntData(methodId);
     _ref=readLongData();
     
  } 
  
  
  /*public void destroyInstance() throws de.tum.ascodt.utils.exceptions.ASCoDTException{
     int methodId=1;
     sendIntData(methodId);
     sendLongData(_ref);
      
  }*/
  
  /**
   * Connect a uses port.
   *
   * @throw If already connected to another port.
   * @see Operation with name of any implementing component 
   */
  public void connect(RegularGrid  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
    connect(port.getReference());
     if (_destinations==null) {
      throw new de.tum.ascodt.utils.exceptions.ASCoDTException( getClass().getName(), "connect(...)", "port already was connected", null );
    }
    _destinations.add(port);
  }
  
  public void connect(long portRef) throws de.tum.ascodt.utils.exceptions.ASCoDTException{
      int method=0;
      sendIntData(method);
      sendLongData(portRef);
     
  }
  
  public void disconnect(RegularGrid  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
    
    disconnect(port.getReference());
    //((SocketComponent) port).close();
    if (_destinations==null) {
      throw new de.tum.ascodt.utils.exceptions.ASCoDTException( getClass().getName(), "disconnect(...)", "tried to disconnect port that was not connected before", null );
    }
     
    if (!_destinations.contains(port)) {
      throw new de.tum.ascodt.utils.exceptions.ASCoDTException( getClass().getName(), "disconnect(...)", "tried to disconnect port from port that was not connected before", null );
    }
    _destinations.remove(port);
  }
  
  public void disconnect(long portRef) throws de.tum.ascodt.utils.exceptions.ASCoDTException{
     int method=1;
     sendIntData(method);
     sendLongData(portRef);
     
  }
  
  public boolean isConnected(){
     return !_destinations.isEmpty();
  }
  
}
