#ifndef FDF_H
# define FDF_H
#include <stdlib.h>

#ifdef DARWIN
# define UP 125
# define DOWN 126
# define LEFT 123
# define RIGHT 124
# define PLUS 69
# define MINUS 78
# define Z 6
# define X 7
# define W 13
# define S 1
# define ESC 53
#else

# define UP 65364
# define DOWN 65362
# define LEFT 65361
# define RIGHT 65363
# define PLUS 61
# define MINUS 45
# define Z 6
# define X 7
# define W 13
# define S 1
# define ESC 65307

# endif


#ifndef COLOR_H

# define COLOR_H

# define TEXT_COLOR			0xEAEAEA
# define BACKGROUND			0x222223
# define MENU_BACKGROUND	0x1E1E1E

# define COLOR_DISCO		0x9A1F6A
# define COLOR_BRICK_RED	0xC2294E
# define COLOR_FLAMINGO		0xEC4B27
# define COLOR_JAFFA		0xEF8633
# define COLOR_SAFFRON		0xF3AF3D

#endif

# define MENU_WIDTH		250
# define NAME_PROGRAMM "Fdf"
# define WIDTH 1920
# define HEIGHT 1080 
# define WHIITE 0xffffff
# define RED 0xe80c0c
# define ZOOM 20



enum error
{
	err_argv = 1,
	err_open = 2
};

typedef enum
{
	false,
	true
}	t_bool;



typedef struct		s_map
{
	int 			height;
	int 			width;
	int				**z_matrix;
	int				**colors;
	int				z_min;
	int				z_max;
	int				z_range;
}					t_map;

// typedef struct		s_mouse
// {
// 	char			is_pressed;
// 	int				x;
// 	int				y;
// 	int				previous_x;
// 	int				previous_y;
// }					t_mouse;

typedef struct			s_camera
{
	//t_projection		projection;
	int					zoom;
	double				alpha;
	double				beta;
	double				gamma;
	float				z_divisor;
	float				angle;
	int					shift_x;
	int					shift_y;
}						t_camera;

typedef struct		s_data
{
	t_map			map;
	//t_mouse			mouse;
	t_camera		camera;
	int 			color;

	void			*mlx_win;
	void			*mlx_ptr;
	void			*img;
	char			*data_addr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}					t_data;


typedef struct	s_rgb
{
	int	red;
	int	green;
	int	blue;
}				t_rgb;

int				create_rgb(int r, int g, int b);
t_rgb			ft_rgb_mult_db(t_rgb rgb, double a);
t_rgb			ft_rgb_plus_rgb(t_rgb a, t_rgb b);


int	ft_parse_map(char *filename, t_map *map);
int	ft_atoi_base(const char *str, int base);
int map_min_z(t_map *map);
int map_max_z(t_map *map);

void *malloc_x(size_t size);




//
void	print_menu(t_data *data);

#endif