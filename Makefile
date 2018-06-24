CC  = gcc -static
CCL = gcc -static 
INCLUDE = -I.
DST = a.exe
MODULE = lib/block.o lib/chain.o lib/fs.o lib/hash.o lib/hashStorage.o lib/stack.o lib/stringProcess.o lib/filter.o dbop.o ui.o ramop.o hddop.o

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

lib/stringProcess.o: lib/stringProcess.c
	$(CC) -c ./lib/stringProcess.c -o ./lib/stringProcess.o $(INCLUDE) -O2

lib/filter.o: lib/filter.c
	$(CC) -c ./lib/filter.c -o ./lib/filter.o $(INCLUDE) -O2

dbop.o: dbop.c
	$(CC) -c dbop.c -o dbop.o $(INCLUDE) -O2

ui.o: ui.c
	$(CC) -c ui.c -o ui.o $(INCLUDE) -O2

hddop.o: hddop.c
	$(CC) -c hddop.c -o hddop.o $(INCLUDE) -O2

ramop.o: ramop.c
	$(CC) -c ramop.c -o ramop.o $(INCLUDE) -O2
