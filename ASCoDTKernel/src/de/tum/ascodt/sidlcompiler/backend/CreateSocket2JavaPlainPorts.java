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
import de.tum.ascodt.repository.entities.NativeComponent;
import de.tum.ascodt.sidlcompiler.astproperties.ExclusivelyInParameters;
import de.tum.ascodt.sidlcompiler.astproperties.GetParameterList;
import de.tum.ascodt.sidlcompiler.frontend.analysis.DepthFirstAdapter;
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
public class CreateSocket2JavaPlainPorts extends DepthFirstAdapter {
  private static Trace _trace =
      new Trace(CreateSocket2JavaPlainPorts.class.getCanonicalName());

  private Stack<TemplateFile> _templateJava2Scoket;
  private Stack<TemplateFile> _templateJavaSocket2Socket;
  private Stack<TemplateFile> _templateJavaOperations;
  private Path _javaDirectoryPath;
  private String[] _namespace;

  private SymbolTable _symbolTable;

  private boolean _generateSuperport;

  private String _operationInvokers;
  private HashMap<String, Integer> _operationsMap;

  private String _fullyQualifiedComponentName;

  private String _componentName;

  public CreateSocket2JavaPlainPorts(SymbolTable symbolTable,
                                     Path componentsDirectoryPath,
                                     String[] namespace,
                                     HashMap<String, Integer> operationsMap) {
    _templateJava2Scoket = new Stack<TemplateFile>();
    _templateJavaSocket2Socket = new Stack<TemplateFile>();
    _templateJavaOperations = new Stack<TemplateFile>();
    _javaDirectoryPath = componentsDirectoryPath.resolve("java");
    _namespace = namespace;
    _symbolTable = symbolTable;
    _generateSuperport = false;
    _operationInvokers = "";
    _operationsMap = operationsMap;

  }

  /**
   * @param portName
   * @param fullQualifiedPortName
   */
  public void addMappingsJava(String portName, String fullQualifiedPortName) {
    _templateJava2Scoket.peek().addMapping("__PORT_NAME__", portName);
    _templateJava2Scoket.peek()
                        .addMapping("__NATIVE_COMPONENT__",
                                    NativeComponent.class.getCanonicalName());
    _templateJavaSocket2Socket.peek().addMapping("__PORT_NAME__", portName);
    _templateJavaSocket2Socket.peek()
                              .addMapping("__FULL_QUALIFIED_PORT_NAME__",
                                          fullQualifiedPortName);
    _templateJavaSocket2Socket.peek()
                              .addMapping("__NATIVE_COMPONENT__",
                                          NativeComponent.class.getCanonicalName());

  }

  @Override
  public void inAInterfacePackageElement(AInterfacePackageElement node) {
    _trace.in("inAInterfacePackageElement(...)", "open new port interface");

    if (!_generateSuperport) {
      _componentName = node.getName().getText();
      _fullyQualifiedComponentName =
          _symbolTable.getScope(node).getFullyQualifiedName(_componentName);

      _templateJava2Scoket.push(new TemplateFile(Paths.get("java-port-socket2java-plain-port.template"),
                                                 _javaDirectoryPath.resolve(_fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                    "/") + "Socket2JavaPlainPort.java"),
                                                 _namespace,
                                                 TemplateFile.getLanguageConfigurationForJava(),
                                                 true));
      _templateJavaSocket2Socket.push(new TemplateFile(Paths.get("java-port-socket2socket-plain-port.template"),
                                                       _javaDirectoryPath.resolve(_fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                          "/") + "Socket2SocketPlainPort.java"),
                                                       _namespace,
                                                       TemplateFile.getLanguageConfigurationForJava(),
                                                       true));

      addMappingsJava(_componentName, _fullyQualifiedComponentName);

      _templateJavaSocket2Socket.peek().open();

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

      TemplateFile templateJava =
          new TemplateFile(_templateJava2Scoket.peek(),
                           Paths.get("java-port-socket2java-operation-plain-java-implementation.template"));

      GetParameterList parameterList =
          new GetParameterList(_symbolTable.getScope(node));
      node.apply(parameterList);
      templateJava.addMapping("__SOCKET_PULL__",
                              parameterList.pullInFromSocketForJava());
      templateJava.addMapping("__SOCKET_PUSH__",
                              parameterList.pushOutToSocketFromJava2Cxx());
      templateJava.addMapping("__OPERATION_NAME__", node.getName().getText());

      _operationInvokers +=
          "\t_invokers[" + _operationsMap.get(_fullyQualifiedComponentName + "" +
                                              node.getName().getText()) +
              "]= new " +
              _componentName +
              "SocketInvoker(){\n";
      _operationInvokers +=
          "\t\tpublic void invoke() throws de.tum.ascodt.utils.exceptions.ASCoDTException{\n";
      _operationInvokers +=
          "\t\t\tinvoke_" + node.getName().getText() + "();\n";
      _operationInvokers += "\t\t}\n";
      _operationInvokers += "\t};\n";
      _operationInvokers +=
          "\t_invokers[" + _operationsMap.get(_fullyQualifiedComponentName + "" +
                                              node.getName().getText() +
                                              "Parallel") +
              "]= new " +
              _componentName +
              "SocketInvoker(){\n";
      _operationInvokers +=
          "\t\tpublic void invoke() throws de.tum.ascodt.utils.exceptions.ASCoDTException{\n";
      _operationInvokers +=
          "\t\t\tinvoke_" + node.getName().getText() + "Parallel();\n";
      _operationInvokers += "\t\t}\n";
      _operationInvokers += "\t};\n";
      templateJava.addMapping("__OPERATION_PARAMETERS_LIST__",
                              parameterList.getParameterListInJava(onlyInParameters.areAllParametersInParameters()));
      templateJava.addMapping("__FUNCTION_CALL_PARAMETERS_LIST__",
                              parameterList.getFunctionCallListInJava());

      _templateJavaOperations.add(templateJava);

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
    Assert.isTrue(_templateJava2Scoket.size() == 1);
    Assert.isTrue(_templateJavaSocket2Socket.size() == 1);
    if (!_generateSuperport) {
      _templateJava2Scoket.peek().addMapping("__SET_INVOKERS__",
                                             _operationInvokers);
      _templateJava2Scoket.peek().addMapping("__OPERATIONS__",
                                             "" + 2 + _operationsMap.size());
      _templateJava2Scoket.peek().open();
      while (!_templateJavaOperations.isEmpty()) {
        _templateJavaOperations.peek().open();
        _templateJavaOperations.peek().close();

        _templateJavaOperations.pop();

      }
      _templateJavaSocket2Socket.peek().close();
      _templateJava2Scoket.peek().close();
      _templateJavaSocket2Socket.pop();
      _templateJava2Scoket.pop();
    }
  }

}
