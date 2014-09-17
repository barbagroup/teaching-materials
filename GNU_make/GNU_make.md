# Introduction to GNU ***make***

---------------------------------------------------
## Why Do We Need *make*? What is *make*?

Consider the following example. If the program is composed of 3 files:
  
<table>
	<tr>
		<td>main.c</td>
		<td>PrintHello.c</td>
		<td>HaHa.h</td>
	</tr>

	<tr>
		<td>
			&nbsp;#include "HaHa.h" <br>
			&nbsp;int main(void) <br>
			&nbsp;{ <br>
    			&nbsp;	&nbsp;&nbsp;&nbsp;&nbsp;PrintHello(); <br>
    			&nbsp;	&nbsp;&nbsp;&nbsp;&nbsp;return 0; <br>
			&nbsp;} <br>
		</td>

		<td>
			&nbsp;#include <stdio.h> <br>
			&nbsp;void PrintHello(void) <br>
			&nbsp;{ <br>
    			&nbsp;	&nbsp;&nbsp;&nbsp;&nbsp;printf("Hello World!\n"); <br>
    			&nbsp;	&nbsp;&nbsp;&nbsp;&nbsp;return; <br>
			&nbsp;} <br>
		</td>

		<td>
			&nbsp;void PrintHello(void);<br><br><br><br><br><br>
		</td>
	</tr>
</table>

The standard procedure of the compilation is:

```C
	$ gcc -g3 -Wall -pedantic-errors -o PrintHello.o PrintHello.c -c
	$ gcc -g3 -Wall -pedantic-errors -o main.o main.c -c
	$ gcc -g3 -Wall -pedantic-errors -o binary main.o PrintHello.o
``` 

It looks fine because there are only 3 commands. But how if we have 10, 50, 100, or even more source files? Manually compiling each source file seems impractical. When the relationship between each sourcefile becomes more complicated, it is more difficult to manually compile them.

How about if we want to re-built this program after some modifications on source files? Though we can re-compile the modified source files only, it may still takes long time to do so when there are lots of modified files. That's why we need a tool to help us automatically determine how to build/re-build the program. That tool is ***make***.

>"The ***make*** utility automatically determines which pieces of a large program need to be recompiled, and issues commands to recompile them."            *~ p.1, GNU Make Manual[1]*

>"A ***make*** utility is a controller that controls how the executable and other non-source files (like objective files or libraries) be generated from source files" ~*[2]*.

Furthermore, usually we have to change the compiling flags for switching between several building modes, such as *release mode* or *debug mode*. It is not an efficient way to type those complicated flags repeatedly. We can easily switch the building mode by ***make***. By combining ***make*** with some simple shell script, ***make*** can also help users manage the built files or do something like cleaning all built files by one simple command.

Most visualized IDEs in Windows system have their own ***make*** utilities behind the GUI. However, for Linux users, we have to use standalone ***make*** utilities in CLI. There are several standalone ***make*** utilities: SunPro make, pmake, GNU make, nmake etc.  The ***GNU make*** is a standard built-in tool in Linux. We will introduce ***GNU make*** here.

-------------------------------
## Basic Working flow of the *make* 

The ***make*** follows the rules defined in a script file call ***makefile***. The basic component in a makefile is call ***target***. It looks like:  

```
	target name: dependencies of this target
	< TAB >	shell commands that will be executed for this target
```

***target name*** : 1) the name of the file outputed after executing this target, or 2) just the name of this action.

***dependencies*** : the files that this target depends on; before the ***make*** execute this target, it will first check whether the dependencies exist or whether they are up-to-date.

***commands*** : the shell commands that will be executed in this target. For example, a compilation command.


When we execute the command `$ make` in a terminal,  

1. the ***make*** will search the current folder for the **makefile**.  
2. After it locates the makefile, it will execute the first target in the **makefile** by default.  
3. And then it checks the dependencies, goes to the target that output the dependencies if needed, and finally goes back to the first target and finish it.  

The ***make*** will automatically check the version of files to determine if the files need to be re-generated: if a target is newer than all dependencies, the target won't be re-generated. 

We can also use another name for the file contains targets or directly execute specific target from CLI. Just use these commands:

```
	$ make -f <other file name>
```

```
	$ make <target name>
```

### Ex 1: A Simplest Makefile
The basic makefile for the program we mentioned in the beginning may looks like this:  

```makefile  
	 1 #======================================================================  
	 2 # Title: ex1  
	 3 # Purpose: A Simplest Makefile  
	 4 #======================================================================
	 5
	 6 ex1: PrintHello.o main.o
	 7     gcc -g3 -Wall -pedantic-errors -o ex1 main.o PrintHello.o
	 8 PrintHello.o: PrintHello.c
	 9     gcc -g3 -Wall -pedantic-errors -o PrintHello.o PrintHello.c -c
	10 main.o: main.c HaHa.h
	11     gcc -g3 -Wall -pedantic-errors -o main.o main.c -c
	12 clean:
	13     rm ex1 main.o PrintHello.o
	14
	15 #=============================End of File============================== 
```

In this file, there are 3 main targets: **ex1**, **PrintHello.o**, and **main.o**.  Because the command of these three targets all output files, the name of these three target are also the name of the output files from these target. Each time we execute the command ```$ make```, the ***make*** will go through the following steps.  

**Step 1. : **  
The ***make*** starts from the **target ex1** by default. It will first check whether the dependencies need to be re-generated, or says, are update-to-date. In this case, it will check the **file PrintHello.o** first and then the **file main.o**.

**Step 2. : **  
The ***make*** goes to the **target PrintHello.o**. It won't check whether the dependency needs to be re-generated or not, because the dependency is now a source file, i.e. **PrintHello.c**. It will then check the version of the **file PrintHello.o**. If the **PrintHello.c** is newer than the **file PrintHello.o**, the shell commands of this target -- ```gcc -g3 -Wall -pedantic-errors -o PrintHello.o PrintHello.c -c``` will be executed. The **file PrintHello.o** thus is updated. Otherwise, if **PrintHello.c** is older than the **file PrintHello.o**, nothing will happen. Of course, if **PrintHello.o** doesn't exist, ***make*** still executes the shell command to generate that. 

**Step 3. : ** 
Almost the same with Step 2, but the target now is **main.o**.

**Step 4. :**  
Finally, the ***make*** goes back to the **target ex1** and then check whether the dependencies now are newer than the **file ex1** or not. If it is true, or the **file ex1** doesn't exist, the shell command will be executed.

At line 12, there is an extra target called **clean**. **clean** is apparently not a name of an output file, because the shell command of this target doesn't output files. We can run command ```$ make clean``` in terminal to directly launch this target. From the line 13, we can see what this target will do is to remove all generated output files.

-------------------------------
## Basic Skills 
### Ex 2: PHONY, Simple Imlicit Rule, $@, $<, -, @
```makefile
	 1 #======================================================================
	 2 # Title: ex2
	 3 # Purpose: Simple Imlicit Rule, PHONY, -, @, $@, $<
	 4 #======================================================================
	 5 
	 6 .PHONY: clean
	 7 ex2: PrintHello.o main.o
	 8     gcc -g3 -Wall -pedantic-errors -o ex2 main.o PrintHello.o
	 9 %.o:%.c HaHa.h
	10     gcc -g3 -Wall -pedantic-errors -o $@ $< -c
	11 clean:
	12     -@rm ex2
	13     -@rm main.o
	14     -@rm PrintHello.o
	15
	16 #=============================End of File==============================
```

**PHONY : **  
Targets that don't output files shoule be listed following the keyword **.PHONY**.  (Try: create a balnk file call **clean** and see what will happen.)

**Implicit Rules : **  
There are implicit rules that can help users simplify their makefiles. The simplest implicit rule is shown at the line 9. This can be used when the names of output files(not including extension names) are the same as that of source files or input files. For other implicit rules, please refer to **GNU make Manual**.

**$@** and **$<**:  
These two symbols represent the name of output file (i.e. the target name) and the first dependency (in this case, the source file) respectively.

**-** and **@**:  
Symbol "-" means ignoring error messages and continuing the subsequent commands.  And symbol "@" represents showing only error message. (Try: take off the "-" in the line 12 and see what will happen if **ex2** doesn't exist.; take off the "@" in the line 12 and see the results when **ex2** exists.) 

### Ex 3: Variables (Macro)
```makefile
	 1 #======================================================================
	 2 # Title: ex3
	 3 # Purpose: Variables (Macro)
	 4 #======================================================================
	 5  
	 6 CC = gcc
	 7 CFLAGS = -g3 -Wall -pedantic-errors
	 8 OBJS = PrintHello.o main.o
	 9 BIN = ex3
	10 INC = HaHa.h
	11 
	12 .PHONY: clean
	13 
	14 ${BIN}: ${OBJS}
	15     ${CC} ${CFLAGS} -o ${BIN} ${OBJS}
	16 %.o: %.c ${INC}
	17     ${CC} ${CFLAGS} -o $@ $< -c
	18 clean:
	19     -@rm ${BIN} ${OBJS}
	20
	21 #=============================End of File==============================
```
**Variables (or Macro) : **

* Use "**=**" to assign values to variables and ${} or $() to get the values of variables. ***Important***: *the value of a variable depends on the final assignment in **makefile**, not the location of the variable.* For example, in the following codes, the **y** will be *xyz*, rather than *foo*. :

```
	x = foo
	y = ${x}
	x = xyz
```  
 
* There are also other symbols for assigning values. The most often seen symbols are **+=**, **?=**, and **:=**. 
	1. **:=**: Using this symbol to assign values, the values of the variable will depend on the location.
	1. **?=**: If the variable is undefined, than this assigns values to it. Otherwise the **make** keep the old value.
	3. **+=**: add a new value to the original values. For example: `a = ff`, then after `a += gg`, **a** will become *ff gg*. 
* The values of a variable can be change when we run `$ make` command. For example: `$ make BIN='exHAHAHA'`. The **BIN** during this execution will be **exHAHAHA** instead of **ex3**.
* The **make** can also get the environmental variables of current operating system, such as ${PATH} etc.

### Ex 4: A Simple Application
```makefile
	 1 #======================================================================
	 2 # Title: ex4
	 3 # Purpose: A Simple Application
	 4 #======================================================================
	 5
	 6 CC = gcc
	 7
	 8 SRC = src
	 9 BPATH = bin
	10 OPATH = obj
	11 IPATH = includes
	12 
	13 BIN = ex4
	14 OBJ = PrintHello.o main.o
	15 INC = HaHa.h
	16 
	17 .PHONY: clean debug release build
	18 
	19 debug: MODE = Debug
	20 debug: CFLAGS = -g3 -Wall -pedantic-errors -I ${IPATH}
	21 debug: 
	22     make build MODE="${MODE}" CFLAGS="${CFLAGS}"
	23
	24 release: MODE = Release
	25 release: CFLAGS = -O3 -fopenmp -I ${IPATH}
	26 release: 
	27     make build MODE="${MODE}" CFLAGS="${CFLAGS}"
	28
	29 build: 
	30     @if [ ! -e ${BPATH} ]; then mkdir ${BPATH}; fi
	31     @if [ ! -e ${BPATH}/${MODE} ]; then mkdir ${BPATH}/${MODE}; fi
	32     @if [ ! -e ${OPATH} ]; then mkdir ${OPATH}; fi
	33     make ${BPATH}/${MODE}/${BIN}
	34
	35 ${BPATH}/${MODE}/${BIN}: $(foreach i, ${OBJ}, ${OPATH}/${i})
	36     ${CC} ${CFLAGS} -o ${BPATH}/${MODE}/${BIN} \
	37				$(foreach i, ${OBJ}, ${OPATH}/${i})
	38
	39 ${OPATH}/%.o: ${SRC}/%.c ${IPATH}/${INC}
	40     ${CC} ${CFLAGS} -o $@ -c $<
	41
	42 clean:
	43     -@if [ -e ${BPATH} ]; then rm -r ${BPATH}; fi
	44     -@if [ -e ${OPATH} ]; then rm -r ${OPATH}; fi
	45
	46 #=============================End of File==============================
```

**Shell Scripts in the *make*:**  

* When the ***make*** executes the shell commands, it starts **a new shell** for **each line**. Therefore, some commands have to be written in the same line and be connected by the symbol "**;**". For example, the **if ... ; then ...; fi** commands. They can not be executed separately in different shell.
* If a shell returns any error to the ***make*** in the end of execution, the ***make*** will stop the execution. So some commands **can not** run in the same shell using "**;**". For example, if directory **ABC** doesn't exist, running `cd ./ABC/ ; echo ${PATH}`, the **make** will still execute `echo ${PATH}`, though it may got an error message `cd: ./ABC: No such file or directory`. To avoid this problem, we can use "**&&**" rather than "**;**".

**GNE *make* Functions:**

There are some built-in functions in GNU make. The `$(foreach i, ${OBJ}, ${OPATH}/${i})` in the line 35 and 37 is an example. **foreach** is a function. It is something like **for-loop** in python. **i** is the variable, and **${OBJ} is the list. **${OPATH}/${i}** is the command it has to execute during each loop. If we translate `$(foreach i, ${OBJ}, ${OPATH}/${i})` into python, it will look like:

```python
	OBJ =  ['PrintHello.o', 'main.o']
	OPATH = 'obj'
	def foreach(idx, LIST, MM):
		tmp = []
		for idx in LIST:
			tmp.append(MM + idx)
		return tmp[:]
	i = ''
	foreach(i, OBJ, OPATH + '/')
```
For more functions, please refer to the **GNU make Manual**. Wihtout the help of the GNU make functions, we can still utilize the ***make*** to do many things.

**Local Variables Defined in a Target:**  
In the line 19, 20, 24 and 25, we define several local variables. These variables only exist in their targets. So if we need other targets to use them, we have to figure out some ways to pass them. There are many approaches, one of them is to pass them by `$ make <target> [var1 = '...' var2 = '...']`.

-------------------------------
## Reference  
[1] Stallman, M., McGrath, R., & Smith, P. D. (1991). gnu Make. Free Software Foundation, Boston.  
[2] http://prateekvjoshi.com/2014/02/01/cmake-vs-make/
