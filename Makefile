gslfindroot_func_skel.o: gslfindroot_func_skel.c
	gcc -c gslfindroot_func_skel.c -I/opt/local/include -L/opt/local/lib -lgsl


gslmultiroot_func_skel.o: gslmultiroot_func_skel.c
	gcc -c gslmultiroot_func_skel.c -I/opt/local/include -L/opt/local/lib -lgsl

clean:
	rm *.o *~


all: gslfindroot_func_skel.o gslmultiroot_func_skel.o
