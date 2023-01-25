/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:28:31 by tpereira          #+#    #+#             */
/*   Updated: 2023/01/25 08:32:01 by tpereira         ###   ########.fr       */
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
	while (i < (int)cube->map.height)
	{
		j = 0;
		while (j < (int)cube->map.width)
		{
			if (ft_strchr("NSEW", cube->map.map[i][j]))
			{
				cube->player.posx = j + 0.4 - 3;
				cube->player.posy = (i * 2) - 1 + 0.4;
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
