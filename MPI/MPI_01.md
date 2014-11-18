# Message Passing Interface

### Parallel Programming Model
It is an abstract view of data and execution.
* **Message Passing** : MPI
  * Two-sided communication (significant communication overhead for small transactions)
  * Single Program Multiple Data
  * With locality awareness
  * Ghost cell problem

![image](./image/MP.png)

* **Shared Memory** : OpenMP
  * Simple read & write on global memory (Simplified code development)
  * Without locality awareness
  * Manipulating shared data requires synchronization

![image](./image/SM.png)

* **Distributed Shared Memory** : UPC, Titanium, X10 (not widely used)

![image](./image/DSM.png)
--------------------------------
**Note**:
* MPI is a library, not a language. MPI can be linked with C, C++, Fortran
* MPI-2 is the current version, MPI-3 is under developement

### Six Basics to Start with MPI
* **MPI_Init**      :		 Initiate an MPI computation.
* **MPI_Finalize**  :		 Terminate a computation.
* **MPI_Comm_size** :   Determine number of processes.
* **MPI_Comm_rank** :		 Determine my process identifier.
* **MPI_Send**      :		 Send a message.
* **MPI_Recv**      :		 Receive a message.

```
#include <stdio.h>
#include <mpi.h>
int main(int argc, char *argv[]) {

int rank, size;
MPI_Init(&argc, &argv); 
MPI_Comm_rank(MPI_COMM_WORLD, &rank); 
MPI_Comm_size(MPI_COMM_WORLD, &size); 

/* ... your code here ... */

printf(“Hello from node %d of %d\n”, rank,size) 
MPI_Finalize();
return 0;
}
```
￼￼
