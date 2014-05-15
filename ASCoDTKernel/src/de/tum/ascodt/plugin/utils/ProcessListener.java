package de.tum.ascodt.plugin.utils;


import java.util.EventListener;


/**
 * Interface for process listeners . Can be used to detect different
 * exit values of external process.
 * 
 * @author Atanas Atanasov
 * 
 */
public interface ProcessListener extends EventListener {
  public void processFinished(int returnValue) throws de.tum.ascodt.utils.exceptions.ASCoDTException;
}
