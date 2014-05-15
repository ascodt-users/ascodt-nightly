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
 * @author Tobias Weinzierl
 */
public class CreateJavaPortInterface extends DepthFirstAdapter {
  private static Trace _trace =
      new Trace(CreateJavaPortInterface.class.getCanonicalName());

  private Stack<TemplateFile> _templateInterfaceFiles;
  private Stack<TemplateFile> _templateDispatcherFiles;
  private Stack<TemplateFile> _templateDispatcherNativeFiles;
  private Stack<TemplateFile> _templateDispatcherSocketFiles;
  private Path _javaDirectoryPath;
  private String[] _namespace;

  private SymbolTable _symbolTable;
  private HashMap<String, Integer> _portsHashmap;
  private boolean _generateSuperPort;

  private String _fullyQualifiedComponentName;

  public CreateJavaPortInterface(SymbolTable symbolTable,
                                 Path componentsDirectoryPath,
                                 String[] namespace,
                                 HashMap<String, Integer> portsHashmap) {
    _templateInterfaceFiles = new Stack<TemplateFile>();
    _templateDispatcherFiles = new Stack<TemplateFile>();
    _templateDispatcherNativeFiles = new Stack<TemplateFile>();
    _templateDispatcherSocketFiles = new Stack<TemplateFile>();
    _javaDirectoryPath = componentsDirectoryPath.resolve("java");
    _namespace = namespace;
    _symbolTable = symbolTable;
    _portsHashmap = portsHashmap;
    _generateSuperPort = false;
  }

  @Override
  public void inAInterfacePackageElement(AInterfacePackageElement node) {
    _trace.in("inAInterfacePackageElement(...)", "open new port interface");

    if (!_generateSuperPort) {
      String componentName = node.getName().getText();
      _fullyQualifiedComponentName =
          _symbolTable.getScope(node).getFullyQualifiedName(componentName);

      _portsHashmap.put(_fullyQualifiedComponentName + "createPort",
                        2 + _portsHashmap.size());
      _portsHashmap.put(_fullyQualifiedComponentName + "connectPort",
                        2 + _portsHashmap.size());
      _portsHashmap.put(_fullyQualifiedComponentName + "disconnectPort",
                        2 + _portsHashmap.size());

      _templateInterfaceFiles.push(new TemplateFile(Paths.get("java-port-interface.template"),
                                                    _javaDirectoryPath.resolve(_fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                       "/") + ".java"),
                                                    _namespace,
                                                    TemplateFile.getLanguageConfigurationForJava(),
                                                    true));
      _templateDispatcherFiles.push(new TemplateFile(Paths.get("java-port-dispatcher.template"),
                                                     _javaDirectoryPath.resolve(_fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                        "/") + "Dispatcher.java"),
                                                     _namespace,
                                                     TemplateFile.getLanguageConfigurationForJava(),
                                                     true));
      _templateDispatcherNativeFiles.push(new TemplateFile(Paths.get("java-port-dispatcher-native.template"),
                                                           _javaDirectoryPath.resolve(_fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                              "/") + "NativeDispatcher.java"),
                                                           _namespace,
                                                           TemplateFile.getLanguageConfigurationForJava(),
                                                           true));
      _templateDispatcherSocketFiles.push(new TemplateFile(Paths.get("java-port-dispatcher-socket.template"),
                                                           _javaDirectoryPath.resolve(_fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                              "/") + "SocketDispatcher.java"),
                                                           _namespace,
                                                           TemplateFile.getLanguageConfigurationForJava(),
                                                           true));
      TemplateFile templateAbstractPort =
          new TemplateFile(Paths.get("java-port-abstract-port.template"),
                           _javaDirectoryPath.resolve(_fullyQualifiedComponentName.replaceAll("[.]",
                                                                                              "/") + "AbstractPort.java"),
                           _namespace,
                           TemplateFile.getLanguageConfigurationForJava(),
                           true);
      TemplateFile templateAbstractSocketPort =
          new TemplateFile(Paths.get("java-port-abstract-socket-port.template"),
                           _javaDirectoryPath.resolve(_fullyQualifiedComponentName.replaceAll("[.]",
                                                                                              "/") + "AbstractSocketPort.java"),
                           _namespace,
                           TemplateFile.getLanguageConfigurationForJava(),
                           true);
      TemplateFile templateSocketPort =
          new TemplateFile(Paths.get("java-port-socket-port.template"),
                           _javaDirectoryPath.resolve(_fullyQualifiedComponentName.replaceAll("[.]",
                                                                                              "/") + "SocketPort.java"),
                           _namespace,
                           TemplateFile.getLanguageConfigurationForJava(),
                           true);

      _templateInterfaceFiles.peek().addMapping("__PORT_NAME__", componentName);
      _templateDispatcherFiles.peek()
                              .addMapping("__PORT_NAME__", componentName);
      _templateDispatcherNativeFiles.peek().addMapping("__PORT_NAME__",
                                                       componentName);
      _templateDispatcherSocketFiles.peek().addMapping("__PORT_NAME__",
                                                       componentName);
      String interfaceExtensions = "";
      String delim = "extends ";
      for (PUserDefinedType superInterface : node.getSupertype()) {
        String usesTypeName = superInterface.toString().trim();
        usesTypeName = usesTypeName.replace(' ', '.');
        interfaceExtensions += delim + usesTypeName;
        delim = ",";

      }
      templateAbstractPort.addMapping("__PORT_NAME__", componentName);
      templateSocketPort.addMapping("__PORT_NAME__", componentName);
      templateAbstractSocketPort.addMapping("__PORT_NAME__", componentName);
      _templateInterfaceFiles.peek().addMapping("__SUPER_TYPES__",
                                                interfaceExtensions);
      templateAbstractPort.open();
      templateAbstractPort.close();
      templateSocketPort.open();
      templateSocketPort.close();
      templateAbstractSocketPort.open();
      templateAbstractSocketPort.close();
      _templateInterfaceFiles.peek().open();
      _templateDispatcherFiles.peek().open();
      _templateDispatcherNativeFiles.peek().open();
      _templateDispatcherSocketFiles.peek().open();
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
      TemplateFile template =
          new TemplateFile(_templateInterfaceFiles.peek(),
                           Paths.get("java-port-operation-interface.template"));

      TemplateFile templateDispatcherOpertion =
          new TemplateFile(_templateDispatcherFiles.peek(),
                           Paths.get("java-port-dispatcher-operation.template"));

      GetParameterList parameterList =
          new GetParameterList(_symbolTable.getScope(node));
      node.apply(parameterList);

      ExclusivelyInParameters onlyInParameters = new ExclusivelyInParameters();
      node.apply(onlyInParameters);
      _portsHashmap.put(_fullyQualifiedComponentName + node.getName().getText(),
                        2 + _portsHashmap.size());
      _portsHashmap.put(_fullyQualifiedComponentName + node.getName().getText() +
                            "Parallel",
                        2 + _portsHashmap.size());

      template.addMapping("__OPERATION_NAME__", node.getName().getText());
      template.addMapping("__OPERATION_PARAMETERS_LIST__",
                          parameterList.getParameterListInJava(onlyInParameters.areAllParametersInParameters()));
      templateDispatcherOpertion.addMapping("__OPERATION_NAME__",
                                            node.getName().getText());
      templateDispatcherOpertion.addMapping("__OPERATION_PARAMETERS_LIST__",
                                            parameterList.getParameterListInJava(onlyInParameters.areAllParametersInParameters()));
      templateDispatcherOpertion.addMapping("__FUNCTION_CALL_PARAMETERS_LIST__",
                                            parameterList.getFunctionCallListInJava());
      templateDispatcherOpertion.addMapping("__INT_ENUM_OPERATION_PARAMETERS_LIST__",
                                            parameterList.getParameterListInJavaWithIntEnums(onlyInParameters.areAllParametersInParameters()));
      templateDispatcherOpertion.addMapping("__INT_ENUM_FUNCTION_CALL_PARAMETERS_LIST__",
                                            parameterList.getFunctionCallListInJNI2Java());
      templateDispatcherOpertion.addMapping("__PREPARE_ENUMS__",
                                            parameterList.prepareJavaEnumParametersForJNI2JavaCall());
      templateDispatcherOpertion.addMapping("__WRITE_ENUMS__",
                                            parameterList.writeJavaEnumParametersAfterJNI2JavaCall());

      template.open();
      template.close();
      templateDispatcherOpertion.open();
      templateDispatcherOpertion.close();
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
      _generateSuperPort = true;
      interfaceDefintion.apply(this);
      _generateSuperPort = false;
    }
  }

  @Override
  public void outAInterfacePackageElement(AInterfacePackageElement node) {
    Assert.isTrue(_templateInterfaceFiles.size() == 1);
    if (!_generateSuperPort) {
      _templateInterfaceFiles.peek().close();
      _templateDispatcherFiles.peek().close();
      _templateDispatcherNativeFiles.peek().close();
      _templateDispatcherSocketFiles.peek().close();
      _templateDispatcherFiles.pop();
      _templateInterfaceFiles.pop();
      _templateDispatcherNativeFiles.pop();
      _templateDispatcherSocketFiles.pop();
    }
  }

}
