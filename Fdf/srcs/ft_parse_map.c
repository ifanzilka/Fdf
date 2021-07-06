#include "libft.h"
#include "fdf.h"

typedef enum
{
	false,
	true
}	t_bool;


/*
** Check is this char present in selected numeral system
*/

static int		ft_isdigit_base(char c, int base)
{
	const char	*digits = "0123456789ABCDEF";
	int			i;

	i = 0;
	while (i < base)
	{
		if (digits[i] == ft_toupper(c))
			return (i);
		i++;
	}
	return (-1);
}

/*
** Check is this string contain prefix of its numeral system
*/

static t_bool	ft_has_prefix(const char *str, int base)
{
	size_t	i;

	i = 0;
	if (base == 2 || base == 8 || base == 16)
	{
		if (str[i++] != '0')
			return (false);
		if (base == 2 && (str[i] == 'b' || str[i] == 'B'))
			return (true);
		if (base == 16 && (str[i] == 'x' || str[i] == 'X'))
			return (true);
		if (base == 8)
			return (true);
	}
	return (false);
}

/*
** Check is this string a number according to the selected numeral system
*/

t_bool			ft_isnumber(char *str, int base)
{
	size_t		i;
	size_t		digits;

	i = 0;
	digits = 0;
	while (ft_isspace(str[i]))
		i++;
	if (base != 10 && !ft_has_prefix(&str[i], base))
		return (false);
	if (base == 2 || base == 16)
		i += 2;
	else if (base == 8)
		i++;
	else if (base == 10 && (str[i] == '-' || str[i] == '+'))
		i++;
	while (ft_isdigit_base(str[i], base) >= 0)
	{
		i++;
		digits++;
	}
	return ((!str[i] && digits) ? true : false);
}

/*
** Convert string to number according to the selected numeral system
*/

int				ft_atoi_base(const char *str, int base)
{
	unsigned long	result;
	size_t			i;
	int				sign;

	result = 0;
	i = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (base != 10 && !ft_has_prefix(&str[i], base))
		return (false);
	if (base == 2 || base == 16)
		i += 2;
	else if (base == 8)
		i++;
	else if (base == 10 && (str[i] == '-' || str[i] == '+'))
		sign = (str[i++] == '-') ? -1 : 1;
	while (ft_isdigit_base(str[i], base) >= 0)
		result = result * base + ft_isdigit_base(str[i++], base);
	return ((int)(result * sign));
}

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

static void	fill_matrix(int *z_line, int k, char *line, t_map *map)
{
	char	**nums;
	char	*sub;
	int		i;
	
	
	i = 0;
	sub = NULL;
	nums = ft_split(line, ' ');
	while (nums[i])
	{
		printf("nums[i]: %s\n",nums[i]);
		z_line[i] = ft_atoi(nums[i]);
		sub = ft_strchr(nums[i], ',');
		if (sub != NULL)
		{
			map->colors[k][i] = ft_atoi_base(sub, 16);
			printf("int:%d\ns: %s\n color:%d\n",z_line[i],sub + 1, map->colors[k][i]);
		}
		else
			map->colors[k][i] = -1;

		i++;
	}
	i = 0;
	while(nums[i++])
		free(nums[i]);
	free(nums);
}

int map_max_z(t_map *map)
{
	int max = -10000;
	int i;
	int j;

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

int map_min_z(t_map *map)
{
	int min = 10000;
	int i;
	int j;

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

int	ft_parse_map(char *filename, t_map *map)
{
	char	*line;
	int		i;
	int		fd;

	map->height = get_height(filename);
	map->width = get_width(filename);
	map->z_matrix = (int **)malloc_x(sizeof(int *) * (map->height + 1));
	map->colors = (int **)malloc_x(sizeof(int *) * (map->height + 1));
	i = 0;
	printf("width: %d\nheight: %d\n ",map->width, map->height);
	while (i < map->height)
	{
		map->z_matrix[i] = (int *)malloc_x(sizeof(int) * (map->width + 1));
		map->colors[i] = (int *)malloc_x(sizeof(int) * (map->width + 1));
		i++;
	}
	fd = open(filename, O_RDONLY);
	i = 0;
	printf("2\n");
	while (get_next_line(fd, &line) && i < map->height )
	{	
		fill_matrix(map->z_matrix[i], i, line, map);
		i++;
		free(line);
	}
	printf("3\n");
	free(line);
	map->z_matrix[i] = NULL;
	close(fd);
	map->z_max = map_max_z(map);
	map->z_min = map_min_z(map);

	return (0);
}