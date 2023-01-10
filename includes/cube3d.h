/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez- <jibanez-@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:50:38 by jibanez-          #+#    #+#             */
/*   Updated: 2023/01/10 14:51:24 by jibanez-         ###   ########.fr       */
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

# ifndef WIDTH
#  define WIDTH 640
# endif

# ifndef HEIGHT
#  define HEIGHT 360
# endif

/*
**	=============
**	 Structures
**	=============
*/

typedef struct s_player
{
	double	x;
	double	y;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;

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
	t_player	p;

	bool		win;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_no;
	void		*img_so;
	void		*img_we;
	void		*img_ea;
}				t_mlx;

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


/*
**	error_handling.c
*/
void	error(char *msg, t_mlx *cube);
void	unload(t_mlx *cube);
int		quit(t_mlx *cube);

#endif