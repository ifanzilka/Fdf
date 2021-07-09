#include "fdf.h"
#include "libft.h"

int	map_max_z(t_map *map)
{
	int	max;
	int	i;
	int	j;

	max = map->z_matrix[0][0];
	i = 0;
	while (i <= map->height - 1)
	{
		j = 0;
		while (j <= map->width - 1)
		{
			if (map->z_matrix[i][j] > max)
				max = map->z_matrix[i][j];
			j++;
		}
		i++;
	}
	return (max);
}

int	map_min_z(t_map *map)
{
	int	min;
	int	i;
	int	j;

	min = map->z_matrix[0][0];
	i = 0;
	while (i < map->height - 1)
	{
		j = 0;
		while (j < map->width - 1)
		{
			if (map->z_matrix[i][j] < min)
				min = map->z_matrix[i][j];
			j++;
		}
		i++;
	}
	return (min);
}
