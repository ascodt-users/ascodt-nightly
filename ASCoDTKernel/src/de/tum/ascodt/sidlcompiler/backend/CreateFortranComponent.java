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
 * This generator is used to create the fortran code for native components.
 * 
 * @author Atanas Atanasov
 * 
 */
public class CreateFortranComponent extends DepthFirstAdapter {
  private Trace _trace =
      new Trace(CreateFortranComponent.class.getCanonicalName());

  private Stack<TemplateFile> _templateFilesOfFortranImplementation;
  private Stack<TemplateFile> _templateFilesOfAbstractFortranImplementation;
  private Stack<TemplateFile> _templateFilesForAbstractUsesPorts;
  private Path _sourcesDirectoryPath;
  private Path _fortranDirectoryPath;
  private String[] _namespace;

  private String _fullyQualifiedComponentName;
  private SymbolTable _symbolTable;
  private boolean _generateProvidesMethods;
  private String _provideOperations;
  private String _usesImports;
  private String _usesVariables;
  private Stack<TemplateFile> _subTemplates;

  private String _usesMethods;

  private String _usesVariablesValidity;

  public CreateFortranComponent(SymbolTable symbolTable,
                                Path sourcesDirectoryPath,
                                Path componentsDirectoryPath,
                                String[] namespace) {
    _templateFilesOfFortranImplementation = new Stack<TemplateFile>();
    _templateFilesOfAbstractFortranImplementation = new Stack<TemplateFile>();
    _subTemplates = new Stack<TemplateFile>();
    _templateFilesForAbstractUsesPorts = new Stack<TemplateFile>();
    _sourcesDirectoryPath = sourcesDirectoryPath;
    _fortranDirectoryPath = componentsDirectoryPath.resolve("fortran");
    _namespace = namespace;
    _symbolTable = symbolTable;
    _provideOperations = "";
    _usesImports = "";
    _usesVariables = "";
    _usesMethods = "";
    _usesVariablesValidity = "";

  }

  @Override
  public void inAClassPackageElement(AClassPackageElement node) {
    _trace.in("inAClassPackageElement(...)", "open new port interface");

    String componentName = node.getName().getText();
    _fullyQualifiedComponentName =
        _symbolTable.getScope(node).getFullyQualifiedName(componentName);

    _templateFilesOfFortranImplementation.push(new TemplateFile(Paths.get("native-component-fortran-implementation.template"),
                                                                _sourcesDirectoryPath.resolve(_fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                                      "/") + "Implementation.f90"),
                                                                _namespace,
                                                                TemplateFile.getLanguageConfigurationForFortran(),
                                                                false));
    _templateFilesOfAbstractFortranImplementation.push(new TemplateFile(Paths.get("native-component-fortran-abstract-implementation.template"),
                                                                        _fortranDirectoryPath.resolve(_fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                                              "/") + "AbstractImplementation.f90"),
                                                                        _namespace,
                                                                        TemplateFile.getLanguageConfigurationForFortran(),
                                                                        true));

    _templateFilesOfFortranImplementation.peek()
                                         .addMapping("__FULL_QUALIFIED_NAME__",
                                                     _fullyQualifiedComponentName.replaceAll("\\.",
                                                                                             "_")
                                                                                 .toLowerCase());
    _templateFilesOfFortranImplementation.peek()
                                         .addMapping("__COMPONENT_NAME__",
                                                     componentName);
    _templateFilesOfAbstractFortranImplementation.peek()
                                                 .addMapping("__COMPONENT_NAME__",
                                                             componentName);

    _generateProvidesMethods = true;

    if (node.getProvides().size() > 0) {
      // _templateFilesOfAbstractCXXHeader.peek().addMapping("__IMPLEMENTS__",": public");
      // else
      //
      // _templateFilesOfAbstractCXXHeader.peek().addMapping("__IMPLEMENTS__","");
      for (PUserDefinedType definedType : node.getProvides()) {
        definedType.apply(this);
      }
    }
    _generateProvidesMethods = false;

    _trace.out("inAClassPackageElement(...)", "open new port interface");
  }

  @Override
  public void inAOperation(AOperation node) {
    Assert.isTrue(_generateProvidesMethods);
    try {
      TemplateFile template =
          new TemplateFile(_templateFilesOfFortranImplementation.peek(),
                           Paths.get("native-component-fortran-implementation-provides-port.template"));

      ExclusivelyInParameters onlyInParameters = new ExclusivelyInParameters();
      node.apply(onlyInParameters);

      GetParameterList parameterList =
          new GetParameterList(_symbolTable.getScope(node));
      node.apply(parameterList);
      template.addMapping("__PARAMETER_LIST_TYPES_INTENTS__",
                          parameterList.getParameterListTypesForF(false));
      template.addMapping("__OPERATION_NAME__", node.getName().getText());
      _provideOperations +=
          "procedure,public::" + node.getName().getText() + "\n";
      template.addMapping("__OPERATION_PARAMETERS_LIST__",
                          parameterList.getParameterListInF(onlyInParameters.areAllParametersInParameters()));
      _subTemplates.push(template);

    } catch (ASCoDTException e) {
      ErrorWriterDevice.getInstance().println(e);
    }
  }

  @Override
  public void inAUserDefinedType(AUserDefinedType node) {
    if (_generateProvidesMethods) {
      String fullQualifiedSymbol = Scope.getSymbol(node);
      AInterfacePackageElement interfaceDefintion =
          _symbolTable.getScope(node)
                      .getInterfaceDefinition(fullQualifiedSymbol);
      if (interfaceDefintion != null) {
        interfaceDefintion.apply(this);
      }
    }
  }

  @Override
  public void inAUses(AUses node) {
    _trace.in("inAUses(AUses)", node.toString());
    // try {
    GetProvidesAndUsesPortsOfComponent getPorts =
        new GetProvidesAndUsesPortsOfComponent();
    node.apply(getPorts);
    ExclusivelyInParameters onlyInParameters = new ExclusivelyInParameters();
    node.apply(onlyInParameters);
    String portName = node.getAs().getText();
    String fullQualifiedpPortType = getPorts.getUsesPorts("", ".");
    String portType =
        fullQualifiedpPortType.substring(fullQualifiedpPortType.lastIndexOf(".") + 1);

    _usesImports +=
        "use " + fullQualifiedpPortType.replaceAll("\\.", "_").toLowerCase() +
            "FNativeSocketDispatcher\n";
    _usesVariables +=
        "type(" + portType.replaceAll("\\.", "_") +
            "NativeSocketDispatcher)::" +
            portName +
            "\n";
    _usesVariables += "logical:: v_is_connected_" + portName + "\n";
    _usesMethods +=
        "procedure,public::connect_" + portName.toLowerCase() + "\n";
    _usesMethods +=
        "\tprocedure,public::disconnect_" + portName.toLowerCase() + "\n";
    _usesMethods +=
        "\tprocedure,public::is_connected_" + portName.toLowerCase() + "\n";
    _usesVariablesValidity += ".and.this%v_is_connected_" + portName + "";

    try {
      TemplateFile template =
          new TemplateFile(_templateFilesOfAbstractFortranImplementation.peek(),
                           Paths.get("native-component-fortran-abstract-implementation-uses-port.template"));
      template.addMapping("__FULL_QUALIFIED_USES_PORT_TYPE__",
                          fullQualifiedpPortType.replaceAll("\\.", "_")
                                                .toLowerCase());
      template.addMapping("__USES_PORT_AS__", portName);
      template.addMapping("__USES_PORT_TYPE__", portType.replaceAll("\\.", "_"));
      _templateFilesForAbstractUsesPorts.add(template);
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
    Assert.isTrue(_templateFilesOfFortranImplementation.size() == 1);
    Assert.isTrue(_templateFilesOfAbstractFortranImplementation.size() == 1);

    _templateFilesOfFortranImplementation.peek()
                                         .addMapping("__PROVIDE_PORTS__",
                                                     _provideOperations);
    _templateFilesOfFortranImplementation.peek().open();
    _templateFilesOfAbstractFortranImplementation.peek()
                                                 .addMapping("__USE_PORTS_VARIABLES__",
                                                             _usesVariables);
    _templateFilesOfAbstractFortranImplementation.peek()
                                                 .addMapping("__USE_PORTS_IMPORTS__",
                                                             _usesImports);
    _templateFilesOfAbstractFortranImplementation.peek()
                                                 .addMapping("__USE_PORTS_CONN_METHODS__",
                                                             _usesMethods);
    if (_usesVariablesValidity.equals("")) {
      _usesVariablesValidity = ".True.";
    }
    _templateFilesOfAbstractFortranImplementation.peek()
                                                 .addMapping("__USES_PORTS_VARIABLES_VALIDITY__",
                                                             _usesVariablesValidity.replaceFirst(".and.",
                                                                                                 ""));
    _templateFilesOfAbstractFortranImplementation.peek().open();
    while (!_subTemplates.isEmpty()) {
      _subTemplates.peek().open();
      _subTemplates.peek().close();
      _subTemplates.pop();
    }
    while (!_templateFilesForAbstractUsesPorts.isEmpty()) {
      _templateFilesForAbstractUsesPorts.peek().open();
      _templateFilesForAbstractUsesPorts.peek().close();
      _templateFilesForAbstractUsesPorts.pop();
    }
    _templateFilesOfFortranImplementation.peek().close();
    _templateFilesOfAbstractFortranImplementation.peek().close();
    _templateFilesOfFortranImplementation.pop();
    _templateFilesOfAbstractFortranImplementation.pop();

  }
}