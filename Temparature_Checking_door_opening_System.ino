#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MLX90614.h>
#include <Servo.h>
 

#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 64    // OLED display height, in pixels
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
 
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Servo motor;
int ir;
double temp_amb;
double temp_obj;
 
void setup()
{
  //Serial.begin(9600);
  motor.attach(10);
  pinMode(9,OUTPUT);
  pinMode(11,INPUT);
  pinMode(12,OUTPUT);
  mlx.begin();         //Initialize MLX90614
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //initialize with the I2C addr 0x3C (128x64)
  
  display.clearDisplay();
  display.setCursor(25,15);  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Temp Monitor:");
  display.setCursor(25,35);
  display.setTextSize(1);
  display.print("Initializing");
  display.display();
  delay(5000);
}
 
void loop()
{
 
  temp_amb = mlx.readAmbientTempF();
  temp_obj = mlx.readObjectTempF();
  
  temp_obj = temp_obj-13;
  if(temp_obj<99)
  {
  digitalWrite(9,0);
  display.clearDisplay();
  display.setCursor(25,10);  
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.println("Temp:");
  display.setCursor(25,30);
  display.setTextSize(2);
  display.print(temp_obj);
  display.print((char)247);
  display.print("F");
  display.display();
  motor.write(20);
  
  }
  else{
    digitalWrite(9,1);
    display.clearDisplay();
    display.setCursor(25,10);
    display.setTextSize(1);
    display.print(temp_obj);
    display.print((char)247);
    display.print("F");
    display.setCursor(25,30);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.print("Danger");
    
    display.display();
    motor.write(120);
    delay(2000);
  }
  ir = digitalRead(11);
  if(ir==0)
  {
    digitalWrite(12,1);
    
  }
  else
  {
    digitalWrite(12,0);
  }
 
  delay(1000);
}
