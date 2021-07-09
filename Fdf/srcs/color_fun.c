#include "fdf.h"

/*
** Get percent
*/

double	percent(int start, int end, int current)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	if (distance == 0)
		return (1.0);
	return (placement / distance);
}

/*
** Get color from default palette. Color depends on altitude
*/

int	get_default_color(int z, t_map *map)
{
	double	percentage;

	percentage = percent(map->z_min, map->z_max, z);
	if (percentage < 0.2)
		return (COLOR_DISCO);
	else if (percentage < 0.4)
		return (COLOR_BRICK_RED);
	else if (percentage < 0.6)
		return (COLOR_FLAMINGO);
	else if (percentage < 0.8)
		return (COLOR_JAFFA);
	else
		return (COLOR_SAFFRON);
}

/*
** Get light for color. Result depends on point position.
** This function is needed to create linear gradient.
*/

int	get_mix_color(int start, int end, double percent)
{
	t_rgb	st;
	t_rgb	en;
	t_rgb	new_color;

	st = ft_create_trgb(start);
	en = ft_create_trgb(end);
	new_color = ft_rgb_mult_db(st, (1 - percent));
	new_color = ft_rgb_plus_rgb(new_color, ft_rgb_mult_db(en, percent));
	return (ft_trgbtoint(new_color));
}

/*
** Get color. Result depends on point position.
** This function is needed to create linear gradient.
*/

int	get_color(t_point current, t_point start, t_point end, t_point delta)
{
	double	percentage;

	if (current.color == end.color)
		return (current.color);
	if (delta.x > delta.y)
		percentage = percent(start.x, end.x, current.x);
	else
		percentage = percent(start.y, end.y, current.y);
	return (get_mix_color(start.color, end.color, percentage));
}
