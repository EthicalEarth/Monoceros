#! /bin/bash
#Произносит текущие данные
temperature_dht11=($(awk -F ":" '{print $2}' /tmp/latest_data_dht11))
humidity_dht11=($(awk -F ":" '{print $3}'  /tmp/latest_data_dht11))
temperature_dht22=($(awk -F ":" '{print $2}' /tmp/latest_data_dht22))
humidity_dht22=($(awk -F ":" '{print $3}'  /tmp/latest_data_dht22))
temperature_dht22_1=($(printf "%1.0f" $temperature_dht22))
humidity_dht22_1=($(printf "%1.0f" $humidity_dht22))

echo $temperature_dht11
echo $humidity_dht11
echo $temperature_dht22_1
echo $humidity_dht22_1

### Произношение с учетом знака температуры на улице.

if (("$temperature_dht22_1" > "0"))
then
	echo "Температура в комнате " $temperature_dht11 "градусов."\
	"Температура на улице " $temperature_dht22_1 " градусов, "\
	"Влажность на улице" $humidity_dht22_1 "процента." \
	| festival --tts --language russian
else
	echo "Температура в комнате " $temperature_dht11 "градусов."\
	"Температура на улице минус" $temperature_dht22_1 " градусов, "\
	"Влажность на улице" $humidity_dht22_1 "процента." \
	| festival --tts --language russian
fi

### Произношение с учетом знака температуры на улице.




###Deprecated
#echo "Температура в комнате " $temperature_dht11 "градусов."\
#     "Температура на улице " $temperature_dht22_1 " градусов, "\
#     "Влажность на улице" $humidity_dht22_1 "процента." \
#     | festival --tts --language russian
