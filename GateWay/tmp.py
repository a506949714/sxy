import time
import sqlite3

def fun1(temperature,datatime):
    con = sqlite3.connect("sensor.db")
    c = con.cursor()
    #c.execute('''CREATE TABLE temp(
        #id int PRIMARY KEY ,
       #temp FLOAT ,
       #datetime varchar(20))''')
    c.execute("INSERT INTO temp(temp,datetime) VALUES (?,?)",(temperature, datatime))
    con.commit()
    con.close()



while True:
    tfile = open("/sys/bus/w1/devices/28-0216001ef7ff/w1_slave")
    text = tfile.read()
    tfile.close()
    secondline = text.split("\n")[1]
    temperaturedata = secondline.split(" ")[9]
    temperature = float(temperaturedata[2:])
    temperature = temperature / 1000
    res = '%f' %temperature
    res1 = '%s' %time.strftime('%Y.%m.%d  %H:%M:%S', time.localtime(time.time()))
    fun1(res, res1)
    print("ok")
    time.sleep(300)