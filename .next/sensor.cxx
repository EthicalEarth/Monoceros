using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iostream>

typedef struct SensorResult{
	float value1;
	float value2;
	float value3;
	float value4;
}SensorResult;


class Sensor {
public:
    virtual SensorResult read() {
}
    virtual ~Sensor(){} // деструктор
};


