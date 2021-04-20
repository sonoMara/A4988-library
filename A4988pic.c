#ifndef A4988pic_c      //prevent from problems caused by including 2 times the same library
#define A4988pic_c

#include "mcc_generated_files/mcc.h"

//same pins for motor 1 and 2
#define MS1 LATBbits.LATB1              //defining ms1 pin of both motors
#define MS2 LATBbits.LATB2              //defining ms2 pin of both motors
#define MS3 LATBbits.LATB3              //defining ms3 pin of both motors
#define ENABLE LATAbits.LATA0           //defining enable of both motors

//motor 1
#define DIR1 LATBbits.LATB4             //defining DIR pin of first motor
#define STEP1 LATBbits.LATB5            //defining STEP pin of first motor
#define SLEEP1 LATAbits.LATA1           //defining SLEEP pin of first mortor

//motor 2
#define DIR2 LATBbits.LATB6             //defining DIR pin of second motor
#define STEP2 LATBbits.LATB7            //defining STEP pin of second motor
#define SLEEP2 LATAbits.LATA2           //defining SLEEP pin of second motor



int steprev=200;
static bool lastDIR1;
static bool lastDIR2;

void us_delay(unsigned long us){    //delay using a variable (default delay did not allow that)
    for(us=us;us>0;us--){           //for cycle for the selected lenght
        __delay_us(1);              //delay of 1 us repeated for the selected times
    }
}

void step_initialize(void){     //enable the drivers and setting default values for the correct working of the program
    ENABLE = 0;
    SLEEP1 = 1;
    SLEEP2 = 1;
    DIR1 = 0;
    DIR2 = 0;
}

void step_sleep(char motornum){     //puts the selected motor on sleep, 0=both motors, 1=motor1, 2=motor2
    if(motornum==1)
        SLEEP1 = 1;
    if(motornum==2)
        SLEEP2 = 1;
    if(motornum==3)
        SLEEP1 = 1;
        SLEEP2 = 1;
}

void step_stop(void){       //disable the drivers
    ENABLE = 1;
}

void step(char motornum, unsigned long speed, int cyclenum){      //doing a single step by a preset direction (used inside all other functions)
    if(motornum==1){
        SLEEP1=0;
        if(speed!=0){                                       //checking if speed isn't 0
            unsigned long delay;                
            delay=4294967296-((speed*4294967295)/100);    //putting speed value in proportion
            if(delay<715&&cyclenum<=15){
                delay=715;
            }
            else if (delay<125){
                delay=125;
            }
            STEP1=1;                                     //setting step pin HIGH
            us_delay(delay);                                
            STEP1=0;                                     //setting step pin LOW
            us_delay(delay);
        
        }
        SLEEP1=1;
    }
    if(motornum==2){
        SLEEP2=0;
        if(speed!=0){                                       //checking if speed isn't 0
            unsigned long delay;                
            delay=4294967296-((speed*4294967295)/100);      //putting speed value in proportion
            if (delay<125){
                delay=125;
            }
            STEP2=1;                                     //setting step pin HIGH
            us_delay(delay);                                
            STEP2=0;                                     //setting step pin LOW
            us_delay(delay);
        
        }
        SLEEP2=1;
    }
}

void step_dir(char motornum, char d){       //setting step dir (used inside all other functions)
    if(motornum==1){
        switch(d){                                          //switch contruct
        case 's':                                       //left cases (ita & eng)
        case 'S':
        case 'l':
        case 'L': 
            DIR1 = 1;                                    //setting direction pin to left
            break;
        case 'd':                                       //right cases (ita & eng)
        case 'D':
        case 'r':
        case 'R': 
            DIR1 = 0;                                    //setting direction pin to right
            break;
    }
    if(lastDIR1!=DIR1){
        __delay_ms(1);
    }
    lastDIR1=DIR1;
    }
    if(motornum==2){
        switch(d){                                          //switch contruct
        case 's':                                       //left cases (ita & eng)
        case 'S':
        case 'l':
        case 'L': 
            DIR2 = 1;                                    //setting direction pin to left
            break;
        case 'd':                                       //right cases (ita & eng)
        case 'D':
        case 'r':
        case 'R': 
            DIR2 = 0;                                    //setting direction pin to right
            break;
    }
    if(lastDIR2!=DIR2){
        __delay_ms(1);
    }
    lastDIR2=DIR2;
    }
}

void step_setres(int ms){     //setting step lenght using ms pins
    //   if not connected is set by default to 0 0 0
    switch(ms){                     //switch construct using ms viriable     
        case 1:                     //case ms=1 or ms=200
        case 200:    
            MS1=0;                  //setting ms pins to full res
            MS2=0;
            MS3=0;
	    steprev=200;
            break;
        case 2:                     //case ms=2 or ms=400
        case 400:    
            MS1=1;                  //setting ms pins to half res
            MS2=0;
            MS3=0;
	    steprev=400;
            break;
        case 4:                     //case ms=4 or ms=800
        case 800:    
            MS1=0;                  //setting ms pins to a quarter of full res
            MS2=1;
            MS3=0;
	    steprev=800;
            break;
        case 8:                     //case ms=8 or ms=1600
        case 1600:                  
            MS1=1;                  //setting ms pins to a eighth of full res
            MS2=1;
            MS3=0;
	    steprev=1600;
            break;
        case 16:                    //case ms=16 or ms=3200
        case 3200:    
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

void step_go(char motornum, unsigned long speed, char d){            //run the motor setting speed and direction
    int cyclenum=16;
    step_dir(motornum, d);
    step(motornum, speed, cyclenum);
}

void step_go_num(char motornum, unsigned long speed, char d, int numstep){ //run the motor setting speed, direction and revolution numbers
    step_dir(motornum, d);
    int cyclenum = 0;
    for(numstep=numstep;numstep>0;numstep--){
            cyclenum++;
            step(motornum, speed, cyclenum);
    }  
}

void step_go_adcspeed(char motornum, char d, int numstep){             //run the motor setting the speed using an external analog input
    
    step_dir(motornum, d);
    int cyclenum = 0;
    if(ADCON0!=0){
        unsigned long delay;
        for(numstep=numstep;numstep>0;numstep--){
            cyclenum++;
            step(motornum, ADCON0 , cyclenum);
        }
    }
}

void step_one_rev(char motornum, unsigned long speed, char d){         //make the motor do a revolution, you can decide speed and direction
    step_dir(motornum, d);
    int cyclenum = 0;
    int numstep;
    for(numstep=steprev;numstep>0;numstep--){
            cyclenum++;
            step(motornum, speed, cyclenum);
    } 
}

void step_half_rev(char motornum, unsigned long speed, char d){        //make the motor do an half revolution, you can decide speed and direction
    step_dir(motornum, d);
    int cyclenum = 0;
    int numstep;
    for(numstep=steprev/2;numstep>0;numstep--){
            cyclenum++;
            step(motornum, speed, cyclenum);
    }
}

void step_quarter_rev(char motornum, unsigned long speed, char d){     //make the motor do a quarter of revolution, you can decide speed and direction
    step_dir(motornum, d);
    int cyclenum = 0;
    int numstep;
    for(numstep=steprev/4;numstep>0;numstep--){
            cyclenum++;
            step(motornum, speed, cyclenum);
    }
}

void step_n_rev(char motornum, unsigned long speed, char d, int numrev){   //make the motor do a noumber of completes revolution, you can decide speed, number and direction
    step_dir(motornum, d);
    int cyclenum = 0;
    int numstep;
    for(numstep=numrev*steprev;numstep>0;numstep--){
            cyclenum++;
            step(motornum, speed, cyclenum);
    }
}

void step_degree(char motornum, unsigned long speed, int degree){      //make the motor run a set number of degrees, you can decide speed, direction and degrees
    int cyclenum = 0;
        
    int oMS1=MS1;                                       //creating and putting old ms values in a memory
    int oMS2=MS2;
    int oMS3=MS3;
    
    MS1=1;                                              //setting ms to max resolution (1/16)
    MS2=1;
    MS3=1;
    if(motornum==1){
        if(0!=degree){
            if(degree>0){                                       //defining the rotation direction
                DIR1=0;
            }else{
                DIR1=1;
                degree=-degree; 
            }
            if(lastDIR1!=DIR1){
                __delay_ms(1);
            }
            lastDIR1=DIR1;
            
            int numstep=degree/0.1125;
        
            for(numstep=numstep;numstep>0;numstep--){
                cyclenum++;
                step(motornum, speed, cyclenum);
            }   
        }   
    }
    if(motornum==2){
        if(0!=degree){
            if(degree>0){                                       //defining the rotation direction
                DIR2=0;
            }else{
                DIR2=1;
                degree=-degree; 
            }
            if(lastDIR2!=DIR2){
                __delay_ms(1);
            }
            lastDIR2=DIR2;
            
            int numstep=degree/0.1125;
        
            for(numstep=numstep;numstep>0;numstep--){
                cyclenum++;
                step(motornum, speed, cyclenum);
            }   
        }   
    }
    
    MS1=oMS1;                                           //putting back the old ms values on the pins
    MS2=oMS2;
    MS3=oMS3;   
}

#endif