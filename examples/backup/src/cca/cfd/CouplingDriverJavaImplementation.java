//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package cca.cfd;

import java.io.File;

import org.eclipse.swt.SWT;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.FileDialog;


public class CouplingDriverJavaImplementation extends CouplingDriverBasisJavaImplementation {
	public CouplingDriverJavaImplementation( String identifier ) throws de.tum.ascodt.utils.exceptions.ASCoDTException{
		super(identifier);
	}


	public boolean isValid() {
		// @todo Insert your code here
		return true;
	}


	public boolean hasGUI() {
		// @todo Insert your code here
		return true;
	}


	public void openGUI() {
		FileDialog fd = new FileDialog(Display.getDefault().getActiveShell(), SWT.OPEN);
		fd.setText("Scenario file:");
		fd.setFilterPath("/work_fast/atanasoa/Programme/workspace_new/LB_NS_EOF/trunk/src/configurationFiles");
		String[] filterExt = {"*.xml" };
		fd.setFilterExtensions(filterExt);
		String inputScenario = fd.open();
		if((new File(inputScenario)).exists()){
			this.go(inputScenario);
		}
	}


	public void closeGUI() {
		// @todo Insert your code here
	}

	public void destroy(){
		super.destroy();
	}

}



