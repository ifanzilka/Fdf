#include "fdf.h"
#include "mlx.h"
#include "math.h"
#include "libft.h"

/* In backgroung color */

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

/* Funcrion in draw line in two point*/

void	draw_line(t_point a, t_point b, t_data *data)
{
	t_point	a_;
	t_point	delta;
	t_point	cur;
	double	step_x_y_max[3];

	a_ = a;
	delta.x = fabs(a.x - b.x);
	delta.y = fabs(a.y - b.y);
	cur.x = a.x;
	cur.y = a.y;
	step_x_y_max[0] = b.x - a.x;
	step_x_y_max[1] = b.y - a.y;
	step_x_y_max[2] = fmax(fabs(step_x_y_max[0]), fabs(step_x_y_max[1]));
	step_x_y_max[0] /= step_x_y_max[2];
	step_x_y_max[1] /= step_x_y_max[2];
	while ((int)(cur.x - b.x) || (int)(cur.y - b.y))
	{
		if (cur.x >= WIDTH || cur.y >= HEIGHT || cur.x < 0 || cur.y < 0)
			break ;
		if (cur.x > MENU_WIDTH)
			my_mlx_pixel_put(data, cur.x, cur.y, get_color(cur, a_, b, delta));
		cur.x += step_x_y_max[0];
		cur.y += step_x_y_max[1];
	}
}

/* Cicle for all map*/

void	draw(t_data *data)
{
	int	x;
	int	y;

	data->img = mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
	data->data_addr = mlx_get_data_addr(data->img, &(data->bits_per_pixel),
			&(data->size_line), &(data->endian));
	draw_background(data);
	y = 0;
	while (y < data->map.height)
	{
		x = -1;
		while (++x < data->map.width)
		{
			if (x != data->map.width - 1)
				draw_line(project(new_point(x, y, data), data),
					project(new_point(x + 1, y, data), data), data);
			if (y != data->map.height - 1)
				draw_line(project(new_point(x, y, data), data),
					project(new_point(x, y + 1, data), data), data);
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);
	print_menu(data);
	mlx_destroy_image(data->mlx_ptr, data->img);
}
