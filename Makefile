output: libs/fileManager.o libs/flagManager.o  main.o
	gcc main.o libs/fileManager.o libs/flagManager.o -o output.out
	cp output.out /usr/bin/dsvc

flagmanager.o: libs/flagManager.c
	gcc -c libs/flagManager.c -o libs/flagManager.o

filemanager.o: libs/fileManager.c
	gcc -c libs/fileManager.c -o libs/fileManager.o

main.o: main.c
	echo "Compiling the main file"
	gcc -c main.c -o main.o

clean:
	rm output.out ./**/*.o -f
	rm *.o
	rm /usr/bin/dsvc -f
