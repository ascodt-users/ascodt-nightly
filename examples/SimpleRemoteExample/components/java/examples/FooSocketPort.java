//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package examples;
public interface FooSocketPort extends Foo,de.tum.ascodt.plugin.utils.ProcessListener{
     public String getHost();
     public int getPort();
     public void open() throws de.tum.ascodt.utils.exceptions.ASCoDTException;
     public void setReference(long ref);
}


