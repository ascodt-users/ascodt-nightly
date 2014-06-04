export CCA_CFD_LB_JAVA=off
export CCA_CFD_LB_WORKERS=80
export CCA_CFD_LB_XML=/home/hpc/pr63so/lu26hij3/workspace/ascodt-nightly/examples/CouplingLBNS/workspace/StandaloneWorkbench.xml
export CCA_CFD_LB_BUFFER_SIZE=8192
export CCA_CFD_LB_NET_INTERFACE=ib0
export I_MPI_JOB_SIGNAL_PROPAGATION=yes
export I_MPI_DAPL_UD=1
export I_MPI_DAPL_UD_RDMA_MIXED=1
export I_MPI_DAPL_CONN_EVD_SIZE=10000

#export I_MPI_DAPL_EAGER_MESSAGE_AGGREGATION=0
mpiexec.hydra -genv OMP_NUM_THREADS 2 -np 1 -ppn 1  /home/hpc/pr63so/lu26hij3/workspace/ascodt-nightly/examples/CouplingLBNS/bin/cca.cfd.LB
