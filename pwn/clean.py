import os

os.system('docker kill $(docker ps -q)')
os.system('docker rm $(docker ps -qa)')
os.system('docker rmi $(docker images -q)')