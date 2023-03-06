/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpereira <tpereira@42Lisboa.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:28:31 by tpereira          #+#    #+#             */
/*   Updated: 2023/03/06 14:46:06 by tpereira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_player_dir(t_mlx *cube, char c)
{
	if (c == 'N')
		cube->player.angle = PI3 + 0.00001;
	else if (c == 'S')
		cube->player.angle = PI2 + 0.00001;
	else if (c == 'E')
		cube->player.angle = PII + 0.00001;
	else if (c == 'W')
		cube->player.angle = PI + 0.00001;
	else
		cube->player.angle = PI3 + 0.00001;
	cube->player.dirx = cos(cube->player.angle) * 5;
	cube->player.diry = sin(cube->player.angle) * 5;
}

void	init_player(t_mlx *cube)
{
	int	i;
	int	j;

	i = -1;
	while (++i < (int)cube->map.height)
	{
		j = -1;
		while (++j < (int)cube->map.width)
		{
			if (ft_strchr("NSEW", cube->map.map[i][j]))
			{
				if (cube->map.map[i][j] == '\0')
					break ;
				cube->player.posx = j + 0.4f;
				cube->player.posy = i + 0.4f;
				cube->player.angle = 1.5;
				cube->player.fov = 1.5;
				cube->player.dirx = cos(cube->player.angle) * 5;
				cube->player.diry = sin(cube->player.angle) * 5;
				init_player_dir(cube, cube->map.map[i][j]);
				return ;
			}
		}
	}
}
