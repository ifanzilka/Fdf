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
# define MOUSE_UP 5
# define MOUSE_DOWN 4
# define MOUSE_LEFT 1
# define MOUSE_RIGHT 2
# define MOUSE_MIDDLE 3

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
# define MOUSE_UP 5
# define MOUSE_DOWN 4
# define MOUSE_LEFT 1
# define MOUSE_RIGHT 2
# define MOUSE_MIDDLE 3

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

typedef enum
{
	ISO,
	PARALLEL
}	t_projection;

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

typedef struct		s_mouse
{
	char			is_pressed;
	int				x;
	int				y;
	int				previous_x;
	int				previous_y;
}					t_mouse;

typedef struct			s_camera
{
	t_projection		projection;
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
	t_mouse			mouse;
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


typedef struct	s_point
{
	double			x;
	double			y;
	double			z;
	int			color;
}				t_point;


/* Rgb Functions */

int 			ft_trgbtoint(t_rgb rgb);
int				ft_create_rgb(int r, int g, int b);
t_rgb			ft_rgb_mult_db(t_rgb rgb, double a);
t_rgb			ft_rgb_plus_rgb(t_rgb a, t_rgb b);
t_rgb 			ft_create_trgb(int color);

/* Colors */

int	get_color(t_point current, t_point start, t_point end, t_point delta);
int	get_default_color(int z, t_map *map);

/* Map fun */

int	ft_parse_map(char *filename, t_map *map);
int	ft_atoi_base(const char *str, int base);
int map_min_z(t_map *map);
int map_max_z(t_map *map);

void *malloc_x(size_t size);




/* Keyboard */

int	ft_keyyboard(int keycode, t_data *data);



/* Draw */
void	draw(t_data *data);
void	print_menu(t_data *data);

/* Projection */

t_point		project(t_point p, t_data *data);

/* Math Utils */

double	max(double a, double b);
int 	mod(int i);
int 	ft_min(int a , int b);


/* Points */

t_point direction(t_point f, t_point s);
t_point	new_point(int x, int y, t_data *data);

/* Mlx fun */
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		ft_close_win(t_data *data);
void	ft_init_mlx(t_data *data);


/* Camera */
void	zooming(int code, t_data *data);

#endif