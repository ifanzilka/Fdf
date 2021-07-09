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


void draw_line(t_point f, t_point s, t_data *data)
{
	t_point	delta;
	t_point	cur;
	t_point	vec;	
	int		coord[2];
	
	cur = f;
	delta.x = mod(s.x - f.x);
	delta.y = mod(s.y - f.y);
	vec = direction(f, s);
	coord[0] = delta.x - delta.y;
	while (cur.x != s.x || cur.y != s.y)
	{
		if (cur.x >= WIDTH || cur.y >= HEIGHT || cur.y < 0 || cur.x < 0)
 			break;
		if (cur .x > MENU_WIDTH)
			my_mlx_pixel_put(data, cur.x, cur.y, get_color(cur, f, s, delta));
		coord[1] = coord[0] * 2;
		if (coord[1] > -delta.y) 
		{
			coord[0] -= delta.y;
			cur.x += vec.x;
		}
		if (coord[1] < delta.x) 
		{
			coord[0] += delta.x; 
			cur.y += vec.y;
		}
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
				draw_line(project(new_point(x, y, data),data),
					project(new_point(x + 1, y, data),data), data);
			if (y != data->map.height - 1)
				draw_line(project(new_point(x, y, data), data),
					project(new_point(x, y + 1, data),data), data);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->mlx_win, data->img, 0, 0);
	print_menu(data);
}

