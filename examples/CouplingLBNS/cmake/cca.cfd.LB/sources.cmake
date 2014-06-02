SET(CPP_FILES
     ../../components/c++/cca/cfd/LBAbstractImplementation.cpp
     ../../src/cca/cfd/LBImplementation.cpp
     ../../components/c++/cca/cfd/LBC2CxxProxy.cpp 
     ../../components/c++/tinyxml_ascodt.cpp
)

set(CPP_FILES
   	${CPP_FILES}
   	../../components/c++/cca/cfd/NSSolverNative2JavaPlainPort.cpp 
   	../../components/c++/cca/cfd/NSSolverNative2NativePlainPort.cpp
	../../components/c++/cca/cfd/NSSolverCxx2SocketPlainPort.cpp
	../../components/c++/cca/cfd/NSSolverC2CxxSocketPlainPort.cpp 
	../../components/c++/cca/cfd/NSSolverNativeDispatcher.cpp
	../../components/c++/cca/cfd/NSSolverNativeSocketDispatcher.cpp
	../../components/c++/cca/cfd/NSSolverCProxyNativeSocketDispatcher.cpp
)
