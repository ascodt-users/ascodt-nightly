package de.tum.ascodt.sidlcompiler.backend;


import java.io.File;
import java.net.URL;
import java.util.Stack;

import org.eclipse.core.runtime.Assert;

import de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice;
import de.tum.ascodt.plugin.utils.tracing.Trace;
import de.tum.ascodt.sidlcompiler.astproperties.ExclusivelyInParameters;
import de.tum.ascodt.sidlcompiler.astproperties.GetParameterList;
import de.tum.ascodt.sidlcompiler.astproperties.GetProvidesAndUsesPortsOfComponent;
import de.tum.ascodt.sidlcompiler.frontend.analysis.DepthFirstAdapter;
import de.tum.ascodt.sidlcompiler.frontend.node.AClassPackageElement;
import de.tum.ascodt.sidlcompiler.frontend.node.AInterfacePackageElement;
import de.tum.ascodt.sidlcompiler.frontend.node.AOperation;
import de.tum.ascodt.sidlcompiler.frontend.node.AUserDefinedType;
import de.tum.ascodt.sidlcompiler.frontend.node.AUses;
import de.tum.ascodt.sidlcompiler.frontend.node.PUserDefinedType;
import de.tum.ascodt.sidlcompiler.symboltable.Scope;
import de.tum.ascodt.sidlcompiler.symboltable.SymbolTable;
import de.tum.ascodt.utils.TemplateFile;
import de.tum.ascodt.utils.exceptions.ASCoDTException;


/**
 * This generator is used to create the cxx code for native components.
 * 
 * @author Atanas Atanasov
 * 
 */
public class CreateCxxComponent extends DepthFirstAdapter {
  private Trace _trace = new Trace(CreateCxxComponent.class.getCanonicalName());

  private Stack<TemplateFile> _templateFilesOfCXXHeader;
  private Stack<TemplateFile> _templateFilesOfCXXImplementation;
  private Stack<TemplateFile> _templateFilesOfAbstractCXXHeader;
  private Stack<TemplateFile> _templateFilesOfAbstractCXXImplementation;
  private Stack<TemplateFile> _templateFilesHeaderUsesPorts;
  private Stack<TemplateFile> _templateFilesHeaderProvidesPorts;
  private Stack<TemplateFile> _templateFilesImplementationUsesPorts;
  private Stack<TemplateFile> _templateFilesImplementationProvidesPorts;
  private URL _userImplementationsDestinationDirectory;
  private URL _generatedFilesDirectory;
  private String[] _namespace;

  private String _fullQualifiedName;
  private SymbolTable _symbolTable;
  private boolean _generateProvidesMethods;

  private String _usesPortsIncludes;

  private String _usesPortsVariables;
  private String _usesPortsInitialisation;

  private String _providePortsIncludes;

  private String _providePortsInterfaces;

  private String _delimiter;

  public CreateCxxComponent(SymbolTable symbolTable,
      URL userImplementationsDestinationDirectory, URL generatedFilesDirectory,
      String[] namespace) {
    _templateFilesOfCXXHeader = new Stack<TemplateFile>();
    _templateFilesOfCXXImplementation = new Stack<TemplateFile>();
    _templateFilesOfAbstractCXXHeader = new Stack<TemplateFile>();
    _templateFilesOfAbstractCXXImplementation = new Stack<TemplateFile>();
    _templateFilesHeaderUsesPorts = new Stack<TemplateFile>();
    _templateFilesHeaderProvidesPorts = new Stack<TemplateFile>();
    _templateFilesImplementationUsesPorts = new Stack<TemplateFile>();
    _templateFilesImplementationProvidesPorts = new Stack<TemplateFile>();
    _userImplementationsDestinationDirectory = userImplementationsDestinationDirectory;
    _generatedFilesDirectory = generatedFilesDirectory;
    _namespace = namespace;
    _symbolTable = symbolTable;
    _usesPortsIncludes = "";
    _usesPortsVariables = "";
    _usesPortsInitialisation = "";
    _providePortsIncludes = "";
    _providePortsInterfaces = "";
    _delimiter = "";
  }

  @Override
  public void inAClassPackageElement(AClassPackageElement node) {
    _trace.in("inAClassPackageElement(...)", "open new port interface");
    try {
      String componentName = node.getName().getText();
      _fullQualifiedName = _symbolTable.getScope(node).getFullyQualifiedName(
          componentName);

      String templateFileForCXXComponentHeader = "native-component-cxx-header.template";
      String templateFileForCXXComponentImplemention = "native-component-cxx-implementation.template";
      String templateFileForAbstractCXXComponentHeader = "native-component-abstract-cxx-header.template";
      String templateFileForAbstractCXXComponentImplementation = "native-component-abstract-cxx-implementation.template";
      String destinationFileForCXXHeader = _userImplementationsDestinationDirectory
          .toString() +
          File.separatorChar +
          _fullQualifiedName.replaceAll("[.]", "/") + "Implementation.h";
      String destinationFileForCXXImplementation = _userImplementationsDestinationDirectory
          .toString() +
          File.separatorChar +
          _fullQualifiedName.replaceAll("[.]", "/") + "Implementation.cpp";
      String destinationFileForAbstractCXXHeader = _generatedFilesDirectory
          .toString() +
          File.separatorChar +
          _fullQualifiedName.replaceAll("[.]", "/") +
          "AbstractImplementation.h";
      String destinationFileForAbstractCXXImplementation = _generatedFilesDirectory
          .toString() +
          File.separatorChar +
          _fullQualifiedName.replaceAll("[.]", "/") +
          "AbstractImplementation.cpp";

      _templateFilesOfCXXHeader.push(new TemplateFile(
          templateFileForCXXComponentHeader, destinationFileForCXXHeader,
          _namespace, TemplateFile.getLanguageConfigurationForCPP(), false));
      _templateFilesOfCXXImplementation.push(new TemplateFile(
          templateFileForCXXComponentImplemention,
          destinationFileForCXXImplementation, _namespace, TemplateFile
              .getLanguageConfigurationForCPP(), false));
      _templateFilesOfAbstractCXXHeader.push(new TemplateFile(
          templateFileForAbstractCXXComponentHeader,
          destinationFileForAbstractCXXHeader, _namespace, TemplateFile
              .getLanguageConfigurationForCPP(), true));
      _templateFilesOfAbstractCXXImplementation.push(new TemplateFile(
          templateFileForAbstractCXXComponentImplementation,
          destinationFileForAbstractCXXImplementation, _namespace, TemplateFile
              .getLanguageConfigurationForCPP(), true));

      _templateFilesOfCXXHeader.peek().addMapping("__COMPONENT_NAME__",
          componentName);
      _templateFilesOfAbstractCXXHeader.peek().addMapping("__COMPONENT_NAME__",
          componentName);
      _templateFilesOfCXXImplementation.peek().addMapping("__COMPONENT_NAME__",
          componentName);
      _templateFilesOfAbstractCXXImplementation.peek().addMapping(
          "__COMPONENT_NAME__", componentName);

      _templateFilesOfCXXHeader.peek().addMapping(
          "__INCLUDE_GUARD_FULL_QUALIFIED_NAME__",
          _fullQualifiedName.replaceAll("[.]", "_").toUpperCase());
      _templateFilesOfCXXHeader.peek().addMapping(
          "__CXX_FULL_QUALIFIED_NAME__",
          _fullQualifiedName.replaceAll("[.]", "::"));
      _templateFilesOfAbstractCXXHeader.peek().addMapping(
          "__INCLUDE_GUARD_FULL_QUALIFIED_NAME__",
          _fullQualifiedName.replaceAll("[.]", "_").toUpperCase());
      _templateFilesOfAbstractCXXHeader.peek().addMapping(
          "__CXX_FULL_QUALIFIED_NAME__",
          _fullQualifiedName.replaceAll("[.]", "::"));

      _templateFilesOfCXXImplementation.peek().addMapping(
          "__CXX_FULL_QUALIFIED_NAME__",
          _fullQualifiedName.replaceAll("[.]", "::"));
      _templateFilesOfCXXImplementation.peek().addMapping(
          "__PATH_FULL_QUALIFIED_NAME__",
          _fullQualifiedName.replaceAll("[.]", "/"));
      _templateFilesOfCXXImplementation.peek().addMapping("__SRC_OUTPUT__",
          _userImplementationsDestinationDirectory.getPath().toString());

      _templateFilesOfAbstractCXXImplementation.peek().addMapping(
          "__CXX_FULL_QUALIFIED_NAME__",
          _fullQualifiedName.replaceAll("[.]", "::"));
      _templateFilesOfAbstractCXXImplementation.peek().addMapping(
          "__PATH_FULL_QUALIFIED_NAME__",
          _fullQualifiedName.replaceAll("[.]", "/"));
      _templateFilesOfAbstractCXXImplementation.peek()
          .addMapping("__GENERATED_OUTPUT__",
              _generatedFilesDirectory.getPath().toString());

      _templateFilesOfCXXHeader.peek().addMapping("__GENERATED_OUTPUT__",
          _generatedFilesDirectory.getPath().toString());
      _templateFilesOfCXXHeader.peek().addMapping(
          "__PATH_FULL_QUALIFIED_NAME__",
          _fullQualifiedName.replaceAll("[.]", "/"));

      _templateFilesOfCXXHeader.peek().open();
      _templateFilesOfCXXImplementation.peek().open();

      _generateProvidesMethods = true;

      for (PUserDefinedType definedType : node.getProvides()) {
        definedType.apply(this);
      }
      _generateProvidesMethods = false;
    } catch (ASCoDTException e) {
      ErrorWriterDevice.getInstance().println(e);
    }

    _trace.out("inAClassPackageElement(...)", "open new port interface");
  }

  @Override
  public void inAInterfacePackageElement(AInterfacePackageElement node) {
    // if (_generateProvidesMethods) {
    _delimiter = ",public ";
    String fullQualifiedSymbolName = _symbolTable.getScope(node)
        .getFullyQualifiedName(Scope.getSymbol(node));
    _providePortsIncludes += "#include \"" +
        fullQualifiedSymbolName.replaceAll("[.]", "/") + ".h\"\n";
    _providePortsInterfaces += _delimiter +
        fullQualifiedSymbolName.replaceAll("[.]", "::");

    // }
  }

  @Override
  public void inAOperation(AOperation node) {
    Assert.isTrue(_generateProvidesMethods);
    try {
      String templateCxxImplementationFile = "native-component-cxx-implementation-provides-port.template";
      String templateCxxImplementationHeaderFile = "native-component-cxx-header-provides-port.template";
      String templateCxxImplementationAbstractHeaderFile = "native-component-abstract-cxx-header-provides-port.template";
      String templateCxxImplementationAbstractFile = "native-component-abstract-cxx-implementation-provides-port.template";

      TemplateFile cxxImplementationHeaderTemplate = new TemplateFile(
          _templateFilesOfCXXHeader.peek(), templateCxxImplementationHeaderFile);
      TemplateFile cxxImplementationTemplate = new TemplateFile(
          _templateFilesOfCXXImplementation.peek(),
          templateCxxImplementationFile);
      TemplateFile cxxImplementationAbstractHeaderTemplate = new TemplateFile(
          _templateFilesOfAbstractCXXHeader.peek(), templateCxxImplementationAbstractHeaderFile);
      TemplateFile cxxImplementationAbstractTemplate = new TemplateFile(
          _templateFilesOfAbstractCXXImplementation.peek(),
          templateCxxImplementationAbstractFile);
      ExclusivelyInParameters onlyInParameters = new ExclusivelyInParameters();
      node.apply(onlyInParameters);

      GetParameterList parameterList = new GetParameterList(
          _symbolTable.getScope(node));
      node.apply(parameterList);

      cxxImplementationHeaderTemplate.addMapping("__OPERATION_NAME__", node
          .getName().getText());
      cxxImplementationAbstractHeaderTemplate.addMapping("__OPERATION_NAME__", node
          .getName().getText());
      cxxImplementationTemplate.addMapping("__OPERATION_NAME__", node.getName()
          .getText());
      cxxImplementationAbstractTemplate.addMapping("__OPERATION_NAME__", node.getName()
          .getText());
      cxxImplementationHeaderTemplate.addMapping(
          "__OPERATION_PARAMETERS_LIST__",
          parameterList.getParameterListInCxx());
      cxxImplementationAbstractHeaderTemplate.addMapping(
          "__OPERATION_PARAMETERS_LIST__",
          parameterList.getParameterListInCxx());
      
      cxxImplementationTemplate.addMapping("__OPERATION_PARAMETERS_LIST__",
          parameterList.getParameterListInCxx());
      cxxImplementationTemplate.addMapping("__CXX_FULL_QUALIFIED_NAME__",
          _fullQualifiedName.replaceAll("[.]", "::"));
      
      cxxImplementationAbstractTemplate.addMapping("__OPERATION_PARAMETERS_LIST__",
          parameterList.getParameterListInCxx());
      cxxImplementationAbstractTemplate.addMapping("__CXX_FULL_QUALIFIED_NAME__",
          _fullQualifiedName.replaceAll("[.]", "::"));
      
      cxxImplementationHeaderTemplate.open();
      cxxImplementationHeaderTemplate.close();
      cxxImplementationTemplate.open();
      cxxImplementationTemplate.close();
      _templateFilesHeaderProvidesPorts.add(cxxImplementationAbstractHeaderTemplate);
      _templateFilesImplementationProvidesPorts.add(cxxImplementationAbstractTemplate);
      

    } catch (ASCoDTException e) {
      ErrorWriterDevice.getInstance().println(e);
    }
  }

  @Override
  public void inAUserDefinedType(AUserDefinedType node) {
    if (_generateProvidesMethods) {
      String fullQualifiedSymbol = Scope.getSymbol(node);
      AInterfacePackageElement interfaceNode = _symbolTable.getScope(node)
          .getInterfaceDefinition(fullQualifiedSymbol);
      if (interfaceNode != null) {
        interfaceNode.apply(this);
      }

    }
  }

  @Override
  public void inAUses(AUses node) {
    _trace.in("inAUses(AUses)", node.toString());
    try {
      GetProvidesAndUsesPortsOfComponent getPorts = new GetProvidesAndUsesPortsOfComponent();
      node.apply(getPorts);
      ExclusivelyInParameters onlyInParameters = new ExclusivelyInParameters();
      node.apply(onlyInParameters);

      String portType = getPorts.getUsesPorts("", "::");
      String portTypePath = getPorts.getUsesPorts("", "/");
      String portName = node.getAs().getText();
      String templateFileHeader = "native-component-abstract-cxx-header-uses-port.template";
      String templateFileImlementation = "native-component-abstract-cxx-implementation-uses-port.template";

      _usesPortsIncludes += "#include \"" + portTypePath +
          "NativeDispatcher.h\"\n";
      _usesPortsVariables += portType + "NativeDispatcher* _" + portName +
          ";\n";
      _usesPortsInitialisation += "_" + portName + " = 0;\n";
      TemplateFile templateHeader = new TemplateFile(
          _templateFilesOfAbstractCXXHeader.peek(), templateFileHeader);
      _templateFilesHeaderUsesPorts.add(templateHeader);
      templateHeader.addMapping("__USES_PORT_AS__", portName);
      templateHeader.addMapping("__USES_PORT_TYPE__", portType);

      TemplateFile templateImplementation = new TemplateFile(
          _templateFilesOfAbstractCXXImplementation.peek(),
          templateFileImlementation);
      _templateFilesImplementationUsesPorts.add(templateImplementation);
      templateImplementation.addMapping("__USES_PORT_AS__", portName);
      templateImplementation.addMapping("__USES_PORT_TYPE__", portType);

    } catch (ASCoDTException e) {
      ErrorWriterDevice.getInstance().println(e);
    }
    _trace.out("inAUses(AUses)");
  }

  /**
   * Close the output streams.
   */
  @Override
  public void outAClassPackageElement(AClassPackageElement node) {
    Assert.isTrue(_templateFilesOfCXXHeader.size() == 1);
    Assert.isTrue(_templateFilesOfCXXImplementation.size() == 1);
    Assert.isTrue(_templateFilesOfAbstractCXXHeader.size() == 1);
    Assert.isTrue(_templateFilesOfAbstractCXXImplementation.size() == 1);

    try {
      _templateFilesOfAbstractCXXHeader.peek().addMapping(
          "__INCLUDE_USES_PORTS__", _usesPortsIncludes);
      _templateFilesOfAbstractCXXHeader.peek().addMapping(
          "__INCLUDE_PROVIDE_PORTS__", _providePortsIncludes);
      _templateFilesOfAbstractCXXHeader.peek().addMapping("__PROVIDE_PORTS__",
          _providePortsInterfaces);
      _templateFilesOfAbstractCXXHeader.peek().addMapping(
          "__USES_PORTS_VARS__", _usesPortsVariables);
      _templateFilesOfAbstractCXXHeader.peek().open();
      while (!_templateFilesHeaderUsesPorts.isEmpty()) {
        _templateFilesHeaderUsesPorts.peek().open();
        _templateFilesHeaderUsesPorts.peek().close();
        _templateFilesHeaderUsesPorts.pop();
      }
      
      while (!_templateFilesHeaderProvidesPorts.isEmpty()) {
        _templateFilesHeaderProvidesPorts.peek().open();
        _templateFilesHeaderProvidesPorts.peek().close();
        _templateFilesHeaderProvidesPorts.pop();
      }
      
      _templateFilesOfCXXHeader.peek().close();
      _templateFilesOfCXXImplementation.peek().close();
      _templateFilesOfAbstractCXXHeader.peek().close();
      _templateFilesOfAbstractCXXImplementation.peek().addMapping(
          "__USES_PORTS_VARS__", _usesPortsInitialisation);
      _templateFilesOfAbstractCXXImplementation.peek().addMapping(
          "__INIT_USES_VARS__", _usesPortsInitialisation);

      _templateFilesOfAbstractCXXImplementation.peek().open();
      while (!_templateFilesImplementationUsesPorts.isEmpty()) {
        _templateFilesImplementationUsesPorts.peek().open();
        _templateFilesImplementationUsesPorts.peek().close();
        _templateFilesImplementationUsesPorts.pop();
      }
      while (!_templateFilesImplementationProvidesPorts.isEmpty()) {
        _templateFilesImplementationProvidesPorts.peek().open();
        _templateFilesImplementationProvidesPorts.peek().close();
        _templateFilesImplementationProvidesPorts.pop();
      }
      _templateFilesOfAbstractCXXImplementation.peek().close();

    } catch (ASCoDTException e) {
      ErrorWriterDevice.getInstance().println(e);
    }

    _templateFilesOfCXXHeader.pop();
    _templateFilesOfCXXImplementation.pop();
    _templateFilesOfAbstractCXXHeader.pop();
    _templateFilesOfAbstractCXXImplementation.pop();

  }
}