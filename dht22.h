#ifndef DHT22_H_
#define DHT22_H_
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef struct data_dht22{
	float temperature;
	float humidity;
	data_dht22(float t,float h)
	{
		temperature=t;
		humidity=h;	
	}
}data_dht22;

class DHT22{
private:
	int MAX_TIME;
	int DHT22PIN;
	int ATTEMPTS_DHT22;
	int dht22_val[5];
	float temperature;
	float humidity;
	int flag; //determine whether open /proc/cpuinfo
	float handel_val_dht22(); 

public:	
//	int DHT22PIN;
	DHT22();
//	float handel_val_dht22(); 
	data_dht22 dht22_read(); //use this function to get the data
	setpin(int PIN);
};

#endif
