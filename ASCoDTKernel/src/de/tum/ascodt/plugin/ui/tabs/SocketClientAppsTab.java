package de.tum.ascodt.plugin.ui.tabs;


import org.eclipse.swt.SWT;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.Display;
import org.eclipse.swt.widgets.ExpandBar;
import org.eclipse.swt.widgets.ExpandItem;
import org.eclipse.swt.widgets.Label;
import org.eclipse.swt.widgets.Text;

import de.tum.ascodt.plugin.services.SocketService;
import de.tum.ascodt.repository.entities.SocketComponent;
import de.tum.ascodt.utils.exceptions.ASCoDTException;


/**
 * A socket client tab with additional fields for hostname and port
 * 
 * @author Atanas Atanasov
 * 
 */
public class SocketClientAppsTab extends ProgramArgsTab {

  private Text textHostname;
  private Text textPort;
  private SocketComponent component;
  private int _daemonPort;

  public SocketClientAppsTab(String label,
                             SocketComponent component,
                             String containerId) {
    super(label, containerId);
    this.component = component;
    _daemonPort = SocketService.getDefault().getFreePort();
  }

  private void createClientUIGroup(ExpandBar bar) {
    GridLayout gridLayout = new GridLayout();
    gridLayout.numColumns = 2;

    Composite argsComp = new Composite(bar, SWT.NONE);
    argsComp.setLayout(gridLayout);
    GridData textGridData = new GridData();
    textGridData.horizontalAlignment = GridData.FILL;
    textGridData.grabExcessHorizontalSpace = true;

    Label labelHostname = new Label(argsComp, SWT.LEFT);
    labelHostname.setText("Hostname:");
    labelHostname.setLayoutData(textGridData);

    textHostname = new Text(argsComp, SWT.RIGHT);
    textHostname.setText(component.getHost() == null
                                                    ? "127.0.0.1"
                                                    : component.getHost());
    textHostname.setLayoutData(textGridData);

    Label labelPort = new Label(argsComp, SWT.LEFT);
    labelPort.setText("Port:");
    labelPort.setLayoutData(textGridData);

    textPort = new Text(argsComp, SWT.RIGHT);
    textPort.setText("" + component.getPort());
    textPort.setLayoutData(textGridData);

    final ExpandItem itemData = new ExpandItem(bar, SWT.NONE, 0);
    bar.setSize(argsComp.computeSize(SWT.DEFAULT, SWT.DEFAULT).x, SWT.DEFAULT);
    itemData.setText("Client settings");
    itemData.setHeight(argsComp.computeSize(SWT.DEFAULT, SWT.DEFAULT).y);
    itemData.setControl(argsComp);
    itemData.setExpanded(true);
  }

  @Override
  protected void createControlGroup(ExpandBar bar) {
    createClientUIGroup(bar);
    super.createControlGroup(bar);
  }

  @Override
  public void dispose() {

    super.dispose();
    component = null;
  }

  @Override
  public String getCommandForExecution() {
    String mpiPrefix = "";
    if (numberOfProcesses.getSelection() > 1) {
      mpiPrefix =
          "/home/atanasoa/intel/impi/4.1.3.049/intel64/bin/mpiexec -np " + numberOfProcesses.getSelection() +
              " ";
    }
    return mpiPrefix + textProgramExecutable.getText() +
           " " +
           textProgramArguments.getText();
  }

  @Override
  public String[] getEnv() {
    return new String[] {_label.toUpperCase().replaceAll("[.]", "_") + "_BUFFER_SIZE=" +
                             SocketService.getDefault().getBufferSize(),
                         _label.toUpperCase().replaceAll("[.]", "_") + "_DAEMON_PORT=" +
                             _daemonPort,
                         _label.toUpperCase().replaceAll("[.]", "_") + "_HOSTNAME=" +
                             textHostname.getText(),
                         _label.toUpperCase().replaceAll("[.]", "_") + "_PORT=" +
                             textPort.getText(),
                         _label.toUpperCase().replaceAll("[.]", "_") + "_JAVA=on",};
  }

  public String getHost() {
    class HostGetter implements Runnable {
      private String host;

      String getHost() {
        return host;
      }

      @Override
      public void run() {
        host = textHostname.getText();
      }
    }

    HostGetter hostGetter = new HostGetter();
    Display.getDefault().syncExec(hostGetter);

    return hostGetter.getHost();
  }

  public int getPort() {
    return _daemonPort;
  }

  @Override
  public void onStart() throws ASCoDTException {
    super.onStart();
    component.open();

  }
}
