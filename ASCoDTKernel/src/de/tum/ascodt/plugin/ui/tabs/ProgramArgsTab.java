package de.tum.ascodt.plugin.ui.tabs;


import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Map;
import java.util.concurrent.ExecutorService;

import org.eclipse.core.resources.IResource;
import org.eclipse.core.runtime.Assert;
import org.eclipse.core.runtime.CoreException;
import org.eclipse.core.runtime.Path;
import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.events.SelectionListener;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.ExpandBar;
import org.eclipse.swt.widgets.ExpandItem;
import org.eclipse.swt.widgets.FileDialog;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Shell;
import org.eclipse.swt.widgets.Spinner;
import org.eclipse.swt.widgets.Text;
import org.eclipse.ui.PlatformUI;

import de.tum.ascodt.plugin.project.Project;
import de.tum.ascodt.plugin.project.ProjectBuilder;
import de.tum.ascodt.plugin.services.SocketService;
import de.tum.ascodt.plugin.utils.ProcessExitDetector;
import de.tum.ascodt.plugin.utils.ProcessListener;
import de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice;
import de.tum.ascodt.utils.exceptions.ASCoDTException;


abstract class ProgramArgsTab extends ContainerTab implements ProcessListener {

  protected Text textProgramArguments;
  protected Text textProgramExecutable;
  private java.io.File applicationSettings;
  private boolean _isStarted;
  protected ProcessExitDetector _exitDetector;
  private String _projectLocation;
  private Process _process;
  private ExecutorService _executionService;
  protected Spinner numberOfProcesses;

  protected ProgramArgsTab(String label, String containerId) {
    super(label, containerId);
    _exitDetector = new ProcessExitDetector();
    _exitDetector.addListener(this);
    _isStarted = false;
  }

  public void addListener(ProcessListener processListner) {
    _exitDetector.addListener(processListner);
  }

  protected void createParallelControlItems(ExpandBar bar) {
    GridLayout gridLayout = new GridLayout();
    gridLayout.numColumns = 2;

    Composite parallelComp = new Composite(bar, SWT.NONE);
    parallelComp.setLayout(gridLayout);
    GridData textGridData = new GridData();
    textGridData.horizontalAlignment = GridData.FILL;
    textGridData.grabExcessHorizontalSpace = true;

    Label labelProcessesExecutable = new Label(parallelComp, SWT.LEFT);
    labelProcessesExecutable.setText("Number of processes:");
    labelProcessesExecutable.setLayoutData(textGridData);

    numberOfProcesses =
        new org.eclipse.swt.widgets.Spinner(parallelComp, SWT.RIGHT);
    numberOfProcesses.setMinimum(1);
    numberOfProcesses.setMaximum(1024);
    numberOfProcesses.setSelection(1);
    numberOfProcesses.setLayoutData(textGridData);

    final ExpandItem parallelItemData = new ExpandItem(bar, SWT.NONE, 0);
    bar.setSize(parallelComp.computeSize(SWT.DEFAULT, SWT.DEFAULT).x,
                SWT.DEFAULT);
    parallelItemData.setText("Parallel settings");
    parallelItemData.setHeight(parallelComp.computeSize(SWT.DEFAULT,
                                                        SWT.DEFAULT).y);
    parallelItemData.setControl(parallelComp);
    parallelItemData.setExpanded(true);
  }

  protected void createArgsCotrolItems(ExpandBar bar) {
    GridLayout gridLayout = new GridLayout();
    gridLayout.numColumns = 2;

    Composite argsComp = new Composite(bar, SWT.NONE);
    argsComp.setLayout(gridLayout);
    GridData textGridData = new GridData();
    textGridData.horizontalAlignment = GridData.FILL;
    textGridData.grabExcessHorizontalSpace = true;

    Label labelProgramExecutable = new Label(argsComp, SWT.LEFT);
    labelProgramExecutable.setText("Executable:");
    labelProgramExecutable.setLayoutData(textGridData);

    textProgramExecutable = new Text(argsComp, SWT.RIGHT);
    textProgramExecutable.setText("");
    textProgramExecutable.setLayoutData(textGridData);

    Label labelProgramArgumets = new Label(argsComp, SWT.LEFT);
    labelProgramArgumets.setText("Arguments:");
    labelProgramArgumets.setLayoutData(textGridData);

    textProgramArguments = new Text(argsComp, SWT.RIGHT);
    textProgramArguments.setText("");
    textProgramArguments.setLayoutData(textGridData);

    Button browseBtn = new Button(argsComp, SWT.LEFT);
    browseBtn.setText("Browse..");
    browseBtn.setLayoutData(textGridData);

    browseBtn.addSelectionListener(new SelectionListener() {

      @Override
      public void widgetDefaultSelected(SelectionEvent e) {
        // TODO Auto-generated method stub

      }

      @Override
      public void widgetSelected(SelectionEvent e) {
        Shell shell =
            PlatformUI.getWorkbench().getActiveWorkbenchWindow().getShell();
        FileDialog fileDialog = new FileDialog(shell, SWT.OPEN);
        fileDialog.setText("Path to executable");
        // fileDialog.setFilterExtensions(new String[]{"*.ascodt-component"});
        textProgramExecutable.setText(fileDialog.open());

      }

    });

    Button startBtn = new Button(argsComp, SWT.RIGHT);
    startBtn.setText("Start");
    startBtn.setLayoutData(textGridData);
    startBtn.addSelectionListener(new SelectionListener() {

      @Override
      public void widgetDefaultSelected(SelectionEvent e) {
        // TODO Auto-generated method stub

      }

      @Override
      public void widgetSelected(SelectionEvent e) {
        execute();
      }

    });
    final ExpandItem itemData = new ExpandItem(bar, SWT.NONE, 0);
    bar.setSize(argsComp.computeSize(SWT.DEFAULT, SWT.DEFAULT).x, SWT.DEFAULT);
    itemData.setText("Domain settings");
    itemData.setHeight(argsComp.computeSize(SWT.DEFAULT, SWT.DEFAULT).y);
    itemData.setControl(argsComp);
    itemData.setExpanded(true);

  }

  @Override
  protected void createControlGroup() {

    GridLayout layout = new GridLayout();
    layout.numColumns = 1;

    super.tabFolderPage.setLayout(layout);

    final ExpandBar bar =
        new org.eclipse.swt.widgets.ExpandBar(super.tabFolderPage, SWT.NONE);
    GridData gridData = new GridData();
    gridData.horizontalAlignment = GridData.FILL;
    gridData.verticalAlignment = GridData.FILL;
    gridData.grabExcessHorizontalSpace = true;
    gridData.grabExcessVerticalSpace = true;
    bar.setLayoutData(gridData);
    createControlGroup(bar);
  }

  protected void createControlGroup(ExpandBar bar) {

    createArgsCotrolItems(bar);
    createParallelControlItems(bar);
  }

  /**
   * clear running processes
   */
  @Override
  public void dispose() {
    _exitDetector.removeListener(this);
    if (_process != null) {
      if (_executionService != null && !_executionService.isShutdown()) {
        _executionService.shutdownNow();
        _executionService = null;
      }
      _process.destroy();
    }
    super.dispose();
  }

  /**
	 * 
	 */
  public void execute() {
    try {
      for (int i = 1; i < this.numberOfProcesses.getSelection(); i++) {
        SocketService.getDefault().getFreePort();
      }
      String cmd = getCommandForExecution();

      ProcessBuilder pb = new ProcessBuilder(cmd.split(" "));
      Map<String, String> env = pb.environment();
      if (env != null) {
        for (String envVar : getEnv()) {
          String[] envPair = envVar.split("=");
          Assert.isTrue(envPair.length == 2);
          env.put(envPair[0], envPair[1]);
        }
      }

      _process = pb.start();
      _exitDetector.setProcess(_process);
      _executionService = java.util.concurrent.Executors.newCachedThreadPool();
      _executionService.execute(_exitDetector);
      _executionService.execute(new Runnable() {

        @Override
        public void run() {
          BufferedReader reader =
              new BufferedReader(new InputStreamReader(_process.getInputStream()));
          String line = "";
          try {
            while ((line = reader.readLine()) != null) {
              System.out.println(line);
            }
            reader.close();
          } catch (IOException e) {
            ErrorWriterDevice.getInstance().println(e);
          }

        }

      });
      _executionService.execute(new Runnable() {

        @Override
        public void run() {
          BufferedReader reader =
              new BufferedReader(new InputStreamReader(_process.getErrorStream()));
          String line = "";
          try {
            while ((line = reader.readLine()) != null) {
              System.err.println(line);
            }
            reader.close();
          } catch (IOException e) {
            ErrorWriterDevice.getInstance().println(e);
          }

        }

      });
      onStart();

    } catch (IOException | ASCoDTException e) {
      if (_process != null) {
        _process.destroy();
      }
      ErrorWriterDevice.getInstance().println(e);
    }
  }

  public abstract String getCommandForExecution();

  // public String[] getCmd(){
  // String[] tokenizedArgs= textProgramArguments.getText().split(" ");
  // String[] res = new String[tokenizedArgs.length+1];
  // res[0]= textProgramExecutable.getText();_exitDetector= new
  // ProcessExitDetector(p);
  // for(int i=0;i<tokenizedArgs.length;i++)
  // res[i+1]=tokenizedArgs[i];
  // return res;
  // }
  public String[] getEnv() {
    return new String[] {};
  }

  public boolean hasApplicationSettings() {
    return applicationSettings != null && applicationSettings.exists();
  }

  public synchronized boolean isStarted() {
    return _isStarted;
  }

  private void loadStorageFiles() {
    if (hasApplicationSettings()) {
      try {
        BufferedReader reader =
            new BufferedReader(new FileReader(applicationSettings));
        String line = "";
        int counter = 0;
        while ((line = reader.readLine()) != null) {
          if (counter == 0) {
            textProgramExecutable.setText(line);
          } else if (counter == 1) {
            textProgramArguments.setText(line);
          } else if (counter == 2) {
            numberOfProcesses.setSelection(Integer.parseInt(line));
          }
          counter++;
        }
        reader.close();
      } catch (FileNotFoundException e) {
        // TODO Auto-generated catch block
        e.printStackTrace();
      } catch (IOException e) {
        // TODO Auto-generated catch block
        e.printStackTrace();
      }

    }
  }

  public void onStart() throws ASCoDTException {
    saveProgramSettings();
    synchronized (this) {
      _isStarted = true;
    }
  }

  @Override
  public void processFinished(int returnValue) throws de.tum.ascodt.utils.exceptions.ASCoDTException {
    if (_process != null) {
      _process = null;
    }
    if (_executionService != null && returnValue != 0) {
      _executionService.shutdownNow();
      _executionService = null;
    }
  }

  public void removeListener(ProcessListener processListner) {
    _exitDetector.removeListener(processListner);
  }

  private void saveProgramSettings() {
    Assert.isNotNull(applicationSettings);
    FileWriter fwriter;
    try {
      fwriter = new FileWriter(applicationSettings, false);
      BufferedWriter writer = new BufferedWriter(fwriter);
      writer.write(textProgramExecutable.getText() + "\n");
      writer.write(textProgramArguments.getText() + "\n");
      writer.write(numberOfProcesses.getText() + "\n");
      writer.close();
      Project project =
          ProjectBuilder.getInstance()
                        .getProject(new Path(_projectLocation).lastSegment());
      project.getEclipseProjectHandle().refreshLocal(IResource.DEPTH_INFINITE,
                                                     null);
    } catch (IOException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    } catch (CoreException e) {
      // TODO Auto-generated catch block
      e.printStackTrace();
    }

  }

  public void setProjectLocation(String location) {
    _projectLocation = location;
    if (textProgramExecutable != null) {
      textProgramExecutable.setText(_projectLocation + File.separator +
                                    "bin" +
                                    File.separator +
                                    _label);
    }
    applicationSettings =
        new java.io.File(_projectLocation + File.separator +
                         "settings" +
                         File.separator +
                         _label +
                         ".settings");
    loadStorageFiles();
  }
}
