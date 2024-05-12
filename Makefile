Hepsi: Derle Link Calistir

Calistir:
	./bin/program.exe sampleInput.dat sampleOutput.dat
Derle:
	gcc -g -I ./include -c ./src/main.c -o ./lib/main.o  
	gcc -g -I ./include -c ./src/program.c -o ./lib/program.o  
	gcc -g -I ./include -c ./src/utility.c -o ./lib/utility.o  
Link:
	gcc -g ./lib/main.o ./lib/program.o ./lib/utility.o ./lib/libfdr.a  -o ./bin/program.exe