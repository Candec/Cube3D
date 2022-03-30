/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jibanez- <jibanez-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 16:50:38 by jibanez-          #+#    #+#             */
/*   Updated: 2022/03/29 15:43:21 by jibanez-         ###   ########.fr       */
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

typedef struct	s_map
{
	char	**map;
	int		height;
	int		width;
}				t_map;

typedef struct	s_mlx
{
	t_map	map;
}				t_mlx;

/*
**	=============
**		Files
**	=============
*/

/*
**	Main.c
*/

/*
**	Parse.c
*/
void	ft_parse(t_mlx *cube, char *map);
void	map_init(t_mlx *cube);
void	map_size(t_mlx *cube, char *map);


# endif