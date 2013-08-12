package de.tum.ascodt.sidlcompiler.backend;

import java.io.File;
import java.net.URL;
import java.util.HashMap;

import org.eclipse.core.runtime.Assert;

import de.tum.ascodt.plugin.utils.exceptions.ErrorWriterDevice;
import de.tum.ascodt.plugin.utils.tracing.Trace;
import de.tum.ascodt.sidlcompiler.astproperties.ExclusivelyInParameters;
import de.tum.ascodt.sidlcompiler.astproperties.GetParameterList;
import de.tum.ascodt.sidlcompiler.astproperties.GetProvidesAndUsesPortsOfComponent;
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

public class CreateSocketProxyForCxx extends de.tum.ascodt.sidlcompiler.frontend.analysis.DepthFirstAdapter{
	private Trace                      _trace = new Trace(CreateSocketProxyForCxx.class.getCanonicalName());

	private java.util.Stack< TemplateFile >   _templateFilesOfC2CxxProxyImplementation;
	private java.util.Stack< TemplateFile >   _templateFilesOfC2CxxProxyHeader;
	private java.util.Stack< TemplateFile >   _templateFilesProvidesPorts;
	private java.util.Stack< TemplateFile >   _templateFilesUsesPortsForC2Cxx;

	private java.util.Stack< String > 			  _serverInvokers;
	private java.util.Stack< String > 		    _clientInvokers;

	private URL 															_generatedFilesDirectory;
	private String[]                          _namespace;
	private SymbolTable                       _symbolTable;
	private String _fullQualifiedName;
	private boolean                           _generateProvidesMethods;
	private HashMap<String, Integer> _offset_map;

	//private String _providePortName;

	private String _fullQualifiedPortName;
	
	CreateSocketProxyForCxx(
			SymbolTable symbolTable,
			URL userImplementationsDestinationDirectory,
			URL generatedFilesDirectory,
			String[] namespace,
			HashMap<String, Integer> offset_map) {
		_templateFilesOfC2CxxProxyImplementation = new java.util.Stack< TemplateFile >();
		_templateFilesOfC2CxxProxyHeader = new java.util.Stack< TemplateFile >();
		_templateFilesProvidesPorts = new java.util.Stack< TemplateFile >();
		_templateFilesUsesPortsForC2Cxx = new java.util.Stack< TemplateFile >();
		_serverInvokers = new java.util.Stack< String >();
		_clientInvokers = new java.util.Stack< String >();
		_generatedFilesDirectory  = generatedFilesDirectory;
		_namespace            = namespace;
		_symbolTable          = symbolTable;
		_offset_map					  = offset_map;
	
	}

	public void inAClassPackageElement(AClassPackageElement node) {
		_trace.in( "inAClassPackageElement(...)", "open new port interface" );
		try {
			String  componentName              = node.getName().getText();
			_fullQualifiedName													 = _symbolTable.getScope(node).getFullQualifiedName(componentName) ;

			String  templateFileForC2CxxProxyComponentImplemention = "native-component-c2cxx-socket-implementation.template";
			String  templateFileForC2CxxProxyComponentHeader = "native-component-c2cxx-socket-header.template";
			
			String  destinationFileForC2CxxProxyImplementation 						 = _generatedFilesDirectory.toString() + File.separatorChar + _fullQualifiedName.replaceAll("[.]", "/") + "C2CxxProxy.cpp";
			String  destinationFileForC2CxxProxyHeader 						 = _generatedFilesDirectory.toString() + File.separatorChar + _fullQualifiedName.replaceAll("[.]", "/") + "C2CxxProxy.h";
			

			_templateFilesOfC2CxxProxyImplementation.push(
					new TemplateFile( templateFileForC2CxxProxyComponentImplemention, destinationFileForC2CxxProxyImplementation, _namespace, TemplateFile.getLanguageConfigurationForJNI() ,true)
					);
			_templateFilesOfC2CxxProxyHeader.push(
					new TemplateFile( templateFileForC2CxxProxyComponentHeader, destinationFileForC2CxxProxyHeader, _namespace, TemplateFile.getLanguageConfigurationForJNI() ,true)
					);
			

			_templateFilesOfC2CxxProxyImplementation.peek().addMapping( "__COMPONENT_NAME__", componentName.toLowerCase() );
			_templateFilesOfC2CxxProxyImplementation.peek().addMapping( "__COMPONENT_NAME_4WIN__", componentName.toUpperCase() );
			_templateFilesOfC2CxxProxyImplementation.peek().addMapping( "__COMPONENT_NAME_ENV__",componentName.toUpperCase());
			_templateFilesOfC2CxxProxyImplementation.peek().addMapping( "__CXX_FULL_QUALIFIED_NAME__",_fullQualifiedName.replaceAll("[.]", "::"));
			_templateFilesOfC2CxxProxyImplementation.peek().addMapping( "__PATH_FULL_QUALIFIED_NAME__",_fullQualifiedName.replaceAll("[.]", "/"));
			_templateFilesOfC2CxxProxyHeader.peek().addMapping( "__PATH_FULL_QUALIFIED_NAME__",_fullQualifiedName.replaceAll("[.]", "/"));
			_templateFilesOfC2CxxProxyHeader.peek().addMapping( "__COMPONENT_NAME_ENV__",componentName.toUpperCase());
			_templateFilesOfC2CxxProxyHeader.peek().open();
			_generateProvidesMethods = true;

			for ( PUserDefinedType definedType: node.getProvides() ) {
				definedType.apply(this);

			}
			_generateProvidesMethods = false;
		}catch (ASCoDTException  e ) {
			ErrorWriterDevice.getInstance().showError(getClass().getName(), "inAInterfacePackageElement(...)", e);
		}

		_trace.out( "inAClassPackageElement(...)", "open new port interface" );
	}

	public void inAUses(AUses node) {
		_trace.in( "inAUses(AUses)", node.toString() );
		GetProvidesAndUsesPortsOfComponent getPorts = new GetProvidesAndUsesPortsOfComponent();
		node.apply( getPorts );
		String fullQualifiedpPortTypeForC = getPorts.getUsesPorts("", "::");
		String fullQualifiedpPortType = getPorts.getUsesPorts("", ".");
		String fullQualifiedpPortTypeAsPath = getPorts.getUsesPorts("", "/");
		String portName = node.getAs().getText();
		String templateFileForC2Cxx    = "native-component-c2cxx-socket-implementation-uses-ports.template";
		try {
			TemplateFile templateForC2Cxx = new TemplateFile( _templateFilesOfC2CxxProxyImplementation.peek(), templateFileForC2Cxx );
			templateForC2Cxx.addMapping( "__USES_PORT_AS__",   portName );
			templateForC2Cxx.addMapping( "__USES_PORT_AS_4WIN__",portName.toUpperCase());
			templateForC2Cxx.addMapping( "__CXX_FULL_QUALIFIED_PORT_TYPE__", fullQualifiedpPortTypeForC );
			templateForC2Cxx.addMapping("__PATH_FULL_QUALIFIED_PORT_TYPE__",fullQualifiedpPortTypeAsPath);
			_templateFilesUsesPortsForC2Cxx.push(templateForC2Cxx);
			_serverInvokers.push("invokers["+(_offset_map.get(fullQualifiedpPortType+"createPort"))+"]=invoker_create_client_port_for_"+portName+";\n");
			_serverInvokers.push("invokers["+(_offset_map.get(fullQualifiedpPortType+"connectPort"))+"]=invoker_connect_client_dispatcher_"+portName+";\n");
			_serverInvokers.push("invokers["+(_offset_map.get(fullQualifiedpPortType+"disconnectPort"))+"]=invoker_disconnect_client_dispatcher_"+portName+";\n");
			_clientInvokers.push("invokers["+(_offset_map.get(fullQualifiedpPortType+"createPort"))+"]=invoker_create_client_port_for_"+portName+";\n");
			_clientInvokers.push("invokers["+(_offset_map.get(fullQualifiedpPortType+"connectPort"))+"]=invoker_connect_client_dispatcher_"+portName+";\n");
			_clientInvokers.push("invokers["+(_offset_map.get(fullQualifiedpPortType+"disconnectPort"))+"]=invoker_disconnect_client_dispatcher_"+portName+";\n");
		}catch (ASCoDTException  e ) {
			ErrorWriterDevice.getInstance().showError(getClass().getName(), "inAInterfacePackageElement(...)", e);
		}
		
		_trace.out( "inAUses(AUses)" );
	}
	/**
	 * Close the output streams.
	 */
	public void outAClassPackageElement(AClassPackageElement node) {
		Assert.isTrue(_templateFilesOfC2CxxProxyImplementation.size()==1);
		Assert.isTrue(_templateFilesOfC2CxxProxyHeader.size()==1);
		try {
			String serverInvokers="";
			String clientInvokers="";
			while(!_serverInvokers.isEmpty()){
				serverInvokers+=_serverInvokers.peek();
				_serverInvokers.pop();
			}
			while(!_clientInvokers.isEmpty()){
				clientInvokers+=_clientInvokers.peek();
				_clientInvokers.pop();
			}
			_templateFilesOfC2CxxProxyImplementation.peek().addMapping("__SET_SERVER_INVOKERS__", serverInvokers);
			_templateFilesOfC2CxxProxyImplementation.peek().addMapping("__SET_CLIENT_INVOKERS__", clientInvokers);
			_templateFilesOfC2CxxProxyImplementation.peek().addMapping("__CLIENT_METHODS__", ""+(2+_offset_map.size()));
			_templateFilesOfC2CxxProxyImplementation.peek().addMapping("__SERVER_METHODS__", ""+(2+_offset_map.size()));
			_templateFilesOfC2CxxProxyImplementation.peek().open();
			while(!_templateFilesUsesPortsForC2Cxx.isEmpty()){
				_templateFilesUsesPortsForC2Cxx.peek().open();
				_templateFilesUsesPortsForC2Cxx.peek().close();
				_templateFilesUsesPortsForC2Cxx.pop();
			}
			
			while(!_templateFilesProvidesPorts.isEmpty()){
				_templateFilesProvidesPorts.peek().open();
				_templateFilesProvidesPorts.peek().close();
				_templateFilesProvidesPorts.pop();
			}
			
			_templateFilesOfC2CxxProxyImplementation.peek().close();
			_templateFilesOfC2CxxProxyHeader.peek().close();
		}
		catch (ASCoDTException  e ) {
			ErrorWriterDevice.getInstance().showError(getClass().getName(), "inAInterfacePackageElement(...)", e);
		}
		_templateFilesOfC2CxxProxyImplementation.pop();
		_templateFilesOfC2CxxProxyHeader.pop();
	}

	public void inAOperation(AOperation node) {
		Assert.isTrue( _generateProvidesMethods );
		try {
			_serverInvokers.push("invokers["+(_offset_map.get(_fullQualifiedPortName+node.getName().getText()))+"]=invoker_"+node.getName().getText()+";\n");
			_clientInvokers.push("invokers["+(_offset_map.get(_fullQualifiedPortName+node.getName().getText()))+"]=invoker_"+node.getName().getText()+";\n");
			
			String templateC2CxxProxyImplementationFile    = "native-component-c2cxx-socket-implementation-provides-port.template";
			

			TemplateFile c2CxxProxyImplementationTemplate = new TemplateFile( _templateFilesOfC2CxxProxyImplementation.peek(), templateC2CxxProxyImplementationFile );
			

			ExclusivelyInParameters onlyInParameters = new ExclusivelyInParameters();
			node.apply( onlyInParameters );

			GetParameterList parameterList = new GetParameterList(_symbolTable.getScope(node));
			node.apply( parameterList );
			c2CxxProxyImplementationTemplate.addMapping("__SOCKET_PULL__", parameterList.pullInFromSocketForCxx());

			c2CxxProxyImplementationTemplate.addMapping("__SOCKET_PUSH__", parameterList.pushOutToSocketForCxx());
			c2CxxProxyImplementationTemplate.addMapping("__OPERATION_PARAMETERS_LIST__",parameterList.getParameterListInJNI(onlyInParameters.areAllParametersInParameters()) );
			c2CxxProxyImplementationTemplate.addMapping("__OPERATION_NAME__", node.getName().getText());
			c2CxxProxyImplementationTemplate.addMapping("__OPERATION_NAME_4WIN__", node.getName().getText().toUpperCase());
			
			c2CxxProxyImplementationTemplate.addMapping("__OPERATION_PARAMETERS_LIST_C2F__",parameterList.getParameterListInC2F());
			c2CxxProxyImplementationTemplate.addMapping("__FUNCTION_CALL_PARAMETERS_LIST__",parameterList.getFunctionCallListInCxx());
			
			_templateFilesProvidesPorts.add(c2CxxProxyImplementationTemplate);

		}
		catch (ASCoDTException  e ) {
			ErrorWriterDevice.getInstance().showError(getClass().getName(), "inAInterfacePackageElement(...)", e);
		}
	}

	public void inAUserDefinedType(AUserDefinedType node) {
		String fullQualifiedSymbol = Scope.getSymbol(node);
		AInterfacePackageElement interfaceNode=_symbolTable.getScope(node).getInterfaceDefinition(fullQualifiedSymbol);
		String portName                      = interfaceNode.getName().getText();
		_fullQualifiedPortName = _symbolTable.getScope(interfaceNode).getFullQualifiedName(portName);
		if (_generateProvidesMethods) {
			
			if(interfaceNode!=null)
				interfaceNode.apply(this);
		}
	}
}