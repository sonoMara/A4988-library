 library written by Enrico Maraldi and Andrea D'agostino, a.s. 20/21
 
 this library can control 2 A4988 drivers for stepper motor
 
 fully tested with pic16f1847, 2 A4988 drivers and 2 NEMA 17 1.5A step-motors
 	
 default pin configuration(you can change every pin at the start of .c file)
               		    |-------------------|
          			      |					          |
          SLEEP2	RA2	|1				        18|RA1    SLEEP1
             	    RA3	|2				        17|RA0    ENABLE
                 RA4	|3				        16|RA7
               	  MCLR|4                15|RA6
                	VSS	|5   pic16f18xx	  14|VDD
                 RB0	|6				        13|RB7    STEP2
            MS1		RB1	|7				        12|RB6    DIR2
            MS2		RB2	|8				        11|RB5    STEP1
            MS3		RB3	|9				        10|RB4    DIR1
                  	  |					          |
                      |-------------------|
 

