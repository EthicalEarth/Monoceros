/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * logger.h
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

#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <iostream>
#include <string>  

class Logger
{
public:
Logger();                                                       //Конструктор класса
	 
void CreateFiles();                                             //Создать файлы если отстутсвуют
void CheckTime();	                                            //Получить время
void CheckYear();	                                            //Проверить год
void SyncClock();	                                            //Синхронизировать время  //Проверка наличия в системе Network Time Provider
void CheckRRDtool();                                            //Проверка наличия в системе RRDtool (Round Robin database tool)	 
void Write();                                                   //Метод для записи всех всех данных в файлы.	 
	 
protected:

private:

int ID;                                                              //Вывод к которому подключен датчик
std::string baseType;                                                //Тип датчика 	 
std::string baseDIR=std::string("/tmp/");	                         //Базовая папка
std::string baseFilenameArchive = std::string("array_");             //Базовый шаблон текстового архива
std::string baseFilenameArchiveLatest = std::string("array_latest"); //Базовый шаблон текстового файла последних данных	 
std::string baseFilenameDatabase = std::string("database_");         //Базовый шаблон базы данных
std::string baseFilenameSeparator = std::string("_"); 	             //Разделитель слов
std::string baseFilenameDatabasePrefix = std::string(".rrd");	     //Префикс формата файла
std::string baseID = std::to_string(ID);                             //Айди в строку
std::string FileName_1 = baseDIR + baseFilenameArchive + baseType + baseFilenameSeparator + baseID;                             //   /tmp/array_ DHT22 _ 4         
std::string FileName_2 = baseDIR + baseFilenameArchiveLatest + baseType + baseFilenameSeparator + baseID;                       //   /tmp/array_latest_ DHT22 _ 4
std::string FileName_3 = baseDIR + baseFilenameDatabase + baseType +baseFilenameSeparator+ baseID + baseFilenameDatabasePrefix; //   /tmp/database_ DHT22 _ 4 .rrd
std::string CommandCreate = std::string("touch ");
std::string CreateFile1 = CommandCreate + FileName_1; //Создать первый файл
std::string CreateFile2 = CommandCreate + FileName_2; //создать второй файл
std::string CreateFile3 = CommandCreate + FileName_3; //создать базу данных	 
	 
};

#endif // _LOGGER_H_

