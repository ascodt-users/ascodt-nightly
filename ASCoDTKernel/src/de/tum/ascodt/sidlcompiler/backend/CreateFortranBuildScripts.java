package de.tum.ascodt.sidlcompiler.backend;


import java.nio.file.Path;
import java.nio.file.Paths;
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
  private Path _cmakeDirectoryPath;

  private String[] _namespace;
  private SymbolTable _symbolTable;
  private Target _target;

  CreateFortranBuildScripts(Target target,
                            SymbolTable symbolTable,
                            Path projectDirectoryPath,
                            String[] namespace) {

    _templateFilesOfFortranMakefile = new Stack<TemplateFile>();
    _templateFilesOfFortranCMakefile = new Stack<TemplateFile>();
    _templateFilesOfSourcesFortranCMakefile = new Stack<TemplateFile>();
    _templateFilesOfTargetsFortranCMakefile = new Stack<TemplateFile>();
    _cmakeDirectoryPath = projectDirectoryPath.resolve("cmake");
    _namespace = namespace;
    _symbolTable = symbolTable;
    _target = target;
  }

  private void createComponentMappings(String componentName,
                                       String fullQualifiedName,
                                       Stack<TemplateFile> template) {
    template.peek().addMapping("__COMPONENT_NAME__", componentName);
    template.peek().addMapping("__PATH_FULL_QUALIFIED_NAME__",
                               fullQualifiedName.replaceAll("[.]", "/"));
  }

  @Override
  public void inAClassPackageElement(AClassPackageElement node) {
    String componentName = node.getName().getText();
    String fullyQualifiedComponentName =
        _symbolTable.getScope(node).getFullyQualifiedName(componentName);

    Path sourcesCMakeSourceFilePath = null;
    Path targetsCMakeSourceFilePath = null;

    switch (_target.getType()) {
    case FortranNative:
      sourcesCMakeSourceFilePath =
          Paths.get("cmakefile-sources-native-fortran.template");
      targetsCMakeSourceFilePath =
          Paths.get("cmakefile-targets-native-fortran.template");

      break;
    case FortranRemoteSocket:
      sourcesCMakeSourceFilePath =
          Paths.get("cmakefile-sources-remote-fortran.template");
      targetsCMakeSourceFilePath =
          Paths.get("cmakefile-targets-remote-fortran.template");

      break;
    default:
      break;
    }

    _templateFilesOfFortranMakefile.push(new TemplateFile(Paths.get("makefile-fortran.template"),
                                                          _cmakeDirectoryPath.resolve(fullyQualifiedComponentName)
                                                                             .resolve("Makefile." + componentName),
                                                          _namespace,
                                                          TemplateFile.getLanguageConfigurationForCPP(),
                                                          true));
    _templateFilesOfFortranCMakefile.push(new TemplateFile(Paths.get("cmakefile-fortran.template"),
                                                           _cmakeDirectoryPath.resolve(fullyQualifiedComponentName)
                                                                              .resolve("CMakeLists.txt"),
                                                           _namespace,
                                                           TemplateFile.getLanguageConfigurationForCPP(),
                                                           true));
    _templateFilesOfSourcesFortranCMakefile.push(new TemplateFile(sourcesCMakeSourceFilePath,
                                                                  _cmakeDirectoryPath.resolve(fullyQualifiedComponentName)
                                                                                     .resolve("sources.cmake"),
                                                                  _namespace,
                                                                  TemplateFile.getLanguageConfigurationForCPP(),
                                                                  true));
    _templateFilesOfTargetsFortranCMakefile.push(new TemplateFile(targetsCMakeSourceFilePath,
                                                                  _cmakeDirectoryPath.resolve(fullyQualifiedComponentName)
                                                                                     .resolve("targets.cmake"),
                                                                  _namespace,
                                                                  TemplateFile.getLanguageConfigurationForCPP(),
                                                                  false));
    createComponentMappings(componentName,
                            fullyQualifiedComponentName,
                            _templateFilesOfFortranMakefile);
    createComponentMappings(componentName,
                            fullyQualifiedComponentName,
                            _templateFilesOfFortranCMakefile);
    createComponentMappings(componentName,
                            fullyQualifiedComponentName,
                            _templateFilesOfSourcesFortranCMakefile);

    createComponentMappings(componentName,
                            fullyQualifiedComponentName,
                            _templateFilesOfTargetsFortranCMakefile);
    _templateFilesOfFortranMakefile.peek().addMapping("__TAB__", "\t");
    _templateFilesOfFortranMakefile.peek().open();
    _templateFilesOfFortranCMakefile.peek().open();
    _templateFilesOfSourcesFortranCMakefile.peek().open();
    _templateFilesOfTargetsFortranCMakefile.peek().open();
  }

  /**
   * For each uses relation, we have to generate all the connection
   * operations.
   */
  @Override
  public void inAUses(AUses node) {
    try {
      GetProvidesAndUsesPortsOfComponent getPorts =
          new GetProvidesAndUsesPortsOfComponent();
      node.apply(getPorts);

      String portTypePath = getPorts.getUsesPorts("", "/");

      TemplateFile templateMakefile =
          new TemplateFile(_templateFilesOfFortranMakefile.peek(),
                           Paths.get("makefile-fortran-uses-port.template"));
      templateMakefile.addMapping("__USES_PORT_PATH__", portTypePath);
      templateMakefile.open();
      templateMakefile.close();
      TemplateFile templateCMakefile =
          new TemplateFile(_templateFilesOfSourcesFortranCMakefile.peek(),
                           Paths.get("cmakefile-fortran-uses-port.template"));
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

    _templateFilesOfFortranMakefile.peek().close();
    _templateFilesOfFortranCMakefile.peek().close();
    _templateFilesOfSourcesFortranCMakefile.peek().close();
    _templateFilesOfTargetsFortranCMakefile.peek().close();
    _templateFilesOfFortranMakefile.pop();
    _templateFilesOfFortranCMakefile.pop();
    _templateFilesOfSourcesFortranCMakefile.pop();
    _templateFilesOfTargetsFortranCMakefile.pop();
  }
}
