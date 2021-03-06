package de.tum.ascodt.sidlcompiler.backend;


import java.nio.file.Path;
import java.nio.file.Paths;
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
  private Path _sourcesDirectoryPath;
  private Path _cxxDirectoryPath;
  private String[] _namespace;

  private String _fullyQualifiedComponentName;
  private SymbolTable _symbolTable;
  private boolean _generateProvidesMethods;

  private String _usesPortsIncludes;

  private String _usesPortsVariables;
  private String _usesPortsInitialisation;

  private String _providePortsIncludes;

  private String _providePortsInterfaces;

  private String _delimiter;

  public CreateCxxComponent(SymbolTable symbolTable,
                            Path sourcesDirectoryPath,
                            Path componentsDirectoryPath,
                            String[] namespace) {
    _templateFilesOfCXXHeader = new Stack<TemplateFile>();
    _templateFilesOfCXXImplementation = new Stack<TemplateFile>();
    _templateFilesOfAbstractCXXHeader = new Stack<TemplateFile>();
    _templateFilesOfAbstractCXXImplementation = new Stack<TemplateFile>();
    _templateFilesHeaderUsesPorts = new Stack<TemplateFile>();
    _templateFilesHeaderProvidesPorts = new Stack<TemplateFile>();
    _templateFilesImplementationUsesPorts = new Stack<TemplateFile>();
    _templateFilesImplementationProvidesPorts = new Stack<TemplateFile>();
    _sourcesDirectoryPath = sourcesDirectoryPath;
    _cxxDirectoryPath = componentsDirectoryPath.resolve("c++");
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

    String componentName = node.getName().getText();
    _fullyQualifiedComponentName =
        _symbolTable.getScope(node).getFullyQualifiedName(componentName);

    _templateFilesOfCXXHeader.push(new TemplateFile(Paths.get("native-component-cxx-header.template"),
                                                    _sourcesDirectoryPath.resolve(_fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                          "/") + "Implementation.h"),
                                                    _namespace,
                                                    TemplateFile.getLanguageConfigurationForCPP(),
                                                    false));

    _templateFilesOfCXXImplementation.push(new TemplateFile(Paths.get("native-component-cxx-implementation.template"),
                                                            _sourcesDirectoryPath.resolve(_fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                                  "/") + "Implementation.cpp"),
                                                            _namespace,
                                                            TemplateFile.getLanguageConfigurationForCPP(),
                                                            false));
    _templateFilesOfAbstractCXXHeader.push(new TemplateFile(Paths.get("native-component-abstract-cxx-header.template"),
                                                            _cxxDirectoryPath.resolve(_fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                              "/") + "AbstractImplementation.h"),
                                                            _namespace,
                                                            TemplateFile.getLanguageConfigurationForCPP(),
                                                            true));
    _templateFilesOfAbstractCXXImplementation.push(new TemplateFile(Paths.get("native-component-abstract-cxx-implementation.template"),
                                                                    _cxxDirectoryPath.resolve(_fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                                      "/") + "AbstractImplementation.cpp"),
                                                                    _namespace,
                                                                    TemplateFile.getLanguageConfigurationForCPP(),
                                                                    true));

    _templateFilesOfCXXHeader.peek().addMapping("__COMPONENT_NAME__",
                                                componentName);
    _templateFilesOfAbstractCXXHeader.peek().addMapping("__COMPONENT_NAME__",
                                                        componentName);
    _templateFilesOfCXXImplementation.peek().addMapping("__COMPONENT_NAME__",
                                                        componentName);
    _templateFilesOfAbstractCXXImplementation.peek()
                                             .addMapping("__COMPONENT_NAME__",
                                                         componentName);

    _templateFilesOfCXXHeader.peek()
                             .addMapping("__INCLUDE_GUARD_FULL_QUALIFIED_NAME__",
                                         _fullyQualifiedComponentName.replaceAll("[.]",
                                                                                 "_")
                                                                     .toUpperCase());
    _templateFilesOfCXXHeader.peek()
                             .addMapping("__CXX_FULL_QUALIFIED_NAME__",
                                         _fullyQualifiedComponentName.replaceAll("[.]",
                                                                                 "::"));
    _templateFilesOfAbstractCXXHeader.peek()
                                     .addMapping("__INCLUDE_GUARD_FULL_QUALIFIED_NAME__",
                                                 _fullyQualifiedComponentName.replaceAll("[.]",
                                                                                         "_")
                                                                             .toUpperCase());
    _templateFilesOfAbstractCXXHeader.peek()
                                     .addMapping("__CXX_FULL_QUALIFIED_NAME__",
                                                 _fullyQualifiedComponentName.replaceAll("[.]",
                                                                                         "::"));

    _templateFilesOfCXXImplementation.peek()
                                     .addMapping("__CXX_FULL_QUALIFIED_NAME__",
                                                 _fullyQualifiedComponentName.replaceAll("[.]",
                                                                                         "::"));
    _templateFilesOfCXXImplementation.peek()
                                     .addMapping("__PATH_FULL_QUALIFIED_NAME__",
                                                 _fullyQualifiedComponentName.replaceAll("[.]",
                                                                                         "/"));
    _templateFilesOfAbstractCXXImplementation.peek()
                                             .addMapping("__CXX_FULL_QUALIFIED_NAME__",
                                                         _fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                 "::"));
    _templateFilesOfAbstractCXXImplementation.peek()
                                             .addMapping("__PATH_FULL_QUALIFIED_NAME__",
                                                         _fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                 "/"));
    _templateFilesOfCXXHeader.peek()
                             .addMapping("__PATH_FULL_QUALIFIED_NAME__",
                                         _fullyQualifiedComponentName.replaceAll("[.]",
                                                                                 "/"));

    _templateFilesOfCXXHeader.peek().open();
    _templateFilesOfCXXImplementation.peek().open();

    _generateProvidesMethods = true;

    for (PUserDefinedType definedType : node.getProvides()) {
      definedType.apply(this);
    }
    _generateProvidesMethods = false;

    _trace.out("inAClassPackageElement(...)", "open new port interface");
  }

  @Override
  public void inAInterfacePackageElement(AInterfacePackageElement node) {
    // if (_generateProvidesMethods) {
    _delimiter = ",public ";
    String fullQualifiedSymbolName =
        _symbolTable.getScope(node)
                    .getFullyQualifiedName(Scope.getSymbol(node));
    _providePortsIncludes +=
        "#include \"" + fullQualifiedSymbolName.replaceAll("[.]", "/") +
            ".h\"\n";
    _providePortsInterfaces +=
        _delimiter + fullQualifiedSymbolName.replaceAll("[.]", "::");

    // }
  }

  @Override
  public void inAOperation(AOperation node) {
    Assert.isTrue(_generateProvidesMethods);
    try {
      TemplateFile cxxImplementationHeaderTemplate =
          new TemplateFile(_templateFilesOfCXXHeader.peek(),
                           Paths.get("native-component-cxx-header-provides-port.template"));
      TemplateFile cxxImplementationTemplate =
          new TemplateFile(_templateFilesOfCXXImplementation.peek(),
                           Paths.get("native-component-cxx-implementation-provides-port.template"));
      TemplateFile cxxImplementationAbstractHeaderTemplate =
          new TemplateFile(_templateFilesOfAbstractCXXHeader.peek(),
                           Paths.get("native-component-abstract-cxx-header-provides-port.template"));
      TemplateFile cxxImplementationAbstractTemplate =
          new TemplateFile(_templateFilesOfAbstractCXXImplementation.peek(),
                           Paths.get("native-component-abstract-cxx-implementation-provides-port.template"));
      ExclusivelyInParameters onlyInParameters = new ExclusivelyInParameters();
      node.apply(onlyInParameters);

      GetParameterList parameterList =
          new GetParameterList(_symbolTable.getScope(node));
      node.apply(parameterList);

      cxxImplementationHeaderTemplate.addMapping("__OPERATION_NAME__",
                                                 node.getName().getText());
      cxxImplementationAbstractHeaderTemplate.addMapping("__OPERATION_NAME__",
                                                         node.getName()
                                                             .getText());
      cxxImplementationTemplate.addMapping("__OPERATION_NAME__", node.getName()
                                                                     .getText());
      cxxImplementationAbstractTemplate.addMapping("__OPERATION_NAME__",
                                                   node.getName().getText());
      cxxImplementationHeaderTemplate.addMapping("__OPERATION_PARAMETERS_LIST__",
                                                 parameterList.getParameterListInCxx());
      cxxImplementationAbstractHeaderTemplate.addMapping("__OPERATION_PARAMETERS_LIST__",
                                                         parameterList.getParameterListInCxx());

      cxxImplementationTemplate.addMapping("__OPERATION_PARAMETERS_LIST__",
                                           parameterList.getParameterListInCxx());
      cxxImplementationTemplate.addMapping("__CXX_FULL_QUALIFIED_NAME__",
                                           _fullyQualifiedComponentName.replaceAll("[.]",
                                                                                   "::"));

      cxxImplementationAbstractTemplate.addMapping("__OPERATION_PARAMETERS_LIST__",
                                                   parameterList.getParameterListInCxx());
      cxxImplementationAbstractTemplate.addMapping("__CXX_FULL_QUALIFIED_NAME__",
                                                   _fullyQualifiedComponentName.replaceAll("[.]",
                                                                                           "::"));

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
      AInterfacePackageElement interfaceNode =
          _symbolTable.getScope(node)
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
      GetProvidesAndUsesPortsOfComponent getPorts =
          new GetProvidesAndUsesPortsOfComponent();
      node.apply(getPorts);
      ExclusivelyInParameters onlyInParameters = new ExclusivelyInParameters();
      node.apply(onlyInParameters);

      String portType = getPorts.getUsesPorts("", "::");
      String portTypePath = getPorts.getUsesPorts("", "/");
      String portName = node.getAs().getText();

      _usesPortsIncludes +=
          "#include \"" + portTypePath + "NativeDispatcher.h\"\n";
      _usesPortsVariables +=
          portType + "NativeDispatcher* _" + portName + ";\n";
      _usesPortsInitialisation += "_" + portName + " = 0;\n";
      TemplateFile templateHeader =
          new TemplateFile(_templateFilesOfAbstractCXXHeader.peek(),
                           Paths.get("native-component-abstract-cxx-header-uses-port.template"));
      _templateFilesHeaderUsesPorts.add(templateHeader);
      templateHeader.addMapping("__USES_PORT_AS__", portName);
      templateHeader.addMapping("__USES_PORT_TYPE__", portType);

      TemplateFile templateImplementation =
          new TemplateFile(_templateFilesOfAbstractCXXImplementation.peek(),
                           Paths.get("native-component-abstract-cxx-implementation-uses-port.template"));
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

    _templateFilesOfAbstractCXXHeader.peek()
                                     .addMapping("__INCLUDE_USES_PORTS__",
                                                 _usesPortsIncludes);
    _templateFilesOfAbstractCXXHeader.peek()
                                     .addMapping("__INCLUDE_PROVIDE_PORTS__",
                                                 _providePortsIncludes);
    _templateFilesOfAbstractCXXHeader.peek()
                                     .addMapping("__PROVIDE_PORTS__",
                                                 _providePortsInterfaces);
    _templateFilesOfAbstractCXXHeader.peek().addMapping("__USES_PORTS_VARS__",
                                                        _usesPortsVariables);
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
    _templateFilesOfAbstractCXXImplementation.peek()
                                             .addMapping("__USES_PORTS_VARS__",
                                                         _usesPortsInitialisation);
    _templateFilesOfAbstractCXXImplementation.peek()
                                             .addMapping("__INIT_USES_VARS__",
                                                         _usesPortsInitialisation);

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

    _templateFilesOfCXXHeader.pop();
    _templateFilesOfCXXImplementation.pop();
    _templateFilesOfAbstractCXXHeader.pop();
    _templateFilesOfAbstractCXXImplementation.pop();

  }
}