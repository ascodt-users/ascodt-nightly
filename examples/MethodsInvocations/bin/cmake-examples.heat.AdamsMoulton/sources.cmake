SET(SRC_COMP
     ../../components/java/examples/heat/AdamsMoultonJNIProxy.cpp
     ../../components/java/examples/heat/AdamsMoultonAbstractImplementation.cpp
     ../../src/examples/heat/AdamsMoultonImplementation.cpp)

set(SRC_COMP
   	${SRC_COMP}
   	../../components/java/examples/heat/SolverNative2JavaPlainPort.cpp 
   	../../components/java/examples/heat/SolverNative2NativePlainPort.cpp
	../../components/java/examples/heat/SolverCxx2SocketPlainPort.cpp
	../../components/java/examples/heat/SolverC2CxxSocketPlainPort.cpp 
	../../components/java/examples/heat/SolverNativeDispatcher.cpp
	../../components/java/examples/heat/SolverNativeSocketDispatcher.cpp
	../../components/java/examples/heat/SolverCProxyNativeSocketDispatcher.cpp
)
