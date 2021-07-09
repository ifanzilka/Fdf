#include "fdf.h"

t_point	new_point(int x, int y, t_data *data)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = data->map.z_matrix[y][x];
	if (data->map.colors[y][x] != -1)
		point.color = data->map.colors[y][x];
	else
		point.color = get_default_color(point.z, &data->map);
	return (point);
}

t_point	direction(t_point f, t_point s)
{
	t_point	vec;

	if (f.x < s.x)
		vec.x = 1;
	else
		vec.x = -1;
	if (f.y < s.y)
		vec.y = 1;
	else
		vec.y = -1;
	return (vec);
}
