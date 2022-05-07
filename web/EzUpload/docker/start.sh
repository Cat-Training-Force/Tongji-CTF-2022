#!/bin/bash
echo $FLAG > /flag
chmod 755 /flag

export FLAG=not_flag
FLAG=not_flag

/etc/init.d/apache2 restart
service mysql restart
/usr/bin/tail -f /dev/null
