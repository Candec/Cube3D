/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez- <jibanez-@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:50:38 by jibanez-          #+#    #+#             */
/*   Updated: 2022/12/22 16:08:43 by jibanez-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUBE3D_H
#  define CUBE3D_H

# include <mlx.h>
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

# if __Linux__
# include <X11/X.h>
# include <X11/keysym.h>
# include "../minilibx/mlx.h"
# endif

/*
**	=============
**	 Macros
**	=============
*/

# ifndef SQ_S
#  define SQ_S 128
# endif

/*
**	=============
**	 Structures
**	=============
*/

typedef struct	s_map
{
	char	**map;
	size_t	height;
	size_t	width;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	t_rgb	F_rgb;
	t_rgb	C_rgb;
}				t_map;

typedef struct	s_mlx
{
	t_map	map;
	bool	mlx_init;
	bool	win_init;
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_NO;
	void	*img_SO;
	void	*img_WE;
	void	*img_EA;
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
void	validate_chr(t_mlx *cube);
void	validate_map(t_mlx *cube);
bool	check_h(t_mlx *cube, size_t i, size_t j);
bool	check_v(t_mlx *cube, size_t i, size_t j);

/*
**	Play.c
*/
void	start_mlx_and_window(t_mlx *cube);
int		xpm_to_image_wrapper(t_mlx *data, void* img, char *filename);



/*
**	error_handling.c
*/
void	error(char *msg, t_mlx *cube);
int		quit(t_mlx *cube);

# endif