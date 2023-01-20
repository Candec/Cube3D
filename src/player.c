/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:28:31 by tpereira          #+#    #+#             */
/*   Updated: 2023/01/20 16:01:41 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_player_dir(t_mlx *game, char c)
{
	if (c == 'N')
	{
		game->player.dirx = -1;
		game->player.planey = 0.66;
	}
	else if (c == 'S')
	{
		game->player.dirx = 1;
		game->player.planey = -0.66;
	}
	else if (c == 'E')
	{
		game->player.diry = 1;
		game->player.planex = 0.66;
	}
	else if (c == 'W')
	{
		game->player.diry = -1;
		game->player.planex = -0.66;
	}
}

void	init_player(t_mlx *cube)
{
	int	i;
	int	j;

	i = 0;
	while (i < cube->map.rows)
	{
		j = 0;
		while (j < cube->map.cols)
		{
			if (ft_strchr("NSEW", cube->map.map[i][j]))
			{
				cube->player.posx = j + 0.5;
				cube->player.posy = i + 0.5;
				cube->player.dirx = 0;
				cube->player.diry = 0;
				cube->player.planex = 0;
				cube->player.planey = 0;
				init_player_dir(cube, cube->map.map[i][j]);
				return ;
			}
			j++;
		}
		i++;
	}
}
