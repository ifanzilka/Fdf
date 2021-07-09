#include "fdf.h"

/*
**  Fun create_rgb
**
**  Example:
** r -> 155  (10011011)
** g -> 240  (11110000)
** b -> 100  (01100100)
** (r << 16) -> (100110110000000000000000) (plus 16 zero bit)
** (g << 8) -> (1111000000000000)
** b ->   (01100100)
** "l" -> oretion OR (bits)
**    (100110110000000000000000)
** or (000000001111000000000000)
**    (000000000000000001100100)
** res(100110111111000001100100)
*/

t_rgb	ft_create_trgb(int color)
{
	t_rgb	rgb;

	rgb.red = (color >> 16) & 0xFF;
	rgb.green = (color >> 8) & 0xFF;
	rgb.blue = (color) & 0xFF;
	return (rgb);
}

int	ft_create_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

int 	ft_trgbtoint(t_rgb rgb)
{
	return (rgb.red << 16 | rgb.green << 8 | rgb.blue);
}

t_rgb	ft_rgb_mult_db(t_rgb rgb, double a)
{
	rgb.red = (int)((double)rgb.red * a);
	rgb.green = (int)((double)rgb.green * a);
	rgb.blue = (int)((double)rgb.blue * a);
	if (rgb.red > 255)
		rgb.red = 255;
	if (rgb.green > 255)
		rgb.green = 255;
	if (rgb.blue > 255)
		rgb.blue = 255;
	return (rgb);
}

t_rgb	ft_rgb_plus_rgb(t_rgb a, t_rgb b)
{
	t_rgb	rgb;

	rgb.red = a.red + b.red;
	rgb.green = a.green + b.green;
	rgb.blue = a.blue + b.blue;
	if (rgb.red > 255)
		rgb.red = 255;
	if (rgb.green > 255)
		rgb.green = 255;
	if (rgb.blue > 255)
		rgb.blue = 255;
	return (rgb);
}
