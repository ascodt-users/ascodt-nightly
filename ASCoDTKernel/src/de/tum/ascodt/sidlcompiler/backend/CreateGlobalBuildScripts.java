package de.tum.ascodt.sidlcompiler.backend;


import java.io.File;
import java.net.MalformedURLException;
import java.net.URISyntaxException;
import java.net.URL;
import java.nio.file.Paths;
import java.util.LinkedList;
import java.util.List;
import java.util.Stack;

import org.eclipse.core.runtime.Assert;

import de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice;
import de.tum.ascodt.sidlcompiler.frontend.analysis.DepthFirstAdapter;
import de.tum.ascodt.sidlcompiler.frontend.node.AClassPackageElement;
import de.tum.ascodt.sidlcompiler.frontend.node.AUses;
import de.tum.ascodt.sidlcompiler.symboltable.SymbolTable;
import de.tum.ascodt.utils.TemplateFile;
import de.tum.ascodt.utils.exceptions.ASCoDTException;


/**
 * A class which generates global build scripts
 * for all components in a given symbol table
 * 
 * @author Atanas Atanasov
 * 
 */
public class CreateGlobalBuildScripts extends DepthFirstAdapter {
  /**
   * the project symbol table
   */
  private SymbolTable _symbolTable;
  private List<String> _fullyQualifiedComponentNames;

  /**
   * output stack for a global cmake file
   */
  private Stack<TemplateFile> _templateFilesOfGlobalCMakeFile;

  public CreateGlobalBuildScripts(SymbolTable symbolTable) {
    _symbolTable = symbolTable;
    _templateFilesOfGlobalCMakeFile = new Stack<TemplateFile>();
    _fullyQualifiedComponentNames = new LinkedList<String>();
  }

  private void closeOutputStreams() throws ASCoDTException {
    StringBuilder sb = new StringBuilder();

    for (String fullQualifiedName : _fullyQualifiedComponentNames) {
      sb.append("\n");
      sb.append("add_subdirectory");
      sb.append("(");
      sb.append("cmake");
      sb.append("/");
      sb.append(fullQualifiedName);
      sb.append(")");
    }

    if (sb.length() > 0) {
      sb.deleteCharAt(0);
    }

    String subdirectories = sb.toString();

    _templateFilesOfGlobalCMakeFile.peek().addMapping("__SUBDIRECTORIES__",
        subdirectories);
    _templateFilesOfGlobalCMakeFile.peek().open();

    Assert.isTrue(_templateFilesOfGlobalCMakeFile.size() == 1);
    try {
      _templateFilesOfGlobalCMakeFile.peek().close();
    } catch (ASCoDTException e) {
      ErrorWriterDevice.getInstance().println(e);
    }

    _templateFilesOfGlobalCMakeFile.pop();
  }

  public void create(URL generatedFilesDestinationDirectory,
      URL userImplementedFilesDestinationDirectory,
      URL nativeDestinationDirectory) throws ASCoDTException {
    URL projectDirectory = null;
    try {
      projectDirectory = Paths
          .get(userImplementedFilesDestinationDirectory.toURI()).getParent()
          .toUri().toURL();
    } catch (MalformedURLException e) {
      ErrorWriterDevice.getInstance().println(e);
    } catch (URISyntaxException e) {
      ErrorWriterDevice.getInstance().println(e);
    }

    openOutputStreams(generatedFilesDestinationDirectory, projectDirectory,
        nativeDestinationDirectory);
    for (AClassPackageElement component : _symbolTable.getGlobalScope()
        .getFlattenedClassElements()) {
      component.apply(this);
    }
    closeOutputStreams();
  }

  /**
   * This method is invoked for every component in the symbol table
   */
  @Override
  public void inAClassPackageElement(AClassPackageElement node) {
    String componentName = node.getName().getText();
    String fullyQualifiedComponentName = _symbolTable.getScope(node)
        .getFullyQualifiedName(componentName);
    _fullyQualifiedComponentNames.add(fullyQualifiedComponentName);
  }

  /**
   * For each uses relation, we have to generate all the connection
   * operations.
   */
  @Override
  public void inAUses(AUses node) {}

  /**
   * Open output streams by using the correct templates
   * 
   * @param generatedFilesDestinationDirectory
   * @param projectDirectory
   * @param nativeDestinationDirectory
   * @throws ASCoDTException
   */
  private void openOutputStreams(URL generatedFilesDestinationDirectory,
      URL projectDirectory, URL nativeDestinationDirectory)
      throws ASCoDTException {
    _fullyQualifiedComponentNames.clear();

    String templateFileForGlobalCmake = "cmakefile-cxx-global.template";
    String destinationFileForGlobalCmake = projectDirectory.toString() +
        File.separatorChar + "CMakeLists.txt";

    _templateFilesOfGlobalCMakeFile.push(new TemplateFile(
        templateFileForGlobalCmake, destinationFileForGlobalCmake, null,
        TemplateFile.getLanguageConfigurationForCPP(), true));
  }

  /**
   * Leaving the definition scope of a given component
   */
  @Override
  public void outAClassPackageElement(AClassPackageElement node) {}
}
