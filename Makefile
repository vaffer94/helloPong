build:
	gcc -Wall -std=c99 ./*.c -lSDL2 -o helloPongRun

run:
	./helloPongRun

clean:
	rm helloPongRun