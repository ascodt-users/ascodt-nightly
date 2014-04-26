export CCA_CFD_NS_JAVA=off
export CCA_CFD_NS_WORKERS=10
export CCA_CFD_NS_XML=StandaloneWorkbench.xml
export CCA_CFD_NS_BUFFER_SIZE=4096
/home/atanasoa/intel/impi/4.1.3.049/intel64/bin/mpiexec -np 6 ../bin/cca.cfd.NS
