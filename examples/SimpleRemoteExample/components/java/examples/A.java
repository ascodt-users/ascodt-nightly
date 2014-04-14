//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package examples;


public interface A extends examples.Driver,de.tum.ascodt.repository.entities.CxxReverseRemoteSocketComponent {

  public static final String Implementation = "";
  

  /**
   * Connect a uses port.
   *
   * @throws ASCoDTException If you connect the same object twice and if you 
   *           try to connect to several ports even though 
   *           mayConnectMultiplePortsTofooHandler() returns false.
   * @param port Valid port instance. Use factory method createPortForfooHandler() to 
   *           create port instances. 
   */
  void connectfooHandler(examples.Foo  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException;
  
  /**
   * Create a port object for a given target. Each class is well aware of its 
   * own target and thus can create the port that is best suited for it. If 
   * the target is running remotely, e.g., and the destination target it the 
   * same remote machine, both components can communicate directly and the 
   * returned java port simply is a representant for this direct communication.
   */
  examples.Foo createPortForfooHandler(
     de.tum.ascodt.repository.Target  target,
     de.tum.ascodt.repository.TargetParameters  targetParameters
  ) throws de.tum.ascodt.utils.exceptions.ASCoDTException;
  
  /**
   * Disconnect a port.
   * 
   * @throws ASCoDTException If the port has not been successfully connected to 
   *            the component before. 
   */
  void disconnectfooHandler(examples.Foo  port) throws de.tum.ascodt.utils.exceptions.ASCoDTException;
  
  //boolean mayConnectMultiplePortsTofooHandler();

}
 


