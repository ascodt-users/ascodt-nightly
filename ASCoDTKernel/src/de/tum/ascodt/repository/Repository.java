package de.tum.ascodt.repository;


import java.io.Serializable;
import java.util.Map.Entry;


class NonSerializableRepository {
  protected java.util.Set<RepositoryListener> _myListeners;

  NonSerializableRepository() {
    _myListeners = new java.util.HashSet<RepositoryListener>();
  }
}

/**
 * A component repository
 * 
 * 
 * @image html architecture.png
 * 
 * @author Tobias Weinzierl
 */
public class Repository extends NonSerializableRepository implements
    Serializable {

  /**
   * default serialisation id
   */
  private static final long serialVersionUID = 1L;

  /**
   * list of the project component interfaces
   */
  private java.util.HashMap<String, String> _componentInterfaces;

  public Repository() {

    _componentInterfaces = new java.util.HashMap<String, String>();
  }

  /**
   * adds a new component description to the repository
   * 
   * @param componentInterface
   * @param description
   */
  public void addComponent(String componentInterface, String target) {
    if (!_componentInterfaces.containsKey(componentInterface)) {
      _componentInterfaces.put(componentInterface, target);
      informListenersAboutChangedComponents();
    }
  }

  public void addListener(RepositoryListener listener) {
    _myListeners.add(listener);
    informListenersAboutChangedComponents();
  }

  public void informListenersAboutChangedComponents() {
    for (RepositoryListener listener : _myListeners) {
      listener.begin();
      for (Entry<String, String> componentEntry : _componentInterfaces
          .entrySet()) {
        listener.notify(componentEntry.getKey(), componentEntry.getValue());
      }
      listener.end();
    }
  }

  // /**
  // * remove a component interface from the repository
  // * @param componentInterface the interface to be removed
  // */
  // public void removeComponent(String componentInterface) {
  // if(_componentInterfaces.containsKey(componentInterface)){
  // _componentInterfaces.remove( componentInterface );
  // informListenersAboutChangedComponents();
  // }
  // }
  //

  public void removeListener(RepositoryListener listener) {
    _myListeners.remove(listener);
    informListenersAboutChangedComponents();
  }

  public void reset() {
    _componentInterfaces.clear();
    informListenersAboutChangedComponents();
  }

}
