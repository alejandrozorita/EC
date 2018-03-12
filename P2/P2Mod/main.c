#include <stdio.h>
#include "44b.h"
#include "button.h"
#include "leds.h"
#include "utils.h"
#include "D8Led.h"
#include "gpio.h"

struct RLstat {
	int moving;
	int speed;
	int iter;
	int direction;
	int position;
	int position2;
};

static struct RLstat RL = {
	.moving = 1,
	.speed = 3,
	.iter = 3,
	.direction = 1,
	.position = 0,
};
static struct RLstat RL2 = {
	.moving = 1,
	.speed = 3,
	.iter = 3,
	.direction = 1,
	.position = 1,
};

int setup(void)
{
	leds_init();
	D8Led_init();
	D8Led_segment(RL.position);

	/* Port G: configuración para espera activa */

	//COMPLETAR: utilizando el interfaz para el puerto G definido en gpio.h hay
	//que configurar los pines 6 y 7 del puerto G como pines de entrada y
	//activar las correspondientes resistencias de pull-up
	
	/*******************************************/
	portG_conf(6, INPUT);
	portG_conf(7, INPUT);

	portG_conf_pup(6, ENABLE);
	portG_conf_pup(7, ENABLE);

	Delay(0);
	return 0;
}

int loop(void)
{
	unsigned int buttons = read_button();

	if (buttons & BUT1) {
		// COMPLETAR: utilizando la interfaz para los leds definida en leds.h
		// hay que conmutar el led1
		// También hay que comutar la dirección del movimiento del led rotante
		// representado por el campo direction de la variable RL
		led1_switch();
		RL.direction = -RL.direction;
		/*if (RL.direction == 0)
		{
			led1_on();
			RL.direction = 1;
		}
		else
		{
			led1_off();
			RL.direction = -1;
		}*/
	}

	if (buttons & BUT2) {
		// COMPLETAR: utilizando la interfaz para los leds definida en leds.h
		// hay que conmutar el led2
		// También hay que comutar el estado de movimiento del led rotante
		// representado por el campo moving de la variable RL, y en caso de
		// ponerlo en marcha debemos reiniciar el campo iter al valor del campo
		// speed.

		led2_switch();
		/*if (RL.moving)
			RL.moving = 0; //paro la rotacion
		else
		{
			RL.moving = 1;
			RL.iter = RL.speed; //reinicializo iter a speed
		}*/
		RL.speed += 3;
		if (RL.speed > 12)
		{
			RL.speed = 3;
		}
	}
	if (RL.moving) {
		RL.iter--;
		if (RL.iter == 0) {
			// COMPLETAR: debemos hacer avanzar el led rotante una posición en
			// la dirección indicada por el campo direction de la variable RL.
			// La posición actual está representada en el campo position.
			// Recordar que queremos un movimiento circular, representado por
			// las 6 primeras posiciones en el array Segmentes del display de 8
			// segmentos, por lo que position debe estar siempre entre 0 y 5.


			
			if(RL.direction == 1)
			{
				if (RL.position == 5)
				{
					RL.position = 0;
				}
				else
				{
					RL.position += RL.direction;
				}
			}
			else
			{
				if (RL.position == 0)
				{
					RL.position = 5;
				}
				else
				{
					RL.position += RL.direction;
				}
			}
			if (RL2.position == 5)
			{
				RL2.position = 0;
			}
			else
			{
				RL2.position += RL2.direction;
			}
			D8Led_2segments(RL.position, RL2.position);
			RL.iter = RL.speed; //reinicializo iter a speed
		}

	}

	Delay(2000); // espera de 200ms para que el bucle se repita 5 veces por segundo
	return 0;
}

int main(void)
{
	setup();

	while (1) {
		loop();
	}
}
