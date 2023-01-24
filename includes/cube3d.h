/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:50:38 by jibanez-          #+#    #+#             */
/*   Updated: 2023/01/24 13:14:24 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <math.h>
# include <mlx.h>
# include <variables.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <stdbool.h>
# include <sys/wait.h>
# include "../libft_ext/libft.h"

/*
**	=============
**	 Macros
**	=============
*/

# ifndef SQ_S
#  define SQ_S 128
# endif

# ifndef WIN_WIDTH
#  define WIN_WIDTH 1920
# endif

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 1200
# endif

# ifndef WIDTH
#  define WIDTH 640
# endif

# ifndef HEIGHT
#  define HEIGHT 360
# endif

# ifndef TILE_SIZE
#  define TILE_SIZE 64
# endif

# ifndef WALL_HEIGHT
#  define WALL_HEIGHT 64
# endif

# ifndef PI
#  define PI 3.14159265358979323846
# endif

/*
**	=================
**	 Color Macros
**	=================
*/

# ifndef RED
#  define RED 0xFF0000
# endif

# ifndef GREEN
#  define GREEN 0x00FF00
# endif

# ifndef BLUE
#  define BLUE 0x0000FF
# endif

# ifndef WHITE
#  define WHITE 0xFFFFFF
# endif

# ifndef YELLOW
#  define YELLOW 0xFFFF00
# endif

# ifndef BLACK
#  define BLACK 0x000000
# endif


/*
**	=================
**	 Keyboard Macros
**	=================
*/

# ifndef ESCAPE
#  define ESCAPE 53
# endif

# ifndef FORWARD
#  define FORWARD 65362
# endif

# ifndef BACKWARD
#  define BACKWARD 65364
# endif

# ifndef LEFT
#  define LEFT 65361
# endif

# ifndef RIGHT
#  define RIGHT 65363
# endif

/*
**	=============
**	 Structures
**	=============
*/

typedef struct s_player
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	angle;
	double	planex;
	double	planey;
	double	height;
	double	fov;
	double	position;

	bool	e;
}				t_player;

typedef struct s_img
{
	void	*img;
	int		*data;

	int		size_l;
	int		bpp;
	int		endian;
	int		img_width;
	int		img_height;
}				t_img;

typedef struct s_map
{
	char	**map;
	size_t	height;
	size_t	width;
	int		rows;
	int		cols;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	t_rgb	f_rgb;
	t_rgb	c_rgb;
}				t_map;

typedef struct s_mlx
{
	t_map		map;
	t_img		frame;
	t_player	player;

	bool		win;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_no;
	void		*img_so;
	void		*img_we;
	void		*img_ea;
}				t_mlx;

typedef struct s_game
{
	t_mlx		cube;
}				t_game;


/*
**	=============
**		Files
**	=============
*/

/*
**	Main.c
*/
// int		main(int argc, char**argv);
void	init(t_mlx *cube);
void	parse(t_mlx *cube, char *map);
void	play(t_mlx *cube);

/*
**	Parse.c
*/
void	info(t_mlx *cube, char *map);
void	scan_file(t_mlx *cube, char *line);
void	save_path(t_mlx *cube, char *dir, char *path);
void	scan_map(t_mlx *cube, char *line);
int		info_complete(t_mlx *cube);

/*
**	Check.c
*/
void	set_p(size_t i, size_t j, t_mlx *cube);
void	validate_chr(t_mlx *cube);
void	validate_map(t_mlx *cube);
bool	check_h(t_mlx *cube, size_t i, size_t j);
bool	check_v(t_mlx *cube, size_t i, size_t j);

/*
**	Play.c
*/
void	start_mlx_and_window(t_mlx *cube);
void	load_img(t_mlx *cube);
int		xpm_to_image_wrapper(t_mlx *data, void *img, char *filename);
int		keypress(int keysym, t_mlx *cube);
int		draw_frame(t_mlx *cube);

/*
**	Draw.c
*/
void	add_pixel(t_img *frame, int rgb, int x, int y);
void	draw_bg(t_mlx *cube);
void	draw_wall(t_mlx *cube, int x, int y, int height);
void	draw_player(t_mlx *cube, int x, int y, int height);
void	draw_square(t_mlx *cube, int x, int y, int height, int color);
void	blackout(t_mlx *cube);
void	draw_line(t_mlx *cube, int x1, int y1, int x2, int y2, int color);
void	draw_circle(t_mlx *cube, int x, int y, int radius, int color);

/*
**	error_handling.c
*/
void	error(char *msg, t_mlx *cube);
void	unload(t_mlx *cube);
int		quit(t_mlx *cube);

/*
**	player.c
*/
void	init_player_dir(t_mlx *cube, char c);
void	init_player(t_mlx *cube);
void	draw_player_2D(t_mlx *cube);

/*
**	map.c
*/
void	draw_map_2D(t_mlx *game);

#endif