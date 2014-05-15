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
 * This generator is used to create the java code for native components.
 * 
 * @author Atanas Atanasov
 * 
 */
public class CreateJavaCxxNativeComponent extends DepthFirstAdapter {
  private Trace _trace =
      new Trace(CreateJavaCxxNativeComponent.class.getCanonicalName());
  private Stack<TemplateFile> _templateFilesOfAbstractImplementation;
  private Stack<TemplateFile> _templateFilesOfPlainImplementation;
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

  CreateJavaCxxNativeComponent(SymbolTable symbolTable,
                               Path sourcesDirectoryPath,
                               Path componentsDirectoryPath,
                               String[] namespace) {
    _templateFilesOfAbstractImplementation = new Stack<TemplateFile>();
    _templateFilesOfPlainImplementation = new Stack<TemplateFile>();
    _sourcesDirectoryPath = sourcesDirectoryPath;
    _javaDirectoryPath = componentsDirectoryPath.resolve("java");
    _namespace = namespace;
    _symbolTable = symbolTable;
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

    _templateFilesOfAbstractImplementation.push(new TemplateFile(Paths.get("java-cxx-native-component-abstract-java-implementation.template"),
                                                                 _javaDirectoryPath.resolve(_fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                                    "/") + "AbstractJavaNativeImplementation.java"),
                                                                 _namespace,
                                                                 TemplateFile.getLanguageConfigurationForJava(),
                                                                 true));
    _templateFilesOfPlainImplementation.push(new TemplateFile(Paths.get("java-native-component-java-implementation.template"),
                                                              _sourcesDirectoryPath.resolve(_fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                                    "/") + "JavaImplementation.java"),
                                                              _namespace,
                                                              TemplateFile.getLanguageConfigurationForJava(),
                                                              false));

    _templateFilesOfAbstractImplementation.peek()
                                          .addMapping("__COMPONENT_NAME__",
                                                      componentName);
    _templateFilesOfAbstractImplementation.peek()
                                          .addMapping("__FULLY_QUALIFIED_COMPONENT_NAME__",
                                                      _fullyQualifiedComponentName);
    _templateFilesOfPlainImplementation.peek().addMapping("__COMPONENT_NAME__",
                                                          componentName);
    _templateFilesOfAbstractImplementation.peek().open();
    _templateFilesOfPlainImplementation.peek().open();

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
          new TemplateFile(_templateFilesOfAbstractImplementation.peek(),
                           Paths.get("java-cxx-native-component-java-implementation-provides-port.template"));

      ExclusivelyInParameters onlyInParameters = new ExclusivelyInParameters();
      node.apply(onlyInParameters);

      GetParameterList parameterList =
          new GetParameterList(_symbolTable.getScope(node));
      node.apply(parameterList);

      javaImplementationTemplate.addMapping("__OPERATION_NAME__",
                                            node.getName().getText());
      if (parameterList.size() > 0) {
        javaImplementationTemplate.addMapping("__SEPARATOR__", ",");
      } else {
        javaImplementationTemplate.addMapping("__SEPARATOR__", "");
      }
      javaImplementationTemplate.addMapping("__OPERATION_PARAMETERS_LIST__",
                                            parameterList.getParameterListInJava(onlyInParameters.areAllParametersInParameters()));
      javaImplementationTemplate.addMapping("__JNI_OPERATION_PARAMETERS_LIST__",
                                            parameterList.getParameterListInJavaWithIntEnums(onlyInParameters.areAllParametersInParameters()));
      javaImplementationTemplate.addMapping("__PREPARE_ENUMS__",
                                            parameterList.prepareJavaEnumParametersForJava2JNICall());
      javaImplementationTemplate.addMapping("__JNI_FUNCTION_CALL_PARAMETERS_LIST__",
                                            parameterList.getFunctionCallListInJava2JNI());
      javaImplementationTemplate.addMapping("__WRITE_ENUMS__",
                                            parameterList.writeJavaEnumParametersAfterJava2JNICall());
      javaImplementationTemplate.open();
      javaImplementationTemplate.close();
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
          new TemplateFile(_templateFilesOfAbstractImplementation.peek(),
                           Paths.get("java-cxx-native-component-abstract-java-implementation-uses-port.template"));
      template.addMapping("__USES_PORT_AS__", portName);
      template.addMapping("__USES_PORT_TYPE__", portType);

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
    Assert.isTrue(_templateFilesOfAbstractImplementation.size() == 1);

    _templateFilesOfAbstractImplementation.peek().close();
    _templateFilesOfPlainImplementation.peek().close();
    _templateFilesOfAbstractImplementation.pop();
    _templateFilesOfPlainImplementation.pop();
  }
}
