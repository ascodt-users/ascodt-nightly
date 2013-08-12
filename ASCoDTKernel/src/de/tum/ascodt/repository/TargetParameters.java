package de.tum.ascodt.repository;

import java.util.HashMap;

public class TargetParameters {
	private HashMap<String,String> _stringArgs;
	private HashMap<String,Integer> _intArgs;
	public TargetParameters(){
		_stringArgs=new HashMap<String,String>();
		_intArgs = new HashMap<String,Integer>();
	}
	
	public String getStringParameter(String key){
		return _stringArgs.get(key);
	}
	
	public int getIntParameter(String key){
		return _intArgs.get(key);
	}
	
	public static TargetParameters createRemoteSocketParameters(String host,int port){
		TargetParameters parameters = new TargetParameters();
		parameters._stringArgs.put("host", host);
		parameters._intArgs.put("port", port);
		return parameters;
	}
}
