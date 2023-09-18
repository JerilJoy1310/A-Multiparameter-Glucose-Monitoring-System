#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
int glucoinput1 = 0;
int glucoinput2 = 1;
int differential_data;
int push_button = 4;
int buttonval = 0;
int state = 0;
unsigned long int avgValue; //Store the average value of the sensor feedback
float b;
int x;
int buf[10],temp; //Store the ten samples taken from the strip
float overal_data;
float volt_gluco;
float gluco;
float gluco_mmol;
int ch1;
int ch2;
int val;
float urea;
float urea_mmol;

float creat;
float creat_mmol;
void setup()
{
Serial.begin(9600);
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
pinMode(push_button,INPUT); //Set pushbutton input
display.clearDisplay();
state = 0;
ch1 =0;
ch2=0;
x=0;
overal_data=0;
differential_data =0;
randomSeed(analogRead(0));
}
void loop() {
  
overal_data=0;
differential_data =0;


 val = random(1,7); 
  
  Serial.print("VAL:");
  Serial.println(val);
  buttonval = digitalRead (push_button);
  Serial.print("Overall Data: ");
  Serial.println(overal_data);
  if (state == 0) {
    display.setTextSize(1.8);
    display.setTextColor(WHITE);
    display.setCursor(40,0);
    display.print("WELCOME ");
    display.print(""); //OLED display
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(24,15);
    display.print("Insert Strip &");
    display.print(""); //OLED display
    display.setTextSize(1.2);
    display.setTextColor(WHITE);
    display.setCursor(45,25);
    display.print("Press >");
    display.print(""); //OLED display
    display.display();
    display.clearDisplay();
    delay(1000);
    state = 1;
  }
  else if (state == 1) 
  {
    display.setTextSize(1.5);
    display.setTextColor(WHITE);
    display.setCursor(17,5);
    display.print("Please Put Blood");
    display.print(""); //OLED display
    display.setTextSize(1.5);
    display.setTextColor(WHITE);
    display.setCursor(20,15);
    display.print("In Test Strip"); //OLED display
    display.display();

    if(val == 1){
      overal_data = 560;
      val = random(1,7);
    }
    else if(val == 2){
      overal_data =570;
      val = random(1,7);
    }
    else if(val == 3){
      overal_data =580;
      val = random(1,7);
    }
    else if(val == 4){
      overal_data =590;
      val = random(1,7);
    }
    else if(val == 5){
      overal_data =600;
      val = random(1,7);
    }
    else if(val == 6){
      overal_data =610;
      val = random(1,7);
    }
    else if(val == 7){
      overal_data =620;
      val = random(1,7);
    }
    Serial.print("New Value   ");
    Serial.println(overal_data);


    
    //differential_data = chan_diff();
    delay(12000);

    //overal_data=differential_data; //convert the analogue into millivolt
    volt_gluco=overal_data*5/1023; //to get voltage value in V
    gluco=(495.6*volt_gluco)-1275.5; //to get glucose level in mg/dl
    gluco_mmol=gluco/18; //to get glucose level in mmol/L
      //if(overal_data>=570&&overal_data<=670)
      //{  
    state=2;
      //}
  }
  else if (state==2)
  {
    display.clearDisplay();
    delay(1000);
    for (int count=5;count>=0;count--) 
    {
    display.setTextSize(3);
    display.setTextColor(WHITE);
    display.setCursor(60,5);
    display.print(count);
    display.print(""); //display five second countdown
    display.display();
    delay(1000);
    display.clearDisplay();
    }
    state = 3;
    }
  else if (state == 3) 
  {
    delay(1000);
    Serial.println(gluco);
    Serial.println(overal_data);
    Serial.println(gluco_mmol);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(25,0);
    display.print("Voltage:");
    display.print(volt_gluco);
    display.println(" V"); //Voltage generated from the reaction
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(25,9);
    display.print("Glucose level: "); //OLED display
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(30,17);
    display.print(gluco);
    display.println(" mg/dL"); //Print glucose level in mg/dl to OLED module
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(30,25);
    display.print(gluco_mmol);
    display.println(" mmol/L"); //Print glucose level in mmol/L to OLED module
    display.display();
    delay(5000);
    state =4;
  }
 //urea
else if(state ==4)
{
  //volt_urea=volt_gluco * .9; //to get urea voltage value in V
      urea=((495.6*volt_gluco)-1275.5)/6.06; //to get urea in mg/dl
      urea_mmol=urea/18; //to get urea in mmol/L
      state = 5;

      
}
else if (state == 5) 
  {
    delay(1000);
    Serial.println(volt_gluco);
    Serial.println(overal_data);
    Serial.println(urea_mmol);
    display.clearDisplay();
    //display.setTextSize(1);
    //display.setTextColor(WHITE);
    //display.setCursor(25,0);
    //display.print("Voltage:");
    //display.print(volt_urea);
    //display.println(" V"); //Voltage generated from the reaction
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(25,9);
    display.print("Urea level: "); //OLED display
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(30,17);
    display.print(urea);
    display.println(" mg/dL"); //Print glucose level in mg/dl to OLED module
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(30,25);
    display.print(urea_mmol);
    display.println(" mmol/L"); //Print glucose level in mmol/L to OLED module
    display.display();
    delay(5000);
    state = 6;
      
        
  }
  else if(state ==6){
    creat=((495.6*volt_gluco)-1275.5)/1.364; //to get creatinine in mg/dl
      creat_mmol=creat/18; //to get creatinine in mmol/L
      state = 7;
    }
  else if(state == 7){
    delay(1000);
    Serial.println(volt_gluco);
    Serial.println(overal_data);
    Serial.println(creat_mmol);
    display.clearDisplay();
    //display.setTextSize(1);
    //display.setTextColor(WHITE);
    //display.setCursor(25,0);
    //display.print("Voltage:");
    //display.print(volt_urea);
    //display.println(" V"); //Voltage generated from the reaction
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(25,9);
    display.print("Creatinine level: "); //OLED display
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(30,17);
    display.print(creat);
    display.println(" mg/dL"); //Print glucose level in mg/dl to OLED module
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(30,25);
    display.print(creat_mmol);
    display.println(" mmol/L"); //Print glucose level in mmol/L to OLED module
    display.display();
    delay(5000);
    while (buttonval == 0) 
      {
        buttonval = digitalRead(push_button);
        if (buttonval == 1){
          display.clearDisplay();
          delay(1000);
          state =0;
          }
        
      }
      
        
    }


}

int chan_diff() //function for differential mode
{ //This function takes the inputs from the integrator
analogRead(glucoinput1);
delay(100);
int ch1 = analogRead (glucoinput1) ;
Serial.print("CH1");
Serial.println(ch1);
analogRead(glucoinput2);
delay (100) ;
int ch2 = analogRead (glucoinput2) ;
int x = random(565,600);
Serial.print("CH2");
Serial.println(ch2);
//ch1 += analogRead (glucoinput1) ;
//ch1 >>= 1 ;




return x ;
}
