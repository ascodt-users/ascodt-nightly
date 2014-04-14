SET(CPP_FILES
     ../../components/java/cca/cfd/NSAbstractImplementation.cpp
     ../../src/cca/cfd/NSImplementation.cpp
     ../../components/java/cca/cfd/NSC2CxxProxy.cpp 
     
)

set(CPP_FILES
   	${CPP_FILES}
   	../../components/java/cca/cfd/LBSolverNative2JavaPlainPort.cpp 
   	../../components/java/cca/cfd/LBSolverNative2NativePlainPort.cpp
	../../components/java/cca/cfd/LBSolverCxx2SocketPlainPort.cpp
	../../components/java/cca/cfd/LBSolverC2CxxSocketPlainPort.cpp 
	../../components/java/cca/cfd/LBSolverNativeDispatcher.cpp
	../../components/java/cca/cfd/LBSolverNativeSocketDispatcher.cpp
	../../components/java/cca/cfd/LBSolverCProxyNativeSocketDispatcher.cpp
)
