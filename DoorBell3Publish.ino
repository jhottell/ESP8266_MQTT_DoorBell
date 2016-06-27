//########################################################################
//#  ESP8266 MQTT DoorBell for a four bell system, adds more tunes.       #
//#  Blog post, videos, and code can  be found at www.electronhacks.com  #
//#  Please have fun, modify, and reuse this code.                       #
//########################################################################


//##### Declarations and Variables #####
#include <PubSubClient.h>
#include <ESP8266WiFi.h>
int delay1 = 50;
char vInp5 = 0;
int vA0 = 0;
int iA0 = 0;
int Counter = 0;
String rx;
int  rxLength = 0;
//Configuration, enter your own values here
char ssid[]         = "shp";                 // your network name also called SSID
char password[]     = "fef105ec00";       // your network password
char server[]       = "192.168.1.165";       // MQTT Server IP or machine name
char topic[]        = "DoorBell";             // MQTT Topic
char mQTTID[]       = "ESP8266DoorBell";      // MQTT ID. Make this unique for each device connecting to the MQTT Broker or they will disconnect eachother!
char mQTTUser[]     = "guest";                 // MQTT UserName (See below for modification if you don't use user and password)
char mQTTPassword[] = "12345";                 // MQTT Password (See below for modification if you don't use user and password)

WiFiClient wifiClient;
PubSubClient client(server, 1883, callback, wifiClient);


//##### Void Setup, runs once on startup #####
void setup()
{
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(16, OUTPUT);      
  pinMode(5, INPUT_PULLUP);
  
  Serial.begin(115200);
  Serial.print("Attempting to connect to Network named: ");   
  Serial.println(ssid);   
  WiFi.begin(ssid, password);  
  while ( WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");     // print dots while we wait to connect
    delay(300);
  }
  
  Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");
  while (WiFi.localIP() == INADDR_NONE) 
  {
    Serial.print(".");     // print dots while we wait for an ip addresss
    delay(300);
  }
  Serial.println("\nIP Address obtained");
}




//##### Main Program #####
void loop()  
{ 
  //Reconnect if we are not subscribed to the LaunchPad/In topic
  if (!client.connected()) { 
    Serial.println("Disconnected. Reconnecting....");
    delay(30000); //Wait 30 seconds between connection attempts
    if(!client.connect(mQTTID, mQTTUser, mQTTPassword)) {   //Comment out this line if you DON"T have a User or Password for the MQTT Broker 
  //if(!client.connect(mQTTID)) {                           //Comment out this line if you DO have a User or Password for the MQTT Broker 
      Serial.println("Connection failed");
    } else {
      Serial.println("Connection success");
      if(client.subscribe(topic)) {
        Serial.println("Subscription successfull");
        client.publish(topic, "Front Door Bell Subscribed");
      }
    }
  }

  ///// Evaluate input 13 and send a message if the value changes 
  if (digitalRead(5) != vInp5)
  {
   vInp5 = digitalRead(5);
   if (vInp5 == LOW)
   {    
     client.publish(topic, "FrontDoorBell");
     Serial.println("TX: FrontDoorBell");
     chime1();
   }
  } 

  client.loop(); // Check if any subscribed messages were received
  delay(10);
}



//##### Subroutines #####

///// VOID CALLBACK - prints to the serial monitor if we recieve a MQTT message /////
void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("RX: ");
  //Convert and clean up the MQTT payload messsage into a String
  rx = String((char *)payload);                    //Payload is a Byte Array, convert to char to load it into the "String" object 
  rxLength = rx.length();                          //Figure out how long the resulting String object is 
  for (int i = length; i <= rxLength; i++)         //Loop through setting extra characters to null as garbage may be there
  {
    rx.setCharAt(i, ' ');
  }
  rx.trim();                                       //Use the Trim function to finish cleaning up the string   
  Serial.print(rx);                                //Print the recieved message to serial
  Serial.println();

  //Evaulate the recieved message to do stuff
  if (rx == "Chime1")
  {
    chime1();
  } 
  if (rx == "Chime2")
  {
    chime2();
  }                                 
  if (rx == "Chime3")
  {
    chime3();
  }   
  if (rx == "Chime4")
  {
    chime4();
  }   
  if (rx == "Chime5")
  {
    chime5();
  }   
  if (rx == "Chime6")
  {
    chime6();
  } 
  if (rx == "Bell1")
  {
    bell(16);
  } 
  if (rx == "Bell2")
  {
    bell(14);
  }
  if (rx == "Bell3")
  {
    bell(13);
  }
  if (rx == "Bell4")
  {
    bell(12);
  }
      
}


void bell(int bell)
{
   digitalWrite(bell, 1);   
   delay(100);
   digitalWrite(bell, 0);     
}

void chime1()
{
    digitalWrite(12, 1);  //4
    delay(delay1);                                    
    digitalWrite(12, 0);  //4                             
    delay(700); 
     digitalWrite(14, 1); //2 
    delay(delay1);                                    
    digitalWrite(14, 0);  //2                             
    delay(700);
     digitalWrite(13, 1);  //3
    delay(delay1);                                     
    digitalWrite(13, 0);    //3                            
    delay(700);
     digitalWrite(16, 1);  //1
    delay(delay1);                                    
    digitalWrite(16, 0);   //1                             
    delay(1500); 
     digitalWrite(16, 1);  
    delay(delay1);                                     
    digitalWrite(16, 0);                               
    delay(700); 
     digitalWrite(13, 1);  
    delay(delay1);                                     
    digitalWrite(13, 0);                               
    delay(700);
     digitalWrite(12, 1);  
    delay(delay1);                                     
    digitalWrite(12, 0);                               
    delay(700);
     digitalWrite(14, 1);  
    delay(delay1);                                     
    digitalWrite(14, 0);                               
    delay(2000); 
}

void chime2()
{
    digitalWrite(12, 1);  //4
    delay(delay1);                                     
    digitalWrite(12, 0);  //4                             
    delay(500); 
     digitalWrite(13, 1); //3
    delay(delay1);                                    
    digitalWrite(13, 0);  //3                            
    delay(500);
    digitalWrite(14, 1);  //2 
    delay(delay1);                                    
    digitalWrite(14, 0);  //2                             
    delay(500);
    digitalWrite(16, 1);  //1
    delay(delay1);                                    
    digitalWrite(16, 0);  //1                             
    delay(500);   
    digitalWrite(12, 1);  //4
    delay(delay1); 
    digitalWrite(12, 0);  //4                             
    delay(500); 
    digitalWrite(13, 1); //3
    delay(delay1);                                     
    digitalWrite(13, 0);  //3                            
    delay(500);
    digitalWrite(14, 1);  //2 
    delay(delay1);                                     
    digitalWrite(14, 0);  //2                             
    delay(500);
    digitalWrite(16, 1);  //1
    delay(delay1);                                    
    digitalWrite(16, 0);  //1                             
                    
}

void chime3()
{
    digitalWrite(16, 1);  //1
    delay(delay1);                                    
    digitalWrite(16, 0);  //1    
    delay(500);   
    digitalWrite(14, 1);  //2 
    delay(delay1);                                    
    digitalWrite(14, 0);  //2                             
    delay(500);
    digitalWrite(13, 1);  //3
    delay(delay1);                                     
    digitalWrite(13, 0);  //3                            
    delay(500);
    digitalWrite(12, 1);  //4
    delay(delay1);                                   
    digitalWrite(12, 0);  //4                             
    delay(500); 
    digitalWrite(16, 1);  //1
    delay(delay1);                                     
    digitalWrite(16, 0);  //1    
    delay(500);   
    digitalWrite(14, 1);  //2 
    delay(delay1);                                    
    digitalWrite(14, 0);  //2                             
    delay(500);
    digitalWrite(13, 1);  //3
    delay(delay1);                                     
    digitalWrite(13, 0);  //3                            
    delay(500);
    digitalWrite(12, 1);  //4
    delay(delay1);                                    
    digitalWrite(12, 0);  //4                             
    delay(500); 
}

void chime4()
{
    digitalWrite(13, 1);  //3
    delay(delay1);                                    
    digitalWrite(13, 0);  //3                            
    delay(400);  
    digitalWrite(14, 1);  //2 
    delay(delay1);                                    
    digitalWrite(14, 0);  //2                             
    delay(400);
    digitalWrite(13, 1);  //3
    delay(delay1);                                     
    digitalWrite(13, 0);  //3                            
    delay(400);  
    digitalWrite(14, 1);  //2 
    delay(delay1);                                    
    digitalWrite(14, 0);  //2                             
    delay(400);  
    digitalWrite(13, 1);  //3
    delay(delay1);                                    
    digitalWrite(13, 0);  //3                            
    delay(400);
    digitalWrite(12, 1);  //4
    delay(delay1);                                    
    digitalWrite(12, 0);  //4                             
    delay(600);   
}

void chime5()
{
    digitalWrite(16, 1);  //1
    delay(delay1);                                    
    digitalWrite(16, 0);  //1    
    delay(200);   
    digitalWrite(12, 1);  //4
    delay(delay1);                                    
    digitalWrite(12, 0);  //4                             
    delay(200);
    digitalWrite(16, 1);  //1
    delay(delay1);                                    
    digitalWrite(16, 0);  //1    
    delay(200);   
    digitalWrite(12, 1);  //4
    delay(delay1);                                   
    digitalWrite(12, 0);  //4                             
    delay(200);
    digitalWrite(16, 1);  //1
    delay(delay1);                                     
    digitalWrite(16, 0);  //1    
    delay(200);   
    digitalWrite(13, 1);  //3
    delay(delay1);                                   
    digitalWrite(13, 0);  //3                            
    delay(200);  
    digitalWrite(16, 1);  //1
    delay(delay1);                                 
    digitalWrite(16, 0);  //1    
    delay(200);   
    digitalWrite(13, 1);  //3
    delay(delay1);                                    
    digitalWrite(13, 0);  //3                            
    delay(200);  
    digitalWrite(14, 1);  //2 
    delay(delay1);                                    
    digitalWrite(14, 0);  //2                             
    delay(600);   
}

void chime6()
{
    digitalWrite(12, 1);  //4
    delay(delay1);                                    
    digitalWrite(12, 0);  //4                             
    delay(700);
     digitalWrite(14, 1); //2 
    delay(delay1);                                    
    digitalWrite(14, 0);  //2                             
    delay(600);   
}
