package de.tum.ascodt.plugin.project.builders;


import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PushbackReader;
import java.net.MalformedURLException;
import java.util.Vector;

import org.eclipse.core.resources.IFile;
import org.eclipse.core.resources.IFolder;
import org.eclipse.core.resources.IProject;
import org.eclipse.core.resources.IResource;
import org.eclipse.core.runtime.CoreException;

import de.tum.ascodt.plugin.project.Project;
import de.tum.ascodt.plugin.project.ProjectBuilder;
import de.tum.ascodt.plugin.utils.tracing.Trace;
import de.tum.ascodt.sidlcompiler.backend.CreateComponentsAndInterfaces;
import de.tum.ascodt.sidlcompiler.backend.CreateGlobalBuildScripts;
import de.tum.ascodt.sidlcompiler.frontend.lexer.Lexer;
import de.tum.ascodt.sidlcompiler.frontend.lexer.LexerException;
import de.tum.ascodt.sidlcompiler.frontend.node.Start;
import de.tum.ascodt.sidlcompiler.frontend.parser.Parser;
import de.tum.ascodt.sidlcompiler.frontend.parser.ParserException;
import de.tum.ascodt.sidlcompiler.symboltable.ASTValidator;
import de.tum.ascodt.sidlcompiler.symboltable.BuildSymbolTable;
import de.tum.ascodt.sidlcompiler.symboltable.SymbolTable;
import de.tum.ascodt.utils.exceptions.ASCoDTException;


/**
 * The project builder has the task to invoke the sidl compiler when the sidl
 * resources are changed
 * 
 * @author atanasoa
 * 
 */
public class SiDLBuilder {
  public static String ID = SiDLBuilder.class.getCanonicalName();

  /**
   * Compile an added or modified resource file. We start by parsing the
   * corresponding sidl file and filling
   * up the parsed entries in the project symbol table. After this step we make
   * sure that there are no conflicts
   * in the table through the ast validator. Then we can start with the
   * generation of the java/c++ source files
   * using CreateComponentsAndInterfaces class. The newly generated source files
   * are added unter <project>/<components>/<target-language>
   * folder
   * 
   * @param resourceLocation
   *          the resource file to be compiled
   * @param eclipseProject
   *          handle of the eclipse project
   * @throws ASCoDTException
   */
  public static Start buildStartSymbolsForSIDLResource(InputStream stream)
      throws ASCoDTException {
    Start result = null;
    try {
      InputStreamReader fileReader = new InputStreamReader(stream);
      Parser parser = new Parser(new Lexer(new PushbackReader(fileReader)));
      result = parser.parse();

    } catch (ParserException e) {
      throw new ASCoDTException(SiDLBuilder.class.getName(),
          "buildComponentsAndInterfaces()", e.getMessage(), e);
    } catch (LexerException e) {
      throw new ASCoDTException(SiDLBuilder.class.getName(),
          "buildComponentsAndInterfaces()", e.getMessage(), e);
    } catch (IOException e) {
      throw new ASCoDTException(SiDLBuilder.class.getName(),
          "buildComponentsAndInterfaces()", e.getMessage(), e);
    }
    return result;
  }

  /**
   * Compile an added or modified resource file. We start by parsing the
   * corresponding sidl file and filling
   * up the parsed entries in the project symbol table. After this step we make
   * sure that there are no conflicts
   * in the table through the ast validator. Then we can start with the
   * generation of the java/c++ source files
   * using CreateComponentsAndInterfaces class. The newly generated source files
   * are added unter <project>/<components>/<target-language>
   * folder
   * 
   * @param resourceLocation
   *          the resource file to be compiled
   * @param eclipseProject
   *          handle of the eclipse project
   * @throws ASCoDTException
   */
  public static Start buildStartSymbolsForSIDLResource(String resourceLocation)
      throws ASCoDTException {
    try {
      return buildStartSymbolsForSIDLResource(new FileInputStream(
          resourceLocation));
    } catch (FileNotFoundException e) {
      throw new ASCoDTException(SiDLBuilder.class.getName(),
          "buildComponentsAndInterfaces()", e.getMessage(), e);
    }
  }

  /**
   * build all project sidl files in given folder
   * 
   * @param startSymbolsMap
   *          a hash map for stroring resources startsymbols
   * @throws ASCoDTException
   */
  public static void buildStartSymbolsForSIDLResources(
      Vector<SIDLPair<String, Start>> startSymbolsMap, IResource resource)
          throws ASCoDTException {

    try {
      if (resource instanceof IFolder) {
        Vector<IResource> files = new Vector<IResource>();
        for (IResource child : ((IFolder)resource).members()) {
          if (child instanceof IFile) {
            files.add(child);
          } else {
            buildStartSymbolsForSIDLResources(startSymbolsMap, child);
          }

        }
        for (IResource file : files) {
          buildStartSymbolsForSIDLResources(startSymbolsMap, file);
        }

      } else if (resource instanceof IFile &&
          resource.getName().contains(".sidl")) {
        startSymbolsMap.add(new SIDLPair<String, Start>(resource.getLocation()
            .toPortableString(),
            de.tum.ascodt.plugin.project.builders.SiDLBuilder
            .buildStartSymbolsForSIDLResource(resource.getLocation()
                .toPortableString())));
      }

    } catch (CoreException e) {
      throw new ASCoDTException(SiDLBuilder.class.getName(),
          "buildProjectSources()", "building sidl files failed", e);
    }
  }

  public static void extendSymbolTable(Start startNode,
      SymbolTable symbolTable, String resourceLocation) {

    BuildSymbolTable symbolTableBuilderForResource = new BuildSymbolTable(
        symbolTable, resourceLocation);
    startNode.apply(symbolTableBuilderForResource);

  }

  /**
   * Executes the ascodt compiler to generate the blueprints for given symbol
   * table
   * 
   * @param eclipseProject
   *          the current eclipse project
   * @throws ASCoDTException
   */
  public static void generateBlueprints(IProject eclipseProject)
      throws ASCoDTException {
    Project project = ProjectBuilder.getInstance().getProject(eclipseProject);
    assert project.getSymbolTable() != null;

    CreateComponentsAndInterfaces interfaces = new CreateComponentsAndInterfaces(
        project.getSymbolTable());

    try {
      interfaces.create(

          new File(eclipseProject.getLocation().toPortableString() +
              project.getJavaProxiesFolder()).toURI().toURL(),
              new File(eclipseProject.getLocation().toPortableString() +
                  project.getJavaSourcesFolder()).toURI().toURL(),
                  new File(eclipseProject.getLocation().toPortableString() +
                      project.getFolderForExecutables()).toURI().toURL()

          );


      eclipseProject.refreshLocal(IResource.DEPTH_INFINITE, null);
    } catch (MalformedURLException e) {
      throw new ASCoDTException(SiDLBuilder.class.getName(),
          "generateBlueprints()", "wrong blueprint url:" +
              e.getLocalizedMessage(), e);
    } catch (CoreException e) {
      throw new ASCoDTException(SiDLBuilder.class.getName(),
          "generateBlueprints()", "eclipse core exception:" +
              e.getLocalizedMessage(), e);
    }
  }

  /**
   * Executes the ascodt compiler to generate the build scripts for given symbol
   * table
   * 
   * @param eclipseProject
   *          the current eclipse project
   * @throws ASCoDTException
   */
  public static void generateBuildScripts(IProject eclipseProject) throws ASCoDTException{
    Project project = ProjectBuilder.getInstance().getProject(eclipseProject);
    assert project.getSymbolTable() != null;
    CreateGlobalBuildScripts buildScripts = new CreateGlobalBuildScripts(
        project.getSymbolTable());
    try{
      buildScripts.create(
          new File(eclipseProject.getLocation().toPortableString() +
              project.getJavaProxiesFolder()).toURI().toURL(),
          new File(eclipseProject.getLocation().toPortableString() +
              project.getJavaSourcesFolder()).toURI().toURL(),
          new File(eclipseProject.getLocation().toPortableString() +
              project.getFolderForExecutables()).toURI().toURL()
          );
      eclipseProject.refreshLocal(IResource.DEPTH_INFINITE, null);
    } catch (MalformedURLException e) {
      throw new ASCoDTException(SiDLBuilder.class.getName(),
          "generateBuildScripts()", "wrong blueprint url:" +
              e.getLocalizedMessage(), e);
    } catch (CoreException e) {
      throw new ASCoDTException(SiDLBuilder.class.getName(),
          "generateBuildScripts()", "eclipse core exception:" +
              e.getLocalizedMessage(), e);
    }
  }
  /**
   * A routine to validate the global symbol table against specific sidl file
   * 
   * @param startNode
   *          the starting node of the sidl resource
   * @param symbolTable
   *          to validate with
   * @return a error string or "" if valid
   */
  public static String validateSymbolTableForSIDLResource(Start startNode,
      String resourceLocation, SymbolTable symbolTable) {
    ASTValidator validator = new ASTValidator(symbolTable, resourceLocation);
    startNode.apply(validator);
    return validator.getErrorMessages();

  }

  private Trace _trace = new Trace(SiDLBuilder.class.getCanonicalName());

  public SiDLBuilder() {
    super();
    _trace.in("Constructor");

    _trace.out("Constructor");
  }

}
