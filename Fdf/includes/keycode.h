#ifndef KEYCODE_H
# define KEYCODE_H

# ifdef DARWIN
#  define UP 125
#  define DOWN 126
#  define LEFT 123
#  define RIGHT 124
#  define PLUS 69
#  define MINUS 78
#  define Z 6
#  define X 7
#  define W 13
#  define S 1
#  define ESC 53
#  define MOUSE_UP 5
#  define MOUSE_DOWN 4
#  define MOUSE_LEFT 1
#  define MOUSE_RIGHT 2
#  define MOUSE_MIDDLE 3
#  define DIVIZOR_MINUS 43
#  define DIVIZOR_PLUS 47
#  define I 34
#  define P 35

# else
#  define UP 65364
#  define DOWN 65362
#  define LEFT 65361
#  define RIGHT 65363
#  define PLUS 61
#  define MINUS 45
#  define Z 6
#  define X 7
#  define W 13
#  define S 1
#  define ESC 65307
#  define MOUSE_UP 5
#  define MOUSE_DOWN 4
#  define MOUSE_LEFT 1
#  define MOUSE_RIGHT 2
#  define MOUSE_MIDDLE 3
#  define DIVIZOR_MINUS 43
#  define DIVIZOR_PLUS 47
#  define I 34
#  define P 35
# endif

#endif