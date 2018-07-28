#include "dht22.h"  
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

////
float temperature_tmp;
float humidity_tmp;
int success=0;
float correct_humidity_dht22=0;
float correct_celsium_dht22=0;
////
DHT22::DHT22()
{
    MAX_TIME=85;
    // DHT22PIN=7;
    ATTEMPTS_DHT22=3;
    // temperature=0;
    // humidity=0;
    flag=0;
    for(int i=0;i<5;i++)
    dht22_val[i]=0;
}
float DHT22::handel_val_dht22()
{

    uint8_t lststate=HIGH;         //last state
    uint8_t counter=0;
    uint8_t j=0,i;
    for(i=0;i<5;i++)
    dht22_val[i]=0;
    //host send start signal    
    pinMode(DHT22PIN,OUTPUT);      //set pin to output 
    digitalWrite(DHT22PIN,LOW);    //set to low at least 18ms 
    delay(18);
    digitalWrite(DHT22PIN,HIGH);   //set to high 20-40us
    delayMicroseconds(40);
    //start recieve dht response
    pinMode(DHT22PIN,INPUT);       //set pin to input
    for(i=0;i<MAX_TIME;i++)         
    {
        counter=0;
        while(digitalRead(DHT22PIN)==lststate){ //read pin state to see if dht responsed. if dht always high for 255 + 1 times, break this while circle
            counter++;
            delayMicroseconds(2);
            if(counter==255)//255
                break;
        }
        lststate=digitalRead(DHT22PIN);             //read current state and store as last state. 
        if(counter==255)                            //if dht always high for 255 + 1 times, break this for circle
            break;
        // top 3 transistions are ignored, maybe aim to wait for dht finish response signal
        if((i>=4)&&(i%2==0)){
            dht22_val[j/8]<<=1;                     //write 1 bit to 0 by moving left (auto add 0)
            if(counter>16)                          //long mean 1
                dht22_val[j/8]|=1;                  //write 1 bit to 1 
            j++;
        }
    }
    // verify checksum and print the verified data
    if((j=40)&&(dht22_val[4]==((dht22_val[0]+dht22_val[1]+dht22_val[2]+dht22_val[3])& 0xFF))){
        humidity = (float)((dht22_val[0] << 8) + dht22_val[1]) / 10;// for DHT22
		temperature = (float)(((dht22_val[2] & 0x7F) << 8) + dht22_val[3]) / 10;// for DHT22
		if ( humidity > 100 )	// for DHT22
		{
		humidity = dht22_val[0];	// for DHT22
		};
                if ( temperature > 125 )	// for DHT22
		{
		temperature = dht22_val[2];	// for DHT22
		};
		if ( dht22_val[2] & 0x80 )	// for DHT22
		{
			temperature = -temperature;	// for DHT22
		};
                if ((temperature !=0)&&(humidity!=0)){
                temperature_tmp=temperature;
                humidity_tmp=humidity;
                }else{
                temperature=temperature_tmp;
                humidity=humidity_tmp;
                }

        return 1;
    }
    else
        return 0;
}

data_dht22 DHT22::dht22_read(){
    int attempts_dht22=ATTEMPTS_DHT22;
    if(!flag&&wiringPiSetup()==-1)
        exit(1);
	else if(flag==0)
		flag=1;
    while(attempts_dht22){                        //you have 5 times to retry
        float success_dht22 = handel_val_dht22();     //get result including printing out
        if (success_dht22) {                      //if get result, quit program; if not, retry 5 times then quit
            break;
        }
        attempts_dht22--;
        delay(100);
    }
    temperature=temperature+correct_celsium_dht22;
    humidity=humidity+correct_humidity_dht22;
    return data_dht22(temperature,humidity);
}

int DHT22::setpin(int PIN){
	DHT22PIN=PIN;
}
