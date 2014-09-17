export CCA_CFD_LB_JAVA=off
export CCA_CFD_LB_WORKERS=20
export CCA_CFD_LB_XML=StandaloneWorkbench.xml
export CCA_CFD_LB_BUFFER_SIZE=4096
/home/atanasoa/intel/impi/4.1.3.049/intel64/bin/mpiexec -np 1 ../bin/cca.cfd.LB #/work_fast/atanasoa/Programme/workspace_new/LB_NS_EOF/trunk/src/configurationFiles/conf_channel_cpl_lb.xml
