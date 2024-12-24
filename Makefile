output: libs/fileManager.o main.o
	gcc main.o libs/fileManager.o -o output.out
	cp output.out /usr/bin/dsvc

test.o: libs/fileManager.c
	gcc -c libs/fileManager.c -o libs/fileManager.o

main.o: main.c
	echo "Compiling the main file"
	gcc -c main.c -o main.o

clean:
	rm output.out ./**/*.o -f
	rm /usr/bin/dsvc -f
