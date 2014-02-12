/**
 * 
 */
package de.tum.ascodt.plugin.ui.wizards;

import java.io.IOException;
import java.net.MalformedURLException;

import org.eclipse.core.runtime.CoreException;
import org.eclipse.jface.viewers.IStructuredSelection;
import org.eclipse.jface.wizard.Wizard;
import org.eclipse.ui.INewWizard;
import org.eclipse.ui.IWorkbench;
import de.tum.ascodt.plugin.ASCoDTVTKPlugin;
import de.tum.ascodt.plugin.project.ProjectBuilder;
import de.tum.ascodt.plugin.ui.wizards.NewVTKWizardPage;
import de.tum.ascodt.plugin.ui.wizards.VTKMessages;
import de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice;
import de.tum.ascodt.plugin.vtk.VTKPipeline;
import de.tum.ascodt.resources.ResourceManager;
import de.tum.ascodt.utils.TemplateFile;
import de.tum.ascodt.utils.exceptions.ASCoDTException;

/**
 * @author Atanas Atanasov
 *
 */
public class VTKWizard extends Wizard implements INewWizard {
	public static String ID=VTKWizard.class.getCanonicalName();
	
	/**
	 * the main page of the wizard
	 */
	private NewVTKWizardPage _page;
	
	/**
	 * the initial project identifier
	 */
	private String _initialProjectIdentifier;
	

	public VTKWizard() {
		setWindowTitle(VTKMessages.NewVTKWizard);
	}

	/**
	 * insert the pages of the new component wizard
	 */
	@Override
	public void addPages() {
		super.addPages();
		_page=new NewVTKWizardPage(VTKMessages.NewVTKWizard);
		_page.setTitle(VTKMessages.CustomVTKNewWizard_2);
		_page.setDescription(VTKMessages.VTKFromScratch);
		addPage(_page);
		_page.setInitialProjectIdentifier(_initialProjectIdentifier);
	}
	
	@Override
	public void init(IWorkbench workbench, IStructuredSelection selection) {
		// TODO Auto-generated method stub

	}

	@Override
	public boolean performFinish() {
		de.tum.ascodt.plugin.utils.tracing.Trace trace = new de.tum.ascodt.plugin.utils.tracing.Trace(getClass().getName());
		trace.in( "performFinish()" );
		try {
		   
			String projectIdentifier=_page.getProjectName();
	    String componentInterface=_page.getComponentInterface();
	    org.eclipse.core.resources.IFile sourceFile = ProjectBuilder.getInstance().getProject(projectIdentifier).createJavaSourceFile(componentInterface.replaceAll("\\.", "/")+"VTKPipeline.java");
			
			_page.dispose();
			String[]namespaces=ProjectBuilder.getInstance().getProject(projectIdentifier).retrieveNamespaces(componentInterface);
			
			TemplateFile templateFile = new TemplateFile(
					ResourceManager.getResourceAsStream("new-vtk-pipeline.template",ASCoDTVTKPlugin.ID),
					sourceFile.getLocationURI().toURL(),
					namespaces,
					TemplateFile.getLanguageConfigurationForJava(),
					true);
			templateFile.addMapping("__COMPONENT_NAME__", componentInterface.substring(componentInterface.lastIndexOf(".")+1));
			templateFile.addMapping("__VTK_CLASS__", VTKPipeline.class.getCanonicalName());
			templateFile.open();
			templateFile.close();
	    	
		}catch (CoreException e) {
			ErrorWriterDevice.getInstance().showError( getClass().getName(), "performFinish()",  "Cannot create new vtk pipeline", e );
      trace.out( "performFinish()", false );
		} catch (MalformedURLException e) {
			ErrorWriterDevice.getInstance().showError( getClass().getName(), "performFinish()",  "Cannot create new vtk pipeline", e );
      trace.out( "performFinish()", false );
		} catch (IOException e) {
			ErrorWriterDevice.getInstance().showError( getClass().getName(), "performFinish()",  "Cannot create new vtk pipeline", e );
      trace.out( "performFinish()", false );
		} catch (ASCoDTException e) {
      ErrorWriterDevice.getInstance().showError( getClass().getName(), "performFinish()",  "Cannot create new vtk pipeline", e );
      trace.out( "performFinish()", false );
      return false;
    } 
		trace.out( "performFinish()" );
		return true;
	}

	/**
	 * Setter for the initial project identifier
	 * @param initialProjectIdentifier
	 */
	public void setInitialProjectIdentifier(String initialProjectIdentifier) {
		_initialProjectIdentifier=initialProjectIdentifier;
	}
}
