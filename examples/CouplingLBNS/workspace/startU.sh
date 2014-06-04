export CCA_CFD_UEKERMANNDRIVER_JAVA=off
export CCA_CFD_UEKERMANNDRIVER_WORKERS=10
export CCA_CFD_UEKERMANNDRIVER_XML=/home/hpc/pr63so/lu26hij3/workspace/ascodt-nightly/examples/CouplingLBNS/workspace/StandaloneWorkbench.xml
export CCA_CFD_UEKERMANNDRIVER_BUFFER_SIZE=8192
export I_MPI_JOB_SIGNAL_PROPAGATION=yes
export I_MPI_DAPL_UD=1
#export I_MPI_DAPL_EAGER_MESSAGE_AGGREGATION=0
#export I_MPI_DAPL_UD_RDMA_MIXED=0
#export I_MPI_DAPL_UD=0
#export I_MPI_DAPL_CONN_EVD_SIZE=10000

#export I_MPI_DAPL_EAGER_MESSAGE_AGGREGATION=0
export I_MPI_DAPL_UD_RDMA_MIXED=1
rm /home/hpc/pr63so/lu26hij3/ascodt-nightly/examples/CouplingLBNS/workspace/cca.cfd.UekermannDriver.conf
mpiexec.hydra -np 1 /home/hpc/pr63so/lu26hij3/workspace/ascodt-nightly/examples/CouplingLBNS/bin/cca.cfd.UekermannDriver ~/conf_channel_cpl.xml
