package de.tum.ascodt.plugin.ui.wizards;

import org.eclipse.osgi.util.NLS;

public class VTKMessages extends NLS {
	private static final String BUNDLE_NAME = "de.tum.ascodt.plugin.ui.wizards.messages"; //$NON-NLS-1$
	public static String NewVTKWizard;
	public static String VTKFromScratch;
	public static String CustomVTKNewWizard_2;
	
	static {
		// initialize resource bundle
		NLS.initializeMessages(BUNDLE_NAME, VTKMessages.class);
	}

	private VTKMessages() {
	}
}
