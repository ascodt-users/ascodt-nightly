//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov
//
package test;


public abstract class AAbstractJavaNativeImplementation implements A {
  private boolean _isLocked;

  private String _instanceName;

  protected long _ref;

  public void
  setProjectLocation(String location) {}

  public AAbstractJavaNativeImplementation(String instanceName) {
    assert (instanceName != null);

    _instanceName = instanceName;
    _isLocked     = false;

    String path =
      getClass().getProtectionDomain().getCodeSource().getLocation().getPath();

    path = path.substring(0, path.indexOf("bin"));

    if (System.getProperty("os.name").startsWith("Windows")) {
      System.load(path + "/bin/test.A.dll");
    } else {
      System.load(path + "/lib/libtest.A.so");
    }

    createInstance();
  }
  public long
  getNativeReference() {
    return _ref;
  }

  /**
   * proxy for the native factory method
   */
  public native void
  createInstance();

  /**
   * frees the memory of the component
   */
  public native void
  destroyInstance(long ref);

  /**
   * @see de.tum.ascodt.repository.entities
   */
  public void
  lock() {}

  /**
   * @see de.tum.ascodt.repository.entities
   */
  public void
  unlock() {}

  /**
   * @see de.tum.ascodt.repository.entities
   */
  public de.tum.ascodt.repository.Target
  getTarget() {
    return de.tum.ascodt.repository.Target.createCxxNativeTarget();
  }

  public de.tum.ascodt.repository.TargetParameters
  getTargetParameters() {
    return null;
  }

  /**
   * @see de.tum.ascodt.repository.entities
   */
  public String
  getInstanceName() {
    return _instanceName;
  }

  /**
   * @see de.tum.ascodt.repository.entities
   */
  public void
  setInstanceName(String instanceName) {
    _instanceName = instanceName;
  }

  /**
   * @see de.tum.ascodt.repository.entities
   */
  public void
  destroy() {
    destroyInstance(_ref);
  }

  public long
  getReference() {
    return _ref;
  }

  public void
  setReference(long ref) {
    _ref = ref;
  }


  public void bar(){
     
     bar(_ref);
     
  }
  public native void bar(long ref);
  

  /**
   * Uses port
   */
  protected test.FooNativeDispatcher _foo = null;
  
    
  /**
   * @see Case class 
   */
  public void connectfoo(test.Foo  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
    assert(_isLocked);
    assert(port!=null);
   
    if(_foo==null){
       _foo = new test.FooNativeDispatcher();
       connectfoo(_ref,_foo.getReference());
    }
    _foo.connect(port);
   
  }
  
  private native void connectfoo(long ref,long portRef);
  
  /**
   * @see Case class 
   */
  public test.Foo createPortForfoo(
     de.tum.ascodt.repository.Target  target ,
     de.tum.ascodt.repository.TargetParameters targetParameters
     ) throws de.tum.ascodt.utils.exceptions.ASCoDTException{
    test.Foo result = null;
        
    if (target.getType()==de.tum.ascodt.repository.Target.TargetType.JavaLocal) {
      result = new test.FooNative2JavaPlainPort();
    }
    if (target.getType()==de.tum.ascodt.repository.Target.TargetType.JavaNative) {
      result = new test.FooNative2NativePlainPort();
    }
    if (target.getType()==de.tum.ascodt.repository.Target.TargetType.FortranNative) {
        result = new test.FooNative2JavaPlainPort();
    }
  
    /*if (target.getType()==de.tum.ascodt.repository.Target.TargetType.FortranRemoteSocket) {
      result = new test.FooNative2SocketClientPlainPort();
    }
    if (target.getType() == de.tum.ascodt.repository.Target.TargetType.CxxRemoteSocket){
      result = new test.FooCxx2CxxRemoteSocketPort();
    }
    if (target.getType() == de.tum.ascodt.repository.Target.TargetType.ReverseCxxRemoteSocket){
      result = new test.FooReverseCxx2CxxRemoteSocketPort();
    }*/  
    assert(result!=null);
    
    return result;
  }
  

  /**
   * @see Case class 
   */
  public void disconnectfoo(test.Foo  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
    assert(_isLocked);
    assert(port!=null);
    if (_foo==null ) {
      throw new de.tum.ascodt.utils.exceptions.ASCoDTException( getClass().getName(), "disconnectfoo(...)", "tried to disconnect uses port that has not been connected to any other port before", null );
    }
    
    _foo.disconnect(port);
    
    if(!_foo.isConnected()){
      disconnectfoo(_ref);
      _foo.destroy();
      _foo = null;
    }
  }
  
  
   private native void disconnectfoo(long ref);
}


