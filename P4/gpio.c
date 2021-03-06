#include "44b.h"
#include "gpio.h"

/* Port B interface implementation */

int portB_conf(int pin, enum port_mode mode)
{
	int ret = 0;
	if (pin < 0 || pin > 10)
		return -1;

	if (mode == SIGOUT)
		// COMPLETAR: tomar la implementación de la primera parte
	else if (mode == OUTPUT)
		// COMPLETAR: tomar la implementación de la primera parte
	else
		ret = -1;

	return ret;
}

int portB_write(int pin, enum digital val)
{
	if (pin < 0 || pin > 10)
		return -1;

	if (val < 0 || val > 1)
		return -1;

	if (val)
		// COMPLETAR: tomar la implementación de la primera parte
	else
		// COMPLETAR: tomar la implementación de la primera parte

	return 0;
}

/* Port G interface implementation */

int portG_conf(int pin, enum port_mode mode)
{
	int pos  = pin*2;

	if (pin < 0 || pin > 7)
		return -1;

	switch (mode) {
		case INPUT:
			// COMPLETAR: tomar la implementación de la primera parte
			break;
		case OUTPUT:
			// COMPLETAR: tomar la implementación de la primera parte
			break;
		case SIGOUT:
			// COMPLETAR: tomar la implementación de la primera parte
			break;
		case EINT:
			// COMPLETAR: tomar la implementación de la primera parte
			break;
		default:
			return -1;
	}

	return 0;
}

int portG_eint_trig(int pin, enum trigger trig)
{
	int pos = pin*4;

	if (pin < 0 || pin > 7)
		return -1;

	switch (trig) {
		case LLOW:
			// COMPLETAR: tomar la implementación de la seguna parte
			break;
		case LHIGH:
			// COMPLETAR: tomar la implementación de la seguna parte
			break;
		case FALLING:
			// COMPLETAR: tomar la implementación de la seguna parte
			break;
		case RISING:
			// COMPLETAR: tomar la implementación de la seguna parte
			break;
		case EDGE:
			// COMPLETAR: tomar la implementación de la seguna parte
			break;
		default:
			return -1;
	}
	return 0;
}

int portG_write(int pin, enum digital val)
{
	int pos = pin*2;

	if (pin < 0 || pin > 7)
		return -1;

	if (val < 0 || val > 1)
		return -1;

	if ((rPCONG & (0x3 << pos)) != (0x1 << pos))
		return -1;

	if (val)
		// COMPLETAR: tomar la implementación de la primera parte
	else
		// COMPLETAR: tomar la implementación de la primera parte

	return 0;
}

int portG_read(int pin, enum digital* val)
{
	int pos = pin*2;

	if (pin < 0 || pin > 7)
		return -1;

	if (rPCONG & (0x3 << pos))
		return -1;

	if (rPDATG & (0x1 << pin))
		// COMPLETAR: tomar la implementación de la primera parte
	else
		// COMPLETAR: tomar la implementación de la primera parte

	return 0;
}

int portG_conf_pup(int pin, enum enable st)
{
	if (pin < 0 || pin > 7)
		return -1;

	if (st != ENABLE && st != DISABLE)
		return -1;

	if (st == ENABLE)
		// COMPLETAR: tomar la implementación de la primera parte
	else
		// COMPLETAR: tomar la implementación de la primera parte

	return 0;
}

