/*  Program responds to joystick movement and displays real-time, 
*   mapped coordinates on the LCD and reports them to serial comms port
*
*   Author: Dr Tim Amsdon Feb 2022
*/

#include "mbed.h"
#include "Joystick.h" 
#include "N5110.h"

//                  y     x
Joystick joystick(PC_3, PC_2);  //attach and create joystick object

//Pin assignment format:  lcd(IO, Ser_TX, Ser_RX, MOSI, SCLK, PWM)  
N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);


int main(){
    joystick.init();
    lcd.init(LPH7366_1);        //initialise for LPH7366-1 LCD (Options are LPH7366_1 and LPH7366_6)
    lcd.setContrast(0.55);      //set contrast to 55%
    lcd.setBrightness(0.5);     //set brightness to 50% (utilises the PWM)
    
    while (1) {
          // read the joystick to get the x- and y- values
        Vector2D coord = joystick.get_mapped_coord(); 
        printf("Coord = %f | %f\n",coord.x,coord.y);    
        
        lcd.clear();  // clear buffer at the start of the loop
        char buffer[14]={0};  // each character is 6 pixels wide, screen is 84 pixels (84/6 = 14)
        sprintf(buffer,"x = %.3f",coord.x); // print formatted data to buffer
        lcd.printString(buffer,0,2);     // display on screen
        sprintf(buffer,"y = %.3f",coord.y); // print formatted data to buffer
        lcd.printString(buffer,0,3);     // display on screen
        lcd.refresh();  // need to fresh the screen to get the message to appear
        
        ThisThread::sleep_for(30ms);
    }
}
