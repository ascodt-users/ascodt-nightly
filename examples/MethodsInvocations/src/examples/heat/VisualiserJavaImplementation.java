//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package examples.heat;

import de.tum.ascodt.plugin.ASCoDTVTKPlugin;


public class VisualiserJavaImplementation extends VisualiserBasisJavaImplementation {
  
  public VisualiserJavaImplementation( String identifier ) throws de.tum.ascodt.utils.exceptions.ASCoDTException{
    super(identifier);
    
  }
  
  
  public boolean isValid() {
    // @todo Insert your code here
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

  public void destroy(){
	  super.destroy();
  }

}
 


