package de.tum.ascodt.sidlcompiler.backend;

import java.io.File;
import java.net.URL;

import org.eclipse.core.runtime.Assert;

import de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice;
import de.tum.ascodt.sidlcompiler.astproperties.GetProvidesAndUsesPortsOfComponent;
import de.tum.ascodt.sidlcompiler.frontend.node.AClassPackageElement;
import de.tum.ascodt.sidlcompiler.frontend.node.AUses;
import de.tum.ascodt.sidlcompiler.symboltable.SymbolTable;
import de.tum.ascodt.utils.TemplateFile;
import de.tum.ascodt.utils.exceptions.ASCoDTException;

/**
 * Compiler Adapter for generating fortran makefiles
 * @author Atanas Atanasov
 *
 */
public class CreateCxxBuildScripts extends de.tum.ascodt.sidlcompiler.frontend.analysis.DepthFirstAdapter{
	private java.util.Stack< TemplateFile >   _templateFilesOfCxxMakefile;
	private java.util.Stack< TemplateFile >   _templateFilesOfCxxCMakefile;
	private URL                               _userImplementationsDestinationDirectory;
	private URL 							  							_generatedFilesDirectory;
	
	private String[]                          _namespace;
	private SymbolTable                       _symbolTable;


	CreateCxxBuildScripts(SymbolTable symbolTable, URL userImplementationsDestinationDirectory
			,URL generatedFilesDirectory,URL nativeDirectory, String[] namespace){
		_templateFilesOfCxxMakefile  = new java.util.Stack< TemplateFile >();
		_templateFilesOfCxxCMakefile = new java.util.Stack< TemplateFile >();
		_userImplementationsDestinationDirectory = userImplementationsDestinationDirectory;
		_generatedFilesDirectory  = generatedFilesDirectory;
		_namespace            = namespace;
		_symbolTable          = symbolTable;
	}

	public void inAClassPackageElement(AClassPackageElement node) {
		try {
			String  componentName              = node.getName().getText();
			String fullQualifiedName													 = _symbolTable.getScope(node).getFullQualifiedName(componentName) ;

			String  templateFileForCxxMakefile 						     = "makefile-cxx.template";
			String  destinationFileForCxxMakefile							 = _userImplementationsDestinationDirectory.toString() + File.separatorChar + "Makefile."+componentName;
			String  templateFileForCxxCMakefile 						     = "cmakefile-cxx.template";
			String  destinationFileForCxxCMakefile							 = _userImplementationsDestinationDirectory.toString() + File.separatorChar + "cmake-"+fullQualifiedName+ File.separatorChar +"CMakeLists.txt";
			
			
			_templateFilesOfCxxMakefile.push(
					new TemplateFile( templateFileForCxxMakefile, destinationFileForCxxMakefile, _namespace, TemplateFile.getLanguageConfigurationForCPP(),true)
					);
			_templateFilesOfCxxCMakefile.push(
					new TemplateFile( templateFileForCxxCMakefile, destinationFileForCxxCMakefile, _namespace, TemplateFile.getLanguageConfigurationForCPP(),false)
					);
			createComponentMappings(componentName, fullQualifiedName,_templateFilesOfCxxMakefile);
			createComponentMappings(componentName, fullQualifiedName,_templateFilesOfCxxCMakefile);
			
			_templateFilesOfCxxMakefile.peek().addMapping( "__TAB__","\t");
			_templateFilesOfCxxMakefile.peek().open();
			_templateFilesOfCxxCMakefile.peek().open();
		}catch (ASCoDTException  e ) {
			ErrorWriterDevice.getInstance().showError(getClass().getName(), "inAInterfacePackageElement(...)", e);
		}
	}

	private void createComponentMappings(String componentName,
			String fullQualifiedName,
			java.util.Stack< TemplateFile > template) {
		template.peek().addMapping( "__COMPONENT_NAME__", componentName );
		template.peek().addMapping( "__PATH_FULL_QUALIFIED_NAME__",fullQualifiedName.replaceAll("[.]", "/"));
		template.peek().addMapping( "__GENERATED_OUTPUT__", _generatedFilesDirectory.getPath().toString() );
		template.peek().addMapping( "__SRC_OUTPUT__", _userImplementationsDestinationDirectory.getPath().toString() );
	}

	/**
	 * Close the output streams.
	 */
	public void outAClassPackageElement(AClassPackageElement node) {
		Assert.isTrue( _templateFilesOfCxxMakefile.size()==1 );
		Assert.isTrue( _templateFilesOfCxxCMakefile.size()==1 );

		try {
			_templateFilesOfCxxMakefile.peek().close();
			_templateFilesOfCxxCMakefile.peek().close();
		}
		catch (ASCoDTException  e ) {
			ErrorWriterDevice.getInstance().showError(getClass().getName(), "inAInterfacePackageElement(...)", e);
		}

		_templateFilesOfCxxMakefile.pop();
		_templateFilesOfCxxCMakefile.pop();
	}

	/**
	 * For each uses relation, we have to generate all the connection 
	 * operations.
	 */
	public void inAUses(AUses node) {
		try {
			GetProvidesAndUsesPortsOfComponent getPorts = new GetProvidesAndUsesPortsOfComponent();
			node.apply( getPorts );
			String templateMakefileName = "makefile-cxx-uses-port.template";
			String templateCMakefileName = "cmakefile-cxx-uses-port.template";
			String portTypePath = getPorts.getUsesPorts("", "/");

			TemplateFile templateMakefile = new TemplateFile( _templateFilesOfCxxMakefile.peek(), templateMakefileName );
			templateMakefile.addMapping("__USES_PORT_PATH__",portTypePath);
			templateMakefile.open();
			templateMakefile.close();
			TemplateFile templateCMakefile = new TemplateFile( _templateFilesOfCxxCMakefile.peek(), templateCMakefileName );
			templateCMakefile.addMapping("__USES_PORT_PATH__",portTypePath);
			templateCMakefile.open();
			templateCMakefile.close();
		}catch (ASCoDTException  e ) {
			ErrorWriterDevice.getInstance().showError(getClass().getName(), "inAInterfacePackageElement(...)", e);
		}
	}
}
