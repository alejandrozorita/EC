#include <stdio.h>
#include "44b.h"
#include "button.h"
#include "leds.h"
#include "utils.h"
#include "D8Led.h"
#include "intcontroller.h"
#include "timer.h"
#include "gpio.h"

struct RLstat {
	int moving;
	int speed;
	int direction;
	int position;
	int count;
};

static struct RLstat RL = {
	.moving = 0,
	.speed = 5,
	.direction = 1,
	.position = 0,
	.count = 0,
};

void irq_ISR(void) __attribute__ ((interrupt ("IRQ")));

void timer_ISR(void)
{
	//COMPLETAR: tomar el código de avance de posición del led rotante de la
	//primera parte
	if (RL.moving == 1)
	{
		if (RL.direction == 1)
		{
			RL.position++;
			if (RL.position > 5)
			{
			RL.position = 0;
			}
		}
		else
		{
			RL.position--;
				if (RL.position < 0)
				{
					RL.position = 5;
				}
		}
	}

	D8Led_segment(RL.position);
}

void button_ISR(void)
{
	unsigned int whicheint = rEXTINTPND;
	unsigned int buttons = (whicheint >> 2) & 0x3;

	//COMPLETAR: usar el código de la primera parte parte de atención a los
	//pulsadores
	if (buttons & BUT1)
	{
		led1_switch();
		//RL.direction = -RL.direction;
		RL.count =  (RL.count+1)%4;
		switch (RL.count)
		{
		case 1:
			tmr_set_divider(TIMER0, D1_8);
			tmr_set_count(TIMER0, 62500,45835);
			tmr_update(TIMER0);
			break;
		case 2:
			tmr_set_divider(TIMER0, D1_8);
			tmr_set_count(TIMER0, 31250,15000);
			tmr_update(TIMER0);
			break;
		case 3:
			tmr_set_divider(TIMER0, D1_8);
			tmr_set_count(TIMER0, 15625 ,7800);
			tmr_update(TIMER0);
			break;
		default:
			tmr_set_divider(TIMER0, D1_4);
			tmr_set_count(TIMER0, 15625 ,7800);
			tmr_update(TIMER0);
			break;
		}
	}
	if (buttons & BUT2)
	{
		led2_switch();
		if (RL.moving)
			RL.moving = 0; //paro la rotacion
		else
		{
			RL.moving = 1;
			//RL.iter = RL.speed; //reinicializo iter a speed
		}
	}


	// eliminamos rebotes
	Delay(2000);
	// borramos el flag en extintpnd
	//rEXTINTPND = (0x1 << buttons);
	rEXTINTPND = whicheint;
				//COMPLETAR: debemos borrar las peticiones de interrupción en
		         //EXTINTPND escribiendo un 1 en los flags que queremos borrar (los
				 //correspondientes a los pulsadores pulsados)
}

void irq_ISR(void)
{
	int bit = rI_ISPR;

	//COMPLETAR: debemos ver si la interrupción que debemos atender (bit) es la
	//de la línea INT_TIMER0 and INT_EINT4567. Si es la del timer se invocará la
	//función timer_ISR y después se borrará el flag de interrupción utilizando
	//el interfaz definido en intcontroller.h. Si es la de EINT4567 se invocará
	//la función button_ISR y se borrará el flag correspondiente utilizando el
	//mismo interfaz.
	if(bit == INT_BIT(INT_TIMER0)){
		timer_ISR();
		ic_cleanflag(INT_TIMER0);
	}
	else if(bit == INT_BIT(INT_EINT4567)){
		button_ISR();
		ic_cleanflag(INT_EINT4567);
	}

}


int setup(void)
{
	leds_init();
	D8Led_init();
	D8Led_segment(RL.position);

	/* Port G: configuración para generación de interrupciones externas */

	//COMPLETAR: utilizando el interfaz para el puerto G definido en gpio.h
	//configurar los pines 6 y 7 del puerto G para poder generar interrupciones
	//externas por flanco de bajada por ellos y activar las correspondientes
	//resistencias de pull-up.
	portG_conf(6, EINT);

	portG_conf(7, EINT);



	portG_eint_trig(6, FALLING);
	portG_eint_trig(7, FALLING);

	portG_conf_pup(6, HIGH);
	portG_conf_pup(7, HIGH);


	/********************************************************************/

	/* Configuración del timer */

	//COMPLETAR: utilizando el interfaz para los timers definido en timer.h
	//configurar el timer 0: 
	//      valor de prescalado a 255
	//      valor del divisor 1/8
	//      valor de cuenta 62500 y cualquier valor de comparación entre 1 y 62499
	//      actualizar el contador con estos valores (update)
	//      poner el contador en modo RELOAD
	//      dejar el contador parado



	tmr_set_prescaler(TIMER0, 255);
	tmr_set_divider(TIMER0, D1_8);
	tmr_set_count(TIMER0, 62500,45835);
	tmr_update(TIMER0);
	tmr_set_mode(TIMER0, RELOAD);
	tmr_stop(TIMER0);


//	if (RL.moving)
		tmr_start(TIMER0);
	/***************************/

	// Registramos la ISR
	pISR_IRQ = (unsigned) irq_ISR;//COMPLETAR: registrar irq_ISR como rutina de tratamiento de
		       //interrupción para la linea IRQ

	/* Configuración del controlador de interrupciones
	 * Habilitamos la línea IRQ, en modo no vectorizado
	 * y registramos una ISR para la línea IRQ
	 * Configuramos el timer 0 en modo IRQ y habilitamos
	 * esta línea
	 * Configuramos la línea EINT4567 en modo IRQ y la
	 * habilitamos
	 */
	ic_init();
	ic_conf_irq(ENABLE, NOVEC);
	ic_conf_fiq(DISABLE);
	ic_conf_line(INT_TIMER0, IRQ);
	ic_enable(INT_TIMER0);
	ic_conf_line(INT_EINT4567, IRQ);
	ic_enable(INT_EINT4567);


	//COMPLETAR: utilizando el interfaz definido en intcontroller.h
	//		habilitar la línea IRQ en modo no vectorizado
	//		deshabilitar la línea FIQ
	//		configurar la línea INT_TIMER0 en modo IRQ
	//		configurar la línea INT_EINT4567 en modo IRQ
	//		habilitar la línea INT_TIMER0
	//		habilitar la línea INT_EINT4567

	//***************************************************/

	ic_conf_irq(ENABLE, NOVEC);
	ic_conf_fiq(DISABLE);
	ic_conf_line(INT_TIMER0, IRQ);
	ic_conf_line(INT_EINT4567, IRQ);
	ic_enable(INT_TIMER0);
	ic_enable(INT_EINT4567);

	Delay(0);
	return 0;
}

int loop(void)
{
	return 0;
}


int main(void)
{
	setup();

	while (1) {
		loop();
	}
}
