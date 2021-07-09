#include "fdf.h"

double	max(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}

int	mod(int i)
{
	if (i > 0)
		return (i);
	return (i * (-1));
}
