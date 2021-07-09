#include "libft.h"
#include "fdf.h"

static int	get_height(char *filename)
{
	char	*line;
	int		cnt;
	int		fd;

	fd = open(filename, O_RDONLY, 0);
	cnt = 0;
	while (get_next_line(fd, &line))
	{
		cnt++;
		free(line);
	}
	free(line);
	close(fd);
	return (cnt);
}

static size_t	ft_count_words(const char *s, char c)
{
	size_t	cnt;
	char	is_start;

	is_start = 1;
	cnt = 0;
	while (*s)
	{
		if (*(s++) != c)
		{
			if (is_start)
				cnt++;
			is_start = 0;
		}
		else
			is_start = 1;
	}
	return (cnt);
}

static int	get_width(char *filename)
{
	char	*line;
	int		width;
	int		fd;

	fd = open(filename, O_RDONLY, 0);
	get_next_line(fd, &line);
	width = ft_count_words(line, ' ');
	free(line);
	close(fd);
	return (width);
}

static void	fill_matrix(int *line_i, int num_i, char *line, t_map *map)
{
	char	**nums;
	char	*sub;
	int		i;

	i = 0;
	sub = NULL;
	nums = ft_split(line, ' ');
	while (nums[i])
	{
		line_i[i] = ft_atoi(nums[i]);
		sub = ft_strchr(nums[i], ',');
		if (sub != NULL)
			map->colors[num_i][i] = ft_atoi_base(++sub, 16);
		else
			map->colors[num_i][i] = -1;
		i++;
	}
	i = 0;
	while (nums[i])
	{
		free(nums[i]);
		i++;
	}
	free(nums);
}

int	ft_parse_map(char *filename, t_map *map)
{
	char	*line;
	int		i;
	int		fd;

	map->height = get_height(filename);
	map->width = get_width(filename);
	map->z_matrix = (int **)malloc_x(sizeof(int *) * (map->height + 1));
	map->colors = (int **)malloc_x(sizeof(int *) * (map->height + 1));
	i = -1;
	while (++i < map->height)
	{
		map->z_matrix[i] = (int *)malloc_x(sizeof(int) * (map->width + 1));
		map->colors[i] = (int *)malloc_x(sizeof(int) * (map->width + 1));
	}
	fd = open(filename, O_RDONLY);
	i = -1;
	while (get_next_line(fd, &line) && ++i < map->height)
	{	
		fill_matrix(map->z_matrix[i], i, line, map);
		free(line);
	}
	free(line);
	close(fd);
	return (0);
}
