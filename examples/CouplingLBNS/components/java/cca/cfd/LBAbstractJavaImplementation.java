//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package cca.cfd;


public abstract class LBAbstractJavaImplementation extends SocketComponent implements LB{
  protected de.tum.ascodt.plugin.ui.tabs.SocketClientAppsTab _appTab;
  protected String   _instanceName;
  protected String _projectLocation;
  public LBAbstractJavaImplementation( String instanceName ) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
    _instanceName = instanceName;
    _appTab = new de.tum.ascodt.plugin.ui.tabs.SocketClientAppsTab("cca.cfd.LB",this, de.tum.ascodt.plugin.ui.views.AppsViewContainer.ID);
    _appTab.setVisible(true);
    _appTab.addListener(this);
    
    
  }
  
  public de.tum.ascodt.repository.Target getTarget() {
     return de.tum.ascodt.repository.Target.createCxxRemoteSocketTarget();
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
               de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
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
 
  

  public void setup(final String inputScenario) {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=23;
         sendIntData(methodId);
         sendStringData(inputScenario);

           
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }

  public void setupParallel(final String inputScenario) {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=23+1;
         sendIntData(methodId);
         sendStringData(inputScenario);

           
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }
    

  public void setupCommForNSRegion(final int startOfRegion[],final int endOfRegion[],final String commids[]) {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=25;
         sendIntData(methodId);
         sendIntData(startOfRegion.length);
sendIntData(startOfRegion);
sendIntData(endOfRegion.length);
sendIntData(endOfRegion);
sendIntData(commids.length);
sendStringData(commids);

           
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }

  public void setupCommForNSRegionParallel(final int startOfRegion[],final int endOfRegion[],final String commids[]) {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=25+1;
         sendIntData(methodId);
         sendIntData(startOfRegion.length);
sendIntData(startOfRegion);
sendIntData(endOfRegion.length);
sendIntData(endOfRegion);
sendIntData(commids.length);
sendStringData(commids);

           
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }
    

  public void solve() {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=27;
         sendIntData(methodId);
         
           
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }

  public void solveParallel() {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=27+1;
         sendIntData(methodId);
         
           
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }
    

  public void solveOneTimestep() {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=29;
         sendIntData(methodId);
         
           
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }

  public void solveOneTimestepParallel() {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=29+1;
         sendIntData(methodId);
         
           
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }
    

  public void setVelocities(final double velocitiesX[],final double velocitiesY[],final double velocitiesZ[]) {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=31;
         sendIntData(methodId);
         sendIntData(velocitiesX.length);
sendDoubleData(velocitiesX);
sendIntData(velocitiesY.length);
sendDoubleData(velocitiesY);
sendIntData(velocitiesZ.length);
sendDoubleData(velocitiesZ);

           
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }

  public void setVelocitiesParallel(final double velocitiesX[],final double velocitiesY[],final double velocitiesZ[]) {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=31+1;
         sendIntData(methodId);
         sendIntData(velocitiesX.length);
sendDoubleData(velocitiesX);
sendIntData(velocitiesY.length);
sendDoubleData(velocitiesY);
sendIntData(velocitiesZ.length);
sendDoubleData(velocitiesZ);

           
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }
    

  public void setPressure(final double pressure[]) {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=33;
         sendIntData(methodId);
         sendIntData(pressure.length);
sendDoubleData(pressure);

           
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }

  public void setPressureParallel(final double pressure[]) {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=33+1;
         sendIntData(methodId);
         sendIntData(pressure.length);
sendDoubleData(pressure);

           
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }
    

  public void setGradients(final double gradients[]) {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=35;
         sendIntData(methodId);
         sendIntData(gradients.length);
sendDoubleData(gradients);

           
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }

  public void setGradientsParallel(final double gradients[]) {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=35+1;
         sendIntData(methodId);
         sendIntData(gradients.length);
sendDoubleData(gradients);

           
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }
    

  public void closeLBProfiles() {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=37;
         sendIntData(methodId);
         
           
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }

  public void closeLBProfilesParallel() {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=37+1;
         sendIntData(methodId);
         
           
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }
    

  public void printLBDensity() {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=39;
         sendIntData(methodId);
         
           
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }

  public void printLBDensityParallel() {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=39+1;
         sendIntData(methodId);
         
           
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }
    

  public void printLBProfiles() {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=41;
         sendIntData(methodId);
         
           
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }

  public void printLBProfilesParallel() {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=41+1;
         sendIntData(methodId);
         
           
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }
    

  public void forwardVelocities(int keys[],int offsets[],int flips[],double values[],int ackn[]) {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=43;
         sendIntData(methodId);
         sendIntData(keys.length);
sendIntData(keys);
sendIntData(offsets.length);
sendIntData(offsets);
sendIntData(flips.length);
sendIntData(flips);
sendIntData(values.length);
sendDoubleData(values);
sendIntData(ackn);

         readIntData(ackn,1);
  
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }

  public void forwardVelocitiesParallel(int keys[],int offsets[],int flips[],double values[],int ackn[]) {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=43+1;
         sendIntData(methodId);
         sendIntData(keys.length);
sendIntData(keys);
sendIntData(offsets.length);
sendIntData(offsets);
sendIntData(flips.length);
sendIntData(flips);
sendIntData(values.length);
sendDoubleData(values);
sendIntData(ackn);

         readIntData(ackn,1);
  
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }
    

  public void forwardPressure(int keys[],int offsets[],int flips[],double values[],int ackn[]) {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=45;
         sendIntData(methodId);
         sendIntData(keys.length);
sendIntData(keys);
sendIntData(offsets.length);
sendIntData(offsets);
sendIntData(flips.length);
sendIntData(flips);
sendIntData(values.length);
sendDoubleData(values);
sendIntData(ackn);

         readIntData(ackn,1);
  
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }

  public void forwardPressureParallel(int keys[],int offsets[],int flips[],double values[],int ackn[]) {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=45+1;
         sendIntData(methodId);
         sendIntData(keys.length);
sendIntData(keys);
sendIntData(offsets.length);
sendIntData(offsets);
sendIntData(flips.length);
sendIntData(flips);
sendIntData(values.length);
sendDoubleData(values);
sendIntData(ackn);

         readIntData(ackn,1);
  
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }
    

  public void syncr(int value[]) {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=47;
         sendIntData(methodId);
         sendIntData(value);

         readIntData(value,1);
  
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }

  public void syncrParallel(int value[]) {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=47+1;
         sendIntData(methodId);
         sendIntData(value);

         readIntData(value,1);
  
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }
    

  public void plot() {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=49;
         sendIntData(methodId);
         
           
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }

  public void plotParallel() {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=49+1;
         sendIntData(methodId);
         
           
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }
    

  public void iterateBoundary() {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=10;
         sendIntData(methodId);
         
           
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }

  public void iterateBoundaryParallel() {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=10+1;
         sendIntData(methodId);
         
           
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }
    

  public void iterateInner() {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=12;
         sendIntData(methodId);
         
           
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }

  public void iterateInnerParallel() {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=12+1;
         sendIntData(methodId);
         
           
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }
    

  public void retrieveTimestep(double dt[]) {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=14;
         sendIntData(methodId);
         sendDoubleData(dt);

         readDoubleData(dt,1);
  
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }

  public void retrieveTimestepParallel(double dt[]) {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=14+1;
         sendIntData(methodId);
         sendDoubleData(dt);

         readDoubleData(dt,1);
  
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }
    

  public void retrieveVelocitiesSize(int memoryX[],int memoryY[],int memoryZ[]) {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=16;
         sendIntData(methodId);
         sendIntData(memoryX);
sendIntData(memoryY);
sendIntData(memoryZ);

         readIntData(memoryX,1);
readIntData(memoryY,1);
readIntData(memoryZ,1);
  
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }

  public void retrieveVelocitiesSizeParallel(int memoryX[],int memoryY[],int memoryZ[]) {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=16+1;
         sendIntData(methodId);
         sendIntData(memoryX);
sendIntData(memoryY);
sendIntData(memoryZ);

         readIntData(memoryX,1);
readIntData(memoryY,1);
readIntData(memoryZ,1);
  
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }
    

  public void retrieveVelocitiesCopy(double velocityX[],double velocityY[],double velocityZ[]) {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=18;
         sendIntData(methodId);
         sendIntData(velocityX.length);
sendDoubleData(velocityX);
sendIntData(velocityY.length);
sendDoubleData(velocityY);
sendIntData(velocityZ.length);
sendDoubleData(velocityZ);

         int velocityX_len;
velocityX_len=readIntData();
readDoubleData(velocityX,velocityX_len);
int velocityY_len;
velocityY_len=readIntData();
readDoubleData(velocityY,velocityY_len);
int velocityZ_len;
velocityZ_len=readIntData();
readDoubleData(velocityZ,velocityZ_len);
  
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }

  public void retrieveVelocitiesCopyParallel(double velocityX[],double velocityY[],double velocityZ[]) {
    //__SWITCH_SYNC_ASYNC__
    try{
         int methodId=18+1;
         sendIntData(methodId);
         sendIntData(velocityX.length);
sendDoubleData(velocityX);
sendIntData(velocityY.length);
sendDoubleData(velocityY);
sendIntData(velocityZ.length);
sendDoubleData(velocityZ);

         int velocityX_len;
velocityX_len=readIntData();
readDoubleData(velocityX,velocityX_len);
int velocityY_len;
velocityY_len=readIntData();
readDoubleData(velocityY,velocityY_len);
int velocityZ_len;
velocityZ_len=readIntData();
readDoubleData(velocityZ,velocityZ_len);
  
    }catch(de.tum.ascodt.utils.exceptions.ASCoDTException e){
       de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println(e);
    }  
  }
    

  /**
   * Uses port
   */
  protected cca.cfd.NSSolverSocketDispatcher _ns = null;
  
  
 
  
  
  /**
   * @see Case class 
   */
  public cca.cfd.NSSolver createPortForns(
     de.tum.ascodt.repository.Target target,
     de.tum.ascodt.repository.TargetParameters targetParameters
  ) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
    
    cca.cfd.NSSolverSocketPort result = null;
    if (
      target.getType()==de.tum.ascodt.repository.Target.TargetType.JavaLocal||
      target.getType()==de.tum.ascodt.repository.Target.TargetType.JavaNative||
      target.getType()==de.tum.ascodt.repository.Target.TargetType.FortranNative
    ) {
      result = new cca.cfd.NSSolverSocket2JavaPlainPort();
     
    }else if(
      target.getType()==de.tum.ascodt.repository.Target.TargetType.FortranRemoteSocket||
      target.getType()==de.tum.ascodt.repository.Target.TargetType.CxxRemoteSocket
    ){
          result = new cca.cfd.NSSolverSocket2SocketPlainPort(
               targetParameters.getStringParameter("host"),
               targetParameters.getIntParameter("port")
          );
    }
    assert(result!=null);
    _appTab.addListener(result);
    long port_ref=createClientPortForns(result);
    result.setReference(port_ref); 
    
    
    
    
    
    return result;
  }
  
  

   long createClientPortForns(cca.cfd.NSSolverSocketPort socketPort) throws de.tum.ascodt.utils.exceptions.ASCoDTException{
     int method=66;
     long ref=-1;
     sendIntData(method);
     sendStringData(socketPort.getHost());
     sendIntData(socketPort.getPort());
     socketPort.open();
     de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println("Create");
     ref=readLongData();
     de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println("Created: " + ref);
     return ref;
  }
  
  /**
   * @see Case class 
   */
  public void connectns(final cca.cfd.NSSolver  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
    //assert(_isLocked);
    assert(port!=null);
     if(_ns==null){
       
        _ns = new cca.cfd.NSSolverSocketDispatcher();
        _appTab.addListener(_ns);
        long dispRef = connectClientDispatcherns(_ns.getHost(),_ns.getPort());
        _ns.setReference(dispRef);
     }
     _ns.connect(port);
              
   
   
  }
  
  public long  connectClientDispatcherns(String host,int port) throws de.tum.ascodt.utils.exceptions.ASCoDTException{
     int method=67;
     long ref=-1;
     sendIntData(method);
     sendStringData(host);
     sendIntData(port);
     _ns.open();
     ref=readLongData();
     de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().println("Connected: " + ref);
     return ref;
  }
  
  
  
  /**
   * @see Case class 
   */
  public void disconnectns(final cca.cfd.NSSolver  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
    assert(port!=null);
    if(_ns!=null&&_ns.isConnected()){
               assert(_ns!=null );
               _appTab.removeListener(( cca.cfd.NSSolverSocketPort)port);
               _ns.disconnect(port);
               if(!_ns.isConnected()){
                 _appTab.removeListener(_ns);
                 disconnectDispatcherns();
                 _ns.close();
                 _ns = null;
               }
    }
  }
  
  public void disconnectDispatcherns() throws de.tum.ascodt.utils.exceptions.ASCoDTException{
     int methodId=68;
     sendIntData(methodId);
     
  }
  
  


}
 


