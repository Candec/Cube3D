/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:28:31 by tpereira          #+#    #+#             */
/*   Updated: 2023/01/26 15:10:34 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_player_dir(t_mlx *cube, char c)
{
	if (c == 'N')
	{
		cube->player.angle = M_PI / 2;
		cube->player.dirx = cos(cube->player.angle) * 50;
		cube->player.diry = -sin(cube->player.angle) * 50;
	}
	else if (c == 'S')
	{
		cube->player.angle = (3 * M_PI) / 2;
		cube->player.dirx = cos(cube->player.angle) * 50;
		cube->player.diry = -sin(cube->player.angle) * 50;
	}
	else if (c == 'E')
	{
		cube->player.angle = 2 * M_PI;
		cube->player.dirx = cos(cube->player.angle) * 50;
		cube->player.diry = -sin(cube->player.angle) * 50;
	}
	else if (c == 'W')
	{
		cube->player.angle = M_PI;
		cube->player.dirx = cos(cube->player.angle) * 50;
		cube->player.diry = -sin(cube->player.angle) * 50;
	}
	else
	{
		cube->player.angle = M_PI;
		cube->player.dirx = cos(cube->player.angle) * 50;
		cube->player.diry = -sin(cube->player.angle) * 50;
	}
}

void	init_player(t_mlx *cube)
{
	int	i;
	int	j;

	i = 0;
	while (i < (int)cube->map.height)
	{
		j = 0;
		while (j < (int)cube->map.width)
		{
			if (ft_strchr("NSEW", cube->map.map[i][j]))
			{
				printf("c = %c\n\n", cube->map.map[i][j]);
				cube->player.posx = j + 0.4 - 3;
				cube->player.posy = (i * 2) - 1 + 0.4;
				cube->player.dirx = 0;
				cube->player.diry = 0;
				cube->player.angle = 0;
				cube->player.planex = 0;					// what should we use this for? Is it the same as dirx?
				cube->player.planey = 0;
				init_player_dir(cube, cube->map.map[i][j]);
				return ;
			}
			j++;
		}
		i++;
	}
}
