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
			// hacky, but ledval will be roughly in the -400..400 range
			int32_t ledval = neuron.potential >> 18; 
			ledval += 400;
			setLED((uint16_t)ledval);
        }
	}
}
