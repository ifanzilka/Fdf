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
	//printf("mouse_press button: %d x: %d y: %d\n", button, x, y);
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
	//printf("MOUSE RELEASE button: %d x: %d y: %d\n", button, x, y);
	return (0);
}

/*
** Handle mouse move
*/

int	mouse_move(int x, int y, void *param)
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
