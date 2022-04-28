
import os
dirs=[('easy_format',9999),('easy_sc',9998),('easy_stack',9997),('easy_struct',9996),('canary',9995)]
for d,port in dirs:
    os.system(os.path.join(d+'.docker','run.sh'))