#ifndef A4988pic_h      //prevent from problems caused by including 2 times the library
#define A4988pic_h

#include "A4988pic.c"   //includes library's source file
#endif

void us_delay(unsigned long us);                            //delay using a variable (default delay did not consent that)
void step_setres(unsigned char ms);                         //setting step lenght using ms pins
void step_go(unsigned char speed, char dir);                //run the motor setting speed and direction
void step_go_num(unsigned long speed, char d, int numstep); //run the motor setting speed, direction and revolution numbers
void step_go_adcspeed(char d, int numstep);                 //run the motor setting the speed using an external analog input
void step_one_rev(unsigned long speed, char d);             //make the motor do a revolution, you can decide speed and direction
void step_half_rev(unsigned long speed, char d);            //make the motor do an half revolution, you can decide speed and direction
void step_quarter_rev(unsigned long speed, char d);         //make the motor do a quarter of revolution, you can decide speed and direction
void step_n_rev(unsigned long speed, char d, int numrev);   //make the motor do a noumber of completes revolution, you can decide speed, number and direction
void step_degree(unsigned long speed, int degree);          //make the motor run a set number of degrees, you can decide speed, direction and degrees