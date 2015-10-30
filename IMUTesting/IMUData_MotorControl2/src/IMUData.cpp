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

mraa::Pwm* initPwm();

int main()
{
	// Parameter declaration
    int sampleCount = 0;
    int sampleRate = 0;
    uint64_t rateTimer;
    uint64_t displayTimer;
    uint64_t now;

    mraa::Pwm* pwm = initPwm(); // Initialize PWM Object
	float duty_cycle=0.0;

    RTIMUSettings *settings = new RTIMUSettings("RTIMULib");

    RTIMU *imu = RTIMU::createIMU(settings);

    if ((imu == NULL) || (imu->IMUType() == RTIMU_TYPE_NULL)) {
        printf("No IMU found\n");
        exit(1);
    }

    //  This is an opportunity to manually override any settings before the call IMUInit

    imu->IMUInit();
    imu->setSlerpPower(0.02);
    imu->setGyroEnable(true);
    //imu->setAccelEnable(true);
    //imu->setCompassEnable(true);


    // Set up serial out UART ports
    mraa_uart_context uart;
    //uart = mraa_uart_init(0);
    uart=mraa_uart_init_raw("/dev/ttyGS0");
	mraa_uart_set_baudrate(uart, 9600);
	if (uart == NULL) {
		fprintf(stderr, "UART failed to setup\n");
		return 0;
	}
	// char buffer[20]={}; // To hold UART output
    while (1) {

        while (imu->IMURead()) {
            RTIMU_DATA imuData = imu->getIMUData();
                printf("%s\r", RTMath::displayDegrees("Gyro", imuData.fusionPose));
                float current_reading=imuData.fusionPose.x()*(180.0/3.14);
                //sprintf(buffer,"%4f\n",imuData.fusionPose.x()*(180.0/3.14));
                //mraa_uart_write(uart, buffer, sizeof(buffer)); // Write to UART
                //duty_cycle=((current_reading/90)*0.05)+0.05;
                duty_cycle=(current_reading/90); //scale from 0.5 to 0.7
                duty_cycle=((duty_cycle*.2)+0.5);
                pwm->config_percent(3,duty_cycle); // Write duty_cycle with period of 1ms
                //pwm->period_us(200);
                //pwm->pulsewidth_us(duty_cycle*200);
                printf("\n\n");
                fflush(stdout);


        }

    }
    mraa_uart_stop(uart);
  	mraa_deinit();
}

mraa::Pwm* initPwm(){
	mraa::Pwm* pwm;
	pwm=new mraa::Pwm(0);
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



