package de.tum.ascodt.sidlcompiler.backend;


import java.nio.file.Path;
import java.nio.file.Paths;
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
public class CreatePlainJavaPorts extends DepthFirstAdapter {
  private static Trace _trace =
      new Trace(CreatePlainJavaPorts.class.getCanonicalName());

  private Stack<TemplateFile> _templateFiles;
  private Path _javaDirectoryPath;
  private String[] _namespace;

  private SymbolTable _symbolTable;
  private boolean _generateSuperport;

  public CreatePlainJavaPorts(SymbolTable symbolTable,
                              Path componentsDirectoryPath,
                              String[] namespace) {
    _templateFiles = new Stack<TemplateFile>();
    _javaDirectoryPath = componentsDirectoryPath.resolve("java");
    _namespace = namespace;
    _symbolTable = symbolTable;
    _generateSuperport = false;
  }

  @Override
  public void inAInterfacePackageElement(AInterfacePackageElement node) {
    _trace.in("inAInterfacePackageElement(...)", "open new port interface");

    if (!_generateSuperport) {
      String componentName = node.getName().getText();
      String fullyQualifiedComponentName =
          _symbolTable.getScope(node).getFullyQualifiedName(componentName);

      _templateFiles.push(new TemplateFile(Paths.get("java-port-plain-port.template"),
                                           _javaDirectoryPath.resolve(fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                             "/") + "PlainJavaPort.java"),
                                           _namespace,
                                           TemplateFile.getLanguageConfigurationForJava(),
                                           true));

      _templateFiles.peek().addMapping("__PORT_NAME__", componentName);
      _templateFiles.peek().open();
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

      TemplateFile template =
          new TemplateFile(_templateFiles.peek(),
                           Paths.get("java-port-operation-plain-java-implementation.template"));

      GetParameterList parameterList =
          new GetParameterList(_symbolTable.getScope(node));
      node.apply(parameterList);

      template.addMapping("__OPERATION_NAME__", node.getName().getText());
      template.addMapping("__OPERATION_PARAMETERS_LIST__",
                          parameterList.getParameterListInJava(onlyInParameters.areAllParametersInParameters()));
      template.addMapping("__FUNCTION_CALL_PARAMETERS_LIST__",
                          parameterList.getFunctionCallListInJava());

      template.open();
      template.close();
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
    Assert.isTrue(_templateFiles.size() == 1);
    if (!_generateSuperport) {

      _templateFiles.peek().close();
      _templateFiles.pop();
    }
  }
}