
import os
import shutil
import random as rd
import string

xinetd='''service ctf
{
    disable = no
    socket_type = stream
    protocol    = tcp
    wait        = no
    user        = root
    type        = UNLISTED
    port        = 9999
    bind        = 0.0.0.0
    server      = /usr/sbin/chroot
    # replace helloworld to your program
    server_args = --userspec=1000:1000 /home/ctf ./%s
    banner_fail = /etc/banner_fail
    # safety options
    per_source	= 10 # the maximum instances of this service per source IP address
    rlimit_cpu	= 20 # the maximum number of CPU seconds that the service may use
    #rlimit_as  = 1024M # the Address Space resource limit for the service
    #access_times = 2:00-9:00 12:00-24:00
}'''

os.system('docker kill $(docker ps -q)')
os.system('docker rm $(docker ps -qa)')
os.system('docker rmi $(docker images -q)')
dirs=[('easy_format',9999),('easy_sc',9998),('easy_stack',9997),('easy_struct',9996),('canary',9995)]

for d,port in dirs:
    print(f'[*] building {d}...')
    if os.path.exists(d+'.docker'):
        shutil.rmtree(d+'.docker')
    os.system(f'cp docker {d}.docker -r')
    os.chdir(d+'.docker')
    open('build.sh','w').write(f'docker build -t \"{d}\" .')
    open('run.sh','w').write(f'docker run -d -p "0.0.0.0:{port}:9999" -h "{d}" --name="{d}" {d}')
    os.system(f'cp ../{d}/{d} ./bin')
    open('bin/flag','w').write('tjctf{'+''.join(rd.choice(string.hexdigits.lower()) for i in range(32))+'}')
    open('ctf.xinetd','w').write(xinetd%d)
    os.system('./build.sh')
    os.chdir('..')


