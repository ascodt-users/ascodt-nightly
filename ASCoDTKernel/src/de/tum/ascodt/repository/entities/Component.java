package de.tum.ascodt.repository.entities;


import de.tum.ascodt.repository.Target;
import de.tum.ascodt.repository.TargetParameters;


/**
 * Represents one component
 * 
 * @author Tobias Weinzierl
 */
public interface Component {
  void closeGUI();

  void destroy();

  String getInstanceName();

  /**
   * Yields the target object, i.e. a description about the location and mode
   * in which this component is running.
   * 
   * @return
   */
  Target getTarget();

  TargetParameters getTargetParameters();

  /**
   * If this field is set, the workbench provides an open button for the GUI.
   * 
   * @return
   */
  boolean hasGUI();

  /**
   * Self-explaining.
   * 
   * @return
   */
  boolean isValid();

  /**
   * Before anybody invokes an operation on an component object, he has to call
   * lock. Only after lock() returns you may do something with the object. Do
   * not forget to call unlock() afterwards.
   */
  void lock();

  void openGUI();

  void setInstanceName(String instanceName);

  void setProjectLocation(String location);

  /**
   * Unlock component.
   * 
   * This is the counterpart of lock().
   * 
   * @see lock()
   */
  void unlock();
}
