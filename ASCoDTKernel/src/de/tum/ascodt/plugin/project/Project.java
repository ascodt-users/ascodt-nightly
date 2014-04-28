package de.tum.ascodt.plugin.project;


import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.IOException;
import java.io.InputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;
import java.util.Vector;

import org.eclipse.core.filesystem.EFS;
import org.eclipse.core.filesystem.IFileInfo;
import org.eclipse.core.filesystem.IFileStore;
import org.eclipse.core.filesystem.IFileSystem;
import org.eclipse.core.resources.IContainer;
import org.eclipse.core.resources.IFile;
import org.eclipse.core.resources.IFolder;
import org.eclipse.core.resources.IProject;
import org.eclipse.core.resources.IResource;
import org.eclipse.core.resources.IncrementalProjectBuilder;
import org.eclipse.core.runtime.Assert;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.core.runtime.IConfigurationElement;
import org.eclipse.core.runtime.IExtensionRegistry;
import org.eclipse.core.runtime.IProgressMonitor;
import org.eclipse.core.runtime.IStatus;
import org.eclipse.core.runtime.Path;
import org.eclipse.core.runtime.QualifiedName;
import org.eclipse.core.runtime.RegistryFactory;
import org.eclipse.core.runtime.Status;
import org.eclipse.core.runtime.jobs.Job;
import org.eclipse.jdt.core.IClasspathEntry;
import org.eclipse.jdt.core.IJavaProject;
import org.eclipse.jdt.core.JavaCore;
import org.eclipse.jdt.core.JavaModelException;
import org.eclipse.jdt.launching.JavaRuntime;
import org.eclipse.swt.widgets.Display;
import org.eclipse.ui.IEditorReference;
import org.eclipse.ui.PartInitException;
import org.eclipse.ui.PlatformUI;
import org.eclipse.ui.part.FileEditorInput;

import de.tum.ascodt.plugin.ASCoDTKernel;
import de.tum.ascodt.plugin.project.builders.SIDLPair;
import de.tum.ascodt.plugin.project.builders.SiDLBuilder;
import de.tum.ascodt.plugin.repository.ClasspathRepository;
import de.tum.ascodt.plugin.ui.editors.gef.WorkbenchEditor;
import de.tum.ascodt.plugin.ui.gef.model.Diagram;
import de.tum.ascodt.plugin.ui.tabs.UITab;
import de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice;
import de.tum.ascodt.plugin.utils.tracing.Trace;
import de.tum.ascodt.repository.Repository;
import de.tum.ascodt.repository.Target;
import de.tum.ascodt.resources.ResourceManager;
import de.tum.ascodt.sidlcompiler.frontend.node.AClassPackageElement;
import de.tum.ascodt.sidlcompiler.frontend.node.Start;
import de.tum.ascodt.sidlcompiler.symboltable.SymbolTable;
import de.tum.ascodt.utils.TemplateFile;
import de.tum.ascodt.utils.exceptions.ASCoDTException;


/**
 * Represents one particular project.
 * 
 * @image html ../../../../../architecture_packages-and-important-classes.png
 * 
 * @author Tobias Weinzierl
 */
public class Project {

  private static final String DEPENDENCIES = "dependencies";

  /**
   * creates all parents for a given file
   * 
   * @param folder
   * @throws CoreException
   */
  private static void createParentFolders(IFolder folder) throws CoreException {
    IContainer parent = folder.getParent();
    if (parent instanceof IFolder) {
      createParentFolders((IFolder)parent);
    }
    IFileSystem fileSystem = EFS.getLocalFileSystem();
    IFileStore store = fileSystem.getStore(folder.getFullPath());
    IFileInfo localInfo = store.fetchInfo();
    if (!folder.exists()) {
      if (!localInfo.exists()) {
        folder.create(false, true, null);
      }
      folder.refreshLocal(IResource.DEPTH_INFINITE, null);
    }
  }

  private Trace _trace = new Trace(Project.class.getCanonicalName());

  /**
   * holds the eclipse project handler
   */
  private IProject _eclipseProjectHandle;

  /**
   * instance of the static repository
   */
  private Repository _staticRepository;

  private String _projectFileName;

  /**
   * list of all folders, which can be displayed in the navigator
   */
  private Vector<IFolder> _folders;

  /**
   * All the sidl files associated to the project. Should be equal to the sidl
   * files stored in src, so if the user does a refresh, this list should be
   * updated.
   */
  // TODO private java.util.Set<String> _SIDLFiles;

  /**
   * Set of full qualified SIDL files that are imported both in the project and
   * by all compiler calls.
   */
  // TODO private java.util.Set<String> _importSIDLFiles;

  // TODO private java.util.Set<String> _importedJars;

  /**
   * a global symbol table for all sidl files in the project
   */
  private SymbolTable _symbolTable;
  private HashMap<String, Integer> _functionTable;

  /**
   * a classpath repository
   */
  private ClasspathRepository _classpathRepository;

  public Project(IProject eclipseProjectHandle) throws ASCoDTException {
    _trace.in("Project(...)", eclipseProjectHandle.getName());
    _eclipseProjectHandle = eclipseProjectHandle;
    _staticRepository = new Repository();
    try {
      initiliaseClasspathRepository();
    } catch (IOException e) {
      throw new ASCoDTException(getClass().getName(), "Project()",
          "initilisation of classspath repository failed!", e);
    }

    _projectFileName = "." + _eclipseProjectHandle.getName() + ".ascodt";
    _folders = new Vector<IFolder>();
    _symbolTable = new SymbolTable();
    _functionTable = new HashMap<String,Integer>();

    IFile projectFile = _eclipseProjectHandle.getFile(getNameOfProjectFile());
    if (!projectFile.exists()) {
      writeProjectFile();

    }
    addClasspathEntries();
    // folder for sidl files
    createSource();

    // folder for included sidl files
    createIncludes();
    createSettings();
    // folder where all native libraries are collected
    createBuildFolders();
    // folder for all imported components
    createImports();
    // workspace for dynamic repositories
    createWorkspace();
    createJavaFolders();
    readProjectFile();
    resetStaticRepository();
    _trace.out("Project(...)", eclipseProjectHandle.getName());
  }

  /**
   * sets the default classpath entries of the ascodt project
   * 
   * @throws ASCoDTException
   */
  private void addClasspathEntries() throws ASCoDTException {
    IJavaProject javaProject = JavaCore.create(_eclipseProjectHandle);

    try {
      Set<IClasspathEntry> entries = new HashSet<IClasspathEntry>();
      for (IClasspathEntry classElement : Arrays.asList(javaProject
          .getRawClasspath())) {
        if (classElement.getEntryKind() == org.eclipse.jdt.core.IClasspathEntry.CPE_CONTAINER ||
            classElement.getEntryKind() == org.eclipse.jdt.core.IClasspathEntry.CPE_LIBRARY) {
          entries.add(classElement);
        }
      }
      if (!entries.contains(JavaCore
          .newLibraryEntry(
              new Path(ResourceManager.getResourceAsPath("", ASCoDTKernel.ID)
                  .getPath()), null, null, false))) {
        entries.add(JavaCore.newLibraryEntry(new Path(ResourceManager
            .getResourceAsPath("", ASCoDTKernel.ID).getPath()), null, null,
            false));
      }
      if (!entries.contains(JavaCore.newLibraryEntry(new Path(ResourceManager
          .getResourceAsPath("third-party-libs/swt.jar", ASCoDTKernel.ID)
          .getPath()), null, null, false))) {
        entries.add(JavaCore.newLibraryEntry(new Path(ResourceManager
            .getResourceAsPath("third-party-libs/swt.jar", ASCoDTKernel.ID)
            .getPath()), null, null, false));
      }
      if (!entries.contains(JavaRuntime.getDefaultJREContainerEntry())) {
        entries.add(JavaRuntime.getDefaultJREContainerEntry());
      }
      IExtensionRegistry reg = RegistryFactory.getRegistry();
      evaluateContributions(reg, entries);
      javaProject.setRawClasspath(
          entries.toArray(new IClasspathEntry[entries.size()]), null);
    } catch (JavaModelException e) {
      throw new ASCoDTException(getClass().getName(), "addClasspathEntries()",
          "adding default classpath entries to project " +
              _eclipseProjectHandle.getLocation().toString() + " failed", e);
    } catch (IOException e) {
      throw new ASCoDTException(getClass().getName(), "addClasspathEntries()",
          "adding default classpath entries to project " +
              _eclipseProjectHandle.getLocation().toString() + " failed", e);
    } catch (CoreException e) {
      throw new ASCoDTException(getClass().getName(), "addClasspathEntries()",
          "adding default classpath entries to project " +
              _eclipseProjectHandle.getLocation().toString() + " failed", e);
    }
  }

  /**
   * add a new source entry to the project. This extends the build path of the
   * project
   * 
   * @param entryPath
   *          the path of the entry
   * @throws ASCoDTException
   */
  public void addClasspathSource(String entryPath) throws ASCoDTException {
    try {
      if (entryPath.contains(":")) {
        entryPath = entryPath.replaceFirst(
            entryPath.substring(entryPath.indexOf(":") - 1,
                entryPath.indexOf(":") + 1), "");
      }
      IJavaProject javaProject = JavaCore.create(_eclipseProjectHandle);
      Set<IClasspathEntry> entries = new HashSet<IClasspathEntry>();
      for (IClasspathEntry classElement : Arrays.asList(javaProject
          .getRawClasspath())) {
        if (!new Path(classElement.getPath().toFile().toURI().toURL()
            .toString()).lastSegment().contains(
            getEclipseProjectHandle().getName())) {
          entries.add(classElement);
        }
      }
      entries.add(JavaCore
          .newLibraryEntry(
              new Path(ResourceManager.getResourceAsPath("", ASCoDTKernel.ID)
                  .getPath()), null, null, false));
      IClasspathEntry entry = JavaCore.newSourceEntry(new Path(entryPath),
          new Path[] {new Path("*.java"), new Path("**/*.java")},
          new Path[] {new Path("cmake*/")}, null);
      // .newSourceEntry(new Path(entryPath));

      if (!entries.contains(entry)) {
        entries.add(entry);
      }
      javaProject.setRawClasspath(
          entries.toArray(new IClasspathEntry[entries.size()]), null);

    } catch (JavaModelException e) {
      throw new ASCoDTException(getClass().getName(), "addClasspathSource()",
          "adding default classpath source entry to project " +
              _eclipseProjectHandle.getLocation().toString() + " failed", e);
    } catch (IOException e) {
      throw new ASCoDTException(getClass().getName(), "addClasspathSource()",
          "adding default classpath source entry to project " +
              _eclipseProjectHandle.getLocation().toString() + " failed", e);

    }
  }

  /**
   * adds a new dependency to the project. The add operation has two phases:
   * 1. code generation with the sidl compiler
   * 2. extending the project persistent properties
   * 
   * @param dependency
   *          the sidl dependency to be compiled
   * @throws ASCoDTException
   * @throws CoreException
   */
  public void addSIDLDependency(String dependency) throws ASCoDTException,
      CoreException {

    Start startNode = SiDLBuilder.buildStartSymbolsForSIDLResource(dependency);
    String err = "";
    if ((err = SiDLBuilder.validateSymbolTableForSIDLResource(startNode,
        dependency, _symbolTable)).equals("")) {
      SiDLBuilder.extendSymbolTable(startNode, _symbolTable, dependency);
      SiDLBuilder.generateBlueprints(_eclipseProjectHandle);
      SiDLBuilder.generateBuildScripts(_eclipseProjectHandle);
      String oldDependencies = _eclipseProjectHandle
          .getPersistentProperty(new QualifiedName(
              "de.tum.ascodt.plugin.ASCoDTKernel", DEPENDENCIES));

      if (oldDependencies != null) {
        _eclipseProjectHandle.setPersistentProperty(new QualifiedName(
            "de.tum.ascodt.plugin.ASCoDTKernel", DEPENDENCIES),
            oldDependencies + "," + dependency);
      } else {
        _eclipseProjectHandle.setPersistentProperty(new QualifiedName(
            "de.tum.ascodt.plugin.ASCoDTKernel", DEPENDENCIES), dependency);
      }
    }
  }

  /**
   * Build the global symbol table
   * 
   * @throws ASCoDTException
   * @throws CoreException
   * @see buildProjectSources
   */
  public void buildProjectSources() throws ASCoDTException {
    try {
      Vector<SIDLPair<String, Start>> sources = new Vector<SIDLPair<String, Start>>();
      Vector<SIDLPair<String, Start>> deps = new Vector<SIDLPair<String, Start>>();
      Vector<SIDLPair<String, Start>> imports = new Vector<SIDLPair<String, Start>>();
      SymbolTable symbolTable = new SymbolTable();
      for (String dep : getSIDLDependencies()) {
        deps.add(new SIDLPair<String, Start>(dep, SiDLBuilder
            .buildStartSymbolsForSIDLResource(dep)));
      }
      SiDLBuilder.buildStartSymbolsForSIDLResources(imports,
          _eclipseProjectHandle.getFolder(getImportsFolder()));
      SiDLBuilder.buildStartSymbolsForSIDLResources(sources,
          _eclipseProjectHandle.getFolder(getSourcesFolder()));
      for (SIDLPair<String, Start> resourceEntry : deps) {
        SiDLBuilder.extendSymbolTable(resourceEntry._second, symbolTable,
            resourceEntry._first);
      }

      for (SIDLPair<String, Start> resourceEntry : imports) {
        SiDLBuilder.extendSymbolTable(resourceEntry._second, symbolTable,
            resourceEntry._first);
      }

      for (SIDLPair<String, Start> resourceEntry : sources) {
        SiDLBuilder.extendSymbolTable(resourceEntry._second, symbolTable,
            resourceEntry._first);
      }
      _symbolTable = null;
      _symbolTable = symbolTable;
      _functionTable.clear();
      SiDLBuilder.generateBlueprints(_eclipseProjectHandle);
      SiDLBuilder.generateBuildScripts(_eclipseProjectHandle);

    } catch (CoreException e) {
      throw new ASCoDTException(getClass().getName(), "buildProjectSources()",
          "getting sidl dependencies failed", e);
    }
  }

  /**
   * this method closes all running workbench instances. It is needed to assure
   * the consistency of the
   * component classes. the method is invoked by the compileComponents method
   */
  public Vector<IFile> closeRunningWorkbenchInstances() {
    final Vector<IFile> editorInputs = new Vector<IFile>();
    Display.getDefault().syncExec(new Runnable() {

      @Override
      public void run() {
        if (PlatformUI.getWorkbench() != null &&
            PlatformUI.getWorkbench().getActiveWorkbenchWindow() != null &&
            PlatformUI.getWorkbench().getActiveWorkbenchWindow()
                .getActivePage() != null &&
            PlatformUI.getWorkbench().getActiveWorkbenchWindow()
                .getActivePage().getEditorReferences() != null) {

          for (IEditorReference ref : PlatformUI.getWorkbench()
              .getActiveWorkbenchWindow().getActivePage().getEditorReferences()) {
            if (ref.getEditor(false) instanceof WorkbenchEditor &&
                ProjectBuilder
                    .getInstance()
                    .getProject(
                        ((WorkbenchEditor)ref.getEditor(false)).getProject())
                    .equals(Project.this)) {
              editorInputs.add(((FileEditorInput)ref.getEditor(false)
                  .getEditorInput()).getFile());
              ref.getEditor(false).getSite().getPage()
                  .closeEditor(ref.getEditor(false), false);

            }

          }
        }

      }
    });
    return editorInputs;
  }

  public void compileComponents() {
    Job job = new Job("Classes Compilation") {

      @Override
      protected IStatus run(IProgressMonitor monitor) {
        try {

          compileComponents_i();

          // Project.this.openWorkbenchEditors(instances);
          return Status.OK_STATUS;
        } catch (Exception e) {
          return Status.CANCEL_STATUS;
        }
      }

    };
    job.schedule();

  }

  /**
   * compiles the java classes for all components in the project
   * 
   * @throws ASCoDTException
   */
  public void compileComponents_i() {
    IJavaProject jProject = JavaCore.create(_eclipseProjectHandle);
    try {
      jProject.getProject().build(IncrementalProjectBuilder.FULL_BUILD,
          "org.eclipse.jdt.core.javabuilder", null, null);
    } catch (CoreException e) {
      ErrorWriterDevice.getInstance().println(e);
    }

  }

  /**
   * creates a folder where we store the libraries needed
   * for native components
   * 
   * @throws ASCoDTException
   */
  private void createBuildFolders() throws ASCoDTException {
    IFolder executablesFolder = _eclipseProjectHandle
        .getFolder(getFolderForExecutables());
    IFolder libsFolder = _eclipseProjectHandle.getFolder(getFolderForLibs());

    try {
      executablesFolder.refreshLocal(IResource.DEPTH_INFINITE, null);
      if (!executablesFolder.exists()) {
        createParentFolders(executablesFolder);
      }
      libsFolder.refreshLocal(IResource.DEPTH_INFINITE, null);
      if (!libsFolder.exists()) {
        createParentFolders(libsFolder);
      }
    } catch (CoreException e) {
      throw new ASCoDTException(getClass().getName(), "createIncludes()",
          "creating an includes folder failed", e);
    }

  }

  /**
   * creates a new source file for specified component. It sets the initial
   * structure
   * of the sidl file (namespace and component definition)
   * 
   * @param componentName
   *          name of the component
   * @param namespace
   *          namespace of the component coded as <n0>.<n1>.<n2>...
   * @param componentTarget
   *          target language for the component to be compiled
   * @throws ASCoDTException
   */
  public void createComponent(String componentName, String namespace,
      Target componentTarget) throws ASCoDTException {
    _trace.in("createComponentSIDLSourceFile()");
    IFile sourceFile = _eclipseProjectHandle.getFile(getSourcesFolder() + "/" +
        namespace + "." + componentName + ".sidl");

    try {
      Assert.isNotNull(namespace);
      String[] namespaces;
      if (namespace.equals("")) {
        namespaces = new String[] {"default"};
      } else {
        if (!namespace.contains(".")) {
          namespaces = new String[] {namespace};
        } else {
          namespaces = namespace.split("\\.");
        }
      }
      TemplateFile templateFile = new TemplateFile(
          ResourceManager.getResourceAsStream("new-sidl-component.template",
              ASCoDTKernel.ID), sourceFile.getLocationURI().toURL(),
          namespaces, TemplateFile.getLanguageConfigurationForSIDL(), true);
      templateFile.addMapping("__CLASS_NAME__", componentName);
      templateFile.addMapping("__TARGET__", componentTarget.getType()
          .toString());
      templateFile.open();
      templateFile.close();
      _eclipseProjectHandle.refreshLocal(IResource.DEPTH_INFINITE, null);
      buildProjectSources();
      compileComponents();
      resetStaticRepository();
    } catch (Exception e) {
      throw new ASCoDTException(getClass().getName(),
          "createComponentSIDLSourceFile()",
          "creating SIDL file from template failed", e);
    }
    _trace.out("createComponentSIDLSourceFile()");
  }

  /**
   * creates a folder where we store the libraries needed
   * for native components
   * 
   * @throws ASCoDTException
   */
  private void createImports() throws ASCoDTException {
    IFolder importsFolder = _eclipseProjectHandle.getFolder(getImportsFolder());
    try {
      importsFolder.refreshLocal(IResource.DEPTH_INFINITE, null);
      if (!importsFolder.exists()) {
        createParentFolders(importsFolder);
      }
    } catch (CoreException e) {
      throw new ASCoDTException(getClass().getName(), "createIncludes()",
          "creating an includes folder failed", e);
    }

  }

  /**
   * creates the includes folder for the project and the corresponding model
   * 
   * @throws ASCoDTException
   */
  private void createIncludes() throws ASCoDTException {
    IFolder includesFolder = _eclipseProjectHandle
        .getFolder(getIncludesFolder());
    try {

      includesFolder.refreshLocal(IResource.DEPTH_INFINITE, null);
      if (!includesFolder.exists()) {
        createParentFolders(includesFolder);
      }
    } catch (CoreException e) {
      throw new ASCoDTException(getClass().getName(), "createIncludes()",
          "creating an includes folder failed", e);
    }
  }

  /**
   * creates all folders where the java classes are generated and sets the
   * corresponding classpaths
   * 
   * @throws ASCoDTException
   */
  private void createJavaFolders() throws ASCoDTException {
    IFolder sourcesFolder = _eclipseProjectHandle
        .getFolder(getJavaSourcesFolder());
    IFolder proxiesFolder = _eclipseProjectHandle
        .getFolder(getJavaProxiesFolder());

    IFolder classOutputFolder = _eclipseProjectHandle
        .getFolder(getClassOutputFolder());
    try {
      sourcesFolder.refreshLocal(IResource.DEPTH_INFINITE, null);
      proxiesFolder.refreshLocal(IResource.DEPTH_INFINITE, null);
      classOutputFolder.refreshLocal(IResource.DEPTH_INFINITE, null);
      if (!sourcesFolder.exists()) {
        createParentFolders(sourcesFolder);
      }
      if (!proxiesFolder.exists()) {
        createParentFolders(proxiesFolder);
      }
      if (!classOutputFolder.exists()) {
        createParentFolders(classOutputFolder);
      }

      addClasspathSource(Path.ROOT +
          sourcesFolder
              .getLocation()
              .removeFirstSegments(
                  _eclipseProjectHandle.getLocation().segmentCount() - 1)
              .toPortableString());
      addClasspathSource(Path.ROOT +
          proxiesFolder
              .getLocation()
              .removeFirstSegments(
                  _eclipseProjectHandle.getLocation().segmentCount() - 1)
              .toPortableString());

      _folders.add(sourcesFolder);
    } catch (CoreException e) {
      throw new ASCoDTException(getClass().getName(), "createJavaFolders()",
          "creating java folders failed!", e);
    }
  }

  /**
   * @param componentInterface
   * @return
   * @throws CoreException
   * @throws IOException
   */
  public IFile createJavaSourceFile(String relativePath) throws CoreException,
      IOException {
    IFile sourceUIFile = _eclipseProjectHandle.getFile(getJavaSourcesFolder() +
        "/" + relativePath);

    createProjectFile(sourceUIFile, null);
    sourceUIFile.refreshLocal(IResource.DEPTH_INFINITE, null);
    return sourceUIFile;
  }

  /**
   * creates a file and all missing parent folders in the given project
   * 
   * @param projectFile
   * @throws CoreException
   * @throws IOException
   */
  private void createProjectFile(IFile projectFile, InputStream stream)
      throws CoreException, IOException {
    if (projectFile.getParent() != null &&
        projectFile.getParent() instanceof IFolder) {
      createParentFolders((IFolder)projectFile.getParent());
    }
    if (!projectFile.exists()) {
      projectFile.create(stream, true, null);
    } else {
      projectFile.setContents(stream, true, true, null);
    }
  }

  /**
   * creates a folder where we store the libraries needed
   * for native components
   * 
   * @throws ASCoDTException
   */
  private void createSettings() throws ASCoDTException {
    IFolder settingsFolder = _eclipseProjectHandle
        .getFolder(getSettingsFolder());
    try {
      settingsFolder.refreshLocal(IResource.DEPTH_INFINITE, null);
      if (!settingsFolder.exists()) {
        createParentFolders(settingsFolder);
      }
    } catch (CoreException e) {
      throw new ASCoDTException(getClass().getName(), "createIncludes()",
          "creating an includes folder failed", e);
    }

  }

  /**
   * creates the source folder for the project and the corresponding model
   * 
   * @throws ASCoDTException
   */
  private void createSource() throws ASCoDTException {
    IFolder srcFolder = _eclipseProjectHandle.getFolder(getSourcesFolder());

    try {
      srcFolder.refreshLocal(IResource.DEPTH_INFINITE, null);
      if (!srcFolder.exists()) {
        createParentFolders(srcFolder);
      }
      _folders.add(srcFolder);
    } catch (CoreException e) {
      throw new ASCoDTException(getClass().getName(), "createSource()",
          "creating a source folder failed", e);
    }
  }

  /**
   * A method used to create the java classes for a new user interface for
   * specific
   * component.
   * 
   * @param componentInterface
   *          identifier of the component
   * @throws ASCoDTException
   */
  public void createUserInterface(String componentInterface)
      throws ASCoDTException {
    _trace.in("createUserInterface()");
    try {
      IFile sourceUIFile = createJavaSourceFile(componentInterface.replaceAll(
          "\\.", "/") + "UI.java");
      String[] namespaces = retrieveNamespaces(componentInterface);
      TemplateFile templateFile = new TemplateFile(
          ResourceManager.getResourceAsStream("new-ui.template",
              ASCoDTKernel.ID), sourceUIFile.getLocationURI().toURL(),
          namespaces, TemplateFile.getLanguageConfigurationForJava(), true);
      templateFile
          .addMapping("__COMPONENT_NAME__", componentInterface
              .substring(componentInterface.lastIndexOf(".") + 1));
      templateFile
          .addMapping("__UITAB_CLASS__", UITab.class.getCanonicalName());
      templateFile.open();
      templateFile.close();
      _eclipseProjectHandle.refreshLocal(IResource.DEPTH_INFINITE, null);

    } catch (Exception e) {
      throw new ASCoDTException(getClass().getName(), "createUserInterface()",
          "creating user interface for \"" + componentInterface +
              "\" from template failed", e);
    }
    _trace.out("createUserInterface()");
  }

  /**
   * creates a workbench file with the given name
   * 
   * @param workbenchName
   *          the name of the workbench to be created
   */
  public void createWorkbech(String workbenchName) throws ASCoDTException {
    _trace.in("createWorkbech()");
    IFile workbenchFile = _eclipseProjectHandle.getFile(getSourcesFolder() +
        "/" + workbenchName + ".workbench");

    try {
      ByteArrayOutputStream out = new ByteArrayOutputStream();
      ObjectOutputStream objectStream = new ObjectOutputStream(out);
      objectStream.writeObject(new Diagram());
      objectStream.flush();
      objectStream.close();
      createProjectFile(workbenchFile,
          new ByteArrayInputStream(out.toByteArray()));

      workbenchFile.refreshLocal(IResource.DEPTH_INFINITE, null);
    } catch (CoreException e) {
      throw new ASCoDTException(getClass().getName(), "createWorkbech()",
          "creating a workbench file failed", e);
    } catch (IOException e) {
      throw new ASCoDTException(getClass().getName(), "createWorkbech()",
          "creating a workbench file initial content failed", e);
    }
    _trace.out("createWorkbech()");
  }

  /**
   * creates a workbench file for the dynamic ASCoDT repository
   * 
   * @param workbenchName
   *          name of the workbench
   */
  public void createWorkbench(String workbenchName) throws ASCoDTException {
    _trace.in("createWorkbench()");
    IFile workbenchFile = _eclipseProjectHandle.getFile(getWorkspaceFolder() +
        "/" + workbenchName + ".workbench");

    try {
      ByteArrayOutputStream out = new ByteArrayOutputStream();
      ObjectOutputStream outputStream = new ObjectOutputStream(out);
      outputStream.writeObject(null);
      outputStream.close();
      createProjectFile(workbenchFile,
          new ByteArrayInputStream(out.toByteArray()));
      workbenchFile.refreshLocal(IResource.DEPTH_INFINITE, null);
    } catch (Exception e) {
      throw new ASCoDTException(getClass().getName(), "createWorkbench()",
          "creating SIDL file from template failed", e);
    }
    _trace.out("createComponentSIDLSourceFile()");
  }

  /**
   * creates the workspace folder used for the storage of the dynamic repository
   * files
   * 
   * @throws ASCoDTException
   */
  private void createWorkspace() throws ASCoDTException {
    IFolder workspaceFolder = _eclipseProjectHandle
        .getFolder(getWorkspaceFolder());
    try {
      workspaceFolder.refreshLocal(IResource.DEPTH_INFINITE, null);
      if (!workspaceFolder.exists()) {
        createParentFolders(workspaceFolder);
      }
      _folders.add(workspaceFolder);
    } catch (CoreException e) {
      throw new ASCoDTException(getClass().getName(), "createWorkspace()",
          "creating a workspace folder failed", e);
    }
  }

  public void destroy() {
    // Vector<IFile> instances=
    Project.this.closeRunningWorkbenchInstances();
    if (_classpathRepository != null) {
      try {
        _classpathRepository.close();
      } catch (IOException e) {
        _classpathRepository = null;

      }
      _classpathRepository = null;
    }
  }

  private void evaluateContributions(IExtensionRegistry registry,
      Set<IClasspathEntry> classpathEntries) throws CoreException,
      ASCoDTException {
    IConfigurationElement[] config = registry
        .getConfigurationElementsFor(de.tum.ascodt.plugin.extensions.Project.ID);

    for (IConfigurationElement e : config) {

      final Object o = e.createExecutableExtension("class");
      if (o != null && o instanceof de.tum.ascodt.plugin.extensions.Project) {
        _trace.debug("evaluateContributions()", "executing a contribution");
        ((de.tum.ascodt.plugin.extensions.Project)o)
            .addClasspathEntries(classpathEntries);
      }
    }

  }

  public String getClassOutputFolder() {
    return "/bin";
  }

  /**
   * @return the _classpathRepository
   */
  public ClasspathRepository getClasspathRepository() {
    return _classpathRepository;
  }

  public File[] getComponentJavaProxies() {
    // TODO Auto-generated method stub
    Vector<File> proxies = new Vector<File>();
    retrieveSources(_eclipseProjectHandle.getLocation().toPortableString() +
        getJavaProxiesFolder(), proxies);
    return proxies.toArray(new File[] {});
  }

  public File[] getComponentJavaSources() {
    Vector<File> sources = new Vector<File>();
    retrieveSources(_eclipseProjectHandle.getLocation().toPortableString() +
        getJavaSourcesFolder(), sources);
    return sources.toArray(new File[] {});
  }

  /**
   * @return the _eclipseProjectHandle
   */
  public IProject getEclipseProjectHandle() {
    return _eclipseProjectHandle;
  }

  public String getFolderForExecutables() {
    return "/bin";
  }

  public String getFolderForLibs() {
    return "/lib";
  }

  /**
   * 
   * @return all children folders
   */
  public Object[] getFolders() {

    return _folders.toArray();
  }

  public String getImportsFolder() {
    return "/imports";
  }

  private String getIncludesFolder() {
    return "/includes";
  }

  public String getJavaProxiesFolder() {
    return "/components/java";
  }

  public String getJavaSourcesFolder() {
    return "/src";
  }

  /**
   * 
   * @return the name of the project
   */
  public String getName() {
    return _eclipseProjectHandle.getName();
  }

  /**
   * @return The full qualified project file
   */
  public String getNameOfProjectFile() {
    return _projectFileName;
  }

  /**
   * 
   * @return Project file or throw exception if it doesn't exist.
   * 
   * @throws ASCoDTException
   */
  public IFile getProjectFile() throws ASCoDTException {
    String projectFilePath = getNameOfProjectFile();
    IFile result = _eclipseProjectHandle.getFile(projectFilePath);
    if (!result.exists()) {
      throw new ASCoDTException(getClass().getName(), "getProjectFile()",
          "project file " + projectFilePath + " does not exist", null);
    }
    return result;
  }

  public String getSettingsFolder() {
    return "/settings";
  }

  /**
   * A getter for all project dependencies (sidl include deps)
   * 
   * @return a list of all sidl dependencies
   * @throws CoreException
   */
  public String[] getSIDLDependencies() throws CoreException {
    String deps = _eclipseProjectHandle
        .getPersistentProperty(new QualifiedName("de.tum.ascodt.plugin",
            DEPENDENCIES));
    if (deps != null) {
      if (deps.contains(",")) {
        return deps.split(",");
      } else {
        return new String[] {deps};
      }
    }
    return new String[] {};
  }

  /**
   * 
   * @return identifier of the source folder
   */
  private String getSourcesFolder() {
    return "sidl";
  }

  /**
   * @return static repository
   */
  public Repository getStaticRepository() {
    return _staticRepository;
  }

  /**
   * @return the _symbolTable
   */
  public SymbolTable getSymbolTable() {
    return _symbolTable;
  }

  /**
   * 
   * @return folder for the storage of dynamic repositories
   */
  private String getWorkspaceFolder() {
    return "/workspace";
  }

  /**
   * 
   * @param workbenchName
   *          name of the workbench
   * @return true if the project has a workbench in the workspace
   */
  public boolean hasWorkbench(String workbenchName) {
    return _eclipseProjectHandle.getFile(
        getWorkspaceFolder() + "/" + workbenchName + ".workbench").exists();
  }

  /**
   * This method removes an existing classpath repository and initialises a new
   * one
   * 
   * @throws IOException
   */
  private void initiliaseClasspathRepository() throws IOException {

    _classpathRepository = new ClasspathRepository(_eclipseProjectHandle,
        ASCoDTKernel.getDefault().getClass().getClassLoader());
    _classpathRepository.addURL(new File(_eclipseProjectHandle.getLocation()
        .toPortableString() + "/bin").toURI().toURL());
  }

  public void openWorkbenchEditors(final Vector<IFile> workbenchInputs)
      throws ASCoDTException {

    Display.getDefault().asyncExec(new Runnable() {

      @Override
      public void run() {
        for (IFile input : workbenchInputs) {
          try {
            PlatformUI.getWorkbench().getActiveWorkbenchWindow()
                .getActivePage()
                .openEditor(new FileEditorInput(input), WorkbenchEditor.ID);
          } catch (PartInitException e) {

          }
        }
      }

    });

  }

  /**
   * Reads the project file and loads the saved static repository.
   */
  private void readProjectFile() throws ASCoDTException {
    _trace.in("readProjectFile()");

    IFile projectFile = _eclipseProjectHandle.getFile(getNameOfProjectFile());

    try {
      projectFile.refreshLocal(0, null);
      if (projectFile.getContents() != null) {
        ObjectInputStream in = new ObjectInputStream(projectFile.getContents());
        Object object = in.readObject();
        if (object != null && object instanceof Repository) {
          setStaticRepository((Repository)object);
        }
        in.close();
      }
    } catch (Exception e) {
      throw new ASCoDTException(getClass().getName(), "readProjectFile()",
          "reading project file failed", e);
    }
    _trace.out("readProjectFile()");
  }

  public void removeComponent(String componentName) throws ASCoDTException {
    try {
      IFile file = _eclipseProjectHandle.getFile(getSourcesFolder() + "/" +
          componentName + "" + ".sidl");
      if (file.exists()) {
        file.delete(true, null);
      }
      _eclipseProjectHandle.refreshLocal(IResource.DEPTH_INFINITE, null);
      buildProjectSources();
      resetStaticRepository();
    } catch (Exception e) {
      throw new ASCoDTException(getClass().getName(), "removeComponent()",
          "remove SIDL file from project failed", e);
    }
  }

  /**
   * notify all project listeners for the changed symbolTable and write down the
   * change
   * 
   * @throws ASCoDTException
   */
  public void resetStaticRepository() throws ASCoDTException {
    _staticRepository.reset();
    for (AClassPackageElement component : _symbolTable.getGlobalScope()
        .getFlattenedClassElements()) {

      _staticRepository.addComponent(_symbolTable.getScope(component)
          .getFullyQualifiedName(component.getName().getText()), component
          .getTarget().getText());
    }
    writeProjectFile();
  }

  /**
   * @param componentInterface
   * @return
   */
  public String[] retrieveNamespaces(String componentInterface) {
    String namespace = componentInterface.substring(0,
        componentInterface.lastIndexOf("."));
    String[] namespaces;
    if (namespace.equals("")) {
      namespaces = new String[] {"default"};
    } else {
      if (!namespace.contains(".")) {
        namespaces = new String[] {namespace};
      } else {
        namespaces = namespace.split("\\.");
      }
    }
    return namespaces;
  }

  /**
   * retrieves all source files in given directory.
   * 
   * @param path
   *          directory to search for source files.
   * @param sources
   *          a collection, where to put the founded source files
   */
  private void retrieveSources(String path, Vector<File> sources) {
    File f = new File(path);
    if (f.isFile() && f.getName().endsWith(".java")) {
      sources.add(f);
    } else {
      if (f.listFiles() != null) {
        for (File file : f.listFiles()) {
          retrieveSources(file.getAbsolutePath(), sources);
        }
      }
    }
  }

  /**
   * @param staticRepository
   *          the staticRepository to set
   */
  private void setStaticRepository(Repository staticRepository) {
    _staticRepository = staticRepository;
  }

  
  /**
   * Writes the project file.
   * 
   * Overwrites an existing file. Basically streams the repositories to the
   * file. If they are empty, the operation creates the startup project file.
   */
  private void writeProjectFile() throws ASCoDTException {
    _trace.in("writeProjectFile()");

    IFile projectFile = _eclipseProjectHandle.getFile(getNameOfProjectFile());

    try {
      ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
      ObjectOutputStream objectOutputStream = new ObjectOutputStream(
          byteArrayOutputStream);

      objectOutputStream.writeObject(_staticRepository); // argument must be
                                                         // Serializable
      objectOutputStream.close();
      createProjectFile(projectFile, new ByteArrayInputStream(
          byteArrayOutputStream.toByteArray()));

    } catch (Exception e) {
      throw new ASCoDTException(getClass().getName(), "writeProjectFile()",
          "writing project file failed", e);
    }

    _trace.out("writeProjectFile()");
  }

  public HashMap<String, Integer> getFunctionTable() {
    return _functionTable;
  }

}
