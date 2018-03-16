/*********************************************************************************************
* Fichero:		timer.c
* Descrip:		funciones de control del timer0 del s3c44b0x
*********************************************************************************************/

/*--- ficheros de cabecera ---*/
#include "44b.h"
#include "timer.h"

int tmr_set_prescaler(int p, int  value)
{
	int offset = p*8;
	value &= 0xFF;

	if (p < 0 || p > 3)
		return -1;

	//COMPLETAR

	return 0;
}

int tmr_set_divider(int d, enum tmr_div div)
{
	int ret = 0;

	if ((d < 0 || d > 5) ||
			(div == D1_32 && d > 3) ||
			(div == EXTCLK && d != 5) ||
			(div == TCLK && d != 4))
		return -1;

	if (div == EXTCLK || div == TCLK)
		div = 4;

	//COMPLETAR: tomar el código de la segunda parte

	return 0;
}

int tmr_set_count(enum tmr_timer t, int count, int cmp)
{
	int err = 0;
	switch (t) {
		case TIMER0:
			//COMPLETAR: tomar el código de la segunda parte
			 break;
		case TIMER1:
			//COMPLETAR: tomar el código de la segunda parte
			 break;
		case TIMER2:
			//COMPLETAR: tomar el código de la segunda parte
			 break;
		case TIMER3:
			//COMPLETAR: tomar el código de la segunda parte
			 break;
		case TIMER4:
			//COMPLETAR: tomar el código de la segunda parte
			 break;
		case TIMER5:
			//COMPLETAR: tomar el código de la segunda parte
			 break;
		default:
			err = -1;
	}

	return err;
}

int tmr_update(enum tmr_timer t)
{
	int pos = t*4;
	if (t > 0)
		pos += 4;

	if (t < 0 || t > 5)
		return -1;

	//COMPLETAR: tomar el código de la segunda parte

	return 0;
}

int tmr_set_mode(enum tmr_timer t, enum tmr_mode mode)
{
	int err = 0;
	int pos = t*4;
	if (t > 0)
		pos += 4;

	if (t < 0 || t > 5)
		return -1;

	if (mode == ONE_SHOT)
		//COMPLETAR: tomar el código de la segunda parte
	else if (mode == RELOAD)
		//COMPLETAR: tomar el código de la segunda parte
	else
		err = -1;

	return err;
}

int tmr_start(enum tmr_timer t)
{
	int pos = t*4;
	if (t > 0)
		pos += 4;

	if (t < 0 || t > 5)
		return -1;

	//COMPLETAR: tomar el código de la segunda parte
	return 0;
}

int tmr_stop(enum tmr_timer t)
{
	int pos = t*4;
	if (t > 0)
		pos += 4;

	if (t < 0 || t > 5)
		return -1;

	//COMPLETAR: tomar el código de la segunda parte
	return 0;
}

int tmr_isrunning(enum tmr_timer t)
{
	int ret = 0;
	int pos = t*4;
	if (t > 0)
		pos += 4;

	if ((t >= 0) && (t <= 5) 
			&& (rTCON & (0x1 << pos)))
		ret = 1;

	return ret;
}

