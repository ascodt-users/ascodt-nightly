package de.tum.ascodt.sidlcompiler.backend;


import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Stack;

import org.eclipse.core.runtime.Assert;

import de.tum.ascodt.plugin.ui.tabs.SocketClientAppsTab;
import de.tum.ascodt.plugin.ui.views.AppsViewContainer;
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
 * This generator is used to create the java code for native components.
 * 
 * @author Atanas Atanasov
 * 
 */
public class CreateJava2SocketClient extends DepthFirstAdapter {
  private Trace _trace =
      new Trace(CreateJava2SocketClient.class.getCanonicalName());
  private Stack<TemplateFile> _templateFilesForAbstractComponent;
  private Stack<TemplateFile> _templateFilesForJavaBasisImplementation;
  private Stack<TemplateFile> _templateFilesForJavaImplementation;
  private Path _sourcesDirectoryPath;
  private Path _javaDirectoryPath;

  private String[] _namespace;
  private SymbolTable _symbolTable;

  /**
   * Helper
   * 
   * @see inAClassPackageElement()
   */
  private boolean _generateProvidesMethods;
  private String _fullyQualifiedComponentName;
  private HashMap<String, Integer> _operationMap;
  private String _fullQualifiedPortName;
  private String _language;

  CreateJava2SocketClient(SymbolTable symbolTable,
                          Path sourcesDirectoryPath,
                          Path componentsDirectoryPath,
                          String[] namespace,
                          HashMap<String, Integer> operationMap,
                          String language) {
    _templateFilesForAbstractComponent = new Stack<TemplateFile>();
    _templateFilesForJavaBasisImplementation = new Stack<TemplateFile>();
    _templateFilesForJavaImplementation = new Stack<TemplateFile>();
    _sourcesDirectoryPath = sourcesDirectoryPath;
    _javaDirectoryPath = componentsDirectoryPath.resolve("java");
    _namespace = namespace;
    _symbolTable = symbolTable;
    _operationMap = operationMap;
    _language = language;
  }

  /**
   * Tell the asking method the name of the component instantiation that
   * ASCoDT shall instantiate later on.
   * 
   * @return
   */
  public String getFullQualifiedNameOfTheComponentImplementation() {
    return _fullyQualifiedComponentName + "JavaImplementation";
  }

  @Override
  public void inAClassPackageElement(AClassPackageElement node) {
    _trace.in("inAClassPackageElement(...)", "open new port interface");

    String componentName = node.getName().getText();
    _fullyQualifiedComponentName =
        _symbolTable.getScope(node).getFullyQualifiedName(componentName);

    _templateFilesForAbstractComponent.push(new TemplateFile(Paths.get("java-remote-client-component-implementation.template"),
                                                             _javaDirectoryPath.resolve(_fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                                "/") + "AbstractJavaImplementation.java"),
                                                             _namespace,
                                                             TemplateFile.getLanguageConfigurationForJava(),
                                                             true));
    _templateFilesForJavaBasisImplementation.push(new TemplateFile(Paths.get("basis-java-implementation.template"),
                                                                   _sourcesDirectoryPath.resolve(_fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                                         "/") + "BasisJavaImplementation.java"),
                                                                   _namespace,
                                                                   TemplateFile.getLanguageConfigurationForJava(),
                                                                   true));
    _templateFilesForJavaImplementation.push(new TemplateFile(Paths.get("java-component-java-implementation.template"),
                                                              _sourcesDirectoryPath.resolve(_fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                                    "/") + "JavaImplementation.java"),
                                                              _namespace,
                                                              TemplateFile.getLanguageConfigurationForJava(),
                                                              false));
    _templateFilesForAbstractComponent.peek().addMapping("__COMPONENT_NAME__",
                                                         componentName);
    _templateFilesForAbstractComponent.peek()
                                      .addMapping("__FULLY_QUALIFIED_COMPONENT_NAME__",
                                                  _fullyQualifiedComponentName);
    _templateFilesForAbstractComponent.peek()
                                      .addMapping("__SOCKET_CLIENT_UI__",
                                                  SocketClientAppsTab.class.getCanonicalName());
    _templateFilesForAbstractComponent.peek()
                                      .addMapping("__APPS_CONTAINER__",
                                                  AppsViewContainer.class.getCanonicalName());
    _templateFilesForJavaBasisImplementation.peek()
                                            .addMapping("__COMPONENT_NAME__",
                                                        componentName);
    _templateFilesForJavaImplementation.peek().addMapping("__COMPONENT_NAME__",
                                                          componentName);
    _templateFilesForJavaBasisImplementation.peek()
                                            .addMapping("__FULL_QUALIFIED_COMPONENT_NAME__",
                                                        _fullyQualifiedComponentName);

    _templateFilesForAbstractComponent.peek().addMapping("__LANG__", _language);
    _templateFilesForAbstractComponent.peek().open();
    _templateFilesForJavaBasisImplementation.peek().open();
    _templateFilesForJavaImplementation.peek().open();
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
      TemplateFile javaImplementationTemplate =
          new TemplateFile(_templateFilesForAbstractComponent.peek(),
                           Paths.get("java-remote-client-server-component-implementation-provides-port.template"));

      ExclusivelyInParameters onlyInParameters = new ExclusivelyInParameters();
      node.apply(onlyInParameters);

      GetParameterList parameterList =
          new GetParameterList(_symbolTable.getScope(node));
      node.apply(parameterList);

      javaImplementationTemplate.addMapping("__OPERATION_NAME__",
                                            node.getName().getText());
      javaImplementationTemplate.addMapping("__OPERATION_PARAMETERS_LIST__",
                                            parameterList.getParameterListInJava(onlyInParameters.areAllParametersInParameters()));
      javaImplementationTemplate.addMapping("__OPERATION_ID__",
                                            "" + _operationMap.get(_fullQualifiedPortName + node.getName()
                                                                                                .getText()));
      javaImplementationTemplate.addMapping("__SOCKET_PULL__",
                                            parameterList.pullOutFromSocketForJava());
      javaImplementationTemplate.addMapping("__SOCKET_PUSH__",
                                            parameterList.pushInToSocketForJava());
      javaImplementationTemplate.open();
      javaImplementationTemplate.close();

    } catch (ASCoDTException e) {
      ErrorWriterDevice.getInstance().println(e);
    }
  }

  @Override
  public void inAUserDefinedType(AUserDefinedType node) {
    String fullQualifiedSymbol = Scope.getSymbol(node);
    AInterfacePackageElement interfaceNode =
        _symbolTable.getScope(node).getInterfaceDefinition(fullQualifiedSymbol);
    String portName = interfaceNode.getName().getText();
    _fullQualifiedPortName =
        _symbolTable.getScope(interfaceNode).getFullyQualifiedName(portName);
    if (_generateProvidesMethods) {
      if (interfaceNode != null) {
        interfaceNode.apply(this);
      }
    }
  }

  /**
   * For each uses relation, we have to generate all the connection
   * operations.
   */
  @Override
  public void inAUses(AUses node) {
    _trace.in("inAUses(AUses)", node.toString());
    try {
      GetProvidesAndUsesPortsOfComponent getPorts =
          new GetProvidesAndUsesPortsOfComponent();
      node.apply(getPorts);
      ExclusivelyInParameters onlyInParameters = new ExclusivelyInParameters();
      node.apply(onlyInParameters);

      String portType = getPorts.getUsesPorts("", ".");
      String portName = node.getAs().getText();

      TemplateFile template =
          new TemplateFile(_templateFilesForAbstractComponent.peek(),
                           Paths.get("java-remote-client-server-component-implementation-uses-port.template"));
      template.addMapping("__USES_PORT_AS__", portName);
      template.addMapping("__USES_PORT_TYPE__", portType);

      template.addMapping("__CREATE_PORT_ID__",
                          "" + _operationMap.get(portType + "createPort"));
      template.addMapping("__CONNECT_DISPATCHER_PORT_ID__",
                          "" + _operationMap.get(portType + "connectPort"));
      template.addMapping("__DISCONNECT_DISPATCHER_PORT_ID__",
                          "" + _operationMap.get(portType + "disconnectPort"));
      // template.addMapping("__CONNECT_PORT_ID__",""+_operationId++);
      // template.addMapping("__DISCONNECT_PORT_ID__",""+_operationId++);
      template.open();
      template.close();
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
    Assert.isTrue(_templateFilesForAbstractComponent.size() == 1);
    Assert.isTrue(_templateFilesForJavaBasisImplementation.size() == 1);
    Assert.isTrue(_templateFilesForJavaImplementation.size() == 1);

    _templateFilesForAbstractComponent.peek().close();
    _templateFilesForJavaImplementation.peek().close();
    _templateFilesForJavaBasisImplementation.peek().close();
    _templateFilesForAbstractComponent.pop();
    _templateFilesForJavaBasisImplementation.pop();
    _templateFilesForJavaImplementation.pop();
  }
}