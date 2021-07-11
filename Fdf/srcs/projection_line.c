#include "fdf.h"
#include "math.h"

static void	rotate_x(double *y, double *z, double alpha)
{
	int	previous_y;

	previous_y = *y;
	*y = previous_y * cos(alpha) + *z * sin(alpha);
	*z = -previous_y * sin(alpha) + *z * cos(alpha);
}

/*
** Rotate coordinate by y axis
*/

static void	rotate_y(double *x, double *z, double beta)
{
	int	previous_x;

	previous_x = *x;
	*x = previous_x * cos(beta) + *z * sin(beta);
	*z = -previous_x * sin(beta) + *z * cos(beta);
}

/*
** Rotate coordinate by z axis
*/

static void	rotate_z(double *x, double *y, double gamma)
{
	int	previous_x;
	int	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = previous_x * cos(gamma) - previous_y * sin(gamma);
	*y = previous_x * sin(gamma) + previous_y * cos(gamma);
}

/*
** Convert coordinate to iso projection
*/

static void	iso(double *x, double *y, double z)
{
	double	previous_x;
	double	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = ((int)previous_x - (int)previous_y) * cos(0.523599);
	*y = -z + ((int)previous_x + (int)previous_y) * sin(0.523599);
}

t_point	project(t_point p, t_data *data)
{
	p.x *= data->camera.zoom;
	p.y *= data->camera.zoom;
	p.z *= data->camera.zoom / data->map.z_divisor;
	p.x -= (data->map.width * data->camera.zoom) / 2;
	p.y -= (data->map.height * data->camera.zoom) / 2;
	rotate_x(&p.y, &p.z, data->camera.alpha);
	rotate_y(&p.x, &p.z, data->camera.beta);
	rotate_z(&p.x, &p.y, data->camera.gamma);
	if (data->camera.projection == ISO)
		iso(&p.x, &p.y, p.z);
	p.x += (WIDTH - MENU_WIDTH) / 2 + data->camera.shift_x + MENU_WIDTH;
	p.y += (HEIGHT + data->map.height * data->camera.zoom) / 2
		+ data->camera.shift_y;
	return (p);
}
