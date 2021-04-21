/*
 * library written by Enrico Maraldi and Andrea D'agostino, s.y. 20/21
 * 
 * this library can control 2 A4988 drivers for stepper motor
 * 	
 * default pin configuration(you can change every pin at the start of .c file)
 * 
 *                      |-------------------|
 *           		|		    |
 *      SLEEP2	RA2	|1                18|RA1    SLEEP1
 *              RA3	|2                17|RA0    ENABLE
 *              RA4	|3                16|RA7
 *              MCLR    |4                15|RA6
 *              VSS	|5   pic16f18xx	  14|VDD
 *              RB0	|6		  13|RB7    STEP2
 *    MS1	RB1	|7		  12|RB6    DIR2
 *    MS2	RB2	|8		  11|RB5    STEP1
 *    MS3	RB3	|9		  10|RB4    DIR1
 *                  |					          |
 *                  |-------------------|
 * 
 * Libreria scritta da Enrico Maraldi and Andrea D'agostino, a.s. 20/21
 * 
 * questa libreria può controllare 2 driver A4988 per motori passo passo
 * 	
 * configurazione pin di default (sono completamente personalizzabili all'inizio del file .c)
 * 
 *               		|-------------------|
 *           		    |					          |
 *      SLEEP2	RA2	|1				        18|RA1    SLEEP1
 *              RA3	|2				        17|RA0    ENABLE
 *              RA4	|3				        16|RA7
 *              MCLR|4                15|RA6
 *              VSS	|5   pic16f18xx	  14|VDD
 *              RB0	|6				        13|RB7    STEP2
 *        MS1		RB1	|7				        12|RB6    DIR2
 *        MS2		RB2	|8				        11|RB5    STEP1
 *        MS3		RB3	|9				        10|RB4    DIR1
 *                  |					          |
 *                  |-------------------|
 * 
 * 
 */
#ifndef A4988_H      //prevent from problems caused by including 2 times the same library
#define A4988_H

//functions prototypes

void us_delay(unsigned long us);                                             //delay using a variable (default delay did not allow that)
void step_initialize(void);                                                  //enable the drivers and setting default values for the correct working of the program
void step_sleep(char motornum);                                              //puts the selected motor on sleep, 0=both motors, 1=motor1, 2=motor2
void step_stop(void);                                                        //disable the drivers
void step(char motornum, unsigned long speed, int cyclenum);                 //doing a single step by a preset direction (used inside all other functions)
void step_dir(char motornum, char d);                                        //setting step dir (used inside all other functions)
void step_setres(int ms);                                                    //setting step lenght using ms pins
void step_go(char motornum, unsigned long speed, char d);                    //run the motor setting speed and direction
void step_go_num(char motornum, unsigned long speed, char d, int numstep);   //run the motor setting speed, direction and revolution numbers
void step_go_adcspeed(char motornum, char d, int numstep);                   //run the motor setting the speed using an external analog input
void step_one_rev(char motornum, unsigned long speed, char d);               //make the motor do a revolution, you can decide speed and direction
void step_half_rev(char motornum, unsigned long speed, char d);              //make the motor do an half revolution, you can decide speed and direction
void step_quarter_rev(char motornum, unsigned long speed, char d);           //make the motor do a quarter of revolution, you can decide speed and direction
void step_n_rev(char motornum, unsigned long speed, char d, int numrev);     //make the motor do a noumber of completes revolution, you can decide speed, number and direction
void step_degree(char motornum, unsigned long speed, int degree);            //make the motor run a set number of degrees, you can decide speed, direction and degrees

#endif
