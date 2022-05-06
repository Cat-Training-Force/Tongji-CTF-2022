#!/bin/bash

if [[ -f /flag.sh ]]; then
	source /flag.sh
fi

cd /usr/local/tomcat/webapps/

if [ "$APP_CMD" ];then
	su ctf -c "$APP_CMD"
else
    su ctf -c "/usr/local/tomcat/bin/catalina.sh run"
fi
