#include "dht11.h"

int temperature_tmp_dht11;
int humidity_tmp_dht11;
int correct_humidity_dht11=30;
DHT11::DHT11()
{
    MAX_TIME=85;
  //  DHT11PIN=7;
    ATTEMPTS_DHT11=3;
   // temperature=0;
   // humidity=0;
    flag=0;
    for(int i=0;i<5;i++)
        dht11_val[i]=0;
}

int DHT11::handel_val_dht11()
{

    uint8_t lststate=HIGH;         //last state
    uint8_t counter=0;
    uint8_t j=0,i;
    for(i=0;i<5;i++)
        dht11_val[i]=0;

    //host send start signal
    pinMode(DHT11PIN,OUTPUT);      //set pin to output
    digitalWrite(DHT11PIN,LOW);    //set to low at least 18ms
    delay(18);
    digitalWrite(DHT11PIN,HIGH);   //set to high 20-40us
    delayMicroseconds(40);
    //start recieve dht response
    pinMode(DHT11PIN,INPUT);       //set pin to input
    for(i=0;i<MAX_TIME;i++)
    {
        counter=0;
        while(digitalRead(DHT11PIN)==lststate){//read pin state to see if dht responsed. if dht always high for 255 + 1 times, break this while circle
            counter++;
            delayMicroseconds(3);
            if(counter==255)
                break;
        }
        lststate=digitalRead(DHT11PIN);             //read current state and store as last state. 
        if(counter==255)                            //if dht always high for 255 + 1 times, break this for circle
            break;
        // top 3 transistions are ignored, maybe aim to wait for dht finish response signal
        if((i>=4)&&(i%2==0)){
            dht11_val[j/8]<<=1;                     //write 1 bit to 0 by moving left (auto add 0)
            if(counter>16)                          //long mean 1
                dht11_val[j/8]|=1;                  //write 1 bit to 1
            j++;
        }
    }
    // verify checksum and print the verified data
    if((j=40)&&(dht11_val[4]==((dht11_val[0]+dht11_val[1]+dht11_val[2]+dht11_val[3])& 0xFF))){
        temperature=dht11_val[2];	// for DHT11
        humidity=dht11_val[0];	// for DHT11
         if ((temperature !=0)&&(humidity!=0)){
         temperature_tmp_dht11=temperature;
         humidity_tmp_dht11=humidity;}
         else{ 
         temperature=temperature_tmp_dht11; 
         humidity=humidity_tmp_dht11;};
        return 1;
    }
    else
        return 0;
}

data_dht11 DHT11::dht11_read(){
    int attempts_dht11=ATTEMPTS_DHT11;
    if(!flag&&wiringPiSetup()==-1)
        exit(1);
	else if(flag==0)
		flag=1;
    while(attempts_dht11){                          //you have 5 times to retry
        int success_dht11 = handel_val_dht11();     //get result including printing out
        if (success_dht11) {                        //if get result, quit program; if not, retry 5 times then quit
            break;
        }
        attempts_dht11--;
        delay(50);
    }

    humidity=humidity+correct_humidity_dht11;// for DHT11
    if (humidity>100) {humidity=100;};// for DHT11
    return data_dht11(temperature,humidity);
}

int DHT11::setpin(int PIN){
	DHT11PIN=PIN;
}
