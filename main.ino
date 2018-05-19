#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Servo.h>
#include <MPU6050.h>

// OLED display TWI address
#define OLED_ADDR   0x3C

Adafruit_SSD1306 display(-1);

int sensorPin = A13;    // LDR
int sensorValue = 0;    // LDR

int potiPin = A14;    // Poti
int potiValue = 0;    // Poti

const int buttonPin_1 = 30;     // the number of the pushbutton pin
const int buttonPin_2 = 28;     // the number of the pushbutton pin
int row_count = 0;
int buttonState_1 = 0; 
int buttonState_2 = 0; 
int x = 0;
int select = 0;
int select_flag = false;

Servo servo_eye_y;  // create servo object to control a servo
Servo servo_eye_x;  // create servo object to control a servo
Servo  servo_mouth;

MPU6050 sensor;
int16_t ax, ay ,az;
int16_t gx, gy, gz;


#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


void setup() 
{
  
  select = 0;
  // Initilize Buttom
  pinMode(buttonPin_1, INPUT);
  pinMode(buttonPin_2, INPUT);
  
  // initialize and clear display
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();

  // update display with all of the above graphics
  display.display();
  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  servo_eye_y.attach(9);  // attaches the servo on pin 9 to the servo object
  servo_eye_x.attach(8); 
  servo_mouth.attach(10); 
  Wire.begin();
  
  Serial.begin(9600);
  Serial.println (sensor.testConnection ( ) ? "Successfully Connected" : "Connection failed"); 

  delay (1000); 
  Serial.println ( "Taking Values from the sensor" );
  delay (1000);
}



void loop() 
{
  
  buttonState_1 = digitalRead(buttonPin_1);
  buttonState_2 = digitalRead(buttonPin_2);
  sensorValue = analogRead(sensorPin);
  potiValue = analogRead(potiPin);

 
   
  if(buttonState_1 == HIGH && select_flag == false)
  {
    row_count = (row_count+8) % 32;
  }
  if(buttonState_2 == HIGH)
  {
    select = row_count/8;
    select_flag = ToggleFlag(select_flag);
  }
  
  if(sensorValue < 200 )
  {
    display.invertDisplay(true);
  }
  else
  {
     display.invertDisplay(false);
  }

  display.clearDisplay();
  if(select_flag == true)
  {
    PrintSelection();
  }
  else
  {
    PrintMenu();
  }
    
  display.display();
  delay(200);

  
}

void PrintMenu()
{
   display.setTextSize(1);
  display.setCursor(0,row_count);
  display.println(">");
  display.setCursor(7,0);
  display.println("Poti 2 Servo");
  display.setCursor(7,8);
  display.println("MPU 2 Servo");
  display.setCursor(7,16);
  display.println("LED");
  display.setCursor(7,24);
  display.println("Clock");

}

void PrintSelection()
{
  display.setTextSize(1);
  switch(select)
  {
    case 0:
      display.setCursor(0,0);
      display.println("Poti 2 Servo");
      display.setCursor(20,10);
      display.println( potiValue );
      potiValue = map(potiValue, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
      servo_mouth.write(potiValue);  
      break;
    case 1:
      display.setCursor(0,0);
      display.println("MPU 2 Servo");
      sensor.getMotion6 (&ax, &ay, &az, &gx, &gy, &gz);
      ax = map (ax, -17000, 17000, 20, 160) ;
      ay = map (ay, -17000, 17000, 20, 160) ;
      az = map (az, -17000, 17000, 40, 120) ;
      display.setCursor(20,10);
      display.println(ax);
      display.setCursor(20,20);
      display.println( ay);
      
      Serial.println (az);
      Serial.println (gx);
      servo_mouth.write (az); 
      servo_eye_x.write (ax); 
      servo_eye_y.write (ay); 
      break;
    case 2:
      display.setCursor(0,0);
      display.println("LDR");
      
      display.setTextSize(2);
      display.setCursor(20,10);
      display.println( sensorValue );
      break;    
    case 3:
      
      display.setCursor(0,0);
      display.println("Clock");
      
      display.setTextSize(2);
      display.setCursor(20,10);
      display.println( "18:32" );
      break;
    default:
      break; 
  }
}

bool ToggleFlag(bool flag)
{
  if(flag == true)
  {
    flag = false ;
  }
  else 
  {
    flag = true; 
  }
  return flag;  
}


