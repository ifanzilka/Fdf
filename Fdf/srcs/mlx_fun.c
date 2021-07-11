#include "fdf.h"
#include "mlx.h"
#include "math.h"
#include <stdio.h>

int	ft_close_win(t_data *data)
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

static void	ft_init_data(t_data *data)
{
	data->camera.alpha = 0;
	data->camera.beta = 0;
	data->camera.gamma = 0;
	data->camera.zoom = fmin((WIDTH - MENU_WIDTH) / data->map.width / 2,
			HEIGHT / data->map.height / 2);
	data->camera.shift_x = 0;
	data->camera.shift_y = 0;
	data->map.z_divisor = 1;
	data->mouse.is_pressed = false;
	data->camera.projection = ISO;
}

void	ft_init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, NAME_PROGRAMM);
	data->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->data_addr = mlx_get_data_addr(data->img, &(data->bits_per_pixel),
			&(data->size_line), &(data->endian));
	ft_init_data(data);
	draw(data);
	print_menu(data);
	mlx_key_hook(data->mlx_win, ft_keyyboard, data);
	mlx_hook(data->mlx_win, 2, 0, ft_keyyboard, data);
	mlx_hook(data->mlx_win, 17, 0L, ft_close_win, data);
	mlx_hook(data->mlx_win, 4, 0, mouse_press, data);
	mlx_hook(data->mlx_win, 5, 0, mouse_release, data);
	mlx_hook(data->mlx_win, 6, 0, mouse_move, data);
	mlx_loop(data->mlx_ptr);
}
