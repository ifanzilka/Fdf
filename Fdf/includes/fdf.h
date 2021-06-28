#ifndef FDF_H
# define FDF_H


# define NAME_PROGRAMM "Fdf"
# define WIDTH 1000
# define HEIGHT 1000 
# define WHIITE 0xffffff
# define RED 0xe80c0c
# define ZOOM 20


enum error
{
	err_argv = 1,
	err_open = 2
};

typedef struct		s_map
{
	int 			height;
	int 			width;
	int				**z_matrix;
}					t_map;

typedef struct		s_data
{
	t_map			map;
	int				zoom;
	int 			color;
	void			*mlx_win;
	void			*mlx_ptr;
}					t_data;



int	ft_parse_map(char *filename, t_map *map);

#endif