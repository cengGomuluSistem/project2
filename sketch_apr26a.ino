#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "calismurat.com";
const char* password = "Savis1987.";
const char* mqtt_server = "m21.cloudmqtt.com";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;


const int gasPin = D0;
const int gasPin1 = D1;

const int buzzerPin = D2; //Define buzzerPin
const int buzzerPin1 = D3; //Define buzzerPin
const int buzzerPin2 = D4; //Define buzzerPin

void setup_wifi() { //WIFI Bağlantısı
delay(10);
Serial.println();
Serial.println(ssid);
Serial.println("BAGLANILIYOR");
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
randomSeed(micros());
Serial.println("");
Serial.println("WIFI BAGLANDI");
Serial.println("IP ADRES: ");
Serial.println(WiFi.localIP());
}

//GELEN MQTT MESAJLARI
void callback(char* topic, byte* payload, unsigned int length) {
Serial.print("MESAJ GELDI [");
Serial.print(topic);
Serial.print("] ");
for (int i = 0; i < length; i++) {
Serial.print((char)payload[i]);
}
Serial.println();
}

//MQTT SERVER  BAGLAN
void reconnect() {
while (!client.connected()) {
Serial.println("TEKRAR MQTT BAGLANILIYOR");
String clientId = "ESP8266Client-";
clientId += String(random(0xffff), HEX);
if (client.connect(clientId.c_str()), "t4h4", "neshecomis") {
Serial.println("BAGLANDI");
//client.publish("esp8266", "Merhaba"); //MesajGonder topiğinde Merhaba paylaş
//client.subscribe("esp8266"); //MesajOku topiğine üye ol, gelen mesajları oku
} else {
Serial.print("failed, rc=");
Serial.print(client.state());
Serial.println(" 5 saniye sonra tekrar denenecek");
delay(5000);
}}}

void setup() {
Serial.begin(115200);

pinMode(D6,OUTPUT);
pinMode(buzzerPin, OUTPUT); //Set buzzerPin as output
pinMode(buzzerPin1, OUTPUT); //Set buzzerPin as output
pinMode(buzzerPin2, OUTPUT); //Set buzzerPin as output

setup_wifi();
client.setServer(mqtt_server, 1883); // 1883 MQTT Server Portunu ayarlayınız
client.setCallback(callback);
}

void loop() {
if (!client.connected()) {
reconnect();
}
client.loop();




//2 saniyede bir Merhaba mesajı gönder
long now = millis();
if (now - lastMsg > 2000) {
lastMsg = now;
int a = digitalRead(gasPin);
int b = digitalRead(gasPin1);
int c =1;
//++value;
//snprintf (msg, 75, "Merhaba", value);

if(a==0){

  Serial.print("a SENSOR DEGERI: ");
Serial.println(a);  
delay(2000);
client.publish("esp8266", "a yangin");
  digitalWrite(D6, HIGH);
  analogWrite(buzzerPin, HIGH); //Setting pin to high
  analogWrite(buzzerPin1, HIGH); //Setting pin to high
  analogWrite(buzzerPin2, HIGH); //Setting pin to high
  delay(1000); //Delaying
  analogWrite(buzzerPin ,LOW); //Setting pin to LOW
  analogWrite(buzzerPin1 ,LOW); //Setting pin to LOW
  analogWrite(buzzerPin2 ,LOW); //Setting pin to LOW
  digitalWrite(D6, LOW);
  delay(1000); //Delaying
  delay(500);
  

}
if (b==0){

  Serial.print("b SENSOR DEGERI: ");
Serial.println(b);  
client.publish("esp8266", "b yangin");
  digitalWrite(D6, HIGH);
  analogWrite(buzzerPin, HIGH); //Setting pin to high
  analogWrite(buzzerPin1, HIGH); //Setting pin to high
  analogWrite(buzzerPin2, HIGH); //Setting pin to high
  delay(1000); //Delaying
  analogWrite(buzzerPin ,LOW); //Setting pin to LOW
  analogWrite(buzzerPin1 ,LOW); //Setting pin to LOW
  analogWrite(buzzerPin2 ,LOW); //Setting pin to LOW
  digitalWrite(D6, LOW);
  delay(1000); //Delaying
  delay(500);

  
  

}
//delay(7000);

}}
