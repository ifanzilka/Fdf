#include "fdf.h"
#include "mlx.h"

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

void	draw_line(t_point a, t_point b, t_data *data)
{
	t_point	a_;
	t_point	delta;
	t_point	cur;
	double	step[3];

	a_ = a;
	delta.x = mod(a.x - b.x);
	delta.y = mod(a.y - b.y);
	cur.x = a.x;
	cur.y = a.y;
	step[0] = b.x - a.x;
	step[1] = b.y - a.y;
	step[2] = max(mod(step[0]), mod(step[1]));
	step[0] /= step[2];
	step[1] /= step[2];
	while ((int)(cur.x - b.x) || (int)(cur.y - b.y))
	{
		if (cur.x >= WIDTH || cur.y >= HEIGHT || cur.x < 0 || cur.y < 0)
			break ;
		if (cur.x > MENU_WIDTH)
			my_mlx_pixel_put(data, cur.x, cur.y, get_color(cur, a_, b, delta));
		cur.x += step[0];
		cur.y += step[1];
	}
}

void	draw(t_data *data)
{
	int	x;
	int	y;

	draw_background(data);
	y = 0;
	while (y < data->map.height)
	{
		x = 0;
		while (x < data->map.width)
		{
			if (x != data->map.width - 1)
				draw_line(project(new_point(x, y, data), data),
					project(new_point(x + 1, y, data), data), data);
			if (y != data->map.height - 1)
				draw_line(project(new_point(x, y, data), data),
					project(new_point(x, y + 1, data), data), data);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);
	print_menu(data);
}
