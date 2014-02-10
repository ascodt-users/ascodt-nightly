//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package fsdfsd;
public class SocketComponent 
     implements java.nio.channels.CompletionHandler< java.nio.channels.AsynchronousSocketChannel, Object>,
     
     de.tum.ascodt.repository.entities.SocketComponent,de.tum.ascodt.plugin.utils.ProcessListener{
     
     
     protected String _host;
     protected int _port;
     protected java.nio.channels.AsynchronousSocketChannel _channel; 
     protected java.nio.channels.AsynchronousServerSocketChannel _server; 
     protected int _bufferSize;
     protected  java.nio.channels.AsynchronousChannelGroup _group;
     protected boolean _isServer;
     protected java.nio.ByteBuffer _rcvBuffer;
     protected java.nio.ByteBuffer _sendBuffer;
     protected byte[] _rcvBytes;
     protected byte[] _sendBytes;
     /**
      * default constructor
      */
     protected SocketComponent()  throws de.tum.ascodt.utils.exceptions.ASCoDTException{
          this(de.tum.ascodt.plugin.services.SocketService.getDefault().getBufferSize()); 
     }

     protected SocketComponent(String host)  throws de.tum.ascodt.utils.exceptions.ASCoDTException{
          this(host,de.tum.ascodt.plugin.services.SocketService.getDefault().getBufferSize()); 
     }

     public int getPort(){
          return _port;
     }

     public String getHost(){
          return _host;
     }

     /**
      * server constructor
      */
     protected SocketComponent(int bufferSize)  throws de.tum.ascodt.utils.exceptions.ASCoDTException{
          _host="localhost";
          _port=de.tum.ascodt.plugin.services.SocketService.getDefault().getFreePort();
          _bufferSize=bufferSize;
          _rcvBytes=new byte[bufferSize];
          _sendBytes=new byte[bufferSize];
          _rcvBuffer=java.nio.ByteBuffer.wrap(_rcvBytes).order(java.nio.ByteOrder.LITTLE_ENDIAN);
          _sendBuffer=java.nio.ByteBuffer.wrap(_sendBytes).order(java.nio.ByteOrder.LITTLE_ENDIAN);
          //_rcvBuffer=java.nio.ByteBuffer.allocateDirect(_bufferSize).order(java.nio.ByteOrder.LITTLE_ENDIAN);
          //_sendBuffer=java.nio.ByteBuffer.allocateDirect(_bufferSize).order(java.nio.ByteOrder.LITTLE_ENDIAN);
          try {
               _group = java.nio.channels.AsynchronousChannelGroup.withThreadPool(java.util.concurrent.Executors.newSingleThreadExecutor());
          } catch (java.io.IOException e) {
               throw new de.tum.ascodt.utils.exceptions.ASCoDTException(
                         SocketComponent.class.getCanonicalName(),
                         "sendIntData()",
                         e.getLocalizedMessage(),
                         e);
          }
          _isServer=true;

     }

     protected SocketComponent(String host,int bufferSize)  throws de.tum.ascodt.utils.exceptions.ASCoDTException{
          _host = host;
          _port = de.tum.ascodt.plugin.services.SocketService.getDefault().getFreePort();
          _bufferSize = bufferSize;
          _rcvBytes=new byte[bufferSize];
          _sendBytes=new byte[bufferSize];
          _rcvBuffer=java.nio.ByteBuffer.wrap(_rcvBytes).order(java.nio.ByteOrder.LITTLE_ENDIAN);
          _sendBuffer=java.nio.ByteBuffer.wrap(_sendBytes).order(java.nio.ByteOrder.LITTLE_ENDIAN);
          try {
               _group = java.nio.channels.AsynchronousChannelGroup.withThreadPool(java.util.concurrent.Executors.newSingleThreadExecutor());
               _isServer=false;
          } catch (java.io.IOException e) {
               throw new de.tum.ascodt.utils.exceptions.ASCoDTException(
                         SocketComponent.class.getCanonicalName(),
                         "sendIntData()",
                         e.getLocalizedMessage(),
                         e);
          }

     } 
     public void processFinished(int exitValue) throws de.tum.ascodt.utils.exceptions.ASCoDTException{
          if(exitValue!=0)
               close();

     }

     public void open() throws de.tum.ascodt.utils.exceptions.ASCoDTException{


          if(_isServer){
               try{
                    _server=java.nio.channels.AsynchronousServerSocketChannel.open(_group).bind(
                              new java.net.InetSocketAddress(_port));
                    completed(_server.accept().get(),null);
               }catch (Exception e) {
                    throw new de.tum.ascodt.utils.exceptions.ASCoDTException(
                              SocketComponent.class.getCanonicalName(),
                              "sendIntData()",
                              e.getLocalizedMessage(),
                              e);
               }
          }else{
               try{
                    boolean initialized=false;
                    java.nio.channels.AsynchronousSocketChannel channel=null;
                    while(!initialized){

                         try {

                              channel= java.nio.channels.AsynchronousSocketChannel.open();
                              channel.connect(new java.net.InetSocketAddress(_host,_port)).get();

                         } catch (java.util.concurrent.ExecutionException e) {
                              System.out.println("trying client connection:"+_host+","+_port);
                              Thread.sleep(1000);
                              continue;
                         }
                         initialized=true;
                    }
                    completed(channel,null);
               } catch (java.lang.InterruptedException e) {
                    throw new de.tum.ascodt.utils.exceptions.ASCoDTException(
                              SocketComponent.class.getCanonicalName(),
                              "sendIntData()",
                              e.getLocalizedMessage(),
                              e);
               } catch (java.io.IOException e) {
                    throw new de.tum.ascodt.utils.exceptions.ASCoDTException(
                              SocketComponent.class.getCanonicalName(),
                              "sendIntData()",
                              e.getLocalizedMessage(),
                              e);
               }
          }


     }

     public boolean isServer(){
          return _isServer;
     }
     @Override
     public void completed(java.nio.channels.AsynchronousSocketChannel result, Object attachment) {
          synchronized(this){
               _channel=result;
          }

     }

     public synchronized boolean isConnected(){
          return _channel!=null;
     }


     @Override
     public void failed(Throwable exc, Object attachment) {
          //de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().showError(fullQualifiedClassName, methodName, message) 
     }

     protected void sendIntData(int data) throws de.tum.ascodt.utils.exceptions.ASCoDTException {

           _sendBuffer.clear();
           _sendBuffer.asIntBuffer().put(data);
           int sentBytes=0;
           try {
                while(sentBytes<_bufferSize)
                     sentBytes+=_channel.write(_sendBuffer).get();
           } catch (Exception e) {
                throw new de.tum.ascodt.utils.exceptions.ASCoDTException(
                          SocketComponent.class.getCanonicalName(),
                          "sendIntData()",
                          e.getLocalizedMessage(),
                          e);
           }

      }
     protected void sendLongData(long data) throws de.tum.ascodt.utils.exceptions.ASCoDTException {

           _sendBuffer.clear();
           _sendBuffer.asLongBuffer().put(data);
           int sentBytes=0;
           try {
                while(sentBytes<_bufferSize)
                     sentBytes+=_channel.write(_sendBuffer).get();
           } catch (Exception e) {
                throw new de.tum.ascodt.utils.exceptions.ASCoDTException(
                          SocketComponent.class.getCanonicalName(),
                          "sendLongData()",
                          e.getLocalizedMessage(),
                          e);
           }

      }
      protected void sendIntData(int []data) throws de.tum.ascodt.utils.exceptions.ASCoDTException {

           int bufferSize= (((data.length*4-1)/_bufferSize)+1)*_bufferSize;
           java.nio.ByteBuffer buffer= java.nio.ByteBuffer.allocate(bufferSize).order(java.nio.ByteOrder.LITTLE_ENDIAN);
           buffer.asIntBuffer().put(data);
           int offset=0;
           int sentBytes=0;
           try {
                while(offset*_bufferSize<bufferSize){
                     _sendBuffer.clear();
                     buffer.get(_sendBytes);
                     sentBytes=0;
                     while(sentBytes<_bufferSize)
                          sentBytes+=_channel.write(_sendBuffer).get();
                     offset++;
                }
           }catch (Exception e) {
                throw new de.tum.ascodt.utils.exceptions.ASCoDTException(
                          SocketComponent.class.getCanonicalName(),
                          "sendIntData()",
                          e.getLocalizedMessage(),
                          e);
           }
      }
     protected void sendLongData(long []data) throws de.tum.ascodt.utils.exceptions.ASCoDTException {

           int bufferSize= (((data.length*8-1)/_bufferSize)+1)*_bufferSize;
           java.nio.ByteBuffer buffer= java.nio.ByteBuffer.allocate(bufferSize).order(java.nio.ByteOrder.LITTLE_ENDIAN);
           buffer.asLongBuffer().put(data);
           int offset=0;
           int sentBytes=0;
           try {
                while(offset*_bufferSize<bufferSize){
                     _sendBuffer.clear();
                     buffer.get(_sendBytes);
                     sentBytes=0;
                     while(sentBytes<_bufferSize)
                          sentBytes+=_channel.write(_sendBuffer).get();
                     offset++;
                }
           }catch (Exception e) {
                throw new de.tum.ascodt.utils.exceptions.ASCoDTException(
                          SocketComponent.class.getCanonicalName(),
                          "sendLongData()",
                          e.getLocalizedMessage(),
                          e);
           }
      }
      protected void sendDoubleData(double data) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
           //java.nio.ByteBuffer buffer=java.nio.ByteBuffer.allocateDirect(_bufferSize).order(java.nio.ByteOrder.LITTLE_ENDIAN);
           _sendBuffer.clear();
           _sendBuffer.asDoubleBuffer().put(data);
           int sentBytes=0;
           try{
                while(sentBytes<_bufferSize)
                     sentBytes+=_channel.write(_sendBuffer).get();
           } catch (Exception e) {
                throw new de.tum.ascodt.utils.exceptions.ASCoDTException(
                          SocketComponent.class.getCanonicalName(),
                          "sendIntData()",
                          e.getLocalizedMessage(),
                          e);
           }

      }

      protected void sendDoubleData(double []data) throws de.tum.ascodt.utils.exceptions.ASCoDTException{
           int bufferSize= (((data.length*8-1)/_bufferSize)+1)*_bufferSize;
           java.nio.ByteBuffer buffer= java.nio.ByteBuffer.allocate(bufferSize).order(java.nio.ByteOrder.LITTLE_ENDIAN);
           buffer.asDoubleBuffer().put(data);
           int offset=0;
           int sentBytes=0;
           try {
                while(offset*_bufferSize<bufferSize){
                     _sendBuffer.clear();
                     buffer.get(_sendBytes);
                     sentBytes=0;
                     while(sentBytes<_bufferSize)
                          sentBytes+=_channel.write(_sendBuffer).get();
                     offset++;
                }
           } catch (Exception e) {
                throw new de.tum.ascodt.utils.exceptions.ASCoDTException(
                          SocketComponent.class.getCanonicalName(),
                          "sendIntData()",
                          e.getLocalizedMessage(),
                          e);
           }
      }

      protected void sendBooleanData(boolean data) throws de.tum.ascodt.utils.exceptions.ASCoDTException{
           sendIntData(data?1:0);
      }

      protected void sendBooleanData(boolean[] data) throws de.tum.ascodt.utils.exceptions.ASCoDTException{
           int[] convertedData=new int[data.length];
           for(int i=0;i<data.length;i++)
                convertedData[i]=data[i]?1:0;
           sendIntData(convertedData);
      }

      protected void sendStringData(String data)  throws de.tum.ascodt.utils.exceptions.ASCoDTException {
           try {
                java.nio.ByteBuffer strBuf=java.nio.charset.Charset.forName("UTF-8").encode(data+"\0");
                int bufferSize= (int) Math.ceil(((double)strBuf.capacity())/(double)de.tum.ascodt.plugin.services.SocketService.getDefault().getBufferSize())*de.tum.ascodt.plugin.services.SocketService.getDefault().getBufferSize();
                java.nio.ByteBuffer buffer= java.nio.ByteBuffer.allocate(bufferSize).order(java.nio.ByteOrder.LITTLE_ENDIAN);
                buffer.put(strBuf);   
                sendIntData(strBuf.capacity());
                buffer.rewind();
                _channel.write(buffer).get();
           } catch (Exception e) {
                throw new de.tum.ascodt.utils.exceptions.ASCoDTException(
                          SocketComponent.class.getCanonicalName(),
                          "sendIntData()",
                          e.getLocalizedMessage(),
                          e);
           }
      }

      protected void sendStringData(String [] data) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
           for(int i=0;i<data.length;i++){
                sendStringData(data[i]);
           }
      }
      

      protected int readIntData() throws de.tum.ascodt.utils.exceptions.ASCoDTException {
           try {
                //java.nio.ByteBuffer buffer=java.nio.ByteBuffer.allocate(_bufferSize).order(java.nio.ByteOrder.LITTLE_ENDIAN);
                _rcvBuffer.clear();
                int readBytes=0;
                while(readBytes<_bufferSize){ 
                     readBytes+=_channel.read(_rcvBuffer).get();
                }
                _rcvBuffer.flip();
                return _rcvBuffer.getInt();
           } catch (Exception e) {
                throw new de.tum.ascodt.utils.exceptions.ASCoDTException(
                          SocketComponent.class.getCanonicalName(),
                          "readIntData()",
                          e.getLocalizedMessage(),
                          e);
           }
      }
      protected long readLongData() throws de.tum.ascodt.utils.exceptions.ASCoDTException {
           try {
                //java.nio.ByteBuffer buffer=java.nio.ByteBuffer.allocate(_bufferSize).order(java.nio.ByteOrder.LITTLE_ENDIAN);
                _rcvBuffer.clear();
                int readBytes=0;
                while(readBytes<_bufferSize){ 
                     readBytes+=_channel.read(_rcvBuffer).get();
                }
                _rcvBuffer.flip();
                return _rcvBuffer.getLong();
           } catch (Exception e) {
                throw new de.tum.ascodt.utils.exceptions.ASCoDTException(
                          SocketComponent.class.getCanonicalName(),
                          "readLongData()",
                          e.getLocalizedMessage(),
                          e);
           }
      }


      protected void readIntData(int[] result,int size)  throws de.tum.ascodt.utils.exceptions.ASCoDTException {
           int readBytes=0;
           int bufferReadBytes=0;
           int bytesToRead=size*4;
           java.nio.ByteBuffer resultBuffer=java.nio.ByteBuffer.allocate(bytesToRead).order(java.nio.ByteOrder.LITTLE_ENDIAN);
           try{
                while(readBytes<bytesToRead){
                     _rcvBuffer.clear();
                     bufferReadBytes=0;
                     while(bufferReadBytes<_bufferSize)
                          bufferReadBytes+=_channel.read(_rcvBuffer).get();

                     readBytes+=_bufferSize;
                     _rcvBuffer.flip();
                     if(readBytes>bytesToRead){
                          resultBuffer.put(_rcvBytes,0,bytesToRead-readBytes+_bufferSize);
                     }else{
                          resultBuffer.put(_rcvBytes);
                     }
                }
                resultBuffer.flip();
                resultBuffer.asIntBuffer().get(result);
           } catch (Exception e) {
                throw new de.tum.ascodt.utils.exceptions.ASCoDTException(
                          SocketComponent.class.getCanonicalName(),
                          "readIntData()",
                          e.getLocalizedMessage(),
                          e);
           }
      }
      protected void readLongData(long[] result,int size)  throws de.tum.ascodt.utils.exceptions.ASCoDTException {
           int readBytes=0;
           int bufferReadBytes=0;
           int bytesToRead=size*8;
           java.nio.ByteBuffer resultBuffer=java.nio.ByteBuffer.allocate(bytesToRead).order(java.nio.ByteOrder.LITTLE_ENDIAN);
           try{
                while(readBytes<bytesToRead){
                     _rcvBuffer.clear();
                     bufferReadBytes=0;
                     while(bufferReadBytes<_bufferSize)
                          bufferReadBytes+=_channel.read(_rcvBuffer).get();

                     readBytes+=_bufferSize;
                     _rcvBuffer.flip();
                     if(readBytes>bytesToRead){
                          resultBuffer.put(_rcvBytes,0,bytesToRead-readBytes+_bufferSize);
                     }else{
                          resultBuffer.put(_rcvBytes);
                     }
                }
                resultBuffer.flip();
                resultBuffer.asLongBuffer().get(result);
           } catch (Exception e) {
                throw new de.tum.ascodt.utils.exceptions.ASCoDTException(
                          SocketComponent.class.getCanonicalName(),
                          "readLongData()",
                          e.getLocalizedMessage(),
                          e);
           }
      }
      protected double readDoubleData()  throws de.tum.ascodt.utils.exceptions.ASCoDTException  {
           try{
                _rcvBuffer.clear();
                int readBytes=0;
                while(readBytes<_bufferSize) 
                     readBytes+=_channel.read(_rcvBuffer).get();
                _rcvBuffer.flip();
                return _rcvBuffer.getDouble();
           } catch (Exception e) {
                throw new de.tum.ascodt.utils.exceptions.ASCoDTException(
                          SocketComponent.class.getCanonicalName(),
                          "readDoubleData()",
                          e.getLocalizedMessage(),
                          e);
           }
      }


      protected void readDoubleData(double [] result,int size)  throws de.tum.ascodt.utils.exceptions.ASCoDTException  {
           try{
                int readBytes=0,bufferReadBytes=0;
                int bytesToRead=size*8;
                java.nio.ByteBuffer resultBuffer=java.nio.ByteBuffer.allocate(bytesToRead).order(java.nio.ByteOrder.LITTLE_ENDIAN);;
                while(readBytes<bytesToRead){
                     _rcvBuffer.clear();
                     bufferReadBytes=0;
                     while(bufferReadBytes<_bufferSize)
                          bufferReadBytes+=_channel.read(_rcvBuffer).get();
                     readBytes+=_bufferSize;
                     _rcvBuffer.flip();
                     if(readBytes>bytesToRead){
                          resultBuffer.put(_rcvBytes,0,bytesToRead-readBytes+_bufferSize);
                     }else{
                          resultBuffer.put(_rcvBytes);
                     }
                }
                resultBuffer.flip();
                resultBuffer.asDoubleBuffer().get(result);
           } catch (Exception e) {
                throw new de.tum.ascodt.utils.exceptions.ASCoDTException(
                          SocketComponent.class.getCanonicalName(),
                          "readDoubleData()",
                          e.getLocalizedMessage(),
                          e);
           }
      }

      protected boolean readBooleanData() throws de.tum.ascodt.utils.exceptions.ASCoDTException {
           return readIntData()==1;
      }


      protected void readBooleanData(boolean[] result,int size)  throws de.tum.ascodt.utils.exceptions.ASCoDTException {
           int []result_i=new int[size];
           readIntData(result_i,size);
           for(int i=0;i<size;i++)
                result[i]=result_i[i]==1;
      }


      
      protected String readStringData()  throws de.tum.ascodt.utils.exceptions.ASCoDTException  {
           try{
                String res="";
                int stringSize=readIntData();
                int readBytes=0;
                int bufferSize= (int) Math.ceil(((double)stringSize)/(double)de.tum.ascodt.plugin.services.SocketService.getDefault().getBufferSize())*de.tum.ascodt.plugin.services.SocketService.getDefault().getBufferSize();
                java.nio.ByteBuffer buffer=java.nio.ByteBuffer.allocate(bufferSize).order(java.nio.ByteOrder.LITTLE_ENDIAN);
                while(readBytes<bufferSize)
                     readBytes+=_channel.read(buffer).get();
                byte[] strBytes=new byte[stringSize];
                buffer.flip();
                buffer.get(strBytes);
                res=new String(strBytes,java.nio.charset.Charset.forName("UTF-8"));
                return res;
           } catch (Exception e) {
                throw new de.tum.ascodt.utils.exceptions.ASCoDTException(
                          SocketComponent.class.getCanonicalName(),
                          "readStringData()",
                          e.getLocalizedMessage(),
                          e);
           }
      }

      void readStringData(String[]data,int size)  throws de.tum.ascodt.utils.exceptions.ASCoDTException {
           for(int i=0;i<size;i++){
                data[i]=readStringData();
           }
      }

     
     public void close(){
          try{
               if(_channel!=null){

                    _channel.close();
                    _channel=null;

                    System.out.println("destroying channel");
               }

               if(_server!=null){
                    System.out.println("destroying server");
                    _server.close();
                    _server=null;
               }
               _group.shutdownNow();
          }catch (Exception e) {
               de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice.getInstance().showError(
                SocketComponent.class.getCanonicalName(),
                 "close()",
                 "close exception()"+e.getMessage()
                
               );
          }
     }


     
}  

