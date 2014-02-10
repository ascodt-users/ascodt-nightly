//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package de.tum;


public abstract class DriverComponentAbstractJavaImplementation extends SocketComponent implements DriverComponent{
  protected de.tum.ascodt.plugin.ui.tabs.SocketClientAppsTab _appTab;
  protected String   _instanceName;
  protected String _projectLocation;
  public DriverComponentAbstractJavaImplementation( String instanceName ) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
    _instanceName = instanceName;
    _appTab = new de.tum.ascodt.plugin.ui.tabs.SocketClientAppsTab("DriverComponent",this, de.tum.ascodt.plugin.ui.views.AppsViewContainer.ID);
    _appTab.setVisible(true);
    _appTab.addListener(this);
    
    
  }
  
  public de.tum.ascodt.repository.Target getTarget() {
     return de.tum.ascodt.repository.Target.createReverseCxxRemoteSocketTarget();
  }
  
  public de.tum.ascodt.repository.TargetParameters getTargetParameters(){
     return de.tum.ascodt.repository.TargetParameters.createRemoteSocketParameters(
          _appTab.getHost(),
          _appTab.getPort()
          );
  }

  public long getReference(){
    return 0;
  }  
  
  public void setReference(long ref){
   
  }
  
  /**
   * @see de.tum.ascodt.repository.entities
   */
  public void lock() {
    
  }

  public void setProjectLocation(String location){
     _projectLocation = location;
     _appTab.setProjectLocation(location);
     if(_appTab.hasApplicationSettings())
          _appTab.execute();
  }
 
  /**
   * @see de.tum.ascodt.repository.entities
   */
  public void unlock() {
    
  }
  
 
  public void destroy()  {
          try{
               if(isConnected())
                    sendIntData(1);
          }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
               de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().showError(getClass().getName(), "destroy()", e);
          }
          super.close();
          _appTab.removeListener(this);
          _appTab.setVisible(false);
          _appTab.dispose();
    
  }
  
  public boolean isValid() {
     return true;
  }


  public boolean hasGUI() {
    // @todo Insert your code here
    return false;
  }
  
  
  public void openGUI() {
    // @todo Insert your code here
  }
  
  
  public void closeGUI() {
    // @todo Insert your code here
  }
  
  @Override
  public String getInstanceName() {
    return _instanceName;
  }

  @Override
  public void setInstanceName(String instanceName) {
    _instanceName=instanceName;
  }
  
  public void createInstance(){
     
  }
 
  public void destroyInstance(){
  }
 
  

  public void go() {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=5;
         sendIntData(methodId);
         
           
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().showError( getClass().getName() , "go()", e);
    }  
  }
  

  /**
   * Uses port
   */
  protected de.tum.FooBarSocketDispatcher _uPort = null;
  
  
 
  
  
  /**
   * @see Case class 
   */
  public de.tum.FooBar createPortForuPort(
     de.tum.ascodt.repository.Target target,
     de.tum.ascodt.repository.TargetParameters targetParameters
  ) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
    
    de.tum.FooBarSocketPort result = null;
    if (
      target.getType()==de.tum.ascodt.repository.Target.TargetType.JavaLocal||
      target.getType()==de.tum.ascodt.repository.Target.TargetType.JavaNative
    ) {
      result = new de.tum.FooBarSocket2JavaPlainPort();
     
    }else if(
      target.getType()==de.tum.ascodt.repository.Target.TargetType.ReverseFortranRemoteSocket||
      target.getType()==de.tum.ascodt.repository.Target.TargetType.ReverseCxxRemoteSocket
    ){
          result = new de.tum.FooBarSocket2SocketPlainPort(
               targetParameters.getStringParameter("host"),
               targetParameters.getIntParameter("port")
          );
    }
    assert(result!=null);
    _appTab.addListener(result);
    long port_ref=createClientPortForuPort(result);
    result.setReference(port_ref); 
    
    
    
    
    
    return result;
  }
  
  

   long createClientPortForuPort(de.tum.FooBarSocketPort socketPort) throws de.tum.ascodt.utils.exceptions.ASCoDTException{
     int method=6;
     long ref=-1;
     sendIntData(method);
     sendStringData(socketPort.getHost());
     sendIntData(socketPort.getPort());
     socketPort.open();
     ref=readLongData();
     return ref;
  }
  
  /**
   * @see Case class 
   */
  public void connectuPort(final de.tum.FooBar  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
    //assert(_isLocked);
    assert(port!=null);
     if(_uPort==null){
       
        _uPort = new de.tum.FooBarSocketDispatcher();
        _appTab.addListener(_uPort);
        long dispRef = connectClientDispatcheruPort(_uPort.getHost(),_uPort.getPort());
        _uPort.setReference(dispRef);
     }
     _uPort.connect(port);
              
   
   
  }
  
  public long  connectClientDispatcheruPort(String host,int port) throws de.tum.ascodt.utils.exceptions.ASCoDTException{
     int method=7;
     long ref=-1;
     sendIntData(method);
     sendStringData(host);
     sendIntData(port);
     _uPort.open();
     ref=readLongData();
     
     return ref;
  }
  
  
  
  /**
   * @see Case class 
   */
  public void disconnectuPort(final de.tum.FooBar  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
    assert(port!=null);
    if(_uPort!=null&&_uPort.isConnected()){
               assert(_uPort!=null );
               _appTab.removeListener(( de.tum.FooBarSocketPort)port);
               _uPort.disconnect(port);
               if(!_uPort.isConnected()){
                 _appTab.removeListener(_uPort);
                 disconnectDispatcheruPort();
                 _uPort.close();
                 _uPort = null;
               }
    }
  }
  
  public void disconnectDispatcheruPort() throws de.tum.ascodt.utils.exceptions.ASCoDTException{
     int methodId=8;
     sendIntData(methodId);
     
  }
  
  


}
 


