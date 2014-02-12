//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package de.tum.logging;

import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.apache.logging.log4j.core.LoggerContext;
import org.apache.logging.log4j.core.config.XMLConfigurationFactory;
import org.apache.logging.log4j.status.StatusLogger;


public class LoggerBasisJavaImplementation extends de.tum.logging.LoggerAbstractJavaImplementation {
  public LoggerBasisJavaImplementation( String identifier ) {
    super(identifier);
  }
  
  public void setXMLConfiguration(String fileName){
		System.setProperty(
				XMLConfigurationFactory.CONFIGURATION_FILE_PROPERTY,
				fileName);
		final LoggerContext ctx = (LoggerContext) LogManager.getContext(false);
      ctx.reconfigure();
      StatusLogger.getLogger().reset();
	}

  /**
   * Provides methods block
   */

  public void info(final String logger,final String message) {
	  Logger log = LogManager.getLogger(logger);
	  log.info(message);	
  }
  

  public void debug(final String logger,final String message) {
	  Logger log = LogManager.getLogger(logger);
	  log.debug(message);	
  }
  

  public void warn(final String logger,final String message) {
	  Logger log = LogManager.getLogger(logger);
	  log.warn(message);	
  }
  

  public void error(final String logger,final String message) {
	  Logger log = LogManager.getLogger(logger);
	  log.error(message);	
  }

}
 
