//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package examples.heat;


public abstract class LaplaceAbstractJavaImplementation implements Laplace {
  /**
   * Semaphore object.
   */
  private boolean  _isLocked;
  
  private String   _instanceName;

  private long _reference;
  public LaplaceAbstractJavaImplementation(String instanceName) {
    assert(instanceName!=null); 
    _instanceName = instanceName;
    
  }
    
  public long getReference(){
    return _reference;
  }  
  
  public void setProjectLocation(String location){
  }
  public void setReference(long reference){
     _reference = reference;
  }
  /**
   * @see de.tum.ascodt.repository.entities
   */
  public void lock() {
    
  }

 
  /**
   * @see de.tum.ascodt.repository.entities
   */
  public void unlock() {
    
  }
  

    
  /**
   * @see de.tum.ascodt.repository.entities
   */
  public de.tum.ascodt.repository.Target getTarget() {
    return de.tum.ascodt.repository.Target.createJavaLocalTarget();
  }
  public de.tum.ascodt.repository.TargetParameters getTargetParameters(){
    return null;
  }

  /**
   * @see de.tum.ascodt.repository.entities
   */
  public String getInstanceName() {
    return _instanceName;
  }
  
  /**
   * @see de.tum.ascodt.repository.entities
   */
  public void setInstanceName(String instanceName){
     _instanceName=instanceName;
  }
  
  /**
   * @see de.tum.ascodt.repository.entities
   */
  /**
   * @see de.tum.ascodt.repository.entities
   */
  public void destroy(){
  
  }
  
  public boolean isValid() {
     return true;
  }


  public boolean hasGUI() {
    // @todo Insert your code here
    return false;
  }
  
  
  public void openGUI() {
    
  }
  
  
  public void closeGUI() {
    
  }

  

}
 


