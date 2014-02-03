package de.tum.ascodt.plugin.services;


public class SocketService{
	
	private static SocketService singleton;
	private int port=50000;
	private int _bufferSize;
	public SocketService() {
		_bufferSize=16*1024;
		
	}
	public static SocketService getDefault(){
		if(singleton==null)
			singleton=new SocketService();
		return singleton;
	}
	
	public int getBufferSize(){
		return _bufferSize;
	}
	public synchronized int getFreePort(){
		return port++; 
	}
	
}
