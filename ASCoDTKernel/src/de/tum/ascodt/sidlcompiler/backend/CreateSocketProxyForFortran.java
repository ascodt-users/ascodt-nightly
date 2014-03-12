package de.tum.ascodt.sidlcompiler.backend;


import java.io.File;
import java.net.URL;
import java.util.HashMap;
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


public class CreateSocketProxyForFortran extends DepthFirstAdapter {
  private Trace _trace = new Trace(
      CreateSocketProxyForFortran.class.getCanonicalName());

  // private java.util.Stack< TemplateFile > _templateFilesOfJNIProxyHeader;
  private Stack<TemplateFile> _templateFilesOfC2FProxyImplementation;
  private Stack<TemplateFile> _templateFilesOfFortranProxyImplementation;
  private Stack<TemplateFile> _templateFilesProvidesPorts;
  private Stack<TemplateFile> _templateFilesUsesPortsForC2F;
  private Stack<TemplateFile> _templateFilesUsesPortsForFProxy;

  private Stack<String> _serverInvokers;
  private Stack<String> _clientInvokers;

  // private java.util.Stack< TemplateFile > _templateFilesUsesPorts;

  // private URL _userImplementationsDestinationDirectory;
  private URL _generatedFilesDirectory;
  private String[] _namespace;
  private SymbolTable _symbolTable;
  private String _fullQualifiedName;
  private boolean _generateProvidesMethods;
  private HashMap<String, Integer> _offset_map;

  // private String _providePortName;

  private String _fullQualifiedPortName;

  CreateSocketProxyForFortran(SymbolTable symbolTable,
      URL userImplementationsDestinationDirectory, URL generatedFilesDirectory,
      String[] namespace, HashMap<String, Integer> offset_map) {
    _templateFilesOfC2FProxyImplementation = new Stack<TemplateFile>();
    _templateFilesOfFortranProxyImplementation = new Stack<TemplateFile>();
    _templateFilesProvidesPorts = new Stack<TemplateFile>();
    _templateFilesUsesPortsForC2F = new Stack<TemplateFile>();
    _templateFilesUsesPortsForFProxy = new Stack<TemplateFile>();
    _serverInvokers = new Stack<String>();
    _clientInvokers = new Stack<String>();
    _generatedFilesDirectory = generatedFilesDirectory;
    _namespace = namespace;
    _symbolTable = symbolTable;
    _offset_map = offset_map;

  }

  @Override
  public void inAClassPackageElement(AClassPackageElement node) {
    _trace.in("inAClassPackageElement(...)", "open new port interface");
    try {
      String componentName = node.getName().getText();
      _fullQualifiedName = _symbolTable.getScope(node).getFullyQualifiedName(
          componentName);

      String templateFileForC2FProxyComponentImplemention = "native-component-c2f-socket-implementation.template";
      String templateFileForFortranProxyComponentImplemention = "native-component-fproxy-implementation.template";

      String destinationFileForC2FProxyImplementation = _generatedFilesDirectory
          .toString() +
          File.separatorChar +
          _fullQualifiedName.replaceAll("[.]", "/") + "C2FProxy.cpp";
      String destinationFileForFortranProxyImplementation = _generatedFilesDirectory
          .toString() +
          File.separatorChar +
          _fullQualifiedName.replaceAll("[.]", "/") + "FProxy.f90";

      _templateFilesOfC2FProxyImplementation.push(new TemplateFile(
          templateFileForC2FProxyComponentImplemention,
          destinationFileForC2FProxyImplementation, _namespace, TemplateFile
              .getLanguageConfigurationForJNI(), true));
      //
      _templateFilesOfFortranProxyImplementation.push(new TemplateFile(
          templateFileForFortranProxyComponentImplemention,
          destinationFileForFortranProxyImplementation, _namespace,
          TemplateFile.getLanguageConfigurationForJNI(), true));

      _templateFilesOfC2FProxyImplementation.peek().addMapping(
          "__COMPONENT_NAME__", componentName.toLowerCase());
      _templateFilesOfC2FProxyImplementation.peek().addMapping(
          "__COMPONENT_NAME_4WIN__", componentName.toUpperCase());
      _templateFilesOfC2FProxyImplementation.peek().addMapping(
          "__COMPONENT_NAME_ENV__", componentName.toUpperCase());
      _templateFilesOfFortranProxyImplementation.peek().addMapping(
          "__COMPONENT_NAME__", componentName);
      _templateFilesOfFortranProxyImplementation.peek().addMapping(
          "__FULL_QUALIFIED_NAME__", _fullQualifiedName.replaceAll("[.]", "_"));
      _templateFilesOfFortranProxyImplementation.peek().open();
      // _templateFilesOfC2FProxyImplementation.peek().open();
      _generateProvidesMethods = true;

      for (PUserDefinedType definedType : node.getProvides()) {
        // _clientOperations=_offset_map.get(_symbolTable.getGlobalScope().getInterfaceDefinition(_symbolTable.getScope(definedType).getSymbol(definedType)));
        // _serverOperations=_clientOperations;
        definedType.apply(this);

      }
      _generateProvidesMethods = false;
    } catch (ASCoDTException e) {
      ErrorWriterDevice.getInstance().println(e);
    }

    _trace.out("inAClassPackageElement(...)", "open new port interface");
  }

  @Override
  public void inAOperation(AOperation node) {
    Assert.isTrue(_generateProvidesMethods);
    try {
      _serverInvokers.push("invokers[" +
          _offset_map.get(_fullQualifiedPortName + node.getName().getText()) +
          "]=invoker_" + node.getName().getText() + ";\n");
      _clientInvokers.push("invokers[" +
          _offset_map.get(_fullQualifiedPortName + node.getName().getText()) +
          "]=invoker_" + node.getName().getText() + ";\n");

      String templateC2FProxyImplementationFile = "native-component-c2f-socket-implementation-provides-port.template";
      // String templateJNIProxyImplementationHeaderFile =
      // "native-component-jniproxy-cxx-header-provides-port.template";
      String templateFortranProxyImplementationFile = "native-component-fproxy-implementation-provides-port.template";

      // TemplateFile c2FProxyImplementationHeaderTemplate = new TemplateFile(
      // _templateFilesOfJNIProxyHeader.peek(),
      // templateJNIProxyImplementationHeaderFile );
      TemplateFile c2FProxyImplementationTemplate = new TemplateFile(
          _templateFilesOfC2FProxyImplementation.peek(),
          templateC2FProxyImplementationFile);
      TemplateFile fortranProxyImplementationTemplate = new TemplateFile(
          _templateFilesOfFortranProxyImplementation.peek(),
          templateFortranProxyImplementationFile);

      ExclusivelyInParameters onlyInParameters = new ExclusivelyInParameters();
      node.apply(onlyInParameters);

      GetParameterList parameterList = new GetParameterList(
          _symbolTable.getScope(node));
      node.apply(parameterList);
      c2FProxyImplementationTemplate.addMapping("__SOCKET_PULL__",
          parameterList.pullInFromSocketForCxx());

      c2FProxyImplementationTemplate.addMapping("__SOCKET_PUSH__",
          parameterList.pushOutToSocketForCxx());
      c2FProxyImplementationTemplate.addMapping(
          "__OPERATION_PARAMETERS_LIST__", parameterList
              .getParameterListInJNI(onlyInParameters
                  .areAllParametersInParameters()));
      c2FProxyImplementationTemplate.addMapping("__OPERATION_NAME__", node
          .getName().getText());
      c2FProxyImplementationTemplate.addMapping("__OPERATION_NAME_4WIN__", node
          .getName().getText().toUpperCase());
      c2FProxyImplementationTemplate.addMapping("__F_OPERATION_NAME__", node
          .getName().getText().toLowerCase());

      c2FProxyImplementationTemplate.addMapping("__F_OPERATION_NAME_4WIN__",
          node.getName().getText().toUpperCase());
      c2FProxyImplementationTemplate.addMapping(
          "__OPERATION_PARAMETERS_LIST_C2F__",
          parameterList.getParameterListInC2F());
      String funcCallParamters = parameterList.getFunctionCallListInCxx();
      if (!funcCallParamters.equals("")) {
        funcCallParamters = "," + funcCallParamters;
      }
      c2FProxyImplementationTemplate.addMapping(
          "__FUNCTION_CALL_PARAMETERS_LIST__", funcCallParamters);
      // jniProxyImplementationHeaderTemplate.addMapping("__OPERATION_PARAMETERS_LIST__",parameterList.getParameterListInJNI(onlyInParameters.areAllParametersInParameters())
      // );
      // jniProxyImplementationHeaderTemplate.addMapping(
      // "__JNI_FULL_QUALIFIED_NAME__",_fullQualifiedName.replaceAll("[.]",
      // "_"));
      //
      // jniProxyImplementationTemplate.addMapping("__OPERATION_PARAMETERS_LIST__",parameterList.getParameterListInJNI(onlyInParameters.areAllParametersInParameters())
      // );
      // jniProxyImplementationTemplate.addMapping("__OPERATION_NAME__",
      // node.getName().getText());
      // jniProxyImplementationTemplate.addMapping("__F_OPERATION_NAME__",
      // node.getName().getText().toLowerCase());
      //
      // jniProxyImplementationTemplate.addMapping(
      // "__JNI_FULL_QUALIFIED_NAME__",_fullQualifiedName.replaceAll("[.]",
      // "_"));
      // jniProxyImplementationTemplate.addMapping("__CXX_FULL_QUALIFIED_NAME__",_fullQualifiedName.replaceAll("[.]",
      // "::"));
      // jniProxyImplementationTemplate.addMapping("__START_METHOD_CALL__",parameterList.prepareJNIParametersForCxxCall());
      // jniProxyImplementationTemplate.addMapping("__FUNCTION_CALL_PARAMETERS_LIST__",parameterList.getFunctionCallListInJNI2Cxx());
      // jniProxyImplementationTemplate.addMapping("__END_METHOD_CALL__",
      // parameterList.writeCxxParamatersFromJNIProvideCall());
      // jniProxyImplementationTemplate.addMapping("__OPERATION_PARAMETERS_LIST_C2F__",parameterList.getParameterListInC2F());
      //
      fortranProxyImplementationTemplate.addMapping("__OPERATION_NAME__", node
          .getName().getText());

      fortranProxyImplementationTemplate.addMapping(
          "__OPERATION_PARAMETERS_LIST__", parameterList
              .getParameterListInF(onlyInParameters
                  .areAllParametersInParameters()));

      fortranProxyImplementationTemplate.addMapping(
          "__FUNCTION_CALL_PARAMETERS_LIST__", parameterList
              .getFunctionCallListInFServer().replaceFirst(",", ""));
      fortranProxyImplementationTemplate.addMapping(
          "__PARAMETER_LIST_TYPES_INTENTS__",
          parameterList.getParameterListTypesForFCBindedFromC());
      fortranProxyImplementationTemplate.addMapping("__PARAMETER_LIST_CONV__",
          parameterList.getParameterListC2FConversions());
      // _templateFilesProvidesPorts.add(jniProxyImplementationTemplate);
      // jniProxyImplementationHeaderTemplate.open();
      // jniProxyImplementationHeaderTemplate.close();
      fortranProxyImplementationTemplate.open();
      fortranProxyImplementationTemplate.close();
      _templateFilesProvidesPorts.add(c2FProxyImplementationTemplate);

    } catch (ASCoDTException e) {
      ErrorWriterDevice.getInstance().println(e);
    }
  }

  @Override
  public void inAUserDefinedType(AUserDefinedType node) {
    String fullQualifiedSymbol = Scope.getSymbol(node);
    AInterfacePackageElement interfaceNode = _symbolTable.getScope(node)
        .getInterfaceDefinition(fullQualifiedSymbol);
    String portName = interfaceNode.getName().getText();
    _fullQualifiedPortName = _symbolTable.getScope(interfaceNode)
        .getFullyQualifiedName(portName);
    if (_generateProvidesMethods) {

      // _providePortName =
      // _symbolTable.getScope(interfaceNode).getFullQualifiedName(interfaceNode.getName().getText());
      if (interfaceNode != null) {
        interfaceNode.apply(this);
      }
    }
  }

  @Override
  public void inAUses(AUses node) {
    _trace.in("inAUses(AUses)", node.toString());
    GetProvidesAndUsesPortsOfComponent getPorts = new GetProvidesAndUsesPortsOfComponent();
    node.apply(getPorts);
    String fullQualifiedpPortType = getPorts.getUsesPorts("", ".");
    String portName = node.getAs().getText();
    String portType = fullQualifiedpPortType.substring(fullQualifiedpPortType
        .lastIndexOf(".") + 1);
    String templateFileForC2F = "native-component-c2f-socket-implementation-uses-ports.template";
    String templateFileForFProxy = "native-component-fproxy-implementation-uses-port.template";
    try {
      TemplateFile templateForC2F = new TemplateFile(
          _templateFilesOfC2FProxyImplementation.peek(), templateFileForC2F);
      templateForC2F.addMapping("__USES_PORT_AS__", portName);
      templateForC2F
          .addMapping("__USES_PORT_AS_4WIN__", portName.toUpperCase());
      templateForC2F.addMapping("__USES_PORT_TYPE__", portType);

      TemplateFile templateForFProxy = new TemplateFile(
          _templateFilesOfFortranProxyImplementation.peek(),
          templateFileForFProxy);
      templateForFProxy.addMapping("__USES_PORT_AS__", portName);
      templateForFProxy.addMapping("__USES_PORT_TYPE__",
          portType.replaceAll("\\.", "_"));
      templateForFProxy.addMapping("__FULL_QUALIFIED_USES_PORT_TYPE__",
          fullQualifiedpPortType.replaceAll("\\.", "_").toLowerCase());
      _templateFilesUsesPortsForC2F.push(templateForC2F);
      _templateFilesUsesPortsForFProxy.push(templateForFProxy);
      _serverInvokers.push("invokers[" +
          _offset_map.get(fullQualifiedpPortType + "createPort") +
          "]=invoker_create_client_port_for_" + portName + ";\n");
      _serverInvokers.push("invokers[" +
          _offset_map.get(fullQualifiedpPortType + "connectPort") +
          "]=invoker_connect_client_dispatcher_" + portName + ";\n");
      _serverInvokers.push("invokers[" +
          _offset_map.get(fullQualifiedpPortType + "disconnectPort") +
          "]=invoker_disconnect_client_dispatcher_" + portName + ";\n");
      _clientInvokers.push("invokers[" +
          _offset_map.get(fullQualifiedpPortType + "createPort") +
          "]=invoker_create_client_port_for_" + portName + ";\n");
      _clientInvokers.push("invokers[" +
          _offset_map.get(fullQualifiedpPortType + "connectPort") +
          "]=invoker_connect_client_dispatcher_" + portName + ";\n");
      _clientInvokers.push("invokers[" +
          _offset_map.get(fullQualifiedpPortType + "disconnectPort") +
          "]=invoker_disconnect_client_dispatcher_" + portName + ";\n");
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
    // Assert.isTrue( _templateFilesOfJNIProxyHeader.size()==1 );
    // Assert.isTrue( _templateFilesOfJNIProxyImplementation.size()==1 );
    Assert.isTrue(_templateFilesOfFortranProxyImplementation.size() == 1);
    Assert.isTrue(_templateFilesOfC2FProxyImplementation.size() == 1);
    try {
      // _templateFilesOfJNIProxyHeader.peek().close();
      String serverInvokers = "";
      String clientInvokers = "";
      while (!_serverInvokers.isEmpty()) {
        serverInvokers += _serverInvokers.peek();
        _serverInvokers.pop();
      }
      while (!_clientInvokers.isEmpty()) {
        clientInvokers += _clientInvokers.peek();
        _clientInvokers.pop();
      }
      _templateFilesOfC2FProxyImplementation.peek().addMapping(
          "__SET_SERVER_INVOKERS__", serverInvokers);
      _templateFilesOfC2FProxyImplementation.peek().addMapping(
          "__SET_CLIENT_INVOKERS__", clientInvokers);
      _templateFilesOfC2FProxyImplementation.peek().addMapping(
          "__CLIENT_METHODS__", "" + (2 + _offset_map.size()));
      _templateFilesOfC2FProxyImplementation.peek().addMapping(
          "__SERVER_METHODS__", "" + (2 + _offset_map.size()));
      _templateFilesOfC2FProxyImplementation.peek().open();
      while (!_templateFilesUsesPortsForC2F.isEmpty()) {
        _templateFilesUsesPortsForC2F.peek().open();
        _templateFilesUsesPortsForC2F.peek().close();
        _templateFilesUsesPortsForC2F.pop();
      }
      while (!_templateFilesUsesPortsForFProxy.isEmpty()) {
        _templateFilesUsesPortsForFProxy.peek().open();
        _templateFilesUsesPortsForFProxy.peek().close();
        _templateFilesUsesPortsForFProxy.pop();
      }
      while (!_templateFilesProvidesPorts.isEmpty()) {
        _templateFilesProvidesPorts.peek().open();
        _templateFilesProvidesPorts.peek().close();
        _templateFilesProvidesPorts.pop();
      }

      _templateFilesOfC2FProxyImplementation.peek().close();
      _templateFilesOfFortranProxyImplementation.peek().close();

    } catch (ASCoDTException e) {
      ErrorWriterDevice.getInstance().println(e);
    }
    _templateFilesOfFortranProxyImplementation.pop();
    _templateFilesOfC2FProxyImplementation.pop();
  }
}