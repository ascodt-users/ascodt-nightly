package de.tum.ascodt.sidlcompiler.backend;


import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Stack;

import org.eclipse.core.runtime.Assert;

import de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice;
import de.tum.ascodt.plugin.utils.tracing.Trace;
import de.tum.ascodt.sidlcompiler.frontend.analysis.DepthFirstAdapter;
import de.tum.ascodt.sidlcompiler.frontend.node.AAutoEnumeratorEnumerator;
import de.tum.ascodt.sidlcompiler.frontend.node.AEnumDeclarationPackageElement;
import de.tum.ascodt.sidlcompiler.frontend.node.ASpecificEnumeratorEnumerator;
import de.tum.ascodt.sidlcompiler.symboltable.SymbolTable;
import de.tum.ascodt.utils.TemplateFile;
import de.tum.ascodt.utils.exceptions.ASCoDTException;


public class CreateJavaAndCxxEnumeration extends DepthFirstAdapter {
  private static Trace _trace =
      new Trace(CreateJavaAndCxxEnumeration.class.getCanonicalName());

  private Stack<TemplateFile> _templateFilesForJavaEnums;
  private Stack<TemplateFile> _templateFilesForCxxEnums;
  private Path _javaDirectoryPath;
  private Path _cxxDirectoryPath;
  private String[] _namespace;

  private SymbolTable _symbolTable;

  private boolean _multipleEnumerators;

  private String _constructors;

  private String _defaultConstructor;

  public CreateJavaAndCxxEnumeration(SymbolTable symbolTable,
                                     Path componentsDirectoryPath,
                                     String[] namespace) {
    _templateFilesForJavaEnums = new Stack<TemplateFile>();
    _templateFilesForCxxEnums = new Stack<TemplateFile>();
    _javaDirectoryPath = componentsDirectoryPath.resolve("java");
    _cxxDirectoryPath = componentsDirectoryPath.resolve("c++");
    _namespace = namespace;
    _symbolTable = symbolTable;
    _multipleEnumerators = false;
    _constructors = "";
    _defaultConstructor = "";
  }

  @Override
  public void inAAutoEnumeratorEnumerator(AAutoEnumeratorEnumerator node) {
    _trace.in("inAAutoEnumeratorEnumerator(...)");
    try {
      TemplateFile templateForCxx =
          new TemplateFile(_templateFilesForCxxEnums.peek(),
                           Paths.get("auto-enumerator.template"));
      TemplateFile templateForJava =
          new TemplateFile(_templateFilesForJavaEnums.peek(),
                           Paths.get("auto-enumerator.template"));
      String delim = "";
      if (_multipleEnumerators) {
        delim = ",";
      }
      templateForJava.addMapping("__ENUMERATOR_NAME__", delim + node.getName()
                                                                    .getText());
      templateForCxx.addMapping("__ENUMERATOR_NAME__", delim + node.getName()
                                                                   .getText());
      _constructors += "if(v==" + node.getName().getText() + ".value())\n";
      _constructors += "\treturn " + node.getName().getText() + ";\n";
      _defaultConstructor = "return " + node.getName().getText() + ";\n";
      templateForJava.open();
      templateForJava.close();
      templateForCxx.open();
      templateForCxx.close();
      _multipleEnumerators = true;
    } catch (ASCoDTException e) {
      ErrorWriterDevice.getInstance().println(e);
    }

    _trace.out("inAOperation(...)");
  }

  @Override
  public void inAEnumDeclarationPackageElement(AEnumDeclarationPackageElement node) {
    _trace.in("inAEnumDeclarationPackageElement(...)", "open new enumeration ");

    String componentName = node.getName().getText();
    String fullyQualifiedComponentName =
        _symbolTable.getScope(node).getFullyQualifiedName(componentName);

    _templateFilesForJavaEnums.push(new TemplateFile(Paths.get("java-enumeration.template"),
                                                     _javaDirectoryPath.resolve(fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                       "/") + ".java"),
                                                     _namespace,
                                                     TemplateFile.getLanguageConfigurationForJava(),
                                                     true));
    _templateFilesForCxxEnums.push(new TemplateFile(Paths.get("cxx-enumeration.template"),
                                                    _cxxDirectoryPath.resolve(fullyQualifiedComponentName.replaceAll("[.]",
                                                                                                                     "/") + ".h"),
                                                    _namespace,
                                                    TemplateFile.getLanguageConfigurationForCPP(),
                                                    true));

    _templateFilesForJavaEnums.peek().addMapping("__ENUMERATION_NAME__",
                                                 componentName);
    _templateFilesForJavaEnums.peek().open();
    _templateFilesForCxxEnums.peek().addMapping("__ENUMERATION_NAME__",
                                                componentName);
    _templateFilesForCxxEnums.peek()
                             .addMapping("__INCLUDE_GUARD_FULL_QUALIFIED_NAME__",
                                         fullyQualifiedComponentName.replaceAll("[.]",
                                                                                "_")
                                                                    .toUpperCase());
    _templateFilesForCxxEnums.peek().open();

    _trace.out("inAEnumDeclarationPackageElement(...)",
               "close new enumeration ");
  }

  @Override
  public void inASpecificEnumeratorEnumerator(ASpecificEnumeratorEnumerator node) {
    _trace.in("inAAutoEnumeratorEnumerator(...)");
    try {
      TemplateFile templateForJava =
          new TemplateFile(_templateFilesForJavaEnums.peek(),
                           Paths.get("java-specific-enumerator.template"));

      TemplateFile templateForCxx =
          new TemplateFile(_templateFilesForCxxEnums.peek(),
                           Paths.get("cxx-specific-enumerator.template"));
      String delim = "";
      if (_multipleEnumerators) {
        delim = ",";
      }
      _constructors += "if(v==" + node.getName().getText() + ".value())\n";
      _constructors += "\treturn " + node.getName().getText() + ";\n";
      _defaultConstructor = "return " + node.getName().getText() + ";\n";
      templateForJava.addMapping("__ENUMERATOR_NAME__", delim + node.getName()
                                                                    .getText());
      templateForJava.addMapping("__ENUMERATOR_VALUE__", node.getValue()
                                                             .getText());
      templateForCxx.addMapping("__ENUMERATOR_NAME__", delim + node.getName()
                                                                   .getText());
      templateForCxx.addMapping("__ENUMERATOR_VALUE__", node.getValue()
                                                            .getText());
      templateForJava.open();
      templateForJava.close();
      templateForCxx.open();
      templateForCxx.close();
      _multipleEnumerators = true;
    } catch (ASCoDTException e) {
      ErrorWriterDevice.getInstance().println(e);
    }

    _trace.out("inAOperation(...)");
  }

  @Override
  public void outAEnumDeclarationPackageElement(AEnumDeclarationPackageElement node) {
    Assert.isTrue(_templateFilesForJavaEnums.size() == 1);
    Assert.isTrue(_templateFilesForCxxEnums.size() == 1);

    _templateFilesForJavaEnums.peek().addMapping("__CONSTUCTORS__",
                                                 _constructors);
    _templateFilesForJavaEnums.peek().addMapping("__DEFAULT_CONSTUCTOR__",
                                                 _defaultConstructor);
    _templateFilesForJavaEnums.peek().close();
    _templateFilesForCxxEnums.peek().close();
    _templateFilesForJavaEnums.pop();
    _templateFilesForCxxEnums.pop();

  }

}
