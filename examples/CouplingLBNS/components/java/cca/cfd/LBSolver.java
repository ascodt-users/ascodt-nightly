//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package cca.cfd;


public interface LBSolver  {
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
  

  public void setup(final String inputScenario);
  public void setupParallel(final String inputScenario);

  public void setupCommForNSRegion(final int startOfRegion[],final int endOfRegion[],final String commids[]);
  public void setupCommForNSRegionParallel(final int startOfRegion[],final int endOfRegion[],final String commids[]);

  public void solve();
  public void solveParallel();

  public void solveOneTimestep();
  public void solveOneTimestepParallel();

  public void setVelocities(final double velocitiesX[],final double velocitiesY[],final double velocitiesZ[]);
  public void setVelocitiesParallel(final double velocitiesX[],final double velocitiesY[],final double velocitiesZ[]);

  public void setPressure(final double pressure[]);
  public void setPressureParallel(final double pressure[]);

  public void setGradients(final double gradients[]);
  public void setGradientsParallel(final double gradients[]);

  public void closeLBProfiles();
  public void closeLBProfilesParallel();

  public void printLBDensity();
  public void printLBDensityParallel();

  public void printLBProfiles();
  public void printLBProfilesParallel();

  public void forwardVelocities(int keys[],int offsets[],int flips[],double values[],int ackn[]);
  public void forwardVelocitiesParallel(int keys[],int offsets[],int flips[],double values[],int ackn[]);

  public void forwardPressure(int keys[],int offsets[],int flips[],double values[],int ackn[]);
  public void forwardPressureParallel(int keys[],int offsets[],int flips[],double values[],int ackn[]);

  public void syncr(int value[]);
  public void syncrParallel(int value[]);

  public void plot();
  public void plotParallel();


}
 


