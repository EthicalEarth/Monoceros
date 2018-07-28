#ifndef DHT11_H_
#define DHT11_H_
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef struct data_dht11{
	int temperature;
	int humidity;
	data_dht11(int t,int h)
	{
		temperature=t;
		humidity=h;	
	}
}data_dht11;

class DHT11{
private:
	int MAX_TIME;
	int DHT11PIN;
	int ATTEMPTS_DHT11;
	int dht11_val[5];
	int temperature;
	int humidity;
	int flag; //determine whether open /proc/cpuinfo
	int handel_val_dht11(); 

public:
//	int DHT11PIN;
	DHT11();
//	int handel_val(); 
	data_dht11 dht11_read(); //use this function to get the data
        setpin(int PIN);

};

#endif
