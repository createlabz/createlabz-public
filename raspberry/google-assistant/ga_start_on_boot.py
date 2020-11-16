import urllib3
import time
import subprocess
import os

def isInternetConnected():
    try:
        http = urllib3.PoolManager()
        r = http.request('GET', 'https://google.com/')
        print(r.status)
        if r.status == 200:
            return True
    except Exception as err: 
        print(err)
    
    return False

while True:
    if isInternetConnected():
        # os.system("source /home/pi/env/bin/activate")
        os.system("/home/pi/env/bin/google-assistant-demo --project-id rpi--assistant-218a0 --device-model-id rpi--assistant-218a0-rpi-google-assistant-rqzoq6")
        break
        # run = subprocess.run(["google-assistant-demo ", "--project-id","rpi--assistant-218a0","--device-model-id","rpi--assistant-218a0-rpi-google-assistant-rqzoq6"])
        # print(run)
        # break
    time.sleep(1)
