SET(SRC_COMP
     ../../components/java/examples/heat/ImplicitEulerJNIProxy.cpp
     ../../components/java/examples/heat/ImplicitEulerAbstractImplementation.cpp
     ../../src/examples/heat/ImplicitEulerImplementation.cpp)

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
