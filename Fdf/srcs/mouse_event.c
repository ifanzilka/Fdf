#include "fdf.h"

int	mouse_press(int button, int x, int y, void *param)
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
	return (0);
}

/*
** Handle mouse release
*/

int	mouse_release(int button, int x, int y, void *param)
{
	t_data	*data;

	(void)x;
	(void)y;
	(void)button;
	data = (t_data *)param;
	data->mouse.is_pressed = false;
	return (0);
}

/*
** Handle mouse move
*/

int	mouse_move(int x, int y, void *param)
{
	t_data	*data;

	data = (t_data *)param;
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
