SET(SRC_COMP
     ../../components/java/de/tum/DriverComponentAbstractImplementation.cpp
     ../../src/de/tum/DriverComponentImplementation.cpp
     ../../components/java/de/tum/DriverComponentC2CxxProxy.cpp 
     
)

set(SRC_COMP
   	${SRC_COMP}
   	../../components/java/de/tum/FooBarNative2JavaPlainPort.cpp 
   	../../components/java/de/tum/FooBarNative2NativePlainPort.cpp
	../../components/java/de/tum/FooBarCxx2SocketPlainPort.cpp
	../../components/java/de/tum/FooBarC2CxxSocketPlainPort.cpp 
	../../components/java/de/tum/FooBarNativeDispatcher.cpp
	../../components/java/de/tum/FooBarNativeSocketDispatcher.cpp
	../../components/java/de/tum/FooBarCProxyNativeSocketDispatcher.cpp
)
