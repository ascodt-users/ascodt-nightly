package de.tum.ascodt.sidlcompiler.backend;


import java.io.File;
import java.net.MalformedURLException;
import java.net.URISyntaxException;
import java.net.URL;
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
public class CreateCxxBuildScripts extends DepthFirstAdapter {
  private Stack<TemplateFile> _templateFilesOfCxxMakefile;
  private Stack<TemplateFile> _templateFilesOfCxxCMakefile;
  private Stack<TemplateFile> _templateFilesOfSourcesCxxCMakefile;
  private Stack<TemplateFile> _templateFilesOfTargetsCxxCMakefile;
  private URL _cmakeDirectory;
  private URL _generatedFilesDirectory;

  private String[] _namespace;
  private SymbolTable _symbolTable;
  private Target _target;

  CreateCxxBuildScripts(Target target, SymbolTable symbolTable,
      URL userImplementationsDestinationDirectory, URL generatedFilesDirectory,
      URL nativeDirectory, String[] namespace) {
    _templateFilesOfCxxMakefile = new Stack<TemplateFile>();
    _templateFilesOfCxxCMakefile = new Stack<TemplateFile>();
    _templateFilesOfSourcesCxxCMakefile = new Stack<TemplateFile>();
    _templateFilesOfTargetsCxxCMakefile = new Stack<TemplateFile>();

    try {
      _cmakeDirectory = Paths
          .get(userImplementationsDestinationDirectory.toURI()).getParent()
          .resolve("cmake").toUri().toURL();
    } catch (MalformedURLException e) {
      e.printStackTrace();
    } catch (URISyntaxException e) {
      e.printStackTrace();
    }

    _generatedFilesDirectory = generatedFilesDirectory;
    _namespace = namespace;
    _symbolTable = symbolTable;
    _target = target;
  }

  private void createComponentMappings(String componentName,
      String fullyQualifiedComponentName, Stack<TemplateFile> template) {
    template.peek().addMapping("__COMPONENT_NAME__", componentName);
    template.peek().addMapping("__FULLY_QUALIFIED_COMPONENT_NAME__",
        fullyQualifiedComponentName);
    template.peek().addMapping("__FULLY_QUALIFIED_COMPONENT_PATH__",
        fullyQualifiedComponentName.replaceAll("[.]", "/"));
    template.peek().addMapping("__GENERATED_OUTPUT__",
        _generatedFilesDirectory.getPath().toString());
    template.peek().addMapping("__SRC_OUTPUT__",
        _cmakeDirectory.getPath().toString());
  }

  @Override
  public void inAClassPackageElement(AClassPackageElement node) {
    try {
      String componentName = node.getName().getText();
      String fullyQualifiedComponentName = _symbolTable.getScope(node)
          .getFullyQualifiedName(componentName);

      String templateFileForCxxMakefile = "makefile-cxx.template";
      String destinationFileForCxxMakefile = _cmakeDirectory.toString() +
          File.separatorChar + "Makefile." + componentName;

      String templateFileForCxxCMakefile = "cmakefile-cxx.template";
      String templateFileForSourcesCmakefile = "";
      String templateFileForTargetsCmakefile = "";
      switch (_target.getType()) {
      case JavaNative:
        templateFileForSourcesCmakefile = "cmakefile-sources-native-cxx.template";
        templateFileForTargetsCmakefile = "cmakefile-targets-native-cxx.template";

        break;

      case ReverseCxxRemoteSocket:
        templateFileForSourcesCmakefile = "cmakefile-sources-remote-cxx.template";
        templateFileForTargetsCmakefile = "cmakefile-targets-remote-cxx.template";

        break;

      default:
        break;
      }
      String destinationFileForCxxCMakefile = _cmakeDirectory.toString() +
          File.separatorChar + fullyQualifiedComponentName +
          File.separatorChar + "CMakeLists.txt";
      String destinationFileForSourcesCxxCMakefile = _cmakeDirectory.toString() +
          File.separatorChar +
          fullyQualifiedComponentName +
          File.separatorChar + "sources.cmake";
      String destinationFileForTargetsCxxCMakefile = _cmakeDirectory.toString() +
          File.separatorChar +
          fullyQualifiedComponentName +
          File.separatorChar + "targets.cmake";

      _templateFilesOfCxxMakefile.push(new TemplateFile(
          templateFileForCxxMakefile, destinationFileForCxxMakefile,
          _namespace, TemplateFile.getLanguageConfigurationForCPP(), true));
      _templateFilesOfCxxCMakefile.push(new TemplateFile(
          templateFileForCxxCMakefile, destinationFileForCxxCMakefile,
          _namespace, TemplateFile.getLanguageConfigurationForCPP(), false));
      _templateFilesOfSourcesCxxCMakefile.push(new TemplateFile(
          templateFileForSourcesCmakefile,
          destinationFileForSourcesCxxCMakefile, _namespace, TemplateFile
              .getLanguageConfigurationForCPP(), true));
      _templateFilesOfTargetsCxxCMakefile.push(new TemplateFile(
          templateFileForTargetsCmakefile,
          destinationFileForTargetsCxxCMakefile, _namespace, TemplateFile
              .getLanguageConfigurationForCPP(), false));
      createComponentMappings(componentName, fullyQualifiedComponentName,
          _templateFilesOfCxxMakefile);
      createComponentMappings(componentName, fullyQualifiedComponentName,
          _templateFilesOfCxxCMakefile);
      createComponentMappings(componentName, fullyQualifiedComponentName,
          _templateFilesOfSourcesCxxCMakefile);

      createComponentMappings(componentName, fullyQualifiedComponentName,
          _templateFilesOfTargetsCxxCMakefile);
      _templateFilesOfCxxMakefile.peek().addMapping("__TAB__", "\t");
      _templateFilesOfCxxMakefile.peek().open();
      _templateFilesOfCxxCMakefile.peek().open();
      _templateFilesOfSourcesCxxCMakefile.peek().open();

      _templateFilesOfTargetsCxxCMakefile.peek().open();
    } catch (ASCoDTException e) {
      ErrorWriterDevice.getInstance().showError(getClass().getName(),
          "inAInterfacePackageElement(...)", e);
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
      String templateMakefileName = "makefile-cxx-uses-port.template";
      String templateCMakefileName = "cmakefile-cxx-uses-port.template";
      String portTypePath = getPorts.getUsesPorts("", "/");

      TemplateFile templateMakefile = new TemplateFile(
          _templateFilesOfCxxMakefile.peek(), templateMakefileName);
      templateMakefile.addMapping("__USES_PORT_PATH__", portTypePath);
      templateMakefile.open();
      templateMakefile.close();
      TemplateFile templateCMakefile = new TemplateFile(
          _templateFilesOfSourcesCxxCMakefile.peek(), templateCMakefileName);
      templateCMakefile.addMapping("__USES_PORT_PATH__", portTypePath);
      templateCMakefile.open();
      templateCMakefile.close();
    } catch (ASCoDTException e) {
      ErrorWriterDevice.getInstance().showError(getClass().getName(),
          "inAInterfacePackageElement(...)", e);
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

    try {
      _templateFilesOfCxxMakefile.peek().close();
      _templateFilesOfCxxCMakefile.peek().close();
      _templateFilesOfSourcesCxxCMakefile.peek().close();

      _templateFilesOfTargetsCxxCMakefile.peek().close();
    } catch (ASCoDTException e) {
      ErrorWriterDevice.getInstance().showError(getClass().getName(),
          "inAInterfacePackageElement(...)", e);
    }

    _templateFilesOfCxxMakefile.pop();
    _templateFilesOfCxxCMakefile.pop();
    _templateFilesOfSourcesCxxCMakefile.pop();

    _templateFilesOfTargetsCxxCMakefile.pop();
  }
}
