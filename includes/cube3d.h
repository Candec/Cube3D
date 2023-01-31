/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:50:38 by jibanez-          #+#    #+#             */
/*   Updated: 2023/01/31 14:48:48 by tpereira         ###   ########.fr       */
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
#  define WIN_WIDTH 1366
# endif

# ifndef WIN_HEIGHT
#  define WIN_HEIGHT 768
# endif

// TIAGO WIDESCREEN RESOLUTION SETTINGS

// # ifndef WIN_WIDTH
// #  define WIN_WIDTH 2560
// # endif

// # ifndef WIN_HEIGHT
// #  define WIN_HEIGHT 1440
// # endif

# ifndef WIDTH
#  define WIDTH 640
# endif

# ifndef HEIGHT
#  define HEIGHT 360
# endif

# ifndef TILE_SIZE
#  define TILE_SIZE 48
# endif

# ifndef WALL_HEIGHT
#  define WALL_HEIGHT 32
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
**	=============
**	 Structures
**	=============
*/

typedef struct s_player
{
	t_coord pos;
	float	posx;
	float	posy;
	float	dirx;
	float	diry;
	float	angle;
	float	planex;
	float	planey;
	float	height;
	float	fov;
	float	position;

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

typedef struct s_raycast
{
	t_coord	end;
	t_coord	dir;
	t_coord	grid;
	t_coord	len;
	t_coord	step;
	t_coord	step_size;
	t_coord	intersection;
	double	distance;
	bool	reach_end;
}				t_raycast;

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
void	draw_line(t_mlx *cube, float x1, float y1, float x2, float y2, int color);
void	draw_circle(t_mlx *cube, int x, int y, int radius, int color);
void	bresenham(t_mlx *cube, float x1, float y1, int color);
void	draw_fov(t_mlx *cube);
void	draw_rays_2D(t_mlx *cube);
float	distance(float x1, float y1, float x2, float y2);

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

/*
**	Math.c
*/
float	deg_to_rad(float deg);
int		fix_angle(float *angle);

/*
**	dda.c
*/
t_coord	dda(t_mlx *cube, double x, double y);

#endif