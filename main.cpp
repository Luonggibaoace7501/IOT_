#include <Arduino.h>
#include<WiFi.h>
#include <PubSubClient.h>
#include "FirebaseESP32.h"
#include <ArduinoJson.h>

#define FIREBASE_HOST "https://do-muc-nuoc-default-rtdb.asia-southeast1.firebasedatabase.app/"
#define FIREBASE_AUTH "h74n3w2l1CRFCUaIWAuOzQcDPCclvRXrB0lZXqe6"
FirebaseData firebaseData ;
String path="/";
FirebaseJson json;
const char* ssid ="Phong IOT"; // tên wifi nhà 
const char* password ="11111111"; // mật khẩu wifi

const byte trig = 12  ;  // sử dụng chân của cảm biên kết nối với chân vi điều khiển
const byte echo = 13 ;
const byte red = 27 ;
const byte blue = 25;
const byte green = 26;
const byte coi = 16;
const byte led = 23;
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void setup_wifi() {

  delay(10);
  // Kết nối wifi
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
  
void setup() {
  pinMode(trig, OUTPUT);     // Khởi tạo chân cảm biến
  pinMode (echo,INPUT);
  pinMode (red,OUTPUT);
  pinMode (blue,OUTPUT);
  pinMode (green,OUTPUT);
  pinMode (coi,OUTPUT);
  pinMode(led,OUTPUT);
  Serial.begin(9600);
  setup_wifi();

  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
      if (!Firebase.beginStream(firebaseData, path))
      {
        Serial.println("REASON:" + firebaseData.errorReason());
        Serial.println();
      }
}

void loop() {

       int chieudai ;
       int khoangcach;
       int mucnuoc ;
       int thetich ;
    digitalWrite(trig, 0); // khái báo phát xung từ cảm biến
    delayMicroseconds (1);
    digitalWrite(trig, 1);
    delayMicroseconds(1);
     digitalWrite(trig, 0 );
     khoangcach =  30;  //cài đặt khoảng cách ban đầu
     unsigned long dai;
     dai = pulseIn(echo,HIGH); 
     chieudai = int(dai/2/29.412+1); //tính chiều dài của bước sóng
     mucnuoc = int(khoangcach-chieudai); //tính mực nước
     thetich = int(mucnuoc*100); //thể tích nước
     Serial.print("mực mước = ");
     Serial.print(mucnuoc);
     Serial.println("cm");
     Serial.print("Thể tích =");
     Serial.print(thetich);
       Serial.println("cm^3");
     delay(100);
      if (mucnuoc>0)
    {
      Firebase.setInt(firebaseData, path = "/muc_nuoc/cao", int(mucnuoc));
      Firebase.setInt(firebaseData, path = "/muc_nuoc/thetich", int(thetich));
    }
      
    if (mucnuoc>25) {
        digitalWrite(red, LOW);   
        digitalWrite(green, HIGH);// bật đèn led 
        digitalWrite(blue, LOW);
        analogWrite(coi, 1000);    // bật còi
        Firebase.setInt(firebaseData, path = "/muc_nuoc/bon", int(3));
    }

       if (mucnuoc<5) { 
        digitalWrite(red, HIGH);   // bật đèn led 
        digitalWrite(green, LOW);
        digitalWrite(blue, LOW);
        analogWrite(coi, 1000);    // bật còi
        Firebase.setInt(firebaseData, path = "/muc_nuoc/bon", int(1));
    }
       else if (mucnuoc>5 && mucnuoc < 26) {
        digitalWrite(red, LOW);   
        digitalWrite(green, LOW);
        digitalWrite(blue, HIGH); // bật đèn led 
        analogWrite(coi, 0);     // tắt còi
        Firebase.setInt(firebaseData, path = "/muc_nuoc/bon", int(2));
    }
    
  Firebase.getInt (firebaseData, "muc_nuoc/led"); 
  if (firebaseData.intData() == 1  ){
    digitalWrite (led, HIGH);
    }
  else {
    digitalWrite (led, LOW);
  }
    Serial.println(firebaseData.intData());
  client.loop();

 

}