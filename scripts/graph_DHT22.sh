#!/bin/bash
#Рисует графики

TEMP_COLOR="#ff7902"
TEMP1_COLOR="#ff4f02"
AREA_TEMP_COLOR="#92380630"
AREA_TEMP1_COLOR="#92380610"
HUM_COLOR="#1e39dd"
HUM_COLOR1="#1e6fdd"
AREA_HUM_COLOR="#1e39dd30"
AREA_HUM1_COLOR="#1e39dd10"

ARGS0="-E --y-grid 0.7:5 --width 1024 --height 768   \
 -a PNG --title="MicroClimate"   \
 --vertical-label 'Температура [C]'\
 --right-axis 1:0 --right-axis-label 'Влажность [%]'\
 --lower-limit 0  --font-render-mode normal\
 -c MGRID#E0E1E550 --no-minor -c ARROW#B0B0B0\
 -c CANVAS#16161D -c FONT#FFFFFF -c BACK#16161D \
      DEF:temp=/tmp/statistic_dht22.rrd:temperature:AVERAGE
      LINE2:temp$TEMP_COLOR:'Температура (мгновенные значения за 1 сек) / 4 часа..........'
      AREA:temp$AREA_TEMP_COLOR
      DEF:humidity=/tmp/statistic_dht22.rrd:humidity:AVERAGE
      LINE2:humidity$HUM_COLOR:'Влажность (мгновенные значения за 1 сек) / 4 часа..........'
      AREA:humidity$AREA_HUM_COLOR
      HRULE:0#E0E1E595"

ARGS1="-E --y-grid 0.7:5 --width 1024 --height 768   \
 -a PNG --title="MicroClimate"   \
 --vertical-label 'Температура [C]'\
 --right-axis 1:0 --right-axis-label 'Влажность [%]'\
 --lower-limit 0  --font-render-mode normal\
 -c MGRID#E0E1E550 --no-minor -c ARROW#B0B0B0\
 -c CANVAS#16161D -c FONT#FFFFFF -c BACK#16161D \

      DEF:temp=/tmp/statistic_dht22.rrd:temperature:AVERAGE
      LINE2:temp$TEMP_COLOR:'Температура (период осреднения 15 минут) / 24 часа..........'
      AREA:temp$AREA_TEMP_COLOR
      VDEF:temp0=temp,LAST
      GPRINT:temp0:"%3.1lf*C"

      VDEF:tempavg=temp,AVERAGE
      AREA:tempavg$AREA_TEMP1_COLOR
      LINE2:tempavg$TEMP1_COLOR:'Температура (средняя за сутки) / 24 часа..........'
      GPRINT:tempavg:"%3.1lf*C"

      DEF:humidity=/tmp/statistic_dht22.rrd:humidity:AVERAGE
      LINE2:humidity$HUM_COLOR:'Влажность (период осреднения 15 минут) / 24 часа..........'
      AREA:humidity$AREA_HUM_COLOR
      VDEF:hum0=humidity,LAST
      GPRINT:hum0:"%3.1lf%%"

      VDEF:humavg=humidity,AVERAGE
      AREA:humavg$AREA_HUM1_COLOR
      LINE2:humavg$HUM_COLOR1:'Влажность (средняя за сутки) / 24 часа..........'
      GPRINT:humavg:"%3.1lf%%"
      HRULE:0#E0E1E595"

ARGS2="-E --y-grid 0.7:5 --width 1024 --height 768   \
 -a PNG --title="MicroClimate"   \
 --vertical-label 'Температура [C]'\
 --right-axis 1:0 --right-axis-label 'Влажность [%]'\
 --lower-limit 0  --font-render-mode normal\
 -c MGRID#E0E1E550 --no-minor -c ARROW#B0B0B0\
 -c CANVAS#16161D -c FONT#FFFFFF -c BACK#16161D \

      DEF:temp=/tmp/statistic_dht22.rrd:temperature:AVERAGE
      LINE2:temp$TEMP_COLOR:'Температура (период осреднения 15 минут) / неделя..........'
      AREA:temp$AREA_TEMP_COLOR
      VDEF:temp0=temp,LAST
      GPRINT:temp0:"%3.1lf*C"

      VDEF:tempavg=temp,AVERAGE
      AREA:tempavg$AREA_TEMP1_COLOR
      LINE2:tempavg$TEMP1_COLOR:'Температура (средняя за неделю) / неделя..........'
      GPRINT:tempavg:"%3.1lf*C"

      DEF:humidity=/tmp/statistic_dht22.rrd:humidity:AVERAGE
      LINE2:humidity$HUM_COLOR:'Влажность (период осреднения 15 минут) / неделя..........'
      AREA:humidity$AREA_HUM_COLOR
      VDEF:hum0=humidity,LAST
      GPRINT:hum0:"%3.1lf%%"

      VDEF:humavg=humidity,AVERAGE
      AREA:humavg$AREA_HUM1_COLOR
      LINE2:humavg$HUM_COLOR1:'Влажность (средняя за неделю) / неделя..........'
      GPRINT:humavg:"%3.1lf%%"
      HRULE:0#E0E1E595"

ARGS3="-E --y-grid 0.7:5 --width 1024 --height 768   \
 -a PNG --title="MicroClimate"   \
 --vertical-label 'Температура [C]'\
 --right-axis 1:0 --right-axis-label 'Влажность [%]'\
 --lower-limit 0  --font-render-mode normal\
 -c MGRID#E0E1E550 --no-minor -c ARROW#B0B0B0\
 -c CANVAS#16161D -c FONT#FFFFFF -c BACK#16161D \

      DEF:temp=/tmp/statistic_dht22.rrd:temperature:AVERAGE
      LINE2:temp$TEMP_COLOR:'Температура (период осреднения 1 час ) / месяц..........'
      AREA:temp$AREA_TEMP_COLOR
      VDEF:temp0=temp,LAST
      GPRINT:temp0:"%3.1lf*C"

      VDEF:tempavg=temp,AVERAGE
      AREA:tempavg$AREA_TEMP1_COLOR
      LINE2:tempavg$TEMP1_COLOR:'Температура (средняя за месяц) / месяц..........'
      GPRINT:tempavg:"%3.1lf*C"

      DEF:humidity=/tmp/statistic_dht22.rrd:humidity:AVERAGE
      LINE2:humidity$HUM_COLOR:'Влажность (период осреднения 1 час) / месяц..........'
      AREA:humidity$AREA_HUM_COLOR
      VDEF:hum0=humidity,LAST
      GPRINT:hum0:"%3.1lf%%"

      VDEF:humavg=humidity,AVERAGE
      AREA:humavg$AREA_HUM1_COLOR
      LINE2:humavg$HUM_COLOR1:'Влажность (средняя за месяц) / месяц..........'
      GPRINT:humavg:"%3.1lf%%"
      HRULE:0#E0E1E595"


ARGS4="-E --y-grid 0.7:5 --width 1024 --height 768   \
 -a PNG --title="MicroClimate"   \
 --vertical-label 'Температура [C]'\
 --right-axis 1:0 --right-axis-label 'Влажность [%]'\
 --lower-limit 0  --font-render-mode normal\
 -c MGRID#E0E1E550 --no-minor -c ARROW#B0B0B0\
 -c CANVAS#16161D -c FONT#FFFFFF -c BACK#16161D \

      DEF:temp=/tmp/statistic_dht22.rrd:temperature:AVERAGE
      LINE2:temp$TEMP_COLOR:'Температура (период осреднения 365 сек) / год..........'
      AREA:temp$AREA_TEMP_COLOR
      VDEF:temp0=temp,LAST
      GPRINT:temp0:"%3.1lf*C"

      VDEF:tempavg=temp,AVERAGE
      AREA:tempavg$AREA_TEMP1_COLOR
      LINE2:tempavg$TEMP1_COLOR:'Температура (средняя за год) / год..........'
      GPRINT:tempavg:"%3.1lf*C"

      DEF:humidity=/tmp/statistic_dht22.rrd:humidity:AVERAGE
      LINE2:humidity$HUM_COLOR:'Влажность (период осреднения 365 сек) / год..........'
      AREA:humidity$AREA_HUM_COLOR
      VDEF:hum0=humidity,LAST
      GPRINT:hum0:"%3.1lf%%"

      VDEF:humavg=humidity,AVERAGE
      AREA:humavg$AREA_HUM1_COLOR
      LINE2:humavg$HUM_COLOR1:'Влажность (средняя за год) / год..........'
      GPRINT:humavg:"%3.1lf%%"
      HRULE:0#E0E1E595"




echo $ARGS0  | xargs rrdtool graph /tmp/temp_hourly_dht22.png --start -4h
echo $ARGS1 | xargs rrdtool graph /tmp/temp_daily_dht22.png --start -1d
echo $ARGS2 | xargs rrdtool graph /tmp/temp_weekly_dht22.png --start -1w
echo $ARGS3  | xargs rrdtool graph /tmp/temp_monthly_dht22.png --start -1m
echo $ARGS4  | xargs rrdtool graph /tmp/temp_yearly_dht22.png --start -1y

chmod  644        /var/www/localhost/htdocs/dht22/hourly.png
chmod  644        /var/www/localhost/htdocs/dht22/daily.png
chmod  644        /var/www/localhost/htdocs/dht22/weekly.png
chmod  644        /var/www/localhost/htdocs/dht22/monthly.png
chmod  644        /var/www/localhost/htdocs/dht22/yearly.png
chmod  644        /var/www/localhost/htdocs/dht22/index.html

mv -f /tmp/temp_hourly_dht22.png  /var/www/localhost/htdocs/dht22/hourly.png
mv -f /tmp/temp_daily_dht22.png   /var/www/localhost/htdocs/dht22/daily.png
mv -f /tmp/temp_weekly_dht22.png  /var/www/localhost/htdocs/dht22/weekly.png
mv -f /tmp/temp_monthly_dht22.png /var/www/localhost/htdocs/dht22/monthly.png
mv -f /tmp/temp_yearly_dht22.png  /var/www/localhost/htdocs/dht22/yearly.png


file="/tmp/latest_data_dht22"
temperature=($(awk -F ":" '{print $2}' /tmp/latest_data_dht22))
humidity=($(awk -F ":" '{print $3}'  /tmp/latest_data_dht22))
sed -i "s/<div id=\"data\">.*<\/div>/<div id=\"data\"> Температура : ${temperature}°C, Влажность : ${humidity}%<\/div>/" /var/www/localhost/htdocs/dht22/index.html

#ARGS1="-E --y-grid 0.7:5 --width 1024 --height 768   \
# -a PNG --title="MicroClimate"   \
# --vertical-label 'Temperature [C]'\
# --right-axis 1:0 --right-axis-label 'Humidity [%]'\
# --lower-limit 0  --font-render-mode normal\
# -c MGRID#E0E1E550 --no-minor -c ARROW#B0B0B0\
# -c CANVAS#16161D -c FONT#FFFFFF -c BACK#16161D \
#      DEF:temp=/tmp/statistic_dht22.rrd:temperature:AVERAGE
#      LINE2:temp$TEMP_COLOR:'Temperature'
#      AREA:temp$AREA_TEMP_COLOR
#
#      DEF:temp0=/tmp/statistic_dht22.rrd:temperature:AVERAGE:step=2400
#      LINE2:temp0$TEMP1_COLOR:'24 Hours temperature'
#      VDEF:tempavg=temp0,AVERAGE
#      AREA:tempavg$AREA_TEMP_COLOR
#      GPRINT:tempavg:"%5.2lf%S*C"
#
#      DEF:humidity=/tmp/statistic_dht22.rrd:humidity:AVERAGE
#      LINE2:humidity$HUM_COLOR:'Humidity'
#      AREA:humidity$AREA_HUM_COLOR
#      HRULE:0#E0E1E595"

