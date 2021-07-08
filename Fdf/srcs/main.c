#include <libft.h>
#include <fdf.h>
#include <fcntl.h>
#include "mlx.h"
#include "math.h"

double max(double a, double b)
{
	if (a > b)
		return (a);
	return (b); 
}

int mod(int i)
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

// void	draw_line(float x, float y, float x1, float y1, t_data *data)
// {
// 	float 	x_step;
// 	float 	y_step;
// 	float 	maxi;
// 	int 	z;
// 	int 	z1;
	
// 	z = data->map.z_matrix[(int)y][(int)x];
// 	z1 = data->map.z_matrix[(int)y1][(int)x1];
// 	x *= data->camera.zoom;
// 	y *= data->camera.zoom;
// 	x1 *= data->camera.zoom;
// 	y1 *= data->camera.zoom;
// 	if (z || z1)
// 		data->color = COLOR_DISCO;
// 	else
// 	{
		
// 		data->color = WHIITE;
// 	}
// 	//printf("x: %f y: %f\n", x, y);
// 	// if (data->map.colors[(int)y][(int)x] != -1)
// 	// {
// 	// 	data->color = data->map.colors[(int)y][(int)x];
// 	// }
	
// 	format3d(&x, &y, z, data->camera.angle);
// 	format3d(&x1, &y1, z1, data->camera.angle);
// 	x_step = x1 - x;
//  	y_step = y1 - y;
	 
// 	x += data->camera.shift_x;
// 	y += data->camera.shift_y;
// 	x1 += data->camera.shift_x;
// 	y1 += data->camera.shift_y;
// 	maxi = max(mod(x_step), mod(y_step));
// 	x_step /= maxi;
// 	y_step /= maxi;
// 	while ((int)(x  - x1) || (int)(y - y1))
// 	{
// 		if (x > WIDTH || y > HEIGHT || y < 0 || x < 0)
// 			break ;
// 		if (x > MENU_WIDTH)
// 			my_mlx_pixel_put(data, x, y, data->color);
// 		x += x_step;
// 		y += y_step;
		
// 	}
// }


// static void	put_pixel(t_data *fdf, int x, int y, int color)
// {
// 	int		i;

// 	if (x >= MENU_WIDTH && x < WIDTH && y >= 0 && y < HEIGHT)
// 	{
// 		i = (x * fdf->bits_per_pixel / 8) + (y * fdf->size_line);
// 		fdf->data_addr[i] = color;
// 		fdf->data_addr[++i] = color >> 8;
// 		fdf->data_addr[++i] = color >> 16;
// 	}
// }

t_point vec_xy(t_point f, t_point s)
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

void draw_line(t_point f, t_point s, t_data *data) //[1, 1] [3, 11]
{
	t_point	delta;
	t_point vec;
	t_point cur;
	double  step[2];
	
	f.x *= ZOOM;
	f.y *= ZOOM;

	s.x *= ZOOM;
	s.y *= ZOOM;
	
	
	
	cur = f;
	delta.x = mod(s.x - f.x);
	delta.y = mod(s.y - f.y);
	step[0] = delta.x;
	step[1] = delta.y;
	vec = vec_xy(f, s);
	
	step[0] /= max(mod(delta.x), mod(delta.y));
	step[1] /= max(mod(delta.x), mod(delta.y));	
	cur.x += data->camera.shift_x;
	cur.y +=data->camera.shift_y;

	s.x +=  data->camera.shift_x;
	s.y +=  data->camera.shift_y;
	
	while (cur.x != s.x || cur.y != s.y)
	{
		if (cur.x >= WIDTH || cur.y >= HEIGHT || cur.y < 0 || cur.x < 0)
 			break ;
 		my_mlx_pixel_put(data, cur.x, cur.y, RED);
		cur.x +=  step[0];
		cur.y +=  step[1];
		
	}
}

void	draw_background(t_data *data)
{
	int	*image;
	int	i;

	ft_bzero(data->data_addr, WIDTH * HEIGHT * (data->bits_per_pixel / 8));
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

t_point	new_point(int x, int y, t_data *data)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = data->map.z_matrix[y][x];
	if (data->map.colors[y][x] != -1)
		point.color = data->map.colors[y][x];
	else
		point.color = 	COLOR_DISCO;
	//get_default_color(point.z, map) : map->colors_arr[index];
	return (point);
}

// void draw(t_data *data)
// {
// 	int x;
// 	int y;

// 	draw_background(data);
	
// 	y = 0;
// 	while (y < data->map.height)
// 	{
// 		x = 0;
// 		while (x < data->map.width)
// 		{
// 			if (x != data->map.width - 1)
// 				draw_line(x, y, x + 1, y , data);
// 			if (y != data->map.height - 1)
// 				draw_line(x, y, x, y + 1, data);
// 			x++;
// 		}
// 		y++;
// 	}
// 	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);
// 	print_menu(data);
// }

void draw(t_data *data)
{
	int x;
	int y;

	//draw_background(data);
	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (x != data->map.width - 1)
			{
				draw_line(new_point(x, y, data), new_point(x + 1, y, data), data);
				//draw_line(x, y, x + 1, y , data);
			}
			if (y != data->map.height - 1)
			{
				draw_line(new_point(x, y, data),new_point(x, y + 1, data), data);
				//draw_line(x, y, x, y + 1, data);
			}
				
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);
	//print_menu(data);
}

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
		data->camera.angle -= 0.1;
	if (keycode == X)
		data->camera.angle += 0.1;		
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
	data->camera.zoom = ZOOM;
	data->camera.shift_x = 0;
	data->camera.shift_y = 0;
	data->camera.angle = 0.8;
	
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