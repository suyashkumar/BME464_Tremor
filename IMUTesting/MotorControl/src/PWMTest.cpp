#include <iostream>
#include <string.h>
#include <time.h>
#include <mraa.hpp>


int main() {

	mraa::Pwm* pwm;
	pwm = new mraa::Pwm(0);
	clock_t t;
	if (pwm == NULL) {
		return MRAA_ERROR_UNSPECIFIED;
	}
	if (pwm->enable(true) != MRAA_SUCCESS) {
		std::cerr << "Cannot enable PWM on mraa::PWM object, exiting" << std::endl;
		return MRAA_ERROR_UNSPECIFIED;
	}
	char buffer[20];
	float duty_cycle=0.5;
  for (;;) {

	  pwm->config_percent(20,(0.8*0.05)+0.05);
	  usleep(50000);
	  pwm->config_percent(20,0.05+0.05);
	  //pwm->period_us(500);

	  usleep(50000);
  }
  delete pwm;
  return 0;
}
