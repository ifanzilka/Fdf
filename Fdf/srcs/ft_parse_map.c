#include "libft.h"
#include "fdf.h"

static int get_height(char *filename)
{
	char	*line;
	int		cnt;
	int		fd;

	fd = open(filename, O_RDONLY,0);
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
		if (*(s++) != c)
		{
			if (is_start)
				cnt++;
			is_start = 0;
		}
		else
			is_start = 1;
	return (cnt);
}

static int get_width(char *filename)
{
	char	*line;
	int		width;
	int 	fd;

	fd = open(filename, O_RDONLY,0);
	get_next_line(fd, &line);
	width = ft_count_words(line, ' ');
	free(line);
	close(fd);
	return (width);
}

static void	fill_matrix(int *z_line, char *line)
{
	char	**nums;
	int		i;
	
	i = 0;
	nums = ft_split(line, ' ');
	while (nums[i])
	{
		z_line[i] = ft_atoi(nums[i]);
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
	i = 0;
	printf("width: %d\nheight: %d\n ",map->width, map->height);
	while (i < map->height)
		map->z_matrix[i++] = (int *)malloc_x(sizeof(int) * (map->width + 1));
	fd = open(filename, O_RDONLY);
	i = 0;
	while (get_next_line(fd, &line) && i < map->height )
	{	
		fill_matrix(map->z_matrix[i++], line);
		free(line);
	}
	free(line);
	map->z_matrix[i] = NULL;
	close(fd);
	printf("111\n");
	return (0);
}