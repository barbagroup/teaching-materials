#Introduction to GDB

##What is GDB? Why do we need it?

##Getting started
* Compile with `-g` flag.
* Run `gdb [executable]` in your command line.

##Main GDB commands

####Run the code 
* `run` (`r`): run code.
* `quit` (`q`): quit GDB.

####Pause execution
* `break` (`b`): set breakpoint on line number or function name.
* `watch`: stops every time a variable changes.
* `rwatch`: stops every time a variable is read.
* `awatch`: stops every time a variable is read or written.
* `disable`: removes break and watch points.

####Inspect the code
* `list` (`l`): show code around current line.
* `backtrace` (`bt`): function calls that led to the current state.

###Read/write
* `print` (`p`): read and write on variable.
* `info locals`: read all local variables.

####Navigate the code
* `step` (`s`): execute next line of code.
* `next` (`n`): execute next line of code. If it is a function, treat it as one line.
* `continue` (`c`): execute until next breakpoint (or watch).
* `finish` (`fin`): execute until current function finishes.
