// A program for performing caesar ciphers in arduino and serial outing to an OLED screen (whilst simultaneously outputting the number of rotations to an LED and a 7 segment display)

//includes
    //general
#include <Streaming.h> 
#include <iomanip>
    //OLED
#include <Adafruit_GFX.h> 
#include <Adafruit_SSD1306.h>
    //7seg
#include <InvertedTM1638.h>
#include <TM1638.h>
#include <TM1638QYF.h>
#include <TM1640.h>
#include <TM16XX.h>
#include <TM16XXFonts.h>

//defines
    //OLED
#define OLED_RESET -1
#define OLED_SCREEN_I2C_ADDRESS 0x3C
Adafruit_SSD1306 display(OLED_RESET);
    //7seg
#define TM1638_STB D5
#define TM1638_CLK D6
#define TM1638_DIO D7

TM1638 module(TM1638_DIO, TM1638_CLK, TM1638_STB);

//global variables
int cae = 0; //shift
String sar = ""; //message
String orig; // set sar to original message before encoding happens so the transition can be shown on-board

void setup() {

    //OLED setup
    display.begin(SSD1306_SWITCHCAPVCC, OLED_SCREEN_I2C_ADDRESS);
    display.display(); 
    delay(2000);

    display.clearDisplay(); 
    display.setCursor(0,0);
    display.setTextSize(1);    // - a line is 21 chars in this size
    display.setTextColor(WHITE);

    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_BUILTIN, OUTPUT);

    // set up the 7-segement display
    module.clearDisplay();
    module.setupDisplay(true, 2);
    
    //allows for input to be taken for the Serial monitor
    Serial.begin(115200);
    Serial.println("How many positions would you like to shift by?");
}

//encode function
void Encode(int key, String input)
{
    for (int i = 0; input[i] != '\0'; i++) //as long as null terminator (defines the end of a string) not reached, continue loop
    {
      //set each character in input to be its own separate char value
        char in;
        in = input[i];
        
        //encrypt for lowercase letter
        if (in >= 'a' && in <= 'z') //bearing in mind chars are interpreted as number values in c++
        {
            in += key; //add the value of the key to the char
            if (in > 'z')
            {
                //loops back to the beginning of the alphabet 
                in = in - 'z' + 'a' - 1; //in this instance char in always = ('z'+1), so (z+1)-z+a-1 = a, resetting loop.
            }
            input[i] = in; //sets eain value of in after being encoded back to the input array
        }
        //encrypt for uppercase letter
        else if (in >= 'A' && in <= 'Z')
        {
            in += key;
            if (in > 'Z')
            {
                in = in - 'Z' + 'A' - 1;
            }
            input[i] = in;
        }
        else if (in >= '0' && in <= '9')
            in += key;
            if (in > '9')
            {
                in = in - '9' + '0' - 1;
            }
    }
    display << "Original: " << orig << " \n Encoded: " << input; 
    display.display();
}

//takes the key as an argument and blinks the on-board LED that number of times
void Blink(int numOfBlinks)
{
    for (int i = 0; i < numOfBlinks; i++)
    {
        digitalWrite(LED_BUILTIN, HIGH); //high voltage, light on
        delay(500); //delay's in ms, 1000 = 1 second
        digitalWrite(LED_BUILTIN, LOW);  //low voltage, lght off
        delay(500);
    }
}

void loop() {  
    display.clearDisplay();
    display.setCursor(0, 0);
    
    Serial.println("How many positions would you like to shift by?");
  
    while (!Serial.available()){}; //if serial is not available, do nothing

    //will always run at least once, as soon as cae becomes available (inutting value) loop is exited
    do{
        cae = Serial.readString().toInt();
    }while(!cae);

    //shows user value they've printed
    Serial.println(cae);
    Serial.println("What is your message?");
  
    while (!Serial.available()){};
    
    do{
        sar = Serial.readString();
    }while(!sar);
  
    Serial.println(sar);

    //sets sar to orig before sar gets changed, so they can be displyed side-by-side once the program is completed
    orig = sar;
  
    Encode(cae, sar);
    module.setDisplayToDecNumber(cae, 0, false); //args are, in order, number displayed, position of decimal, showLeadingZeroes
    Blink(cae);
}
