#pragma config(I2C_Usage, I2C1, i2cSensors)
#pragma config(Sensor, dgtl1,  button1,        sensorTouch)
#pragma config(Sensor, dgtl2,  button2,        sensorTouch)
#pragma config(Sensor, I2C_1,  ,               sensorQuadEncoderOnI2CPort,    , AutoAssign )
#pragma config(Motor,  port1,           motor1,        tmotorVex393_HBridge, openLoop, encoderPort, I2C_1)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// WHEN YOU FINISH EACH EXERCISE, INCREMENT THIS VALUE
#define EXERCISE_NUMBER     1

bool button1_pushed; //flag to store button1 input
bool button2_pushed; //flag to store button2 input


/* monitorInput()
 *
 *  Used to flag button inputs
 *       - this avoids errors caused by program recognizing input, taking action, and
 *         reading input again before button is released
 */
void monitorInput()
{
    if(SensorValue(button1) && !button1_pushed)
    {
        button1_pushed = true;
    }
    
    if(SensorValue(button2) && !button2_pushed)
    {
        button2_pushed = true;
    }
}

void exercise_1()
{
    // Define tag for enumerated type for exercise 1
    enum T_exercise1_state {
        MOTOR_STOP = 0,
        MOTOR_RUNNING
    };
    
    // Declare variable to hold state, intialize to MOTOR_STOP state.
    T_exercise1_state exercise1_state = MOTOR_STOP;
    
    while(true)
    {
        // This function updates the button1_pushed and button2_pushed flags.
        monitorInput();
        
        // Switch the states.
        switch(exercise1_state) {
                
                // Code for MOTOR_STOP state:
            case MOTOR_STOP:
                // Turn motor off.
                motor[motor1] = 0;
                if ( button1_pushed ) {
                    // If button1 pushed, change to the MOTOR_RUNNING state.
                    exercise1_state = MOTOR_RUNNING;
                    // Clear flag to indicate button 1 processed.
                    button1_pushed = false;
                }
                break;
            case MOTOR_RUNNING:
                // Turn motor on.
                motor[motor1] = 50;
                if (button2_pushed) {
                    // If button 2 pushed, transition to MOTOR_STOP state.
                    exercise1_state = MOTOR_STOP;
                    // Clear flag to indicate that button 2 processed.
                    button2_pushed = false;
                }
                break;
            default:
        }
        
    }//end while
}

void exercise_2()
{
    
    while(true)
    {
        monitorInput();
    if(button1_pushed){
        while(getMotorEncoder(motor1) <= 627){
            motor[motor1] = 50;
        }
        button1_pushed = false;
        resetMotorEncoder(motor1);
        motor[motor1] = 0;
        }
    }// end while

} // end exercise_2

void exercise_3()
{	
	enum T_motor_state {
		OFF = 0,
		FORWARD,
		BACKWARD
	};

	// Create motor state
	T_motor_state motor_state = OFF;

    while(true)
    {
        monitorInput();
        
		//Figure out what state to switch into then execute the right case statement
		//If motor is off OR running backwards allow for state to change to FORWARD
		if((button1_pushed && motor_state == OFF) || (button1_pushed && motor_state == BACKWARD)) {
			// Set motor to run forward
			motor_state = FORWARD;

			// If the motor is off OR running forwards allow for it to switch to backwards
		} else if ((button2_pushed && motor_state == OFF) || (button1_pushed && motor_state == FORWARD)) {
			// Set motor to run backward
			motor_state = BACKWARD;

		} else {
			//If neither button is pressed keep state as OFF
			motor_state = OFF;
		}//if


		switch (motor_state)
		{
			case OFF:
				// motor is not running 
				// Maintain motor at 0 speed
				motor[motor1] = 0;
				break;

			case FORWARD:
				// Motor is travelling forward direction
				while(getMotorEncoder(motor1) <= 3000){
					motor[motor1] = 50;

					// monitorInput to see if other button is pressed
					monitorInput();
				}// while
				
				// Reset encoder 
				resetMotorEncoder(motor1);

				//turn off button variable to prevent accidental switch into FORWARD again
				button2_pushed = false;

				// Set motor_state to OFF so it wil not accidentally keep running forward 
				motor_state = OFF;
				break;

			case BACKWARD:
				// Motor travel backwards
				while(getMotorEncoder(motor1) >= -3000){
					motor[motor1] = -50;

						// monitorInput to see if other button is pressed
						monitorInput();
					}
				
				// Reset encoder 
				resetMotorEncoder(motor1);

				//turn off button variable to prevent accidental switch into BACKWARD again
				button1_pushed = false;

				// Set motor_state to OFF so it wil not accidentally keep running backwards
				motor_state = OFF;
				break;

			default:
				//Shouldn't happen
        }
    }//end while
    
}//end exercse_3


task main()
{
    button1_pushed = button2_pushed = false;
    
    switch (EXERCISE_NUMBER)
    {
        case 1:
            exercise_1();
            break;
        case 2:
            exercise_2();
            break;
        case 3:
            exercise_3();
            break;
        default: //should never get here.
    } // end switch
    
}// end main