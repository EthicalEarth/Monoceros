#!/bin/bash
#Создает базу данных
rrdtool create /tmp/statistic_dht22.rrd --step 1 --start N \
        DS:temperature:GAUGE:1:-40:70 \
        DS:humidity:GAUGE:1:0:100 \
        RRA:AVERAGE:0.5:1:14400 \
        RRA:AVERAGE:0.5:900:96 \
        RRA:AVERAGE:0.5:900:672 \
        RRA:AVERAGE:0.5:3600:720 \
        RRA:AVERAGE:0.5:365:86400
#1:14400
#900:96
