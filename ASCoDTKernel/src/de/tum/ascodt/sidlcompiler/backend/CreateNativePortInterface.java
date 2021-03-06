package de.tum.ascodt.sidlcompiler.backend;


import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.HashSet;
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
import de.tum.ascodt.sidlcompiler.frontend.node.PUserDefinedType;
import de.tum.ascodt.sidlcompiler.symboltable.Scope;
import de.tum.ascodt.sidlcompiler.symboltable.SymbolTable;
import de.tum.ascodt.utils.TemplateFile;
import de.tum.ascodt.utils.exceptions.ASCoDTException;


/**
 * Create the interface representing a port. This class is always to be invoked
 * directly on an interface node, i.e. never on the whole tree.
 * 
 * @author Atanas Atanasov
 */
public class CreateNativePortInterface extends DepthFirstAdapter {
  private static Trace _trace =
      new Trace(CreateNativePortInterface.class.getCanonicalName());

  private Stack<TemplateFile> _templateFilesInterface;
  private Stack<TemplateFile> _templateFilesDispatcherHeader;
  private Stack<TemplateFile> _templateFilesDispatcherImplementation;

  private Stack<TemplateFile> _templateFilesSocketDispatcherHeader;
  private Stack<TemplateFile> _templateFilesSocketDispatcherImplementation;

  private Stack<TemplateFile> _templateFilesFortranSocketDispatcher;
  private Stack<TemplateFile> _templateFilesFortranProxy4SocketDispatcher;
  private Stack<TemplateFile> _templateFilesCProxy4SocketDispatcher;

  private Stack<TemplateFile> _cxxOperationsTemplateFiles;
  private Stack<TemplateFile> _fortranOperationsTemplateFiles;
  private Path _fortranDirectoryPath;
  private Path _cxxDirectoryPath;
  private String[] _namespace;

  private SymbolTable _symbolTable;
  private String _enumerationIncludes;
  private HashSet<String> _enums;

  private String _operations;

  private boolean _generateSuperport;

  public CreateNativePortInterface(SymbolTable symbolTable,
                                   Path componentsDirectoryPath,
                                   String[] namespace) {
    _templateFilesInterface = new Stack<TemplateFile>();
    _templateFilesDispatcherHeader = new Stack<TemplateFile>();
    _templateFilesDispatcherImplementation = new Stack<TemplateFile>();
    _templateFilesSocketDispatcherHeader = new Stack<TemplateFile>();
    _templateFilesSocketDispatcherImplementation = new Stack<TemplateFile>();
    _templateFilesFortranSocketDispatcher = new Stack<TemplateFile>();
    _templateFilesFortranProxy4SocketDispatcher = new Stack<TemplateFile>();
    _templateFilesCProxy4SocketDispatcher = new Stack<TemplateFile>();
    _cxxOperationsTemplateFiles = new Stack<TemplateFile>();
    _fortranOperationsTemplateFiles = new Stack<TemplateFile>();
    _fortranDirectoryPath = componentsDirectoryPath.resolve("fortran");
    _cxxDirectoryPath = componentsDirectoryPath.resolve("c++");
    _namespace = namespace;
    _symbolTable = symbolTable;
    _enumerationIncludes = "";
    _enums = new HashSet<String>();
    _operations = "";
    _generateSuperport = false;
  }

  /**
   * @param portName
   */
  public void addMappingsHeader(String portName, String fullQualifiedPortName) {
    _templateFilesDispatcherHeader.peek().addMapping("__PORT_NAME__", portName);
    _templateFilesDispatcherHeader.peek()
                                  .addMapping("__INCLUDE_GUARD_FULL_QUALIFIED_NAME__",
                                              fullQualifiedPortName.replaceAll("[.]",
                                                                               "_")
                                                                   .toUpperCase());
    _templateFilesDispatcherHeader.peek()
                                  .addMapping("__FULL_QUALIFIED_NAME__",
                                              fullQualifiedPortName.replaceAll("[.]",
                                                                               "::"));
    _templateFilesDispatcherHeader.peek()
                                  .addMapping("__PATH_FULL_QUALIFIED_NAME__",
                                              fullQualifiedPortName.replaceAll("[.]",
                                                                               "/"));
    _templateFilesDispatcherHeader.peek()
                                  .addMapping("__JNI_FULL_QUALIFIED_NAME__",
                                              fullQualifiedPortName.replaceAll("[.]",
                                                                               "_"));

    _templateFilesSocketDispatcherHeader.peek().addMapping("__PORT_NAME__",
                                                           portName);
    _templateFilesSocketDispatcherHeader.peek()
                                        .addMapping("__INCLUDE_GUARD_FULL_QUALIFIED_NAME__",
                                                    fullQualifiedPortName.replaceAll("[.]",
                                                                                     "_")
                                                                         .toUpperCase());
    _templateFilesSocketDispatcherHeader.peek()
                                        .addMapping("__FULL_QUALIFIED_NAME__",
                                                    fullQualifiedPortName.replaceAll("[.]",
                                                                                     "::"));
    _templateFilesSocketDispatcherHeader.peek()
                                        .addMapping("__PATH_FULL_QUALIFIED_NAME__",
                                                    fullQualifiedPortName.replaceAll("[.]",
                                                                                     "/"));
    _templateFilesSocketDispatcherHeader.peek()
                                        .addMapping("__JNI_FULL_QUALIFIED_NAME__",
                                                    fullQualifiedPortName.replaceAll("[.]",
                                                                                     "_"));

  }

  /**
   * @param portName
   * @param fullQualifiedName
   */
  public void addMappingsImplementation(String portName,
                                        String fullQualifiedName) {
    _templateFilesDispatcherImplementation.peek()
                                          .addMapping("__FULL_QUALIFIED_NAME__",
                                                      fullQualifiedName.replaceAll("[.]",
                                                                                   "::"));
    _templateFilesDispatcherImplementation.peek().addMapping("__PORT_NAME__",
                                                             portName);
    _templateFilesDispatcherImplementation.peek()
                                          .addMapping("__PATH_FULL_QUALIFIED_NAME__",
                                                      fullQualifiedName.replaceAll("[.]",
                                                                                   "/"));
    _templateFilesDispatcherImplementation.peek()
                                          .addMapping("__JNI_FULL_QUALIFIED_NAME__",
                                                      fullQualifiedName.replaceAll("[.]",
                                                                                   "_"));

    _templateFilesSocketDispatcherImplementation.peek()
                                                .addMapping("__FULL_QUALIFIED_NAME__",
                                                            fullQualifiedName.replaceAll("[.]",
                                                                                         "::"));
    _templateFilesSocketDispatcherImplementation.peek()
                                                .addMapping("__PORT_NAME__",
                                                            portName);
    _templateFilesSocketDispatcherImplementation.peek()
                                                .addMapping("__PATH_FULL_QUALIFIED_NAME__",
                                                            fullQualifiedName.replaceAll("[.]",
                                                                                         "/"));
    _templateFilesSocketDispatcherImplementation.peek()
                                                .addMapping("__JNI_FULL_QUALIFIED_NAME__",
                                                            fullQualifiedName.replaceAll("[.]",
                                                                                         "_"));

    _templateFilesFortranSocketDispatcher.peek().addMapping("__PORT_NAME__",
                                                            portName);
    _templateFilesFortranSocketDispatcher.peek()
                                         .addMapping("__C_FULL_QUALIFIED_NAME__",
                                                     fullQualifiedName.replaceAll("[.]",
                                                                                  "_")
                                                                      .toLowerCase());
    _templateFilesFortranProxy4SocketDispatcher.peek()
                                               .addMapping("__C_FULL_QUALIFIED_NAME__",
                                                           fullQualifiedName.replaceAll("[.]",
                                                                                        "_")
                                                                            .toLowerCase());
    _templateFilesCProxy4SocketDispatcher.peek()
                                         .addMapping("__C_FULL_QUALIFIED_NAME_4WIN__",
                                                     fullQualifiedName.replaceAll("[.]",
                                                                                  "_")
                                                                      .toUpperCase());

    _templateFilesCProxy4SocketDispatcher.peek()
                                         .addMapping("__C_FULL_QUALIFIED_NAME__",
                                                     fullQualifiedName.replaceAll("[.]",
                                                                                  "_")
                                                                      .toLowerCase());
    _templateFilesCProxy4SocketDispatcher.peek()
                                         .addMapping("__CXX_FULL_QUALIFIED_NAME__",
                                                     fullQualifiedName.replaceAll("[.]",
                                                                                  "::"));
    _templateFilesCProxy4SocketDispatcher.peek()
                                         .addMapping("__PATH_FULL_QUALIFIED_NAME__",
                                                     fullQualifiedName.replaceAll("[.]",
                                                                                  "/"));
  }

  /**
   * @param portName
   * @param fullQualifiedName
   * @param interfaceExtensions
   * @param interfaceExtensionsIncludes
   */
  public void addMappingsInterface(String portName,
                                   String fullQualifiedName,
                                   String interfaceExtensions,
                                   String interfaceExtensionsIncludes) {
    _templateFilesInterface.peek().addMapping("__SUPER_PORTS_INCLUDES__",
                                              interfaceExtensionsIncludes);
    _templateFilesInterface.peek().addMapping("__PORT_NAME__", portName);
    _templateFilesInterface.peek().addMapping("__SUPER_TYPES__",
                                              interfaceExtensions);
    _templateFilesInterface.peek()
                           .addMapping("__INCLUDE_GUARD_FULL_QUALIFIED_NAME__",
                                       fullQualifiedName.replaceAll("[.]", "_")
                                                        .toUpperCase());
    _templateFilesInterface.peek()
                           .addMapping("__FULL_QUALIFIED_NAME__",
                                       fullQualifiedName.replaceAll("[.]", "::"));
  }

  /**
   * @param node
   * @param enums
   */
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
      // }
    }
  }

  @Override
  public void inAInterfacePackageElement(AInterfacePackageElement node) {
    if (!_generateSuperport) {
      _trace.in("inAInterfacePackageElement(...)", "open new port interface");

      String componentName = node.getName().getText();
      String fullyQualifiedComponentName =
          _symbolTable.getScope(node).getFullyQualifiedName(componentName);

      _templateFilesInterface.push(new TemplateFile(Paths.get("cxx-port-interface.template"),
                                                    _cxxDirectoryPath.resolve(fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                     "/") + ".h"),
                                                    _namespace,
                                                    TemplateFile.getLanguageConfigurationForCPP(),
                                                    true));
      _templateFilesDispatcherHeader.push(new TemplateFile(Paths.get("cxx-port-dispatcher-header.template"),
                                                           _cxxDirectoryPath.resolve(fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                            "/") + "NativeDispatcher.h"),
                                                           _namespace,
                                                           TemplateFile.getLanguageConfigurationForCPP(),
                                                           true));
      _templateFilesDispatcherImplementation.push(new TemplateFile(Paths.get("cxx-port-dispatcher-implementation.template"),
                                                                   _cxxDirectoryPath.resolve(fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                                    "/") + "NativeDispatcher.cpp"),
                                                                   _namespace,
                                                                   TemplateFile.getLanguageConfigurationForCPP(),
                                                                   true));
      _templateFilesSocketDispatcherHeader.push(new TemplateFile(Paths.get("cxx-port-socket-dispatcher-header.template"),
                                                                 _cxxDirectoryPath.resolve(fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                                  "/") + "NativeSocketDispatcher.h"),
                                                                 _namespace,
                                                                 TemplateFile.getLanguageConfigurationForCPP(),
                                                                 true));
      _templateFilesSocketDispatcherImplementation.push(new TemplateFile(Paths.get("cxx-port-socket-dispatcher-implementation.template"),
                                                                         _cxxDirectoryPath.resolve(fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                                          "/") + "NativeSocketDispatcher.cpp"),
                                                                         _namespace,
                                                                         TemplateFile.getLanguageConfigurationForCPP(),
                                                                         true));
      _templateFilesFortranSocketDispatcher.push(new TemplateFile(Paths.get("fortran-port-socket-dispatcher-implementation.template"),
                                                                  _fortranDirectoryPath.resolve(fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                                       "/") + "FNativeSocketDispatcher.f90"),
                                                                  _namespace,
                                                                  TemplateFile.getLanguageConfigurationForFortran(),
                                                                  true));
      _templateFilesFortranProxy4SocketDispatcher.push(new TemplateFile(Paths.get("fortran-port-socket-dispatcher-proxy-implementation.template"),
                                                                        _fortranDirectoryPath.resolve(fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                                             "/") + "FProxyNativeSocketDispatcher.f90"),
                                                                        _namespace,
                                                                        TemplateFile.getLanguageConfigurationForFortran(),
                                                                        true));
      _templateFilesCProxy4SocketDispatcher.push(new TemplateFile(Paths.get("c-port-socket-dispatcher-proxy-implementation.template"),
                                                                  _cxxDirectoryPath.resolve(fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                                   "/") + "CProxyNativeSocketDispatcher.cpp"),
                                                                  _namespace,
                                                                  TemplateFile.getLanguageConfigurationForCPP(),
                                                                  true));
      String interfaceExtensions = "";
      String interfaceExtensionsIncludes = "";
      String delim = ": public ";
      for (PUserDefinedType superInterface : node.getSupertype()) {
        String usesTypeName = superInterface.toString().trim();
        interfaceExtensions += delim + usesTypeName.replaceAll(" ", "::");
        interfaceExtensionsIncludes +=
            "#include \"" + usesTypeName.replaceAll(" ", "/") + ".h\"\n";
        delim = ", public ";

      }

      addMappingsInterface(componentName,
                           fullyQualifiedComponentName,
                           interfaceExtensions,
                           interfaceExtensionsIncludes);

      addMappingsHeader(componentName, fullyQualifiedComponentName);
      addMappingsImplementation(componentName, fullyQualifiedComponentName);
      generateEnumIncludes();
      _templateFilesInterface.peek().addMapping("__ENUM_INCLUDES__",
                                                _enumerationIncludes);
      _templateFilesCProxy4SocketDispatcher.peek()
                                           .addMapping("__ENUM_INCLUDES__",
                                                       _enumerationIncludes);
      _templateFilesDispatcherHeader.peek().open();
      _templateFilesDispatcherImplementation.peek().open();
      _templateFilesSocketDispatcherHeader.peek().open();
      _templateFilesSocketDispatcherImplementation.peek().open();
      _templateFilesFortranProxy4SocketDispatcher.peek().open();
      _templateFilesCProxy4SocketDispatcher.peek().open();
      // _templateFilesFortranSocketDispatcher.peek().open();

      _trace.out("inAInterfacePackageElement(...)", "open new port interface");
    }
  }

  /**
   * We create the one operation belonging to this port operation.
   */
  @Override
  public void inAOperation(AOperation node) {
    _trace.in("inAOperation(...)");
    try {
      TemplateFile templateDispatcherHeader =
          new TemplateFile(_templateFilesDispatcherHeader.peek(),
                           Paths.get("cxx-port-native-operation-plain-header.template"));
      TemplateFile templateDispatcherImplementation =
          new TemplateFile(_templateFilesDispatcherImplementation.peek(),
                           Paths.get("cxx-port-native-operation-dispatcher-implementation.template"));
      TemplateFile templateFortranOperation4DispatcherImplementation =
          new TemplateFile(_templateFilesFortranSocketDispatcher.peek(),
                           Paths.get("fortran-port-socket-dispatcher-operation-implementation.template"));
      TemplateFile templateFortranProxyOperation4DispatcherImplementation =
          new TemplateFile(_templateFilesFortranProxy4SocketDispatcher.peek(),
                           Paths.get("fortran-port-socket-dispatcher-proxy-operation-implementation.template"));
      TemplateFile templateCProxyOperation4DispatcherImplementation =
          new TemplateFile(_templateFilesCProxy4SocketDispatcher.peek(),
                           Paths.get("c-port-socket-dispatcher-operation-implementation.template"));
      GetParameterList parameterList =
          new GetParameterList(_symbolTable.getScope(node));
      node.apply(parameterList);
      if (parameterList.hasEnums()) {
        HashSet<String> enums = parameterList.getEnumTypes();
        _enums.addAll(enums);
      }
      ExclusivelyInParameters onlyInParameters = new ExclusivelyInParameters();
      node.apply(onlyInParameters);
      if (!_generateSuperport) {
        TemplateFile templateInterface =
            new TemplateFile(_templateFilesInterface.peek(),
                             Paths.get("cxx-port-operation-interface.template"));

        templateInterface.addMapping("__OPERATION_NAME__", node.getName()
                                                               .getText());
        templateInterface.addMapping("__OPERATION_PARAMETERS_LIST__",
                                     parameterList.getParameterListInCxx());

        _cxxOperationsTemplateFiles.push(templateInterface);
      }
      templateFortranOperation4DispatcherImplementation.addMapping("__OPERATION_NAME__",
                                                                   node.getName()
                                                                       .getText());
      templateFortranProxyOperation4DispatcherImplementation.addMapping("__OPERATION_NAME__",
                                                                        node.getName()
                                                                            .getText());

      templateFortranOperation4DispatcherImplementation.addMapping("__OPERATION_PARAMETERS_LIST__",
                                                                   parameterList.getParameterListInF(true));
      templateFortranOperation4DispatcherImplementation.addMapping("__OPERATION_PARAMETERS_TYPES_LIST_FOR_C__",
                                                                   parameterList.getParameterListTypesForFCBindedToC(false));
      templateFortranOperation4DispatcherImplementation.addMapping("__OPERATION_PARAMETERS_TYPES_LIST__",
                                                                   parameterList.getParameterListTypesForF(true));

      templateFortranProxyOperation4DispatcherImplementation.addMapping("__OPERATION_PARAMETERS_LIST__",
                                                                        parameterList.getParameterListInF(true));
      templateFortranProxyOperation4DispatcherImplementation.addMapping("__OPERATION_PARAMETERS_TYPES_LIST__",
                                                                        parameterList.getParameterListTypesForFCBindedToC(true));

      templateFortranOperation4DispatcherImplementation.addMapping("__FUNCTION_CALL_PARAMETERS_LIST__",
                                                                   parameterList.getFunctionCallListInFClient(true));
      templateFortranOperation4DispatcherImplementation.addMapping("__FUNCTION_CALL_PARAMETERS_LIST_FOR_C__",
                                                                   parameterList.getFunctionCallListInFClient(false));

      templateDispatcherHeader.addMapping("__OPERATION_NAME__", node.getName()
                                                                    .getText());
      templateDispatcherHeader.addMapping("__OPERATION_PARAMETERS_LIST__",
                                          parameterList.getParameterListInCxx());

      templateDispatcherImplementation.addMapping("__OPERATION_NAME__",
                                                  node.getName().getText());
      templateDispatcherImplementation.addMapping("__OPERATION_PARAMETERS_LIST__",
                                                  parameterList.getParameterListInCxx());
      templateDispatcherImplementation.addMapping("__FUNCTION_CALL_PARAMETERS_LIST__",
                                                  parameterList.getFunctionCallListInCxx());
      String parameters = parameterList.getParameterListInF2Cxx();
      if (!parameters.equals("")) {
        parameters = "," + parameters;
      }
      templateCProxyOperation4DispatcherImplementation.addMapping("__PREPARE__STRING_ARGS__",
                                                                  parameterList.convertCharsToString());
      templateCProxyOperation4DispatcherImplementation.addMapping("__OPERATION_NAME__",
                                                                  node.getName()
                                                                      .getText()
                                                                      .toLowerCase());
      templateCProxyOperation4DispatcherImplementation.addMapping("__OPERATION_NAME_4WIN__",
                                                                  node.getName()
                                                                      .getText()
                                                                      .toUpperCase());

      templateCProxyOperation4DispatcherImplementation.addMapping("__CXX_OPERATION_NAME__",
                                                                  node.getName()
                                                                      .getText());
      templateCProxyOperation4DispatcherImplementation.addMapping("__FUNCTION_CALL_PARAMETERS_LIST__",
                                                                  parameterList.getFunctionCallListInF2Cxx());
      templateCProxyOperation4DispatcherImplementation.addMapping("__OPERATION_PARAMETERS_LIST__",
                                                                  parameters);

      _operations += "\tprocedure,public::" + node.getName().getText() + "\n";
      _operations +=
          "\tprocedure,private::" + node.getName().getText() + "_internal\n";
      templateDispatcherHeader.open();
      templateDispatcherHeader.close();

      templateDispatcherImplementation.open();
      templateDispatcherImplementation.close();
      templateFortranProxyOperation4DispatcherImplementation.open();
      templateFortranProxyOperation4DispatcherImplementation.close();
      templateCProxyOperation4DispatcherImplementation.open();
      templateCProxyOperation4DispatcherImplementation.close();
      _fortranOperationsTemplateFiles.add(templateFortranOperation4DispatcherImplementation);
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
    Assert.isTrue(_templateFilesInterface.size() == 1);
    if (!_generateSuperport) {

      _templateFilesFortranSocketDispatcher.peek().addMapping("__OPERATIONS__",
                                                              _operations);

      _templateFilesFortranSocketDispatcher.peek().open();
      _templateFilesInterface.peek().open();

      while (!_cxxOperationsTemplateFiles.isEmpty()) {
        TemplateFile operationTemplate = _cxxOperationsTemplateFiles.peek();
        operationTemplate.open();
        operationTemplate.close();
        _cxxOperationsTemplateFiles.pop();
      }
      while (!_fortranOperationsTemplateFiles.isEmpty()) {
        TemplateFile operationTemplate = _fortranOperationsTemplateFiles.peek();
        operationTemplate.open();
        operationTemplate.close();
        _fortranOperationsTemplateFiles.pop();
      }

      _templateFilesInterface.peek().close();
      _templateFilesDispatcherHeader.peek().close();
      _templateFilesDispatcherImplementation.peek().close();
      _templateFilesSocketDispatcherHeader.peek().close();
      _templateFilesSocketDispatcherImplementation.peek().close();
      _templateFilesFortranSocketDispatcher.peek().close();
      _templateFilesFortranProxy4SocketDispatcher.peek().close();
      _templateFilesCProxy4SocketDispatcher.peek().close();

      _templateFilesInterface.pop();
      _templateFilesDispatcherHeader.pop();
      _templateFilesDispatcherImplementation.pop();
      _templateFilesSocketDispatcherHeader.pop();
      _templateFilesSocketDispatcherImplementation.pop();
      _templateFilesFortranSocketDispatcher.pop();
      _templateFilesFortranProxy4SocketDispatcher.pop();
      _templateFilesCProxy4SocketDispatcher.pop();
    }
  }

}
