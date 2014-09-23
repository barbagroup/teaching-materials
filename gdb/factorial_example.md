The file `factorial.cpp` is the source of a code that computes the factorial of an integer. Compile and run:

```
$ g++ factorial.cpp -o factorial 
$ ./factorial
Enter a positive integer: 4

4! = 2116635728
```

Clearly, there is something wrong! Let's use GDB to debug this code. First, compile with debug flag:

```
$ g++ factorial.cpp -g -o factorial
```

And run GDB 

```
$ gdb ./factorial
```

to get the GBD prompt `(gdb)`.

Maybe we want to check if the error repeats inside GDB, let's run the code

```
(gdb) r
Starting program: /home/cdcooper/gdb/factorial 
Enter a positive integer: 4

4! = 958647376
[Inferior 1 (process 20801) exited normally]
```

Yep, error still there. 

We have no idea where it might be going wrong, so let's put a breakpoint right in the beginning, and start from there.

```
(gdb) b main
Breakpoint 1 at 0x4008bc: file factorial.cpp, line 18.
```
Breakpoints can be placed on line numbers or functions. If you are working with more than one file, you might want to specify the file name so that GDB doesn't get confused. For example, `(gdb) b factorial.cpp:18` places a breakpoint at line 18 of file factorial.cpp, just like we did before.

Let's run:

```
(gdb) r
Starting program: /home/cdcooper/gdb/factorial 

Breakpoint 1, main () at factorial.cpp:18
18	    std::cout << "Enter a positive integer: ";
```

Okay, reached breakpoint, and GDB shows the line that is about to execute, but hasn't yet. Stepping down with `s` takes us to line 21 and pressing the `return` key again repeats the last operation, asking for the positive integer:

```
(gdb) s
21	    std::cin >> num;
(gdb) 
Enter a positive integer: 4
22	    std::cout << std::endl;
```

Stepping down a bit more takes us into the `factorial` function

```
(gdb) s

24	    num_fact = factorial(num);
(gdb) 
factorial (N=4) at factorial.cpp:7
7	    for (int i=1; i<=N; i++)
(gdb) 
```
If we would have done this stepping down with `next`, GDB would have executed `factorial` without going actually into the function.

We might be a bit lost and want to know where we are in the code. We can ask for a `list` of lines around the one about to be executed

```
(gdb) l
2	
3	int factorial(int N)
4	{
5	    int fact;
6	
7	    for (int i=1; i<=N; i++)
8	    {
9		fact = fact*i;
10	    }
```
and to know how we got to this point, we can run a `backtrace`

```
(gdb) bt
#0  factorial (N=4) at factorial.cpp:7
#1  0x00000000004008f5 in main () at factorial.cpp:24
```
Everything looks good: we are inside the function `factorial`, called by `main` with input parameter `N=4`. In fact, we can check that by printing `N`:

```
(gdb) p N
$1 = 4
```
And `$1` is a variable inside GDB that we can call later!

We can navigate the code a little with the command `up`, which takes us back to `main`

```
(gdb) up
#1  0x00000000004008f5 in main () at factorial.cpp:24
24	    num_fact = factorial(num);
(gdb) p N
No symbol "N" in current context.
(gdb) p num
$4 = 4
```

`N` does not exist in `main`, but `num` does, and has the expected value 4. Now, back to `factorial` with `down`

```
(gdb) down
#0  factorial (N=4) at factorial.cpp:7
7	    for (int i=1; i<=N; i++)
```

Let's step down the code to make sure the `for` loop is being executed (no need to press `s` the every time!)

```
(gdb) s
9		fact = fact*i;
(gdb) 
7	    for (int i=1; i<=N; i++)
(gdb) 
9		fact = fact*i;
(gdb) 
7	    for (int i=1; i<=N; i++)
(gdb) 
9		fact = fact*i;
(gdb) 
7	    for (int i=1; i<=N; i++)
(gdb) 
9		fact = fact*i;
(gdb) 
7	    for (int i=1; i<=N; i++)
(gdb) 
12	    return fact;
```

`for` loop works fine. Let's print `fact`

```
(gdb) p fact
$5 = 958647376
```

That is wrong! Let's let the program run finish with `continue`

```
(gdb) c
Continuing.
4! = 958647376
[Inferior 1 (process 20810) exited normally]
```
Let's do the same, but being more careful. We know that the inputs to `factorial` are correct, so let's remove the breakpoint from `main` and put another one right before the function call

```
(gdb) disable 1
(gdb) b factorial.cpp:24
Breakpoint 2 at 0x4008eb: file factorial.cpp, line 24.
(gdb) r
Starting program: /home/cdcooper/gdb/factorial 
Enter a positive integer: 4


Breakpoint 2, main () at factorial.cpp:24
24	    num_fact = factorial(num);
```
Now, let's step down to the loop:

```
(gdb) s
factorial (N=4) at factorial.cpp:7
7	    for (int i=1; i<=N; i++)
(gdb) 
9		fact = fact*i;
```
and inspect all the local variables with `info locals`

```
(gdb) info locals
i = 1
fact = -139013330
```
The loop has not run and `fact` is already wrong! Let's force it to be the number it should be with `print` and `watch` it to see what happens:

```
(gdb) p fact=1
$6 = 1
(gdb) watch fact
Hardware watchpoint 4: fact
```
The `watch ` command sets a breakpoint every time the variable `fact` is modified. Then, we can use `continue` rather than `step` to move forward faster 

```
(gdb) c
Continuing.
Hardware watchpoint 4: fact

Old value = 1
New value = 2
factorial (N=4) at factorial.cpp:7
7	    for (int i=1; i<=N; i++)
(gdb) c
Continuing.
Hardware watchpoint 4: fact

Old value = 2
New value = 6
factorial (N=4) at factorial.cpp:7
7	    for (int i=1; i<=N; i++)
(gdb) c
Continuing.
Hardware watchpoint 4: fact

Old value = 6
New value = 24
factorial (N=4) at factorial.cpp:7
7	    for (int i=1; i<=N; i++)
(gdb) c
Continuing.

Watchpoint 4 deleted because the program has left the block in
which its expression is valid.
```

Loop is running correctly! The problem is that `fact` is coming into the loop with the wrong value. If we look at the declaration of `fact`, we see

```C
     int fact;
```

We forgot to initialize it! If we replace that line by

```C
     int fact = 1;
```

The code runs conrrectly.

This example was based on material from Harvard University's CS50, by David J. Malan (under CC BY-NC-SA 3.0).
