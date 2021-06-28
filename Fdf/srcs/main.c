#include <libft.h>
#include <fdf.h>
#include <fcntl.h>
#include "mlx.h"
#include "math.h"


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

void 	format3d(float *x, float *y, int z)
{
	*x = (*x - *y) * cos(0.8);
	*y = (*x + *y) * sin(0.8) - z;

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
		format3d(&x, &y, z);
	format3d(&x1, &y1, z1);
	
	x *= data->zoom;
	y *= data->zoom;
	x1 *= data->zoom;
	y1 *= data->zoom;
	
	if (z || z1)
		data->color = RED;
	else
		data->color = WHIITE;
	

	x_step = x1 - x;
 	y_step = y1 - y;



	x +=150;
	y +=150;
	x1 +=150;
	y1 +=150;
	
	maxi = max(mod(x_step), mod(y_step));
	x_step /= maxi;
	y_step /= maxi;
	while ((int)(x  - x1) || (int)(y - y1))
	{
		mlx_pixel_put(data->mlx_ptr, data->mlx_win, x, y, data->color);
		x += x_step;
		y += y_step;
		if (x > WIDTH || y > HEIGHT || y < 0 || x < 0)
			break ;
	}
}

void draw(t_data *data)
{
	int x;
	int y;

	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (x < data->map.width - 1)
				draw_line(x, y, x + 1, y , data);
			if (y < data->map.height - 1)
				draw_line(x, y, x, y + 1, data);
			x++;
		}
		y++;
	}
}

int	ft_keyyboard(int keycode)
{
	printf("Keycode: %d\n", keycode);
	return (0);
}

void	ft_init_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, NAME_PROGRAMM);
	data->zoom = ZOOM;
	//draw_line(20, 20 , 100 , 100, data);
	draw(data);
	mlx_key_hook(data->mlx_win, ft_keyyboard, NULL);
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
		ft_init_mlx(&data);
	}
	return (0);
}