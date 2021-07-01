#include <libft.h>
#include <fdf.h>
#include <fcntl.h>
#include "mlx.h"
#include "math.h"

void	print_menu(t_data *data)
{
	int		y;
	void	*mlx;
	void	*win;

	y = 0;
	mlx = data->mlx_ptr;
	win = data->mlx_win;
	mlx_string_put(mlx, win, 65, y += 20, TEXT_COLOR, "How to Use");
	mlx_string_put(mlx, win, 15, y += 35, TEXT_COLOR, "Zoom: Scroll or +/-");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Move: Arrows");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Flatten: </>");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Rotate: Press & Move");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Rotate:");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "X-Axis - 2/8");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "Y-Axis - 4/6");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "Z-Axis - 1(3)/7(9)");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Projection");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "ISO: I Key");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "Parallel: P Key");
}


float max(float a, float b)
{
	if (a > b)
		return (a);
	return (b); 
}

float mod(float i)
{
	if (i > 0)
		return i;
	return (i * (-1));
}

void 	format3d(float *x, float *y, int z, float angle)
{
	*x = (*x - *y) * cos(angle);
	*y = (*x + *y) * sin(angle) - z;

}


void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->data_addr + (y * data->size_line + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_line(float x, float y, float x1, float y1, t_data *data)
{
	float 	x_step;
	float 	y_step;
	float 	maxi;
	int 	z;
	int 	z1;
	
	z = data->map.z_matrix[(int)y][(int)x];
	z1 = data->map.z_matrix[(int)y1][(int)x1];
	x *= data->zoom;
	y *= data->zoom;
	x1 *= data->zoom;
	y1 *= data->zoom;
	if (z || z1)
		data->color = RED;
	else
		data->color = WHIITE;
	format3d(&x, &y, z, data->angle);
	format3d(&x1, &y1, z1, data->angle);
	x_step = x1 - x;
 	y_step = y1 - y;
	x += data->shift_x;
	y += data->shift_y;
	x1 += data->shift_x;
	y1 += data->shift_y;
	maxi = max(mod(x_step), mod(y_step));
	x_step /= maxi;
	y_step /= maxi;
	while ((int)(x  - x1) || (int)(y - y1))
	{
		//if (x > 250)
		my_mlx_pixel_put(data, x, y, data->color);
			//mlx_pixel_put(data->mlx_ptr, data->mlx_win, x, y, data->color);
		x += x_step;
		y += y_step;
		if (x > WIDTH || y > HEIGHT || y < 0 || x < 0)
			break ;
	}
}

static void	draw_background(t_data *data)
{
	int	*image;
	int	i;

	ft_bzero(data->data_addr, WIDTH * HEIGHT * (data->bits_per_pixel / 8));
	image = (int *)(data->data_addr);
	i = 0;
	while (i < HEIGHT * WIDTH)
	{
		image[i] = (i % WIDTH < MENU_WIDTH) ? MENU_BACKGROUND : BACKGROUND;
		i++;
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
				draw_line(x, y, x + 1, y , data);
			if (y != data->map.height - 1)
				draw_line(x, y, x, y + 1, data);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);
}

int	ft_keyyboard(int keycode, t_data *data)
{
	(void) data;
	printf("Keycode: %d\n", keycode);
	if (keycode == ESC)
		exit(0);
	if (keycode == LEFT)	
		data->shift_x -=10;
	if (keycode == RIGHT)
		data->shift_x +=10;
	if (keycode == UP)
		data->shift_y +=10;
	if (keycode == DOWN)
		data->shift_y -=10;
	if (keycode == PLUS)
		data->zoom +=5;
	if (keycode == MINUS)
		data->zoom -=5;
	if (keycode == Z)
		data->angle -= 0.1;
	if (keycode == X)
		data->angle += 0.1;		
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

void	ft_init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, NAME_PROGRAMM);
	data->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->data_addr = mlx_get_data_addr(data->img, &(data->bits_per_pixel),
											&(data->size_line), &(data->endian));
	data->zoom = ZOOM;
	data->shift_x = 0;
	data->shift_y = 0;
	data->angle = 0.8;
	
	print_menu(data);
	draw(data);
	//mlx_hook()
	//mlx_key_hook(data->mlx_win, ft_keyyboard, data);
	mlx_hook(data->mlx_win, 2, 0, ft_keyyboard, data);
	mlx_hook(data->mlx_win, 17, 0L, ft_close_win, data);
	mlx_loop(data->mlx_ptr);
}

int main(int argc, char **argv)
{
	t_data 	data;
	int		fd;
	char 	*line;
	
	line = NULL;
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
		//ft_init_mlx(&data);
	}
	return (0);
}