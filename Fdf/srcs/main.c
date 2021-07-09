#include <libft.h>
#include <fdf.h>
#include <fcntl.h>
#include "mlx.h"
#include "math.h"

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
	if (keycode == PLUS)
		data->camera.zoom +=1;
	if (keycode == MINUS)
		data->camera.zoom -=1;
	if (keycode == Z)
		data->camera.beta += 0.1;
	if (keycode == X)
		data->camera.beta -= 0.1;
			
	mlx_clear_window(data->mlx_ptr, data->mlx_win);
	draw(data);
	return (0);
}

int		ft_close_win(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->mlx_win);
	exit(0);
	return (1);
}

int ft_min(int a , int b)
{
	if (a < b)
		return (a);
	return (b);	
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
	
	draw(data);
	mlx_key_hook(data->mlx_win, ft_keyyboard, data);
	mlx_hook(data->mlx_win, 2, 0, ft_keyyboard, data);
	mlx_hook(data->mlx_win, 17, 0L, ft_close_win, data);
	mlx_loop(data->mlx_ptr);
}

int main(int argc, char **argv)
{
	t_data 	data;
	int		fd;
	
	if (argc < 2)
	{
		ft_putstr_fd("Please, Usage: ./fdf [File]\n", 1);
		return (err_argv);
	}
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			ft_putstr_fd("Could not open file\n", 2);
			return (err_open);
		}
		close(fd);
		ft_parse_map(argv[1], &data.map);
		data.map.z_max = map_max_z(&data.map);
		data.map.z_min = map_min_z(&data.map);
		
		// int i;
		// int j;

		// i = 0;
		// while (i < data.map.height)
		// {
		// 	j = 0;
		// 	while (j < data.map.width)
		// 	{
		// 		printf("%2d ", data.map.z_matrix[i][j]);
		// 		j++;
		// 	}
		// 	printf("\n");
		// 	i++;
		// }
		ft_init_mlx(&data);
	}
	return (0);
}