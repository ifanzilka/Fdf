#include "fdf.h"
#include "mlx.h"
#include <stdio.h>

int	ft_is_projection(int code)
{
	if (code == A || code == D || code == W
		|| code == S || code == Q || code == E)
	{
		return (1);
	}
	return (0);
}

int	ft_keyyboard2(int code, t_data *data)
{
	if (code == S)
		data->camera.alpha += 0.05;
	if (code == W)
		data->camera.alpha -= 0.05;
	if (code == A)
		data->camera.beta += 0.05;
	if (code == D)
		data->camera.beta -= 0.05;
	if (code == Q)
		data->camera.gamma += 0.05;
	if (code == E)
		data->camera.gamma -= 0.05;
	return (0);
}
