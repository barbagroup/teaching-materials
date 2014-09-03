# Introduction to GNU ***make*** #

---------------------------------------------------
## Why do we need *make*? What is *make*? ##

Consider the following example. If there are three source files A.F90, B.F90 and C.F90, and 

* C.F90 has first to be compiled and packed as a library, 
* B.F90 is a module using the LAPACK library, and 
* finally the main program in A.F90 has to be linked to module B and library C

The standard procedure of the compilation is:
```
    $ gfortran B.F90 C.F90 -c 
    $ ar rc libC.a c.o 
    $ gfortran A.F90 -c 
    $ gfortrna A.o B.o -L ./ -lC -llapack -o test.out 
``` 
It looks fine because there are only four compilation commands. But how if we have 10, 50, 100, or even thousands of source files? Typing each compilation command for each source file seems impractical.

Futhermore, if we want to rebuilt this program after some modifications, we can again type these four commands in termal, or we can also only compile the modified source file and then linked all object file. But both of these choices have the disadvantages. Re-building the program from the first source file to the final one will take a lot of time and be annoying. And only re-compiling the modified files sometimes is also annoying because we have to determine which files must be re-compiled manually. That's why we need a tool to help us automatically determine how to re-build the program. That tool is ***make***.

>"The ***make*** utility automatically determines which pieces of a large program need to be recompiled, and issues commands to recompile them."            *~ p.1, GNU Make Manual[1]*

>A ***make*** utility is a controller that controls how the executable and other non-source files (like objective files or libraries) be generated from source files*[2]*.

Besides, sometimes we have to change between several building modes using different compilation flags, such as *release mode* or *debug mode*, it will be a pain to type those complicated flags repeatedly.  We can easily change the build mode by ***make***.

Also, combining ***make*** with some simple shell script, **make** can let users manage the built files or do something like **clean all built files by one command**! 

In fact, most visualized IDEs in Windows system have their own ***make*** utilities behind the GUI. However, for Linux users, we have to use standalone ***make*** utilities. There are several standalone ***make*** utilities: SunPro make, pmake, GNU make, nmake etc.  The GNU make is a standard tool for Linux. We will introduce GNU make in this notebook.

-------------------------------
## How does *make* work? ##  
1234564864684
