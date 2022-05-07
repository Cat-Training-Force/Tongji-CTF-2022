#!/bin/bash

if [[ -f /flag.sh ]]; then
	source /flag.sh
fi

service cron start

cd /app && mkdir EasyFS

if [ "$APP_CMD" ];then
	$APP_CMD
else
	/usr/local/openjdk-8/bin/java -jar /app/app.jar
fi
