import time
while True:
    tfile = open("/sys/bus/w1/devices/28-0216001ef7ff/w1_slave")
    text = tfile.read()
    tfile.close()
    secondline = text.split("\n")[1]
    temperaturedata = secondline.split(" ")[9]
    temperature = float(temperaturedata[2:])
    temperature = temperature / 1000
    res = '%f' %temperature
    output = open('/var/www/html/temperature', 'w')
    output.write(res)
    output.close
    print("ok")
    time.sleep(1)