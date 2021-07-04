#include "libft.h"

int	check_end(char **reminder, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*reminder)[i] != 0 && (*reminder)[i] != '\n')
		i++;
	if ((*reminder)[i] == '\n')
	{
		*line = ft_substr(*reminder, 0, i);
		tmp = *reminder;
		*reminder = ft_strdup(*reminder + i + 1);
		free(tmp);
		return (1);
	}
	else
	{
		*line = ft_strdup(*reminder);
		free(*reminder);
		*reminder = 0;
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	char		buf[21];
	int			read_bite;
	static char	*reminder = 0;
	char		*tmp;

	read_bite = 1;
	while (read_bite)
	{
		read_bite = read(fd, buf, 20);
		if (read_bite < 0 || !line)
			return (-1);
		buf[read_bite] = 0;
		if (reminder)
		{
			tmp = reminder;
			reminder = ft_strjoin(reminder, buf);
			free(tmp);
		}
		else
			reminder = ft_strdup(buf);
		if (ft_strchr(reminder, '\n'))
			break ;
	}
	return (check_end(&reminder, line) || read_bite || reminder);
}
