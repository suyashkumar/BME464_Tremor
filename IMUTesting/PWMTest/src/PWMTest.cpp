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
	  std::cout << "Type new duty cycle: ";
	  std::cin >> buffer;
	  duty_cycle=atof(buffer);

	  t = clock();
	  pwm->config_percent(1,duty_cycle); // Write 50% duty cycle period of 1ms
	  t = clock() - t;
	  double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
	  printf("Time taken to write: %f seconds\n", time_taken);
	  //pwm->period_us(500);

	  usleep(1000);
  }
  delete pwm;
  return 0;
}
