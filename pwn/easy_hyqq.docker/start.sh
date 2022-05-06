#!/bin/sh
# Add your startup script
# DO NOT DELETE
echo $FLAG > /flag

export FLAG=not_flag
FLAG=not_flag
/usr/sbin/sshd -D &

/etc/init.d/xinetd start;
sleep infinity;
