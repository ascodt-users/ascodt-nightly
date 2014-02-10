//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package examples.heat;


public interface Stencil  {
  class IntegerWrapper {
    public int value;
  }
  class DoubleWrapper {
    public double value;
  }
  class StringWrapper {
    public String value;
  }
  class BooleanWrapper {
    public boolean value;
  }
  public long getReference();
  public void setReference(long ref);
  //void lock();
 
  //void unlock();
  

  public void getStencil(double stencil[]);


}
 


