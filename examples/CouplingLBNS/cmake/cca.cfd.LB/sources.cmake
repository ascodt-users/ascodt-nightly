SET(CPP_FILES
     ../../components/java/cca/cfd/LBAbstractImplementation.cpp
     ../../src/cca/cfd/LBImplementation.cpp
     ../../components/java/cca/cfd/LBC2CxxProxy.cpp 
     
)

set(CPP_FILES
   	${CPP_FILES}
   	../../components/java/cca/cfd/NSSolverNative2JavaPlainPort.cpp 
   	../../components/java/cca/cfd/NSSolverNative2NativePlainPort.cpp
	../../components/java/cca/cfd/NSSolverCxx2SocketPlainPort.cpp
	../../components/java/cca/cfd/NSSolverC2CxxSocketPlainPort.cpp 
	../../components/java/cca/cfd/NSSolverNativeDispatcher.cpp
	../../components/java/cca/cfd/NSSolverNativeSocketDispatcher.cpp
	../../components/java/cca/cfd/NSSolverCProxyNativeSocketDispatcher.cpp
)
