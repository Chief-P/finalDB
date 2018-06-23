CC  = gcc -static
CCL = gcc -static 
INCLUDE = -I.
DST = a.out
MODULE = lib/block.o lib/chain.o lib/fs.o lib/hash.o lab/hashStorage.o lib/stack.o

$(DST): $(MODULE) main.o
	$(CC) main.o $(MODULE) -o $(DST) $(INCLUDE)

main.o: main.c
	$(CC) -c main.c -o main.o -O2 $(INCLUDE)

lib/block.o: lib/block.c
	$(CC) -c ./lib/block.c -o ./lib/block.o $(INCLUDE) -O2

lib/chain.o: lib/chain.c
	$(CC) -c ./lib/chain.c -o ./lib/chain.o $(INCLUDE) -O2

lib/fs.o: lib/fs.c
	$(CC) -c ./lib/fs.c -o ./lib/fs.o $(INCLUDE) -O2

lib/hash.o: lib/hash.c
	$(CC) -c ./lib/hash.c -o ./lib/hash.o $(INCLUDE) -O2

lib/hashStorage.o: lib/hashStorage.c
	$(CC) -c ./lib/hashStorage.c -o ./lib/hashStorage.o $(INCLUDE) -O2

lib/stack.o: lib/stack.c
	$(CC) -c ./lib/stack.c -o ./lib/stack.o $(INCLUDE) -O2

lib/func.o: lib/func.c
	$(CC) -c ./lib/func.c -o ./lib/func.o $(INCLUDE) -O2

lib/show.o: lib/show.c
	$(CC) -c ./lib/show.c -o ./lib/show.o $(INCLUDE) -O2
