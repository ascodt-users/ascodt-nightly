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


public class CreateJNIProxyForCxx extends DepthFirstAdapter {
  private Trace _trace =
      new Trace(CreateJNIProxyForCxx.class.getCanonicalName());

  private Stack<TemplateFile> _templateFilesOfJNIProxyHeader;
  private Stack<TemplateFile> _templateFilesOfJNIProxyImplementation;
  private Stack<TemplateFile> _templateFilesUsesPorts;
  private Stack<TemplateFile> _templateFilesProvidesPorts;

  private Path _cxxDirectoryPath;
  private String[] _namespace;
  private SymbolTable _symbolTable;
  private String _fullyQualifiedComponentName;
  private boolean _generateProvidesMethods;
  private String _usesPortsIncludes;

  CreateJNIProxyForCxx(SymbolTable symbolTable,
                       Path componentsDirectoryPath,
                       String[] namespace) {
    _templateFilesOfJNIProxyHeader = new Stack<TemplateFile>();
    _templateFilesOfJNIProxyImplementation = new Stack<TemplateFile>();
    _templateFilesUsesPorts = new Stack<TemplateFile>();
    _templateFilesProvidesPorts = new Stack<TemplateFile>();
    _cxxDirectoryPath = componentsDirectoryPath.resolve("c++");
    _namespace = namespace;
    _symbolTable = symbolTable;
    _usesPortsIncludes = "";
  }

  @Override
  public void inAClassPackageElement(AClassPackageElement node) {
    _trace.in("inAClassPackageElement(...)", "open new port interface");

    String componentName = node.getName().getText();
    _fullyQualifiedComponentName =
        _symbolTable.getScope(node).getFullyQualifiedName(componentName);

    _templateFilesOfJNIProxyHeader.push(new TemplateFile(Paths.get("native-component-jniproxy-cxx-header.template"),
                                                         _cxxDirectoryPath.resolve(_fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                           "/") + "JNIProxy.h"),
                                                         _namespace,
                                                         TemplateFile.getLanguageConfigurationForJNI(),
                                                         true));
    _templateFilesOfJNIProxyImplementation.push(new TemplateFile(Paths.get("native-component-jniproxy-cxx-implementation.template"),
                                                                 _cxxDirectoryPath.resolve(_fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                                   "/") + "JNIProxy.cpp"),
                                                                 _namespace,
                                                                 TemplateFile.getLanguageConfigurationForJNI(),
                                                                 true));
    _templateFilesOfJNIProxyImplementation.peek()
                                          .addMapping("__COMPONENT_NAME__",
                                                      componentName);
    _templateFilesOfJNIProxyHeader.peek()
                                  .addMapping("__INCLUDE_GUARD_FULL_QUALIFIED_NAME__",
                                              _fullyQualifiedComponentName.replaceAll("[.]",
                                                                                      "_")
                                                                          .toUpperCase());
    _templateFilesOfJNIProxyHeader.peek()
                                  .addMapping("__JNI_FULL_QUALIFIED_NAME__",
                                              _fullyQualifiedComponentName.replaceAll("[.]",
                                                                                      "_"));
    _templateFilesOfJNIProxyImplementation.peek()
                                          .addMapping("__JNI_FULL_QUALIFIED_NAME__",
                                                      _fullyQualifiedComponentName.replaceAll("[.]",
                                                                                              "_"));
    _templateFilesOfJNIProxyImplementation.peek()
                                          .addMapping("__CXX_FULL_QUALIFIED_NAME__",
                                                      _fullyQualifiedComponentName.replaceAll("[.]",
                                                                                              "::"));
    _templateFilesOfJNIProxyImplementation.peek()
                                          .addMapping("__PATH_FULL_QUALIFIED_NAME__",
                                                      _fullyQualifiedComponentName.replaceAll("[.]",
                                                                                              "/"));
    _templateFilesOfJNIProxyHeader.peek().open();
    _generateProvidesMethods = true;
    for (PUserDefinedType definedType : node.getProvides()) {
      definedType.apply(this);
    }
    _generateProvidesMethods = false;

    _trace.out("inAClassPackageElement(...)", "open new port interface");
  }

  @Override
  public void inAOperation(AOperation node) {
    Assert.isTrue(_generateProvidesMethods);
    try {
      TemplateFile jniProxyImplementationHeaderTemplate =
          new TemplateFile(_templateFilesOfJNIProxyHeader.peek(),
                           Paths.get("native-component-jniproxy-cxx-header-provides-port.template"));
      TemplateFile jniProxyImplementationTemplate =
          new TemplateFile(_templateFilesOfJNIProxyImplementation.peek(),
                           Paths.get("native-component-jniproxy-cxx-implementation-provides-port.template"));

      ExclusivelyInParameters onlyInParameters = new ExclusivelyInParameters();
      node.apply(onlyInParameters);

      GetParameterList parameterList =
          new GetParameterList(_symbolTable.getScope(node));
      node.apply(parameterList);

      jniProxyImplementationHeaderTemplate.addMapping("__OPERATION_NAME__",
                                                      node.getName().getText());
      jniProxyImplementationTemplate.addMapping("__OPERATION_NAME__",
                                                node.getName().getText());
      jniProxyImplementationHeaderTemplate.addMapping("__OPERATION_PARAMETERS_LIST__",
                                                      parameterList.getParameterListInJNI(onlyInParameters.areAllParametersInParameters()));
      jniProxyImplementationTemplate.addMapping("__OPERATION_PARAMETERS_LIST__",
                                                parameterList.getParameterListInJNI(onlyInParameters.areAllParametersInParameters()));
      jniProxyImplementationHeaderTemplate.addMapping("__JNI_FULL_QUALIFIED_NAME__",
                                                      _fullyQualifiedComponentName.replaceAll("[.]",
                                                                                              "_"));
      jniProxyImplementationTemplate.addMapping("__JNI_FULL_QUALIFIED_NAME__",
                                                _fullyQualifiedComponentName.replaceAll("[.]",
                                                                                        "_"));
      jniProxyImplementationTemplate.addMapping("__CXX_FULL_QUALIFIED_NAME__",
                                                _fullyQualifiedComponentName.replaceAll("[.]",
                                                                                        "::"));
      jniProxyImplementationTemplate.addMapping("__START_METHOD_CALL__",
                                                parameterList.prepareJNIParametersForCxxCall());
      jniProxyImplementationTemplate.addMapping("__FUNCTION_CALL_PARAMETERS_LIST__",
                                                parameterList.getFunctionCallListInJNI2Cxx(false));
      jniProxyImplementationTemplate.addMapping("__END_METHOD_CALL__",
                                                parameterList.writeCxxParamatersFromJNIProvideCall());

      _templateFilesProvidesPorts.add(jniProxyImplementationTemplate);
      jniProxyImplementationHeaderTemplate.open();
      jniProxyImplementationHeaderTemplate.close();

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
      String portName = node.getAs().getText();
      String portTypePath = getPorts.getUsesPorts("", "/");

      TemplateFile templateHeader =
          new TemplateFile(_templateFilesOfJNIProxyHeader.peek(),
                           Paths.get("native-component-jniproxy-cxx-header-uses-port.template"));
      templateHeader.addMapping("__USES_PORT_AS__", portName);
      // templateHeader.addMapping( "__USES_PORT_TYPE__", portType );
      _usesPortsIncludes += "#include \"" + portTypePath + ".h\"\n";

      TemplateFile templateImplementation =
          new TemplateFile(_templateFilesOfJNIProxyImplementation.peek(),
                           Paths.get("native-component-jniproxy-cxx-implementation-uses-port.template"));
      templateImplementation.addMapping("__USES_PORT_AS__", portName);
      templateImplementation.addMapping("__USES_PORT_TYPE__", portType);
      _templateFilesUsesPorts.add(templateImplementation);
      templateHeader.open();
      templateHeader.close();

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
    Assert.isTrue(_templateFilesOfJNIProxyHeader.size() == 1);
    Assert.isTrue(_templateFilesOfJNIProxyImplementation.size() == 1);

    _templateFilesOfJNIProxyHeader.peek().close();
    _templateFilesOfJNIProxyImplementation.peek()
                                          .addMapping("__INCLUDE_USES_PORTS__",
                                                      _usesPortsIncludes);

    _templateFilesOfJNIProxyImplementation.peek().open();
    while (!_templateFilesUsesPorts.isEmpty()) {
      _templateFilesUsesPorts.peek().open();
      _templateFilesUsesPorts.peek().close();
      _templateFilesUsesPorts.pop();
    }
    while (!_templateFilesProvidesPorts.isEmpty()) {
      _templateFilesProvidesPorts.peek().open();
      _templateFilesProvidesPorts.peek().close();
      _templateFilesProvidesPorts.pop();
    }
    _templateFilesOfJNIProxyImplementation.peek().close();
    _templateFilesOfJNIProxyHeader.pop();
    _templateFilesOfJNIProxyImplementation.pop();
  }
}