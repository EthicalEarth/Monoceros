all: tmd
tmd: main.o dht11.o dht22.o
		g++ -o tmd main.o dht11.o dht22.o -lwiringPi  -Wformat-security -fpermissive -Wreturn-local-addr
main.o: main.cpp dht11.h
		g++ -c main.cpp -std=c++11 -Wformat-security -fpermissive -Wreturn-local-addr
dht11.o: dht11.c dht11.h
		g++ -c dht11.c -lwiringPi -fpermissive
dht22.o: dht22.c dht22.h
		g++ -c dht22.c -lwiringPi -fpermissive
clean:
		rm main.o dht11.o dht22.o tmd
check:
		make clean && make
rebuild:
		make clean && make -j4
