/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * logger.cpp
 * Copyright (C) 2017 Andrey Ivanov <search_terminal@mail.ru>
 *
 * monoceros is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * monoceros is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "logger.h"
#include <iostream>
#include <unistd.h>
#include <string>
#include <csignal>

using namespace std;

void Logger::CreateFiles ()
{
	if (!access (FileName_1.c_str(), 0)){                   // проверка наличия массива данных
	cout<<"File "<<FileName_1<<" available"<<endl;
	}
	else{
	cout<<"File "<<FileName_1<<" not found. CREATED!"<<endl;
	system(CreateFile1.c_str());
	};
	if (!access (FileName_2.c_str(), 0)){                   // проверка наличия массива данных
	cout<<"File "<<FileName_2<<" available"<<endl;
	}
	else{
	cout<<"File "<<FileName_2<<" not found. CREATED!"<<endl;
	system(CreateFile2.c_str());
	};
	if (!access (FileName_3.c_str(), 0)){                   // проверка наличия базы данных данных
	cout<<"File "<<FileName_3<<" available"<<endl;
	}
	else{
	cout<<"File "<<FileName_3<<" not found. CREATED!"<<endl;
	system(CreateFile3.c_str());
	};
};

void Logger::CheckTime(){
char timebuffer[80];//Создаем буфер для времени.
const char* format = "%Y%m%d%H%M%S";//Создаем шаблон для формирования строки времени.
	time_t seconds = time(NULL); 
	tm* timeinfo = localtime(&seconds); 
	strftime(timebuffer, 80, format, timeinfo); //Получить время
};

void Logger::CheckYear(){
	char yearbuffer[80];//Создаем буфер для времени.
	const char* yearformat = "%Y";//Создаем шаблон для формирования строки времени.
	time_t seconds = time(NULL);
	tm* timeinfo = localtime(&seconds);
	strftime(yearbuffer, 80, yearformat, timeinfo);//Проверить год
};

void Logger::SyncClock()
{
	if (!access ("/usr/sbin/ntpdate", 0)){//Проверка наличия в системе Network Time Provider
	cout<<"NTP service checked [ OK ]"<<endl;
	system("./scripts/ntp_start.sh");//Запуск синхронизации времени.
	}
	else{
	cout<<"Time maybe no real! [ WARNING ]"<<endl;
	};
};

void Logger::CheckRRDtool()
{                                          //Проверка наличия в системе RRDtool (Round Robin database tool)	
	if ( !access ("/usr/bin/rrdtool", 0) ){//проверка наличия утилиты для работы с базой данных 
	cout<<"Round Robin Database FOUND! [ OK ]"<<endl;
	}
	else{
	cout<<"Round Robin Database NOT FOUND! [ FAIL ]"<<endl;
	cout<<"Program will be TERMINATED!  [ SIGTERM ]"<<endl;
	raise(SIGINT); //Вызов события прерывания
	}; 
};

void Logger::Write(){;};   //Метод для записи всех всех данных в файлы.
