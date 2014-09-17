# ex5
# application of variables and shell script
cc=gcc
src=./src/
inc=HaHa.h
Ipath=-I ./inc/
bin=ex5
bin_path=bin/
objs=PrintHello.o main.o
objs_path=./obj/

debug: flags=-g3 -Wall -pedantic-errors
debug: mode=Debug
debug:
	make $(bin)

$(bin): $(obj_path)$(objs)
	$(cc) $(flags) -o $(bin) $(objs)
%.o: $(src)%.c $(inc)
	$(cc) $(flags) $(Ipath) -o $@ $< -c
#.PHONY: clean
clean:
	rm $(bin) $(objs)