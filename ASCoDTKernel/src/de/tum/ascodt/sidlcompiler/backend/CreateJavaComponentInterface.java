package de.tum.ascodt.sidlcompiler.backend;


import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Stack;

import org.eclipse.core.runtime.Assert;

import de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice;
import de.tum.ascodt.plugin.utils.tracing.Trace;
import de.tum.ascodt.repository.Target;
import de.tum.ascodt.repository.entities.Component;
import de.tum.ascodt.repository.entities.CxxReverseRemoteSocketComponent;
import de.tum.ascodt.repository.entities.NativeComponent;
import de.tum.ascodt.sidlcompiler.astproperties.GetProvidesAndUsesPortsOfComponent;
import de.tum.ascodt.sidlcompiler.frontend.analysis.DepthFirstAdapter;
import de.tum.ascodt.sidlcompiler.frontend.node.AClassPackageElement;
import de.tum.ascodt.sidlcompiler.frontend.node.AUses;
import de.tum.ascodt.sidlcompiler.symboltable.SymbolTable;
import de.tum.ascodt.utils.TemplateFile;
import de.tum.ascodt.utils.exceptions.ASCoDTException;


/**
 * This class creates the base class for all components of a given type.
 * 
 * There might be multiple component implementations, i.e. multiple variants of
 * a component with different targets. They have in common one base class in
 * Java that acts as a proxy to the real implementation. This class creates this
 * common base class with all its abstract files.
 * 
 * @author Tobias Weinzierl
 */
public class CreateJavaComponentInterface extends DepthFirstAdapter {
  private static Trace _trace =
      new Trace(CreateJavaComponentInterface.class.getCanonicalName());

  private Stack<TemplateFile> _templateFiles;
  private Path _javaDirectoryPath;
  private String[] _namespace;
  private String _fullQualifiedNameOfTheComponentImplementation;
  private SymbolTable _symbolTable;
  private Target _target;

  public CreateJavaComponentInterface(SymbolTable symbolTable,
                                      Path componentsDirectoryPath,
                                      String[] namespace,
                                      String fullQualifiedNameOfTheComponentImplementation,
                                      Target target) {
    _templateFiles = new Stack<TemplateFile>();
    _javaDirectoryPath = componentsDirectoryPath.resolve("java");
    _namespace = namespace;
    _symbolTable = symbolTable;
    _target = target;
    _fullQualifiedNameOfTheComponentImplementation =
        fullQualifiedNameOfTheComponentImplementation;
  }

  /**
   * This is the major plug-in point. We opne a new template file and
   * imediately push it on the file writer stack. This stack has been
   * empty before. When we leave the class package again, this file
   * writer is to be closed. To find out which provides ports are
   * implemented, we have to use GetProvidesAndUsesPorts on node. To
   * find out what the actual implementation file is, we
   */
  @Override
  public void inAClassPackageElement(AClassPackageElement node) {
    _trace.in("inAClassPackageElement(...)", node.toString());

    String componentName = node.getName().getText();
    String fullyQualifiedComponentName =
        _symbolTable.getScope(node).getFullyQualifiedName(componentName);

    _templateFiles.push(new TemplateFile(Paths.get("java-component-interface.template"),
                                         _javaDirectoryPath.resolve(fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                           "/") + ".java"),
                                         _namespace,
                                         TemplateFile.getLanguageConfigurationForJava(),
                                         true));

    _templateFiles.peek().addMapping("__COMPONENT_NAME__", componentName);
    _templateFiles.peek()
                  .addMapping("__FULL_QUALIFIED_PATH_OF_IMPLEMENTATION_FILE__",
                              _fullQualifiedNameOfTheComponentImplementation);

    GetProvidesAndUsesPortsOfComponent getPorts =
        new GetProvidesAndUsesPortsOfComponent();
    node.apply(getPorts);

    String extendingInterfaces = getPorts.getProvidesPorts(",", ".");
    if (!extendingInterfaces.equals("")) {
      extendingInterfaces += ",";
    }
    switch (_target.getType()) {
    case JavaLocal:
      extendingInterfaces += Component.class.getCanonicalName();
      break;
    case JavaNative:
      extendingInterfaces += NativeComponent.class.getCanonicalName();
      break;
    case CxxRemoteSocket:
      extendingInterfaces +=
          CxxReverseRemoteSocketComponent.class.getCanonicalName();
      break;
    default:
      extendingInterfaces += Component.class.getCanonicalName();
      break;
    }

    _templateFiles.peek()
                  .addMapping("__LIST_OF_PROVIDES_INTERFACES_AND_STANDARD_COMPONENT_INTERFACE__",
                              extendingInterfaces);
    _templateFiles.peek().open();

    _trace.out("inAClassPackageElement(...)");
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

      String portType = getPorts.getUsesPorts("", ".");
      String portName = node.getAs().getText();

      TemplateFile template =
          new TemplateFile(_templateFiles.peek(),
                           Paths.get("java-component-interface-uses-port.template"));

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
   * Close output streams.
   */
  @Override
  public void outAClassPackageElement(AClassPackageElement node) {
    Assert.isTrue(_templateFiles.size() == 1);

    _templateFiles.peek().close();
    _templateFiles.pop();
  }

}
