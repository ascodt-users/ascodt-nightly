//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package test;


public class AJavaImplementation extends AAbstractJavaNativeImplementation {
  public AJavaImplementation( String identifier ) {
    super(identifier);
  }
  
 
  
  public boolean isValid() {
    // @todo Insert your code here
    return true;
  }


  public boolean hasGUI() {
    // @todo Insert your code here
    return true;
  }
  
  
  public void openGUI() {
    this.bar();
  }
  
  
  public void closeGUI() {
    // @todo Insert your code here
  }

  public void destroy(){
    super.destroy();
  }



@Override
public void barParallel() {
	// TODO Auto-generated method stub
	
}

}
 


