//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package de.tum;


public class FooBarPlainJavaPort extends FooBarAbstractPort {

  public FooBarPlainJavaPort() {
    super();
  }
  

  public void foo(final double data[]) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.foo(data);
      //_destination.unlock();
    //}
  }
  

  public void bar(double data[]) {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.bar(data);
      //_destination.unlock();
    //}
  }
  

  public void reset() {
   // if (_destination!=null) {
      //_destination.lock();
      _destination.reset();
      //_destination.unlock();
    //}
  }
  
  

}
 


