//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package de.tum.logging;


public class LoggerJavaImplementation extends LoggerBasisJavaImplementation {

	private LoggerUI _ui;

	public LoggerJavaImplementation( String identifier ) {
		super(identifier);
		_ui= new LoggerUI(this);
	}


	public boolean isValid() {
		// @todo Insert your code here
		return true;
	}


	public boolean hasGUI() {
		return true;
	}


	public void openGUI() {
		_ui.setVisible(true);
	}


	public void closeGUI() {
		_ui.setVisible(false);
	}

	public void destroy(){
		super.destroy();
		_ui.dispose();
	}

}


