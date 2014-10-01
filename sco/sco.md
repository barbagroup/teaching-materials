#Single Core Optimization
--------------------------

##Introduction: *Performance of Computing Platforms.*

In the last few years the exponential increase in CPU frequency results in a "free" speedup for numerical software. In other words, legacy codes written for a predecessor will run faster without any extra effort. However, the performance of computers has evolved due to increases in the processors' parallelism (vector processing, multi-threading, SIMD, multicore, etc). 

Ideally, compilers would take care of this porblem by automatically vectorizing and parallelizing existing source code. However, this not usually happens. Most time taking advantage of platform's available parallelism often requires an algorithm structured differently than
the one that would be used in the corresponding sequential code.

Similar problems are caused by the computer's memory hierarchy (see Fig 1.), independently of the available parallelism. Moving data from and to memory has become the bottleneck. The memory hierarchy, aims to address this problem, but can only work if data is accessed in a suitable order. Compilers are inherently limited in optimizing for the memory hirarchy since this optimizations may require algorithm restructuring. 

<center>![image](./images/mem_hier.png)</center>

Adding to these problems is the fact that CPU frequency scaling is approaching its en due to limits to the chip's possible power density (see Fig 2.). This implies the end of "automatic speedup"; then, in order to obtain performance gains, we need to parallelize. 

<center>![image](./images/intel_performance.png)</center>


The first step before parallelize code is to optimize our sequential code. This type of optimizations involves not only how to use well the memory resources but also how to avoid, when it is possible,  compute more instructions than the ones we need.

Before start with some examples we are going to introduce some helpful tools which allow us:

* To know a new tool to meassure time (in sec) in an easy way.
* To know information about our cpu resources
* To know where is the bottleneck in our code (target to optimize)
* To know information about cache-references, cache-misses, time, etc.

### omp_get_wtime

(Need to install libgomp1, the GCC OpenMP (GOMP) support library)

Elapsed wall clock time in seconds. The time is measured per thread, no guarantee can be made that two distinct threads measure the same time. Time is measured from some "time in the past", which is an arbitrary time guaranteed not to change during the execution of the program.

C/C++:
    Prototype:     double omp_get_wtime(void); 

To use this tool in our code we should add:

```
	#include <omp.h>
```

When we compile:

```
	gcc -o our_program our_program.c -fopenmp -lgomp 
```

In the examples you can see how we use this tool to meassure time. However, [here](http://msdn.microsoft.com/en-us/library/x721b5yk.aspx) is a general example of how to use this function.

### lscpu and cat /proc/cpuinfo

If you type these two commands in your terminal you can obtain useful information about your cpu resources that would be useful.

Try it and experiment by yourself!!!

### gprof (GNU profiler)

Profiling allows you to learn where your program spent its time and which functions called which other functions while it was executing. This information can show you which pieces of your program are slower than you expected, and might be candidates for rewriting to make your program execute faster.

How to use it: 

**Step 1:**


Compile and link your program with profiling enabled, when we compile we should introduce the flag -pg

```
	gcc -o our_program our_program.c -pg
```

**Step 2:**

Execute your program to generate a profile data file


```
	./our_program 
```

You program will write the profile data into a file called `gmon.out' just before exiting.

**Step 3:**

Run `gprof` to analyze the profile data

After you have a profile data file `gmon.out'`, you can run gprof to interpret the information in it. The gprof program prints a flat profile and a call graph on standard output. Typically you would redirect the output of `gprof` into a file with `>`. 

```
	 gprof our_program gmon.out > profile.txt
```

Then `profile.txt` is going to contain lot of useful information but the first lines should look like this:

```
    %       cumulative    self            self     total
    time     seconds    seconds   calls  ms/call  ms/call   name

    92.68      0.38       0.38      1    380.00    380.00   function2
    7.32       0.41       0.03      1     30.00     30.00   function1
```

You can try using gprof in your own program and see where is the bootleneck of your code. 

For more information about `gprof`, [here](https://www.cs.utah.edu/dept/old/texinfo/as/gprof.html) there is a manual.


### perf (Linux profiling with performance counters)

The perf tool offers a rich set of commands to collect and analyze performance and trace data.

First we need to install perf so:

```
    sudo apt-get install linux-tools-common
```

Common comands:

 * perf stat: obtain event counts
 * perf record: record events for later reporting
 * perf report: break down events by process, function, etc.
 * perf annotate: annotate assembly or source code with event counts

If we want to measure more than one event, simply provide a comma separated list with no space, e.g: 

```
    perf stat -e instructions,cache-misses,cache-references ./our_program
```

To learn more about perf, click [here](https://perf.wiki.kernel.org/index.php/Tutorial)


#Let's start with optimizations

1. Without modifying code - using compiler flags

    Try what happend if you use -O0, -O1, -O2, -O3, -Ofast .
    To see which flags are enable and disable with these flags write in
    the command line:
    
```
    gcc -c -Q -O3 --help=optimizers
```
    
    If you want to add a flag that is not include in the -OX you choose
    you can add it directly as a flag when you compile.
    
    In folder examples, you can find the code (example_1.c) try to run it
    and see what happens using different flags.
    There are also available the assembly codes so you can see the magic 
    of the compiler.

2. If you can, avoid unnecessary if statements.

For example: non-periodic boundary conditions
    
```C
        1 void compute1(float a[], const unsigned int N) {
        2     for (unsigned int i=0; i<N; ++i) {
        3         if (i==0) {
        4             a[i] = a[i+1]/2;
        5         } else if (i==N-1) {
        6             a[i] = a[i-1]/2;
        7         } else { // 0<i<N-1
        8             a[i] = (a[i-1]+a[i+1])/2;
        9         }
        10     }
        11 }
    
``` 
    
Is better if we write it like this:
    

```C
    1 void compute2(float a[], const unsigned int N) {
    2     a[0]=a[1]/2;
    3     for (unsigned int i=1; i<N-1; ++i) {
    4         a[i] = (a[i-1]+a[i+1])/2;
    5     }
    6     a[N-1]=a[N-2]/2;
    7 }
``` 

In folder examples, you can find the code (example_2.c) which justify this. Besides, you can try it with different flags of compilation and see what happend.

###Note:

These codes are easy codes for the compiler, most times happens that the compiler does not optimize automatically so you need to work in the code. 
    
--------------------------------------------------------------------------
What makes sense to do?

* A little of loop unrolling: 
        Disassemble dependencies using records to achieve more Instruction 
        Level Parallelism (ILP).
        It has a limit: *register spilling*.

* Expose paralellism, when is possible, so the compiler can vectorize 
automatically.

* Cache Optimizations.
    -Rearranging loops..
    -Cache blocking.
    -Memory alignment.

* Indicate there is no aliasing.

--------------------------------------------------------------------------

###Interesting examples:

#### B = A^t (transposed)

    * Arithmetic intensity = number of FLOPs per memory access = 0/ (2 ∗ L^2) = 0

    * We have a memory bound problem.

The matrix in the memory looks like:

<center>![image](./images/mat_in_mem.jpg)</center>

###Naïve code:

```C 
    1 #define L (1<<11)
    2 
    3 float a[L][L], b[L][L];
    4 
    5 int main(void) {
    6     unsigned int i=0, j=0;
    7     for (i=0; i<L; ++i)
    8             for (j=0; j<L; ++j)
    9                 b[j][i] = a[i][j];
    10     return (int)b[(int)b[0][2]][(int)b[2][0]];
    11 }
```
Code available in folder examples as `mtxtransp1.c` 

If we run this code with perf (-r 4 means run 4 times and do an average), we obtain:

We also compile with -O0 to avoid optimizations and see the raw behaviour.

```
perf stat -r 4 -e instructions,cycles,cache-references,cache-misses ./mtxtransp1
```

```
Performance counter stats for './mtxtransp1' (4 runs):

       67.429.332 instructions              #    0,14  insns per cycle          ( +-  8,75% ) [75,45%]
       483.118.384 cycles                     ( +-  1,50% ) [75,39%]
       4.657.399 cache-references                                              ( +-  0,30% ) [75,73%]
       4.545.049 cache-misses              #   97,588 % of all cache refs      ( +-  1,11% ) [49,25%]

       0,233285113 seconds time elapsed                                          ( +-  3,62% )

```

###Doing cache blocking:

Code `mtxtransp2.c` in folder examples, we obtain:

```
Performance counter stats for './mtxtransp2' (4 runs):

        83.762.004 instructions              #    0,59  insns per cycle          ( +-  1,02% ) [75,36%]
       142.685.092 cycles                     ( +-  1,08% ) [76,10%]
         4.792.723 cache-references                                              ( +-  1,41% ) [77,15%]
           650.754 cache-misses              #   13,578 % of all cache refs      ( +-  2,30% ) [48,54%]

       0,067984763 seconds time elapsed  
```

*Speedup*: 0.233/0.067 = 3.5x :D

If now we run both codes with -O3 we obtain: 

*Speedup*: 0.19/0.046 = 4.1x :D :D

You can try different values of Bx and By and see how the performance is modified; but we are lucky because someone run different possible combinations and found the best blocking for this problem is Bx= 2^1 and By=2^8.

<center>![image](./images/best_blocking.png)</center>

*Speedup*: 0.19/0.035 = 5.4x :D :D :D

#### C = AxB (matrix-matrix)

(show slids and translate)

##Limits and Problems:

*[Roof line model](http://www.eecs.berkeley.edu/Pubs/TechRpts/2008/EECS-2008-134.pdf)


## References
[1](http://www.agner.org/optimize/optimizing_cpp.pdf) Optimizing software in C++. Agner Fog. Technical University of Denmark.

[2](http://users.ece.cmu.edu/~franzf/papers/gttse07.pdf) How To Write Fast Numerical Code: A Small Introduction. Srinivas Chellappa, Franz Franchetti, and Markus Puschel

[3] Classes notes from "Computación paralela - 2014 FaMAF-UNC". Nicolás Wolowick


















 

