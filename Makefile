MANAGERS = libs/managers
FUNCS = libs/funcs


output: $(MANAGERS)/fileManager.o $(MANAGERS)/flagManager.o $(FUNCS)/ignoreFunctionality.o  main.o
	gcc main.o $(MANAGERS)/fileManager.o $(MANAGERS)/flagManager.o $(FUNCS)/ignoreFunctionality.o -o output.out
	cp output.out /usr/bin/dsvc

flagmanager.o: $(MANAGERS)/flagManager.c
	gcc -c $(MANAGERS)/flagManager.c -o $(MANAGERS)/flagManager.o

filemanager.o: $(MANAGERS)/fileManager.c
	gcc -c $(MANAGERS)/fileManager.c -o $(MANAGERS)/fileManager.o

ignoreFunctionality.o: $(FUNCS)/ignoreFunctionality.c
	gcc -c $(FUNCS)/ignoreFunctionality.c -o $(FUNCS)/ignoreFunctionality.o

main.o: main.c
	echo "Compiling the main file"
	gcc -c main.c -o main.o

clean:
	rm output.out ./**/*.o -f
	rm *.o
	rm /usr/bin/dsvc -f
