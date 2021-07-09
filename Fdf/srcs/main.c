#include <libft.h>
#include <fdf.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	t_data 	data;
	int		fd;
	
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
		data.map.z_max = map_max_z(&data.map);
		data.map.z_min = map_min_z(&data.map);
		
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