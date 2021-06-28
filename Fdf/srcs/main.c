#include <libft.h>
#include <fdf.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	int	fd;

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
		//ft_parse_map(fd);
	}
	return (0);
}