##Slurm - Simple Linux Utility for Resource Management

### Basic Commands
* `sinfo` :  give an overview of the resources offered by the cluster
```
# sinfo
PARTITION    AVAIL  TIMELIMIT  NODES  STATE NODELIST
defq*           up 14-00:00:0    136  alloc node[033-168]
short           up 2-00:00:00     94  alloc node[097-190]
128gb           up 14-00:00:0     24  alloc node[041-064]
256gb           up 14-00:00:0      8  alloc node[033-040]
gpu             up 7-00:00:00     32  alloc node[001-032]
gpu-noecc       up 7-00:00:00     32  alloc node[001-032]
ivygpu          up 7-00:00:00     21  alloc node[333-353]
ivygpu-noecc    up 7-00:00:00     21  alloc node[333-353]
debug           up    2:00:00      1  alloc node991
debug           up    2:00:00      1   idle node992
```

A **partition** is a set of compute nodes (computers dedicated to ... computing,) grouped logically. Typical examples include partitions dedicated to batch processing, debugging, post processing, or visualization. *Default partition* is marked with an asterisk. 

* `sinfo -N` gives a node-oriented view
```
# sinfo -N
NODELIST       NODES    PARTITION STATE
node[001-032]     32          gpu alloc
node[001-032]     32    gpu-noecc alloc
node[033-168]    136        defq* alloc
node[033-040]      8        256gb alloc
node[041-064]     24        128gb alloc
node[097-190]     94        short alloc
node[333-353]     21 ivygpu-noecc alloc
node[333-353]     21       ivygpu alloc
node991            1        debug alloc
node992            1        debug idle
```

* `squeue` : shows the list of jobs which are currently running or pending.
```
# squeue
 JOBID PARTITION     NAME     USER ST       TIME  NODES NODELIST(REASON)
666411     256gb mpileup-  mjm1366  R   21:26:46      1 node033
666745     256gb submit.4 avoutchk  R    1:18:30      1 node037
666419     debug Jacqueli j20_rose PD       0:00      1 (PartitionTimeLimit)
668443      defq DrosoRTs zajitsch PD       0:00      1 (Resources)
668442     debug     bash zajitsch PD      43:46      1 (Priority)
```
use `squeue --user=username` or `squeue --partition=partitionname` to filter the result.

### Create a Job
The typical way of creating a job is to write a **submission script**. A submission script is a shell script, e.g. a Bash script, whose comments, if they are prefixed with SBATCH, are understood by Slurm as parameters describing resource requests and other submissions options. You can get the complete list of parameters from the sbatch manpage `man sbatch`.

```
# vim job.qsub

#!/bin/bash

#SBATCH --job-name="hello"
#SBATCH --ntasks=8
#SBATCH --time=00:05:00
#SBATCH --output=slurm-job-%j.out
#SBATCH --error=slurm-job-%j.err
#SBATCH --partition=short

mpirun -n $SLURM_NPROCS ./hello
```



* `sbatch` : **submit a job script** for later execution. The script will typically contain one or more srun commands to launch parallel tasks.

* `scancel` : **cancel a pending or running job** or job step. It can also be used to send an arbitrary signal to all processes associated with a running job or job step.




sacct is used to report job or job step accounting information about active or completed jobs.

salloc is used to allocate resources for a job in real time. Typically this is used to allocate resources and spawn a shell. The shell is then used to execute srun commands to launch parallel tasks.

sattach is used to attach standard input, output, and error plus signal capabilities to a currently running job or job step. One can attach to and detach from jobs multiple times.


sbcast is used to transfer a file from local disk to local disk on the nodes allocated to a job. This can be used to effectively use diskless compute nodes or provide improved performance relative to a shared file system.



scontrol is the administrative tool used to view and/or modify SLURM state. Note that many scontrol commands can only be executed as user root.

sinfo reports the state of partitions and nodes managed by SLURM. It has a wide variety of filtering, sorting, and formatting options.

smap reports state information for jobs, partitions, and nodes managed by SLURM, but graphically displays the information to reflect network topology.

squeue reports the state of jobs or job steps. It has a wide variety of filtering, sorting, and formatting options. By default, it reports the running jobs in priority order and then the pending jobs in priority order.

srun is used to submit a job for execution or initiate job steps in real time. srun has a wide variety of options to specify resource requirements, including: minimum and maximum node count, processor count, specific nodes to use or not use, and specific node characteristics (so much memory, disk space, certain required features, etc.). A job can contain multiple job steps executing sequentially or in parallel on independent or shared nodes within the job's node allocation.

smap reports state information for jobs, partitions, and nodes managed by SLURM, but graphically displays the information to reflect network topology.

strigger is used to set, get or view event triggers. Event triggers include things such as nodes going down or jobs approaching their time limit.

sview is a graphical user interface to get and update state information for jobs, partitions, and nodes managed by SLURM.
