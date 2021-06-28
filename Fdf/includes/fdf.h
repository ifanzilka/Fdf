#ifndef FDF_H
# define FDF_H

enum error
{
	err_argv = 1,
	err_open = 2
};

typedef struct		s_map
{
	int 			height;
	int 			width;
	int				**z;
}					t_map;

#endif