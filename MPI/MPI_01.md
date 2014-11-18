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

* **Distributed Shared Memory** : 

![image](./image/DSM.png)

* **Data Parallel** : High Performance Fortran
