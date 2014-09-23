# Segfault example

Segmentation faults can be difficult to debug: compiler runs silently, and the execution fails without any helpful information. Plus, pointers can be very confusing.

The code `segfault.cpp` computes the number of characters of a string. Let's run it to see what happens:

```
$ g++ segfault.cpp -o segfault
$ ./segfault
Segmentation fault (core dumped)
```

Oh well, that is not much information to start debugging!

Let's try it with GDB:

```
$ g++ segfault.cpp -g -o segfault
$ gdb ./segfault
```

compiles in debugging mode and opens the GDB prompt, ready to run the code. Let's do that:

```
(gdb) r
Starting program: /home/cdcooper/gdb/segfault 

Program received signal SIGSEGV, Segmentation fault.
0x0000000000400587 in foo_len (s=0x0) at segfault.cpp:7
7	  return strlen (s);
```
This is a LOT more than what we got before: we know exactly where the segfault is hapenning. Let's take a look at the code at that point:

```
(gdb) l
2	#include <stdlib.h>
3	#include <string.h>
4	 
5	int foo_len (const char *s)
6	{
7	  return strlen (s);
8	}
9	 
10	int main (int argc, char *argv[])
11	{
```
and look at `s`:

```
(gdb) p s
$1 = 0x0
```

Aha! The `NULL` pointer. No wonder `strlen` was complaining.

Let's check if this is a problem that comes from outside `foo_len`:

```
(gdb) up
#1  0x00000000004005b8 in main (argc=1, argv=0x7fffffffda08) at segfault.cpp:14
14	  printf ("size of a = %d\n", foo_len (a));
(gdb) p a
$2 = 0x0
```
The input to `foo_len` is also the `NULL` pointer. Let's re-run the code with a breakpoint where we define `a`. No need to restart GDB, we'll do everything from inside:

```
(gdb) b 12
Breakpoint 1 at 0x4005a4: file segfault.cpp, line 12.
(gdb) r
The program being debugged has been started already.
Start it from the beginning? (y or n) y

Starting program: /home/cdcooper/gdb/segfault 

Breakpoint 1, main (argc=1, argv=0x7fffffffda08) at segfault.cpp:12
12	  const char *a = NULL;
```

Here we are. Now, we can step once and redefine `a` to something else, say "test"

```
(gdb) s
14	  printf ("size of a = %d\n", foo_len (a));
(gdb) p a="test"
$5 = 0x403010 "test"
```
And let the program `continue`

```
(gdb) c
Continuing.
size of a = 4
[Inferior 1 (process 21537) exited normally]
```

Cool! No segmentation fault, and the right output. 
