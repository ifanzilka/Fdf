
#include "fdf.h"
#include "mlx.h"

/*
** Get percent
*/

double	percent(int start, int end, int current)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
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

int	get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

/*
** Get color. Result depends on point position.
** This function is needed to create linear gradient.
*/

int	get_color(t_point current, t_point start, t_point end, t_point delta)
{
	int		red;
	int		green;
	int		blue;
	double	percentage;

	if (current.color == end.color)
		return (current.color);
	if (delta.x > delta.y)
		percentage = percent(start.x, end.x, current.x);
	else
		percentage = percent(start.y, end.y, current.y);
	red = get_light((start.color >> 16) & 0xFF,
					(end.color >> 16) & 0xFF,
					percentage);
	green = get_light((start.color >> 8) & 0xFF,
					(end.color >> 8) & 0xFF,
					percentage);
	blue = get_light(start.color & 0xFF,
					end.color & 0xFF,
					percentage);
	return ((red << 16) | (green << 8) | blue);
}


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->data_addr + (y * data->size_line + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_background(t_data *data)
{
	int	*image;
	int	i;

	image = (int *)(data->data_addr);
	i = 0;
	while (i < HEIGHT * WIDTH)
	{
		if (i % WIDTH < MENU_WIDTH)
			image[i] = MENU_BACKGROUND;
		else
			image[i] = BACKGROUND;	
		i++;
	}
}

#include <stdio.h>

t_point	new_point(int x, int y, t_data *data)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = data->map.z_matrix[y][x];
	if (data->map.colors[y][x] != -1)
	{
		//point.color = get_default_color(point.z, &data->map);
		point.color = data->map.colors[y][x];
		//printf("color: %d\n", point.color);
	}	
	else
		point.color = get_default_color(point.z, &data->map);
	return (point);
}

t_point direction(t_point f, t_point s)
{
	t_point vec;

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

static void	put_pixel(t_data *fdf, int x, int y, int color)
{
	int		i;

	if (x >= MENU_WIDTH && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		i = (x * fdf->bits_per_pixel / 8) + (y * fdf->size_line);
		fdf->data_addr[i] = color;
		fdf->data_addr[++i] = color >> 8;
		fdf->data_addr[++i] = color >> 16;
	}
}

void draw_line(t_point f, t_point s, t_data *data)
{
	t_point	delta;
	t_point	cur;
	t_point	vec;	
	int		coord[2];
	
	cur = f;
	delta.x = mod(s.x - f.x);
	delta.y = mod(s.y - f.y);
	vec = direction(f, s);
	coord[0] = delta.x - delta.y;
	while (cur.x != s.x || cur.y != s.y)
	{
		if (cur.x >= WIDTH || cur.y >= HEIGHT || cur.y < 0 || cur.x < 0)
 			break;
		if (cur .x > MENU_WIDTH)
			put_pixel(data, cur.x, cur.y, get_color(cur, f, s, delta));
			//my_mlx_pixel_put(data, cur.x, cur.y, get_color(cur, f, s, delta));
		coord[1] = coord[0] * 2;
		if (coord[1] > -delta.y) 
		{
			coord[0] -= delta.y;
			cur.x += vec.x;
		}
		if (coord[1] < delta.x) 
		{
			coord[0] += delta.x; 
			cur.y += vec.y;
		}
	}
}

void draw(t_data *data)
{
	int x;
	int y;

	draw_background(data);
	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (x != data->map.width - 1)
				draw_line(project(new_point(x, y, data),data),
					project(new_point(x + 1, y, data),data), data);
			if (y != data->map.height - 1)
				draw_line(project(new_point(x, y, data), data),
					project(new_point(x, y + 1, data),data), data);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);
	print_menu(data);
}

