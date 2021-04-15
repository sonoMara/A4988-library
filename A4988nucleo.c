#ifndef A4988nucleo_c 				//prevent from problems caused by including 2 times the library
#define A4988nuclco_c

#include "stm32f4xx_hal.h"

#define MS_PORT GPIOA				//defining in what port are located ms pins (MS1, MS2, MS3)
#define DATA_PORT GPIOA 			//defining in what port are located data pins (DIR and STEP)

#define MS1_PIN   GPIO_PIN_3     	//defining MS1 pin
#define MS2_PIN   GPIO_PIN_2      	//defining MS2 pin
#define MS3_PIN   GPIO_PIN_10    	//defining MS3 pin

#define DIR_PIN   GPIO_PIN_6      	//defining DIR pin
#define STEP_PIN  GPIO_PIN_7       	//defining STEP pin

#endif

#define MS1_HIGH 	HAL_GPIO_WritePin(MS_PORT, MS1_PIN, 1)
#define MS1_LOW 	HAL_GPIO_WritePin(MS_PORT, MS1_PIN, 0)
#define MS2_HIGH 	HAL_GPIO_WritePin(MS_PORT, MS2_PIN, 1)
#define MS2_LOW 	HAL_GPIO_WritePin(MS_PORT, MS2_PIN, 0)
#define MS3_HIGH 	HAL_GPIO_WritePin(MS_PORT, MS3_PIN, 1)
#define MS3_LOW 	HAL_GPIO_WritePin(MS_PORT, MS3_PIN, 0)

#define DIR_HIGH 	HAL_GPIO_WritePin(DATA_PORT, DIR_PIN, 1)
#define DIR_LOW 	HAL_GPIO_WritePin(DATA_PORT, DIR_PIN, 0)
#define STEP_HIGH 	HAL_GPIO_WritePin(DATA_PORT, STEP_PIN, 1)
#define STEP_LOW 	HAL_GPIO_WritePin(DATA_PORT, STEP_PIN, 0)

int steprev=200;
static int lastDIR;
int DIRchng;

/*
void us_delay(unsigned long us){    //delay using a variable
    for(us=us;us>0;us--){           //for cycle for the selected lenght
        __delay_us(1);              //delay of 1 us repeated for the selected times
    }
}
*/

void step_setres(int ms){ //setting step lenght using ms pins
    //   if not connected is set by default to 0 0 0
    switch(ms){                     //switch construct using ms viriable
        case 1:                     //case ms=1
        case 200:
        	MS1_LOW;                  //setting ms pins to full res
        	MS2_LOW;
        	MS3_LOW;
	    steprev=200;
            break;
        case 2:                     //case ms=2
        case 400:
        	MS1_HIGH;                  //setting ms pins to half res
        	MS2_LOW;
        	MS3_LOW;
	    steprev=400;
            break;
        case 4:                     //case ms=4
        case 800:
        	MS1_LOW;                  //setting ms pins to a quarter of full res
        	MS2_HIGH;
        	MS3_LOW;
	    steprev=800;
            break;
        case 8:                     //case ms=8
        case 1600:
        	MS1_HIGH;                  //setting ms pins to a eighth of full res
        	MS2_HIGH;
        	MS3_LOW;
	    steprev=1600;
            break;
        case 16:                    //case ms=16
        case 3200:
        	MS1_HIGH;                  //setting ms pins to a sixteenth of full res
        	MS2_HIGH;
        	MS3_HIGH;
	    steprev=3200;
            break;
        default:                    //other cases
        	MS1_LOW;                  //setting ms pins to full res
        	MS2_LOW;
        	MS3_LOW;
	    steprev=200;
            break;
    }

}

void step_go(unsigned long speed, char d){              //run the motor setting speed and direction
    switch(d){                                          //switch contruct
        case 's':                                       //left cases (ita & eng)
        case 'S':
        case 'l':
        case 'L':
        	DIR_HIGH; 									//setting direction pin to left
        	if(lastDIR!=1){
        		DIRchng = 1;
        	}
        lastDIR	= 1;
            break;
        case 'd':                                       //right cases (ita & eng)
        case 'D':
        case 'r':
        case 'R':
            DIR_LOW;                                    //setting direction pin to right
            if(lastDIR!=0){
                 DIRchng = 1;
             }
            lastDIR	= 0;
            break;
    }
    if(DIRchng){
        HAL_Delay(1);
    }
    DIRchng=0;
    if(speed!=0){                                       //checking if speed isn't 0
        unsigned long delay;
        delay=4294967296-((speed*4294967295)/100);      //putting speed value in proportion
        if (delay<125){
            delay=125;
        }
        STEP_HIGH;                                     //setting step pin HIGH
        us_delay(delay);
        STEP_LOW;                                     //setting step pin LOW
        us_delay(delay);

    }

}

void step_go_num(unsigned long speed, char d, int numstep){ //run the motor setting speed, direction and revolution numbers

    int cyclenum = 0;

    switch(d){                                          //switch contruct
            case 's':                                       //left cases (ita & eng)
            case 'S':
            case 'l':
            case 'L':
            	DIR_HIGH; 									//setting direction pin to left
            	if(lastDIR!=1){
            		DIRchng = 1;
            	}
            lastDIR	= 1;
                break;
            case 'd':                                       //right cases (ita & eng)
            case 'D':
            case 'r':
            case 'R':
                DIR_LOW;                                    //setting direction pin to right
                if(lastDIR!=0){
                     DIRchng = 1;
                 }
                lastDIR	= 0;
                break;    }
    if(DIRchng){
        HAL_Delay(1);
    }

    if(speed!=0){
        unsigned long delay;
        delay=4294967296-((speed*4294967295)/100);          //putting speed value in proportion
        for(numstep=numstep;numstep>0;numstep--){
            cyclenum++;
            if(delay<715&&cyclenum<=15){
                STEP_HIGH;                                     //setting step pin HIGH
                us_delay(715);
                STEP_LOW;                                     //setting step pin LOW
                us_delay(715);
            }else if (delay<125){
                delay=125;
            }
            STEP_HIGH;                                     //setting step pin HIGH
            us_delay(delay);
            STEP_LOW;                                     //setting step pin LOW
            us_delay(delay);
        }
    }
}



void step_one_rev(unsigned long speed, char d){         //make the motor do a revolution, you can decide speed and direction

   int cyclenum = 0;

   switch(d){                                          //switch contruct
           case 's':                                       //left cases (ita & eng)
           case 'S':
           case 'l':
           case 'L':
           	DIR_HIGH; 									//setting direction pin to left
           	if(lastDIR!=1){
           		DIRchng = 1;
           	}
           lastDIR	= 1;
               break;
           case 'd':                                       //right cases (ita & eng)
           case 'D':
           case 'r':
           case 'R':
               DIR_LOW;                                    //setting direction pin to right
               if(lastDIR!=0){
                    DIRchng = 1;
                }
               lastDIR	= 0;
               break;    }
    if(DIRchng){
        HAL_Delay(1);
    }

    if(speed!=0){
        unsigned long delay;
        delay=4294967296-((speed*4294967295)/100);      //putting speed value in proportion
        for(int numstep=steprev;numstep>0;numstep--){
            cyclenum++;
            if(delay<715&&cyclenum<=15){
                STEP_HIGH;                                     //setting step pin HIGH
                us_delay(715);
                STEP_LOW;                                     //setting step pin LOW
                us_delay(715);
            }else if (delay<125){
                delay=125;
            }
            STEP_HIGH;                                     //setting step pin HIGH
            us_delay(delay);
            STEP_LOW;                                     //setting step pin LOW
            us_delay(delay);
            }
        }

    }

void step_half_rev(unsigned long speed, char d){        //make the motor do an half revolution, you can decide speed and direction

   int cyclenum = 0;

   switch(d){                                          //switch contruct
           case 's':                                       //left cases (ita & eng)
           case 'S':
           case 'l':
           case 'L':
           	DIR_HIGH; 									//setting direction pin to left
           	if(lastDIR!=1){
           		DIRchng = 1;
           	}
           lastDIR	= 1;
               break;
           case 'd':                                       //right cases (ita & eng)
           case 'D':
           case 'r':
           case 'R':
               DIR_LOW;                                    //setting direction pin to right
               if(lastDIR!=0){
                    DIRchng = 1;
                }
               lastDIR	= 0;
               break;    }
    if(DIRchng){
        HAL_Delay(1);
    }

    if(speed!=0){
        unsigned long delay;
        delay=4294967296-((speed*4294967295)/100);      //putting speed value in proportion
        for(int numstep=steprev/2;numstep>0;numstep--){
            cyclenum++;
            if(delay<715&&cyclenum<=15){
                STEP_HIGH;                                     //setting step pin HIGH
                us_delay(715);
                STEP_LOW;                                     //setting step pin LOW
                us_delay(715);
            }else if (delay<125){
                delay=125;
            }
            STEP_HIGH;                                     //setting step pin HIGH
            us_delay(delay);
            STEP_LOW;                                     //setting step pin LOW
            us_delay(delay);
            }
        }

    }

void step_quarter_rev(unsigned long speed, char d){     //make the motor do a quarter of revolution, you can decide speed and direction

    int cyclenum = 0;

    switch(d){                                          //switch contruct
            case 's':                                       //left cases (ita & eng)
            case 'S':
            case 'l':
            case 'L':
            	DIR_HIGH; 									//setting direction pin to left
            	if(lastDIR!=1){
            		DIRchng = 1;
            	}
            lastDIR	= 1;
                break;
            case 'd':                                       //right cases (ita & eng)
            case 'D':
            case 'r':
            case 'R':
                DIR_LOW;                                    //setting direction pin to right
                if(lastDIR!=0){
                     DIRchng = 1;
                 }
                lastDIR	= 0;
                break;    }
    if(DIRchng){
        HAL_Delay(1);
    }

    if(speed!=0){
        unsigned long delay;
        delay=4294967296-((speed*4294967295)/100);      //putting speed value in proportion
        for(int numstep=steprev/4;numstep>0;numstep--){
            cyclenum++;
            if(delay<715&&cyclenum<=15){
                STEP_HIGH;                                     //setting step pin HIGH
                us_delay(715);
                STEP_LOW;                                     //setting step pin LOW
                us_delay(715);
            }else if (delay<125){
                delay=125;
            }
            STEP_HIGH;                                     //setting step pin HIGH
            us_delay(delay);
            STEP_LOW;                                     //setting step pin LOW
            us_delay(delay);
            }
        }

    }

void step_n_rev(unsigned long speed, char d, int numrev){   //make the motor do a noumber of completes revolution, you can decide speed, number and direction

    int cyclenum = 0;

    switch(d){                                          //switch contruct
            case 's':                                       //left cases (ita & eng)
            case 'S':
            case 'l':
            case 'L':
            	DIR_HIGH; 									//setting direction pin to left
            	if(lastDIR!=1){
            		DIRchng = 1;
            	}
            lastDIR	= 1;
                break;
            case 'd':                                       //right cases (ita & eng)
            case 'D':
            case 'r':
            case 'R':
                DIR_LOW;                                    //setting direction pin to right
                if(lastDIR!=0){
                     DIRchng = 1;
                 }
                lastDIR	= 0;
                break;    }
    if(DIRchng){
        HAL_Delay(1);
    }

    if(speed!=0){
        unsigned long delay;
        delay=4294967296-((speed*4294967295)/100);          //putting speed value in proportion
        for(int numstep=numrev*steprev;numstep>0;numstep--){
            cyclenum++;
            if(delay<715&&cyclenum<=15){
                STEP_HIGH;                                     //setting step pin HIGH
                us_delay(715);
                STEP_LOW;                                     //setting step pin LOW
                us_delay(715);
            }else if (delay<125){
                delay=125;
            }
            STEP_HIGH;                                     //setting step pin HIGH
            us_delay(delay);
            STEP_LOW;                                     //setting step pin LOW
            us_delay(delay);
        }
    }

}

void step_degree(unsigned long speed, int degree){      //make the motor run a set number of degrees, you can decide speed, direction and degrees
    int cyclenum = 0;



    MS1_HIGH;                                              //setting ms to max resolution (1/16)
    MS2_HIGH;
    MS3_HIGH;
    if(0!=degree){
    if(degree>0){                                       //defining the rotation direction
	    DIR_LOW;
    }else{
	    DIR_HIGH;
	    degree=-degree;
	}
    if(DIRchng){
        HAL_Delay(1);
    }

    unsigned long delay;
    delay=4294967296-((speed*4294967295)/100);          //putting speed value in proportion

    int numstep=degree/0.1125;                          //putting in proportion degree value

    if(speed!=0){
        for(numstep=numstep;numstep>0;numstep--){
            cyclenum++;
            if(delay<715&&cyclenum<=15){
                STEP_HIGH;                                     //setting step pin HIGH
                us_delay(715);
                STEP_LOW;                                     //setting step pin LOW
                us_delay(715);
            }else if (delay<125){
                delay=125;
            }
            STEP_HIGH;                                     //setting step pin HIGH
            us_delay(delay);
            STEP_LOW;                                     //setting step pin LOW
            us_delay(delay);
            }
        }
    }


    step_setres(steprev);                                           //putting back the old ms values on the pins


}
