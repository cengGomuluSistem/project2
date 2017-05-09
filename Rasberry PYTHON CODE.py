import paho.mqtt.client as mqtt
import time
import smtplib
from email.mime.text import MIMEText
istemci = mqtt.Client()
def mesaj_geldiginde(client, userdata, msg):
    print msg.topic+" "+str(msg.payload)
    
    if str(msg.payload) == "a yangin":
        textfile = "a.txt"
        fp = open(textfile, 'rb')
        msg = MIMEText(fp.read())
        fp.close()

        me = "kolektifaparman@gmail.com"
        you = "tahayasin@outlook.com"

        mailServer = smtplib.SMTP("smtp.gmail.com", 587)
        mailServer.ehlo()
        mailServer.starttls()
        mailServer.ehlo()
        mailServer.login("kolektifapartman@gmail.com", "ohdude_4627")

        msg['Subject'] = "Yangin ihbar %s" % textfile
        msg['From'] = me
        msg['To'] = you

        mailServer.sendmail(me, [you], msg.as_string())
        mailServer.quit()
        
    elif str(msg.payload) == "b yangin":
        textfile = "b.txt"
        fp = open(textfile, 'rb')
        msg = MIMEText(fp.read())
        fp.close()

        me = "kolektifaparman@gmail.com"
        you = "tahayasin@outlook.com"

        mailServer = smtplib.SMTP("smtp.gmail.com", 587)
        mailServer.ehlo()
        mailServer.starttls()
        mailServer.ehlo()
        mailServer.login("kolektifapartman@gmail.com", "ohdude_4627")

        msg['Subject'] = "Yangin ihbar %s" % textfile
        msg['From'] = me
        msg['To'] = you

        mailServer.sendmail(me, [you], msg.as_string())
        mailServer.quit()       

def baglanti_saglandiginda(client, userdata, flags, rc):
    print "Sunucuya baglandi."
    client.subscribe("esp8266")

istemci.on_connect = baglanti_saglandiginda
istemci.on_message = mesaj_geldiginde
istemci.connect ("m21.cloudmqtt.com", 1883, 60)
istemci.loop_forever()
    
