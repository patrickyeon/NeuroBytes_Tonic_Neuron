#include "HAL.h"
#include "neuron.h"
#include "izhi.h"

int main(void)
{
	clock_setup();
	gpio_setup();
	tim_setup();
	// this gives a main_tick roughly every 5.1ms, which makes the neuron
	//  trigger at a sensible rate on my setup
	systick_setup(10);

	// initialize neuron
	ineuron_t neuron;
	CH_i(&neuron);

	for(;;)
	{
		if (main_tick)
		{
			main_tick = 0;
			step_i(&neuron, 10 * neuron.scale, 3);
			// have the LED in R, G, B for the rest, transition, spike regions
			//  respectively
			if (neuron.potential < -60 * neuron.scale) {
				setLED(1000, 0, 0);
			} else if (neuron.potential < -40 * neuron.scale) {
				setLED(0, 1000, 0);
			} else {
				setLED(0, 0, 1000);
			}
        }
	}
}
