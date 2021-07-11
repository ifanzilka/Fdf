#include "fdf.h"
#include "mlx.h"
#include <stdio.h>

void	zooming(int code, t_data *data)
{
	if (code == MINUS || code == MOUSE_DOWN)
		data->camera.zoom--;
	if (code == PLUS || code == MOUSE_UP)
		data->camera.zoom++;
	if (data->camera.zoom < 1)
		data->camera.zoom = 1;
}

static void	moving_map(int code, t_data *data)
{
	if (code == LEFT)
		data->camera.shift_x -= 10;
	if (code == RIGHT)
		data->camera.shift_x += 10;
	if (code == UP)
		data->camera.shift_y += 10;
	if (code == DOWN)
		data->camera.shift_y -= 10;
}

static void	divizor_map(int code, t_data *data)
{
	if (code == DIVIZOR_MINUS)
		data->map.z_divisor -= 0.1;
	if (code == DIVIZOR_PLUS)
		data->map.z_divisor += 0.1;
	if (data->map.z_divisor <= 0.0)
		data->map.z_divisor = 0.1;
	if (data->map.z_divisor >= 10.0)
		data->map.z_divisor = 10.0;
}

static void	projection(int code, t_data *data)
{
	if (code == I)
		data->camera.projection = ISO;
	if (code == P)
	{
		data->camera.projection = PARALLEL;
		data->camera.alpha = 0;
		data->camera.beta = 0;
		data->camera.gamma = 0;
	}
}

int	ft_keyyboard(int code, t_data *data)
{
	if (code == ESC)
		exit(0);
	if (code == LEFT || code == RIGHT || code == UP || code == DOWN)
		moving_map(code, data);
	if (code == PLUS || code == MINUS)
		zooming(code, data);
	if (code == DIVIZOR_MINUS || code == DIVIZOR_PLUS)
		divizor_map(code, data);
	if (code == I || code == P)
		projection(code, data);
	if (ft_is_projection(code))
		ft_keyyboard2(code, data);
	draw(data);
	print_menu(data);
	return (0);
}
