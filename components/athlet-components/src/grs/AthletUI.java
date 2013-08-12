//
// ASCoDT - Advanced Scientific Computing Development Toolkit
//
// This file was generated by ASCoDT's simplified SIDL compiler.
//
// Authors: Tobias Weinzierl, Atanas Atanasov   
//
package grs;

import org.eclipse.swt.SWT;
import org.eclipse.swt.events.SelectionAdapter;
import org.eclipse.swt.events.SelectionEvent;
import org.eclipse.swt.layout.GridData;
import org.eclipse.swt.layout.GridLayout;
import org.eclipse.swt.widgets.Button;
import org.eclipse.swt.widgets.Composite;
import org.eclipse.swt.widgets.ExpandBar;
import org.eclipse.swt.widgets.ExpandItem;

public class AthletUI extends de.tum.ascodt.plugin.ui.tabs.UITab {
     
     public AthletUI(Athlet component){
          super(component);
     }
     /**
      * here you need to instantiate your own controls
      * use _tabFolderPage as parent
      */
     @Override
     protected void createControlGroup() {
    	GridLayout layout= new GridLayout();
 		layout.numColumns=1;

 		super.tabFolderPage.setLayout(layout);

 		final ExpandBar bar = new org.eclipse.swt.widgets.ExpandBar(super.tabFolderPage, SWT.NONE);
 		GridData gridData = new GridData();
 		gridData.horizontalAlignment = GridData.FILL;
 		gridData.verticalAlignment = GridData.FILL;
 		gridData.grabExcessHorizontalSpace = true;	
 		gridData.grabExcessVerticalSpace = true;
 		bar.setLayoutData(gridData);
 		createControlGroup(bar);
     }
     
     private void createControlGroup(ExpandBar bar) {
    	 GridLayout gridLayout = new GridLayout();
 		gridLayout.numColumns=1;

 		Composite argsComp = new Composite(bar,SWT.NONE);
 		argsComp.setLayout(gridLayout);
 		GridData textGridData = new GridData();
 		textGridData.horizontalAlignment = GridData.FILL;
 		textGridData.grabExcessHorizontalSpace = true;
 		
 		
 		
 		Button setupBtn = new Button(argsComp,SWT.LEFT);
 		setupBtn.setText("Setup");
 		setupBtn.setLayoutData(textGridData);
 		
 		setupBtn.addSelectionListener(new SelectionAdapter(){

 			@Override
 			public void widgetSelected(SelectionEvent e) {
 				getCastedComponent().setup();
 			}

 			
 		});
 		
 		Button startBtn = new Button(argsComp,SWT.LEFT);
 		startBtn.setText("Start");
 		startBtn.addSelectionListener(new SelectionAdapter(){

 			@Override
 			public void widgetSelected(SelectionEvent e) {
 				getCastedComponent().start();
 			}

 			
 		});
 		
 		final ExpandItem itemData = new ExpandItem(bar, SWT.NONE, 0);
 		bar.setSize(argsComp.computeSize(SWT.DEFAULT, SWT.DEFAULT).x,
 				SWT.DEFAULT);
 		itemData.setText("Simulation controler");
 		itemData.setHeight(argsComp.computeSize(SWT.DEFAULT, SWT.DEFAULT).y);
 		itemData.setControl(argsComp);
 		itemData.setExpanded(true);
	}
     private Athlet getCastedComponent(){
          if(_component instanceof Athlet){
               return (Athlet) _component;
          }
          return null;
     }
}
