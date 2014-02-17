package de.tum.ascodt.plugin.utils;


import java.util.HashSet;

import de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice;
import de.tum.ascodt.utils.exceptions.ASCoDTException;


/**
 * A detector class to for listening to process exit events
 * 
 * @author Atanas Atanasov
 * 
 */
public class ProcessExitDetector implements Runnable {

  private Process _process;
  private HashSet<ProcessListener> _listeners;

  public ProcessExitDetector() {
    _listeners = new HashSet<ProcessListener>();
  }

  public synchronized void addListener(ProcessListener listener) {
    _listeners.add(listener);
  }

  public synchronized void notifyListeners(int returnValue) {
    try {
      for (ProcessListener listener : _listeners) {
        listener.processFinished(returnValue);
      }

      _listeners.clear();
    } catch (ASCoDTException e) {
      ErrorWriterDevice.getInstance().showError(getClass().getName(),
          "notifyListeners()", "process finished error!", e);
      e.printStackTrace();
    }
  }

  public synchronized void removeListener(ProcessListener listener) {
    if (_listeners.contains(listener)) {
      _listeners.remove(listener);
    }
  }

  @Override
  public void run() {
    try {
      notifyListeners(_process.waitFor());
    } catch (InterruptedException e) {
      notifyListeners(-1);
      ErrorWriterDevice.getInstance().showError(getClass().getName(),
          "ProcessExitDetector", "process waitFor interrupted", e);

    }

  }

  public synchronized void setProcess(Process p) {
    _process = p;
  }

}