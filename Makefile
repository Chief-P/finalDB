CC  = gcc -static
CCL = gcc -static 
INCLUDE = -I.
DST = a.out
MODULE = lib/block.o lib/chain.o lib/fs.o lib/hash.o lib/hashStorage.o lib/stack.o operation.o ui.o dbio.o

$(DST): $(MODULE) main.o
	$(CC) main.o $(MODULE) -o $(DST) $(INCLUDE)

main.o: main.c
	$(CC) -c main.c -o main.o -O2 $(INCLUDE)

lib/block.o: lib/block.c
	$(CC) -c ./lib/block.c -o ./lib/block.o $(INCLUDE) -O2

lib/chain.o: lib/chain.c
	$(CC) -c ./lib/chain.c -o ./lib/chain.o $(INCLUDE) -O2

lib/filter.o: lib/filter.c
	$(CC) -c ./lib/filter.c -o ./lib/filter.o $(INCLUDE) -O2

lib/fs.o: lib/fs.c
	$(CC) -c ./lib/fs.c -o ./lib/fs.o $(INCLUDE) -O2

lib/hash.o: lib/hash.c
	$(CC) -c ./lib/hash.c -o ./lib/hash.o $(INCLUDE) -O2

lib/hashStorage.o: lib/hashStorage.c
	$(CC) -c ./lib/hashStorage.c -o ./lib/hashStorage.o $(INCLUDE) -O2

lib/stack.o: lib/stack.c
	$(CC) -c ./lib/stack.c -o ./lib/stack.o $(INCLUDE) -O2

lib/stringProcess: lib/stringProcess.c
	$(CC) -c ./lib/stringProcess.c -o ./lib/stringProcess.o $(INCLUDE) -O2

operation.o: operation.c
	$(CC) -c operation.c -o operation.o $(INCLUDE) -O2

ui.o: ui.c
	$(CC) -c ui.c -o ui.o $(INCLUDE) -O2

dbio.o: dbio.c
	$(CC) -c dbio.c -o dbio.o $(INCLUDE) -O2
