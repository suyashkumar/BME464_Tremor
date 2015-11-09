////////////////////////////////////////////////////////////////////////////
//
//  This file is part of RTIMULib
//
//  Copyright (c) 2014-2015, richards-tech, LLC
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy of
//  this software and associated documentation files (the "Software"), to deal in
//  the Software without restriction, including without limitation the rights to use,
//  copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the
//  Software, and to permit persons to whom the Software is furnished to do so,
//  subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
//  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
//  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
//  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
//  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
//  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


#include "RTIMULib/RTIMULib.h"
#include "stdio.h"
#include "mraa.h"
#include "mraa.hpp"
#include <unistd.h>
#include <iostream>
#include <exception>
#include <fstream>

// Forward function declarations:
mraa::Pwm* initPwm(int pin);
float calculateDutyCycle(float deflection);
void motorControl(RTIMU_DATA imuData, mraa::Pwm* pwm);


int main()
{
	// Parameter declaration, initiation:
    int sampleCount = 0;
    int sampleRate = 0;

    mraa::Pwm* pwm = initPwm(0); // Initialize PWM Object

    RTIMUSettings *settings = new RTIMUSettings("RTIMULib");
    RTIMU *imu = RTIMU::createIMU(settings);
    if ((imu == NULL) || (imu->IMUType() == RTIMU_TYPE_NULL)) {
        printf("No IMU found\n");
        exit(1);
    }

    // IMU Init:
    imu->IMUInit();
    imu->setSlerpPower(0.02);
    imu->setGyroEnable(true);

    // Main loop:
    while (1) {
        while (imu->IMURead()) {
            RTIMU_DATA imuData = imu->getIMUData();
            motorControl(imuData,pwm); // Update motor position
        }
    }
    //mraa_uart_stop(uart);
  	mraa_deinit();
}
/*
 * initPwm()
 * Initiates a PWM object on the supplied pin.
 * @param pin an integer representing the pin to initiate PWM on.
 * @returns pwm a mraa::Pwm* pointer
 */
mraa::Pwm* initPwm(int pin){
	mraa::Pwm* pwm;
	pwm=new mraa::Pwm(pin);
	if (pwm == NULL) { // Look for null case
			//return MRAA_ERROR_UNSPECIFIED;
			std::cerr << "PWM object was returned as null...exiting" << std::endl;
			exit(1);
	}
	if (pwm->enable(true) != MRAA_SUCCESS) { // enable and check status of enable
		std::cerr << "Cannot enable PWM on mraa::PWM object, exiting" << std::endl;
		//return MRAA_ERROR_UNSPECIFIED;
		exit(1);
	}
	return pwm;

}
/*
 * calculateDutyCycle()
 * Calculates the duty cycle needed to move our servo to the provided deflection.
 * @param deflection the input angular deflection
 * @returns duty_cycle the duty cycle to send to the motor
 */
float calculateDutyCycle(float deflection){

	return ((0.317*deflection)+52.464)/100;

}

/*
 * motorControl()
 * Inspects last read set of data from IMU and calculates a restoring displacement that is
 * then translated to a duty cycle that is then sent to the motor. Any smoothing tasks occur
 * in this function.
 * @param imuData the RTIMU_DATA object that holds the last read set of data.
 * @param pwm the PWM control object that writes the motor control signal.
 */
void motorControl(RTIMU_DATA imuData, mraa::Pwm* pwm){
	std::ofstream logfile ("lastRun2.csv",std::ios::app);
	printf("%s\r", RTMath::displayDegrees("Gyro", imuData.fusionPose));
	float current_reading=imuData.fusionPose.y()*(180.0/3.14);
	char buffer[20]={};
	sprintf(buffer,"%f,",current_reading);

	logfile << buffer;
	            //mraa_uart_write(uart, buffer, sizeof(buffer)); // Write to UART
	            //duty_cycle=((current_reading/90)*0.05)+0.05;
	float duty_cycle=calculateDutyCycle(current_reading);
	//printf("\nDuty cycle: %f\n",duty_cycle);
	pwm->config_percent(3,duty_cycle); // Write duty_cycle with period of 1ms
	printf("\n\n");
	logfile.close();
	fflush(stdout);
}





