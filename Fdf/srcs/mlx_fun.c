#include "fdf.h"
#include "mlx.h"
#include "math.h"
#include <stdio.h>

int		ft_close_win(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	exit(0);
	return (1);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->data_addr + (y * data->size_line + x
			* (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int			mouse_press(int button, int x, int y, void *param)
{
	t_data	*data;

	(void)x;
	(void)y;
	data = (t_data *)param;
	if (button == MOUSE_UP || button == MOUSE_DOWN)
	{	
		zooming(button, data);
		draw(data);
	}
	else if (button == MOUSE_LEFT)
		data->mouse.is_pressed = true;
	printf("mouse_press button: %d x: %d y: %d\n", button, x, y);
	return (0);
}


/*
** Handle mouse release
*/

int			mouse_release(int button, int x, int y, void *param)
{
	t_data	*data;

	(void)x;
	(void)y;
	(void)button;
	data = (t_data *)param;
	data->mouse.is_pressed = false;
	printf("MOUSE RELEASE button: %d x: %d y: %d\n", button, x, y);
	return (0);
}

/*
** Handle mouse move
*/

int			mouse_move(int x, int y, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	//printf("x: %d y: %d   prev_x: %d prev_y: %d\n", x, y,  data->mouse.previous_x, data->mouse.previous_y);
	data->mouse.previous_x = data->mouse.x;
	data->mouse.previous_y = data->mouse.y;
	data->mouse.x = x;
	data->mouse.y = y;
	if (data->mouse.is_pressed)
	{
		data->camera.beta += (x - data->mouse.previous_x) * 0.002;
		data->camera.alpha += (y - data->mouse.previous_y) * 0.002;
		draw(data);
	}
	return (0);
}


void	ft_init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, NAME_PROGRAMM);
	data->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->data_addr = mlx_get_data_addr(data->img, &(data->bits_per_pixel),
											&(data->size_line), &(data->endian));
	
	
	data->camera.alpha = 0;
	data->camera.beta = 0;
	data->camera.gamma = 0;
	data->camera.zoom = ft_min((WIDTH - MENU_WIDTH) / data->map.width / 2,
												HEIGHT / data->map.height / 2);
	data->camera.shift_x = 0;
	data->camera.shift_y = 0;
	data->camera.z_divisor = 1;
	data->mouse.is_pressed = false;
	draw(data);
	mlx_key_hook(data->mlx_win, ft_keyyboard, data);
	mlx_hook(data->mlx_win, 2, 0, ft_keyyboard, data);
	mlx_hook(data->mlx_win, 17, 0L, ft_close_win, data);

	mlx_hook(data->mlx_win, 4, 0, mouse_press, data);
	mlx_hook(data->mlx_win, 5, 0, mouse_release, data);
	mlx_hook(data->mlx_win, 6, 0, mouse_move, data);


	mlx_loop(data->mlx_ptr);
}
