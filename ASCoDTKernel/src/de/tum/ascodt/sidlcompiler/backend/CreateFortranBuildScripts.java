package de.tum.ascodt.sidlcompiler.backend;


import java.io.File;
import java.net.URL;
import java.util.Stack;

import org.eclipse.core.runtime.Assert;

import de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice;
import de.tum.ascodt.repository.Target;
import de.tum.ascodt.sidlcompiler.astproperties.GetProvidesAndUsesPortsOfComponent;
import de.tum.ascodt.sidlcompiler.frontend.analysis.DepthFirstAdapter;
import de.tum.ascodt.sidlcompiler.frontend.node.AClassPackageElement;
import de.tum.ascodt.sidlcompiler.frontend.node.AUses;
import de.tum.ascodt.sidlcompiler.symboltable.SymbolTable;
import de.tum.ascodt.utils.TemplateFile;
import de.tum.ascodt.utils.exceptions.ASCoDTException;


/**
 * Compiler Adapter for generating fortran makefiles
 * 
 * @author Atanas Atanasov
 * 
 */
public class CreateFortranBuildScripts extends DepthFirstAdapter {
  private Stack<TemplateFile> _templateFilesOfFortranMakefile;
  private Stack<TemplateFile> _templateFilesOfFortranCMakefile;

  private Stack<TemplateFile> _templateFilesOfSourcesFortranCMakefile;
  private Stack<TemplateFile> _templateFilesOfTargetsFortranCMakefile;
  private URL _userImplementationsDestinationDirectory;
  private URL _generatedFilesDirectory;

  private String[] _namespace;
  private SymbolTable _symbolTable;
  private Target _target;

  CreateFortranBuildScripts(Target target, SymbolTable symbolTable,
      URL userImplementationsDestinationDirectory, URL generatedFilesDirectory,
      URL nativeDirectory, String[] namespace) {
    _templateFilesOfFortranMakefile = new Stack<TemplateFile>();
    _templateFilesOfFortranCMakefile = new Stack<TemplateFile>();
    _templateFilesOfSourcesFortranCMakefile = new Stack<TemplateFile>();
    _templateFilesOfTargetsFortranCMakefile = new Stack<TemplateFile>();
    _userImplementationsDestinationDirectory = userImplementationsDestinationDirectory;
    _generatedFilesDirectory = generatedFilesDirectory;
    _namespace = namespace;
    _symbolTable = symbolTable;
    _target = target;
  }

  private void createComponentMappings(String componentName,
      String fullQualifiedName, Stack<TemplateFile> template) {
    template.peek().addMapping("__COMPONENT_NAME__", componentName);
    template.peek().addMapping("__PATH_FULL_QUALIFIED_NAME__",
        fullQualifiedName.replaceAll("[.]", "/"));
    template.peek().addMapping("__GENERATED_OUTPUT__",
        _generatedFilesDirectory.getPath().toString());
    template.peek().addMapping("__SRC_OUTPUT__",
        _userImplementationsDestinationDirectory.getPath().toString());
  }

  @Override
  public void inAClassPackageElement(AClassPackageElement node) {
    try {
      String componentName = node.getName().getText();
      String fullQualifiedName = _symbolTable.getScope(node)
          .getFullyQualifiedName(componentName);

      String templateFileForFortranMakefile = "makefile-fortran.template";
      String destinationFileForFortranMakefile = _userImplementationsDestinationDirectory
          .toString() + File.separatorChar + "Makefile." + componentName;
      String templateFileForFortranCMakefile = "cmakefile-fortran.template";
      String destinationFileForFortranCMakefile = _userImplementationsDestinationDirectory
          .toString() +
          File.separatorChar +
          "cmake-" +
          fullQualifiedName +
          File.separatorChar + "CMakeLists.txt";
      String templateFileForSourcesCmakefile = "";
      String templateFileForTargetsCmakefile = "";
      switch (_target.getType()) {
      case FortranNative:
        templateFileForSourcesCmakefile = "cmakefile-sources-native-fortran.template";
        templateFileForTargetsCmakefile = "cmakefile-targets-native-fortran.template";

        break;
      case ReverseFortranRemoteSocket:
        templateFileForSourcesCmakefile = "cmakefile-sources-remote-fortran.template";
        templateFileForTargetsCmakefile = "cmakefile-targets-remote-fortran.template";

        break;
      default:
        break;
      }
      String destinationFileForSourcesFortranCMakefile = _userImplementationsDestinationDirectory
          .toString() +
          File.separatorChar +
          "cmake-" +
          fullQualifiedName +
          File.separatorChar + "sources.cmake";
      String destinationFileForTargetsFortranCMakefile = _userImplementationsDestinationDirectory
          .toString() +
          File.separatorChar +
          "cmake-" +
          fullQualifiedName +
          File.separatorChar + "targets.cmake";

      _templateFilesOfFortranMakefile.push(new TemplateFile(
          templateFileForFortranMakefile, destinationFileForFortranMakefile,
          _namespace, TemplateFile.getLanguageConfigurationForCPP(), true));
      _templateFilesOfFortranCMakefile.push(new TemplateFile(
          templateFileForFortranCMakefile, destinationFileForFortranCMakefile,
          _namespace, TemplateFile.getLanguageConfigurationForCPP(), false));
      _templateFilesOfSourcesFortranCMakefile.push(new TemplateFile(
          templateFileForSourcesCmakefile,
          destinationFileForSourcesFortranCMakefile, _namespace, TemplateFile
              .getLanguageConfigurationForCPP(), true));
      _templateFilesOfTargetsFortranCMakefile.push(new TemplateFile(
          templateFileForTargetsCmakefile,
          destinationFileForTargetsFortranCMakefile, _namespace, TemplateFile
              .getLanguageConfigurationForCPP(), false));
      createComponentMappings(componentName, fullQualifiedName,
          _templateFilesOfFortranMakefile);
      createComponentMappings(componentName, fullQualifiedName,
          _templateFilesOfFortranCMakefile);
      createComponentMappings(componentName, fullQualifiedName,
          _templateFilesOfSourcesFortranCMakefile);

      createComponentMappings(componentName, fullQualifiedName,
          _templateFilesOfTargetsFortranCMakefile);
      _templateFilesOfFortranMakefile.peek().addMapping("__TAB__", "\t");
      _templateFilesOfFortranMakefile.peek().open();
      _templateFilesOfFortranCMakefile.peek().open();
      _templateFilesOfSourcesFortranCMakefile.peek().open();
      _templateFilesOfTargetsFortranCMakefile.peek().open();
    } catch (ASCoDTException e) {
      ErrorWriterDevice.getInstance().println(e);
    }
  }

  /**
   * For each uses relation, we have to generate all the connection
   * operations.
   */
  @Override
  public void inAUses(AUses node) {
    try {
      GetProvidesAndUsesPortsOfComponent getPorts = new GetProvidesAndUsesPortsOfComponent();
      node.apply(getPorts);
      String templateMakefileName = "makefile-fortran-uses-port.template";
      String templateCMakefileName = "cmakefile-fortran-uses-port.template";
      String portTypePath = getPorts.getUsesPorts("", "/");

      TemplateFile templateMakefile = new TemplateFile(
          _templateFilesOfFortranMakefile.peek(), templateMakefileName);
      templateMakefile.addMapping("__USES_PORT_PATH__", portTypePath);
      templateMakefile.open();
      templateMakefile.close();
      TemplateFile templateCMakefile = new TemplateFile(
          _templateFilesOfSourcesFortranCMakefile.peek(), templateCMakefileName);
      templateCMakefile.addMapping("__USES_PORT_PATH__", portTypePath);
      templateCMakefile.open();
      templateCMakefile.close();
    } catch (ASCoDTException e) {
      ErrorWriterDevice.getInstance().println(e);
    }
  }

  /**
   * Close the output streams.
   */
  @Override
  public void outAClassPackageElement(AClassPackageElement node) {
    Assert.isTrue(_templateFilesOfFortranMakefile.size() == 1);
    Assert.isTrue(_templateFilesOfFortranCMakefile.size() == 1);
    Assert.isTrue(_templateFilesOfSourcesFortranCMakefile.size() == 1);

    Assert.isTrue(_templateFilesOfTargetsFortranCMakefile.size() == 1);

    try {
      _templateFilesOfFortranMakefile.peek().close();
      _templateFilesOfFortranCMakefile.peek().close();
      _templateFilesOfSourcesFortranCMakefile.peek().close();
      _templateFilesOfTargetsFortranCMakefile.peek().close();
    } catch (ASCoDTException e) {
      ErrorWriterDevice.getInstance().println(e);
    }

    _templateFilesOfFortranMakefile.pop();
    _templateFilesOfFortranCMakefile.pop();
    _templateFilesOfSourcesFortranCMakefile.pop();
    _templateFilesOfTargetsFortranCMakefile.pop();
  }
}
