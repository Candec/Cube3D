/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:50:38 by jibanez-          #+#    #+#             */
/*   Updated: 2022/03/31 18:00:36 by jibanez-         ###   ########.fr       */
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
**	 Structures
**	=============
*/
typedef struct	s_rgb
{
	bool	fill;
	int		r;
	int		g;
	int		b;
}				t_rgb;

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
	void	*mlx_ptr;
	void	*win_ptr;
}				t_mlx;

/*
**	=============
**		Files
**	=============
*/

/*
**	Main.c
*/
int		main(int argc, char**argv);

/*
**	Parse.c
*/
void	ft_parse(t_mlx *cube, char *map);
void	map_init(t_mlx *cube);
void	map_info(t_mlx *cube, char *map);
void	scan_file(t_mlx *cube, char *line);
void	save_path(t_mlx *cube, char *dir, char *path);
void	save_rgb(t_rgb *rgb, char *rgb_code);
void	scan_map(t_mlx *cube, char *line);
int		ft_char_is_valid(char c);
int		info_complete(t_mlx *cube);
void	print_arr(char **arr);



/*
**	error_handling.c
*/
void	ft_error(char *msg, t_mlx *cube);
void	ft_exit(t_mlx *cube);




# endif