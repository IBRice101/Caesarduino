# Caesarduino
A program for performing caesar ciphers in arduino and serial outing to an OLED screen (whilst simultaneously outputting the number of rotations to an LED and a 7 segment display)

Built for CMP101 at Abertay University

hardware components:
    LOLIN(WEMOS)D1 board (ESP-8266)
    Male-To-Male Arduino Jumper wires (x9)
    Breadboard
    OLED Screen (SSD1306)
    7 Segment Display (TMI1638)
architecture:
    OLED:
    Plugged into Breadboard pins 14-17F
    Wiring (OLED -> BOARD):
      GND-GND
      VCC-5V
      SCL-SCL
      SDA-SDA
    7Seg:
    Plugged directly in to the board
    Wiring (7seg -> board):
      VCC-3V3
      GND-GND
      STD-D5
      CLK-D6
      DIO-D7
