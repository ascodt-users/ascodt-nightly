/**
 * 
 */
package de.tum.ascodt.sidlcompiler.backend;


import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Stack;

import org.eclipse.core.runtime.Assert;

import de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice;
import de.tum.ascodt.plugin.utils.tracing.Trace;
import de.tum.ascodt.sidlcompiler.astproperties.ExclusivelyInParameters;
import de.tum.ascodt.sidlcompiler.astproperties.GetParameterList;
import de.tum.ascodt.sidlcompiler.frontend.analysis.DepthFirstAdapter;
import de.tum.ascodt.sidlcompiler.frontend.node.AEnumDeclarationPackageElement;
import de.tum.ascodt.sidlcompiler.frontend.node.AInterfacePackageElement;
import de.tum.ascodt.sidlcompiler.frontend.node.AOperation;
import de.tum.ascodt.sidlcompiler.frontend.node.AUserDefinedType;
import de.tum.ascodt.sidlcompiler.symboltable.Scope;
import de.tum.ascodt.sidlcompiler.symboltable.SymbolTable;
import de.tum.ascodt.utils.TemplateFile;
import de.tum.ascodt.utils.exceptions.ASCoDTException;


/**
 * @author Atanas Atanasov
 * 
 */
public class CreateNative2SocketPlainPorts extends DepthFirstAdapter {
  private static Trace _trace =
      new Trace(CreateNative2SocketPlainPorts.class.getCanonicalName());

  private Stack<TemplateFile> _templateCxxFilesHeader;
  private Stack<TemplateFile> _templateCxxFilesImplementation;
  private Stack<TemplateFile> _templateCFilesHeader;
  private Stack<TemplateFile> _templateCFilesImplementation;
  private Stack<TemplateFile> _templateFPort;
  private Stack<TemplateFile> _templateFPortProxy;
  private Stack<TemplateFile> _templateFPortOperations;
  private Path _fortranDirectoryPath;
  private Path _cxxDirectoryPath;
  private String[] _namespace;
  private SymbolTable _symbolTable;

  private boolean _generateSuperport;

  private String _operations;

  private HashMap<String, Integer> _operationsMap;

  private String _fullyQualifiedComponentName;
  private String _enumerationIncludes;

  public CreateNative2SocketPlainPorts(SymbolTable symbolTable,
                                       Path componentsDirectoryPath,
                                       String[] namespace,
                                       HashMap<String, Integer> operationsMap) {
    _templateCxxFilesHeader = new Stack<TemplateFile>();
    _templateCxxFilesImplementation = new Stack<TemplateFile>();
    _templateCFilesHeader = new Stack<TemplateFile>();
    _templateCFilesImplementation = new Stack<TemplateFile>();
    _templateFPort = new Stack<TemplateFile>();
    _templateFPortProxy = new Stack<TemplateFile>();
    _templateFPortOperations = new Stack<TemplateFile>();
    _fortranDirectoryPath = componentsDirectoryPath.resolve("fortran");
    _cxxDirectoryPath = componentsDirectoryPath.resolve("c++");
    _namespace = namespace;
    _symbolTable = symbolTable;
    _generateSuperport = false;
    _operations = "";
    _operationsMap = operationsMap;
    _enumerationIncludes = "";
  }

  /**
   * @param portName
   * @param fullQualifiedPortName
   * @throws ASCoDTException
   */
  public void addMappingCHeader(String portName, String fullQualifiedPortName) throws ASCoDTException {
    // _templateCFilesHeader.peek().addMapping("__PORT_NAME__", portName);
    _templateCFilesHeader.peek()
                         .addMapping("__INCLUDE_GUARD_C_FULL_QUALIFIED_NAME__",
                                     fullQualifiedPortName.replaceAll("[.]",
                                                                      "_")
                                                          .toUpperCase());
    _templateCFilesHeader.peek()
                         .addMapping("__C_FULL_QUALIFIED_NAME__",
                                     fullQualifiedPortName.replaceAll("[.]",
                                                                      "_")
                                                          .toLowerCase());

    _templateCFilesHeader.peek()
                         .addMapping("__C_FULL_QUALIFIED_NAME_4WIN__",
                                     fullQualifiedPortName.replaceAll("[.]",
                                                                      "_")
                                                          .toUpperCase());
    // _templateCFilesHeader.peek().addMapping(
    // "__PATH_FULL_QUALIFIED_NAME__",fullQualifiedPortName.replaceAll("[.]",
    // "/"));

  }

  /**
   * @param portType
   * @param fullQualifiedPortName
   */
  public void addMappingCImplementation(String portType,
                                        String fullQualifiedPortName) {
    // TODO static
    _templateCFilesImplementation.peek()
                                 .addMapping("__C_FULL_QUALIFIED_NAME__",
                                             fullQualifiedPortName.replaceAll("[.]",
                                                                              "_")
                                                                  .toLowerCase());

    _templateCFilesImplementation.peek()
                                 .addMapping("__C_FULL_QUALIFIED_NAME_4WIN__",
                                             fullQualifiedPortName.replaceAll("[.]",
                                                                              "_")
                                                                  .toUpperCase());
    _templateCFilesImplementation.peek()
                                 .addMapping("__CXX_FULL_QUALIFIED_NAME__",
                                             fullQualifiedPortName.replaceAll("[.]",
                                                                              "::"));
    _templateCFilesImplementation.peek().addMapping("__PORT_NAME__", portType);
    _templateCFilesImplementation.peek()
                                 .addMapping("__PATH_FULL_QUALIFIED_NAME__",
                                             fullQualifiedPortName.replaceAll("[.]",
                                                                              "/"));

    // _templateCFilesImplementation.peek().addMapping(
    // "__JNI_FULL_QUALIFIED_NAME__",fullQualifiedPortName.replaceAll("[.]",
    // "_"));

  }

  /**
   * @param portName
   * @param fullQualifiedPortName
   * @throws ASCoDTException
   */
  public void addMappingCxxHeader(String portName, String fullQualifiedPortName) throws ASCoDTException {
    _templateCxxFilesHeader.peek().addMapping("__PORT_NAME__", portName);
    _templateCxxFilesHeader.peek()
                           .addMapping("__INCLUDE_GUARD_FULL_QUALIFIED_NAME__",
                                       fullQualifiedPortName.replaceAll("[.]",
                                                                        "_")
                                                            .toUpperCase());
    _templateCxxFilesHeader.peek()
                           .addMapping("__FULL_QUALIFIED_NAME__",
                                       fullQualifiedPortName.replaceAll("[.]",
                                                                        "::"));
    _templateCxxFilesHeader.peek()
                           .addMapping("__PATH_FULL_QUALIFIED_NAME__",
                                       fullQualifiedPortName.replaceAll("[.]",
                                                                        "/"));
    _templateCxxFilesHeader.peek()
                           .addMapping("__JNI_FULL_QUALIFIED_NAME__",
                                       fullQualifiedPortName.replaceAll("[.]",
                                                                        "_"));

  }

  /**
   * @param portType
   * @param fullQualifiedPortName
   */
  public void addMappingCxxImplementation(String portType,
                                          String fullQualifiedPortName) {
    _templateCxxFilesImplementation.peek()
                                   .addMapping("__FULL_QUALIFIED_NAME__",
                                               fullQualifiedPortName.replaceAll("[.]",
                                                                                "::"));
    _templateCxxFilesImplementation.peek()
                                   .addMapping("__PORT_NAME__", portType);
    _templateCxxFilesImplementation.peek()
                                   .addMapping("__PATH_FULL_QUALIFIED_NAME__",
                                               fullQualifiedPortName.replaceAll("[.]",
                                                                                "/"));
    // _templateCxxFilesImplementation.peek().addMapping(
    // "__JNI_FULL_QUALIFIED_NAME__",fullQualifiedPortName.replaceAll("[.]",
    // "_"));

  }

  private void addMappingFPort(String portName, String fullQualifiedPortName) {
    _templateFPortProxy.peek()
                       .addMapping("__C_FULL_QUALIFIED_NAME__",
                                   fullQualifiedPortName.replaceAll("[.]", "_")
                                                        .toLowerCase());
  }

  private void addMappingFPortProxy(String portName,
                                    String fullQualifiedPortName) {
    _templateFPort.peek().addMapping("__PORT_NAME__", portName);
    _templateFPort.peek().addMapping("__C_FULL_QUALIFIED_NAME__",
                                     fullQualifiedPortName.replaceAll("[.]",
                                                                      "_")
                                                          .toLowerCase());
  }

  private void generateEnumIncludes() {
    for (AEnumDeclarationPackageElement globalEnumeration : _symbolTable.getGlobalScope()
                                                                        .getFlattenedEnumsElements()) {
      // for(String localEnumeration:_enums)

      // if(globalEnumeration.getName().getText().contains(localEnumeration.substring(localEnumeration.lastIndexOf(".")+1))){
      String fullQualifiedName =
          _symbolTable.getScope(globalEnumeration)
                      .getFullyQualifiedName(globalEnumeration.getName()
                                                              .getText());
      _enumerationIncludes +=
          "#include \"" + fullQualifiedName.replaceAll("[.]", "/") + ".h\"\n";
    }
    // }
  }

  @Override
  public void inAInterfacePackageElement(AInterfacePackageElement node) {
    _trace.in("inAInterfacePackageElement(...)", "open new port interface");
    try {
      if (!_generateSuperport) {
        String componentName = node.getName().getText();
        _fullyQualifiedComponentName =
            _symbolTable.getScope(node).getFullyQualifiedName(componentName);

        _templateCxxFilesHeader.push(new TemplateFile(Paths.get("cxx-port-native2socket-plain-header.template"),
                                                      _cxxDirectoryPath.resolve(_fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                        "/") + "Cxx2SocketPlainPort.h"),
                                                      _namespace,
                                                      TemplateFile.getLanguageConfigurationForCPP(),
                                                      true));
        _templateCxxFilesImplementation.push(new TemplateFile(Paths.get("cxx-port-native2socket-plain-implementation.template"),
                                                              _cxxDirectoryPath.resolve(_fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                                "/") + "Cxx2SocketPlainPort.cpp"),
                                                              _namespace,
                                                              TemplateFile.getLanguageConfigurationForCPP(),
                                                              true));
        _templateCFilesHeader.push(new TemplateFile(Paths.get("c-port-native2socket-plain-header.template"),
                                                    _cxxDirectoryPath.resolve(_fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                      "/") + "C2CxxSocketPlainPort.h"),
                                                    _namespace,
                                                    TemplateFile.getLanguageConfigurationForCPP(),
                                                    true));
        _templateCFilesImplementation.push(new TemplateFile(Paths.get("c-port-native2socket-plain-implementation.template"),
                                                            _cxxDirectoryPath.resolve(_fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                              "/") + "C2CxxSocketPlainPort.cpp"),
                                                            _namespace,
                                                            TemplateFile.getLanguageConfigurationForCPP(),
                                                            true));

        _templateFPort.push(new TemplateFile(Paths.get("fortran-port-f2native-plain-port-implementation.template"),
                                             _fortranDirectoryPath.resolve(_fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                   "/") + "2SocketPlainPort.f90"),
                                             _namespace,
                                             TemplateFile.getLanguageConfigurationForFortran(),
                                             true));
        _templateFPortProxy.push(new TemplateFile(Paths.get("fortran-port-f2native-proxy-plain-port-implementation.template"),
                                                  _fortranDirectoryPath.resolve(_fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                        "/") + "2SocketPlainPortProxy.f90"),
                                                  _namespace,
                                                  TemplateFile.getLanguageConfigurationForFortran(),
                                                  true));

        addMappingCxxHeader(componentName, _fullyQualifiedComponentName);
        addMappingCxxImplementation(componentName, _fullyQualifiedComponentName);
        addMappingCHeader(componentName, _fullyQualifiedComponentName);
        addMappingCImplementation(componentName, _fullyQualifiedComponentName);
        addMappingFPort(componentName, _fullyQualifiedComponentName);
        addMappingFPortProxy(componentName, _fullyQualifiedComponentName);
        generateEnumIncludes();
        _templateCFilesHeader.peek().addMapping("__ENUM_INCLUDES__",
                                                _enumerationIncludes);
        _templateCxxFilesHeader.peek().open();
        _templateCxxFilesImplementation.peek().open();
        _templateCFilesHeader.peek().open();
        _templateCFilesImplementation.peek().open();
        _templateFPortProxy.peek().open();
      }
    } catch (ASCoDTException e) {
      ErrorWriterDevice.getInstance().println(e);
    }

    _trace.out("inAInterfacePackageElement(...)", "open new port interface");
  }

  /**
   * We create the one operation belonging to this port operation.
   */
  @Override
  public void inAOperation(AOperation node) {
    _trace.in("inAOperation(...)");
    try {
      ExclusivelyInParameters onlyInParameters = new ExclusivelyInParameters();
      node.apply(onlyInParameters);

      TemplateFile templateCxxOperationHeader =
          new TemplateFile(_templateCxxFilesHeader.peek(),
                           Paths.get("cxx-port-native-operation-plain-header.template"));
      TemplateFile templateCxxImplementation =
          new TemplateFile(_templateCxxFilesImplementation.peek(),
                           Paths.get("cxx-port-native2socket-operation-plain-implementation.template"));
      TemplateFile templateCOperationHeader =
          new TemplateFile(_templateCFilesHeader.peek(),
                           Paths.get("c-port-native2socket-operation-plain-header.template"));
      TemplateFile templateCImplementation =
          new TemplateFile(_templateCFilesImplementation.peek(),
                           Paths.get("c-port-native2socket-operation-plain-implementation.template"));
      TemplateFile templateFPortOperation =
          new TemplateFile(_templateFPort.peek(),
                           Paths.get("fortran-port-f2native-plain-port-operation-implementation.template"));
      TemplateFile templateFPortProxyOperation =
          new TemplateFile(_templateFPortProxy.peek(),
                           Paths.get("fortran-port-f2native-proxy-plain-port-operation-implementation.template"));
      _templateFPortOperations.add(templateFPortOperation);
      GetParameterList parameterList =
          new GetParameterList(_symbolTable.getScope(node));
      node.apply(parameterList);
      //
      templateCxxOperationHeader.addMapping("__OPERATION_NAME__",
                                            node.getName().getText());
      templateCxxOperationHeader.addMapping("__OPERATION_PARAMETERS_LIST__",
                                            parameterList.getParameterListInCxx());
      templateFPortOperation.addMapping("__OPERATION_NAME__", node.getName()
                                                                  .getText());
      templateFPortProxyOperation.addMapping("__OPERATION_NAME__",
                                             node.getName().getText());
      templateFPortOperation.addMapping("__OPERATION_PARAMETERS_LIST__",
                                        parameterList.getParameterListInF(true));
      templateFPortOperation.addMapping("__OPERATION_PARAMETERS_TYPES_LIST__",
                                        parameterList.getParameterListTypesForF(true));
      templateFPortProxyOperation.addMapping("__OPERATION_PARAMETERS_LIST__",
                                             parameterList.getParameterListInF(true));
      templateFPortProxyOperation.addMapping("__OPERATION_PARAMETERS_TYPES_LIST__",
                                             parameterList.getParameterListTypesForFCBindedToC(true));
      templateFPortOperation.addMapping("__FUNCTION_CALL_PARAMETERS_LIST__",
                                        parameterList.getFunctionCallListInFClient(false));

      templateCOperationHeader.addMapping("__OPERATION_NAME__",
                                          node.getName()
                                              .getText()
                                              .toLowerCase());
      templateCOperationHeader.addMapping("__OPERATION_NAME_4WIN__",
                                          node.getName()
                                              .getText()
                                              .toUpperCase());
      String parameters = parameterList.getParameterListInF2Cxx();
      if (!parameters.equals("")) {
        parameters = "," + parameters;
      }
      //
      templateCOperationHeader.addMapping("__OPERATION_PARAMETERS_LIST__",
                                          parameters);
      templateCxxImplementation.addMapping("__OPERATION_ID__",
                                           "" + _operationsMap.get(_fullyQualifiedComponentName + node.getName()
                                                                                                      .getText()));
      templateCxxImplementation.addMapping("__PARALLEL_OPERATION_ID__",
                                           "" + _operationsMap.get(_fullyQualifiedComponentName + node.getName()
                                                                                                      .getText() +
                                                                   "Parallel"));
      templateCxxImplementation.addMapping("__OPERATION_NAME__", node.getName()
                                                                     .getText());
      templateCxxImplementation.addMapping("__FUNCTION_CALL_PARAMETERS_LIST__",
                                           parameterList.getFunctionCallListInCxx());
      templateCxxImplementation.addMapping("__OPERATION_PARAMETERS_LIST__",
                                           parameterList.getParameterListInCxx());
      String pullOut = parameterList.pullOutFromSocketForCxx();
      String switchSyncAsync = "";
      if (pullOut.equals("")) {
        switchSyncAsync += "#ifdef _WIN32\n";
        switchSyncAsync += "#else\n";

        switchSyncAsync += "int flags;\n";
        switchSyncAsync += "flags = fcntl(_newsockfd, F_GETFL, 0);\n";
        switchSyncAsync += "flags |= O_NONBLOCK;\n";
        switchSyncAsync += "fcntl(_newsockfd, F_SETFL, flags);\n";
        switchSyncAsync += "#endif\n";

        templateCxxImplementation.addMapping("__SWITCH_SYNC_ASYNC__",
                                             switchSyncAsync);
      } else {
        switchSyncAsync += "#ifdef _WIN32\n";
        switchSyncAsync += "#else\n";
        switchSyncAsync += "int flags;\n";
        switchSyncAsync += "flags = fcntl(_newsockfd, F_GETFL, 0);\n";
        switchSyncAsync += "flags ^= O_NONBLOCK;\n";
        switchSyncAsync += "fcntl(_newsockfd, F_SETFL, flags);\n";
        switchSyncAsync += "#endif\n";
        templateCxxImplementation.addMapping("__SWITCH_SYNC_ASYNC__",
                                             switchSyncAsync);
      }

      templateCxxImplementation.addMapping("__SOCKET_PUSH__",
                                           parameterList.pushInToSocketForCxx());

      templateCxxImplementation.addMapping("__SOCKET_PULL__",
                                           parameterList.pullOutFromSocketForCxx());
      templateCImplementation.addMapping("__PREPARE__STRING_ARGS__",
                                         parameterList.convertCharsToString());
      templateCImplementation.addMapping("__OPERATION_NAME__",
                                         node.getName().getText().toLowerCase());
      templateCImplementation.addMapping("__OPERATION_NAME_4WIN__",
                                         node.getName().getText().toUpperCase());

      templateCImplementation.addMapping("__CXX_OPERATION_NAME__",
                                         node.getName().getText());
      templateCImplementation.addMapping("__FUNCTION_CALL_PARAMETERS_LIST__",
                                         parameterList.getFunctionCallListInF2Cxx());
      templateCImplementation.addMapping("__OPERATION_PARAMETERS_LIST__",
                                         parameters);
      _operations += "procedure,public::" + node.getName().getText() + "\n";
      //

      templateCxxOperationHeader.open();
      templateCxxOperationHeader.close();
      templateCxxImplementation.open();
      templateCxxImplementation.close();
      templateCOperationHeader.open();
      templateCOperationHeader.close();
      templateCImplementation.open();
      templateCImplementation.close();
      templateFPortProxyOperation.open();
      templateFPortProxyOperation.close();
      //
      //
      // templateJava.open();
      // templateJava.close();
    } catch (ASCoDTException e) {
      ErrorWriterDevice.getInstance().println(e);
    }

    _trace.out("inAOperation(...)");
  }

  @Override
  public void inAUserDefinedType(AUserDefinedType node) {

    String fullQualifiedSymbol = Scope.getSymbol(node);
    AInterfacePackageElement interfaceDefintion =
        _symbolTable.getScope(node).getInterfaceDefinition(fullQualifiedSymbol);
    if (interfaceDefintion != null) {
      _generateSuperport = true;
      interfaceDefintion.apply(this);
      _generateSuperport = false;
    }
  }

  @Override
  public void outAInterfacePackageElement(AInterfacePackageElement node) {
    Assert.isTrue(_templateCxxFilesHeader.size() == 1);
    if (!_generateSuperport) {

      _templateCxxFilesHeader.peek().close();
      _templateCxxFilesImplementation.peek().close();

      _templateCFilesHeader.peek().close();
      _templateCFilesImplementation.peek().close();
      _templateFPort.peek().addMapping("__OPERATIONS__", _operations);
      _templateFPort.peek().open();
      while (!_templateFPortOperations.isEmpty()) {
        _templateFPortOperations.peek().open();
        _templateFPortOperations.peek().close();
        _templateFPortOperations.pop();
      }
      _templateFPort.peek().close();
      _templateFPortProxy.peek().close();
      _templateCxxFilesHeader.pop();
      _templateCxxFilesImplementation.pop();
      _templateCFilesHeader.pop();
      _templateCFilesImplementation.pop();
      _templateFPort.pop();
      _templateFPortProxy.pop();
    }
  }
}
