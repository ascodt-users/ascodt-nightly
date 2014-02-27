package de.tum.ascodt.sidlcompiler.backend;

import java.net.URL;
import java.util.Stack;

import org.eclipse.core.runtime.Assert;

import de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice;
import de.tum.ascodt.sidlcompiler.frontend.node.AClassPackageElement;
import de.tum.ascodt.sidlcompiler.frontend.node.AUses;
import de.tum.ascodt.sidlcompiler.symboltable.SymbolTable;
import de.tum.ascodt.utils.TemplateFile;
import de.tum.ascodt.utils.exceptions.ASCoDTException;

/**
 * A class which generates global build scripts 
 * for all components in a given symbol table
 * @author Atanas Atanasov
 *
 */
public class CreateGlobalBuildScripts extends de.tum.ascodt.sidlcompiler.frontend.analysis.DepthFirstAdapter{
  /**
   * the project symbol table
   */
  private SymbolTable  _symbolTable;

  /**
   * output stack for a global cmake file
   */
  private Stack<TemplateFile> _templateFilesOfGlobalCMakeFile;

  
  public CreateGlobalBuildScripts(SymbolTable symbolTable){
    _symbolTable = symbolTable;
    _templateFilesOfGlobalCMakeFile  = new java.util.Stack< TemplateFile >();
  }

  public void create(
      URL generatedFilesDestinationDirectory,
      URL userImplementedFilesDestinationDirectory,
      URL nativeDestinationDirectory) throws ASCoDTException{
    openOutputStreams(
        generatedFilesDestinationDirectory,
        userImplementedFilesDestinationDirectory,
        nativeDestinationDirectory);
    for ( 
        de.tum.ascodt.sidlcompiler.frontend.node.AClassPackageElement component:
          _symbolTable.getGlobalScope().getFlattenedClassElements()
        ) {
      component.apply(this);
    }
    closeOutputStreams();
  }

  /**
   * Open outputstreams by using the correct templates 
   * @param generatedFilesDestinationDirectory
   * @param userImplementedFilesDestinationDirectory
   * @param nativeDestinationDirectory
   * @throws ASCoDTException 
   */
  private void openOutputStreams(
      URL generatedFilesDestinationDirectory,
      URL userImplementedFilesDestinationDirectory,
      URL nativeDestinationDirectory) throws ASCoDTException {

    // TODO define template file location and destination
    
//    String templateFileForGlobalCmake = "";
//    String destinationFileForGlobalCmake = "";
//    _templateFilesOfGlobalCMakeFile.push(
//        new TemplateFile( 
//            templateFileForGlobalCmake,
//            destinationFileForGlobalCmake,
//            null,
//            TemplateFile.getLanguageConfigurationForCPP(),true)
//        );
//    addTemplateMappings();
//    _templateFilesOfGlobalCMakeFile.peek().open();
  }

  /**
   * initializes all template mappings 
   */
  private void addTemplateMappings() {
    // TODO add mappings/string for replacement
    
  }

  private void closeOutputStreams() {
//    Assert.isTrue( _templateFilesOfGlobalCMakeFile.size()==1 );
//    try {
//      _templateFilesOfGlobalCMakeFile.peek().close();
//       
//    }
//    catch (ASCoDTException  e ) {
//        ErrorWriterDevice.getInstance().showError(getClass().getName(), "closeOutputStreams(...)", e);
//    }
//    _templateFilesOfGlobalCMakeFile.pop();
  }

  /**
   * This method is invoked for every component in the symbol table
   */
  public void inAClassPackageElement(AClassPackageElement node) {

  }
  
  /**
   * Leaving the definition scope of a given component
   */
  public void outAClassPackageElement(AClassPackageElement node) {
    
  }
  /**
   * For each uses relation, we have to generate all the connection 
   * operations.
   */
  public void inAUses(AUses node) {

  }
}
