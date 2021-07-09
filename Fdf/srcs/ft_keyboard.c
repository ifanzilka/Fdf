#include "fdf.h"
#include "mlx.h"
#include <stdio.h>

int	ft_keyyboard(int keycode, t_data *data)
{
	(void) data;
	printf("Keycode: %d\n", keycode);
	if (keycode == ESC)
		exit(0);
	if (keycode == LEFT)	
		data->camera.shift_x -=10;
	if (keycode == RIGHT)
		data->camera.shift_x +=10;
	if (keycode == UP)
		data->camera.shift_y +=10;
	if (keycode == DOWN)
		data->camera.shift_y -=10;
	if (keycode == PLUS || keycode == MINUS)
		zooming(keycode, data);
	if (keycode == Z)
		data->camera.beta += 0.1;
	if (keycode == X)
		data->camera.beta -= 0.1;
			
	mlx_clear_window(data->mlx_ptr, data->mlx_win);
	draw(data);
	return (0);
}