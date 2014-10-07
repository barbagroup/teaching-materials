ex1: example_1.c
	gcc -std=c99 -O3 -o ex1 example_1.c

example_1.s: example_1.c
	gcc -std=c99 -O3 -S example_1.c

ex2_O0: example_2.c
	gcc -O0 -std=c99 -o ex2_O0 example_2.c

ex02_O1: example_2.c
	gcc -O1 -std=c99 -o ex2_O1 example_2.c

ex2_O2: example_2.c
	gcc -O2 -std=c99 -o ex2_O2 example_2.c

ex2_O3: example_2.c
	gcc -O3 -std=c99 -o ex2_O3 example_2.c

mt1_O0: mtxtransp1.c
	gcc -O0 mtxtransp1.c -o mt1_O0

mt1_O3: mtxtransp1.c
	gcc -O0 mtxtransp1.c -o mt1_O3

mt2_O0: mtxtransp2.c
	gcc -O0 mtxtransp2.c -o mt2_O0

mt2_O3: mtxtransp2.c
	gcc -O3 mtxtransp2.c -o mt2_O3

clean:
	rm -rf ex1 example_1.s ex2* mt1* mt2*