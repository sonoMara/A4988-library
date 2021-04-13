#ifndef A4988pic_c //prevent from problems created by including 2 times the library
#define A4988pic_c

#include "mcc_generated_files/mcc.h"

#define MS1 LATBbits.LATB1              //defining ms1 pin
#define MS2 LATBbits.LATB2              //defining ms2 pin
#define MS3 LATBbits.LATB3              //defining ms3 pin

#define DIR LATBbits.LATB6              //defining DIR pin
#define STEP LATBbits.LATB5             //defining STEP pin

#endif

int steprev=200;
static bool lastDIR;

void us_delay(unsigned long us){    //delay using a variable
    for(us=us;us>0;us--){           //for cycle for the selected lenght
        __delay_us(1);              //delay of 1 us repeated for the selected times
    }
}

void step_setres(unsigned char ms){ //setting step lenght using ms pins
    //   if not connected is set by default to 0 0 0
    switch(ms){                     //switch construct using ms viriable     
        case 1:                     //case ms=1
            MS1=0;                  //setting ms pins to full res
            MS2=0;
            MS3=0;
	    steprev=200;
            break;
        case 2:                     //case ms=2
            MS1=1;                  //setting ms pins to half res
            MS2=0;
            MS3=0;
	    steprev=400;
            break;
        case 4:                     //case ms=4
            MS1=0;                  //setting ms pins to a quarter of full res
            MS2=1;
            MS3=0;
	    steprev=800;
            break;
        case 8:                     //case ms=8
            MS1=1;                  //setting ms pins to a eighth of full res
            MS2=1;
            MS3=0;
	    steprev=1600;
            break;
        case 16:                    //case ms=16
            MS1=1;                  //setting ms pins to a sixteenth of full res
            MS2=1;
            MS3=1;
	    steprev=3200;
            break;
        default:                    //other cases
            MS1=0;                  //setting ms pins to full res
            MS2=0;
            MS3=0;
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
            DIR = 1;                                    //setting direction pin to left
            break;
        case 'd':                                       //right cases (ita & eng)
        case 'D':
        case 'r':
        case 'R': 
            DIR = 0;                                    //setting direction pin to right
            break;
    }
    if(lastDIR!=DIR){
        __delay_ms(1);
    }
    
    if(speed!=0){                                       //checking if speed isn't 0
        unsigned long delay;                
        delay=4294967296-((speed*4294967295)/100);      //putting speed value in proportion
        if (delay<125){
            delay=125;
        }
        STEP=1;                                     //setting step pin HIGH
        us_delay(delay);                                
        STEP=0;                                     //setting step pin LOW
        us_delay(delay);
        
    }
    lastDIR=DIR;
}

void step_go_num(unsigned long speed, char d, int numstep){ //run the motor setting speed, direction and revolution numbers
    
    int cyclenum = 0;
    
    switch(d){                                              //switch contruct
        case 's':                                           //left cases (ita & eng)
        case 'S':
        case 'l':
        case 'L': 
            DIR = 1;                                        //setting direction pin to left
            break;
        case 'd':                                           //right cases (ita & eng)
        case 'D':
        case 'r':
        case 'R': 
            DIR = 0;                                        //setting direction pin to right
            break;
    }
    if(lastDIR!=DIR){
        __delay_ms(1);
    }
    
    if(speed!=0){
        unsigned long delay;
        delay=4294967296-((speed*4294967295)/100);          //putting speed value in proportion
        for(numstep=numstep;numstep>0;numstep--){
            cyclenum++;
            if(delay<715&&cyclenum<=15){                 
                STEP=1;                                     //setting step pin HIGH
                us_delay(715);                                
                STEP=0;                                     //setting step pin LOW
                us_delay(715);
            }else if (delay<125){
                delay=125;
            }
            STEP=1;                                     //setting step pin HIGH
            us_delay(delay);                                
            STEP=0;                                     //setting step pin LOW
            us_delay(delay); 
        }
    }
}

void step_go_adcspeed(char d, int numstep){             //run the motor setting the speed using an external analog input
    int cyclenum = 0;
    
    switch(d){                                          //switch contruct
        case 's':                                       //left cases (ita & eng)
        case 'S':
        case 'l':
        case 'L': 
            DIR = 1;                                    //setting direction pin to left
            break;
        case 'd':                                       //right cases (ita & eng)
        case 'D':
        case 'r':
        case 'R': 
            DIR = 0;                                    //setting direction pin to right
            break;
    }
    
    if(ADCON0!=0){
        unsigned long delay;
        for(numstep=numstep;numstep>0;numstep--){
            delay=4294967296-((ADCON0*4294967295)/256); //putting speed value in proportion
            cyclenum++;
            if(delay<715&&cyclenum<=15){                 
                STEP=1;                                     //setting step pin HIGH
                us_delay(715);                                
                STEP=0;                                     //setting step pin LOW
                us_delay(715);
            }else if (delay<125){
                delay=125;
            }
            STEP=1;                                     //setting step pin HIGH
            us_delay(delay);                                
            STEP=0;                                     //setting step pin LOW
            us_delay(delay);
            }
        }
    
lastDIR=DIR;
}

void step_one_rev(unsigned long speed, char d){         //make the motor do a revolution, you can decide speed and direction
    
   int cyclenum = 0;
    
   switch(d){                                           //switch contruct
        case 's':                                       //left cases (ita & eng)
        case 'S':
        case 'l':
        case 'L': 
            DIR = 1;                                    //setting direction pin to left
            break;
        case 'd':                                       //right cases (ita & eng)
        case 'D':
        case 'r':
        case 'R': 
            DIR = 0;                                    //setting direction pin to right
            break;
    }
    if(lastDIR!=DIR){
        __delay_ms(1);
    }
    
    if(speed!=0){
        unsigned long delay;
        delay=4294967296-((speed*4294967295)/100);      //putting speed value in proportion
        for(int numstep=steprev;numstep>0;numstep--){
            cyclenum++;
            if(delay<715&&cyclenum<=15){                 
                STEP=1;                                     //setting step pin HIGH
                us_delay(715);                                
                STEP=0;                                     //setting step pin LOW
                us_delay(715);
            }else if (delay<125){
                delay=125;
            }
            STEP=1;                                     //setting step pin HIGH
            us_delay(delay);                                
            STEP=0;                                     //setting step pin LOW
            us_delay(delay);
            }
        }
   lastDIR=DIR;
    }

void step_half_rev(unsigned long speed, char d){        //make the motor do an half revolution, you can decide speed and direction
    
   int cyclenum = 0;
    
   switch(d){                                           //switch contruct
        case 's':                                       //left cases (ita & eng)
        case 'S':
        case 'l':
        case 'L': 
            DIR = 1;                                    //setting direction pin to left
            break;
        case 'd':                                       //right cases (ita & eng)
        case 'D':
        case 'r':
        case 'R': 
            DIR = 0;                                    //setting direction pin to right
            break;
    }
    if(lastDIR!=DIR){
        __delay_ms(1);
    }
    
    if(speed!=0){
        unsigned long delay;
        delay=4294967296-((speed*4294967295)/100);      //putting speed value in proportion
        for(int numstep=steprev/2;numstep>0;numstep--){
            cyclenum++;
            if(delay<715&&cyclenum<=15){                 
                STEP=1;                                     //setting step pin HIGH
                us_delay(715);                                
                STEP=0;                                     //setting step pin LOW
                us_delay(715);
            }else if (delay<125){
                delay=125;
            }
            STEP=1;                                     //setting step pin HIGH
            us_delay(delay);                                
            STEP=0;                                     //setting step pin LOW
            us_delay(delay);
            }
        }
   lastDIR=DIR;
    }

void step_quarter_rev(unsigned long speed, char d){     //make the motor do a quarter of revolution, you can decide speed and direction
    
    int cyclenum = 0;
    
    switch(d){                                          //switch contruct
        case 's':                                       //left cases (ita & eng)
        case 'S':
        case 'l':
        case 'L': 
            DIR = 1;                                    //setting direction pin to left
            break;
        case 'd':                                       //right cases (ita & eng)
        case 'D':
        case 'r':
        case 'R': 
            DIR = 0;                                    //setting direction pin to right
            break;
    }
    if(lastDIR!=DIR){
        __delay_ms(1);
    }
    
    if(speed!=0){
        unsigned long delay;
        delay=4294967296-((speed*4294967295)/100);      //putting speed value in proportion
        for(int numstep=steprev/4;numstep>0;numstep--){
            cyclenum++;
            if(delay<715&&cyclenum<=15){                 
                STEP=1;                                     //setting step pin HIGH
                us_delay(715);                                
                STEP=0;                                     //setting step pin LOW
                us_delay(715);
            }else if (delay<125){
                delay=125;
            }
            STEP=1;                                     //setting step pin HIGH
            us_delay(delay);                                
            STEP=0;                                     //setting step pin LOW
            us_delay(delay);
            }
        }
    lastDIR=DIR;
    }

void step_n_rev(unsigned long speed, char d, int numrev){   //make the motor do a noumber of completes revolution, you can decide speed, number and direction
    
    int cyclenum = 0;
    
    switch(d){                                              //switch contruct
        case 's':                                           //left cases (ita & eng)
        case 'S':
        case 'l':
        case 'L': 
            DIR = 1;                                        //setting direction pin to left
            break;
        case 'd':                                           //right cases (ita & eng)
        case 'D':
        case 'r':
        case 'R': 
            DIR = 0;                                        //setting direction pin to right
            break;
    }
    if(lastDIR!=DIR){
        __delay_ms(1);
    }
    
    if(speed!=0){
        unsigned long delay;
        delay=4294967296-((speed*4294967295)/100);          //putting speed value in proportion
        for(int numstep=numrev*steprev;numstep>0;numstep--){
            cyclenum++;
            if(delay<715&&cyclenum<=15){                 
                STEP=1;                                     //setting step pin HIGH
                us_delay(715);                                
                STEP=0;                                     //setting step pin LOW
                us_delay(715);
            }else if (delay<125){
                delay=125;
            }
            STEP=1;                                     //setting step pin HIGH
            us_delay(delay);                                
            STEP=0;                                     //setting step pin LOW
            us_delay(delay);
        }
    }
    lastDIR=DIR;
}

void step_degree(unsigned long speed, int degree){      //make the motor run a set number of degrees, you can decide speed, direction and degrees
    int cyclenum = 0;
    
    
    int oMS1=MS1;                                       //creating and putting old ms values in a memory
    int oMS2=MS2;
    int oMS3=MS3;
    
    MS1=1;                                              //setting ms to max resolution (1/16)
    MS2=1;
    MS3=1;
    if(0!=degree){
    if(degree>0){                                       //defining the rotation direction
	    DIR=0;
    }else{
	    DIR=1;
	    degree=-degree; 
	}
    if(lastDIR!=DIR){
        __delay_ms(1);
    }
    
    unsigned long delay;
    delay=4294967296-((speed*4294967295)/100);          //putting speed value in proportion

    int numstep=degree/0.1125;                          //putting in proportion degree value

    if(speed!=0){
        for(numstep=numstep;numstep>0;numstep--){
            cyclenum++;
            if(delay<715&&cyclenum<=15){                 
                STEP=1;                                     //setting step pin HIGH
                us_delay(715);                                
                STEP=0;                                     //setting step pin LOW
                us_delay(715);
            }else if (delay<125){
                delay=125;
            }
            STEP=1;                                     //setting step pin HIGH
            us_delay(delay);                                
            STEP=0;                                     //setting step pin LOW
            us_delay(delay);
            }
        }
    }
    

    MS1=oMS1;                                           //putting back the old ms values on the pins
    MS2=oMS2;
    MS3=oMS3;
    lastDIR=DIR;
}