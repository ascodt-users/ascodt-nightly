//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package examples.heat;


public class fMeshSocket2JavaPlainPort extends fMeshAbstractSocketPort 
     implements java.lang.Runnable,java.nio.channels.CompletionHandler< java.nio.channels.AsynchronousSocketChannel, Object>{

  interface fMeshSocketInvoker {
    void invoke() throws de.tum.ascodt.utils.exceptions.ASCoDTException;
  } 
  private long _ref;
  private fMeshSocketInvoker[] _invokers;
  private java.util.concurrent.ExecutorService _executor;
  public fMeshSocket2JavaPlainPort(String host,int port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
    super(host,port);
    _invokers = new  fMeshSocketInvoker[241];
    	_invokers[40]= new fMeshSocketInvoker(){
		public void invoke() throws de.tum.ascodt.utils.exceptions.ASCoDTException{
			invoke_allocate();
		}
	};
	_invokers[41]= new fMeshSocketInvoker(){
		public void invoke() throws de.tum.ascodt.utils.exceptions.ASCoDTException{
			invoke_copyData();
		}
	};
	_invokers[42]= new fMeshSocketInvoker(){
		public void invoke() throws de.tum.ascodt.utils.exceptions.ASCoDTException{
			invoke_getData();
		}
	};

  }
  
  public fMeshSocket2JavaPlainPort() throws de.tum.ascodt.utils.exceptions.ASCoDTException {
    super();
    _invokers = new  fMeshSocketInvoker[241];
    	_invokers[40]= new fMeshSocketInvoker(){
		public void invoke() throws de.tum.ascodt.utils.exceptions.ASCoDTException{
			invoke_allocate();
		}
	};
	_invokers[41]= new fMeshSocketInvoker(){
		public void invoke() throws de.tum.ascodt.utils.exceptions.ASCoDTException{
			invoke_copyData();
		}
	};
	_invokers[42]= new fMeshSocketInvoker(){
		public void invoke() throws de.tum.ascodt.utils.exceptions.ASCoDTException{
			invoke_getData();
		}
	};

  }
  
  @Override
  public void completed(java.nio.channels.AsynchronousSocketChannel result, java.lang.Object attachment) {
    super.completed(result,attachment);
    //createInstance();
    _executor=java.util.concurrent.Executors.newSingleThreadExecutor();
    _executor.execute(this);           
   
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
  public void destroyInstance() throws de.tum.ascodt.utils.exceptions.ASCoDTException{
     int methodId=1;
     sendIntData(methodId);
     sendLongData(_ref);
          
  }
  
  /**
   * Disconnect a port.
   * 
   * @throw If already not connected to type port.
   * @see Operation with name of any implementing component 
   */
  //public void disconnect(fMesh  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
     //destroyInstance();
  //   super.disconnect(port);
  //}
  
  
  public long getReference(){
    return _ref;
  }  
  
  public void setReference(long ref){
     _ref=ref;
  }
  
  public void close(){
     if(_executor!=null&&!_executor.isShutdown())
          _executor.shutdownNow();
     super.close();
  }
  public void run(){
     int methodId=0;
     try{
          methodId=readIntData(); 
          while(methodId!=-1){
             
              _invokers[methodId].invoke();
              methodId=readIntData();      
          }
         
     }catch(Exception e){
          
          
          de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().showError(
            fMeshSocket2JavaPlainPort.class.getCanonicalName(),
            "run()",
            "Operation fetching error:"+e.getMessage()
           
          );
     }
     super.close();
  }

  public void invoke_getData() throws 
         de.tum.ascodt.utils.exceptions.ASCoDTException{
     long [] handle= new long[1];
readLongData(handle,1);

     getData(handle);
     sendLongData(handle);

  }
  public void getData(long handle[]) {
     _destination.getData(handle);
  }
  

  public void invoke_copyData() throws 
         de.tum.ascodt.utils.exceptions.ASCoDTException{
     int data_len=readIntData();
double []data=new double[data_len];
readDoubleData(data,data_len);

     copyData(data);
     sendIntData(data.length);
sendDoubleData(data);

  }
  public void copyData(double data[]) {
     _destination.copyData(data);
  }
  

  public void invoke_allocate() throws 
         de.tum.ascodt.utils.exceptions.ASCoDTException{
     int dim_len=readIntData();
int []dim=new int[dim_len];
readIntData(dim,dim_len);

     allocate(dim);
     
  }
  public void allocate(final int dim[]) {
     _destination.allocate(dim);
  }
  


}
 

