#include "fdf.h"

void	zooming(int code, t_data *data)
{
	if (code == MINUS || code == MOUSE_DOWN)
		data->camera.zoom--;
	if (code == PLUS || code == MOUSE_UP)
		data->camera.zoom++;
	if (data->camera.zoom < 1)
		data->camera.zoom = 1;	
}