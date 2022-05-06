#!/bin/bash

echo $FLAG > /'.fl@g_1S_h3re'
export FLAG=not_flag
FLAG=not_flag

exec /usr/local/tomcat/bin/catalina.sh run
