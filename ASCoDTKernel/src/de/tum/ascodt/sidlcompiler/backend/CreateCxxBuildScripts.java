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
 * Compiler Adapter for generating c++ makefiles
 * 
 * @author Atanas Atanasov
 * 
 */
public class CreateCxxBuildScripts extends DepthFirstAdapter {
  private Stack<TemplateFile> _templateFilesOfCxxMakefile;
  private Stack<TemplateFile> _templateFilesOfCxxCMakefile;
  private Stack<TemplateFile> _templateFilesOfSourcesCxxCMakefile;
  private Stack<TemplateFile> _templateFilesOfTargetsCxxCMakefile;
  private Path _cmakeDirectoryPath;

  private String[] _namespace;
  private SymbolTable _symbolTable;
  private Target _target;

  CreateCxxBuildScripts(Target target,
                        SymbolTable symbolTable,
                        Path projectDirectoryPath,
                        String[] namespace) {
    _templateFilesOfCxxMakefile = new Stack<TemplateFile>();
    _templateFilesOfCxxCMakefile = new Stack<TemplateFile>();
    _templateFilesOfSourcesCxxCMakefile = new Stack<TemplateFile>();
    _templateFilesOfTargetsCxxCMakefile = new Stack<TemplateFile>();
    _cmakeDirectoryPath = projectDirectoryPath.resolve("cmake");
    _namespace = namespace;
    _symbolTable = symbolTable;
    _target = target;
  }

  private void createComponentMappings(String componentName,
                                       String fullyQualifiedComponentName,
                                       Stack<TemplateFile> template) {
    template.peek().addMapping("__COMPONENT_NAME__", componentName);
    template.peek().addMapping("__FULLY_QUALIFIED_COMPONENT_NAME__",
                               fullyQualifiedComponentName);
    template.peek().addMapping("__FULLY_QUALIFIED_COMPONENT_PATH__",
                               fullyQualifiedComponentName.replaceAll("[.]",
                                                                      "/"));
  }

  @Override
  public void inAClassPackageElement(AClassPackageElement node) {
    String componentName = node.getName().getText();
    String fullyQualifiedComponentName =
        _symbolTable.getScope(node).getFullyQualifiedName(componentName);

    Path sourcesCMakeSourceFilePath = null;
    Path targetsCMakeSourceFilePath = null;

    switch (_target.getType()) {
    case JavaNative:
      sourcesCMakeSourceFilePath =
          Paths.get("cmakefile-sources-native-cxx.template");
      targetsCMakeSourceFilePath =
          Paths.get("cmakefile-targets-native-cxx.template");

      break;

    case CxxRemoteSocket:
      sourcesCMakeSourceFilePath =
          Paths.get("cmakefile-sources-remote-cxx.template");
      targetsCMakeSourceFilePath =
          Paths.get("cmakefile-targets-remote-cxx.template");

      break;

    default:
      break;
    }

    _templateFilesOfCxxMakefile.push(new TemplateFile(Paths.get("makefile-cxx.template"),
                                                      _cmakeDirectoryPath.resolve(fullyQualifiedComponentName)
                                                                         .resolve("Makefile." + componentName),
                                                      _namespace,
                                                      TemplateFile.getLanguageConfigurationForCPP(),
                                                      true));
    _templateFilesOfCxxCMakefile.push(new TemplateFile(Paths.get("cmakefile-cxx.template"),
                                                       _cmakeDirectoryPath.resolve(fullyQualifiedComponentName)
                                                                          .resolve("CMakeLists.txt"),
                                                       _namespace,
                                                       TemplateFile.getLanguageConfigurationForCPP(),
                                                       false));
    _templateFilesOfSourcesCxxCMakefile.push(new TemplateFile(sourcesCMakeSourceFilePath,
                                                              _cmakeDirectoryPath.resolve(fullyQualifiedComponentName)
                                                                                 .resolve("sources.cmake"),
                                                              _namespace,
                                                              TemplateFile.getLanguageConfigurationForCPP(),
                                                              true));
    _templateFilesOfTargetsCxxCMakefile.push(new TemplateFile(targetsCMakeSourceFilePath,
                                                              _cmakeDirectoryPath.resolve(fullyQualifiedComponentName)
                                                                                 .resolve("targets.cmake"),
                                                              _namespace,
                                                              TemplateFile.getLanguageConfigurationForCPP(),
                                                              true));
    createComponentMappings(componentName,
                            fullyQualifiedComponentName,
                            _templateFilesOfCxxMakefile);
    createComponentMappings(componentName,
                            fullyQualifiedComponentName,
                            _templateFilesOfCxxCMakefile);
    createComponentMappings(componentName,
                            fullyQualifiedComponentName,
                            _templateFilesOfSourcesCxxCMakefile);
    createComponentMappings(componentName,
                            fullyQualifiedComponentName,
                            _templateFilesOfTargetsCxxCMakefile);
    _templateFilesOfCxxMakefile.peek().addMapping("__TAB__", "\t");
    _templateFilesOfCxxMakefile.peek().open();
    _templateFilesOfCxxCMakefile.peek().open();
    _templateFilesOfSourcesCxxCMakefile.peek().open();

    _templateFilesOfTargetsCxxCMakefile.peek().open();
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
          new TemplateFile(_templateFilesOfCxxMakefile.peek(),
                           Paths.get("makefile-cxx-uses-port.template"));
      templateMakefile.addMapping("__USES_PORT_PATH__", portTypePath);
      templateMakefile.open();
      templateMakefile.close();
      TemplateFile templateCMakefile =
          new TemplateFile(_templateFilesOfSourcesCxxCMakefile.peek(),
                           Paths.get("cmakefile-cxx-uses-port.template"));
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
    Assert.isTrue(_templateFilesOfCxxMakefile.size() == 1);
    Assert.isTrue(_templateFilesOfCxxCMakefile.size() == 1);

    Assert.isTrue(_templateFilesOfSourcesCxxCMakefile.size() == 1);
    Assert.isTrue(_templateFilesOfTargetsCxxCMakefile.size() == 1);

    _templateFilesOfCxxMakefile.peek().close();
    _templateFilesOfCxxCMakefile.peek().close();

    _templateFilesOfSourcesCxxCMakefile.peek().close();
    _templateFilesOfTargetsCxxCMakefile.peek().close();

    _templateFilesOfCxxMakefile.pop();
    _templateFilesOfCxxCMakefile.pop();

    _templateFilesOfSourcesCxxCMakefile.pop();
    _templateFilesOfTargetsCxxCMakefile.pop();
  }
}
