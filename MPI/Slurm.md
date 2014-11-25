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

* `sbatch` : **submit a job script** for later execution. 
```
$ sbatch job.qsub
sbatch: Submitted batch job 666827
```

* `scancel` : **cancel a pending or running job** .
```
$ scancel 666827
```

### Note:
* running a multi-process program (SPMD paradigm, e.g. with MPI)
```
#SBATCH --ntasks=4
```

* running a multithreaded program (shared memory paradigm, e.g. with OpenMP or pthreads)
```
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=4
```
In the Slurm context, a task is to be understood as a process. So a multi-process program is made of several tasks. By contrast, a multithreaded program is composed of only one task, which uses several CPUs.


