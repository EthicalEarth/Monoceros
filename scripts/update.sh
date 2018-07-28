#! /bin/bash
#file="/tmp/latest_data_home"
#temperature=($(awk -F ":" '{print $2}' /tmp/latest_data_home))
#humidity=($(awk -F ":" '{print $3}'  /tmp/latest_data_home))
#sed -i "s/<div id=\"data\">.*<\/div>/<div id=\"data\"> Температура : ${temperature}°C, Влажность : ${humidity}%<\/div>/" /var/www/localhost/htdocs/index.html
#rrdtool update /tmp/temperature_home.rrd N:${temperature}:${humidity}
