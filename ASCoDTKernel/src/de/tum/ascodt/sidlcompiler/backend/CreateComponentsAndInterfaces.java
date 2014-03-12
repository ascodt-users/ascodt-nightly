package de.tum.ascodt.sidlcompiler.backend;


import java.net.URL;
import java.util.HashMap;

import de.tum.ascodt.plugin.utils.tracing.Trace;
import de.tum.ascodt.repository.Target;
import de.tum.ascodt.sidlcompiler.frontend.node.AClassPackageElement;
import de.tum.ascodt.sidlcompiler.frontend.node.AEnumDeclarationPackageElement;
import de.tum.ascodt.sidlcompiler.frontend.node.AInterfacePackageElement;
import de.tum.ascodt.sidlcompiler.symboltable.SymbolTable;
import de.tum.ascodt.utils.exceptions.ASCoDTException;


/**
 * 
 * 
 * @author Tobias Weinzierl, Atanas Atanasov
 */
public class CreateComponentsAndInterfaces {
  private static Trace _trace = new Trace(
      CreateComponentsAndInterfaces.class.getCanonicalName());

  private SymbolTable _symbolTable;

  public CreateComponentsAndInterfaces(SymbolTable symbolTable) {
    _symbolTable = symbolTable;
  }

  /**
   * Creates all blue prints for given sidl file in specific folder
   * 
   * @param templateDirectory
   *          Should be the URL pointing to de.tum.ascodt.plugin.ui.resources.
   * @param generatedFilesDestinationDirectory
   *          Should be the URL of the Java sources. I'd recommend a directory
   *          ports.
   */
  public void create(URL generatedFilesDestinationDirectory,
      URL userImplementedFilesDestinationDirectory,
      URL nativeDestinationDirectory) {
    _trace.in("create(...)", generatedFilesDestinationDirectory.toString());
    HashMap<String, Integer> offset_map = new HashMap<String, Integer>();
    for (AEnumDeclarationPackageElement enumeration : _symbolTable
        .getGlobalScope().getFlattenedEnumsElements()) {
      CreateJavaAndCxxEnumeration createJavaEnumeration = new CreateJavaAndCxxEnumeration(
          _symbolTable,

          generatedFilesDestinationDirectory, _symbolTable
              .getScope(enumeration).getFullIdentifierOfPackage()

      );
      enumeration.apply(createJavaEnumeration);
    }

    generatePorts(generatedFilesDestinationDirectory, offset_map);
    try {
      for (AClassPackageElement component : _symbolTable.getGlobalScope()
          .getFlattenedClassElements()) {
        CreateSocketComponent socketComponent = new CreateSocketComponent(
            generatedFilesDestinationDirectory, _symbolTable
                .getScope(component).getFullIdentifierOfPackage());
        socketComponent.apply();
        String implementationClassName = "";
        if (component.getTarget() == null ||
            Target.isJavaLocal(component.getTarget().getText())) {
          CreateLocalJavaComponent createJavaComponent = new CreateLocalJavaComponent(
              _symbolTable, generatedFilesDestinationDirectory,
              userImplementedFilesDestinationDirectory, _symbolTable.getScope(
                  component).getFullIdentifierOfPackage());
          component.apply(createJavaComponent);
          implementationClassName = createJavaComponent
              .getFullQualifiedNameOfTheComponentImplementation();
        } else if (component.getTarget() != null &&
            Target.isCxxNative(component.getTarget().getText())) {
          CreateJavaCxxNativeComponent createJavaNativeComponent = new CreateJavaCxxNativeComponent(
              _symbolTable, userImplementedFilesDestinationDirectory,
              generatedFilesDestinationDirectory, nativeDestinationDirectory,
              _symbolTable.getScope(component).getFullIdentifierOfPackage());
          CreateCxxBuildScripts createMakefile = new CreateCxxBuildScripts(
              Target.createTarget(component.getTarget().getText()),
              _symbolTable, userImplementedFilesDestinationDirectory,
              generatedFilesDestinationDirectory, nativeDestinationDirectory,
              _symbolTable.getScope(component).getFullIdentifierOfPackage());
          CreateJNIProxyForCxx createJNIComponent = new CreateJNIProxyForCxx(
              _symbolTable, userImplementedFilesDestinationDirectory,
              generatedFilesDestinationDirectory, _symbolTable.getScope(
                  component).getFullIdentifierOfPackage());
          CreateCxxComponent createCxxComponent = new CreateCxxComponent(
              _symbolTable, userImplementedFilesDestinationDirectory,
              generatedFilesDestinationDirectory, _symbolTable.getScope(
                  component).getFullIdentifierOfPackage());

          component.apply(createJavaNativeComponent);
          component.apply(createJNIComponent);
          component.apply(createCxxComponent);
          component.apply(createMakefile);

          implementationClassName = createJavaNativeComponent
              .getFullQualifiedNameOfTheComponentImplementation();
        } else if (component.getTarget() != null &&
            Target.isFortranNative(component.getTarget().getText())) {
          CreateJavaFortranNativeComponent createJavaNativeComponent = new CreateJavaFortranNativeComponent(
              _symbolTable, userImplementedFilesDestinationDirectory,
              generatedFilesDestinationDirectory, nativeDestinationDirectory,
              _symbolTable.getScope(component).getFullIdentifierOfPackage());
          CreateFortranBuildScripts createMakefile = new CreateFortranBuildScripts(
              Target.createTarget(component.getTarget().getText()),
              _symbolTable, userImplementedFilesDestinationDirectory,
              generatedFilesDestinationDirectory, nativeDestinationDirectory,
              _symbolTable.getScope(component).getFullIdentifierOfPackage());
          CreateJNIProxyForFortran createJNIComponent = new CreateJNIProxyForFortran(
              _symbolTable, userImplementedFilesDestinationDirectory,
              generatedFilesDestinationDirectory, _symbolTable.getScope(
                  component).getFullIdentifierOfPackage());
          CreateFortranComponent createFortranComponent = new CreateFortranComponent(
              _symbolTable, userImplementedFilesDestinationDirectory,
              generatedFilesDestinationDirectory, _symbolTable.getScope(
                  component).getFullIdentifierOfPackage());

          component.apply(createJavaNativeComponent);
          component.apply(createJNIComponent);
          component.apply(createFortranComponent);
          component.apply(createMakefile);
          implementationClassName = createJavaNativeComponent
              .getFullQualifiedNameOfTheComponentImplementation();
        } else if (component.getTarget() != null &&
            Target.isCxxRemoteSocket(component.getTarget().getText())) {
          CreateJava2SocketServer createJave2SocketServer = new CreateJava2SocketServer(
              _symbolTable, userImplementedFilesDestinationDirectory,
              generatedFilesDestinationDirectory, nativeDestinationDirectory,
              _symbolTable.getScope(component).getFullIdentifierOfPackage(),
              offset_map);
          CreateCxxComponent createCxxComponent = new CreateCxxComponent(
              _symbolTable, userImplementedFilesDestinationDirectory,
              generatedFilesDestinationDirectory, _symbolTable.getScope(
                  component).getFullIdentifierOfPackage());
          CreateSocketProxyForCxx createSocketServerProxy = new CreateSocketProxyForCxx(
              _symbolTable, userImplementedFilesDestinationDirectory,
              generatedFilesDestinationDirectory, _symbolTable.getScope(
                  component).getFullIdentifierOfPackage(), offset_map);
          // CreateSocketProxyForCxx createCxxSocketServerComponent = new
          // CreateSocketServerProxyForCxx(
          // _symbolTable,
          // userImplementedFilesDestinationDirectory,
          // generatedFilesDestinationDirectory,
          // _symbolTable.getScope(component).getFullIdentifierOfPackage(),
          // offset_map
          // );
          // component.apply( createCxxSocketServerComponent );
          component.apply(createCxxComponent);
          implementationClassName = "TBD";
        } else if (component.getTarget() != null &&
            Target.isReverseCxxRemoteSocket(component.getTarget().getText())) {
          CreateJava2SocketClient createJave2SocketClient = new CreateJava2SocketClient(
              _symbolTable, userImplementedFilesDestinationDirectory,
              generatedFilesDestinationDirectory, nativeDestinationDirectory,
              _symbolTable.getScope(component).getFullIdentifierOfPackage(),
              offset_map, "Cxx");
          CreateCxxComponent createCxxComponent = new CreateCxxComponent(
              _symbolTable, userImplementedFilesDestinationDirectory,
              generatedFilesDestinationDirectory, _symbolTable.getScope(
                  component).getFullIdentifierOfPackage());
          CreateSocketProxyForCxx createSocketServerProxy = new CreateSocketProxyForCxx(
              _symbolTable, userImplementedFilesDestinationDirectory,
              generatedFilesDestinationDirectory, _symbolTable.getScope(
                  component).getFullIdentifierOfPackage(), offset_map);
          CreateCxxBuildScripts createMakefile = new CreateCxxBuildScripts(
              Target.createTarget(component.getTarget().getText()),
              _symbolTable, userImplementedFilesDestinationDirectory,
              generatedFilesDestinationDirectory, nativeDestinationDirectory,
              _symbolTable.getScope(component).getFullIdentifierOfPackage());
          component.apply(createSocketServerProxy);
          component.apply(createJave2SocketClient);
          component.apply(createCxxComponent);
          component.apply(createMakefile);

        } else if (component.getTarget() != null &&
            Target.isFortranRemoteSocket(component.getTarget().getText())) {
          CreateJava2SocketClient createJave2SocketClient = new CreateJava2SocketClient(
              _symbolTable, userImplementedFilesDestinationDirectory,
              generatedFilesDestinationDirectory, nativeDestinationDirectory,
              _symbolTable.getScope(component).getFullIdentifierOfPackage(),
              offset_map, "Fortran");
          CreateFortranComponent createFortranComponent = new CreateFortranComponent(
              _symbolTable, userImplementedFilesDestinationDirectory,
              generatedFilesDestinationDirectory, _symbolTable.getScope(
                  component).getFullIdentifierOfPackage());
          CreateSocketProxyForFortran createSocketServerProxy = new CreateSocketProxyForFortran(
              _symbolTable, userImplementedFilesDestinationDirectory,
              generatedFilesDestinationDirectory, _symbolTable.getScope(
                  component).getFullIdentifierOfPackage(), offset_map);
          CreateFortranBuildScripts createBuildscripts = new CreateFortranBuildScripts(
              Target.createTarget(component.getTarget().getText()),
              _symbolTable, userImplementedFilesDestinationDirectory,
              generatedFilesDestinationDirectory, nativeDestinationDirectory,
              _symbolTable.getScope(component).getFullIdentifierOfPackage());
          component.apply(createJave2SocketClient);
          component.apply(createSocketServerProxy);
          component.apply(createFortranComponent);
          component.apply(createBuildscripts);
          implementationClassName = "TBD";
        } else if (component.getTarget() != null &&
            Target
                .isReverseFortranRemoteSocket(component.getTarget().getText())) {
          CreateJava2SocketClient createJave2SocketClient = new CreateJava2SocketClient(
              _symbolTable, userImplementedFilesDestinationDirectory,
              generatedFilesDestinationDirectory, nativeDestinationDirectory,
              _symbolTable.getScope(component).getFullIdentifierOfPackage(),
              offset_map, "Fortran");
          CreateFortranComponent createFortranComponent = new CreateFortranComponent(
              _symbolTable, userImplementedFilesDestinationDirectory,
              generatedFilesDestinationDirectory, _symbolTable.getScope(
                  component).getFullIdentifierOfPackage());
          CreateFortranBuildScripts createMakefile = new CreateFortranBuildScripts(
              Target.createTarget(component.getTarget().getText()),
              _symbolTable, userImplementedFilesDestinationDirectory,
              generatedFilesDestinationDirectory, nativeDestinationDirectory,
              _symbolTable.getScope(component).getFullIdentifierOfPackage());
          CreateSocketProxyForFortran createSocketClientProxyF = new CreateSocketProxyForFortran(
              _symbolTable, userImplementedFilesDestinationDirectory,
              generatedFilesDestinationDirectory, _symbolTable.getScope(
                  component).getFullIdentifierOfPackage(), offset_map);
          component.apply(createJave2SocketClient);
          component.apply(createSocketClientProxyF);
          component.apply(createFortranComponent);
          component.apply(createMakefile);
          implementationClassName = createJave2SocketClient
              .getFullQualifiedNameOfTheComponentImplementation();
        }

        CreateJavaComponentInterface createJavaComponentInterface = new CreateJavaComponentInterface(
            _symbolTable, generatedFilesDestinationDirectory, _symbolTable
                .getScope(component).getFullIdentifierOfPackage(),
            implementationClassName, Target.createTarget(component.getTarget()
                .getText()));
        component.apply(createJavaComponentInterface);

      }
    } catch (ASCoDTException aoe) {

    }

    _trace.out("create(...)");
  }

  /**
   * @param generatedFilesDestinationDirectory
   * @param offset_map
   */
  public void generatePorts(URL generatedFilesDestinationDirectory,
      HashMap<String, Integer> offset_map) {
    for (AInterfacePackageElement port : _symbolTable.getGlobalScope()
        .getFlattenedInterfaceElements()) {
      // 1. java interfaces for the ports
      CreateJavaPortInterface createJavaPortInterfaces = new CreateJavaPortInterface(
          _symbolTable, generatedFilesDestinationDirectory, _symbolTable
              .getScope(port).getFullIdentifierOfPackage(), offset_map);
      port.apply(createJavaPortInterfaces);

      // 2. native interfaces for the ports

      CreateNativePortInterface createNativePortInterface = new CreateNativePortInterface(
          _symbolTable, generatedFilesDestinationDirectory, _symbolTable
              .getScope(port).getFullIdentifierOfPackage());
      port.apply(createNativePortInterface);

      // 3. plain java ports
      CreatePlainJavaPorts createPlainJavaPorts = new CreatePlainJavaPorts(
          _symbolTable, generatedFilesDestinationDirectory, _symbolTable
              .getScope(port).getFullIdentifierOfPackage());
      port.apply(createPlainJavaPorts);

      // 4. plain native2java ports
      CreateNative2JavaPlainPorts createPlainNative2JavaPorts = new CreateNative2JavaPlainPorts(
          _symbolTable, generatedFilesDestinationDirectory, _symbolTable
              .getScope(port).getFullIdentifierOfPackage());
      port.apply(createPlainNative2JavaPorts);

      // 5. plain native2native ports

      CreateNative2NativePlainPorts createPlainNative2NativePorts = new CreateNative2NativePlainPorts(
          _symbolTable, generatedFilesDestinationDirectory, _symbolTable
              .getScope(port).getFullIdentifierOfPackage());
      port.apply(createPlainNative2NativePorts);

      // 6. plain native2remote ports
      CreateNative2SocketPlainPorts createPlainNative2SocketClientPorts = new CreateNative2SocketPlainPorts(
          _symbolTable, generatedFilesDestinationDirectory, _symbolTable
              .getScope(port).getFullIdentifierOfPackage(), offset_map);
      port.apply(createPlainNative2SocketClientPorts);

      // 7. plain java2remote ports

      // 8. plain remote2remote ports

      // 9. plain remote2java
      CreateSocket2JavaPlainPorts createPlainSocketClient2JavaPorts = new CreateSocket2JavaPlainPorts(
          _symbolTable, generatedFilesDestinationDirectory, _symbolTable
              .getScope(port).getFullIdentifierOfPackage(), offset_map);
      port.apply(createPlainSocketClient2JavaPorts);

    }
  }
}
