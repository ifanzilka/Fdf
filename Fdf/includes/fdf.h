#ifndef FDF_H
# define FDF_H
# include <stdlib.h>
# include "keycode.h"

# ifndef COLOR_H
#  define COLOR_H
#  define TEXT_COLOR			0xEAEAEA
#  define BACKGROUND			0x222223
#  define MENU_BACKGROUND	0x1E1E1E
#  define COLOR_DISCO		0x9A1F6A
#  define COLOR_BRICK_RED	0xC2294E
#  define COLOR_FLAMINGO		0xEC4B27
#  define COLOR_JAFFA		0xEF8633
#  define COLOR_SAFFRON		0xF3AF3D
#  define WHIITE 			0xffffff
#  define RED 				0xe80c0c
# endif

# define MENU_WIDTH		250
# define NAME_PROGRAMM "Fdf"
# define WIDTH 1920
# define HEIGHT 1080 

typedef enum e_projection
{
	ISO,
	PARALLEL
}			t_projection;

typedef enum e_error
{
	err_argv = 1,
	err_open = 2
}			t_error;

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct s_map
{
	int		height;
	int		width;
	int		**z_matrix;
	int		**colors;
	int		z_min;
	int		z_max;
	int		z_range;
	float	z_divisor;
}				t_map;

typedef struct s_mouse
{
	char	is_pressed;
	int		x;
	int		y;
	int		previous_x;
	int		previous_y;
}				t_mouse;

typedef struct s_camera
{
	t_projection	projection;
	int				zoom;
	double			alpha;
	double			beta;
	double			gamma;
	int				shift_x;
	int				shift_y;
}				t_camera;

typedef struct s_data
{
	t_map		map;
	t_mouse		mouse;
	t_camera	camera;
	int			color;
	void		*mlx_win;
	void		*mlx_ptr;
	void		*img;
	char		*data_addr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}				t_data;

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}				t_rgb;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
	int		color;
}				t_point;

void	*malloc_x(size_t size);

/* Map fun */

int		ft_parse_map(char *filename, t_map *map);
int		ft_atoi_base(const char *str, int base);
int		map_min_z(t_map *map);
int		map_max_z(t_map *map);

/* Draw */

void	draw(t_data *data);
void	print_menu(t_data *data);

/* Projection */

t_point	project(t_point p, t_data *data);

/* Points */

t_point	direction(t_point f, t_point s);
t_point	new_point(int x, int y, t_data *data);

/* Rgb Functions */

int		ft_trgbtoint(t_rgb rgb);
int		ft_create_rgb(int r, int g, int b);
t_rgb	ft_rgb_mult_db(t_rgb rgb, double a);
t_rgb	ft_rgb_plus_rgb(t_rgb a, t_rgb b);
t_rgb	ft_create_trgb(int color);

/* Colors */

int		get_color(t_point current, t_point start, t_point end, t_point delta);
int		get_default_color(int z, t_map *map);

/* Keyboard */

int		ft_keyyboard(int keycode, t_data *data);
int 	ft_is_projection(int code);
int		ft_keyyboard2(int code, t_data *data);

/* Mlx fun */

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		ft_close_win(t_data *data);
void	ft_init_mlx(t_data *data);

/* Mouse Events */

int		mouse_move(int x, int y, void *param);
int		mouse_release(int button, int x, int y, void *param);
int		mouse_press(int button, int x, int y, void *param);
void	zooming(int code, t_data *data);

#endif