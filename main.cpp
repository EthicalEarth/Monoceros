#include <iostream>
#include "dht11.h"
#include "dht22.h"
#include <fstream>
#include <iomanip>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <sstream>
#include <csignal>
#include <stdint.h>
#include <sys/stat.h>
#include <syslog.h>
#include <vector>
#include <dirent.h>
#include <iterator>
#include <cstdlib>
#include <cstring>
#include <sstream>

/********************************
* Settings
********************************/
#define DHT11_CONNECT                   3    //22gpio
#define DHT22_CONNECT                   7    //7gpio
#define DHT11_FILE_LOCATION             "/tmp/data_file_dht11"
#define DHT22_FILE_LOCATION             "/tmp/data_file_dht22"
#define DHT11_LATEST_FILE_LOCATION      "/tmp/latest_data_dht11"
#define DHT22_LATEST_FILE_LOCATION      "/tmp/latest_data_dht22"
#define DHT11_DATABASE_LOCATION  "/tmp/statistic_dht11.rrd"
#define DHT22_DATABASE_LOCATION  "/tmp/statistic_dht22.rrd"
#define UPDATE_SCRIPT            "/opt/monoceros/scripts/update.sh"
#define NTPDATE_LOCATION         "/usr/sbin/ntpdate"
#define NTP_SCRIPT_LOCATION      "/opt/monoceros/scripts/ntp_start.sh"
#define RRDTOOL_LOCATION         "/usr/bin/rrdtool"
#define DHT11DATABASECREATE      "/opt/monoceros/scripts/create_DHT11.sh"
#define DHT22DATABASECREATE      "/opt/monoceros/scripts/create_DHT22.sh"
/********************************
* Settings
********************************/
using namespace std;
/********************************
* Functions
********************************/
int check_local_year(void);
int check_ntp(void);
int check_database_dht11(void);
int check_database_dht22(void);
int read_dht11(void);
int read_dht22(void);
int check_rrdtool(void);
void signalHandler( int signum );
/********************************
* Functions
********************************/
/********************************
* Main
********************************/
/*

int main()
{
signal(SIGINT, signalHandler);

check_rrdtool();

int result_scheck_ntp=check_ntp();

if (result_scheck_ntp==0){}else{};

int yearbuffer=check_local_year();
if (yearbuffer>=2017){
	cout<<"Time checked OK:             ["<<yearbuffer<<"]"<<endl;
	} else {
	cout<<"Time checked FAILED!:        ["<<yearbuffer<<"]"<<endl;
	return(1);
};

check_database_dht11 ();
check_database_dht22 ();

while(true){
read_dht11();
delay(200);
read_dht22();
delay(200);
}
return 0;
}

*/

void do_heartbeat()
{
   // TODO: implement processing code to be performed on each heartbeat


//while(true){
read_dht11();
delay(200);
read_dht22();
delay(200);
//}
//return 0;
//}

}


int main(void)
{

   // Define variables
   pid_t pid, sid;

   // Fork the current process
   pid = fork();
   // The parent process continues with a process ID greater than 0
   if (pid > 0)
   {
      exit(EXIT_SUCCESS);
   }
   // A process ID lower than 0 indicates a failure in either process
   else if(pid < 0)
   {
      exit(EXIT_FAILURE);
   }
   // The parent process has now terminated, and the forked child process will continue
   // (the pid of the child process was 0)

   // Since the child process is a daemon, the umask needs to be set so files and logs can be written
   umask(0);

   // Open system logs for the child process
   openlog("tmd", LOG_NOWAIT | LOG_PID, LOG_USER);
   syslog(LOG_NOTICE, "Successfully started temperature monitoring daemon!");

   // Generate a session ID for the child process
   sid = setsid();
   // Ensure a valid SID for the child process
   if(sid < 0)
   {
      // Log failure and exit
      syslog(LOG_ERR, "Could not generate session ID for child process");

      // If a new session ID could not be generated, we must terminate the child process
      // or it will be orphaned
      exit(EXIT_FAILURE);
   }
   // Change the current working directory to a directory guaranteed to exist
   if((chdir("/")) < 0)
   {
      // Log failure and exit
      syslog(LOG_ERR, "Could not change working directory to /");
      // If our guaranteed directory does not exist, terminate the child process to ensure
      // the daemon has not been hijacked
      exit(EXIT_FAILURE);
   }

 
/////////////////////////////////////////////////////////////////////
   signal(SIGINT, signalHandler);

   check_rrdtool();

   int result_scheck_ntp=check_ntp();

   if (result_scheck_ntp==0){}else{};

   int yearbuffer=check_local_year();
   if (yearbuffer>=2017){
	cout<<"Time checked OK:             ["<<yearbuffer<<"]"<<endl;
	} else {
	cout<<"Time checked FAILED!:        ["<<yearbuffer<<"]"<<endl;
	return(1);
   };

   check_database_dht11 ();
   check_database_dht22 ();
   // A daemon cannot use the terminal, so close standard file descriptors for security reasons
   close(STDIN_FILENO);
   close(STDOUT_FILENO);
   close(STDERR_FILENO);
   // Daemon-specific intialization should go here
   const int SLEEP_INTERVAL = 200;
   //        
   //
   // Enter daemon loop
////////////////////////////////////////////////////////////////////////
   while(1)
   {
      // Execute daemon heartbeat, where your recurring activity occurs
      do_heartbeat();
      // Sleep for a period of time
      //delay(SLEEP_INTERVAL);
   }
   // Close system logs for the child process
   syslog(LOG_NOTICE, "Stopping temperature monitoring daemon!");
   closelog();
   // Terminate the child process when the daemon completes
   exit(EXIT_SUCCESS);
}


/********************************
* Main
********************************/

void signalHandler( int signum ) {
   cout << "Interrupt signal (" << signum << ") received.\n";
   // cleanup and close up stuff here
   // terminate program
   exit(signum);
}

int check_local_year(void){
char yearbuffer[80];////////////Создаем буфер для времени.
const char* yearformat = "%Y";//Создаем шаблон для формирования строки времени.
time_t seconds = time(NULL);
tm* timeinfo = localtime(&seconds);
strftime(yearbuffer, 80, yearformat, timeinfo);
return(stoi(yearbuffer));
}

int check_ntp(void){
if ( !access (NTPDATE_LOCATION, 0) ){
cout<<"NTP service checked            [ OK ]"<<endl;
system(NTP_SCRIPT_LOCATION);//Запуск синхронизации времени.
}
else{
cout<<"Time maybe no real!          [ WARNING ]"<<endl;////
return(1);
}
return(0);
}

int check_rrdtool(void){
if ( !access (RRDTOOL_LOCATION, 0) ){////////////////
cout<<"Round Robin Database FOUND!        [ OK ]"<<endl;
}
else{
cout<<"Round Robin Database NOT FOUND!    [ FAIL ]"<<endl;
cout<<"Program will be TERMINATED!  [ SIGTERM ]"<<endl;
raise( SIGINT);
return(1);
}
return(0);
}

int check_database_dht11(void){

if ( !access (DHT11_DATABASE_LOCATION, 0) ){////////////////////
cout<<"Database found:              [ Ok ]"<<endl;//////////////
}///////////////////////////////////////////////////////////////
else{///////////////////////////////////////////////////////////
cout<<"Database not found:          [Database will be created!]"<<endl;

system(DHT11DATABASECREATE);
//system("./scripts/create_DHT11.sh");////////////////////////////
}///////////////////////////////////////////////////////////////

return(0);
};
int check_database_dht22(void){

if ( !access (DHT22_DATABASE_LOCATION, 0) ){////////////////////
cout<<"Database found:              [ Ok ]"<<endl;//////////////
}///////////////////////////////////////////////////////////////
else{///////////////////////////////////////////////////////////
cout<<"Database not found:          [Database will be created!]"<<endl;
system(DHT22DATABASECREATE);
//system("./scripts/create_DHT22.sh");////////////////////////////
}///////////////////////////////////////////////////////////////

return(0);
};

int read_dht11(void){

DHT11 sensor_dht11;
//sensor_dht11.DHT11PIN=DHT11_CONNECT;
sensor_dht11.setpin (DHT11_CONNECT);
//ofstream data_file_dht11;//Создаем индификатор файла для истории данных.
//Связываем индификатор с файлом для дозаписи.
//data_file_dht11.open(DHT11_FILE_LOCATION, ios_base::app);
ofstream latest_data_dht11;//Создаем индификатор файла для последних данных.
char timebuffer[80];//Создаем буфер для времени.
const char* format = "%Y%m%d%H%M%S";//Создаем шаблон для формирования строки времени.
//
time_t seconds = time(NULL);//
tm* timeinfo = localtime(&seconds);//
strftime(timebuffer, 80, format, timeinfo);//

data_dht11 the_data_dht11=sensor_dht11.dht11_read();//Чтение датчика
//data_file_dht11<<timebuffer<<" "<<the_data_dht11.temperature<<" "<<the_data_dht11.humidity<<std::endl;
std::cout<<the_data_dht11.temperature<<" "<<the_data_dht11.humidity<<std::endl;

latest_data_dht11.open(DHT11_LATEST_FILE_LOCATION,ios_base::out | ios_base::trunc);
latest_data_dht11<<timebuffer<<":"<<the_data_dht11.temperature<<":"<<the_data_dht11.humidity<<std::endl;
latest_data_dht11.close();
std::string arg11_0 = std::string("rrdtool update ");
std::string arg11_1 = std::to_string(seconds);
std::string arg11_2 = std::to_string(the_data_dht11.temperature);
std::string arg11_3 = std::to_string(the_data_dht11.humidity);
std::string commandline_11 = arg11_0 +DHT11_DATABASE_LOCATION+std::string(" ")+arg11_1+std::string(":")+ std::string(arg11_2)+std::string(":")+std::string(arg11_3);
cout<<commandline_11<<endl;
system(commandline_11.c_str());
//system(UPDATE_SCRIPT);

//data_file_dht11.close();
return 0;
};


int read_dht22(void){

DHT22 sensor_dht22;
//sensor_dht22.DHT22PIN=DHT22_CONNECT;
sensor_dht22.setpin(DHT22_CONNECT);
//ofstream data_file_dht22;//Создаем индификатор файла для истории данных.
//data_file_dht22.open(DHT22_FILE_LOCATION, ios_base::app);//Связываем индификатор с файлом для дозаписи.
ofstream latest_data_dht22;//Создаем индификатор файла для последних данных.
char timebuffer[80];//Создаем буфер для времени.
const char* format = "%Y%m%d%H%M%S";//Создаем шаблон для формирования строки времени.
time_t seconds = time(NULL);
tm* timeinfo = localtime(&seconds);
strftime(timebuffer, 80, format, timeinfo);
data_dht22 the_data_dht22=sensor_dht22.dht22_read();//Чтение датчика
//data_file_dht22<<timebuffer<<" "<<the_data_dht22.temperature<<" "<<the_data_dht22.humidity<<std::endl;
std::cout<<the_data_dht22.temperature<<" "<<the_data_dht22.humidity<<std::endl;
latest_data_dht22.open(DHT22_LATEST_FILE_LOCATION,ios_base::out | ios_base::trunc);
latest_data_dht22<<timebuffer<<":"<<the_data_dht22.temperature<<":"<<the_data_dht22.humidity<<std::endl;
latest_data_dht22.close();
std::string arg22_0 = std::string("rrdtool update ");
std::string arg22_1 = std::to_string(seconds);
std::string arg22_2 = std::to_string(the_data_dht22.temperature);
std::string arg22_3 = std::to_string(the_data_dht22.humidity);
std::string commandline_22 = arg22_0 +DHT22_DATABASE_LOCATION+std::string(" ")+arg22_1+std::string(":")+ std::string(arg22_2)+std::string(":")+std::string(arg22_3);
cout<<commandline_22<<endl;
system(commandline_22.c_str());
system(UPDATE_SCRIPT);

//data_file_dht22.close();
return 0;
};


//while(true){
//signal(SIGINT, signalHandler);
//int key;
//cout << "Going to sleep...." << endl;
//if( key == 3 ) {
//raise( SIGINT);
//}
//delay(150);

