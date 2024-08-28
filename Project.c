#include <LiquidCrystal.h> 
LiquidCrystal lcd (2, 3, 4, 5, 6, 7); 
#include <SoftwareSerial.h> 
#include <dht11.h> 
#define RX 9 
#define TX 10 
#define dht_apin 11 // Analog Pin sensor is connected to 
dht11 dhtObject; 
int ldrPin = A1;     // LDR connected to analog pin A0 
int output_value ; 
String AP = "elegant";      // AP NAME 
String PASS = "smartwork"; // AP PASSWORD 
String API = "4AXUTFZK14BGTOAP";   // Write API KEY 9EWU4V8S8ECXFQUX 
String HOST = "api.thingspeak.com"; 
String PORT = "80"; 
int countTrueCommand; 
int countTimeCommand;  
boolean found = false;  
int valSensor = 1; 
int value; 

SoftwareSerial esp8266(RX,TX);  
void setup()
{ 
    lcd.begin(16, 2); 
    lcd.clear(); lcd.setCursor(2, 0);         
    lcd.print("  WELCOME"); 
    delay(1000); 
    lcd.clear(); 
    lcd.print("  MULTI SENSOR "); 
    lcd.setCursor(0, 1);  lcd.print("DATA USING IoT"); 
    delay(1000); 
    Serial.begin(9600); 
    esp8266.begin(115200); 
    sendCommand("AT",5,"OK"); 
    sendCommand("AT+CWMODE=1",5,"OK"); 
    sendCommand("AT+CWJAP=\""+ AP +"\",\""+ PASS +"\"",20,"OK"); 
} 
void loop()
{ 
    String 
    getData 
    = 
    "GET 
    /update?api_key="+ 
    API 
    +"&field1="+getTemperatureValue()+"&field2="+getHumidityValue()+"&field3="+getldr(); 
    sendCommand("AT+CIPMUX=1",5,"OK"); 
    
    sendCommand("AT+CIPSTART=0,\"TCP\",\""+ HOST +"\","+ PORT,15,"OK"); 
    sendCommand("AT+CIPSEND=0," +String(getData.length()+4),4,">"); 
    esp8266.println(getData);delay(1500);countTrueCommand++; 
    sendCommand("AT+CIPCLOSE=0",5,"OK"); 
} 
String getTemperatureValue()
{    
    dhtObject.read(dht_apin); 
    Serial.print("Temperature(C)= "); 
    lcd.setCursor(0, 1);  
    lcd.print("Temperature="); 
    float  temp = dhtObject.temperature; 
    Serial.println(temp); 
    lcd.print(temp); 
    delay(100); 
    return String(temp);    
} 
String getHumidityValue()
{ 
    dhtObject.read(dht_apin); 
    Serial.print(" Humidity in %="); 
    lcd.clear(); 
    lcd.print("Humidity%="); 
    float humidity = dhtObject.humidity; 
    Serial.println(humidity); 
    lcd.print(humidity); 
    delay(100); 
    return String(humidity);  
} 
String getldr()  
{ 
    int ldrValue = analogRead(ldrPin); 
    lcd.clear(); 
    lcd.print("Light intensity: "); 
    lcd.setCursor(0, 1); 
    lcd.print(ldrValue); 
} 
// You may need to adjust the threshold value based on your ambient light conditions 
int threshold = 500;  // Adjust this value based on your setup 
delay(1000);  // Adjust the delay as needed for your application 
return String(ldrValue); 
void sendCommand(String command, int maxTime, char readReplay[]) 
{ 
    Serial.print(countTrueCommand); 
    Serial.print(". at command => "); 
    Serial.print(command); 
    Serial.print(" "); 
}
while(countTimeCommand < (maxTime*1)) 
{ 
 
    esp8266.println(command);//at+cipsend 
    if(esp8266.find(readReplay))//ok 
    {    
        found = true; 
        break; 
    }
    countTimeCommand++; 
    if(found == true) 
    { 
      
        Serial.println("OYI"); 
        countTrueCommand++; 
        countTimeCommand = 0; 
    }
    if(found == false) 
    {     
        Serial.println("Fail"); 
        countTrueCommand = 0; 
        countTimeCommand = 0; 
        found = false; 
    }
} 
